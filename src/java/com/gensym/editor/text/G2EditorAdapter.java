/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2EditorAdapter.java
 *
 */
package com.gensym.editor.text;

import javax.swing.text.JTextComponent;
import com.gensym.classes.Item;


public class G2EditorAdapter implements G2Editor {

  //---- methods directly in G2Editor

  @Override
  public void setText(String text, int caretPosition) {}

  @Override
  public void sendTextChangesToParser() {}

  @Override
  public boolean attemptToConcludeText(Item item, ParserInputEventListener l,
				       Boolean editingForRuntimeChange) {
    return false;
  }

  @Override
  public void positionCursorAtError() {}


  //---- methods in JTextArea but not in other daughters of JTextComponent
  @Override
  public void insert(String string, int caretPosition) {}


  //---- methods in JTextComponent

  @Override
  public int getCaretPosition() { return 0; }
  @Override
  public String getText() { return ""; }


  //---- methods in PromptsTarget
  @Override
  public void moveCursor(int position) {}
  @Override
  public void insertPromptStringAtCursor(String s) {}
  @Override
  public String getLeftPromptContext(int length) { return "";}
  @Override
  public String getRightPromptContext(int length) { return "";}


  //---- methods in ParserInputSource
  @Override
  public void addParserInputEventListener(ParserInputEventListener l) {}
  @Override
  public void removeParserInputEventListener(ParserInputEventListener l) {}


  //---- methods in ParsingStatusUpdatedListener
  @Override
  public void changeParsingStatus(ParsingStatusUpdatedEvent e) {}

}
