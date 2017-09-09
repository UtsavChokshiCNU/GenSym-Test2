/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2RemoteClient.java
 *
 *     
 *   Modifications:
 *
 */

/* This interface is so that both JGI and NTW RMI connections can
   handle the remote ping keep alive implementation without duplicating
   the ClientPing class, so that ClientPing can use the type G2RemoteClient
   as its argument. */

package com.gensym.jgi.rmi;
import com.gensym.jgi.*;
public interface G2RemoteClient {
  boolean isAlive();
  public void dispatchG2ConnectionEvent(G2ConnectionEvent event);
}
