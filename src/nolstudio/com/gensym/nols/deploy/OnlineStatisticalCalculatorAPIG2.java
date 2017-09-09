package com.gensym.nols.deploy;
/*
 *		Wrapper class for Gensym OnlineProcessor.
 *		Cannot be encrypted!
 */

import java.awt.Frame;
import java.awt.TextArea;
import java.io.Serializable;

import com.gensym.classes.FloatArray;
import com.gensym.core.DebugUtil;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.Pls;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.stats.Stats;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/** OnlineProcessor class */
public class OnlineStatisticalCalculatorAPIG2 implements Cloneable, Serializable {

  private static volatile Frame errorFrame;
  private static TextArea errorTA;
  private boolean debugBean = true;
  private boolean isloaded = false;
  
  //symbols for catching exceptions in G2
  private static Symbol RETVAL_ = Symbol.intern("RETVAL");
  private static Symbol ERROR_ = Symbol.intern("ERROR");
  private static Symbol BACKTRACE_ = Symbol.intern("BACKTRACE");
 
/** Create a null OnlineProcessor with no argument */
  public OnlineStatisticalCalculatorAPIG2() {
  }
  
  @Override
  public Object clone() throws CloneNotSupportedException {
	return super.clone();
  }
  
  public boolean getDebugProcessor () {
    return debugBean;
  }
  
