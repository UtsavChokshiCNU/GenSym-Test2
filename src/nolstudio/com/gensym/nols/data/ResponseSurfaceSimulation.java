package com.gensym.nols.data;
/*
 *		Gensym ResponseSurfaceSimulation Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.io.Serializable;
import java.util.Hashtable;
import java.util.Vector;

import com.gensym.DEBUG;
import com.gensym.math.MathException;
import com.gensym.math.datafit.Model;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;

public class ResponseSurfaceSimulation extends NolSimulation implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected int numberOfPoints;
	protected Hashtable minMaxValues;

/** Create a new ResponseSurfaceSimulation containing no characters.*/
	public ResponseSurfaceSimulation() {
		super();
		numberOfPoints = 1;
		minMaxValues = new Hashtable();
	}

/** Create a ResponseSurfaceSimulation information object with ResponseSurfaceSimulation and given index.*/
	public ResponseSurfaceSimulation(Project project, NolModel2 model) throws MathException {
		super(project, model);
		numberOfPoints = 1;
		minMaxValues = new Hashtable();
		initialData();
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		ResponseSurfaceSimulation cloned = (ResponseSurfaceSimulation) super.clone();
		cloned.minMaxValues = minMaxValues == null ? null : (Hashtable) minMaxValues.clone();
		return cloned;
	}

/** Get the min and max for one variable with specific delay.*/
	public double[] getMinMax(String varName){
		double[] minMax = (double[])minMaxValues.get(varName);
		if(DEBUG.debugFlag){
			System.out.println("minMax[0]="+minMax[0]+" minMax[1]="+minMax[1]);
		}
		return minMax;
	}

/** Set the min and max for one variable with specific delay.*/
	public void setMinMax(String varName, double min, double max){
		double[] minMax = new double[2];
		minMax[0] = min;
		minMax[1] = max;
		if(DEBUG.debugFlag){
			System.out.println("minMax[0]="+minMax[0]+" minMax[1]="+minMax[1]);
		}
		minMaxValues.put(varName,minMax);
	}

/** Return the number of points.*/
	public int getNumberOfPoints(){
		return numberOfPoints;
	}

/** Set the number of points.*/
	public void setNumberOfPoints(int n){
		numberOfPoints = n;
	}

/** Return the output dataseries.*/
	@Override
	public DataSeries getOutputData(){
		if(!dataSeries.isEmpty())
			return (DataSeries)dataSeries.elementAt(0);
		return null;
	}

/** Return the output dataseries.*/
	public DataSeries getInputData(){
		if(dataSeries.size()>1)
			return (DataSeries)dataSeries.elementAt(1);
		return null;
	}

