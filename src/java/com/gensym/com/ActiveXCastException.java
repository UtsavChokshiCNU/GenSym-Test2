/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXCastException.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

/** The class <code>ActiveXCastException</code> exception indicates a 
* failure when casting a dispatch pointer to a classID.  Normally
* this will be thrown after a call to the checkCast method
* on an <code>ActiveXProxy</code> object fails.
* @see ActiveXProxy
*/
public class ActiveXCastException extends ActiveXException {
    
  /** Zero argument constructor. */
  public ActiveXCastException() {
        super();
    }

  /** Construct with an error message. */
  public ActiveXCastException(String message) {
      super(message);
  }
}

