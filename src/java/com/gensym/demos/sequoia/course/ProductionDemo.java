/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	ProductionDemo.java
 *
 */
package com.gensym.demos.sequoia.course;

import java.awt.event.WindowListener;
import java.util.Vector;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIStatusBar;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.shell.commands.SwitchConnectionCommand;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.TW2MDIWorkspaceShowingAdapter;
import com.gensym.shell.util.WorkspaceDocumentFactory;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.ui.Command;
import com.gensym.util.Symbol;
import javax.swing.JMenuBar;
import javax.swing.UIManager;

public class ProductionDemo extends TW2MDIApplication implements ContextChangedListener {

  private static Resource shortBundle = Resource.getBundle("com/gensym/demos/sequoia/course/Messages");

  private static final String DEVELOPER = "Developer";

  private MDIFrame demoFrame = null;
  private ConnectionManager connectionManager = null;

  private MDIStatusBar statusBar = null;
  private MDIToolBarPanel toolBarPanel = null;
  private CMenuBar menuBar = null;
  
  // commands written specifically for ProductionDemo
  private DemoWorkspaceCommands demoWorkspaceHandler;
  private ViewCommands viewHandler;
  private ProductionCommands productionHandler;
  private ModeCommands modeHandler;
  private Command helpHandler;

  // commands used from com.gensym.shell.commands
  private SwitchConnectionCommand switchConnectionHandler;
  private ConnectionCommands connectionHandler;
  private WorkspaceCommands workspaceHandler;  
  private ExitCommands exitHandler;

  // WorkspaceDocumentFactory is responsible for creating the correct
  // subclass of WorkspaceDocument for the application
  private WorkspaceDocumentFactory demoWkspDocFactory;
 
  public ProductionDemo(String[] cmdLineArgs){
    /*
     * By calling super(cmdLineArgs) we do the following:
     *
     * 1. let TW2MDIApplication parse for the following
     * command line arguments:
     *
     *  -url, -host, -port
     *
     * 2. let UIApplication parse for the following
     * command line arguments:
     *
     *   -title, -geometry
     *
     * 3. let GensymApplication deal with the following 
     * command line arguments:
     *
     *   -development, -tracekeys, -messages, -tracelevel,
     *   -traceon, -debug, -language, -country, -variant
     */
    super(cmdLineArgs);

    /*
     * Create the Production Demo application frame and components
     */
    createProductionDemo();
  }

  private void createProductionDemo () {
    /*
     * create the frame
     */
    demoFrame = createFrame(shortBundle.getString("ProductionDemoTitle"));

    /* 
     * set the frame in UiApplication 
     */
    setCurrentFrame(demoFrame);

    /*
     * create the connectionManager and have it listen to changes
     * to connetions registered with the connectonManager
     */
    connectionManager = new ConnectionManager();
    connectionManager.addContextChangedListener(this);

    /*
     * Create the MenuBar, ToolBar, and StatusBar
     */
    createUiComponents();

    /*
     * register the WorkspaceDocumentFactory for Telewindows2
     */
    registerWkspDocFactory();   

    /*
     * register frame with the dialog manager and launcher
     */
    com.gensym.dlgruntime.DialogManager.registerFrame (demoFrame);
    com.gensym.dlgruntime.DefaultDialogLauncher.registerFrame(demoFrame);
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
  }

  private void createUiComponents() {
    demoFrame.setStatusBar(statusBar = createStatusBar());
    demoFrame.setDefaultMenuBar(menuBar = createMenuBar());
    demoFrame.setDefaultToolBarPanel(toolBarPanel = createToolBarPanel());
  }

  private MDIFrame createFrame(String title) {
    return new MDIFrame(title);
  }

  private MDIStatusBar createStatusBar() {
    MDIStatusBar sb = new MDIStatusBar();
    return sb;
  }

  protected CMenuBar createMenuBar() {
    CMenuBar mb = new CMenuBar();

    mb.add(createFileMenu());
    mb.add(createViewMenu());
    mb.add(createProductionMenu());
    mb.add(createModeMenu());
    mb.add(createConnectMenu());   
    mb.add(createHelpMenu());
    
    return mb;
  }

  private CMenu createFileMenu() {
    CMenu menu = new CMenu (shortBundle.getString("FileMenu"));

    if (demoWorkspaceHandler == null)
      demoWorkspaceHandler = new DemoWorkspaceCommands(demoFrame, 
						       connectionManager);

    if (workspaceHandler == null)
      workspaceHandler = new WorkspaceCommands(demoFrame,
					       connectionManager);    

    if (exitHandler == null)
      exitHandler = new ExitCommands(demoFrame, connectionManager);

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

  private CMenu createViewMenu() {
    CMenu menu = new CMenu (shortBundle.getString("ViewMenu"));
    if (viewHandler == null) 
      viewHandler = new ViewCommands(demoFrame, connectionManager);
    menu.add(viewHandler);
    return menu;
  }

  private CMenu createProductionMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ProductionMenu"));
    if (productionHandler == null) 
      productionHandler = new ProductionCommands(demoFrame, 
						 connectionManager);
    menu.add(productionHandler);
    return menu;
  }

