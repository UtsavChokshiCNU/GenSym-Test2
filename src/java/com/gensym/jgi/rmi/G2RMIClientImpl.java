/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   G2RMIClientImpl.java 
 * 
 * 
 */ 
  
package com.gensym.jgi.rmi;

import java.rmi.*;
import java.util.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.ItemImpl;
import com.gensym.classes.VariableOrParameter;
import com.gensym.classes.G2Definition;
import java.lang.reflect.Field;
import java.io.StringWriter;
import java.io.PrintWriter;

/** This provides a client implementation in front of G2 for the third tier
 * in a 3-tier RMI implementation. It forwards method calls into G2 to a
 * remote stub of a middle tier implementation */

public class G2RMIClientImpl extends G2Gateway
implements G2Access, RMIEventQueueProcessor, RemoteG2JavaStubControllerAccess, G2RemoteClient {

  private G2RMIAccess server;
  private G2JavaStubController g2JavaStubController = G2RMIJavaStubControllerImpl.getG2JavaStubController();

  public static final boolean traceOn = false;
  private static MessageKey errorKey =
  Trace.registerMessageKey("com.gensym.rmi" ,
			   "com.gensym.jgi.rmi.G2RMIClientImpl");

  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.rmi" ,
			   "com.gensym.jgi.rmi.G2RMIClientImpl");

  private static Resource i18nJgiTrace = Trace.getBundle("com.gensym.jgi.rmi.Trace");

  private static Resource i18n = Trace.getBundle("com.gensym.jgi.rmi.Messages");

  private static final Symbol SUBSCRIPTION_HANDLE_ =
  Symbol.intern ("SUBSCRIPTION-HANDLE");

  protected String url;

  private Hashtable subscpnTableHandle = getSubscpnTable();
  private Hashtable g2ClassNameMap = new Hashtable();

  private boolean isConnected = false;

  /** prevents initialization of JGInterface (should occur in remote VM).*/
  public static void initialize() {
    Trace.send(1, traceKey, i18nJgiTrace, "localInitializationCalled");
  }

  /** This constructor on its own will not provide a "useful"
   * connection. One must call initiateConnection() in order
   * to do have a useful connection. It is best to use getOrMakeConnection. */
  public G2RMIClientImpl() {
    super();
    try {
      exportSelf();
      if (System.getSecurityManager() != null) {
	System.setSecurityManager(new RMISecurityManager());
      }
    } catch (Exception ex) {
      Trace.exception(ex);
    }
  }

  /** Contacts the Broker specified in the info object and
   * tries getOrMakeConnection on that broker */
  @Override
  public boolean initiateConnection(G2ConnectionInfo info)
  throws G2AccessInitiationException{
    try {
      setConnectionInfo(info);
      String brokerUrl = info.getBrokerURL();
      
      Trace.send(10, traceKey, i18nJgiTrace, "Look for broker");
      G2RMIAccessBroker broker = (G2RMIAccessBroker)Naming.lookup(brokerUrl);
      Trace.send(3, traceKey, i18nJgiTrace, "got broker: {0}", broker);
      
      // A near clone, only changing the connectionClassName:
      // the client should be able to decide what kind of server
      // it wants.
      G2ConnectionInfo remoteInfo =
	new G2ConnectionInfo(null, // No four-tier apps!!!
			     info.getLogicalName(),
			     info.getHost(),
			     info.getPort(),
			     "com.gensym.jgi.rmi.G2RMIServerImpl",
			     info.getGsiInterfaceClassName(),
			     info.getInterfaceName(),
			     G2ConnectionInfo.GSI_PROTOCOL,
			     info.getPermanent(),
			     info.getRpis(),
			     info.isForceNew(),
			     info.isSharable());
      
      Trace.send(10, traceKey, i18nJgiTrace, "contact server");
      server = (G2RMIAccess)broker.
	getOrMakeConnection(remoteInfo, this, false);
      Trace.send(10, traceKey, i18nJgiTrace, "got server");
      
      Trace.send(3, traceKey, i18nJgiTrace, "got server: {0}", server.toString());
      ConnectionResolver.mapStubToWrapper(server, this);
      isConnected = true;
    } catch (Exception e) {
      e.printStackTrace();
      throw new G2AccessInitiationException(e);
    }
    initializeInstance ();
    storeOpenConnection();
    dispatchG2ConnectionEvent(new G2ConnectionEvent(this,
						    G2ConnectionEvent.G2_CONNECTION_INITIALIZED));
    new ClientPing(this,server).start();
    return true;
  }

  //
  // begin shared code
  //

  /**
   * @undocumented
   */
  @Override
  protected void initializeReceiveRegistrations() {
  }

  /** IMPORTANT: must only be called once.
   */
  protected void exportSelf() {
    try {
      Trace.send(10, traceKey, i18nJgiTrace, "rciTryToExport");
      java.rmi.server.UnicastRemoteObject.exportObject(this);
      Trace.send(3, traceKey, i18nJgiTrace, "rciExported", this);

      G2RMIJavaStubControllerImpl.exportObject();
      Trace.send(3, traceKey, i18nJgiTrace, "rciExported", g2JavaStubController);
    } catch (RemoteException ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }
  }

  @Override
  public String checkForHandleOK(int type) {
    return null;
  }

  @Override
  public final void closeConnection()
  {
    try {
    server.removeRemoteConnection(this);
    // In two-tier gateways, this is fired by GSI after the
    // closeConnection method has been called on the Gateway.
    dispatchG2ConnectionEvent(new G2ConnectionEvent(this,
						    G2ConnectionEvent.G2_CONNECTION_CLOSED));
    super.closeConnection();
    } catch (com.gensym.jgi.G2GatewayNotInitializedError e) {
      //Want some of the cleanup from the call to super,
      // but that throws an exception on the third tier
      //e.printStackTrace();
    } catch (RemoteException re) {
      re.printStackTrace();
    }
    ConnectionResolver.clearStub(server);
  }

  @Override
  public boolean isAlive () {
    return isConnected;
  }

  @Override
  public Object callRPC (Symbol g2_procedure_name, 
				    Object items[])
  throws G2AccessException{
    Object retnval = null;
    try {
     retnval = server.callRPC(g2_procedure_name, items);
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
    return retnval;
  }

  @Override
  public Object callRPC (Symbol g2_procedure_name, 
				    Object items[], int timeout)
  throws G2AccessException{
     
    Object retnval = null;
    try {
      retnval = server.callRPC(g2_procedure_name, items, timeout);
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
    return retnval;
  }

  @Override
  public void startRPC(Symbol g2_procedure_name, 
		       Object items[])
  {
    try {
    server.startRPC(g2_procedure_name, items);
    } catch (RemoteException re) {
      Trace.exception(re);
    }
  }

  /**
   * Return an Item that represents a G2 ITEM that is a proxy for a
   * Java Object.
   *
   *@param g2ProxyClass the G2 Class name, used to create an instance of a proxy
   * in the event that an existing proxy could not be found. Set null to
   * use the default G2 Class registered for the class of JavaObject.
   *@param javaObject the Java Object to create a proxy for.
   *@exception G2AccessException When there is a problem communicating with G2 or
   * a G2 Class could not be found to create the proxy ITEM
   */
  @Override
  public Item getG2ProxyForJavaObject(String g2ProxyClass,
				      Symbol g2ParentClass,
				      Object javaObject) 
  throws G2AccessException {
    try {
      Item itm =  server.getG2ProxyForJavaObject(g2ProxyClass,
					    g2ParentClass,
					    g2JavaStubController);
      g2JavaStubController.associate(this, itm, javaObject);
      return itm;
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
  }

  /** Return the Remote G2RMIJavaStubController from the server.
   */
  @Override
  public G2RMIJavaStubController getRemoteG2JavaStubController() 
       throws RemoteException {
    return server.getRemoteG2JavaStubController();
  }


  /** The is the signature used by ItemImpl, and so it must be
   * intercepted by the client context in three tier */
  @Override
  public Structure subscribeToItem(Item itm, Sequence denotation,
				   Object userData)
  throws G2AccessException {
    Structure returnValue = null;
    try {
       returnValue = server.subscribeToItem(this, itm, denotation,
					      userData);
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
    Integer subscrpnHandle =
      (Integer)returnValue.getAttributeValue (SUBSCRIPTION_HANDLE_, null);
    subscpnTableHandle.put(subscrpnHandle, itm);
    return returnValue;
  }

  /** The is the signature used by ItemImpl, and so it must be
   * intercepted by the client context in three tier. This is for
   * subscribing multiple items
   * @author fy 02/28/00
   */
  @Override
  public Sequence subscribeToItemMultiple(Item itm, Sequence denotation_sequences,
				   Object userData)
  throws G2AccessException {
    Sequence returnValue = null;
    try {
       returnValue = server.subscribeToItemMultiple(this, itm, denotation_sequences,
					      userData);
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
    for (int i=0; i < returnValue.size(); i++) {
        Integer subscrpnHandle =
                (Integer) ((Structure) returnValue.get(i)).getAttributeValue (SUBSCRIPTION_HANDLE_, null);
        subscpnTableHandle.put(subscrpnHandle, itm);
    }
    return returnValue;
  }

  /**
   * Removes a subscription.
   * @param subscrpnHandle the Integer obtained from subscribetoG2Item
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @return a boolean specifying whether the unsubscribe was successful
   */
  @Override
  public boolean unsubscribeToItem (int subscrpnHandle)
       throws G2AccessException
  {
    Item itm = (Item)subscpnTableHandle.remove (subscrpnHandle);
    if (!isAlive ())
      return true;

    if (itm != null) {
      try {
	server.unsubscribeToItem(this, itm);
	return true;
      } catch (RemoteException re) {
	Trace.exception(re);
	throw new G2AccessException(re);
      }
    } else {
      return false;
    }
  }

  /**
   * Removes a set of subscriptions.
   * @param subscrpnHandle the Integer obtained from subscribetoG2Item
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @return a boolean specifying whether the unsubscribe was successful
   * @author fy 02/29/00
   */
  @Override
  public boolean unsubscribeToItemMultiple (Sequence subscrpnHandles)
       throws G2AccessException
  {
    Item itm = null;
    for (int i=0; i < subscrpnHandles.size(); i++) {
       itm = (Item)subscpnTableHandle.remove ((Integer) subscrpnHandles.elementAt(i));
    }
    if (!isAlive ())
      return true;

    if (itm != null) {
      try {
	server.unsubscribeToItemMultiple(this, itm, subscrpnHandles);
	return true;
      } catch (RemoteException re) {
	Trace.exception(re);
	throw new G2AccessException(re);
      }
    } else {
      return false;
    }
  }

  @Override
  public void setInterfaceDebugOptions (boolean debugState) {
    try {
      server.setInterfaceDebugOptions(debugState);
    } catch (RemoteException re) {
      Trace.exception(re);
    }
  }

  /**
   * Get the G2Definition object from the 2nd tier
   */
  @Override
  public G2Definition getDefinition (Symbol g2ClassName) throws G2AccessException {
    try {
      return server.getDefinition (g2ClassName);
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
  }

  @Override
  public G2Definition getDefinition(Item item) throws G2AccessException {
    try {
      return server.getDefinition(item);
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
  }

  @Override
  public G2Definition getDefinition(int handle, int handleVersion) throws G2AccessException{
    try {
      G2Definition definition = getClassManager().getDefinition(handle, handleVersion);
      if (definition == null) {
	definition = server.getDefinition(handle, handleVersion);
 	Symbol className = definition.getClassName();
 	getClassManager().storeClassDefinition(className, definition,
					       com.gensym.classes.SystemPredicate.isSystemClass (className));
      }
      return definition;
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
  }

  @Override
  public Sequence getSystemClassInheritancePath(G2Definition definition)
  throws G2AccessException {
    try {
      return server.getSystemClassInheritancePath(definition);
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new G2AccessException(re);
    }
  }      

  /**
   * <bold>FOR INTERNAL USE ONLY.</bold>
   * Stores the interface by its G2 Class name symbol.
   * Will be properly hidden in later releases. If the interface
   * has no g2ClassName field, then it is not stored, and its
   * super-interfaces are not stored.
   * @param thisInterface should be an interface, not a class.
   * @undocumented
   * @deprecated
   */
  @Override
  public void storeInterfaceForG2Class (Class thisInterface) {
    if (ITEM_CLASS.isAssignableFrom (thisInterface)) {
      try {
	Field field = thisInterface.getField("g2ClassName");
	if (field == null)
	  return;
	
	Symbol key = (Symbol)field.get(null);
	if (g2ClassNameMap.get(key) != null)
	  return;
	
	g2ClassNameMap.put(key, thisInterface);
	Class[] interfaces = thisInterface.getInterfaces();
	if (interfaces == null)
	  return;
	int length = interfaces.length;
	for(int i = 0; i < length; i++) {
	  storeInterfaceForG2Class(interfaces[i]);
	}
      } catch (Exception ex) {
	Trace.exception (ex, "Exception while storing Interface of : " + thisInterface.getName());
      }
    }
  }

  /**
   * @undocumented
   * Three tier version, does nothing.
   */
  @Override
  public void unloadClass(Symbol g2ClassName) {
  }

  /**
   * @undocumented
   * No loader in third tier.
   */
  @Override
  public boolean makesOwnStubs() {
    return false;
  }

  /**
   * For finding an already loaded interface based on its G2 name.
   * @return The interface corresponding to <code>g2ClassName_</code>
   * if that interface has already been loaded, <code>null</code> otherwise.
   */
  @Override
  public Class getInterfaceForG2Class (Symbol g2ClassName_) {
    Class clazz = (Class)g2ClassNameMap.get(g2ClassName_);
    if (clazz != null)
      return clazz;

    try {
      String className = server.getInterfaceNameForG2Class (g2ClassName_);
      if (className == null)
	return null;

      ClassLoader loader = getClass().getClassLoader();
	  
      if (loader == null)
	clazz = Class.forName(className);
      else
	clazz = loader.loadClass(className);
      g2ClassNameMap.put(g2ClassName_, clazz);
      return clazz;
    } catch (Exception ex) {
      Trace.exception(ex);
      throw new com.gensym.util.UnexpectedException(ex);
    }
  }

  @Override
  public void dispatchG2ConnectionEvent(G2ConnectionEvent event) {
    if (event.getId () == G2ConnectionEvent.G2_CONNECTION_CLOSED)
      isConnected = false;
    super.dispatchG2ConnectionEvent(event);
  }

  @Override
  public void receiveServerDisconnectEvent(MessageEvent e) {
    Message.send(e);
  }

  @Override
  public void setRemoteRPCReturnKind (Symbol g2_procedure_name,
				      int return_value_type)
  {
    try {
      server.setRemoteRPCReturnKind(g2_procedure_name, return_value_type);
    } catch (RemoteException re) {
      Trace.exception(re);
      throw new com.gensym.util.UnexpectedException(re);
    }
  }

  /** NOTE: if the processing of any event throws anything worse than
   * an Exception (e.g., an Error), all event processing will stop.
   */
  @Override
  public void processEventQueue(Vector queue) {
    if (traceOn)
      Trace.send(20, traceKey, i18nJgiTrace, "g2rciprocessEventQueue", this, queue.size());
    Vector failedEvents = null;
    Vector eventExceptions = null;
    Vector stackTraces = null;

    for (Enumeration en = queue.elements(); en.hasMoreElements();) {
      EventObject e = (EventObject)en.nextElement();
      Trace.send(30, traceKey, i18nJgiTrace, "g2rciprocessEventQueue2", e);
      try {
	if (e instanceof ItemEvent) {
	  ((ItemImpl)e.getSource()).
	    processItemEvent((ItemEvent)e);
	} else if (e instanceof G2ConnectionEvent) {
	  dispatchG2ConnectionEvent((G2ConnectionEvent)e);
	} else if (e instanceof VariableValueEvent) {
	  ((VariableOrParameter)e.getSource()).
	    processVariableValueEvent((VariableValueEvent)e);
	} else if (e instanceof G2JavaStubControllerEvent) {
	  g2JavaStubController.processG2JavaStubControllerEvent((G2JavaStubControllerEvent)e);
	  //
	  // end shared code
	  //
	} else {
	  throw new IllegalArgumentException(i18n.format("unknownEventClass", e));
	}
      } catch (Exception ex) {
	Trace.exception(ex);
	Message.send(new MessageEvent(this, 1, errorKey,
				      i18n, "eventProcessingException",
				      new Object[] {e, ex}));
	if (failedEvents == null) {
	  failedEvents = new Vector();
	  eventExceptions = new Vector();
	  stackTraces = new Vector();
	}
	failedEvents.addElement(e);
	eventExceptions.addElement(ex);

	// Server will loose the stack trace information;
	StringWriter sw = new StringWriter();
	PrintWriter pw = new PrintWriter(sw);
	ex.printStackTrace(pw);
	stackTraces.addElement(sw.toString());
      }
    }

    if (eventExceptions != null) {
      Trace.send(5, traceKey, i18nJgiTrace, "loopEventExceptions",
		 eventExceptions, failedEvents);
      throw new LoopProcessingException(eventExceptions, stackTraces, failedEvents);
    }
  }


  @Override
  public void returnValues(Item[] items, 
			  Structure[] attributesArray, 
			  Object[] values, 
			   int[] statusValues) {
    try {
      server.returnValues(items, 
			  attributesArray, 
			  values, 
			  statusValues);
      } catch (RemoteException re) {
	throw new com.gensym.util.UnexpectedException(re);
      }
  }

  @Override
  public void returnMessage(String message) {
    try {
      server.returnMessage(message);
      } catch (RemoteException re) {
	throw new com.gensym.util.UnexpectedException(re);
      }
  }

}
