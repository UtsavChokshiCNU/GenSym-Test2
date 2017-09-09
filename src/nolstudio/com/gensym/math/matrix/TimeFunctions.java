package com.gensym.math.matrix;  // TBD -- Change to com.gensym.nols.data???

import java.util.*;
import com.gensym.math.*;
// TBD -- Revise packaging to make the following imports unnecessary?
import com.gensym.nols.data.Variable;
import com.gensym.nols.data.DataSeries;

/** These functions are involve matrices and time stamp arrays.  
Used by the formula (transform) facility.  Also functions for preparing
training sets.  */

public final class TimeFunctions {

	/** interpolate array X with timestamps T0 onto new time array T */
	public static double[] interpolateArray(double[] X, long[] T0, long[] T) throws MathException {
		int T0length = T0.length;
		if(T0length != X.length) {
			throw new MathException("interpolateArray: dimension mismatch");
		}
		int k=0;  // index into T0
		int lastk;
		int rows = T.length;
		double[] Y = new double[rows];
		for(int i=0;i<rows;i++) {  // loop over output matrix rows
			long t = T[i];  // target time
			// find index into T0, at or just beyond the target time
			while(k<T0length && T0[k]<t) {
				k++;
			}
			lastk = k - 1;  // store previous index
			// seek next valid value
			while(k<T0length && Double.isNaN(X[k])) {
				k++;
			} 
//System.out.println("valid value in row "+i+" k = "+k+" t = "+t+" T0k = "+T0[k]);
			if (k==0 || t==T0[k]) 
				Y[i] = X[k];
			else if (k==T0length) 
				Y[i] = X[T0length-1];
			else {
				// seek previous valid point for interpolation
				while(lastk>=0 && Double.isNaN(X[lastk])) {
					--lastk;
				}
				if (lastk<0) {
					Y[i] = X[k];  // no left side point for interpolation
				} else {
					Y[i] = interpolateLinear(T0[lastk],t,T0[k],X[lastk],X[k]);
				}
			}
		}
		return Y;
	}

	/** Fill in column c of matrix M using times T, given input matrix M0,
	time stamps T0, and source column c0. NaN entries in M0 are ignored. 
	The resulting matrix is finite (no NaNs). */
	public static void interpolateColumn(Matrix M0, long[] T0, int c0, Matrix M, long[] T, int c) throws MathException {
		int rows = T.length;
		int T0length = T0.length;
		if(T0length != M0.getRows()) {
			throw new MathException("interpolateColumn: input dimension mismatch");
		}
		if(T.length != M.getRows()) {
			throw new MathException("interpolateColumn: output dimension mismatch");
		}
		int k=0;  // index into T0
		int lastk;
		for(int i=0;i<rows;i++) {  // loop over output matrix rows
			long t = T[i];  // target time
			// find index into T0, at or just beyond the target time
			while(k<T0length && T0[k]<t) {
				k++;
			}
			lastk = k - 1;  // store previous index
			// seek next valid value
			while(k<T0length && Double.isNaN(M0.get(k,c0))) {
				k++;
			} 
//System.out.println("valid value in row "+i+" k = "+k+" t = "+t+" T0k = "+T0[k]);
			if (k==0 || t==T0[k]) 
				M.set(i,c,M0.get(k,c0));
			else if (k==T0length) 
				M.set(i,c,M0.get(T0length-1,c0));
			else {
				// seek previous valid point for interpolation
				while(lastk>=0 && Double.isNaN(M0.get(lastk,c0))) {
					--lastk;
				}
				if (lastk<0){
					M.set(i,c,M0.get(k,c0));  // no left side point for interpolation
				}else {
					M.set(i,c,interpolateLinear(T0[lastk],t,T0[k],M0.get(lastk,c0),M0.get(k,c0)));
				}
			}
		}
	}

	// interpolate by time
	public static final double interpolateLinear(long low,long mid,long hi,double lowval,double hival) {
//System.out.println("Interpolating "+low+" "+mid+" "+hi+" "+lowval+" "+hival);
		if (hi==low) {
			return 0.5*(hival + lowval);  // degenerate timestamp case
		} else {
			return (mid - low)*(hival - lowval)/(hi - low) + lowval;
		}
	}

