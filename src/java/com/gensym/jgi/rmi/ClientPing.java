/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   ClientPing.java 
 * 
 * 
 */ 
  
package com.gensym.jgi.rmi;
import java.rmi.*;
import com.gensym.jgi.*;



/* This thread implements a keep alive so that a third tier client can
   be informed when the middle tier goes down -- this will be treated
   as a G2 connection closed event, as GSI would if its network
   connection to G2 were severed. */

  /**
   * @undocumented
   */
public class ClientPing extends Thread {
  G2RemoteClient cl;
  G2RMIAccess srv;
  public ClientPing (G2RemoteClient client, G2RMIAccess server) {
    super();
    cl = client;
    srv = server;
    try {
      pingFrequency = srv.getPingFrequency();
    } catch (RemoteException e) {
      pingFrequency = -1; //give up if any problem
    }      
  }

  private int pingFrequency;

  @Override
  public void run() {
    if (pingFrequency >= 0) {
      do {
	try {
	  sleep (pingFrequency * 1000L);
	}
	catch (java.lang.InterruptedException e) { System.out.println ("got interrupted in ping thread.");}
	try {
	  srv.receivePing();
	} catch (RemoteException ex) {
	  cl.dispatchG2ConnectionEvent(new G2ConnectionEvent(cl,
							     G2ConnectionEvent.G2_CONNECTION_CLOSED));
	  
	}
      } while (cl.isAlive());
    }
  }
}
  
