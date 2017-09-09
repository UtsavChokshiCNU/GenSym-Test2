package com.gensym.nols.data;
/*		
 *	Re-written by MK to handle formulas involving variables from different time series.
 *
 *	TO DO: Must change from variable names to tags!
 *  TO DO: Must support separate interpolators for each variable
 *		(This will be done by creating a new class, Interpolator, and extending the 
 *		Variable class so that each variable can (optionally) have its own Interpolator.
 */

import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.matrix.TimeFunctions;
import com.gensym.nols.data.function.FunctionInterface;

public class Formula2 extends Object implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected String name;  // to be removed
	protected String description;
	// Vector inputs contains names of variables, or formulas, or values
	protected Vector inputs;  
	// Vector outputs contains names of output variables. Note that embedded formulas
	// will not have explicit outputs, so this vector may be empty
	protected Vector outputs;  
	protected FunctionInterface function;

/** Create a null data Formula2 object. */	
	public Formula2() {
		super();
		name = "";   // dead, uses function name
		description = "";
		inputs = new Vector();
		outputs = new Vector();
		function = null;
	}

	/** return a clone of the current formula */
	public Formula2(Formula2 formula) {
		this();
		Object newObj, obj;
		for(int i=0;i<formula.inputs.size();i++) {
			obj = formula.inputs.elementAt(i);
			if(obj instanceof InnerFormula2){
				newObj = new InnerFormula2((InnerFormula2) obj);
			}else{
				newObj = obj;  // otherwise, an (immutable) string or double, so no need to duplicate
			}
			inputs.addElement(newObj);
		}
		for(int i=0;i<formula.outputs.size();i++) {
			outputs.addElement(formula.outputs.elementAt(i));
		}
		function = formula.function;  // should duplicate rather than just point at it ???
	}

/** Create a Formula2 object with given inputs and outputs */	
	public Formula2(FunctionInterface func, Vector ins, Vector outs) {
		this();
		inputs = ins;
		outputs = outs;
		function = func;
	}

/** Create a Formula2 object with given inputs */
	public Formula2(FunctionInterface func, Vector ins) {
		this(func, ins, new Vector());
	}
	
/** Create a Formula2 object with empty inputs or outputs */
	public Formula2(FunctionInterface func) {
		this(func, new Vector(), new Vector());
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		Formula2 cloned = (Formula2) super.clone();
		cloned.inputs = inputs == null ? null : (Vector) inputs.clone();
		cloned.outputs = outputs == null ? null : (Vector) outputs.clone();
		cloned.function = function == null ? null : (FunctionInterface) function.clone();
		
		return cloned;
	}

/** get the function of this formula */
	public FunctionInterface getFunction() {
		return function;
	}

/** get the function of this formula, and sets the input and outputs if the function
	has specific names it must use.  */
	public void setFunction(FunctionInterface func) {
		function = func;
		Vector inputNames = func.getInputVarNames();
		Vector outputNames = func.getOutputVarNames();
		if(inputNames!=null) {
			inputs.removeAllElements();
			for(int i=0;i<inputNames.size();i++) {
				inputs.addElement(inputNames.elementAt(i));
			}
		}
		if(outputNames!=null) {
			outputs.removeAllElements();
			for(int i=0;i<outputNames.size();i++) {
				outputs.addElement(outputNames.elementAt(i));
			}
		}
	}

/** Set the function with a string */
	public void setFunction(String funcName) throws ClassNotFoundException, IllegalAccessException, InstantiationException  {
		FunctionInterface func = (FunctionInterface) Class.forName(FormulaMap.toQualifiedName(funcName)).newInstance();
		setFunction(func);
	}

	public void clearFunction() {
		function = null;
	}

/** return the name of the formula, the same as the name of its function */
	public String getName() {
		if(getFunction()==null){
			return "";
		}else{
			return getFunction().getName();
		}
	}

/** Test whether this Formula has a output variable with given name. */
	public boolean hasOutput(String varName){
		for(int i=0;i<outputs.size();i++){
			if(outputs.elementAt(i) instanceof String){
				if(varName.equals(outputs.elementAt(i))){
					return true;
				}
			}
		}
		return false;
	}

/** Test whether this Formula has a input variable with given name. */
	public boolean hasInput(String varName){
		for(int i=0;i<inputs.size();i++){
			Object inputObj = inputs.elementAt(i);
			if(inputObj instanceof String){
				if(varName.equals(inputs.elementAt(i))){
					return true;
				}
			} else if(inputObj instanceof Formula2){
				return (((Formula2)inputObj).hasInput(varName));
			}
		}
		return false;
	}

