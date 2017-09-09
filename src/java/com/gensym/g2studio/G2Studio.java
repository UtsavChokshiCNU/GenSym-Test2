/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Studio.java
 *
 */
package com.gensym.g2studio;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIStatusBar;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionInfo;import com.gensym.ntw.TwConnectionInfo;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.EditCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.ItemCommands;
import com.gensym.shell.commands.SwitchConnectionCommand;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.commands.WorkspaceInstanceCommands;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.HostPortPanel;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.TW2MDIWorkspaceShowingAdapter;
import com.gensym.shell.util.UserModePanel;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.Command;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.uitools.commands.BrowserCommands;
import com.gensym.shell.commands.*;
import com.gensym.ntw.util.uitools.CommandTabbedPane;
import com.gensym.ntw.util.uitools.CustomPalettePanel;
import com.gensym.ntw.util.uitools.LoginFailureHandler;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;

import javax.swing.Box;
import javax.swing.JDialog;
import javax.swing.JSplitPane;
import javax.swing.JMenuItem;
import javax.swing.SwingConstants;
import javax.swing.UIManager;

public class G2Studio extends TW2MDIApplication implements ContextChangedListener {

  private static Resource shortBundle = Resource.getBundle("com/gensym/g2studio/Messages");

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

  private CustomPalettePanel paletteTB;

  private Symbol userMode;
  private TW2ModeListener modeListener = new TW2ModeListener();
  private LoginFailureHandler loginFailureHandler;

  // uitools commands
  private AlignmentCommands alignmentHandler;
  private BrowserCommands browserHandler;
  private ModuleCommands  moduleHandler;
  private NudgeCommands nudgeHandler;
  private OrderCommands orderHandler;
  private ProjectCommands projectHandler;
  private RotateCommands rotateHandler;
  private SnapshotCommands snapshotHandler;
  private ViewCommands viewHandler;

  protected Command[] layoutCommands;
  protected CommandTabbedPane layoutToolBar;
  protected JDialog layoutTBDialog;

  // TW2 shell commands 
  private ConnectionCommands connectionHandler;
  private EditCommands editHandler;
  private ExitCommands exitHandler;
  private ItemCommands itemHandler;
  private WorkspaceInstanceCommands workspaceInstanceHandler;
 
  public G2Studio (String[] cmdLineArgs) {
    super(cmdLineArgs);
    createG2Studio();
  }

  private void createG2Studio() {
    setCurrentFrame(frame = createFrame(shortBundle.getString("G2StudioTitle")));
    connectionManager = new ConnectionManager();
    connectionManager.addContextChangedListener(this);
    createUiComponents();
    loginFailureHandler = new LoginFailureHandler();
  }

  @Override
  public ConnectionManager getConnectionManager(){
    return connectionManager;
  }

  // do not implement 
  @Override
  public TwAccess getConnection() {
    return null;
  }

  // do not implement
  @Override
  public void setConnection(TwAccess connection){}

  private void createUiComponents() {
    frame.setStatusBar(statusBar = createStatusBar());
    frame.setDefaultMenuBar(menuBar = createMenuBar());
    frame.setDefaultToolBarPanel(toolBarPanel = createToolBarPanel()); 

    /*
     * 1. remove MDIManager from frame
     * 2. create/add JSplitPane to frame with MDIManager and paletteTB as args
     */
    Container contentPane = frame.getContentPane();
    MDIManager mdiManager = frame.getManager();
    contentPane.remove(mdiManager);
    paletteTB = new CustomPalettePanel(connectionManager.getCurrentConnection());
    JSplitPane splitter = new JSplitPane(JSplitPane.VERTICAL_SPLIT, false, mdiManager, paletteTB);
    contentPane.add(splitter);
  }

  private MDIFrame createFrame(String title) {
    MDIFrame frame = new MDIFrame(title);
    // set the logo to be the Gensym logo
    Image image = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("gensym_logo.gif"));
    if (image != null)
      frame.setIconImage(image);
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
    tb.add(new WorkspaceCommands(frame, connectionManager));
    tb.addSeparator();

