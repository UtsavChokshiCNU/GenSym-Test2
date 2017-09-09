package com.gensym.nols.deploy;
/*
 *		Gensym OnlineAutoRecusiveProcessor Class.
 *		This class is extended from Object.class
 *		Modified 3/2/99 by Gchen
 */

import java.io.Serializable;
import java.text.ParseException;
import java.util.Date;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.NolAutorecursiveModel;
import com.gensym.nols.data.NolModel2;
import com.gensym.nols.data.Preprocessor;

/** An OnlineAutoRecusiveProcessor object provides a way to run the NOLStudio predictive model online.
* The object maintains a data buffer for storing the online data. 
* The steps for online deployment: 
* 1. Create a OnlineAutoRecusiveProcessor using default constructor.
* 2. Load exported model file using loadModel method.
* 3. You can check the variable names and tags, or whether it is a time-based model 
*    by call corresponding methods. 
* 4. Follow the user's guide to push input data into the data buffer.
* 5. Calculate the model prediction.
* 6. Follow the user's guide to get output values. 
*/
public class OnlineAutoRecusiveProcessor extends OnlineProcessor
 implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected long totalLatestRealTime;
	protected long[] latestRealTimes;

/** Create a null OnlineAutoRecusiveProcessor with no argument */
	public OnlineAutoRecusiveProcessor() {
		super();
		totalLatestRealTime = 0l;
	}

/** Create a data OnlineAutoRecusiveProcessor from a given name and resources. This is for model export.*/
	public OnlineAutoRecusiveProcessor(String name, Preprocessor prep, NolModel2 model)
		throws MathException {
		super(name, prep, model);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

/** Initialize the properties of the OnlineProcessor. */
	@Override
	protected void initialize(Preprocessor prep, NolModel2 model) throws MathException {
		super.initialize(prep,model);
		latestRealTimes = new long[varNames.size()];
		totalLatestRealTime = 0;
	}

/** Calculate the model for time based model.*/
	@Override
	public void calculateOutputAtTime(String time) throws MathException{
		//need to test whether you have the data to do the calculation gchen 1/9/04
		
//System.out.println("get here 1");
		
		if(canDoCalculationAtTime(time)){
//System.out.println("get here 3");
			super.calculateOutputAtTime(time);
		}else{
//System.out.println("get here 30");
			calculateOutputAtTimeRecursively(time);
		}
   	}

/** Calculate the model for time based model.*/
	public void calculateOutputAtTimeRecursively(String time) throws MathException{
		try {
			NolAutorecursiveModel model = (NolAutorecursiveModel)getModel();
			long currentTime = dateTimeFormat.parse(time).getTime();
			long delayInterval = model.getDelayInterval();
			double ctd = currentTime;
			double ttd = totalLatestRealTime;
			double did = delayInterval;
			int steps = (int)((ctd - ttd) / did + 0.5);
//System.out.println("calculateOutputAtTimeRecursively (ctd - ttd) / did = "+(ctd - ttd) / did);
//System.out.println("calculateOutputAtTimeRecursively steps = "+steps);
//System.out.println("calculateOutputAtTimeRecursively time = "+time);
			for (int i=steps;i>0;i--){
				String newTime = dateTimeFormat.format(new Date(currentTime-(i-1)*delayInterval));
//System.out.println("calculateOutputAtTimeRecursively newTime = "+newTime);
				super.calculateOutputAtTime(newTime);
			}
		} catch (Exception e) {
			System.out.println("Exception is "+e.getMessage());
			e.printStackTrace();
			throw new MathException("Exception is "+e.getMessage());
		}
	}

/** Test whether there is already a valid value for this variable at the given time.*/
	protected boolean canDoCalculationAtTime(String time){
		try{
			long shortest = Long.MAX_VALUE;
			long longest = 0l;
			NolAutorecursiveModel model = (NolAutorecursiveModel)getModel();
			Vector outputDelays = model.getOutputDelays();
			for(int i=0;i<outputDelays.size();i++){
  				long[] dls = (long[])outputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if (dls[j] > longest){
						longest = dls[j];
					}
					if (dls[j] < shortest) {
						shortest = dls[j];
					}
				}
			}
			long currentTime = dateTimeFormat.parse(time).getTime();
			long lastValid = currentTime - shortest;
			long firstValid = currentTime - longest;
			long startTimeforvalidData = getStartTimeForValidData();
//System.out.println("get here 30");
			if(lastValid > totalLatestRealTime) {
				return false;
			}
			if(firstValid < startTimeforvalidData) {
				return false;
			}
		} catch(Exception evt){
			System.err.println("Non-Fatal exception preparing training set: " + evt.getMessage());
			evt.printStackTrace();
		}
		return true;
	}

	protected long getStartTimeForValidData(){
		long[] ts = outputData.getTimeStamps();
		Matrix data = outputData.getDataMatrix();
		int cols = data.getCols();
		for(int r=0;r<ts.length;r++){
			if(ts[r]>0l){
				boolean ok=true;
				for(int c=0;c<cols;c++){
					if(Double.isNaN(data.get(r,c))){
						ok = false;
						break;
					}
				}
				if(ok){
					return ts[r];
				}
			}
		}

		return 0l;
	}


