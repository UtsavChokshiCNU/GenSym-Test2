/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   AlreadyLoggedInException.java 
 * 
 * 
 */

package com.gensym.ntw;

import com.gensym.jgi.G2AccessException;

/** 
 * An exception thrown when trying to call a restricted
 * RPC without logging in first.
 * @see com.gensym.ntw.TwGateway#login
 */
public class AlreadyLoggedInException extends G2AccessException {

  public AlreadyLoggedInException() {
    super();
  }

  public AlreadyLoggedInException(String message) {
    super(null, message);
  }
}
