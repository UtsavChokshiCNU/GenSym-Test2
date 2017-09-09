/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ParsingStatusUpdatedListener.java
 *
 */
package com.gensym.editor.text;

/** This is the listener for status updates from the G2 Parser. These
 * are issued after every ParserInputEvent once the parser has updated
 * its analysis to take into account the changes the event indicated
 * had occurred to the text. 
 *
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */
public interface ParsingStatusUpdatedListener extends java.util.EventListener {

  /** Every ParsingStatusUpdatedListener must implement this method.
   * @see com.gensym.editor.text.ParsingStatusUpdatedEvent
  * @undocumented -- final Text Editor API is still under review
   */
  public void changeParsingStatus(ParsingStatusUpdatedEvent e);

}