	/** Creates training set for time-based data. Rows containing NaNs are removed.  
	Times are taken from the output data series. */
	public static final long[] createTrainingSet(Vector inVars, Vector inputDelays, Vector outVars, Matrix X, Matrix Y, boolean clearBadData) throws MathException {
		createDataMatrix(outVars,Y);
		long[] outTimes = getOutputTimes(outVars);
		createInputMatrix(inVars,inputDelays,outTimes,X);
		if (!clearBadData)
			return outTimes;
		Matrix B = Matlib.createMatrix();
		//System.out.println("x size c="+X.getCols()+"r="+X.getRows()+"Y size c="+Y.getCols()+"r="+Y.getRows());
		cutBadRows(X,Y,B); // B is incidence matrix for bad rows
		outTimes = selectTimes(outTimes, B);
		return outTimes;
	}
	
	public static final long[] createTrainingSet(Vector inVars, Vector inputDelays, Vector outVars, Matrix X, Matrix Y) throws MathException {
		return createTrainingSet(inVars, inputDelays, outVars, X, Y, true);
	}

	/** Creates a training set for row-based data.  Bad rows are removed.
	Data must be from a single data series (assumed, not verified) */
	public static final void createTrainingSet(Vector inVars, Vector outVars, Matrix X, Matrix Y) throws MathException {
		createDataMatrix(outVars,Y);
		createDataMatrix(inVars,X);
//Matlib.disp(Y,"cutBadRows Y = ");
		cutBadRows(X,Y);
//Matlib.disp(Y,"Y = ");
//Matlib.disp(X, "X = ");
	}

	/** Get times associated with output variables */
	public static final long[] getOutputTimes(Vector outVars) {
		DataSeries ds = ((Variable) outVars.elementAt(0)).getDataSeries();
		if(ds.getHasTimeStamps()){
			return ds.getTimeStamps();
		}else {
			return null;
		}
	}

	/** Create a matrix whose columns correspond to the Variable objects
	contained in vars.  All elements of vars must be from the same data series. 
	This can be used for either X or Y matrices, for row-based data. */
	public static final void createDataMatrix(Vector vars, Matrix X) throws MathException {
		DataSeries dataSeries = ((Variable) vars.elementAt(0)).getDataSeries();
		int n = vars.size();
		Matrix fullData = dataSeries.getDataMatrix();  // includes all rows and cols
//System.out.println("createDataMatrix n= "+n);
//System.out.println("createDataMatrix fullData.getCols()= "+fullData.getCols());
		Matrix B = Matlib.zeros(1,fullData.getCols());  // incidence matrix to select relevant columns
//System.out.println("createDataMatrix B.getCols()= "+X.getCols());
		for(int i=0;i<n;i++) { 
			B.set(0,((Variable) vars.elementAt(i)).getColumnIndex(),1.0);
//System.out.println("\tB.get(r, c)= "+ B.get(0, ((Variable) vars.elementAt(i)).getColumnIndex()));
		}
		Matlib.getColumns(fullData,B,X);
//System.out.println("createDataMatrix X.getCols()= "+X.getCols());
		B.clear();
	}

	/** Creates X matrix for input to NN model to generate predictions at a given
	grid of output times, for time-based data. */
	public static final void createInputMatrix(Vector inVars, Vector inputDelays, long[] outTimes, Matrix X) throws MathException {
		int i,j,k;
		X.redimension(0,0);
		// Build the X matrix, column by column, looping through each delay of each input variable
		int ntimes = outTimes.length;
		long[] delayedTimes = new long[ntimes];
		Matrix delayedInputs = Matlib.createMatrix(ntimes,1);  // for input data interpolated at delayed times
		Matrix inData = Matlib.createMatrix();
		for(i=0;i<inVars.size();i++) {
			Variable inVar = (Variable) inVars.elementAt(i);
			DataSeries inDataSeries = inVar.getDataSeries();
			long[] inTimes = inDataSeries.getTimeStamps();
			inDataSeries.getVarMatrix(inVar,inData);   // one column of data
			long[] delays = (long[]) inputDelays.elementAt(i);
			for(j=0;j<delays.length;j++) {
				long delay = delays[j];
				if(delay>0l) {
					// prepare array of delayed times
					for(k=0;k<ntimes;k++) {
						delayedTimes[k] = outTimes[k] - delay;
					}
					// interpolate the inputs onto the delayedTimes
					TimeFunctions.interpolateColumn(inData,inTimes,0,delayedInputs,delayedTimes,0);
				} else {
					// no delay
					// note: if input and output are from the same data series, we could in theory
					// avoid interpolation; however, interpolation may eliminate NaNs
					TimeFunctions.interpolateColumn(inData,inTimes,0,delayedInputs,outTimes,0);
				}
				// append to X
				Matlib.appendColumns(X,delayedInputs,X);
			}
		}
		delayedInputs.clear();
		inData.clear();
	}

	/** Cut any bad training samples from a training set. */
	public static final void cutBadRows(Matrix X, Matrix Y) throws MathException {
		Matrix goodRows = Matlib.createMatrix();
		cutBadRows(X,Y,goodRows);
		goodRows.clear();
	}

