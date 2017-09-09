package com.gensym.nols.deploy;
/*
 *		Wrapper class for Gensym OnlineProcessor.
 *		Cannot be encrypted!
 */

import java.awt.Frame;
import java.awt.TextArea;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.lang.reflect.Method;
import java.util.Vector;
import java.util.zip.GZIPInputStream;

import com.gensym.classes.FloatArray;
import com.gensym.core.DebugUtil;
import com.gensym.jgi.G2AccessException;
import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.VersionManagerForOnlineProcessor;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.NolModel2;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/** OnlineProcessor class */
public class OnlineProcessorAPIG2 implements Cloneable, Serializable {

  private OnlineProcessor processor; 
  private static volatile Frame errorFrame;
  private static TextArea errorTA;
  private boolean debugBean = true;
  private boolean isloaded = false;
  
  //symbols for catching exceptions in G2
  private static Symbol RETVAL_ = Symbol.intern("RETVAL");
  private static Symbol ERROR_ = Symbol.intern("ERROR");
  private static Symbol BACKTRACE_ = Symbol.intern("BACKTRACE");

  private String g2Uuid = "";
 
/** Create a null OnlineProcessor with no argument */
  public OnlineProcessorAPIG2() {
	  this(new OnlineProcessor());
  }

	public OnlineProcessorAPIG2(OnlineProcessor processor) {
		this.processor = processor;
  }
  
  @Override
  public Object clone() throws CloneNotSupportedException {
	  OnlineProcessorAPIG2 cloned = (OnlineProcessorAPIG2) super.clone();
	  cloned.processor = processor == null ? null : (OnlineProcessor)processor.clone();
      return cloned;
  }
  
  public boolean getDebugProcessor () {
    return debugBean;
  }
  
  public void setDebugProcessor (boolean newDebugState) {
    debugBean = newDebugState;
  }
  
  private void debug (String eString) {
    if (!debugBean)
      return;
    if (eString == null)
      return;
    initErrorFrame();
    errorTA.append (eString + "\n");
    errorFrame.setVisible (true);
  }
  
  private void initErrorFrame() {
    if (errorFrame == null) {
      synchronized (OnlineStatisticalCalculatorAPIG2.class) {
        if (errorFrame == null) {
          errorFrame = new Frame("Processor Errors");
          errorFrame.add(errorTA = new TextArea());
          errorFrame.setSize(600, 400);
        }
      }
    }
  }
  

  /** Create a data OnlineProcessor for a file. */
  private OnlineProcessorAPIG2(String file, String directory){
	  this();   // creates processor
	 loadModel(file,directory);
  }
  
  /** Create a data OnlineProcessor for a file. */
  private OnlineProcessorAPIG2(String file){
	  this();
	 loadModel(file);
  }
  
/**	Load the model and formulas from a file.*/ 
  public void loadModel(String file, String directory){
	  try{
		File sourceFile;
		if(directory==null)
			sourceFile = new File(file);	
		else
			sourceFile = new File(directory,file);
		FileInputStream fis = new FileInputStream(sourceFile); 
		GZIPInputStream gzis = new GZIPInputStream(fis);   
		ObjectInputStream in = new ObjectInputStream(gzis); 
		VersionManagerForOnlineProcessor ver  = (VersionManagerForOnlineProcessor)in.readObject();
		in.close(); 
		if(ver.getProcessor() instanceof OnlineAutoRecusiveProcessor){
			this.processor = new OnlineAutoRecusiveProcessor();
			processor.copyToThis(ver.getProcessor());
		}else if(ver.getProcessor() instanceof OnlineProcessor){
			this.processor = new OnlineProcessor();
			processor.copyToThis(ver.getProcessor());
		}
		isloaded=true;
	}catch (Exception evt){
		System.err.println("Non-Fatal exception: " + evt.getMessage());
		evt.printStackTrace();
		isloaded=false;
	}
  }
  
  /**	Load the model and formulas from a file.*/ 
  public void loadModel(String file){
	  loadModel(file,null);
  }
  
  /** Get the name of this data OnlineProcessor. */	
	public String getName(){
		if(isloaded){
			return processor.getName();
		}
		return "";
	}
  
  /** Get the comment of this data OnlineProcessor. */	
	public String getComment(){
		if(isloaded){
			return processor.getComment();
		}
		return "";
	}
  