  public void setDebugProcessor (boolean newDebugState) {
    debugBean = newDebugState;
  }
  
/** Make full PCA calculation.*/
	public Structure pcaFull(Sequence X)
	{

		if (debugBean){
			System.out.println("start full calculation of pca");
		}
		Structure retval = new Structure();
		try{
			int nrows = X.size();
System.out.println("nrows = "+nrows);

			Object[] inputRows = X.getContents();
			double[][] xx = new double[nrows][];
			for(int i=0;i<nrows;i++){
				xx[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
			}

			Matrix XTemp = Matlib.createMatrix(xx);

			Matrix PTemp = Matlib.createMatrix();
			Matrix VarTemp = Matlib.createMatrix();




			Matrix Xmean = Matlib.createMatrix();
			Matrix Xstd = Matlib.createMatrix();
			//System.out.println("X is "+X.getRows()+" by "+X.getCols());
			Matlib.mean(XTemp, Xmean);
			Matlib.stdnonzero(XTemp, Xstd);
			Matlib.normalize(XTemp, Xmean, Xstd, XTemp);
			// Now do the PCA calculation
			Stats.pca(XTemp,PTemp,VarTemp);

Matlib.disp(PTemp);
Matlib.disp(VarTemp);

			double[][] pp = Matlib.create2DArray(PTemp);

			double[] mm = Matlib.create1DArray(Xmean);
			double[] ss = Matlib.create1DArray(Xstd);
			double[] vv = Matlib.create1DArray(VarTemp);

			Sequence mmSeq = new Sequence(mm.length);
			Sequence ssSeq = new Sequence(ss.length);
			Sequence ppSeq = new Sequence(pp.length);
			Sequence vvSeq = new Sequence(vv.length);
			Sequence retSeq = new Sequence(4);

			for(int i=0;i<pp.length;i++){
				Sequence ppElem = new Sequence(pp[i].length);
				for(int j=0;j<pp[i].length;j++){
					ppElem.addElement(new Double(pp[i][j]));
				}
				ppSeq.addElement(ppElem);
			}

			for(int i=0;i<mm.length;i++){
				mmSeq.addElement(new Double(mm[i]));
			}
			for(int i=0;i<ss.length;i++){
				ssSeq.addElement(new Double(ss[i]));
			}
			for(int i=0;i<vv.length;i++){
				vvSeq.addElement(new Double(vv[i]));
			}
			retSeq.addElement(ppSeq);
			retSeq.addElement(vvSeq);
			retSeq.addElement(mmSeq);
			retSeq.addElement(ssSeq);
			retval.setAttributeValue(RETVAL_, retSeq);
			XTemp.clear();
			PTemp.clear();
			VarTemp.clear();

		} catch (Exception ie){
			ie.printStackTrace();
			retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
		}
		return retval;
	}

/** Make full PCA calculation and return weights*/
	public Structure pcaWeights(Sequence X)
	{

		if (debugBean) {
			System.out.println("start full calculation of pca");
		}
		Structure retval = new Structure();
		try{
			int nrows = X.size();
			Object[] inputRows = X.getContents();
			double[][] xx = new double[nrows][];
			for(int i=0;i<nrows;i++){
				xx[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
			}

			Matrix XTemp = Matlib.createMatrix(xx);
			Matrix PTemp = Matlib.createMatrix();
			Stats.pca(XTemp,PTemp);

			double[][] pp = Matlib.create2DArray(PTemp);

			Sequence ppSeq = new Sequence(pp.length);

			for(int i=0;i<pp.length;i++){
				ppSeq.addElement(pp[i]);
			}
			retval.setAttributeValue(RETVAL_, ppSeq);
			XTemp.clear();
			PTemp.clear();
		} catch (Exception ie){
			ie.printStackTrace();
			retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
		}
		return retval;
	}

/** Make PCA calculation for given number of components.
	There is no efficiency gain from using this routine compared to full PCA, 
	since internally, all PC's are calculated.*/
	public Structure pcaComponents(Sequence X, int npc)
	{

		if (debugBean) {
			System.out.println("start full calculation of pca");
		}
		Structure retval = new Structure();
		try{
			int nrows = X.size();
			Object[] inputRows = X.getContents();
			double[][] xx = new double[nrows][];
			for(int i=0;i<nrows;i++){
				xx[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
			}

			Matrix XTemp = Matlib.createMatrix(xx);
			Matrix PTemp = Matlib.createMatrix();
			Stats.pca(XTemp,npc,PTemp);

			double[][] pp = Matlib.create2DArray(PTemp);

			Sequence ppSeq = new Sequence(pp.length);

			for(int i=0;i<pp.length;i++){
				ppSeq.addElement(pp[i]);
			}
			retval.setAttributeValue(RETVAL_, ppSeq);
			XTemp.clear();
			PTemp.clear();
		} catch (Exception ie){
			ie.printStackTrace();
			retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
		}
		return retval;
	}

/** Calculates as many principal components as necessary to explain 
	the variance var, between 0.0 and 1.0 */
	public Structure pcaVariance(Sequence X, double var)
	{

		if (debugBean) {
			System.out.println("start full calculation of pca");
		}
		Structure retval = new Structure();
		try{
			int nrows = X.size();
			Object[] inputRows = X.getContents();
			double[][] xx = new double[nrows][];
			for(int i=0;i<nrows;i++){
				xx[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
			}

			Matrix XTemp = Matlib.createMatrix(xx);
			Matrix PTemp = Matlib.createMatrix();
			Stats.pca(XTemp,var,PTemp);

			double[][] pp = Matlib.create2DArray(PTemp);

			Sequence ppSeq = new Sequence(pp.length);

			for(int i=0;i<pp.length;i++){
				ppSeq.addElement(pp[i]);
			}
			retval.setAttributeValue(RETVAL_, ppSeq);
			XTemp.clear();
			PTemp.clear();
		} catch (Exception ie){
			ie.printStackTrace();
			retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
		}
		return retval;
	}
	/** Calculates nfactors using nipals recursively. This routine requires
	that X and Y are normalized to have zero-mean and unit standard deviation. */
	public Structure pls(Sequence X,Sequence Y, int nfactors){

		if (debugBean) {
			System.out.println("start pls calculation ");
		}
		if (debugBean) {
			System.out.println("nfactors="+nfactors);
		}
		Structure retval = new Structure();
		Sequence retvalsq = new Sequence(5);
		try{
			int nx = X.size();
			Object[] inputRowsX = X.getContents();
			double[][] xx = new double[nx][];
			for(int i=0;i<nx;i++){
				xx[i] = ((FloatArray)inputRowsX[i]).getFloatArrayContents();
			}

			int ny = Y.size();
			Object[] inputRowsY = Y.getContents();
			double[][] yy = new double[ny][];
			for(int i=0;i<ny;i++){
				yy[i] = ((FloatArray)inputRowsY[i]).getFloatArrayContents();
			}

			Matrix XTemp = Matlib.createMatrix(xx);
			Matrix YTemp = Matlib.createMatrix(yy);

System.out.println("nx="+nx);
System.out.println("ny="+ny);
System.out.println("XTemp.getCols()="+XTemp.getCols());
System.out.println("XTemp.getrow()="+XTemp.getRows());
System.out.println("YTemp.getCols()="+YTemp.getCols());
System.out.println("YTemp.getrow()="+XTemp.getRows());
//Matlib.disp(XTemp);
//Matlib.disp(YTemp);			
			ArchitectureParameters AP = new ArchitectureParameters(XTemp.getCols(),YTemp.getCols(),nfactors,nfactors);
			AP.trainingFraction = 1.0;
			Pls model = new Pls(AP);
			model.train(XTemp,YTemp);

			
			Matrix  Xmean = model.getXMean();
			Matrix  Ymean = model.getYMean();
			Matrix S = model.getS();
			Matrix R = model.getR();
			Matrix B = model.getB();

			double[] pp = Matlib.create1DArray(Xmean);
			Sequence ppSeq = new Sequence(pp.length);
			for(int i=0;i<pp.length;i++){
				ppSeq.addElement(new Double(pp[i]));
			}
			double[] qq = Matlib.create1DArray(Ymean);
			Sequence qqSeq = new Sequence(qq.length);
			for(int i=0;i<qq.length;i++){
				qqSeq.addElement(new Double(qq[i]));
			}

			double[][] ss = Matlib.create2DArray(S);
			Sequence ssSeq = new Sequence(ss.length);
			for(int i=0;i<ss.length;i++){
				Sequence ssElem = new Sequence(ss[i].length);
				for(int j=0;j<ss[i].length;j++){
					ssElem.addElement(new Double(ss[i][j]));
				}
				ssSeq.addElement(ssElem);
			}
			double[][] rr = Matlib.create2DArray(R);
			Sequence rrSeq = new Sequence(rr.length);
			for(int i=0;i<rr.length;i++){
				Sequence rrElem = new Sequence(rr[i].length);
				for(int j=0;j<rr[i].length;j++){
					rrElem.addElement(new Double(rr[i][j]));
				}
				rrSeq.addElement(rrElem);
			}
			double[][] bb = Matlib.create2DArray(B);
			Sequence bbSeq = new Sequence(bb.length);
			for(int i=0;i<bb.length;i++){
				Sequence bbElem = new Sequence(bb[i].length);
				for(int j=0;j<bb[i].length;j++){
					bbElem.addElement(new Double(bb[i][j]));
				}
				bbSeq.addElement(bbElem);
			}
			retvalsq.addElement(ppSeq);
			retvalsq.addElement(qqSeq);
			retvalsq.addElement(rrSeq);
			retvalsq.addElement(bbSeq);
			retvalsq.addElement(ssSeq);
			retval.setAttributeValue(RETVAL_, retvalsq);

			XTemp.clear();
			YTemp.clear();
			Ymean.clear();
			Xmean.clear();
			S.clear();
			R.clear();
			B.clear();
		} catch (Exception ie){
			ie.printStackTrace();
			retval.setAttributeValue(ERROR_, new String(ie.getMessage()));
			retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
		}
		return retval;
	}

}