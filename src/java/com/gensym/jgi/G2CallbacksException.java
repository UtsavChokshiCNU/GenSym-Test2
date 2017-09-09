package com.gensym.jgi;

import java.io.PrintWriter;

/**
 * Signals that a problem has occured while executing a callback from G2
 * into java.
 *
 * @version     1.00 12-Aug-97
 * @author      R. Penny
 */

public class G2CallbacksException
       extends Exception {

  private Exception _targetException = null;

  public G2CallbacksException () {
    super ();
  }

  public G2CallbacksException (String key) {
    super (key);
  }

  public G2CallbacksException (Exception target_exception, String key)
  {
    super(key);
    _targetException = target_exception;
  }

  public G2CallbacksException (Exception target_exception)
  {
    super();
    _targetException = target_exception;
  }

  @Override
  public void printStackTrace() {
    super.printStackTrace();
    if (_targetException != null) {
      System.out.println("Nested Exception: ");
      _targetException.printStackTrace();
    }
  }

  @Override
  public void printStackTrace(PrintWriter writer) {
    super.printStackTrace(writer);
    if (_targetException != null) {
      writer.println("Nested Exception: ");
      _targetException.printStackTrace(writer);
    }
  }
}
