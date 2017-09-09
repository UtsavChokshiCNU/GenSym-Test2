package com.gensym.nols.deploy;
/*
 *		Gensym OnlineProcessor Class.
 *		This class is extended from Object.class
 *		Modified 3/2/99 by Gchen
 */

import java.awt.Frame;
import java.awt.TextArea;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.OptionalDataException;
import java.io.Serializable;
import java.io.StreamCorruptedException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Vector;
import java.util.zip.GZIPInputStream;

import com.gensym.math.MathException;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.EnsembleModelEvent;
import com.gensym.math.datafit.EnsembleModelListener;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.Formula2;
import com.gensym.nols.data.INolModel2;
import com.gensym.nols.data.NolModel2;
import com.gensym.nols.data.NolModelTrainThread;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Processor;
import com.gensym.nols.data.Variable;
import com.gensym.nols.data.VersionManagerForOnlineProcessor;

/** An OnlineProcessor object provides a way to run the NOLStudio predictive model online.
* The object maintains a data buffer for storing the online data. 
* The steps for online deployment: 
* 1. Create a OnlineProcessor using default constructor.
* 2. Load exported model file using loadModel method.
* 3. You can check the variable names and tags, or whether it is a time-based model 
*    by call corresponding methods. 
* 4. Follow the user's guide to push input data into the data buffer.
* 5. Calculate the model prediction.
* 6. Follow the user's guide to get output values. 
*/
public class OnlineProcessor
 implements EnsembleModelListener, Processor, Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	static int INITIAL_BUFFER_SIZE = 10;  // number of points to store for time-based histories
	static int HISTORY_GROWTH_INCREMENT = 10;  // number of points to grow histories when increasing size
	static int MAX_BUFFER_SIZE = 1000;  // maximum number of points to store for time-based histories

	protected static int onlineProcessorInstanceCount = 0;
	protected String name;
	protected String comment; //Defaults are "".
	protected Vector inputDataBuffer;  // contains data buffers
	protected DataSeries outputData;
	protected long[] inputBufferLength = null;
	protected long outputBufferLength = 0l;
	protected DataSeries rowBasedInputData;
	protected Vector inputNames = null; // contains only original variables
	protected Vector outputNames = null;
	protected Vector varNames = null;  // contains all original variables used in formulas
	protected Vector varTags = null;
	protected Preprocessor preprocessor = null;
	protected int itsHashCode;
	protected boolean hasTimeStamps;
	protected SimpleDateFormat dateTimeFormat;		

	protected double[] testRMSE;
	protected double[] testCORR;
	protected double[] trainRMSE;
	protected double[] trainCORR;
	protected double modelRateValue = -1;
	protected boolean retrained = false;

	protected transient Vector itsEventListeners;

	protected String decFormatLocalString;

/** Create a null OnlineProcessor with no argument */
	public OnlineProcessor() {
		super();
		name = "OnlineProcessor" + onlineProcessorInstanceCount;
		comment = "";
		onlineProcessorInstanceCount++;
		inputNames = new Vector(0,10);
		outputNames = new Vector(0,10);
		varNames = new Vector(0,10);
		varTags = new Vector(0,10);
		itsHashCode = hashCode();
		inputDataBuffer = new Vector();
		dateTimeFormat = new SimpleDateFormat("M/d/y H:m:s");
		itsEventListeners = new Vector();
		decFormatLocalString = "English";
	}

/** Create a data OnlineProcessor from a given name and resources. This is for model export.*/
	public OnlineProcessor(String name, Preprocessor prep, NolModel2 model)
		throws MathException {
		this();
		this.name = name;
		onlineProcessorInstanceCount--;  // name is provided, decrement count that was incremented in this()
		initialize(prep, model);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		OnlineProcessor cloned = (OnlineProcessor) super.clone();
		
		cloned.outputData = outputData == null ? null : (DataSeries) outputData.clone();
		cloned.rowBasedInputData = rowBasedInputData == null ? null : (DataSeries) rowBasedInputData.clone();
		
		cloned.preprocessor = preprocessor == null ? null : (Preprocessor) preprocessor.clone();
		cloned.dateTimeFormat = dateTimeFormat == null ? null : (SimpleDateFormat) dateTimeFormat.clone();
		
		cloned.inputDataBuffer = inputDataBuffer == null ? null : (Vector) inputDataBuffer.clone();
		cloned.inputNames = inputNames == null ? null : (Vector) inputNames.clone();
		cloned.outputNames = outputNames == null ? null : (Vector) outputNames.clone();
		cloned.varNames = varNames == null ? null : (Vector) varNames.clone();
		cloned.varTags = varTags == null ? null : (Vector) varTags.clone();
		cloned.itsEventListeners = itsEventListeners == null ? null : (Vector) itsEventListeners.clone();
		
		return cloned;
	}

/** Initialize the properties of the OnlineProcessor. */
	protected void initialize(Preprocessor prep, NolModel2 model) throws MathException {
		comment = model.getComment();
		hasTimeStamps = prep.getHasTimeStamps();
		Vector modelOutputs = model.getOutputVarNames();
		Vector modelInputs = model.getInputVarNames();
		outputNames = (Vector)modelOutputs.clone();
		Vector derivedVarNames = new Vector();
		Vector formulas = new Vector();
		prep.getInputNamesDerivedVarsFormulasForModel(modelInputs,inputNames,derivedVarNames,formulas);
		varNames.removeAllElements();
		varTags.removeAllElements();

		Vector varObjects = new Vector();

		// get names and tags corresponding to varNames
		for(int i=0;i<inputNames.size();i++) {
			String varName =  (String)inputNames.elementAt(i);
			if(!varNames.contains(varName)){
				varNames.addElement(varName);
			}
 			Variable varObj = prep.getVariableFromVariableName(varName);
			if(!varTags.contains(varObj.getTag())){
				varTags.addElement(varObj.getTag());
			}
			if(!varObjects.contains(varObj)){
				varObjects.addElement(varObj);
			}
		}

		//Add output names and tags.
		for(int i=0;i<outputNames.size();i++) {
			String varName =  (String)outputNames.elementAt(i);
			if(!varNames.contains(varName)){
				varNames.addElement(varName);
			}
 			Variable varObj = prep.getVariableFromVariableName(varName);
			if(!varTags.contains(varObj.getTag())){
				varTags.addElement(varObj.getTag());
			}
			if(!varObjects.contains(varObj)){
				varObjects.addElement(varObj);
			}
		}
		int no = outputNames.size();
		
		addModelToFormula(formulas,model);
		preprocessor = new Preprocessor(prep.getName(),prep.getComment(),
			varNames, varTags, derivedVarNames, formulas,
			hasTimeStamps);


		if(hasTimeStamps){
			// when running preprocessor, each function records the maximum input buffer
			// length required.  This gives an estimate of the buffer length for "calculated" time delays
			initializeInputBufferLength();  
			int ni = inputNames.size();
			for(int c=0;c<ni;c++){
				// get name and tag of each input, used to create input data series
				String varName = (String)inputNames.elementAt(c);
				int index = varNames.indexOf(varName);
				String varTag = (String)varTags.elementAt(index);
				// We know the amount of time, but not the frequency, so we don't know how many 
				// points to store.  We adapt the number of points later to fit the required time window.
 				DataSeries ds  = new DataSeries(INITIAL_BUFFER_SIZE,1); 
				ds.setName(varName);
				ds.setVariableParameters(0,varTag,varName,"None");

				Variable varObj = ds.getVarByIndex(0);
				Variable varObj1 = findVariable(varObjects,varName);
//System.out.println("varObj1.getUnit() ="+varObj1.getUnit()); 
				varObj.setStatistics(varObj1.getStatistics());
				varObj.setUnit(varObj1.getUnit());

				inputDataBuffer.addElement(ds);
				long[] ts = new long[INITIAL_BUFFER_SIZE];
				for(int i=0;i<INITIAL_BUFFER_SIZE;i++){
					ts[i] = -1L;
					ds.setValueAt(i,0,Double.NaN);
				}
				ds.setTimeStamps(ts);
//				System.out.println("ds="+ds.toStringForSave());
			}
			if(model.isRecursiveModel()){
//System.out.println("isRecursiveModel ="+model.isRecursiveModel()); 
				initializeOutputBufferLength();  
				outputData = new DataSeries(INITIAL_BUFFER_SIZE,no);
				long[] timeStamps = new long[INITIAL_BUFFER_SIZE];
				timeStamps[0] = System.currentTimeMillis();
				for(int i=0;i<INITIAL_BUFFER_SIZE;i++){
					timeStamps[i] = -1L;
					for(int j=0;j<no;j++){
						outputData.setValueAt(i,j,Double.NaN);
					}
				}
//System.out.println("timeStamps.length ="+timeStamps.length); 
				outputData.setTimeStamps(timeStamps);
			}else{
				outputData = new DataSeries(1,no);
				long[] timeStamps = new long[1];
				timeStamps[0] = System.currentTimeMillis();
				outputData.setTimeStamps(timeStamps);
			}
			outputData.setName("OnlinePreprocessorOutputData");
			for(int c=0;c<no;c++){
				String varName = (String)outputNames.elementAt(c);
				int index = varNames.indexOf(varName);
//System.out.println("varName ="+varName+"  index=" +index); 
				String varTag = (String)varTags.elementAt(index);
				outputData.setVariableParameters(c,varTag,varName,"None");

				Variable varObj = outputData.getVarByIndex(c);
				Variable varObj1 = findVariable(varObjects,varName);
				varObj.setStatistics(varObj1.getStatistics());
				varObj.setUnit(varObj1.getUnit());
			}
		}else{
			rowBasedInputData = new DataSeries(1,varNames.size());  // n=# of varNames = number of inputs used in formulas
			for(int c=0;c<varNames.size();c++){
				String varName = (String)varNames.elementAt(c);
				int index = varNames.indexOf(varName);
				String varTag = (String)varTags.elementAt(index);
				rowBasedInputData.setVariableParameters(c,varTag,varName,"None");

				Variable varObj = rowBasedInputData.getVarByIndex(c);
				Variable varObj1 = findVariable(varObjects,varName);
				varObj.setStatistics(varObj1.getStatistics());
				varObj.setUnit(varObj1.getUnit());
			}
 			outputData = new DataSeries(1,no);
			for(int c=0;c<no;c++){
				String varName = (String)outputNames.elementAt(c);
				int index = varNames.indexOf(varName);
				String varTag = (String)varTags.elementAt(index);
				outputData.setVariableParameters(c,varTag,varName,"None");
			
				Variable varObj = outputData.getVarByIndex(c);
				Variable varObj1 = findVariable(varObjects,varName);
				varObj.setStatistics(varObj1.getStatistics());
				varObj.setUnit(varObj1.getUnit());
			}
		}	
	}

	private Variable findVariable(Vector vars, String varName){
		int n = vars.size();
		for(int i=0;i<n;i++){
			Variable varObj = (Variable)vars.elementAt(i);
			if(varName.equals(varObj.getName())){
				return varObj;
			}
		}
		return null;
	}

  /** Add the model to the formula list.*/	
	protected void addModelToFormula(Vector formulas, NolModel2 model){
		try{
			Formula2 newFormula = new Formula2();
			NolModel2 fm = (NolModel2)model.clone();
			newFormula.setFunction(fm);
			formulas.addElement(newFormula);
		}catch(Exception evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
		}
	}


	
