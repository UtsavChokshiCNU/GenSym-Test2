/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2EditorWithUndo.java
 *
 */
package com.gensym.editor.text;

public interface G2EditorWithUndo extends G2Editor {

  public void undo();
  public void redo();
}

