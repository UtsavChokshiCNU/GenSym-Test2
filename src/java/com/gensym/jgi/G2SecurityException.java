package com.gensym.jgi;

import java.io.PrintWriter;

/**
 * Signals that the requested  access to G2 is not valid
 * from this class of access.
 *
 * @version     1.00 30-April-1998
 * @author      Paul B. Konigsberg
 */

public class G2SecurityException extends G2AccessException {

  /**
   * Constructs a G2SecurityException with no detail message
   */
  public G2SecurityException () {
    super ();
  }

  /**
   * Constructs a G2SecurityException with the specified detail message
   * @param message the detail message
   */
  public G2SecurityException (String message) {
    super (message);
  }
  
  /**
   * Constructs a G2SecurityException with the stackTrace of
   * specified nested exception.
   * @param nested Exception the original exception from which this
   * exception orinated.
   */
  public G2SecurityException (Exception nestedException)
  {
    super(nestedException);
  }

  /**
   * Constructs a G2SecurityException with the specified detail message
   * and stackTrace of specified nested exception.
   * @param nested Exception the original exception from which this
   * exception orinated.
   * @param message the detail message
   */
  public G2SecurityException (Exception nestedException, String message)
  {
    super(nestedException, message);
  }

}
