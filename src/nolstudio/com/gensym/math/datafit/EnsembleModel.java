package com.gensym.math.datafit;

import java.io.*;
import java.nio.charset.Charset;
import java.util.*;
import com.gensym.math.*;
import com.gensym.math.matrix.*;
import com.gensym.math.stats.Stats;
import com.gensym.DEBUG;

import com.gensym.util.*;

public class EnsembleModel extends TrainableModel implements Serializable {
	static final long serialVersionUID = 1L;
	private static boolean VERBOSE = false;
	private Vector models;
	private Vector ratings;
	private int predictionSize;
	private int capacity;
	private long trainingTime;
	private int trainingPhase;
	private int numberOfModelsTrained;
	private Pls bestLinearModel;
	private Vector errorHistory;
	private boolean useAutomaticStopping;

	static final int DEFAULT_PREDICTION_SIZE = 5;
	static final int DEFAULT_CAPACITY = 10;
	static final int LINEAR_TRAINING_PHASE = 1;
	static final int NONLINEAR_TRAINING_PHASE = 2;
	static final int LINEAR_PHASE_TRIALS = 20;
	static final int ONE_STRUCTURE_TRIALS = 2;
	static final int PLS = 0;
	static final int NLPLS = 1;
	static final int PlsBPN = 2;

	private transient Vector itsListeners;

 	private transient BufferedWriter target = null;
 	private transient boolean canWrite = false;
 	private transient Vector structureBuffer = null;
		// added in 2.2 for Neil
	private transient boolean singlePLSModel;

	public EnsembleModel(ArchitectureParameters AP) {
		super(AP);
		models = new Vector(0,10);
		ratings = new Vector(0,10);
		predictionSize = DEFAULT_PREDICTION_SIZE;
		capacity = DEFAULT_CAPACITY;
		itsListeners = new Vector(0,10);
		trainingTime = 1l;
		trainingPhase = LINEAR_TRAINING_PHASE;
		// added in 2.1
		numberOfModelsTrained = 0;
		bestLinearModel = null;
		errorHistory = new Vector(0,20);
		useAutomaticStopping = true;

		// added in 2.2 for Neil
		singlePLSModel = false;
		structureBuffer = new Vector(0,20);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		EnsembleModel cloned = (EnsembleModel) super.clone();
		cloned.bestLinearModel = bestLinearModel == null ? null : (Pls) bestLinearModel.clone();
		cloned.models = models == null ? null : (Vector) models.clone();
		cloned.ratings = ratings == null ? null : (Vector) ratings.clone();
		cloned.errorHistory = errorHistory == null ? null : (Vector) errorHistory.clone();
		cloned.itsListeners = itsListeners == null ? null : (Vector) itsListeners.clone();
		cloned.structureBuffer = structureBuffer == null ? null : (Vector) structureBuffer.clone();
		
		return cloned;
	}

	// if automatic stopping = false, then this will be the actual
	// training time.  Otherwise, it is the maximum training time.
	public void useAutomaticStopping(boolean useIt) {
		useAutomaticStopping = useIt;
	}

	public boolean isUseAutomaticStopping(){
		return useAutomaticStopping;
	}
/** Clear the submodels.*/
	//added in 42r0
	public void clearModels(){
		models.removeAllElements();
		ratings.removeAllElements();
		if(structureBuffer == null){
			structureBuffer = new Vector();
		}else{
			structureBuffer.removeAllElements();
		}
		errorHistory.removeAllElements();
		numberOfModelsTrained = 0;
		bestLinearModel = null;
		singlePLSModel = false;
	}


	// This flag is set for Neil, in 2.2r0.
	public void setSinglePLSModel(boolean mode) {
		singlePLSModel = mode;
		if(singlePLSModel)
			setPredictionSize(1);
	}

	public boolean isSinglePLSModel(){
		return singlePLSModel;
	}

	public long getTrainingTime() {
		return trainingTime;
	}

	// if automatic stopping = false, then this will be the actual
	// training time.  Otherwise, it is the maximum training time.
	public void setTrainingTime(long millisec) {
		trainingTime = millisec;
	}

	public void addListener(EnsembleModelListener l) {
		if(itsListeners == null){
			itsListeners = new Vector(0,10);
		}
		itsListeners.addElement(l);
	}

	public void removeListener(EnsembleModelListener l) {
		if(itsListeners == null){
			itsListeners = new Vector(0,10);
		}
		itsListeners.removeElement(l);
	}

	public void removeAllListeners() {
		if(itsListeners == null){
			itsListeners = new Vector(0,10);
		}else{
			itsListeners.removeAllElements();
		}
	}

	/** Determines the number of models used in a prediction.
	The top n models are used (those with highest ratings.
	If n = 0, it is a flag that all models are to be used */
	public void setPredictionSize(int n) {
		predictionSize = n;
	}

	public int getPredictionSize() {
		return predictionSize;
	}

	public int getModelSize() {
		int nmodels;
		if(predictionSize<=0 || predictionSize>size()){
			nmodels = size();
		}else{
			nmodels = predictionSize;
		}
		return nmodels;
	}

	public void setCapacity(int n) {
		capacity = n;
		if(size()>capacity){
			trimToSize();
		}
	}