    tb.add(projectHandler, ProjectCommands.NEW_PROJECT);
    tb.add(projectHandler, ProjectCommands.OPEN_PROJECT);
    tb.add(projectHandler, ProjectCommands.SAVE_PROJECT);
    tb.addSeparator();

    tb.add(editHandler, EditCommands.CUT_SELECTION);
    tb.add(editHandler, EditCommands.COPY_SELECTION);
    tb.add(editHandler, EditCommands.PASTE_SELECTION);
    tb.addSeparator();

    tb.add(workspaceInstanceHandler, WorkspaceInstanceCommands.PRINT_WORKSPACE);
    tb.addSeparator();

    panel.add(tb);

    // add HostPortPanel for switching between existing connections
    ToolBar tb2 = new ToolBar ();
    try {
      tb2.add (new HostPortPanel(connectionManager));
      tb2.add (Box.createGlue());
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

  private CMenuBar createMenuBar() {
    CMenuBar mb = new CMenuBar(); 
    mb.add(createFileMenu());
    mb.add(createEditMenu());
    mb.add(createViewMenu());
    mb.add(createLayoutMenu());
    mb.add(createToolsMenu());
    mb.add(createG2Menu()); 
    mb.add(createHelpMenu()); 
    return mb;
  }

  private CMenu createFileMenu() {
    CMenu menu = new CMenu (shortBundle.getString("FileMenu"));

    projectHandler = new ProjectCommands(frame, connectionManager);
    menu.add(projectHandler, ProjectCommands.NEW_PROJECT, menuConstraints);
    menu.add(projectHandler, ProjectCommands.OPEN_PROJECT, menuConstraints);
    menu.add(projectHandler, ProjectCommands.CLOSE_PROJECT, menuConstraints);
    menu.addSeparator();

    CMenu moduleMenu = new CMenu("Modules");
    moduleMenu.add(moduleHandler = new ModuleCommands(frame, connectionManager));
    menu.add(moduleMenu);
    menu.addSeparator();

    CMenu snapMenu = new CMenu("Snapshots");
    snapMenu.add(snapshotHandler = new SnapshotCommands(frame, connectionManager));
    menu.add(snapMenu);
    menu.addSeparator();

    menu.add(projectHandler, ProjectCommands.SAVE_PROJECT, menuConstraints);
    menu.add(projectHandler, ProjectCommands.SAVE_PROJECT_AS, menuConstraints);
    menu.addSeparator();
  
    workspaceInstanceHandler = new WorkspaceInstanceCommands(frame);
    menu.add(workspaceInstanceHandler, WorkspaceInstanceCommands.PRINT_WORKSPACE, menuConstraints);
    menu.addSeparator();

    menu.add(exitHandler = new ExitCommands(frame, connectionManager), menuConstraints);
    return menu;
  }

  private CMenu createEditMenu() {
    CMenu menu = new CMenu("Edit"); 
    menu.add(editHandler = new EditCommands(frame), menuConstraints);
    menu.add(itemHandler = new ItemCommands(frame), ItemCommands.DELETE_SELECTION, menuConstraints);
    menu.addSeparator();
    menu.add(workspaceInstanceHandler, WorkspaceInstanceCommands.SELECT_ALL_WORKSPACE_ITEMS, menuConstraints);
    return menu;
  }

  private CMenu createViewMenu() {
    CMenu menu = new CMenu("View");
    CMenu tbMenu = new CMenu("Toolbars");
    JMenuItem layoutMenuItem = new JMenuItem("Layout");
    layoutMenuItem.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
	if (layoutTBDialog == null) {
	  layoutTBDialog = new JDialog(frame, "Layout Tools", false);
	  layoutTBDialog.getContentPane().add(layoutToolBar = new CommandTabbedPane(layoutCommands));
	  layoutTBDialog.pack();
	  
	  Dimension frameSize = frame.getSize();
	  Point     frameLoc  = frame.getLocation();
	  Dimension mySize    = layoutTBDialog.getSize();
      
	  int x = Math.max(0, frameLoc.x + (frameSize.width/2) -(mySize.width/2));
	  int y = Math.max(0,frameLoc.y + (frameSize.height/2)-(mySize.height/2));
     
	  layoutTBDialog.setBounds (x, y, mySize.width, mySize.height);
	}
	layoutTBDialog.setVisible(true);
      }
    });
    tbMenu.add(layoutMenuItem);
    menu.add(tbMenu);

    CMenu paletteMenu = new CMenu("Palettes");
    menu.add(paletteMenu);
    menu.addSeparator();

    menu.add(viewHandler = new ViewCommands(this), menuConstraints);

    return menu;
  }

  private CMenu createLayoutMenu() {
    Vector commands = new Vector();
    int cnt = 0;
    CMenu menu = new CMenu("Layout");
    CMenu tmpMenu = new CMenu("Alignment");
    tmpMenu.add(alignmentHandler = new AlignmentCommands(frame), menuConstraints);
    cnt++;
    menu.add(tmpMenu);
    commands.addElement(alignmentHandler);

    tmpMenu = new CMenu("Order");
    tmpMenu.add(orderHandler = new OrderCommands(frame), menuConstraints);
    menu.add(tmpMenu);
    cnt++;
    commands.addElement(orderHandler);

    tmpMenu = new CMenu("Nudge");
    tmpMenu.add(nudgeHandler = new NudgeCommands(frame), menuConstraints);
    menu.add(tmpMenu);
    cnt++;
    commands.addElement(nudgeHandler);

    tmpMenu = new CMenu("Rotate/Flip");
    tmpMenu.add(rotateHandler = new RotateCommands(frame), menuConstraints);
    menu.add(tmpMenu);
    commands.addElement(rotateHandler);
    cnt++;

    layoutCommands = new Command[cnt];
    for (int i=0; i<cnt; i++)
      layoutCommands[i] = (Command)commands.elementAt(i);
    
    return menu;
  }

  private CMenu createToolsMenu() {
    CMenu menu = new CMenu(shortBundle.getString("ToolsMenu"));
    browserHandler = new BrowserCommands(connectionManager.getCurrentConnection());
    menu.add(browserHandler, menuConstraints);
    return menu;
  }

  private CMenu createG2Menu() {
    CMenu menu = new CMenu(shortBundle.getString("G2Menu")); 
    menu.add(new SwitchConnectionCommand(connectionManager));
    menu.addSeparator();
    menu.add(connectionHandler = new ConnectionCommands(this), menuConstraints);
    return menu;
  }

  private CMenu createHelpMenu() {
    CMenu menu = new CMenu(shortBundle.getString("HelpMenu"));
    //menu.add(new HelpCommands(frame));
    return menu;
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
    if (connection == null) {
      setStatusBarStatus(shortBundle.getString("TW2NoConnection"), null);
      paletteTB.setConnection(connection);
      browserHandler.setConnection(connection);
    }
    else {
      if (e.isConnectionNew()) {
	connection.addTwConnectionListener(modeListener);
	paletteTB.setConnection(connection);
	browserHandler.setConnection(connection);
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
  }
  // END: ContextChangedListener Methods

  private void setStatusBarStatus(String connection, Symbol mode) {
    String status = connection;
    if (mode != null)
     status = status + "  " + mode.toString().toLowerCase();
    statusBar.setStatus(status);
  }

  class TW2ModeListener extends TwConnectionAdapter {
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
      throw new UnexpectedException(ex);
    }

    /*
     * Create an instance of this class. 
     */
    G2Studio application = new G2Studio(cmdLineArgs);

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
      workspaceShowingListener = new TW2MDIWorkspaceShowingAdapter(connectionMgr);
      TwConnectionInfo connectionInfo = getG2ConnectionInformation();
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
    }
    catch (G2AccessException gae) {
      Trace.exception (gae);
      application.loginFailureHandler.handleLoginFailureException(gae,
								  unloggedInConnection);
    }

    /*
     * Make the frame visible!
     */
    application.frame.setVisible(true);
  }

  class TestDialog extends com.gensym.dlg.StandardDialog {
    TestDialog (java.awt.Frame frame, String title, boolean isModal, java.awt.Component x, com.gensym.dlg.StandardDialogClient client) {
      super(frame, title, isModal, new String[] {"OK", "Cancel"}, new int[] {1, 2}, x, client);
    }
  }
}