/** Initialize the data for this model.*/
	private void initialData() throws MathException {
		DataSeries outputData = null;
		DataSeries inputData = null;
		Preprocessor prep = model.getPreprocessor();
		if(model instanceof NolOptimizeModel) {
			NolOptimizeModel optModel = (NolOptimizeModel) model;
			Vector stateinputs = optModel.getStateInput();
			Vector outputs = optModel.getOutputs();
			Vector inputs = optModel.getInputs();
			Vector states = optModel.getState();

			int oc = outputs.size();
			int ic = inputs.size();
			int sic = stateinputs.size();
			int sc = states.size();
			int count = 0;
			for(int i=0;i<sic;i++){
				String varName = (String)stateinputs.elementAt(i);
				Variable colObj = prep.getVariableFromVariableName(varName);
				double[] statistic = colObj.getStatistics();
				double[] minMax = new double[2];
				if(statistic.length == 11){
					minMax[0] = statistic[0];
					minMax[1] = statistic[0];
				}
				minMaxValues.put(varName,minMax);
				count++;
			}
			for(int i=0;i<ic;i++){
				String varName = (String)inputs.elementAt(i);
				if(!(stateinputs.contains(varName)||states.contains(varName))){
					Variable colObj = prep.getVariableFromVariableName(varName);
					double[] statistic = colObj.getStatistics();
					double[] minMax = new double[2];
					if(statistic.length == 11){
						minMax[0] = statistic[0];
						minMax[1] = statistic[0];
					}
					minMaxValues.put(varName,minMax);
					count++;
				}
			}

			outputData = new DataSeries(1, oc+sc);
			outputData.setName("Output");
			outputData.setDataSource(this);
			String tag,name,unit;
			for(int i=0;i<oc+sc;i++){
				if(i<sc){
					String varName = (String)states.elementAt(i);
					Variable colObj = prep.getVariableFromVariableName(varName);
					tag = colObj.getTag();
					name = colObj.getName();
					unit = colObj.getUnit();
					outputData.setVariableParameters(i,tag,name,unit);
				}else{
					String varName = (String)outputs.elementAt(i-sc);
					Variable colObj = prep.getVariableFromVariableName(varName);
					tag = colObj.getTag();
					name = colObj.getName();
					unit = colObj.getUnit();
					outputData.setVariableParameters(i,tag,name,unit);
				}
			}

			inputData = new DataSeries(1, count);
			inputData.setName("Input");
			inputData.setDataSource(this);
			int cc=0;
			for(int i=0;i<sic+ic;i++){
				if(i<sic){
					String varName = (String)stateinputs.elementAt(i);
					Variable colObj = prep.getVariableFromVariableName(varName);
					if(DEBUG.debugFlag){
						System.out.println("stateinputs colObj="+colObj.toString());
						System.out.println(" cc="+cc);
					}
					tag = colObj.getTag();
					name = colObj.getName();
					unit = colObj.getUnit();
					inputData.setVariableParameters(cc,tag,name,unit);
					cc++;
				}else if(i<sic+ic){
					String varName = (String)inputs.elementAt(i-sic);
					Variable colObj = prep.getVariableFromVariableName(varName);
					if(!(stateinputs.contains(varName)||states.contains(varName))){
						if(DEBUG.debugFlag){
							System.out.println("mani outside statein colObj="+colObj.toString());
							System.out.println(" cc="+cc);
						}
						tag = colObj.getTag();
						name = colObj.getName();
						unit = colObj.getUnit();
						inputData.setVariableParameters(cc,tag,name,unit);
						cc++;
					}
				}
			}
		} else if(model instanceof NolModel2){
			Vector outputs = model.getOutputs();
			Vector inputs = model.getInputs();
			Vector outputDelays = model.getOutputDelays();
			Vector inputDelays = model.getInputDelays();
			Vector inputObjs = new Vector();
			int inputCols = 0;
			for(int i=0;i<outputDelays.size();i++){
				long[] dls = (long[])outputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						inputCols++;
						String varName = (String)outputs.elementAt(i);
						Variable colObj = prep.getVariableFromVariableName(varName);
						double[] statistic = colObj.getStatistics();
						inputObjs.addElement(colObj);
						double[] minMax = new double[2];
						if(statistic.length == 11){
							minMax[0] = statistic[0];
							minMax[1] = statistic[0];
						}
						minMaxValues.put(varName,minMax);
						break;
					}
				}
			}
			for(int i=0;i<inputs.size();i++){
				inputCols++;
				String varName = (String)inputs.elementAt(i);
				Variable colObj = prep.getVariableFromVariableName(varName);
				double[] statistic = colObj.getStatistics();
				inputObjs.addElement(colObj);
				double[] minMax = new double[2];
				if(statistic.length == 11){
					minMax[0] = statistic[0];
					minMax[1] = statistic[0];
				}
				minMaxValues.put(varName,minMax);
			}
			outputData = new DataSeries(1, outputs.size());
			outputData.setName("Output");
			outputData.setDataSource(this);
			String tag,name,unit;
			for(int i=0;i<outputs.size();i++){
				String varName = (String)outputs.elementAt(i);
				Variable colObj = prep.getVariableFromVariableName(varName);
				if(DEBUG.debugFlag){
					System.out.println(" outputs[i]="+varName);
					System.out.println(" outputsobj="+colObj.toString());
				}
				tag = colObj.getTag();
				name = colObj.getName();
				unit = colObj.getUnit();
				outputData.setVariableParameters(i,tag,name,unit);
			}
			inputData = new DataSeries(1, inputCols);
			inputData.setName("Input");
			inputData.setDataSource(this);
			for(int i=0;i<inputObjs.size();i++){
				Variable colObj = (Variable)inputObjs.elementAt(i);
				if(DEBUG.debugFlag){
					System.out.println(" inputObjs="+colObj.toString());
				}
				tag = colObj.getTag();
				name = colObj.getName();
				unit = colObj.getUnit();
				inputData.setVariableParameters(i,tag,name,unit);
			}
//			if(DEBUG.debug){
//				System.out.println(" initialData outputData="+outputData.toStringForSave(1));
//				System.out.println(" initialData inputData="+inputData.toStringForSave(1));
//			}
		}
		dataSeries.removeAllElements();
		dataSeries.addElement(outputData);
		dataSeries.addElement(inputData);
	}

