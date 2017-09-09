package com.gensym.nols.data;
import java.util.*;
import java.io.*;

/** The action ProjectEvent event. 	*/

public class ProjectEvent extends EventObject implements Serializable {

	static final long serialVersionUID = 1L;

	private String id;
/*	id = labelCategoryAdded; labelCategoryRemoved;
	dataPointsLabeled; variableAdded; variableRemoved*/	

/** Constructs a ProjectEvent object with the specified source object. 

     Parameters: 
*/  
 	public ProjectEvent(Object project, String id){
		super(project);
		this.id = id;
	}

	public Object getProject(){
		return super.getSource();
	}

	public String getIdentifier(){
		return this.id;
	}
}
