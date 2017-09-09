package com.gensym.nols.data;
/*
 *		Gensym Optimization Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.util.*;
import java.io.*;
import com.gensym.math.opt.*;
import com.gensym.math.matrix.*;
import com.gensym.math.MathException;
import com.gensym.DEBUG;

public class NolOptimization extends DataSource implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;

	// added by bbush 5-3-99
	private static final int LOW_LIMIT = 0;
	private static final int SOFT_LOW_LIMIT = 1;
	private static final int SETPOINT = 2;
	private static final int SOFT_HIGH_LIMIT = 3;
	private static final int HIGH_LIMIT = 4;
	private static final int MIN_POINT = 5;
	private static final int MAX_POINT = 6;
	private static final int ARRAY_SIZE = 7;
	
	private static final String DELAY_SEPARATOR = "#Del#Sep#";

	protected INolOptimizeModel optModel;
	protected boolean isCalculated;
	protected Hashtable weights;
	protected Hashtable bounds;
	protected Matrix initX;
	protected Matrix X;	//result
	protected Matrix Y;	//result
	protected double F;

	private transient INolObjective objective;
	private transient Matrix simplexP;

	private int NMAX;
	private int statusFlag; //Added gchen 6.28.2000, for returning the status of optimization
	private String statusMessage = ""; //Added gchen 6.28.2000, for returning the message of optimization

	private transient IObjectiveFactory objectiveFactory = new ObjectiveFactory();

/** Create a new Optimization containing no characters.*/
	public NolOptimization() {
		super();
		isCalculated = false;
		weights = new Hashtable();
		bounds = new Hashtable();
		X = Matlib.createMatrix();
		Y = Matlib.createMatrix();
		NMAX = 10000; 
		statusFlag = 0;
	}

/** Create a new optimization containing no characters.*/
	public NolOptimization(Project p, String n) {
		this();
		project = p;
		name = n;
	}


/** Set the modelndex of the NolOptimization.*/
	public void setModel(int modelIndex){
		optModel = project.getOptimizationModel(modelIndex);
		initWeights();
		initBounds();
	}

/** Set the model of the NolOptimization.*/
	public void setModel(INolOptimizeModel optModel){
		this.optModel = optModel;
		initWeights();
		initBounds();
	}


 /** Get model of this NolOptimization.*/
	public INolOptimizeModel getModel(){
		return optModel;
	}

/** init the weight in the hashtable.*/
	public void initWeights(){
		Vector outputs = optModel.getOutputs();
		Vector states = optModel.getState();
		Vector manis = optModel.getManipulate();
		Vector exogs = optModel.getExogenous();
		for(int i=0;i<outputs.size();i++){
			double[] ww = new double[4];
			ww[1] = 1.0;
			putWeights(outputs.elementAt(i),ww);
		}
		for(int i=0;i<states.size();i++){
			double[] ww = new double[4];
			putWeights(states.elementAt(i),ww);
		}
		for(int i=0;i<manis.size();i++){
			double[] ww = new double[4];
			putWeights(manis.elementAt(i),ww);
		}
		for(int i=0;i<exogs.size();i++){
			double[] ww = new double[4];
			ww[1] = 1.0;	  //Gchen changed for green thymb bug 5/12/99
			putWeights(exogs.elementAt(i),ww);
		}
	}

/** put the weight in the hashtable.*/
	public void putWeights(Object key, Object weight){
		weights.put(key,weight);
	}

/** get the weight in the hashtable.*/
	public double[] getWeights(Object key){
		return (double[])weights.get(key);
	}

/** put the bound in the hashtable.*/
	public void putBounds(Object key, Object b){
		bounds.put(key,b);
	}

/** put the bound in the hashtable.*/
	public void putBounds(Object key, Object b, long delay){
		bounds.put("" + key + DELAY_SEPARATOR + delay, b);
	}

/** get the bound in the hashtable.*/
	public double[] getBounds(Object key){
		return (double[])bounds.get(key);
	}

