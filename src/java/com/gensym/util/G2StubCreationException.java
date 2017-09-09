package com.gensym.util;

/**
 * Class raised when G2 Stub creation has failed.
 */
public class G2StubCreationException extends Exception {

  public G2StubCreationException () {
    super();
  }

  public G2StubCreationException (String ErrorDetails) {
    super(ErrorDetails);
  }
}
