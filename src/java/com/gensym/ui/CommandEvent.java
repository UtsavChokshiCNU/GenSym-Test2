/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CommandEvent.java
 *
 */

package com.gensym.ui;

import java.util.EventObject;


/**
 * A "Command" event is delivered whenever the availability, state, description,
 * or structure of a Command changes.
 */

//Note: Consider changing this to a PropertyChangedEvent.

public class CommandEvent extends EventObject {
  public static final int AVAILABILITY_CHANGED = 0;
  public static final int STATE_CHANGED = 1;
  public static final int DESCRIPTION_CHANGED = 2;
  public static final int ICON_CHANGED = 3;
  public static final int STRUCTURE_CHANGED = 4;

  private int id;
  private String key;

  /** 
   * Creates a CommandEvent with the specified source object, event type, 
   * and command key.
   */
  public CommandEvent(Object source, int id, String key){
    super(source);
    this.id = id;
    this.key = key;
  }

  /** 
   * Returns the command key of the CommandEvent.  The key indicates which
   * of the Command's actions has changed.
   */
  public String getKey(){
    return key;
  }

  /** Returns the id of the CommandEvent */
  public int getId(){
    return id;
  }
}







