package com.gensym.nols.data;
import java.util.*;
import java.io.*;

/** The action PreprocessorEvent event. 	*/

public class PreprocessorEvent extends EventObject implements Serializable {

	static final long serialVersionUID = 1L;
	private String id;
	private Vector dataBanks;
	private Vector varObjs;

/** Constructs a PreprocessorEvent object with the specified source object. 

     Parameters: 
*/  
 	public PreprocessorEvent(Object prep, String id){
		super(prep);
		this.id = id;
		this.dataBanks = new Vector();
		varObjs = new Vector();
	}

 	public PreprocessorEvent(Object prep, String id,Vector dss,int flag){
		this(prep,id);
		if(flag == 0)
			this.dataBanks = dss;
		else if(flag == 1)
			varObjs = dss;
	}


	public Object getPreprocessor(){
		return super.getSource();
	}

	public String getIdentifier(){
		return this.id;
	}

	public Vector getDataSeries(){
		return dataBanks;
	}

	public Vector getVarObjects(){
		return varObjs;
	}

}
