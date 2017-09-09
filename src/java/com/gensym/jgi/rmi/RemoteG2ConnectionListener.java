/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      RemoteG2ConnectionListener.java
 *
 * Description:
 *               One set of information to draw and how to draw it
 *
 *
 */
package com.gensym.jgi.rmi;

import java.rmi.Remote;
import java.rmi.RemoteException;
import com.gensym.jgi.G2ConnectionEvent;

public interface RemoteG2ConnectionListener extends Remote {
  
  public void dispatchG2ConnectionEvent(G2ConnectionEvent event)
       throws RemoteException;
}

