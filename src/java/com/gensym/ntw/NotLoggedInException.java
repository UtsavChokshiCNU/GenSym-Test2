/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   NotLoggedInException.java 
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
public class NotLoggedInException extends G2AccessException {

  public NotLoggedInException() {
    super();
  }

  public NotLoggedInException(String message) {
    super(null, message);
  }
}
