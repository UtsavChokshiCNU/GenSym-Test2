
package com.gensym.demos.multiplewkspapplet;

import java.awt.*;
import java.util.*;
import java.applet.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.wksp.*;
import com.gensym.draw.*;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.symbol.G2ClassSymbols;

/** A demonstration applet showing how to include a G2 workspace as part
 * of an applet.
 *
 */
public class MultipleWkspAppletWithLogin extends Applet implements
NtwNotificationHandler, java.awt.event.ActionListener {

  private Container loginUiHolder, wkspSelectionUiHolder, wkspHolder;
  
  protected TextField hostField;
  protected TextField portField;
  /** If this is non-empty when the getWkspButton is pressed, it causes
   * the applet to run in a "pure-Java", "three-tier" mode.
   */
  protected TextField urlField;
  protected TextField userNameField;
  protected TextField userModeField;
  protected TextField passwordField;
  protected Button loginButton;

  protected TextField workspaceNameField;
  protected Button getWkspButton;

  private TwAccess currentConnection;

  private MultipleWorkspacePanel view;

  static {
    // temp hack: netscape has problems with resources
    Resource.setResourceDebug(true);
  }

  // For translation of user-visible messages
  protected static Resource i18n =
  Resource.getBundle("com.gensym.demos.multiplewkspapplet.Messages");


  // Tracing tools
  protected static Resource i18nTrace =
  Resource.getBundle("com.gensym.demos.multiplewkspapplet.TraceMessages");
  protected static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.ntw", MultipleWkspAppletWithLogin.class);
  // only one of these is needed for an application, though one can
  // use more than one of these.
  private static TraceOut traceListener = new TraceOut();
  private static boolean trace = true;

  public MultipleWkspAppletWithLogin () {
    // Some parts of Sequioa generate user notification messages,
    // so it is a good idea to listen for them.
    NtwNotification.registerListener ((NtwNotificationHandler)this,
				      (NtwNotificationFilter)null);
  }

  @Override
  public String getAppletInfo() {
    return
      "Gensym JavaTeleWindows\n" +
      "Version 1.0 Alpha Rev 0\n" +
      "Copyright (C) 1986-2017 Gensym Corporation.\n" +
      //"Machine ID: " + machineID + "\n" +
      "All Rights Reserved.\n" +
      "Authors: Joe E. Devlin, Christine Hostage,\n" +
      "                Paul B. Konigsberg, Robert Penny, \n" +
      "                Vikram Pillai.\n" +
      "Squirrels: 3 1/8\n" +
      "________________________________________________________________";
  }

  private String[][] pinfo =
  {{"traceKeys",     "string",
    "space delimited set of string keys specifying general areas of tracing"},
   {"messages",      "string",
    "space delimited set of string keys specifying specific tracing messages"},
   {"language",      "string",
    "a valid ISO language code"},
   {"country",       "string",
    "a valid ISO country code"},
   {"variant",       "string",
    "the language variant"}
  };

  @Override
  public String[][] getParameterInfo() {
    return pinfo;
  }
    
  @Override
  public void init () {
    handleTraceParameters();
    handleLocaleParameters();

    buildUI();

    Trace.send(10, traceKey, i18nTrace, "showApplet");
    setVisible(true);
  }

  private void handleTraceParameters(){
    if (app) return;
    String traceKeys = getParameter("traceKeys");
    String messages = getParameter("messages");
    Trace.send(10, traceKey, i18nTrace, "initializeTracing");
    if (traceKeys != null) {
      Trace.setTraceOn(true);
      Trace.setExceptionTraceOn(true);
      traceListener.initialize(traceKeys, Trace.ALL_LEVELS, messages);
    }
  }

  private void handleLocaleParameters () {
    if (app) return;
    String language = getParameter("language");
    String country  = getParameter("country");
    String variant  = getParameter("variant");

    Locale defaultLocale = Locale.getDefault();
    
    if (language == null) language = defaultLocale.getLanguage();
    if (country == null) country = defaultLocale.getCountry();
    if (variant == null) variant = defaultLocale.getVariant();

    // fix this: need error checking here to see if it is really a valid
    // locale?
    try {
      Locale newLocale = new Locale(language, country, variant);
      Locale.setDefault(newLocale);
    } catch (Exception e) {
      Trace.exception(e, null);
    }
  }


  /** Builds the section on the right and left of the applet where users can
   * specify the important things such as "url", "host", "port",
   * and "workspace". Initializes the instance variables <code>urlField,
   * hostField, portField, </code>and <code>workspaceNameField</code>.
   * Adds the applet as an ActionListener to the getWkspButton.
   */
  protected void buildUI() {
    setLayout(new BorderLayout());
    buildLoginUI();
    validate();
  }

  private void buildLoginUI(){
    loginUiHolder = new SimpleContainer();
    GridBagLayout gridbag = new GridBagLayout();
    GridBagConstraints c = new GridBagConstraints();
    loginUiHolder.setLayout(gridbag);
    hostField = (TextField)addThing("host", new TextField("localhost"), c, gridbag, loginUiHolder);
    portField = (TextField)addThing("port", new TextField("1111"), c, gridbag, loginUiHolder);
    urlField = (TextField)addThing("brokerUrl", new TextField(), c, gridbag, loginUiHolder);
    userNameField = (TextField)addThing("userName", new TextField(), c, gridbag, loginUiHolder);
    userModeField = (TextField)addThing("userMode", new TextField(), c, gridbag, loginUiHolder);
    passwordField = (TextField)addThing("password", new TextField(), c, gridbag, loginUiHolder);
    passwordField.setEchoChar('*');
    loginButton = addButton(new Button(i18n.getString("login")), c, gridbag, loginUiHolder);

    workspaceNameField = (TextField)addThing("workspace", new TextField(), c, gridbag, loginUiHolder);
    getWkspButton = addButton(new Button(i18n.getString("getWksp")), c, gridbag, loginUiHolder);
    enableWkspSelection(false);

    add(loginUiHolder, BorderLayout.WEST);
  }

  /** Make a label/component pair, with the component as the last
   * thing in the row.
   */
  private Component addThing(String label,
			     Component cmp,
			     GridBagConstraints c,
			     GridBagLayout gridbag,
			     Container parent) {
    addLabel(label, c, gridbag, parent);
    c.fill = GridBagConstraints.BOTH;
    c.gridwidth = GridBagConstraints.REMAINDER;
    gridbag.setConstraints(cmp, c);
    parent.add(cmp);
    return cmp;
  }

  /** Make the label second-last in the row, and non-expandable.
   */
  private void addLabel(String label, GridBagConstraints c,
			GridBagLayout gridbag, Container parent) {
    c.gridwidth = GridBagConstraints.RELATIVE;
    c.fill = GridBagConstraints.NONE;
    Label labelThing = new Label(i18n.getString(label)+":", Label.RIGHT);
    gridbag.setConstraints(labelThing, c);
    parent.add(labelThing);
  }

  private Button addButton(Button button,
			   GridBagConstraints c,
			   GridBagLayout gridbag, 
			   Container parent){
    c.gridwidth = GridBagConstraints.REMAINDER;
    c.fill = GridBagConstraints.NONE;
    gridbag.setConstraints(button, c);
    parent.add(button);
    button.addActionListener(this);
    return button;
  }

  private void enableWkspSelection(boolean enable){
    workspaceNameField.setEnabled(enable);
    getWkspButton.setEnabled(enable);
  }

  /** Puts the <code>view</code> into a lightweight Container
   * in the "center" of the Applet.
   */
  private void buildWkspHolder() {
    if (wkspHolder != null) {
      return;
    }

    wkspHolder = new SimpleContainer();
    wkspHolder.setLayout (new BorderLayout ());

    if (view == null)
      view = new MultipleWorkspacePanel();
    wkspHolder.add(view, BorderLayout.CENTER);
    add(wkspHolder, BorderLayout.CENTER);

    // hook up the containment tree
    validate();
  }

  /** This is the method that actually reads the values out of
   * the user-input fields on the right of the applet, then uses
   * that information to get the workspace from the specified G2.
   */
  @Override
  public void actionPerformed(java.awt.event.ActionEvent event) {
    Object source = event.getSource();
    try{
      if (loginButton.equals(source)){
	currentConnection = TwGateway.openConnection(getConnectionInfo());
	if (!currentConnection.isLoggedIn())
	  currentConnection.login(getLoginRequest());
	enableWkspSelection(true);
	currentConnection.addWorkspaceShowingListener(view);
      }
      else {
	KbWorkspace wksp = 
	  (KbWorkspace)currentConnection.getUniqueNamedItem(G2ClassSymbols.KB_WORKSPACE_, 
					       getWorkspaceName());
	view.addWorkspace(wksp);
	view.setCurrentWorkspace(wksp);
	validate();
      }
    }
    catch(G2AccessException ex){
      ex.printStackTrace();
    }
  } 

  private TwConnectionInfo getConnectionInfo(){
    String host = hostField.getText().trim();
    String port = portField.getText().trim();
    String url = urlField.getText().trim();
    // Clean up the url not to pass in an empty string
    if ("".equals(url))
      url = null;
    return new TwConnectionInfo(url, host, port, /* want sharable connections */ false, true);
  }

  private LoginRequest getLoginRequest(){
    LoginRequest newRequest;
    String mode = userModeField.getText().trim().toUpperCase();
    String name = userNameField.getText().trim().toUpperCase();
    String password = passwordField.getText().trim();
    Symbol password_ = null;
    if (!password.equals(""))
      password_ = Symbol.intern(password.toUpperCase());
    newRequest = new LoginRequest(Symbol.intern(mode), Symbol.intern(name), password_);
    return newRequest; 
  }

  private Symbol getWorkspaceName(){
    return Symbol.intern(workspaceNameField.getText().trim().toUpperCase());
  }

  @Override
  public void start() {
    // For some reason, it is best not to build the wkspHolder
    // in the init() method along with the uiHolder. It works
    if (wkspHolder == null)
      buildWkspHolder();
    super.start();
  }

  /**
   * The application needs to know how to route notification
   * messages. It needs access to the UI if the message is
   * to be conveyed to the user.
   */

  @Override
  public void handleNtwNotification (NtwNotification notfn) {
    System.out.println ("Telewindows handling Notification: " + notfn);
    if (notfn.notfnCode == NtwNotification.TIMEOUT) {
      showStatus(notfn.details);
    }
    else if (notfn.notfnCode == NtwNotification.UPDATE) {
      showStatus(notfn.details);
    }
    System.out.println ("Unhandled Notification: " + notfn.details);
  }

  @Override
  public void update(Graphics g) {
    paint(g);
  }

  private boolean app = false;

  MultipleWkspAppletWithLogin(boolean app){
    this.app = app;
  }

  public static void main(String[] args){
    Frame f = new Frame();
    Applet a = new MultipleWkspAppletWithLogin(true);
    a.init();
    a.start();
    f.add(a);
    f.setSize(500, 500);
    f.setVisible(true);
    
  }
  
}

class SimpleContainer extends Container {
}
