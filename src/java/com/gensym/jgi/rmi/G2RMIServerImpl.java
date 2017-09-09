package com.gensym.jgi.rmi;

import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.ItemImpl;
import com.gensym.classes.VariableOrParameter;
import com.gensym.classes.VariableOrParameterImpl;
import com.gensym.classes.G2Definition;

/** This provides a server implementation in front of G2 for the middle tier
 * in a 3-tier RMI implementation.
 * It forwards callbacks out from G2 (G2Events) into a remote stub, or
 * queues them for a G2Connection client implementation to pick up.
 */

public class G2RMIServerImpl extends G2Gateway
implements G2Callbacks, G2RMIAccess{

  private transient Vector eventQueue = new Vector();
    
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.rmi",
			   "com.gensym.jgi.rmi.G2RMIServerImpl");
  private static Resource i18nTrace = null;

  private Hashtable remoteConnections = new Hashtable();

  private boolean unsubscribeOnConnectException = true;

  private boolean disconnected = false;

  private static Symbol _handle_subscriptions 
                          = Symbol.intern ("HANDLESUBSCRIPTIONS");

  private static Symbol _removeSubscriber_Symbol 
                        = Symbol.intern("G2-UNSUBSCRIBE-TO-ITEM");

  private static final Symbol SUBSCRIPTION_HANDLE_
                              = Symbol.intern ("SUBSCRIPTION-HANDLE");

  private static final Symbol INITIAL_VALUE_ = Symbol.intern ("INITIAL-VALUE");

  public G2RMIServerImpl() {
    super();
    try {
      UnicastRemoteObject.exportObject(this);
    } catch (RemoteException re) {
      throw new com.gensym.util.UnexpectedException(re);
    }
  }

  //
  // begin psuedo shared code
  //

  private Hashtable client2QueueManagerMap = new Hashtable();
  
  protected G2ServerQueueManager getQueueManager(RMIEventQueueProcessor
						 remoteClient) {
    G2ServerQueueManager sqm =
      (G2ServerQueueManager)client2QueueManagerMap.get(remoteClient);
    if (sqm == null) {
      sqm = new G2ServerQueueManager(this, remoteClient);
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
}
