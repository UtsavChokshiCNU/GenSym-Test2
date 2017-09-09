package com.gensym.math.rank;

import com.gensym.nols.dlg.ProgressListener;
import com.gensym.nols.dlg.ProgressEvent;
import com.gensym.math.*;
import com.gensym.math.matrix.*;
import java.util.*;
import com.gensym.math.stats.*;
import com.gensym.nols.data.Variable;

public final class Rank {
	private Vector itsListeners;
	private static int LIMITSIZE = 3000;

	public Rank() {
		itsListeners = new Vector(0,10);
	}
	
	public Rank(Rank rank){
		Collections.copy(this.itsListeners, rank.itsListeners);
	}

	/** add listener.*/
	public void addListener(ProgressListener l) {
		itsListeners.addElement(l);
	}

	public void performRanking(Vector inVars, Vector inputDelays, Vector outVars, Vector ratings) throws MathException {
		long[] outTimes = TimeFunctions.getOutputTimes(outVars);
		if(outTimes==null) {  // row-based data
			performRanking(inVars,outVars,ratings);
			return;
		}
		int i,j,k,col=0;
		double sf,sg,maxRankCorr,rankCorr;
		ratings.removeAllElements();
		// create target data matrix and get target times
		Matrix outData = Matlib.createMatrix();
		TimeFunctions.createDataMatrix(outVars, outData);
		// get target times
		int nout = outVars.size();
		int ntimes = outData.getRows();
		// if matrix is too big, reduce matrix by sampling random rows
		if(ntimes > LIMITSIZE) {
			Matrix B = Matlib.createMatrix();
			Stats.randomSplit(ntimes, LIMITSIZE, B);
			Matlib.getRows(outData,B,outData);
			outTimes = TimeFunctions.selectTimes(outTimes,B);
			ntimes = LIMITSIZE;
			B.clear();
		}
		// Create the input matrix. This is no bigger than LIMITSIZE rows.
		Matrix X = Matlib.createMatrix();
		TimeFunctions.createInputMatrix(inVars, inputDelays, outTimes, X);
		// GENSYMCID-1674: Re: Please advise how rating is calculated?
		// Filter out all NaNs
		TimeFunctions.cutBadRows(X, outData);
		ntimes = outData.getRows();
		if (ntimes == 0) {
			for (i = 0; i < inVars.size(); i++) {
				long[] delays = (long[])inputDelays.elementAt(i);
				double[] maxRanks = new double[delays.length];
				for (j = 0; j < maxRanks.length; j++)
					maxRanks[j] = 0.0;
				ratings.addElement(maxRanks);
			}
			return;
		}
		// Rank the output matrix, and store result in vector for quick access
		Vector outRanks = new Vector(0,nout);
		Matrix Sg = Matlib.createMatrix(1,nout);
		Matrix outCol = Matlib.createMatrix();
		for(i=0;i<nout;i++) {
			Matlib.getColumn(outData,i,outCol);
			Matrix outRank = Matlib.createMatrix();
			sg = crank(outCol,outRank);
			outRanks.addElement(outRank);
			Sg.set(0,i,sg);
		}
		outCol.clear();
		outData.clear();
		// Rank input matrix, one column at a time
		Matrix XCol = Matlib.createMatrix();
		Matrix XRank = Matlib.createMatrix();
		Matrix finiteColIndex = Matlib.createMatrix(1,1);
		finiteColIndex.set(0,0,1.0);
//	System.out.println("first finiteColIndex.get(0,0)= "+finiteColIndex.get(0,0));
		Variable[] nVars = null;
		for(i=0;i<inVars.size();i++) {
			long[] delays = (long[]) inputDelays.elementAt(i);
			double[] maxRanks = new double[delays.length]; // hold results for this input variable
			for(j=0;j<delays.length;j++) {
				Matlib.getColumn(X,col,XCol);
				// now check NaN for this column
				Matlib.findAllNaNColumns(XCol,finiteColIndex);
//	System.out.println("finiteColIndex.get(0,0)= "+finiteColIndex.get(0,0));
				if(Double.compare(finiteColIndex.get(0,0), 1.0) == 0){
					maxRankCorr = 0.0;
					maxRanks[j] = maxRankCorr;
				}else{
					// now rank this input
					sf = crank(XCol,XRank);
					// now calculate Spearman statistic w.r.t. each output, and take maximum
					maxRankCorr = 0.0;
					for(k=0;k<nout;k++) {
						rankCorr = rankStat(XRank,sf,(Matrix) outRanks.elementAt(k),Sg.get(0,k));
	//System.out.println("output "+k+", rank corr = "+rankCorr);
						maxRankCorr = Math.max(maxRankCorr,rankCorr);
					}
					maxRanks[j] = maxRankCorr;
	//System.out.println("rank corr = "+maxRankCorr);
					// report progress
				}
				informListeners();
				col++;
			}
			// put maxRanks in return vector
			ratings.addElement(maxRanks);
		}
		// Clean up
		X.clear();
		XCol.clear();
		XRank.clear();
		for(k=0;k<nout;k++) {
			((Matrix) outRanks.elementAt(k)).clear();
		}
		Sg.clear();
	}

