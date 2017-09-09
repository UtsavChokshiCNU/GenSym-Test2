/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 InstancePopupMenuFactory.java
 *
 */
package com.gensym.ntw.util;

import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;

import javax.swing.JPopupMenu;
import javax.swing.JTree;

/**
 *  This interface defines a factory for creating popup menus.
 */

public interface InstancePopupMenuFactory {

  /**
   *  Creates and returns a JPopupMenu
   */
  public JPopupMenu createInstancePopupMenu(TwAccess cxn, Symbol dataType, JTree tree);

}
