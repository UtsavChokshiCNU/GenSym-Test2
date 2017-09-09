package com.gensym.math.datafit;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;

/** A MIMO neural network based on PLS */
public class Nlpls extends TrainableModel implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected Matrix Xmean;
	protected Matrix Ymean;
	protected Matrix R;  // mapping to T, compressed equivalent of P and W
	protected Matrix S;  // mapping to outputs, concatenation of Qs
	protected Vector Nets;  // inner relations

	public Nlpls(ArchitectureParameters AP) {
		super(AP);
		Nets = new Vector(0,10);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		Nlpls cloned = (Nlpls) super.clone();
		cloned.Xmean = Xmean == null ? null : (Matrix) Xmean.clone();
		cloned.Ymean = Ymean == null ? null : (Matrix) Ymean.clone();
		cloned.R = R == null ? null : (Matrix) R.clone();
		cloned.S = S == null ? null : (Matrix) S.clone();
		cloned.Nets = Nets == null ? null : (Vector) Nets.clone();
		
		return cloned;
	}

	private void clear() {
		// reclaims all matrices;
		Matlib.clear(Xmean);
		Matlib.clear(Ymean);
		Matlib.clear(R);
		Matlib.clear(S);
		Nets.removeAllElements();
	}

	/** Makes a model that shares the same P, Q, Nets, and scale factors as the
	sourceModel, but uses a different number of factors.  If a Nlpls model has 
	a submodel, you must not clear any of the matrices or vectors in the source 
	model. */
	public Nlpls getSubmodel(int nfactors) throws MathException, CloneNotSupportedException {
		if(nfactors>AP.nfactors){
			throw new MathException("Cannot create a Nlpls model from another Nlpls model with fewer factors");
		}
		Nlpls submodel = (Nlpls) clone();  // attributes of submodel point to the same subobjects
		submodel.AP = new ArchitectureParameters(AP.nin, AP.nout, nfactors, AP.nhidden);
		submodel.trainingResults = null;
		submodel.testingResults = null;
		return submodel;
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		if (X.getCols() != AP.nin){
			throw new MathException("Nlpls.evaluate: column dimension of input matrix does not match model dimension");
		}
		// allocate temporary storage
		Matrix Xnorm = Matlib.createMatrix();
		Matrix T = Matlib.createMatrix();
		Matrix U = Matlib.createMatrix();
		Matrix t = Matlib.createMatrix();
		Matrix u = Matlib.createMatrix();
		// scale the inputs
		Matlib.subtract(X,Xmean,Xnorm); // R contains Xstd, so no division is necessary!
		if(AP.nfactors==R.getCols()){
			Matlib.multiply(Xnorm,R,T);
		}else {  // support submodels where sizes of matrices reflects original number of factors
			Matrix r = Matlib.createMatrix();
			Matlib.getColumns(R,0,AP.nfactors-1,r);
			Matlib.multiply(Xnorm,r,T);
			Matlib.clear(r);
		}
		SisoBpn net;
		for(int i=0;i<AP.nfactors;i++) {
			net = (SisoBpn) Nets.elementAt(i);
			Matlib.getColumns(T,i,i,t);
			net.evaluate(t,u);
			Matlib.appendColumns(U,u,U);
		}
		if(AP.nfactors==S.getRows()){
			Matlib.multiply(U,S,Y);
		}else {
			Matrix s = Matlib.createMatrix();
			Matlib.getRows(S,0,AP.nfactors-1,s);
			Matlib.multiply(U,s,Y);
			Matlib.clear(s);
		}
		// unnormalize Y
		Matlib.add(Y,Ymean,Y);
		Matlib.clear(Xnorm);
		Matlib.clear(T);
		Matlib.clear(U);
		Matlib.clear(t);
		Matlib.clear(u);
	}

	@Override
	public void learn(Matrix X, Matrix Y) throws MathException {
		clear();  // just in case we are retraining this model
		if(AP.nin != X.getCols()){
			throw new MathException("NLPLS Input dimensions do not match"+AP.nin+" "+X.getCols());
		}
		if(AP.nout != Y.getCols()){
			throw new MathException("Output dimensions do not match");
		}
		int nfactors = AP.nfactors, nhidden = AP.nhidden;
		// create subobjects of this Nlpls model
		S = Matlib.createMatrix();
		R = Matlib.createMatrix();
		Xmean = Matlib.createMatrix();
		Ymean = Matlib.createMatrix();
		// create temporary storage
		Matrix Xstd = Matlib.createMatrix();
		Matrix Ystd = Matlib.createMatrix();
		Matrix Xnorm = Matlib.createMatrix();
		Matrix Ynorm = Matlib.createMatrix();
		Matrix T = Matlib.createMatrix();
		Matrix TT = Matlib.createMatrix();
		Matrix U = Matlib.createMatrix();
		Matrix YF = Matlib.createMatrix();
		Matrix XF = Matlib.createMatrix();
		Matrix UPred = Matlib.createMatrix();
		Matrix P = Matlib.createMatrix();
		Matrix Q = Matlib.createMatrix();
		Matrix W = Matlib.createMatrix();
		// normalize the inputs and outputs
		Matlib.mean(X,Xmean);
		Matlib.stdnonzero(X,Xstd);
		Matlib.mean(Y,Ymean);
		Matlib.stdnonzero(Y,Ystd);
		Matlib.normalize(X,Xmean,Xstd,Xnorm);
		Matlib.normalize(Y,Ymean,Ystd,Ynorm);
		// main loop
		int nh = (int) Math.floor(((double)nhidden)/nfactors);
		int nhleftover = nhidden - nh*nfactors;
		ArchitectureParameters BAP = new ArchitectureParameters(1,1,nh,0);
		ArchitectureParameters BAPplus = new ArchitectureParameters(1,1,nh+1,0);
		SisoBpn net;
		for(int i=0;i<nfactors;i++) {
			if(nhleftover>0) {
				nhleftover--;
				net = new SisoBpn(BAPplus);
			} else net = new SisoBpn(BAP);
			Stats.nipals(Xnorm,Ynorm,P,Q,W,T,U);
			Matlib.appendColumns(TT,T,TT);
			Matlib.transpose(Q,Q);
			Matlib.appendRows(S,Q,S);
			net.learn(T,U);
			net.evaluate(T,UPred);
			Nets.addElement(net);
			if(i<nfactors-1) {
				// deflate the Xnorm and Ynorm matrices for next iteration
				Matlib.transpose(P,P);
				Matlib.multiply(T,P,XF);
				Matlib.multiply(UPred,Q,YF);
				Matlib.subtract(Xnorm,XF,Xnorm);
				Matlib.subtract(Ynorm,YF,Ynorm);
			}
		}
		Matlib.clear(T);
		Matlib.clear(U);
		Matlib.clear(YF);
		Matlib.clear(XF);
		Matlib.clear(UPred);
		Matlib.clear(P);
		Matlib.clear(Q);
		Matlib.clear(W);
		Matlib.clear(Ynorm);
		// create R matrix
		Matlib.normalize(X,Xmean,Xstd,Xnorm);   // this is inefficient!
		Matlib.divide(Xnorm,TT,R);				// this involves a SVD, might improve?
		Matlib.clear(TT);
		Matlib.clear(Xnorm);
		// fold std into R and S
		Matlib.transpose(Xstd,Xstd);
		Matlib.divideElements(R,Xstd,R);
		Matlib.multiplyElements(S,Ystd,S);
		Matlib.clear(Xstd);
		Matlib.clear(Ystd);
	}

	@Override
	public String getDescription() {
		return ("Nlpls with "+AP.nfactors+" factors, "+AP.nhidden+" hidden");
	}

	@Override
	public void writeWeights(BufferedWriter Source) throws MathException, IOException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		equivalentBpn.writeWeights(Source);
	}

	@Override
	public String getModelParameters(String modelName, int index) throws MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		return equivalentBpn.getModelParameters(modelName,index);
	}

	/** write variable infor of nlpls to a string buffer as in C code format */
	@Override
	public void writeParamVariable(StringBuffer sb, int index) {
		try{
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeParamVariable(sb,index);
		}catch (MathException e){}
	}

		/** write weights of nlpls to a string buffer as in C code format */
	@Override
	public void writeWeightAsC(StringBuffer sb, int index) {
		try{
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeWeightAsC(sb,index);
		}catch (MathException e){}
	}
	/** write weights of nlpls to a string buffer as in C code format */
	@Override
	public void writeMatrixInit(StringBuffer sb, int index) {
		try{
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeMatrixInit(sb,index);
		}catch (MathException e){}
	}

/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() throws MathException{
		MimoBpn equivalentBpn = new MimoBpn(this);
		return equivalentBpn.getParametersVector();
	}

/** write a NLPLS to a file in XML format */
	@Override
	public int  writeXMLFile(BufferedWriter target, int indentNumber) throws IOException,MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		return equivalentBpn.writeXMLFile(target,indentNumber);
	}
}
