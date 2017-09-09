package com.gensym.nols.data;
/*
 *		Gensym Model Class.
 *		This class is extended from Object.class
 *		Modified 3/25/98 by Gchen
 */

import java.io.Closeable;
import java.io.IOException;
import java.io.Serializable;
import java.util.Vector;

import com.gensym.DEBUG;
import com.gensym.math.MathException;
import com.gensym.math.Utilities;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.Model;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.matrix.TimeFunctions;
import com.gensym.nols.data.function.FunctionInterface;
/** Model class. */
public class NolModel2 implements INolModel2, FunctionInterface, Serializable {
	static final long serialVersionUID = 1L;
	protected Vector inputs;
	protected Vector outputs;
	protected Vector inputDelays;
	protected Vector outputDelays;
	protected Model model;
	protected boolean isTrained;
	private String comment;
	private int delayTimeUnit; // 1: Hour; 2: Minute; 3: Second.
	protected boolean hasTimeStamps;
	protected String name;

	protected double modelRateValue;
	protected Vector TrainingRmse;
	protected Vector TestingRmse;
	protected Vector TrainingCorrcoef;
	protected Vector TestingCorrcoef;

	protected transient Preprocessor preprocessor;  // reference to preprocessor
	protected int preprocessorHashCode;  // reference to data series object

/** Create a null data Model object. */	
	public NolModel2() {
		super();
		comment = "";
		delayTimeUnit = 2;
		isTrained = false;
		hasTimeStamps = true;
	}

/** Create a Model object with given EnsembleModel object.*/	
	public NolModel2(EnsembleModel net, String name, Vector outs, 
		Vector ins, Vector oDelays, Vector iDelays, Preprocessor prep){
		this();
		preprocessor = prep;
		preprocessorHashCode = prep.hashCode();
		this.name = new String(name);
		model = net;
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


// Implementation of FunctionInterface
	@Override
	public String getName() {
		return name;
	}


	public void setName(String n) {
		name = n;
	}

	@Override
	public String getDescription() {
		return comment;
	}

	@Override
	public int getMinimumInputs() {
		return model.getNin();
	}

	@Override
	public int getMaximumInputs() {
		return model.getNin();
	}

	@Override
	public int getNumberOfOutputs(int numberOfInputs) {
		return model.getNout();
	}

	/** return the flag of auto resursive model.*/
	public boolean isAutoRecursiveModel(){
		return inputs.isEmpty() && !outputs.isEmpty();
	}

	/** return the flag of resursive model.*/
	@Override
	public boolean isRecursiveModel(){
		for(int i=0;i<outputs.size();i++){
  			long[] dls = (long[])outputDelays.elementAt(i);
			for(int j=0;j<dls.length;j++){
				if(dls[j]>0){
					return true;
				}
			}
		}
		return false;
	}

	@Override
	public void evaluate(long t[], Vector inputs, Vector outputs) 
		throws MathException {		 //Gchen implemented 3/2/99
		int cols = inputs.size();
		double[][] array = new double[cols][];
		for(int c=0;c<cols;c++){
			array[c] = (double[])inputs.elementAt(c);
		}
		Matrix X = Matlib.createMatrix(array);
		Matlib.transpose(X,X);
		Matrix Y = Matlib.createMatrix(X.getRows(),outputs.size());
		model.evaluate(X,Y);
		outputs.removeAllElements();
		Matlib.transpose(Y,Y);
		double[][] outputArray =  Matlib.create2DArray(Y);
		for(int c=0;c<outputArray.length;c++){
			outputs.addElement(outputArray[c]);
		}
	}

	@Override
	public Vector getInputVarNames() {
		return inputs;
	}

	@Override
	public Vector getOutputVarNames() {
		return outputs;
	}

// End of Function Interface implementation

	@Override
	public Model getModel() {
		return model;
	}

/** Return the comment of this model.*/
	@Override
	public String getComment(){
		return comment;
	}

/** Set the comment of this model.*/
	public void setComment(String c){
		comment = c;
	}

/** Return the delayTimeUnit of this model.*/
	@Override
	public int getDelayTimeUnit(){
		return delayTimeUnit;
	}

/** Set the delayTimeUnit of this model.*/
	public void setDelayTimeUnit(int n){
		delayTimeUnit = n;
	}

 /** Get the status of this timestamps. */
	public boolean getHasTimeStamps(){
		return hasTimeStamps;
	}
	
 /** Set the status of this timestamps. */
	public void setHasTimeStamps(boolean h){
		hasTimeStamps = h;
	}

	@Override
	public boolean isTrained(){
		return isTrained;
	}

	@Override
	public void setIsTrained(boolean b){
		isTrained = b;
	}

	@Override
	public Vector getInputDelays(){
		return inputDelays;
	}

	@Override
	public Vector getOutputDelays(){
		return outputDelays;
	}

	@Override
	public Vector getInputs(){
		return inputs;
	}

	@Override
	public Vector getOutputs(){
		return outputs;
	}

	public Preprocessor getPreprocessor(){
		return preprocessor;
	}

	public void getPreprocessor(Preprocessor prep){
		preprocessor = prep;
	}

/** toString method*/
	@Override
	public String toString(){
		return name;
	}

/** toString method*/
	public String modelToString(){
		String s = name+"(";
		for(int i=0;i<inputs.size();i++){
			s=s+inputs.elementAt(i).toString();
			if(i<inputs.size()-1) {
				s = s+",";
			}
		}
		s = s +")";
		return s;
	}

	@Override
	public int getNin(){
		return model.getNin();
	}

	@Override
	public int getNout(){
		return model.getNout();
	}

	@Override
	public ArchitectureParameters getArchitectureParameters(){
		return model.getArchitectureParameters();
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException{
		model.evaluate(X,Y);
	}

	public void initTransient(Project p){
		Vector preps = p.getPreprocessors();
		for(int i=0;i<preps.size();i++){
			Preprocessor prep = (Preprocessor)preps.elementAt(i);
			if(DEBUG.debugFlag){
				System.out.println("i="+i);
				System.out.println("name="+name);
				System.out.println("preprocessorHashCode="+preprocessorHashCode);
				System.out.println("prep.getItsHashCode()="+prep.getItsHashCode());
			}
			if(preprocessorHashCode == prep.getItsHashCode()){
				preprocessor = prep;
				break;
			}
		}
		preprocessorHashCode = preprocessor.hashCode();
	}


	public long[] prepareTrainingSet(Matrix X, Matrix Y) throws MathException{
		return prepareTrainingSet(X, Y, true);
	}

	public long[] prepareTrainingSet(Matrix X, Matrix Y, boolean clearBadData) throws MathException{
		Vector inVars = new Vector(inputs.size());
		Vector inVarDelay = new Vector(inputs.size());
		Vector outVars = new Vector(outputs.size());
//System.out.println("get here 1");
		for(int i=0;i<outputs.size();i++){
			String varName = (String)outputs.elementAt(i);
			Variable varObj = preprocessor.getVariableFromVariableName(varName);
  			outVars.addElement(varObj);
  			long[] dls = (long[])outputDelays.elementAt(i);
			int r = 0;
			for(int j=0;j<dls.length;j++){
				if(dls[j]>0){
					r++;
				}
			}
			if (r > 0 ){
				inVars.addElement(varObj);
				long[] newdls = new long[r];
				int c = 0;
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						newdls[c] =dls[j];
						c++;
					}
				}
				inVarDelay.addElement(newdls);
			}
		}
//System.out.println("get here 2");
		for(int i=0;i<inputs.size();i++){
			String varName = (String)inputs.elementAt(i);
			Variable varObj = preprocessor.getVariableFromVariableName(varName);
			inVars.addElement(varObj);
			inVarDelay.addElement(inputDelays.elementAt(i));
		}
//System.out.println("get here 3");
		if(hasTimeStamps)
			return TimeFunctions.createTrainingSet(inVars, inVarDelay, outVars, X, Y, clearBadData);
//System.out.println("get here 4");
		TimeFunctions.createTrainingSet(inVars,outVars, X, Y);
//System.out.println("get here 5");
		return null;
	}

/** Return variable object for the variable name.*/
	protected Variable getVariableFromVariableName(Vector processedData, String varName){
		for(int i=0;i<processedData.size();i++){
			DataSeries ds = (DataSeries)processedData.elementAt(i);
			Variable varObj = ds.getVarByName(varName);
			if(varObj != null){
				return varObj;
			}
		}
		return null;
	}

