/*
 * 	 NotJavaClassException.java
 *
 *	 Description
 *      Exception to raised when read when trying to read a java class from a source file
 *
 *	 Author:
 *		V.Pillai/M.D.Gribble		Dec/96
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.util;


import java.io.*;

/**
 * Exception to raised when read when trying to read a java class from a source file
 *
 * @version 	1.0, 01 Dec 1996
 *
 * @author M.D.Gribble
 * @author Vikram Pillai
 */

public class NotJavaClassException extends Exception {

  public NotJavaClassException (String ErrorDetails) {
    super(ErrorDetails);
  }

  @Override
  public String toString () {
    return ("The following error occurred while reading a java source file:\n" + super.toString());
  }
}

