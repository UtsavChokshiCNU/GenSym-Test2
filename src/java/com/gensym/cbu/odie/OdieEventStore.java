package com.gensym.cbu.odie;

import java.rmi.RemoteException;
import java.rmi.Remote;
import java.io.Serializable;

interface OdieEventStore extends Remote 
{
  public void addPassportStamp(String stamp) throws StampAlreadyInPassportException, RemoteException;
  
  public void setAdditionalAttributeValue (String attributeName, 
					   Serializable attributeValue, 
					   boolean overwrite) 
       throws AttributeAlreadyExistsException, RemoteException;

  public boolean getDataChanged() throws RemoteException;

  public void clearDataChanged() throws RemoteException;
}



