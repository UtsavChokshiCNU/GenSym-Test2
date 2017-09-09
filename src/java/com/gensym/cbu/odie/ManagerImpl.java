package com.gensym.cbu.odie;

import java.beans.PropertyChangeSupport;
import java.beans.PropertyChangeListener;
import java.util.Date;
import java.util.Enumeration;
import java.util.Hashtable;
import com.gensym.denali.common.DenaliRemoteObject;
import java.rmi.RemoteException;
import java.io.Serializable;
import com.gensym.denali.model.GraphElement;
import com.gensym.denali.model.ServerImpl;

public class ManagerImpl extends DenaliRemoteObject implements Serializable, Manager
{
  String name = "ODiE Manager";
  PropertyChangeSupport propertyChangeSupport;
  EventTypeManager eventTypeManager;
  SubscriptionManager subscriptionManager;
  EventStore eventStore = new EventStoreImpl();
  GroupManager groupManager;

  public ManagerImpl() throws RemoteException
  {
    super();
    propertyChangeSupport  = new PropertyChangeSupport(this);
    eventTypeManager = new EventTypeManagerImpl();
    subscriptionManager = new SubscriptionManagerImpl();
    eventStore = new EventStoreImpl();
    groupManager = new GroupManagerImpl();
  }

  public ManagerImpl(String name) throws RemoteException
  {
    this();
    this.name = name;
  }

  @Override
  public String getName () throws  RemoteException
  { 
    return name; 
  }

  @Override
  public void setName (String name) throws  RemoteException
  { 
    String oldName = this.name;
    this.name = name;
    GraphElement[] elements = ServerImpl.getGraphElementsContaining(this);
    for(int i = 0; i< elements.length; i++)
      ((GraphElement)elements[i]).setName(name);
    propertyChangeSupport.firePropertyChange("name", oldName, name);
  }

  //Manager Interface

  /**Publishes a new event
    @param eventType the class of event to publish
    @param targetId the unique identifier of the target of the event
    @param senderId the unique identifer of the sender of the event
    @param messageText the main description of the event
    @param additionalText a secondary message or supporting text
    @return the dispatched event
    */
  @Override
  public OdieEvent publishNewEvent(String eventType, 
				   String targetId, 
				   String senderId, 
				   String messageText, 
				   String additionalText, 
				   Date publicationTime, 
				   String[] passportStamps, 
				   Hashtable additionalData) 
       throws RemoteException, EventTypeDoesNotExistException
  {
    System.out.println(name + " publishing event of type (" + eventType + ")");
    if (!eventTypeManager.isEventTypeDefined(eventType))
      throw new EventTypeDoesNotExistException ("Event Type (" + eventType + ") is not defined.");

    OdieEvent odieEvent = eventStore.createEvent(eventType, 
						 targetId, 
						 senderId,
						 messageText, 
						 additionalText,
						 publicationTime,
						 passportStamps,
						 additionalData);
    publishEvent(odieEvent);
    return odieEvent;
  }  //end publishNewEvent

  //EventTypeManager Interfaces
  @Override
  public String getEventTypeDescription (String eventType) 
       throws EventTypeDoesNotExistException, RemoteException
  {
    return eventTypeManager.getDescription(eventType);
  }//end getEventTypeDescription
       
  @Override
  public void setEventTypeDescription (String eventType, 
				       String description, 
				       boolean overwrite) 
       throws EventTypeAlreadyDefinedException, RemoteException
  {
    System.out.println("DefaultManager (" + name + ") setting event type description");
    eventTypeManager.setDescription(eventType, description, overwrite);
  }//end setEventTypeDescription

  @Override
  public void removeEventTypeDescription (String eventType) 
       throws EventTypeDoesNotExistException, RemoteException
  {
    eventTypeManager.removeDescription(eventType);
  }//end removeEventTypeDescription

  @Override
  public Enumeration getEventTypes() throws RemoteException
  {
    return eventTypeManager.getEventTypes();
  }//end getEventTypes();

  @Override
  public boolean isEventTypeDefined(String eventType) throws RemoteException
  {
    return eventTypeManager.isEventTypeDefined(eventType);
  }//end isEventTypeDefined
  //end EventTypeManager Interfaces


  //SubscriptionManager Interfaces
  @Override
  public Subscription addSubscription(Subscriber subscriber, EventFilter eventFilter, int priority) 
       throws SubscriptionAlreadyExistsException, RemoteException
  {
    return subscriptionManager.addSubscription(subscriber, eventFilter, priority);
  }//end addSubscription

  @Override
  public void removeSubscription(Subscriber subscriber, EventFilter eventFilter, int priority) 
       throws SubscriptionNotFoundException, RemoteException
  {
    subscriptionManager.removeSubscription(subscriber, eventFilter, priority);
  }//end removeSubscription