/** Get the input buffer length for each input variable.
	MAYBE move to preprocessor later? */
 	protected void initializeInputBufferLength() {
		if(!hasTimeStamps){
			return;
		}
		inputBufferLength = new long[inputNames.size()];
		for(int	i=0;i<preprocessor.getNumberOfFormulas();i++){
			Formula2 fm = preprocessor.getFormula(i);
			long ibl = fm.getInputBufferLength();
			for(int j=0;j<inputNames.size();j++){
				String varName = (String)inputNames.elementAt(j);
				if(fm.hasVariable(varName)){
					// Take maximum buffer length
					if(inputBufferLength[j]<ibl){
						inputBufferLength[j] = ibl;
					}
				}
			}
		}
		// apply fudge factor to make sure buffer is long enough
		for(int i=0;i<inputBufferLength.length;i++) {
			inputBufferLength[i] *= 2;
		}
	}

/** Get the output buffer length for output data series.*/
 	protected void initializeOutputBufferLength() {
		INolModel2 model = getModel();
		Vector outputDelays = model.getOutputDelays();
		for(int i=0;i<outputDelays.size();i++){
  			long[] dls = (long[])outputDelays.elementAt(i);
			for(int j=0;j<dls.length;j++){
				if (dls[j] > outputBufferLength){
					outputBufferLength = dls[j];
				}
			}
		}
		// apply fudge factor to make sure buffer is long enough
		outputBufferLength *= 2;
	}

/** Get the name of this model. */
	@Override
	public String getName(){
		return name;
	}
	
/** Set the name of this model. */
	public void setName(String c){
		name = c;
	}	
	
/** Return the comment of this model.*/
	public String getComment(){
		return comment;
	}

/** Set the comment of this model.*/
	public void setComment(String c){
		comment = c;
	}

/** Get the status of this timestamps. */
	public boolean getHasTimeStamps(){
		return hasTimeStamps;
	}
	
/** Get the status of this timestamps. */
	public boolean hasTimeStamps(){
		return hasTimeStamps;
	}

/** Get the hasCode for this preprocessor.*/
	public int getItsHashCode(){
		return itsHashCode;
	}

	/** Return the names of variables.*/
	public Vector getVariableNames() {
		return varNames;
	}

	/** Return the number of variables.*/
	public int getNumberOfVariables() {
		return varNames.size();
	}

/** Return the tags of variables. */
	public Vector getVariableTags() {
		return varTags;
	}

/** Return the data series which contains the variable name using 
	the processor's own data series. This is not for online use.*/
	public DataSeries getDataSeriesFromVariableName(String varName){
		return getDataSeriesFromVariableName(inputDataBuffer, varName);
	}

