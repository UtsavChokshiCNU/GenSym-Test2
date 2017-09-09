package com.gensym.nols.data;
/*
 *		Gensym Model Class.
 *		This class is extended from Object.class
 *		Modified 3/25/98 by Gchen
 */

import java.util.*;
import java.io.*;
import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;
import com.gensym.math.stats.Stats;

/** Model class. */
public class NolPcaModel extends NolModel2{
	static final long serialVersionUID = 1L;

	private Matrix score;
	private Matrix Xmean;
	private Matrix Xstd;
	private Matrix P;
	private Matrix Pclim;
	private Matrix Variants;
	private Matrix ssq;

	private DataSeries dataSeries;
	private int retainedFactorNumber = 5;
	private double defaultCutVariant = 0.9;
	private Matrix Res;
	private Matrix T2;
	private double Q;
	private double tsq;


	public ClassicValidationParameters trainingResults;

/** Create a Model object with given variables.*/	
	public NolPcaModel(String name, Vector varNames, Preprocessor prep){
		preprocessor = prep;
		preprocessorHashCode = prep.hashCode();
		this.name = new String(name);
		try{
			inputs = (Vector)varNames.clone();
			outputs = new Vector();
			outputs.addElement(varNames.elementAt(0));
		}catch(Exception e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
		String varName = (String)outputs.elementAt(0); 
		Variable var = prep.getVariableFromVariableName(varName);
		dataSeries = var.getDataSeries();
	}

/** Create a Model object with given variable objects.This creator is used for the model just for exportation.*/	
	public NolPcaModel(String name, Vector varObjs){
		this.name = new String(name);
		inputs = new Vector();
		outputs = new Vector();
		if (varObjs.isEmpty()) 
			return;
		for (int i=0;i<varObjs.size();i++){
			inputs.addElement(varObjs.elementAt(i).toString());
		}
		outputs.addElement(varObjs.elementAt(0).toString());
		Variable var = (Variable)varObjs.elementAt(0);
		dataSeries = var.getDataSeries();
	}

	public void train()throws MathException{
		int nVar = dataSeries.getColumn();
		Matrix X0 = dataSeries.getDataMatrix();  // do not clear or change X0, it is permanent!
		// temporary matrices, must be cleared
		Matrix badCols = Matlib.createMatrix();  
		int ncols = X0.getCols();
		Matrix S = Matlib.createMatrix(1,ncols);
		for(int i=0; i<ncols; i++) {
			Variable var = dataSeries.getVarByIndex(i);
			boolean included = inputs.contains(var.getName());
			if (included) {
				S.set(0,i,1.0);
			}else{
				S.set(0,i,0.0);
			}
		}
		Matrix X = Matlib.createMatrix();
		Matlib.getColumns(X0, S, X);

		Matlib.findZeroVarianceColumns(X, badCols);  // also finds columns with all NaNs
		boolean badMatrix = false;
		for(int i=0; i<badCols.getCols(); i++) {
			if(Double.compare(badCols.get(0,i), 1.0) == 0) {
				badMatrix = true;
				break;
			}
		}
		if(badMatrix) {
			Matlib.clear(badCols);
			Matlib.clear(S);
			Matlib.clear(X);
			throw new MathException("There is variable with all NaNs.");
		}
		// now find good rows
		Matrix goodRows = Matlib.createMatrix();
		Matlib.findFiniteRows(X,goodRows);
		Matlib.sum(goodRows,S);
		if(S.get(0,0)<=X.getCols()) {
//System.out.println("S.get(0,0) is "+S.get(0,0)+" goodCols by "+goodCols);
			Matlib.clear(badCols);
			Matlib.clear(S);
			Matlib.clear(X);
			Matlib.clear(goodRows);
			throw new MathException("Not enough valid rows to create projection plot.");
		}
		if((int) Math.rint(S.get(0,0))<X.getRows()) {
			Matlib.getRows(X, goodRows, X);
		}
		// Now do mean centering and scaling of X matrix
		Xmean = Matlib.createMatrix();
		Xstd = Matlib.createMatrix();
		//System.out.println("X is "+X.getRows()+" by "+X.getCols());
		Matlib.mean(X, Xmean);
		Matlib.stdnonzero(X, Xstd);
		Matlib.normalize(X, Xmean, Xstd, X);
		// Now do the PCA calculation
		P = Matlib.createMatrix();
		Pclim = Matlib.createMatrix();
		Variants = Matlib.createMatrix();
		ssq = Matlib.createMatrix();
		Stats.pca(X, P, Pclim, ssq, Variants); 

		retainedFactorNumber = Variants.getCols();
		for(int i=0;i<Variants.getCols();i++) {
			if (Variants.get(i) >= defaultCutVariant) {
				retainedFactorNumber = i+1;
				break;
			}
		}
		Matlib.multiply(X, P, S);
		Matrix V = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		Matlib.getColumns(P,0,retainedFactorNumber-1,V);
		Matlib.multiply(X,V,temp);
		Matlib.transpose(V,V);
		Matlib.multiply(temp,V,temp);
		Matlib.subtract(X,temp,temp);
		Matlib.transpose(temp,temp);
		Matlib.powerElements(temp, 2.0,temp);
		Matlib.sum(temp,temp);

		int row = goodRows.getRows();
		int col = S.getCols();
		score = Matlib.createMatrix(row,col);
		if (Res == null){
			Res = Matlib.createMatrix(row,1);
		}else{
			Res.redimension(row,1);
		}
		int rr=0;
		for(int r = 0; r < row; r++) {
			if(Double.compare(goodRows.get(r,0), 1.0) == 0){
				for(int c=0;c<col;c++){
					score.set(r,c,S.get(rr,c));
				}
				Res.set(r,0,temp.get(rr));
				rr++;
			}else{
				for(int c=0;c<col;c++){
					score.set(r,c,Double.NaN);
				}
				Res.set(r,0,Double.NaN);
			}
		}
		double th1 = 0;
		double th2 = 0;
		double th3 = 0;
		for (int i = retainedFactorNumber; i<col;i++){
			th1 = th1 + ssq.get(i);
			th2 = th2 + ssq.get(i)*ssq.get(i);
			th3 = th3 + ssq.get(i)*ssq.get(i)*ssq.get(i);
		}
		double h0 = 1 - ((2*th1*th3)/(3*th2*th2));
		if (h0 <= 0.0){
			h0 = 0.0001;
		}
		Q = 1.65*Math.sqrt(2*th2*h0*h0)/th1 + 1 + th2*h0*(h0-1)/(th1*th1);
		Q = th1*(Math.pow(Q,1/h0));
		int m = S.getRows();
		if(retainedFactorNumber > 1) {
			if (m > 300){
				tsq = (retainedFactorNumber*(m-1)/(m-retainedFactorNumber))*Stats.ftest(.05,retainedFactorNumber,300);
			}else{
				tsq = (retainedFactorNumber*(m-1)/(m-retainedFactorNumber))*Stats.ftest(.05,retainedFactorNumber,m-retainedFactorNumber);
			}
			temp.redimension(1,retainedFactorNumber);
			for (int i =0; i< retainedFactorNumber; i++){
				temp.set(0,i,1 / Math.sqrt(ssq.get(i)));
			}
			Matlib.getColumns(score,0,retainedFactorNumber,V);
			for(int r = 0; r < row; r++) {
				for(int c=0;c<retainedFactorNumber;c++){
					V.set(r,c,V.get(r,c) / temp.get(c));
				}
			}
			Matlib.transpose(V,V);
			if(T2 == null) {
				T2 = Matlib.createMatrix();
			}
			Matlib.sum(V,T2);
		}else{
			tsq = 1.96*1.96;
			Matlib.clear(badCols);
			Matlib.clear(S);
			Matlib.clear(X);
			Matlib.clear(V);
			Matlib.clear(temp);
			Matlib.clear(goodRows);
			throw new MathException("T^2 not calculated when number of latent variables = 1.");
		}
		Matlib.clear(badCols);
		Matlib.clear(S);
		Matlib.clear(X);
		Matlib.clear(V);
		Matlib.clear(temp);
		Matlib.clear(goodRows);
	}

	public int getRetainedFactorNumber(){
		return retainedFactorNumber;
	}

	private void prepareTrainingData(Matrix X, Matrix goodRows) throws MathException{
		int nVar = dataSeries.getColumn();
		Matrix X0 = dataSeries.getDataMatrix();  // do not clear or change X0, it is permanent!
		// temporary matrices, must be cleared
		Matrix badCols = Matlib.createMatrix();  
		int ncols = X0.getCols();
		Matrix S = Matlib.createMatrix(1,ncols);
		for(int i=0; i<ncols; i++) {
			Variable var = dataSeries.getVarByIndex(i);
			boolean included = inputs.contains(var.getName());
			if (included) {
				S.set(0,i,1.0);
			}else{
				S.set(0,i,0.0);
			}
		}
		Matlib.getColumns(X0, S, X);
		Matlib.findZeroVarianceColumns(X, badCols);  // also finds columns with all NaNs
		boolean badMatrix = false;
		for(int i=0; i<badCols.getCols(); i++) {
			if(Double.compare(badCols.get(0,i), 1.0) == 0) {
				badMatrix = true;
				break;
			}
		}
		if(badMatrix) {
			Matlib.clear(badCols);
			Matlib.clear(S);
			throw new MathException("There is variable with all NaNs.");
		}
		// now find good rows
		Matlib.findFiniteRows(X,goodRows);
		Matlib.sum(goodRows,S);
		if(S.get(0,0)<=X.getCols()) {
			Matlib.clear(badCols);
			Matlib.clear(S);
			Matlib.clear(goodRows);
			throw new MathException("Not enough valid rows to create projection plot.");
		}
		if((int) Math.rint(S.get(0,0))<X.getRows()) {
			Matlib.getRows(X, goodRows, X);
		}
		Matlib.normalize(X, Xmean, Xstd, X);
		Matlib.clear(badCols);
		Matlib.clear(S);
	}

	public void setRetainedFactorNumber(int f){
		int col = Variants.getCols();
		if (f > col || f< 0){
			retainedFactorNumber = col;
		}else{
			retainedFactorNumber = f;
		}
		Matrix X = Matlib.createMatrix();
		Matrix goodRows = Matlib.createMatrix();
		Matrix V = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		try{
			prepareTrainingData(X,goodRows);
			Matlib.getColumns(P,0,retainedFactorNumber-1,V);
			Matlib.multiply(X,V,temp);
			Matlib.transpose(V,V);
			Matlib.multiply(temp,V,temp);
			Matlib.subtract(X,temp,temp);
			Matlib.transpose(temp,temp);
			Matlib.powerElements(temp, 2.0,temp);
			Matlib.sum(temp,temp);
			int row = goodRows.getRows();
			if (Res == null){
				Res = Matlib.createMatrix(row,1);
			}else{
				Res.redimension(row,1);
			}
			int rr=0;
			for(int r = 0; r < row; r++) {
				if(Double.compare(goodRows.get(r,0), 1.0) == 0){
					Res.set(r,0,temp.get(rr));
					rr++;
				}else{
					Res.set(r,0,Double.NaN);
				}
			}

			double th1 = 0;
			double th2 = 0;
			double th3 = 0;
			for (int i = retainedFactorNumber; i<col;i++){
				th1 = th1 + ssq.get(i);
				th2 = th2 + ssq.get(i)*ssq.get(i);
				th3 = th3 + ssq.get(i)*ssq.get(i)*ssq.get(i);
			}
			double h0 = 1 - ((2*th1*th3)/(3*th2*th2));
			if (h0 <= 0.0){
				h0 = 0.0001;
			}
			Q = 1.65*Math.sqrt(2*th2*h0*h0)/th1 + 1 + th2*h0*(h0-1)/(th1*th1);
			Q = th1*(Math.pow(Q,1/h0));
		}catch (MathException evt){
			Matlib.clear(temp);
			Matlib.clear(V);
			Matlib.clear(X);
			Matlib.clear(goodRows);
		}
		Matlib.clear(temp);
		Matlib.clear(V);
		Matlib.clear(X);
		Matlib.clear(goodRows);
	}

	public Matrix getScore(){
		return score;
	}
	public Matrix getLoadings(){
		return P;
	}

	public double getQ(){
		return Q;
	}

	public Matrix getSPEStatistics(){
		return Res;
	}

	public Matrix getScoreLimits(){
		return Pclim;
	}

	public Matrix getEigenvalues(){
		return ssq;
	}

	public Matrix getVariants(){
		return Variants;
	}
	
	public Matrix getT2Statistics(){
		return T2;
	}
	
	public double getT2Limits(){
		return tsq;
	}
	
	public DataSeries getDataSeries(){
		return dataSeries;
	}

	@Override
	public String getDescription(){
		return "";
	}

/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() throws MathException {
		Vector para = new Vector();
		para.addElement(10);
		int N = Xmean.getCols();
		para.addElement(N);
		para.addElement(retainedFactorNumber);

		double[] pp = Matlib.create1DArray(Xmean);
		para.addElement(pp);
		pp = Matlib.create1DArray(Xstd);
		para.addElement(pp);
		pp = Matlib.create1DArray(Variants);
		para.addElement(pp);

		
		for (int i=0;i<N;i++) {
			pp = new double[retainedFactorNumber];
			for (int j=0;j<retainedFactorNumber;j++) {
				pp[j] =P.get(i,j);
			}
			para.addElement(pp);
		}
		pp = Matlib.create1DArray(Pclim);
		para.addElement(pp);
		pp = Matlib.create1DArray(ssq);
		para.addElement(pp);
		para.addElement(Q);
		para.addElement(tsq);

		return para;
	}

/** Return the model data as in a Vector */
	public Vector getDataVector() throws MathException {
		Vector para = new Vector();
		para.addElement(11);
		para.addElement(retainedFactorNumber);

		Matrix V = Matlib.createMatrix();
		Matrix W = Matlib.createMatrix();
		int row = score.getRows();
		if(retainedFactorNumber > 1) {
			Matlib.getColumns(score,0,retainedFactorNumber,V);
		}
		Matlib.copy(score,V);
		Matlib.copy(Res,W);
		if (row > 1000){
			Matrix B = Matlib.createMatrix();
			Stats.randomSplit(row,1000,B);
			Matlib.getRows(V,B,V);
			Matlib.getRows(W,B,W);
			Matlib.findFiniteRows(V,B);
			Matlib.getRows(V,B,V);
			Matlib.getRows(W,B,W);
			Matlib.clear(B);
			row = V.getRows();
		}
		para.addElement(row);
		for (int i=0;i<row;i++) {
			double[] pp = new double[V.getCols()];
			for (int j=0;j<retainedFactorNumber;j++) {
				pp[j] =V.get(i,j);
			}
			para.addElement(pp);
		}
		for (int i=0;i<row;i++) {
			para.addElement(W.get(i));
		}
		Matlib.clear(V);
		Matlib.clear(W);
		return para;
	}
/** Set the model information as in a Vector */
	@Override
	public void setParametersVector(Vector params) throws MathException {
	}

/** Save the parameters into a file */
	public void saveParameters(BufferedWriter Source) throws IOException {
		Source.write("10; Version of this file for PCA save/restore protocol");
		Source.newLine();
		int N = Xmean.getCols();
		Source.write(N+"; Number of variables");
		Source.newLine();
		Source.write(retainedFactorNumber+"; Number of factors");
		Source.newLine();

		for (int i=0;i<N;i++) {
			if(i<N-1){
				Source.write(Xmean.get(0,i)+",");
			}else{
				Source.write(Xmean.get(0,i)+"; Means");
			}
		}
		Source.newLine();
		for (int i=0;i<N;i++) {
			if(i<N-1){
				Source.write(Xstd.get(0,i)+",");
			}else{
				Source.write(Xstd.get(0,i)+"; Stds");
			}
		}
		Source.newLine();
		for (int i=0;i<N;i++) {
			if(i<N-1){
				Source.write(Variants.get(0,i)+",");
			}else{
				Source.write(Variants.get(0,i)+"; Explained variants");
			}
		}
		Source.newLine();

		for (int i=0;i<N;i++) {
			for (int j=0;j<retainedFactorNumber;j++) {
				if(j<retainedFactorNumber-1){
					Source.write(P.get(i,j)+",");
				}else{
					Source.write(P.get(j,j)+"; Weight");
				}
			}
			Source.newLine();
		}

//new for version 5.0r0
		Source.write("50; New version");
		Source.newLine();
		for (int i=0;i<N;i++) {
			if(i<N-1){
					Source.write(Pclim.get(i)+",");
			}else{
					Source.write(Pclim.get(i)+"; PC Limits");			
			}
		}
		Source.newLine();
		for (int i=0;i<N;i++) {
			if(i<N-1){
					Source.write(ssq.get(i)+",");
			}else{
					Source.write(ssq.get(i)+"; EigenValues");			
			}
		}
		Source.newLine();
		Source.write(Q+"; Q value");
		Source.newLine();
		Source.write(tsq+"; tsq value");
		Source.newLine();
	}

/** Save the original scores into a file */
	public void saveScores(BufferedWriter Source) throws IOException, MathException {
		Source.write("11; Version of this file for PCA save/restore protocol");
		Source.newLine();
		Source.write(retainedFactorNumber+"; Number of factors");
		Source.newLine();

		Matrix V = Matlib.createMatrix();
		Matrix W = Matlib.createMatrix();
		int row = score.getRows();
		if(retainedFactorNumber > 1) {
			Matlib.getColumns(score,0,retainedFactorNumber,V);
		}
		Matlib.copy(score,V);
		Matlib.copy(Res,W);
		if (row > 1000){
			Matrix B = Matlib.createMatrix();
			Stats.randomSplit(row,1000,B);
			Matlib.getRows(V,B,V);
			Matlib.getRows(W,B,W);
			Matlib.findFiniteRows(V,B);
			Matlib.getRows(V,B,V);
			Matlib.getRows(W,B,W);
			Matlib.clear(B);
			row = V.getRows();
		}
		Source.write(row+"; Number of samples");
		Source.newLine();
		for (int i=0;i<row;i++) {
			for (int j=0;j<retainedFactorNumber;j++) {
				if(j < retainedFactorNumber-1){
					Source.write(V.get(i,j)+",");
				}else{
					Source.write(V.get(i,j)+";");
				}
			}
			Source.newLine();
		}
		for (int i=0;i<row;i++) {
			Source.write(W.get(i)+";");
			Source.newLine();
		}
		Matlib.clear(V);
		Matlib.clear(W);
	}

	@Override
	public void evaluate(Matrix X, Matrix pc) throws MathException{
		Matrix Temp = Matlib.createMatrix();
		Matrix V = Matlib.createMatrix();
		Matlib.getColumns(P,0,retainedFactorNumber-1,V);
		Matlib.normalize(X, Xmean, Xstd, Temp);
		Matlib.multiply(Temp, V, pc);
		Matlib.clear(Temp);
		Matlib.clear(V);
	}

	public void fullEvaluate(Matrix X, Matrix pc,Matrix Res) throws MathException{
		Matrix Temp = Matlib.createMatrix();
		Matrix V = Matlib.createMatrix();
		Matlib.getColumns(P,0,retainedFactorNumber-1,V);
		Matlib.normalize(X, Xmean, Xstd, Temp);
		Matlib.multiply(Temp, V, pc);
		Matlib.transpose(V,V);
		Matlib.multiply(pc,V,V);
		Matlib.subtract(Temp,V,Temp);
		Matlib.transpose(Temp,Temp);
		Matlib.powerElements(Temp, 2.0,Temp);
		Matlib.sum(Temp,Res);
		Matlib.clear(Temp);
		Matlib.clear(V);
	}

	@Override
	public int getNin(){
		return inputs.size();
	}

	@Override
	public int getNout(){
		return 0;
	}

}


