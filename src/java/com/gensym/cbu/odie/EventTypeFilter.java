package com.gensym.cbu.odie;

import java.util.Vector;
import com.gensym.denali.common.DenaliRemoteObject;
import java.rmi.RemoteException;

class EventTypeFilter extends DenaliRemoteObject implements EventFilter
{

  public EventTypeFilter() throws RemoteException
  {
    super();
  }

  @Override
  public boolean eventPassesFilter(OdieEvent odieEvent) throws RemoteException
  {
    boolean filterPassed = false;

    if (odieEvent.getEventType() == "Interface Down")
      {
	filterPassed = true;
      }
    return filterPassed;
  }

  @Override
  public int numberOfEventsPassingFilter(OdieEvent[] candidateEvents) throws RemoteException
  {
    int numberPassingFilter = 0;

    for( int cnt = 0; cnt < candidateEvents.length; cnt++)
      {
	if (eventPassesFilter(candidateEvents[cnt]) == true) numberPassingFilter++;
      }

    return numberPassingFilter;
  }
    

  @Override
  public OdieEvent[] eventsPassingFilter(OdieEvent[] candidateEvents) throws RemoteException
  {
    int numberPassingFilter = 0;
    Vector passingEvents = new Vector();

    for(int cnt = 0; cnt < candidateEvents.length; cnt++)
      {
	if (eventPassesFilter(candidateEvents[cnt]) == true) 
	  {
	    passingEvents.add((OdieEvent)candidateEvents[cnt]);
	  }
      }

    return (OdieEvent[])passingEvents.toArray();
  }
}
    
