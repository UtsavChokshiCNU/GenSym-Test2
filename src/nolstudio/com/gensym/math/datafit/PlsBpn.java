package com.gensym.math.datafit;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;

/** A MIMO neural network based on PLS */
public class PlsBpn extends TrainableModel implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected Matrix Xmean;
	protected Matrix R;  // mapping to T, compressed equivalent of P and W
	protected Vector Nets;  // output maps

	public PlsBpn(ArchitectureParameters AP) {
		// nhidden is number of hidden nodes per output, not total!
		super(AP);
		Nets = new Vector(0,AP.nout);
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		PlsBpn cloned = (PlsBpn) super.clone();
		cloned.Xmean = Xmean == null ? null : (Matrix) Xmean.clone();
		cloned.R = R == null ? null : (Matrix) R.clone();
		cloned.Nets = Nets == null ? null : (Vector) Nets.clone();
		
		return cloned;
	}
	
	private void clear() {
		// reclaims all matrices;
		if(Xmean!=null) {
			Matlib.clear(Xmean); 
			Xmean=null;
		}
		if(R!=null) {
			Matlib.clear(R); 
			R=null;
		}
		Nets.removeAllElements();
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		if (X.getCols() != AP.nin) {
			throw new MathException("PlsBpn.evaluate: column dimension of input matrix does not match model dimension");
		}
		// allocate temporary storage
		Matrix Xnorm = Matlib.createMatrix();
		Matrix T = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Y.redimension(0,0);
		// scale the inputs
		Matlib.subtract(X,Xmean,Xnorm); // R contains Xstd, so no division is necessary!
		Matlib.multiply(Xnorm,R,T);
		MisoBpn net;
		for(int i=0;i<AP.nout;i++) {
			net = (MisoBpn) Nets.elementAt(i);
			net.evaluate(T,y);
			Matlib.appendColumns(Y,y,Y);
		}
		Matlib.clear(Xnorm);
		Matlib.clear(T);
		Matlib.clear(y);
	}

	@Override
	public void learn(Matrix X, Matrix Y) throws MathException {
		clear();  // just in case we are retraining this model
		if(AP.nin != X.getCols()){
			throw new MathException("PLSBPN Input dimensions do not match"+AP.nin+" "+X.getCols());
		}
		if(AP.nout != Y.getCols()){
			throw new MathException("Output dimensions do not match");
		}
		int nfactors = AP.nfactors, nhidden = AP.nhidden;
		Xmean = Matlib.createMatrix();
		R = Matlib.createMatrix();
		// create temporary storage
		Matrix T = Matlib.createMatrix();
		Matrix Xnorm = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		// create PLS model and store a copy of R
		Pls model = new Pls(AP);
		model.train(X,Y);
		Matlib.copy(model.R,R);
		Matlib.copy(model.Xmean,Xmean);
		// calculate scores
		Matlib.subtract(X,Xmean,Xnorm); 
		Matlib.multiply(Xnorm,R,T);
		// main loop
		ArchitectureParameters BAP = new ArchitectureParameters(nfactors,1,AP.nhidden,0);
		for(int i=0;i<AP.nout;i++) {
			MisoBpn net = new MisoBpn(BAP);
			Matlib.getColumns(Y,i,i,y);
			net.learn(T,y);
			Nets.addElement(net);
		}
		Matlib.clear(T);
		Matlib.clear(Xnorm);
		Matlib.clear(y);
	}

	@Override
	public String getDescription() {
		return ("PlsBpn with "+AP.nfactors+" factors, "+AP.nout*AP.nhidden+" hidden");
	}

	@Override
	public void writeWeights(BufferedWriter Source) throws IOException, MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		equivalentBpn.writeWeights(Source);
	}


	@Override
	public String getModelParameters(String modelName, int index) throws MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		return equivalentBpn.getModelParameters(modelName,index);
	}

	/** write variable infor of plsbpn to a string buffer as in C code format */
	@Override
	public void writeParamVariable(StringBuffer sb, int index) {
		try{
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeParamVariable(sb,index);
		}catch (MathException e){}
	}

	/** write weights of plsbpn to a string buffer as in C code format */
	@Override
	public void writeWeightAsC(StringBuffer sb, int index) {
		try{
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeWeightAsC(sb,index);
		}catch (MathException e){}
	}
	/** write weights of plsbpn to a string buffer as in C code format */
	@Override
	public void writeMatrixInit(StringBuffer sb, int index) {
		try{
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeMatrixInit(sb,index);
		}catch (MathException e){}
	}
/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() throws MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		return equivalentBpn.getParametersVector();
	}
/** write a plsBpn to a file in XML format */
	@Override
	public int writeXMLFile(BufferedWriter target,int indentNumber) throws IOException,MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		return equivalentBpn.writeXMLFile(target,indentNumber);
	}
}
