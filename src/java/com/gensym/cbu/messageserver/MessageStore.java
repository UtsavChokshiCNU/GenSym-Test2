package com.gensym.cbu.messageserver;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Date;

interface MessageStore 
{
  void setPriority(int newPriority);

  void acknowledge(String acknowledger, Date acknowledgementDate) throws MessageAlreadyAcknowledgedException;
}
