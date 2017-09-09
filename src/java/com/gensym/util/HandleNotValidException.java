/*
 * 	 HandleNotValidException.java
 *
 *	 Description
 *      Exception raised when an Instance handle does not refer to an obect
 *
 *	 Author:
 *		M.D.Gribble		Feb/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.util;


import java.io.*;

/**
 * Exception to raised when read when trying to read a java class from a source fil	
 *
 * @version 	1.0, 25 Feb 1997
 *
 * @author M.D.Gribble
 */

public class HandleNotValidException extends Exception {

  public HandleNotValidException () {
    super();
  }

  public HandleNotValidException (String ErrorDetails) {
    super(ErrorDetails);
  }
}

