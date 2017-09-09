/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   InvalidUserModeException.java 
 * 
 * 
 */ 

package com.gensym.ntw;

import com.gensym.jgi.G2AccessException;

/** An exception thrown when g2 rejects an attempt to change to
 * a new user mode.
 */
public class InvalidUserModeException extends G2AccessException {

  public InvalidUserModeException() {
    super();
  }

  public InvalidUserModeException(String message) {
    super(null, message);
  }
}