	/** Cut any bad training samples from a training set, and returns a incidence matrix
	showing location of good rows (1 = good, 0 = bad). */
	public static final void cutBadRows(Matrix X, Matrix Y, Matrix goodRows) throws MathException {
		Matrix goodX = Matlib.createMatrix();
		Matrix goodY = Matlib.createMatrix();
		Matlib.findFiniteRows(X,goodX);
		Matlib.findFiniteRows(Y,goodY);
//Matlib.disp(goodX, "good X = ");
//Matlib.disp(goodY, "good Y = ");
		Matlib.and(goodX,goodY,goodRows);
//sMatlib.disp(goodRows, "good Rows = ");
		goodX.clear();
		goodY.clear();
		Matlib.getRows(X,goodRows,X);
		Matlib.getRows(Y,goodRows,Y);
	}

	/** Create a new timestamp array including elements selected by vector S,
	whose elements are 0 or 1 */
	public static final long[] selectTimes(long[] T0, Matrix S) {
		int ngood = 0;
		for(int i=0;i<S.getElements();i++) {
			if(Double.compare(S.get(i), 0.0) != 0){
				ngood++;
			}
		}
		long[] T = new long[ngood];
		int j =0;
		for(int i=0;i<S.getElements();i++) {
			if(Double.compare(S.get(i), 0.0) != 0) {
				T[j] = T0[i];
				j++;
			}
		}
		return T;
	}

}