/** Return the data series which contains the variable name from 
	a vector of possibilities.This is not for online use.*/
	public DataSeries getDataSeriesFromVariableName(Vector Data, String varName){
		for(int i=0;i<Data.size();i++){
			DataSeries ds = (DataSeries)Data.elementAt(i);
			int vIndex = ds.getVarIndexByName(varName);
			if(vIndex != -1){
				return ds;
			}
		}
		return null;
	}

	private void setResultToOutputs(Vector newDatas, long currentTime) throws MathException{
//System.out.println("setResultToOutputs currentTime = "+currentTime);
		DataSeries ds = null;
		for(int i=0;i<newDatas.size();i++){
			//System.out.println("At 1, i="+i+" name = "+((DataSeries)newDatas.elementAt(i)).toString());
			if(newDatas.elementAt(i).toString().equals("OnlinePreprocessorOutputData")){
				ds = (DataSeries)newDatas.elementAt(i);
				break;
			}//use fixed name for checking is not a good idea.
		}
		long[] ts = ds.getTimeStamps();
		int location1 = -1;
		for(int r=0;r<ts.length;r++) {
			if(currentTime==ts[r]) {
				location1 = r;
				break;
			}
		}
		ts = outputData.getTimeStamps();
		long expireTime = currentTime-outputBufferLength;
		if(ts[0]>0L && expireTime<ts[0]) {
			Matrix data = outputData.getDataMatrix();
			if(MAX_BUFFER_SIZE < data.getRows()+HISTORY_GROWTH_INCREMENT){
				Matrix newChunk = Matlib.zeros(HISTORY_GROWTH_INCREMENT,data.getCols());
				Matlib.appendRows(newChunk,data,data);
				Matlib.getPart(data, 0, 0, MAX_BUFFER_SIZE-1, data.getCols() - 1, data);
				newChunk.clear();
				long[] newTs = new long[MAX_BUFFER_SIZE];
				for(int r=0;r<MAX_BUFFER_SIZE-HISTORY_GROWTH_INCREMENT;r++){
					newTs[r+HISTORY_GROWTH_INCREMENT] = ts[r];
				}
				for(int r=0;r<HISTORY_GROWTH_INCREMENT;r++){
					newTs[r] = -1L; // indicates row not used (yet)
				}
				outputData.setTimeStamps(newTs);

			}else{
				Matrix newChunk = Matlib.zeros(HISTORY_GROWTH_INCREMENT,data.getCols());
				// insert the new rows at beginning of data matrix
				Matlib.appendRows(newChunk,data,data);
				newChunk.clear();
				long[] newTs = new long[ts.length+HISTORY_GROWTH_INCREMENT];
				for(int r=0;r<ts.length;r++){
					newTs[r+HISTORY_GROWTH_INCREMENT] = ts[r];
				}
				for(int r=0;r<HISTORY_GROWTH_INCREMENT;r++) {
					newTs[r] = -1L; // indicates row not used (yet)
				}
				outputData.setTimeStamps(newTs);
			}
		}
		ts = outputData.getTimeStamps();
		// Now insert the data into the history buffer
		// first locate the insertion point in this array (searching backwards since likely place is at the end!)
		int replaceRow = -1;
		int insertAt = -1;
		for(int r=ts.length-1;r>=0;r--) {
			if(currentTime==ts[r]) {
				replaceRow = r;
				break;
			} else if(currentTime>ts[r]) {
				insertAt=r;
				break;
			}
		}
//System.out.println("replaceRow= "+replaceRow);
//System.out.println("insertAt= "+insertAt);
//System.out.println("ts.length= "+ts.length);
		if(replaceRow != -1){ // replace the value in an existing row (rare)
			insertAt = replaceRow;
		} else { // shift timestamps and matrix toward zero to make room for insertion of current value
			for(int r=0;r<insertAt;r++){
				ts[r] = ts[r+1];
			}
			ts[insertAt] = currentTime;
			Matrix M = outputData.getDataMatrix();				
			for(int r=0;r<insertAt;r++){
				for(int c=0;c<M.getCols();c++){
					M.set(r,c,M.get(r+1,c));
				}
			}
		}
		for(int i=0;i<outputNames.size();i++){
 			String varName = (String)outputNames.elementAt(i);
			int index1 = outputData.getVarIndexByName(varName);
			int index2 = ds.getVarIndexByName(varName);
			try{
				outputData.setValueAt(insertAt,index1,ds.getValueAt(location1,index2));
			}catch(MathException evt){
				System.err.println("Could not find output variable");
				evt.printStackTrace();
			}
		}
	}

	private void setResultToOutputs(Vector newDatas){
		DataSeries ds = null;
		if(hasTimeStamps){
			for(int i=0;i<newDatas.size();i++){
				//System.out.println("At 1, i="+i+" name = "+((DataSeries)newDatas.elementAt(i)).toString());
				if(newDatas.elementAt(i).toString().equals("OnlinePreprocessorOutputData")){
					ds = (DataSeries)newDatas.elementAt(i);
					break;
				}//use fixed name for checking is not a good idea.
			}
		}else{
			ds = (DataSeries)newDatas.elementAt(0);
		}
		for(int i=0;i<outputNames.size();i++){
 			String varName = (String)outputNames.elementAt(i);
			int index1 = outputData.getVarIndexByName(varName);
			int index2 = ds.getVarIndexByName(varName);
			try{
				outputData.setValueAt(0,index1,ds.getValueAt(0,index2));
			}catch(MathException evt){
				System.err.println("Could not find output variable");
				evt.printStackTrace();
			}
		}
	}

/** Load the model and formulas from a file. This is not recommended. 
	This supposes the file is in current directory.*/ 
	public void loadModel(String fileName)throws
	FileNotFoundException,IOException,StreamCorruptedException, 
	OptionalDataException,ClassNotFoundException{
		loadModel(fileName,null);
	}

/** Load the model and formulas from a file.*/ 
	public void loadModel(String fileName, String directory) throws
	FileNotFoundException,IOException,StreamCorruptedException, 
	OptionalDataException,ClassNotFoundException{
		try{
			File sourceFile;
			if(directory==null)
				sourceFile = new File(fileName);	
			else
				sourceFile = new File(directory,fileName);
			FileInputStream fis = new FileInputStream(sourceFile); 
			GZIPInputStream gzis = new GZIPInputStream(fis);   
			ObjectInputStream in = new ObjectInputStream(gzis); 
			VersionManagerForOnlineProcessor ver  = (VersionManagerForOnlineProcessor)in.readObject();
			OnlineProcessor processor = ver.getProcessor();
			copyToThis(processor);
			in.close(); 
		}catch (StreamCorruptedException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}catch (OptionalDataException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}catch (FileNotFoundException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}catch (IOException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}catch (ClassNotFoundException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}
		
		

	}

	public void copyToThis(OnlineProcessor processor) {
		name = processor.name;
		comment = processor.comment;
		varNames = processor.varNames;
		varTags = processor.varTags;
		inputNames = processor.inputNames;
		outputNames = processor.outputNames;
		inputBufferLength = processor.inputBufferLength;
		preprocessor = processor.preprocessor;
		hasTimeStamps = processor.hasTimeStamps;
		dateTimeFormat = processor.dateTimeFormat;
		inputDataBuffer = processor.inputDataBuffer;
		outputData = processor.outputData;
		rowBasedInputData = processor.rowBasedInputData;
		itsHashCode = hashCode();
		itsEventListeners = new Vector();
		outputData.initVarTransient();
//System.out.println("load time= " + outputData.getTimeStamps().length);
		if(rowBasedInputData != null)
			rowBasedInputData.initVarTransient();
		for(int i=0;i<inputDataBuffer.size();i++){
			DataSeries ds = (DataSeries)inputDataBuffer.elementAt(i);
			ds.initVarTransient();
		}
		outputBufferLength = processor.outputBufferLength;

		if(processor.decFormatLocalString != null){
			decFormatLocalString = processor.decFormatLocalString;
		}else{
			decFormatLocalString = "English";
		}
			
	}

/** Calculate the model for time based model.*/
	public void calculateOutputAtTime(String time) throws MathException{ 
		if(!hasTimeStamps){
			throw new MathException("Call time-based method from row-based model.");
			// MK -- Illegal call, should signal a run-time error
		}
//System.out.println("calculateOutputAtTime get here 2");
		try {
			INolModel2 model = getModel();
			if(model.isRecursiveModel()){
//System.out.println("calculateOutputAtTime get here 3");
				long currentTime = dateTimeFormat.parse(time).getTime();
//System.out.println("calculateOutputAtTime currentTime="+currentTime);
				DataSeries ds = (DataSeries)outputData.clone();
//System.out.println("calculateOutputAtTime before setting outputData="+outputData.toStringForSave(1,new SimpleDateFormat("MM/dd/yy"),new SimpleDateFormat("H:mm:ss")));
				setCurrentTimeStamp(ds,currentTime);
				Vector ioData = (Vector) inputDataBuffer.clone();
				ioData.insertElementAt(ds,0);
				Vector processedData = new Vector();
//System.out.println("calculateOutputAtTime ioData.size="+ioData.size());
//System.out.println("calculateOutputAtTime after outputData="+ds.toStringForSave(1,new SimpleDateFormat("MM/dd/yy"),new SimpleDateFormat("H:mm:ss")));

				preprocessor.applyPreprocessor(ioData, processedData);
//DataSeries ds1 = (DataSeries)processedData.elementAt(0);
//System.out.println("calculateOutputAtTime calculated outputData="+ds1.toStringForSave(1,new SimpleDateFormat("MM/dd/yy"),new SimpleDateFormat("H:mm:ss")));
				setResultToOutputs(processedData,currentTime);
			}else{
				long currentTime = dateTimeFormat.parse(time).getTime();
				long[] ts = outputData.getTimeStamps();
				ts[0] = currentTime;
				outputData.setTimeStamps(ts);
				Vector ioData = (Vector) inputDataBuffer.clone();
				ioData.insertElementAt(outputData,0);
				Vector processedData = new Vector();
				preprocessor.applyPreprocessor(ioData, processedData);
				setResultToOutputs(processedData);
			}
		} catch (Exception e) {
			System.out.println("Exception is "+e.getMessage());
			e.printStackTrace();
		}
   	}
