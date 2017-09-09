/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Shell.java
 *
 */
package com.gensym.ntw.test;

import java.awt.Image;
import java.awt.Toolkit;

import com.gensym.clscupgr.ModuleManager;
import com.gensym.clscupgr.ModuleHandlerFactoryAlreadyRegisteredException;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIStatusBar;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.util.VersionHelper;
import com.gensym.shell.commands.*;
import com.gensym.shell.util.*;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.util.Symbol;
                           
import javax.swing.SwingConstants;
import javax.swing.UIManager;

/**
 * Shell is an application frame that pulls together 
 * some of the components of the Telewindow2 1.0 release. It 
 * is composed of a MDIFrame with a title bar region, menubar 
 * region and work area region that manages document windows, 
 * otherwise known as MDIDocuments. <p>
 *
 * Menus (and toolbars) are generated from Commmands. Each Command 
 * consists of one or more task-specific event. In this release, 
 * Telewindows2 offers commands that generate menus and toolbar
 * buttons for the following high-level actions: <p>
 * <ul>
 * <li> File
 * <li> G2
 * <li> Help
 * </ul>
 * <p>
 * The File menu is built by combining actions from several different 
 * Commands: WorkspaceCommands, and ExitCommands. By being a listener 
 * for specific events, commands and the menu items and toolbar buttons 
 * generated from them, are enabled/disabled when appropriate. For more 
 * information on Commands, please refer to: com.gensym.ui.Command. <p>
 * 
 * Shell demonstrates Telewindows2's ability to allow users to connect to 
 * any number of G2s. Users can display workspaces from different G2s 
 * simultaneously.
 * 
 * @see com.gensym.ui.Command
 *
 * @see com.gensym.shell.commands.ConnectionCommands
 * @see com.gensym.shell.commands.SwitchConnectionCommands
 * @see com.gensym.shell.commands.CondensedG2StateCommands
 * @see com.gensym.shell.commands.ExitCommands
 * @see com.gensym.shell.commands.TraceCommands
 * @see com.gensym.shell.commands.WorkspaceCommands
 */
public class Shell extends TW2MDIApplication implements ContextChangedListener {

  // bind the message resource for Shell
  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/Messages");

  private MDIFrame frame;
  private ConnectionManager connectionManager;

