package com.gensym.jgi.rmi;

import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2AccessInitiationException;

/** The bootstrapping remote interface for connecting to G2 via RMI
* @param client The remote object from the client that will receive
* messages from G2 and call into G2. */
public interface G2RMIAccessBroker extends java.rmi.Remote {
  public G2RMIAccess getOrMakeConnection(G2ConnectionInfo info,
					 RMIEventQueueProcessor clientRep,
					 boolean forceNew)
       throws java.rmi.RemoteException, ConnectionTimedOutException,
	      ClassNotFoundException, G2AccessInitiationException;
}
