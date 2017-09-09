/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	ItemEditor.java: Interface for custom dialogs
 *
 *     
 *   Modifications:
 *
 */


package com.gensym.dlgruntime;

import com.gensym.classes.Item;
import com.gensym.controls.ItemProxy;

/**
 * This interface enables easy integration with the Telewindows 2 Toolkit
 * of custom dialog classes that edit a multiple item.
 */

public interface MultipleItemEditor extends Commandable {

  /**
   * Will be called by the dialog launcher to specify the item
   * to be edited.
   */
  public ItemProxy[] getProxies();
}