/** get the bound in the hashtable.*/
	public double[] getBounds(Object key, long delay){
		double[] bb = (double[])bounds.get("" + key + DELAY_SEPARATOR + delay);
		if (bb == null) {
			bb = getBounds(key);
			if (bb == null){
				return null;
			}
			putBounds(key, bb.clone(), delay);
		}
		return (double[])bounds.get("" + key + DELAY_SEPARATOR + delay);
	}

/** init the bound in the hashtable.*/
	public void initBounds(){
		Vector outputs = optModel.getOutputs();
		Vector states = optModel.getState();
		Vector manis = optModel.getManipulate();
		Vector exogs = optModel.getExogenous();

		IPreprocessor prep = optModel.getPreprocessor();
		for(int i=0;i<outputs.size();i++){
			String varName = (String)outputs.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
//			double[] statistic = colObj.getStatistics();						
			double[] bb = new double[ARRAY_SIZE];
			// added by bbush 5-3-99 - for reference only 
		/*		public static final int LOW_LIMIT = 0;
				public static final int SOFT_LOW_LIMIT = 1;
				public static final int SETPOINT = 2;
				public static final int SOFT_HIGH_LIMIT = 3;
				public static final int HIGH_LIMIT = 4;
				public static final int MIN_POINT = 5;
				public static final int MAX_POINT = 6;
				private static final int ARRAY_SIZE = 7;
		*/
			// added/re-wrote/decoded by bbush 5-3-99
			// get the default upper/lower soft/hard bounds
			double minValue = colObj.getMinValue();
			double maxValue = colObj.getMaxValue();
			bb[LOW_LIMIT] = minValue; // decoded from bb[0] = Double.NEGATIVE_INFINITY;    
			bb[SOFT_LOW_LIMIT] = minValue; // decoded from bb[1] = Double.NEGATIVE_INFINITY;	
			bb[SOFT_HIGH_LIMIT] = maxValue; // decoded from bb[3] = Double.POSITIVE_INFINITY;	
			bb[HIGH_LIMIT] = maxValue; // decoded from bb[4] = Double.POSITIVE_INFINITY;	

			// the mean value
			bb[SETPOINT] = colObj.getMeanValue();  // decoded from bb[2] = statistic[0];

			// the min and max values
			bb[MIN_POINT] = minValue; // used to be bb[5] = statistic[7];
			bb[MAX_POINT] = maxValue; // used to be bb[6] = statistic[8];

			putBounds(varName,bb);
		}
		for(int i=0;i<states.size();i++){
			String varName = (String)states.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			double[] statistic = colObj.getStatistics();						
			double[] bb = new double[ARRAY_SIZE];
/*			bb[0] = Double.NEGATIVE_INFINITY;
			bb[1] = Double.NEGATIVE_INFINITY;
			bb[2] = statistic[0];
			bb[3] = Double.POSITIVE_INFINITY;
			bb[4] = Double.POSITIVE_INFINITY;
			bb[5] = statistic[7];
			bb[6] = statistic[8];
*/
			double minValue = colObj.getMinValue();
			double maxValue = colObj.getMaxValue();
			bb[LOW_LIMIT] = minValue; // decoded from bb[0] = Double.NEGATIVE_INFINITY;    
			bb[SOFT_LOW_LIMIT] = minValue; // decoded from bb[1] = Double.NEGATIVE_INFINITY;	
			bb[SOFT_HIGH_LIMIT] = maxValue; // decoded from bb[3] = Double.POSITIVE_INFINITY;	
			bb[HIGH_LIMIT] = maxValue; // decoded from bb[4] = Double.POSITIVE_INFINITY;	

			// the mean value
			bb[SETPOINT] = colObj.getMeanValue();  // decoded from bb[2] = statistic[0];

			// the min and max values
			bb[MIN_POINT] = minValue; // used to be bb[5] = statistic[7];
			bb[MAX_POINT] = maxValue; // used to be bb[6] = statistic[8];
		
			putBounds(varName,bb);
		}
		for(int i=0;i<manis.size();i++){
			String varName = (String)manis.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			double[] statistic = colObj.getStatistics();						
			double[] bb = new double[7];
/*			bb[0] = Double.NEGATIVE_INFINITY;
			bb[1] = Double.NEGATIVE_INFINITY;
			bb[2] = statistic[0];
			bb[3] = Double.POSITIVE_INFINITY;
			bb[4] = Double.POSITIVE_INFINITY;
			bb[5] = statistic[7];
			bb[6] = statistic[8];
*/
			double minValue = colObj.getMinValue();
			double maxValue = colObj.getMaxValue();
			bb[LOW_LIMIT] = minValue; // decoded from bb[0] = Double.NEGATIVE_INFINITY;    
			bb[SOFT_LOW_LIMIT] = minValue; // decoded from bb[1] = Double.NEGATIVE_INFINITY;	
			bb[SOFT_HIGH_LIMIT] = maxValue; // decoded from bb[3] = Double.POSITIVE_INFINITY;	
			bb[HIGH_LIMIT] = maxValue; // decoded from bb[4] = Double.POSITIVE_INFINITY;	

			// the mean value
			bb[SETPOINT] = colObj.getMeanValue();  // decoded from bb[2] = statistic[0];

			// the min and max values
			bb[MIN_POINT] = minValue; // used to be bb[5] = statistic[7];
			bb[MAX_POINT] = maxValue; // used to be bb[6] = statistic[8];
			putBounds(varName,bb);
		}
		for(int i=0;i<exogs.size();i++){
			String varName = (String)exogs.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			double[] statistic = colObj.getStatistics();						
			double[] bb = new double[7];
/*			bb[0] = Double.NEGATIVE_INFINITY;
			bb[1] = Double.NEGATIVE_INFINITY;
			bb[2] = statistic[0];
			bb[3] = Double.POSITIVE_INFINITY;
			bb[4] = Double.POSITIVE_INFINITY;
			bb[5] = statistic[7];
			bb[6] = statistic[8];
*/
			double minValue = colObj.getMinValue();
			double maxValue = colObj.getMaxValue();
			bb[LOW_LIMIT] = minValue; // decoded from bb[0] = Double.NEGATIVE_INFINITY;    
			bb[SOFT_LOW_LIMIT] = minValue; // decoded from bb[1] = Double.NEGATIVE_INFINITY;	
			bb[SOFT_HIGH_LIMIT] = maxValue; // decoded from bb[3] = Double.POSITIVE_INFINITY;	
			bb[HIGH_LIMIT] = maxValue; // decoded from bb[4] = Double.POSITIVE_INFINITY;	

			// the mean value
			bb[SETPOINT] = colObj.getMeanValue();  // decoded from bb[2] = statistic[0];

			// the min and max values
			bb[MIN_POINT] = minValue; // used to be bb[5] = statistic[7];
			bb[MAX_POINT] = maxValue; // used to be bb[6] = statistic[8];
	
			putBounds(varName,bb);
		}
	}

	/** Overide the object clone method.*/
	@Override
	public Object clone() throws CloneNotSupportedException{ 
		NolOptimization cloned = (NolOptimization) super.clone();
		cloned.weights = weights == null ? null : (Hashtable) weights.clone();
		cloned.bounds = bounds == null ? null : (Hashtable) bounds.clone();
		cloned.initX = initX == null ? null : (Matrix) initX.clone();
		cloned.X = X == null ? null : (Matrix) X.clone();
		cloned.Y = Y == null ? null : (Matrix) Y.clone();
		cloned.simplexP = simplexP == null ? null : (Matrix) simplexP.clone();
		cloned.objectiveFactory = new ObjectiveFactory();
		cloned.optModel = optModel == null ? null : (INolOptimizeModel)optModel.clone();
		
		return cloned;
	}

	/** Overide the object equals method.*/
	@Override
	public boolean equals(Object obj){
		if(obj == null || !getClass().equals(obj.getClass()))
			return false;
		NolOptimization obj1 = (NolOptimization)obj;
		return obj1.name.equals(name);
	}
	
	/** Overide the object hashcode method.*/
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		return prime * result + ((this.name == null) ? 0 : this.name.hashCode());
	}

	/** Returns a String object representing this NolOptimization value.  */
	public String toString(boolean flag){
		String s = "Name="+name;

		Vector inputs = optModel.getInputs();
		Vector outputs = optModel.getOutputs();
		Vector states = optModel.getState();
		Vector manis = optModel.getManipulate();
		Vector exogs = optModel.getExogenous();
		s =s +"Output:\n";
		for(int i=0;i<outputs.size();i++){
			String varName = (String)outputs.elementAt(i);
			double[] ww = (double[])weights.get(varName); 
			double[] bb = (double[])getBounds(varName); 
			s = s +varName+" Weight:"+ww[0]+","+ww[1]+","+ww[2]+","+ww[3];
			s = s +  "\n Bounds:"+bb[0]+","+bb[1]+","+bb[2]+","+bb[3]+","+bb[4]+"\n" ;
//			s = s +"\nBounds:"+String.valueOf(bb[0])+String.valueOf(bb[1])+String.valueOf(bb[2])+String.valueOf(bb[3])+String.valueOf(bb[4])+"\n";
		}
		s =s +"Manipulated:\n";
		for(int i=0;i<manis.size();i++){
			String varName = (String)manis.elementAt(i);
			double[] ww = (double[])weights.get(varName); 
			double[] bb = (double[])getBounds(varName); 
			s = s +varName+" Weight:"+ww[0]+","+ww[1]+","+ww[2]+","+ww[3];
			s = s +  "\n Bounds:"+bb[0]+","+bb[1]+","+bb[2]+","+bb[3]+","+bb[4]+"\n" ;
		}
		s =s +"State:\n";
		for(int i=0;i<states.size();i++){
			String varName = (String)states.elementAt(i);
			double[] ww = (double[])weights.get(varName); 
			double[] bb = (double[])getBounds(varName); 
			s = s +varName+" Weight:"+ww[0]+","+ww[1]+","+ww[2]+","+ww[3];
			s = s +  "\n Bounds:"+bb[0]+","+bb[1]+","+bb[2]+","+bb[3]+","+bb[4]+"\n" ;
		}
		s =s +"Exogenous:\n";
		for(int i=0;i<exogs.size();i++){
			String varName = (String)manis.elementAt(i);
			double[] ww = (double[])weights.get(varName); 
			double[] bb = (double[])getBounds(varName); 
			s = s +varName+" Weight:"+ww[0]+","+ww[1]+","+ww[2]+","+ww[3];
			s = s +  "\n Bounds:"+bb[0]+","+bb[1]+","+bb[2]+","+bb[3]+","+bb[4]+"\n" ;
		}
		return s;
	}
