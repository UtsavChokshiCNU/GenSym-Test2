package com.gensym.cbu.odie;

import java.io.Serializable;
import com.gensym.denali.common.DenaliRemoteObject;
import java.rmi.RemoteException;

class SubscriptionImpl extends DenaliRemoteObject implements Serializable, Subscription 
{
  EventFilter eventFilter;
  Subscriber subscriber;
  int priority;
	
  public SubscriptionImpl(Subscriber subscriber, EventFilter eventFilter, int priority) throws RemoteException
  {
    this.eventFilter = eventFilter;
    this.subscriber = subscriber;
    this.priority = priority;
  }//end Subscription constructor
      
  @Override
  public Subscriber getSubscriber() throws RemoteException
  {
    return subscriber;
  }
  
  @Override
  public EventFilter getEventFilter() throws RemoteException
  {
    return eventFilter;
  }
  
  @Override
  public int getPriority() throws RemoteException
  {
    return priority;
  }
  
  @Override
  public void setPriority(int priority) throws RemoteException
  {
    this.priority = priority;
  }

}//end class Subscription




