/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceBrowserApp.java
 *
 */
package com.gensym.demos.multiplecxnsdiapp;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import com.gensym.classes.KbWorkspace;
import com.gensym.dlg.MessageDialog;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.SwitchConnectionCommand;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.TW2Application;
import com.gensym.ui.menu.awt.CMenu;
import com.gensym.ui.menu.awt.CMenuBar;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.wksp.MultipleWorkspacePanel;

import javax.swing.Box;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.SwingConstants;
import javax.swing.UIManager;

public class WorkspaceBrowserApp extends TW2Application implements ContextChangedListener {

  private static Resource shortBundle = Resource.getBundle("com/gensym/demos/multiplecxnsdiapp/Messages");

  private JFrame frame;
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;

  private WorkspaceBrowserPanel wkspBrowser;
  private MultipleWorkspacePanel workspacePanel;
  private JButton wkspLeftButton;
  private JButton wkspRightButton;

  private CMenuBar menuBar;

  private Symbol userMode;

  private ConnectionCommands connectionHandler;
  private ExitCommands exitHandler;

  private static final String appTitle = shortBundle.getString("AppTitle");
 
  public WorkspaceBrowserApp (String[] cmdLineArgs) {
    /*
     * By calling super(cmdLineArgs) we do the following:
     *
     * 1. let TW2Application parse for the following
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
     * Create the G2Studio container
     */
    createWorkspaceBrowserApp();
  }

  private void createWorkspaceBrowserApp() {
    setCurrentFrame(frame = createFrame(appTitle));
    connectionManager = new ConnectionManager();
    connectionManager.addContextChangedListener(this);
    createUiComponents();
    registerFrameWithDialogManager(frame);
  }

  /**
   * Gets the ConnectionManager for this application
   *
   * @see com.gensym.shell.util.ConnectionManager
   */
  @Override
  public ConnectionManager getConnectionManager(){
    return connectionManager;
  }

  /**
   * Not implemented for this application, which is
   * a multiple connection application and uses the 
   * ConnectionManager. Users should use getConnectionManager()
   * instead.
   */
  @Override
  public TwAccess getConnection(){
    return null;
  }

  /**
   * Not implemented for this application, which is
   * a multiple connection application and uses the
   * Connection Manager.
   *
   * @see com.gensym.shell.util.ConnectionManager
   */
  @Override
  public void setConnection(TwAccess connection){}

  private void registerFrameWithDialogManager(JFrame frame) {
    com.gensym.dlgruntime.DialogManager.registerFrame (frame);
    com.gensym.dlgruntime.DefaultDialogLauncher.registerFrame (frame);
  }

  private void createUiComponents() {
    frame.setMenuBar(menuBar = createMenuBar());

    JPanel toolbarPanel = new JPanel();
    toolbarPanel.setLayout(new BorderLayout());
    toolbarPanel.add(setupToolBar(), BorderLayout.WEST);
    toolbarPanel.add(setupWkspButtons(), BorderLayout.EAST);

    Container contentPane = frame.getContentPane();
    contentPane.add(toolbarPanel, BorderLayout.NORTH);
   
    wkspBrowser = new WorkspaceBrowserPanel(frame, connectionManager);
    workspacePanel = new MultipleWorkspacePanel();
    
    JSplitPane splitter = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, false,
					 wkspBrowser, workspacePanel);
    contentPane.add(splitter, BorderLayout.CENTER);
  }

  private JFrame createFrame(String title) {
    JFrame frame = new JFrame(title);
    // set the logo to be the Gensym logo
    Image image = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("gensym_logo.gif"));
    if (image != null)
      frame.setIconImage(image);
    frame.setBounds(0, 0, 900, 600);
    return frame;
  }

  private CMenuBar createMenuBar() {
    CMenuBar mb = new CMenuBar(); 
    mb.add(createFileMenu());
    mb.add(createG2Menu()); 
    mb.add(createHelpMenu()); 
    return mb;
  }

  private CMenu createFileMenu() {
    CMenu menu = new CMenu (shortBundle.getString("FileMenu"));
    menu.add(exitHandler = new ExitCommands(frame, connectionManager));
    return menu;
  }

  private CMenu createG2Menu() {
    CMenu menu = new CMenu(shortBundle.getString("G2Menu")); 
    menu.add(new SwitchConnectionCommand(connectionManager));
    menu.addSeparator();
    menu.add(connectionHandler = new ConnectionCommands(this));
    return menu;
  }

  private CMenu createHelpMenu() {
    CMenu menu = new CMenu(shortBundle.getString("HelpMenu"));
    menu.add(new HelpCommands(frame));
    return menu;
  }

  private ToolBar setupToolBar() {
    ToolBar tb = new ToolBar();
    tb.add(exitHandler);
    tb.addSeparator();
    tb.add(connectionHandler);
    return tb;
  }

  private JPanel setupWkspButtons() {
    JPanel wkspButtonPanel = new JPanel();
    wkspButtonPanel.setLayout(new FlowLayout());

    wkspLeftButton = new JButton(new ImageIcon("wksp_left.gif"));
    wkspLeftButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
    //wkspLeftButton.setEnabled(false);
    wkspLeftButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed (ActionEvent e) {
	KbWorkspace[] workspaces = workspacePanel.getWorkspaces();
	if (workspaces.length <= 1)
	  new MessageDialog(frame, "FYI", true, "There are currently <"+workspaces.length+"> workspace views registered with the MultipleWorkspacePanel", null).setVisible(true);
	else
	  workspacePanel.nextWorkspace();
      }
    });
    wkspButtonPanel.add(wkspLeftButton);

    wkspRightButton = new JButton(new ImageIcon("wksp_right.gif"));
    wkspRightButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
    //wkspRightButton.setEnabled(false);
    wkspRightButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed (ActionEvent e) {
	KbWorkspace[] workspaces = workspacePanel.getWorkspaces();
	if (workspaces.length <= 1)
	  new MessageDialog(frame, "FYI", true, "There are currently <"+workspaces.length+"> workspace views registered with the MultipleWorkspacePanel", null).setVisible(true);
	else
	  workspacePanel.previousWorkspace();
      }
    });
    wkspButtonPanel.add(wkspRightButton);

    return wkspButtonPanel;
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
    
    if (currentConnection != null) {
      KbWorkspace[] showingWorkspaces = workspacePanel.getWorkspaces();
      for (int i=0; i<showingWorkspaces.length; i++) 
	workspacePanel.removeWorkspace(showingWorkspaces[i]);
      
      try {
	currentConnection.removeWorkspaceShowingListener(workspacePanel);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    currentConnection = connection;

    if (currentConnection != null) {
      try {
	currentConnection.addWorkspaceShowingListener(workspacePanel);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
  }
  // END: ContextChangedListener Methods

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
    WorkspaceBrowserApp application = new WorkspaceBrowserApp(cmdLineArgs);

    /*
     * Make the frame visible!
     */
    application.frame.setVisible(true);
  }
}