	public int addModel(TrainableModel M) throws MathException {
		ValidationParameters testVP = M.testingResults;
		ValidationParameters trainVP = M.trainingResults;
		if(testVP == null){
			throw new MathException("Attempted to add model, but testing results were missing");
		}
		if(trainVP == null){
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
		if(MAP.nin != AP.nin){
			throw new MathException("Attempted to add model, but the number of inputs did not match");
		}
		if(MAP.nout != AP.nout){
			throw new MathException("Attempted to add model, but the number of outputs did not match");		
		}
		int modelType = getModelType(M);
		boolean bestLinear = (modelType==PLS? true: false);
		for (int i=0; i<size(); i++) {
			double rat = ((Double) ratings.elementAt(i)).doubleValue();
			if (rating > rat) {
				if (VERBOSE){
					System.out.println("Added at position "+i+" rating = "+rating);
				}
				models.insertElementAt(M,i);
				ratings.insertElementAt(rating,i);
				if(size()>capacity){
					trimToSize();
				}
				if(i<predictionSize){
					informListeners(M, EnsembleModelEvent.MODEL_ADDED);
				}
				if(bestLinear){
					bestLinearModel = (Pls) M;
				}
				return i;
			}
			// if we passed a linear model, then this one isn't the best
			if(getModelType((Model) models.elementAt(i))==PLS){
				bestLinear = false;
			}
		}
		if(size()>=capacity){
			return -1;  // not added, return -1
		}
		// if here, insert at end
		if (VERBOSE){
			System.out.println("Added at position "+size()+" rating = "+rating);
		}
		models.addElement(M);
		ratings.addElement(rating);
		if(size()-1<predictionSize){
			informListeners(M, EnsembleModelEvent.MODEL_ADDED);
		}
		return size()-1;
	}

	// new in 2.1, used in console
	public double getMeanPredictionError() {
		double mpe = 0.0;
		int currentSize = Math.min(predictionSize, models.size());
		if(currentSize==0){
			return 0.0;  //  ?? or signal an error
		}
		for (int ps = 0; ps < currentSize; ps++) {			
			TrainableModel submodel = (TrainableModel) getModel(ps);
			mpe += Math.max(submodel.testingResults.chisq, submodel.trainingResults.chisq);
		}
		return (mpe/currentSize);
	}

	private void informListeners(Model M, int type) {
		EnsembleModelEvent e;
		EnsembleModelListener l;
		e = new EnsembleModelEvent(this, M, type);
		if(itsListeners == null){
			itsListeners = new Vector(0,10);
			return;
		}

//System.out.println("informListeners type=" +  type);

		for (int i=0; i<itsListeners.size(); ++i) {
			l = (EnsembleModelListener) itsListeners.elementAt(i);
			if(type==EnsembleModelEvent.MODEL_ADDED){
				l.modelAdded(e);
			}
			else if(type==EnsembleModelEvent.MODEL_REMOVED){
				l.modelRemoved(e);
			}
			else if(type==EnsembleModelEvent.TRAINING_COMPLETE){
				l.trainingComplete(e);
			}
			else if(type==EnsembleModelEvent.MODEL_TRAINED){
				l.modelTrained(e);
			}
		}
	}

	public void removeModel(Model M) {
		int i = models.indexOf(M);
		models.removeElement(M);
		ratings.removeElementAt(i);
		informListeners(M,EnsembleModelEvent.MODEL_REMOVED);
	}

	public void removeModel(int i) throws ArrayIndexOutOfBoundsException {
		Model M = (Model) models.elementAt(i);
		models.removeElementAt(i);
		ratings.removeElementAt(i);
		informListeners(M,EnsembleModelEvent.MODEL_REMOVED);
	}

	private void trimToSize() {
		int currentSize = size();
		while(currentSize>capacity) {
			currentSize--;
			Model M = (Model) models.elementAt(currentSize);
			models.removeElementAt(currentSize);
			ratings.removeElementAt(currentSize);
			informListeners(M,EnsembleModelEvent.MODEL_REMOVED);   // this is unnecessary
		}
	}

	public Model getModel(int i) throws ArrayIndexOutOfBoundsException {
		return (Model) models.elementAt(i);
	}

	public double getRating(int i) throws ArrayIndexOutOfBoundsException {
		return ((Double) ratings.elementAt(i)).doubleValue();
	}

	public int size() {
		return models.size();
	}

	/** Calculates values of Y, given X using median of top n models, 
	where n is given by the current predictionSize. */
	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		if (size()==0){
			throw new MathException("Ensemble contains no models, could not evaluate");
		}
		if(predictionSize == 1){
			Model model = (Model) models.elementAt(0);
			model.evaluate(X,Y);
			return;
		}
		
		// create array of matrices to hold predictions for each output, rows correspond to data, columns to models
		Matrix[] M = new Matrix[AP.nout];  
		for (int i=0;i<AP.nout;i++){
			M[i] = Matlib.createMatrix();
		}
		evaluateSubmodels(X,M);
		findMedian(M,Y);
		for (int j=0;j<AP.nout;j++){
			Matlib.clear(M[j]);
		}
	}

	public void evaluateSubmodels(Matrix X, Matrix[] M) throws MathException {
		int nmodels;
		if(predictionSize<=0 || predictionSize>size()){
			nmodels = size();
		}
		else{
			nmodels = predictionSize;
		}
		Matrix YY = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		for (int i=0;i<nmodels;i++) {
			Model model = (Model) models.elementAt(i);
			model.evaluate(X,YY);
			if(AP.nout==1) // special case, save one call to getColumns
				Matlib.appendColumns(M[0],YY,M[0]);
			else {
				for(int j=0;j<AP.nout;j++) {
					Matlib.getColumns(YY,j,j,temp);
					Matlib.appendColumns(M[j],temp,M[j]);
				}
			}
		}
		Matlib.clear(temp);
		Matlib.clear(YY);
	}

	public static void findMedian(Matrix[] M, Matrix Y) throws MathException {
		Matrix temp = Matlib.createMatrix();
		Y.redimension(0,0); // empty Y to make room for predictions
		for(int j=0;j<M.length;j++) {
			Matlib.transpose(M[j],temp);
			Matlib.median(temp,temp);  // median ignores NaN elements
			Matlib.transpose(temp,temp);
			Matlib.appendColumns(Y,temp,Y);
		}
		Matlib.clear(temp);
	}

