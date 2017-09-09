/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 LoginDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;

import com.gensym.message.Trace;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.TabGroupPanel;
import com.gensym.message.Resource;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.uiutil.StandardGridBagPanel;
import com.gensym.util.Symbol;

public class LoginDialog extends StandardDialog {

  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ShellDialogResources");

  /** String used for the button that tries to establish the connection and login. */
  public static final String CONNECT_LABEL = shortBundle.getString("DialogButtonConnect");
  /** String used for the button that cancel the connection and login attempt. */
  public static final String CANCEL_LABEL = shortBundle.getString("DialogCancel");

  /** Constant for identifying the connection tab page. */
  public static final int CONNECTION_TAB_PAGE = 0;
  /** Constant for identifying the security tab page. */
  public static final int SECURITY_TAB_PAGE = 1;
  /** Constant for specifying the connection and security tab pages. */
  public static final int CONNECTION_AND_SECURITY_TAB_PAGES = 10;
  /** Constant for specifying "no" tab pages. */
  public static final int NO_TAB_PAGES = 11;

  private int editableTabPages = CONNECTION_AND_SECURITY_TAB_PAGES;
  private int selectedTabPage = CONNECTION_TAB_PAGE;

  private TwConnectionInfo currentConnectionInfo;
  private LoginRequest currentLoginRequest;

  // values for Connection Tab Page text fields
  private String hostName = "";
  private String portName = "";
  private String brokerURL = "";

  // values for Security Tab Page text fields
  private String userName = "";
  private String userMode = "";
  private String password = "";

  private static int CONNECT = OK;

  private TW2ConnectionPanel connectionPanel;
  private TabGroupPanel tabGroup;
  private ConnectionPanel connectionTabPanel;
  private SecurityPanel securityTabPanel;

  /**
   * The LoginDialog class displays a dialog window from which the user can specify connection
   * and login information for connecting and logging into a G2 session.
   */
  public LoginDialog (Frame parentFrame, String title,
		      boolean isModal,
		      StandardDialogClient client) {

    super (parentFrame, title, isModal,
	   new String[] {CONNECT_LABEL, CANCEL_LABEL},
	   new int[] {CONNECT, CANCEL},
	   new TW2ConnectionPanel(),
	   client);

    connectionPanel = (TW2ConnectionPanel) getDialogComponent();
    tabGroup = (TabGroupPanel)connectionPanel.getComponent(0);

    connectionTabPanel = (ConnectionPanel)tabGroup.getComponentAt(0);
    securityTabPanel = (SecurityPanel)tabGroup.getComponentAt(1);
    setupKeyHandler ();

    /*****************************************************
     * Update UI to reflect the state of connection info,
     * login info, editable state, and focus
     *****************************************************/

    // 1. update connection info fields
    executeUpdateConnectionInfoFields();

    // 2. update login info fields
    executeUpdateLoginInfoFields();

    // 3. make the "selected" tab page the accessible one for the group
    tabGroup.addAccessibleSelection(selectedTabPage);

    // 4. check "editable" status for tab pages
    executeSetEditableTabPages(editableTabPages);

    setDefaultButton (CONNECT);
    setCancelButton (CANCEL);
  }

  private void setupKeyHandler () {
    java.awt.event.KeyListener stdKeyAdapter = getStandardKeyInterpreter ();
    connectionTabPanel.hostTextField.addKeyListener (stdKeyAdapter);
    connectionTabPanel.portTextField.addKeyListener (stdKeyAdapter);
    connectionTabPanel.urlTextField.addKeyListener (stdKeyAdapter);
    securityTabPanel.userNameTextField.addKeyListener (stdKeyAdapter);
    securityTabPanel.userModeTextField.addKeyListener (stdKeyAdapter);
    securityTabPanel.passwordTextField.addKeyListener (stdKeyAdapter);
  }

  private void executeUpdateConnectionInfoFields() {
    //System.out.println("LoginDialog.executeUpdateConnectionInfoFields");
    connectionTabPanel.hostTextField.setText(hostName);
    connectionTabPanel.portTextField.setText(portName);
    connectionTabPanel.urlTextField.setText(brokerURL);
  }

  private void executeUpdateLoginInfoFields() {
    //System.out.println("LoginDialog.executeUpdateLoginInfoFields");
    securityTabPanel.userNameTextField.setText(userName);
    securityTabPanel.userModeTextField.setText(userMode);
    securityTabPanel.passwordTextField.setText(password);
  }

