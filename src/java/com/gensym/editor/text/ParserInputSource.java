/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ParserInputSource.java
 *
 */
package com.gensym.editor.text;


/** Defines the add and remove methods that an object must define to
 * be a valid source of input text events to the G2 Parser.  
 *
 * @see com.gensym.editor.text.ParserInputEventListener
 *
 * @author David McDonald
 * @version 1.0
 * @undocumented -- final Text Editor API is still under review
 */

public interface ParserInputSource {

  /** Adds the listener to the list 
   * @undocumented -- final Text Editor API is still under review
   */
  public void addParserInputEventListener (ParserInputEventListener l);

  /** Removes the listener from the list 
   * @undocumented -- final Text Editor API is still under review
   */
  public void removeParserInputEventListener (ParserInputEventListener l);

}
