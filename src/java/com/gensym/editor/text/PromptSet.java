/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PromptSet.java
 *
 */
package com.gensym.editor.text;

import com.gensym.util.Sequence;


/** A PromptSet is a simple packaging that encapsulates the various kinds
 * of prompts that a G2 Parser can provide. Each instance of this class
 * represents the prompts that pertain to a particular cursor position
 * in the text given the text up to that point. They can be safely cached
 * provided that one can guarentee that no changes have occurred in the
 * text to the left of the position at which they were issued. 
 *
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */

public class PromptSet {

  Sequence categoryChoices;
  Sequence completionChoices;

  /** Returns a com.gensym.util.Sequence of Strings. Each string names a 
   * preterminal grammatical category in G2's grammar, all of which are
   * applicable at the point in the text being edited to which this
   * PromptSet corresponds. 
  * @undocumented -- final Text Editor API is still under review
   */
  public Sequence getCategoryChoices() {
    return(categoryChoices);
  }


  /** Returns a com.gensym.util.Sequence of Strings. Each string names
   * a token (terminal, word) in G2's grammar, all of which are
   * applicable at the point in the text being edited to which this
   * PromptSet corresponds.  
  * @undocumented -- final Text Editor API is still under review
   */
  public Sequence getCompletionChoices() {
    return(completionChoices);
  }

  /*
  * @undocumented -- final Text Editor API is still under review
  */
  protected PromptSet( Sequence categoryChoices,
		       Sequence completionChoices) {
    this.categoryChoices = categoryChoices;
    this.completionChoices = completionChoices;
  }

}
