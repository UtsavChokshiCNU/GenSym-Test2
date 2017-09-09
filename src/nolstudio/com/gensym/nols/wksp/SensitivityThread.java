package com.gensym.nols.wksp;

import java.awt.Toolkit;
import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;
import com.gensym.nols.data.NolModel2;
import com.gensym.nols.data.NolOptimizeModel;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Variable;
import com.gensym.nols.dlg.NolProgressBarDialog;
import com.gensym.nols.dlg.ProgressEvent;

public class SensitivityThread implements Runnable, Cloneable, Serializable {   // why Serializable??
	private NolProgressBarDialog progressDialog;
	private NolModel2 model;
	private NolSensitivityWKSP wksp;
	private Matrix signedSensitivityValues;
	private Matrix absSensitivityValues;
	private Vector inputVars;
	private Vector outVars;
	private Vector ratings;
	private Matrix sampleMatrix;

	private Matrix signedSensitivityValues1;
	private Matrix absSensitivityValues1;
	private Vector inputVars1;
	private Vector outVars1;
	private Vector ratings1;
	private Matrix sampleMatrix1;

	private boolean hasTwoEnsembles;

	public SensitivityThread(NolSensitivityWKSP wksp, NolModel2 model,
		Matrix signedSensitivityValues,Matrix absSensitivityValues,Vector inputVars, Matrix sampleMatrix,
		Matrix signedSensitivityValues1,Matrix absSensitivityValues1,Vector inputVars1, Matrix sampleMatrix1){
		this.wksp = wksp;
		this.model = model;
		this.signedSensitivityValues = signedSensitivityValues;
		this.absSensitivityValues = absSensitivityValues;
		this.inputVars = inputVars;
		if(sampleMatrix != null)
			this.sampleMatrix = sampleMatrix;
		else
			this.sampleMatrix = null;

		this.signedSensitivityValues1 = signedSensitivityValues1;
		this.absSensitivityValues1 = absSensitivityValues1;
		this.inputVars1 = inputVars1;
		if(sampleMatrix1 != null)
			this.sampleMatrix = sampleMatrix1;
		else
			this.sampleMatrix1 = null;
		hasTwoEnsembles = true;
	}

	public SensitivityThread(NolSensitivityWKSP wksp, NolModel2 model,
		Matrix signedSensitivityValues,Matrix absSensitivityValues,Vector inputVars, Matrix sampleMatrix){
		this.wksp = wksp;
		this.model = model;
		this.signedSensitivityValues = signedSensitivityValues;
		this.absSensitivityValues = absSensitivityValues;
		this.inputVars = inputVars;
		if(sampleMatrix != null)
			this.sampleMatrix = sampleMatrix;
		else
			this.sampleMatrix = null;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		SensitivityThread cloned = (SensitivityThread) super.clone();
		
		cloned.model = model == null ? null : (NolModel2) model.clone();
		cloned.signedSensitivityValues = signedSensitivityValues == null ? null : (Matrix) signedSensitivityValues.clone();
		cloned.absSensitivityValues = absSensitivityValues == null ? null : (Matrix) absSensitivityValues.clone();
		cloned.inputVars = inputVars == null ? null : (Vector) inputVars.clone();
		cloned.outVars = outVars == null ? null : (Vector) outVars.clone();
		cloned.ratings = ratings == null ? null : (Vector) ratings.clone();
		cloned.sampleMatrix = sampleMatrix == null ? null : (Matrix) sampleMatrix.clone();

		cloned.signedSensitivityValues1 = signedSensitivityValues1 == null ? null : (Matrix) signedSensitivityValues1.clone();
		cloned.absSensitivityValues1 = absSensitivityValues1 == null ? null : (Matrix) absSensitivityValues1.clone();
		cloned.inputVars1 = inputVars1 == null ? null : (Vector) inputVars1.clone();
		cloned.outVars1 = outVars1 == null ? null : (Vector) outVars1.clone();
		cloned.ratings1 = ratings1 == null ? null : (Vector) ratings1.clone();
		cloned.sampleMatrix1 = sampleMatrix1 == null ? null : (Matrix) sampleMatrix1.clone();
		
		return cloned;
	}

