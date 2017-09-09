package com.gensym.nols.data;

import java.io.Serializable;

/** InnerFormula class. REPLACED BY InnerFormula2 IN 20B0, 3/99 */
public class InnerFormula extends Formula implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;

/** Create a null data transform object. */	
	public InnerFormula() {
		super();
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
}