package com.gensym.demos.gmsdemo;

import java.awt.Image;
import java.awt.Toolkit;
import java.util.Hashtable;

import com.gensym.clscupgr.gms.*;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.MessageDialog;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.mdi.MDIStatusBar;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.mdi.MDIFrame;
import com.gensym.message.Trace;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.TwGateway;
import com.gensym.shell.commands.CondensedG2StateCommands;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.util.HostPortPanel;
import com.gensym.shell.util.UserModePanel;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.shell.util.TW2MDIWorkspaceShowingAdapter;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import javax.swing.JMenuBar;
import javax.swing.UIManager;

public class GMSApp extends TW2MDIApplication implements MenuNotificationListener {

  private MDIFrame frame;
  private MDIToolBarPanel toolBarPanel;
  private MDIStatusBar statusBar;

  private TwAccess currentConnection = null;
  private MenuManager menuManager = null;
  private GMSJMenuBar menuBar = null;
  private int menuBarIndex;

  private Symbol userMode;
  private ModeListener modeListener = new ModeListener();

  private G2ConnectionListener g2ConnectionAdapter;

  private HostPortPanel cxnPanel;
  private UserModePanel modePanel;

  private WorkspaceCommands wkspHandler;
  private ExitCommands exitHandler;
  private CondensedG2StateCommands g2StateHandler;
  private ConnectionCommands connectionHandler;

  public GMSApp (String[] cmdLineArgs) {
    super(cmdLineArgs);
    createGMSApp();
  }

  private void createGMSApp() {
    frame = createFrame("GMS Application");
    setCurrentFrame(frame);

    frame.setStatusBar(statusBar = createStatusBar());
    frame.setDefaultToolBarPanel(toolBarPanel = createToolBarPanel());

    g2ConnectionAdapter = new G2StateConnectionAdapter();
  }

  @Override
  public ConnectionManager getConnectionManager() {
    return null;
  }

  @Override
  public TwAccess getConnection() {
    return currentConnection;
  }

  @Override
  public void setConnection(TwAccess connection){
    setCurrentConnection(connection);
  }
  
  protected void setCurrentConnection(TwAccess connection) {
    System.out.println("\nBEGIN: GMSApp.setCurrentConnection: "+connection);

    if ((currentConnection != null) && (currentConnection.equals(connection))) return;

    if (currentConnection != null) {
      ((TwGateway)currentConnection).getMenuManager().removeMenuNotificationListener(this);
      currentConnection.removeTwConnectionListener(modeListener);
      currentConnection.removeG2ConnectionListener(g2ConnectionAdapter);
    }

    currentConnection = connection;

    if (currentConnection != null) {
      System.out.println("add GMSApp as a MenuNotificationListener");
      ((TwGateway)currentConnection).getMenuManager().addMenuNotificationListener(this);
      currentConnection.addTwConnectionListener(modeListener);
      currentConnection.addG2ConnectionListener(g2ConnectionAdapter);
	
      // update connection for command handlers
      try {
	TW2MDIWorkspaceShowingAdapter workspaceShowingListener = new TW2MDIWorkspaceShowingAdapter(currentConnection);
	cxnPanel.setConnection((TwConnection)currentConnection);
	modePanel.setConnection((TwConnection)currentConnection);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	new ErrorDialog(frame, "Error", true, gae.getMessage(), null).setVisible(true);
      }
      
      connectionHandler.setConnection(currentConnection);
      wkspHandler.setConnection(currentConnection);
      exitHandler.setConnection(currentConnection);
      g2StateHandler.setConnection(currentConnection);
      
      // get a handle to the MenuManager for the connection
      menuManager = ((TwGateway)currentConnection).getMenuManager(); 
      
      try {
	setStatusBarStatus(currentConnection.toShortString(), currentConnection.getUserMode());
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    } else {
      menuManager = null;
      setStatusBarStatus(null, null);
    }

    System.out.println("END: GMSApp.setCurrentConnection\n");
  }

  private MDIFrame createFrame(String title) {
    MDIFrame frame = new MDIFrame(title);
    frame.getManager().setDocumentsModifyMenuBar(false);

    // set the logo to be the Gensym logo
    Image image = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("gensym_logo.gif"));
    if (image != null)
      frame.setIconImage(image);
    return frame;
  }

