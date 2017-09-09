/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BrowserCommands.java
 *
 */
package com.gensym.uitools.browsers;

import java.awt.event.ActionEvent;

import com.gensym.core.UiApplication;
import com.gensym.mdi.MDIFrame;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.util.Symbol;

public final class BrowserCommands extends AbstractCommand implements BrowserSymbols {

  public static final String ALL_HIERARCHIES     = "AllHierarchies";
  public static final String MODULE_HIERARCHY    = "ModuleHierarchy";
  public static final String WORKSPACE_HIERARCHY = "WorkspaceHierarchy";
  public static final String CLASS_HIERARCHY     = "ClassHierarchy";
  public static final String KB_BROWSER          = "Browser";

  public static final Symbol KB_WORKSPACE_     = Symbol.intern("KB-WORKSPACE");
  public static final Symbol MODULE_           = Symbol.intern("MODULE");
  public static final Symbol CLASS_DEFINITION_ = Symbol.intern("CLASS-DEFINITION");

  private static final String shortResource = "CommandShortResource";
  private static final String longResource  = "CommandLongResource";
  private static Resource shortBundle = Resource.getBundle("com/gensym/g2studio/browsers/CommandShortResource");

  private TwAccess currentConnection;
  private MDIFrame frame;

  public BrowserCommands(TwAccess cxn) {
    super(new CommandInformation[]{
      new CommandInformation(ALL_HIERARCHIES, true,
			     shortResource, longResource,
			     null, null, null, false),
	new CommandInformation(MODULE_HIERARCHY, true, 
			       shortResource, longResource,
			       null, null, null, false),
	new CommandInformation(WORKSPACE_HIERARCHY, true,
			       shortResource, longResource,
			       null, null, null, false),
	new CommandInformation(CLASS_HIERARCHY, true,
			       shortResource, longResource,
			       null, null, null, false),
	new CommandInformation(KB_BROWSER, true,
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
    if (!isAvailable(cmdKey)) 
      throw new IllegalStateException(shortBundle.format("CommandIsUnavailable", cmdKey));

    com.sun.java.swing.JDialog dlg;
    Symbol[] classNames;
    String title;

    if (cmdKey.equals(ALL_HIERARCHIES)) {
      classNames = new Symbol[] {MODULE_HIERARCHY_, WORKSPACE_HIERARCHY_, CLASS_HIERARCHY_};
      title = "Inspect";
      dlg = new com.sun.java.swing.JDialog(frame, title, false);
      dlg.getContentPane().add(new ClassInstanceBrowser(currentConnection, classNames, ROOT_, ALL_));
      dlg.setSize(500, 400);
      dlg.setVisible(true);
    }
    else if (cmdKey.equals(WORKSPACE_HIERARCHY)) {
      classNames = new Symbol[] {WORKSPACE_HIERARCHY_};
      title = "Workspace Hierarchy";
      dlg = new com.sun.java.swing.JDialog(frame, title, false);
      dlg.getContentPane().add(new ClassInstanceBrowser(currentConnection, classNames, ROOT_, ALL_));
      dlg.setSize(500, 400);
      dlg.setVisible(true);
    } else if (cmdKey.equals(MODULE_HIERARCHY)) {
      classNames = new Symbol[] {MODULE_HIERARCHY_};
      title = "Module Hierarchy";
      dlg = new com.sun.java.swing.JDialog(frame, title, false);
      dlg.getContentPane().add(new ClassInstanceBrowser(currentConnection, classNames, ROOT_, ALL_));
      dlg.setSize(500, 400);
      dlg.setVisible(true);
    } else if (cmdKey.equals(CLASS_HIERARCHY)) {
      classNames = new Symbol[] {CLASS_HIERARCHY_};
      title = "Class Hierarchy";
      dlg = new com.sun.java.swing.JDialog(frame, title, false);
      dlg.getContentPane().add(new ClassInstanceBrowser(currentConnection, classNames, ROOT_, ALL_));
      dlg.setSize(500, 400);
      dlg.setVisible(true);
    } else if (cmdKey.equals(KB_BROWSER)) {
      title = "Kb Browser";
      dlg = new com.sun.java.swing.JDialog(frame, title, false);
      dlg.getContentPane().add(new KbBrowser(currentConnection));
      dlg.setSize(500, 400);
      dlg.setVisible(true);
    } else return;

  }

  private void updateAvailability() {
    setAvailable(ALL_HIERARCHIES, (currentConnection != null));
    setAvailable(WORKSPACE_HIERARCHY, (currentConnection != null));
    setAvailable(MODULE_HIERARCHY, (currentConnection != null));
    setAvailable(CLASS_HIERARCHY, (currentConnection != null));
    setAvailable(KB_BROWSER, (currentConnection != null));
  } 
}







