package com.gensym.math.stats;

import java.security.SecureRandom;
import com.gensym.math.*;
import com.gensym.math.matrix.*;
import com.gensym.math.datafit.*;

public final class Stats {
	private static final SecureRandom randomGenerator = new SecureRandom();
	
	static{
		randomGenerator.setSeed(System.currentTimeMillis());
	}

	/** Random sampling of data. Boolean (0-1) matrix B (ndata by 1) is returned 
	with n random non-zero elements. */
	public static void randomSplit(int ndata, int n, Matrix B) {
		Sampler sam = new Sampler(ndata);
		B.redimension(ndata,1);
		B.initialize(Matrix.ZEROS);
		for(int i=0;i<n;i++) {
			B.set(sam.nextSample(),0,1.0);
		}
	}

	public static void randomSplit(Matrix X, Matrix Y, int ntrain, Matrix XTrain, Matrix YTrain, Matrix XTest, Matrix YTest) throws MathException {
		Matrix B = Matlib.createMatrix();
		randomSplit(X,Y,ntrain,XTrain,YTrain,XTest,YTest,B);
		Matlib.clear(B);
	}

	// Returns B, the incidence matrix of test data
	public static void randomSplit(Matrix X, Matrix Y, int ntrain, Matrix XTrain, Matrix YTrain, Matrix XTest, Matrix YTest, Matrix B) throws MathException {
		Stats.randomSplit(X.getRows(),ntrain,B);
		Matlib.getRows(X,B,XTrain);
		Matlib.getRows(Y,B,YTrain);
		Matlib.not(B,B);
		Matlib.getRows(X,B,XTest);
		Matlib.getRows(Y,B,YTest);
	}


	public static void blockSplit(Matrix X, Matrix Y, int ntrain, int blockLength, Matrix XTrain, Matrix YTrain, Matrix XTest, Matrix YTest, Matrix B) throws MathException {
		int ndata = X.getRows();
		int ntest = ndata - ntrain;
		blockSplit(ndata, blockLength, ntrain,B);  // set up B initially to pick out training samples
		Matlib.getRows(X,B,XTrain);
		Matlib.getRows(Y,B,YTrain);
		Matlib.not(B,B);
		Matlib.getRows(X,B,XTest);
		Matlib.getRows(Y,B,YTest);
	}

	/** Block random sampling of data.  Boolean (0-1) matrix is returned
	so that sum(B)/ndata = n (approximately).  In addition, samples
	are selected in blocks of approximate length blockLength, which 
	is the best way to sample time series data to avoid correlation between 
	training and testing data. For best results, make sure n > blockLength
	and blockLength << ndata */
	public static void blockSplit(final int ndata, final int blockLength, final int n, Matrix B) throws MathException {
		int blockSize = blockLength;
		B.redimension(ndata, 1);
		B.initialize(Matrix.ZEROS);
		int selectBlocks = n/blockSize;
		int leftoverSamples = n - blockSize*selectBlocks;
		if (leftoverSamples>0) {
			selectBlocks++;  // include one short block to make sure we use exactly the required number of test samples
		}
		int totalBlocks = ndata/blockSize;
		if(totalBlocks<=selectBlocks) { // no training data -- this is bad, so reduce block length
			blockSize = blockSize/2;
			blockSplit(ndata, blockSize, n, B);
			return;
		}
		Sampler sam = new Sampler(totalBlocks);
		Matrix BB = Matlib.createMatrix();
		BB.redimension(totalBlocks,1);
		BB.initialize(Matrix.ZEROS);
		int block,i,firstRow,lastRow,row;
		for(i=0;i<selectBlocks;i++) {
			block = sam.nextSample();
			BB.set(block,0,1.0);
		}
		for(i=0;i<totalBlocks;i++) {
			if(Double.compare(BB.get(i,0), 1.0) == 0) {
				firstRow = i*blockSize;
				if (leftoverSamples>0) { 
					lastRow = firstRow + leftoverSamples - 1;
					leftoverSamples = 0;
				} else { 
					lastRow = firstRow + blockSize - 1;
				}
				
				for(row=firstRow;row<=lastRow;row++) 
					B.set(row,0,1.0);
			}
		}
		BB.clear();
	}

