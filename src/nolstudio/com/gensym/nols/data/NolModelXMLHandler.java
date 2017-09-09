package com.gensym.nols.data;
/*
 *		Gensym NolModelXMLHandler Class.
 *		This class is extended from Object.class
 *		Modified 12/15/2006 by Gchen
 */

import java.io.BufferedWriter;
import java.io.Closeable;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Serializable;
import java.io.Writer;
import java.nio.charset.Charset;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.datafit.EnsembleModel;

public class NolModelXMLHandler implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	private Vector outputVarNames; 
	private Vector trainingRmse; 
	private Vector testingRmse; 
	private Vector trainingCorroef; 
	private Vector testingCorroef; 

	private double modelRateValue = 0.0;
	private NolModel2 model;
	private int indNumber = 1;

/** Create a new NolModelXMLHandler containing no characters.*/
	public NolModelXMLHandler() {
		super();
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		NolModelXMLHandler cloned = (NolModelXMLHandler) super.clone();
		cloned.outputVarNames = outputVarNames == null ? null : (Vector) outputVarNames.clone();
		cloned.trainingRmse = trainingRmse == null ? null : (Vector) trainingRmse.clone();
		cloned.testingRmse = testingRmse == null ? null : (Vector) testingRmse.clone();
		cloned.trainingCorroef = trainingCorroef == null ? null : (Vector) trainingCorroef.clone();
		cloned.testingCorroef = testingCorroef == null ? null : (Vector) testingCorroef.clone();

		cloned.model = model == null ? null : (NolModel2) model.clone();
		return cloned;
	}

/** set the model.*/
	public void setModel(NolModel2 model) {
		this.model = model;
		model.calculateModelStatistics();
		modelRateValue = model.getModelRate();
		outputVarNames = model.getOutputVarNames();
		trainingRmse = model.getTrainingRmse();
		testingRmse = model.getTestingRmse();
		trainingCorroef = model.getTrainingCorrcoef();
		testingCorroef = model.getTestingCorrcoef();
	}

/** set the model rate.*/
	public void setModelRate(double modelRateValue) {
		this.modelRateValue = modelRateValue;
	}

	public double getModelRate() {
		return this.modelRateValue;
	}

	public Vector getTrainingRmse() {
		return this.trainingRmse;
	}

	public Vector getTrainingCorroef() {
		return this.trainingCorroef;
	}

	public Vector getTestingRmse() {
		return this.testingRmse;
	}

	public Vector getTestingCorref() {
		return this.testingCorroef;
	}

/** save out the xml file to the specified file.*/
	public void saveToFile(String fileName, String directory) throws IOException, MathException{
		File targetFile;
		if(directory==null)
			targetFile = new File(fileName);	
		else
			targetFile = new File(directory,fileName);
		
		BufferedWriter target = null;
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
		try {
	        outStream = new FileOutputStream(targetFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
	        target = new BufferedWriter(streamWriter);
			saveToStream(target);
			target.flush();
		} finally {
			closeSilently(target);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}	
	}
	
	private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("NON-FATAL: Error while closing stream : " + e.toString());
      } 
    }
		
