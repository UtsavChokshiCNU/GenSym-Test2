package com.gensym.cbu.odie;

import java.util.Vector;
import java.util.Enumeration;
import java.io.Serializable;
import com.gensym.core.util.QuickSorter;
import java.rmi.RemoteException;

class SubscriptionManagerImpl implements Serializable, SubscriptionManager
{
  Vector subscriptions = new Vector();

  public SubscriptionManagerImpl() throws RemoteException
  {
  }//end DefaultSubscriptionManager constructor

  @Override
  public Subscription addSubscription(Subscriber subscriber, 
			      EventFilter eventFilter, 
			      int priority) 
       throws SubscriptionAlreadyExistsException, RemoteException
  {
    try
      {
	Subscription subscription = findSubscriptionAtAnyPriority(subscriber, eventFilter);
	throw new SubscriptionAlreadyExistsException ("A subscription for subscriber (" + subscriber +
						      ") and eventFilter (" + eventFilter +
						      "already exists at priority " + subscription.getPriority());
      }
    catch (SubscriptionNotFoundException e)
      {
	Subscription subscription = new SubscriptionImpl(subscriber, eventFilter, priority);
	subscriptions.add(subscription);
	sortSubscriptions();
	return subscription;
      }
  }//end addSubscription

  @Override
  public void removeSubscription(Subscriber subscriber, 
				 EventFilter eventFilter, 
				 int priority)
       throws SubscriptionNotFoundException, RemoteException
  {

    Subscription subscription = findSubscription(subscriber, eventFilter, priority);
    subscriptions.remove(subscription);
    //no need to resort unless Vectors reorder things when something is removed
  }//end removeSubscription

  @Override
  public void removeSubscription(Subscription subscription) 
       throws SubscriptionNotFoundException, RemoteException
  {
    subscriptions.remove(subscription);
    //no need to resort unless Vectors reorder things when something is removed
  }

  @Override
  public void changeSubscriptionPriority(Subscriber subscriber, 
					 EventFilter eventFilter, 
					 int oldPriority, 
					 int newPriority)
       throws SubscriptionNotFoundException, RemoteException
  {
    Subscription subscription = findSubscription(subscriber, eventFilter, oldPriority);
    subscription.setPriority(newPriority);
    sortSubscriptions();
  }

  @Override
  public Subscription getFirstSubscription(OdieEvent odieEvent) 
       throws SubscriptionNotFoundException, RemoteException
  {
    Subscription subscription;
    EventFilter eventFilter;
    
    for(Enumeration e = subscriptions.elements(); e.hasMoreElements();)
      {
	subscription = (Subscription)e.nextElement();
	eventFilter = subscription.getEventFilter();

	if (eventFilter.eventPassesFilter(odieEvent))
	    return subscription;
      }
    throw new SubscriptionNotFoundException ("Odie Event (" + odieEvent + ") passes no subscriptions");
  }//end getFirstSubscription

  @Override
  public Subscription getNextSubscription(OdieEvent odieEvent, 
					  Subscription previousSubscription) 
       throws SubscriptionNotFoundException, RemoteException
  {
    Subscription subscription;
    EventFilter eventFilter;
    Enumeration e;
    boolean previousSubscriptionFound = false;
    
    //find previousSubscription
    for(e = subscriptions.elements(); e.hasMoreElements() && previousSubscriptionFound == false;)
      {
	subscription = (Subscription)e.nextElement();
	if (subscription == previousSubscription)
	    previousSubscriptionFound = true;
      }
    
    //find nextPassingSubscription
    for (;e.hasMoreElements();)
      {
	subscription = (Subscription)e.nextElement();
	eventFilter = subscription.getEventFilter();

	if (eventFilter.eventPassesFilter(odieEvent) == true)
	  return subscription;
      }
    throw new SubscriptionNotFoundException ("Odie Event (" + odieEvent + ") passes more subscriptions.");
  }//end getNextSubscriber

  Subscription findSubscription(Subscriber subscriber, 
				EventFilter eventFilter, 
				int priority)
    throws SubscriptionNotFoundException, RemoteException
    {
      Enumeration e;
      Subscription subscription;
    
      for(e = subscriptions.elements(); e.hasMoreElements(); )
	{
	  subscription = (Subscription)e.nextElement();
	  if (subscription.getSubscriber() == subscriber 
	      && subscription.getEventFilter() == eventFilter
	      && subscription.getPriority() == priority)
	    return subscription;
	}
      throw new SubscriptionNotFoundException ("No Subcription Found for subscriber (" + subscriber + 
					       "), eventFilter (" + eventFilter +
					       "at priority " + priority);
    }//end findSubscription


    Subscription findSubscriptionAtAnyPriority(Subscriber subscriber, 
				EventFilter eventFilter)
    throws SubscriptionNotFoundException, RemoteException
    {
      Enumeration e;
      Subscription subscription;
    
      for(e = subscriptions.elements(); e.hasMoreElements(); )
	{
	  subscription = (Subscription)e.nextElement();
	  if (subscription.getSubscriber() == subscriber 
	      && subscription.getEventFilter() == eventFilter)
	    return subscription;
	}
    throw new SubscriptionNotFoundException ("No Subcription Found for subscriber (" + subscriber + 
					     "), eventFilter (" + eventFilter);
    }//end findSubscriptionAtAnyPriority

  void sortSubscriptions() throws RemoteException
  {
    QuickSorter sorter = new QuickSorter()
      {
	@Override
	public boolean lessThan(Object sub1, Object sub2)
	  {
	    try 
	      {
		return ((Subscription)sub1).getPriority() < ((Subscription)sub2).getPriority();
	      }
	    catch (RemoteException e)
	      {
		throw new Error(e.toString());
	      }
	  }
      };
    sorter.quickSortInPlace(subscriptions);
  }//end sortSubscriptions
}//end class DefaultSubscriptionManager



