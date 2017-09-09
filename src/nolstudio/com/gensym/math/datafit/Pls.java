package com.gensym.math.datafit;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.Utilities;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;

public class Pls extends TrainableModel implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected Matrix Xmean;
	protected Matrix Ymean;
	protected Matrix R;  // mapping to T, compressed equivalent of P and W
	protected Matrix S;  // mapping to outputs, concatenation of Qs
	protected Matrix B;  // inner relations

	public Pls(ArchitectureParameters AP) {
		super(AP);
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		Pls cloned = (Pls) super.clone();
		cloned.Xmean = Xmean == null ? null : (Matrix) Xmean.clone();
		cloned.Ymean = Ymean == null ? null : (Matrix) Ymean.clone();
		cloned.R = R == null ? null : (Matrix) R.clone();
		cloned.S = S == null ? null : (Matrix) S.clone();
		cloned.B = B == null ? null : (Matrix) B.clone();
		
		return cloned;
	}
	
	private void clear() {
		// reclaims all matrices;
		if(Xmean!=null) {
			Matlib.clear(Xmean); 
			Xmean=null;
		}
		if(Ymean!=null) {
			Matlib.clear(Ymean); 
			Ymean=null;
		}
		if(R!=null) {
			Matlib.clear(R); 
			R=null;
		}
		if(S!=null) {
			Matlib.clear(S); 
			S=null;
		}
		if(B!=null) {
			Matlib.clear(B); 
			B=null;
		}
	}

	/** Makes a model that shares the same P, Q, B, and scale factors as the
	sourceModel, but uses a different number of factors.  If a Nlpls model has 
	a submodel, you must not clear any of the matrices or vectors in the source 
	model. NOT CURRENTLY USED.  */
	public Pls getSubmodel(int nfactors) throws MathException, CloneNotSupportedException {
		if(nfactors>AP.nfactors){
			throw new MathException("Cannot create a pls model from another pls model with fewer factors");
		}
		Pls submodel = (Pls) clone();  // attributes of submodel point to the same subobjects
		submodel.AP = new ArchitectureParameters(AP.nin, AP.nout, 0, nfactors);
		submodel.trainingResults = null;
		submodel.testingResults = null;
		return submodel;
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		if (X.getCols() != AP.nin){
			throw new MathException("Pls.evaluate: column dimension of input matrix does not match model dimension");
		}
		boolean isSubmodel;
		if(AP.nfactors==R.getCols()){
			isSubmodel=false;
		}else{
			isSubmodel = true;		
		}
		// allocate temporary storage
		Matrix Xnorm = Matlib.createMatrix();
		Matrix T = Matlib.createMatrix();
		Matrix U = Matlib.createMatrix();
		Matrix t = Matlib.createMatrix();
		Matrix u = Matlib.createMatrix();
		// scale the inputs
		Matlib.subtract(X,Xmean,Xnorm); // R contains Xstd, so no division is necessary!
		if(!isSubmodel){
			Matlib.multiply(Xnorm,R,T);
		}else {  // support submodels where sizes of matrices reflects original number of factors
			Matrix r = Matlib.createMatrix();
			Matlib.getColumns(R,0,AP.nfactors-1,r);
			Matlib.multiply(Xnorm,r,T);
			Matlib.clear(r);
		}
		Matlib.multiply(Xnorm,R,T);  
		if(!isSubmodel){
			Matlib.multiplyElements(T,B,U);
		}else {
			Matrix b = Matlib.createMatrix();
			Matlib.getColumns(B,0,AP.nfactors-1,b);
			Matlib.multiplyElements(T,b,U);
			Matlib.clear(b);
		}
		if(!isSubmodel){
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
			throw new MathException("PLS Input dimensions do not match"+AP.nin+" "+X.getCols());
		}
		if(AP.nout != Y.getCols()){
			throw new MathException("Output dimensions do not match");
		}
		int nfactors = AP.nfactors;
		// create subobjects of this Nlpls model
		S = Matlib.createMatrix();
		R = Matlib.createMatrix();
		B = Matlib.zeros(1,nfactors);
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
		double bb;
		for(int i=0;i<nfactors;i++) {
			Stats.nipals(Xnorm,Ynorm,P,Q,W,T,U);
			bb=Matlib.dotProduct(U,T)/Matlib.dotProduct(T,T);
			B.set(0,i,bb);
			Matlib.appendColumns(TT,T,TT);
			Matlib.transpose(Q,Q);
			Matlib.appendRows(S,Q,S);
			Matlib.multiply(T,bb,UPred);
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
		return ("Pls with "+AP.nfactors+" factors");
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

	/** write variable infor of pls to a string buffer as in C code format */
	@Override
	public void writeParamVariable(StringBuffer sb, int index) {
		try{
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeParamVariable(sb,index);
		}catch (MathException e){}
	}

	/** write weights of pls to a string buffer as in C code format */
	@Override
	public void writeWeightAsC(StringBuffer sb, int index) {
		try{
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeWeightAsC(sb,index);
		}catch (MathException e){}
	}
	/** write weights of pls to a string buffer as in C code format */
	@Override
	public void writeMatrixInit(StringBuffer sb, int index) {
		try{
//			System.out.println("in pls"+sb);
			MimoBpn equivalentBpn = new MimoBpn(this);
			equivalentBpn.writeMatrixInit(sb,index);
		}catch (MathException e){}
	}

	public Matrix getXMean(){
		return Xmean;
	}

	public Matrix getYMean(){
		return Ymean;
	}
	
	
	public Matrix getR(){
		return R;
	}
	
	public Matrix getB() throws MathException{
		Matrix b = Matlib.createMatrix();
		Matlib.getColumns(B,0,AP.nfactors-1,b);
//		System.out.println("b.col="+b.getCols()+" b.row="+b.getRows());
		return b;
	}

	public Matrix getS()throws MathException{
		Matrix s = Matlib.createMatrix();
		Matlib.getRows(S,0,AP.nfactors-1,s);
//		System.out.println("s.col="+s.getCols()+" s.row="+s.getRows());
		return s;
	}

	public void writeWeightsAsPLS(BufferedWriter Source) throws IOException, MathException {
		int ni = Xmean.getCols();
		int no = Ymean.getCols();
		int nb = R.getCols();

		Source.write("2; Version of this file save/restore protocol");
		Source.newLine();
		Source.write(ni+"; Number of inputs");
		Source.newLine();
		Source.write(no+"; Number of outputs");
		Source.newLine();
		Source.write(nb+"; Number of inner nodes");
		Source.newLine();

		double[] pp = Matlib.create1DArray(Xmean);
		for(int i=0;i<pp.length;i++){
			if(i == pp.length-1){
				Source.write(pp[i]+"; Input means");
			}else{
				Source.write(pp[i]+",");
			}
		}
		Source.newLine();

		pp = Matlib.create1DArray(Ymean);
		for(int i=0;i<pp.length;i++){
			if(i == pp.length-1){
				Source.write(pp[i]+"; Output means");
			}else{
				Source.write(pp[i]+",");
			}
		}
		Source.newLine();
		
		for(int j=0;j<R.getRows();j++){
			for(int i=0;i<R.getCols();i++){
				if(i == R.getCols()-1){
					Source.write(R.get(j,i)+"; R element");
				}else{
					Source.write(R.get(j,i)+",");
				}
			}
			Source.newLine();
		}
		

		Matrix b = Matlib.createMatrix();
		Matlib.getColumns(B,0,AP.nfactors-1,b);
		Matrix s = Matlib.createMatrix();
		Matlib.getRows(S,0,AP.nfactors-1,s);

		for(int j=0;j<b.getRows();j++){
			for(int i=0;i<b.getCols();i++){
				if(i == b.getCols()-1){
					Source.write(b.get(j,i)+"; B element");
				}else{
					Source.write(b.get(j,i)+",");
				}
			}
			Source.newLine();
		}
		
		for(int j=0;j<s.getRows();j++){
			for(int i=0;i<s.getCols();i++){
				if(i == s.getCols()-1){
					Source.write(s.get(j,i)+"; S element");
				}else{
					Source.write(s.get(j,i)+",");
				}
			}
			Source.newLine();
		}
		Matlib.clear(b);
		Matlib.clear(s);
	}
/** Return the model information in a Vector as a BPN.*/
	@Override
	public Vector getParametersVector() throws MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		return equivalentBpn.getParametersVector();
	}

/** Return the model information in a Vector as PLS. */
	public Vector getPlsParametersVector() throws MathException {

		int ni = Xmean.getCols();
		int no = Ymean.getCols();
		int nb = R.getCols();
		Vector para = new Vector();
		para.addElement(2);
		para.addElement(ni);
		para.addElement(no);
		para.addElement(nb);

 		Matrix Temp = Matlib.createMatrix();

		double[] pp = Matlib.create1DArray(Xmean);
		para.addElement(pp);
		pp = Matlib.create1DArray(Ymean);
		para.addElement(pp);
		
		for(int j=0;j<R.getRows();j++){
			Matlib.getRows(R,j,j,Temp);
			pp = Matlib.create1DArray(Temp);
			para.addElement(pp);
		}
		

		Matrix b = Matlib.createMatrix();
		Matlib.getColumns(B,0,AP.nfactors-1,b);
		Matrix s = Matlib.createMatrix();
		Matlib.getRows(S,0,AP.nfactors-1,s);

		for(int j=0;j<b.getRows();j++){
			Matlib.getRows(b,j,j,Temp);
			pp = Matlib.create1DArray(Temp);
			para.addElement(pp);
		}
		
		for(int j=0;j<s.getRows();j++){
			Matlib.getRows(s,j,j,Temp);
			pp = Matlib.create1DArray(Temp);
			para.addElement(pp);
		}
		Matlib.clear(Temp);
		Matlib.clear(b);
		Matlib.clear(s);
		return para;
	}
	@Override
	public int writeXMLFile(BufferedWriter Source, int indentNumber) throws IOException, MathException {
		MimoBpn equivalentBpn = new MimoBpn(this);
		return equivalentBpn.writeXMLFile(Source,indentNumber);
	}

	public int writeXMLFileAsPLS(final BufferedWriter target, final int indentNumber) throws IOException, MathException {
		int indent = indentNumber;
		String dataString = Utilities.indent(indent)+"<bpn>\n";
		target.write(dataString,0,dataString.length());
		indent++;

		int ni = Xmean.getCols();
		int no = Ymean.getCols();
		int nb = R.getCols();

		dataString = Utilities.indent(indent)+"<numberOfInputs>"+ni+"</numberOfInputs>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<numberOfOutputs>"+no+"</numberOfOutputs>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<numberOfInnerNodes>"+nb+"</numberOfInnerNodes>\n";
		target.write(dataString,0,dataString.length());

		dataString = Utilities.indent(indent)+"<inputMeans>\n";
		target.write(dataString,0,dataString.length());
		indent++;

		double[] pp = Matlib.create1DArray(Xmean);
		for(int i=0;i<pp.length;i++){
			dataString = Utilities.indent(indent)+"<mean>\n";
			target.write(dataString,0,dataString.length());
			indent++;
			dataString = Utilities.indent(indent)+"<value>"+pp[i]+"</value>\n";
			target.write(dataString,0,dataString.length());
			dataString = Utilities.indent(indent)+"<index>"+i+"</index>\n";
			target.write(dataString,0,dataString.length());
			indent--;
			dataString = Utilities.indent(indent)+"</mean>\n";
			target.write(dataString,0,dataString.length());
		}
		indent--;
		dataString = Utilities.indent(indent)+"</inputMeans>\n";
		target.write(dataString,0,dataString.length());

		dataString = Utilities.indent(indent)+"<outputputMeans>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		pp = Matlib.create1DArray(Ymean);
		for(int i=0;i<pp.length;i++){
			dataString = Utilities.indent(indent)+"<mean>\n";
			target.write(dataString,0,dataString.length());
			indent++;
			dataString = Utilities.indent(indent)+"<value>"+pp[i]+"</value>\n";
			target.write(dataString,0,dataString.length());
			dataString = Utilities.indent(indent)+"<index>"+i+"</index>\n";
			target.write(dataString,0,dataString.length());
			indent--;
			dataString = Utilities.indent(indent)+"</mean>\n";
			target.write(dataString,0,dataString.length());
		}
		indent--;
		dataString = Utilities.indent(indent)+"</outputMeans>\n";
		target.write(dataString,0,dataString.length());
		
		for(int j=0;j<R.getRows();j++){
			for(int i=0;i<R.getCols();i++){
				dataString = Utilities.indent(indent)+"<r_element>\n";
				target.write(dataString,0,dataString.length());
				indent++;
				dataString = Utilities.indent(indent)+"<weight>"+R.get(j,i)+"</weight>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<row>"+j+"</row>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<column>"+i+"</column>\n";
				target.write(dataString,0,dataString.length());
				indent--;
				dataString = Utilities.indent(indent)+"</r_element>\n";
				target.write(dataString,0,dataString.length());
			}
		}
		

		Matrix b = Matlib.createMatrix();
		Matlib.getColumns(B,0,AP.nfactors-1,b);
		Matrix s = Matlib.createMatrix();
		Matlib.getRows(S,0,AP.nfactors-1,s);

		for(int j=0;j<b.getRows();j++){
			for(int i=0;i<b.getCols();i++){
				dataString = Utilities.indent(indent)+"<b_element>\n";
				target.write(dataString,0,dataString.length());
				indent++;
				dataString = Utilities.indent(indent)+"<weight>"+b.get(j,i)+"</weight>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<row>"+j+"</row>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<column>"+i+"</column>\n";
				target.write(dataString,0,dataString.length());
				indent--;
				dataString = Utilities.indent(indent)+"</b_element>\n";
				target.write(dataString,0,dataString.length());
			}
		}
		
		for(int j=0;j<s.getRows();j++){
			for(int i=0;i<s.getCols();i++){
				dataString = Utilities.indent(indent)+"<s_element>\n";
				target.write(dataString,0,dataString.length());
				indent++;
				dataString = Utilities.indent(indent)+"<weight>"+s.get(j,i)+"</weight>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<row>"+j+"</row>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<column>"+i+"</column>\n";
				target.write(dataString,0,dataString.length());
				indent--;
				dataString = Utilities.indent(indent)+"</s_element>\n";
				target.write(dataString,0,dataString.length());
			}
		}
		Matlib.clear(b);
		Matlib.clear(s);
		return indent;
	}
}
