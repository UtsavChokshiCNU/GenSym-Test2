package com.gensym.nols.data;
/*
 *		Gensym Model Class.
 *		This class is extended from Object.class
 *		Modified 3/25/98 by Gchen
 */

import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.matrix.TimeFunctions;
/** Model class. */
public class NolAutorecursiveModel extends NolModel2 implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected long delayInterval;

/** Create a Model object with given EnsembleModel object.*/	
	public NolAutorecursiveModel(EnsembleModel net, String name, Vector outs, 
		Vector ins, Vector oDelays, Vector iDelays, Preprocessor prep){
		super( net,  name,  outs, ins,  oDelays,  iDelays,  prep);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	public long getDelayInterval() {
		return delayInterval;
	}

	public void setDelayInterval(long d) {
		delayInterval = d;
	}

	public long[] prepareDataSet(Matrix X, Matrix Y, int horizon, Vector predictions) throws MathException{
		Vector inVars = new Vector(inputs.size());
		Vector inVarDelay = new Vector(inputs.size());
		Vector outVars = new Vector(outputs.size());
//System.out.println("get here 1");
		for(int i=0;i<outputs.size();i++){
			String varName = (String)outputs.elementAt(i);
			Variable varObj = preprocessor.getVariableFromVariableName(varName);
  			outVars.addElement(varObj);
  			long[] dls = (long[])outputDelays.elementAt(i);
			int r = 0;
			for(int j=0;j<dls.length;j++){
				if(dls[j]>0){
					r++;
				}
			}
			if (r > 0 ){
				inVars.addElement(varObj);
				long[] newdls = new long[r];
				int c = 0;
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						newdls[c] =dls[j];
						c++;
					}
				}
				inVarDelay.addElement(newdls);
			}
		}
//System.out.println("get here 3");
		long[] timeStampes = TimeFunctions.createTrainingSet(inVars, inVarDelay, outVars, X, Y);
		int r = 0;
		for(int i=0;i<inVars.size();i++) {
			Variable inVar = (Variable) inVars.elementAt(i);
			DataSeries inDataSeries = inVar.getDataSeries();
			long[] delays = (long[]) inVarDelay.elementAt(i);
			for(int j=0;j<delays.length;j++) {
				long delay = delays[j];
				if(delay - delayInterval*horizon <=0 ){
					int h = (int)((int)delay)/((int)delayInterval);
//System.out.println("delay h="+h+"  delay="+delay+"   delayInterval="+delayInterval+"  horizon="+horizon);
					replaceDelayedData(X,predictions,r,i,horizon-h,timeStampes,delay);
				}
				r=r+1;
			}
		}
//System.out.println("get here 4");
		Matrix B = Matlib.createMatrix();
//System.out.println("x size c="+X.getCols()+"r="+X.getRows()+"Y size c="+Y.getCols()+"r="+Y.getRows());
		TimeFunctions.cutBadRows(X,Y,B); // B is incidence matrix for bad rows
		long[] outTimes = TimeFunctions.selectTimes(timeStampes, B);
		return outTimes;

	}

	private void replaceDelayedData(Matrix X, Vector predictions, int r, int i, int h, long[] requiredTs,long delay){
		Prediction p = (Prediction)predictions.elementAt(h);
		Matrix yp = p.getYP();
		long[] times = p.getTimeStamps();
		int rows = X.getRows();
	//First assume the sampling intervals are the same, should consider different interval later. gchen 1/6/04
//System.out.println("x size c="+X.getCols()+"r="+X.getRows()+"    yp size c="+yp.getCols()+"r="+yp.getRows());
//System.out.println("i="+i+"        r="+r);
//System.out.println("h="+h);
		for(int n=0;n<rows;n++){
			long t = requiredTs[n]-delay;
			if(t<times[0]){	// no left side point less than the required time;
				X.set(n,r,Double.NaN);
			}else{
				int k=0;
				while(times[k]<t) {
					k++;
				} // no interpolation assume the value equals the value at later time. Need interpolation for better accuracy,gchen 1/6/04

//				System.out.println("t="+t+"    times[k]="+times[k-1]);
				if(k>=times.length){
					X.set(n,r,Double.NaN);	
				}else if(t == times[k] || k == 0){
					X.set(n,r,yp.get(k,i));
				}else{
					X.set(n,r,TimeFunctions.interpolateLinear(times[k-1],t,times[k],yp.get(k-1,i),yp.get(k,i)));
				}
			}
		}
	//end
	}


/** Return variable object for the variable name.*/
	@Override
	protected Variable getVariableFromVariableName(Vector processedData, String varName){
		for(int i=0;i<processedData.size();i++){
			DataSeries ds = (DataSeries)processedData.elementAt(i);
			Variable varObj = ds.getVarByName(varName);
			if(varObj != null) {
				return varObj;
			}
		}
		return null;
	}

}