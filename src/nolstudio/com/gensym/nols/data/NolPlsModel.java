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
import com.gensym.math.stats.Stats;

/** Model class. */
public class NolPlsModel extends NolModel2{
	static final long serialVersionUID = 1L;
	public ClassicValidationParameters trainingResults;
	private boolean givenModelStructure = false;
	private Vector models;
	private Vector ratings;
	private int predictionSize;
	private int capacity;
	private int numberOfModelsTrained;
	private ArchitectureParameters AP;
 	private transient Vector structureBuffer = null;
	private boolean fixedFactor = false;
	private int fixedFactorNumber = 0;

	static final int LINEAR_PHASE_TRIALS = 20;
	static final int ONE_STRUCTURE_TRIALS = 2;

	protected boolean VERBOSE = false;

/** Create a NolPlsModel object with given pls object.*/	
	public NolPlsModel(ArchitectureParameters AP, String name, Vector outs, 
		Vector ins, Vector oDelays, Vector iDelays, Preprocessor prep){
		super();
		preprocessor = prep;
		preprocessorHashCode = prep.hashCode();
		this.name = new String(name);
		this.AP = AP;
		capacity = 10;
		models = new Vector();
		ratings = new Vector();
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

	public void setFixedFactor(boolean fixedFactor){
		this.fixedFactor = fixedFactor;
	}

	public void setFixedFactorNumber(int f){
		this.fixedFactorNumber = f;
	}

	public void train(Matrix X, Matrix Y)throws MathException{
		if(fixedFactor){
			TrainableModel currentModel;
			ArchitectureParameters currentAP;
			double trainError, testError;
			ValidationParameters trainVP, testVP;
			int ndata=X.getRows(),ntrain,ntest,blockLength;
			if(ndata<10) {
				throw new MathException("Cannot train with less than 10 valid data points");
			}
			Matrix XTrain = Matlib.createMatrix();
			Matrix YTrain = Matlib.createMatrix();
			Matrix XTest = Matlib.createMatrix();
			Matrix YTest = Matlib.createMatrix();
			Matrix B = Matlib.createMatrix(); // train-test split
			// initially use 80% of training data or at most maxTrain samples 
			// (The random generation phase will automatically increase the number of examples if beneficial.)
			double percentTrain = 0.8, maxTrain = 100.0;
			ntrain = (int) Math.round(percentTrain*ndata/(1.0+percentTrain*ndata/maxTrain));
			ntest = ndata - ntrain;
			if(ntest<2) {
				ntrain = ndata - 2;   // prevent corrcoef problem by providing at least 2 test samples
				ntest = 2;
			}
			// seed the training with one PLS model, with 1 factor
			currentAP = new ArchitectureParameters(this.AP.nin,this.AP.nout,0,fixedFactorNumber);
			currentAP.trainingFraction = ((double) ntrain)/((double) ndata);
			currentModel = new Pls(currentAP);
			if(VERBOSE) {
				currentModel.describe();
			}
			Stats.randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);  // do a different split each time
			try{
				currentModel.train(XTrain,YTrain);
				currentModel.trainingResults = new ValidationParameters(currentModel,XTrain,YTrain);
				currentModel.testingResults = new ValidationParameters(currentModel,XTest,YTest);
	//				informListeners(model, EnsembleModelEvent.MODEL_TRAINED);
				if(VERBOSE) {
					System.out.println("train="+Utilities.formatDouble(currentModel.trainingResults.chisq,3)+", test="+Utilities.formatDouble(currentModel.testingResults.chisq,3)+", test95="+Utilities.formatDouble(currentModel.testingResults.chisq95,3));
				}
				int addedAt = addModel(currentModel);
				if(VERBOSE) {
					System.out.println("addedAt="+addedAt);
				}
				if(addedAt != -1) {
					boolean b[] = Matlib.create1DBooleanArray(B);
					currentModel.testingSamples = b;   	// store the incidence array of testing samples
					models.addElement(currentModel);
					ratings.addElement(0.0);
				}
			} catch (MathException e) {
				// if here, it is impossible to continue, since no seed model				
				if(VERBOSE){
					//e.printStackTrace();
					System.out.println("	EXCEPTION TRAINING SEED MODEL:"+e.getMessage());
				}
			}
			model = (Pls) models.elementAt(0);
			Matlib.clear(XTrain);
			Matlib.clear(YTrain);
			Matlib.clear(XTest);
			Matlib.clear(YTest);
			Matlib.clear(B);
			return;
		}

		TrainableModel baseModel, currentModel;
		ArchitectureParameters currentAP;
		double trainError, testError;
		ValidationParameters trainVP, testVP;
		int ndata=X.getRows(),ntrain,ntest,blockLength;
		if(ndata<10) {
			throw new MathException("Cannot train with less than 10 valid data points");
		}
		Matrix XTrain = Matlib.createMatrix();
		Matrix YTrain = Matlib.createMatrix();
		Matrix XTest = Matlib.createMatrix();
		Matrix YTest = Matlib.createMatrix();
		Matrix B = Matlib.createMatrix(); // train-test split
		// initially use 80% of training data or at most maxTrain samples 
		// (The random generation phase will automatically increase the number of examples if beneficial.)
		double percentTrain = 0.8, maxTrain = 100.0;
		ntrain = (int) Math.round(percentTrain*ndata/(1.0+percentTrain*ndata/maxTrain));
		ntest = ndata - ntrain;
		if(ntest<2) {
			ntrain = ndata - 2;   // prevent corrcoef problem by providing at least 2 test samples
			ntest = 2;
		}
		// seed the training with one PLS model, with 1 factor
		currentAP = new ArchitectureParameters(this.AP.nin,this.AP.nout,0,1);
		currentAP.trainingFraction = ((double) ntrain)/((double) ndata);
		currentModel = new Pls(currentAP);
		if(VERBOSE) {
			currentModel.describe();
		}
		Stats.randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);  // do a different split each time
		int failureCount = 1;
		while(failureCount<11) {
			Stats.randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);  // do a different split each time
			try{
				currentModel.train(XTrain,YTrain);
				currentModel.trainingResults = new ValidationParameters(currentModel,XTrain,YTrain);
				currentModel.testingResults = new ValidationParameters(currentModel,XTest,YTest);
//				informListeners(model, EnsembleModelEvent.MODEL_TRAINED);
				if(VERBOSE) {
					System.out.println("train="+Utilities.formatDouble(currentModel.trainingResults.chisq,3)+", test="+Utilities.formatDouble(currentModel.testingResults.chisq,3)+", test95="+Utilities.formatDouble(currentModel.testingResults.chisq95,3));
				}
				int addedAt = addModel(currentModel);
				if(VERBOSE) {
					System.out.println("addedAt="+addedAt);
				}
				if(addedAt != -1) {
					boolean b[] = Matlib.create1DBooleanArray(B);
					currentModel.testingSamples = b;   	// store the incidence array of testing samples
				}
				failureCount = 12;   // force exit if model was successfully trained
			} catch (MathException e) {
				if(failureCount>=10) {
					throw new MathException("Training terminated abnormally.  Could not train seed model.");
				}
				failureCount++;
				// if here, it is impossible to continue, since no seed model				
				if(VERBOSE){
					//e.printStackTrace();
					System.out.println("	EXCEPTION TRAINING SEED MODEL:"+e.getMessage());
				}
			}
		}
		// The main training loop...
		while(true) {
			if(numberOfModelsTrained>LINEAR_PHASE_TRIALS) {
				break;
			}
			baseModel = (TrainableModel) getModelObject(Stats.importanceSample((int) Math.min(capacity,size())));
			currentModel = mutate(baseModel);
			if(currentModel == null) {
				break;
			}
			ntrain = (int) Math.round(currentModel.AP.trainingFraction*ndata);
			ntest = ndata - ntrain;
			if(ntest<2) {
				ntrain = ndata - 2;  // prevent corrcoef problem
				ntest = 2;
			}
			// use random split for small data sets, but use block split for large data sets
			// this helps prevent overtraining due to serial correlation in training data
			if(ntest<20 || ndata<100) {
				Stats.randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);
			}
			else {// for best results, ntest > blockLength and blockLength << ndata
				blockLength = ntest/10;  // normally, split test data into 10 blocks
				if(blockLength*5>ntrain)  // make sure ndata >> blockLength
					blockLength = Math.min(ntrain,ntest)/5;
				Stats.blockSplit(X,Y,ntrain,blockLength,XTrain,YTrain,XTest,YTest,B);  // was randomSplit
			}
			int addedAt	= -1;
			try {
				if(VERBOSE) {
					currentModel.describe();
				}
				currentModel.train(XTrain,YTrain);
				currentModel.trainingResults = new ValidationParameters(currentModel,XTrain,YTrain);
				currentModel.testingResults = new ValidationParameters(currentModel,XTest,YTest);
//				informListeners(currentModel, EnsembleModelEvent.MODEL_TRAINED);
				addedAt = addModel(currentModel);
				if(addedAt != -1) {
					boolean b[] = Matlib.create1DBooleanArray(B);
					currentModel.testingSamples = b;
				}
				numberOfModelsTrained++;
				if(VERBOSE) {
					double baseRating = Math.max(baseModel.testingResults.chisq95, baseModel.trainingResults.chisq95);
					double newRating = Math.max(currentModel.testingResults.chisq95, currentModel.trainingResults.chisq95);
					if(newRating < baseRating) {
						System.out.println("	IMPROVED from "+Utilities.formatDouble(baseRating,3)+" to "+Utilities.formatDouble(newRating,3));
					}else {
						System.out.println("	degraded from "+Utilities.formatDouble(baseRating,3)+" to "+Utilities.formatDouble(newRating,3));
					}
				}
			} catch (MathException e) {
				// if here, try to continue on, print warning, otherwise go to next iteration
				if(VERBOSE) {
					System.out.println("	EXCEPTION DURING TRAINING:"+e.getMessage());
				}
			}
			Matrix.clearPool();
		}
		int n = size();
		if(n>0){
			model = (Pls) models.elementAt(0);
		}
