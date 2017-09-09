/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BShell.java
 *
 */
package com.gensym.uitools.browsers;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Image;
import java.awt.Toolkit;

import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIStatusBar;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.SwitchConnectionCommand;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.uitools.commands.BrowserCommands;
import com.gensym.ntw.util.uitools.CustomPalettePanel;
import com.gensym.util.Symbol;

import javax.swing.JSplitPane;
import javax.swing.SwingConstants;
import javax.swing.UIManager;

public class BShell extends TW2MDIApplication implements ContextChangedListener {

  private MDIFrame frame;
  private ConnectionManager connectionManager;
  private TwAccess cxn;

  private MDIStatusBar statusBar;
  private MDIToolBarPanel toolBarPanel;
  private CMenuBar menuBar;
  private RepresentationConstraints menuConstraints = 
                             new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
							   SwingConstants.LEFT, 
							   SwingConstants.CENTER, 
							   SwingConstants.RIGHT, 
							   SwingConstants.CENTER);

  private CustomPalettePanel paletteToolBar;

  private Symbol userMode;
  private ShellModeListener modeListener = new ShellModeListener();

  ConnectionCommands connectionHandler;
  SwitchConnectionCommand switchConnectionHandler;
  BrowserCommands browserHandler;

  public BShell (String[] cmdLineArgs) {
    super(cmdLineArgs);
    createBShell();
  }

  private void createBShell() {
    frame = createFrame("Browser Test Application");
    setCurrentFrame(frame);
    connectionManager = new ConnectionManager();
    connectionManager.addContextChangedListener(this);
    setConnection(connectionManager.getCurrentConnection());
    createUiComponents();
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
  public void setConnection(TwAccess connection){
    cxn = connection;
  }

  private void createUiComponents() {
    frame.setStatusBar(statusBar = createStatusBar());
    frame.setDefaultMenuBar(menuBar = createMenuBar());
    frame.setDefaultToolBarPanel(toolBarPanel = createToolBarPanel()); 

    Container contentPane = frame.getContentPane();
    MDIManager mdiManager = frame.getManager();
    contentPane.remove(mdiManager);

    paletteToolBar = new CustomPalettePanel(cxn);

    JSplitPane splitter = new JSplitPane(JSplitPane.VERTICAL_SPLIT, false, mdiManager, paletteToolBar);
    contentPane.add(splitter, BorderLayout.CENTER);
  }

  private MDIFrame createFrame(String title) {
    MDIFrame frame = new MDIFrame(title);

    // set the logo to be the Gensym logo
    Image image = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("gensym_logo.gif"));
    if (image != null)
      frame.setIconImage(image);
    return frame;
  }

  private CMenuBar createMenuBar() {
    CMenuBar mb = new CMenuBar(); 
    mb.add(createFileMenu());
    mb.add(createG2Menu());
    return mb;
  }

  private MDIToolBarPanel createToolBarPanel() {
    MDIToolBarPanel panel = new MDIToolBarPanel();
    ToolBar tb = new ToolBar();
    tb.add(connectionHandler);
    panel.add(tb);
    return panel;
  }

  private MDIStatusBar createStatusBar() {
    MDIStatusBar sb = new MDIStatusBar();
    return sb;
  }

  private CMenu createFileMenu() {
    CMenu menu = new CMenu ("TW2");
    menu.add(new ExitCommands(frame, connectionManager), menuConstraints);
    return menu;
  }

  private CMenu createG2Menu() {
    CMenu menu = new CMenu("G2"); 
    switchConnectionHandler = new SwitchConnectionCommand(connectionManager);
    menu.add(switchConnectionHandler);
    connectionHandler = new ConnectionCommands(this); 
    menu.add(connectionHandler, menuConstraints);
    menu.addSeparator();
    browserHandler = new BrowserCommands(connectionManager.getCurrentConnection());
    menu.add(browserHandler);
    return menu;
  }

  // BEGIN: ContextChangedListener Methods
  @Override
  public void currentConnectionChanged(ContextChangedEvent e) {
    TwAccess connection = e.getConnection();
    if (connection == null) {
      setStatusBarStatus("no connection", null);
      browserHandler.setConnection(connection);
      paletteToolBar.setConnection(connection);
    }
    else {
      if (e.isConnectionNew()) {
	connection.addTwConnectionListener(modeListener);
	browserHandler.setConnection(connection);
	paletteToolBar.setConnection(connection);
      }
      if (connection.isLoggedIn()) {
	try {
	  userMode = connection.getUserMode();
	  setStatusBarStatus(connection.toShortString(), userMode);
	} catch (G2AccessException ex) {
	  Trace.exception(ex);
	}
      } else {
	// not logged in yet
	setStatusBarStatus(connection.toShortString(), null);
      }
    }

    setConnection(connection);
  }
  // END: ContextChangedListener Methods

  private void setStatusBarStatus(String connection, Symbol mode) {
    String status = connection;
    if (mode != null)
     status = status + "  " + mode.toString().toLowerCase();
    statusBar.setStatus(status);
  }

  class ShellModeListener extends TwConnectionAdapter {
    @Override
    public void loggedIn (TwConnectionEvent e) {
      userMode = e.getUserMode ();
      TwAccess connection = (TwAccess) e.getSource ();
      setStatusBarStatus(connection.toShortString(), userMode);
    }
   
    @Override
    public void userModeChanged (TwConnectionEvent e) {
      userMode = e.getUserMode ();
      TwAccess connection = (TwAccess) e.getSource ();
      TwAccess currentCxn = connectionManager.getCurrentConnection();
      if (connection != null && currentCxn != null && connection == currentCxn) {
	setStatusBarStatus(connection.toShortString(), userMode);
      } 
    }
  }

  public static void main(String[] cmdLineArgs) {
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }

    BShell application = new BShell(cmdLineArgs);

    String title = getTitleInformation();
    if (title != null)
      application.frame.setTitle(title);

    String geometry = getGeometryInformation();
    if (geometry != null)
      setBoundsForFrame(application.frame, geometry);

    application.frame.setVisible(true);
  }
}


