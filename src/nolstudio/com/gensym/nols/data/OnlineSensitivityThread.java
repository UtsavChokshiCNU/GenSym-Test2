package com.gensym.nols.data;

import java.awt.Toolkit;
import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;
import com.gensym.nols.deploy.NolG2Gateway;


public class OnlineSensitivityThread implements Runnable, Cloneable, Serializable {   // why Serializable??
	private NolModel2 model;
	private NolG2Gateway gateway;
	private Matrix signedSensitivityValues;
	private Vector inputVars;
	private Vector outVars;
	private Vector ratings;
	private Matrix X;
	private Matrix Y;
	private Vector calculatingDataSeries;
	private String modelUUID;

	public OnlineSensitivityThread(String modelUUID, NolG2Gateway gateway, NolModel2 model,
		Matrix signedSensitivityValues,Vector inputVars, Vector calculatingDataSeries){
		this.gateway = gateway;
		this.model = model;
		this.signedSensitivityValues = signedSensitivityValues;
		this.inputVars = inputVars;
		this.calculatingDataSeries = calculatingDataSeries;
		this.modelUUID = modelUUID;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		OnlineSensitivityThread cloned = (OnlineSensitivityThread) super.clone();
		cloned.model = model == null ? null : (NolModel2) model.clone();
		cloned.signedSensitivityValues = signedSensitivityValues == null ? null : (Matrix) signedSensitivityValues.clone();
		cloned.X = X == null ? null : (Matrix) X.clone();
		cloned.Y = Y == null ? null : (Matrix) Y.clone();
		cloned.inputVars = inputVars == null ? null : (Vector) inputVars.clone();
		cloned.outVars = outVars == null ? null : (Vector) outVars.clone();
		cloned.ratings = ratings == null ? null : (Vector) ratings.clone();
		cloned.calculatingDataSeries = calculatingDataSeries == null ? null : (Vector) calculatingDataSeries.clone();

		return cloned;
	}


	@Override
	public void run () {
		Matrix matrixX = Matlib.createMatrix();
		Matrix matrixY = Matlib.createMatrix();
		Preprocessor prep = model.getPreprocessor();//	  Saved old one from gchen 5.26.99
		try{
			model.prepareTrainingSetFromDataSeries(calculatingDataSeries,matrixX,matrixY);
		} catch(MathException evt){
			System.err.println("Non-fatal exception preparing training data: "+evt.getMessage());
			evt.printStackTrace();
		}
		int row = matrixX.getRows();
		int ni = matrixX.getCols();
		int no = matrixY.getCols();
		for(int c=0;c<no;c++){
			for(int r=0;r<ni;r++){
				signedSensitivityValues.set(r,c,0.0);
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
				Matlib.copy(matrixX,sampledX);
				Matlib.copy(matrixY,sampledY);
			}else{
				Matrix sampleMatrix = Matlib.createMatrix(matrixX.getRows(),1);
				Stats.randomSplit(matrixX.getRows(),100,sampleMatrix);
				Matlib.getRows(matrixX,sampleMatrix,sampledX);
				Matlib.getRows(matrixY,sampleMatrix,sampledY);
			}
			double[] deltas = new double[ni];
			double[] stds = new double[ni];
			for(int i=0;i<ni;i++){
				String varName = (String)inputVars.elementAt(i);
				Variable colObj = prep.getVariableFromVariableName(varName);
				deltas[i] = colObj.getRange()/200;
				stds[i] = colObj.getSTD();
			}
			for(int r=0;r<rCount;r++){
				for(int i=0;i<ni;i++){
					Matlib.getRow(matrixX,r,pX);
					Matlib.getRow(matrixX,r,nX);
					pX.set(0,i,pX.get(0,i)+deltas[i]);
					nX.set(0,i,nX.get(0,i)-deltas[i]);
					model.evaluate(pX,pY);
					model.evaluate(nX,nY);
					Matlib.subtract(pY,nY,singleY);
					Matlib.divide(singleY,deltas[i]*2,singleY);
					Matlib.multiply(singleY,stds[i],singleY);
					for(int c=0;c<no;c++){
						signedSensitivityValues.set(i,c,signedSensitivityValues.get(i,c)+singleY.get(0,c));
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
				}
			}
		}
		Matlib.clear(pX);
		Matlib.clear(nX);
		Matlib.clear(pY);
		Matlib.clear(nY);
		Matlib.clear(singleY);
		Matlib.clear(sampledX);
		Matlib.clear(sampledY);
		Toolkit.getDefaultToolkit().beep();
Matlib.disp(signedSensitivityValues);
		try{
			gateway.endSensitivityCalculation(modelUUID, signedSensitivityValues);	
		}catch(Exception evt){}
	}
}