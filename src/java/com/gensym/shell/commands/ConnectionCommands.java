/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ConnectionCommands.java
 *
 */
package com.gensym.shell.commands;

import java.util.Vector;
import java.awt.Cursor;
import java.awt.event.ActionEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.WarningDialog;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.LoginFailedException;
import com.gensym.ntw.TooManyLoginAttemptsException;
import com.gensym.ntw.AlreadyLoggedInException;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.OkException;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.core.UiApplication;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.shell.dialogs.LoginDialog;
import com.gensym.shell.util.*;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.shell.util.ConnectionListCellRenderer;

/** 
 * Command to open a connection to G2 and close a connection with G2
 * This command may be used in single and multiple 
 * connection applications. Multiple connection applications must use 
 * the ConnectionManager for maintaining the open connections to G2.
 * Single connection applications must use this command to open a 
 * connection to G2.
 */
public final class ConnectionCommands extends AbstractCommand {
  /** Command key to open a connection to G2. */
  public static final String TW_CONNECT = "TwConnect";
  /** Command key to close a connection with G2. */
  public static final String TW_DISCONNECT = "TwDisconnect";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";

  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");

  private static UiApplication app;
  private static ConnectionManager connectionMgr;
  private static G2ConnectionAdapter closingListener;
  private static TwAccess unloggedInConnection;
  private static TwAccess currentConnection;

  private LoginDialog loginDialog;
  private LoginFailureHandler loginFailureHandler;

  private static String hostName = "localhost";
  private static String portNumber = "1111";
  private static String brokerURL = null;
  private static Symbol userName_ = Symbol.intern (System.getProperty ("user.name").toUpperCase ());
  private static Symbol userMode_ = Symbol.intern ("ADMINISTRATOR");
  private static Symbol password_ = null;
  private static TwConnectionInfo previousConnectionInfo;
  private static LoginRequest previousLoginRequest;

  private static StandardDialogClient dialogClient;
  private static ContextChangedListener contextChangedListener;
  private static ConnectionOpener cxnOpener;


  public ConnectionCommands(TW2Application app){
    this(app, app.getConnectionManager());
  }

  public ConnectionCommands(TW2MDIApplication app){
    this(app, app.getConnectionManager());
  }

  private ConnectionCommands(UiApplication app, ConnectionManager cxnMgr){
    super (new CommandInformation[]{
      new CommandInformation(TW_CONNECT, true, shortResource, 
			     longResource, "connect.gif", null, null, false, mnemonicResource, null),
      new CommandInformation(TW_DISCONNECT, true, shortResource, 
			     longResource, "disconnect.gif", null, null,
			     (cxnMgr == null), mnemonicResource, null)});

      dialogClient = new DialogClient();
      closingListener = new G2CloseAdapter();
      cxnOpener = new ConnectionOpener();

      if (previousConnectionInfo == null)
	previousConnectionInfo = new TwConnectionInfo(brokerURL, hostName, portNumber);
      if (previousLoginRequest == null)
	previousLoginRequest = new LoginRequest(userMode_, userName_, password_);

      loginFailureHandler = new LoginFailureHandler();

      //multiple connection application
      if (cxnMgr != null){
	connectionMgr = cxnMgr;
	TwAccess[] cxns = connectionMgr.getOpenConnections();

	setCurrentConnection(connectionMgr.getCurrentConnection());
	contextChangedListener = new ContextChangedAdapter();
	connectionMgr.addContextChangedListener(contextChangedListener);
	if (!connectionMgr.hasConnections())
	  setAvailable(TW_DISCONNECT, false);
      }
      //single connection application
      else{
	this.app = app;
	setAvailable(TW_DISCONNECT, false);
      }
    }

  /**
   * Sets the TwConnectionInfo object that is used for updating the LoginDialog used
   * while handling TW_CONNECT
   */
  public void setPreviousConnectionInformation(TwConnectionInfo connectionInfo) {
    previousConnectionInfo = connectionInfo;
    if (connectionInfo != null) {
      if (connectionInfo.getHost() != null)
	hostName = connectionInfo.getHost();
      if (connectionInfo.getPort() != null)
	portNumber = connectionInfo.getPort();
      if (connectionInfo.getBrokerURL() != null)
	brokerURL = connectionInfo.getBrokerURL();
    }
  }

