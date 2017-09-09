package com.gensym.jgi;
/**
 * Signals that a Timeout has occured during an Interface operation 
 * such as an RPC call.
 * 
 * @version     1.00, 25-April-1997
 * @author      M.D.Gribble
 */

public class TimeoutException extends G2AccessException {

  /* NOTE Class extends RuntimeException, compiler does not moan if is
     not caught at compile time */

  /**
   * Constructs a TimeoutException with no detail message.
   * A detail message is a String that describes this particular exception.
   */
  public TimeoutException () {
    super ();
  }

  /**
   * Constructs a TimeoutException with the specified detail message.
   * A detail message is a String that describes this particular exception.
   * @param details the detail message
   */
  public TimeoutException (String details) {
    super (details);
  }
}
