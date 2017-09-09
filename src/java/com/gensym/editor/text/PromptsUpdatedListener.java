/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PromptsUpdatedListener.java
 *
 *   Description: 
 *     
 *
 *	 Author:
 *		David McDonald		October/97
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.editor.text;


/** Any object that wants to be informed of the prompts that the G2 Parser
 * issues in response to changes in the text it is analyzing must implement
 * PromptsUpdatedListener. 
 *
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */
public interface PromptsUpdatedListener extends java.util.EventListener {

  /** This method is called whenever the Parser has a new set of prompts
   * to issue, corresponding to the results of its analysis of the last
   * input event that it processed from its text source. The prompts reflect
   * the options available at the cursor position in the text source at
   * the moment that it issued the ParserInputEvent. 
  * @undocumented -- final Text Editor API is still under review
   */
  public void updatePrompts(PromptsUpdatedEvent e);

}
