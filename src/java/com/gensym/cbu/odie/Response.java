package com.gensym.cbu.odie;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Response extends Remote
{
  public void respond(OdieEvent odieEvent) throws RemoteException;
}