/** return the calculation status.*/
	public boolean isCalculated(){
		return isCalculated;
	}

/** set the calculation status.*/
	public void setCalculated(boolean status){
		isCalculated = status;
	}

/** return the calculation X result.*/
	public Matrix getXResult(){
		return X;
	}

/** return the calculation Y result.*/
	public Matrix getYResult(){
		return Y;
	}

/** return the objective function result.*/
	public double getObjectiveValue(){
		return F;
	}

/** Set the initial X .*/
	public void setInitX(Matrix M){
		if(initX == null){
			initX = Matlib.createMatrix();
		}
		int nin = optModel.getNin();
		if(nin != M.getCols()){
			return;
		}
		Matlib.copy(M,initX);
		if(optModel.getModel()!=null && optModel.getStateModel()==null){
			Vector inputs = optModel.getInputs();
//			int nin = inputs.size();
			for(int i=0;i<nin;i++){
				String varName = (String)inputs.elementAt(i);
				double[] bb = getBounds(varName);
				double initValue = initX.get(0,i);
				if(initValue <bb[NolObjective.LOWER_BOUND] 
					|| initValue > bb[NolObjective.UPPER_BOUND]){
					double value  = (bb[NolObjective.LOWER_BOUND]+bb[NolObjective.UPPER_BOUND])/2.0;
					initX.set(0,i,value);
				}
			}
		}else if(optModel.getStateModel()!=null){
			Vector stateInputs = optModel.getStateInput();
			Vector inputs = optModel.getInputs();
			Vector states = optModel.getState();
//				int nin = optModel.getNin();
//				int sc = states.size(); 
			int ic = inputs.size(); 
			int sic = stateInputs.size(); 
			int cc=0;
			for(int i=0;i<sic+ic;i++){
				if(i<sic){
					String varName = (String)stateInputs.elementAt(i);
					double[] bb = getBounds(varName);
					double initValue = initX.get(0,i);
					if(initValue <bb[NolObjective.LOWER_BOUND] 
						|| initValue > bb[NolObjective.UPPER_BOUND]){
						double value  = (bb[NolObjective.LOWER_BOUND]+bb[NolObjective.UPPER_BOUND])/2.0;
						initX.set(0,i,value);
					}
				}else{
					String varName = (String)inputs.elementAt(i-sic);
  					if(!states.contains(varName) && !stateInputs.contains(varName)){
						double[] bb = getBounds(varName);
						double initValue = initX.get(0,sic+cc);
						if(initValue <bb[NolObjective.LOWER_BOUND] 
							|| initValue > bb[NolObjective.UPPER_BOUND]){
							double value  = (bb[NolObjective.LOWER_BOUND]+bb[NolObjective.UPPER_BOUND])/2.0;
							initX.set(0,sic+cc,value);
							cc++;
						}
					}
				}
			}
		}
	
	}

