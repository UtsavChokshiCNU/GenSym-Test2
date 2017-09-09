/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GeneratedDialogFactory.java
 *
 */

package com.gensym.gcg;

import java.awt.Component;
import java.awt.Frame;
import java.util.Locale;
import com.gensym.classes.Item;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemProxy;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;

/**
 * Interface for creating properties dialogs for items.
 */
public interface GeneratedDialogFactory{

  /**
   * Creates a properties dialog for the item.
   */
  public Component generateDialog(Frame frame, TwAccess connection, ItemProxy itemProxy, 
				  DialogCommand dialogCommand, Locale locale) throws G2AccessException;
  
}
