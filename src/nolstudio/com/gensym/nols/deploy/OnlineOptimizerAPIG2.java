package com.gensym.nols.deploy;
/*
 *		Wrapper class for Gensym OnlineOptimizer.
 *		Cannot be encrypted!
 *		Created 3/18/99 by Gchen
 *              update 9/3/99 by ellen
*/

import java.awt.Frame;
import java.awt.TextArea;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Vector;

import com.gensym.classes.FloatArray;
import com.gensym.core.DebugUtil;
import com.gensym.jgi.G2AccessException;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;

import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.NolOptimization;

/* eg - Optimizer G2 implementation for error catching
requires use of Javalink util classes, Symbol and Structure */


/** OnlineOptimizer class */
public class OnlineOptimizerAPIG2 implements Cloneable, Serializable {

  private OnlineOptimizer optimizer; 
  private static volatile Frame errorFrame;
  private static TextArea errorTA;
  private boolean debugBean = true;
  private boolean isloaded = false;

  // symbols for catching exceptions in G2
  public static final Symbol RETVAL_ = Symbol.intern("RETVAL");
  public static final Symbol ERROR_ = Symbol.intern("ERROR");
  public static final Symbol BACKTRACE_ = Symbol.intern("BACKTRACE");

  private String g2Uuid = "";

  /** Create a null OnlineOptimizer with no argument */
  public OnlineOptimizerAPIG2(){}
  
  @Override
  public Object clone() throws CloneNotSupportedException {
	  OnlineOptimizerAPIG2 cloned = (OnlineOptimizerAPIG2) super.clone();
	  cloned.optimizer = optimizer == null ? null : (OnlineOptimizer)optimizer.clone();
      return cloned;
  }
	
  private void ensureCoreOptimizer (){
		try {
		  optimizer = new OnlineOptimizer();
		  debug ("", null);
		  errorTA.append ("Made procesor : " + optimizer + " CL = " + optimizer.getClass().getClassLoader ());
		} catch (Exception e) {
		  debug ("Error in Constructor", e);
		}
  }
  
  public boolean getDebugOptimizer () {
    return debugBean;
  }
  
  public void setDebugOptimizer (boolean newDebugState) {
    debugBean = newDebugState;
  }
  
  private void debug (final String methodName, final Exception e) {
	Exception exception = e;
    if (!debugBean)
      return;
    if (exception == null)
      return;
    initErrorFrame();
    errorTA.append (methodName +" : \n\n" + exception.getClass () + "\n");
    errorTA.append (exception.getMessage ());
    errorTA.append ("\n");
    errorTA.append (com.gensym.nols.deployutil.DebugUtil.getStackTrace (exception));
    errorTA.append ("\n");
    if (exception instanceof InvocationTargetException) {
      InvocationTargetException ite = (InvocationTargetException)exception;
      exception = (InvocationTargetException)ite.getTargetException ();
      debug ("Nested Exception", exception);
    }
    errorFrame.setVisible (true);
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
          errorFrame = new Frame("Optimizer Errors");
          errorFrame.add(errorTA = new TextArea());
          errorFrame.setSize(600, 400);
        }
      }
    }
  }

/** Create a data OnlineOptimizer for a file. */
	private OnlineOptimizerAPIG2(String file, String directory){
		this();   // creates Optimizer
		loadOptimization(file,directory);
	}

/** Create a data OnlineOptimizer for a file. */
  private OnlineOptimizerAPIG2(String file) {
	 this();
	 loadOptimization(file);
  }
  
  /**	Load the model and formulas from a file.*/ 
  public void loadOptimization(String file, String directory) {
	  ensureCoreOptimizer ();
	  try{
		optimizer.loadOptimization(file,directory);
 		isloaded=true;
	}catch (Exception evt){
		System.err.println("Non-Fatal exception: " + evt.getMessage());
		evt.printStackTrace();
		isloaded=false;
	}
 }
  
  /**	Load the model and formulas from a file.*/ 
  public void loadOptimization(String file) {
	ensureCoreOptimizer ();
	try{
		optimizer.loadOptimization(file);
		isloaded=true;
	}catch (Exception evt){
		System.err.println("Non-Fatal exception: " + evt.getMessage());
		evt.printStackTrace();
		isloaded=false;
	}
}
  
  /** Get the name of this data OnlineOptimizer. */	
  public String getName(){
  		if(isloaded){
			return optimizer.getName();
		}
		return "";
	}
  
  /** Get the comment of this data OnlineOptimizer. */	
  public String getComment(){
  		if(isloaded){
			return optimizer.getComment();
		}
		return "";
	}
  
  /** Calculate the model.*/
