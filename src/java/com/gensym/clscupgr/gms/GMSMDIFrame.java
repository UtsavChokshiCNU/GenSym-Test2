/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GMSMDIFrame.java
 *
 */

package com.gensym.clscupgr.gms;

import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIFrame;
import com.gensym.shell.util.WorkspaceDocument;

import javax.swing.JMenu;
import javax.swing.JMenuBar;


public class GMSMDIFrame extends MDIFrame {
  public GMSMDIFrame (String title) {
    super(title);
    getManager().setDocumentsModifyMenuBar(false);
  }

  @Override
  public void setDefaultMenuBar(JMenuBar defaultMenuBar) {
    setDefaultMenuBar(defaultMenuBar, null);
  }
}