/** Set the time for calculation to the new output data series.*/
	protected void setCurrentTimeStamp(DataSeries ds, long currentTime){
		long[] ts = ds.getTimeStamps();
		// Now insert the data into the history buffer
		// first locate the insertion point in this array (searching backwards since likely place is at the end!)
		int replaceRow = -1;
		int insertAt = -1;
		for(int r=ts.length-1;r>=0;r--) {
			if(currentTime==ts[r]) {
		// found the location with the same time stamp and don't need to do anything!)
				replaceRow = r;
				return;
			} else if(currentTime>ts[r]) {
				insertAt=r;
				break;
			}
		}
//System.out.println("insertAt ="+insertAt);
//System.out.println("ts.length ="+ts.length);

		if(insertAt == -1){	   //run the model at earlier time, then need to reset the output data series.
			Matrix M = ds.getDataMatrix();				
			for(int r=ts.length-1;r>=0;r--) {
				ts[r] = -1L;
				for(int j=0;j<M.getCols();j++){
					M.set(r,j,Double.NaN);
				}
			}
			ts[ts.length-1] = currentTime;
			for(int j=0;j<M.getCols();j++){
				M.set(ts.length-1,j,0.0);
			}
		}else{
			for(int r=0;r<insertAt;r++){
				ts[r] = ts[r+1];
			}
			ts[insertAt] = currentTime;
			Matrix M = ds.getDataMatrix();				
			for(int r=0;r<insertAt;r++){
				for(int c=0;c<M.getCols();c++){
					M.set(r,c,M.get(r+1,c));
				}
			}
			for(int c=0;c<M.getCols();c++){
				M.set(insertAt,c,0.0);
			}
		}
	}
/** Calculate the model for row based model.*/
	public void calculateOutputForRow() throws MathException{ 
		if(hasTimeStamps){
			throw new MathException("Call row-based method from time-based model.");
			// MK -- Illegal call, should signal a run-time error
		} 
		try {
			Vector ioData =  new Vector();
			ioData.addElement(rowBasedInputData);
			Vector processedData = new Vector();
			preprocessor.applyPreprocessor(ioData, processedData);
			setResultToOutputs(processedData);
		} catch (Exception e) {
			System.out.println("Exception is "+e.getMessage());
			e.printStackTrace();
		}
	}

/** Get the number of inputs.*/
	public int getNumberOfInputs(){
		return inputNames.size();
	}

/** Get input variables' names by index of the array */
	public String getInputName(int index) {
		String vName = (String)inputNames.elementAt(index);
		return vName;
	}

/** Get input variables' names */
	public String[] getInputNames (){
		int n=inputNames.size();
		String[] names = new String[n];
		for(int i=0;i<n;i++){
			String vName = (String)inputNames.elementAt(i);
			names[i]=vName;
		}
		return names;
	}


/** Get input variables' names by index of the array */
	public String getInputTag(int index) {
		String vName = (String)inputNames.elementAt(index);
		int i = varNames.indexOf(vName);
		String varTag = (String)varTags.elementAt(i);
		return varTag;
	}

/** Get input variables' tags */
	public String[] getInputTags(){
		int n=inputNames.size();
		String[] tags = new String[n];
		for(int i=0;i<n;i++){
			String vName = (String)inputNames.elementAt(i);
			int index = varNames.indexOf(vName);
			String varTag = (String)varTags.elementAt(index);
			tags[i]=varTag;
		}
		return tags;
	}

/** Get the number of outputs.*/
	public int getNumberOfOutputs(){
		return outputNames.size();
	}

/** Get output variables' names by index of the array */
	public String getOutputName (int index){
		String vName = (String)outputNames.elementAt(index);
		return vName;
	}

/** Get output variables' names */
	public String[] getOutputNames (){
		int n=outputNames.size();
		String[] names = new String[n];
		for(int i=0;i<n;i++){
			String vName = (String)outputNames.elementAt(i);
			names[i]=vName;
		}
		return names;
	}

/** Get output variables' names by index of the array */
	public String getOutputTag (int index){
		String vName = (String)outputNames.elementAt(index);
		int i = varNames.indexOf(vName);
		String varTag = (String)varTags.elementAt(i);
		return varTag;
	}

/** Get output variables' tags */
	public String[] getOutputTags (){
		int n=outputNames.size();
		String[] tags = new String[n];
		for(int i=0;i<n;i++){
			String vName = (String)outputNames.elementAt(i);
			int index = varNames.indexOf(vName);
			String varTag = (String)varTags.elementAt(index);
			tags[i]=varTag;
		}
		return tags;
	}

/** Set the time format string for time based model. e.g."yyyyy.MMMMM.dd hh:mm" */
	public void setTimeFormat(String timeFormat)throws MathException{
		if(!hasTimeStamps){
			throw new MathException("Call time-based method from row-based model.");
			// MK -- Illegal call, should signal a run-time error
		}
		dateTimeFormat = new SimpleDateFormat(timeFormat);
	}

/** Set the decimal format string */
	public void setDecimalFormatLocalString(String form)throws MathException{
		decFormatLocalString = form;
	}

/** Set the input value by variable number and value */
	public void setInputAtTimeByIndex(int inNumber, double val, String time)
		throws ParseException, MathException{
		if(!hasTimeStamps){
			throw new MathException("Call time-based method from row-based model.");
			// MK -- Illegal call, should signal a run-time error
		}
//System.out.println("setting input at "+time+" with index="+inNumber);
		int inputNumber = inNumber;
		String varName = (String)inputNames.elementAt(inputNumber);
		setInputAtTimeByName(varName, val, time);
	}

/** Set the input value by variable tag and value */
	public void setInputAtTimeByTag(String varTag, double val, String time)
		throws ParseException, MathException{
		if(!hasTimeStamps){
			throw new MathException("Call time-based method from row-based model.");
			// MK -- Illegal call, should signal a run-time error
		}
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		setInputAtTimeByName(varName, val, time);
	}

/** Set the input value by variable name and value */
	public void setInputAtTimeByName(String varName, double val, String time) throws ParseException, MathException{
		if(!hasTimeStamps){
			throw new MathException("Call time-based method from row-based model.");
			// MK -- Illegal call, should signal a run-time error
		}
		int inputNumber = inputNames.indexOf(varName);
		double value = val;
		long currentTime = dateTimeFormat.parse(time).getTime();
//System.out.println("setting input at "+currentTime);
		long expireTime = currentTime-inputBufferLength[inputNumber];
		// To support asynchonous data acquisition, each variable has its own data series
		DataSeries ds = getDataSeriesFromVariableName(varName);
		if(ds == null){
			return;
		}
		long[] ts = ds.getTimeStamps();
		// We have to grow the history if it is full (ts[0]>0L) 
		// and we need data at times earlier than the first entry (expireTime<ts[0])
		if(ts[0]>0L && expireTime<ts[0]) {
			Matrix data = ds.getDataMatrix();
			if(MAX_BUFFER_SIZE < data.getRows()+HISTORY_GROWTH_INCREMENT){
				Matrix newChunk = Matlib.zeros(HISTORY_GROWTH_INCREMENT,data.getCols());
				Matlib.appendRows(newChunk,data,data);
				Matlib.getPart(data, 0, 0, MAX_BUFFER_SIZE-1, data.getCols() - 1, data);
				newChunk.clear();
				long[] newTs = new long[MAX_BUFFER_SIZE];
				for(int r=0;r<MAX_BUFFER_SIZE-HISTORY_GROWTH_INCREMENT;r++){
					newTs[r+HISTORY_GROWTH_INCREMENT] = ts[r];
				}
				for(int r=0;r<HISTORY_GROWTH_INCREMENT;r++){
					newTs[r] = -1L; // indicates row not used (yet)
				}
				ds.setTimeStamps(newTs);

			}else{
				Matrix newChunk = Matlib.zeros(HISTORY_GROWTH_INCREMENT,data.getCols());
				// insert the new rows at beginning of data matrix
				Matlib.appendRows(newChunk,data,data);
				newChunk.clear();
				long[] newTs = new long[ts.length+HISTORY_GROWTH_INCREMENT];
				for(int r=0;r<ts.length;r++){
					newTs[r+HISTORY_GROWTH_INCREMENT] = ts[r];
				}
				for(int r=0;r<HISTORY_GROWTH_INCREMENT;r++){
					newTs[r] = -1L; // indicates row not used (yet)
				}
				ds.setTimeStamps(newTs);
			}
		}
		ts = ds.getTimeStamps();
		// Now insert the data into the history buffer
		// first locate the insertion point in this array (searching backwards since likely place is at the end!)
		int replaceRow = -1;
		int insertAt = -1;
		for(int r=ts.length-1;r>=0;r--) {
			if(currentTime==ts[r]) {
				replaceRow = r;
				break;
			} else if(currentTime>ts[r]) {
				insertAt=r;
				break;
			}
		}
		if(replaceRow>-1){ // replace the value in an existing row (rare)
			ds.setValueAt(replaceRow,0,value);
		} else { // shift timestamps and matrix toward zero to make room for insertion of current value
			for(int r=0;r<insertAt;r++){
				ts[r] = ts[r+1];
			}
			ts[insertAt] = currentTime;
			Matrix M = ds.getDataMatrix();				
			for(int r=0;r<insertAt;r++){
				M.set(r,0,M.get(r+1,0));
			}
			M.set(insertAt,0,value);
		}
	}


