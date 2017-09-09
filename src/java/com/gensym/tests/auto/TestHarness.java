/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TestHarness.java
 *
 */
package com.gensym.tests.auto;

import java.awt.Dimension;
import java.awt.event.WindowListener;
import com.gensym.demos.standarddialogs.DlgCommand;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIStatusBar;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.TW2MDIWorkspaceShowingAdapter;
import com.gensym.tests.auto.ntw.TwAccessTestCommand;
import com.gensym.tests.auto.wksp.WorkspaceViewTestCommand;
import com.gensym.ui.Command;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.message.Trace;
import javax.swing.UIManager;

public class TestHarness extends TW2MDIApplication implements ContextChangedListener {
  private static TestHarness testHarness = null;

  private MDIFrame frame;

  private CMenuBar menuBar;
  private MDIToolBarPanel  toolBarPanel;
  private MDIStatusBar statusBar;

  private ConnectionManager connectionManager;

  private Command connectionHandler, exitHandler;
  private Command twAccessTestHandler, 
                  wkspViewTestHandler, 
                  dlgCommandTestHandler;
  private Command logWindowHandler;

  private LogWindow logWindow;

  public TestHarness (String[] cmdLineArgs){
    super(cmdLineArgs);
    createTestHarness();
  }

  private void createTestHarness() {
    // create the frame
    frame = createFrame("Sequoia Test Harness");

    // set the frame in UiApplication 
    setCurrentFrame(frame);

    // create the connectionManager and have it listen to changes
    // to connetions registered with the connectonManager
    connectionManager = new ConnectionManager();
    connectionManager.addContextChangedListener(this);

    logWindow = new LogWindow();

    // Create the MenuBar, ToolBar, and StatusBar
    createUiComponents();

    // register frame with StandardDialog in case we dont have 
    // access to it
    StandardDialog.registerFrame(frame);

    // register frame with the dialog manager and launcher
    com.gensym.dlgruntime.DialogManager.registerFrame(frame);
    com.gensym.dlgruntime.DefaultDialogLauncher.registerFrame(frame);
  }

  @Override
  public ConnectionManager getConnectionManager(){
    return connectionManager;
  }

  @Override
  public TwAccess getConnection(){
    return null;
  }

  @Override
  public void setConnection(TwAccess connection){}

  private void createUiComponents() {
    frame.setStatusBar(statusBar = createStatusBar());
    frame.setDefaultMenuBar(menuBar = createMenuBar(), null);
    frame.setDefaultToolBarPanel(toolBarPanel = createToolBarPanel());
  }

  private MDIFrame createFrame(String title) {
    MDIFrame frame =  new MDIFrame(title);
    return frame;
  }

  public MDIFrame getFrame() {
    return frame;
  }

  private CMenuBar createMenuBar() {
    CMenuBar mb = new CMenuBar(); 
    mb.add(createFileMenu());
    mb.add(createG2Menu()); 
    mb.add(createTestMenu());
    mb.add(createHelpMenu()); 
    return mb;
  }

  public MDIToolBarPanel createToolBarPanel(){
    MDIToolBarPanel panel = new MDIToolBarPanel();
    ToolBar tb = new ToolBar();
    if (connectionHandler == null)
      connectionHandler = new ConnectionCommands(this);
    tb.add(connectionHandler, "TwConnect");
    panel.add(tb);
    return panel;
  }

  private MDIStatusBar createStatusBar() {
    MDIStatusBar sb = new MDIStatusBar();
    return sb;
  }

  private CMenu createFileMenu() {
    CMenu menu = new CMenu("File");
    if (exitHandler == null)
      exitHandler = new ExitCommands(frame, connectionManager);
    menu.add(exitHandler);
    return menu;
  }

  private CMenu createG2Menu() {
    CMenu menu = new CMenu("G2");
    if (connectionHandler == null)
      connectionHandler = new ConnectionCommands(this);
    menu.add(connectionHandler, "TwConnect");
    return menu;
  }

  private CMenu createTestMenu() {
    CMenu menu = new CMenu("Test");

    if (wkspViewTestHandler == null)
      wkspViewTestHandler =  new WorkspaceViewTestCommand(this,
							  connectionManager);
    menu.add(wkspViewTestHandler);
    menu.addSeparator();

    if (twAccessTestHandler == null)
      twAccessTestHandler =  new TwAccessTestCommand(this, 
						     logWindow, 
						     connectionManager);
    menu.add(twAccessTestHandler);
    menu.addSeparator();

    if (dlgCommandTestHandler == null)
      dlgCommandTestHandler = new DlgCommand(frame);
    menu.add(dlgCommandTestHandler);
    return menu;
  }

  private CMenu createWindowMenu() {
    CMenu menu = new CMenu("Window");
    if (logWindowHandler == null)
      logWindowHandler = new LogWindowCommand(logWindow);
    menu.add(logWindowHandler);
    return (menu);
  }

  private CMenu createHelpMenu() {
    CMenu menu = new CMenu("Help");
    return (menu);
  }

  // BEGIN: ContextChangedListener Methods
  @Override
  public void currentConnectionChanged(ContextChangedEvent e){
    TwAccess connection = e.getConnection();
    if (connection == null) statusBar.setStatus("no connection");
    else statusBar.setStatus(connection.toShortString());
  }
  // END: ContextChangedListener Methods

  public static void main(String[] cmdLineArgs){
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }

    TestHarness application = new TestHarness(cmdLineArgs);

    String title = getTitleInformation();
    if (title != null)
      application.frame.setTitle(title);

    String geometry = getGeometryInformation();
    if (geometry != null)
      setBoundsForFrame(application.frame, geometry);

try {
      TwConnectionInfo connectionInfo = getG2ConnectionInformation();
      if (connectionInfo != null) {
	ConnectionManager connectionMgr = application.getConnectionManager();
	connectionMgr.openConnection(connectionInfo.getBrokerURL(),
				     connectionInfo.getHostName(),
				     connectionInfo.getPortName());
      } 
    }
    catch (ConnectionTimedOutException e) {
      Trace.exception (e);
    }
    catch (G2AccessInitiationException e) {
      Trace.exception (e);
    }
    catch (G2AccessException e) {
      Trace.exception (e);
    }

    /*
     * create a workspace showing listener to respond to show 
     * and hide (programmatic) actions in G2
     */
    try {
      WorkspaceShowingListener workspaceShowingListener = new TW2MDIWorkspaceShowingAdapter(application.connectionManager);
    }
    catch(G2AccessException ex) {
      Trace.exception(ex);
    }

    application.frame.setVisible(true);
  }
}
