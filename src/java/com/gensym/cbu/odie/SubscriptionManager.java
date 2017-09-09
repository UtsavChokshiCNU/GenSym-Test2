package com.gensym.cbu.odie;

import java.rmi.RemoteException;
import java.rmi.Remote;
import java.util.Enumeration;
import java.io.Serializable;

interface SubscriptionManager extends Remote
{
  public Subscription addSubscription(Subscriber subscriber, EventFilter eventFilter, int priority) 
       throws SubscriptionAlreadyExistsException, RemoteException;

  public void removeSubscription(Subscriber subscriber, EventFilter eventFilter, int priority) 
       throws SubscriptionNotFoundException, RemoteException;

  public void removeSubscription(Subscription subscription) throws SubscriptionNotFoundException, RemoteException;

  public void changeSubscriptionPriority(Subscriber subscriber, 
					 EventFilter eventFilter, 
					 int oldPriority, 
					 int newPriority)
       throws SubscriptionNotFoundException, RemoteException;

  public Subscription getFirstSubscription(OdieEvent odieEvent) 
       throws SubscriptionNotFoundException, RemoteException;

  public Subscription getNextSubscription(OdieEvent odieEvent, Subscription previousSubscription) 
       throws SubscriptionNotFoundException, RemoteException;
}//end interface SubscriptionManager