/** return the init X.*/
	public Matrix getInitX(){
		int nin = optModel.getNin();
		if (initX == null || initX.getCols() != nin) {
			IPreprocessor prep = optModel.getPreprocessor();
			if (optModel.getModel() != null && optModel.getStateModel() == null)
			{
				Vector inputs = optModel.getInputs();
				initX = Matlib.createMatrix(1,nin);
				for(int i = 0; i < inputs.size(); i++) {
					String varName = (String)inputs.elementAt(i);
					Variable colObj = prep.getVariableFromVariableName(varName);
					double[] bb = getBounds(varName);
  					double[] statistic = colObj.getStatistics();
					if(statistic[0] <bb[NolObjective.LOWER_BOUND] 
						|| statistic[0] > bb[NolObjective.UPPER_BOUND]){
						double value  = (bb[NolObjective.LOWER_BOUND]
						     + bb[NolObjective.UPPER_BOUND]) / 2.0;
						initX.set(0,i,value);
					}else{					
						initX.set(0,i,statistic[0]);
					}
				}
			}else if(optModel.getStateModel()!=null){
				Vector stateInputs = optModel.getStateInput();
				Vector inputs = optModel.getInputs();
				Vector states = optModel.getState();
				int sc = states.size(); 
				int ic = inputs.size(); 
				int sic = stateInputs.size(); 
				initX = Matlib.createMatrix(1,nin);
				int cc=0;
				for(int i=0;i<sic+ic;i++){
					if(i<sic){
						String varName = (String)stateInputs.elementAt(i);
						Variable colObj = prep.getVariableFromVariableName(varName);
  						double[] statistic = colObj.getStatistics();
						double[] bb = getBounds(varName);
						if(statistic[0] <bb[NolObjective.LOWER_BOUND] 
							|| statistic[0] > bb[NolObjective.UPPER_BOUND]){
							double value  = (bb[NolObjective.LOWER_BOUND]+bb[NolObjective.UPPER_BOUND])/2.0;
							initX.set(0,i,value);
						}else{					
							initX.set(0,i,statistic[0]);
						}
					}else{
						String varName = (String)inputs.elementAt(i-sic);
						Variable colObj = prep.getVariableFromVariableName(varName);
  						if(!states.contains(varName) && !stateInputs.contains(varName)){
							double[] statistic = colObj.getStatistics();
							double[] bb = getBounds(varName);
							if(statistic[0] <bb[NolObjective.LOWER_BOUND] 
								|| statistic[0] > bb[NolObjective.UPPER_BOUND]){
								double value  = (bb[NolObjective.LOWER_BOUND]+bb[NolObjective.UPPER_BOUND])/2.0;
								initX.set(0,sic+cc,value);
							}else{					
								initX.set(0,sic+cc,statistic[0]);
							}
							cc++;
						}
					}
				}
			}
		}
		return initX;
	}

