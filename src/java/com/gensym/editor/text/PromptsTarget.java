/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PromptsTarget.java
 *
 */
package com.gensym.editor.text;


/** 
 * Any text component that wants to accept prompts from the G2 grammar
 * must implement this interface. 
 *   Prompts are introduced at the position of the text-insertion cursor
 * (caret). The prompt that is selected may overlap with the text to
 * either side and only the needed additional text will be added. 
 * To arrive at just how much text (if any) needs to be added, the
 * program managing the prompts needs to get a snapshot of the characters
 * to either side of the insertion point. In cases of overlap it may
 * also be appropriate just to move the target's cursor.
 *   Note that the cursor is assumed to lie between a pair of characters
 * rather than on some character.
 */

public interface PromptsTarget {

  /** Return the indicated number of characters to the left of the
   * current location of the cursor. If the text is smaller than that
   * number return what there is. */
  public String getLeftPromptContext (int length);

  /** Return the indicated number of characters to the right of the
   * current location of the cursor. If the text is smaller than that
   * number return what there is. */
  public String getRightPromptContext (int length);

  /** Add the indicated string verbatim to the target text at the current 
   * location of the character-insertion cursor. */
  public void insertPromptStringAtCursor (String s);

  /** Move the location of the character-insertion cusor the indicated
   * number of characters either the right (positive delta) or to the
   * left (negative delta). */
  public void moveCursor(int delta);
   
}