	/** Returns a boolean (0-1) matrix, ndata by ntrial, indicating which samples 
	should be used for TESTING in each of ntrial cross validation iterations, so
	each sample is used exactly once for testing.  The samples are randomly selected. */
	public static void cvRandomDesign(int ndata, int ntrials, Matrix B) throws MathException {
		int i,j,row,samplesPerTrial,leftoverSamples,samplesNow;
		Sampler sam = new Sampler(ndata);
		// First determine the division of blocks into trials
		B.redimension(ndata,ntrials);
		B.initialize(Matrix.ZEROS);
		samplesPerTrial = ndata/ntrials;
		leftoverSamples = ndata - samplesPerTrial*ntrials;
		for(j=0;j<ntrials;j++) {
			if(leftoverSamples > 0) {
				samplesNow = samplesPerTrial+1;
				leftoverSamples--;
			} else samplesNow = samplesPerTrial;
			for(i=0;i<samplesNow;i++) {
				row = sam.nextSample();
				B.set(row,j,1.0);
			}
		}
	}

	/** Returns a boolean (0-1) matrix, ndata by ntrial, indicating which samples 
	should be used for TESTING in each of ntrial cross validation iterations.
	The nblocks argument is used in pre-dividing the data into contiguous blocks,
	which is the best way to divide time series data to avoid correlation between
	training and test sets.  For even division of samples, nblocks should be an
	integral multiple of ntrials, and nblock should be big enough to capture closely 
	time-correlated samples */
	public static void cvBlockDesign(int ndata, int nblocks, int ntrials, Matrix B) throws MathException {
		int i,j,block,blocksPerTrial,leftoverBlocks,blocksNow;
		Sampler sam = new Sampler(nblocks);
		// First determine the division of blocks into trials
		Matrix BB = Matlib.createMatrix();
		BB.redimension(nblocks,ntrials);
		BB.initialize(Matrix.ZEROS);
		blocksPerTrial = nblocks/ntrials;
		leftoverBlocks = nblocks - blocksPerTrial*ntrials;
		for(j=0;j<ntrials;j++) {
			if(leftoverBlocks > 0) {
				blocksNow = blocksPerTrial+1;
				leftoverBlocks--;
			} else blocksNow = blocksPerTrial;
			for(i=0;i<blocksNow;i++) {
				block = sam.nextSample();
				BB.set(block,j,1.0);
			}
		}
		// now assign the samples to each trial
		int samplesPerBlock,leftoverSamples,row,firstRow,lastRow;
		samplesPerBlock = ndata/nblocks;
		leftoverSamples = ndata - nblocks*samplesPerBlock;
		B.redimension(ndata,ntrials);
		B.initialize(Matrix.ZEROS);
		for(i=0;i<nblocks;i++) {
			for(j=0;j<ntrials;j++) {
				if(Double.compare(BB.get(i,j), 1.0) == 0) {
					firstRow = i*samplesPerBlock + Math.min(i,leftoverSamples);
					lastRow = firstRow + samplesPerBlock - 1;
					if (i<leftoverSamples){ 
						lastRow++; // leading blocks contain 1 extra sample
					}
					for(row=firstRow;row<=lastRow;row++) {
						B.set(row,j,1.0);
					}
				}
			}
		}
		Matlib.clear(BB);
	}

	/** Calculates predictions based on cross validation.  CV block design is
	used if nblocks > ntrials, otherwise, random division into ntrials is 
	performed.  This routine takes about ntrials times the time of training.  
	The predictions are returned in YPred. */
	public static void cvPredict (TrainableModel L, Matrix X, Matrix Y, int nblocks, int ntrials, Matrix YPred) throws MathException {
		int i,j,k,trial,ndata = X.getRows(),nout=Y.getCols();
		Matrix XTrain = Matlib.createMatrix();
		Matrix YTrain = Matlib.createMatrix();
		Matrix XTest = Matlib.createMatrix();
		// matrix to hold results of cross validation
		YPred.redimension(ndata,nout);
		Matrix temp = Matlib.createMatrix();
		Matrix B = Matlib.createMatrix();
		Matrix BB = Matlib.createMatrix();
		if (nblocks > ntrials) {
			cvBlockDesign(ndata,nblocks,ntrials,B);
		}
		else cvRandomDesign(ndata,ntrials,B);
		for (trial=0;trial<ntrials;trial++) {
			Matlib.getColumn(B,trial,BB);
			Matlib.getRows(X,BB,XTest);
			Matlib.not(BB,BB);
			Matlib.getRows(X,BB,XTrain);
			Matlib.getRows(Y,BB,YTrain);
//System.out.println("Training with "+XTrain.getRows()+" samples, testing with "+XTest.getRows());
			L.learn(XTrain,YTrain);
			L.evaluate(XTest,temp);
			Matlib.not(BB,BB);
			// re-insert the results at the correct row
			k=0;
			for(i=0;i<BB.getRows();i++) {
				if (Double.compare(BB.get(i,0), 0.0) != 0) {
					for(j=0;j<nout;j++) 
						YPred.set(i,j,temp.get(k,j));
					k++;
				}
			}
		}
		Matlib.clear(XTrain);
		Matlib.clear(YTrain);
		Matlib.clear(XTest);
		Matlib.clear(temp);
		Matlib.clear(B);
		Matlib.clear(BB);
	}