/** Get all the variable names from the formula inputs. */
	public void getInputVars(Vector vars){
		for(int i=0;i<inputs.size();i++){
			Object inputObj = inputs.elementAt(i);
			if(inputObj instanceof String){
				vars.addElement(inputObj);
			}else if(inputObj instanceof Formula2){
				((Formula2)inputObj).getInputVars(vars);
			}
		}
	}

/** Test whether this Formula has a variable with given name. */
	public boolean hasVariable(String varName){
		if(hasOutput(varName) || hasInput(varName)) {
			return true;
		}
		return false;
	}


/** Get the input object array.*/
	public Vector getInputs(){ 
		return inputs;
	}

/** Get the output object array.*/
	public Vector  getOutputs(){ 
		return outputs;
	}

/** Set the input object array.*/
	public void setInputs(Vector ins){
		inputs=ins;
	}

/** Set the output object array.*/
	public void setOutputs(Vector outs){
		outputs=outs;
	}

/** Add the input object array.*/
	public void addInput(Object ins){
		inputs.addElement(ins);
	}

/** Remove a input object from the end of the input array.*/
	public void removeInput(){
		inputs.removeElementAt(inputs.size()-1);
	}

/** Add the output object array.*/
	public void addOutput(Object outs){
		outputs.addElement(outs);
	}

/** Remove a outputs object from the end of the input array.*/
	public void removeOutput(){
		outputs.removeElementAt(outputs.size()-1);
	}


/** get the number of inputs of this Formula.*/
	public int getNumberOfInputs(){
		return inputs.size();
	}

/** get the number of inputs of this Formula.*/
	public int getNumberOfOutputs(){
		return outputs.size();
	}

	/** get top-level */
	public Object getInput(int i) {
		return inputs.elementAt(i);
	}

	/** Recursively search inputs given a Vector containing integers.
	If the input is a formula, we get the input of that formula.
	This can generate all sorts of exceptions & it is up to the caller to make
	sure that all indices point to subformulas, not other objects. */
	public synchronized Object getInput(Vector indices) {
		return getInput(indices, indices.size());
	}

	/** Recursive search of inputs using only the first n elements of indices vector */
	public synchronized Object getInput(Vector indices, int n) {
		if(n<=0) {
			return this;  // special case
		}
		Formula2 workingFormula = this;
		Object obj = null;
		for(int i=0;i<n;i++) {
			int index = ((Integer) indices.elementAt(i)).intValue();
			obj = workingFormula.getInputs().elementAt(index);
			if(i!=n-1) {
				workingFormula = (Formula2) obj;  // attempt a cast
			}
		}
		return obj;
	}

