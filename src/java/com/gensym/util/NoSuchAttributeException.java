
package com.gensym.util;

/**
 * Signals an attempt to access a non-existent attribute in a
 * Structure.
 * @version     1.00, 11/12/96
 * @author      vkp
 */
public class NoSuchAttributeException extends Exception {

  /**
   * Constructs a NoSuchAttributeException with no detail message.
   * A detail message is a String that describes this particular exception.
   */
  public NoSuchAttributeException () {
    super ();
  }

/**
   * Constructs a NoSuchAttributeException with the specified detail message.
   * A detail message is a String that describes this particular exception.
   * @param details the detail message
   */
  public NoSuchAttributeException (String details) {
    super (details);
  }
}
