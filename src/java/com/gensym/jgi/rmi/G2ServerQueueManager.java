/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   ServerQueueManager.java 
 * 
 * 
 */ 
  
package com.gensym.jgi.rmi;

import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.EventObject;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.io.StringWriter;
import java.io.PrintWriter;

import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.VariableValueListener;
import com.gensym.util.VariableValueEvent;
import com.gensym.message.Trace;
import com.gensym.message.MessageEvent;
import com.gensym.message.Resource;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.message.MessageKey;
import com.gensym.util.VectorQueueManager;
import com.gensym.util.LoopProcessingException;
import com.gensym.util.UnexpectedException;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.ConnectionNotAvailableException;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.VariableOrParameter;
import com.gensym.jgi.G2JavaStubControllerListener;
import com.gensym.jgi.G2JavaStubControllerEvent;
import com.gensym.util.Sequence;

/** Manages the event queue on the server for a single client, and
 * services that client. All calls from a G2 to a client pass through
 * this queue manager.
 */
public class G2ServerQueueManager extends VectorQueueManager
implements ItemListener, G2ConnectionListener, VariableValueListener, G2JavaStubControllerListener {

  private static MessageKey traceKey =
  Trace.registerMessageKey ("com.gensym.jgi.rmi.queue",
			    G2ServerQueueManager.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.rmi.TraceMessages");

  protected MessageKey errorKey =
  Message.registerMessageKey("com.gensym.jgi.rmi.queue",
			     G2ServerQueueManager.class);

  protected Resource i18n =
  Resource.getBundle("com.gensym.jgi.rmi.Messages");
  
  protected Vector lastLoopExceptions = new Vector();
  protected G2Access g2Access;

  private RMIEventQueueProcessor remoteClient;
  private Hashtable itemEventSources = new Hashtable(201);
  private Hashtable variableEventSources = new Hashtable();
  private boolean connectionListening = false;

  private boolean unsubscribeOnConnectError = true;

  protected G2ServerQueueManager(G2Access g2Access,
			       RMIEventQueueProcessor remoteClient) {
    this.g2Access = g2Access;
    setRemoteClient(remoteClient);
  }

  /** Register the fact that the queueManager recognizes <code>source</code>
   * as a source of events. Subclassers can either let their sources
   * become heterogeneous Hashtables, or maintain separate Hashtables for
   * different classes of event source.
   * @return true if <code>source</code> is a new source of events.
   */
  protected boolean addSource(Object source, Hashtable eventSources) {
    if (eventSources.get(source) == null) {
      eventSources.put(source, Boolean.TRUE);
      return true;
    } else {
      return false;
    }
  }

  public Structure subscribeToItem(Item item) throws G2AccessException {
    try {
      addSource(item, itemEventSources);
      return ((ImplAccess)item).addItemListenerRetrievingState(this);
    } catch (G2AccessException g2ae) {
      itemEventSources.remove(item);
      throw g2ae;
    }
  }

  public Sequence subscribeToItemMultiple(Item item, Sequence denotation_sequences) throws G2AccessException {
    try {
      addSource(item, itemEventSources);
      return ((ImplAccess)item).addItemListenerRetrievingStateMultiple(this, denotation_sequences);
    } catch (G2AccessException g2ae) {
      itemEventSources.remove(item);
      throw g2ae;
    }
  } 

  public boolean unsubscribeToItem(Item item) throws G2AccessException{
    if (itemEventSources.get(item) != null) {
      item.removeItemListener(this);
      itemEventSources.remove(item);
      return true;
    } else {
      return false;
    }
  }

  public boolean unsubscribeToItemMultiple(Item item, Sequence subscriptionHandles) throws G2AccessException{
    if (itemEventSources.get(item) != null) {
      ((ImplAccess) item).removeItemListenerForThreeTiers(this, subscriptionHandles);
      itemEventSources.remove(item);
      return true;
    } else {
      return false;
    }
  }

  private static final Symbol SUBSCRIPTION_HANDLE_ = Symbol.intern ("SUBSCRIPTION-HANDLE");

  public Structure startVariableValueListening(VariableOrParameter itm)
  throws G2AccessException {
    Structure val = itm.addVariableValueListenerRetrievingState(this);
    variableEventSources.put(itm, Boolean.TRUE);
    return val;
  }

  public void stopVariableValueListening(VariableOrParameter itm)
  throws G2AccessException {
    itm.removeVariableValueListener(this);
    variableEventSources.remove(itm);
  }

  public void startConnectionListening() {
    g2Access.addG2ConnectionListener(this);
    connectionListening = true;
  }

  public void stopConnectionListening() {
    if (connectionListening) {
      g2Access.removeG2ConnectionListener(this);
      connectionListening = false;
    }
  }

  @Override
  public void unsubscribeAll() {
    lastLoopExceptions.removeAllElements();
    for (Enumeration en = itemEventSources.keys(); en.hasMoreElements();) {
      Item source = (Item)en.nextElement();
      try {
	unsubscribeToItem(source);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	lastLoopExceptions.addElement(g2ae);
      }
    }
    for (Enumeration en = variableEventSources.keys(); en.hasMoreElements();) {
      VariableOrParameter source = (VariableOrParameter)en.nextElement();
      try {
	stopVariableValueListening(source);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	lastLoopExceptions.addElement(g2ae);
      }
    }
    stopConnectionListening();
    if (!lastLoopExceptions.isEmpty()) {
      // fix this: should add explanatory message
      throw new UnexpectedException((Throwable)lastLoopExceptions.firstElement());
    }
  }

  /** Attempts to notify both the client and the server that
   * they are being disconnected from each other, then stops the
   * thread.
   */
  protected void disconnectClient(Exception ex) {
    
    MessageEvent me =
      new MessageEvent(g2Access, 0, errorKey, i18n,
		       "eventProcessingError",
		       new Object[] {ex});
    Message.send(me);
    try {
      warnServer(ex);
    } catch(Exception ex2) {
      Trace.exception(ex2);
    }

    try {
      unsubscribeAll();
    } catch(Exception ex2) {
      Trace.exception(ex2);
    }

    try {
      // Probably vain attempt to tell the client they are
      // being disconnected
      remoteClient.receiveServerDisconnectEvent(me);
    } catch(Exception ex2) {
      Trace.exception(ex2);
    }
    setRemoteClient(null);
  }
	    
  public void setRemoteClient (RMIEventQueueProcessor rc) {
    remoteClient = rc;
    if (remoteClient == null)
      setRunning(false);
  }
 

  /** Sends the current queue contents to a remote client.
   * Relies on the fact that this method is called *only* from the
   * run method of the thread, and as such is not synchronized on the
   * object or the queue.
   * Is synchronized on the eventSources.
   * <p>
   * If a RemoteException is thrown during the the remoteClient's
   * event processing, one of the following will occur:
   * <UL>
   * <L1> If the RemoteException is a ConnectException, or if the
   * the RemoteException is nesting an Error, then notify the client and the
   * server that a disconnection will occur, then disconnect the client and
   * stop the thread. </L1>
   * <L1> Otherwise, simply warn the server that a problem has occured,
   * but proceed with event processing. <L1>
   * </UL>
   */
  @Override
  protected void processQueue(Vector queueCopy) {
    try {
      Trace.send(30, traceKey, i18nTrace, "sqmrun1", this);
      remoteClient.processEventQueue(queueCopy);
    } catch (java.rmi.ConnectException ce) {
      Trace.send(30, traceKey, i18nTrace, "sqmrun2", this);
      Trace.exception(ce);
      disconnectClient(ce);
    } catch (RemoteException ex) {
      Trace.send(30, traceKey, i18nTrace, "sqmrun3", this);
      Trace.exception(ex);
      Throwable t = ex.detail;
      if (t instanceof LoopProcessingException) {
	Trace.send(30, traceKey, i18nTrace, "sqmrun4", this);
	warnServer(t);
      } else if (t instanceof Error) {
	Trace.send(30, traceKey, i18nTrace, "sqmrun5", this);
	disconnectClient(ex);
      } else {
	Trace.send(30, traceKey, i18nTrace, "sqmrun6", this);
	warnServer(ex);
      }
    }
  }

  protected void warnServer(Throwable t) {
    StringWriter stw = new StringWriter();
    PrintWriter pw = new PrintWriter(stw);
    if (t instanceof LoopProcessingException)
      ((LoopProcessingException)t).printFullStackTrace(pw);
    else
      t.printStackTrace(pw);
    g2Access.reportLogBookErrorMessage(Symbol.intern(t.getClass().getName()), 
				       "Exception raised from client (" + remoteClient + ")\n" + 
				       stw.toString());
  }

  @Override
  public String toString() {
    return super.toString() + "[" + getClass() + ";"+ g2Access +
      ";" + remoteClient + "]";
  }

  //
  // ItemListener
  //

  @Override
  public void receivedInitialValues (ItemEvent e) {
    // This should only be generated directly by
    // an item, and should not be passed on.
  }

  @Override
  public void itemModified (ItemEvent e){
    addEvent(e);
  }

  @Override
  public void itemDeleted (ItemEvent e){
    addEvent(e);
  }

  //
  // G2ConnectionListener
  //
  
  @Override
  public void g2IsPaused(G2ConnectionEvent e){
    addEvent(e);
  }
  
  @Override
  public void g2IsResumed(G2ConnectionEvent e){
    addEvent(e);
  }

  @Override
  public void g2IsReset(G2ConnectionEvent e){
    addEvent(e);
  }

  @Override
  public void g2IsStarted(G2ConnectionEvent e){
    addEvent(e);
  }

  @Override
  public void g2ConnectionClosed(G2ConnectionEvent e){
    addEvent(e);
  } 

  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent e){
    addEvent(e);
  }

  @Override
  public void g2MessageReceived(G2ConnectionEvent e){
    addEvent(e);
  }

  @Override
  public void communicationError(G2CommunicationErrorEvent e){
    addEvent(e);
  }

  @Override
  public void readBlockage(G2ConnectionEvent e){
    addEvent(e);
  }

  @Override
  public void writeBlockage(G2ConnectionEvent e){
    addEvent(e);
  }

  //
  // VariableValueListener
  //
  @Override
  public void valueChanged(VariableValueEvent e) {
    addEvent(e);
  }

  @Override
  public void receivedInitialValue(VariableValueEvent e) {
    // swallow it: third-tier client will get its own
    // event generated by the VariableOrParameter on the
    // third-tier addEvent(e);
  }

  // G2JavaStubControllerlistener

  @Override
  public void callMethod(G2JavaStubControllerEvent e) {
    //System.out.println("Got " + e + e.getTarget() + e.getMethodName());
    if (running)
      addEvent(e);
    else {
      // force an exception, so that the G2JavaStubController dispatch cleans up
      RMIEventQueueProcessor temp = remoteClient;
      setRemoteClient(null);
      throw new ConnectionNotAvailableException("Client " + temp + " is no longer connected");
    }
  }

  @Override
  public void deleteInstance(G2JavaStubControllerEvent e) {
    addEvent(e);
  }
}

