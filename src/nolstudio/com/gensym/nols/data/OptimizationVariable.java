package com.gensym.nols.data;

import java.io.Serializable;

 /**
 * Gensym OptimizationVariable Class
 * @version     1.0 September 30, 1998
 * @author      Brian O. Bush, Gang Chen
 **/

public class OptimizationVariable extends Variable implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;

	/** Default constructor.*/
	public OptimizationVariable() {
		super();
	}

/** Constructor with name, dataseries reference and column index.*/
	public OptimizationVariable(String name) {
		this();
		this.name = new String(name); // why is this necessary?  For proper serialization?
		tag = this.name;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	/** Returns a String object representing this column value.  */
	@Override
	public String toString(){
		return name;
	}
  }