/** Calculate the simulation*/
	@Override
	public void calulationSimulation(){
		if(isCalculated) {
			return;		
		}
		if(model instanceof NolOptimizeModel) {
			NolOptimizeModel optModel = (NolOptimizeModel)model;
			Vector stateinputs = optModel.getStateInput();
			Vector inputs = optModel.getInputs();
			Vector outputs = optModel.getOutputs();
			Vector states = optModel.getState();

			int oc = outputs.size();
			int ic = inputs.size();
			int sic = stateinputs.size();
			int sc = states.size();
			if(optModel.getStateModel()==null){
				Matrix X = Matlib.createMatrix(numberOfPoints, ic);
				for(int c=0;c<ic;c++){
					String varName = (String)inputs.elementAt(c);
					double[] minMax = (double[])minMaxValues.get(varName);
					if(numberOfPoints<=1){
							X.set(0,c,minMax[0]);
					}else{
						for(int r=0;r<numberOfPoints;r++){
							double value = minMax[0]+r*(minMax[1]-minMax[0])/(numberOfPoints-1);
							X.set(r,c, value);
						}
					}
				}
				Model net = optModel.model;
				Matrix yPred = Matlib.createMatrix();
				try{
					net.evaluate(X,yPred);
				}catch(MathException e){
					System.err.println("Non-Fatal exception: " + e.getMessage());
					e.printStackTrace();
				}

				DataSeries inputData = (DataSeries)dataSeries.elementAt(1);
				inputData.setDataMatrix(X);
				inputData.calculateVarStatistics();
				DataSeries outputData = (DataSeries)dataSeries.elementAt(0);
				outputData.setDataMatrix(yPred);
				outputData.calculateVarStatistics();				
			}else{
				if(numberOfPoints <1) {
					numberOfPoints =1;
				}
				Matrix I = Matlib.createMatrix(numberOfPoints, sic);
				for(int c=0;c<sic;c++){
					String varName = (String)stateinputs.elementAt(c);
					double[] minMax = (double[])minMaxValues.get(varName);
					if(numberOfPoints==1){
							I.set(0,c,minMax[0]);
					}else{
						for(int r=0;r<numberOfPoints;r++){
							double value = minMax[0]+r*(minMax[1]-minMax[0])/(numberOfPoints-1);
							I.set(r,c, value);
						}
					}
				}
				Model net2 = optModel.getStateModel();
				Matrix dPred = Matlib.createMatrix();
				try{
					net2.evaluate(I,dPred);
				}catch(MathException e){
					System.err.println("Non-Fatal exception: " + e.getMessage());
					e.printStackTrace();
				}

				Matrix X = Matlib.createMatrix(numberOfPoints, ic);
				for(int c=0;c<ic;c++){
					String varName = (String)inputs.elementAt(c);
					int indepIndex = stateinputs.indexOf(varName);
					int stateIndex = states.indexOf(varName);
					if(indepIndex != -1){
						for(int r=0;r<numberOfPoints;r++){
							X.set(r,c,I.get(r,indepIndex));
						}
					}else if(stateIndex != -1){
						for(int r=0;r<numberOfPoints;r++){
							X.set(r,c,dPred.get(r,stateIndex));
						}
					}else{
						double[] minMax = (double[])minMaxValues.get(varName);
						if(numberOfPoints==1){
								X.set(0,c,minMax[0]);
						}else{
							for(int r=0;r<numberOfPoints;r++){
								double value = minMax[0]+r*(minMax[1]-minMax[0])/(numberOfPoints-1);
								X.set(r,c, value);
							}
						}
					}
				}
				if(DEBUG.debugFlag){
		//			System.out.println("in model2 X=");
		//			Matlib.disp(X);
				}
				Model net1 = optModel.getModel();
				Matrix yPred = Matlib.createMatrix();
				try{
					net1.evaluate(X,yPred);
				}catch(MathException e){
					System.err.println("Non-Fatal exception: " + e.getMessage());
					e.printStackTrace();
				}

				DataSeries outputData = (DataSeries)dataSeries.elementAt(0);
				Matrix outputM = Matlib.createMatrix(numberOfPoints,oc+sc);
				for(int c=0;c<sc+oc;c++){
					for(int r=0;r<numberOfPoints;r++){
						if(c<sc)
							outputM.set(r,c, dPred.get(r,c));
						else
							outputM.set(r,c, yPred.get(r,c-sc));
					}
				}
				outputData.setDataMatrix(outputM);
				outputData.calculateVarStatistics();
  				DataSeries inputData = (DataSeries)dataSeries.elementAt(1);
				Matrix inputM = Matlib.createMatrix(numberOfPoints,inputData.getColumn());
				int cc = 0;
				for(int c=0;c<sic+ic;c++){
					if(c<sic){
						for(int r=0;r<numberOfPoints;r++){
							inputM.set(r,c, I.get(r,c));
						}
					}else{
						String varName = (String)inputs.elementAt(c-sic);
						if(!(stateinputs.contains(varName)||states.contains(varName))){
							for(int r=0;r<numberOfPoints;r++){
								inputM.set(r,sic+cc, X.get(r,c-sic));
							}
							cc++;
						}
					}
				}
				inputData.setDataMatrix(inputM);
				inputData.calculateVarStatistics();
			}
		} else if (model instanceof NolModel2) {
			Vector outputs = model.getOutputs();
			Vector inputs = model.getInputs();
			Vector outputDelays = model.getOutputDelays();
			Vector inputDelays = model.getInputDelays();
			Vector minMaxBuffer = new Vector();
			int inputCols = 0;
			for(int i=0;i<outputDelays.size();i++){
				long[] dls = (long[])outputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						inputCols++;
						String varName = (String)outputs.elementAt(i);
						double[] minMax = (double[])minMaxValues.get(varName);
						minMaxBuffer.addElement(minMax);
					}
				}
			}
			for(int i=0;i<inputDelays.size();i++){
				long[] dls = (long[])inputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					inputCols++;
					String varName = (String)inputs.elementAt(i);
					double[] minMax = (double[])minMaxValues.get(varName);
					minMaxBuffer.addElement(minMax);
				}
			}

			DataSeries inputData = (DataSeries)dataSeries.elementAt(1);
			int inputVarCount = 0;
			for(int i=0;i<outputDelays.size();i++){
				long[] dls = (long[])outputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						inputVarCount++;
						break;
					}
				}
			}
			inputVarCount = inputVarCount + inputs.size();
  			Matrix inputM = Matlib.createMatrix(numberOfPoints, inputVarCount);
			int ccc = 0;
			for(int i=0;i<outputDelays.size();i++){
				long[] dls = (long[])outputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						String varName = outputs.elementAt(i).toString();
						double[] minMax = (double[])minMaxValues.get(varName);
						if(numberOfPoints<=1){
								inputM.set(0,ccc,minMax[0]);
						}else{
							for(int r=0;r<numberOfPoints;r++){
								double value = minMax[0]+r*(minMax[1]-minMax[0])/(numberOfPoints-1);
								inputM.set(r,ccc, value);
							}
						}
						ccc++;
						break;
					}
				}
			}
			for(int c=0;c<inputs.size();c++){
				String varName = inputs.elementAt(c).toString();
				double[] minMax = (double[])minMaxValues.get(varName);
				if(numberOfPoints<=1){
						inputM.set(0,c+ccc,minMax[0]);
				} else {
					for(int r=0;r<numberOfPoints;r++){
						double value = minMax[0]+r*(minMax[1]-minMax[0])/(numberOfPoints-1);
						inputM.set(r,c+ccc, value);
					}
				}
			}
			inputData.setDataMatrix(inputM);
			inputData.calculateVarStatistics();
			Matrix X = Matlib.createMatrix(numberOfPoints, inputCols);
			for(int c=0;c<inputCols;c++){
				double[] minMax = (double[])minMaxBuffer.elementAt(c);
				if(numberOfPoints<=1){
						X.set(0,c,minMax[0]);
				}else{
					for(int r=0;r<numberOfPoints;r++){
						double value = minMax[0]+r*(minMax[1]-minMax[0])/(numberOfPoints-1);
						X.set(r,c, value);
					}
				}
			}
//			Model net = model.getModel();
			Matrix yPred = Matlib.createMatrix();
			try{
				model.evaluate(X,yPred);
			}catch(MathException e){
				System.err.println("Exception in calculating predictive  model"+e.getMessage());
				e.printStackTrace();
			}
			DataSeries outputData = (DataSeries)dataSeries.elementAt(0);
			outputData.setDataMatrix(yPred);
			outputData.calculateVarStatistics();
		}
		isCalculated = true;
	}

}