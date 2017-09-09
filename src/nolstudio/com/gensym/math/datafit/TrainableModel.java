package com.gensym.math.datafit;

import java.io.*;
import java.nio.charset.Charset;
import java.util.*;

import com.gensym.math.matrix.*;
import com.gensym.math.MathException;

public class TrainableModel implements TrainableModelInterface, Serializable, Cloneable {
	static final long serialVersionUID = 1L;
	public ArchitectureParameters AP;
	public ValidationParameters trainingResults;
	public ValidationParameters testingResults;
	public boolean[] testingSamples;   // 2.1 -- indicates which samples were used from training
	public long trainingTime;
	public Matrix outputVariance;

	public TrainableModel(ArchitectureParameters AP) {
		this.AP = AP;
		trainingResults = null;
		testingResults = null;
		trainingTime = 0l;
		outputVariance = Matlib.createMatrix();
		testingSamples = null;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		TrainableModel cloned = (TrainableModel) super.clone();
		cloned.AP = AP == null ? null : new ArchitectureParameters(AP);
		cloned.trainingResults = trainingResults == null ? null : new ValidationParameters(trainingResults);
		cloned.testingResults = testingResults == null ? null : new ValidationParameters(testingResults);
		cloned.outputVariance = outputVariance == null ? null : (Matrix)outputVariance.clone();
		
		return cloned;
	}

	/** The user calls train, but implements learn.  Train calls the 
	model's learn method. */
	public final void train(Matrix X, Matrix Y) throws MathException {
		long startTime = System.currentTimeMillis();
		Matlib.var(Y,outputVariance);  // default -- hard coded for now
		learn(X,Y);
		trainingTime = System.currentTimeMillis() - startTime;
	}

	@Override
	public int getNin() {
		return AP.nin;
	}

	@Override
	public int getNout() {
		return AP.nout;
	}

	@Override
	public ArchitectureParameters getArchitectureParameters() {
		return AP;
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		// implemented by subclasses
	}

	/** Never call learn directly.  Call train instead. */
	@Override
	public void learn(Matrix X, Matrix Y) throws MathException {
		// implemented by subclasses
	}

	// like getDescription, but prints to System.out
	public void describe() {   
		System.out.println(getDescription());
	}


	public String getDescription() {
		String classname =  this.getClass().getName();
		classname = classname.substring(24);  // eliminate com.gensym.blah,blah
		return ("Trainable model: "+classname+" with "+AP.nfactors+" factors, "+AP.nhidden+" hidden");
	}

	public void writeWeightFile(String fileName) throws IOException, MathException {
		writeWeightFile(null,fileName);
	}

	public void writeWeightFile(String dir,String fileName) throws IOException, MathException {
		File SourceFile = null;
		if(dir == null)
			SourceFile = new File(fileName);
		else
			SourceFile = new File(dir,fileName);
		
	    FileOutputStream outStream = null;
	    Writer fileOut = null;
	    BufferedWriter Source = null;
	    try {
	    	outStream = new FileOutputStream(SourceFile);
	    	fileOut = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(fileOut);
			writeWeights(Source);
	    }finally {
	  	  closeSilently(Source);
	  	  closeSilently(fileOut);
	  	  closeSilently(outStream);
	    }
	}
	
	protected void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println(e.toString());
      } 
	}

	public void writeWeights(BufferedWriter Source) throws IOException, MathException {
		// implemented in subclasses
	}

	public String getModelParameters(String modelName, int index) throws MathException {
		// implemented in subclasses
		return "";
	}

	public void writeParamVariable(StringBuffer sb, int index) {
		// implemented in subclasses
	}
	public void writeWeightAsC(StringBuffer sb, int index) {
		// implemented in subclasses
	}

	public void writeMatrixInit(StringBuffer sb, int index) {
		// implemented in subclasses
	}
	public Vector getParametersVector() throws MathException {
		return new Vector();
		// implemented in subclasses
	}

	public int writeXMLFile(BufferedWriter Source, int indentNumber) throws IOException, MathException {
		// implemented in subclasses
		return indentNumber; 
	}
}
