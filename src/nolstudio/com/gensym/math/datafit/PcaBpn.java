package com.gensym.math.datafit;

import java.io.*;
import java.util.*;
import com.gensym.math.MathException;
import com.gensym.math.matrix.*;
import com.gensym.math.Utilities;
import com.gensym.math.stats.Stats;

/** A MIMO neural network based on PCA */
public class PcaBpn extends TrainableModel implements Cloneable {
	static final long serialVersionUID = 1L;
	private Matrix Xmean;
	private Matrix P;  // mapping to T
	private Vector Nets;  // output maps

	public PcaBpn(ArchitectureParameters AP) {
		super(AP);
		Nets = new Vector(0,AP.nout);
	}

	private void clear() {
		// reclaims all matrices;
		if(Xmean!=null) {Matlib.clear(Xmean); Xmean=null;}
		if(P!=null) {Matlib.clear(P); P=null;}
		Nets.removeAllElements();
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		if (X.getCols() != AP.nin) throw new MathException("PcaBpn.evaluate: column dimension of input matrix does not match model dimension");
		// allocate temporary storage
		Matrix Xnorm = Matlib.createMatrix();
		Matrix T = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Y.redimension(0,0);
		// scale the inputs
		Matlib.subtract(X,Xmean,Xnorm); // P contains Xstd, so no division is necessary!
		Matlib.multiply(Xnorm,P,T);
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
		if(AP.nin != X.getCols()) throw new MathException("Input dimensions do not match"+AP.nin+X.getCols());
		if(AP.nout != Y.getCols()) throw new MathException("Output dimensions do not match");
		int nfactors = AP.nfactors, nhidden = AP.nhidden;
		Xmean = Matlib.createMatrix();
		P = Matlib.createMatrix();
		// create temporary storage
		Matrix T = Matlib.createMatrix();
		Matrix Xnorm = Matlib.createMatrix();
		Matrix y = Matlib.createMatrix();
		Matrix Xstd = Matlib.createMatrix();
		// normalize inputs
		Matlib.mean(X,Xmean);
		Matlib.stdnonzero(X,Xstd);
		Matlib.normalize(X,Xmean,Xstd,Xnorm);
		// create PCA model and fold Xstd into P to simplify future evaluation
		Stats.pca(Xnorm, AP.nfactors, P);
		Matlib.multiply(Xnorm,P,T);  // calc scores
		Matlib.transpose(Xstd,Xstd);
		Matlib.divideElements(P,Xstd,P);
		// main loop
		ArchitectureParameters BAP = new ArchitectureParameters(nfactors,1,AP.nhidden,0);
		for(int i=0;i<AP.nout;i++) {
			MisoBpn net = new MisoBpn(BAP);
			Matlib.getColumns(Y,i,i,y);
			net.learn(T,y);
			Nets.addElement(net);
		}
		// release temporary matrices
		Matlib.clear(T);
		Matlib.clear(Xnorm);
		Matlib.clear(y);
		Matlib.clear(Xstd);
	}

/** write a PCABPN to a file in XML format */
/*	Appearly no Pca bpn is used in the ensemble.
	public void writeXMLFile(BufferedWriter target) throws IOException,MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		equivalentBpn.writeWeights(target);
	}

  */
}
