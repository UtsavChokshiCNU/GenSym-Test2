package com.gensym.math.datafit;

import java.io.*;
import java.util.*;
import com.gensym.math.*;
import com.gensym.math.matrix.*;
import com.gensym.nols.util.Parser;

/** 3-layer radio basis function model. Not trainable, but compatible with NOL Classic. */

public class ClassicRbfn implements Model, Serializable{
	static final long serialVersionUID = 1L;
	protected ArchitectureParameters AP;
	protected Matrix Xmean;		
	protected Matrix Xstd;		
	protected Matrix Ymean;
	protected Matrix Ystd;		
	protected Matrix MaxAct;		
	public double rmse;
	protected double ysize;
	public int nlayers;
	public int[] nodes;  // layer sizes
	public int unitType;
	public double overlap;	 
	public int bias;
	public Matrix[] weights;
	private boolean normalizeData;

	public ClassicRbfn(int[] nodes, double overlap, int unitType) {
		this.nlayers = 3;
		this.overlap = overlap;
		this.nodes = nodes;
		this.unitType = unitType;
		this.weights = new Matrix[nlayers];
		for(int i=0;i<nlayers-1;i++) {
			weights[i] = Matlib.createMatrix();
		}
		AP = new ArchitectureParameters(nodes[0], nodes[nlayers-1], 1, 1);

	}
	@Override
	public int getNin() {
		return nodes[0];
	}

	@Override
	public int getNout() {
		return nodes[nlayers-1];
	}

	public void setNout(int n) {
		nodes[nlayers-1] = n;
	}

	public void setBias(int bias){
		this.bias = bias;
	}

	public void setNormalizeData(boolean b){
		this.normalizeData = b;
	}

	@Override
	public ArchitectureParameters getArchitectureParameters() {
		ArchitectureParameters archParams = new ArchitectureParameters(getNin(), getNout(), -1, -1);
		return archParams;
	}

	public void prepareDataStat(Matrix X, Matrix Y)throws MathException{
		Xmean = Matlib.createMatrix();
		Ymean = Matlib.createMatrix();
		Xstd = Matlib.createMatrix();
		Ystd = Matlib.createMatrix();
		Matlib.mean(X,Xmean);
		Matlib.stdnonzero(X,Xstd);
		Matlib.mean(Y,Ymean);
		Matlib.stdnonzero(Y,Ystd);
		ysize = (double)Y.getCols()*Y.getRows();

	}