	public static void pca(Matrix X, Matrix P) throws MathException {
		Matrix Var = Matlib.createMatrix();
		pca(X,P,Var);
		Matlib.clear(Var);
	}

	/** Calculates all principal components of X using SVD. Loadings 
	may be calculated as T = XP.  Variance explained is returned in row
	vector Var.  If you want X to be mean-centered or equal variance, you
	must condition X before calling this method. */
	public static void pca(Matrix X, Matrix P, Matrix Var) throws MathException {
		Matrix Cov = Matlib.createMatrix();
		Matrix U = Matlib.createMatrix();
		Matrix V = Matlib.createMatrix();
		Matrix W = Matlib.createMatrix();
		int ncols = X.getCols(), nrows = X.getRows();
		if (nrows > ncols) {
			Matlib.xTx(X, Cov);
			Matlib.divide(Cov, nrows-1.0d, Cov);
			Matlib.svd(Cov,U,W,V,false);   // added last argument MK 2/4/99
		} else {
			Matrix temp = Matlib.createMatrix();
			Matlib.transpose(X, Cov);  // can't use xTx, we must calculate xxT
			Matlib.multiply(X,Cov,Cov);
			Matlib.divide(Cov,nrows-1.0d,Cov);
			Matlib.svd(Cov,U,W,V,false);  // added last argument MK 2/4/99
			Matlib.transpose(X, temp);
			Matlib.multiply(temp, V, V);
			for(int i=0;i<V.getCols();i++) {
				Matlib.getColumn(V, i, temp);
				Matlib.divide(temp, Matlib.norm(temp), temp);
				Matlib.setPart(V,temp,0,i,V);
			}
			Matlib.clear(temp);
		}
		Matlib.diag(W,W);  // column vector of singular values
		Matlib.cumsum(W,W);
		double wtot = W.get(W.getRows()-1);
		Matlib.divide(W,wtot,Var);
		Matlib.transpose(Var, Var);
		Matlib.copy(V,P);
		Matlib.clear(Cov);
		Matlib.clear(U);
		Matlib.clear(W);
		Matlib.clear(V);
	}

	/** Calculates all principal components of X using SVD. Loadings 
	may be calculated as T = XP.  Variance explained is returned in row
	vector Var.  If you want X to be mean-centered or equal variance, you
	must condition X before calling this method. */
	public static void pca(Matrix X, Matrix P, Matrix Pclim, Matrix ssg, Matrix Var) throws MathException {
		Matrix Cov = Matlib.createMatrix();
		Matrix U = Matlib.createMatrix();
		Matrix V = Matlib.createMatrix();
		Matrix W = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		int ncols = X.getCols(), nrows = X.getRows();
		if (nrows > ncols) {
			Matlib.xTx(X, Cov);
			Matlib.divide(Cov, nrows-1.0d, Cov);
			Matlib.svd(Cov,U,W,V,false);   // added last argument MK 2/4/99
		} else {
			Matlib.transpose(X, Cov);  // can't use xTx, we must calculate xxT
			Matlib.multiply(X,Cov,Cov);
			Matlib.divide(Cov,nrows-1.0d,Cov);
			Matlib.svd(Cov,U,W,V,false);  // added last argument MK 2/4/99
			Matlib.transpose(X, temp);
			Matlib.multiply(temp, V, V);
			for(int i=0;i<V.getCols();i++) {
				Matlib.getColumn(V, i, temp);
				Matlib.divide(temp, Matlib.norm(temp), temp);
				Matlib.setPart(V,temp,0,i,V);
			}
		}
		Matlib.diag(W,W);  // column vector of singular values
		Matlib.copy(W,ssg);
		Matlib.cumsum(W,W);
		double wtot = W.get(W.getRows()-1);
		Matlib.divide(W,wtot,Var);
		Matlib.transpose(Var, Var);
		Matlib.copy(V,P);
		Pclim.redimension(1,Var.getCols());
		for(int i=0;i<Var.getCols();i++){ 
			double pl =Math.sqrt(ssg.get(i))*ttestp(0.025,((double)nrows)-i,2);
			Pclim.set(i,pl);
		}
/*		int npc = Var.getCols();
		for(int i=0;i<Var.getCols();i++) {
			if (Var.get(i) >= var) {
				npc = i+1;
				break;
			}
		}
		Matlib.getColumns(V,0,npc-1,V);
		Matlib.multiply(X,V,temp);
		Matlib.transpose(V,V);
		Matlib.multiply(temp,V,temp);
		Matlib.subtract(X,temp,temp);
		Matlib.transpose(temp,temp);
		Matlib.powerElements(temp, 2.0,temp);
		
		Matlib.sum(temp,Res);

*/		Matlib.clear(temp);
		Matlib.clear(Cov);
		Matlib.clear(U);
		Matlib.clear(W);
		Matlib.clear(V);
//		return npc;
	}


