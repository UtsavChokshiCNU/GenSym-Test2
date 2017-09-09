
package com.gensym.util;

/** Signals an attempt to re-initialize an object or class.
 * Methods that are designed to initialize an object or class and that should
 * only be called once should throw this exception if they are able to detect
 * that they have been called a second time.
 */

public class AlreadyInitializedException extends Exception {

  public AlreadyInitializedException() {
    super ();
  }

  public AlreadyInitializedException(String key) {
    super (key);
  }
}
