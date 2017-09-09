package com.gensym.jgi.download;

/**
 * Class raised at runtime when Stub creation has failed.
 */
public class StubCreationException extends RuntimeException {

  public StubCreationException () {
    super();
  }

  public StubCreationException (String ErrorDetails) {
    super(ErrorDetails);
  }

}