  /**
   * Sets the LoginRequest object that is used for updating the LoginDialog used
   * while handling TW_CONNECT
   */
  public void setPreviousLoginRequest(LoginRequest loginRequest) {
    previousLoginRequest = loginRequest;
    if (loginRequest != null) {
      if (loginRequest.getUserName() != null)
	userName_ = loginRequest.getUserName();
      if (loginRequest.getUserMode() != null)
	userMode_ = loginRequest.getUserMode();
    }
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));

    if (cmdKey.equals(TW_CONNECT)) 
      handleTWConnectCommand();
    else if (cmdKey.equals(TW_DISCONNECT))
      handleTWDisconnectCommand();
  }

  private void handleTWConnectCommand() {
    if (loginDialog == null){
      loginDialog = new LoginDialog (null, 
				     shortBundle.getString("OpenTwConnectionTitle"),
				     true, dialogClient);
    }

    loginDialog.setConnectionInformation(previousConnectionInfo);
    loginDialog.setLoginRequest(previousLoginRequest);
    loginDialog.setVisible(true);
  }

  private void handleTWDisconnectCommand() {
    if (connectionMgr != null){
      TwAccess[] connections = connectionMgr.getOpenConnections();
      int currentConnectionIndex = -1;
      for (int i=0; i<connections.length; i++){
        if (connections[i].equals(currentConnection)) currentConnectionIndex = i;
      }
      new SelectionDialog(null, shortBundle.getString("CloseTwConnectionTitle"),
			                true, shortBundle.getString("ChooseConnection"),
			                connections, new ConnectionListCellRenderer(),
                            false, currentConnectionIndex,
                            true, dialogClient).setVisible(true);

    }
    else
      currentConnection.closeConnection();
  }

  public void setConnection(TwAccess connection){
    if (connectionMgr == null){
      if (((currentConnection != null) && ((!currentConnection.equals(connection)))) ||
	  ((currentConnection == null) && (connection != null))){
	if (currentConnection != null)
	  currentConnection.removeG2ConnectionListener(closingListener);
	setCurrentConnection(connection);
	if (connection != null)
	  connection.addG2ConnectionListener(closingListener);     
      }
    }
    else
      throw new IllegalStateException(i18n.getString("CantCallSetCxnInMultiCxnApp"));
  }

  private void setCurrentConnection(TwAccess connection){
    currentConnection = connection;
    if (connectionMgr != null){
    }
    else{
      if (currentConnection == null){
	setAvailable(TW_CONNECT, true);
	setAvailable(TW_DISCONNECT, false);
      }
      else{
	setAvailable(TW_CONNECT, false);
	setAvailable(TW_DISCONNECT, true);
      }
      if (app instanceof TW2Application)
	((TW2Application)app).setConnection(currentConnection);
      else
	((TW2MDIApplication)app).setConnection(currentConnection);
    }
  }

  /** 
   *  Sets the availability of command and notifies listeners if availability
   *  has changed.
   */
  @Override
  protected void setAvailable(String key, boolean available){
    super.setAvailable(key, available);
  }

  class ConnectionOpener{
    private String url, host, port;
    private Symbol name_, mode_, password_;
    ConnectionOpener(){}

    void openConnection(String url, String host, String port, Symbol name_, 
			Symbol mode_, Symbol password_){
      this.url = url;
      this.host = host;
      this.port = port;
      this.name_ = name_;
      this.mode_ = mode_;
      this.password_ = password_;
      openConnection();
    }

    void openConnection(TwConnectionInfo connectionInfo, LoginRequest loginRequest) {
      openConnection();
    }

    void openConnection(){
      loginDialog.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

      try{
	if (unloggedInConnection == null) {
	  if (connectionMgr != null)
	    unloggedInConnection = connectionMgr.openConnection (previousConnectionInfo);
	  else{
	    setCurrentConnection(TwGateway.openConnection(previousConnectionInfo));
	    currentConnection.addG2ConnectionListener(closingListener);
	    unloggedInConnection = currentConnection;
	  }
	}

	unloggedInConnection.login(previousLoginRequest);
	unloggedInConnection = null;

	hostName = host;
	portNumber = port;
	userName_ = name_;
	userMode_ = mode_;
	loginDialog.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	loginDialog.setVisible(false);
	loginDialog.dispose();
	loginDialog = null; // let the garbage collector have it
      }
      catch (G2AccessException gae){
	Trace.exception(gae);
	loginDialog.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	loginFailureHandler.handleLoginFailureException(gae);
      }
    }
  }

  class DialogClient implements StandardDialogClient {
    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {
      if (dlg.wasCancelled()){
	if (dlg instanceof LoginDialog)
	  dlg.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	if (unloggedInConnection != null) {
	  unloggedInConnection.closeConnection();
	  unloggedInConnection = null;
	}
	return;
      }

      if (dlg instanceof LoginDialog) {
	LoginDialog  lDlg = (LoginDialog)dlg;
	TwConnectionInfo newConnectionInfo = lDlg.getConnectionInformation();
	if (newConnectionInfo == null) // Exception handled by UI.
	  return;
	if ((unloggedInConnection != null) && (!(newConnectionInfo.equals(previousConnectionInfo)))) {
	  unloggedInConnection.closeConnection();
	  unloggedInConnection = null;
	}
	  
	previousConnectionInfo = newConnectionInfo;
	previousLoginRequest = lDlg.getLoginRequest();
	cxnOpener.openConnection(previousConnectionInfo, previousLoginRequest);
      }
      else {//close connection
	SelectionDialog osd = (SelectionDialog)dlg;
	Object[] chosenConnections = osd.getSelectedItems();
	for (int i=0; i < chosenConnections.length; i++) {
	  TwAccess cxn = (TwAccess) chosenConnections[i];
	  if (cxn != null) cxn.closeConnection();
	}
      }
    } 
  }

  //multiple connection apps
  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      TwAccess newCurrentConnection = e.getConnection();
	  setAvailable(TW_DISCONNECT, connectionMgr.hasConnections());
      setCurrentConnection(newCurrentConnection);
    }
  }

  class G2CloseAdapter extends G2ConnectionAdapter{
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e){
      TwAccess connection = (TwAccess)e.getSource();
      if (connectionMgr != null){

	if (!connectionMgr.hasConnections()){
	  setAvailable(TW_DISCONNECT, false);
	}
      }
      else
	setCurrentConnection(null);
      connection.removeG2ConnectionListener(closingListener);
    }
  }

  class LoginFailureHandler {
    final String cxnErrorTitle = i18n.getString("UnableToConnectDialogTitle");
    public LoginFailureHandler() {
    }

    protected void handleLoginFailureException (G2AccessException gae) {
      //System.out.println("handleLoginFailureException: "+gae);
      String loginError = gae.getMessage();
      
      if (gae instanceof G2AccessInitiationException) {
	/*
	 * G2AccessInitiationException: Display informational message and let the user try again
	 */
	String hostPortInfo = "  (" + previousConnectionInfo.getHost()+" : "+previousConnectionInfo.getPort()+")";
	new WarningDialog(null, cxnErrorTitle, true, 
			  i18n.format("UnableToOpenConnectionWithReason", 
				      hostPortInfo, loginError), null).setVisible(true);

      } else if (gae instanceof ConnectionTimedOutException) {
	/*
	 * ConnectionTimedOutException: Display informationl message and let the user try again
	 */
	String hostPortInfo = "  (" +previousConnectionInfo.getHost()+" : "+previousConnectionInfo.getPort()+")";
	new WarningDialog(null, cxnErrorTitle, true, 
			  i18n.format("UnableToOpenConnectionWithReason", 
				      hostPortInfo, loginError), null).setVisible(true);

      } else if ( (gae instanceof TooManyLoginAttemptsException)
                  || (gae instanceof OkException)
                  || ( (gae instanceof LoginFailedException)
                       && ( loginError.equals("NO-AVAILABLE-FLOATING-LICENSES") ) ) ) {
	/*
	 * TooManyLoginAttemptsException: Display informational message, close connection, get out.
	 */
	String hostPortInfo = "  (" +previousConnectionInfo.getHost()+" : "+previousConnectionInfo.getPort()+")";
	new WarningDialog(null, cxnErrorTitle, true, 
			  i18n.format("UnableToOpenConnectionWithReason", 
				      hostPortInfo, loginError), null).setVisible(true);
	loginDialog.setVisible(false);
	loginDialog.dispose();
	unloggedInConnection.closeConnection();
	unloggedInConnection = null;

      } else if (gae instanceof LoginFailedException) {
	/*
	 * Error is one of the following:
	 *   USER-NAME-REQUIRED
	 *   PASSWORD-REQUIRED
	 *   UNKNOWN-USER-OR-BAD-PASSWORD
	 *   UNAUTHORIZED-MODE
	 * Display informational message and let the user try again
	 */
	String hostPortInfo = "  (" +previousConnectionInfo.getHost()+" : "+previousConnectionInfo.getPort()+")";
	new WarningDialog(null, cxnErrorTitle, true, 
			  i18n.format("UnableToOpenConnectionWithReason", 
				      hostPortInfo, loginError), null).setVisible(true);
	loginDialog.setLoginRequest(previousLoginRequest);
	loginDialog.selectTabPage(loginDialog.SECURITY_TAB_PAGE);
      }
      else if (gae instanceof AlreadyLoggedInException) {
        /*
         * AlreadyLoggedInException: Null out the
         * unloggedInConnection, but don't close it (because it's a
         * valid connection).
         */
        String hostPortInfo = "  (" +previousConnectionInfo.getHost()+" : "+previousConnectionInfo.getPort()+")";
	new WarningDialog(null, cxnErrorTitle, true, 
			  i18n.format("UnableToOpenConnectionWithReason", 
				      hostPortInfo, loginError), null).setVisible(true);
        unloggedInConnection = null;
      }
    }
  }
}
