package com.gensym.nols.data;
/*
 */

import java.util.*;
import java.io.*;	   

import com.gensym.math.matrix.*;
import com.gensym.math.*;

public class NolOptimizationThread implements Runnable,
	Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	private NolOptimization optimization;
	private DataSeries data;
	private Vector itsListeners;
	private volatile boolean isStopping;

	public NolOptimizationThread(NolOptimization optimization,DataSeries ds){
		super();
		this.optimization = optimization;
		data = ds;
		itsListeners = new Vector();
		isStopping = false;
	}

	public void addListener(OptimizationListener l) {
		itsListeners.addElement(l);
	}

	public void removeListener(OptimizationListener l) {
		itsListeners.removeElement(l);
	}

	private void informListeners(int flag,int row) {
		for (int i=0; i<itsListeners.size(); ++i) {
			OptimizationListener l = (OptimizationListener) itsListeners.elementAt(i);
			if(flag == 0){
				l.completeNewSample(row);
			}else if(flag == 1){
				l.completeCalculation();
			}
		}
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		NolOptimizationThread cloned = (NolOptimizationThread) super.clone();
		cloned.optimization = optimization == null ? null : (NolOptimization) optimization.clone();
		cloned.data = data == null ? null : (DataSeries) data.clone();
		cloned.itsListeners = itsListeners == null ? null : (Vector) itsListeners.clone();

		return cloned;
	}

	@Override
	public void run (){
		Vector varObjs = data.getVarObjects();
		Matrix Y = data.getDataMatrix();
		for(int r=0;r<Y.getRows();r++){

			Thread thisThread = Thread.currentThread();
			try {
				thisThread.sleep(10L);
			} catch (InterruptedException e){
			}
			if(isStopping)
				break;
			for(int c=0;c<varObjs.size();c++){
				String varName=varObjs.elementAt(c).toString();
				double[] bb = optimization.getBounds(varName);
				bb[2] = Y.get(r,c);
			}
 			optimization.setCalculated(false);
			try{
				optimization.calculationOptimization();
			}catch(MathException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
			informListeners(0,r);
		}
		informListeners(1,-1);
	}
	
	public void setDataSeries(DataSeries ds){
		data = ds;
	}
	public void setStop(boolean stop){
		isStopping = stop;
	}

}