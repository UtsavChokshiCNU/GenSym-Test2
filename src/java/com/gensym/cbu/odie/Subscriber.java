package com.gensym.cbu.odie;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Subscriber extends Remote {
  /** The manager calls notify when an event passing the subscriber's filter is published.
   * @param odieEvent the published event.
   * @param manager the manager publishing the event.
   * @return if the next subscriber should be notified, return true.  
   * Return false to stop further notifications
   */
  public boolean notify(OdieEvent odieEvent) throws RemoteException;

  public void addOslConnectionListener(OslConnectionListener listener) throws RemoteException;

  public void removeOslConnectionListener(OslConnectionListener listener) throws RemoteException;
}
