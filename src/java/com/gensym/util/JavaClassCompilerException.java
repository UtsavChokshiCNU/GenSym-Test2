/*
 * 	 JavaClassCompilerException.java
 *
 *	 Description
 *      Exception raised while compiling a java source file
 *
 *	 Author:
 *		V.Pillai/M.D.Gribble		Dec/96
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.util;



/**
 * Exception raised while compiling a java source file
 *
 * @version 	1.0, 01 Dec 1996
 *
 * @author M.D.Gribble
 * @author Vikram Pillai
 */

public class JavaClassCompilerException extends Exception {
	public JavaClassCompilerException (String ErrorDetails) {
		super(ErrorDetails);
	}

	@Override
	public String toString() {
		return ("The following compiler reported the following while compiling a java source file: \n" 
			+ super.toString());
	}
}
