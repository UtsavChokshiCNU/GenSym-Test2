package com.gensym.jmail;
/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Gensym Copyright (c) 2004-2006</p>
 * <p>Company: Gensym Corporation</p>
 * @author not attributable
 * @version 1.0
 */

import com.gensym.util.Sequence;

public class ArraySequence extends Sequence {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ArraySequence() {
	}

	public ArraySequence(Object[] anArray) {
		
		if (anArray != null) {

			for (int i = 0; i < anArray.length; i++) {
				this.add(anArray[i]);
				// G2JavaLog.log(G2JavaLog.BRIDGE_IO, "ArraySequence: " + i);
			}
		}
	}

}