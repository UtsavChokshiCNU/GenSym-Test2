package com.gensym.nols.data;

import java.io.Serializable;
import java.util.EventListener;
import java.util.Vector;

 /**
 * Gensym DataSource Class
 * @version     1.0 September 30, 1998
 * @author      Brian O. Bush, Gang Chen
 **/

public class DataSource implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected String name;
	protected String comment; //Defaults are "".
	protected Vector dataSeries;	

 	protected transient Project project = null;
	protected transient Vector itsEventListeners;

	protected int projectHashCode;

	/*  This class provides a general-purpose data source */

	public DataSource() {
		super();
		name = "";
		comment = "";
		dataSeries = new Vector();
		itsEventListeners = new Vector();
	}

	public DataSource(String sourceName) {
		this();
		name = sourceName;
	}

	public DataSource(Project p) {
		this();
		project = p;
		projectHashCode = project.hashCode();
	}
	
	@Override
	public synchronized Object clone() throws CloneNotSupportedException {
		DataSource cloned = (DataSource) super.clone();
		cloned.dataSeries = dataSeries == null ? null : (Vector) dataSeries.clone();
		cloned.project = project == null ? null : (Project) project.clone();
		cloned.itsEventListeners = itsEventListeners == null ? null : (Vector) itsEventListeners.clone();
		
		return cloned;
	}

	public Vector getDataSeries() {
		return dataSeries;
	}

	protected void setDataSeries(Vector series) {
		dataSeries = series;
	}

/** Get the name of this DataSource. */
	public String getName(){
		return name;
	}
	
/** Set the name of this DataSource. */
	public void setName(String dsName){
		name = dsName;
	}	
	
/** Return the comment of this DataSource.*/
	public String getComment(){
		return comment;
	}

/** Set the comment of this DataSource.*/
	public void setComment(String c){
		comment = c;
	}

/** Return the number of data series.*/
	public int getNumberOfDataSeries() {
		return dataSeries.size();
	}

/** Return the DataSeries from data series vector.*/
	public DataSeries getDataSeries(int dsIndex) {
		if(dsIndex<dataSeries.size())
			return (DataSeries)dataSeries.elementAt(dsIndex);
		return null;
	}

/** Return the DataSeries from data series vector.*/
	public DataSeries getDataSeries(String dataSeriesName) {
		for(int i=0;i<dataSeries.size();i++){
			DataSeries d = (DataSeries)dataSeries.elementAt(i);
			if(dataSeriesName.equals(d.getName()))
				return d;
		}
		return null;
	}

/** Return the index of given data series name.*/
	public int getDataSeriesIndex(String dataSeriesName){
		for(int i=0;i<dataSeries.size();i++){
			DataSeries d = (DataSeries)dataSeries.elementAt(i);
			if(dataSeriesName.equals(d.getName()))
				return i;
		}
		return -1;
	}

/** Return the name of given data series .*/
	public String getDataSeriesName(int index){
		DataSeries d = (DataSeries)dataSeries.elementAt(index);
		if(d != null)
			return d.getName();
		return null;
	}

	
/** Get the project of this raw data. */	
	public Project getProject(){
		return project;
	}

/** Set the project of this raw data. */	
	public  void setProject(Project p){
		project = p;
		projectHashCode = project.hashCode();
	}

	/* The event model for data event.*/
/** Register the data event listener.*/
	public synchronized void addListener(DataSourceListener l){
		if(!itsEventListeners.contains(l))
			itsEventListeners.addElement(l);
	}

/** Deregister the data event listener .*/
	public synchronized void removeListener(DataSourceListener l){
		itsEventListeners.removeElement(l);
	}

/** Clear the data event listener .*/
	public synchronized void clearListener(){
		itsEventListeners.removeAllElements();
	}

/** Initialize the transient attributes.*/
	public synchronized void initTransient(Project p){
		project =p;
		projectHashCode = project.hashCode();
		itsEventListeners = new Vector(0,4);
		for(int i=0;i<dataSeries.size();i++){
			DataSeries ds = (DataSeries)dataSeries.elementAt(i);
			ds.initTransient(this);
		}
	}

	public Vector getEventListeners() {
		return itsEventListeners;
	}

/** Creates a string representation of this. */
	@Override
	public String toString(){
		return name;
	}

}