/** save out the xml file to the specified file.*/
	public void saveToFile(String path) throws IOException, MathException{
		File targetFile;
		targetFile = new File(path);
		BufferedWriter target = null;
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
		try {
	        outStream = new FileOutputStream(targetFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
	        target = new BufferedWriter(streamWriter);
			saveToStream(target);
			target.flush();
		} finally {
			closeSilently(target);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}
		
	private void saveToStream(BufferedWriter target) throws IOException, MathException{
		if(model instanceof NolAnnModel ){
			saveAnnToFile(target);	
		}else if(model instanceof NolBpnModel){
			saveBpnToFile(target);	
		}else if(model instanceof NolRhoModel ){
			saveRhoToFile(target);	
		}else if(model instanceof NolRbfnModel){
			saveRbfnToFile(target);	
		}else if(model instanceof NolPlsModel){
			savePlsToFile(target);	
		}else if(model instanceof NolPcaModel){
			savePcaToFile(target);	
		}else{
			savePredictiveModelToFile(target);	
		}
	}

/** save out the xml file to the specified file.*/
	public void savePlsToFile(BufferedWriter target) throws IOException, MathException{
		indNumber = 1;		
		String dataString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		target.write(dataString,0,dataString.length());
		dataString = "<GNNEPLSModel>\n";
		target.write(dataString,0,dataString.length());
		indNumber = saveModelInfo(target, indNumber);
  // Start write the pls network.
		indNumber = ((NolPlsModel)model).writeXMLFile(target, indNumber);
		dataString = "</GNNEPLSModel>";
		target.write(dataString,0,dataString.length());
	}
/** save out the xml file to the specified file.*/
	public void savePcaToFile(BufferedWriter target) throws IOException, MathException{

	}


/** save out the xml file to the specified file.*/
	public void saveAnnToFile(BufferedWriter target) throws IOException, MathException{
		indNumber = 1;		
		String dataString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		target.write(dataString,0,dataString.length());
		dataString = "<GNNEAANModel>\n";
		target.write(dataString,0,dataString.length());
		indNumber = saveModelInfo(target, indNumber);
  // Start write the bpn network.
		indNumber = ((NolBpnModel)model).writeXMLFile(target, indNumber);
		dataString = "</GNNEAANModel>";
		target.write(dataString,0,dataString.length());
	}
/** save out the xml file to the specified file.*/
	public void saveBpnToFile(BufferedWriter target) throws IOException, MathException{
		indNumber = 1;		
		String dataString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		target.write(dataString,0,dataString.length());
		dataString = "<GNNEBPNModel>\n";
		target.write(dataString,0,dataString.length());
		indNumber = saveModelInfo(target, indNumber);
  // Start write the bpn network.
		indNumber = ((NolBpnModel)model).writeXMLFile(target, indNumber);
		dataString = "</GNNEBPNModel>";
		target.write(dataString,0,dataString.length());
	}
/** save out the xml file to the specified file.*/
	public void saveRhoToFile(BufferedWriter target) throws IOException, MathException{
		indNumber = 1;		
		String dataString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		target.write(dataString,0,dataString.length());
		dataString = "<GNNERHOModel>\n";
		target.write(dataString,0,dataString.length());
		indNumber = saveModelInfo(target, indNumber);
  // Start write the rbfn network.
		indNumber = ((NolRbfnModel)model).writeXMLFile(target, indNumber);
		dataString = "</GNNERHOModel>";
		target.write(dataString,0,dataString.length());
	}
/** save out the xml file to the specified file.*/
	public void saveRbfnToFile(BufferedWriter target) throws IOException, MathException{
		indNumber = 1;		
		String dataString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		target.write(dataString,0,dataString.length());
		dataString = "<GNNERBFNModel>\n";
		target.write(dataString,0,dataString.length());
		indNumber = saveModelInfo(target, indNumber);
  // Start write the rbfn network.
		indNumber = ((NolRbfnModel)model).writeXMLFile(target, indNumber);
		dataString = "</GNNERBFNModel>";
		target.write(dataString,0,dataString.length());
	}

/** save out the xml file to the specified file.*/
	public void savePredictiveModelToFile(BufferedWriter target) throws IOException, MathException{
		indNumber = 1;		
		String dataString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		target.write(dataString,0,dataString.length());
		dataString = "<PredictiveModel>\n";
		target.write(dataString,0,dataString.length());
		indNumber = saveModelInfo(target, indNumber);
  // Start write the ensemble network.
		EnsembleModel ensemble = (EnsembleModel)model.getModel();
		indNumber = ensemble.writeXMLFile(target, indNumber);
		dataString = "</PredictiveModel>";
		target.write(dataString,0,dataString.length());
	}		

	private String indent(int indentNumber){
		String str = "";
		for (int i=0;i<indentNumber;i++){
			str = str + "\t";
		}
		return str;
	}

	private int saveModelInfo(BufferedWriter target, int indentNumber)throws IOException, MathException{
		String dataString = indent(indNumber)+"<name>"+model.getName()+"</name>\n";
		target.write(dataString,0,dataString.length());
		dataString = indent(indNumber)+"<comment>"+model.getComment()+"</comment>\n";
		target.write(dataString,0,dataString.length());
		dataString = indent(indNumber)+"<isTimeBased>"+model.getHasTimeStamps()+"</isTimeBased>\n";
		target.write(dataString,0,dataString.length());
		dataString = indent(indNumber)+"<modelStatistics>\n";
		target.write(dataString,0,dataString.length());
		indNumber++;
		dataString = indent(indNumber)+"<modelRate>"+modelRateValue+"</modelRate>\n";
		target.write(dataString,0,dataString.length());
		dataString = indent(indNumber)+"<outputStatistics>\n";
		target.write(dataString,0,dataString.length());
		indNumber++;
		int nv = outputVarNames.size();
		for(int i=0;i<nv;i++){
			dataString = indent(indNumber)+"<variableStatistics>\n";
			target.write(dataString,0,dataString.length());
			indNumber++;
			dataString = indent(indNumber)+"<name>"+outputVarNames.elementAt(i)+"</name>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<training>\n";
			target.write(dataString,0,dataString.length());
			indNumber++;
			dataString = indent(indNumber)+"<rmse>"+trainingRmse.elementAt(i)+"</rmse>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<corrcoef>"+trainingCorroef.elementAt(i)+"</corrcoef>\n";
			target.write(dataString,0,dataString.length());
			indNumber--;
			dataString = indent(indNumber)+"</training>\n";
			target.write(dataString,0,dataString.length());

			dataString = indent(indNumber)+"<testing>\n";
			target.write(dataString,0,dataString.length());
			indNumber++;
			dataString = indent(indNumber)+"<rmse>"+testingRmse.elementAt(i)+"</rmse>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<corrcoef>"+testingCorroef.elementAt(i)+"</corrcoef>\n";
			target.write(dataString,0,dataString.length());
			indNumber--;
			dataString = indent(indNumber)+"</testing>\n";
			target.write(dataString,0,dataString.length());
			indNumber--;			
			dataString = indent(indNumber)+"</variableStatistics>\n";
			target.write(dataString,0,dataString.length());
		}
		indNumber--;			
		dataString = indent(indNumber)+"</outputStatistics>\n";
		target.write(dataString,0,dataString.length());
		indNumber--;			
		dataString = indent(indNumber)+"</modelStatistics>\n";
		target.write(dataString,0,dataString.length());

//Begin the variables
		int inputIndex = 0;
		Vector outDelays = model.getOutputDelays();
		dataString = indent(indNumber)+"<variables>\n";
		target.write(dataString,0,dataString.length());
		indNumber++;

		Vector outs = model.getOutputs();
		int nout = outs.size();
		Preprocessor preprocessor = model.getPreprocessor();
		for(int i=0;i<nout;i++){
			dataString = indent(indNumber)+"<variable>\n";
			target.write(dataString,0,dataString.length());
			indNumber++;
			
			String varName = (String)outs.elementAt(i);
			Variable varObj = preprocessor.getVariableFromVariableName(varName);
			
			dataString = indent(indNumber)+"<name>"+varObj.getName()+"</name>\n";
			target.write(dataString,0,dataString.length());
			if (!varObj.getTag().equals("")) {
				dataString = indent(indNumber)+"<tag>"+varObj.getTag()+"</tag>\n";
				target.write(dataString,0,dataString.length());
			}
			if (!(varObj.getUnit().equals("")) && !(varObj.getUnit().equals("None"))) {
				dataString = indent(indNumber)+"<unit>"+varObj.getUnit()+"</unit>\n";
				target.write(dataString,0,dataString.length());
			}

			dataString = indent(indNumber)+"<statistics>\n";
			target.write(dataString,0,dataString.length());
			indNumber++;

			dataString = indent(indNumber)+"<min>"+varObj.getMinValue()+"</min>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<max>"+varObj.getMaxValue()+"</max>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<mean>"+varObj.getMeanValue()+"</mean>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<median>"+varObj.getMedianValue()+"</median>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<std>"+varObj.getSTD()+"</std>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<variance>"+varObj.getVariance()+"</variance>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<kurt>"+varObj.getKurt()+"</kurt>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<skew>"+varObj.getSkew()+"</skew>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<range>"+varObj.getRange()+"</range>\n";
			target.write(dataString,0,dataString.length());
			indNumber--;
			dataString = indent(indNumber)+"</statistics>\n";
			target.write(dataString,0,dataString.length());
			
			dataString = indent(indNumber)+"<node>\n";
			target.write(dataString,0,dataString.length());
			indNumber++;
			dataString = indent(indNumber)+"<index>"+i+"</index>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<classification>output</classification>\n";
			target.write(dataString,0,dataString.length());
			indNumber--;
			dataString = indent(indNumber)+"</node>\n";
			target.write(dataString,0,dataString.length());
	
			if(model.getHasTimeStamps()){
				long[] dls = (long[])outDelays.elementAt(i);
				if (dls.length > 0){
					if (dls.length != 1 || dls[0] != 0){
						for(int j=0;j<dls.length;j++){
							dataString = indent(indNumber)+"<node>\n";
							target.write(dataString,0,dataString.length());
							indNumber++;
							dataString = indent(indNumber)+"<index>"+inputIndex+"</index>\n";
							target.write(dataString,0,dataString.length());
							inputIndex =inputIndex + 1;
							dataString = indent(indNumber)+"<classification>input</classification>\n";
							target.write(dataString,0,dataString.length());
							dataString = indent(indNumber)+"<delay>"+dls[j]+"</delay>\n";
							target.write(dataString,0,dataString.length());
							indNumber--;
							dataString = indent(indNumber)+"</node>\n";
							target.write(dataString,0,dataString.length());
						}
					}
				}
			}
			indNumber--;
			dataString = indent(indNumber)+"</variable>\n";
			target.write(dataString,0,dataString.length());
		}
		Vector ins = model.getInputs();
		Vector inDelays = model.getInputDelays();
		for(int i=0;i<ins.size();i++){
			dataString = indent(indNumber)+"<variable>\n";
			target.write(dataString,0,dataString.length());
			indNumber++;
			String varName = (String)ins.elementAt(i);
			Variable varObj = preprocessor.getVariableFromVariableName(varName);
			dataString = indent(indNumber)+"<name>"+varObj.getName()+"</name>\n";
			target.write(dataString,0,dataString.length());
			if (!varObj.getTag().equals("")) {
				dataString = indent(indNumber)+"<tag>"+varObj.getTag()+"</tag>\n";
				target.write(dataString,0,dataString.length());
			}
			if (!(varObj.getUnit().equals("")) && !(varObj.getUnit().equals("None"))) {
				dataString = indent(indNumber)+"<unit>"+varObj.getUnit()+"</unit>\n";
				target.write(dataString,0,dataString.length());
			}

			dataString = indent(indNumber)+"<statistics>\n";
			target.write(dataString,0,dataString.length());
			indNumber++;

			dataString = indent(indNumber)+"<min>"+varObj.getMinValue()+"</min>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<max>"+varObj.getMaxValue()+"</max>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<mean>"+varObj.getMeanValue()+"</mean>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<median>"+varObj.getMedianValue()+"</median>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<std>"+varObj.getSTD()+"</std>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<variance>"+varObj.getVariance()+"</variance>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<kurt>"+varObj.getKurt()+"</kurt>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<skew>"+varObj.getSkew()+"</skew>\n";
			target.write(dataString,0,dataString.length());
			dataString = indent(indNumber)+"<range>"+varObj.getRange()+"</range>\n";
			target.write(dataString,0,dataString.length());
			indNumber--;
			dataString = indent(indNumber)+"</statistics>\n";
			target.write(dataString,0,dataString.length());

			if(model.getHasTimeStamps()){
				long[] dls = (long[])inDelays.elementAt(i);
				if ((dls.length == 1 && dls[0] == 0) || dls.length == 0){
 					dataString = indent(indNumber)+"<node>\n";
					target.write(dataString,0,dataString.length());
					indNumber++;
 					dataString = indent(indNumber)+"<index>"+inputIndex+"</index>\n";
					target.write(dataString,0,dataString.length());
					inputIndex =inputIndex + 1;
					dataString = indent(indNumber)+"<classification>input</classification>\n";
					target.write(dataString,0,dataString.length());
					dataString = indent(indNumber)+"<delay>"+0.0+"</delay>\n";
					target.write(dataString,0,dataString.length());
					indNumber--;
 					dataString = indent(indNumber)+"</node>\n";
					target.write(dataString,0,dataString.length());
				}else{
					for(int j=0;j<dls.length;j++){
						if(dls[j]>0){
 							dataString = indent(indNumber)+"<node>\n";
							target.write(dataString,0,dataString.length());
							indNumber++;
 							dataString = indent(indNumber)+"<index>"+inputIndex+"</index>\n";
							target.write(dataString,0,dataString.length());
							inputIndex =inputIndex + 1;
							dataString = indent(indNumber)+"<classification>input</classification>\n";
							target.write(dataString,0,dataString.length());
							dataString = indent(indNumber)+"<delay>"+dls[j]+"</delay>\n";
							target.write(dataString,0,dataString.length());
							indNumber--;
 							dataString = indent(indNumber)+"</node>\n";
							target.write(dataString,0,dataString.length());
						}
					}
				}
			}else{
 				dataString = indent(indNumber)+"<node>\n";
				target.write(dataString,0,dataString.length());
				indNumber++;
 				dataString = indent(indNumber)+"<index>"+inputIndex+"</index>\n";
				target.write(dataString,0,dataString.length());
				inputIndex =inputIndex + 1;
				dataString = indent(indNumber)+"<classification>input</classification>\n";
				target.write(dataString,0,dataString.length());
				indNumber--;
 				dataString = indent(indNumber)+"</node>\n";
				target.write(dataString,0,dataString.length());
			}
			indNumber--;
			dataString = indent(indNumber)+"</variable>\n";
			target.write(dataString,0,dataString.length());
		}
		indNumber--;
		dataString = indent(indNumber)+"</variables>\n";
		target.write(dataString,0,dataString.length());
		target.flush();
		return indNumber;
	}
}
