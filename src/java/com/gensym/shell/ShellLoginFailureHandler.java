/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ShellLoginFailureHandler.java
 *
 */
package com.gensym.shell;

import java.awt.Cursor;

import com.gensym.core.GensymApplication;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.WarningDialog;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.jgi.G2Gateway;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.OkException;
import com.gensym.ntw.LoginFailedException;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TooManyLoginAttemptsException;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.shell.dialogs.LoginDialog;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.TW2MDIApplication;

/**
 * Handles connection and login failures for Shell, the Telewindows2 default application shell
 *
 * @see com.gensym.shell.Shell
 */
public class ShellLoginFailureHandler {

  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/Messages");

  private ConnectionManager connectionMgr;
  private TwAccess unloggedInConnection;
  private LoginDialog loginDialog;
  private TwConnectionInfo previousConnectionInfo;
  private LoginRequest previousLoginRequest;
  private final static String cxnErrorTitle = shortBundle.getString("ShellUnableToConnectDialogTitle");
  
  public ShellLoginFailureHandler() {
    TW2MDIApplication app = (TW2MDIApplication)GensymApplication.getApplication();
    connectionMgr = app.getConnectionManager();
    setPreviousConnectionInformation(app.getG2ConnectionInformation());
    setPreviousLoginRequest(app.getLoginRequest());
  }
  
  private void setPreviousConnectionInformation(TwConnectionInfo connectionInfo) {
    previousConnectionInfo = connectionInfo;
  }

  private void setPreviousLoginRequest(LoginRequest loginRequest) {
    previousLoginRequest = loginRequest;
  }

  /**
   * Handles G2AccessExceptions that are thrown during connection and login to G2 session.
   * @param gae The G2AccessException thrown
   * @param connection The connection that triggered the exception, may be null.
   *
   * @see com.gensym.jgi.ConnectionTimedOutException;
   * @see com.gensym.jgi.G2AccessException;
   * @see com.gensym.jgi.G2AccessInitiationException;
   * @see com.gensym.ntw.OkException;
   * @see com.gensym.ntw.LoginFailedException;
   * @see com.gensym.ntw.TooManyLoginAttemptsException;
   *
   */
  public void handleLoginFailureException (G2AccessException gae, TwAccess connection) {  

    unloggedInConnection = connection;
    String loginError = gae.getMessage();
   
    if (loginDialog == null) {
      loginDialog = new LoginDialog(null, 
				    shortBundle.getString("ShellOpenConnectionTitle"),
				    true, new DialogClient());
      loginDialog.setConnectionInformation(previousConnectionInfo);
      loginDialog.setLoginRequest(previousLoginRequest);
    }

    if (gae instanceof G2AccessInitiationException) {
      /*
       * G2AccessInitiationException: Display informational message and let the user try again
       */
      String hostPortInfo = "  (" +previousConnectionInfo.getHost()+" : "+
	previousConnectionInfo.getPort()+")";
      new WarningDialog(null, cxnErrorTitle, true, 
			shortBundle.format("UnableToOpenConnectionWithReason", 
					   hostPortInfo, loginError), null).setVisible(true);
      loginDialog.setVisible(true);
    } else if (gae instanceof ConnectionTimedOutException) {
      /*
       * ConnectionTimedOutException: Display informationl message and let the user try again
       */
      String hostPortInfo = "  (" +previousConnectionInfo.getHost()+" : "+
	previousConnectionInfo.getPort()+")";
      new WarningDialog(null, cxnErrorTitle, true, 
			shortBundle.format("UnableToOpenConnectionWithReason", 
					   hostPortInfo, loginError), null).setVisible(true);
      loginDialog.setVisible(true);
    } else if ( (gae instanceof TooManyLoginAttemptsException)
		|| (gae instanceof OkException)
		|| ( (gae instanceof LoginFailedException)
		     && ( loginError.equals("NO-AVAILABLE-FLOATING-LICENSES") ) ) ) {
      /*
       * TooManyLoginAttemptsException: Display informational message, close connection, get out.
       */
      String hostPortInfo = "  (" +previousConnectionInfo.getHost()+" : "+
	previousConnectionInfo.getPort()+")";
      new WarningDialog(null, cxnErrorTitle, true, 
			shortBundle.format("UnableToOpenConnectionWithReason", 
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
			shortBundle.format("UnableToOpenConnectionWithReason", 
					   hostPortInfo, loginError), null).setVisible(true);

      // reset the loginRequest info in the dialog so that the password field is wiped out
      loginDialog.setLoginRequest(previousLoginRequest);
   
      loginDialog.selectTabPage(loginDialog.SECURITY_TAB_PAGE);
      loginDialog.setVisible(true);
    } 
  }
  
  class DialogClient implements StandardDialogClient {
    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {
      if (dlg.wasCancelled()){
	dlg.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	if (unloggedInConnection != null) {
	  unloggedInConnection.closeConnection();
	  unloggedInConnection = null;
	}
      } else {
	LoginDialog lDlg = (LoginDialog)dlg;
	TwConnectionInfo newConnectionInfo = lDlg.getConnectionInformation();
	LoginRequest newLoginRequest = lDlg.getLoginRequest();
	//System.out.println("newConnectionInfo: "+newConnectionInfo+"  newLoginRequest: "+newLoginRequest);

	/*
	 * Check to see if we're attempted to connect to the same connection as
	 * before, or whether or not this is a completely new connection.
	 */
	lDlg.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
	if ((unloggedInConnection == null) || (!(newConnectionInfo.equals(previousConnectionInfo)))) {
	  //System.out.println("either unloggedInConnection is null ("+unloggedInConnection+"), or newConnectionInfo is really new");

	  if (unloggedInConnection != null) {
	    unloggedInConnection.closeConnection();
	    unloggedInConnection = null;
	  }
	  
	  setPreviousConnectionInformation(newConnectionInfo);
	  setPreviousLoginRequest(newLoginRequest);

	  try {
	    connectionMgr.openConnection(previousConnectionInfo);
	    unloggedInConnection = connectionMgr.getCurrentConnection();
	    if (unloggedInConnection != null) {
	      unloggedInConnection.login(previousLoginRequest);
	      lDlg.setVisible(false);
	      lDlg.dispose();
	    }
	  } catch (G2AccessException gae) {
	    Trace.exception(gae);
	    handleLoginFailureException (gae, unloggedInConnection);
	  }
	} else {
	  //System.out.println("newConnectionInfo is the same as previousConnectionInfo, unloggedInConnection: "+unloggedInConnection);
	  
	  // dealing with same connection, re-attempt to login
	  setPreviousLoginRequest(newLoginRequest);

	  try {
	    //System.out.println("unloggedInConnection.login ("+unloggedInConnection+")");
	    unloggedInConnection.login(previousLoginRequest);
	    lDlg.setVisible(false);
	    lDlg.dispose();
	  } catch (G2AccessException gae) {
	    //System.out.println(gae.getMessage());
	    Trace.exception(gae);
	    handleLoginFailureException (gae, unloggedInConnection);
	  }
	}

	lDlg.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
      }
    } 
  }
}