  private CMenu createModeMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ModeMenu"));
    if (modeHandler == null) 
      modeHandler = new ModeCommands(connectionManager);
    menu.add(modeHandler);
    return menu;
  }

  private CMenu createConnectMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ConnectMenu"));
    if (switchConnectionHandler == null)
      switchConnectionHandler = new SwitchConnectionCommand(connectionManager);
    if (connectionHandler == null)
      connectionHandler = new ConnectionCommands(this);
    menu.add(switchConnectionHandler);
    menu.add(connectionHandler);
    return menu;
  }

  protected CMenu createHelpMenu() {
    CMenu menu = new CMenu(shortBundle.getString("HelpMenu"));
    if (helpHandler == null) 
      helpHandler = new HelpCommands(demoFrame);
    menu.add(helpHandler);
    return menu;
  }

  private MDIToolBarPanel createToolBarPanel() {
    MDIToolBarPanel panel = new MDIToolBarPanel();
    ToolBar tb = new ToolBar();
    addWorkspaceToolBarButtons(tb);
    tb.addSeparator();
    addConnectionToolBarButtons(tb);
    panel.add(tb);
    return panel;
  }

  private void addWorkspaceToolBarButtons(ToolBar toolBar) {
    if (workspaceHandler == null)
      workspaceHandler = new WorkspaceCommands(demoFrame, connectionManager);
    toolBar.add(workspaceHandler, "GetKbWorkspace");
  }

  private void addConnectionToolBarButtons(ToolBar toolBar) {
    if (connectionHandler == null) 
      connectionHandler = new ConnectionCommands(this);
    toolBar.add(connectionHandler, "TwConnect");
    toolBar.add(connectionHandler, "TwDisconnect");
  }

  /*
   * Register the DemoWorkspaceDocumentFactory with all commands that add 
   * WorkspaceDocuments to the MDIFrame.
   */
  private void registerWkspDocFactory() {
    demoWkspDocFactory = new DemoWorkspaceDocumentFactoryImpl();
    if (workspaceHandler != null)
      workspaceHandler.setWorkspaceDocumentFactory(demoWkspDocFactory);
  }

  // BEGIN: ContextChangedListener Methods
  @Override
  public void currentConnectionChanged(ContextChangedEvent e) {
    TwAccess connection = e.getConnection();
    if (connection == null) 
      statusBar.setStatus(shortBundle.getString("NoConnection"));
    else 
      statusBar.setStatus(connection.toShortString());
  }

  //create and show an error dialog
  private void displayError(String title, String msg) {
    ErrorDialog dlg = new ErrorDialog (demoFrame, title, true, msg, 
				      (StandardDialogClient) null);
    dlg.show();
  }

  /**
   * @param cmdLineArgs is a String array that consists of command line
   * arguments for ProductionDemo
   */
  public static void main(String[] cmdLineArgs) {
    /*
     * main is where behaviour of the application is imposed upon
     * instances of the class. Users that wish to changed the default
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
    ProductionDemo application  = new ProductionDemo(cmdLineArgs);

    /*
     * Command line arguments were handled by the superior classes of this
     * class. This is where THIS class will handle the results of processing
     * the command line args.
     */

    /*
     * check to see if -title and/or -geometry command line args 
     * were processed by UiApplication. If they were, then use 
     * the command line information for setting up the frame.
     */
    String title = getTitleInformation();
    if (title != null)
      application.demoFrame.setTitle(title);

    String geometry = getGeometryInformation();
    if (geometry != null)
      setBoundsForFrame(application.demoFrame, geometry);

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
	ConnectionManager connectionMgr = application.getConnectionManager();
	connectionMgr.openConnection(connectionInfo.getBrokerURL(),
				     connectionInfo.getHostName(),
				     connectionInfo.getPortName());
	LoginRequest loginRequest = getLoginRequest();
	if (loginRequest != null){
	  TwAccess connection = connectionMgr.getCurrentConnection();
	  if (connection != null)
	    connection.loginSession(loginRequest);
	}
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
     * and hide actions in G2
     */
    try{
      WorkspaceShowingListener workspaceShowingListener = new TW2MDIWorkspaceShowingAdapter(application.connectionManager);
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
    }

    /*
     * Make the frame visible!
     */
    application.demoFrame.setVisible(true);
  }
}
