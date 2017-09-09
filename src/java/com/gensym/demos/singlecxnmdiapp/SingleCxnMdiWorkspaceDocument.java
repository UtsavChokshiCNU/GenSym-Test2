/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SingleCxnMdiWorkspaceDocument.java
 *
 */
package com.gensym.demos.singlecxnmdiapp;

import com.gensym.classes.KbWorkspace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.mdi.MDIApplication;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.core.UiApplication;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.ui.Command;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import javax.swing.SwingConstants;

public class SingleCxnMdiWorkspaceDocument extends WorkspaceDocument {

  private static Resource shortBundle = Resource.getBundle("com/gensym/demos/singlecxnmdiapp/Messages");

  private static RepresentationConstraints menuConstraints = 
                      new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
						    SwingConstants.LEFT, 
						    SwingConstants.CENTER, 
						    SwingConstants.RIGHT, 
						    SwingConstants.CENTER);

  private static MDIFrame frame = (MDIFrame)MDIApplication.getCurrentFrame();
  private static CMenuBar menuBar = createMenuBar();

  private static CMenu windowMenu;
  
  private static TwAccess currentConnection;

  private static boolean alreadySetupConnectionCmds = false;

  private static WorkspaceDocumentFactory factory = new SingleCxnMdiWorkspaceDocumentFactoryImpl();
  private static boolean alreadySetupWorkspaceDocumentFactory = false;

  /**
   * Creates a SingleCxnMdiWorkspaceDocument for the specified connection 
   * and kbworkspace.<p>
   *  The menu bar associated with this document is the 
   * same as the menu bar in SingleConnectionApplication  with the addition
   * of 2 menus: Workspace and Window.<p>
   * The toolbar panel associated with this document is the MDIFrame's default 
   * toolbar panel.
   */
  public SingleCxnMdiWorkspaceDocument(TwAccess connection, KbWorkspace wksp) throws G2AccessException{
    super(connection, wksp, menuBar, windowMenu, frame.getDefaultToolBarPanel());
    currentConnection = connection;
  }

  private static CMenuBar createMenuBar(){
    menuBar = new CMenuBar();
    menuBar.add(createFileMenu());
    menuBar.add(createItemMenu());
    menuBar.add(createViewMenu());
    menuBar.add(createG2Menu());
    menuBar.add(createWindowMenu());
    menuBar.add(createHelpMenu());
    return menuBar;
  }

  private static CMenu createFileMenu() {
    CMenu menu = new CMenu (shortBundle.getString("FileMenu"));
    SingleConnectionApplication app =
      (SingleConnectionApplication)UiApplication.getApplication();
    menu.add(app.wkspHandler, menuConstraints);
    menu.addSeparator();
    menu.add(app.exitHandler);
    return menu;
  }

  private static CMenu createItemMenu(){
    CMenu menu = new CMenu (shortBundle.getString("ItemMenu"));
    menu.add(new ItemCommands(frame));
    return menu;
  }
  
  private static CMenu createViewMenu(){
    CMenu menu = new CMenu("View");//i18n
    menu.add(((SingleConnectionApplication)UiApplication.getApplication()).viewHandler);
    return menu;
  }

  private static CMenu createG2Menu() {
    CMenu menu = new CMenu(shortBundle.getString("G2Menu")); 
    menu.add(new ConnectionCommands((TW2MDIApplication)UiApplication.getApplication()),
	     menuConstraints);
    return menu;
  }

  private static CMenu createWindowMenu(){
    windowMenu = new CMenu(shortBundle.getString("WindowMenu"));
    windowMenu.add(frame.getManager().getTilingCommand());
    return windowMenu;
  }

  private static CMenu createHelpMenu() {
    CMenu menu = new CMenu(shortBundle.getString("HelpMenu"));
    menu.add(new HelpCommands(frame));
    return menu;
  }
}
