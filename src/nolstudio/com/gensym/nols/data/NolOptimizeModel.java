package com.gensym.nols.data;
/*
 *		Gensym NolOptimizeModel Class.
 *		This class is extended from Object.class
 *		Modified 3/25/98 by Gchen
 */

import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.Model;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.matrix.TimeFunctions;

/** Model class. */
public class NolOptimizeModel extends NolModel2 implements INolOptimizeModel,
		Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected Vector stateDelays;
	protected Vector stateInputDelays;
	protected Vector state;
	protected Vector stateInput;
	protected Vector manipulate;
	protected Vector exogenous;
	protected Model stateModel;

/** Create a null data Model object. */	
	public NolOptimizeModel() {
		super();
		stateDelays = new Vector();
		stateInputDelays = new Vector();
		state = new Vector();
		stateInput = new Vector();
		manipulate = new Vector();
		exogenous = new Vector();
	}

/** Create a Model object with given EnsembleModel object.*/	
	public NolOptimizeModel(EnsembleModel net1, String name, Vector outs, 
		Vector ins, Vector manis, Vector exogs, Vector outDelays,
		Vector inDelays, Preprocessor prep) {
		super(net1,name,outs,ins,outDelays,inDelays,prep);
		
		state = new Vector();
		stateInput = new Vector();
		try{
			manipulate = (Vector)manis.clone();
			exogenous = (Vector)exogs.clone();
		}catch(Exception e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
	}

/** Create a Model object with given EnsembleModel object.*/	
	public NolOptimizeModel(EnsembleModel net1, EnsembleModel net2, String name, 
		Vector outs, Vector ins, Vector states, Vector stateInp, 
		Vector manis, Vector exogs, Vector outDelays,Vector inDelays,
		Vector stDelays,Vector stinpDelays,Preprocessor prep) {		
		this(net1,name,outs,ins,manis,exogs,outDelays,inDelays,prep);
		stateModel = net2;
		try{
			this.state = (Vector)states.clone();
			this.stateDelays = (Vector)stDelays.clone();
			this.stateInput = (Vector)stateInp.clone();
			this.stateInputDelays = (Vector)stinpDelays.clone();
		}catch(Exception e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		NolOptimizeModel cloned = (NolOptimizeModel) super.clone();
		cloned.stateInputDelays = stateInputDelays == null ? null : (Vector) stateInputDelays.clone();
		cloned.stateDelays  = stateDelays == null  ? null : (Vector) stateDelays.clone();
		cloned.stateInput   = stateInput  == null  ? null : (Vector) stateInput.clone();
		cloned.manipulate = manipulate == null ? null : (Vector) manipulate.clone();
		cloned.exogenous  = exogenous == null  ? null : (Vector) exogenous.clone();
		cloned.state   = state  == null  ? null : (Vector) state.clone();
		
		return cloned;
	}
	
	@Override
	public Model getStateModel() {
		return stateModel;
	}

	@Override
	public Vector getStateInput(){
		return stateInput;
	}

	@Override
	public Vector getState(){
		return state;
	}

	@Override
	public Vector getManipulate(){
		return manipulate;
	}

	@Override
	public Vector getExogenous(){
		return exogenous;
	}

	@Override
	public Vector getStateInputDelays(){
		return stateInputDelays;
	}

	@Override
	public Vector getStateDelays(){
		return stateDelays;
	}

/** toString method*/
	@Override
	public String modelToString(){
		String s = "";
		s = this.name+"(";
		for(int i=0;i<inputs.size();i++){
			s=s+inputs.elementAt(i).toString();
			if(i<inputs.size()-1){
				s = s+",";
			}
		}
		s = s +")";
		return s;
	}

/** toString method*/
	@Override
	public String parametersToString(){
		String s = this.name+"\nInputs:\n";
		for(int i=0;i<inputs.size();i++){
			s=s+inputs.elementAt(i).toString();
			if(i<inputs.size()-1){
				s = s+",";
			}
		}
		s = s +"\nState:\n";
		for(int i=0;i<state.size();i++){
			s=s+state.elementAt(i).toString();
			if(i<state.size()-1){
				s = s+",";
			}
		}
		s = s +"\nManipulate:\n";
		for(int i=0;i<manipulate.size();i++){
			s=s+manipulate.elementAt(i).toString();
			if(i<manipulate.size()-1){
				s = s+",";
			}
		}
		s = s +"\nState Inputs:\n";
		for(int i=0;i<stateInput.size();i++){
			s=s+stateInput.elementAt(i).toString();
			if(i<stateInput.size()-1){
				s = s+",";
			}
		}
		s = s +"\nexogenous:\n";
		for(int i=0;i<exogenous.size();i++){
			s=s+exogenous.elementAt(i).toString();
			if(i<exogenous.size()-1){
				s = s+",";
			}
		}
		return s;
	}

	@Override
	public int getNin(){
		int manipulateCount = 0;
		for (int i = 0; i < manipulate.size(); ++i) {
			manipulateCount += ((long[]) inputDelays.get(i)).length;
	}
		return manipulateCount + exogenous.size();
	}

	@Override
	public int getNout(){
		return state.size()+model.getNout();
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		if(model==null) {
			throw new MathException("Optimization model missing both models!");
		}
		if(stateModel==null){
			model.evaluate(X,Y);
		}else{
			int sic = stateInput.size();
			int row = X.getRows();
			Matrix I = Matlib.createMatrix(row,sic);
			for(int c=0;c<sic;c++){
				for(int r=0;r<row;r++){
					I.set(r,c,X.get(r,c));
				}
			}
			Matrix dPred = Matlib.createMatrix();
			stateModel.evaluate(I,dPred);
			int ic = inputs.size();
			Matrix XTemp = Matlib.createMatrix(row,ic);
			int cc=0;
 			for(int c=0;c<ic;c++){
				String colObj = (String)inputs.elementAt(c);
				int indepIndex = stateInput.indexOf(colObj);
				int stateIndex = state.indexOf(colObj);
				if(indepIndex != -1){
					for(int r=0;r<row;r++){
						XTemp.set(r,c,I.get(r,indepIndex));
					}
				}else if(stateIndex != -1){
					for(int r=0;r<row;r++){
						XTemp.set(r,c,dPred.get(r,stateIndex));
					}
				}else{
					for(int r=0;r<row;r++){
						XTemp.set(r,c, X.get(r,sic+cc));
					}
					cc++;
				}
			}
			Matrix yPred = Matlib.createMatrix();
			model.evaluate(XTemp,yPred);
			int sc = dPred.getCols();
			int oc = yPred.getCols();
			Y.redimension(row,sc+oc);
 			for(int c=0;c<Y.getCols();c++){
				if(c < sc){
					for(int r=0;r<row;r++){
						Y.set(r,c,dPred.get(r,c));
					}
				}else{
					for(int r=0;r<row;r++){
						Y.set(r,c,yPred.get(r,c-sc));
					}
				}
			}
			Matlib.clear(I);
			Matlib.clear(XTemp);		
			Matlib.clear(dPred);
			Matlib.clear(yPred);		
		}
	}

	public long[] prepareTrainingSet2(Matrix I, Matrix D) throws MathException{
		Vector inVars = new Vector(stateInput.size());
		Vector outVars = new Vector(state.size());
		for(int i=0;i<state.size();i++){
			String varName = (String)state.elementAt(i);
			Variable varObj = preprocessor.getVariableFromVariableName(varName);
  			outVars.addElement(varObj);
		}
		for(int i=0;i<stateInput.size();i++){
			String varName = (String)stateInput.elementAt(i);
			Variable varObj = preprocessor.getVariableFromVariableName(varName);
			inVars.addElement(varObj);
		}

		if(hasTimeStamps)
			return TimeFunctions.createTrainingSet(inVars, stateInputDelays, outVars, I,D);
		TimeFunctions.createTrainingSet(inVars,outVars,I,D);
		return null;
	}

	@Override
	public long[] prepareTrainingSet2FromDataSeries(Vector processedData, Matrix I, Matrix D) throws MathException{
		Vector inVars = new Vector(stateInput.size());
		Vector outVars = new Vector(state.size());
		for(int i=0;i<state.size();i++){
			String varName = (String)state.elementAt(i);
			Variable varObj = getVariableFromVariableName(processedData,varName);
  			outVars.addElement(varObj);
		}
		for(int i=0;i<stateInput.size();i++){
			String varName = (String)stateInput.elementAt(i);
			Variable varObj = getVariableFromVariableName(processedData, varName);
			inVars.addElement(varObj);
		}
		if(hasTimeStamps)
			return TimeFunctions.createTrainingSet(inVars, stateInputDelays, outVars, I, D);
		TimeFunctions.createTrainingSet(inVars,outVars, I, D);
		return null;
	}
}
