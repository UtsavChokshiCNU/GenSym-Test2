/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PromptSelectionListener.java
 *
 */
package com.gensym.editor.text;

/**
 * An interface for listening to prompts being selected in a Prompter
 * @see Prompter
 */
public interface PromptSelectionListener {
  public void promptSelected(String prompt);
}