/*  NOT USED

	// interpolate by row
	private static final double interpolateLinear(int low,int mid,int hi,double lowval,double hival) {
		// don't check for hi==low, since row numbers will never repeat
		return (mid - low)*(hival - lowval)/(hi - low) + lowval;
	}

  	// Method flags
	static int INTERPOLATE = 0;
	static int CLIP = 1;
  private static int indexFromTime(long t, long[] T){
		//  Given ordered array T, find index corresponding to t
		//  If t is between array elements, return the previous element
		int len = T.length;
		if (len==0 || t < T[0]) return -1;
		else if (t >= T[len-1]) return len - 1;
		int lowerBound = 0;
		int upperBound = len - 1;
		int midPt;
		while (upperBound - lowerBound - 1 > 0) {
			midPt = (upperBound + lowerBound)>>2;
			if (t >= T[midPt]) lowerBound = midPt;
			else upperBound = midPt;
		}
		return lowerBound;
	}


	/** Replace NaNs in a matrix whose rows are equally spaced in time.
	See replaceMissings(Matrix, long[]) for more details.   
	public static void replaceMissingValues(Matrix M) throws MathException {
		long[] T = null;
		replaceMissingValues(M,T); 
	}

	/** Replace NaNs in a matrix indexed by ascending times T.
	Constant (zero order) extrapolation is used to fill the gaps at the beginning 
	and end of the matrix columns.  Interior gaps are filled using linear 
	interpolation.  If an entire column is missing values, a MathException is
	thrown.  
	private static void replaceMissingValues(Matrix M, long[] T) throws MathException {
		int rows = M.getRows();
		int cols = M.getCols();	
		if(rows==0 || cols==0) return;
		int[] indices = new int[2];
		double[] vals = new double[2];
		for (int j=0;j<cols;j++) {
			int i=0;
			while(true) {
				findGap(M,j,i,indices,vals);
				fillGap(M,T,j,indices,vals);
				if(indices[1]<0) break;  // no more gaps
				i = indices[1];
			}
		}	
	}
	private static void findGap(Matrix M, int col, int startIndex, int[] indices, double[] vals) {
		// returns the indices and values surrounding segments of NaNs in the given column
		// no gap is indicated by returning -2,-2 as the indices
		// gaps at the beginning or the end are indicated by returning -1 as element 0 or 1, respectively
		int rows = M.rows;
		indices[0] = -2;
		indices[1] = -2;
		boolean foundStart=false;
		// find the beginning of the next gap, starting search at startIndex
		for(int i=startIndex;i<rows;i++) {
			if(Double.isNaN(M.get(i,col))) {
				indices[0] = i-1;
				if(i>0) vals[0] = M.get(i-1,col);
				foundStart = true;
				break;
			}
		}
		if(!foundStart) return;
		for(int i=indices[0]+1;i<rows;i++) {
			if(!Double.isNaN(M.get(i,col))) { // found end of gap
				indices[1] = i;
				vals[1] = M.get(i,col);
				return;
			}
		}
		indices[1] = -1;  // gap goes to the end
	}

	private static void findLowValues(Matrix M, int col, int startIndex, int[] indices, double[] vals, double threshold) {
		// returns the indices and values surrounding segments of NaNs in the given column
		int rows = M.rows;
		indices[0] = -2;
		indices[1] = -2;
		boolean foundStart=false;
		// find the beginning of the next gap, starting search at startIndex
		for(int i=startIndex;i<rows;i++) {
			if(M.get(i,col)<threshold) {
				indices[0] = i-1;
				if(i>0) vals[0] = M.get(i-1,col);
				foundStart = true;
				break;
			}
		}
		if(!foundStart) return;
		for(int i=indices[0]+1;i<rows;i++) {
			if(!(M.get(i,col)<threshold)) {  // test is INTENTIONALLY written this way to deal with NaNs
				indices[1] = i;
				vals[1] = M.get(i,col);
				return;
			}
		}
		indices[1] = -1;  // gap goes to the end
	}


	private static void findHighValues(Matrix M, int col, int startIndex, int[] indices, double[] vals, double threshold) {
		// returns the indices and values surrounding segments of NaNs in the given column
		int rows = M.rows;
		indices[0] = -2;
		indices[1] = -2;
		boolean foundStart=false;
		// find the beginning of the next gap, starting search at startIndex
		for(int i=startIndex;i<rows;i++) {
			if(M.get(i,col)>threshold) {
				indices[0] = i-1;
				if(i>0) vals[0] = M.get(i-1,col);
				foundStart = true;
				break;
			}
		}
		if(!foundStart) return;
		for(int i=indices[0]+1;i<rows;i++) {
			if(!(M.get(i,col)>threshold)) {  // test is INTENTIONALLY written this way to deal with NaNs
				indices[1] = i;
				vals[1] = M.get(i,col);
				return;
			}
		}
		indices[1] = -1;  // gap goes to the end
	}


 	/** Replace values below a given threshold value, substituting with the threshold
	value (CLIP), or by interpolating surrounding in-bounds values (INTERPOLATE).
	If T is null, interpolation will use rows instead of times.  NaNs are left alone 
	by this procedure. 
	public static void replaceLowValues(Matrix M, long[] T, double threshold, int method) throws MathException {
		int rows = M.getRows();
		int cols = M.getCols();	
		if(rows==0 || cols==0) return;
		if(method==CLIP) {
			Matlib.maxSelect(M,threshold,M);  // max select to eliminate low outliers
			return;
		} else if (method==INTERPOLATE) {  // hold previous good value
			int[] indices = new int[2];
			double[] vals = new double[2];
			for (int j=0;j<cols;j++) {
				int i=0;
				while(true) {
					findLowValues(M,j,i,indices,vals,threshold);
					fillGap(M,T,j,indices,vals);
					if(indices[1]<0) break;  // no more low values in this column
					i = indices[1];
				}
			}
		}
	}

 	/** Replace values above a given threshold value, substituting with the threshold
	value (CLIP), or by interpolating surrounding in-bounds values (INTERPOLATE).
	If T is null, interpolation will use rows instead of times.  NaNs are left alone 
	by this procedure. 
	public static void replaceHighValues(Matrix M, long[] T, double threshold, int method) throws MathException {
		int rows = M.getRows();
		int cols = M.getCols();	
		if(rows==0 || cols==0) return;
		if(method==CLIP) {
			Matlib.minSelect(M,threshold,M);  // max select to eliminate low outliers
			return;
		} else if (method==INTERPOLATE) {  // hold previous good value
			int[] indices = new int[2];
			double[] vals = new double[2];
			for (int j=0;j<cols;j++) {
				int i=0;
				while(true) {
					findHighValues(M,j,i,indices,vals,threshold);
					fillGap(M,T,j,indices,vals);
					if(indices[1]<0) break;  // no more high values in this column
					i = indices[1];
				}
			}
		}
	}

	/** Form a large matrix by first putting all matrices in M0 onto the same time
	grid T, then appending matrices side-by-side. Currently, the method flag is not
	used. 
/*	public static void timeMerge(Vector matrices, Vector timeStamps, int method, Matrix M, long[] T) throws MathException {
		Matrix M0;
		long[] T0;
		M.redimension(0,0);
		Matrix MM = Matlib.createMatrix();
		if(matrices.size()!=timeStamps.size()) throw new MathException("time merge: count of matrices and time stamps did not match");
		for(int i=0;i<matrices.size();i++) {
			M0 = (Matrix) matrices.elementAt(i);
			T0 = (long[]) timeStamps.elementAt(i);
			replaceTimeGrid(M0,T0,method,MM,T);
			Matlib.appendColumns(M,MM,M);
		}
	}

	// PRIVATE FUNCTIONS
	
	/** Fill in matrix M by putting matrix M0 with time stamps T0 onto time grid T. 
	Currently, the method flag is not used. 
	public static void replaceTimeGrid(Matrix M0, long[] T0, int method, Matrix M, long[] T) throws MathException {
		int rows = T.length;
		int cols = M0.getCols();
		int T0length = T0.length;
		if(T0length != M0.getRows()) throw new MathException("time merge: mismatch of timestamp dimension and data dimension");
		if(rows==0 || cols==0) return;  // throw an error instead?
		M.redimension(rows,cols);
		int k=0;  // index into T0
		for(int i=0;i<rows;i++) {
			long t = T[i];
			// look for index into T0 where the time is greater than or equal to the target time t 
			while(k<T0length && T0[k]<t) {k++;}
//System.out.println("row "+i+" k = "+k+" t = "+t+" T0k = "+T0[k]);
			for(int j=0;j<cols;j++) {
				if (k==0) M.set(i,j,M0.get(0,j));
				else if (k==T0length) M.set(i,j,M0.get(T0length-1,j));
				else M.set(i,j,interpolateLinear(T0[k-1],t,T0[k],M0.get(k-1,j),M0.get(k,j)));
			}
		}
	}

	private static void fillGap(Matrix M, long[] T, int col, int[] indices, double[] vals) throws MathException {
		// indices gives begin and end point of a gap in the given column of M
		// if indices[0]==-1, the column starts with a gap
		// if indices[1]==-1, the column ends with a gap
		// if both indices are -1, the entire column is a gap, thus no way to fill it (this is an error)
		// constant extrapolation is used for these special cases
		// otherwise, linear interpolation is used
		if(indices[0]==-2 && indices[1]==-2) return;  // no gaps to fill
		if(indices[0]==-1 && indices[1]==-1) throw new MathException("Column has no valid values, cannot fill gaps");
		double d;
		if(indices[0]<0) {  // initial gap
			d = vals[1];
			for(int i=0;i<indices[1];i++) M.set(i,col,d);
		} else if (indices[1]<0) { // final gap
			d = vals[0];
			for(int i=indices[0]+1;i<M.getRows();i++) M.set(i,col,d);
		} else {  // interior gap 
			// If either val is NaN or Inf, we can't interpolate properly, so just fill in values
			// (This can happen when replacing high or low values, but never when replacing NaNs)
			boolean nan0 = Double.isNaN(vals[0]) || Double.isInfinite(vals[0]); 
			boolean nan1 = Double.isNaN(vals[1]) || Double.isInfinite(vals[0]);
			if(nan0 && nan1) {
				for(int i=indices[0]+1;i<indices[1];i++) M.set(i,col,Double.NaN);
			} else if(nan0) {
				d = vals[1];
				for(int i=indices[0]+1;i<indices[1];i++) M.set(i,col,d);
			} else if(nan1) {
				d = vals[0];
				for(int i=indices[0]+1;i<indices[1];i++) M.set(i,col,d);
			} else {  // have good values to interpolate
				if(T==null) {
					for(int i=indices[0]+1;i<indices[1];i++)
						M.set(i,col,interpolateLinear(indices[0],i,indices[1],vals[0],vals[1]));
				} else {
					for(int i=indices[0]+1;i<indices[1];i++) 
						M.set(i,col,interpolateLinear(T[indices[0]],T[i],T[indices[1]],vals[0],vals[1]));
				}
			}
		}
	}

  	/** Fill in matrix M at times T, using data from input matrix M0 with time stamps T0. 
	public static void replaceTimeGrid(Matrix M0, long[] T0, Matrix M, long[] T) throws MathException {
		int rows = T.length;
		int cols = M0.getCols();
		int T0length = T0.length;
		if(T0length != M0.getRows()) throw new MathException("dimension mismatch");
		if(rows==0 || cols==0) return;  // throw an error instead?
		M.redimension(rows,cols);
		int k=0;  // index into T0
		for(int i=0;i<rows;i++) {
			long t = T[i];
			// look for index into T0 where the time is greater than or equal to the target time t 
			while(k<T0length && T0[k]<t) {k++;}
//System.out.println("row "+i+" k = "+k+" t = "+t+" T0k = "+T0[k]);
			for(int j=0;j<cols;j++) {
				if (k==0) M.set(i,j,M0.get(0,j));
				else if (k==T0length) M.set(i,j,M0.get(T0length-1,j));
				else M.set(i,j,interpolateLinear(T0[k-1],t,T0[k],M0.get(k-1,j),M0.get(k,j)));
			}
		}
	}

 */