	/** Perform input ranking, for row-based data */
	private void performRanking(Vector inVars,Vector outVars, Vector ratings) throws MathException {
		int i,j;
		double sf,sg,maxRankCorr,rankCorr;
		ratings.removeAllElements();
		// create target data matrix and get target times
		Matrix X = Matlib.createMatrix();
		Matrix Y = Matlib.createMatrix();
		TimeFunctions.createTrainingSet(inVars,outVars,X,Y);
		int nrows = X.getRows();
		int nx = X.getCols();
		int ny = Y.getCols();
		// if matrix is too big, reduce matrix by sampling random rows
		if(nrows > LIMITSIZE) {
			Matrix B = Matlib.createMatrix();
			Stats.randomSplit(nrows, LIMITSIZE, B);
			Matlib.getRows(X,B,X);
			Matlib.getRows(Y,B,Y);
			nrows = LIMITSIZE;
			B.clear();
		}
		// Rank Y, and store result in vector for quick access
		Vector YRanks = new Vector(0,ny);
		Matrix Sg = Matlib.createMatrix(1,ny);
		Matrix YCol = Matlib.createMatrix();
		for(j=0;j<ny;j++) {
			Matlib.getColumn(Y,j,YCol);
			Matrix YRank = Matlib.createMatrix();
			sg = crank(YCol,YRank);
			YRanks.addElement(YRank);
			Sg.set(0,j,sg);
		}
		// at this point, we only need to store Y ranks
		YCol.clear();
		Y.clear();
		// Rank input matrix, one column at a time
		Matrix XCol = Matlib.createMatrix();
		Matrix XRank = Matlib.createMatrix();
		Matrix finiteColIndex = Matlib.createMatrix(1,1);
		finiteColIndex.set(0,0,1.0);
//	System.out.println("first finiteColIndex.get(0,0)= "+finiteColIndex.get(0,0));
		for(i=0;i<nx;i++) {
			double[] maxRanks = new double[1];  // no delays, always length 1
			Matlib.getColumn(X,i,XCol);
			Matlib.findAllNaNColumns(XCol,finiteColIndex);
//System.out.println("finiteColIndex.get(0,0)= "+finiteColIndex.get(0,0));
			if(Double.compare(finiteColIndex.get(0,0), 1.0) == 0){
				maxRankCorr = 0.0;
				maxRanks[0] = maxRankCorr;
			}else{
					// now rank this input
				sf = crank(XCol,XRank);
					// now calculate Spearman statistic w.r.t. each output, and take maximum
				maxRankCorr = 0.0;
				for(j=0;j<ny;j++) {
					rankCorr = rankStat(XRank,sf,(Matrix) YRanks.elementAt(j),Sg.get(0,j));
	//System.out.println("output "+j+", rank corr = "+rankCorr);
					maxRankCorr = Math.max(maxRankCorr,rankCorr);
				}
	//System.out.println("rank corr = "+maxRankCorr);
				maxRanks[0] = maxRankCorr;
			}
			ratings.addElement(maxRanks);
				// report progress
			informListeners();
		}
		// Clean up
		X.clear();
		XCol.clear();
		XRank.clear();
		for(j=0;j<ny;j++) {
			((Matrix) YRanks.elementAt(j)).clear();
		}
		Sg.clear();
	}

