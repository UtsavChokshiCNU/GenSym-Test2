
package com.gensym.jgi;

/**
 * Signals an attempt to access a G2 Connection that is not
 * available or has not been created.
 *
 * @version     1.00, 22/Apr/98
 * @author      mdg
 */
public class ConnectionNotAvailableException extends RuntimeException {

  /**
   * Constructs a ItemNotAvailableException with no detail message.
   */
  public ConnectionNotAvailableException () {
    super ();
  }

/**
   * Constructs a ItemNotAvailableException with the specified detail message.
   * A detail message is a String that describes this particular exception.
   * @param details the detail message
   */
  public ConnectionNotAvailableException (String details) {
    super (details);
  }
}
