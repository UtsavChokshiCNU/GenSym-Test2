/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXException.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

/** The class <code>ActiveXException</code> is the top level
* exception class thrown by the com.gensym.com package..
*/
public class ActiveXException extends Exception {
  
  /** Zero argument constructor.*/  
  public ActiveXException() {
        super();
    }

  /** Construct with a message.*/  
  public ActiveXException(String message) {
      super(message);
  }

}