/** Test whether there is already a valid value for this variable at the given time.*/
	protected boolean canSetValueAtTime(String varName, long currentTime){
		int inputNumber = inputNames.indexOf(varName);
		// To support asynchonous data acquisition, each variable has its own data series
		DataSeries ds = getDataSeriesFromVariableName(varName);
		if(ds == null) {
			return false;
		}
		long[] ts = ds.getTimeStamps();
		//The data is at the earlier stage of the buffer
		if(currentTime < ts[0]) {
			return false;
		}
		boolean found = false; // test whether there is a value at given time.
		for(int i=0;i<ts.length;i++){
			if(currentTime == ts[0]){
				found = true;
				break;
			}
		}
		return found;
	}

	@Override
	public void copyToThis(OnlineProcessor processor) {
		super.copyToThis(processor);
		totalLatestRealTime = ((OnlineAutoRecusiveProcessor)processor).totalLatestRealTime;
		latestRealTimes = ((OnlineAutoRecusiveProcessor)processor).latestRealTimes;
	}

/** Set the input value by variable name and value */
	@Override
	public void setInputAtTimeByName(String varName, double val, String time) throws ParseException, MathException{
		super.setInputAtTimeByName(varName,  val,  time);
		updateTheLatestRealTimeIndex(varName,time);
	}

/** Set the input value by variable number and value */
	@Override
	public void setInputAtTimeByIndex(int inNumber, double val, String time)
		throws ParseException, MathException{
		super.setInputAtTimeByIndex(inNumber,  val,  time);
		String varName = (String)inputNames.elementAt(inNumber);
		updateTheLatestRealTimeIndex(varName,time);
	}

/** Set the input value by variable tag and value */
	@Override
	public void setInputAtTimeByTag(String varTag, double val, String time)
		throws ParseException, MathException{
		super.setInputAtTimeByTag(varTag,  val,  time);
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		updateTheLatestRealTimeIndex(varName,time);
	}

/** Set the variable value by variable name and value */
	@Override
	public void setVariableValueAtTimeByName(String varName, double value, String time) throws ParseException, MathException{
		super.setVariableValueAtTimeByName(varName,  value,  time);
		updateTheLatestRealTimeIndex(varName,time);
	}

	protected void updateTheLatestRealTimeIndex(String varName,String time)throws ParseException{
		int index = varNames.indexOf(varName);
		long currentTime = dateTimeFormat.parse(time).getTime();
		if(currentTime > latestRealTimes[index]){
			latestRealTimes[index] = currentTime;
		}
		boolean last = true;
		for(int i=0;i<latestRealTimes.length;i++){
			if(currentTime > latestRealTimes[i]){
				last = false;
			}
		}
		if(last){
			if(totalLatestRealTime<currentTime){
				totalLatestRealTime = currentTime;
			}
		}
	}
}