/** Set the value of one input variable. */	
	public void setInputForRowByIndex(int inputNumber, double value) throws MathException{
		if(hasTimeStamps){
			throw new MathException("Call row-based method from time-based model.");
			// MK -- Illegal call, should signal a run-time error
		} 
		int index = inputNumber;
		String varName = (String)inputNames.elementAt(index);
		int cols = rowBasedInputData.getVarIndexByName(varName);
		rowBasedInputData.setValueAt(0,cols,value);
	}

/** Set the value of one input variable. */	
	public void setInputForRowByTag(String varTag, double value) throws MathException{
		if(hasTimeStamps){
			throw new MathException("Call row-based method from time-based model.");
			// MK -- Illegal call, should signal a run-time error
		} 
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		setInputForRowByName(varName, value);
	}

/** Set the value of one input variable. */	
	public void setInputForRowByName(String varName, double value) throws MathException{
		if(hasTimeStamps){
			throw new MathException("Call row-based method from time-based model.");
			// MK -- Illegal call, should signal a run-time error
		} 
		int cols = rowBasedInputData.getVarIndexByName(varName);
		if(cols == -1){
			throw new MathException("Wrong variable name.");
		}
		rowBasedInputData.setValueAt(0,cols,value);
	}

/** Get the current value of one output variable. */	
	public double getCurrentOutputByIndex(int inputNumber) throws MathException {
		int index = inputNumber;
		String varName = (String)outputNames.elementAt(index);
		int cols = outputData.getVarIndexByName(varName);
		return outputData.getValueAt(0,cols);
	}

/** Get the current value of one output variable. */	
	public double getCurrentOutputByName(String varName) throws MathException{
		int cols = outputData.getVarIndexByName(varName);
		return outputData.getValueAt(0,cols);
	}

/** Get the current value of one output variable. */	
	public double getCurrentOutputByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getCurrentOutputByName(varName);
	}

/** Get the value of one output variable.at given time */ 	
	public double getOutputAtTimeByIndex(int inputNumber, String time) throws MathException , ParseException{
		String varName = (String)outputNames.elementAt(inputNumber);
		int cols = outputData.getVarIndexByName(varName);
		long[] ts = outputData.getTimeStamps();
		int location1 = 0;
		long currentTime = dateTimeFormat.parse(time).getTime();
		for(int r=0;r<ts.length;r++) {
			if(currentTime==ts[r]) {
				location1 = r;
				break;
			}
		}
		return outputData.getValueAt(location1,cols);
	}

/** Get the value of one output variable.at given time */ 	
	public double getOutputAtTimeByName(String varName, String time) throws MathException, ParseException{
		int cols = outputData.getVarIndexByName(varName);
		long[] ts = outputData.getTimeStamps();
		int location1 = 0;
		long currentTime = dateTimeFormat.parse(time).getTime();
		for(int r=0;r<ts.length;r++) {
			if(currentTime==ts[r]) {
				location1 = r;
				break;
			}
		}
		return outputData.getValueAt(location1,cols);
	}

/** Get the value of one output variable.at given time */ 	
	public double getOutputAtTimeByTag(String varTag, String time) throws MathException, ParseException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		int cols = outputData.getVarIndexByName(varName);
		long[] ts = outputData.getTimeStamps();
		int location1 = 0;
		long currentTime = dateTimeFormat.parse(time).getTime();
		for(int r=0;r<ts.length;r++) {
			if(currentTime==ts[r]) {
				location1 = r;
				break;
			}
		}
		return outputData.getValueAt(location1,cols);
	}
						
/*	public String toStringForTest(){
		String s = "";
		if(hasTimeStamps){
			for(int i=0;i<inputDataBuffer.size();i++){
				DataSeries ds = (DataSeries)inputDataBuffer.elementAt(i);
				s = s+ds.toStringForSave(1,new SimpleDateFormat("MM/dd/yy"),new SimpleDateFormat("H:mm:ss"))+"\n";
			}
			s = s + outputData.toStringForSave(1,new SimpleDateFormat("MM/dd/yy"),new SimpleDateFormat("H:mm:ss"));
		}else{
			s = s + rowBasedInputData.toStringForSave(1,new SimpleDateFormat("MM/dd/yy"),new SimpleDateFormat("H:mm:ss"))+"\n";
			s = s + outputData.toStringForSave(1,new SimpleDateFormat("MM/dd/yy"),new SimpleDateFormat("H:mm:ss"));
		}
		return s;
	}
  */
/** Get variable object from variable name.*/
	private Variable getVariableByName(String varName) throws MathException{
		if(hasTimeStamps){
			int index = inputNames.indexOf(varName);
			if(index != -1){
				DataSeries ds = getDataSeriesFromVariableName(varName);
				Variable varObj = ds.getVarByName(varName); 
				return varObj;
			}else{
				if(outputNames.indexOf(varName) == -1){
					throw new MathException("Wrong variable name.");
				}
				Variable varObj = outputData.getVarByName(varName); 
				return varObj;
			}
		}else{
			Variable varObj = rowBasedInputData.getVarByName(varName);
			if(varObj == null){
				throw new MathException("Wrong variable name.");	
			}
			return varObj;
		}
	}

/** Get variable statistics from variable name.*/
	private double[] getVarStatisticsByName(String varName) throws MathException{
		Variable varObj = getVariableByName(varName);
		if(varObj == null) {
			throw new MathException("Wrong variable name.");	
		}
		double[] statistics = varObj.getStatistics();
		return statistics;
	}

/** Get the data max from variable name.*/
	public double getMaxValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[8];
	}

/** Get the data max from variable tag.*/
	public double getMaxValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getMaxValueByName(varName);
	}

/** Get the data min from variable name.*/
	public double getMinValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[7];
	}

/** Get the data min from variable tag.*/
	public double getMinValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getMinValueByName(varName);
	}

/** Get the data mean from variable name.*/
	public double getMeanValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[0];
	}

/** Get the data mean from variable tag.*/
	public double getMeanValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getMeanValueByName(varName);
	}

/** Get the data median from variable name.*/
	public double getMedianValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[1];
	}

/** Get the data median from variable tag.*/
	public double getMedianValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getMedianValueByName(varName);
	}

/** Get the data sum from variable name.*/
	public double getSumValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[9];
	}

/** Get the data sum from variable tag.*/
	public double getSumValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getSumValueByName(varName);
	}

/** Get the data std from variable name.*/
	public double getSTDValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[2];
	}

/** Get the data std from variable tag.*/
	public double getSTDValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getSTDValueByName(varName);
	}

/** Get the data variance from variable name.*/
	public double getVarianceValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[3];
	}

/** Get the data variance from variable tag.*/
	public double getVarianceValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getVarianceValueByName(varName);
	}

/** Get the data kurt from variable name.*/
	public double getKurtValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[4];
	}

/** Get the data kurt from variable tag.*/
	public double getKurtValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getKurtValueByName(varName);
	}