/** Calculate the model.*/
  public Structure calculateForG2(){
	   
	  Structure retval = new Structure();
	  try{
		  optimizer.calculate();
	    //in G2 the value of RETURN is the actual value returned by the
	    // method, in this case there isn't any
	    retval.setAttributeValue(RETVAL_, new Boolean("true"));
	  } catch (MathException ie) {
	      retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	      retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							       (ie)));
	  }
	  return retval;
  }

  /** Calculate the model and return the status flag.*/
/** Calculate the model.*/
  public int calculateOptimizationForG2() {
	  int flag = optimizer.optimize();
	  return flag;
  }

/** Return the variable names of specified variable type. 
(0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/
	public Sequence getVariableNames(int type){
		Sequence retval = new Sequence();
		if(isloaded){
			String[] names = optimizer.getVariableNames(type);
			for(int i=0;i<names.length;i++){
				retval.addElement(names[i]);
			}
		}
		return retval;
	}

/** Return the variable tags of specified variable type. 
(0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/
	public Sequence getVariableTags(int type){
		Sequence retval = new Sequence();
		if(isloaded){
			String[] tags = optimizer.getVariableTags(type);
			for(int i=0;i<tags.length;i++){
				retval.addElement(tags[i]);
			}
		}
		return retval;
	}

/** Return the variable units of specified variable type. 
(0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/
	public Sequence getVariableUnits(int type){
		Sequence retval = new Sequence();
		if(isloaded){
			String[] units = optimizer.getVariableUnits(type);
			for(int i=0;i<units.length;i++){
				retval.addElement(units[i]);
			}
		}
		return retval;
	}


/** Return the number of variables for specified variable type.
(0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/
	public int getNumberOfVariables(int type){
		
		if(isloaded){
			return optimizer.getNumberOfVariables(type);
		}
		return 0;
	}

/** Set the value by variable name. This method is used to set the initial
	values for manipulated variables and the values for exogenous variables.*/
  public Structure setValueByNameForG2(String varName, double val){
	   Structure retval = new Structure();
	   try {
		   optimizer.setValueByName(varName,val);
		   retval.setAttributeValue(RETVAL_, new Boolean("true"));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }
  
/** Set the value by variable tag. This method is used to set the initial
	values for manipulated variables and the values for exogenous variables.*/
  public Structure setValueByTagForG2(String tag, double val){
	   Structure retval = new Structure();
	   try {
		   optimizer.setValueByTag(tag,val);
		   retval.setAttributeValue(RETVAL_, new Boolean("true"));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

  
  /** Return the value by variable name. This method can be used to get the values of 
    each variable before calculation and after calculation. */
  public Structure getValueByNameForG2(String varName){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getValueByName(varName);
		     retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

  /** Return the value by variable tag. This method can be used to get the values of 
    each variable before calculation and after calculation. */
  public Structure getValueByTagForG2(String tag){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getValueByTag(tag);
		     retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the value array for specified variable type. The order of value array is the 
same as the order of name array. 
(0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/
  public Structure getValuesForG2(int type){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getValues(type);
		     retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
		   System.out.println("message="+ie.getMessage());
		   System.out.println("trace="+DebugUtil.getStackTrace
						       (ie));
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()+" new error"));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)+" error trace"));
	   }
	   return retval;
  }