	/** PCA-Nipals algorithm for finding a fixed number of PCA factors.  
	Assumes matrix X is mean-centered. */
	// (MK 2/5/99: Turns out this is not as fast as SVD approach, but keep around anyway)
	public static void pcanipals(Matrix X, int npc, Matrix P) throws MathException {
		if (npc < 0 || npc > X.getCols()) 
			throw new MathException("pca: number of principal components must be between 0 and the number of columns of X");
		Matrix x = Matlib.createMatrix();
		Matrix t = Matlib.createMatrix();
		Matrix p = Matlib.createMatrix();
		Matrix tp = Matlib.createMatrix();
		Matrix terr = Matlib.createMatrix();
		Matrix xtp = Matlib.createMatrix();
		double tol = 1.e-9*X.getRows();
		Matlib.copy(X,x);  // x is the deflated X matrix
		int col = 0;  // column to choose initial t from x
		for(int i=1;i<=npc;i++) {
			int iter = 0;
			Matlib.getColumn(x,col,t);
			double scalar_err = 999.0;
			while(iter < 100 && scalar_err > tol) {
				iter++;
				Matlib.transpose(t,t);
				Matlib.multiply(t,x,p);  // p is row vector
				Matlib.transpose(t,t);  // restore to column vector
				double pnorm = Matlib.norm(p);
				Matlib.divide(p,pnorm,p);
				Matlib.transpose(p,p);  // change to column vector 
				Matlib.multiply(x,p,tp);
				Matlib.subtract(t,tp,terr);
				scalar_err = Matlib.norm(terr);
				if(Double.isNaN(scalar_err)) {
					// chose bad initial column, probably constant or all zeros
					col++;
					if(col>=x.getCols()) {
						throw new MathException("PCA failed: Matrix had no principal directions");
					}
					Matlib.getColumn(x,col,tp);
					scalar_err = tol + 1.0;  // to force continuation
				}
				Matlib.copy(tp,t);
			}
			//System.out.println("factor "+i+", iter = "+iter+", err = "+scalar_err);
			if(i==1) {
				Matlib.copy(p,P);
			}
			else Matlib.appendColumns(P,p,P);
			Matlib.transpose(p,p);
			Matlib.multiply(t,p,xtp);
			Matlib.subtract(x,xtp,x);
		}
		Matlib.clear(x);
		Matlib.clear(xtp);
		Matlib.clear(t);
		Matlib.clear(p);
		Matlib.clear(tp);
		Matlib.clear(terr);
	}


	/** Calculates first npc principal components of X using SVD. 
	There is no efficiency gain from using this routine compared to full PCA, 
	since internally, all PC's are calculated.*/
	public static void pca(Matrix X, int npc, Matrix P) throws MathException {
		if (npc < 0 || npc > X.getCols()) 
			throw new MathException("pca: number of principal components must be between 0 and the number of columns of X");
		pca(X,P);
		Matlib.getColumns(P,0,npc-1,P);
	}

	/** Calculates as many principal components as necessary to explain 
	the variance var, between 0.0 and 1.0 */
	public static void pca(Matrix X, double var, Matrix P) throws MathException {
		Matrix Var = Matlib.createMatrix();
		pca(X,P,Var);
		int npc = Var.getCols();
//Matlib.disp(Var);
		for(int i=0;i<Var.getCols();i++) {
			if (Var.get(i) >= var) {
				npc = i+1;
				break;
			}
		}
//System.out.println("npc = "+npc);
		Matlib.getColumns(P,0,npc-1,P);
		Matlib.clear(Var);
	}

	/** Principal component regression with npc factors.  P is the 
	the loadings matrix returned from pca.  The resulting coefficients 
	B are returned as a (nin, nout) matrix, so Y = XB in least-squares sense */
	public static void pcr(Matrix X, Matrix P, Matrix Y, Matrix B) throws MathException {
		Matrix T = Matlib.createMatrix();
		Matlib.multiply(X,P,T);
		Matlib.divide(T,Y,B);
		Matlib.multiply(P,B,B);
		Matlib.clear(T);
	}

