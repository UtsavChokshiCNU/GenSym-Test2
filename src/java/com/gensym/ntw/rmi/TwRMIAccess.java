/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwAccess.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.ntw.rmi;

import java.rmi.*;
import java.util.Vector;

import com.gensym.jgi.rmi.*;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.irm.IconRenderingManager;
import com.gensym.ntw.*;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.TrendChart;
import com.gensym.classes.UiClientSession;

/** This interface class provides the outbound methods for
 * access to workspace methods in G2
 *
 * @version 1.0 22 May 1977
 *
 * @author Robert Penny
 */

public interface TwRMIAccess extends G2RMIAccess
{

  public Structure representWorkspace (KbWorkspace workspace,
				       RMIEventQueueProcessor clientRep,
				       UiClientSession session,
				       Symbol callback) 
  throws RemoteException, G2AccessException;

  public boolean unrepresentWorkspace(KbWorkspace workspace,
				      UiClientSession session,
				      RMIEventQueueProcessor clientRep)
  throws RemoteException, G2AccessException;

  public Structure subscribeToModules (RMIEventQueueProcessor clientRep) 
  throws RemoteException, G2AccessException;

  public void unsubscribeToModules (RMIEventQueueProcessor clientRep) 
  throws RemoteException, G2AccessException;

  public Structure representTrendChart (Item item,
					RMIEventQueueProcessor client) 
  throws RemoteException, G2AccessException;

  public boolean unrepresentTrendChart (RMIEventQueueProcessor client,
					TrendChart trendChart) 
  throws RemoteException, G2AccessException;

//   public UiClientSession makeUiClientSession(G2ConnectionInfo info,
// 					     Object clientRep)
//        throws RemoteException;

  public Integer subscribeToWorkspaceShowing(UiClientSession session,
					     RMIEventQueueProcessor clientRep)
       throws RemoteException, G2AccessException;

  public void unsubscribeToWorkspaceShowing(Integer subscpnHandle,
					    RMIEventQueueProcessor clientRep)
       throws RemoteException, G2AccessException;

  public void setUserMode (Symbol newUserMode) 
  throws RemoteException, G2AccessException;

  public Symbol getUserMode () 
  throws RemoteException, G2AccessException;

  public UiClientSession registerUiClient(RMIEventQueueProcessor client,
					  LoginRequest login,
					  boolean autoRegisterShowing)
  throws RemoteException, G2AccessException;
}