	@Override
	public void learn(Matrix X, Matrix Y) throws MathException {

		
		// added in 2.2 for Neil
		if(singlePLSModel){
			if(errorHistory==null) {  // continue training a pre-2.1 model, upgrade now...
				errorHistory = new Vector(0,20);
				numberOfModelsTrained = 0;
				useAutomaticStopping = false;
				bestLinearModel = null;
				trainingPhase = LINEAR_TRAINING_PHASE;
			}
			TrainableModel model,baseModel;
			ArchitectureParameters AP;
			double trainError, testError;
			ValidationParameters trainVP, testVP;
			int ndata=X.getRows(),ntrain,ntest,blockLength;
			if(ndata<10){
				throw new MathException("Cannot train with less than 10 valid data points");
			}
			long elapsedTime = 0L, allowedTime = trainingTime, startTime = System.currentTimeMillis();
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
			if(ntrain<2) {
				ntest = ndata - 2;   // prevent corrcoef problem by providing at least 2 test samples
				ntrain = 2;
			}
			// seed the training with one PLS model, with 1 factor
			AP = new ArchitectureParameters(this.AP.nin,this.AP.nout,0,1);
			AP.trainingFraction = ((double) ntrain)/((double) ndata);
			model = (TrainableModel) new Pls(AP);
			if(VERBOSE){
				model.describe();
			}
			int failureCount = 1;
			if(size()>0){
				failureCount = 12;  // just to skip the following loop
			}
			while(!Thread.currentThread().isInterrupted() && failureCount<11) {
				Stats.randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);  // do a different split each time
				try{
					model.train(XTrain,YTrain);
					model.trainingResults = new ValidationParameters(model,XTrain,YTrain);
					model.testingResults = new ValidationParameters(model,XTest,YTest);
					informListeners(model, EnsembleModelEvent.MODEL_TRAINED);
					if(VERBOSE){
						System.out.println("train="+Utilities.formatDouble(model.trainingResults.chisq,3)+", test="+Utilities.formatDouble(model.testingResults.chisq,3)+", test95="+Utilities.formatDouble(model.testingResults.chisq95,3));
					}
					int addedAt = addModel(model);
////					if(addedAt != -1 && addedAt < predictionSize) {
					if(addedAt != -1) {
						boolean b[] = Matlib.create1DBooleanArray(B);
						model.testingSamples = b;   	// store the incidence array of testing samples
					}
					failureCount = 12;   // force exit if model was successfully trained
				} catch (Exception e) {	   //Change the exception type to the general exception to take care of the matrix failure.	gchen 2/12/07
					if(failureCount>=10){
						throw new MathException("Training terminated abnormally.  Could not train seed model.");
					}
					failureCount++;
					// if here, it is impossible to continue, since no seed model				
if(DEBUG.debugOutput){
	System.out.println("	EXCEPTION TRAINING SEED MODEL:"+e.toString());
}
				}
			}
			elapsedTime = System.currentTimeMillis() - startTime;

/*			if(target == null){
				try { 
					File targetFile = new File("training.log");
					if(!targetFile.canWrite()){
						canWrite = false;
						if(targetFile.delete()) canWrite =true;
						targetFile = new File("training.log");
					}else{
						canWrite = true;
					}
					if(canWrite){
						target = new BufferedWriter(new FileWriter(targetFile));
						String titleStr = "#\tType\tFactor#\tHidden#\ttrain#\ttest#\ttrainTime\tensembleRank\tTrainingError\tTestingError\tTesting95Error\tMPE";
		//System.out.println(titleStr);
						target.write(titleStr,0,titleStr.length());
						target.newLine();
					}
				}catch(IOException e){
					System.err.println("Non-Fatal exception: " + e.getMessage());
					e.printStackTrace();		
				}
			}		
*/
			// The main training loop...
			while(!Thread.currentThread().isInterrupted()) {
				if(trainingPhase == LINEAR_TRAINING_PHASE && numberOfModelsTrained>LINEAR_PHASE_TRIALS) {
//					bestLinearModel = (Pls) models.elementAt(0);
//					int n = size();
//					for(int i=1;i<n;i++) removeModel(1);  // only keep top models
					break;
				}
				baseModel = (TrainableModel) getModel(Stats.importanceSample((int) Math.min(capacity,size())));
				model = mutate(baseModel);
				if(model == null){
					break;
				}
				ntrain = (int) Math.round(model.AP.trainingFraction*ndata);
				ntest = ndata - ntrain;
				if(ntest<2) {
					ntrain = ndata - 2;  // prevent corrcoef problem
					ntest = 2;
				}
				if(ntrain<2) {
					ntest = ndata - 2;   // prevent corrcoef problem by providing at least 2 test samples
					ntrain = 2;
				}
				// use random split for small data sets, but use block split for large data sets
				// this helps prevent overtraining due to serial correlation in training data
				if(ntest<20 || ndata<100){
					Stats.randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);
				}
				else {// for best results, ntest > blockLength and blockLength << ndata
					blockLength = ntest/10;  // normally, split test data into 10 blocks
					if(blockLength*5>ntrain)  // make sure ndata >> blockLength
						blockLength = Math.min(ntrain,ntest)/5;
					Stats.blockSplit(X,Y,ntrain,blockLength,XTrain,YTrain,XTest,YTest,B);  // was randomSplit
				}
				double mpe = 0.0;
				int addedAt	= -1;
				boolean validTraining = true;
				try {
					model.train(XTrain,YTrain);
					validTraining = true;
				}catch (Exception e){	   //try to catch every error during the training to make it robust.
if(DEBUG.debugOutput) {
	System.out.println("	EXCEPTION TRAINING MAIN MODEL:"+e.toString());
}
					validTraining = false;
				}
				if (validTraining){
					try {
						if(VERBOSE) {
							model.describe();
						}
						model.trainingResults = new ValidationParameters(model,XTrain,YTrain);
						model.testingResults = new ValidationParameters(model,XTest,YTest);
						informListeners(model, EnsembleModelEvent.MODEL_TRAINED);
						addedAt = addModel(model);
	//					if(addedAt != -1 && addedAt < predictionSize) {
						if(addedAt != -1) {
							boolean b[] = Matlib.create1DBooleanArray(B);
							model.testingSamples = b;
						}
						numberOfModelsTrained++;
						mpe = getMeanPredictionError(); 
						errorHistory.addElement(mpe);
						if(VERBOSE) {
							double baseRating = Math.max(baseModel.testingResults.chisq95, baseModel.trainingResults.chisq95);
							double newRating = Math.max(model.testingResults.chisq95, model.trainingResults.chisq95);
							if(newRating < baseRating){
								System.out.println("	IMPROVED from "+Utilities.formatDouble(baseRating,3)+" to "+Utilities.formatDouble(newRating,3));
							}
							else{
								System.out.println("	degraded from "+Utilities.formatDouble(baseRating,3)+" to "+Utilities.formatDouble(newRating,3));
							}
						}
					} catch (Exception e) {
						// if here, try to continue on, print warning, otherwise go to next iteration
if(DEBUG.debugOutput){
	System.out.println("	EXCEPTION TRAINING MAIN MODEL:"+e.toString());
}
					}
				}
				Matrix.clearPool();
				elapsedTime = System.currentTimeMillis() - startTime;
/*				String s = outputModelStatistics(model,numberOfModelsTrained,
					XTrain.getRows(),XTest.getRows(),addedAt,elapsedTime,mpe);
	//System.out.println(s);
				if(canWrite){
					try {					
						target.newLine();
						target.write(s,0,s.length());
						target.flush();
					}catch (IOException e){
		//				System.err.println("Non-Fatal exception: " + e.getMessage());
		//				e.printStackTrace();
					}
				}
*/
				if(elapsedTime>=allowedTime){
					break;
				}
				if(useAutomaticStopping && hasConverged()){
					break;
				}
			}
/*			if(canWrite){
				try {					
					target.flush();
					target.close();
				}catch (IOException e){
		//			System.err.println("Non-Fatal exception: " + e.getMessage());
		//			e.printStackTrace();
				}
			}
*/
			int n = size();
			if(n>0){
				bestLinearModel = (Pls) models.elementAt(0);
//				for(int i=predictionSize;i<n;i++) removeModel(predictionSize);  // only keep top models
				for(int i=predictionSize;i<size();i++) {
					removeModel(i);  // only keep top models
				}
			}
			target = null;
			informListeners(model, EnsembleModelEvent.TRAINING_COMPLETE);
			Matlib.clear(XTrain);
			Matlib.clear(YTrain);
			Matlib.clear(XTest);
			Matlib.clear(YTest);
			Matlib.clear(B);
			return;
		}

		if(errorHistory==null) {  // continue training a pre-2.1 model, upgrade now...
			errorHistory = new Vector(0,20);
			numberOfModelsTrained = 0;
			useAutomaticStopping = false;
			bestLinearModel = null;
			trainingPhase = NONLINEAR_TRAINING_PHASE;
		}
		TrainableModel model,baseModel;
		ArchitectureParameters AP;
		double trainError, testError;
		ValidationParameters trainVP, testVP;
		int ndata=X.getRows(),ntrain,ntest,blockLength;
		if(ndata<10){
			throw new MathException("Cannot train with less than 10 valid data points");
		}
		long elapsedTime = 0L, allowedTime = trainingTime, startTime = System.currentTimeMillis();
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
		if(ntrain<2) {
			ntest = ndata - 2;   // prevent corrcoef problem by providing at least 2 test samples
			ntrain = 2;
		}
		// seed the training with one PLS model, with 1 factor
		AP = new ArchitectureParameters(this.AP.nin,this.AP.nout,0,1);
		AP.trainingFraction = ((double) ntrain)/((double) ndata);
		model = (TrainableModel) new Pls(AP);
		if(VERBOSE){
			model.describe();
		}
		int failureCount = 1;
		if(size()>0){
			failureCount = 12;  // just to skip the following loop
		}
		while(!Thread.currentThread().isInterrupted() && failureCount<11) {
			Stats.randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);  // do a different split each time
			try{
				model.train(XTrain,YTrain);
				model.trainingResults = new ValidationParameters(model,XTrain,YTrain);
				model.testingResults = new ValidationParameters(model,XTest,YTest);
				informListeners(model, EnsembleModelEvent.MODEL_TRAINED);
				if(VERBOSE){
					System.out.println("train="+Utilities.formatDouble(model.trainingResults.chisq,3)+", test="+Utilities.formatDouble(model.testingResults.chisq,3)+", test95="+Utilities.formatDouble(model.testingResults.chisq95,3));
				}
				int addedAt = addModel(model);
				if(addedAt != -1) {
//				if(addedAt != -1 && addedAt < predictionSize) {
					boolean b[] = Matlib.create1DBooleanArray(B);
					model.testingSamples = b;   	// store the incidence array of testing samples
				}
				failureCount = 12;   // force exit if model was successfully trained
			} catch (Exception e) {	 //Change the exception type to the general exception to take care of the matrix failure. gchen 2/12/07
				if(failureCount>=10){
					throw new MathException("Training terminated abnormally.  Could not train seed model.");
				}
				failureCount++;
				// if here, it is impossible to continue, since no seed model				
if(DEBUG.debugOutput){
	System.out.println("	EXCEPTION TRAINING GENERAL SEED MODEL failureCount=:"+failureCount);
}
if(DEBUG.debugOutput){
	System.out.println("	EXCEPTION TRAINING GENERAL SEED MODEL:"+e.toString());
}
			}
		}
		elapsedTime = System.currentTimeMillis() - startTime;

