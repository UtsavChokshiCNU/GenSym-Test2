/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ShellWorkspaceDocument.java
 *
 */
package com.gensym.ntw.test;

import com.gensym.classes.KbWorkspace;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.mdi.MDIApplication;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.VersionHelper;
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

  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/Messages");
  private static MDIFrame frame = (MDIFrame)MDIApplication.getCurrentFrame();
  private static RepresentationConstraints menuConstraints = new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON, SwingConstants.LEFT, SwingConstants.CENTER, SwingConstants.RIGHT, SwingConstants.CENTER);
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
    menuBar = new CMenuBar();
    CMenu fileMenu = createFileMenu();
    menuBar.add(fileMenu);
    menuBar.add(createEditMenu());
    menuBar.add(createItemMenu());
    if (VersionHelper.isUsingJava2D(ShellWorkspaceDocument.class))
      menuBar.add(createViewMenu());
    menuBar.add(createWorkspaceMenu());
    menuBar.add(createG2Menu());
    menuBar.add(createWindowMenu());
    menuBar.add(createHelpMenu());
    //mb.setHelpMenu(HELP_MENU);
    return menuBar;
  }

  private static CMenu createFileMenu() {
    CMenu menu = new CMenu (shortBundle.getString("ShellFileMenu"));
    menu.setMnemonic(shortBundle.getString("ShellFileMenuMnemonic").charAt(0));
    Shell app = (Shell)UiApplication.getApplication();
    menu.add(app.wkspHandler, WorkspaceCommands.GET_KBWORKSPACE, menuConstraints);
    menu.addSeparator();
    menu.add(app.exitHandler, menuConstraints);
    return menu;
  }

  private static CMenu createEditMenu() {
    CMenu menu = new CMenu (shortBundle.getString("ShellWorkspaceEditMenu"));
    menu.setMnemonic(shortBundle.getString("ShellWorkspaceEditMenuMnemonic").charAt(0));
    menu.add(new EditCommands(frame), null, menuConstraints);
    return menu;
  }

  private static CMenu createItemMenu(){
    CMenu menu = new CMenu (shortBundle.getString("ShellWorkspaceItemMenu"));
    menu.setMnemonic(shortBundle.getString("ShellWorkspaceItemMenuMnemonic").charAt(0));
    menu.add(new ItemCommands(frame), menuConstraints);
    return menu;
  }

  private static CMenu createViewMenu(){
    CMenu menu = new CMenu (shortBundle.getString("ShellViewMenu"));
    menu.setMnemonic(shortBundle.getString("ShellViewMenuMnemonic").charAt(0));
    Shell app = (Shell)UiApplication.getApplication();
    // WARNING: test this for version when there are more menu items. remove
    // test around call to createViewMenu
    menu.add(app.zoomHandler, app.zoomHandler.ZOOM, menuConstraints);
    return menu;
  }

  private static CMenu createWorkspaceMenu(){
    CMenu menu = new CMenu (shortBundle.getString("ShellWorkspaceMenu"));
    menu.setMnemonic(shortBundle.getString("ShellWorkspaceMenuMnemonic").charAt(0));
    menu.add(new WorkspaceInstanceCommands(frame), menuConstraints);
    return menu;
  }
   
  private static CMenu createG2Menu() {
    CMenu menu = new CMenu(shortBundle.getString("ShellG2Menu")); 
    menu.setMnemonic(shortBundle.getString("ShellG2MenuMnemonic").charAt(0));
    Shell app = (Shell)UiApplication.getApplication();
    menu.add(app.switchConnectionHandler);
    menu.add(app.connectionHandler, menuConstraints);
    menu.addSeparator();
    menu.add(app.g2StateHandler, menuConstraints);
    return menu;
  }

  private static CMenu createWindowMenu(){
    windowMenu = new CMenu(shortBundle.getString("ShellWindowMenu"));
    windowMenu.setMnemonic(shortBundle.getString("ShellWindowMenuMnemonic").charAt(0));
    windowMenu.add(frame.getManager().getTilingCommand());
    return windowMenu;
  }

  private static CMenu createHelpMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ShellHelpMenu"));
    menu.setMnemonic(shortBundle.getString("ShellHelpMenuMnemonic").charAt(0));
    Shell app = (Shell)UiApplication.getApplication();
    menu.add(app.helpHandler);
    menu.addSeparator();
    menu.add(app.traceHandler);
    return menu;
  }
}
