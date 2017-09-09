package com.gensym.nols.data;
/*
 */

import java.util.*;
import java.io.*;	   

import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;

public class NolModelTrainThread implements Runnable,
	Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	private EnsembleModel ensemble1;
	private Matrix input1;
	private Matrix output1;
	private EnsembleModel ensemble2;
	private Matrix input2;
	private Matrix output2;
	private Vector itsListeners;

	public NolModelTrainThread(EnsembleModel ensemble ){
		super();
		this.ensemble1 = ensemble;
		itsListeners = new Vector();
	}

	public void addListener(ModelTrainerListener l) {
		itsListeners.addElement(l);
	}

	public void removeListener(ModelTrainerListener l) {
		itsListeners.removeElement(l);
	}

	private void informListeners() {
		for (int i=0; i<itsListeners.size(); ++i) {
			ModelTrainerListener l = (ModelTrainerListener) itsListeners.elementAt(i);
			l.trainingComplete();
		}
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		NolModelTrainThread cloned = (NolModelTrainThread) super.clone();
		cloned.ensemble1 = ensemble1 == null ? null : (EnsembleModel) ensemble1.clone();
		cloned.input1 = input1 == null ? null : (Matrix) input1.clone();
		cloned.output1 = output1 == null ? null : (Matrix) output1.clone();
		cloned.ensemble2 = ensemble2 == null ? null : (EnsembleModel) ensemble2.clone();
		cloned.input2 = input2 == null ? null : (Matrix) input2.clone();
		cloned.output2 = output2 == null ? null : (Matrix) output2.clone();
		cloned.itsListeners = itsListeners == null ? null : (Vector) itsListeners.clone();

		return cloned;
	}

	@Override
	public void run (){
		try{
			if(input1 != null && output1 != null){
				if(ensemble1.getTrainingTime()>0){
					ensemble1.train(input1,output1);
				}
			}
			if(input2 != null && output2 != null){
				if(ensemble2.getTrainingTime()>0){
					ensemble2.train(input2,output2);
				}
			}
			informListeners();
		}catch(MathException evt){
			System.err.println("Exception in building with MathException " + evt.getMessage());
			evt.printStackTrace();
		}
	}


	public void setEnsembleModel1(EnsembleModel ensemble){
		this.ensemble1 = ensemble;
	}

	public void setEnsembleModel2(EnsembleModel ensemble){
		this.ensemble2 = ensemble;
	}

	public EnsembleModel getEnsembleModel1(){
		return this.ensemble1;
	}
	
	public EnsembleModel getEnsembleModel2(){
		return this.ensemble2;
	}
	
	public void setTrainingTimeForModel1(long timeInMilli){
		if(ensemble1 != null){
			ensemble1.setTrainingTime(timeInMilli); 

		}
	}

	public void setTrainingTimeForModel2(long timeInMilli){
		if(ensemble2 != null){
			ensemble2.setTrainingTime(timeInMilli); 

		}
	}

	public void addModel1Listener(EnsembleModelListener l){
		if(ensemble1 != null){
			ensemble1.addListener(l); 
		}
	}
	
	public void addModel2Listener(EnsembleModelListener l){
		if(ensemble2 != null){
			ensemble2.addListener(l); 
		}
	}
	
	public void setInput1(Matrix X){
		input1 = X;
	}

	public void setInput2(Matrix X){
		input2 = X;
	}

	public Matrix getInput1(){
		return input1;
	}

	public Matrix getInput2(){
		return input2;
	}

	public void setOutput1(Matrix Y){
		output1 = Y;
	}

	public void setOutput2(Matrix Y){
		output2 = Y;
	}

	public Matrix getOutput1(){
		return output1;
	}

	public Matrix getOutput2(){
		return output2;
	}
}