  private void executeSetEditableTabPages(int editableTabPages) {
    if (editableTabPages == CONNECTION_AND_SECURITY_TAB_PAGES) {
      connectionTabPanel.setEditable(true);
      securityTabPanel.setEditable(true);
    } else if (editableTabPages == SECURITY_TAB_PAGE) {
      connectionTabPanel.setEditable(false);
      securityTabPanel.setEditable(true);
    } else if (editableTabPages == CONNECTION_TAB_PAGE) {
      connectionTabPanel.setEditable(true);
      securityTabPanel.setEditable(false);
    } else if (editableTabPages == NO_TAB_PAGES) {
      connectionTabPanel.setEditable(false);
      securityTabPanel.setEditable(false);
    }
  }

  /** Begin patch for e-SCOR,needed a way to control accessibility of panels.
   *  Add to T2 as new api
   *  @undocumented
   */
  public void setURLAndModeEditable(boolean textEditable, boolean modeEditable) {
	connectionTabPanel.urlTextField.setEditable(textEditable);
	securityTabPanel.userModeTextField.setEditable(modeEditable);
  }
  // end patch for e-SCOR

  /**
   * Sets the TwConnectionInfo object that is used for updating the text fields on the
   * Connection tab page. The text fields are immediately updated following this method call.
   * @see com.gensym.ntw.TwConnectionInfo
   * @see com.gensym.jgi.G2ConnectionInfo
   */
  public void setConnectionInformation(TwConnectionInfo connectionInfo) {
    //System.out.println("LoginDialog.setConnectionInformation: "+connectionInfo);
    currentConnectionInfo = connectionInfo;
    if (currentConnectionInfo.getHost() != null)
      hostName = currentConnectionInfo.getHost();
    if (currentConnectionInfo.getPort() != null)
      portName = currentConnectionInfo.getPort();
    if (currentConnectionInfo.getBrokerURL() != null)
      brokerURL = currentConnectionInfo.getBrokerURL();
    executeUpdateConnectionInfoFields();
  }

  /**
   * Gets the TwConnectionInfo object that contains the current values that are displayed
   * on the Connection tab page. Does basic checking to make sure that host and port values
   * entered are valid. If these checks fail, an error dialog is presented to the user and
   * this method returns null.
   * @see com.gensym.ntw.TwConnectionInfo
   * @see com.gensym.jgi.G2ConnectionInfo
   */
  public TwConnectionInfo getConnectionInformation() {
    TwConnectionInfo newInfo = null; //currentConnectionInfo;
    if (connectionTabPanel != null) {
      String host = connectionTabPanel.hostTextField.getText().trim();
      String port = connectionTabPanel.portTextField.getText().trim();
      String tmp = connectionTabPanel.urlTextField.getText().trim();
      String url = ("".equals(tmp) ? null : tmp);
      // validation
      if (connectionPanel.connectionPanel.checkHost() &&
	  connectionPanel.connectionPanel.checkPort())
	newInfo = new TwConnectionInfo(url, host, port);
    }
    return newInfo;
  }

  /**
   * Sets the LoginRequest object that is used for updating the text fields on the
   * Security tab page. The text fields are immediately updated following this method call.
   * @see com.gensym.ntw.LoginRequest
   */
  public void setLoginRequest(LoginRequest loginRequest) {
    //System.out.println("LoginDialog.setLoginRequest: "+loginRequest);
    currentLoginRequest = loginRequest;
    if (currentLoginRequest.getUserName() != null)
      userName = currentLoginRequest.getUserName().getPrintValue().toLowerCase();
    if (currentLoginRequest.getUserMode() != null)
      userMode = currentLoginRequest.getUserMode().getPrintValue().toLowerCase();
    executeUpdateLoginInfoFields();
  }

  /**
   * Gets the LoginRequest object that contains the current values that are displayed
   * on the Security tab page.
   * @see com.gensym.ntw.LoginRequest
   */
  public LoginRequest getLoginRequest() {
    LoginRequest newRequest = currentLoginRequest;
    if (securityTabPanel != null) {
      String mode = securityTabPanel.userModeTextField.getText().trim().toUpperCase();
      String name = securityTabPanel.userNameTextField.getText().trim().toUpperCase();
      String password = securityTabPanel.passwordTextField.getText().trim();
      Symbol password_ = null;
      if (!password.equals(""))
	password_ = Symbol.intern(password.toUpperCase());
      newRequest = new LoginRequest(Symbol.intern(mode), Symbol.intern(name), password_);
    }
    return newRequest;
  }