  private MDIStatusBar statusBar;
  private MDIToolBarPanel toolBarPanel;
  private CMenuBar menuBar;
  private RepresentationConstraints menuConstraints = 
                             new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
							   SwingConstants.LEFT, 
							   SwingConstants.CENTER, 
							   SwingConstants.RIGHT, 
							   SwingConstants.CENTER);

  private Symbol userMode;
  private ShellModeListener modeListener = new ShellModeListener();
  private ShellLoginFailureHandler loginFailureHandler;

  // Handlers for the commands used for Shell's menu and toolbar
  ConnectionCommands connectionHandler;
  SwitchConnectionCommand switchConnectionHandler;
  CondensedG2StateCommands g2StateHandler;
  ExitCommands exitHandler;
  HelpCommands helpHandler;
  TraceCommands traceHandler;
  WorkspaceCommands wkspHandler;
  ZoomCommands zoomHandler;

  // WorkspaceDocumentFactory is responsible for creating the correct
  // subclass of WorkspaceDocument for the application
  private WorkspaceDocumentFactory shellWkspDocFactory;

  public Shell (String[] cmdLineArgs) {
    /*
     * By calling super(cmdLineArgs) we do the following:
     *
     * 1. let TW2MDIApplication parse for the following
     * command line arguments:
     *
     *  -url, -host, -port
     *
     * 2. let UiApplication parse for the following
     * command line arguments:
     *
     *   -title, -geometry
     *
     * 3. let GensymApplication parse and handle the following 
     * command line arguments:
     *
     *   -development, -tracekeys, -messages, -tracelevel,
     *   -traceon, -debug, -language, -country, -variant
     */
    super(cmdLineArgs);

    /*
     * Create the Shell container
     */
    createShell();
  }

  public void createShell() {
    /*
     * create the frame, getting the title from the message resource
     */
    frame = createFrame(shortBundle.getString("ShellTitle"));

    /* 
     * set the frame in UiApplication, so that other components
     * associated with this application can access it via the
     * getCurrentFrame() method
     */
    setCurrentFrame(frame);

    /*
     * create the connectionManager and have it listen to changes
     * to connections registered with the connectonManager
     */
    if (connectionManager == null) {
      connectionManager = new ConnectionManager();
      connectionManager.addContextChangedListener(this);
   }
    /*
     * create the MenuBar, ToolBar, and StatusBar
     */
    createUiComponents();

    /*
     * register the WorkspaceDocumentFactory for Shell
     */
    registerWorkspaceDocumentFactory();   
    
    /*
     * setup a login failure handler for handling command line login 
     * attempts that fail
     */
    loginFailureHandler = new ShellLoginFailureHandler();
  }

  /**
   * Gets the ConnectionManager for this application (Shell)
   *
   * @see com.gensym.shell.util.ConnectionManager
   */
  @Override
  public ConnectionManager getConnectionManager(){
    return connectionManager;
  }

  /**
   * Not implemented for Shell. Shell is a multiple connection 
   * application and uses the ConnectionManager. Users should 
   * use getConnectionManager() instead.
   */
  @Override
  public TwAccess getConnection(){
    return null;
  }

  /**
   * Not implemented for Shell. Shell is a multiple connection 
   * application and uses the Connection Manager.
   *
   * @see com.gensym.shell.util.ConnectionManager
   */
  @Override
  public void setConnection(TwAccess connection){}

  private void createUiComponents() {
    frame.setStatusBar(statusBar = createStatusBar());
    frame.setDefaultMenuBar(menuBar = createMenuBar());
    frame.setDefaultToolBarPanel(toolBarPanel = createToolBarPanel()); 
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
    if (VersionHelper.isUsingJava2D(this.getClass()))
      mb.add(createViewMenu());
    mb.add(createG2Menu()); 
    mb.add(createHelpMenu()); 
    return mb;
  }

  private MDIToolBarPanel createToolBarPanel() {
    MDIToolBarPanel panel = new MDIToolBarPanel();
  
    ToolBar tb = new ToolBar();
    tb.add(wkspHandler, WorkspaceCommands.GET_KBWORKSPACE);
    tb.addSeparator();
    tb.add(connectionHandler);
    tb.addSeparator();
    tb.add(g2StateHandler);
    tb.addSeparator();
    if (zoomHandler != null) {
      tb.add(zoomHandler, zoomHandler.ZOOM_IN);
      tb.add(zoomHandler, zoomHandler.ZOOM_OUT);
    }
    panel.add(tb);

    // add HostPortPanel for switching between existing connections
    ToolBar tb2 = new ToolBar ();
    try {
      tb2.add (new HostPortPanel(connectionManager));
      tb2.add (javax.swing.Box.createGlue());
    } catch (G2AccessException ex) {
      Trace.exception (ex);
    }

    // add UserModePanel for switching user mode of connection
    try {
      tb2.add (new UserModePanel(connectionManager, true));
    } catch (G2AccessException ex) {
      Trace.exception (ex);
    }

    panel.add(tb2);
    return panel;
  }

  private MDIStatusBar createStatusBar() {
    MDIStatusBar sb = new MDIStatusBar();
    return sb;
  }

  private CMenu createFileMenu() {
    CMenu menu = new CMenu (shortBundle.getString("ShellFileMenu"));
    menu.setMnemonic(shortBundle.getString("ShellFileMenuMnemonic").charAt(0));
    wkspHandler = new WorkspaceCommands(frame, connectionManager);
    menu.add(wkspHandler, WorkspaceCommands.GET_KBWORKSPACE, menuConstraints);
    exitHandler = new ExitCommands(frame, connectionManager);
    menu.addSeparator();
    menu.add(exitHandler, menuConstraints);
    return menu;
  }

  private CMenu createViewMenu() {
    CMenu menu = new CMenu (shortBundle.getString("ShellViewMenu"));
    menu.setMnemonic(shortBundle.getString("ShellViewMenuMnemonic").charAt(0));
    // WARNING: test this for version when there are more menu items. remove
    // test around call to createViewMenu
    zoomHandler = new ZoomCommands(frame);
    menu.add(zoomHandler, zoomHandler.ZOOM, menuConstraints);
    return menu;
  }

  private CMenu createG2Menu() {
    CMenu menu = new CMenu(shortBundle.getString("ShellG2Menu"));
    menu.setMnemonic(shortBundle.getString("ShellG2MenuMnemonic").charAt(0));
    switchConnectionHandler = new SwitchConnectionCommand(connectionManager);
    menu.add(switchConnectionHandler);
    connectionHandler = new ConnectionCommands(this);
    //connectionHandler = new ConnectionCommands(this, connectionManager);
     
    menu.add(connectionHandler, menuConstraints);
    g2StateHandler = new CondensedG2StateCommands(connectionManager);
    menu.addSeparator();
    menu.add(g2StateHandler, menuConstraints);
    return menu;
  }

  private CMenu createHelpMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ShellHelpMenu"));
    menu.setMnemonic(shortBundle.getString("ShellHelpMenuMnemonic").charAt(0));
    helpHandler = new HelpCommands(frame);
    menu.add(helpHandler);
    traceHandler = new TraceCommands(frame);
    menu.addSeparator();
    menu.add(traceHandler);
    return menu;
  }

  /*
   * Register the ShellWorkspaceDocumentFactory with all 
   * commands that add WorkspaceDocuments to the MDIFrame.
   */
  private void registerWorkspaceDocumentFactory() {
    shellWkspDocFactory = new ShellWorkspaceDocumentFactoryImpl();
    if (wkspHandler != null)
      ((WorkspaceCommands)wkspHandler).setWorkspaceDocumentFactory(shellWkspDocFactory);
  }


  // BEGIN: ContextChangedListener Methods
  /**
   * Sets the status bar with the current connection information.
   * Called whenever the current connection changes. ContextChangedEvents
   * occur whenever the current connection is closed, or a new connection
   * becomes the current connection. 
   *
   * @see com.gensym.util.ContextChangedListener
   * @see com.gensym.util.ContextChangedEvent
   */
  @Override
  public void currentConnectionChanged(ContextChangedEvent e) {
    TwAccess connection = e.getConnection();
    if (connection == null) 
      setStatusBarStatus(shortBundle.getString("ShellNoConnection"), null);
    else {
      if (e.isConnectionNew())
	connection.addTwConnectionListener(modeListener);
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

  public void setShellApplication(Shell application) {
    /*
     * check to see if -title and/or -geometry command line args
     * were processed by UiApplication. If they were, then use
     * the command line information for setting up the frame.
     */
    String title = getTitleInformation();
    if (title != null)
      application.frame.setTitle(title);

    String geometry = getGeometryInformation();
    if (geometry != null)
      setBoundsForFrame(application.frame, geometry);

    /*
     * check to see if -url, -host, and -port command line args
     * were processed by TW2MDIApplication. If they were, then use
     * the TwConnectionInfo created by TW2MDIApplication to try to
     * open a connection. If the connection attempt fails, post a
     * dialog stating that the connection could not be opened.
     */
    TwAccess unloggedInConnection = null;
    TW2MDIWorkspaceShowingAdapter workspaceShowingListener = null;
    try {
      ConnectionManager connectionMgr = application.getConnectionManager();
      TwConnectionInfo connectionInfo = getG2ConnectionInformation();
      /*
       * create a workspace showing listener to respond to show 
       * and hide (programmatic) actions in G2
       */
	    workspaceShowingListener =
	      new TW2MDIWorkspaceShowingAdapter(application.connectionManager);
      if (connectionInfo != null) {
	      // set connection information in the ConnectionCommands
	      application.connectionHandler.setPreviousConnectionInformation(connectionInfo);

	      connectionMgr.openConnection(connectionInfo);
	      LoginRequest loginRequest = getLoginRequest();
	      if (loginRequest != null){
	        // set login information in the ConnectionCommands
	        application.connectionHandler.setPreviousLoginRequest(loginRequest);

	        unloggedInConnection = connectionMgr.getCurrentConnection();
	        if (unloggedInConnection != null)
	         unloggedInConnection.login(loginRequest);
	      }
      }
      workspaceShowingListener.setWorkspaceDocumentFactory(application.shellWkspDocFactory);
    } catch (G2AccessException gae) {
      Trace.exception (gae);
      application.loginFailureHandler.handleLoginFailureException(gae,
								  unloggedInConnection);
    }

    // Set status bar if there is any connection  - FY 01/19/00
    if (connectionManager != null) {
        if (connectionManager.hasConnections()) {
            TwAccess connection = connectionManager.getCurrentConnection();
            String statusMsg = connection.toShortString();
            try {
                setStatusBarStatus(statusMsg, connection.getUserMode());
            } catch (G2AccessException ex) {
	            Trace.exception(ex);
	        }
        }
    }
    
    /*
     * Make the frame visible!
     */
    application.frame.setVisible(true);
  }

  //Clean up MDI frame, 
  public void dispose() {
    if (connectionManager.getCurrentConnection() != null) {
        (connectionManager.getCurrentConnection()).closeConnection();
    }    
  }     
     
  public static void main(String[] cmdLineArgs) {
    /*
     * main is where policy is imposed upon instances of 
     * the class. Users that wish to changed the default
     * behaviour, should extend the class and impose their own
     * behaviour in the main method of their own sub-class.
     */

    /*
     * This needs to be called BEFORE the constructor:
     * In Swing 1.0.1 the default look and feel is their own,
     * we want the standard Windows/Motif look and feel. This
     * sets it globally.
     */
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }

    /*
     * Create an instance of this class. 
     */
    Shell application = new Shell(cmdLineArgs);

    /*
     * Command line arguments were handled by the superior classes 
     * of this class. This is where THIS class will handle the 
     * results of processing the command line args.
     */

     //Set up Shell application
    application.setShellApplication(application);
  }
}