	/** Calculates values of Y, given X, using the current weights */
	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		int k = X.getRows();
		int nin = X.getCols();
		int h = weights[0].getRows();
		int hp = weights[2].getRows();
		int hout = weights[2].getCols();
		MaxAct.redimension(k,h);
		Matrix temp = Matlib.createMatrix();
		layer1(weights[0],weights[1],X,temp);
		if(hp==h+1) {
			Matlib.appendColumns(temp,Matlib.ones(k,1),temp);
		}
		Matlib.multiply(temp,weights[2],Y);
		Matlib.clear(temp);
	}

	private void layer1(Matrix M, Matrix shape, Matrix X, Matrix Y)throws MathException{
		int h = M.getRows();
		int hx = shape.getRows();
		int scol = shape.getCols();
		int k = X.getRows();
		int nin = X.getCols();

		Matrix sqdist = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		Matrix temp2 = Matlib.createMatrix();
		if(hx == h){
			dist2(X,M,sqdist);
			Matlib.multiplyElements(shape,shape,temp);
			Matlib.multiply(temp,Matlib.ones(1,k),temp);
			Matlib.divideElements(sqdist,temp,temp);
			Matlib.unaryMinus(temp,temp);
			Matlib.exp(temp,Y);
		}else if(hx == h*nin){
			for(int i=0;i<h;++i) {
				int start = i*nin;
				int finish = start+nin-1;
				Matlib.getPart(shape,start,0,finish,scol,temp);
				Matlib.getRow(M,i,temp2);
				Matlib.multiply(Matlib.ones(k,1),temp2,temp2);
				mahal2(temp2,X,temp,temp);
				Matlib.transpose(temp,temp);
				Matlib.unaryMinus(temp,temp);
				if(i==0){
					Matlib.exp(temp,Y);
				}else{
					Matlib.exp(temp,temp);
					Matlib.appendColumns(Y,temp,Y);
				}
			}
		}
		Matlib.clear(temp);
		Matlib.clear(temp2);
		Matlib.clear(sqdist);
	}

	private void mahal2(Matrix X1,Matrix X2, Matrix shape,Matrix Y) throws MathException{
		int k = X1.getRows();
		int nin = X1.getCols();
		Matrix temp1 = Matlib.createMatrix();
		Matrix temp2 = Matlib.createMatrix();
		Matrix diff = Matlib.createMatrix();
		Y.redimension(1,k);
		for (int i=0;i<k;++i) {
			Matlib.getRow(X1,i,temp1);
			Matlib.getRow(X2,i,temp2);
			Matlib.subtract(temp1,temp2,diff);
			Matlib.multiply(diff,shape,temp1);
			Matlib.transpose(diff,diff);
			Matlib.multiply(temp1,diff,temp1);
			Y.set(0,i,temp1.get(0));
		}
		Matlib.clear(temp1);
		Matlib.clear(temp2);
		Matlib.clear(diff);
	}

	private void dist2(Matrix X1, Matrix X2, Matrix Y)throws MathException{
		int row1 = X1.getRows();
		int col1 = X1.getCols();
		int row2 = X2.getRows();
		int col2 = X2.getCols();
		Matrix temp = Matlib.createMatrix();
		Matrix sqdist = Matlib.createMatrix();
		for(int i=0;i<row2;++i) {
			Matlib.getRow(X2, i, temp);
			Matlib.multiply(Matlib.ones(row1,1), temp, temp);
			Matlib.subtract(X1,temp,temp);
			Matlib.multiplyElements(temp,temp,temp);
			if(col1 == 1){
				if(i==0){
					Matlib.transpose(temp,sqdist);
				}else{
					Matlib.transpose(temp,temp);
					Matlib.appendRows(sqdist,temp,temp);
				}
			}else{
				if(i==0){
					Matlib.transpose(temp,sqdist);
					Matlib.sum(sqdist,sqdist);
				}else{
					Matlib.transpose(temp,temp);
					Matlib.sum(temp,temp);
					Matlib.appendRows(sqdist,temp,temp);
				}
			}
		}
		Matlib.clear(temp);
		Matlib.copy(sqdist,Y);
		Matlib.clear(sqdist);
	}

	public void writeData(BufferedWriter Source, Matrix X, Matrix Y)throws IOException, MathException{ 
//System.out.println("class this="+this);
		int len = X.getRows();
		int nin = X.getCols();
		int nout = Y.getCols();

		Source.write("1; Version of this save/restore protocol for data sets");
		Source.newLine();
		Source.write(len+" ; Number of samples in this data-set");
		Source.newLine();
		Source.write(nin+" ; Length of each input data vector");
		Source.newLine();
		Source.write(nout+" ; Length of each output data vector");
		Source.newLine();
		if(normalizeData){
// scale the inputs
			Matrix Xnorm = Matlib.createMatrix();
			Matrix Ynorm = Matlib.createMatrix();
			Matlib.normalize(X,Xmean,Xstd,Xnorm);
			Matlib.normalize(Y,Ymean,Ystd,Ynorm);

			for(int i=0;i<len;i++){
				String inputRow = arrayToText(Xnorm,i);
				String outputRow = arrayToText(Ynorm,i);
				double timeStamp = (double)i;
				Source.write(i+", "+timeStamp+", OK, "+inputRow+", " + outputRow);
				Source.newLine();
			}
			Matlib.clear(Xnorm);
			Matlib.clear(Ynorm);
		}else{
			for(int i=0;i<len;i++){
				String inputRow = arrayToText(X,i);
				String outputRow = arrayToText(Y,i);
				double timeStamp = (double)i;
				Source.write(i+", "+timeStamp+", OK, "+inputRow+", " + outputRow);
				Source.newLine();
			}
		}
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
		int version = Integer.parseInt(valueString);
		if(version != 1){
			return;
		}
//Read sizes of layes
		lineStr = Source.readLine();	
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		Vector ss = Parser.string2Strings(valueString,",");
		nodes = new int[nlayers];
		for(int i=0;i<nlayers;i++){
			String s = (String)ss.elementAt(i);
			nodes[i] = Integer.parseInt(s);
		}
//Read overlap
		lineStr = Source.readLine();	
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		overlap = Double.parseDouble(valueString);
//Read unitType
		lineStr = Source.readLine();	
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		unitType = Integer.parseInt(valueString);
//Read bias
		lineStr = Source.readLine();	
		sepIndex = lineStr.indexOf(";",0);
		valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
		bias= Integer.parseInt(valueString);
		
		int nin = nodes[0];
		int nout = nodes[2];
		int h = nodes[1];
		int hp,hx,nx;
		if(bias==1) 
			hp = h+1; 
		else 
			hp = h;
		if(unitType == 0) {
			hx = h; 
			nx=1;
		}else{
			hx = nin*h; 
			nx = nin;
		}
//Read weight matrix
		weights[0] = Matlib.zeros(h,nin);
		for(int i=0;i<h;i++){
			lineStr = Source.readLine();	
			sepIndex = lineStr.indexOf(";",0);
			valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
			ss = Parser.string2Strings(valueString,",");
			for(int j=0;j<nin;j++){
				String s = (String)ss.elementAt(j);
				double d = Double.parseDouble(s);
				weights[0].set(i,j,d);
			}
		}
		weights[1] = Matlib.zeros(hx,nx);
		for(int i=0;i<hx;i++){
			lineStr = Source.readLine();	
			sepIndex = lineStr.indexOf(";",0);
			valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
			ss = Parser.string2Strings(valueString,",");
			for(int j=0;j<nx;j++){
				String s = (String)ss.elementAt(j);
				double d = Double.parseDouble(s);
				weights[1].set(i,j,d);
			}
		}
		weights[2] = Matlib.zeros(hp,nout);
		for(int i=0;i<hp;i++){
			lineStr = Source.readLine();	
			sepIndex = lineStr.indexOf(";",0);
			valueString = lineStr.substring(0,sepIndex).trim();   // eliminate trim?
			ss = Parser.string2Strings(valueString,",");
			for(int j=0;j<nout;j++){
				String s = (String)ss.elementAt(j);
				double d = Double.parseDouble(s);
				weights[2].set(i,j,d);
			}
		}

	}

	/** write a RBFN to a file in NOL format */
	public void writeParameters(BufferedWriter Source) throws IOException {
		Source.write("1; Version of this file save/restore protocol for RBFNs or Rho-Nets");
		Source.newLine();
		Source.write(""+nodes[0]);
		for(int i=1;i<nlayers;i++){
			Source.write(", "+nodes[i]);
		}
		Source.write("; Layer sizes.");
		Source.newLine();
		Source.write(overlap+"; Unit overlap parameter");
		Source.newLine();
		Source.write(unitType+"; Unit type (0 = spherical, 1 = elliptical) ");
		Source.newLine();
		Source.write(bias+"; Bias (0 = omitted, 1 = included)");
		Source.newLine();
	}

	public void writeWeights(BufferedWriter Source) throws IOException {

		int nin = nodes[0];
		int nout = nodes[2];
		int h = nodes[1];
		int hp,hx,nx;
		if(bias==1) 
			hp = h+1; 
		else 
			hp = h;
		if(unitType == 0) {
			hx = h; 
			nx=1;
		}else{
			hx = nin*h; 
			nx = nin;
		}

		for(int i=0;i<h;i++){
			for(int j=0;j<nin;j++){
				if(j == nin-1){
					Source.write(weights[0].get(i,j)+" ; Unit centers");
				}else{
					Source.write(weights[0].get(i,j)+",");
				}
			}
			Source.newLine();
		}
		for(int i=0;i<hx;i++){
			for(int j=0;j<nx;j++){
				if(j == nx-1){
					Source.write(weights[1].get(i,j)+" ; Unit shapes");
				}else{
					Source.write(weights[1].get(i,j)+",");
				}
			}
			Source.newLine();
		}
		for(int i=0;i<hp;i++){
			for(int j=0;j<nout;j++){
				if(j == nout-1){
					Source.write(weights[2].get(i,j)+" ; Second layer weights");
				}else{
					Source.write(weights[2].get(i,j)+",");
				}
			}
			Source.newLine();
		}		
	}

	public void writeNormalizeFactorToFile(BufferedWriter Source) throws IOException {
		Source.write("Means,");
		for(int i=0;i<Xmean.getCols();i++){
			Source.write(Xmean.get(0,i)+",");
		}
		for(int i=0;i<Ymean.getCols();i++){
			Source.write(String.valueOf(Ymean.get(0,i)));
			if(i<Ymean.getCols()-1) {
				Source.write(",");
			}
		}
		Source.newLine();
		Source.write("Stds,");
		for(int i=0;i<Xstd.getCols();i++){
			Source.write(Xstd.get(0,i)+",");
		}
		for(int i=0;i<Ystd.getCols();i++){
			Source.write(String.valueOf(Ystd.get(0,i)));
			if(i<Ystd.getCols()-1) {
				Source.write(",");
			}
		}
		Source.newLine();
	}

	public void unnormalizePrediction(Matrix Y)throws MathException{
		Matlib.unnormalize(Y,Ymean,Ystd,Y);
	}

	public double getRMSE(){
		return rmse;
	}

	public String getDescription(){
		String newLine = System.getProperty("line.separator");
		String description =""+nodes[0];
		for(int i=1;i<nlayers;i++) {
			description = description + ", "+nodes[i];
		}
		description = description +"; Layer sizes."+ newLine;
		description = description + overlap+"; Unit overlap parameter"+ newLine;
		description = description + unitType+"; Unit type (0 = spherical, 1 = elliptical) "+ newLine;
		description = description + bias+"; Bias (0 = omitted, 1 = included)"+ newLine;
		return description;
	}

