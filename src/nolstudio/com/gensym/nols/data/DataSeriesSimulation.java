package com.gensym.nols.data;
/*
 *		Gensym DataSeriesSimulation Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.util.*;
import java.io.*;

import com.gensym.math.datafit.*;
import com.gensym.math.*;
import com.gensym.math.matrix.*;

public class DataSeriesSimulation extends NolSimulation implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected Preprocessor preprocessor;
	protected DataSeries dataSeriesSource;

/** Create a new DataSeriesSimulation containing no characters.*/
	public DataSeriesSimulation() {
		super();
	}

/** Create a DataSeriesSimulation information object with DataSeriesSimulation and given index.*/
	public DataSeriesSimulation(Project project, NolModel2 model, DataSeries ds){
		super(project, model);
		preprocessor = (Preprocessor)ds.getDataSource();
		dataSeriesSource = ds;
	}

	public Preprocessor getPreprocessor(){
		return preprocessor;
	}

/** Calculate the simulation*/
	@Override
	public void calulationSimulation(){
		if(isCalculated) return;
		if(modelType == 0){
			Vector outputDelays = model.getOutputDelays();
			Vector inputDelays = model.getInputDelays();
			Vector outputs = model.getOutputs();
			Vector inputs = model.getInputs();
			int maxDelay = 0;
			for(int i=0;i<outputDelays.size();i++){
				int[] dls = (int[])outputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if(dls[j] > maxDelay){
							maxDelay = dls[j];
					}
				}
			}
			for(int i=0;i<inputDelays.size();i++){
				int[] dls = (int[])inputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if(dls[j] > maxDelay){
							maxDelay = dls[j];
					}
				}
			}
// MK 2/20/99 THIS IS NOT UP TO DATE WITH NEW FORMULA MECHANISM !!
			/////FormulaCalculator tc = new FormulaCalculator();
			DataSeries data = (DataSeries)dataSeries.elementAt(0);
			long[] time = data.getTimeStamps();
			Matrix yPred;
			try{
				yPred = tc.calculateModel(model,data, true);
				DataSeries outputData = new DataSeries(yPred);
				int oc = outputs.size();

				String tag,name,unit;
				for(int i=0;i<oc;i++){
					Variable colObj = (Variable)outputs.elementAt(i-1);
					tag = colObj.getTag();
					name = colObj.getName();
					unit = colObj.getUnit();
					outputData.setVariableParameters(i,tag,name,unit);
				}
				int row = yPred.getRows();
				long[] newTime = new long[row];
				for(int r=0;r<row;r++){
					newTime[r] = time[r+maxDelay];
				}
				outputData.setTimeStamps(newTime);
				dataSeries.removeAllElements();
				dataSeries.addElement(outputData);
			}catch(Exception e){
				System.err.println("There is exception when calcualte model."+ e.getMessage());
				e.printStackTrace();
			}			
		}else if(modelType == 1){

		}
		isCalculated = true;
	}
}