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

/** Model class. */
public class NolBpnModel extends NolModel2 implements ClassicModel {
	static final long serialVersionUID = 1L;
	protected int iterations;
	protected int trainingMethod;
	protected int pcaFlag;
	public ClassicValidationParameters trainingResults;

/** Create a NolBpnModel object with given ClassicBpn object.*/	
	public NolBpnModel(ClassicBpn net, String name, Vector outs, 
		Vector ins, Vector oDelays, Vector iDelays, Preprocessor prep){
		super();
		preprocessor = prep;
		preprocessorHashCode = prep.hashCode();
		this.name = new String(name);
		model = net;
		iterations =40;
		trainingMethod =3;
		pcaFlag =0;
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
		NolBpnModel cloned = (NolBpnModel) super.clone();
		cloned.trainingResults = trainingResults == null ? null : new ClassicValidationParameters(trainingResults);
		return cloned;
	}

	public void setRunningParameter(int iterations,int method,int pcaFlag){
		this.iterations = iterations;
		this.trainingMethod = method;
		this.pcaFlag = pcaFlag;
	}

	public int getIterations(){
		return iterations;
	}
	
	public int getTrainingMethod(){
		return trainingMethod;
	}

	public int getPcaFlag(){
		return pcaFlag;
	}
	
	public void prepareDataStat(Matrix X, Matrix Y)throws MathException{
		ClassicBpn net = (ClassicBpn)model;
		net.prepareDataStat(X,Y);
	}

	public void writeBpnToFile(String outfile,Matrix X, Matrix Y)throws IOException,MathException{
		ClassicBpn net = (ClassicBpn)model;
		double pcaFactor = 0;
		if(pcaFlag > 0) {
			pcaFactor = 0.02;
		}
		File SourceFile = new File(outfile);
		
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			net.writeData(Source, X, Y);
			Source.write("100, 0.0, "+trainingMethod+", "+pcaFactor+" ; Control vector for training");
			Source.newLine();
			net.writeWeights(Source);
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}
	
	public void writeBpnToFile(String outfile)throws IOException{
		ClassicBpn net = (ClassicBpn)model;
		File SourceFile = new File(outfile);
		
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			net.writeUnscaledWeights(Source);
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}

	public void readBpnFromFile(String infile)throws IOException{
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
			ClassicBpn net = (ClassicBpn)model;
			net.readWeights(Source);
	    } finally {
	  	  closeSilently(Source);
	  	  closeSilently(streamReader);
	  	  closeSilently(inStream);
	  	}
	    
		isTrained = true;
	}
	
	@Override
	public double getRMSE(){
		ClassicBpn net = (ClassicBpn)model;	 
		return net.getRMSE();

	}
	protected transient NolClassicModelTrainer trainer;
	public void setTrainer(NolClassicModelTrainer classicModelTrainer){
		this.trainer = classicModelTrainer;
	}


	public void train(Matrix XTrain, Matrix YTrain)throws IOException,MathException{
		int iterationsLocal = getIterations();
		int counter = iterationsLocal/100;
		prepareDataStat(XTrain,YTrain);
		int savepcaflag = pcaFlag;
		for(int i=0;i<counter;i++){
			if(i==0)
				pcaFlag = 0;
			else
				pcaFlag = savepcaflag;
			String [] fileNames = trainer.makeRPCfileNames(); 
			writeBpnToFile(fileNames[0],XTrain,YTrain);
			int result = trainer.jbpn_trainer(fileNames[0],fileNames[1]);
			if(result == 1)
				readBpnFromFile(fileNames[1]);
			else {
				String message = trainer.readErrorFromFile(fileNames[1]);
				trainer.informListeners("error",message);
				return;
			}

			trainer.informListeners("update","");
			trainer.deleteFiles(fileNames);
		}
		trainingResults = new ClassicValidationParameters(this,XTrain,YTrain);
		trainer.informListeners("complete","");
	}

	@Override
	public String getDescription(){
		return ((ClassicBpn)model).getDescription();
	
	}

/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() throws MathException {
		ClassicBpn net = (ClassicBpn)getModel();
		return net.getParametersVector();
	}

/** Set the model information as in a Vector */
	@Override
	public void setParametersVector(Vector params) throws MathException {
		ClassicBpn net = (ClassicBpn)getModel();
		net.setParametersVector(params);
	}

	public int writeXMLFile(final BufferedWriter target, final int indentNumber) throws IOException, MathException {
		ClassicBpn net = (ClassicBpn)model;
		return net.writeXMLFile(target,indentNumber);
	}
}