	public static void plsPredict() {
		// not yet implemented 
	}

	/** Calculates nfactors using nipals recursively. This routine requires
	that X and Y are normalized to have zero-mean and unit standard deviation. */
	public static void pls(Matrix X, Matrix Y, Matrix P, Matrix Q, Matrix W, Matrix T, Matrix U, Matrix B, int nfactors) throws MathException {
		Matrix XF = Matlib.createMatrix();
		Matlib.copy(X,XF);
		Matrix YF = Matlib.createMatrix();
		Matlib.copy(Y,YF);
		P.redimension(0,0);
		Q.redimension(0,0);
		W.redimension(0,0);
		T.redimension(0,0);
		U.redimension(0,0);
		B.redimension(1,nfactors);
		Matrix p = Matlib.createMatrix();
		Matrix q = Matlib.createMatrix();
		Matrix w = Matlib.createMatrix();
		Matrix t = Matlib.createMatrix();
		Matrix u = Matlib.createMatrix();
		Matrix xf = Matlib.createMatrix();
		Matrix yf = Matlib.createMatrix();
		double bb;
		for(int i=0;i<nfactors;i++) {
			nipals(XF,YF,p,q,w,t,u);
			bb=Matlib.dotProduct(u,t)*Matlib.dotProduct(t,t);
			B.set(0,i,bb);
			if(i==0) {
				Matlib.copy(p,P);
				Matlib.copy(q,Q);
				Matlib.copy(w,W);
				Matlib.copy(t,T);
				Matlib.copy(u,U);
			} else {
				Matlib.appendColumns(P,p,P);
				Matlib.appendColumns(Q,q,Q);
				Matlib.appendColumns(W,w,W);
				Matlib.appendColumns(T,t,T);
				Matlib.appendColumns(U,u,U);
			}
			if(i<nfactors-1) {
				// prepare for next factor by determining residuals
				Matlib.transpose(p,p);
				Matlib.multiply(t,p,xf);
				Matlib.subtract(XF,xf,XF);
				Matlib.transpose(q,q);
				Matlib.multiply(t,q,yf);
				Matlib.multiply(yf,bb,yf);
				Matlib.subtract(YF,yf,YF);
			}
		}
		Matlib.clear(XF);
		Matlib.clear(YF);
		Matlib.clear(p);
		Matlib.clear(q);
		Matlib.clear(w);
		Matlib.clear(t);
		Matlib.clear(u);
		Matlib.clear(xf);
		Matlib.clear(yf);
	}

	/** Calculates one pls factor */
	public static void nipals(Matrix X, Matrix Y, Matrix P, Matrix Q, 
		Matrix W, Matrix T, Matrix U) throws MathException {
		Matrix ssy = Matlib.createMatrix();
		Matrix yi = Matlib.createMatrix();
		Matrix ymax = Matlib.createMatrix();
		Matrix told = Matlib.createMatrix();
		Matrix ut = Matlib.createMatrix();
		Matrix tt = Matlib.createMatrix();
		Matrix qt = Matlib.createMatrix();
		Matrix ttt = Matlib.createMatrix();
		Matrix ttx = Matlib.createMatrix();
		Matrix wt = Matlib.createMatrix();
		Matrix dt = Matlib.createMatrix();

		int my = Y.getRows();
		int ny = Y.getCols();
		if (ny > 1) {
			Matlib.multiplyElements(Y,Y,ssy);
			Matlib.sum(ssy,ssy);
			Matlib.max(ssy,ymax,yi);
			Matlib.getColumn(Y,(int) yi.get(0,0),U);
		} else Matlib.copy(Y,U);
		double conv = 1.0;
		int count = 1;
		Matlib.getColumn(X,0,told);
		while (conv>1.e-10 || count <100) {
			count++;
			Matlib.transpose(U,ut);
			Matlib.multiply(ut,X,wt);
			Matlib.divide(wt,Matlib.norm(wt),wt);
			Matlib.transpose(wt,W);
			Matlib.multiply(X,W,T);
			if(ny==1) {
				Q.redimension(1,1);
				Q.set(0,0,1.0);
				break;
			}
			Matlib.transpose(T,tt);
			Matlib.multiply(tt,Y,qt);
			Matlib.divide(qt,Matlib.norm(qt),qt);
			Matlib.transpose(qt,Q);
			Matlib.multiply(Y,Q,U);
			Matlib.subtract(told,T,dt);
			conv = Matlib.norm(dt);
			Matlib.copy(T,told);
//			if (count >= 50) throw new MathException("nipals: Algorithm failed to converge");
		}
		Matlib.transpose(T,tt);
		Matlib.multiply(tt,T,ttt);
		Matlib.multiply(tt,X,ttx);
		Matlib.divide(ttx,ttt,P);
		Matlib.transpose(P,P);
		double p_norm = Matlib.norm(P);
		Matlib.multiply(T,p_norm,T);
		Matlib.multiply(W,p_norm,W);
		Matlib.divide(P,p_norm,P);
		Matlib.clear(ssy);
		Matlib.clear(yi);
		Matlib.clear(ymax);
		Matlib.clear(told);
		Matlib.clear(ut);
		Matlib.clear(tt);
		Matlib.clear(qt);
		Matlib.clear(ttt);
		Matlib.clear(ttx);
		Matlib.clear(wt);
		Matlib.clear(dt);
	}

