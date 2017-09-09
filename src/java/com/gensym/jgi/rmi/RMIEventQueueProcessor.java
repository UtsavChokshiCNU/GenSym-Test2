package com.gensym.jgi.rmi;

import java.util.Vector;
import java.rmi.Remote;
import java.rmi.RemoteException;

import com.gensym.message.MessageEvent;

/** This is for classes that can take Vectors of events for
 * processing. Is useful for connections with a high latency.
 */
public interface RMIEventQueueProcessor extends Remote {

  /** Take the current contents of the queue and process them.
   */
  public void processEventQueue(Vector queueContents)
  throws RemoteException;

  /** The server will attempt to notify the client if it is being disconnected.
   */
  public void receiveServerDisconnectEvent(MessageEvent e)
  throws RemoteException;
}