/** Get the data skew from variable name.*/
	public double getSkewValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[5];
	}

/** Get the data skew from variable tag.*/
	public double getSkewValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getSkewValueByName(varName);
	}

/** Get the data range from variable name.*/
	public double getRangeValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[6];
	}

/** Get the data range from variable tag.*/
	public double getRangeValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getRangeValueByName(varName);
	}

/** Get the input variable delays from variable name.*/
	public long[] getInputDelayByName(String varName) throws MathException{
		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();
		Vector modelInputs = model.getInputVarNames();
		Vector modelInputDelays = model.getInputDelays();
		int index = modelInputs.indexOf(varName);
		if(index == -1){
			throw new MathException("Wrong variable name.");
		}
		long[] delays = (long[]) modelInputDelays.elementAt(index);
		return delays;
	}

/** Get the input variable delays from variable tag.*/
	public long[] getInputDelayByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getInputDelayByName(varName);
	}

/** Get the formula list.*/
	public String getFormulas() throws MathException{
		Vector formulaList = preprocessor.getFormulas();
		int count = formulaList.size();
		String formulaStrings = "";
		for(int i=0;i<count;i++){
			formulaStrings += formulaList.elementAt(i).toString() + "\n";
		}
		return formulaStrings;
	}

/** Clear the buffer for time based data.*/
	public void clearDataBuffer() throws MathException{
		if(hasTimeStamps){
			int size = inputDataBuffer.size();
			for(int i=0;i<size;i++){
				DataSeries ds = (DataSeries)inputDataBuffer.elementAt(i);
				long[] ts = ds.getTimeStamps();
				for(int j=0;j<ts.length;j++){
					ts[j] = -1L;
					ds.setValueAt(j,0,Double.NaN);
				}
			}
		}
	}

/** Return the neural net model contained in this processor.*/
	public INolModel2 getModel(){
		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();
		return model;
	}		

	private String display(Matrix x){

		String s ="";
		for(int r=0;r<x.getRows();r++)	{
		 	for(int c=0;c<x.getCols();c++){
		 		s = s + "	" + x.get(r,c);
		 	}
			s = s +"\n";
		}
		return s;
	}

/** Return the input number of ensemble model. This is an internal method used for checking*/
	public int getNumberOfModelInputs(){
		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();
		EnsembleModel ensemble = (EnsembleModel)model.getModel();
		return ensemble.getNin();
	}

/** Return the output number of ensemble model. This is an internal method used for checking*/
	public int getNumberOfModelOutputs(){
		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();
		EnsembleModel ensemble = (EnsembleModel)model.getModel();
		return ensemble.getNout();
	}

/** Update max and min of input and outputs after re-train */
	public void updateMaxAndMinValues(Matrix X, Matrix Y, boolean newTraining) {
		// Update max and min values for input
		for (int c = 0; c < X.getCols(); c++) {
			double min = Double.POSITIVE_INFINITY;
			double max = Double.NEGATIVE_INFINITY;
			for (int r = 0; r < X.getRows(); r++) {
				double v = X.get(r, c);
				if (!Double.isNaN(v)) {
					if (min > v) { 
						min = v; 
					}
					if (max < v) { 
						max = v; 
					}
				}
			}
			try {
				String varName = (String)inputNames.elementAt(c);
				double[] statistics = getVarStatisticsByName(varName);
				if (newTraining || statistics[7] > min) { 
					statistics[7] = min; 
				}
				if (newTraining || statistics[8] < max) { 
					statistics[8] = max; 
				}
			} catch (Throwable t) {
				// do nothing
			}
		}
		// Update max and min values for output
		for (int c = 0; c < Y.getCols(); c++) {
			double min = Double.POSITIVE_INFINITY;
			double max = Double.NEGATIVE_INFINITY;
			for (int r = 0; r < Y.getRows(); r++) {
				double v = Y.get(r, c);
				if (!Double.isNaN(v)) {
					if (min > v) { 
						min = v; 
					}
					if (max < v) { 
						max = v; 
					}
				}
			}
			try {
				String varName = (String)outputNames.elementAt(c);
				double[] statistics = getVarStatisticsByName(varName);
				if (newTraining || statistics[7] > min) { 
					statistics[7] = min; 
				}
				if (newTraining || statistics[8] < max) { 
					statistics[8] = max; 
				}
			} catch (Throwable t) {
				// do nothing
			}
		}
	}

/** Retrain the model in this processor.*/
	public void trainModel(Vector modelListeners, Matrix X, Matrix Y, double timeInMilli, boolean autoStop, boolean newTraining, boolean display) throws MathException{


/*		debug("get inside the train model");
		String debugString = "The timeInMilli ="+timeInMilli+"\n"+	"The autoStop ="+autoStop+	"\n"+ "The newTraining ="+newTraining +"\n";
		debugString = debugString + "\nX.getRows()="+X.getRows()+"\nY.getRows()="+Y.getRows()+"\nX.getCols()="+	X.getCols()+"\nY.getCols()="+Y.getCols()+"\n";
		debug(debugString);
		debug("display="+display);
System.out.println("online processor trainModel");
String debugString = "The timeInMilli ="+timeInMilli+"\n"+	"The autoStop ="+autoStop+	"\n"+ "The newTraining ="+newTraining +"\n";
debugString = debugString + "\nX.getRows()="+X.getRows()+"\nY.getRows()="+Y.getRows()+"\nX.getCols()="+	X.getCols()+"\nY.getCols()="+Y.getCols()+"\n";
debug(debugString);
System.out.println("online processor trainModel display="+display);
  */

		if(X.getRows() != Y.getRows()){
			throw new MathException("Input and Output don't have the same number of samples.");
		}
		if(X.getRows() <10){
			throw new MathException("There is not enough data for training.");
		}

		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();
		EnsembleModel ensemble = (EnsembleModel)model.getModel();
		int nin = ensemble.getNin();
		int nout = ensemble.getNout();

		if(X.getCols() != nin){
			throw new MathException("The input matrx does not match the model input.");
		}
		if(Y.getCols() != nout){
			throw new MathException("The output matrx does not match the model input.");
		}
		if(newTraining) {
			ensemble.clearModels();
		}
		updateMaxAndMinValues(X, Y, newTraining);
		ensemble.setTrainingTime((long)timeInMilli);  
		ensemble.useAutomaticStopping(autoStop);
		ensemble.removeAllListeners();
		ensemble.addListener(this);
		NolModelTrainThread trainerThread = new NolModelTrainThread(ensemble);
		Thread trainingthread = new Thread(trainerThread);
		int prior = trainingthread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY) {
			prior = Thread.MIN_PRIORITY;
		}
		trainingthread.setPriority(prior);
		trainerThread.setInput1(X);
		trainerThread.setOutput1(Y);

		if(display){
			if(modelListeners == null){
				OnlineModelListener onlineModelListener = new OnlineModelListener(this, display);
				ensemble.addListener(onlineModelListener);
				NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
				console.setModel1TrainInput(X);
				console.setModel1TrainOutput(Y);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100,100,750,500);
				console.setReady(false);
				console.setVisible(true);
				console.toFront();	
			}else{
				boolean found = false;
				OnlineModelListener foundListener = null;
				for (int i=0;i<modelListeners.size();i++){
					EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
					ensemble.addListener(listener);
					if(listener instanceof OnlineModelListener && !found){
						found = true;
						foundListener = (OnlineModelListener) listener;
					}
				}
				if (!found) {
					foundListener = new OnlineModelListener(this, display);
					ensemble.addListener(foundListener);
				}
				NolOnlineConsoleFrame console = foundListener.getOnlineConsole();
				console.setModel1TrainInput(X);
				console.setModel1TrainOutput(Y);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100, 100, 750, 500);
				console.setReady(false);
				console.setVisible(true);
				console.toFront();
			}
		}else{
			if(modelListeners != null){
				for (int i=0;i<modelListeners.size();i++){
					EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
					ensemble.addListener(listener);
				}
			}
		}
		trainingthread.start();
	}
	