  /** Calculate the model.*/
  public Structure calculateOutputAtTimeForG2(String time){

	   Structure retval = new Structure();
	   try{
	     processor.calculateOutputAtTime(time);
	     retval.setAttributeValue(RETVAL_, new Boolean("true"));

	   } catch (MathException ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String 
					(DebugUtil.getStackTrace(ie)));
	   }
	   return retval; 
  }
  
/** Calculate the model.*/
  public Structure calculateOutputForRowForG2(){ 
	     
	   Structure retval = new Structure();
	   try{
	     processor.calculateOutputForRow();
	     retval.setAttributeValue(RETVAL_, new Boolean("true"));

	   } catch (MathException ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String 
					(DebugUtil.getStackTrace(ie)));
	   }
	   return retval; 

  }
  
  /** Get the number of inputs.*/
  public int getNumberOfInputs(){
		if(isloaded){
			return processor.getNumberOfInputs();
		}
		return 0;
  }
  
  /** Get input variables' names by index of the array */
  public String getInputName(int index) {
		if(isloaded){
		  return processor.getInputName(index);
		}
		return "";
  }
  
  /** Get input variables' names */
  public Sequence getInputNames(){ 
	if(isloaded){
		String[] names =  processor.getInputNames();
		Sequence nameSeq = new Sequence(names.length);
		for(int i=0;i<names.length;i++){
			nameSeq.addElement(names[i]);
		}
		return nameSeq;
	}
	return new Sequence(0);
  }
  
	/** Get input variables' names by index of the array */
	public String getInputTag(int index) {
		if(isloaded){
		  return processor.getInputTag(index);
		}
		return "";
	}

	/** Get input variables' tags  */
	public Sequence getInputTags() {
		if(isloaded){
			String[] tags =  processor.getInputTags();
			Sequence tagSeq = new Sequence(tags.length);
			for(int i=0;i<tags.length;i++){
				tagSeq.addElement(tags[i]);
			}
			return tagSeq;
		}
		return new Sequence(0);
	}

  /** Get the number of outputs.*/
	public int getNumberOfOutputs(){
		if(isloaded){
			return processor.getNumberOfOutputs();
		}
		return 0;
	}

	/** Get output variables' names by index of the array */
	public String getOutputName (int index)	{
		if(isloaded){
		  return processor.getOutputName(index);
		}
		return "";
	}

	/** Get output variables' names */
	public Sequence getOutputNames() {
		if(isloaded){
			String[] names =  processor.getOutputNames();
			Sequence nameSeq = new Sequence(names.length);
			for(int i=0;i<names.length;i++){
				nameSeq.addElement(names[i]);
			}
			return nameSeq;
		}
		return new Sequence(0);
	}

	/** Get output variables' names by index of the array */
	public String getOutputTag (int index){
		if(isloaded){
		  return processor.getOutputTag(index);
		}
		return "";
	}

	/** Get output variables' tags  */
	public Sequence getOutputTags(){ 
		if(isloaded){
			String[] tags =  processor.getOutputTags();
			Sequence tagSeq = new Sequence(tags.length);
			for(int i=0;i<tags.length;i++){
				tagSeq.addElement(tags[i]);
			}
			return tagSeq;
		}
		return new Sequence(0);
	}

  
