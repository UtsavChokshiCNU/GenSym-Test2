package com.gensym.cbu.odie;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Subscription extends Remote
{
  public Subscriber getSubscriber() throws RemoteException;
  
  public EventFilter getEventFilter() throws RemoteException;
  
  public int getPriority() throws RemoteException;
  
  public void setPriority(int newPriority) throws RemoteException;
}