	public long[] prepareTrainingSetFromDataSeries(Vector processedData, Matrix X, Matrix Y) throws MathException{
		Vector inVars = new Vector(inputs.size());
		Vector inVarDelay = new Vector(inputs.size());
		Vector outVars = new Vector(outputs.size());
		for(int i=0;i<outputs.size();i++){
			String varName = (String)outputs.elementAt(i);
			Variable varObj = getVariableFromVariableName(processedData,varName);
  			outVars.addElement(varObj);
  			long[] dls = (long[])outputDelays.elementAt(i);
			int r = 0;
			for(int j=0;j<dls.length;j++){
				if(dls[j]>0){
					r++;
				}
			}
			if (r > 0 ){
				inVars.addElement(varObj);
				long[] newdls = new long[r];
				int c = 0;
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						newdls[c] =dls[j];
						c++;
					}
				}
				inVarDelay.addElement(newdls);
			}
		}
		for(int i=0;i<inputs.size();i++){
			String varName = (String)inputs.elementAt(i);
			Variable varObj = getVariableFromVariableName(processedData, varName);
			inVars.addElement(varObj);
			inVarDelay.addElement(inputDelays.elementAt(i));
		}
//System.out.println("outputs="+outputs.size());
//System.out.println("inputs="+inputs.size());
//System.out.println("invars="+inVars.size());
		if(hasTimeStamps)
			return TimeFunctions.createTrainingSet(inVars, inVarDelay, outVars, X, Y);
		TimeFunctions.createTrainingSet(inVars,outVars, X, Y);
		return null;
	}

	@Override
	public Object clone() throws CloneNotSupportedException{
		NolModel2 cloned = (NolModel2) super.clone();
		cloned.inputs = inputs == null ? null : (Vector) inputs.clone();
		cloned.outputs = outputs == null ? null : (Vector) outputs.clone();
		cloned.inputDelays = inputDelays == null ? null : (Vector) inputDelays.clone();
		cloned.outputDelays = outputDelays == null ? null : (Vector) outputDelays.clone();
		cloned.TrainingRmse = TrainingRmse == null ? null : (Vector) TrainingRmse.clone();
		cloned.TestingRmse = TestingRmse == null ? null : (Vector) TestingRmse.clone();
		cloned.TrainingCorrcoef = TrainingCorrcoef == null ? null : (Vector) TrainingCorrcoef.clone();
		cloned.TestingCorrcoef = TestingCorrcoef == null ? null : (Vector) TestingCorrcoef.clone();
		
		cloned.preprocessor = preprocessor == null ? null : (Preprocessor) preprocessor.clone();

		return cloned;
	}

