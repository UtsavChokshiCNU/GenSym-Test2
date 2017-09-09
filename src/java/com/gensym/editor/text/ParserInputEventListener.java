/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ParserInputEventListener.java
 *
 *
 */
package com.gensym.editor.text;

import com.gensym.classes.Item;


/** This interface defines the methods that a text source will call
 * in order to have its text changes assimilated by a parser (an
 * ParserInputEventListener) for the G2 grammar. Operations on 
 * characters are over objects of type char; operations over regions
 * of text operate on Strings. 
 *
 * Every method will involve one or more 'cursors' represented as
 * ints. These numbers represent positions between characters. The
 * position to the immediate left of the first character in the text
 * has the value zero. The position between that first character and
 * the character immediately adjacent to it to its right is position
 * one, and so on.
 *
 * The description of each of these methods specifies what elements
 * of the ParserInputEvent that they are passed will have values
 * when it is called.
 *
 * @see com.gensym.editor.text.ParserInputEvent
 *
 * @author David McDonald
 * @version 1.1
 */

public abstract interface ParserInputEventListener extends java.util.EventListener {


  /** The ParserInputEvent will provide the position (an int) to which
   * the cursor has just been moved, typically by a mouse click. (The
   * cursor's position also changes with additions and deletions, but
   * those are subsumed by their own events.) The cursor indicates a
   * position between adjacent characters.  
   */
  public void cursorPositionChanged (ParserInputEvent e);


  /** The ParserInputEvent provides a character and the position just
   * to its right, i.e. an int one larger than the value of the
   * insertion point at which the character was added.  
   */
  public void characterAdded (ParserInputEvent e);


  /** The ParserInputEvent provides the position that was to the immediate 
   * left of the deleted character, i.e. the deletion is construed as through 
   * it were always a 'backspace', and has acted on the character just to the 
   * left of the cursor at the moment before the delete occurred. This is what 
   * happens when you type a del (ascii 8) or a rubout (127).
   */
  public void characterDeleted (ParserInputEvent e);


  /** The ParserInputEvent provides a cursor position and a string. The string 
   * is the sequence of characters being added. The position is the position 
   * within the existing text that they are to appear after (i.e. insertion 
   * is to the right of the insertion point just as it is with single characters).
   */
  public void regionAdded (ParserInputEvent e);


  /** The ParserInputEvent provides a cursor position and a number of characters
   * that have been deleted. The position is the one that had been to the immediate
   * left of the deleted contiguous sequence of characters. 
   */
  public void regionDeleted (ParserInputEvent e);


  /** The ParserInputEvent has the same structure as a region added or deleted.
   * The difference in this situation is that the number of adds and deletes
   * have canceled each other out and there is no difference in the length of
   * the text, though the reference position may have changed.
   */
  public void regionReplaced(ParserInputEvent e);


  /** The ParserInputEvent has the same structure as a regionReplaced event
   * in that two regions (strings) are involved. With the addition that since
   * the regions are of unequal length it requires an additional set of
   * position start/end indicies so that each region can be completely
   * described.
   */
  public void replacedUnEqualRegions(ParserInputEvent e);


  /** The passes the parser's interpretation of the text to the G2 where
   * the kb containing the item being edited resides. 
   * @param item  The item whose attribute is being edited
   * @param editingForRuntimeChange  If true, this change is propagated for
   * saving with the kb. 
   * @return true if the conclude was successful and the value of the
   * attribute changed. Any problem, such as the interpretation of the
   * text being rejected by the attribute compiler or the text being
   * ungrammatical will lead to returning false.
   */
  public boolean attemptToConcludeParsingContext(Item item, 
						 Boolean editingForRuntimeChange);


}
