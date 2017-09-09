/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PromptSelectedEvent.java
 *
 */
package com.gensym.editor.text;

import java.awt.event.ItemEvent;
import java.awt.ItemSelectable;


/** This is the event that is issued to indicate that one of the prompts has
 * been selected. It is just a gloss on an ItemEvent, as issued by an awt.List
 * widget. 
 *
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */
public class PromptSelectedEvent extends ItemEvent {

  /** This constructor has the very same signature as an ItemEvent.
   * @param  Source is the object issuing the event.
   * @param  id is the type of event. Issued by a standard awt component as it is
   *   in this case it will be the int ItemEvent.ITEM_STATE_CHANGED.
   * @param  the item in this case is the selected prompt, a String.
   * @param  stateChange is one of the ItemEvent constants indicating whether the
   *   event is a selection or a deselection. 
  * @undocumented -- final Text Editor API is still under review
   */
  public PromptSelectedEvent(ItemSelectable source, int id, Object item, int stateChange) {
    super(source, id, item, stateChange);
  }
}
