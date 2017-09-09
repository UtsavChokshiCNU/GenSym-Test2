package com.gensym.cbu.odie;

import java.util.Vector;
import java.util.Date;
import java.rmi.RemoteException;

public class EventFilterImpl implements EventFilter
{
  Vector targetIds;  
  Vector senderIds;
  Vector eventTypes;
  Date earliestPublicationDate;
  Date latestPublicationDate;

  public EventFilterImpl(String[] targetIds, 
			 String[] senderIds, 
			 String[] eventTypes, 
			 Date earliestPublicationDate, 
			 Date latestPublicationDate)
  {
    if (targetIds != null)
      {
	this.targetIds = new Vector();
	for (int i = 0; i < targetIds.length; i++)
	  this.targetIds.add(targetIds[i]);
      }
    if (senderIds != null)
      {
	this.senderIds = new Vector();
	for (int i = 0; i < senderIds.length; i++)
	  this.senderIds.add(senderIds[i]);
      }
    if (eventTypes != null)
      {
	this.eventTypes = new Vector();
	for (int i = 0; i < eventTypes.length; i++)
	  this.eventTypes.add(eventTypes[i]);
      }

    if (earliestPublicationDate != null)
      this.earliestPublicationDate = earliestPublicationDate;
    if (latestPublicationDate != null)
      this.latestPublicationDate = latestPublicationDate;
  }
  
  @Override
  public boolean eventPassesFilter(OdieEvent odieEvent) throws RemoteException
  {
    if ((targetIds == null || targetIds.contains(odieEvent.getTargetId())) 
	&& (senderIds == null || senderIds.contains(odieEvent.getSenderId())) 
	&& (eventTypes == null || eventTypes.contains(odieEvent.getEventType())) 
	&& (earliestPublicationDate == null || earliestPublicationDate.before(odieEvent.getPublicationDate()))
	&& (latestPublicationDate == null || latestPublicationDate.after(odieEvent.getPublicationDate())))
      return true;
    else
      return false;
  }
  
  @Override
  public int numberOfEventsPassingFilter(OdieEvent[] odieEvents) throws RemoteException
  {
    int numberOfPassingEvents = 0;
    for (int i = 0; i < odieEvents.length; i++)
      {
	if (eventPassesFilter(odieEvents[i]))
	  numberOfPassingEvents++;
      }
    return numberOfPassingEvents;
  }
	  
  @Override
  public OdieEvent[] eventsPassingFilter(OdieEvent[] candidateEvents) throws RemoteException
  {	
    Vector passingEvents = new Vector();
    for (int i = 0; i < candidateEvents.length; i++)
      {
	if (eventPassesFilter(candidateEvents[i]))
	  passingEvents.add(candidateEvents[i]);
      }
    return (OdieEvent[])passingEvents.toArray();
  }
}
