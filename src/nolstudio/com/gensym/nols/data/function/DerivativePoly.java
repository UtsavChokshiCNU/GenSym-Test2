package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;
import com.gensym.math.matrix.*;

public class DerivativePoly extends Function {
	private double maximumTimeWindow;
	
	public DerivativePoly() {
		super();
		maximumTimeWindow = 0.0;
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "DerivativePoly";
	}

	@Override
	public String getDescription() {
		return "C = DerivativePoly(A). Returns the derivative value of A over time. Must have more than 9 points.";
	}

	/** returns the minimum number of input arguments, given current properties */
	@Override
	public int getMinimumInputs() {
		return 1;
	}

	/** returns the maximum number of input arguments, given current properties. */
	@Override
	public int getMaximumInputs() {
		return 1;
	}

	/** returns the number of outputs, given the number of input args */
	@Override
	public int getNumberOfOutputs(int numberOfInputs) {
		return 1;
	}

	@Override
	public void evaluate(long t[], Vector inputs, Vector outputs) throws MathException {
		double[] invals = (double[]) inputs.elementAt(0);
		double[] outvals = (double[]) outputs.elementAt(0);
		int rows = invals.length;
		double d;
		if(rows < 5){
			return;
		}
		outvals[0] = Double.NaN;
		outvals[1] = Double.NaN;
		Matrix F = Matlib.createMatrix(5,1);
		Matrix A = Matlib.createMatrix(2,1);
		Matrix coef = Matlib.createMatrix(2,5);
		getCoefficents(coef,2);
		for(int rr=0; rr<5; rr++){
			F.set(rr,0,invals[rr]);
		}
		Matlib.multiply(coef,F,A);
		outvals[2] = A.get(1,0);
		if(rows == 5){
			outvals[rows-2] = Double.NaN;
			outvals[rows-1] = Double.NaN;
			return;
		}
		if(rows == 6){
			for(int rr=0;rr<6;rr++){
				F.set(rr,0,invals[rr]);
			}
			Matlib.multiply(coef,F,A);
			outvals[3] = A.get(1,0);
			outvals[rows-2] = Double.NaN;
			outvals[rows-1] = Double.NaN;
			return;
		}
		getCoefficents(coef,3);
		F.redimension(7,1);
		for(int rr=0; rr<7; rr++){
			F.set(rr,0,invals[rr]);
		}
		Matlib.multiply(coef,F,A);
		outvals[3] = A.get(1,0);
		if(rows == 7){
			getCoefficents(coef,2);
			F.redimension(5,1);
			for(int rr=0; rr<5; rr++){
				F.set(rr,0,invals[rr+2]);
			}
			Matlib.multiply(coef,F,A);
			outvals[4] = A.get(1,0);
			outvals[rows-2] = Double.NaN;
			outvals[rows-1] = Double.NaN;
			return;
		}else if(rows == 8){
			getCoefficents(coef,3);
			F.redimension(7,1);
			for(int rr=0;rr<7;rr++){
				F.set(rr,0,invals[rr]);
			}
			Matlib.multiply(coef,F,A);
			outvals[3] = A.get(1,0);
			for(int rr=0;rr<7;rr++){
				F.set(rr,0,invals[rr+1]);
			}
			Matlib.multiply(coef,F,A);
			outvals[4] = A.get(1,0);
			getCoefficents(coef,2);
			F.redimension(5,1);
			for(int rr=0;rr<5;rr++){
				F.set(rr,0,invals[rr+3]);
			}
			Matlib.multiply(coef,F,A);
			outvals[5] = A.get(1,0);
			outvals[rows-2] = Double.NaN;
			outvals[rows-1] = Double.NaN;
			return;
		}
		getCoefficents(coef,4);
		F.redimension(9,1);
		for(int r=4;r<rows-4;r++) {
			for(int rr=0;rr<9;rr++){
				F.set(rr,0,invals[r-4+rr]);
			}
			Matlib.multiply(coef,F,A);
			outvals[r] = A.get(1,0);
		}
		getCoefficents(coef,3);
		F.redimension(7,1);
		for(int rr=0;rr<8;rr++){
			F.set(rr,0,invals[rows-8+rr]);
		}
		Matlib.multiply(coef,F,A);
		outvals[rows-4] = A.get(1,0);
		getCoefficents(coef,2);
		F.redimension(5,1);
		for(int rr=0;rr<6;rr++){
			F.set(rr,0,invals[rows-6+rr]);
		}
		Matlib.multiply(coef,F,A);
		outvals[rows-3] = A.get(1,0);
		outvals[rows-2] = Double.NaN;
		outvals[rows-1] = Double.NaN;
	}


	private void getCoefficents(Matrix coef,int n){

		try{
			Matrix A = Matlib.ones(n,n*2+1);
			Matrix temp1 = Matlib.createMatrix();
			Matrix temp2 = Matlib.createMatrix();
			for(int i=0;i<n*2+2;i++){
				for(int j=0;j<n;j++){
					double d = 1.0;
					for(int k=0;k<j;k++){
						d =d*(double)(i-4);
					}
					A.set(j,i,d);
				}
			}
			Matlib.transpose(A,temp1); 
			Matlib.multiply(A,temp1,temp2);
			Matlib.inv(temp2,temp2);
			Matlib.multiply(temp2,A,coef);
//			Matlib.disp(coef,"coef");
		}catch(MathException e){}
	}

	@Override
	public long getRequiredHistoryLength() {
		return (long) maximumTimeWindow;
	}

}


