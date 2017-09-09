package com.gensym.cbu.odie;

import java.util.Date;
import java.util.Enumeration;
import java.rmi.RemoteException;
import java.rmi.Remote;
import java.io.Serializable;

public interface OdieEvent extends Remote
{
  public Manager getManager() throws RemoteException;

  public String getTargetId() throws RemoteException;

  public String getSenderId() throws RemoteException;

  public String getEventType() throws RemoteException;

  public String getMessageText() throws RemoteException;

  public String getAdditionalText() throws RemoteException;

  public Date getPublicationDate() throws RemoteException;

  public Object getAdditionalAttributeValue(String attributeName) 
       throws AttributeNotFoundException, RemoteException;

  public Enumeration getPassportStamps() throws RemoteException;
}



