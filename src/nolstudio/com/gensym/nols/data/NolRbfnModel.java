package com.gensym.nols.data;
/*
 *		Gensym Model Class.
 *		This class is extended from Object.class
 *		Modified 3/25/98 by Gchen
 */

import java.util.*;
import java.io.*;
import java.nio.charset.Charset;

import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;
import com.gensym.nols.util.Parser;

/** Model class. */
public class NolRbfnModel extends NolModel2 implements ClassicModel {
	static final long serialVersionUID = 1L;
	protected int trainingMethod;
	private double rmse	;
	protected String description = "";
	public ClassicValidationParameters trainingResults;
	protected boolean normalizeData;

	protected transient NolClassicModelTrainer trainer;

/** Create a NolRbfnModel object with given ClassicRbfn object.*/	
	public NolRbfnModel(ClassicRbfn net, String name, Vector outs, 
		Vector ins, Vector oDelays, Vector iDelays, Preprocessor prep){
		super();
		preprocessor = prep;
		preprocessorHashCode = prep.hashCode();
		this.name = new String(name);
		model = net;
		trainingMethod =0;
		normalizeData = false;
		try{
			inputs = (Vector)ins.clone();
			outputs = (Vector)outs.clone();
			inputDelays = (Vector)iDelays.clone();
			outputDelays = (Vector)oDelays.clone();
		}catch(Exception e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		NolRbfnModel cloned = (NolRbfnModel) super.clone();
		cloned.trainingResults = trainingResults == null ? null : new ClassicValidationParameters(trainingResults);
		return cloned;
	}

	public void setTrainer(NolClassicModelTrainer trainer){
		this.trainer = trainer;
	}

	public void setRunningParameter(int method){
		this.trainingMethod = method;
	}

	public void setNormalizeData(boolean b){
		this.normalizeData = b;
		ClassicRbfn net = (ClassicRbfn)model;
		net.setNormalizeData(b);
	}

	public boolean isNormalizeData(){
		return normalizeData;
	}

	public void prepareDataStat(Matrix X, Matrix Y)throws MathException{
		ClassicRbfn net = (ClassicRbfn)model;
		net.prepareDataStat(X,Y);
	}

	public void writeRbfnToFile(String outfile,Matrix X, Matrix Y)throws IOException,MathException{
		ClassicRbfn net = (ClassicRbfn)model;
	    FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
			File SourceFile = new File(outfile);
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			net.writeData(Source, X, Y);
			net.writeParameters(Source);
			if(trainingMethod == 0){
	 			Source.write(trainingMethod+"; normal clustering method");
			}else{
				Source.write(trainingMethod+"; class-separate clustering");
			}
			
			Source.newLine();
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}
	
	public void writeRbfnToFile(String outfile)throws IOException{
		ClassicRbfn net = (ClassicRbfn)model;
		
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
			File SourceFile = new File(outfile);
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			net.writeParameters(Source);
			net.writeWeights(Source);
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}


	public void writeNormalizeFactorToFile(String outfile)throws IOException{
		ClassicRbfn net = (ClassicRbfn)model;
		
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
			File SourceFile = new File(outfile);
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			Vector ins = getInputs();
			Vector inDelays = getInputDelays();
			double divide = 60000;
			Source.write("Variables,");
			for(int i=0;i<inDelays.size();i++){
				long[] dls = (long[])inDelays.elementAt(i);
				if(dls.length == 1 && dls[0] == 0){
			 			Source.write(ins.elementAt(i).toString()+",");
				}else{
					for(int j=0;j<dls.length;j++){
						int dd = (int) (dls[j]/divide);
			 			Source.write(ins.elementAt(i)+"("+dd+"),");
					}
				}
			}
	 		Vector outs = getOutputs();
			for(int i=0;i<outs.size();i++){
			 	Source.write(outs.elementAt(i).toString());
				if(i< outs.size()-1){
					Source.write(",");
				}
			}
			Source.newLine();
			net.writeNormalizeFactorToFile(Source);
			Source.newLine();
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}


	public void readRbfnFromFile(String infile)throws IOException{
		File SourceFile = new File(infile);
		if (!SourceFile.exists() || !SourceFile.isFile() || !SourceFile.canRead()) 
			return;
		
		FileInputStream inStream = null;
	    Reader streamReader = null;
	    BufferedReader Source = null;
	    try {
	      inStream = new FileInputStream(SourceFile);	
	      streamReader = new InputStreamReader(inStream, Charset.defaultCharset());
	      Source = new BufferedReader(streamReader);
		
		  ClassicRbfn net = (ClassicRbfn)model;
		  net.readWeights(Source);
	    } finally {
	  	  closeSilently(Source);
	  	  closeSilently(streamReader);
	  	  closeSilently(inStream);
	  	}
	    
		isTrained = true;
	}
		
	public void writeRbfnForEvaluate(String outfile,Matrix X, Matrix Y)throws IOException,MathException{
		ClassicRbfn net = (ClassicRbfn)model;
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
			File SourceFile = new File(outfile);
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			net.writeData(Source, X, Y);
			Source.write("1:  Net is RBFN or RHO NET");
			Source.newLine();
			net.writeParameters(Source);
			net.writeWeights(Source);
			Source.write("0 ;  RMSE fit metric");
			Source.newLine();
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}


	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException{
		if(trainer == null){
			trainer = new NolClassicModelTrainer(this);
		}
		int row = X.getRows();
		int col = getNout();
		Y.redimension(row,col);
		Y.initialize(0);
		try{
			trainer.setFlag(NolClassicModelTrainer.RBFNFIT);
			trainer.setInput(X);
			trainer.setOutput(Y);
			String [] fileNames = trainer.makeRPCfileNames(); 
			writeRbfnForEvaluate(fileNames[0],X,Y);
			int result = trainer.jfit_tester(fileNames[0],fileNames[1]);
			readPredictionFromFile(fileNames[1],Y);
			trainer.deleteFiles(fileNames);
		}catch(IOException evt){
			evt.printStackTrace();
			throw new MathException(evt.getMessage());
		}
	}

	public void readPredictionFromFile(String infile, Matrix YPred)throws MathException, IOException{
		File SourceFile = new File(infile);
		if (!SourceFile.exists() || !SourceFile.isFile() || !SourceFile.canRead()){
			return;
		}
		
		Vector dataString = new Vector();
		FileInputStream inStream = null;
	    Reader streamReader = null;
	    BufferedReader Source = null;
	    try {
	      inStream = new FileInputStream(SourceFile);	
	      streamReader = new InputStreamReader(inStream, Charset.defaultCharset());
	      Source = new BufferedReader(streamReader);
	      
		  while(true){
			String lineStr = Source.readLine();
			if(lineStr == null) {
				break;
			}
			dataString.addElement(lineStr);
		  }
	    } finally {
	  	  closeSilently(Source);
	  	  closeSilently(streamReader);
	  	  closeSilently(inStream);
	  	}

	    int row = dataString.size()-1;
		String lineStr = (String)dataString.elementAt(0);
		int sepIndex = lineStr.indexOf(";",0);
		String valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		Vector ss = Parser.string2Strings(valueString,",");
		int col = ss.size();
		YPred.redimension(row,col);
		for(int j=0;j<col;j++){
			String s = (String)ss.elementAt(j);
			double d = Double.valueOf(s).doubleValue();
			YPred.set(0,j,d);
		}
		for(int i=1;i<row;i++){
			lineStr = (String)dataString.elementAt(i);
			sepIndex = lineStr.indexOf(";",0);
			valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
			ss = Parser.string2Strings(valueString,",");
			for(int j=0;j<col;j++){
				String s = (String)ss.elementAt(j);
				double d = Double.valueOf(s).doubleValue();
				YPred.set(i,j,d);
			}
		}
		lineStr = (String)dataString.elementAt(row);
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		rmse = Double.valueOf(valueString).doubleValue();
		ClassicRbfn net = (ClassicRbfn)model;	 
		if(normalizeData) {
			net.unnormalizePrediction(YPred);
		}
	}

	@Override
	public double getRMSE(){
		return rmse;
	}

	@Override
	public String getDescription(){
		return ((ClassicRbfn)model).getDescription();
	}

	public void train(Matrix XTrain, Matrix YTrain)throws IOException,MathException{
		trainer.setFlag(NolClassicModelTrainer.RBFNTRAINING);
		prepareDataStat(XTrain,YTrain);
		String [] fileNames = trainer.makeRPCfileNames(); 
		writeRbfnToFile(fileNames[0],XTrain,YTrain);
		int result = trainer.jrbfn_trainer(fileNames[0],fileNames[1]);
		if(result == 1){
			readRbfnFromFile(fileNames[1]);
			trainingResults = new ClassicValidationParameters(this,XTrain,YTrain);
			trainer.informListeners("complete","");
		}else{
			String message = trainer.readErrorFromFile(fileNames[1]);
			trainer.informListeners("error",message);
		}
		trainer.deleteFiles(fileNames);
	}
/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() throws MathException {
		ClassicRbfn net = (ClassicRbfn)getModel();
		return net.getParametersVector();
	}

/** Set the model information as in a Vector */
	@Override
	public void setParametersVector(Vector params) throws MathException {
		ClassicRbfn net = (ClassicRbfn)getModel();
		net.setParametersVector(params);
	}

	public int writeXMLFile(final BufferedWriter target, final int indentNumber) throws IOException, MathException {
		ClassicRbfn net = (ClassicRbfn)model;
		return net.writeXMLFile(target,indentNumber);
	}
}

