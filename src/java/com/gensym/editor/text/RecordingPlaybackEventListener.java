/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RecordingPlaybackListener.java
 *
 */
package com.gensym.editor.text;


public interface RecordingPlaybackEventListener extends java.util.EventListener {

  public void handleRecordPlaybackEvent(RecordingPlaybackEvent e);

}
