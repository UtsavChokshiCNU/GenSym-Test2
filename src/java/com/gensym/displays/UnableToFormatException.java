package com.gensym.displays;

/** Signals that an object was unable to complete self-formatting. Typically
 * because it couldn't fit in the space available. */
public class UnableToFormatException extends Exception {

  public UnableToFormatException() {
  }

  public UnableToFormatException(String key) {
    super(key);
  }
}
