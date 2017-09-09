
package com.gensym.util;

/**
 * Signals an attempt to duplicate an existing attribute in a
 * Structure.
 * @version     1.00, 11/12/96
 * @author      vkp
 */
public class DuplicateAttributeException extends Exception {

  /**
   * Constructs a DuplicateAttributeException with no detail message.
   * A detail message is a String that describes this particular exception.
   */
  public DuplicateAttributeException () {
    super ();
  }

  /**
   * Constructs a DuplicateAttributeException with the specified detail message.
   * A detail message is a String that describes this particular exception.
   * @param details the detail message
   */
  public DuplicateAttributeException (String details) {
    super (details);
  }
}
