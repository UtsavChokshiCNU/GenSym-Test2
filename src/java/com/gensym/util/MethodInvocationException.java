package com.gensym.util;

/**
 * Exception raised due to a problem while dynamically invoking a
 * method
 *
 * @author  M.D.Gribble
 * @version 1.0, April 97
 */
public class MethodInvocationException extends Exception {

  public MethodInvocationException () {
    super();
  }

  public MethodInvocationException (String ErrorDetails) {
    super(ErrorDetails);
  }

}
