
package com.gensym.util;
import java.io.Serializable;

/**
 * A class that is used to associate an object with a symbol.
 * @see Symbol
 */

public class Property implements Serializable {

  public Symbol key;
  public Object value;

  /**
   * Contructs an empty Property object.
   */
  public Property () {
  }

  /**
   * Constructs a Property object that is initialized with the
   * specified values.
   * @param key the symbolic key
   * @param value the Object that is the value for that key
   */
  public Property (Symbol key, Object value) {
    this.key = key;
    this.value = value;
  }

  /**
   * Constructs a Property object by cloning the given argument.
   * @param p the property to copy.
   */
  public Property (Property p) {
    key = p.key;
    value = p.value;
  }

  /**
   *
   *
   */
  @Override
  public String toString () {
    return (key + ":" + value);
  }
}
