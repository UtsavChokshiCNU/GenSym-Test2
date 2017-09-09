/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RecordingPlaybackEvent.java
 *
 */
package com.gensym.editor.text;


public class RecordingPlaybackEvent extends java.util.EventObject {

  private Object o;

  public Object getObject() { return o; }

  public RecordingPlaybackEvent(Object o) {
    super(o);
    this.o = o;
  }

}
