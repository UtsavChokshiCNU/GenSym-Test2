
package com.gensym.classes;

/**
 * Signals an attempt to access a G2 Item that is not
 * available/not been fetched from G2
 * @version     1.00, 11/12/96
 * @author      vkp
 */
public class ItemNotAvailableException extends RuntimeException {

  /**
   * Constructs a ItemNotAvailableException with no detail message.
   */
  public ItemNotAvailableException () {
    super ();
  }

/**
   * Constructs a ItemNotAvailableException with the specified detail message.
   * A detail message is a String that describes this particular exception.
   * @param details the detail message
   */
  public ItemNotAvailableException (String details) {
    super (details);
  }
}
