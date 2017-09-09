/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Prompter.java
 *
 */
package com.gensym.editor.text;

/**
 * An interface for abstracting the access to a widget wishing to offer 
 * prompting choices to editors with associated parsing contexts.
 * @see EditContext.setPrompter
 * @see EditContext.getPrompter 
 */
public interface Prompter {
  public String getFirstItem();
  public String getLastItem();
  public void addPromptSelectionListener(PromptSelectionListener l);
  public void removePromptSelectionListener(PromptSelectionListener l);  
}
