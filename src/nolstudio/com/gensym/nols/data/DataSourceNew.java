package com.gensym.nols.data;

import java.io.*;
import java.util.*;

 /**
 * Gensym DataSource Class
 * @version     1.0 September 30, 1998
 * @author      Brian O. Bush, Gang Chen
 **/

public class DataSource extends Object implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected String name;
	private String comment; //Defaults are "".

 	protected transient Project project = null;
	protected transient Vector itsEventListeners;

	protected int projectHashCode;

	/*  This class provides a general-purpose data source */

	public DataSource() {
		super();
		name = "";
		comment = "";
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
	public void initTransient(Project p){
		project =p;
		projectHashCode = project.hashCode();
		itsEventListeners = new Vector(0,4);
	}

/** Creates a string representation of this. */
	public String toString(){
		return name;
	}

}
