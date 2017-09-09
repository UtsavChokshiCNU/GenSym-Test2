package com.gensym.ntw.rmi;

import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.server.Unreferenced;
import java.util.*;
import com.gensym.jgi.rmi.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.*;
import com.gensym.ntw.util.*;
import com.gensym.classes.Item;
import com.gensym.classes.ItemImpl;
import com.gensym.classes.KbImpl;
import com.gensym.classes.Kb;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.KbWorkspaceImpl;
import com.gensym.classes.TrendChart;
import com.gensym.classes.TrendChartImpl;
import com.gensym.classes.UiClientSession;
import com.gensym.classes.VariableOrParameter;
import com.gensym.classes.VariableOrParameterImpl;
import com.gensym.classes.G2Definition;

/** This provides a server implementation in front of G2 for the middle tier
 * in a 3-tier RMI implementation.
 * It forwards callbacks out from G2 (G2Events) into a remote stub, or
 * queues them for a G2Connection client implementation to pick up.
 */

public class TwRMIServerImpl extends TwGateway
implements TwCallbacks, TwRMIAccess, Unreferenced,
com.gensym.util.symbol.TrendChartSymbols {

  private transient Vector eventQueue = new Vector();
    
  private transient Vector g2RemoteConnectionListeners = new Vector();

  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.ntw.rmi",
			   "com.gensym.ntw.rmi.TwRMIServerImpl");
  protected static MessageKey wsTraceKey =
  Trace.registerMessageKey("com.gensym.wksp",
			   "com.gensym.ntw.rmi.TwRMIServerImpl");

  private static Resource wsTraceBundle =
  Trace.getBundle("com.gensym.wksp.Trace", Locale.getDefault());

  private static Resource i18nTrace = Trace.getBundle("com.gensym.ntw.rmi.TraceMessages",
						 Locale.getDefault());

  private static Resource i18n =
  Trace.getBundle("com.gensym.ntw.rmi.Messages");

  private Hashtable remoteConnections = new Hashtable();

  private boolean unsubscribeOnConnectException = true;

  private Hashtable workspaceSubscriptionSessionMap = new Hashtable();

  private boolean disconnected = false;

  private static Symbol _handle_subscriptions 
                          = Symbol.intern ("HANDLESUBSCRIPTIONS");

  private static Symbol _removeSubscriber_Symbol 
                        = Symbol.intern("G2-UNSUBSCRIBE-TO-ITEM");

  private static final Symbol SUBSCRIPTION_HANDLE_
                              = Symbol.intern ("SUBSCRIPTION-HANDLE");

  private static final Symbol INITIAL_VALUE_ = Symbol.intern ("INITIAL-VALUE");

  public static final Symbol ITEM_INFO_LIST_ = Symbol.intern ("ITEM-INFO-LIST");
  public static final Symbol WORKSPACE_BACKGROUND_COLOR_ = Symbol.intern ("WORKSPACE-BACKGROUND-COLOR");
  public static final Symbol WORKSPACE_FOREGROUND_COLOR_ = Symbol.intern ("WORKSPACE-FOREGROUND-COLOR");

  public TwRMIServerImpl() {
    super();
    try {
      UnicastRemoteObject.exportObject(this);
    } catch (RemoteException re) {
      throw new com.gensym.util.UnexpectedException(re);
    }
  }

  //
  // TwGateway overrides
  //

  /**
   * To prevent the middle-tier from consuming a license
   * @undocumented
   */
  protected void initializeUiClientSession(G2ConnectionInfo info)
  throws G2AccessException {
  }

  @Override
  protected void releaseUiClientSession(UiClientSession session)
  throws G2AccessException {
    super.releaseUiClientSession(session);
  }

  /**
   * The middle-tier never actually "logs in", as that
   * would consume an extra license.
   */
  @Override
  protected void checkLoggedIn() throws NotLoggedInException {
    //Trace.exception(new Exception());
  }

  //
  // local methods
  //

  //
  // begin psuedo shared code
  //

  private Hashtable client2QueueManagerMap = new Hashtable();
  
  protected TwServerQueueManager getQueueManager(RMIEventQueueProcessor
						 remoteClient) {
    TwServerQueueManager sqm =
      (TwServerQueueManager)client2QueueManagerMap.get(remoteClient);
    if (sqm == null) {
      sqm = new TwServerQueueManager(this, remoteClient);
      client2QueueManagerMap.put(remoteClient, sqm);
      sqm.start();
    }

    return sqm;
  }

  //
  // begin shared code
  //

  @Override
  public void receivePing()
    throws RemoteException {
  }
  private int pingFrequency = -1;
  @Override
  public void setPingFrequency (int freq) { pingFrequency = freq; }
  @Override
  public int getPingFrequency () throws RemoteException {
    return pingFrequency;
  }


  /** Return this VM's exported G2RMIJavaStubController
   */
  @Override
  public G2RMIJavaStubController getRemoteG2JavaStubController() 
       throws RemoteException {
    G2RMIJavaStubController controller = (G2RMIJavaStubController)
                                   G2RMIJavaStubControllerImpl.getG2JavaStubController();
    G2RMIJavaStubControllerImpl.exportObject();
    return controller;
  }

  /**
   * Get G2JavaStubControllerListener for a given remote client
   */
  @Override
  public G2JavaStubControllerListener getClientListenerForG2JavaStubController(RMIEventQueueProcessor client) {
    // G2ServerQueueManager implements this interface, and will service the client's 
    // G2JavaStubController with any G2JavaStubControllerEvents
    G2ServerQueueManager sqm = getQueueManager(client);
    return (G2JavaStubControllerListener)sqm;
  }


  /** The clients here are whole client applications, not individual
  * ClassDefinitionManagers (for example) */
  @Override
  public synchronized Structure subscribeToItem(RMIEventQueueProcessor client,
						Item itm,
						Sequence denotation,
						Object userData)
  throws G2AccessException, RemoteException{
    G2ServerQueueManager sqm =
      getQueueManager((RMIEventQueueProcessor)client);
    if (AttributeDenotation.WILDCARD_DENOTATION.equals(denotation)) {
      return sqm.subscribeToItem(itm);
    } else if (itm instanceof VariableOrParameter &&
		VariableOrParameterImpl.VALUE_DENOTATION.equals(denotation)) {
      // fix this: Temp hack until a more generic method of
      // adding ItemListeners is found
      return sqm.startVariableValueListening((VariableOrParameter)itm);
    } else {
      //return super.subscribeToItem(
      throw new com.gensym.util.UnexpectedException(null, "non wildcard denotations");
    }
  }

  /** The clients here are whole client applications, not individual
  * ClassDefinitionManagers (for example). This is for subscribing multiple
  * items
  * @author fy 02/28/00
  */
  @Override
  public synchronized Sequence subscribeToItemMultiple(RMIEventQueueProcessor client,
						Item itm,
						Sequence denotation_sequences,
						Object userData)
  throws G2AccessException, RemoteException{
    G2ServerQueueManager sqm =
      getQueueManager((RMIEventQueueProcessor)client);

      return sqm.subscribeToItemMultiple(itm, denotation_sequences);
  }

  /**
   * Removes a subscription.
   * @param subscrpnHandle the Integer obtained from subscribetoG2Item
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @return a boolean specifying whether the unsubscribe was successful
   */
  @Override
  public boolean unsubscribeToItem (RMIEventQueueProcessor client,
				    Item item) 
       throws G2AccessException
  {
    G2ServerQueueManager sqm = getQueueManager(client);
    return sqm.unsubscribeToItem(item);
  }

  @Override
  public boolean unsubscribeToItemMultiple (RMIEventQueueProcessor client,
				    Item item, Sequence subscriptionHandles)
       throws G2AccessException
  {
    G2ServerQueueManager sqm = getQueueManager(client);
    return sqm.unsubscribeToItemMultiple(item, subscriptionHandles);
  }

  /** Could disconnect from G2.
   */
  @Override
  public void unreferenced() {
    System.out.println("Unreferenced: " + this);
    disconnected = true;
    //unsubscribeAll();
  }

  @Override
  public synchronized void
  addRemoteConnection(RMIEventQueueProcessor listener) {
    Trace.send(0, traceKey, i18nTrace, "addConnectionListener", listener);
    G2ServerQueueManager sqm =
      getQueueManager((RMIEventQueueProcessor)listener);
    sqm.startConnectionListening();
    remoteConnections.put(listener, Boolean.TRUE);
    //addG2ConnectionListener(sqm);
  }

  @Override
  public void removeRemoteConnection(RMIEventQueueProcessor client) {
    Trace.send(0, traceKey, i18nTrace, "closeRemoteConnection", client);
    G2ServerQueueManager sqm = getQueueManager(client);
    sqm.unsubscribeAll();
    remoteConnections.remove(client);
    ConnectionResolver.clearStub(client);
    if (remoteConnections.isEmpty()) {
      closeConnection();
      try {
	UnicastRemoteObject.unexportObject(this,true);
      } catch (NoSuchObjectException e) {
	throw new com.gensym.util.UnexpectedException(e);
      }
    }
    sqm.setRemoteClient(null);
    Trace.send(0, traceKey, i18nTrace, "closeRemoteConnection2",
	       remoteConnections, getConnections());
  }

  @Override
  public String getInterfaceNameForG2Class(Symbol g2ClassName_) {
    Class clazz = getInterfaceForG2Class(g2ClassName_);
    if (clazz == null)
      return null;
    else
      return clazz.getName();
  }

  /**
   * Get the definition for this item
   * @undocumented
   */
  @Override
  public G2Definition getDefinition(Item item) throws G2AccessException{
    return item.getDefinition();
  }

  /**
   * @undocumented
   */
  @Override
  public G2Definition getDefinition(int handle, int version) throws G2AccessException{
    G2Definition definition = getClassManager().getDefinition(handle, version);
    return definition;
  }

  /**
   * Get the system inheritance for this item
   * @undocumented
   */
  @Override
  public Sequence getSystemClassInheritancePath(G2Definition definition)
  throws G2AccessException {
    return definition.getSystemClassInheritancePath();
  }

  //
  // end shared code
  //

  /** This relies on the KbWorkspace
  * to maintain accurate information for us to return in the case where
  * the client is an RMIEventQueueProcessor (the default case).
  * Queueing of updates
  * that come in during the downloading process should be handled by the
  * KbWorkspaceImpl.
  * <p>
  * TRICKY STUFF: When an third-tier client wants to represent a
  * workspace we have to make sure G2 knows about the relationship between
  * the client's UiClientSession object and the KbWorkspace. If this is
  * the first third tier representing this workspace via this middle-tier,
  * the KbWorkspaceImpl will result in a call to G2_REPRESENT_WORKSPACE_
  * and we will not need to call G2_REPRESENT_WORKSPACE_. For all subsequent
  * third-tier clients, the KbWorkspaceImpl will just add them as listeners
  * and will not result in a call to G2_REPRESENT_WORKSPACE_, so we will need
  * to make the call ourselves.
  */
  @Override
  public Structure representWorkspace (KbWorkspace workspace,
				       RMIEventQueueProcessor clientRep,
				       UiClientSession session,
				       Symbol callback)
  throws G2AccessException {
    Trace.send(0, traceKey, i18nTrace, "goodRepresentWksp", clientRep,
	       workspace);
    boolean callRepresent = false;
    synchronized (workspaceSubscriptionSessionMap) {
      if (workspaceSubscriptionSessionMap.get(workspace) == null)
	workspaceSubscriptionSessionMap.put(workspace, session);
      else
	callRepresent = true;
    }
    TwServerQueueManager sqm = getQueueManager(clientRep);
    Structure returnVal = sqm.startWorkspaceListening(workspace);

    if (!callRepresent) {
      synchronized (workspaceSubscriptionSessionMap) {
	UiClientSession otherSession =
	  (UiClientSession)workspaceSubscriptionSessionMap.get(workspace);
	if (session.equals(otherSession)) {
	  workspaceSubscriptionSessionMap.remove(workspace);
	  callRepresent = true;
	}
      }
    }
    if (callRepresent)
      representWorkspace(workspace, session);

    return returnVal;
  }

  /** This method is the one that is called by the KbWorkspaceImpl
   */
  @Override
  public Structure representWorkspace (KbWorkspace workspace) 
  throws G2AccessException {
    UiClientSession session =
      (UiClientSession)workspaceSubscriptionSessionMap.remove(workspace);
    if (session == null)
      throw new RuntimeException("error with session");
    return representWorkspace(workspace, session);
  }

  private static final Symbol G2_REPRESENT_WORKSPACE_ = Symbol.intern ("G2-REPRESENT-WORKSPACE");

  private Structure representWorkspace (KbWorkspace workspace,
					UiClientSession session)
  throws G2AccessException {
    
    Object[] args =
    {session, workspace, HANDLE_WORKSPACE_SUBSCRIPTIONS_};

    Structure wsinfo = (Structure)callRPC(G2_REPRESENT_WORKSPACE_, args);
    if (wsinfo != null) {
      Integer subscrpnHandle = (Integer) wsinfo.getAttributeValue(SUBSCRIPTION_HANDLE_, null);
      getSubscpnTable().put(subscrpnHandle, workspace);
    }

    return wsinfo;
  }

  @Override
  public boolean unrepresentWorkspace(KbWorkspace wksp,
				      UiClientSession session,
				      RMIEventQueueProcessor clientRep)
  throws G2AccessException {
    TwServerQueueManager sqm = getQueueManager(clientRep);

    return sqm.stopWorkspaceListening(wksp);
  }

  private static final Symbol G2_UNREPRESENT_WORKSPACE_ = Symbol.intern ("G2-UNREPRESENT-WORKSPACE");

  boolean unrepresentWorkspace(KbWorkspace workspace, UiClientSession session)
  throws G2AccessException {
    int subscriptionHandle = workspace.getG2WkspSubscriptionHandle();
    Object[] args = {session, new Integer(subscriptionHandle)};
    return ((Boolean) callRPC (G2_UNREPRESENT_WORKSPACE_, args)).booleanValue ();
    
  }

  // In the middle-tier the two-arg signature will always be called,
  // and will do the right thing (i.e. result in the ending of the
  // subscription if there are no more sessions interested in
  // this workspace
  @Override
  public boolean unrepresentWorkspace (int subscriptionIndex) 
  throws G2AccessException {
    return true;
  }

  @Override
  public Structure subscribeToModules (RMIEventQueueProcessor remoteQ) 
  throws G2AccessException {
    Trace.send(0, traceKey, i18nTrace, "remoteSubscribeToModules", remoteQ);
    TwServerQueueManager sqm = getQueueManager (remoteQ);

    return sqm.startModuleListening(getKb());
  }

  @Override
  public void unsubscribeToModules (RMIEventQueueProcessor remoteQ) 
  throws G2AccessException {
    Trace.send(0, traceKey, i18nTrace, "remoteUnsubscribeToModules", remoteQ);
    TwServerQueueManager sqm = getQueueManager (remoteQ);
      sqm.stopModuleListening(getKb());
  }

  @Override
  public Structure representTrendChart(Item item, //int itemHandle, 
				       RMIEventQueueProcessor client)
  throws G2AccessException {
    com.gensym.classes.TrendChart trendChart =
      (com.gensym.classes.TrendChart)item;
    Trace.send(0, traceKey, i18nTrace, "goodRepresentTC", client,
	       trendChart);
    TwServerQueueManager sqm = getQueueManager(client);

    return sqm.startTrendChartListening(trendChart);
  }

  @Override
  public boolean unrepresentTrendChart (RMIEventQueueProcessor client,
					TrendChart trendChart) 
       throws G2AccessException
  {
    TwServerQueueManager sqm = getQueueManager(client);
    return sqm.stopTrendChartListening(trendChart);
  }

  @Override
  public Integer subscribeToWorkspaceShowing(UiClientSession session,
					     RMIEventQueueProcessor clientRep)
  throws G2AccessException {
    TwServerQueueManager sqm = getQueueManager(clientRep);

    Integer handle = sqm.subscribeToWorkspaceShowing(session);

     getSubscpnTable().put(handle, sqm);
     return handle;
  }

  @Override
  public void unsubscribeToWorkspaceShowing(Integer subscpnHandle,
					    RMIEventQueueProcessor clientRep)
  throws G2AccessException {
    TwServerQueueManager sqm = getQueueManager(clientRep);
    sqm.unsubscribeToWorkspaceShowing(subscpnHandle);
  }


  /**
   * This method must be overriden, as the assumption in TwGateway
   * is that there is only one UiClientSession to which to subscribe.
   * This is not true in the three-tier architecture.
   */
    @Override
    public void HANDLEWORKSPACESSHOWINGSUBSCRIPTIONS
    (Symbol showOrHide, Item workspace, Structure particulars, 
     int userData, int subscriptionHandle) {
     TwServerQueueManager sqm =
        (TwServerQueueManager)getSubscpnTable().
        get(new Integer(subscriptionHandle));
      
      WorkspaceShowingEvent event
        = new WorkspaceShowingEvent(this, showOrHide, particulars, workspace,
  				  new Integer(userData), subscriptionHandle);

      Trace.send(20, traceKey, i18nTrace, "twrsiHandleWsShowing",
 		showOrHide, sqm, event);

      sqm.addEvent(event);
    }

  @Override
  public UiClientSession registerUiClient(RMIEventQueueProcessor client,
					  LoginRequest login,
					  boolean autoRegisterShowing)
  throws G2AccessException{

    TwServerQueueManager sqm = (TwServerQueueManager)getQueueManager(client);

    UiClientSession session = makeUiClientSession(login,
 						  autoRegisterShowing ?
						  sqm :
 						  null);
    sqm.setSession(session);
    return session;
  }

  /**
   * The UiClientSession for this TwAccess is the object in G2 that
   * represents "this window" for this TwAccess.
   */
  @Override
  public UiClientSession retrieveSession(Object requestor) {
    TwServerQueueManager sqm = (TwServerQueueManager)requestor;
    return sqm.getSession();
  }    

  // What follows are some ideas about how to override hashCode()
  // and equals() in a manner that mimics UnicastRemoteObject
  // (if this ever becomes necessary)
  //sun.rmi.server.ServerRef ref;
  //void setRef(sun.rmi.server.ServerRef ref) {
  //  this.ref = ref;
  //}

  /*
  public int hashCode() {
    return (ref == null) ? super.hashCode() : ref.remoteHashCode();
  }

  public boolean equals(Object obj) {
    if (ref == null)
      return super.equals(obj);

    if (obj instanceof TwRMIServerImpl) {
      return ref.remoteEquals(((TwRMIServerImpl)obj).ref);
    }

    return false;
  }
  */
}