/** get the length of input buffer.*/
	@Override
	public long getRequiredHistoryLength(){
		long L = 0L;
		if(!hasTimeStamps){
			return L;
		}
		for(int i=0;i<inputDelays.size();i++){
			long[] delays = (long[]) inputDelays.elementAt(i);
			for(int j=0;j<delays.length;j++){
				if(L<delays[j])
					L = delays[j];
			}
		}
	/*	for(int i=0;i<outputDelays.size();i++){
			long[] delays = (long[]) outputDelays.elementAt(i);
			for(int j=0;j<delays.length;j++){
				if(L<delays[j])
					L = delays[j];
			}
		} */
		return L;
	}

/** Convert model into C code string.*/
// addition for version 50r0. gchen	 9/23/04
	public String getModelContents(){
		StringBuffer sb = new StringBuffer(1000);
		sb.append(getModelHeader() + "{ \n");
		sb.append(((EnsembleModel)model).getModelCString()+"\n");
		sb.append("y = vector(m);\n");
		sb.append("yp = vector(m);\n");
		sb.append("yp1 = vector(m);\n");
		sb.append("yp2 = vector(m);\n");
		sb.append("yp3 = vector(m);\n");
		sb.append("yp4 = vector(m);\n");
		sb.append("yp5 = vector(m);\n");
		sb.append("yy = matrix(nm,m);\n");

		sb.append("run_bpn(x,yp1,nlayer1,n11,n12,n13,0,0,tf1,w11,w12,NULL,NULL);\n");
		sb.append("if(nm == 1) {\n");
		sb.append("copyvector(yp1,y,m);\n");
		sb.append("free_vector(yp);\n");
		sb.append("free_vector(yp1);\n");
		sb.append("free_vector(yp2);\n");
		sb.append("free_vector(yp3);\n");
		sb.append("free_vector(yp4);\n");
		sb.append("free_vector(yp5);\n");
		sb.append("return y; \n}\n");

		sb.append("run_bpn(x,yp2,nlayer2,n21,n22,n23,n24,0,tf2,w21,w22,w23,NULL);\n");
		sb.append("if(nm == 2) {\n");
		sb.append("copymatrix(yy,yp1,yp2,NULL,NULL,NULL,2,m);\n");
		sb.append("findmedian(yy,yp,m,2);\n");
		sb.append("copyvector(yp,y,m);\n");
		sb.append("free_vector(yp);\n");
		sb.append("free_vector(yp1);\n");
		sb.append("free_vector(yp2);\n");
		sb.append("free_vector(yp3);\n");
		sb.append("free_vector(yp4);\n");
		sb.append("free_vector(yp5);\n");
		sb.append("return y; \n}\n");

		sb.append("run_bpn(x,yp3,nlayer3,n31,n32,n33,0,0,tf3,w31,w32,NULL,NULL);\n");
		sb.append("if(nm == 3) {\n");
		sb.append("copymatrix(yy,yp1,yp2,yp3,NULL,NULL,3,m);\n");
		sb.append("findmedian(yy,yp,m,3);\n");
		sb.append("copyvector(yp,y,m);\n");
		sb.append("free_vector(yp);\n");
		sb.append("free_vector(yp1);\n");
		sb.append("free_vector(yp2);\n");
		sb.append("free_vector(yp3);\n");
		sb.append("free_vector(yp4);\n");
		sb.append("free_vector(yp5);\n");
		sb.append("return y; \n}\n");

		sb.append("run_bpn(x,yp4,nlayer4,n41,n42,n43,0,0,tf4,w41,w42,NULL,NULL);\n");
		sb.append("if(nm == 4){\n");
		sb.append("copymatrix(yy,yp1,yp2,yp3,yp4,NULL,4,m);\n");
		sb.append("findmedian(yy,yp,m,4);\n");
		sb.append("copyvector(yp,y,m);\n");
		sb.append("free_vector(yp);\n");
		sb.append("free_vector(yp1);\n");
		sb.append("free_vector(yp2);\n");
		sb.append("free_vector(yp3);\n");
		sb.append("free_vector(yp4);\n");
		sb.append("free_vector(yp5);\n");
		sb.append("return y; \n}\n");

		sb.append("run_bpn(x,yp5,nlayer5,n51,n52,n53,n54,0,tf5,w51,w52,w53,NULL);\n");
		sb.append("copymatrix(yy,yp1,yp2,yp3,yp4,yp5,5,m);\n");
		sb.append("findmedian(yy,yp,m,5);\n");
		sb.append("copyvector(yp,y,m);\n");
		sb.append("free_vector(yp);\n");
		sb.append("free_vector(yp1);\n");
		sb.append("free_vector(yp2);\n");
		sb.append("free_vector(yp3);\n");
		sb.append("free_vector(yp4);\n");
		sb.append("free_vector(yp5);\n");
		sb.append("return y; \n }\n");
		return sb.toString();
	}

