/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 LoginOkException.java
 *
 * author: David McDonald
 *
 */
package com.gensym.ntw;

import com.gensym.jgi.G2AccessException;

/** An exception thrown when a problem occurs while analyzing an Ok file
 * associated with the login attempt or while checking its authorization.
 */
public class OkException extends G2AccessException {

  public OkException(String msg) {
    super(msg);
  }

}