	@Override
	public void run () {
		if(hasTwoEnsembles){
			Preprocessor prep = model.getPreprocessor();//	  Saved old one from gchen 5.26.99
			Matrix X = Matlib.createMatrix();
			Matrix Y = Matlib.createMatrix();
			Matrix D = Matlib.createMatrix();
			Matrix I = Matlib.createMatrix();
			try{
				model.prepareTrainingSet(X, Y);
				((NolOptimizeModel)model).prepareTrainingSet2(I, D);
			} catch(MathException evt){
				System.err.println("Non-fatal exception preparing training data: "+evt.getMessage());
				evt.printStackTrace();
			}
			EnsembleModel ensemble = (EnsembleModel)model.getModel();
			EnsembleModel ensemble1 = (EnsembleModel)((NolOptimizeModel)model).getStateModel();
			int row = X.getRows();
			int ni = X.getCols();
			int no = Y.getCols();
			for(int c=0;c<no;c++){
				for(int r=0;r<ni;r++){
					signedSensitivityValues.set(r,c,0.0);
					absSensitivityValues.set(r,c,0.0);
				}
			}
			
			Matrix sampledX = Matlib.createMatrix();
			Matrix sampledY = Matlib.createMatrix();			
			Matrix pX = Matlib.createMatrix(1,ni);
			Matrix nX = Matlib.createMatrix(1,ni);
			Matrix pY = Matlib.createMatrix(1,no);
			Matrix nY = Matlib.createMatrix(1,no);
			Matrix singleY = Matlib.createMatrix(1,no);
			int rCount = 100;
			if(row < 100){
				rCount = row;
			}

			int row1 = I.getRows();
			int ni1 = I.getCols();
			int no1 = D.getCols();
			for(int c=0;c<no1;c++){
				for(int r=0;r<ni1;r++){
					signedSensitivityValues1.set(r,c,0.0);
					absSensitivityValues1.set(r,c,0.0);
				}
			}
			Matrix sampledI = Matlib.createMatrix();
			Matrix sampledD = Matlib.createMatrix();			
			Matrix pI = Matlib.createMatrix(1,ni1);
			Matrix nI = Matlib.createMatrix(1,ni1);
			Matrix pD = Matlib.createMatrix(1,no1);
			Matrix nD = Matlib.createMatrix(1,no1);
			Matrix singleD = Matlib.createMatrix(1,no1);
			int rCount1 = 100;
			if(row1 < 100){
				rCount1 = row1;
			}

			
			progressDialog = new NolProgressBarDialog(wksp.getFrame(),
				"Sensitivity Progress", "Calculating, please wait...", rCount+rCount1);
			progressDialog.setLocation(300,300);
			progressDialog.setSize(250,150);
			progressDialog.setVisible(true);
			progressDialog.setThread(Thread.currentThread()); 
			try{
				if(row < 100){
					Matlib.copy(X,sampledX);
					Matlib.copy(Y,sampledY);
				}else{
					if(sampleMatrix == null || sampleMatrix.getRows() != X.getRows()){
						sampleMatrix = Matlib.createMatrix(X.getRows(),1);
						Stats.randomSplit(X.getRows(),100,sampleMatrix);
					}
					Matlib.getRows(X,sampleMatrix,sampledX);
					Matlib.getRows(Y,sampleMatrix,sampledY);
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
						Matlib.getRow(X,r,pX);
						Matlib.getRow(X,r,nX);
						pX.set(0,i,pX.get(0,i)+deltas[i]);
						nX.set(0,i,nX.get(0,i)-deltas[i]);
						ensemble.evaluate(pX,pY);
						ensemble.evaluate(nX,nY);
						Matlib.subtract(pY,nY,singleY);
						Matlib.divide(singleY,deltas[i]*2,singleY);
						Matlib.multiply(singleY,stds[i],singleY);
						for(int c=0;c<no;c++){
							signedSensitivityValues.set(i,c,signedSensitivityValues.get(i,c)+singleY.get(0,c));
							absSensitivityValues.set(i,c,absSensitivityValues.get(i,c)+Math.abs(singleY.get(0,c)));
						}
					}
					ProgressEvent e = new ProgressEvent();
					progressDialog.valueChanged(e);			
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
			Matlib.clear(sampledY);

			try{
				if(row1 < 100){
					Matlib.copy(I,sampledI);
					Matlib.copy(D,sampledD);
				}else{
					if(sampleMatrix1 == null || sampleMatrix1.getRows() != I.getRows()){
						sampleMatrix1 = Matlib.createMatrix(I.getRows(),1);
						Stats.randomSplit(I.getRows(),100,sampleMatrix1);
					}
					Matlib.getRows(I,sampleMatrix1,sampledI);
					Matlib.getRows(D,sampleMatrix1,sampledD);
				}
				double[] deltas = new double[ni1];
				double[] stds = new double[ni1];
				for(int i=0;i<ni1;i++){
					String varName = (String)inputVars1.elementAt(i);
					Variable colObj = prep.getVariableFromVariableName(varName);
					deltas[i] = colObj.getRange()/200;
					stds[i] = colObj.getSTD();
				}
				for(int r=0;r<rCount1;r++){
					for(int i=0;i<ni1;i++){
						Matlib.getRow(I,r,pI);
						Matlib.getRow(I,r,nI);
						pI.set(0,i,pI.get(0,i)+deltas[i]);
						nI.set(0,i,nI.get(0,i)-deltas[i]);
						ensemble1.evaluate(pI,pD);
						ensemble1.evaluate(nI,nD);
						Matlib.subtract(pD,nD,singleD);
						Matlib.divide(singleD,deltas[i]*2,singleD);
						Matlib.multiply(singleD,stds[i],singleD);
						for(int c=0;c<no1;c++){
							signedSensitivityValues1.set(i,c,signedSensitivityValues1.get(i,c)+singleD.get(0,c));
							absSensitivityValues1.set(i,c,absSensitivityValues1.get(i,c)+Math.abs(singleD.get(0,c)));
						}
					}
					ProgressEvent e = new ProgressEvent();
					progressDialog.valueChanged(e);			
				}		
			}catch(MathException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}

			if(rCount1 > 0 ){
				for(int i=0;i<ni1;i++){
					for(int c=0;c<no1;c++){
						signedSensitivityValues1.set(i,c,signedSensitivityValues1.get(i,c)/rCount1);
						absSensitivityValues1.set(i,c,absSensitivityValues1.get(i,c)/rCount1);
					}
				}
			}
			Matlib.clear(pI);
			Matlib.clear(nI);
			Matlib.clear(pD);
			Matlib.clear(nD);
			Matlib.clear(singleD);
			Matlib.clear(sampledI);
			Matlib.clear(sampledD);

			Toolkit.getDefaultToolkit().beep();
			progressDialog.dispose();
			wksp.endSensitivityCalculation();	
		}else{
			Preprocessor prep = model.getPreprocessor();//	  Saved old one from gchen 5.26.99
			Matrix X = Matlib.createMatrix();
			Matrix Y = Matlib.createMatrix();
			try{
				model.prepareTrainingSet(X, Y);
			} catch(MathException evt){
				System.err.println("Non-fatal exception preparing training data: "+evt.getMessage());
				evt.printStackTrace();
			}
			int row = X.getRows();
			int ni = X.getCols();
			int no = Y.getCols();
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
			progressDialog = new NolProgressBarDialog(wksp.getFrame(),
				"Sensitivity Progress", "Calculating, please wait...", rCount);
			progressDialog.setLocation(300,300);
			progressDialog.setSize(250,150);
			progressDialog.setVisible(true);
			progressDialog.setThread(Thread.currentThread()); 
			try{
				if(row < 100){
					Matlib.copy(X,sampledX);
					Matlib.copy(Y,sampledY);
				}else{
					if(sampleMatrix == null || sampleMatrix.getRows() != X.getRows()){
						sampleMatrix = Matlib.createMatrix(X.getRows(),1);
						Stats.randomSplit(X.getRows(),100,sampleMatrix);
					}
					Matlib.getRows(X,sampleMatrix,sampledX);
					Matlib.getRows(Y,sampleMatrix,sampledY);
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
					ProgressEvent e = new ProgressEvent();
					progressDialog.valueChanged(e);			
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
			Matlib.clear(sampledY);
			Toolkit.getDefaultToolkit().beep();
			progressDialog.dispose();
			wksp.endSensitivityCalculation();	
		}
	}
}