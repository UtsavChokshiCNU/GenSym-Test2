package com.gensym.nols.data;
import java.util.*;
import java.io.*;

/** The action RawDataEvent event. 	*/

public class RawDataEvent extends EventObject implements Serializable {

	private String id;
/*	id = labelCategoryAdded; labelCategoryRemoved;
	dataPointsLabeled; dataSeriesAdded; dataSeriesRemoved*/	

	private DataSeries dataSeries;
	private Object eventObj;
	private Vector varObjects;
	private int labelIndex;

/** Constructs a RawDataEvent object with the specified source object. 

     Parameters: 
          project - the object where the event originated 
          id - the type of event 
*/  
 	public RawDataEvent(Object rawData, String id){
		super(rawData);
		this.id = id;
		this.dataSeries = null;
	}

 	public RawDataEvent(Object rawData, String id,DataSeries ds){
		this(rawData,id);
		this.dataSeries = ds;
		varObjects = ds.getVarObjects();
	}

 	public RawDataEvent(Object rawData, String id, Object evtData){
		this(rawData,id);
		this.eventObj = evtData;
	}

 	public RawDataEvent(Object rawData, String id,Vector vars){
		this(rawData,id);
		varObjects = vars;
		if(vars.isEmpty()) 
			return;
		Variable varObj = (Variable)varObjects.elementAt(0);
		DataSeries ds = varObj.getDataSeries();
		if (ds != null) {
			boolean sameDs = true;
			for (int i=0; i<varObjects.size(); i++) {
				varObj = (Variable)varObjects.elementAt(i);
				if (!ds.equals(varObj.getDataSeries())) {
					sameDs = false;
					break;
				}
			}
			if (sameDs) {
				this.dataSeries = ds;
			}
		}
	}

	public Object getRawDataSource(){
		return super.getSource();
	}

	public String getIdentifier(){
		return this.id;
	}

	public DataSeries getDataSeries(){
		return dataSeries;
	}

	public Vector getVarObjects(){
		return varObjects;
	}

	public int getLabelIndex(){
		return labelIndex;
	}

	public Object getEventObject(){
		return eventObj;
	}

}