/** Calculate the NolOptimization*/
	public void calculationOptimization() throws MathException {
		if(isCalculated){
			return;
		}
		if (objectiveFactory == null){
			objectiveFactory = new ObjectiveFactory();
		}
//		if(NMAX<=0){
		if(NMAX<=10000){ //Change for testing.
			NMAX = 10000;
		}
		if(simplexP == null){
			simplexP = Matlib.createMatrix();
		}
		Vector inputs = optModel.getInputs();
		Vector outputs = optModel.getOutputs();
		Vector manis = optModel.getManipulate();
		Vector exogs = optModel.getExogenous();
		IPreprocessor prep = optModel.getPreprocessor();
		int nin = optModel.getNin();
		if(DEBUG.debugFlag)
			System.out.println("optModel="+optModel.parametersToString());
		int nout = optModel.getNout();
		boolean[] varMask = new boolean[nin];
			Matrix xBounds = Matlib.zeros(5,nin);
			Matrix xCosts = Matlib.zeros(4,nin);
			Matrix yBounds = Matlib.zeros(5,nout);
			Matrix yCosts = Matlib.zeros(4,nout);
		if (optModel.getModel() != null && optModel.getStateModel() == null) {
			for (int i = 0, k = 0; k < inputs.size(); k++) {
				String varName = (String) inputs.elementAt(k);
				long[] inputDelays = (long[])optModel.getInputDelays().elementAt(k);
				for (int j = 0; j < inputDelays.length; j++) {
					varMask[i] = manis.contains(varName);
					fillRequirements(varName, i++, xCosts, xBounds, inputDelays[j]);
				}
			}
			for(int i=0, k=0; k<nout; k++){
				String varName = (String)outputs.elementAt(k);
				long[] outputDelays = (long[])optModel.getOutputDelays().elementAt(k);
				for(int j=0; j<outputDelays.length; j++) {
					fillRequirements(varName, i++, yCosts, yBounds,outputDelays[j]);
				}
			}
			try{
				objective = objectiveFactory.createObjective(optModel, varMask,
						xBounds, xCosts, yBounds, yCosts);
			}catch(MathException evt){
				Matlib.clear(xBounds);
				Matlib.clear(xCosts);
				Matlib.clear(yBounds);
				Matlib.clear(yCosts);
				objective.clearMatrices();
				statusMessage = evt.getMessage();
				statusFlag = 3;
				return;
			}
			Matlib.clear(xBounds);
			Matlib.clear(xCosts);
			Matlib.clear(yBounds);
			Matlib.clear(yCosts);
			Matrix X0 = getInitX();
			objective.createSimplex(X0,simplexP);
			Simplex plex = new Simplex();
			plex.setMaxIteration(NMAX);
			plex.optimize(objective,simplexP);
			statusMessage = plex.getStatusMessage();
			statusFlag = plex.getStatusFlag();
			objective.evaluateModel(simplexP,X,Y);
			Matlib.getRow(X,0,X);
			Matlib.getRow(Y,0,Y);
			Matrix temp = Matlib.createMatrix();
			objective.evaluate(X,temp);
			F = temp.get(0);
			objective.clearMatrices();
			Matlib.clear(temp);
		}else if(optModel.getStateModel()!=null){
			Vector stateInputs = optModel.getStateInput();
			Vector states = optModel.getState();
			int sic = stateInputs.size();
			int ic = inputs.size();
			int sc = states.size();
			int cc = 0;
			for(int k=0; k<ic+sic; k++){
				if(k<sic){
					String varName = (String)stateInputs.elementAt(k);
					long[] stateInputDelays = (long[])optModel.getStateInputDelays().elementAt(k);
					for (int j=0; j<stateInputDelays.length; j++) {
						if(manis.contains(varName)){
							varMask[k] = true;
						}else if(exogs.contains(varName)){
							varMask[k] = false;
						}
					fillRequirements(varName, k, xCosts, xBounds, stateInputDelays[j]);
					}
				}else{
					String varName = (String)inputs.elementAt(k-sic);
					long[] inputDelays = (long[])optModel.getInputDelays().elementAt(k-sic);
					for (int j=0; j<inputDelays.length; j++) {
						if (!states.contains(varName)
								&& !stateInputs.contains(varName)) {
							if(manis.contains(varName)){
								varMask[sic+cc] = true;
							}else if(exogs.contains(varName)){
								varMask[sic+cc] = false;
							}
							fillRequirements(varName, sic + cc, xCosts, xBounds, inputDelays[j]);
							cc++;
						}
					}
				}
			}
			
			for(int i=0;i<nout;i++){
				String varName = "";
				if(i<sc){
					varName = (String)states.elementAt(i);
				}else{
					varName = (String)outputs.elementAt(i-sc);
				}
				fillRequirements(varName, i, yCosts, yBounds, 0);
			}
			try{
				objective = objectiveFactory.createObjective(optModel, varMask,
						xBounds, xCosts, yBounds, yCosts);
			}catch(MathException evt){
				Matlib.clear(xBounds);
				Matlib.clear(xCosts);
				Matlib.clear(yBounds);
				Matlib.clear(yCosts);
				objective.clearMatrices();
				statusMessage = evt.getMessage();
				statusFlag = 3;
				return;
			}
			Matlib.clear(xBounds);  //gchen 2.8.98
			Matlib.clear(xCosts);  //gchen 2.8.98
			Matlib.clear(yBounds);//gchen 2.8.98
			Matlib.clear(yCosts); //gchen 2.8.98
			Matrix X0 = getInitX();
			if(DEBUG.debugFlag)
				Matlib.disp(X0,"X0=");
			objective.createSimplex(X0,simplexP);
			Simplex plex = new Simplex();
			plex.setMaxIteration(NMAX);
			plex.optimize(objective,simplexP);
			statusMessage = plex.getStatusMessage();
			statusFlag = plex.getStatusFlag();
			if(DEBUG.debugFlag)
				Matlib.disp(simplexP,"simplexP=");
			objective.evaluateModel(simplexP,X,Y);
			Matlib.getRow(X,0,X);
			Matlib.getRow(Y,0,Y);		
			Matrix temp = Matlib.createMatrix();
			objective.evaluate(X,temp);
			F = temp.get(0);
			if(DEBUG.debugFlag)
				Matlib.disp(temp,"	F = ");
			objective.clearMatrices();
			Matlib.clear(temp);
		}
		if(DEBUG.debugFlag){
			Matlib.disp(X,"	X = ");
			Matlib.disp(Y,"	Y = ");
		}
		isCalculated = true;	
	}
