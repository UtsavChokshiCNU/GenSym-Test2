/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CategoryPromptSelectedListener.java
 *
 */
package com.gensym.editor.text;

import java.awt.event.ItemListener;


/** This is a trivial (empty) extension of ItemListener to allow
 * the listeners of selections against the list of category prompts
 * to be specified more narrowly so as to distinguish them from
 * selections on item lists generally.
  * @undocumented -- final Text Editor API is still under review
 */

public interface CategoryPromptSelectedListener extends ItemListener {

  // has to implement itemStateChanged(ItemEvent)

}
