package com.gensym.nols.wksp;
import java.util.*;
import java.io.*;

/** The action semantic event. 	*/

public class TableDataEvent extends EventObject implements Serializable {

	private String id;
	private int[] coords;

/** Constructs a TableDataEvent object with the specified source object. 

*/  
 	public TableDataEvent(Object source, String id, int[] coords){
		super(source);
		this.id = id;
		this.coords = coords;
	}

	@Override
	public Object getSource(){
		return super.getSource();
	}

	public String getID(){
		return this.id;
	}

	public int[] getCoords() {
		return this.coords;
	}
}
