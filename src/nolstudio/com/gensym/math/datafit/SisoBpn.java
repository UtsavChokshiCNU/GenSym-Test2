package com.gensym.math.datafit;

import java.io.*;
import java.security.SecureRandom;

import com.gensym.math.Algorithms;
import com.gensym.math.MathException;
import com.gensym.math.matrix.*;

/** A single-input single-output three-layer neural network with linear bypass */
public class SisoBpn extends TrainableModel implements Serializable {
	static final long serialVersionUID = 1L;
	public double[] weights;
	public int nweights;
	public static final double SIGMOID_LIM = Math.log(Double.MAX_VALUE);
	public static final double NEG_SIGMOID_LIM = - SIGMOID_LIM;

	public SisoBpn(ArchitectureParameters AP) throws MathException {
		super(AP);
		if(AP.nin!=1 || AP.nout!=1) {
			this.AP = null;
			throw new MathException("SisoBpn can only be created with 1 input and 1 output");
		}
		nweights = 2*AP.nhidden + AP.nhidden + 2;
		weights = new double[nweights];
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		int row, weight, ndata = X.getRows(), nhidden = AP.nhidden, hiddennode, firsthidden=2*nhidden;
		double x, u, output;
		Y.redimension(ndata,1);
		for(row=0;row<ndata;row++) {
			output = 0.0;
			x = X.get(row,0);
			for(hiddennode=0,weight=0;hiddennode<nhidden;hiddennode++,weight+=2) {
				u = x*weights[weight] + weights[weight+1];
				if (u>=SIGMOID_LIM){
					u = 1.0;  // sigmoid
				}else if (u<=NEG_SIGMOID_LIM) {
					u = -1.0;
				}else{
					u = 2.0/(1.0 + Math.exp(-u)) - 1.0; 
				}
				output += u*weights[firsthidden+hiddennode];
			}
			output += weights[nweights-2];  // hidden layer bias
			output += x*weights[nweights-1]; // pass-through weight
			Y.set(row,0,output);
		}
	}

	/** X and Y are vectors */
	@Override
	public void learn(Matrix X, Matrix Y) throws MathException {
		int ndata = X.getRows();
		int i,j,l,maxIters = 200;
		double abstol = 0.0001*ndata;  // target an rms error of 0.01
		double chisq,ochisq,alamda=1.0;
		double[] wtry = new double[nweights];
		double[][] covar = new double[nweights][nweights];  
		double[][] alpha = new double[nweights][nweights]; 
		double[] beta = new double[nweights]; 
		double[] dw = new double[nweights];
		double[] zeros = new double[nweights];
		double[] dydw = new double[nweights];
		double[] act = new double[AP.nhidden];
		double[] delta = new double[AP.nhidden];
		SecureRandom random = new SecureRandom();
		for(j=0;j<nweights;j++){
			zeros[j] = 0.0;
		}
		for (i=0;i<nweights;i++){
			weights[i] = random.nextDouble() - 0.5; 
		}
		ochisq = chisq = mrqcof(X,Y,weights,alpha,beta,zeros,delta,act,dydw);
		int iter=1,smallSteps=0,rejectedSteps=0;
		// main loop
		while(iter<=maxIters && smallSteps<4 && rejectedSteps<8 && chisq>abstol) { 
//System.out.println("iteration "+iter+" rms error = "+Math.sqrt(chisq/ndata));
			for(j=0;j<nweights;j++) {
				System.arraycopy(alpha[j],0,covar[j],0,nweights);
				covar[j][j]=alpha[j][j]*(1.0+alamda);
			}
			try{
				Algorithms.cholsky(covar,nweights,beta,dw); 
			} catch (MathException e) {
				rejectedSteps = 9999;   // staturated one or more nodes in the net -- stuck.
			}
			for (l=0;l<nweights;l++){
				wtry[l] = weights[l] + dw[l];
			}
			chisq = mrqcof(X,Y,wtry,covar,dw,zeros,delta,act,dydw);
			if(chisq>=ochisq) { // a bad step
				rejectedSteps++;
				alamda *= 20.0;
				chisq=ochisq;
			}
			else {  // a good step
				System.arraycopy(wtry,0,weights,0,nweights);
				if(Math.abs((ochisq-chisq)/ochisq) < 0.001){
					smallSteps++;
				}
				else {
					smallSteps=rejectedSteps=0;  // a significant step, reset counters
				}
				alamda *= 0.5;
				ochisq=chisq;
				for(j=0;j<nweights;j++) {
					System.arraycopy(covar[j],0,alpha[j],0,nweights);
					beta[j] = dw[j];
				}
			}
			iter++;
		}
	}
	
	private double mrqcof(Matrix X, Matrix Y, double[] weights, double[][] alpha, double[] beta, 
		double[] zeros, double[] delta, double[] act, double[] dydw) throws MathException {
		double TINY = 1.e-100;
		int j,k,l,m,weight,ndata=X.getRows(),nhidden=AP.nhidden,hiddennode, firsthidden=2*AP.nhidden;
		double x,dy,csq=0.0,u,output,activation;
		for (j=0;j<nweights;j++){
			System.arraycopy(zeros,0,alpha[j],0,nweights);
		}
		System.arraycopy(zeros,0,beta,0,nweights);
		for(int row=0;row<ndata;row++) {
			output = 0.0;
			x = X.get(row,0);
			for(weight=0,hiddennode=0;hiddennode<nhidden;hiddennode++,weight+=2) {
				u = x*weights[weight] + weights[weight+1];
				if (u>=SIGMOID_LIM){
					activation = 1.0;  // sigmoid
				}else if (u<=NEG_SIGMOID_LIM){
					activation = -1.0;
				}else{
					activation = 2.0/(1.0 + Math.exp(-u)) - 1.0;  
				}
				act[hiddennode] = activation;
				delta[hiddennode] = TINY+0.5*(1.0+activation)*(1.0-activation)*weights[firsthidden+hiddennode];
				output += activation*weights[firsthidden+hiddennode];
			}
			output += weights[nweights-2];  // hidden layer bias
			output += x*weights[nweights-1];
			dy = Y.get(row,0) - output;
			for(weight=0,hiddennode=0;hiddennode<nhidden;hiddennode++,weight+=2) {
				dydw[weight]=delta[hiddennode]*x;
				dydw[weight+1]=delta[hiddennode]; // bias
				dydw[firsthidden+hiddennode] = act[hiddennode];
			}
			dydw[nweights-2] = 1.0;  // output bias
			dydw[nweights-1] = x;   // pass-through term
			for (l=0;l<nweights;l++) {
				for (m=0;m<=l;m++){
					alpha[l][m] += dydw[l]*dydw[m];
				}
				beta[l] += dy*dydw[l];
			}
			csq += dy*dy;
		}
		for (j=1;j<nweights;j++){
			for (k=0;k<j;k++){
				alpha[k][j]=alpha[j][k];
			}
		}
		return csq;
	}

}