/** toString method*/
	@Override
	public String toString(){
		String s = "{";
		for(int i=0;i<outputs.size();i++){
			s=s+outputs.elementAt(i).toString();
			if(i<outputs.size()-1) {
				s = s+", ";
			}
		}
		s = s+"}="+function.getName()+"(";
		for(int i=0;i<inputs.size();i++){
			s=s+inputs.elementAt(i).toString();
			if(i<inputs.size()-1) {
				s = s+", ";
			}
		}
		s = s +")";
		return s;
	}


	/** Main method for applying formula.  This methods may ONLY be called on an
	OUTER formula, not one nested into another formula. */
	public void applyFormula(DataSeries[] allData) throws MathException, FormulaException {
		DataSeries timeSource = findTimeSource(allData);
		if(timeSource.isEmpty())
			throw new FormulaException("Can not apply formula to a empty data series"); //Gchen added 3/2/99
		Vector results = applyFormulaCore(timeSource, allData);
		copyResultsToDataSeries(timeSource, allData, results);
	}

	/** Alternate method for applying formula, with data series given as a Vector */
	public void applyFormula(Vector dataSeriesVector) throws MathException, FormulaException {
		int n = dataSeriesVector.size();
		DataSeries[] allData = new DataSeries[n];
		for(int i=0;i<n;i++){
			allData[i] = (DataSeries) dataSeriesVector.elementAt(i);
		}
		applyFormula(allData);
	}

	/** This applies the formula, with a given time source, and returns a vector 
	of double arrays containing the result. Used when evalating nested formulas, 
	and as a step in evaluating outer formulas */
	private Vector applyFormulaCore(DataSeries timeSource, DataSeries[] allData) throws MathException, FormulaException  {
		Vector ins = prepareInputs(timeSource, allData);
		//System.out.println("number of inputs is "+ins.size());
		if (ins.size()<function.getMinimumInputs() || ins.size()>function.getMaximumInputs()) {
			throw new FormulaException("Wrong number of inputs ("+ins.size()+") to "+function.getName());
		}
		int nout = function.getNumberOfOutputs(ins.size());
		int n = timeSource.getRow();
		// prepare output vector
		Vector outs = new Vector();
		for(int i=0;i<nout;i++) {
			outs.addElement(new double[n]);
		}
		function.evaluate(timeSource.getTimeStamps(), ins, outs);
		return outs;
	}

	/** Get inputs as a vector of double arrays, interpolated to the time
	grid given by timeSource.  Recursively evaluates arguments if required. */
	private Vector prepareInputs(DataSeries timeSource, DataSeries[] allData) throws FormulaException, MathException {
		Vector ins = new Vector();
		if((function instanceof NolModel2) && timeSource.getHasTimeStamps()){ //gchen 7.12.99
//		System.out.println("function is NolModel2");
			Vector dds = new Vector();
			for(int i =0;i<allData.length;i++){
				dds.addElement(allData[i]);
			}
			NolModel2  model = (NolModel2)function;
			Matrix X = Matlib.createMatrix();
			Matrix Y = Matlib.createMatrix();
			long[] outputTime = new long[0];
			try{
				outputTime = model.prepareTrainingSetFromDataSeries(dds,X,Y);
//System.out.println("function is NolModel2 prepareInputs");
//for(int i =0;i<outputTime.length;i++){
//System.out.println("outputTime[]="+outputTime[i]);
//}
//Matlib.disp(X);
			} catch(MathException evt){
				System.err.println("Non-Fatal exception preparing training set: " + evt.getMessage());
				evt.printStackTrace();
			}
			int n = timeSource.getRow();  // required length
			if(n == outputTime.length){ 
//		System.out.println("same length = "+n);
				Matlib.transpose(X,X);
				double[][] xArray =  Matlib.create2DArray(X);
				for(int c=0;c<xArray.length;c++){
					ins.addElement(xArray[c]);
				}
			}else{
//		System.out.println("not same length n= "+n+"  outputTime.length="+outputTime.length);
				int cols  = X.getCols();
				double[][] xArray =  new double[cols][n];
				for(int c=0;c<cols;c++){
					for(int r=0;r<n;r++){
						xArray[c][r] = Double.NaN;
					}
				}  //gchen initialized to NaN.
				long[] time1 = timeSource.getTimeStamps();
				int i1 = 0;
				for(int i2=0;i2<outputTime.length;i2++){
					long t1 = time1[i1];
					long t2 = outputTime[i2];
					if(t1==t2){
						for(int c=0;c<cols;c++){
							xArray[c][i1] = X.get(i2,c);
						}
					}else if(t1 < t2){
						while(t1 < t2){
							i1++;
							t1=time1[i1];
						}
						for(int c=0;c<cols;c++){
							xArray[c][i1] = X.get(i2,c);
						}
					}
					i1++;
				}
				for(int c=0;c<xArray.length;c++){
					ins.addElement(xArray[c]);
				}
			}
			Matlib.clear(X);
			Matlib.clear(Y);
		}else{
			for(int i=0;i<inputs.size();i++) {
				Object obj = inputs.elementAt(i);
				//System.out.println("getInputs ---- argument is a "+obj.getClass().getName());
				if(obj instanceof String) {  // it is a variable name
					String varName = (String) obj;
					int dsIndex = findDataSeriesContainingVar(varName, allData);
					if (dsIndex==-1) {
						throw new FormulaException("No variable named "+varName);
					}
					DataSeries ds = allData[dsIndex];
					double[] thisInput =  ds.getVarArrayByName(varName);
					if(thisInput == null)  //Gchen added 3/2/99 for empty data series
						throw new FormulaException("Can not apply formula to a empty data series"); //Gchen added 3/2/99
					if(ds.getHasTimeStamps() && !ds.equals(timeSource)) {
						// input is from a different data series, so interpolate onto the time grid
						thisInput = TimeFunctions.interpolateArray(thisInput, ds.getTimeStamps(), timeSource.getTimeStamps());
					}
					ins.addElement(thisInput);
				} else if (obj instanceof Formula2) {
					Formula2 innerFormula = (Formula2) obj;
					Vector innerResult = innerFormula.applyFormulaCore(timeSource, allData);
					//System.out.println("returned inner result, cols = "+innerResult.size());
					for(int j=0;j<innerResult.size();j++) {
						ins.addElement(innerResult.elementAt(j));
					}
				} else if (obj instanceof Double) {
					// expand into array of proper size
					int n = timeSource.getRow();  // required length of input arrays
					double[] inArray = new double[n];
					double value = ((Double) obj).doubleValue();
					for(int j=0;j<n;j++) {
						inArray[j] = value;
					}
					ins.addElement(inArray);
				} else throw new FormulaException("Unknown input type: "+obj.getClass().getName());
			}
		}
		return ins;
	}

	/** Find the first variable in the formula (considering outputs before inputs)
	that has a time stamp.  If the first argument is a function, we recursively find 
	the first input variable in that function.  If this is row-based data, we return  
	the first data series as a dummy
	MK -- added 5/1/99 -- if formula doesn't use any existing variable, add to the 
	first data series, by default -- this permits formulas like new1 = RandNormal(0,1)*/
	private DataSeries findTimeSource(DataSeries[] allData) throws FormulaException {
		if(!(allData[0]).getHasTimeStamps()) {
			return allData[0];
		}
		for(int i=0;i<outputs.size();i++) {
			String varName = (String) outputs.elementAt(i);
			int index = findDataSeriesContainingVar(varName, allData);
			if(index>=0) {
				return (DataSeries) allData[index];
			}
		}
		for(int i=0;i<inputs.size();i++) {
			Object obj = inputs.elementAt(i);
			if(obj instanceof String) {
				String varName = (String) obj;
				int index = findDataSeriesContainingVar(varName, allData);
				if(index>=0) {
					return (DataSeries) allData[index];
				}else {
					throw new FormulaException("Formula inputs included a variable, "+varName+", that does not in the source data");
				}
			} else if (obj instanceof Formula2) {
				DataSeries timeSource = ((Formula2)obj).findTimeSource(allData);
				return timeSource;
			}
		}
		return allData[0]; 
	}

	/** Return the index of the data series containing varName */
	private int findDataSeriesContainingVar(String varName, DataSeries[] allData) {
		for(int index=0;index<allData.length;index++) {
			DataSeries ds = allData[index];
			int containsVar = ds.getVarIndexByName(varName);
			if(containsVar>=0){
				return index;
			}
		}
		return -1;  //not found
	}

	private void copyResultsToDataSeries(DataSeries timeSource, DataSeries[] allData, Vector results) throws FormulaException, MathException {
		int nout = outputs.size(); 
		int[] outputDsIndex = new int[nout];
		if(results.size()< nout) 
			throw new FormulaException(function.getName()+" returned "+results.size()+" outputs, formula requires "+nout+" values.");
			// Determine index of timeSource within allData (needed below).  Time source must be one of the data series in allData!
		int timeSourceIndex = 0;
		DataSeries ds = allData[0];
		while(!ds.equals(timeSource)) {
			timeSourceIndex++;
			ds = allData[timeSourceIndex];
		}
		// precalculate the number of new derived variables, if any
		Vector newVars = new Vector();
		for(int i=0;i<nout;i++) {
			String varName = (String) outputs.elementAt(i);
			int thisDsIndex = findDataSeriesContainingVar(varName, allData);
			//System.out.println("var = "+varName+" found in data series "+thisDsIndex);
			if(thisDsIndex < 0) { // a new derived variable
				thisDsIndex = timeSourceIndex;  // add new var to time source data series
				newVars.addElement(varName);
			}
		}
		// resize the timeSource data series to hold new vars, if any, update the variable objects
		//System.out.println("Resizing for "+newVars.size()+" more variables");
		if(!newVars.isEmpty()) {
			int numNewVars = newVars.size();
			int oldCols = timeSource.getColumn();
			timeSource.addColumns(numNewVars);
			for(int i=0;i<numNewVars;i++) {
				String varName = (String) newVars.elementAt(i);
				timeSource.setVariableParameters(oldCols+i,varName,varName,"");
			}
		}
		// now copy the numerical results into the appropriate data series
		for(int i=0;i<nout;i++) {
			Object resultsObj = results.elementAt(i);
			if(!(resultsObj instanceof double[])) {
				throw new FormulaException("Function returned a "+resultsObj.getClass().getName()+", not an appropriate type for the value of a variable."); 
			}
			double[] values = (double[]) resultsObj;
			String varName = (String) outputs.elementAt(i);
			int index = findDataSeriesContainingVar(varName, allData);
			ds = allData[index];
			int col = ds.getVarIndexByName(varName);
			//System.out.println("Output "+varName+" in data series "+index+", col "+col);
			ds.setColumnValues(col, values);
		}
	}

/** get the length of input buffer.*/
	public long getInputBufferLength() {
		if(function!=null) {
			return function.getRequiredHistoryLength();
		}
		else return 0L;
	}
}