	/** Spearman rank correlation between two ranked vectors, Xrank and Yrank */
	private double rankStat(Matrix Xrank, double sf, Matrix Yrank, double sg) throws MathException {
		int n = Xrank.getRows(), row;
		double en = (double) n, en3n = en*en*en - en, aved, fac, vard, d = 0.0, t, df, zd, probd, rs, probrs;
		Matrix Drank = Matlib.createMatrix();  // difference in rank
		Matlib.subtract(Xrank, Yrank, Drank);
		d = Matlib.dotProduct(Drank,Drank);
		aved = en3n/6.0 - (sf + sg)/12.0;
		fac = (1.0 - sf/en3n)*(1.0 - sg/en3n);
		vard = ((en - 1.0)*en*en*(en + 1.0)*(en + 1.0)/36.0)*fac;
		zd = Math.abs((d - aved)/Math.sqrt(vard));  // Abs because negative and positive correlations are treated the same
		//probd = Utilities.erfcc(zd/1.4142136);
		//rs = (1.0 - (6.0/en3n)*(d + (sf + sg)/12.0))/Math.sqrt(fac);
//System.out.println("RankStat: d = "+d+" zd = "+zd+" rs = "+rs+" probd = "+probd);
		/* fac = (rs + 1.0)*(1.0 - rs);
		if (fac > 0.0) { 
			t = rs*Math.sqrt((en - 2.0)/fac);
			df = en - 2.0;
			double a = 0.5*df;
			double b = 0.5;
			double x = df/(df + t*t);
			probrs = betaincomplete(a, b, x);
		}	  
		else probrs = 0.0;*/
		Drank.clear();
		return zd;
	}

 	/** Ranks a column vector x, using mean rank for ties. This differs from 
	* num.recipes crank by integrating the sorting step
	* Returns XR which is the rank of the elements of X, including midranking 
	* of ties, and s = f^3-f, where f is the number of elements in each tie */
	private static double crank(Matrix X, Matrix XR) throws MathException {
		int n = X.getRows(), j = 1, jt, ji;
		double s = 0.0, rank, t;
		Matrix permut = Matlib.createMatrix();
		Matrix XSorted = Matlib.createMatrix();
		Matlib.sort(X, XSorted, permut);
		XR.redimension(n,1);
		XR.initialize(Matrix.ZEROS);
		while (j<n) {
			if (Double.compare(XSorted.get1(j + 1,1), XSorted.get1(j,1)) != 0) { //Not a tie
				XR.set1(j,1,(double) j);
				++j;
			} else {  //A tie
				jt = j + 1;
				while (jt < n && Double.compare(XSorted.get1(jt,1), XSorted.get1(j,1)) == 0) {
					++jt;
				}
				
				rank = 0.5*(j + jt - 1);
				ji = j;
				while (ji <= jt - 1) {
					XR.set1(ji,1,rank);
					ji = ji + 1;
				}
				t = ((double)jt) - j;
				s = s + t*t*t - t;
				j = jt;
			}
		}
		if (j == n){
			XR.set1(n,1,(double) n);
		}
		Matlib.permuteRows(XR, permut, XR);	
		XSorted.clear();
		permut.clear();
		return s;
	}

	/** inform listeners that an event has happened.*/
	private void informListeners() {
		ProgressEvent e;
		ProgressListener l;
		e = new ProgressEvent();
		for (int i=0; i<itsListeners.size(); ++i) {
			l = (ProgressListener) itsListeners.elementAt(i);
			l.valueChanged(e);
		}
	}

	/** remove listener.*/
	public void removeListener(ProgressListener l) {
		itsListeners.removeElement(l);
	}
}

