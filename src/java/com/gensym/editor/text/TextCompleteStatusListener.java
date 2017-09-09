/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TextCompleteStatusListener.java
 *
 */
package com.gensym.editor.text;


/** The Listener for TextCompleteStatus events.
 *
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */

public interface TextCompleteStatusListener extends java.util.EventListener {

  /** This method should look at the value returned by the getStatus method
   * of the event. A value of true indicates that was text is complete at 
   * the moment the event was issued. False indicates that it was not.
  * @undocumented -- final Text Editor API is still under review
   */
  public void checkStatus(TextCompleteStatusEvent e);

}