//		informListeners(model, EnsembleModelEvent.TRAINING_COMPLETE);
		Matlib.clear(XTrain);
		Matlib.clear(YTrain);
		Matlib.clear(XTest);
		Matlib.clear(YTest);
		Matlib.clear(B);
	}

	public Pls getModelObject(int i) throws ArrayIndexOutOfBoundsException {
		return (Pls) models.elementAt(i);
	}

	@Override
	public Model getModel() {
		return (Pls) models.elementAt(0);
	}

	private Pls mutate(TrainableModel baseModel) {
		Pls newModel;
		ArchitectureParameters baseAP = baseModel.AP;
		int nhidden = baseAP.nhidden, nfactors = baseAP.nfactors, nout = baseAP.nout;
		double trainingFraction=baseAP.trainingFraction;
		// key statistic is ratio of testing to training error
		double testOverTrain = baseModel.testingResults.chisq/baseModel.trainingResults.chisq;

		int numberOfRepeatition = 0;
		while(true){

			if((testOverTrain>1.5 && Stats.coinFlip(0.667)) || Stats.coinFlip(0.2)) {  
				// test error somewhat greater than train error, favor reduction of model complexity
				// leave 20% chance of coming here regardless
				if(nfactors!=0) {
					if(nfactors==1) {
						nfactors += Stats.randInt(1,4);  // already as simple as possible, try increasing
					}else if(nfactors>4) {
						nfactors += Stats.randInt(-3,1);
					}else {
						nfactors += Stats.randInt(-2,1);
					}
				}
				if(nhidden!=0) {
					if (nhidden==1) {
						nhidden+=Stats.randInt(1,4); // already as simple as possible, try increasing
					}else {
						nhidden += Stats.randInt(-3,1);
					}
				}
				// increase data set size
				trainingFraction *= Stats.randDouble(1.0,3.0);
			} else {  // pretty good balance between test & train errors (or test is smaller), so try increasing complexity of model to get a better fit
				if(nfactors!=0) {
					nfactors += Stats.randInt(-1,3);
				}
				if(nhidden!=0) {
					if(nfactors>baseAP.nfactors) { // grew nfactors, even chance to grow or shrink nhidden
						nhidden += Stats.randInt(-3,3);
					} else { // nfactors shrunk or stayed same, favor growing nhidden
						nhidden += Stats.randInt(-1,3);
					}
				} 
				// 50-50 chance to expand or contract training set
				trainingFraction *= Stats.randDouble(0.5,2.0);
			}
			// final sanity checks
			nhidden = 0;
			if (nfactors>baseAP.nin-1) {
				nfactors = baseAP.nin;  // can't have more than nin factors
			}
			if (nfactors<1) {
				nfactors = 1; 
			}
			if (trainingFraction < 0.001) {
				trainingFraction = 0.001;
			}else if (trainingFraction > 0.8) {
				trainingFraction = 0.8;
			}
			if(!isSameStructureTrainedBefore(0,baseAP.nin, baseAP.nout, nhidden, nfactors,trainingFraction)){
				numberOfRepeatition++;
				if(numberOfRepeatition >10000){
					return null;
				}
				break;
			}

		}	
		// now build it
		ArchitectureParameters derivedAP = new ArchitectureParameters(baseAP.nin, baseAP.nout, nhidden, nfactors);
		derivedAP.trainingFraction = trainingFraction;
		
		newModel = new Pls(derivedAP);
		return newModel;
	}

	private boolean isSameStructureTrainedBefore(int modelType,int nin, int nout, 
		int nhidden, int nfactors, double trainingFraction){
		if(structureBuffer == null){
			structureBuffer = new Vector();
			return false;
		}
		int[] structParam = new int[7];
		structParam[0] = modelType; 
		structParam[1] = nin; 
		structParam[2] = nout; 
		structParam[3] = nhidden; 
		structParam[4] = nfactors; 
		structParam[5] = (int) Math.round(trainingFraction*100.0); 
		structParam[6] = 1;
		boolean foundSameStruct = false;
		for(int i=0;i<structureBuffer.size();i++){
			int[] oldParam = (int[])structureBuffer.elementAt(i);
			boolean condition = oldParam[0]==structParam[0] && oldParam[1]==structParam[1];
			if(condition
				&& oldParam[2]==structParam[2]
				&& oldParam[3]==structParam[3]
				&& oldParam[4]==structParam[4]
				){
				if(structParam[5]>(oldParam[5]-2) && structParam[5]<(oldParam[5]+3)){
					foundSameStruct = true;
					if(oldParam[6] == ONE_STRUCTURE_TRIALS){
//System.out.println("foundSameStruct and reject");
						return true;
					}else{
//System.out.println("foundSameStruct and try again");
						oldParam[6]++;
					}
				}
			}
		}
		if(!foundSameStruct){
			structureBuffer.addElement(structParam);
		}
		return false;
	}

	public int addModel(TrainableModel M) throws MathException {
		ValidationParameters testVP = M.testingResults;
		ValidationParameters trainVP = M.trainingResults;
		if(testVP == null) {
			throw new MathException("Attempted to add model, but testing results were missing");
		}
		if(trainVP == null) {
			throw new MathException("Attempted to add model, but training results were missing");
		}
		// use max to assure that a "lucky" test set is not selected
		double rating = Math.max(M.testingResults.chisq95,M.trainingResults.chisq95);
		return addModel(M,-rating);
	}

	/** Adds a model to the ensemble, inserting it in descending
	order according to rating.  This allows quick prediction from
	the top-N models.  Returns the index where the model was added  */
	public int addModel(Model M, double rating) throws MathException {
		ArchitectureParameters MAP = M.getArchitectureParameters();
		if(MAP.nin != AP.nin) {
			throw new MathException("Attempted to add model, but the number of inputs did not match");
		}
		if(MAP.nout != AP.nout) {
			throw new MathException("Attempted to add model, but the number of outputs did not match");		
		}
		for (int i=0; i<size(); i++) {
			double rat = ((Double) ratings.elementAt(i)).doubleValue();
			if (rating > rat) {
				if (VERBOSE) {
					System.out.println("Added at position "+i+" rating = "+rating);
				}
				models.insertElementAt(M,i);
				ratings.insertElementAt(rating,i);
				if(size()>capacity) {
					trimToSize();
				}
//				if(i<predictionSize) informListeners(M, EnsembleModelEvent.MODEL_ADDED);
				return i;
			}
		}
		if(size()>=capacity) {
			return -1;  // not added, return -1
		}
		// if here, insert at end
		if (VERBOSE) {
			System.out.println("Added at position "+size()+" rating = "+rating);
		}
		models.addElement(M);
		ratings.addElement(rating);
//		if(size()-1<predictionSize) informListeners(M, EnsembleModelEvent.MODEL_ADDED);
		return size()-1;
	}

	private void trimToSize() {
		int currentSize = size();
		while(currentSize>capacity) {
			currentSize--;
			Model M = (Model) models.elementAt(currentSize);
			models.removeElementAt(currentSize);
			ratings.removeElementAt(currentSize);
//			informListeners(M,EnsembleModelEvent.MODEL_REMOVED);   // this is unnecessary
		}
	}

	public int size(){
		return models.size();
	}


	@Override
	public String getDescription(){
		Pls m = (Pls)getModel();
		return m.getDescription();
	}

