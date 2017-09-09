
package com.gensym.util;

/**
 * Signals that a method was called with illegal arguments.
 * @version     1.00, 11/12/96
 * @author      vkp
 */
public class NtwIllegalArgumentException extends Exception {

  /**
     * Constructs a NtwIllegalArgumentException with no detail message.
     * A detail message is a String that describes this particular exception.
     */
  public NtwIllegalArgumentException () {
    super ();
  }

  /**
   * Constructs a NtwIllegalArgumentException with the specified detail message.
   * A detail message is a String that describes this particular exception.
   * @param details the detail message
   */
  public NtwIllegalArgumentException (String details) {
    super (details);
  }
}
