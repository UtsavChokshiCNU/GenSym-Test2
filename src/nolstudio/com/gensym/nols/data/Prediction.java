package com.gensym.nols.data;
/*
 *		Gensym Prediction Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.io.*;
import com.gensym.math.matrix.*;

public class Prediction implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	private long[] timeStamps;
	private Matrix Y;
	private Matrix YP;
	private int horizon;

	/** Create a new Prediction containing no characters.*/
	public Prediction() {
		timeStamps = null;
		YP = null;
		horizon = 0;
	}

/** Create a new Prediction with a name.*/
	public Prediction(long[] timeStamps, Matrix Y,Matrix YP,int h) {
		this();
		this.timeStamps = timeStamps;
		this.Y = Y;
		this.YP = YP;
		this.horizon = h;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		Prediction cloned = (Prediction) super.clone();
		cloned.Y = Y == null ? null : (Matrix) Y.clone();
		cloned.YP = YP == null ? null : (Matrix) YP.clone();
		return cloned;
	}

	public void setTimeStamps(long[] timeStamps){
		this.timeStamps = timeStamps;
	}

	public void setYP(Matrix YP){
		this.YP = YP;
	}

	public void setY(Matrix Y){
		this.Y = Y;
	}

	public void setHorizon(int h){
		this.horizon = h;
	}

	public Matrix getYP(){
		return YP;
	}

	public Matrix getY(){
		return Y;
	}

	public long[] getTimeStamps(){
		return  timeStamps;
	}

	public int getHorizon(){
		return  horizon;
	}

}