/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Editor.java
 *
 */
package com.gensym.editor.text;

import com.gensym.classes.Item;

/** This defines the assumptions that Session and its associated classes
 * make about the component that is being used as the editing area when
 * some variant on the standard UI is being used.
 *   The most direct implementation of this is as a JTextComponent, which
 * is the minimum that will allow the use of all of Unicode and specified 
 * fonts (via the font.properties files). G2EditorAdapter is such a class,
 * with dummy methods for the parsing-specific methods.
 */

public interface G2Editor 
extends ParserInputSource, ParsingStatusUpdatedListener, PromptsTarget {

  /** @return The entire text being edited. */
  public String getText();

  /** @return The position of the caret or cursor. Indicates where new
   * characters will be inserted. Caret positions are located between
   * adjacent characters and start at zero. */
  public int getCaretPosition();


  public void setText(String text, int caretPosition);

  public void insert(String string, int caretPosition);

  public void sendTextChangesToParser();

  public boolean attemptToConcludeText(Item item, ParserInputEventListener l,
				       Boolean editingForRuntimeChange);

  public void positionCursorAtError();

}
