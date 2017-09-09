package com.gensym.math.datafit;

import java.io.*;
import java.lang.*;
import java.util.*;
import com.gensym.math.*;
import com.gensym.math.matrix.*;
import com.gensym.nols.util.Parser;

/** 5-max-layer Mimo Backprop network with linear or sigmoidal layers.
Not trainable, but compatible with NOL Classic. */

public class ClassicBpn extends MimoBpn implements Serializable {
	static final long serialVersionUID = 1L;
	protected ArchitectureParameters AP;
	protected Matrix Xmean;		
	protected Matrix Xstd;		
	protected Matrix Ymean;
	protected Matrix Ystd;		
	public double rmse;
	protected double ysize;

	public ClassicBpn(int nlayers, int[] tf, int[] nodes) {
		this.nlayers = nlayers;
		this.tf = tf;
		this.nodes = nodes;
		this.weights = new Matrix[nlayers-1];
		for(int i=0;i<nlayers-1;i++) {
			weights[i] = Matlib.zeros(nodes[i]+1,nodes[i+1]);
		}
		AP = new ArchitectureParameters(nodes[0], nodes[nlayers-1], 1, 1);

	}

	public void prepareDataStat(Matrix X, Matrix Y)throws MathException{
		if(Xmean == null){
			Xmean = Matlib.createMatrix();
		}
		if(Ymean == null){
			Ymean = Matlib.createMatrix();
		}
		if(Xstd == null){
			Xstd = Matlib.createMatrix();
		}
		if(Ystd == null){
			Ystd = Matlib.createMatrix();
		}
		Matlib.mean(X,Xmean);
		Matlib.stdnonzero(X,Xstd);
		Matlib.mean(Y,Ymean);
		Matlib.stdnonzero(Y,Ystd);
		ysize = (double)Y.getCols()*Y.getRows();
	}

	/** Calculates values of Y, given X, using the current weights */
	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		Matrix Xnorm = Matlib.createMatrix();
		Matrix Ynorm = Matlib.createMatrix();
		Matlib.normalize(X,Xmean,Xstd,Xnorm);
		super.evaluate(Xnorm,Ynorm);
		Matlib.unnormalize(Ynorm,Ymean,Ystd,Y);
		Ynorm.clear();
		Xnorm.clear();
	}

	public void writeData(BufferedWriter Source, Matrix X, Matrix Y)throws IOException, MathException{ 
		int len = X.getRows();
		int nin = X.getCols();
		int nout = Y.getCols();
		Matrix Xnorm = Matlib.createMatrix();
		Matrix Ynorm = Matlib.createMatrix();
// scale the inputs
		Matlib.normalize(X,Xmean,Xstd,Xnorm);
		Matlib.normalize(Y,Ymean,Ystd,Ynorm);

		Source.write("1; Version of this save/restore protocol for data sets");
		Source.newLine();
		Source.write(len+" ; Number of samples in this data-set");
		Source.newLine();
		Source.write(nin+" ; Length of each input data vector");
		Source.newLine();
		Source.write(nout+" ; Length of each output data vector");
		Source.newLine();
		for(int i=0;i<len;i++){
			String inputRow = arrayToText(Xnorm,i);
			String outputRow = arrayToText(Ynorm,i);
			double timeStamp = (double)i;
			Source.write(i+", "+timeStamp+", OK, "+inputRow+", " + outputRow);
			Source.newLine();
		}
		Matlib.clear(Xnorm);
		Matlib.clear(Ynorm);
	}

	private String arrayToText(Matrix m, int row){
		int cols = m.getCols();
		StringBuffer sb = new StringBuffer();
		for(int i=0;i<cols-1;i++){
			sb.append(m.get(row,i)+", ");
		}
		sb.append(m.get(row,cols-1)+"");
		return sb.toString();
	}

	public void readWeights(BufferedReader Source)throws IOException {
		String lineStr = Source.readLine();	
		int sepIndex = lineStr.indexOf(";",0);
		String valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		int version = Integer.valueOf(valueString).intValue();
		if(version != 1){
			return;
		}
//Read number of layes
		lineStr = Source.readLine();	
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		nlayers = Integer.valueOf(valueString).intValue();
//Read sizes of layes
		lineStr = Source.readLine();	
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		Vector ss = Parser.string2Strings(valueString,",");
		nodes = new int[nlayers];
		for(int i=0;i<nlayers;i++){
			String s = (String)ss.elementAt(i);
			nodes[i] = Integer.valueOf(s).intValue();
		}
		
//Read tranfer functions of layes
		lineStr = Source.readLine();	
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		ss = Parser.string2Strings(valueString,",");
		tf = new int[nlayers];
		for(int i=0;i<nlayers;i++){
			String s = (String)ss.elementAt(i);
			tf[i] = Integer.valueOf(s).intValue();
		}
//Read weight matrix
		for(int i=0;i<nlayers-1;i++){
			weights[i] = Matlib.zeros(nodes[i]+1,nodes[i+1]);
			for(int j=0;j<nodes[i]+1;j++){
				for(int k=0;k<nodes[i+1];k++){
					lineStr = Source.readLine();	
					sepIndex = lineStr.indexOf(";",0);
					valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
					double d = Double.valueOf(valueString).doubleValue();
					weights[i].set(j,k,d);
				}
			}
		}
//Read training result
		lineStr = Source.readLine();	
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		ss = Parser.string2Strings(valueString,",");
		String s = (String)ss.elementAt(5);
		rmse = Double.valueOf(s).doubleValue();
		rmse = Math.sqrt(rmse/ysize);
	}


	public double getRMSE(){
		return rmse;
	}

	public String getDescription(){
		String newLine = System.getProperty("line.separator");
		String nstr = "[";
		String tstr = "\n";
		for(int i=0;i<nlayers;i++){
			if(i != (nlayers-1)) {
				nstr = nstr + nodes[i]+", ";
			}
			else{
				nstr = nstr + nodes[i]+"]";
			}
			String ts = " Linear";
			if(tf[i] == 1){
				ts = " Sigmoid";
			}
			if(i != (nlayers-1)){
				tstr = tstr + ts+",\n";
			}
			else {
				tstr = tstr + ts + "\n";
			}
		}
		String description = "Number of layers: " + nlayers + newLine+"Nodes: "+nstr + newLine+"Transfer functions: "+tstr;
		return description;
	}

	/** write a BPN to a file in NOL format */
	public void writeUnscaledWeights(BufferedWriter Source) throws IOException {
		Source.write("1; Version of this file save/restore protocol");
		Source.newLine();
		Source.write(nlayers+"; Number of layers");
		Source.newLine();
		Source.write(""+nodes[0]);
		for(int i=1;i<nlayers;i++){
			Source.write(", "+nodes[i]);
		}
		Source.write("; Layer sizes of network");
		Source.newLine();
		Source.write(""+tf[0]);
		for(int i=1;i<nlayers;i++){
			Source.write(", "+tf[i]);
		}
		Source.write("; Transfer functions of network");
		Source.newLine();
		Matrix[] ws = new Matrix[weights.length];
		for(int l=0;l<nlayers-1;l++) {
			Matrix w = weights[l];
			Matrix w1 = Matlib.createMatrix();
			Matlib.copy(w,w1);
			ws[l] = w1;
		}
		incorporateScaleFactors(Xmean,  Xstd,  Ymean,  Ystd, ws);
		for(int l=0;l<nlayers-1;l++) {
			Matrix w = ws[l];
//Matlib.disp(w,"weight matrix "+l+" = ");
			for(int from=0;from<=nodes[l];from++) {   // le to include bias
				for(int to=0;to<nodes[l+1];to++) {
					Source.write(w.get(from,to)+" ; "+(from+1)+" "+(to+1)+" "+(l+1));
					Source.newLine();
				}
			}
			Matlib.clear(w);
		}
	}

	