  /**
   * Sets which tab pages are to be editable or read-only
   * @param tabPages An integer specifying which tab pages are editable or read-only. Possible values
   * are: CONNECTION_TAB_PAGE, SECURITY_TAB_PAGE, CONNECTION_AND_SECURITY_TAB_PAGES, NO_TAB_PAGES.
   * @param isEditable A boolean value. A value of true indicates that the specified tab pages are
   * editable. A value of false indicates that the specified tab pages are read-only.
   */
  public void setEditableTabPages(int tabPages, boolean isEditable) {
    if (isEditable)
      editableTabPages = tabPages;
    else {
      // determine which tab pages are not editable
      if (tabPages == CONNECTION_TAB_PAGE)
	editableTabPages = SECURITY_TAB_PAGE;
      else if (tabPages == SECURITY_TAB_PAGE)
	editableTabPages = CONNECTION_TAB_PAGE;
      else if (tabPages == CONNECTION_AND_SECURITY_TAB_PAGES)
	editableTabPages = NO_TAB_PAGES;
    }
    executeSetEditableTabPages(editableTabPages);
  }

  /**
   * Gets which tab pages are set to be editable
   * @return An integer that specifies which tab pages are editable. Possible values are:
   * CONNECTION_TAB_PAGE, SECURITY_TAB_PAGE, CONNECTION_AND_SECURITY_TAB_PAGES, NO_TAB_PAGES.
   */
  public int getEditableTabPages() {
    return editableTabPages;
  }

  /**
   * Selects which tab page is the top most tab page.
   * @param tabPage An integer specifying which tab page to make the "selected" tab page.
   * Possible values are: CONNECTION_TAB_PAGE, SECURITY_TAB_PAGE.
   */
  public void selectTabPage(int tabPage) {
    selectedTabPage = tabPage;
    tabGroup.addAccessibleSelection(selectedTabPage);
  }

  /**
   * Called from StandardDialog to lay out buttons
   */
  @Override
  public int getButtonAlignment () {
    return CENTER;
  }
}

class TW2ConnectionPanel extends Panel {

  Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ShellDialogResources");

  TabGroupPanel connectionPanels;
  ConnectionPanel connectionPanel;
  SecurityPanel securityPanel;

  TW2ConnectionPanel () {
    connectionPanels = new TabGroupPanel();
    connectionPanels.addTab(shortBundle.getString("ConnectionTab"),
			    connectionPanel = new ConnectionPanel());
    connectionPanels.addTab(shortBundle.getString("SecurityTab"),
			    securityPanel = new SecurityPanel());
    add(connectionPanels);
  }
}

class ConnectionPanel extends StandardGridBagPanel {

  Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ShellDialogResources");

  TextField hostTextField;
  TextField portTextField;
  TextField urlTextField;

  boolean panelIsEditable = true;

  ConnectionPanel () {
    GridBagConstraints labelGridC = new GridBagConstraints();
    GridBagConstraints textGridC = new GridBagConstraints();
    setLayout (gridBagLayout);

    Insets firstLabelInsets = new Insets (10, 5, 5, 0);
    Insets labelInsets = new Insets (5, 5, 5, 0);
    Insets firstTextInsets = new Insets (10, 10, 5, 5);
    Insets textInsets = new Insets (5, 10, 5, 5);

    // set Label constraints
    labelGridC.gridwidth = 50;
    labelGridC.weightx = 0.0;
    labelGridC.fill = GridBagConstraints.NONE;
    labelGridC.anchor = GridBagConstraints.EAST;
    labelGridC.gridwidth = GridBagConstraints.RELATIVE;

    // set TextField constraints
    textGridC.weightx = 1.0;
    textGridC.gridwidth = 200;
    textGridC.fill = GridBagConstraints.HORIZONTAL;
    textGridC.anchor = GridBagConstraints.WEST;
    textGridC.gridwidth = GridBagConstraints.REMAINDER;

    labelGridC.insets = firstLabelInsets;
    addComponent(new Label(shortBundle.getString("ConnectHost")), labelGridC);

    textGridC.insets = firstTextInsets;
    addComponent(hostTextField = new TextField("", 20), textGridC);

    labelGridC.insets = labelInsets;
    addComponent(new Label(shortBundle.getString("ConnectPort")), labelGridC);

    textGridC.insets = textInsets;
    addComponent(portTextField = new TextField("", 20), textGridC);
    portTextField.addFocusListener(new FocusListener () {
      @Override
      public void focusGained (FocusEvent e) {}
      @Override
      public void focusLost (FocusEvent e) {
	// verify TextField contents
	if (!e.isTemporary ())
	  checkPort ();
      }
    });
    addComponent(new Label(shortBundle.getString("ConnectUrl")), labelGridC);
    addComponent(urlTextField = new TextField("", 20), textGridC);
  }

