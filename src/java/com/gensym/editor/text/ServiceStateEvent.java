/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ServiceStateEvent.java
 *
 */
package com.gensym.editor.text;

import java.util.EventObject;

/** This event is intended to inform any interested parties when
 * one of the TextEditor's services becomes available/unavailable
 */
public class ServiceStateEvent extends EventObject {
  private String service;
  private boolean state;
  
  public static final String Undo = "Undo";
  public static final String Redo = "Redo";
  public static final String GoToError = "GoTo Error";
  public static final String ApplyChanges = "Apply Changes";
  public static final String Load = "Load";
  public static final String Save = "Save";
  public static final String Print = "Print";
  public static final String Replace = "Replace";
    
   public ServiceStateEvent (Object source, String service, boolean state) {
      super(source);
      this.service = service;
      this.state = state;
   }

   public String getService() {
     return service;
   }

   public boolean getState() {
     return state;
   }
}
