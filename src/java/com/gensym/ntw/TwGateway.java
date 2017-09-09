/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwGateway.java
 *
 */
package com.gensym.ntw;

import java.lang.reflect.Method;
import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Vector;
import java.util.Locale;
import java.net.MalformedURLException;
import java.nio.charset.Charset;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.*;
import com.gensym.jgi.*;
import com.gensym.core.GensymApplication;
import com.gensym.classes.Item;
import com.gensym.classes.Kb;
import com.gensym.classes.TrendChart;
import com.gensym.irm.IconRenderingManager;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.UserMenuChoice;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.classes.UiClientSession;
import com.gensym.classes.Message;

import com.gensym.dlgruntime.DialogManager;
import com.gensym.dlgruntime.DialogManagerFactory;
import com.gensym.dlgruntime.DefaultDialogManagerFactory;

import com.gensym.ntw.util.FileProgressListener;
import com.gensym.ntw.util.FileProgressEvent;
import com.gensym.ntw.util.UnsolicitedDialogListener;
import com.gensym.ntw.util.UnsolicitedDialogEvent;
import com.gensym.ntw.util.PackagePreparationListener;
import com.gensym.ntw.util.PackagePreparationEvent;

/**
 * Main class to make a Telewindows connection to G2
 * Requires a floating TW license or an Ok file to be
 * able to make a connection.  This enables it to use the 
 * restricted protocols to represent workspaces and other 
 * interesting classes in G2.
 *
 *  @author  mgribble 05/97
 *  @author  vkp
 *  @author  rpenny
 *  @author  ddm 
 *
 */
public class TwGateway extends G2Gateway implements TwConnection {

  private static final Symbol[] neededUiClientSessionAttributes =
  new Symbol[] {com.gensym.util.symbol.SystemAttributeSymbols.UI_CLIENT_SESSION_USER_MODE_};
  static final
  String DEFAULT_TWO_TIER_CLASS_NAME =
  "com.gensym.ntw.TwGateway",
    DEFAULT_RMI_CLASS_NAME =
  "com.gensym.ntw.rmi.TwRMIClientImpl",
    DEFAULT_GSI_CLASS_NAME = "UI-CLIENT-INTERFACE";

  private static final Symbol LEFT_ = Symbol.intern ("LEFT"),
    TOP_ = Symbol.intern ("TOP"),
    RIGHT_ = Symbol.intern ("RIGHT"),
    BOTTOM_ = Symbol.intern ("BOTTOM");
  /**
   * @undocumented
   */
  protected static final Symbol WORKSPACE_INITIAL_DATA_ = Symbol.intern("WORKSPACE-INITIAL-DATA");
  /**
   * @undocumented
   */
  protected static final Symbol ITEM_INITIAL_DATA_ = Symbol.intern("ITEM-INITIAL-DATA");

  private static int G2APITimeout = 0; // indefinite
  private static int XnTimeout = 20000;
  private Vector packagePreparationListeners = new Vector(5);

  /**
   * @undocumented
   */
  protected static MessageKey wsTraceKey =
  Trace.registerMessageKey("com.gensym.wksp", TwGateway.class);

  private static Resource wsTraceBundle =
  Trace.getBundle("com.gensym.wksp.TraceMessages");

  private static final MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.ntw", TwGateway.class);

  private static final Resource traceBundle =
  Trace.getBundle("com.gensym.ntw.TraceMessages", Locale.getDefault());

  private static final MessageKey itemTrace =
  Trace.registerMessageKey("com.gensym.item", TwGateway.class);

  private static final MessageKey moduleTrace =
  Trace.registerMessageKey ("com.gensym.module", TwGateway.class);

  private static Resource i18n = Resource.getBundle("com.gensym.ntw.Messages");
  
  /**
   * @undocumented
   */
  public static final boolean traceOn = false;


  // Introspection G2 API entry points
  // *****************************************************

  /**
   * @undocumented
   */
  protected static final Symbol
    SUBSCRIPTION_HANDLE_                     = Symbol.intern ("SUBSCRIPTION-HANDLE"),
    HANDLE_WORKSPACE_SUBSCRIPTIONS_          = Symbol.intern ("HANDLEWORKSPACESUBSCRIPTIONS"),
    HANDLE_TREND_CHART_SUBSCRIPTIONS_        = Symbol.intern ("HANDLETRENDCHARTSUBSCRIPTIONS"),
    HANDLE_WORKSPACES_SHOWING_SUBSCRIPTIONS_ = Symbol.intern ("HANDLEWORKSPACESSHOWINGSUBSCRIPTIONS"),
    HANDLE_FIELD_EDIT_SUBSCRIPTIONS_ = Symbol.intern ("HANDLEFIELDEDITSUBSCRIPTIONS"),
    SET_DIALOG_RESOURCE_ENTRY_ = Symbol.intern ("SET-DIALOG-RESOURCE-ENTRY");

  private static final Symbol
    G2_REPRESENT_WORKSPACE_         = Symbol.intern ("G2-REPRESENT-WORKSPACE"),
    G2_UNREPRESENT_WORKSPACE_       = Symbol.intern ("G2-UNREPRESENT-WORKSPACE"),
    G2_REPRESENT_TREND_CHART_       = Symbol.intern ("G2-REPRESENT-TREND-CHART"),
    G2_CHANGE_MODE_FOR_WINDOW_      = Symbol.intern ("G2-CHANGE-MODE-FOR-WINDOW"),
    G2_GET_LIST_OF_WORKSPACES_      = Symbol.intern ("G2-GET-LIST-OF-WORKSPACES"),
    G2_GET_FORMAT_INFO_             = Symbol.intern ("G2-GET-FORMAT-INFO"),
    G2_FINISH_FIELD_EDIT_AND_RECORD_STATUS_
       = Symbol.intern ("G2-FINISH-FIELD-EDIT-AND-RECORD-STATUS"),
    G2_UPDATE_UI_CLIENT_SESSION_FIELD_EDIT_
       = Symbol.intern ("G2-UPDATE-UI-CLIENT-SESSION-FIELD-EDIT"),
    G2_GET_DIALOG_                  = Symbol.intern ("G2-GET-DIALOG"),
    G2_GET_USER_MENU_CHOICE_        = Symbol.intern ("G2-GET-USER-MENU-CHOICE");

  private static final Symbol 
    TEST_RPC_NAME_                        = Symbol.intern ("G2-API-BOGUS-3"),
    G2_SUBSCRIBE_TO_WORKSPACES_SHOWING_   = Symbol.intern ("G2-SUBSCRIBE-TO-WORKSPACES-SHOWING"),
    G2_UNSUBSCRIBE_TO_WORKSPACES_SHOWING_ = Symbol.intern ("G2-UNSUBSCRIBE-TO-WORKSPACES-SHOWING"),
    G2_SUBSCRIBE_TO_FIELD_EDIT_ACTIONS_ = Symbol.intern ("G2-SUBSCRIBE-TO-FIELD-EDIT-ACTIONS"),
    G2_UNSUBSCRIBE_TO_FIELD_EDIT_ACTIONS_ = Symbol.intern ("G2-UNSUBSCRIBE-TO-FIELD-EDIT-ACTIONS"),
    G2_SUBSCRIBE_TO_MODULES_              = Symbol.intern ("G2-SUBSCRIBE-TO-MODULES"),
    G2_UNSUBSCRIBE_TO_MODULES_            = Symbol.intern ("G2-UNSUBSCRIBE-TO-MODULES");
  private static final Symbol G2_VALIDATE_NAMED_TW2_ =
    Symbol.intern ("G2-VALIDATE-NAMED-TW2");
  private static final Symbol G2_MAKE_UI_CLIENT_SESSION_ =
    Symbol.intern ("G2-MAKE-UI-CLIENT-SESSION");
  private static final Symbol G2_RELEASE_UI_CLIENT_SESSION_ =
    Symbol.intern ("G2-RELEASE-UI-CLIENT-SESSION");
  

  private static Symbol HANDLEITEMSUBSCRIPTIONS_
  = Symbol.intern("HANDLEITEMSUBSCRIPTIONS");
  private static Symbol HANDLEMODULESUBSCRIPTIONS_
  = Symbol.intern("HANDLEMODULESUBSCRIPTIONS");

  private static volatile DialogManagerFactory dialogManagerFactory =
  new DefaultDialogManagerFactory();

  private Integer workspacesShowingSubscriptionHandle;
  private volatile WorkspaceShowingListener workspaceShowingListener;
  private volatile FileProgressListener fileProgressListener;
  private volatile UnsolicitedDialogListener unsolicitedDialogListener;  
  
  private Integer fieldEditSubscriptionHandle;
  private volatile Vector fieldEditListeners = new Vector();
  private boolean subscribedToFieldEditActions = false;

  private IconRenderingManager irm;
  private DialogManager dialogManager;
  private com.gensym.classes.Kb kb;

  public static void setDialogManagerFactory(DialogManagerFactory factory) {
    if (factory == null)
      throw new IllegalArgumentException(i18n.getString("twgNullFactory"));
    dialogManagerFactory = factory;
  }

  public static DialogManagerFactory getDialogManagerFactory() {
    return dialogManagerFactory;
  }

  /**
   * @undocumented
   */
  protected UiClientSession uiClientSession;
  private boolean uiClientSessionOK = false;

  /**
   * For testing only.
   * @deprecated
   * @undocumented
   */
  public TwGateway() {
    initializeInstance0 ();
  }

  // need something to help with the memory leaks. I will uncomment
  // or delete this when fixing the fact that opening and closing
  // a connection leaks about a meg
//   /**
//    * @undocumented
//    */
//   protected void dispose(){
//     super.dispose();
//     workspaceShowingListener = null;
//   }

