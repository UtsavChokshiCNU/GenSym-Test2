package com.gensym.nols.data;
/*
 *		Gensym DataResampler Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.util.*;
import java.io.*;

public class DataResampler implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	private String dataSeriesName;
	private long startTime;
	private long endTime;
	private long interval;
	private boolean needResample;

	/** Create a new DataResampler.*/
	public DataResampler() {
		needResample = false;
		dataSeriesName = ""; 
		startTime = 0l; 
		endTime = 0l; 
		interval= 0l;
	}

/** Create a new DataResampler with a name.*/
	public DataResampler(String name, long t1, long t2, long t3) {
		needResample = true;
		dataSeriesName = name; 
		startTime = t1; 
		endTime = t2; 
		interval= t3;
	}

/** Get the name of this Resampler. */	
	public String getDataSeriesName(){
		return dataSeriesName;
	}

/** Set the name of this Resampler. */	
	public void setDataSeriesName(String n){
		dataSeriesName = n;
	}

/** Get the startTime of this Resampler. */	
	public long getStartTime(){
		return startTime;
	}

/** Get the endTime of this Resampler. */	
	public long getEndTime(){
		return endTime;
	}

/** Get the interval of this Resampler. */	
	public long getInterval(){
		return interval;
	}

}