/** Set the value array for specified variable type. The order of value array is the 
same as the order of name array. 
(1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/
  public Structure setValuesForG2(int type, double[] vals){
	  
	   Structure retval = new Structure();
	   try {
		   optimizer.setValues(type,vals);
	     retval.setAttributeValue(RETVAL_, new Boolean ("true"));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

  
/** Set the bounds by variable name. This method if for all variables.
The order of the bounds is [hlBound, slBound, setpoint, suBound, huBound].
*/
  public Structure setBoundsByNameForG2(String varName, double[] bounds){
	  
	   Structure retval = new Structure();
	   try {
		   optimizer.setBoundsByName(varName,bounds);
	     retval.setAttributeValue(RETVAL_, new Boolean ("true"));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }


  /* this was a test method for G2*/
  /*public void setBoundsByName(String varName, double hlBound, double slBound, double setPoint, double suBound, double huBound) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
    
    double[] bounds =  {hlBound, slBound, setPoint, suBound, huBound};
    
    Method method = optimizerClass.getMethod("setBoundsByName",new Class[] {varName.getClass(),bounds.getClass()});
    method.invoke(optimizer,new Object[] {varName,bounds});
    }*/
  
/** Set the bounds by variable tag. This method is for all variables.
The order of the bounds is [hlBound, slBound, setpoint, suBound, huBound].
*/
  public Structure setBoundsByTagForG2 (String tag, double[] bounds){
	  
	   Structure retval = new Structure();
	   try {
		   optimizer.setBoundsByTag(tag,bounds);
	     retval.setAttributeValue(RETVAL_, new Boolean ("true"));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Return the bounds by variable name. This method if for all variables.
The order of the bounds is [hlBound, slBound, setpoint, suBound, huBound].
*/
  public Structure getBoundsByNameForG2(String varName){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getBoundsByName(varName);
	     retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Return the bounds by variable tag. This method is for all variables.
The order of the bounds is [hlBound, slBound, setpoint, suBound, huBound].
*/
  public Structure  getBoundsByTagForG2 (String tag){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getBoundsByTag(tag);
	     retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Set the weights by variable name. This method if for all variables.
The order of the bounds is [linWeight, setpointWeight,subWeight,slbWeight].
*/
  public Structure  setWeightsByNameForG2 (String varName, double[] weights) {
	  
	   Structure retval = new Structure();
	   try {
		   optimizer.setWeightsByName(varName,weights);
		   retval.setAttributeValue(RETVAL_, new Boolean ("true"));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Set the weights by variable tag. This method if for all variables.
The order of the bounds is [linWeight, setpointWeight,subWeight,slbWeight].
*/
  public Structure setWeightsByTagForG2(String tag, double[] weights) {
	  
	   Structure retval = new Structure();
	   try {
		   optimizer.setWeightsByTag(tag,weights);
		   retval.setAttributeValue(RETVAL_, new Boolean ("true"));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }
/** Return the weights by variable name. This method if for all variables.
The order of the bounds is [linWeight, setpointWeight,subWeight,slbWeight].
*/
  public Structure getWeightsByNameForG2(String varName){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getWeightsByName(varName);
		   retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Return the weights by variable tag. This method if for all variables.
The order of the bounds is [linWeight, setpointWeight,subWeight,slbWeight].
*/
  public Structure  getWeightsByTagForG2(String tag){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getWeightsByTag(tag);
		   retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

  /*private static final Symbol DATA_ = Symbol.intern ("DATA");
    Testing the passing of arrays and structures into G2
    public double[] getDoubleArray () {
    return new double[] {10.0, 20.0};
    }

    public Structure getDoubleInStructure () {
    Structure s = new Structure ();
    s.setAttributeValue (DATA_, new double[] {10.0, 20.0});
    s.setAttributeValue (ERROR_,
    "java.lang.MathException");
    return s;
    }
  */
	

/** Get the data max from variable name.*/
	public Structure getMaxValueByNameForG2(String varName){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getMaxValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

	

/** Get the data max from variable tag.*/
	public Structure getMaxValueByTagForG2(String varTag){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getMaxValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }


/** Get the data min from variable name.*/
	public Structure getMinValueByNameForG2(String varName) {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getMinValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data min from variable tag.*/
	public Structure getMinValueByTagForG2(String varTag){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getMinValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }
 

/** Get the data mean from variable name.*/
	public Structure getMeanValueByNameForG2(String varName) {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getMeanValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data mean from variable tag.*/
	public Structure getMeanValueByTagForG2(String varTag) {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getMeanValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }


/** Get the data median from variable name.*/
	public Structure getMedianValueByNameForG2(String varName) {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getMedianValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data median from variable tag.*/
	public Structure getMedianValueByTagForG2(String varTag)  {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getMedianValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data sum from variable name.*/
	public Structure getSumValueByNameForG2(String varName)  {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getSumValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data sum from variable tag.*/
	public Structure getSumValueByTagForG2(String varTag){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getSumValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data std from variable name.*/
	public Structure getSTDValueByNameForG2(String varName){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getSTDValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }


/** Get the data std from variable tag.*/
	public Structure getSTDValueByTagForG2(String varTag){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getSTDValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }


/** Get the data variance from variable name.*/
	public Structure getVarianceValueByNameForG2(String varName){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getVarianceValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data variance from variable tag.*/
	public Structure getVarianceValueByTagForG2(String varTag)  {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getVarianceValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data kurt from variable name.*/
	public Structure getKurtValueByNameForG2(String varName){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getKurtValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data kurt from variable tag.*/
	public Structure getKurtValueByTagForG2(String varTag){
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getKurtValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }


/** Get the data skew from variable name.*/
	public Structure getSkewValueByNameForG2(String varName) {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getSkewValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data skew from variable tag.*/
	public Structure getSkewValueByTagForG2(String varTag) {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getSkewValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

/** Get the data range from variable name.*/
	public Structure getRangeValueByNameForG2(String varName) {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getRangeValueByName(varName);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }

 
/** Get the data range from variable tag.*/
	public Structure getRangeValueByTagForG2(String varTag) {
	  
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getRangeValueByTag(varTag);
		   retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
	       retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
	       retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
						       (ie)));
	   }
	   return retval;
  }


/** Retrain the output model.*/
	public Structure trainOutputModel(final Sequence input, final Sequence output, final double timeInMinute, 
			final boolean autoStop, final boolean newTraining, final boolean display)
		throws MathException, G2AccessException{
		
		double minutes = timeInMinute;
		if (debugBean) {
			System.out.println("start re-training model");
		}
		Structure retval = new Structure();
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
				listener.addElement(new OnlineModelListener(optimizer));
				listener.addElement(new OnlineModelListener(this));
				if (Double.compare(minutes, 0.0) == 0 ) 
					minutes = 5;
				double timeInMilli = (minutes*60000.0);
				optimizer.trainOutputModel(listener,X,Y,timeInMilli,autoStop,newTraining,display);
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


/** Retrain the state model.*/
	public Structure trainStateModel(final Sequence input, final Sequence output, final double timeInMinute, 
			final boolean autoStop, final boolean newTraining, final boolean display)
		{
		double minutes = timeInMinute;
		if (debugBean) {
			System.out.println("start re-training model");
		}
		Structure retval = new Structure();
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
				listener.addElement(new OnlineModelListener(optimizer));
				listener.addElement(new OnlineModelListener(this));
				if (Double.compare(minutes, 0.0) == 0 ) 
					minutes = 5;
				double timeInMilli = (minutes*60000.0);
				optimizer.trainStateModel(listener,X,Y,timeInMilli,autoStop,newTraining,display);
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


/** Retrain the output model from data files.*/
	public Structure trainOutputModelFromFile(String inputDataFileName, 
		String outputDataFileName, double timeInMinute, boolean autoStop, boolean newTraining, boolean display){

		if (debugBean) {
			System.out.println("start re-training model");
		}
		Structure retval = new Structure();
		if(isloaded){
			Vector listener = new Vector();
			listener.addElement(new OnlineModelListener(optimizer));
			listener.addElement(new OnlineModelListener(this));
			try{
				double timeInMilli = (timeInMinute*60000.0);
				optimizer.trainOutputModelFromFile(listener,inputDataFileName,outputDataFileName,timeInMilli,autoStop,newTraining,display);
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


/** Retrain the state model from data files.*/
	public Structure trainStateModelFromFile(String inputDataFileName, 
		String outputDataFileName, double timeInMinute, boolean autoStop, boolean newTraining, boolean display)
	{
		if (debugBean) {
			System.out.println("start re-training model");
		}
		Structure retval = new Structure();
		if(isloaded){
			Vector listener = new Vector();
			listener.addElement(new OnlineModelListener(optimizer));
			listener.addElement(new OnlineModelListener(this));
			try{
				double timeInMilli = (timeInMinute*60000.0);
				optimizer.trainStateModelFromFile(listener,inputDataFileName,outputDataFileName,timeInMilli,autoStop,newTraining,display);
			} catch (Exception ie){
				errorOccur(ie.getMessage());
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			}
		}else{
			errorOccur("Can not train unloaded model");
		}
		return retval;
	}


/** Retrain the optimiation model.*/
	public Structure trainModelFromFile(Sequence dataSeriesFileNames, double timeInMinute, boolean autoStop, boolean newTraining, boolean display)
	{
		if (debugBean) {
			System.out.println("start re-training model");
		}
		Structure retval = new Structure();
		int n = dataSeriesFileNames.size();
		Object[] nameContents= dataSeriesFileNames.getContents();
		String[] fileNames = new String[n];
		for(int i=0;i<n;i++){
			fileNames[i] = (String)nameContents[i];
		}
		if(isloaded){
			Vector listener = new Vector();
			listener.addElement(new OnlineModelListener(optimizer));
			listener.addElement(new OnlineModelListener(this));
			try{
				double timeInMilli = timeInMinute*60000.0;
				optimizer.trainModelFromFile(listener,fileNames,timeInMilli,autoStop,newTraining,display);
			} catch (Exception ie){
				errorOccur(ie.getMessage());
				retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
				retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			}
		}else{
			errorOccur("Can not train unloaded model");
		}
		return retval;
	}

/** Get the model rate of output model after the retraining.*/
	public Structure getOutputModelRateForG2(){ 
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getOutputModelRate();
			 retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the testing RMSE of output model after the retraining.*/
	public Structure getOutputTestRmseForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getOutputTestRmse();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the training RMSE of output model after the retraining.*/
	public Structure getOutputTrainingRmseForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getOutputTrainingRmse();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the testing correlation values of output model after the retraining.*/
	public Structure getOutputTestCorrForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getOutputTestCorr();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the training correlation values of output model after the retraining.*/
	public Structure getOutputTrainingCorrForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getOutputTrainingCorr();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}


/** Get the model rate of state model after the retraining.*/
	public Structure getStateModelRateForG2(){ 
	   Structure retval = new Structure();
	   try {
		   double val = optimizer.getStateModelRate();
			 retval.setAttributeValue(RETVAL_, new Double(val));
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the testing RMSE of state model after the retraining.*/
	public Structure getStateTestRmseForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getStateTestRmse();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the training RMSE of state model after the retraining.*/
	public Structure getStateTrainingRmseForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getStateTrainingRmse();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the testing correlation values of state model after the retraining.*/
	public Structure getStateTestCorrForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getStateTestCorr();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}

/** Get the training correlation values of state model after the retraining.*/
	public Structure getStateTrainingCorrForG2(){
	  
	   Structure retval = new Structure();
	   try {
		   double[] vals = optimizer.getStateTrainingCorr();
			 retval.setAttributeValue(RETVAL_, vals);
	   } catch (Exception ie){
			errorOccur(ie.getMessage());
		   retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
		   retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace
							   (ie)));
	   }
	   return retval;
	}
  /**	Test whether the model is loaded.*/ 
  public boolean isLoaded(){
	  return isloaded;
  }
  
  /**	Load optimziation from optimization name.*/ 
  public boolean loadFromProject(String mName){
	if (NolMainFrame.mainFrame != null){
		Project2 project = NolMainFrame.mainFrame.getProject();
		int index = project.getOptimizationIndexByName(mName);
		if (index == -1) {
			return false;
		}
		NolOptimization opt = project.getOptimization(index);
		try{
		  optimizer = new OnlineOptimizer(mName,opt);
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
  /** Get the status message of this data OnlineOptimizer. */	
  public String getStatusMessage(){
  		if(isloaded){
			return optimizer.getStatusMessage();
		}
		return "";
	}

/** Return the names of variables that reach their hard bounds.
*/
	public Sequence getVariableNameAtHardBound(){
		Sequence retval = new Sequence();
		try{
			if(isloaded){
				String[] names = optimizer.getVariableNameAtHardBound();
				for(int i=0;i<names.length;i++){
					retval.addElement(names[i]);
				}
			}
		}catch(MathException evt){
			errorOccur(evt.getMessage());
		}
		return retval;
	}

/**	Save the model and formulas from a file.*/ 
  public boolean saveModel(final String file, final String directory){
	// try to start writing
	String fileName = file;
	String pName = fileName;
	int dotInd = fileName.indexOf(".");
	if(dotInd == -1){
		fileName = fileName+".opt";
	}else{
		pName = fileName.substring(0,dotInd);	
	}
	optimizer.setName(pName);
	try {
		Class versionManagerClass = Class.forName("com.gensym.nols.data.VersionManagerForOnlineOptimizer");
		Object versionManager = versionManagerClass.newInstance();
		Method method = versionManagerClass.getMethod("setOptimizer",new Class[] {optimizer.getClass()});
		method.invoke(versionManager,new Object[] {optimizer});
		method = versionManagerClass.getMethod("saveToFile",new Class[] {directory.getClass(), fileName.getClass()});
		method.invoke(versionManager,new Object[] {directory, fileName});
	} catch (Exception ex) {
		errorOccur(ex.getMessage());
		return false;
	}
	return true;
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
					isloaded=true;
				}catch(G2AccessException evt){
					isloaded=false;
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

}