	/** weighted coin flip */
	public static boolean coinFlip(double probabilityTrueResult) {
		return probabilityTrueResult >= randDouble(0.0,1.0);
	}

	/** 50-50 coin flip */
	public static boolean coinFlip() {
		return 0.5 >= randDouble(0.0,1.0);
	}

	/** Generate a random integer between given lower and upper bounds (inclusive) **/
	public static int randInt(int lb, int ub) {
		double d = (ub - lb)*randomGenerator.nextDouble() + lb;
		return (int) Math.round(d);
	}

	public static double randDouble(double lb, double ub) {
		return (ub - lb)*randomGenerator.nextDouble() + lb;
	}

	public static int importanceSample(int n) {
		int nchits = ((n+1)*n)/2;
		int draw = randInt(1,nchits);
		int nvotes = 0;
		for(int j=0;j<n;j++) {
			nvotes+=(n-j);
			if(draw<=nvotes) {
				return j;
			}
		}
		return n;
	}

	/** Calculates core beta function */
	public static double betacore(double x, double a, double b){
		double eps = 2.0e-16;
		double y = x;
		double qab = a + b;
		double qap = a + 1;
		double qam = a - 1;
		double am = 1.0;
		double bm = am;

		y = am;
		double bz = 1 - qab * x / qap;
		double d = 0;
		double app = d;
		double ap = d;
		double bpp = d;
		double bp = d;
		double yold = d;
		int m = 1;
		while (Math.abs(y-yold) > 4*eps*Math.abs(y)){
			double tem = 2.0d * m;
			d = m * (b - m) * x / ((qam + tem) * (a + tem));
			ap = y + d * am;
			bp = bz + d * bm;
			d = -(a + m) * (qab + m) * x / ((a + tem) * (qap + tem));
			app = ap + d * y;
			bpp = bp + d * bz;
			yold = y;
			am = ap / bpp;
			bm = bp / bpp;
			y = app / bpp;
			if (m == 1) {
				bz = 1;   // only need to do this first time through
			}
			m = m + 1;
		}
		return y;
	}

		/** Calculates core beta function */
	public static double betainc(double x, double a, double b) throws MathException {
		double y = 0;
		if (x < 0 || x > 1){
			throw new MathException ("In betainc(x,a,b), x must be in the interval [0,1].");
		}
//System.out.println("x="+x);
//S/ystem.out.println("a="+a);
//System.out.println("b="+b);
		double bt = Math.exp(gammaln(a+b)-gammaln(a)-gammaln(b) + a*Math.log(x) + b*Math.log(1-x));
//System.out.println("bt="+bt);
		if (x <	(a+1)/ (a+b+2)){
			y = bt * betacore(x,a,b) / a;
		}
		if (x >= (a+1) / (a+b+2)){
		   y = 1 - bt * betacore(1-x,b,a) / b;
		}		
		return y;
	}

