package com.gensym.cbu.odie;

import java.util.Date;
import java.util.Hashtable;
import java.util.Enumeration;
import java.rmi.RemoteException;
import java.rmi.Remote;
import java.io.Serializable;

public interface Manager extends Remote
{
  public String getName() throws RemoteException;

  public void setName(String name) throws RemoteException;

  /** Publishes a new event with the provided parameters.
   * @param eventType the name of the event type to publish.
   * @param targetId a unique identification of the target
   * @param senderId a unique identificaiton of the sender of the event
   * @param truthValue a measure of the certainty of the event on a scale from 0.0 to 1.0.  Use 1.0 by default.
   * @param messageText the main message text to be shown to an operator.  The message text is included here because often
   * the sender of the event has the neccessary information, expertise, or context to construct a meaningful message.
   * Send null or a null string (i.e. "") for no message.
   * @pararm additionalText Any secondary or supporting information about the event that should be available to an operator.
   * send null or a null string (i.e. "") for no additional text.
   * @param startTime The date the event started.  null sets the starting time to the current time.
   * @param stopDate The date the event stopped.  This field can be null.
   * @param passportStamps An array of initial passport stamps for the event.  This is primarily used in a mom or agent
   * scenario.
   * @param additionalData Any extra data values to be stored.  The keys of the hashtable must be Strings.
   * @return if the next subscriber should be notified, return true.  
   * Return false to stop further notifications
   */
  public OdieEvent publishNewEvent(String eventType, 
				   String targetId, 
				   String senderId,
				   String messageText, 
				   String additionalText, 
				   Date publicationTime,
				   String[] passportStamps, 
				   Hashtable additionalData) 
       throws RemoteException, EventTypeDoesNotExistException;

       //EventTypeManager Interfaces
  public String getEventTypeDescription (String eventType) 
       throws EventTypeDoesNotExistException, RemoteException;
       
  public void setEventTypeDescription (String eventType, 
				       String description, 
				       boolean overwrite) 
       throws EventTypeAlreadyDefinedException, RemoteException;

  public void removeEventTypeDescription (String eventType) 
       throws EventTypeDoesNotExistException, RemoteException;

  public Enumeration getEventTypes() throws RemoteException;

  public boolean isEventTypeDefined(String eventType) throws RemoteException;
       //end EventTypeManager Interfaces


       //SubscriptionManager Interfaces
  public Subscription addSubscription(Subscriber subscriber, EventFilter eventFilter, int priority) 
       throws SubscriptionAlreadyExistsException, RemoteException;

  public void removeSubscription(Subscriber subscriber, EventFilter eventFilter, int priority) 
       throws SubscriptionNotFoundException, RemoteException;

  public void removeSubscription(Subscription subscription) 
       throws SubscriptionNotFoundException, RemoteException;

  public void changeSubscriptionPriority(Subscriber subscriber, EventFilter eventFilter, int oldPriority, int newPriority)
       throws SubscriptionNotFoundException, RemoteException;
       //end SubscriptionManager Interfaces


       //EventStore Interfaces
  public void deleteEvent(OdieEvent odieEvent) 
       throws EventNotInHistoryException, RemoteException;

  public void deleteEvents(EventFilter eventFilter) throws RemoteException;

  public OdieEvent[] eventQuery(EventFilter eventFilter) throws RemoteException;

  public int countQuery(EventFilter eventFilter) throws RemoteException;

  public void addPassportStamp (OdieEvent odieEvent, String passportStamp) 
       throws StampAlreadyInPassportException, RemoteException;

  /** Stores the object (attributeValue) and associates it with attributeName
   * @param odieEvent the OdieEvent to set the attribute in
   * @param attributeName the association name to store the object with
   * @param attributeValue the object to be stored
   * @param overwrite true if the new value should overwrite the existing value, false if the value should only be
   * if it has not already been defined
   * @throws AttributeAlreadyDefined is thrown if overwrite is false and an object is already stored with
   * key attributeName
   */
  public void setAdditionalAttributeValue(OdieEvent odieEvent,
					  String attributeName, 
					  Serializable attributeValue, 
					  boolean overwrite) 
       throws AttributeAlreadyExistsException, RemoteException;
       //end EventStore Interfaces

  //GroupManager Interface

  public String getGroupDescription (String groupName) throws GroupDoesNotExistException;

  public void setGroupDescription (String groupName, String description) 
       throws GroupDoesNotExistException;

  public Enumeration getGroupNames();

  public boolean isGroupDefined(String groupName);

  //end GroupManager Interface
}