/*
private void fillRequirements(String varName, int i, Matrix xCosts,
		Matrix xBounds) {
	double[] ww = (double[]) weights.get(varName);
	double[] bb = (double[]) getBounds(varName); 
	xCosts.set(NolObjective.LINEAR_TERM, i,	ww[NolObjective.LINEAR_TERM]);  
	xCosts.set(NolObjective.QUAD_TERM, i, ww[NolObjective.QUAD_TERM]);
	xCosts.set(NolObjective.LOWER_BOUNDS_TERM, i,
			ww[NolObjective.LOWER_BOUNDS_TERM]);  
	xCosts.set(NolObjective.UPPER_BOUNDS_TERM, i,
			ww[NolObjective.UPPER_BOUNDS_TERM]);

	xBounds.set(NolObjective.LOWER_BOUND, i, bb[NolObjective.LOWER_BOUND]);  
	xBounds.set(NolObjective.SOFT_LOWER_BOUND, i, 
			bb[NolObjective.SOFT_LOWER_BOUND]);
	xBounds.set(NolObjective.SET_POINT, i, bb[NolObjective.SET_POINT]);  
	xBounds.set(NolObjective.SOFT_UPPER_BOUND, i, 
			bb[NolObjective.SOFT_UPPER_BOUND]);
	xBounds.set(NolObjective.UPPER_BOUND, i, bb[NolObjective.UPPER_BOUND]);
}
*/
private void fillRequirements(String varName, int i, Matrix xCosts,
		Matrix xBounds, long delay) {
	double[] ww = (double[]) weights.get(varName); 
	double[] bb = (double[]) getBounds(varName, delay);
	xCosts.set(NolObjective.LINEAR_TERM, i,	ww[NolObjective.LINEAR_TERM]);  
	xCosts.set(NolObjective.QUAD_TERM, i, ww[NolObjective.QUAD_TERM]);
	xCosts.set(NolObjective.LOWER_BOUNDS_TERM, i,
			ww[NolObjective.LOWER_BOUNDS_TERM]);  
	xCosts.set(NolObjective.UPPER_BOUNDS_TERM, i,
			ww[NolObjective.UPPER_BOUNDS_TERM]);

	xBounds.set(NolObjective.LOWER_BOUND, i, bb[NolObjective.LOWER_BOUND]);  
	xBounds.set(NolObjective.SOFT_LOWER_BOUND, i, 
			bb[NolObjective.SOFT_LOWER_BOUND]);
	xBounds.set(NolObjective.SET_POINT, i, bb[NolObjective.SET_POINT]);  
	xBounds.set(NolObjective.SOFT_UPPER_BOUND, i, 
			bb[NolObjective.SOFT_UPPER_BOUND]);
	xBounds.set(NolObjective.UPPER_BOUND, i, bb[NolObjective.UPPER_BOUND]);
}

