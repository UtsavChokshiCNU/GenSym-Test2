/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ServiceStateListener.java
 *
 */
package com.gensym.editor.text;

/** This method is called when one of the TextEditor's
 *  services becomes available/unavailable
 */ 
public interface ServiceStateListener {
   public void serviceStateChanged (ServiceStateEvent event);
}