/** Return the header information for this model.*/
	public String getModelHeader(){
		StringBuffer sb = new StringBuffer();
		sb.append("double * "+getName()+ "(");
		for(int i=0;i<inputs.size()-1;i++){
			sb.append("double x"+ i +",");
		}
		sb.append("double x"+ (inputs.size()-1)+")");
		return sb.toString();
	}

/** Return the model string as in function call.*/
	public String getModelString(){
		StringBuffer sb = new StringBuffer();
		sb.append(getName()+ "(");
		for(int i=0;i<inputs.size()-1;i++){
			sb.append(inputs.elementAt(i).toString() +",");
		}
		sb.append(inputs.elementAt(inputs.size()-1).toString()+")");
		return sb.toString();
	}

/** Return the model information as in a Vector */
	public Vector getParametersVector() throws MathException {
		EnsembleModel ensemble = (EnsembleModel)getModel();
		return ensemble.getParametersVector();
	}

/** Set the model information with a Vector */
	public void setParametersVector(Vector params) throws MathException {
		EnsembleModel ensemble = (EnsembleModel)getModel();
		ensemble.setParametersVector(params);
	}

/** Return the model information including variables as in a Vector */
	public Vector getWholeParametersVector() throws MathException {
		Vector param = new Vector();
		param.addElement(name);
		param.addElement(comment);
		param.addElement(hasTimeStamps);
		calculateModelStatistics();
		param.addElement(modelRateValue);
		param.addElement(outputs.size());
		for (int i=0;i<outputs.size();i++){
			param.addElement(outputs.elementAt(i));
			param.addElement(TrainingRmse.elementAt(i));
			param.addElement(TestingCorrcoef.elementAt(i));
			param.addElement(TestingRmse.elementAt(i));
			param.addElement(TrainingCorrcoef.elementAt(i));
		}
		param.addElement(outputs.size());
		Vector outTags = new Vector();
		Vector outUnits = new Vector();
		Vector outStats = new Vector();
		getVariableInfo(outputs,outTags,outUnits,outStats);
		for (int i=0;i<outputs.size();i++){
			param.addElement(outputs.elementAt(i));
			param.addElement(outTags.elementAt(i));
			param.addElement(outUnits.elementAt(i));
			param.addElement(outStats.elementAt(i));
			param.addElement(outputDelays.elementAt(i));
		}
		param.addElement(inputs.size());
		Vector inTags = new Vector();
		Vector inUnits = new Vector();
		Vector inStats = new Vector();
		getVariableInfo(inputs,inTags,inUnits,inStats);
		for (int i=0;i<inputs.size();i++){
			param.addElement(inputs.elementAt(i));
			param.addElement(inTags.elementAt(i));
			param.addElement(inUnits.elementAt(i));
			param.addElement(inStats.elementAt(i));
			param.addElement(inputDelays.elementAt(i));
		}
		EnsembleModel ensemble = (EnsembleModel)getModel();
		param.addAll(ensemble.getParametersVector());
		return param;
	}

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
		EnsembleModel ensemble;
		if (getModel() instanceof EnsembleModel)
			ensemble = (EnsembleModel) getModel();
		else 
			ensemble = new EnsembleModel(getModel().getArchitectureParameters());

		int digits = 4;
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();
		double[] rmseAve = new double[nout];
		double[] corrAve = new double[nout];
		double rate =0;
		for(int j=0;j<nout;j++) {
			rmseAve[j] = 0.0;
			corrAve[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters VP = null;
				if(type==1) {
					VP = submodel.testingResults;
				}
				else VP = submodel.trainingResults;
				rmseAve[j] += VP.rmse.get(j);
				corrAve[j] += VP.corrcoef.get(j);
			}
			rmseAve[j] /= ensembleSize;
			corrAve[j] /= ensembleSize; 
		}
		for(int i=0;i<nout;i++) {
			rmse.addElement(Utilities.formatDouble(rmseAve[i], digits));
			corrcoef.addElement(Utilities.formatDouble(corrAve[i], digits));
			rate = rate+corrAve[i];
		}
		rate = rate/nout;
		return rate;
	}
	public void getVariableInfo(Vector names,Vector tags, Vector units,Vector statistics) { 
		tags.removeAllElements();
		units.removeAllElements();
		statistics.removeAllElements();
		for(int i=0;i<names.size();i++){
			String varName = (String)names.elementAt(i);
			Variable varObj = preprocessor.getVariableFromVariableName(varName);
			tags.addElement(varObj.getTag());
			units.addElement(varObj.getUnit());
			statistics.addElement(varObj.getStatistics());
		}
	}

	public double getModelRate(){
		return modelRateValue;
	}

	public Vector getTrainingRmse(){
		return TrainingRmse;
	}
	public Vector getTestingRmse(){
		return TestingRmse;
	}
	public Vector getTrainingCorrcoef(){
		return TrainingCorrcoef;
	}
	public Vector getTestingCorrcoef(){
		return TestingCorrcoef;
	}

	public void setModel(Model model) {
		this.model = model;
	}
	
	protected void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("NON-FATAL: Error while closing stream : " + e.toString());
      } 
	}
}