  /** Enables the gateway to have a fully-fledged user-interface-enabled
   * connection to G2. Must first connect to G2 using one of the
   * connect methods.
   * @param loginRequest user profile information
   * @see #openConnection(TwConnectionInfo)
   * @throws AlreadyLoggedInException if the connection is already logged in.
   * @throws G2AccessException if an error occured while trying to communicate
   * with G2.
   */
  @Override
  public void login(LoginRequest loginRequest) throws G2AccessException {
    loginSession(loginRequest);
  }

  /** Enables the gateway to have a fully-fledged user-interface-enabled
   * connection to G2. Must first connect to G2 using one of the
   * openConnection methods.
   * @param login user profile information
   * @see #openConnection(TwConnectionInfo)
   * @throws AlreadyLoggedInException if the connection is already logged in.
   * @throws G2AccessException if an error occured while trying to communicate
   * with G2.
   * @deprecated
   * @see #login
   */
  @Override
  public void loginSession(final LoginRequest login) throws G2AccessException {
    if (uiClientSession != null)
      throw new AlreadyLoggedInException(i18n.format("alreadyLoggedIn",
						     uiClientSession.getUiClientUserName()));

    LoginRequest loginReq = login;
    if (loginReq == null)
      loginReq = new LoginRequest();
    
    if (nonce == null)
      nonce = allocateSessionId();
    loginReq.setNonce(nonce);
    
    //System.out.println("Make UIClientSession ....");
    uiClientSession = makeUiClientSession(loginReq, workspaceShowingListener);
    uiClientSessionOK = true;
    //System.out.println("dispatch tw connectionEvent ...");
    dispatchTwConnectionEvent (new TwConnectionEvent(this, TwConnectionEvent.CONNECTION_LOGGED_IN, loginReq.userMode));
    try {
      //System.out.println("add item listener ...");
	uiClientSession.addItemListener (new SessionListener (this),neededUiClientSessionAttributes);
    } catch (G2AccessException gae) {
      /* We need to swallow this!
       * Callers need not know how this is implemented*/
      Trace.exception (gae);
    }
  }

  /**
   * @undocumented
   */
  // should take a String for the exception
  protected void checkLoggedIn() throws NotLoggedInException {
    if (uiClientSession == null)
      throw new NotLoggedInException();
  }

  /**
   * Indicates if this TwAccess has an active login session
   * with G2. This is necessary to call some methods on
   * this TwGateway, such as <code>changeUserMode</code>.
   * @return true if the TwAccess is logged in, false otherwise
   */
  @Override
  public boolean isLoggedIn() {
    return uiClientSessionOK;
  }

  /**
   * Calls <code>login(new LoginRequest())</code>. Convenience method.
   */
  @Override
  public void login() throws G2AccessException {
    login(new LoginRequest());
  }

  /**
   * Calls <code>loginSession(new LoginRequest())</code>. Convenience method.
   * @deprecated
   * @see #login
   */
  @Override
  public void loginSession() throws G2AccessException {
    loginSession(new LoginRequest());
  }

  @Override
  public UiClientSession retrieveSession(Object requestor) {
    return retrieveSession();
  }

  /**
   * Returns the ui-client-session for this connection.
   * The session object has a one-to-one relationship with this
   * connection, which persists for the lifetime of both.
   * @return the session object
   */
  @Override
  public UiClientSession retrieveSession()
  {
    return uiClientSession;
  }

  private static final Symbol G2_ALLOCATE_SESSION_ID_ = Symbol.intern ("G2-ALLOCATE-SESSION-ID");

  /**
   * @undocumented
   */
  protected String allocateSessionId() throws G2AccessException {
    Object[] args = {};

    return (String)callRPC(G2_ALLOCATE_SESSION_ID_, args);
  }

  private String nonce;

  private static final Symbol SESSION_ITEM_ = Symbol.intern ("SESSION-ITEM");

  private static final Symbol ADMINISTRATOR_ = Symbol.intern ("ADMINISTRATOR");



  //---- Locals and methods for ok-based authorization

  /* These are methods rather than simple instance variables as syntactic
   * sugar in case all this has to 'go native' for security purposes, in
   * which case the modularity will already be in place. */

  /* Policy variable */
  private boolean allowFloaterAccessIfMachineIDUnavailable = true;


  /* First we need to be able to get the id of the machine that we're
   * presently running on. By its nature this entails accessing native
   * code. 
   *   The native function is part of JgiInterface. */

  private String machineID;
  private boolean machineIDHasBeenGotten = false;

  private String getMachineID() throws OkException {
    if ( !machineIDHasBeenGotten ) {
      try {
	machineID = new GetMachineID().getLocalMachineID(); // native
	//System.out.println("Retrieved machine id: \"" + machineID + "\"");
	//machineID = "00609758605D"; // testing hack -- ddm's pc
	machineIDHasBeenGotten = true;
      } catch (UnsatisfiedLinkError e) {
	if ( !allowFloaterAccessIfMachineIDUnavailable )
	  throw new OkException("Unable to link to MachineID library");
      }
    }
    return machineID;
  }



  /* This stores contents of the authorizing entry from the ok file. */
  private OkInfo okInfo;


  /* If there is an ok file then that is the basis of the authorization
   * to log in. If there is one, its name will be included as part of
   * the login information. */
  private boolean authorizationIsOkBased = false;
  private boolean okBasedAuthorization() { return authorizationIsOkBased; }
  private void checkForOkBasedAuthorization(LoginRequest login) {
    if ( login.okFile != null )
      authorizationIsOkBased = true;
  }


  /* We only check once for the presence of an ok file and it's validity. */
  private boolean authorizationChecked = false;
  private boolean hasAuthorizationBeenChecked() { return authorizationChecked; }
  private void authorizationHasBeenChecked() { authorizationChecked = true; }


  /* Records the conclusions reached by the call to vetOkInfo, which
   * is called only once whereas the calls to log into secure G2s might
   * be called several times if the user mistypes their password. */
  private boolean authorized = false;
  private void setAuthorization(boolean b) { authorized = b; }
  private boolean getAuthorization() { return authorized; }

  private boolean allowedToLogin() {
    if ( okBasedAuthorization() )
      return ( authorizationChecked && authorized );
    else
      return true;
  }


  /* This unpacks the OkInfo into an rpc call that checks whether the
   * the codes it gets are correct for that machine and products */
  private boolean vetOkInfo(String nonce, OkInfo info)
  throws G2AccessException {
    Trace.send(1, traceKey, traceBundle, "OkInformation", info.describe());
    Object[] args =
    {nonce,
     info.getMachineID(),
     info.getCode1(),
     info.getCode2(),
     info.getCode3(),
     info.getCode4(),
     info.getCode5(),
     info.getFrom(),
     info.getTo(),
     info.getLevel()
    };

    Object value;
    value = (Object)callRPC(G2_VALIDATE_NAMED_TW2_, args);

    if (value instanceof Boolean) {
      authorized = ((Boolean)value).booleanValue();
    }
    else if (value instanceof Symbol) {
      authorized = false;
      throw new OkException( ((Symbol)value).getPrintValue() );
    }
    else {
      authorized = false;
      throw new OkException(i18n.getString("unknownReturnValueFromValidateRPC"));
    }
    return authorized;
  }
    

  /**
   * Initiates a login to G2 and returns the ui-client-session
   * for this connection. 
   * @undocumented
   * @see #releaseUiClientSession
   */
  protected UiClientSession makeUiClientSession(LoginRequest login,
						WorkspaceShowingListener listener)
  throws G2AccessException{

    Structure struct = null;

    /* We need to enforce the policy that if there's an ok file you can't login
     * via a floating license, rather this machine has to be in that ok file and 
     * have valid codes.
     *   That will be determined the first time a call is made to makeUiClientSession.
     * Not only shouldn't the checking for a valid named authorization be made on
     * subsequent attempts (a waste of computation), but we should also reflexively
     * fail any subsequent attempt when it is already known that the authorization
     * didn't go through. 
     *   If someone cracks this part of the code so as to eliminate the checks
     * against the ok file, the upshot will be that they will be able to
     * log in and get a ui-client-session provided that there is a floating
     * license available on the G2 they are connecting to. If that turns out
     * to eventually be unacceptable to management (it is ok circa 11/98)
     * then the whole login transaction will have to be pushed into native
     * code so that the logging in per se cannot be separated from checks
     * against the ok file. */
    if ( !hasAuthorizationBeenChecked() ) {

      checkForOkBasedAuthorization(login);
      
      if ( okBasedAuthorization() ) {

	machineID = getMachineID();
	
	if ( machineID == null ) {

	  if ( allowFloaterAccessIfMachineIDUnavailable )
	    setAuthorization( true );
	  else
	    throw new OkException(i18n.getString("nullMachineID"));
	}
	else {

	  Reader r = null;
	  try {
	    r = new InputStreamReader( new FileInputStream(login.okFile), Charset.defaultCharset());
	    okInfo = new OkInfo();
	    if ( OkParser.findMachineIDInTw2OkFile(r, okInfo, machineID, login.okFile) ) {
	      /* findMachine... is what parses the Ok file. If it finds an
	       * entry for this machine it populates the OkInfo object. If there's
	       * a problem it will throw an OkException */
	      vetOkInfo(nonce, okInfo);
	    }
	    else {
	      setAuthorization( false );
	    }
	    
	  } catch (FileNotFoundException e) {
	    setAuthorization( false );
	    throw new OkException(i18n.format("OkFileNotFound", login.okFile));
	  } catch (IOException e) {
	    setAuthorization( false );
	    throw new OkException(i18n.format("OkIOException", login.okFile));
	  } finally {
	    try {
	      if ( r != null )
		r.close();
	    } catch (IOException e) {
	      Trace.exception(e);
	    }
	  }
	}
      }
      authorizationHasBeenChecked();
    }
      
    
    if ( !allowedToLogin() ) 
      throw new OkException(i18n.getString("loginNotPermitted"));


    Object[] args =
    {login.getNonce(),
     (login.userMode == null ? ADMINISTRATOR_ : login.userMode),
     login.userName,
     login.getEncodedPassword(),
     login.userNameFromSystem,
     login.language,
     login.hostName,
     login.osType,
     listener == null ?
     null :
     //HANDLE_WORKSPACES_SHOWING_SUBSCRIPTIONS_ : // for easy debugging
     HANDLE_WORKSPACES_SHOWING_SUBSCRIPTIONS_};
    
    struct = (Structure)callRPC(G2_MAKE_UI_CLIENT_SESSION_, args);
    
    UiClientSession session =
      (UiClientSession)struct.getAttributeValue(SESSION_ITEM_, null);
    
    Symbol error = (Symbol)struct.getAttributeValue(ERROR_SYMBOL_, null);
    
    if (TOO_MANY_LOGIN_ATTEMPTS_.equals(error)) {
      nonce = null;
      closeConnection();
      throw new TooManyLoginAttemptsException(error.getPrintValue());
    } else if (error != null)
      throw new LoginFailedException(error.getPrintValue());
    else
      nonce = null;
    
    Integer subscpnHandle =
      (Integer)struct.getAttributeValue(WORKSPACE_SHOWING_HANDLE_, null);

    // if listener != null, subscpnHandle should not be null

    if (listener != null) {
      workspacesShowingSubscriptionHandle = subscpnHandle;
      // NOTE: This entry in the subscriptionTable is really only
      // used by three-tier, so my apologies for putting
      // infrastructure only used by a subclass in here.
      getSubscpnTable().put(subscpnHandle, listener);
    }

    return session;
  }

