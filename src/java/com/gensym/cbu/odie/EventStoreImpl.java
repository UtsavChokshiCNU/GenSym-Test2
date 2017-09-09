package com.gensym.cbu.odie;

import java.util.Vector;
import java.util.Enumeration;
import java.rmi.RemoteException;
import java.io.Serializable;
import com.gensym.denali.common.DenaliRemoteObject;
import java.util.Hashtable;
import java.util.Date;

class EventStoreImpl implements Serializable, EventStore
{

  Vector eventHistory;

  public EventStoreImpl ()
  {
    eventHistory = new Vector();
  }//end DefaultEventManager constructor

  
  @Override
  public OdieEvent createEvent(String eventType, 
			  String targetId, 
			  String senderId,
			  String messageText, 
			  String additionalText,
			  Date publicationDate,
			  String[] passport,
			  Hashtable additionalData) throws RemoteException
  {
    OdieEvent odieEvent = new OdieEventImpl(eventType, 
					    targetId, 
					    senderId,
					    messageText,
					    additionalText,
					    publicationDate,
					    passport,
					    additionalData);
    eventHistory.add(odieEvent);
    return odieEvent;
  }//end createEvent

  //  public void storeEvent(OdieEvent odieEvent) throws EventAlreadyInHistory
  //{
  //  if (eventHistory.contains(odieEvent))
  //	throw new EventAlreadyInHistory("odie Event (" + odieEvent + ") is already stored");
  //  
  //  eventHistory.add(odieEvent);
  //}//end storeEvent

  @Override
  public void deleteEvent(OdieEvent odieEvent) 
       throws EventNotInHistoryException, RemoteException
  {
    if (!eventHistory.contains(odieEvent)) 
	throw new EventNotInHistoryException ("The event (" + odieEvent + ") was not found in history");

    eventHistory.remove(odieEvent);
  }//end deleteEvent

  @Override
  public void deleteEvents(EventFilter eventFilter) throws RemoteException
  {
    OdieEvent[] matchingEvents = eventQuery(eventFilter);
    for(int cnt = 0; cnt < matchingEvents.length; cnt++)
      {
	eventHistory.remove(matchingEvents[cnt]);
      }
  }// end deleteEvents

  @Override
  public OdieEvent[] eventQuery(EventFilter eventFilter) throws RemoteException
  {
    Vector matchingEvents = new Vector();
    OdieEvent currentEvent;
   
    for(Enumeration e = eventHistory.elements(); e.hasMoreElements(); )
      {
	currentEvent = (OdieEvent)e.nextElement();
	if(eventFilter.eventPassesFilter(currentEvent))
	  matchingEvents.add(currentEvent);
      }
    return (OdieEvent[])(matchingEvents.toArray());
  } //end eventQuery

  @Override
  public int countQuery(EventFilter eventFilter) throws RemoteException
  {    
    int eventCount = 0;
    OdieEvent currentEvent;
   
    for(Enumeration e = eventHistory.elements(); e.hasMoreElements(); )
      {
	currentEvent = (OdieEvent)e.nextElement();
	if(eventFilter.eventPassesFilter(currentEvent))
	  eventCount++;
      }
    return eventCount;
  }//end countQuery

  @Override
  public void setAdditionalAttributeValue (OdieEvent odieEvent,
					   String attributeName, 
					   Serializable attributeValue, 
					   boolean overwrite) 
       throws AttributeAlreadyExistsException, RemoteException
  {
    ((OdieEventStore)odieEvent).setAdditionalAttributeValue(attributeName, attributeValue, overwrite);
  }//end setAdditionalAttributeValue
  
  @Override
  public void addPassportStamp (OdieEvent odieEvent, String passportStamp) 
       throws StampAlreadyInPassportException, RemoteException
  { 
    ((OdieEventStore)odieEvent).addPassportStamp(passportStamp);
  }//end addPassportStamp
}//end class DefaultEventManager
    


