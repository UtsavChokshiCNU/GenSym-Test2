/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SingleConnectionApplication.java
 *
 *   This demo demonstrates the basics of how to build a single
 *   connection, multiple document interface, application shell
 *   that connects to a single G2. It allows the user to open
 *   and close connections, get a named workspace or create a new
 *   workspace, and then to enable or disable items on workspaces.
 *
 */
package com.gensym.demos.singlecxnmdiapp;

import com.gensym.dlg.StandardDialog;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIStatusBar;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ntw.LoginFailedException;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.TW2MDIWorkspaceShowingAdapter;
import com.gensym.shell.util.UserModePanel;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.ui.Command;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.util.Symbol;

import javax.swing.SwingConstants;
import javax.swing.UIManager;

public class SingleConnectionApplication extends TW2MDIApplication {

  private static Resource shortBundle = Resource.getBundle("com/gensym/demos/singlecxnmdiapp/Messages");

  private MDIFrame appFrame;
  private TwAccess currentConnection;

  private MDIStatusBar statusBar;
  private MDIToolBarPanel toolBarPanel;
  private CMenuBar menuBar;
  private UserModePanel userModeInfo;

  private Symbol userMode = null;

  private RepresentationConstraints menuConstraints = 
                                 new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
							       SwingConstants.LEFT, 
							       SwingConstants.CENTER, 
							       SwingConstants.RIGHT, 
							       SwingConstants.CENTER);

  // com.gensym.shell.commands Commands
  ExitCommands exitHandler;
  WorkspaceCommands wkspHandler;
  private ConnectionCommands connectionHandler;

  ViewCommands viewHandler;

  // WorkspaceDocumentFactory is responsible for creating the correct
  // subclass of WorkspaceDocument for the application
  private WorkspaceDocumentFactory singleCxnMdiWkspDocFactory;

  public SingleConnectionApplication (String[] cmdLineArgs) {
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
     * 3. let GensymApplication parse and handle the
     * following command line arguments:
     *
     *   -development, -tracekeys, -messages, -tracelevel,
     *   -traceon, -debug, -language, -country, -variant
     */
    super(cmdLineArgs);

    /*
     * Create the SingleConnectionApplication container
     */
    createSingleConnectionApplication();
  }

  private void createSingleConnectionApplication() {
    /*
     * create the frame, getting the title from the resource
     */
    appFrame = createFrame(shortBundle.getString("Title"));

    /* 
     * set the frame in UiApplication so that it is accessible
     * via getCurrentFrame() for other components associated with
     * this application
     */
    setCurrentFrame(appFrame);

    /*
     * Create the MenuBar, ToolBar, and StatusBar
     */
    createUiComponents();

    /*
     * register the WorkspaceDocumentFactory for this application
     */
    registerWkspDocFactory();   
  }

  /*
   * Since SingleConnectionApplication is a single connection
   * application, it does not use the ConnectionManager, it 
   * does not implement the getConnectionManager() method.
   */
  @Override
  public ConnectionManager getConnectionManager(){
    return null;
  }

  /*
   * Since SingleConnectionApplication is a single connection
   * application, it implements the getConnection() menthod.
   */
  @Override
  public TwAccess getConnection() {
    return currentConnection;
  }

  /*
   * setConnection should be called whenever the connection
   * status changes. Commands that effect connection status should
   * call this method with the current connection, or null in the
   * event that there is not a current connection.
   */
  @Override
  public void setConnection(TwAccess connection){
    setCurrentConnection(connection);
  }
  
  protected void setCurrentConnection(TwAccess connection) {
    currentConnection = connection;

    // update the status bar with connection information
    if (connection == null) 
      setStatusBarStatus(shortBundle.getString("NoConnection"), null);
    else {
      connection.addTwConnectionListener(new ModeListener());
      try {
	userMode = connection.getUserMode();
	setStatusBarStatus(connection.toShortString(), userMode);
      } catch (G2AccessException ex) {
	Trace.exception(ex);	
      }
    }

    // update all commands with new connection or null
    if (wkspHandler != null)
      wkspHandler.setConnection(connection);
    if (exitHandler != null)
      exitHandler.setConnection(connection);
    if (connectionHandler != null)
      connectionHandler.setConnection(connection);
    if (viewHandler != null)
      viewHandler.setConnection(connection);

    // update the UserModePanel with new connection or null
    if (userModeInfo != null) {
      try {
	userModeInfo.setConnection((TwConnection)connection);
      } catch (G2AccessException ex) {
	Trace.exception(ex);
      }
    }

    if (connection != null) {
      /*
       * create a workspace showing listener to respond to show 
       * and hide (programmatic) actions in G2
       */
      try {
	WorkspaceShowingListener workspaceShowingListener = new TW2MDIWorkspaceShowingAdapter(currentConnection);
      }
      catch(G2AccessException ex) {
	Trace.exception(ex);
      }
    }
  }

  private void setStatusBarStatus(String connection, Symbol mode) {
    String status = connection;
    if (mode != null)
      status = status + "  " + mode.toString().toLowerCase();
    statusBar.setStatus(status);
  }

  private void createUiComponents() {
    appFrame.setStatusBar(statusBar = createStatusBar());
    appFrame.setDefaultMenuBar(menuBar = createMenuBar(), null);
    appFrame.setDefaultToolBarPanel(toolBarPanel = createToolBarPanel());
  }

  private MDIFrame createFrame(String title) {
    MDIFrame frame =  new MDIFrame(title);
    return frame;
  }

  private MDIStatusBar createStatusBar() {
    MDIStatusBar sb = new MDIStatusBar();
    return sb;
  }

  private MDIToolBarPanel createToolBarPanel() {
    MDIToolBarPanel panel = new MDIToolBarPanel();
    ToolBar tb = new ToolBar();
    tb.add(connectionHandler);
    tb.addSeparator();
    tb.add(wkspHandler);
    panel.add(tb);

    try {
      ToolBar tb2 = new ToolBar();
      tb2.add(userModeInfo = new UserModePanel((TwConnection)currentConnection,
					       true));
      panel.add(tb2);
    } catch (G2AccessException ex) {
      Trace.exception(ex);
    }

    return panel;
  }

  private CMenuBar createMenuBar() {
    CMenuBar mb = new CMenuBar(); 
    mb.add(createFileMenu());
    mb.add(createViewMenu());
    mb.add(createG2Menu());
    mb.add(createHelpMenu());  
    return mb;
  }

  private CMenu createFileMenu() {
    CMenu menu = new CMenu (shortBundle.getString("FileMenu"));
   
    wkspHandler = new WorkspaceCommands(appFrame, currentConnection);
    menu.add(wkspHandler, menuConstraints);
    exitHandler = new ExitCommands(appFrame, currentConnection);
    menu.addSeparator();
    menu.add(exitHandler);

    return menu;
  }

  private CMenu createViewMenu(){
    CMenu menu = new CMenu("View");//i18n
    viewHandler = new ViewCommands(this);
    menu.add(viewHandler);
    return menu;
  }

  private CMenu createG2Menu() {
    CMenu menu = new CMenu(shortBundle.getString("G2Menu")); 

    connectionHandler = new ConnectionCommands(this);
    menu.add(connectionHandler, menuConstraints);

    return menu;
  }

  private CMenu createHelpMenu() {
    CMenu menu = new CMenu(shortBundle.getString("HelpMenu"));
    menu.add(new HelpCommands(appFrame));
    return menu;
  }

  /*
   * Register the SingleCxnMdiWorkspaceDocumentFactory with all 
   * commands that add WorkspaceDocuments to the MDIFrame.
   */
  private void registerWkspDocFactory() {
    singleCxnMdiWkspDocFactory = new SingleCxnMdiWorkspaceDocumentFactoryImpl();
    wkspHandler.setWorkspaceDocumentFactory(singleCxnMdiWkspDocFactory);
  }

  /*
   * Listen for user mode changes and update UI
   */
  class ModeListener extends TwConnectionAdapter {
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
      setStatusBarStatus(connection.toShortString(), userMode);
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
     * In Swing 1.0.1 the default look and feel is there own,
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
    SingleConnectionApplication application = new SingleConnectionApplication(cmdLineArgs);

    /*
     * Command line arguments were handled by the superior classes 
     * of this class. This is where THIS class will handle the 
     * results of processing the command line args.
     */

    /*
     * check to see if -title and/or -geometry command line args 
     * were processed by UiApplication. If they were, then use 
     * the command line information for setting up the frame.
     */
    String title = getTitleInformation();
    if (title != null)
      application.appFrame.setTitle(title);

    String geometry = getGeometryInformation();
    if (geometry != null)
      setBoundsForFrame(application.appFrame, geometry);

    /*
     * check to see if -url, -host, and -port command line args
     * were processed by TW2MDIApplication. If they were, then use
     * the G2ConnectionInfo created by TW2MDIApplication to try to
     * open a connection. If the connection attempt fails, post a
     * dialog stating that the connection could not be opened.
     */
    try {
      TwConnectionInfo connectionInfo = getG2ConnectionInformation();
      if (connectionInfo != null) {
	application.connectionHandler.setPreviousConnectionInformation(connectionInfo);
	TwAccess connection = TwGateway.openConnection(connectionInfo.getHost(), connectionInfo.getPort());

	/*
	 * check to see if -userName, -mode, and -password command line args
	 * were processed by TW2MDIApplication. If they were, then use the
	 * LoginRequest created by TW2MDIApplication to try to login to the
	 * unlogged-in connection.
	 */
	LoginRequest loginRequest = getLoginRequest();
	if (loginRequest != null) {
	  application.connectionHandler.setPreviousLoginRequest(loginRequest);
	  connection.login(loginRequest);
	} else {
	  connection.login();
	}
	application.setCurrentConnection(connection);
      } 
    }
    catch (ConnectionTimedOutException e) {
      // G2 may need to be swapped back in, connection request timed out
      // before it could finish
      Trace.exception (e);
    }
    catch (G2AccessInitiationException e) {
      // There is no G2 to connect to at the specified host/port
      Trace.exception (e);
    }
    catch (LoginFailedException e) {
      // Connecting to a secure G2. login requires a LoginRequest with
      // a valid username/usermode/password combination
      Trace.exception (e);
    }
    catch (G2AccessException e) {
      Trace.exception (e);
    }

    /*
     * Make the frame visible!
     */
    application.appFrame.setVisible(true);
  }
}