/** Calculate the NolOptimization*/
	public void reCalulationOptimization(Matrix P, int NMAX)
			throws MathException {
		
		this.NMAX = NMAX;
		if(objective != null){
			if(simplexP == null){
				simplexP= P;
			}else{
				if(!P.equals(simplexP)){
					Matlib.clear(simplexP); 
					simplexP = P;
				}
			}
			Simplex plex = new Simplex();
			plex.setMaxIteration(NMAX);
			plex.optimize(objective,simplexP);
			statusMessage = plex.getStatusMessage();
			statusFlag = plex.getStatusFlag();
			if(DEBUG.debugFlag)
				Matlib.disp(simplexP,"simplexP=");
			objective.evaluateModel(simplexP,X,Y);
			objective.clearMatrices();
			Matlib.getRow(X,0,X);
			Matlib.getRow(Y,0,Y);		
		}
	}

/** Clear the internal matrices*/
	public void clearMatrices(){
		Matlib.clear(simplexP); 
		Matlib.clear(X); 
		Matlib.clear(Y); 
	}

/** Set Max Iteration number*/
	public void setMaxIteration(int n){
		NMAX = n;
	}

/** Get Max Iteration number*/
	public int getMaxIteration(){
		return NMAX;
	}

/** Return the status flag of the optimization problem.*/
	public int getStatusFlag(){
		return statusFlag;
	}

/** Return the status message of the optimization problem.*/
	public String getStatusMessage(){
		return statusMessage;
	}

	public INolObjective getObjective() {
		return objective;
	}

	public void setObjectiveFactory(IObjectiveFactory factory) {
		objectiveFactory = factory;
	}

	public void setInitXDirectly(Matrix initX) {
		this.initX = initX;
	}

}