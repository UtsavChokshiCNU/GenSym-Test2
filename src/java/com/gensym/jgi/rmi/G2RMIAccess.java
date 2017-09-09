/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2RMIAccess.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.jgi.rmi;

/* Imports */
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;

import java.rmi.RemoteException;
import java.util.Vector;


/**
 * The remote version of <code>G2Access</code>
 * @see com.gensym.jgi.G2Access
 *
 * 
 * @version 	1.0 5th June 1997
 *
 * @author Robert Penny
 */
public interface G2RMIAccess extends java.rmi.Remote
{

  public void returnMessage(String message) throws RemoteException;

  public void closeConnection() throws RemoteException;

  public Object callRPC (Symbol g2_procedure_name, 
			 Object items[], int timeout) throws G2AccessException, RemoteException;

  public Object callRPC (Symbol g2_procedure_name, 
			 Object items[]) throws G2AccessException, RemoteException;

  public void startRPC(Symbol g2_procedure_name, 
		       Object items[]) throws RemoteException;

       /*
  public Object getValue (Item itm, 
			  Sequence denotation,
			  Object defaultValue) throws RemoteException;

  public boolean setValue (Item itm,
			   Sequence denotation,
			   Object value) throws RemoteException;
			   */
  public Item getUniqueNamedItem (Symbol itmClass,
				    Symbol itmName) throws G2AccessException, RemoteException;

  public String getAttributeAsText (Item itm,
				    Symbol slotName,
				    Symbol specificClassIfAny) throws G2AccessException, RemoteException;

  public Sequence getAttributeDescriptions (Symbol className, Sequence attributeNames) throws G2AccessException, RemoteException;

  public Structure subscribeToItem (RMIEventQueueProcessor client,
				    Item itm,
				    Sequence denotation,
				    Object userData) 
  throws RemoteException, G2AccessException;

  public Sequence subscribeToItemMultiple (RMIEventQueueProcessor client,
				    Item itm,
				    Sequence denotation,
				    Object userData) 
  throws RemoteException, G2AccessException;

  public boolean unsubscribeToItem (RMIEventQueueProcessor client,
				    Item item)
       throws RemoteException, G2AccessException;
  public boolean unsubscribeToItemMultiple (RMIEventQueueProcessor client,
				    Item item, Sequence subscrpnHandles)
       throws RemoteException, G2AccessException;
  public String toURLString () throws RemoteException;

  public String toShortString () throws RemoteException;

  public void setInterfaceDebugOptions(boolean on) throws RemoteException;

  public Object getValue (Item itm,
			  Denotation denotation)
       throws G2AccessException, RemoteException;

  public boolean setValue (Item itm,
			   Denotation denotation,
			   Object value) 
       throws G2AccessException, RemoteException;

  public G2Definition getDefinition(Symbol g2ClassName) throws G2AccessException, RemoteException;

  public G2Definition getDefinition (Item item) throws G2AccessException, RemoteException;

  public G2Definition getDefinition(int handle, int handleVersion) throws RemoteException, G2AccessException;

  public Sequence getSystemClassInheritancePath(G2Definition definition)
  throws RemoteException, G2AccessException;

  public void setRemoteRPCReturnKind (Symbol g2_procedure_name,
						    int return_value_type)
  throws RemoteException;

  public void addRemoteConnection(RMIEventQueueProcessor client)
  throws RemoteException;

  public void removeRemoteConnection(RMIEventQueueProcessor client)
  throws RemoteException;

  public Item getG2ProxyForJavaObject(String g2ProxyClass,
				      Symbol g2ParentClass,
				      Object javaObject) throws G2AccessException, RemoteException;

   public G2RMIJavaStubController getRemoteG2JavaStubController()
       throws RemoteException;


   public G2JavaStubControllerListener getClientListenerForG2JavaStubController(RMIEventQueueProcessor client)
       throws RemoteException;

   public String getInterfaceNameForG2Class(Symbol g2ClassName_)
       throws RemoteException;

   public void returnValues(Item[] items, 
			    Structure[] attributesArray, 
			    Object[] values, 
			    int[] statusValues) throws RemoteException;

  public void receivePing() throws RemoteException;
  public int getPingFrequency() throws RemoteException;
  public void setPingFrequency(int freq) throws RemoteException;
}
