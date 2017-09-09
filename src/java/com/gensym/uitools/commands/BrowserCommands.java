/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BrowserCommands.java
 *
 */
package com.gensym.uitools.commands;

import java.awt.Dimension;
import java.awt.Point;
import java.awt.event.ActionEvent;

import com.gensym.core.UiApplication;
import com.gensym.mdi.MDIFrame;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.ntw.util.ClassBrowserScrollPane;
import com.gensym.ntw.util.ModuleBrowserScrollPane;
import com.gensym.uitools.browsers.ObjectBrowserScrollPane;
import com.gensym.uitools.browsers.WorkspaceBrowserScrollPane;
import com.gensym.util.Symbol;

import javax.swing.JDialog;
import javax.swing.WindowConstants;


public final class BrowserCommands extends AbstractCommand implements BrowserSymbols {

  public static final String MODULE_HIERARCHY    = "ModuleHierarchy";
  public static final String WORKSPACE_HIERARCHY = "WorkspaceHierarchy";
  public static final String CLASS_HIERARCHY     = "ClassHierarchy";
  public static final String OBJECT_HIERARCHY    = "ObjectHierarchy";

  public static final Symbol KB_WORKSPACE_     = Symbol.intern("KB-WORKSPACE");
  public static final Symbol MODULE_           = Symbol.intern("MODULE");
  public static final Symbol CLASS_DEFINITION_ = Symbol.intern("CLASS-DEFINITION");

  private static final String shortResource = "BrowserCommandShortResource";
  private static final String longResource  = "BrowserCommandLongResource";
 
  private TwAccess currentConnection;
  private MDIFrame frame;

  public BrowserCommands(TwAccess cxn) {
    super(new CommandInformation[]{
	new CommandInformation(MODULE_HIERARCHY, true, 
			       shortResource, longResource,
			       "module-hierarchy.gif", null, null, false),
	new CommandInformation(WORKSPACE_HIERARCHY, true,
			       shortResource, longResource,
			       "workspace-hierarchy.gif", null, null, false),
	new CommandInformation(CLASS_HIERARCHY, true,
			       shortResource, longResource,
			       "class-hierarchy.gif", null, null, false),
	new CommandInformation(OBJECT_HIERARCHY, true,
			       shortResource, longResource,
			       null, null, null, false)});
    setConnection(cxn);
    frame = (MDIFrame)UiApplication.getCurrentFrame();
  }
    
  public void setConnection(TwAccess connection) {
    currentConnection = connection;
    updateAvailability();
  }

  @Override
  public void actionPerformed(ActionEvent event) {
    String cmdKey = event.getActionCommand();
   
    JDialog dlg;
    Symbol[] classNames;
    String title;

    if (cmdKey.equals(WORKSPACE_HIERARCHY)) {
      title = "Workspace Hierarchy";
      dlg = new JDialog(frame, title, false);
      dlg.getContentPane().add(new WorkspaceBrowserScrollPane(currentConnection, ALL_, ROOT_));
    } else if (cmdKey.equals(MODULE_HIERARCHY)) {
      title = "Module Hierarchy";
      dlg = new JDialog(frame, title, false);
      dlg.getContentPane().add(new ModuleBrowserScrollPane(currentConnection, ALL_, ROOT_));
    } else if (cmdKey.equals(CLASS_HIERARCHY)) {
      title = "Class Hierarchy";
      dlg = new JDialog(frame, title, false);
      dlg.getContentPane().add(new ClassBrowserScrollPane(currentConnection, ALL_, ROOT_));
    } else if (cmdKey.equals(OBJECT_HIERARCHY)) {
      title = "Object Browser";
      dlg = new JDialog(frame, title, false);
      dlg.getContentPane().add(new ObjectBrowserScrollPane(currentConnection, ALL_));
    } else return;

    dlg.setSize(500, 400);
    Dimension frameSize = frame.getSize();
    Point     frameLoc  = frame.getLocation();
    Dimension mySize    = dlg.getSize();
      
    int x = Math.max(0, frameLoc.x + (frameSize.width/2) -(mySize.width/2));
    int y = Math.max(0,frameLoc.y + (frameSize.height/2)-(mySize.height/2));
     
    dlg.setBounds (x, y, mySize.width, mySize.height);
    
    // for now, dispose the dialog on close. once the trees are 100% dynamic, then we
    // can cache the dialogs
    dlg.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);   
    dlg.setVisible(true);

  }

  private void updateAvailability() {
    setAvailable(WORKSPACE_HIERARCHY, (currentConnection != null));
    setAvailable(MODULE_HIERARCHY, (currentConnection != null));
    setAvailable(CLASS_HIERARCHY, (currentConnection != null));
    setAvailable(OBJECT_HIERARCHY, (currentConnection != null));
  } 
}