	public static double gammaln(double x) throws MathException {
		double eps = 2.2204e-016;
     double d1 = -5.772156649015328605195174e-1;
     double p1[] = {4.945235359296727046734888e0, 2.018112620856775083915565e2, 
           2.290838373831346393026739e3, 1.131967205903380828685045e4, 
           2.855724635671635335736389e4, 3.848496228443793359990269e4, 
           2.637748787624195437963534e4, 7.225813979700288197698961e3};
     double q1[] = {6.748212550303777196073036e1, 1.113332393857199323513008e3, 
           7.738757056935398733233834e3, 2.763987074403340708898585e4, 
           5.499310206226157329794414e4, 6.161122180066002127833352e4, 
           3.635127591501940507276287e4, 8.785536302431013170870835e3};
     double d2 = 4.227843350984671393993777e-1;
     double p2[] = {4.974607845568932035012064e0, 5.424138599891070494101986e2, 
           1.550693864978364947665077e4, 1.847932904445632425417223e5, 
           1.088204769468828767498470e6, 3.338152967987029735917223e6, 
           5.106661678927352456275255e6, 3.074109054850539556250927e6};
     double q2[] = {1.830328399370592604055942e2, 7.765049321445005871323047e3, 
           1.331903827966074194402448e5, 1.136705821321969608938755e6, 
           5.267964117437946917577538e6, 1.346701454311101692290052e7, 
           1.782736530353274213975932e7, 9.533095591844353613395747e6};
     double d4 = 1.791759469228055000094023e0;
     double p4[] = {1.474502166059939948905062e4, 2.426813369486704502836312e6, 
           1.214755574045093227939592e8, 2.663432449630976949898078e9, 
           2.940378956634553899906876e10, 1.702665737765398868392998e11, 
           4.926125793377430887588120e11, 5.606251856223951465078242e11};
     double q4[] = {2.690530175870899333379843e3, 6.393885654300092398984238e5, 
           4.135599930241388052042842e7, 1.120872109616147941376570e9, 
           1.488613728678813811542398e10, 1.016803586272438228077304e11, 
           3.417476345507377132798597e11, 4.463158187419713286462081e11};
     double c[] = {-1.910444077728e-03, 8.4171387781295e-04, 
          -5.952379913043012e-04, 7.93650793500350248e-04, 
          -2.777777777777681622553e-03, 8.333333333333333331554247e-02, 
           5.7083835261e-03};

	if (x < 0){
		throw new MathException("Input arguments must be real and nonnegative.");
	}
	double res = x;

//  0 <= x <= eps

	if (x <= eps) {
		res = -Math.log(x);
	}

//  eps < x <= 0.5

	if ((x > eps) && (x<=0.5)){
		double y = x;
		double xden = 1;
		double xnum = 0;
		for(int i = 1; i<=8;i++){
         xnum = xnum * y + p1[i-1];
         xden = xden * y + q1[i-1];
		}
        res = -Math.log(y) + (y * (d1 + y * (xnum / xden)));
	}

//  0.5 < x <= 0.6796875

	if ((x > 0.5) && (x<=0.6796875)){
		double xm1 = (x - 0.5) - 0.5;
		double xden = 1;
		double xnum = 0;
		for(int i = 1; i<=8;i++){
		 xnum = xnum * xm1 + p2[i-1];
		 xden = xden * xm1 + q2[i-1];
		}
		res = -Math.log(x) + xm1 * (d2 + xm1 * (xnum / xden));
	}
//  0.6796875 < x <= 1.5

	if ((x > 0.6796875) && (x<=1.5)){
		double xm1 = (x - 0.5) - 0.5;
		double xden = 1;
		double xnum = 0;
		for(int i = 1; i<=8;i++){
			xnum = xnum * xm1 + p1[i-1];
			xden = xden * xm1 + q1[i-1];
		}
		res = xm1 * (d1 + xm1 * (xnum / xden));
	}
	
//  1.5 < x <= 4
	if ((x > 1.5 ) && (x<=4)){
      double xm2 = x - 2;
		double xden = 1;
		double xnum = 0;
		for(int i = 1; i<=8;i++){
         xnum = xnum * xm2 + p2[i-1];
         xden = xden * xm2 + q2[i-1];
		}
		res = xm2 * (d2 + xm2 * (xnum / xden));
	}


//  4 < x <= 12

	if ((x > 4 ) && (x<=12)){
      double xm4 = x - 4;
      double xden = -1;
      double xnum = 0;
		for(int i = 1; i<=8;i++){
         xnum = xnum * xm4 + p4[i-1];
         xden = xden * xm4 + q4[i-1];
		}
		res = d4 + xm4 * (xnum / xden);
	}

// x > 12
 	if (x > 12){
      double y = x;
      double r = c[6];
      double ysq = y * y;
		for(int i = 1; i<=6;i++){
         r = r / ysq + c[i-1];
		}
      r = r / y;
      double corr = Math.log(y);
      double spi = 0.9189385332046727417803297;
      res = r + spi - 0.5*corr + y * (corr-1);
	}

	return res;
	}