  boolean isEditable() {
    return panelIsEditable;
  }

  boolean checkHost () {
    String s = hostTextField.getText ();
    if ("".equals (s)) {
      //System.out.println ("Empty Host Field at :\n" + com.gensym.core.DebugUtil.getStackTrace ());
      return false;
    }
    try {
      java.net.InetAddress.getByName (s);
      return true;
    } catch (java.net.UnknownHostException uhe) {
      Trace.exception (uhe);
    }
    String title = shortBundle.getString("InvalidHostValueTitle");
    String text = shortBundle.getString("HostValueInstructions");
    ErrorDialog errDialog = new ErrorDialog (null, title,
					     true, text,
					     null);
    errDialog.setVisible(true);
    hostTextField.setText ("");
    hostTextField.requestFocus();
    return false;
  }

  boolean checkPort () {
    String s = portTextField.getText ();
    if ("".equals (s)) {
      //System.out.println ("Empty Port Field at :\n" + com.gensym.core.DebugUtil.getStackTrace ());
      return false;
    }
    try {
      int iValue = Integer.parseInt (s);
      if (iValue >= 0)
	return true;
    } catch (NumberFormatException nfe) {
      Trace.exception (nfe);
    }
    String title = shortBundle.getString("InvalidPortValueTitle");
    String text = shortBundle.getString("PortValueInstructions");
    ErrorDialog errDialog = new ErrorDialog (null, title,
					     true, text,
					     null);
    errDialog.setVisible(true);
    portTextField.requestFocus();
    portTextField.setText ("");
    return false;
  }

  void setEditable(boolean editable) {
    panelIsEditable = editable;
    hostTextField.setEditable(editable);
    portTextField.setEditable(editable);
    urlTextField.setEditable(editable);
  }
}

class SecurityPanel extends StandardGridBagPanel {
  Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ShellDialogResources");

  TextField userNameTextField;
  TextField userModeTextField;
  TextField passwordTextField;

  boolean panelIsEditable = true;

  SecurityPanel () {
    GridBagConstraints labelGridC = new GridBagConstraints();
    GridBagConstraints textGridC = new GridBagConstraints();
    setLayout (gridBagLayout);

    Insets firstLabelInsets = new Insets (10, 5, 5, 0);
    Insets labelInsets = new Insets (5, 5, 5, 0);
    Insets firstTextInsets = new Insets (10, 10, 5, 5);
    Insets textInsets = new Insets (5, 10, 5, 5);

    // set Label constraints
    labelGridC.gridwidth = 50;
    labelGridC.weightx = 0.0;
    labelGridC.fill = GridBagConstraints.NONE;
    labelGridC.anchor = GridBagConstraints.EAST;
    labelGridC.gridwidth = GridBagConstraints.RELATIVE;

    // set TextField constraints
    textGridC.weightx = 1.0;
    textGridC.gridwidth = 200;
    textGridC.fill = GridBagConstraints.HORIZONTAL;
    textGridC.anchor = GridBagConstraints.WEST;
    textGridC.gridwidth = GridBagConstraints.REMAINDER;

    labelGridC.insets = firstLabelInsets;
    addComponent(new Label(shortBundle.getString("UserName")), labelGridC);

    textGridC.insets = firstTextInsets;
    addComponent(userNameTextField = new TextField("", 20), textGridC);

    labelGridC.insets = labelInsets;
    addComponent(new Label(shortBundle.getString("UserMode")), labelGridC);

    textGridC.insets = textInsets;
    addComponent(userModeTextField = new TextField("", 20), textGridC);

    addComponent(new Label(shortBundle.getString("Password")), labelGridC);
    addComponent(passwordTextField = new TextField("", 20), textGridC);
    passwordTextField.setEchoChar('*');
  }

  boolean isEditable() {
    return panelIsEditable;
  }

  void setEditable(boolean editable) {
    panelIsEditable = editable;
    userNameTextField.setEditable(editable);
    userModeTextField.setEditable(editable);
    passwordTextField.setEditable(editable);
  }
}

