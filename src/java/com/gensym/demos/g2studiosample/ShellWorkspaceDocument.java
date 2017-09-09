/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ShellWorkspaceDocument.java
 *
 */
package com.gensym.demos.g2studiosample;

import com.gensym.classes.KbWorkspace;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.WorkspaceDocument;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIApplication;

public class ShellWorkspaceDocument extends WorkspaceDocument {

  /**
   *  Creates a ShellWorkspaceDocument for the specified connection and 
   *  kbworkspace. 
   */
  public ShellWorkspaceDocument(TwAccess connection, KbWorkspace wksp, JMenu windowMenu, JMenuBar menuBar)
       throws com.gensym.jgi.G2AccessException
  {
    super(connection, wksp, menuBar, windowMenu,
	  ((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultToolBarPanel());
  }

  /**
   *  Creates a ShellWorkspaceDocument for the specified connection and 
   *  kbworkspace. 
   */
  public ShellWorkspaceDocument(TwAccess connection, KbWorkspace wksp)
       throws com.gensym.jgi.G2AccessException
  {
    super(connection, wksp);
  }
  
  /**
   *  Sets the title of this frame to be the name concatenated with this
   *  WorkspaceDocument's connection information.
   */
  @Override
  public void setTitle(String name){
    if (isClosed()) 
      return;
    TwAccess connection = getConnection();
    if (connection != null)
      super.setTitle(name+" ("+connection.toShortString()+")");
  }
  
}
