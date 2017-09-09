/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CorruptionException.java
 *
 *     
 *
 */

package com.gensym.util;

/** Use this Exception class when catching an exception indicates
 * that the underlying data is corrupted */

public class CorruptionException extends UnexpectedException {
  public CorruptionException(Throwable exception) {
    super(exception);
  }
  public CorruptionException(Throwable exception, String message) {
    super(exception, message);
  }
}