  private MDIToolBarPanel createToolBarPanel() {
    MDIToolBarPanel panel = new MDIToolBarPanel();
  
    ToolBar tb = new ToolBar();
    exitHandler = new ExitCommands(frame, currentConnection);
    tb.add(exitHandler);
    tb.addSeparator();
    wkspHandler = new WorkspaceCommands(frame, currentConnection);
    tb.add(wkspHandler);
    tb.addSeparator();
    connectionHandler = new ConnectionCommands(this);
    tb.add(connectionHandler);
    tb.addSeparator();
    g2StateHandler = new CondensedG2StateCommands(currentConnection);
    tb.add(g2StateHandler);
    panel.add(tb);

    // add HostPortPanel for switching between existing connections
    ToolBar tb2 = new ToolBar ();
    try {
      tb2.add (cxnPanel = new HostPortPanel((TwConnection)currentConnection));
      tb2.add (javax.swing.Box.createGlue());
    } catch (G2AccessException ex) {
      Trace.exception (ex);
      new ErrorDialog(frame, "Error", true, ex.getMessage(), null).setVisible(true);
    }

    // add UserModePanel for switching user mode of connection
    try {
      tb2.add (modePanel = new UserModePanel((TwConnection)currentConnection, true));
    } catch (G2AccessException ex) {
      Trace.exception (ex);
      new ErrorDialog(frame, "Error", true, ex.getMessage(), null).setVisible(true);
    }

    panel.add(tb2);
    return panel;
  }

  private MDIStatusBar createStatusBar() {
    MDIStatusBar sb = new MDIStatusBar();
    return sb;
  }

 private void executeShowMenu(Structure menuDescription) throws G2AccessException {
    System.out.println("\nGMSApp.executeShowMenu");

    // menuDescription could be null, or it could also just be empty
    if ((menuDescription !=  null) && (menuDescription.getAttributeCount() != 0)) {
      GMSJMenuBar[] gmsJMenuBars = menuManager.buildJMenuBar(menuDescription);
      if (gmsJMenuBars != null && gmsJMenuBars[0] != null) {
	System.out.println("number of menus built: "+gmsJMenuBars.length);
	menuBar = gmsJMenuBars[0];
	frame.setDefaultMenuBar(menuBar);
      } else {
	new ErrorDialog(frame, "FYI Error", true, "menuManager failed to generate JMenuBars", null).setVisible(true);
      }
    }
  }

  private void executeHideMenu() {
    System.out.println("GMSApp.executeHideMenu");
    frame.setDefaultMenuBar(null);
  }

  private void executeShowSubMenu(int index, Structure menuDescription) {
    System.out.println("\nGMSApp.executeShowSubMenu: "+menuDescription+"\n");
    if ((menuDescription != null) && (menuDescription.getAttributeCount() != 0)) {
      menuManager.showDynamicMenu(index, menuDescription);
    }
  }

