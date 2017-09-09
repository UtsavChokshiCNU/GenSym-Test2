/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ShellWorkspaceDocument.java
 *
 */
package com.gensym.demos.multiplecxnmdiapp;

import com.gensym.classes.KbWorkspace;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.mdi.MDIApplication;
import com.gensym.ntw.TwAccess;
import com.gensym.core.UiApplication;
import com.gensym.shell.commands.*;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.TW2Application;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.ui.Command;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;

import javax.swing.SwingConstants;

/**
 * This class creates a WorkspaceDocument that is used by Shell, the
 * default application shell for Telewindows2.
 *
 * @see com.gensym.shell.Shell
 */
public class ShellWorkspaceDocument extends WorkspaceDocument {

  private static Resource i18ui = Resource.getBundle("com/gensym/demos/multiplecxnmdiapp/UiLabels");
  private static MDIFrame frame = (MDIFrame)MDIApplication.getCurrentFrame();
  private static RepresentationConstraints menuConstraints
                  = new RepresentationConstraints (RepresentationConstraints.TEXT_AND_ICON,
						   SwingConstants.LEFT,
						   SwingConstants.CENTER,
						   SwingConstants.RIGHT,
						   SwingConstants.CENTER);
  private static CMenuBar menuBar = createMenuBar();
  private static CMenu windowMenu;

  /**
   *  Creates a ShellWorkspaceDocument for the specified connection and 
   *  kbworkspace. The menu bar associated with this document is the same 
   *  as the menu bar in Shell with the addition of 3 menus: 
   *  Item, Workspace and Window. The toolbar panel associated with this document 
   *  is the MDIFrame's default toolbar panel.
   */
  public ShellWorkspaceDocument(TwAccess connection, KbWorkspace wksp) throws com.gensym.jgi.G2AccessException{
    super(connection, wksp, menuBar, windowMenu, frame.getDefaultToolBarPanel());
  }

  /**
   *  Sets the title of this frame to be the name concatenated with this
   *  WorkspaceDocument's connection information.
   */
  @Override
  public void setTitle(String name){
    TwAccess connection = getConnection();
    if (connection != null)
      super.setTitle(name+" ("+connection.toShortString()+")");
  }

  private static CMenuBar createMenuBar(){
    Shell appln = (Shell) UiApplication.getApplication ();
    menuBar = new CMenuBar();
    menuBar.add (appln.createTwMenu ());
    menuBar.add (appln.createEditMenu ());
    menuBar.add (appln.createG2Menu ());
    menuBar.add (appln.createViewMenu ());
    menuBar.add (appln.createWkspMenu ());
    menuBar.add (createItemMenu ());
    menuBar.add (appln.createWindowMenu ());
    menuBar.add (appln.createHelpMenu ());
    //mb.setHelpMenu(HELP_MENU);
    return menuBar;
  }

  private static CMenu createItemMenu (){
    CMenu menu = new CMenu (i18ui.getString("itemMenu"));
    menu.add(new ItemCommands(frame), menuConstraints);
    return menu;
  }

}








