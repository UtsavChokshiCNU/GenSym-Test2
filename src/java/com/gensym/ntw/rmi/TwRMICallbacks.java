/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwRMICallbacks.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.ntw.rmi;

import com.gensym.jgi.rmi.*;
import com.gensym.jgi.G2Callbacks;
import com.gensym.jgi.G2CallbacksException;
import com.gensym.ntw.util.TrendChartEvent;
import java.rmi.RemoteException;

public interface TwRMICallbacks extends G2RMICallbacks {

  public void handleWorkspaceSubscriptions(RMIWorkspaceEvent event)
       throws RemoteException, G2CallbacksException;

  public void processTrendChartEvent(TrendChartEvent event)
       throws RemoteException, G2CallbacksException;
  
  public String testCall() throws RemoteException;
}
