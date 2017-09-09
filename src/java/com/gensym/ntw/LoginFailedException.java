/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   LoginFailedException.java 
 * 
 * 
 */ 

package com.gensym.ntw;

import com.gensym.jgi.G2AccessException;

/** An exception thrown when a login attempt failed for whatever
 * reason.
 */
public class LoginFailedException extends G2AccessException {

  public LoginFailedException() {
    super();
  }

  public LoginFailedException(String message) {
    super(null, message);
  }
}
