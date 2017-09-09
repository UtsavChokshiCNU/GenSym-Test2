/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WrappingException.java
 *
 *     
 *
 */

package com.gensym.core.util;

import java.io.PrintWriter;
import java.io.PrintStream;

/**
 * Use this Exception class when catching an exception that you did
 * not expect, either because you received an Exception whose type
 * you did not expect (i.e., of the wrong class), or because you felt
 * that the exception you received should not have been thrown, given
 * what you knew about program state.
 * <p>
 * If you are catching an exception that you feel should never happen,
 * by all means catch the exception, but if it is ever thrown, you should
 * throw a subclass of this <code>WrappingException</code> class,
 * nesting within it the exception you caught.
 * @author Robert Penny
 * @version 1.0 11-NOV-1997
 */

import com.gensym.message.*;

public class WrappingException extends RuntimeException {
  protected static Resource i18n = Resource.getBundle("com.gensym.core.util.Messages");
  private Throwable nestedException;
  private String message;

  /** You must have a checked exception object that you will include in this
   * exception */
  public WrappingException (Throwable exception) {
    nestedException = exception;
  }

  /** You can include a message when throwing this exception */

  public WrappingException (Throwable exception, String message) {
    super(message);
    nestedException = exception;
  }

  @Override
  public void printStackTrace() {
    printStackTrace (System.err);
  }

  @Override
  public void printStackTrace (PrintStream ps) {
    super.printStackTrace(ps);
    if (nestedException != null) {
      System.err.println(i18n.getString("nestedException"));
      nestedException.printStackTrace(ps);
    } else {
      System.err.println(i18n.getString("noNestedException"));
    }
  }

  @Override
  public void printStackTrace(PrintWriter writer) {
    super.printStackTrace(writer);
    if (nestedException != null) {
      writer.println(i18n.getString("nestedException"));
      nestedException.printStackTrace(writer);
    } else {
      writer.println(i18n.getString("noNestedException"));
    }
  }

  @Override
  public String toString () {
    return nestedException == null ? super.toString() :
      super.toString() + i18n.format("wrapping", nestedException.toString ());
  }
}

    