/** Return the model information as in a Vector */
	public Vector getParametersVector() {
		Vector infors = new Vector();
		infors.addElement(3d);
		infors.addElement(nodes);
		int nin = nodes[0];
		int nout = nodes[2];
		int h = nodes[1];
		int hp,hx,nx;
		if(bias==1) 
			hp = h+1; 
		else 
			hp = h;
		if(unitType == 0) {
			hx = h; 
			nx=1;
		}else{
			hx = nin*h; 
			nx = nin;
		}		
		infors.addElement(overlap);
		infors.addElement(unitType);

		// Unit centers
		for(int i=0;i<h;i++){
			double[] w1 = new double[nin];
			for(int j=0;j<nin;j++){
				w1[j]= weights[0].get(i,j);
			}
			infors.addElement(w1);
		}
		//Unit shapes
		for(int i=0;i<hx;i++){
			double[] w1 = new double[nx];
			for(int j=0;j<nx;j++){
				w1[j]= weights[1].get(i,j);
			}
			infors.addElement(w1);
		}
		//Second layer weights
		for(int i=0;i<hp;i++){
			double[] w1 = new double[nout];
			for(int j=0;j<nout;j++){
				w1[j]= weights[2].get(i,j);
			}
			infors.addElement(w1);
		}		
		return infors;
	}