/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() {
		Vector infors = new Vector();
		infors.addElement(new Double(nlayers));
		infors.addElement(nodes);
		infors.addElement(tf);
		
		Matrix[] ws = new Matrix[weights.length];
		for(int l=0;l<nlayers-1;l++) {
			Matrix w = weights[l];
			Matrix w1 = Matlib.createMatrix();
			Matlib.copy(w,w1);
			ws[l] = w1;
		}
		incorporateScaleFactors(Xmean,  Xstd,  Ymean,  Ystd, ws);

		for(int l=0;l<nlayers-1;l++) {
			Matrix w = ws[l];
			for(int from=0;from<=nodes[l];from++) {
				double[] w1 = new double[nodes[l+1]];
				for(int to=0;to<nodes[l+1];to++) {
					w1[to] = w.get(from,to);
				}
				infors.addElement(w1);
			}
			Matlib.clear(w);
		}
		ws = null;
		return infors;
	}

	private void incorporateScaleFactors(Matrix Xmean, Matrix Xstd, Matrix Ymean, Matrix Ystd, Matrix[] unscaledW) {
		double xm,xs,w,ym,ys;
		Matrix w1 = weights[0];
		Matrix w2 = weights[weights.length - 1];
		Matrix w11 = unscaledW[0];
		Matrix w12 = unscaledW[weights.length - 1];

		double biasweight = 0;
		int nhidden = nodes[1];
		int nin = nodes[0];
//input weight matrix
		for(int j=0;j<nhidden;j++) {
			biasweight = 0;
			for(int i=0;i<nin;i++) {  // not include bias
				xm = Xmean.get(0,i);
				xs = Xstd.get(0,i);
				w = w1.get(i,j)/xs;
				biasweight = biasweight + w1.get(i,j)*xm/xs;
				w11.set(i,j,w);
			}
			biasweight = w1.get(nin,j) - biasweight;
			w11.set(nin,j,biasweight);
		}
//output weight matrix
		int nout = nodes[nodes.length - 1];
		nhidden = nodes[nodes.length - 2];

		for(int j=0;j<nhidden;j++) {
			for(int i=0;i<nout;i++) {  // not include bias
				ys = Ystd.get(0,i);
				w = w2.get(j,i);
				w = w*ys;
				w12.set(j,i,w);
			}
		}
		for(int i=0;i<nout;i++) {  //take care of the bias
			ym = Ymean.get(0,i);
			ys = Ystd.get(0,i);
			biasweight = w2.get(nhidden,i);
			biasweight =  biasweight*ys + ym;
			w12.set(nhidden,i,biasweight);
		}
	}
}