	public static double ttestp(double x, double a, int z) throws MathException{
		double aa = a * 0.5;
		double y=0;
		if (z == 1){
			double xx = a / (a + x*x);
			double bb = 0.50;
			double tmp = betainc(xx,aa,bb);
//System.out.println("tmp="+tmp);
			y = tmp * 0.50;
		}else if (z == 2){
			int ic = 1;
			double xl = 0.0;
			double xr = 1.0;
			double fxl = -x*2;
			double fxr = 1.0 - (x*2);
			double xx = 0;
			if (fxl * fxr > 0) {
				throw new MathException("probability not in the range(0,1)");
			} else {
				while (ic < 30 ){
					xx = (xl + xr) * 0.5;
					double p1 = betainc(xx,aa,0.5);
					double fcs = p1 - (x*2);
					if (fcs * fxl > 0 ){
						xl = xx;
						fxl = fcs;
					}else{
						xr = xx;
						fxr = fcs;
					}
					double xrmxl = xr - xl;
					if (xrmxl <= 0.0001 || Math.abs(fcs) <= 1e-4 ){
						break;
					} else {
						ic = ic + 1;
					}
				}
			}
			if (ic == 30 ){
				throw new MathException("failed to converge!");
			}
			double tmp = xx;
			y = Math.sqrt((a - a * tmp) / tmp);
		}else {
			throw new MathException("z must be 1 or 2.");
		}
		return y;
	}

	/** %FTEST Inverse F test
%  Calculates the F statistic given the probability point
%  (p) and the numerator (n) and denominator (d) degrees 
%  of freedom.  
%  I/O format is fstat = ftest(p,n,d); 
 */
	public static double ftest(final double p, final int n, final int d) throws MathException{
		double probability = 1-p;
		int numerator = n/2;
		int denominator = d/2;
		int ic = 1;
		double xl = 0.0;
		double xr = 1.0;
		double fxl = -probability;
		double fxr = 1.0 - probability;
		double x = 0;
		if( fxl * fxr > 0 ) {
			throw new MathException("Probability not in the range(0,1) ");
		}
		while (ic < 30 ){
			x = (xl + xr) * 0.5;
			double p1 = betainc(x,numerator,denominator);
			double fcs = p1 - probability;
			if (fcs * fxl > 0){
				xl = x;
				fxl = fcs;
			}else{
				xr = x;
				fxr = fcs;
			}
			double xrmxl = xr - xl;
			if( xrmxl <= 0.0001 || Math.abs(fcs) <= 1E-4) {
				break;
			}else {
				ic = ic + 1;
			}
		}
		if (ic == 30 ) {
			throw new MathException("Failed to converge.");
		}
//% Inverted numerator and denominator 12-26-94
		 double fstat = (denominator * x) / (numerator - numerator * x);
		 return fstat;
	}
}
/* Estimates the best test set size by minimizing the upper 95th 
	percentile of mean testing error (err95).  If the test set is too small, 
	the uncertainty in the test error is large, so err95 is large.
      If the test set is too big, the mean test error is large, though
      the uncertainty is small, err95 will be large. 
	public static int estimateTestSetSize(Matrix X, Matrix Y) throws MathException {
		int nin = X.getCols(), nout = Y.getCols(), ndata = X.getRows();
		PlsArchitectureParameters AP = new PlsArchitectureParameters(nin,nout,2);	
		Matrix XTest = Matlib.createMatrix();
		Matrix YTest = Matlib.createMatrix();
		Matrix XTrain = Matlib.createMatrix();
		Matrix YTrain = Matlib.createMatrix();
		Pls model = new Pls(AP);
		for(int ntest=10;ntest<ndata-10;ntest+=10) {
			Matrix B = Matlib.createMatrix();
			randomSplit(ndata, ntest, B);
			Matlib.getRows(X,B,XTest);
			Matlib.getRows(Y,B,YTest);
			Matlib.not(B,B);
			Matlib.getRows(X,B,XTrain);
			Matlib.getRows(Y,B,YTrain);
			Matlib.clear(B);	
			model.learn(XTrain, YTrain);
			ValidationParameters VP = new ValidationParameters(model,XTrain,YTrain);
			double trainErr = VP.meanError.get(0);
			VP = new ValidationParameters(model,XTest,YTest);
			double testErr = VP.meanError.get(0);
			double testStd = VP.std.get(0);
			double err95 = testErr + 2*testStd/Math.sqrt(ntest);
System.out.println("ntest = "+ntest+" trainErr = "+Utilities.formatDouble(trainErr,4)+" testErr = "+Utilities.formatDouble(testErr,4)+" std = "+Utilities.formatDouble(testStd,4)+" err95 = "+Utilities.formatDouble(err95,4));
		}
		Matlib.clear(XTest);
		Matlib.clear(XTrain);
		Matlib.clear(YTest);
		Matlib.clear(YTrain);
		return 0;
	}
*/