  private static final Symbol WORKSPACE_SHOWING_HANDLE_ = Symbol.intern ("WORKSPACE-SHOWING-HANDLE");

  private static final Symbol ERROR_SYMBOL_            = Symbol.intern ("ERROR-SYMBOL");
  private static final Symbol TOO_MANY_LOGIN_ATTEMPTS_ = Symbol.intern ("TOO-MANY-LOGIN-ATTEMPTS");

  /**
   * Logs out the session without closing the connection. Allows
   * the connection to be logged in with (for example) a different
   * user.
   * @throws G2AccessException if there is a problem communicating
   * with G2.
   */
  @Override
  public void logout() throws G2AccessException {
    releaseUiClientSession(uiClientSession);
  }


  /**
   * Logs out the session without closing the connection. Allows
   * the connection to be logged in with (for example) a different
   * user.
   * @deprecated use logout() instead
   * @see #logout()
   */
  public void logoutSession() throws G2AccessException {
    logout();
  }

  /**
   * Shuts down the user session with G2. Does not actually
   * close the connection.
   * @undocumented
   */
  protected void releaseUiClientSession (UiClientSession session)
  throws G2AccessException{
    checkLoggedIn();
    if (session.isValid()) {
      try {
	callRPC(G2_RELEASE_UI_CLIENT_SESSION_, new Object[] {session});
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    uiClientSession = null;
    uiClientSessionOK = false;
  }

  /**
   * Creates a new connection object and initiates a connection
   * at the specified host and port.
   * @see #openConnection(TwConnectionInfo)
   */
  public static TwAccess openConnection (String host, String port)
  throws ConnectionTimedOutException, G2AccessInitiationException {
    return openConnection(null, host, port);
  }

  /**
   * Creates a new connection object and initiates a connection
   * at the specified host and port via the middle tier at the
   * specified brokerURL.
   * @see #openConnection(TwConnectionInfo)
   */
  // is not fully object-oriented with respect to
  // G2Gateway.getOrMakeConnection(): a factory instance would allow
  // for better inheritance structure.
  public static TwAccess openConnection (String brokerURL, String host, String port)
     throws ConnectionTimedOutException, G2AccessInitiationException {
  TwConnectionInfo info =
    new TwConnectionInfo(brokerURL, 
			 host, 
			 port,
			 true,
			 false);

  return openConnection(info);
  }


  /**
   * Creates a new user connection with G2. This connection
   * is not "logged in", so
   * the connection can only do things that were available in G2Gateway.
   * To do more, the session must be logged in using <code>login</code>.
   * @exception ConnectionTimedOutException when a new connection is not
   * initiated within the default timeout
   */
  public static TwAccess openConnection (TwConnectionInfo info)
  throws ConnectionTimedOutException, G2AccessInitiationException {
    return (TwAccess)getOrMakeConnection(info);
  }

  /**
   * Initialize all Local RPC's used by the introspection RPC
   */
  @Override
  protected void initializeLocalRPCs () {
    super.initializeLocalRPCs();

    try {
      java.lang.reflect.Method hwsMethod = 
	TwGateway.class.getDeclaredMethod("HANDLEWORKSPACESUBSCRIPTIONS",
					  new Class[] {SYMBOL_CLASS, 
							 ITEM_CLASS, 
							 Structure.class, 
							 Integer.TYPE} );

      
      registerJavaMethod(this, 
			 hwsMethod,
			 HANDLE_WORKSPACE_SUBSCRIPTIONS_,
			 DONT_CALL_METHOD_IN_NEW_THREAD);
    } catch (NoSuchMethodException e) {
      Trace.exception(e, "Can not find TwGateway.HANDLEWORKSPACESUBSCRIPTIONS Method");
      throw new NoSuchMethodError(i18n.getString("noHandleWorkspaceSubscriptionsMethod"));
    } 
    
   
    registerJavaMethod (this, TwGateway.class,
			"HANDLETRENDCHARTSUBSCRIPTIONS",
			new Class[] {Integer.TYPE, ITEM_CLASS,
				       SYMBOL_CLASS, Structure.class},
			HANDLE_TREND_CHART_SUBSCRIPTIONS_,
			DONT_CALL_METHOD_IN_NEW_THREAD);

    registerJavaMethod (this,
			"HELLO",
			Symbol.intern ("HELLO"));
    registerJavaMethod (this,
			"HANDLEWORKSPACESSHOWINGSUBSCRIPTIONS",
			HANDLE_WORKSPACES_SHOWING_SUBSCRIPTIONS_ );
    registerJavaMethod (this,
			"HANDLEFIELDEDITSUBSCRIPTIONS",
			HANDLE_FIELD_EDIT_SUBSCRIPTIONS_ );    

    registerJavaMethod (this,
			"SETDIALOGRESOURCEENTRY",
			SET_DIALOG_RESOURCE_ENTRY_);

    registerJavaMethod (this,
			"HANDLEMODULESUBSCRIPTIONS",
			HANDLEMODULESUBSCRIPTIONS_);

    registerJavaMethod(this,
		       fileProgressCallbackMethod,
		       FILE_PROGRESS_CALLBACK_,
		       false);
    registerJavaMethod(this,
		       unsolicitedDialogsCallbackMethod,
		       UNSOLICITED_DIALOGS_CALLBACK_,
		       false);        
    try {
      Method handleSubsMethod = 
	TwGateway.class.getDeclaredMethod("HANDLEITEMSUBSCRIPTIONS", 
					  new Class[] {SYMBOL_CLASS, 
							 ITEM_CLASS, 
							 SEQUENCE_CLASS, 
							 OBJECT_CLASS, 
							 OBJECT_CLASS, 
							 Integer.TYPE});
      
      registerJavaMethod (this, handleSubsMethod, HANDLEITEMSUBSCRIPTIONS_, false);
    } catch (NoSuchMethodException e) { 
      // This is serious
      System.err.println("Cant Find HANDLESUBSCRIPTIONS Method !!! ");
      e.printStackTrace();
      System.exit(0);
    }
  }

  /**
   * Initialize all Remote RPC's used by the introspection API needed for a connection
   * This method will be called just before G2InitializeConnection is called.
   * Users should never need to call this directly.
   * NOTE: Subclasses who override this method must call super.initializeConnectionRPCs()
   */
  @Override
  protected void initializeConnectionRPCs() {
    super.initializeConnectionRPCs();

    /* Initialize G2 introspection API */

    // Set return types for procedures returning items 2/4/97
    setRemoteRPCReturnKind (G2_GET_USER_MENU_CHOICE_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_REPRESENT_WORKSPACE_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (TEST_RPC_NAME_, 2 /*PASS_BY_COPY_WITH_HANDLE*/);
    setRemoteRPCReturnKind (G2_GET_DIALOG_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_SUBSCRIBE_TO_MODULES_, PASS_BY_HANDLE);
  }


  /**
   * Returns the mininum version of G2 that we are allowed to
   * make a connection to. This is inherited from G2Gateway
   * and is overriden by any subclass
   * to indicate that those type of connections may only be made
   * to newer versions of G2. The minumum version can change
   * with every release of Telewindows2.
   * @return a G2Version describing the oldest G2 we expect to talk to
   */
  @Override
  public G2Version getMinimumVersion () {
    return new G2Version (5, 1, "Rev", 0, "H06");
  }

  /**
   * Returns the ui-client-session for this connection.
   * The session object has a one-to-one relationship with this
   * connection, which persists for the lifetime of both.
   * @return the session object
   * @deprecated use retrieveSession instead
   * @see #retrieveSession
   */
  @Override
  public com.gensym.classes.UiClientSession getSession () {
    return uiClientSession;	// may be null?
  }

  private Boolean dlgProcedureExists; // When to invalidate this? Clear, Load, ?
  private static final Symbol PROCEDURE_ = Symbol.intern ("PROCEDURE");

  /**
   * @deprecated
   * @undocumented
   */
  @Override
  public Structure getDialog (Item itm, Symbol userMode, Structure locale) throws G2AccessException {
    if (dlgProcedureExists == null) {
      try {
	Item procedure = getUniqueNamedItem (PROCEDURE_, G2_GET_DIALOG_);
	dlgProcedureExists = Boolean.TRUE;
      } catch (G2AccessException g2ae) { // Assume does not exist
	dlgProcedureExists = Boolean.FALSE;
      }
    }
    if (dlgProcedureExists.equals (Boolean.FALSE))
      return null;
    Object[] args = {itm, userMode, locale};
    Structure result = (Structure) callRPC(G2_GET_DIALOG_, args);
    return result;
  }

  /**
   * Turns on subscriptions for changes happening on the kb-workspace
   * argument. The return value is a structure that describes the initial
   * state of the workspace, against which all changes are reported.
   * @param workspace the kb-workspace for which we are interested in
   *   receiving events
   * @exception G2AccessException if there is an error while communicating
   *   with G2 or if the call is in error
   * @undocumented For Gensym private use only.
   */
  @Override
  public Structure representWorkspace (KbWorkspace workspace) throws G2AccessException {
    Structure wsinfo = representWorkspace (workspace,
					   HANDLE_WORKSPACE_SUBSCRIPTIONS_);
    Trace.send(5, wsTraceKey, wsTraceBundle, "WsSubscription", wsinfo);
    //    Trace.writeObjectToFile(5, wsTraceKey,
    //		    "c:\\TEMP\\trendchart" + workspaceHandle + ".ser",
    //		    wsinfo);
    if (wsinfo != null) {
      Integer subscrpnHandle = (Integer) wsinfo.getAttributeValue(SUBSCRIPTION_HANDLE_, null);
      getSubscpnTable().put(subscrpnHandle, workspace);
    }
    Trace.send(5, wsTraceKey, wsTraceBundle, "WsSubscription", wsinfo);
    return wsinfo;
  }

  /**
   * @undocumented Who calls this?
   */
  protected Structure representWorkspace (KbWorkspace workspace, Symbol callback) throws G2AccessException {

    checkLoggedIn();
    Object[] args = {uiClientSession, workspace, callback};
    //System.out.println ("represent (" + uiClientSession + ", " + workspace + ")");
    return (Structure)callRPC(G2_REPRESENT_WORKSPACE_, args);
  }

  /**
   * Turns off workspace notification for a particular subscription.
   * The argument is the subscription-handle that is part of the
   * data returned by representWorkspace
   * @param subscriptionIndex the subscription handle
   * @exception G2AccessException if there is an error while communicating
   *   with G2 or if the call is in error
   * @undocumented For Gensym private use only.
   */
  @Override
  public boolean unrepresentWorkspace (int subscriptionIndex) throws G2AccessException {
    getSubscpnTable().remove(subscriptionIndex);
    if (!isAlive ())
      return true;
    checkLoggedIn();
    Object[] args = {uiClientSession, subscriptionIndex};
    //System.out.println ("unrepresent (" + uiClientSession + ", " + ")");
    return ((Boolean) callRPC (G2_UNREPRESENT_WORKSPACE_, args)).booleanValue ();
  }

  /**
   * For subscribing to many aspects of a single item. Rather than
   * subscribe to slots one by one, sometimes it is better to subscribe
   * to many aspects of a G2 item, if the item's class in G2 supports this kind
   * of subscription. Displays such as trend charts are good examples of
   * the kind of items that warrant (and support) this kind of subscription.
   * Workspace actions such as move and resize are still handled through
   * the <code>HANDLEWORKSPACESUBSCRIPTION</code> protocol.
   * @param item the Trend Chart
   * @param client the TrendChart client?
   * @param userData unused
   *
   * @undocumented For Gensym private use only.
   */
  @Override
  public Structure representTrendChart(Item item, 
				       TrendChart client,
				       Object userData)
throws G2AccessException {
  Structure itemInfo =
    representTrendChart(item,
			HANDLE_TREND_CHART_SUBSCRIPTIONS_);
  Trace.send(5, itemTrace, traceBundle, "representTrendChart",
	     itemInfo);
  if(itemInfo != null) {
    try {
      // fix this: do we know that this subscrpnHandle will not
      // conflict with the workspace subscriptions? I think it is OK.
      Integer subscrpnHandle =
	(Integer)itemInfo.getAttributeValue(SUBSCRIPTION_HANDLE_);
      getSubscpnTable().put(subscrpnHandle, client);
      return itemInfo;
    } catch (NoSuchAttributeException nsae) {
      throw new G2AccessException(i18n.format("MalformedG2ReturnValue",
					      nsae.getMessage()));
    }
  }
  // can't actually get here, but keep the compiler quiet
  return null;
  }


  /**
   * 
   * @undocumented
   */

  protected Structure representTrendChart (Item item, Symbol callback) throws G2AccessException {
    Object[] args = {item, callback};
    return(Structure)
      callRPC(G2_REPRESENT_TREND_CHART_, args);
  }

  /**
   * @undocumented
   */
  @Override
  public boolean unrepresentTrendChart (int subscriptionHandle) throws G2AccessException {
    return unsubscribeToItem(subscriptionHandle);
  }

  /**
   * @deprecated use changeUserMode
   * @see #changeUserMode
   */
  @Override
  public void setUserMode (Symbol newUserMode) throws G2AccessException {
    changeUserMode(newUserMode);
  }

  /**
   * Changes (in G2) the user-mode associated with this particular session.
   * @param newUserMode the mode to change to
   * @exception G2AccessException if there is an error while communicating
   *   with G2 or if the call is in error or if the user is not authorized
   *   to change to the new mode
   * @see #retrieveUserMode
   */
  public void changeUserMode (Symbol newUserMode) throws G2AccessException {
    checkLoggedIn();
    Object[] args = {uiClientSession, newUserMode};
    Boolean retnvalue = (Boolean)
      callRPC(G2_CHANGE_MODE_FOR_WINDOW_, args);
    if (!retnvalue.booleanValue ())
      throw new InvalidUserModeException(i18n.format("invalidModeForUser",
						     uiClientSession.getUiClientUserName(),
						     newUserMode));
    return ;
  }

  /**
   * @deprecated use retrieveUserMode
   * @see #retrieveUserMode
   */
  @Override
  public Symbol getUserMode () throws G2AccessException {
    return retrieveUserMode();
  }

  /**
   * Returns the current user mode in G2 associated with this particular
   * session
   * @return the current mode
   * @exception G2AccessException if there is an error while communicating
   *   with G2
   */
  public Symbol retrieveUserMode () throws G2AccessException {
    checkLoggedIn();
    return uiClientSession.getUiClientSessionUserMode();
  }

  /**
   * Returns all named workspaces in the remote G2.
   * Clients can use this to obtain a root set of Items
   * after making a connection
   * @return a Sequence of named KbWorkspace items
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  @Override
  public Sequence getNamedWorkspaces () throws G2AccessException {

    Object[] args = new Object[0];
    return (Sequence) callRPC(G2_GET_LIST_OF_WORKSPACES_, args);
  }

  private static final Symbol _T2_REGISTER_BEAN_FOR_FOREIGN_OBJECT_ = 
     Symbol.intern ("_T2-REGISTER-BEAN-FOR-FOREIGN-OBJECT");

  /**
   *
   */
  public void registerBeanForForiegnObject (Object javaBean,
					    com.gensym.classes.G2ForeignObject foreignObject) 
    throws G2AccessException {
    System.out.println ("Registering Bean ...");
    Boolean done = (Boolean)
      callRPC (_T2_REGISTER_BEAN_FOR_FOREIGN_OBJECT_, new Object[] { uiClientSession, javaBean, foreignObject });
    System.out.println ("Registered Bean = " + done);
  }


  /**
   * Callback registered with JavaLink for Trend Chart subscriptions
   * @undocumented
   */
  public void HANDLETRENDCHARTSUBSCRIPTIONS(int subscriptionHandle,
					    Item item,
					    Symbol notificationType,
					    Structure newInfo) {

    TrendChart listener =
      (TrendChart)getSubscpnTable().
      get(subscriptionHandle);
    
    Trace.send(10, wsTraceKey, wsTraceBundle, "twgTrendChartHandler", newInfo,
	       listener);

    listener.processTrendChartEvent
      (new TrendChartEvent(item, item, subscriptionHandle,
			   notificationType, newInfo));
  }
  
  /**
   * The itemTable below is a temporary hack by pbk
   * until all items are passes as items instead of
   * integer handles.
   */
  private Hashtable itemTable = new Hashtable();
  private Hashtable getItemTable() {
    if (itemTable == null)
      itemTable = new Hashtable();
    return itemTable;
  }
  private static Symbol TW_WORKSPACE_ITEM_PROXY_ = Symbol.intern ("TW-WORKSPACE-ITEM-PROXY");

  /**
   * @undocumented Why is this here and who calls it?
   */
  public Item getItem (Structure itemData) {
    Item itm = (Item) itemData.getAttributeValue
      (TW_WORKSPACE_ITEM_PROXY_ , null);
    return itm;
  }

  private Hashtable workspaceEventsTable = new Hashtable ();

  /**
   * @undocumented
   */
  @Override
  public void decacheEvents(Integer subscriptionHandle) {
    KbWorkspace workspace = (KbWorkspace) getSubscpnTable().get(subscriptionHandle);
    Vector events = (Vector)workspaceEventsTable.get(subscriptionHandle);
    if (events != null) {
      Enumeration e = events.elements();
      while (e.hasMoreElements()) {
	Object[] nextEvent = (Object[])e.nextElement();
	handleWorkspaceSubscriptions (new WorkspaceEvent(workspace,
							 (Symbol)nextEvent[0],
							 (Item)nextEvent[1],
							 (Structure)nextEvent[2]));
      }
      workspaceEventsTable.remove(subscriptionHandle);
    }
  }
  
  static Symbol tw_workspace_item_handle_symbol = Symbol.intern ("TW-WORKSPACE-ITEM-HANDLE");

  /**
   * @undocumented
   */
  @Override
  public Object HANDLEWORKSPACESUBSCRIPTIONS(Symbol notificationCode, 
					     Item itm, 
					     Structure extraInfo,
					     int subscriptionHandle) {

    Trace.send(5, wsTraceKey, wsTraceBundle, "ReceivingWsNotification",
	       notificationCode, itm, extraInfo, subscriptionHandle);
    if (false)
      System.out.println ("WKSP NOTFN: " + notificationCode + " -> " + itm); 
    System.out.flush ();
    
    Integer key = subscriptionHandle;
    KbWorkspace workspace = (KbWorkspace) getSubscpnTable().get(key);
    Trace.send(10, wsTraceKey, wsTraceBundle, "twgDispatchingNotification", itm, workspace);
    Vector cachedEvents = (Vector)workspaceEventsTable.get(key);
    if (cachedEvents != null)
      cachedEvents.addElement(new Object[] {notificationCode, itm, extraInfo});
    
    if (workspace != null) {
      if (cachedEvents == null)
	handleWorkspaceSubscriptions(new WorkspaceEvent(workspace,
							notificationCode,
							itm,
							extraInfo));
    } else {
      if (cachedEvents == null) {
	cachedEvents = new Vector();
	cachedEvents.addElement(new Object[] {notificationCode, itm, extraInfo});
	workspaceEventsTable.put(key, cachedEvents);
      }
    }
    return BOGUS_RETURN_VALUE;
  }


  /**
   * @undocumented
   */
  @Override
  public void handleWorkspaceSubscriptions (WorkspaceEvent event) { 
    KbWorkspace workspace = (KbWorkspace) event.getSource();
    workspace.processWorkspaceEvent(event);
  }


  static Symbol _show = Symbol.intern ("SHOW");


  /**
   * @undocumented
   */
  public void HANDLEWORKSPACESSHOWINGSUBSCRIPTIONS
  (Symbol showOrHide,
   Item workspace,
   Structure particulars, 
   int userData,
   int subscriptionHandle)
  {
    
    Trace.send(10, traceKey, traceBundle,
	       "HANDLEWORKSPACESSHOWINGSUBSCRIPTIONS", showOrHide, workspace,
	       uiClientSession);
    if (!(workspace instanceof KbWorkspace)) {
      if (GensymApplication.getDevOption()) {
	System.out.println("Ignoring workspace showing event for " + workspace);
      }
      return;
    }
    WorkspaceShowingEvent event
      = new WorkspaceShowingEvent(this, showOrHide, particulars, workspace,
				  userData, subscriptionHandle);
    processWorkspaceShowingEvent(event);
  }


  /**
   * @undocumented
   */
  @Override
  public void processWorkspaceShowingEvent(WorkspaceShowingEvent event) {
    switch (event.getID()) {
    case WorkspaceShowingEvent.SHOW:
      workspaceShowingListener.showWorkspace(event);
      return;
    case WorkspaceShowingEvent.HIDE:
      workspaceShowingListener.hideWorkspace(event);
      return;
    default:
      throw new IllegalArgumentException
	(i18n.format("twgInvalidEventID", event.getID()));
    }
  }

  /**
   * @undocumented
   */
  public Integer subscribeToWorkspaceShowing(UiClientSession session)
throws G2AccessException {
  checkLoggedIn();
  Trace.send(10, traceKey, traceBundle, "subscribeToWorkspaceShowing",
	     session);
  Object[] args = {session,
		   HANDLE_WORKSPACES_SHOWING_SUBSCRIPTIONS_, 42};
  Integer subscpnHandle =
    (Integer) callRPC( G2_SUBSCRIBE_TO_WORKSPACES_SHOWING_, args);
  getSubscpnTable().put(subscpnHandle, session);
  return subscpnHandle;
  }

  /**
   * @undocumented
   */
  public void unsubscribeToWorkspaceShowing(Integer subscriptionHandle)
throws G2AccessException {
  if (isAlive ())
    callRPC(G2_UNSUBSCRIBE_TO_WORKSPACES_SHOWING_,
	    new Object[] {subscriptionHandle});
  getSubscpnTable().remove(subscriptionHandle);
  }


  /**
   * Adds the specified listener to receive workspace-showing events from this
   * connections. Such events are generated when G2 tries to execute the show
   * or hide actions. These actions can apply to all ui-client-items or can
   * be restricted to specific ones. If the session associated with this
   * connection is one of the applicable targets then a WorkspaceShowingEvent
   * containing the show or hide notification is broadcast to all registered
   * listeners.
   * <p>
   * This method should be called before the connection is logged in, because
   * workspace showing events can be triggered during the login process,
   * and if there are no listeners registered, then the events will be lost.
   * Note that no events will be generated for this connection
   * until after the connection has been logged in.
   * @param listener the workspace-showing listener to add
   * @see com.gensym.jgi.WorkspaceShowingListener
   * @see com.gensym.jgi.WorkspaceShowingEvent
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  @Override
  public void addWorkspaceShowingListener(WorkspaceShowingListener listener) throws G2AccessException {
    Trace.send(10, traceKey, traceBundle, "addWorkspaceShowingListener",
	       listener);
    workspaceShowingListener =
      NtwEventMulticaster.add(workspaceShowingListener, listener);
    if (workspacesShowingSubscriptionHandle == null && isLoggedIn())
      workspacesShowingSubscriptionHandle =
	subscribeToWorkspaceShowing(uiClientSession);
  }

  /**
   * Removes the specified listener so that it no longer receives workspace-showing
   * events from this connection.
   * @param listener the workspace-showing listener to remove
   * @see com.gensym.jgi.WorkspaceShowingListener
   * @see com.gensym.jgi.WorkspaceShowingEvent
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  @Override
  public void removeWorkspaceShowingListener(WorkspaceShowingListener listener) throws G2AccessException {
    if (workspaceShowingListener == null) // protect against unsubscribing because of user error
      return;
    workspaceShowingListener =
      NtwEventMulticaster.remove(workspaceShowingListener, listener);
    if (workspaceShowingListener == null) {
      unsubscribeToWorkspaceShowing(workspacesShowingSubscriptionHandle);
    }
  }

  private Vector getFieldEditListeners(KbWorkspace workspace)
  {    
    if (fieldEditListeners.isEmpty())
      return null;
    Enumeration e = fieldEditListeners.elements();
    Vector listeners = new Vector();
    while (e.hasMoreElements()) {
      FieldEditListener l = (FieldEditListener)e.nextElement();
      KbWorkspace wksp = l.getWorkspace();
      if (wksp.equals(workspace))
	listeners.addElement(l);
    }
    if (listeners.isEmpty())
      return null;
    return listeners;
  }

  private static final Symbol CANCEL_EXIT_ = Symbol.intern ("CANCEL-EXIT");
  /**
   * @undocumented
   */
  public void HANDLEFIELDEDITSUBSCRIPTIONS
  (Symbol fieldEditAction,
   Item workspace,
   Structure particulars, 
   int userData,
   int subscriptionHandle)
  {
    Trace.send(10, traceKey, traceBundle,
	       "HANDLEFIELDEDITSUBSCRIPTIONS", fieldEditAction, workspace,
	       uiClientSession);
    Vector listenersForThisWorkspace = getFieldEditListeners((KbWorkspace)workspace);
    FieldEditEvent event
      = new FieldEditEvent(this, fieldEditAction, particulars, workspace,
			     userData, subscriptionHandle);
    if (listenersForThisWorkspace == null) {
      /*System.out.println("NO FIELD EDIT LISTENERS FOR " + workspace +
			 "\nACTION: " + fieldEditAction);*/
      boolean showingAdapterHandledEvent = false;
      if (!showingAdapterHandledEvent) {
	try {
	  finishFieldEditAndRecordStatus(CANCEL_EXIT_);
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}
      }
    } else {
      Enumeration e = listenersForThisWorkspace.elements();
      while (e.hasMoreElements()) {
	FieldEditListener l = (FieldEditListener)e.nextElement();
	processFieldEditEventForListener(event, l);
      }
    }
  }

  private void processFieldEditEventForListener(FieldEditEvent event,
						FieldEditListener l)
  {
    switch (event.getID()) {
    case FieldEditEvent.CANCEL:
      l.cancelFieldEdit(event); 
      return;
    case FieldEditEvent.CREATE:
      l.createFieldEdit(event); 
      return;
    case FieldEditEvent.REFRESH:
      l.refreshFieldEdit(event); 
      return;
    case FieldEditEvent.UPDATE:
      l.updateFieldEdit(event); 
      return;
    case FieldEditEvent.END:
      l.endFieldEdit(event); 
      return;
    default:
      throw new IllegalArgumentException
	(i18n.format("twgInvalidEventID", event.getID()));
    }
  }

  /**
   * @undocumented
   */
  public Integer subscribeToFieldEditActions (UiClientSession session) throws G2AccessException {
  checkLoggedIn();
  Trace.send(10, traceKey, traceBundle, "subscribeFieldEditActions",
	     session);
  Object[] args = {session,
		   HANDLE_FIELD_EDIT_SUBSCRIPTIONS_,42};
  Integer subscpnHandle =
    (Integer) callRPC( G2_SUBSCRIBE_TO_FIELD_EDIT_ACTIONS_, args);
  getSubscpnTable().put(subscpnHandle, session);
  return subscpnHandle;
  }

  /**
   * @undocumented
   */
  public void unsubscribeToFieldEditActions (Integer subscriptionHandle) throws G2AccessException {
    if (isAlive ())
      callRPC(G2_UNSUBSCRIBE_TO_FIELD_EDIT_ACTIONS_,
	      new Object[] {subscriptionHandle});
    getSubscpnTable().remove(subscriptionHandle);
  }


  /**
   * @undocumented
   * Adds the specified listener to receive field edit events from this
   * connection. Such events are generated when G2 tries to perform a field
   * edit on a message. These actions apply to a single ui-client-items.
   * If the session associated with this connection is one of the applicable
   * targets then a FieldEditEvent containing the field edit action
   * notification is broadcast to all registered listeners
   * @param listener the field edit listener to add
   * @see com.gensym.ntw.util.FieldEditListener
   * @see com.gensym.ntw.FieldEditEvent
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  @Override
  public void addFieldEditListener(FieldEditListener listener) throws G2AccessException {
    Trace.send(10, traceKey, traceBundle, "addFieldEditListener",
	       listener);
    fieldEditListeners.addElement(listener);
    if (!subscribedToFieldEditActions) {
      fieldEditSubscriptionHandle =
	subscribeToFieldEditActions(uiClientSession);
      subscribedToFieldEditActions = true;
    }    
  }


  /**
   * @undocumented
   * Removes the specified listener so that it no longer receives field edit
   * events from this connection.
   * @param listener the field edit listener to remove
   * @see com.gensym.ntw.util.FieldEditListener
   * @see com.gensym.ntw.FieldEditEvent
   * exception G2AccessException if there is an error while communicating
   *   with G2
   */
  @Override
  public void removeFieldEditListener(FieldEditListener listener) throws G2AccessException {
    fieldEditListeners.removeElement(listener);
    if (fieldEditListeners.isEmpty() && subscribedToFieldEditActions) {
      unsubscribeToFieldEditActions(fieldEditSubscriptionHandle);
      subscribedToFieldEditActions = false;
    }
  }

  /**
   * @undocumented
   */
  @Override
  public boolean updateFieldEdit(String newFieldEditValue)
       throws G2AccessException
  {
    Object[] args = new Object[] {uiClientSession, newFieldEditValue};
    Boolean retVal = (Boolean)callRPC(G2_UPDATE_UI_CLIENT_SESSION_FIELD_EDIT_, args);
    return retVal.booleanValue();
  }

  /**
   * @undocumented
   */  
  @Override
  public boolean finishFieldEditAndRecordStatus(Symbol newStatus)
       throws G2AccessException
  {
    Object[] args = new Object[] {uiClientSession, newStatus};
    Boolean retVal = (Boolean)callRPC(G2_FINISH_FIELD_EDIT_AND_RECORD_STATUS_, args);
    return retVal.booleanValue();
  }
  
  private final Hashtable formatTable = new Hashtable (7);


  /**
   * Returns the description of the format named by the argument
   * @undocumented
   * @param formatName the name of the format
   * @return a Structure with the attributes of the format, such as the
   * format info for the FORMAT-TYPE of a TEXT-BOX.
   * @exception G2AccessException if there is an error while communicating
   *   with G2
   */
  @Override
  public Structure getFormatInfo (Symbol formatName) throws G2AccessException {
    Structure formatStruct = (Structure) formatTable.get (formatName);
    if (formatStruct != null)
      return formatStruct;
    Object[] args = new Object[] {formatName};
    formatStruct = (Structure)callRPC(G2_GET_FORMAT_INFO_, args);
    formatTable.put (formatName, formatStruct);
    return formatStruct;
  }


  /**
   * Retrieves a user-menu-choice by its label and applicable-class.
   * @param label the menu-label of the user-menu-choice
   * @param applicableClass the G2 class for which the menu-choice applies
   * @exception G2AccessException if there is an error while communicating
   *   with G2
   */
  @Override
  public UserMenuChoice getUserMenuChoice(Symbol label,
					  Symbol applicableClass) throws G2AccessException {
					    Object[] args = new Object[] {label, applicableClass};
					    return (UserMenuChoice)callRPC(G2_GET_USER_MENU_CHOICE_, args);
  }
       
  private void initializeInstance0 () {
    irm = new IconRenderingManager ();
    dialogManager = dialogManagerFactory.makeDialogManager(this);
    kb = new com.gensym.classes.KbImpl (this);
  }

  /**
   * @undocumented Not ready for public use
   * @see com.gensym.jgi.G2Gateway#initializeInstance
   */
  @Override
  protected void initializeInstance () {
    super.initializeInstance ();
    new com.gensym.clscupgr.ModuleManager (this);
  }


  /**
   * Returns the DialogManager associated with this connection.
   * This DialogManager can be used to request editing and other
   * dialogs for items retrieved throught this connection.
   * @return the DialogManager for this connection
   */
  @Override
  public DialogManager getDialogManager() {
    return dialogManager;
  }

  /**
   */
  public void setDialogManager(DialogManager dialogManager) {
    if (dialogManager == null)
      throw new IllegalArgumentException(i18n.getString("twgNullDialogManager"));
    this.dialogManager = dialogManager;
  }

  /**
   * Returns the Kb object associated with this connection.
   * The Kb object is unique per G2 and can be used to get
   * data and notifications of changes to the module structure
   * in that G2.
   * @return the Kb object
   */
  @Override
  public Kb getKb () {
    return kb;
  }

  /**
   * @undocumented
   */
  public void SETDIALOGRESOURCEENTRY(Symbol className,
				     Symbol userMode,
				     Structure localeStructure,
				     Structure urlStructure) throws G2AccessException, MalformedURLException {
				       dialogManager.setDialogResourceEntry(className,userMode,
									    localeStructure,urlStructure);
  }
  

  /**
   * @undocumented
   */
  public void SETDIALOGRESOURCEENTRY(Item item,
				     Symbol userMode,
				     Structure localeStructure,
				     Structure urlStructure) throws G2AccessException, MalformedURLException {
				       dialogManager.setDialogResourceEntry(item,userMode,
									    localeStructure,urlStructure);
  }


  /**
   * @undocumented
   */
  @Override
  public IconRenderingManager getIconManager () {
    return irm;
  }


  /**
   * @undocumented
   */
  @Override
  public void unsubscribeToModules () throws G2AccessException {
    if (isAlive ())
      callRPC (G2_UNSUBSCRIBE_TO_MODULES_, new Object[] {//uiClientSession
      });
  }

  private static final Symbol MODULES_ = Symbol.intern("MODULES");
  private static final Symbol LOGBOOK_ = Symbol.intern("LOGBOOK");
  private static final Symbol MESSAGE_BOARD_ = Symbol.intern("MESSAGE-BOARD");

  /**
   * @undocumented
   */
  @Override
  public Structure subscribeToModules () throws G2AccessException {
    Object[] args = {//uiClientSession,
      HANDLEMODULESUBSCRIPTIONS_, 42,
      HANDLEITEMSUBSCRIPTIONS_, 101 };
    Structure retnValue = (Structure)callRPC(G2_SUBSCRIBE_TO_MODULES_, args);
    Sequence moduleInfoSequence 
      = (Sequence) retnValue.getAttributeValue(MODULES_,null);
    //System.out.println("module subsc: " + retnValue);
    for (int i=0; i<moduleInfoSequence.size (); i++) {
      Structure particulars = (Structure) moduleInfoSequence.elementAt (i);
      mergeSystemTables (particulars);
    }
    Trace.send (5, moduleTrace, traceBundle, "subscribeModRetnValue", this, retnValue);
    return retnValue;
  }

  private static final Symbol CREATE_ = Symbol.intern ("CREATE");
  private static final Symbol DELETE_ = Symbol.intern ("DELETE");
  private static final Symbol CLEAR_KB_ = Symbol.intern ("CLEAR-KB");
  private static final Symbol ADD_AS_TOP_LEVEL_WORKSPACE_ = Symbol.intern("ADD-AS-TOP-LEVEL-WORKSPACE");
  private static final Symbol REMOVE_AS_TOP_LEVEL_WORKSPACE_ = Symbol.intern("REMOVE-AS-TOP-LEVEL-WORKSPACE");
  private static final Symbol ADD_TO_MESSAGE_BOARD_ 
    = Symbol.intern ("ADD-TO-MESSAGE-BOARD");
  private static final Symbol PACKAGE_PREPARATION_MODE_CHANGED_ =
  Symbol.intern ("PACKAGE-PREPARATION-MODE-CHANGED"),
    SIMULATE_PROPRIETARY_MODE_CHANGED_ =
  Symbol.intern ("SIMULATE-PROPRIETARY-MODE-CHANGED");
  private static final Symbol ADD_TO_LOGBOOK_
    = Symbol.intern ("ADD-TO-LOGBOOK");
  private static final Integer BOGUS_RETURN_VALUE = 5471962;

  /**
   * @undocumented
   */
  public Object HANDLEMODULESUBSCRIPTIONS (Symbol modfnCode, boolean particulars) {
    //Trace.send (5, moduleTrace, traceBundle, "modEvent", modfnCode,
    //particulars?Boolean.TRUE:Boolean.FALSE);
    PackagePreparationEvent evt;
    if (modfnCode.equals(PACKAGE_PREPARATION_MODE_CHANGED_)) 
      evt = createPackagePreparationModeEvent
	(PackagePreparationEvent.PACKAGE_PREPARATION_MODE_CHANGED,
	 particulars);
    else if (modfnCode.equals(SIMULATE_PROPRIETARY_MODE_CHANGED_))
      evt = createPackagePreparationModeEvent
	(PackagePreparationEvent.SIMULATE_PROPRIETARY_MODE_CHANGED,
	 particulars);      
    else
      throw new RuntimeException ("Unexpected modification code <" + modfnCode.getPrintValue () + "> in Module Subscription callback. ");
    //Trace.send (5, moduleTrace, traceBundle, "processModEvent", modfnCode, evt);
    if (evt != null)    
      processPackagePreparationEvent(evt);
    return BOGUS_RETURN_VALUE;    
  }

  /**
   * @undocumented    
   * Add a PackagePreparationListener, who will be informed of any PackagePreparation events for
   * a G2 connection.
   *@param listener The PackagePreparationListener to inform.
   */
  @Override
  public synchronized void addPackagePreparationListener(PackagePreparationListener listener) {
    if (!packagePreparationListeners.contains(listener))
      packagePreparationListeners.addElement(listener);
  }

  /**
   * @undocumented    
   * Remove a PackagePreparationListener, who was previously listening for PackagePreparation
   * events.
   *@param listener The PackagePreparationListener to inform.
   */
  @Override
  public synchronized void removePackagePreparationListener(PackagePreparationListener listener) {
    packagePreparationListeners.removeElement(listener);
  }

  /**
   * Returns the list of current PackagePreparationListeners registered to
   * receive events from this Gateway.
   *@returns A Vector of PackagePreparationListeners.
   */
  protected synchronized Vector getPackagePreparationListeners () {
    return (Vector) packagePreparationListeners.clone ();
  }
  
  /**
   * @undocumented
   */
  protected void processPackagePreparationEvent(PackagePreparationEvent evt)
  {
    int id = evt.getId ();
    Vector packagePrepListeners = getPackagePreparationListeners ();
    for (int i=0; i<packagePrepListeners.size(); i++) {
      java.lang.Object listener = packagePrepListeners.elementAt (i);
      switch (id) {
      case PackagePreparationEvent.PACKAGE_PREPARATION_MODE_CHANGED:
	if (evt.getState())
	  ((PackagePreparationListener)listener).enterPackagePreparationMode(evt); 
	else
	  ((PackagePreparationListener)listener).leavePackagePreparationMode(evt);
	break;
      case PackagePreparationEvent.SIMULATE_PROPRIETARY_MODE_CHANGED:
	if (evt.getState())
	  ((PackagePreparationListener)listener).enterSimulateProprietaryMode(evt); 
	else
	  ((PackagePreparationListener)listener).leaveSimulateProprietaryMode(evt);
	break;	  		
      default:
	// Do nothing. Subclasses may have more events
      }
    }
  }

  //final for performance only
  private final PackagePreparationEvent createPackagePreparationModeEvent(int id,
									  boolean newState) {
    return new PackagePreparationEvent(this,
				       id,
				       newState);
  }
  
  /**
   * @undocumented
   */
  public Object HANDLEMODULESUBSCRIPTIONS (Symbol modfnCode, Object particulars) {
    Trace.send (5, moduleTrace, traceBundle, "modEvent", modfnCode, particulars);
    KbEvent evt;
    if (modfnCode.equals (CREATE_))
      evt = createModuleCreationEvent ((Structure) particulars);
    else if (modfnCode.equals (DELETE_))
      evt = createModuleDeletionEvent ((Item) particulars);
    else if (modfnCode.equals (CLEAR_KB_)) {
      evt = createKbClearedEvent ();
    } 
    else if (modfnCode.equals (ADD_AS_TOP_LEVEL_WORKSPACE_)){
      evt = createTopLevelWkspEvent ((Structure)particulars, KbEvent.TOP_LEVEL_KB_WORKSPACE_ADDED);
    }	     
    else if (modfnCode.equals (REMOVE_AS_TOP_LEVEL_WORKSPACE_)){
      evt = createTopLevelWkspEvent ((Structure)particulars, KbEvent.TOP_LEVEL_KB_WORKSPACE_DELETED);
    }
    else if (modfnCode.equals (ADD_TO_MESSAGE_BOARD_))
      evt = createKbMessageBoardMessageAddedEvent ((Message) particulars);
    else if (modfnCode.equals (ADD_TO_LOGBOOK_))
      evt = createKbLogBookMessageAddedEvent ((Message) particulars);
    else
      throw new RuntimeException ("Unexpected modification code <" + modfnCode.getPrintValue () + "> in Module Subscription callback. Please see vkp.");
    Trace.send (5, moduleTrace, traceBundle, "processModEvent", modfnCode, evt);
    
    if (evt != null)
      ((com.gensym.classes.KbImpl)kb).processKbEvent (evt);
    return BOGUS_RETURN_VALUE;
  }

  private static final Symbol NAME_ = Symbol.intern ("NAME");
  private static final Symbol ITEM_NOTES_ = Symbol.intern ("ITEM-NOTES");


  /**
   * @undocumented
   */
  public Object HANDLEITEMSUBSCRIPTIONS (Symbol modfnCode, Item itm,
					 Sequence denotation,
					 Object newValue, Object userData,
					 int subscriptionHandle) {
    if (denotation.size () != 1)
      throw new IllegalArgumentException ("Denotation with unexpected number of elements = " + denotation.size ());
    Structure struct = (Structure) denotation.elementAt (0);

    Trace.send (5, moduleTrace, traceBundle, "modChangeEvent", modfnCode, itm, denotation, newValue);
    KbEvent evt = createModuleChangeEvent (itm, denotation, newValue);
    if (evt != null) {
      Trace.send (5, moduleTrace, traceBundle, "processModEvent", denotation, evt);
      ((com.gensym.classes.KbImpl)kb).processKbEvent (evt);
    }

    return BOGUS_RETURN_VALUE;
  }


  /**
   * Returns a description of this connection
   * @return the description
   */
  @Override
  public String toString () {
    return (super.toString() + "[Connected@" + hashCode() + "]");
  }

  private static final Symbol TOP_LEVEL_MODULE_ = Symbol.intern ("TOP-LEVEL-MODULE");
  private static final Symbol DIRECTLY_REQUIRED_MODULES_ = Symbol.intern ("DIRECTLY-REQUIRED-MODULES");
  private static final Symbol OTHER_SYSTEM_TABLES_ = Symbol.intern ("OTHER-SYSTEM-TABLES");
  private static final Symbol MODULE_INFORMATION_ = Symbol.intern ("MODULE-INFORMATION");
  private static final Symbol SYSTEM_TABLES_ = Symbol.intern ("SYSTEM-TABLES");
  private static final Symbol IS_TOP_LEVEL_ = Symbol.intern ("IS-TOP-LEVEL");

  private KbEvent createModuleCreationEvent (Structure particulars) {
    mergeSystemTables (particulars);
    KbEvent evt = new KbEvent (kb, null, KbEvent.MODULE_CREATED, particulars);
    return evt;
  }

  private KbEvent createModuleDeletionEvent (Item moduleItem) {
    try {
      ModuleInformation moduleInfo = (ModuleInformation) moduleItem;
      Module module = kb.getModule (moduleInfo);
      KbEvent evt = new KbEvent (kb, module, KbEvent.MODULE_DELETED, null);
      return evt;
    } catch (G2AccessException gae) {
      throw new UnexpectedException (gae, "Call to g2 unexpected.");
    }
  }

  private KbEvent createModuleChangeEvent (Item moduleItem, Sequence denotation, java.lang.Object newValue) {
    if (moduleItem == null)
      return null;	// G2 Bug#1834187. Sends notification with null Item on CLEAR-KB -vkp, 3/2/98
    ModuleInformation moduleInfo = (ModuleInformation)moduleItem;
    try {
      Module module = kb.getModule (moduleInfo);
      Symbol attrName = (Symbol) ((Structure)denotation.elementAt (0)).getAttributeValue (NAME_, null);
      KbEvent evt;
      if (attrName.equals (TOP_LEVEL_MODULE_)) {
	Symbol moduleName = (Symbol) newValue;
	evt = new KbEvent (kb, module, KbEvent.MODULE_NAME_CHANGED, moduleName);
      } else if (attrName.equals (DIRECTLY_REQUIRED_MODULES_)) {
	Sequence requiredModuleNames = (Sequence) newValue;
	evt = new KbEvent (kb, module, KbEvent.MODULE_DEPENDENCY_CHANGED, requiredModuleNames);
      } else
	throw new RuntimeException ("Change to attribute <" + attrName + "> reported. Please report this.");
      return evt;
    } catch (G2AccessException gae) {
      throw new UnexpectedException (gae, "Call to g2 unexpected.");
    }
  }

  private KbEvent createKbClearedEvent () {
    return new KbEvent (kb, null, KbEvent.KB_CLEARED, null);
  }

  private static final Symbol MODULE_NAME_ = Symbol.intern("MODULE-NAME");
  private static final Symbol KB_WORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  private KbEvent createTopLevelWkspEvent(Structure particulars, int id){
    try {
      Module module = kb.getModule((Symbol)particulars.getAttributeValue(MODULE_NAME_, null));
      KbWorkspace wksp = (KbWorkspace)particulars.getAttributeValue(KB_WORKSPACE_, null);
      return new KbEvent (kb, module, id, wksp);
    }
    catch (G2AccessException gae) {
      throw new UnexpectedException (gae, "Call to g2 unexpected.");
    }
  }

  private KbEvent createKbMessageBoardMessageAddedEvent (Message newMessage){
    return new KbEvent(kb, null, KbEvent.KB_MESSAGE_BOARD_MESSAGE_ADDED, newMessage); 
  }

  private KbEvent createKbLogBookMessageAddedEvent (Message newMessage){
    return new KbEvent(kb, null, KbEvent.KB_LOGBOOK_MESSAGE_ADDED, newMessage); 
  }

  private void mergeSystemTables (Structure particulars) {
    Sequence systemTables = (Sequence) particulars.getAttributeValue (OTHER_SYSTEM_TABLES_, null);
    systemTables.addElement (particulars.getAttributeValue (MODULE_INFORMATION_, null));
    particulars.setAttributeValue (SYSTEM_TABLES_, systemTables);
    particulars.deleteAttribute (OTHER_SYSTEM_TABLES_);
  }

  /**
   * Calls addG2ConnectionListener.
   * TwConnectionListeners will receive all G2ConnectionEvents and
   * TwConnectionEvents whether the listeners are
   * added through this method or through
   * addG2ConnectionListener. Objects that only implement G2ConnectionListener
   * will just not receive TwConnectionEvents.
   * @param listener a listener prepared to receive either G2ConnectionEvents
   * or TwConnectionEvents.
   * @see com.gensym.jgi.G2Gateway#addG2ConnectionListener
   */
  @Override
  public synchronized void addTwConnectionListener (TwConnectionListener listener) {
    addG2ConnectionListener (listener);
  }

  /**
   * calls removeG2ConnectionListener
   * @see com.gensym.jgi.G2Gateway#removeG2ConnectionListener
   */
  @Override
  public synchronized void removeTwConnectionListener (TwConnectionListener listener) {
    removeG2ConnectionListener (listener);
  }

  /**
   * @undocumented
   */
  protected void dispatchTwConnectionEvent (TwConnectionEvent evt) {
    int id = evt.getId ();
    if (evt instanceof TwConnectionEvent) {
      Vector connectionListeners = null;
      synchronized (this) {
	connectionListeners = getG2ConnectionListeners ();
      }
      for (int i=0; i<connectionListeners.size(); i++) {
	java.lang.Object listener = connectionListeners.elementAt (i);
	if (listener instanceof TwConnectionListener) {
	  switch (id)
	    {
	    case TwConnectionEvent.CONNECTION_LOGGED_IN:
	      ((TwConnectionListener)listener).loggedIn (evt); 
	      break;
	    case TwConnectionEvent.CONNECTION_LOGGED_OUT:
	      ((TwConnectionListener)listener).loggedOut (evt); 
	      break;
	    case TwConnectionEvent.USER_MODE_CHANGED:
	      ((TwConnectionListener)listener).userModeChanged (evt); 
	      break;
	    default:
	      // Do nothing. Subclasses may have more events
	    }
	}
      }
    } else
      dispatchG2ConnectionEvent ((G2ConnectionEvent)evt);
  }




  private static final Symbol _setItemToBeEdited
  = Symbol.intern("G2-SET-EDITING-CONTEXT-ITEM");

  private final int timeoutForSetItemToBeEdited = 2000; // two seconds
  private transient boolean setItemToBeEditedIsSupported = true; 

  /** Sets the item field of a server-side parsing-context.
   * The method is include here rather than in com.gensym.edit.text.Session
   * because the rpc it calls is only available in certain versions
   * of G2 and this lets us keep connection-specific information. -ddm
   * @undocumented For Gensym private use only.
   */
  @Override
  public void sendItemToG2SideEditingContext(Item item, Integer parsingContext)
  throws  G2AccessException {
    if (setItemToBeEditedIsSupported) {
      Object[] args = new Object[2];
      args[0] = parsingContext;
      args[1] = item;    
      Object returnValue = null;
      try { 
    	  returnValue = callRPC(_setItemToBeEdited, args, timeoutForSetItemToBeEdited);
      } catch (ConnectionNotAliveException e) {
	throw e; // the Session will catch it.
      } catch (G2AccessException e) {
	// Do we have a more specific form of this exception? Like 'rpc undefined' ?
	Trace.exception(e); // look at what we got.
	setItemToBeEditedIsSupported = false;
      }
    }
  }




  ///FILE PROGRESS CHANGES

  private static Method fileProgressCallbackMethod;
  private static final Symbol
  FILE_PROGRESS_CALLBACK_ = Symbol.intern ("FILE-PROGRESS-CALLBACK"),
  G2_SUBSCRIBE_TO_FILE_PROGRESS_CHANGES_ 
   = Symbol.intern ("G2-SUBSCRIBE-TO-FILE-PROGRESS-CHANGES"),
    G2_UNSUBSCRIBE_TO_FILE_PROGRESS_CHANGES_
  = Symbol.intern ("G2-UNSUBSCRIBE-TO-FILE-PROGRESS-CHANGES");
  
  static {
    try {
      fileProgressCallbackMethod
	= com.gensym.ntw.TwGateway.class.getDeclaredMethod
	("fileProgressCallback",
	 new Class[]
	 {Structure.class,
	    Boolean.TYPE,});
      
    } catch (NoSuchMethodException nsme) { 
      Trace.exception(nsme);
    }
  }
  
  private void subscribeToFileProgress()
       throws G2AccessException
  {
    if (isAlive())        
      callRPC(G2_SUBSCRIBE_TO_FILE_PROGRESS_CHANGES_,
	      new Object[]
	      { FILE_PROGRESS_CALLBACK_, 1234567});
  }

  private void unsubscribeToFileProgress()
       throws G2AccessException
  {
    if (isAlive())        
      callRPC(G2_UNSUBSCRIBE_TO_FILE_PROGRESS_CHANGES_,
	      new Object[] {});
  }

  /**
   * @undocumented    
   * Add a FileProgressListener, who will be informed of the status of
   * files being loaded or saved.
   *@param listener The FileProgressListener to inform.
   */
  @Override
  public void addFileProgressListener(FileProgressListener listener)
       throws G2AccessException
  {
    boolean needToSubscribe = (fileProgressListener == null);
    fileProgressListener =
      NtwEventMulticaster.add(fileProgressListener, listener);
    if (needToSubscribe)
      subscribeToFileProgress();
  }

  /**
   * @undocumented    
   * Removes the FileProgressListener so that it will no longer be
   * informed of the status of files being loaded or saved.
   *@param listener The FileProgressListener to remove;
   */
  @Override
  public void removeFileProgressListener(FileProgressListener listener)
       throws G2AccessException
  {
    if (fileProgressListener == null) // protect against unsubscribing because of user error
      return;
    fileProgressListener =
      NtwEventMulticaster.remove(fileProgressListener, listener);
    if (fileProgressListener == null) 
      unsubscribeToFileProgress();
  }
  
  /**
   *@undocumented
   */
  public void fileProgressCallback(Structure fileProgress,
				   boolean delete)
  {
    FileProgressEvent fpe = new FileProgressEvent(this, fileProgress, delete);
    processFileProgressEvent(fpe);
  }

  /**
   * @undocumented
   */
  public void processFileProgressEvent(FileProgressEvent event) {
    if (fileProgressListener == null)
      return;
    switch (event.getID()) {
    case FileProgressEvent.FILE_ADDED:
      fileProgressListener.addFile(event);
      return;
    case FileProgressEvent.FILE_REMOVED:
      fileProgressListener.removeFile(event);
      return;
    default:
      throw new IllegalArgumentException
	(i18n.format("twgInvalidEventID", event.getID()));
    }
  }
  

  ///UNSOLICITED DIALOG SUBSCRIPTION

  private static Method unsolicitedDialogsCallbackMethod;
  private static final Symbol
  UNSOLICITED_DIALOGS_CALLBACK_ = Symbol.intern ("UNSOLICITED-DIALOGS-CALLBACK"),
  G2_SUBSCRIBE_TO_UNSOLICITED_DIALOGS_
   = Symbol.intern ("G2-SUBSCRIBE-TO-UNSOLICITED-DIALOGS"),
  G2_UNSUBSCRIBE_TO_UNSOLICITED_DIALOGS_
   = Symbol.intern ("G2-UNSUBSCRIBE-TO-UNSOLICITED-DIALOGS");
  static {
     try {
       unsolicitedDialogsCallbackMethod
	 = com.gensym.ntw.TwGateway.class.getDeclaredMethod
	 ("unsolicitedDialogsCallback",
	  new Class[]
	  {Integer.TYPE,Item.class,Symbol.class,Symbol.class,Sequence.class});
     } catch (NoSuchMethodException nsme) { 
       Trace.exception(nsme);
     }
  }
  
  private void subscribeToUnsolicitedDialogs()
       throws G2AccessException
  {
    if (isAlive())        
      callRPC(G2_SUBSCRIBE_TO_UNSOLICITED_DIALOGS_,
	      new Object[]
	      { UNSOLICITED_DIALOGS_CALLBACK_, 1234567});
  }

  private void unsubscribeToUnsolicitedDialogs()
       throws G2AccessException
  {
    if (isAlive())    
      callRPC(G2_UNSUBSCRIBE_TO_UNSOLICITED_DIALOGS_,
	      new Object[] {});
  }

  /**
   *@undocumented
   */  
  @Override
  public void addUnsolicitedDialogListener(UnsolicitedDialogListener listener)
       throws G2AccessException
  {
    boolean needToSubscribe = (unsolicitedDialogListener == null);
    unsolicitedDialogListener =
      NtwEventMulticaster.add(unsolicitedDialogListener, listener);
    if (needToSubscribe)
      subscribeToUnsolicitedDialogs();
  }

  /**
   *@undocumented
   */  
  @Override
  public void removeUnsolicitedDialogListener(UnsolicitedDialogListener listener)
       throws G2AccessException
  {
    // protect against unsubscribing because of user error    
    if (unsolicitedDialogListener == null) 
      return;
    unsolicitedDialogListener =
      NtwEventMulticaster.remove(unsolicitedDialogListener, listener);
    if (unsolicitedDialogListener == null) 
      unsubscribeToUnsolicitedDialogs();
  }

  /**
   *@undocumented
   */
  public void unsolicitedDialogsCallback(int dialogID,
					 Item clientItem,
					 Symbol dialogName,
					 Symbol eventType,
					 Sequence dialogInfo) 
  {
    UnsolicitedDialogEvent usde = new UnsolicitedDialogEvent(this,
							     dialogID,
							     clientItem,
							     dialogName,
							     eventType,
							     dialogInfo);
    processUnsolicitedDialogEvent(usde);
  }

  /**
   * @undocumented
   */
  public void processUnsolicitedDialogEvent(UnsolicitedDialogEvent event) {
    if (unsolicitedDialogListener == null)
      return;
    switch (event.getID()) {
    case UnsolicitedDialogEvent.DIALOG_UPDATED:
      unsolicitedDialogListener.updateDialog(event);
      return;
    case UnsolicitedDialogEvent.DIALOG_ENTERED:
      unsolicitedDialogListener.enterDialog(event);
      return;
    case UnsolicitedDialogEvent.DIALOG_EXITED:
      unsolicitedDialogListener.exitDialog(event);
      return;      
    default:
      throw new IllegalArgumentException
	(i18n.format("twgInvalidEventID", event.getID()));
    }
  }
  

  /**
   * @undocumented
   */
  @Override
  public void clearModuleMappings() {
    super.clearModuleMappings();
  }


  //--------- Cache of reusable G2 text editors ------------------

  private Vector editorPool = new Vector(5);
  /**
   * @undocumented
   * @return a <code>Vector</code> of <code>Session</code> objects.
   */
  public Vector getEditorPool() { return editorPool; }
  /**
   * @undocumented
   */
  public void setEditorPool(Vector v) { editorPool = v; }
  
}