/** Set the model information as in a Vector */
	public void setParametersVector(Vector params) {

		nodes  = (int[])params.elementAt(1);
		overlap = ((Number)params.elementAt(2)).doubleValue();
		unitType = ((Number)params.elementAt(3)).intValue();
		int count = 4;
		int nin = nodes[0];
		int nout = nodes[2];
		int h = nodes[1];
		int hp,hx,nx;
		if(bias==1) 
			hp = h+1; 
		else 
			hp = h;
		if(unitType == 0) {
			hx = h; 
			nx=1;
		}else{
			hx = nin*h; 
			nx = nin;
		}		
		// Unit centers
		for(int i=0;i<h;i++){
			double[] w1 = (double[])params.elementAt(count);
			for(int j=0;j<nin;j++){
				weights[0].set(i,j,w1[j]);
			}
			count = count +1;
		}
		//Unit shapes
		for(int i=0;i<hx;i++){
			double[] w1 = (double[])params.elementAt(count);
			for(int j=0;j<nx;j++){
				weights[1].set(i,j,w1[j]);
			}
			count = count +1;
		}
		//Second layer weights
		for(int i=0;i<hp;i++){
			double[] w1 = (double[])params.elementAt(count);
			for(int j=0;j<nout;j++){
				weights[2].set(i,j,w1[j]);
			}
			count = count +1;
		}		
	}
	/** write a rbfn to a file in XML format */
	public int writeXMLFile(final BufferedWriter target, final int indentNumber) throws IOException {
		String dataString = Utilities.indent(indentNumber)+"<rbfn>\n";
		target.write(dataString,0,dataString.length());
		int indent = indentNumber;
		indent++;
		for(int i=0;i<nodes.length;i++){
			dataString = Utilities.indent(indent)+"<layer>\n";
			target.write(dataString,0,dataString.length());
			indent++;
			dataString = Utilities.indent(indent)+"<layerIndex>"+(i+1)+"</layerIndex>\n";
			target.write(dataString,0,dataString.length());
			dataString = Utilities.indent(indent)+"<layerSize>"+nodes[i]+"</layerSize>\n";
			target.write(dataString,0,dataString.length());
			indent--;
			dataString = Utilities.indent(indent)+"</layer>\n";
			target.write(dataString,0,dataString.length());
		}
		dataString = Utilities.indent(indent)+"<overlap>"+overlap+"</overlap>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<unitType>"+unitType+"</unitType>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<bias>"+bias+"</bias>\n";
		target.write(dataString,0,dataString.length());

		int nin = nodes[0];
		int nout = nodes[2];
		int h = nodes[1];
		int hp,hx,nx;
		if(bias==1) 
			hp = h+1; 
		else 
			hp = h;
		if(unitType == 0) {
			hx = h; 
			nx=1;
		}else{
			hx = nin*h; 
			nx = nin;
		}

		dataString = Utilities.indent(indent)+"<unitCenters>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		for(int i=0;i<h;i++){
			for(int j=0;j<nin;j++){
				dataString = Utilities.indent(indent)+"<node>\n";
				target.write(dataString,0,dataString.length());
				indent++;
				dataString = Utilities.indent(indent)+"<center>"+weights[0].get(i,j)+"</center>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<row>"+i+"</row>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<column>"+j+"</column>\n";
				target.write(dataString,0,dataString.length());
				indent--;
				dataString = Utilities.indent(indent)+"</node>\n";
				target.write(dataString,0,dataString.length());
			}
		}
		indent--;
		dataString = Utilities.indent(indent)+"</unitCenters>\n";
		target.write(dataString,0,dataString.length());

		dataString = Utilities.indent(indent)+"<unitShapes>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		for(int i=0;i<hx;i++){
			for(int j=0;j<nx;j++){
				dataString = Utilities.indent(indent)+"<node>\n";
				target.write(dataString,0,dataString.length());
				indent++;
				dataString = Utilities.indent(indent)+"<center>"+weights[1].get(i,j)+"</center>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<row>"+i+"</row>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<column>"+j+"</column>\n";
				target.write(dataString,0,dataString.length());
				indent--;
				dataString = Utilities.indent(indent)+"</node>\n";
				target.write(dataString,0,dataString.length());
			}
		}
		indent--;
		dataString = Utilities.indent(indent)+"</unitShapes>\n";
		target.write(dataString,0,dataString.length());

		dataString = Utilities.indent(indent)+"<secondLayerWeights>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		for(int i=0;i<hp;i++){
			for(int j=0;j<nout;j++){
				dataString = Utilities.indent(indent)+"<node>\n";
				target.write(dataString,0,dataString.length());
				indent++;
				dataString = Utilities.indent(indent)+"<weight>"+weights[2].get(i,j)+"</weight>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<row>"+i+"</row>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<column>"+j+"</column>\n";
				target.write(dataString,0,dataString.length());
				indent--;
				dataString = Utilities.indent(indent)+"</node>\n";
				target.write(dataString,0,dataString.length());
			}
		}		
		indent--;
		dataString = Utilities.indent(indent)+"</secondLayerWeights>\n";
		target.write(dataString,0,dataString.length());
		
		indent--;
		dataString = Utilities.indent(indent)+"</rbfn>\n";
		target.write(dataString,0,dataString.length());
		return indent;
	}

	public boolean isNormalizedData() {
	    return normalizeData;
    }
}

