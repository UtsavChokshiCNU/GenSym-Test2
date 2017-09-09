package com.gensym.math.datafit;

import java.io.*;

import com.gensym.math.matrix.*;
import com.gensym.math.MathException;
import com.gensym.math.Utilities;

public class ValidationParameters implements Serializable {
	static final long serialVersionUID = 1L;
	public Matrix rmse;	// root mean squared error
	public Matrix corrcoef;
	public double chisq;
	public double chisq95;
	public int ndata;

	public ValidationParameters(TrainableModel M, Matrix X, Matrix Y) throws MathException {
		ndata = X.getRows();
		int nout = Y.getCols();
		rmse = Matlib.createMatrix();
		corrcoef = Matlib.createMatrix();
		Matrix YPred = Matlib.createMatrix();
		Matrix chi = Matlib.createMatrix();
		M.evaluate(X,YPred);
		calculateValidationStatistics(Y,YPred,M.outputVariance,rmse,corrcoef,chi);
		Matlib.clear(YPred);
		chisq = chi.get(0);
		chisq95 = chi.get(1);
		Matlib.clear(chi);
	}
	
	public ValidationParameters(ValidationParameters params) {
		ndata = params.ndata;
		rmse = params.rmse == null ? null : new Matrix(params.rmse);
		corrcoef = params.corrcoef == null ? null : new Matrix(params.corrcoef);
		chisq = params.chisq;
		chisq95 = params.chisq95;
	}

	// outputs are rmse, corrcoef and chi.  Chi matrix has two elements, chisq and chisq95
	// YVar is the variance of the output columns, given by the models outputVariance
	public static void calculateValidationStatistics(Matrix Y, Matrix YPred, Matrix YVar, Matrix rmse, Matrix corrcoef, Matrix chi) throws MathException {
		chi.redimension(1,2);
		Matrix Err = Matlib.createMatrix();
		Matrix Errsq = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		Matlib.corrcoef(Y,YPred,corrcoef);
		Matlib.subtract(Y,YPred,Err);
		Matlib.multiplyElements(Err,Err,Errsq);  // squared error, unscaled
		Matlib.clear(Err);
		Matlib.mean(Errsq,rmse);
		Matlib.sqrt(rmse,rmse);
		// now calc chisq and confidence bounds on chisq
		Matlib.divideElements(Errsq,YVar,Errsq);   // scaled squared errors
		Matlib.reshapeToColumn(Errsq,Errsq);
		Matlib.mean(Errsq,temp);   // use mean, not sum, so result is independent of ndata
		double chisq = temp.get(0);
		Matlib.std(Errsq,temp);
		// multiply temp by factor of 2 to get 95% confidence bounds, 
		// divide by sqrt(nout*ndata) for confidence bounds on the mean
		int ndata = Y.getRows();
		int nout = Y.getCols();
		double chisq95 = chisq + 2.0*temp.get(0)/Math.sqrt(((double)ndata)*nout);
		chi.set(0,0,chisq);
		chi.set(0,1,chisq95);
		Matlib.clear(Errsq);
		Matlib.clear(temp);
	}

	// short version, chisq not calculated.  outputs are rmse, corrcoef
	public static void calculateValidationStatistics(Matrix Y, Matrix YPred, Matrix rmse, Matrix corrcoef) throws MathException {
		Matrix Err = Matlib.createMatrix();
		Matrix Errsq = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		Matlib.corrcoef(Y,YPred,corrcoef);
		Matlib.subtract(Y,YPred,Err);
		Matlib.multiplyElements(Err,Err,Errsq);
		Matlib.mean(Errsq,rmse);
		Matlib.sqrt(rmse,rmse);
		Matlib.clear(Err);
		Matlib.clear(Errsq);
		Matlib.clear(temp);
	}

	public String report() {
		String num;
		int digits = 4;
		String S = "root mean squared error 	";
		for(int i=0;i<rmse.getCols();i++) {
			num = Utilities.formatDouble(rmse.get(0,i), digits);
			S += num;
			S += "	";
		}
		S = S + "\ncorrcoef	";
		for(int i=0;i<corrcoef.getCols();i++) {
			num = Utilities.formatDouble(corrcoef.get(0,i), digits);
			S += num;
			S += "	";
		}
		S = S + "\nchisq = "+chisq+"\nchisq95 = "+chisq95; 
		return S;
	}

	public void disp(String S) {
		System.out.println("  ");
		System.out.println(S);
		Matlib.disp(rmse, "	root mean squared error = ");
		Matlib.disp(corrcoef, "    correlation coefficient = ");
		System.out.println("  ");
	}

}