  // BEGIN: MenuNotificationListener methods
  @Override
  public void handleShowMenu(MenuNotificationEvent e) {
    System.out.println("\nGMSApp handleShowMenu, index: "+e.getMenuIndex()+"\n");
    try {
      executeShowMenu(menuManager.getMenuDescription(e.getMenuIndex()));
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      new ErrorDialog(frame, "Error", true, gae.getMessage(), null).setVisible(true);
    }
  }
  @Override
  public void handleHideMenu(MenuNotificationEvent e) {
    System.out.println("\nGMSApp handleHideMenu\n");
    executeHideMenu();
  }
  @Override
  public void handleShowSubMenu(MenuNotificationEvent e) {
    System.out.println("\nGMSApp.handleShowSubMenu");
    try {
      int index = e.getMenuIndex();
      executeShowSubMenu(index, menuManager.getMenuDescription(index));
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      new ErrorDialog(frame, "Error", true, gae.getMessage(), null).setVisible(true);
    }
  }
  @Override
  public void handleHideSubMenu(MenuNotificationEvent e) {
    //new MessageDialog(frame, "MenuNotificationMessage", true, "handleHideSubMenu "+e.getMenuIndex(), null).setVisible(true);
  }
  @Override
  public void handleMenuRecompiled(MenuNotificationEvent e) {
    new MessageDialog(frame, "MenuNotificationMessage", true, "handleMenuRecompiled "+e.getMenuIndex(), null).setVisible(true);
    // application should perhaps:
    // 1. hide current menubar
    // 2. get the new menu description
    // 3. create a new JMenuBar
    // 4. call frame.setDefaultMenuBar
  }
  @Override
  public void handleCheckMenuEntry(MenuNotificationEvent e) {
    executeSetSelected(e.getMenuIndex(), true);
  }
  @Override
  public void handleUnCheckMenuEntry(MenuNotificationEvent e) {
    executeSetSelected(e.getMenuIndex(), false);
  }
  // END: MenuNotificationListener methods

  private void executeSetSelected(int menuIndex, boolean state) {
    System.out.println("GMSApp.executeSetSelected >> menuIndex: "+menuIndex+"  state: "+state);
    Hashtable indexToGMSItemTable = menuManager.getIndexToGMSItemHashtable();
    if (indexToGMSItemTable == null) return;
    GMSItem gmsItem = (GMSItem)indexToGMSItemTable.get(new Integer(menuIndex));
    System.out.println("gmsItem: "+gmsItem);
    if (gmsItem != null && gmsItem instanceof GMSJCheckBoxMenuItem)
      ((GMSJCheckBoxMenuItem)gmsItem).setSelected(state);
  }

  private void setStatusBarStatus(String connection, Symbol mode) {
    String status = connection;
    if (mode != null)
     status = status + "  " + mode.toString().toLowerCase();
    statusBar.setStatus(status);
  }

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
      if (connection != null && currentConnection != null && connection == currentConnection) {
	setStatusBarStatus(connection.toShortString(), userMode);
      } 
    }
  }

  class G2StateConnectionAdapter extends G2ConnectionAdapter {
    @Override
    public void g2IsPaused(G2ConnectionEvent event) { /* do we care */ }
    @Override
    public void g2IsResumed(G2ConnectionEvent event) { /* do we care */ }
    @Override
    public void g2IsReset(G2ConnectionEvent event) {
      // get rid of menubar
      executeHideMenu();
    }
    @Override
    public void g2IsStarted(G2ConnectionEvent event) { /* do we care */ }
  }

  private void executeOpenConnection(TwConnectionInfo cxnInfo) throws ConnectionTimedOutException, G2AccessInitiationException {
    TwAccess cxn = null;
    if (cxnInfo != null) {
      cxn = TwGateway.openConnection(cxnInfo.getHost(), cxnInfo.getPort());
      setConnection(cxn);
    }
  }

  private void executeLoginRequest(LoginRequest loginInfo) throws G2AccessException {
    if (currentConnection != null) {
      if (loginInfo != null)
	currentConnection.login(loginInfo);
      else  
	currentConnection.login();
    }
  }

  public static void main(String[] cmdLineArgs) {
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }

    GMSApp application = new GMSApp(cmdLineArgs);

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
    try {
      application.executeOpenConnection(getG2ConnectionInformation());
      application.executeLoginRequest(getLoginRequest());
    
      application.frame.setVisible(true);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      new ErrorDialog(null, "Connection Error", true, gae.getMessage(), null).setVisible(true);
    }
  }
}
