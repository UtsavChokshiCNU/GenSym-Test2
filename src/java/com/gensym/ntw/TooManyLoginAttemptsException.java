/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   TooManyLoginAttemptsException.java 
 * 
 * 
 */

package com.gensym.ntw;

import com.gensym.jgi.G2AccessException;

/** An exception thrown when a login attempt failed for whatever
 * reason.
 */
public class TooManyLoginAttemptsException extends G2AccessException {

  public TooManyLoginAttemptsException() {
    super();
  }

  public TooManyLoginAttemptsException(String message) {
    super(null, message);
  }
}
