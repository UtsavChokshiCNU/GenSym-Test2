/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DemoWorkspaceDocument.java
 *
 */
package com.gensym.demos.sequoia.course;

import com.gensym.classes.KbWorkspace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.mdi.MDIApplication;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.core.UiApplication;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.ui.Command;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.jgi.G2AccessException;

public class DemoWorkspaceDocument extends WorkspaceDocument {

  private static Resource shortBundle = Resource.getBundle("com/gensym/demos/sequoia/course/Messages");

  private static MDIFrame frame = (MDIFrame)MDIApplication.getCurrentFrame();
  private static CMenuBar menuBar = createMenuBar();
  private static CMenu windowMenu;

  private static DemoWorkspaceCommands demoWorkspaceHandler;
  private static ViewCommands viewHandler;
  private static ProductionCommands productionHandler;
  private static ModeCommands modeHandler;
  private static HelpCommands helpHandler;
  
  // commands used from com.gensym.shell.commands
  private static ConnectionCommands connectionHandler;
  private static WorkspaceCommands workspaceHandler;
  private static ExitCommands exitHandler;

  private static boolean alreadySetupConnectionCmds = false;
  private static boolean alreadySetupWorkspaceDocumentFactory = false;

  private static WorkspaceDocumentFactory factory = new DemoWorkspaceDocumentFactoryImpl();
 
  public DemoWorkspaceDocument(TwAccess connection, KbWorkspace wksp) throws G2AccessException {
    super(connection, wksp, menuBar, windowMenu, frame.getDefaultToolBarPanel());
   
    if ((getConnectionManager() == null) && (!alreadySetupConnectionCmds)) {
      alreadySetupConnectionCmds = true;
      workspaceHandler.setConnection(connection);
      exitHandler.setConnection(connection);

      demoWorkspaceHandler.setConnection(connection);
      //viewHandler.setConnection(connection);
      //productionHandler.setConnection(connection);
      //modeHandler.setConnection(connection);
    }

    if (!alreadySetupWorkspaceDocumentFactory) {
      alreadySetupWorkspaceDocumentFactory = true;
      demoWorkspaceHandler.setWorkspaceDocumentFactory(factory);
      workspaceHandler.setWorkspaceDocumentFactory(factory);
    }
  }

  private static CMenuBar createMenuBar(){
    menuBar = new CMenuBar();
    menuBar.add(createFileMenu());
    menuBar.add(createViewMenu());
    menuBar.add(createProductionMenu());
    menuBar.add(createModeMenu());
    menuBar.add(createConnectMenu());
    menuBar.add(createWindowMenu());
    menuBar.add(createHelpMenu());
    return menuBar;
  }

  private static CMenu createFileMenu() {
    CMenu menu = new CMenu (shortBundle.getString("FileMenu"));

    if (demoWorkspaceHandler == null)
      demoWorkspaceHandler = new DemoWorkspaceCommands(frame, 
						       getConnectionManager());

    if (workspaceHandler == null)
      workspaceHandler = new WorkspaceCommands(frame,
					       getConnectionManager());    

    if (exitHandler == null)
      exitHandler = new ExitCommands(frame, getConnectionManager());

    menu.add(workspaceHandler, "GetKbWorkspace");
    menu.add(demoWorkspaceHandler, "NewKbWorkspace");
    menu.add(demoWorkspaceHandler, "DeleteKbWorkspace");

    //only add Get Workspace in developer mode
    /*DOESN'T WORK
    try {
      Symbol developer = Symbol.intern ("developer");
      if (((TwGateway)connectionManager.getCurrentConnection()).getUserMode() == developer)
	menu.add(workspaceHandler, "GetKbWorkspace");

    } catch (G2AccessException ex){
      displayError("", ex.getMessage());
    }
    */

    menu.addSeparator();
    menu.add(exitHandler);
    return menu;
  }

  private static CMenu createViewMenu() {
    CMenu menu = new CMenu (shortBundle.getString("ViewMenu"));
    if (viewHandler == null) 
      viewHandler = new ViewCommands(frame, getConnectionManager());
    menu.add(viewHandler);
    return menu;
  }

  private static CMenu createProductionMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ProductionMenu"));
    if (productionHandler == null) 
      productionHandler = new ProductionCommands(frame, 
						 getConnectionManager());
    menu.add(productionHandler);
    return menu;
  }

  private static CMenu createModeMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ModeMenu"));
    if (modeHandler == null) 
      modeHandler = new ModeCommands(getConnectionManager());
    menu.add(modeHandler);
    return menu;
  }

  private static CMenu createConnectMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ConnectMenu"));
    if (connectionHandler == null) 
      connectionHandler = new ConnectionCommands((com.gensym.shell.util.TW2MDIApplication)UiApplication.getApplication());
    menu.add(connectionHandler);
    return menu;
  }

  protected static CMenu createHelpMenu() {
    CMenu menu = new CMenu(shortBundle.getString("HelpMenu"));
    if (helpHandler == null) 
      helpHandler = new HelpCommands(frame);
    menu.add(helpHandler);
    return menu;
  }
 
  private static CMenu createWindowMenu(){
    windowMenu = new CMenu(shortBundle.getString("WindowMenu"));
    windowMenu.add(frame.getManager().getTilingCommand());
    return windowMenu;
  }
}