  @Override
  public void removeSubscription(Subscription subscription) 
       throws SubscriptionNotFoundException, RemoteException
  {
    subscriptionManager.removeSubscription(subscription);
  }//end removeSubscription

  @Override
  public void changeSubscriptionPriority(Subscriber subscriber, EventFilter eventFilter, int oldPriority, int newPriority)
       throws SubscriptionNotFoundException, RemoteException
  {
    subscriptionManager.changeSubscriptionPriority(subscriber, eventFilter, oldPriority, newPriority);
  }//end changeSubscriptionPriority
  //end SubscriptionManager Interfaces



       //EventStore Interfaces
  @Override
  public void deleteEvent(OdieEvent odieEvent) 
       throws EventNotInHistoryException, RemoteException
  {
    eventStore.deleteEvent(odieEvent);
  }//end deleteEvent

  @Override
  public void deleteEvents(EventFilter eventFilter) throws RemoteException
  {
    eventStore.deleteEvents(eventFilter);
  }

  @Override
  public OdieEvent[] eventQuery(EventFilter eventFilter) throws RemoteException
  {
    return eventStore.eventQuery(eventFilter);
  }//end eventQuery

  @Override
  public int countQuery(EventFilter eventFilter) throws RemoteException
  {
    return eventStore.countQuery(eventFilter);
  }//end countQuery

  @Override
  public void addPassportStamp (OdieEvent odieEvent, String passportStamp) 
       throws StampAlreadyInPassportException, RemoteException
  {
    eventStore.addPassportStamp(odieEvent, passportStamp);
    publishEvent(odieEvent);
  }//end addPassportStamp

  /** Stores the object (attributeValue) and associates it with attributeName
   * @param odieEvent the OdieEvent to set the attribute in
   * @param attributeName the association name to store the object with
   * @param attributeValue the object to be stored
   * @param overwrite true if the new value should overwrite the existing value, false if the value should only be
   * if it has not already been defined
   * @throws AttributeAlreadyDefined is thrown if overwrite is false and an object is already stored with
   * key attributeName
   */
  @Override
  public void setAdditionalAttributeValue(OdieEvent odieEvent,
					  String attributeName, 
					  Serializable attributeValue, 
					  boolean overwrite) 
       throws AttributeAlreadyExistsException, RemoteException
  {
    eventStore.setAdditionalAttributeValue(odieEvent, attributeName, attributeValue, overwrite);
    publishEvent(odieEvent);
  }//end setAdditionalAttributeValue
       //end EventStore Interfaces



  // end Manager Interface


  //GroupManager Interface
  @Override
  public String getGroupDescription (String groupName) throws GroupDoesNotExistException
  {
    return groupManager.getDescription (groupName);
  }

  @Override
  public void setGroupDescription (String groupName, String description) 
       throws GroupDoesNotExistException
  {
    groupManager.setDescription(groupName, description);
  }

  @Override
  public Enumeration getGroupNames()
  {
    return groupManager.getGroupNames();
  }

  @Override
  public boolean isGroupDefined(String groupName)
  {
    return groupManager.isGroupDefined(groupName);
  }
  //end GroupManager Interface

  void publishEvent (OdieEvent odieEvent) throws RemoteException
  {
    Subscription subscription;
    boolean eventConsumed = false;

    // do nothing if the dataChanged bit hasn't been set?
    // should this throw a runtime error if the data has not been changed?
    // should I even bother with this or should every change be an auto-republish?
    // a negative to auto-republish is that a process could be trying to add several 
    // values or passport stamps that collectively make sense but individually don't
    if( ((OdieEventStore)odieEvent).getDataChanged())
      {
	try
	  {
	    subscription = subscriptionManager.getFirstSubscription(odieEvent);
	    eventConsumed = ((Subscriber)subscription.getSubscriber()).notify(odieEvent);

	    while(!eventConsumed)
	      {
		try
		  {
		    subscription = subscriptionManager.getNextSubscription(odieEvent, subscription);
		    eventConsumed = ((Subscriber)subscription.getSubscriber()).notify(odieEvent);
		  }
		catch  (SubscriptionNotFoundException e)
		  {
		    //no more subscribers
		    break;
		  }
	      }
	  }
	catch (SubscriptionNotFoundException e)
	  {
	    //no subscribers at all
	  }
	((OdieEventStore)odieEvent).clearDataChanged();
      }
  }//end publishEventImpl

  public PropertyChangeSupport getSupport()
  {
    return propertyChangeSupport;
  }

  public void setSupport(PropertyChangeSupport support)
  {
    propertyChangeSupport = support;
  }

  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
    propertyChangeSupport.addPropertyChangeListener(listener);
  }

  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
    propertyChangeSupport.removePropertyChangeListener(listener);
  }
}