/** Retrain the model in this processor. The data is stored in two ascii file.*/
	public void trainModelFromFile(Vector modelListeners, String inputFileName, String outputFileName, double timeInMilli, boolean autoStop, boolean newTraining, boolean display)
	throws IOException, MathException
	{
/*		debug("get inside the trainModelFromFile\n");
		debug("inputFileName="+inputFileName+"\n");
		debug("outputFileName="+outputFileName+"\n");
*/
//		try{
		Matrix X = Matrix.readFromFile(inputFileName);
		Matrix Y = Matrix.readFromFile(outputFileName);
		trainModel(modelListeners, X, Y,timeInMilli,autoStop,newTraining,display);  
/*		}catch (Exception e){
			e.printStackTrace();
			debug("exception="+e.toString());
		}
*/	}

/** Retrain the model in this processor. The data is stored in data series file format.*/
	public void trainModelFromFile(Vector modelListeners, String[] dataSeriesFileNames, double timeInMilli, boolean autoStop, boolean newTraining, boolean display) throws MathException{
/*		debug("get inside the trainModelFromFiles");
		String debugString = "";
		for(int i=0;i<dataSeriesFileNames.length;i++){
			debugString = debugString + "file name = "+ dataSeriesFileNames[i]+"\n";
		}
		debugString = debugString + "The timeInMilli ="+timeInMilli+"\n"+	"The autoStop ="+autoStop+	"\n"+ "The newTraining ="+newTraining +"\n";
		debug(debugString);
  */
		
		Vector retraindataSeries = new Vector();
		for(int i=0;i<dataSeriesFileNames.length;i++){
			String dsFileName = dataSeriesFileNames[i];
			DataSeries ds = new DataSeries();
			ds.setDataSource(preprocessor);
			ds.Load(dsFileName, 0);
			retraindataSeries.addElement(ds);
		}
		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();

		Matrix X = Matlib.createMatrix();
		Matrix Y = Matlib.createMatrix();
		model.prepareTrainingSetFromDataSeries(retraindataSeries,X,Y);
		trainModel(modelListeners, X, Y,timeInMilli,autoStop,newTraining,display);  
	}

	private void getModelStatistics(EnsembleModel ensemble){ 
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();
		testRMSE = new double[nout];
		testCORR = new double[nout];
		trainRMSE = new double[nout];
		trainCORR = new double[nout];
		modelRateValue =0;
		for(int j=0;j<nout;j++) {
			testRMSE[j] = 0.0;
			testCORR[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters VP = submodel.testingResults;
				testRMSE[j] += VP.rmse.get(j);
				testCORR[j] += VP.corrcoef.get(j);
				VP = submodel.trainingResults;
				trainRMSE[j] += VP.rmse.get(j);
				trainCORR[j] += VP.corrcoef.get(j);
			}
			testRMSE[j] /= ensembleSize;
			testCORR[j] /= ensembleSize; 
			trainRMSE[j] /= ensembleSize;
			trainCORR[j] /= ensembleSize; 
		}
		for(int i=0;i<nout;i++) {
			modelRateValue = modelRateValue+testCORR[i];
		}
		modelRateValue = modelRateValue/nout;
	}


/** Get the model rate after the retraining*/
	public double getModelRate() throws MathException {
//System.out.println("online processor getModelRate retrain ="+ retrained);
		if(!retrained){
			throw new MathException("The Model is not Retrained!");
		}
		return modelRateValue;
	}

/** Get the testing RMSE after the retraining*/
	public double[] getTestRmse() throws MathException {
		if(!retrained) {
			throw new MathException("The Model is not Retrained!");
		}
		return testRMSE;
	}

/** Get the training RMSE after the retraining*/
	public double[] getTrainingRmse() throws MathException {
		if(!retrained) {
			throw new MathException("The Model is not Retrained!");
		}
		return trainRMSE;
	}

/** Get the testing correlation value after the retraining*/
	public double[] getTestCorr() throws MathException {
		if(!retrained) {
			throw new MathException("The Model is not Retrained!");
		}
		return testCORR;
	}

/** Get the training correlation value after the retraining.*/
	public double[] getTrainingCorr() throws MathException {
		if(!retrained) {
			throw new MathException("The Model is not Retrained!");
		}
		return trainCORR;
	}

	public void completeTraining(){
		retrained = true;
		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();
		EnsembleModel ensemble = (EnsembleModel)model.getModel();
		getModelStatistics(ensemble);
	}

	@Override
	public void modelTrained(EnsembleModelEvent e) {}
	@Override
	public synchronized void modelAdded(EnsembleModelEvent e) {}
	@Override
	public void modelRemoved(EnsembleModelEvent e){}
/** Get the interface method. Called by the trainer.*/
	@Override
	public void trainingComplete(EnsembleModelEvent e){
//System.out.println("online processor training complete and set retrain = true");
		retrained = true;
		getModelStatistics(e.getEnsembleModel());
	}


	  Frame errorFrame;
	  TextArea errorTA;
	  private void debug (String displayString) {
		if (errorFrame == null) {
		  errorFrame = new Frame ("Processor Errors");
		  errorFrame.add (errorTA = new TextArea ());
		}
		errorTA.append (displayString);
		errorFrame.setSize (600, 400);
		errorFrame.setVisible (true);
	  }


/** Get input variables' unit by index of the array */
	public String getInputUnit(int index) {
		try{
			String vName = (String)inputNames.elementAt(index);
			Variable varObj = getVariableByName(vName);
			return varObj.getUnit();
		} catch (MathException ie){	  }
		return "";
	}


/** Get output variables' unit by index of the array */
	public String getOutputUnit(int index) {
		try{
			String vName = (String)outputNames.elementAt(index);
			Variable varObj = getVariableByName(vName);
			return varObj.getUnit();
		} catch (MathException ie){  }
		return "";
	}

/** Get input variables' units */
	public String[] getInputUnits (){
		int n=inputNames.size();
		String[] units = new String[n];
		try{
			for(int i=0;i<n;i++){
				String vName = (String)inputNames.elementAt(i);
				Variable varObj = getVariableByName(vName);
				units[i] = varObj.getUnit();
			}
		} catch (MathException ie){ 
			for(int i=0;i<n;i++){
				units[i] = "none";
			}
		}
		return units;
	}

/** Get output variables' units */
	public String[] getOutputUnits (){
		int n=outputNames.size();
		String[] units = new String[n];
		try{
			for(int i=0;i<n;i++){
				String vName = (String)outputNames.elementAt(i);
				Variable varObj = getVariableByName(vName);
				units[i] = varObj.getUnit();
			}
		} catch (MathException ie){ 
			for(int i=0;i<n;i++){
				units[i] = "none";
			}
		}
		return units;
	}