/*		if(target == null){
			try { 
				File targetFile = new File("training.log");
				if(!targetFile.canWrite()){
					canWrite = false;
					if(targetFile.delete()) canWrite =true;
					targetFile = new File("training.log");
				}else{
					canWrite = true;
				}
				if(canWrite){
					target = new BufferedWriter(new FileWriter(targetFile));
					String titleStr = "#\tType\tFactor#\tHidden#\ttrain#\ttest#\ttrainTime\tensembleRank\tTrainingError\tTestingError\tTesting95Error\tMPE";
//System.out.println(titleStr);
					target.write(titleStr,0,titleStr.length());
					target.newLine();
				}
			}catch(IOException e){
//				System.err.println("Non-Fatal exception: " + e.getMessage());
//				e.printStackTrace();		
			}
		}		
*/
//System.out.println("The main training loop.");
		// The main training loop...
		while(!Thread.currentThread().isInterrupted()) {
			if(trainingPhase == LINEAR_TRAINING_PHASE && numberOfModelsTrained>LINEAR_PHASE_TRIALS) {
				if(VERBOSE){
					System.out.println("*** DONE WITH LINEAR PHASE, STARTING NONLINEAR TRAINING ***");
				}
				trainingPhase = NONLINEAR_TRAINING_PHASE;
				// save best Pls model for extrapolation
				bestLinearModel = (Pls) models.elementAt(0);
				for(int i=predictionSize;i<size();i++){
					removeModel(predictionSize);  // only keep top models
				}
			}
			baseModel = (TrainableModel) getModel(Stats.importanceSample((int) Math.min(capacity,size())));
			model = mutate(baseModel);
			if(model == null){
				break;
			}
			ntrain = (int) Math.round(model.AP.trainingFraction*ndata);
			ntest = ndata - ntrain;
			if(ntest<2) {
				ntrain = ndata - 2;  // prevent corrcoef problem
				ntest = 2;
			}
			if(ntrain<2) {
				ntest = ndata - 2;   // prevent corrcoef problem by providing at least 2 test samples
				ntrain = 2;
			}
			double mpe = 0.0;
			int addedAt	= -1;
			boolean validTraining = true;

			// use random split for small data sets, but use block split for large data sets
			// this helps prevent overtraining due to serial correlation in training data
			try {
				if(ntest<20 || ndata<100){
					Stats.randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);
				}
				else {// for best results, ntest > blockLength and blockLength << ndata
					blockLength = ntest/10;  // normally, split test data into 10 blocks
					if(blockLength*5>ntrain)  // make sure ndata >> blockLength
						blockLength = Math.min(ntrain,ntest)/5;
					Stats.blockSplit(X,Y,ntrain,blockLength,XTrain,YTrain,XTest,YTest,B);  // was randomSplit
				}
				model.train(XTrain,YTrain);
				validTraining = true;
			}catch (Exception e){	   //try to catch every error during the training to make it robust.
if(DEBUG.debugOutput){
	System.out.println("	EXCEPTION TRAINING GENERAL MAIN MODEL:"+e.toString());
}
				validTraining = false;
//Try to recreate the matrix enviroment
				Matlib.clear(XTrain);
				Matlib.clear(YTrain);
				Matlib.clear(XTest);
				Matlib.clear(YTest);
				Matlib.clear(B);
				XTrain = Matlib.createMatrix();
				YTrain = Matlib.createMatrix();
				XTest = Matlib.createMatrix();
				YTest = Matlib.createMatrix();
				B = Matlib.createMatrix(); // train-test split
			}
			if (validTraining){
			try {
					if(VERBOSE){
						model.describe();
					}

	/*System.out.println("The main training loop. ntrain="+ntrain + "    ntest=" + ntest);
	Matlib.disp(XTrain, "XTrain=");
	Matlib.disp(YTrain, "YTrain=");
	*/
					model.trainingResults = new ValidationParameters(model,XTrain,YTrain);
					model.testingResults = new ValidationParameters(model,XTest,YTest);
					informListeners(model, EnsembleModelEvent.MODEL_TRAINED);
					addedAt = addModel(model);
	//// 				if(addedAt != -1 && addedAt < predictionSize) {
 					if(addedAt != -1) {
						boolean b[] = Matlib.create1DBooleanArray(B);
						model.testingSamples = b;   	// store the incidence array of testing samples
					}
					numberOfModelsTrained++;
					mpe = getMeanPredictionError(); 
					errorHistory.addElement(mpe);
					if(VERBOSE) {
						double baseRating = Math.max(baseModel.testingResults.chisq95, baseModel.trainingResults.chisq95);
						double newRating = Math.max(model.testingResults.chisq95, model.trainingResults.chisq95);
						if(newRating < baseRating){
							System.out.println("	IMPROVED from "+Utilities.formatDouble(baseRating,3)+" to "+Utilities.formatDouble(newRating,3));
						}
						else{
							System.out.println("	degraded from "+Utilities.formatDouble(baseRating,3)+" to "+Utilities.formatDouble(newRating,3));
						}
					}
				} catch (Exception e) {
					// if here, try to continue on, print warning, otherwise go to next iteration
if(DEBUG.debugOutput){
	System.out.println("	EXCEPTION TRAINING GENERAL MAIN MODEL AFTER PROCESSING:"+e.toString());
}
//Try to recreate the matrix enviroment for later iteration.
					Matlib.clear(XTrain);
					Matlib.clear(YTrain);
					Matlib.clear(XTest);
					Matlib.clear(YTest);
					Matlib.clear(B);
					XTrain = Matlib.createMatrix();
					YTrain = Matlib.createMatrix();
					XTest = Matlib.createMatrix();
					YTest = Matlib.createMatrix();
					B = Matlib.createMatrix(); // train-test split
				}
			}
			Matrix.clearPool();
			elapsedTime = System.currentTimeMillis() - startTime;