/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() throws MathException {
		Vector para = new Vector();
		para.addElement(1);
		para.addElement(1);
System.out.println("start getParametersVector");
		para.addAll(((Pls)getModel()).getPlsParametersVector());
System.out.println("ed getParametersVector");
		return para;
	}

/** Set the model information as in a Vector */
	@Override
	public void setParametersVector(Vector params) throws MathException {
	}

/** Return the parameter matrix P. Y = XP.*/
	public void getParameterMatrix(Matrix P)throws MathException {
		Pls m = (Pls)getModel();
		Matrix r = m.getR();
		Matrix b = m.getB();
		Matrix s = m.getS();
		Matlib.multiplyElements(r,b,P);
		Matlib.multiply(P,s,P);
		Matlib.clear(b);
		Matlib.clear(s);
	}


	public void writePLSWeightFile(String dir,String fileName) throws IOException, MathException {
		File SourceFile = null;
		if(dir == null)
			SourceFile = new File(fileName);
		else
			SourceFile = new File(dir,fileName);
		
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			Source.write("1; Version of this file save/restore protocol");
			Source.newLine();
			Source.write(1+"; Number of submodels");
			Source.newLine();		
			((Pls)getModel()).writeWeightsAsPLS(Source);
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}
	public int writeXMLFile(final BufferedWriter target, final int indentNumber) throws IOException, MathException {
		return ((Pls)getModel()).writeXMLFileAsPLS(target,indentNumber);
	}
	
	@Override
	public void calculateModelStatistics (){
		modelRateValue = 0.0;
		TrainingRmse = new Vector();
		TestingRmse = new Vector();
		TrainingCorrcoef = new Vector();
		TestingCorrcoef = new Vector();
		if(isTrained()){
			double r1 = getModelStatistics(TrainingRmse, TrainingCorrcoef,0);
			double r2 = getModelStatistics(TestingRmse, TestingCorrcoef,1);
			modelRateValue = (r1+r2)/2;
		}
	}
	
	private double getModelStatistics(Vector rmse, Vector corrcoef, int type) {
		int digits = 4;
		int nout = model.getNout();
		double[] rmseAve = new double[nout];
		double[] corrAve = new double[nout];
		double rateValue = 0;
		for(int j=0;j<nout;j++) {
			rmseAve[j] = 0.0;
			corrAve[j] = 0.0;
			ValidationParameters VP = null;
			if(type==1) {
				VP = ((Pls)model).testingResults;
			}else {
				VP = ((Pls)model).trainingResults;
			}
			rmseAve[j] += VP.rmse.get(j);
			corrAve[j] += VP.corrcoef.get(j);
		}
		for(int i=0;i<nout;i++) {
			rmse.addElement(Utilities.formatDouble(rmseAve[i], digits));
			corrcoef.addElement(Utilities.formatDouble(corrAve[i], digits));
			rateValue = rateValue+corrAve[i];
		}
		return rateValue/nout;
	}
	
}