/** Set the variable value by variable name and value */
	public void setVariableValueAtTimeByName(String varName, double value, String time) throws ParseException, MathException{
		if(!hasTimeStamps){
			throw new MathException("Call time-based method from row-based model.");
			// MK -- Illegal call, should signal a run-time error
		}
		INolModel2 model = getModel();
		DataSeries ds = getDataSeriesFromVariableName(varName);
		if(ds != null){
			setInputAtTimeByName(varName,value,time);
			return;
		}else{
			if(!model.isRecursiveModel()) {
				throw new MathException("Can not set output value for non-recursive model.");
			}
			int vIndex = outputData.getVarIndexByName(varName);
			if(vIndex == -1) {
				throw new MathException("Wrong variable name.");
			}
		}
		long currentTime = dateTimeFormat.parse(time).getTime();
//System.out.println("setting input at "+currentTime);
//System.out.println("outputBufferLength= "+outputBufferLength);
		long expireTime = currentTime-outputBufferLength;
		long[] ts = outputData.getTimeStamps();
		// We have to grow the history if it is full (ts[0]>0L) 
		// and we need data at times earlier than the first entry (expireTime<ts[0])
//System.out.println("setting 0.1");
//System.out.println("ts[0]= "+ts.length);
//System.out.println("expireTime= "+expireTime);

		if(ts[0]>0L && expireTime<ts[0]) {
			Matrix data = outputData.getDataMatrix();
			if(MAX_BUFFER_SIZE < data.getRows()+HISTORY_GROWTH_INCREMENT){
//System.out.println("get here sett 0.1");
				Matrix newChunk = Matlib.zeros(HISTORY_GROWTH_INCREMENT,data.getCols());
				Matlib.appendRows(newChunk,data,data);
				Matlib.getPart(data, 0, 0, MAX_BUFFER_SIZE-1, data.getCols() - 1, data);
				newChunk.clear();
				long[] newTs = new long[MAX_BUFFER_SIZE];
				for(int r=0;r<MAX_BUFFER_SIZE-HISTORY_GROWTH_INCREMENT;r++){
					newTs[r+HISTORY_GROWTH_INCREMENT] = ts[r];
				}
				for(int r=0;r<HISTORY_GROWTH_INCREMENT;r++) {
					newTs[r] = -1L; // indicates row not used (yet)
				}
				outputData.setTimeStamps(newTs);

			}else{
//System.out.println("get here sett 0.2");
				Matrix newChunk = Matlib.zeros(HISTORY_GROWTH_INCREMENT,data.getCols());
				// insert the new rows at beginning of data matrix
				Matlib.appendRows(newChunk,data,data);
				newChunk.clear();
				long[] newTs = new long[ts.length+HISTORY_GROWTH_INCREMENT];
				for(int r=0;r<ts.length;r++) {
					newTs[r+HISTORY_GROWTH_INCREMENT] = ts[r];
				}
				for(int r=0;r<HISTORY_GROWTH_INCREMENT;r++) {
					newTs[r] = -1L; // indicates row not used (yet)
				}
				outputData.setTimeStamps(newTs);
			}
		}
//System.out.println("setting 0");
		int vIndex = outputData.getVarIndexByName(varName);
		ts = outputData.getTimeStamps();
		// Now insert the data into the history buffer
		// first locate the insertion point in this array (searching backwards since likely place is at the end!)
		int replaceRow = -1;
		int insertAt = -1;
		for(int r=ts.length-1;r>=0;r--) {
			if(currentTime==ts[r]) {
				replaceRow = r;
				break;
			} else if(currentTime>ts[r]) {
				insertAt=r;
				break;
			}
		}
//System.out.println("setVariableValueAtTimeByName currentTime = "+currentTime);
//System.out.println("setting 1");
		if(replaceRow>-1){ // replace the value in an existing row (rare)
//System.out.println("found replaceRow = "+replaceRow);
//System.out.println("found replaceRow vIndex= "+vIndex);
			outputData.setValueAt(replaceRow,vIndex,value);
		} else { // shift timestamps and matrix toward zero to make room for insertion of current value
//System.out.println("can not find replaceRow insertAt = "+insertAt+"  ts.length="+ts.length);
//System.out.println("can not find replaceRow insertAt = "+insertAt);
			for(int r=0;r<insertAt;r++){
				ts[r] = ts[r+1];
			}
			ts[insertAt] = currentTime;
			Matrix M = outputData.getDataMatrix();	
//Matlib.disp(M);
			for(int r=0;r<insertAt;r++){
				for(int c=0;c<M.getCols();c++){
					M.set(r,c,M.get(r+1,c));
				}
			}
			for(int c=0;c<M.getCols();c++){
				M.set(insertAt,c,Double.NaN);
			}
			M.set(insertAt,vIndex,value);
		}
//System.out.println("setting 2");
	}

/** Set the variable value by variable tag and value */
	public void setVariableValueAtTimeByTag(String varTag, double value, String time) throws ParseException, MathException{
		if(!hasTimeStamps){
			throw new MathException("Call time-based method from row-based model.");
			// MK -- Illegal call, should signal a run-time error
		}
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		setVariableValueAtTimeByName(varName, value, time);
	}

/** Calculate the sensitivity with given data.*/
	public void calculateSensitivity(Matrix X, Matrix signedSensitivityValues, Matrix absSensitivityValues) throws MathException{

		if(X.getRows() < 1){
			throw new MathException("There is not enough data for calculating sensitivity.");
		}

		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();
		Vector inputVars = model.getInputs();
		EnsembleModel ensemble = (EnsembleModel)model.getModel();

		int ni = ensemble.getNin();
		int no = ensemble.getNout();
		int row = X.getRows();
		signedSensitivityValues.redimension(ni,no);
		absSensitivityValues.redimension(ni,no);

		if(X.getCols() != ni){
			throw new MathException("The input matrx does not match the model input.");
		}

		for(int c=0;c<no;c++){
			for(int r=0;r<ni;r++){
				signedSensitivityValues.set(r,c,0.0);
				absSensitivityValues.set(r,c,0.0);
			}
		}
		
		Matrix pX = Matlib.createMatrix(1,ni);

		Matrix sampledX = Matlib.createMatrix();
		Matrix sampledY = Matlib.createMatrix();
		
		Matrix nX = Matlib.createMatrix(1,ni);
		Matrix pY = Matlib.createMatrix(1,no);
		Matrix nY = Matlib.createMatrix(1,no);
		Matrix singleY = Matlib.createMatrix(1,no);
		int rCount = 100;
		if(row < 100){
			rCount = row;
		}

		try{
			if(row < 100){
				Matlib.copy(X,sampledX);
			}else{
				Matrix	sampleMatrix = Matlib.createMatrix(X.getRows(),1);
				Stats.randomSplit(X.getRows(),100,sampleMatrix);
				Matlib.getRows(X,sampleMatrix,sampledX);
			}
			double[] deltas = new double[ni];
			double[] stds = new double[ni];
			for(int i=0;i<ni;i++){
				String varName = (String)inputVars.elementAt(i);
				double[] statistics = getVarStatisticsByName(varName);
				deltas[i] = statistics[6]/200;
				stds[i] = statistics[2];
			}
			for(int r=0;r<rCount;r++){
				for(int i=0;i<ni;i++){
					Matlib.getRow(X,r,pX);
					Matlib.getRow(X,r,nX);
					pX.set(0,i,pX.get(0,i)+deltas[i]);
					nX.set(0,i,nX.get(0,i)-deltas[i]);
					model.evaluate(pX,pY);
					model.evaluate(nX,nY);
					Matlib.subtract(pY,nY,singleY);
					Matlib.divide(singleY,deltas[i]*2,singleY);
					Matlib.multiply(singleY,stds[i],singleY);
					for(int c=0;c<no;c++){
						signedSensitivityValues.set(i,c,signedSensitivityValues.get(i,c)+singleY.get(0,c));
						absSensitivityValues.set(i,c,absSensitivityValues.get(i,c)+Math.abs(singleY.get(0,c)));
					}
				}
			}		
		}catch(MathException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
		}
		if(rCount > 0 ){
			for(int i=0;i<ni;i++){
				for(int c=0;c<no;c++){
					signedSensitivityValues.set(i,c,signedSensitivityValues.get(i,c)/rCount);
					absSensitivityValues.set(i,c,absSensitivityValues.get(i,c)/rCount);
				}
			}
		}
		Matlib.clear(pX);
		Matlib.clear(nX);
		Matlib.clear(pY);
		Matlib.clear(nY);
		Matlib.clear(singleY);
		Matlib.clear(sampledX);
	}

	/**	Prepare training data set from giving data series and save them into ascii data matrix files.*/ 
	public void prepareTrainingDataFile(String[] dataSeriesFileNames, int fileType, 
						String inputDataFileName, String outDataFileName)throws MathException, IOException{
		Vector retraindataSeries = new Vector();
		for(int i=0;i<dataSeriesFileNames.length;i++){
			String dsFileName = dataSeriesFileNames[i];
			DataSeries ds = new DataSeries();
			ds.setDataSource(preprocessor);
			ds.Load(dsFileName, fileType);
			retraindataSeries.addElement(ds);
		}
		Vector formulaList = preprocessor.getFormulas();
		Formula2 modelFormula = (Formula2)formulaList.lastElement();
		NolModel2 model = (NolModel2)modelFormula.getFunction();

		Matrix X = Matlib.createMatrix();
		Matrix Y = Matlib.createMatrix();
		model.prepareTrainingSetFromDataSeries(retraindataSeries,X,Y);
		X.writeToFile(inputDataFileName);
		Y.writeToFile(outDataFileName);
		Matlib.clear(X);
		Matlib.clear(Y);
	}
}

