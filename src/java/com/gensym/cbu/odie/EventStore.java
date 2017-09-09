package com.gensym.cbu.odie;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.util.Hashtable;
import java.util.Date;

interface EventStore
{
  public OdieEvent createEvent(String eventType, 
			  String targetId, 
			  String senderId,
			  String messageText, 
			  String additionalText,
			  Date publicationDate,
			  String[] passport,
			  Hashtable additionalData) throws RemoteException;

  //  public void storeEvent(OdieEvent odieEvent) throws EventAlreadyInHistory;
  // -replaced by createEvent?
  
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
}



