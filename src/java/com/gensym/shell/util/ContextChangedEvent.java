/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ContextChangedEvent.java
 *
 */

package com.gensym.shell.util;

import java.util.EventObject;
import com.gensym.ntw.TwAccess;

/** 
 *  A ContextChangedEvent is delivered whenever the current 
 *   connection is changed. 
 */
public class ContextChangedEvent extends EventObject {
  private TwAccess connection;
  private boolean  isNew;

  public ContextChangedEvent(Object source, 
			     TwAccess connectionOfInterest,
			     boolean isNew){
    super(source);
    connection = connectionOfInterest;
    this.isNew = isNew;
  }

  /** 
   *  Returns either the new current connection or null if there is no
   *  current connection.
   */
  public TwAccess getConnection(){
    return connection;
  }

  /**
   * Returns true if the current connection is a new connection, false
   * if the current connection is already being handled by the ConnectionManager.
   */
  public boolean isConnectionNew() {
    return isNew;
  }
}
