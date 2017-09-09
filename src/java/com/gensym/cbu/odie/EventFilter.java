package com.gensym.cbu.odie;

import java.io.Serializable;
import java.rmi.RemoteException;

public interface EventFilter extends Serializable
{
  /** eventPassesFilter compares it's criteria to the provided event.
   * @return Returns true if the event passes the filter, false otherwise.
   */
  public boolean eventPassesFilter(OdieEvent odieEvent) throws RemoteException;

  /** Returns the number of events in the provided OdieEvent Array passing the filter
   */
  public int numberOfEventsPassingFilter(OdieEvent[] odieEvents) throws RemoteException;

  /** Returns an array of the OdieEvents that pass the filter.
   */
  public OdieEvent[] eventsPassingFilter(OdieEvent[] candidateEvents) throws RemoteException;
}