/*			String s = outputModelStatistics(model,numberOfModelsTrained,
				XTrain.getRows(),XTest.getRows(),addedAt,elapsedTime,mpe);
			if(canWrite){
				try {					
					target.newLine();
					target.write(s,0,s.length());
					target.flush();
				}catch (IOException e){
	//				System.err.println("Non-Fatal exception: " + e.getMessage());
	//				e.printStackTrace();
				}
			}	 */


			if(elapsedTime>=allowedTime){
				break;
			}
			if(trainingPhase!= LINEAR_TRAINING_PHASE && useAutomaticStopping && hasConverged()){
				break;
			}
		}
//System.out.println("The main training loop finished");
/*		if(canWrite){
			try {					
				target.flush();
				target.close();
			}catch (IOException e){
	//			System.err.println("Non-Fatal exception: " + e.getMessage());
	//			e.printStackTrace();
			}
		}
		*/
		target = null;
		informListeners(model, EnsembleModelEvent.TRAINING_COMPLETE);
		Matlib.clear(XTrain);
		Matlib.clear(YTrain);
		Matlib.clear(XTest);
		Matlib.clear(YTest);
		Matlib.clear(B);
	}

	private TrainableModel mutate(TrainableModel baseModel) {
		TrainableModel newModel;
		ArchitectureParameters baseAP = baseModel.AP;
		int nhidden = baseAP.nhidden, nfactors = baseAP.nfactors, nout = baseAP.nout;
		double trainingFraction=baseAP.trainingFraction;
		int modelType = getModelType(baseModel);
		// key statistic is ratio of testing to training error
		double testOverTrain = baseModel.testingResults.chisq/baseModel.trainingResults.chisq;

		int numberOfRepeatition = 0;
		while(true){
			// PlsBPN counts nhidden per output, convert to total hidden nodes, and convert back later
			if(modelType==PlsBPN){
				nhidden *= nout;
			}
			// force non-pls models during nonlinear training with 50% probability	
			if(trainingPhase==NONLINEAR_TRAINING_PHASE && modelType==PLS && Stats.coinFlip()) {
				if(Stats.coinFlip()) {
					modelType = NLPLS;
					nhidden = Stats.randInt(1,3)*nfactors;  // anywhere from 1 to 3 hidden per inner relation
				} else {
					modelType = PlsBPN;
					nhidden = Stats.randInt(1,3)*nout;  // anywhere from 1 to 3 hidden per output
				}
			}
			if((testOverTrain>1.5 && Stats.coinFlip(0.667)) || Stats.coinFlip(0.2)) {  
				// test error somewhat greater than train error, favor reduction of model complexity
				// leave 20% chance of coming here regardless
				if(modelType!=PLS && Stats.coinFlip(0.333)) {  // 33% chance to reduce model complexity through change in type
					if(modelType==PlsBPN) {
						modelType=NLPLS;
						if(Stats.coinFlip()){
							nhidden= Stats.randInt(1,3)*nfactors; // 50/50 chance, reinitialize, between to 3 hidden per inner relation
						}
					} else {
						modelType=PLS;
						nhidden=0;
					}
				} else { // reduce complexity by tuning factors & hidden
					if(nfactors!=0) {
						if(nfactors==1){
							nfactors += Stats.randInt(1,4);  // already as simple as possible, try increasing
						}
						else if(nfactors>4){
							nfactors += Stats.randInt(-3,1);
						}
						else{
							nfactors += Stats.randInt(-2,1);
						}
					}
					if(nhidden!=0) {
						if (nhidden==1) {
							nhidden+=Stats.randInt(1,4); // already as simple as possible, try increasing
						}
						else{
							nhidden += Stats.randInt(-3,1);
						}
					}
				}
				// increase data set size
				trainingFraction *= Stats.randDouble(1.0,3.0);
			} else {  // pretty good balance between test & train errors (or test is smaller), so try increasing complexity of model to get a better fit
				// if not already PlsBPN, 1/3 chance to increase complexity by changing model type 
				if(modelType!=PlsBPN && Stats.coinFlip(0.333)) {
					if(modelType==PLS) {  // PLS to NLPLS
						if(trainingPhase!=LINEAR_TRAINING_PHASE) {  // during linear phase, don't change to nonlinear models
							modelType=NLPLS;  
							nhidden= Stats.randInt(1,3)*nfactors; // anywhere from 1 to 3 hidden per inner relation
						} else { // during linear phase, increase complexity by adding factors
							nfactors += Stats.randInt(0,3);
						}
					} else {  // change NLPLS to PlsBPN
						modelType=PlsBPN;
						if(Stats.coinFlip()){
							nhidden=nout*Stats.randInt(nfactors/2, nfactors*2); // 50/50 chance, reinitialize nhidden with reasonable fan-in or fan-out from factor layer
						}
					}
				} else {  // stick with model type, increase hidden and/or factors
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
				}
				// 50-50 chance to expand or contract training set
				trainingFraction *= Stats.randDouble(0.5,2.0);
			}
			// if model is PlsBPN, scale hidden onto per-output basis
			if(modelType==PlsBPN) {
				nhidden = (int) Math.round((double)nhidden/(double)nout);
			}
			// final sanity checks
			if(modelType==PLS){
				nhidden = 0;
			}
			else { // NLPLS or PlsBPN
				if (nhidden<1){
					nhidden = 1;
				}
			}
			if (nfactors>baseAP.nin-1){
				nfactors = baseAP.nin;  // can't have more than nin factors
			}
			if (nfactors<1){
				nfactors = 1; 
			}
			if (trainingFraction < 0.001){
				trainingFraction = 0.001;
			}
			else if (trainingFraction > 0.8){
				trainingFraction = 0.8;
			}
			if(!isSameStructureTrainedBefore(modelType,baseAP.nin, baseAP.nout, nhidden, nfactors,trainingFraction)){
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
		
		if(modelType==PLS){
			newModel = (TrainableModel) new Pls(derivedAP);
		}
		else if(modelType==NLPLS){
			newModel = (TrainableModel)new Nlpls(derivedAP);
		}
		else{
			newModel = (TrainableModel) new PlsBpn(derivedAP);
		}
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
	@Override
	public String getDescription() {
		String newLine = System.getProperty("line.separator");
		String description = "Ensemble model with constituents:"+newLine;
		int nmodels;
		if(predictionSize<=0 || predictionSize>size()){
			nmodels = size();
		}
		else nmodels = predictionSize;
		for (int i=0;i<nmodels;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
			description += model.getDescription();
			description += newLine;
		}
		return description;
	}

	@Override
	public void writeWeights(BufferedWriter Source) throws IOException, MathException {
		Source.write("1; Version of this file save/restore protocol");
		Source.newLine();
		int nmodels,newnmodels;
		if(predictionSize<=0 || predictionSize>size()){
			nmodels = size();
		}
		else nmodels = predictionSize;
		if(nmodels > 5){
			nmodels = 5;
		}
		newnmodels = 5;
		Source.write(newnmodels+"; Number of submodels");
		Source.newLine();
		for (int i=0;i<nmodels;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
			model.writeWeights(Source);
		}
		if(nmodels < 5 || !models.isEmpty()){
			TrainableModel model = (TrainableModel) models.elementAt(0);
			for (int i=nmodels;i<newnmodels;i++) {
				model.writeWeights(Source);
			}
		}
	}

	// stopping criteria
	private boolean hasConverged() {
		// at least 20 iterations beyond linear phase
		if(numberOfModelsTrained - LINEAR_PHASE_TRIALS < 20){
			return false;
		}
		// less than 2% progress in mean predictive error over last 10 models
		int n = errorHistory.size();
		Double currentError = (Double) errorHistory.elementAt(n-1);
		Double pastError = (Double) errorHistory.elementAt(n-11);
		if((pastError.doubleValue() - currentError.doubleValue())/pastError.doubleValue() > 0.01){
			return false;
		}
		if(VERBOSE){
			System.out.println("ERROR CONVERGENCE TEST PASSED");
		}
		// architecture convergence
		int[] modelTypes = new int[predictionSize];
		int havePLS = 0;
		int haveNLPLS = 0;
		int havePlsBPN = 0;
		double minRating = Double.POSITIVE_INFINITY;
		double maxRating = Double.NEGATIVE_INFINITY;
		for(int i=0;i<predictionSize;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
			int modelType = getModelType(model);
			if(modelType==PLS){
				havePLS = 1;
			}
			else if(modelType==NLPLS){
				haveNLPLS = 1;
			}
			else if(modelType==PlsBPN){
				havePlsBPN = 1;
			}
			modelTypes[i] = modelType;
			double rating = Math.abs(((Double) ratings.elementAt(i)).doubleValue());
			if(rating<minRating){
				minRating = rating;
			}
			if(rating>maxRating){
				maxRating = rating;
			}
		}
		// at most two different model types
		if(havePLS + haveNLPLS + havePlsBPN == 3){
			return false;
		}
		if(VERBOSE){
			System.out.println("MODEL TYPE TEST PASSED");
		}
		// top and bottom rating within 10% of each other
		double ratingSpread = (maxRating - minRating)/maxRating;
		if(VERBOSE){
			System.out.println("Rating spread = "+ratingSpread);
		}
		if(ratingSpread > 0.10){
			return false;
		}
		if(VERBOSE){
			System.out.println("ENSEMBLE ERROR SPREAD TEST PASSED");
		}
		for(int type=0;type<3;type++) {
			int minFactors = 9999;
			int maxFactors = 0;
			int minHidden = 9999;
			int maxHidden = 0;
			for(int i=0;i<predictionSize;i++) {
				if(modelTypes[i] == type) {
					TrainableModel model = (TrainableModel) models.elementAt(i);
					ArchitectureParameters AP = model.AP;
					int nhidden = AP.nhidden;
					if(type==PlsBPN){
						nhidden *= model.getNout(); //because PlsBPN records hidden on per-output basis
					}
					int nfactors = AP.nfactors;
					if(nhidden<minHidden){
						minHidden = nhidden;
					}
					if(nhidden>maxHidden){
						maxHidden = nhidden;
					}
					if(nfactors<minFactors){
						minFactors = nfactors;
					}
					if(nfactors>maxFactors){
						maxFactors = nfactors;
					}
				}
			}
			if(maxFactors<5 && (maxFactors - minFactors) > 2){
				return false;
			}
			if(maxFactors<10 && (maxFactors - minFactors) > 3){
				return false;
			}
			if(maxFactors>=10 && (maxFactors - minFactors) > 5){
				return false;
			}
			if(type != PLS) {
				if(maxHidden<10 && (maxHidden - minHidden) > 4){
					return false;
				}
				if(maxHidden>=10 && (maxHidden - minHidden) > 8){
					return false;
				}
			}
		}
		if(VERBOSE){
			System.out.println("ARCHITECTURE HOMOGENIETY TEST PASSED");
		}
		return true;
	}

	static int getModelType(Model M) {
		int modelType;
		String classname =  M.getClass().getName();
		if(classname.equals("com.gensym.math.datafit.Pls")){
			modelType = PLS;
		}
		else if(classname.equals("com.gensym.math.datafit.Nlpls")){
			modelType = NLPLS;
		}
		else modelType = PlsBPN;
		return modelType;
	}

//added in 2.2r0
	public String outputModelParameters(String modelName) throws MathException{
		String s = "";
		int nmodels;
		if(predictionSize<=0 || predictionSize>size()) {
			nmodels = size();
		}
		else{
			nmodels = predictionSize;
		}
		for (int i=0;i<nmodels;i++) {
//			s = s+"double  modelName_weights"+i+"["+3+"]["+6+"]["+5+"] =\n"; 
			TrainableModel model = (TrainableModel) models.elementAt(i);
			s = s+model.getModelParameters(modelName,i)+"\n";
//			model.writeWeights(Source);
		}

/*	SUBMODELPARAMETERS * subparas = new SUBMODELPARAMETERS[5];
	subparas[0] = subpara1;
	subparas[1] = subpara2;
	subparas[2] = subpara3;
	subparas[3] = subpara4;
	subparas[4] = subpara5;
 */
		//		System.out.println(s);
		return s;
	}

//added in 42r0
	public String getModelCString(){

		StringBuffer sb = new StringBuffer(1000); 
		int nmodels;
		if(predictionSize<=0 || predictionSize>size()){
			nmodels = size();
		}
		else{
			nmodels = predictionSize;
		}

		TrainableModel md = (TrainableModel) models.elementAt(0);
		int ins = md.getNin();
		sb.append("long nm = "+nmodels+";\n");
		sb.append("long m = "+md.getNout()+";\n");

		for (int i=0;i<nmodels;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
			model.writeParamVariable(sb,i);
		}
		sb.append("double **yy;\n");
		sb.append("double *yp,*yp1,*yp2,*yp3,*yp4,*yp5;\n");
		sb.append("double x[" + ins + "];\n");
		sb.append("double *y;\n");

		for (int i=0;i<ins;i++) {
			sb.append("x["+i+"] = x"+ i + ";\n");
		}
		
		for (int i=0;i<nmodels;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
//	System.out.println("model="+model);
			model.writeMatrixInit(sb,i);
		}

		for (int i=0;i<nmodels;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
			model.writeWeightAsC(sb,i);
		}
		return sb.toString();
	}

	public void writePLSWeightFile(String dir,String fileName) throws IOException, MathException {
		
		int nmodels;
		if(predictionSize<=0 || predictionSize>size()){
			nmodels = size();
		}
		else{
			nmodels = predictionSize;
		}
		if(nmodels > 5){
			nmodels = 5;
		}
		boolean allPLS = true;
		for (int i=0;i<nmodels;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
			if(!(model instanceof com.gensym.math.datafit.Pls)){
				allPLS = false;
			}
		}
//System.out.println("allpls="+allPLS);
		if(!allPLS){
			return;
		}
		
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
	    	Source.write("1; Version of this file save/restore protocol");
	    	Source.newLine();

			Source.write(nmodels+"; Number of submodels");
			Source.newLine();
			for (int i=0;i<nmodels;i++) {
				Pls model = (Pls) models.elementAt(i);
				model.writeWeightsAsPLS(Source);
			}
	    }finally {
	  	  closeSilently(Source);
	  	  closeSilently(fileOut);
	  	  closeSilently(outStream);
	    }
	}

/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() throws MathException {
		int nmodels,newnmodels;
		if(predictionSize<=0 || predictionSize>size()){
			nmodels = size();
		}
		else{
			nmodels = predictionSize;
		}
		if(nmodels > 5){
			nmodels = 5;
		}
		newnmodels = 5;
		Vector infors = new Vector();
		infors.addElement(5);
		for (int i=0;i<nmodels;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
			infors.addAll(model.getParametersVector());
		}
		if(nmodels < 5 || !models.isEmpty()){
			TrainableModel model = (TrainableModel) models.elementAt(0);
			for (int i=nmodels;i<newnmodels;i++) {
				infors.addAll(model.getParametersVector());
			}
		}
		return infors;
	}

/** Set the model information with a Vector */
	public void setParametersVector(Vector params) throws MathException {
		int bpnCount = (Integer.parseInt(params.elementAt(0).toString()));
System.out.println("Ensemble bpnCount="+bpnCount);
		int counter = 1;
		clearModels();
		for (int i=0;i<bpnCount;i++) {
			MimoBpn	net = new MimoBpn();
			Sequence bpnSqs = (Sequence)params.elementAt(counter);
			counter = counter + 1;
			net.setParametersVector(bpnSqs);
			models.addElement(net);
			ratings.addElement(i);
		}
		numberOfModelsTrained = bpnCount;
	}

	@Override
	public int writeXMLFile(final BufferedWriter target, final int indentNumber) throws IOException, MathException {
		
		int indent = indentNumber;
		int nmodels,newnmodels;
		if(predictionSize<=0 || predictionSize>size()){
			nmodels = size();
		}
		else{
			nmodels = predictionSize;
		}
		if(nmodels > 5){
			nmodels = 5;
		}
		newnmodels = 5;

		String dataString = Utilities.indent(indent)+"<ensemble>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		for (int i=0;i<nmodels;i++) {
			TrainableModel model = (TrainableModel) models.elementAt(i);
			indent = model.writeXMLFile(target,indent);
		}
		if(nmodels < 5 || !models.isEmpty()){
			TrainableModel model = (TrainableModel) models.elementAt(0);
			for (int i=nmodels;i<newnmodels;i++) {
				indent = model.writeXMLFile(target,indent);
			}
		}
		indent--;
		dataString = Utilities.indent(indent)+"</ensemble>\n";
		target.write(dataString,0,dataString.length());
		return indent;
	}
}