/** Set the time format for this online processor. */
  public Structure setTimeFormatForG2(String timeFormat){ 

		Structure retval = new Structure();
		try{
			processor.setTimeFormat(timeFormat);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (MathException ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
		}
		return retval;
  }
  
/** Set the input value by variable index and value */
  public Structure setInputAtTimeByIndexForG2(int inputNumber, double value, String time){
		    
	   Structure retval = new Structure();
 		try{
			processor.setInputAtTimeByIndex(inputNumber,value,time);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (Exception ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
		}
		return retval;

  }
	 
/** Set the input value by variable name and value */
  public Structure setInputAtTimeByNameForG2(String varName, double value, String time){
		    
	   Structure retval = new Structure();
 		try{
			processor.setInputAtTimeByName(varName,value,time);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (Exception ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
		}
		return retval;

}
/** Set the input value by variable tag and value */
  public Structure setInputAtTimeByTagForG2(String varTag, double value, String time){
		    
		Structure retval = new Structure();
		try{
			processor.setInputAtTimeByTag(varTag,value,time);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (Exception ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
		}
		return retval;
  }


/** Set the value of one input variable. */	
  public Structure setInputForRowByIndexForG2(int inputNumber, double value){
	 	    
 	   Structure retval = new Structure();
		try{
			processor.setInputForRowByIndex(inputNumber,value);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (MathException ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
		}
		return retval;

}

  
/** Set the value of one input variable. */	
  public Structure setInputForRowByNameForG2(String varName, double value){
	  	    
 	   Structure retval = new Structure();
		try{
			processor.setInputForRowByName(varName,value);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;

}


/** Set the value of one input variable. */	
  public Structure setInputForRowByTagForG2(String varTag, double value){
	  	    
 	   Structure retval = new Structure();
		try{
			processor.setInputForRowByTag(varTag,value);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;

}

/** Get the current value of one output variable. */	
  public Structure getCurrentOutputByIndexForG2(int inputNumber){
	  
	   Structure retval = new Structure();
 		try{
			double value = processor.getCurrentOutputByIndex(inputNumber);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
  }
  
/** Get the current value of one output variable. */	
  public Structure getCurrentOutputByNameForG2(String varName){
	  
 	   Structure retval = new Structure();
		try{
			double value = processor.getCurrentOutputByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
  }
  

/** Get the current value of one output variable. */	
  public Structure getCurrentOutputByTagForG2(String varTag){
	  
 	   Structure retval = new Structure();
		try{
			double value = processor.getCurrentOutputByTag(varTag);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
  }
  
/** Get the value of one output variable at given time. */	
  public Structure getOutputAtTimeByIndexForG2(int inputNumber, String time){
	  
	   Structure retval = new Structure();
 		try{
			double value = processor.getOutputAtTimeByIndex(inputNumber,time);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (Exception ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
  }
  
/** Get the value of one output variable at given time. */	
  public Structure getOutputAtTimeByNameForG2(String varName, String time){
	  
 	   Structure retval = new Structure();
		try{
			double value = processor.getOutputAtTimeByName(varName,time);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (Exception ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
  }
  

/** Get the value of one output variable at given time. */	
  public Structure getOutputAtTimeByTagForG2(String varTag, String time){
	  
 	   Structure retval = new Structure();
		try{
			double value = processor.getOutputAtTimeByTag(varTag,time);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (Exception ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
  }

/** Get the status of this timestamps. */
  public Structure  hasTimeStamps(){
		Structure retval = new Structure();
		boolean b = processor.getHasTimeStamps();
		retval.setAttributeValue(RETVAL_, new Boolean(b));
		return retval;
  }
  

/** Get the data max from variable name.*/
	public Structure getMaxValueByNameForG2(String varName) {
 	   Structure retval = new Structure();
		try{
			double value = processor.getMaxValueByName(varName);
  			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
	}

/** Get the data max from variable tag.*/
	public Structure getMaxValueByTagForG2(String varTag){
		
 	   Structure retval = new Structure();
		try{
			double value = processor.getMaxValueByTag(varTag);
  			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;

	}


/** Get the data min from variable name.*/
	public Structure getMinValueByNameForG2(String varName) {
		
 	   Structure retval = new Structure();
		try{
			double value = processor.getMinValueByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
	}


/** Get the data min from variable tag.*/
	public Structure getMinValueByTagForG2(String varTag){ 

 	   Structure retval = new Structure();
		try{
			double value = processor.getMinValueByTag(varTag);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
	}
 
/** Get the data mean from variable name.*/
	public Structure getMeanValueByNameForG2(String varName){ 

 	   Structure retval = new Structure();
		try{
			double value = processor.getMeanValueByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
	}
 

/** Get the data mean from variable tag.*/
	public Structure getMeanValueByTagForG2(String varTag) { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getMeanValueByTag(varTag);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		}
		return retval;
	}

/** Get the data median from variable name.*/
	public Structure getMedianValueByNameForG2(String varName)  { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getMedianValueByName(varName) ;
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}

/** Get the data median from variable tag.*/
	public Structure getMedianValueByTagForG2(String varTag)  { 

	   Structure retval = new Structure();
 		try{
			double value = processor.getMedianValueByTag(varTag);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}


/** Get the data sum from variable name.*/
	public Structure getSumValueByNameForG2(String varName)	  { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getSumValueByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}


/** Get the data sum from variable tag.*/
	public Structure getSumValueByTagForG2(String varTag)  { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getSumValueByTag(varTag);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}


/** Get the data std from variable name.*/
	public Structure getSTDValueByNameForG2(String varName) { 

	   Structure retval = new Structure();
 		try{
			double value = processor.getSTDValueByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}



/** Get the data std from variable tag.*/
	public Structure getSTDValueByTagForG2(String varTag) { 

	   Structure retval = new Structure();
 		try{
			double value = processor.getSTDValueByTag(varTag) ;
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}


/** Get the data variance from variable name.*/
	public Structure getVarianceValueByNameForG2(String varName) { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getVarianceValueByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}

/** Get the data variance from variable tag.*/
	public Structure getVarianceValueByTagForG2(String varTag)  { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getVarianceValueByTag(varTag);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}


/** Get the data kurt from variable name.*/
	public Structure getKurtValueByNameForG2(String varName)   { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getKurtValueByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}

/** Get the data kurt from variable tag.*/
	public Structure getKurtValueByTagForG2(String varTag)   { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getKurtValueByTag(varTag);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}

/** Get the data skew from variable name.*/
	public Structure getSkewValueByNameForG2(String varName)  { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getSkewValueByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}


/** Get the data skew from variable tag.*/
	public Structure getSkewValueByTagForG2(String varTag)   { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getSkewValueByTag(varTag) ;
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}

/** Get the data range from variable name.*/
	public Structure getRangeValueByNameForG2(String varName)   { 

 	   Structure retval = new Structure();
		try{
			double value = processor.getRangeValueByName(varName);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}

/** Get the data range from variable tag.*/
	public Structure getRangeValueByTagForG2(String varTag)	 { 

	   Structure retval = new Structure();
 		try{
			double value = processor.getRangeValueByTag(varTag);
			retval.setAttributeValue(RETVAL_, new Double(value));
		} catch (MathException ie){
		retval.setAttributeValue(ERROR_, 
					 new String(ie.getMessage()));
		retval.setAttributeValue(BACKTRACE_, 
					 new String (DebugUtil.getStackTrace
							 (ie)));
		   
		}
		return retval;
	}

/** Get the input variable delays from variable name.*/
	public Structure getInputDelayByNameForG2(String varName){ 
		Structure retval = new Structure();
 		try{
			long[] delays = processor.getInputDelayByName(varName);
			Sequence delaysSeq = new Sequence(delays.length);
			for(int i=0;i<delays.length;i++){
				delaysSeq.addElement(new Double(delays[i]));
			}
			retval.setAttributeValue(RETVAL_, delaysSeq);
		} catch (MathException ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
			   
		}
		return retval;
	}

/** Get the input variable delays from variable tag.*/
	public Structure getInputDelayByTagForG2(String varTag){ 
		Structure retval = new Structure();
 		try{
			long[] delays = processor.getInputDelayByTag(varTag);
			Sequence delaysSeq = new Sequence(delays.length);
			for(int i=0;i<delays.length;i++){
				delaysSeq.addElement(new Double(delays[i]));
			}
			retval.setAttributeValue(RETVAL_, delaysSeq);
		} catch (MathException ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
			   
		}
		return retval;
	}


/** Get the formula list.*/
	public Structure getFormulasForG2(){ 
		Structure retval = new Structure();
 		try{
			String formulas = processor.getFormulas();
			retval.setAttributeValue(RETVAL_, formulas);
		} catch (MathException ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
			   
		}
		return retval;
	}

/** Clear the buffer for time based data.*/
	public Structure clearDataBufferForG2(){
		Structure retval = new Structure();
		if(isloaded){
 			try{
				processor.clearDataBuffer();
			} catch (MathException ie){
				retval.setAttributeValue(ERROR_, 
							 new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, 
							 new String (DebugUtil.getStackTrace
									 (ie)));
			}
		}
		return retval;
	}

/** Retrain the predictive model.*/
	public Structure trainModel(final Sequence input, final Sequence output, final double timeInMinute, 
			final boolean autoStop, final boolean newTraining, final boolean display)
	{
		double minutes = timeInMinute;
		if (debugBean) {
			System.out.println("start re-training model");
		}
		Structure retval = new Structure();
		if (debugBean) {
			System.out.println("start re-training model isloaded="+isloaded);
		}
		if(isloaded){
			try{
				int nrows = input.size();
				if(nrows != output.size()){
					MathException e = new MathException("Input and Output don't have the same number of samples.");
					throw e;
				}
				if(nrows <10){
					MathException e = new MathException("There is not enough data for training.");
					throw e;
				}
				Object[] inputRows = input.getContents();
				Object[] outputRows = output.getContents();
				double[][] x = new double[nrows][];
				double[][] y = new double[nrows][];
				for(int i=0;i<nrows;i++){
					x[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
					y[i] = ((FloatArray)outputRows[i]).getFloatArrayContents();
				}

				Matrix X = Matlib.createMatrix(x);
				Matrix Y = Matlib.createMatrix(y);
				Vector listener = new Vector();
				listener.addElement(new OnlineModelListener(processor));
				listener.addElement(new OnlineModelListener(this));
				if (Double.compare(minutes, 0.0) == 0 ) 
					minutes = 1;
				double timeInMilli = (minutes*60000.0);
if (debugBean) {
	System.out.println("start re-training model in processor");
}
				processor.trainModel(listener,X,Y,timeInMilli,autoStop,newTraining,display);
			} catch (Exception ie){
				errorOccur(ie.getMessage());
				ie.printStackTrace();
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			}
		}else{
			errorOccur("Can not train unloaded model");
		}
		return retval;
	}


/** Retrain the predictive model.*/
	public Structure trainModelFromFile(final String inputDataFileName, final String outputDataFileName, 
			final double timeInMinute, final boolean autoStop, final boolean newTraining, final boolean display)
	{
		double minutes = timeInMinute;
		if (debugBean) {
			System.out.println("start re-training model");
		}
		Structure retval = new Structure();
		if(isloaded){
			Vector listener = new Vector();
			listener.addElement(new OnlineModelListener(processor));
			listener.addElement(new OnlineModelListener(this));
			try{
				if (Double.compare(minutes, 0.0) == 0 ) 
					minutes = 1;
				double timeInMilli = (minutes*60000.0);
				processor.trainModelFromFile(listener,inputDataFileName,outputDataFileName,timeInMilli,autoStop, newTraining,display);
			} catch (IOException ie){
				errorOccur(ie.getMessage());
				ie.printStackTrace();
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			} catch (MathException ie){
				errorOccur(ie.getMessage());
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			}
		}else{
			errorOccur("Can not train unloaded model");
		}
		return retval;
	}

/** Retrain the predictive model.*/
	public Structure trainModelFromFile(final Sequence dataSeriesFileNames, final double timeInMinute, 
			final boolean autoStop, final boolean newTraining, final boolean display)
	{
		double minutes = timeInMinute;
		if (debugBean) {
			System.out.println("start re-training model");
		}
		int n = dataSeriesFileNames.size();
		Object[] nameContents= dataSeriesFileNames.getContents();
		String[] fileNames = new String[n];
		for(int i=0;i<n;i++){
			fileNames[i] = (String)nameContents[i];
		}
		Structure retval = new Structure();
		if(isloaded){
			Vector listener = new Vector();
			listener.addElement(new OnlineModelListener(processor));
			listener.addElement(new OnlineModelListener(this));
			try{
				if (Double.compare(minutes, 0.0) == 0 ) 
					minutes = 1;
				double timeInMilli = (minutes*60000.0);
				processor.trainModelFromFile(listener,fileNames,timeInMilli,autoStop, newTraining,display);
			} catch (MathException ie){
				errorOccur(ie.getMessage());
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			}
		}else{
			errorOccur("Can not train unloaded model");
		}
		return retval;
	}

/** Get the model rate after the retraining.*/
	public Structure getModelRateForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double val = processor.getModelRate();
			 retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
		   errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the testing RMSE after the retraining.*/
	public Structure getTestRmseForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = processor.getTestRmse();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
		   errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the training RMSE after the retraining.*/
	public Structure getTrainingRmseForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = processor.getTrainingRmse();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
		   errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the testing correlation values after the retraining.*/
	public Structure getTestCorrForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = processor.getTestCorr();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
		   errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the training correlation values after the retraining.*/
	public Structure getTrainingCorrForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = processor.getTrainingCorr();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
		   errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}


/** Get input variables' unit by index of the array */
  public String getInputUnit(int index) {
		if(isloaded){
		  return processor.getInputUnit(index);
		}else{
			errorOccur("Can not get parameters for unloaded model");
		}
		return "";
  }

/** Get output variables' unit by index of the array */
  public String getOutputUnit(int index) {
		if(isloaded){
		  return processor.getOutputUnit(index);
		}else{
			errorOccur("Can not get parameters for unloaded model");
		}
		return "";
  }


/** Set the variable value by variable name and value */
  public Structure setVariableValueAtTimeByNameForG2(String varName, double value, String time){
		    
	   Structure retval = new Structure();
 		try{
			processor.setVariableValueAtTimeByName(varName,value,time);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (Exception ie){
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
		}
		return retval;

	}

/** Set the variable value by variable tag and value */
  public Structure setVariableValueAtTimeByTagForG2(String varTag, double value, String time){
		    
	   Structure retval = new Structure();
 		try{
			processor.setVariableValueAtTimeByTag(varTag,value,time);
		  retval.setAttributeValue(RETVAL_, new Boolean("true"));
		} catch (Exception ie){
 		   errorOccur(ie.getMessage());
			retval.setAttributeValue(ERROR_, 
						 new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, 
						 new String (DebugUtil.getStackTrace
								 (ie)));
		}
		return retval;

	}

  /**	Test whether the model is loaded.*/ 
  public boolean isLoaded(){
	  return isloaded;
  }
  
  /**	Load model from model name.*/ 
  public boolean loadFromProject(String mName){
	if (NolMainFrame.mainFrame != null){
		Project2 project = NolMainFrame.mainFrame.getProject();
		int index = project.getPredictiveModelIndexByName(mName);
		if (index == -1) {
			return false;
		}
		NolModel2 model = project.getPredictiveModel(index);
		try{
			if(model.isAutoRecursiveModel()){
				processor = new OnlineAutoRecusiveProcessor(mName,model.getPreprocessor(),model);
			}else{
				processor = new OnlineProcessor(mName,model.getPreprocessor(),model);
			}
		}catch(MathException evt){
			isloaded=false;
			return false;
		}
		isloaded=true;
		return true;
	}
	isloaded=false;
	return false;
  }

	/**	Set the UUID for the corresponding G2 model object.*/ 
	public void setUuidForG2Object(String uuid){
	  g2Uuid = new String(uuid);
	}
	
	/**	After the model is complete inform the G2 model object to set training complete flag.*/ 
	protected void trainingComplete(){
	//System.out.println("online processor training complete and set retrain = true");
		if (NolG2Gateway.g2Gateway != null){
			if(!g2Uuid.equals("")){
				try{
					NolG2Gateway.g2Gateway.informG2TrainingComplete(g2Uuid, true);
				}catch(G2AccessException evt){
				   errorOccur(evt.getMessage());
				}
			}
		}
	}


	/** Set the error flag to the G2 model object.*/
	public void errorOccur(String errorMessage){
	//System.out.println("online processor training complete and set retrain = true");
		if (NolG2Gateway.g2Gateway != null){
			if(!g2Uuid.equals("")){
				try{
					NolG2Gateway.g2Gateway.informG2ErrorOccur(g2Uuid, true, errorMessage);
				}catch(G2AccessException evt){
				}
			}
		}
	}


/**	Save the model and formulas from a file.*/ 
  public boolean saveModel(final String file, final String directory){
	// try to start writing
	String fileName = file;
	String pName = fileName;
	int dotInd = fileName.indexOf(".");
	if(dotInd == -1){
		fileName = fileName+".mod";
	}else{
		pName = fileName.substring(0,dotInd);	
	}
	processor.setName(pName);
	try {
		Class versionManagerClass = Class.forName("com.gensym.nols.data.VersionManagerForOnlineProcessor");
		Object versionManager = versionManagerClass.newInstance();
		Method method = versionManagerClass.getMethod("setProcessor",new Class[] {Class.forName("com.gensym.nols.deploy.OnlineProcessor")});
		method.invoke(versionManager,new Object[] {processor});
		method = versionManagerClass.getMethod("saveToFile",new Class[] {directory.getClass(), fileName.getClass()});
		method.invoke(versionManager,new Object[] {directory, fileName});
	} catch (Exception ex) {
	   errorOccur(ex.getMessage());
		return false;
	}
	return true;
  }
	
  public Structure calculateSensitivity(Sequence input,Sequence signedSensitivity,Sequence absSensitivity) throws G2AccessException{
		Structure retval = new Structure();
		Sequence result	= NolG2Gateway.g2Gateway.getDataSequence();
		result.removeAllElements();
		if (debugBean) {
			debug("start calculateSensitivity isloaded="+isloaded);
		}
		if(isloaded){
			try{
				int nrows = input.size();
if (debugBean) {
	debug("start calculateSensitivity  nrows=" + nrows);
}
				if(nrows <1){
					MathException e = new MathException("There is not enough data for calculation.");
					throw e;
				}
if (debugBean) {
	debug("start convert to matrix");
}
				Object[] inputRows = input.getContents();
				double[][] x = new double[nrows][];
				for(int i=0;i<nrows;i++){
					x[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
				}

				Matrix X = Matlib.createMatrix(x);
				Matrix signedSensitivityValues = Matlib.createMatrix();
				Matrix absSensitivityValues = Matlib.createMatrix();
if (debugBean) {
	debug("start calculateSensitivity");
}
				processor.calculateSensitivity(X, signedSensitivityValues, absSensitivityValues);
				Matlib.clear(X);
				signedSensitivity.removeAllElements();
				Matlib.transpose(signedSensitivityValues,signedSensitivityValues);
				double[][] data = Matlib.create2DArray(signedSensitivityValues);
if (debugBean) {
	debug("finished calculateSensitivity data.length 1= "+data.length);
}
				for (int i=0;i<data.length;i++){
					double[] xx = data[i];
					Sequence xarray	= NolG2Gateway.g2Gateway.getDataSequence();
					xarray.removeAllElements();
					for (int j=0;j<xx.length;j++){
						xarray.addElement(new Double(xx[j]));
					}
					signedSensitivity.addElement(xarray);
				}		
				Matlib.clear(signedSensitivityValues);
				absSensitivity.removeAllElements();
				Matlib.transpose(absSensitivityValues,absSensitivityValues);
				data = Matlib.create2DArray(absSensitivityValues);
if (debugBean) {
	debug("finished calculateSensitivity data.length 2= "+data.length);
}
				for (int i=0;i<data.length;i++){
					double[] xx = data[i];
					Sequence xarray	= NolG2Gateway.g2Gateway.getDataSequence();
					xarray.removeAllElements();
					for (int j=0;j<xx.length;j++){
						xarray.addElement(new Double(xx[j]));
					}
					absSensitivity.addElement(xarray);
				}		
				Matlib.clear(absSensitivityValues);
				result.addElement(signedSensitivity);
				result.addElement(absSensitivity);
				if (debugBean) 
					debug("finished calculateSensitivity set result");
				retval.setAttributeValue(RETVAL_, result);
			} catch (MathException ie){
			   errorOccur(ie.getMessage());
				ie.printStackTrace();
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			} catch (G2AccessException ie){
			   errorOccur(ie.getMessage());
				ie.printStackTrace();
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			} catch (RuntimeException ie){
			   errorOccur(ie.getMessage());
				ie.printStackTrace();
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			}
		}else{
			errorOccur("Can not run unloaded model");
		}
		return retval;
  }

  /**	Prepare training data set from giving data series and save them into ascii data matrix files.*/ 
  public Structure prepareTrainingDataFile(Sequence dataSeriesFileNames, int fileType, String inputDataFileName, String outDataFileName){
		if (debugBean) {
			System.out.println("start prepareTrainingDataFile fileType="+fileType+"   inputDataFileName="+inputDataFileName+"  outDataFileName="+outDataFileName );
		}
		int n = dataSeriesFileNames.size();
		Object[] nameContents= dataSeriesFileNames.getContents();
		String[] fileNames = new String[n];
		for(int i=0;i<n;i++){
			fileNames[i] = (String)nameContents[i];
		}
		Structure retval = new Structure();
		if(isloaded){
			try{
				processor.prepareTrainingDataFile(fileNames, fileType, inputDataFileName, outDataFileName);
			} catch (IOException ie){
//				errorOccur(ie.getMessage());
				ie.printStackTrace();
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			} catch (MathException ie){
//				errorOccur(ie.getMessage());
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			}
		}else{
			errorOccur("Can not use unloaded model");
		}
		return retval;
  }

	public OnlineProcessor getProcessor() {
		return processor;
	}

	public void setIsLoaded(boolean loaded) {
		this.isloaded = loaded;
    }
}
