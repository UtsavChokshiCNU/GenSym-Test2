 package com.gensym.cbu.odie;

import com.gensym.denali.common.DenaliRemoteObject;
import java.io.Serializable;
import java.rmi.RemoteException;
import java.util.Vector;
import java.util.Enumeration;

public class SubscriberImpl extends DenaliRemoteObject 
implements Serializable, Subscriber, EventFilter
{
  String name = "DefaultSubscriber";
  String eventType = "ODiE Event";
  String managerName = "Manager 1";;
  Vector listeners = new Vector();
  
  public SubscriberImpl() throws RemoteException
  {
  }

  //Subscriber Interface
  @Override
  public synchronized boolean notify(OdieEvent odieEvent) 
       throws RemoteException
  {
    //    System.out.println(name + ": I have been notified of (" + odieEvent.toString() + 
    //	       ")\nby " + manager.getName());
    
    for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
      {
	//	System.out.println("notifying listener");
	((OslConnectionListener)e.nextElement())
	  .passEvent(new OslConnectionEvent(this, odieEvent, odieEvent.getManager()));
      }
    return false;
  }

  @Override
  public synchronized void addOslConnectionListener(OslConnectionListener listener) 
       throws RemoteException
  {
    listeners.addElement(listener);
  }

  @Override
  public synchronized void removeOslConnectionListener(OslConnectionListener listener) 
       throws RemoteException
  {
    listeners.removeElement(listener);
  }
  //end Subscriber Interface

  public String getManagerName()
  {
    return managerName;
  }

  public void setManagerName(String managerName) throws RemoteException, SubscriptionAlreadyExistsException
  {
    this.managerName = managerName;

    Manager manager = (Manager)(Utilities.getUniqueGraphElementWithinModule(managerName, this).getBean());
    if (manager == null)
      System.out.println("Manager lookup failed in defineEventTypeTest");
    else
      {
	manager.addSubscription((Subscriber)this, 
				(EventFilter)this,
				10);
	try {
	  manager.setEventTypeDescription(eventType, "", false);	
	}
	  catch (EventTypeAlreadyDefinedException e) 
	    {
	      // the point here is to make sure the event type is defined
	      // if it's already defined, all the better
	      // in a future version, perhaps we won't want to automatically define the eventType
	      // for current demos, I want the convenience
	    }
      }
  }

  public void setEventType (String eventType) throws RemoteException
  {
    this.eventType = eventType;
    Manager manager = (Manager)(Utilities.getUniqueGraphElementWithinModule(managerName, this).getBean());
    if (manager == null)
      System.out.println("!!!Manager lookup failed in defaultSubscriber Subscription");
    else
      {
	try {
	  manager.setEventTypeDescription(eventType, "", false);
	}
	catch (EventTypeAlreadyDefinedException e) 
	  {
	    // the point here is to make sure the event type is defined
	    // if it's already defined, all the better
	    // in a future version, perhaps we won't want to automatically define the eventType
	    // for current demos, I want the convenience
	  }
      }
  }

  public String getEventType () 
  {
    return this.eventType;
  }

  public String getName () 
  {
    return name;
  };

  public void setName (String name) 
  {
    this.name = name;
  }
  //eventFilter interface
  @Override
  public boolean eventPassesFilter(OdieEvent odieEvent) 
       throws RemoteException
  {
    //    System.out.println ("***" + name + ": testing filter. Does " + 
    //      odieEvent.getEventType() + " = " + eventType + " ?");
    if (odieEvent.getEventType() == eventType)
      return true;
    else
      return false;
  }
  
  @Override
  public int numberOfEventsPassingFilter(OdieEvent[] odieEvents) 
       throws RemoteException
  {
    return odieEvents.length;
  }
  
  @Override
  public OdieEvent[] eventsPassingFilter(OdieEvent[] candidateEvents) 
       throws RemoteException
  {
    return candidateEvents;
  }
  //end EventFilter Interface
}









