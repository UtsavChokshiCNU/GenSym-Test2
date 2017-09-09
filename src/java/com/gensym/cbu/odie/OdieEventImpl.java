package com.gensym.cbu.odie;

import java.util.Date;
import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;
import com.gensym.denali.common.DenaliRemoteObject;
import java.io.Serializable;
import java.rmi.RemoteException;

class OdieEventImpl extends DenaliRemoteObject implements Serializable, OdieEvent, OdieEventStore
{
  Manager manager;
  String targetId;
  String senderId;
  String eventType;
  String messageText;
  String additionalText;
  Date publicationDate;
  Vector passport = new Vector();
  Hashtable additionalData= new Hashtable();
  boolean dataChanged = false;

  public OdieEventImpl(Manager manager, 
		       String eventType, 
		       String targetId, 
		       String senderId,
		       String messageText, 
		       String additionalText,
		       Date publicationDate,
		       String[] passport,
		       Hashtable additionalData) throws RemoteException
  {
    this.manager = manager;
    this.eventType = eventType;
    this.targetId = targetId;
    this.senderId = senderId;
    this.messageText = messageText;
    this.additionalText = additionalText;
    if (publicationDate != null)
      {
	this.publicationDate = publicationDate;
      }
    else
      {
	this.publicationDate = new Date();
      }
    this.passport = new Vector();
    if (passport != null) 
      {
	for (int i = 0; i < passport.length; i++)
	  {
	    this.passport.add(passport[i]);
	  }
      }
    if (additionalData == null)
      {
	this.additionalData = new Hashtable();
      }
    else
      {
	this.additionalData = (Hashtable)additionalData.clone();
      }
    this.dataChanged = true;
  }
 

  //OdieEvent interface
  @Override
  public Manager getManager() throws RemoteException
  {
    return manager;
  }

  @Override
  public String getTargetId() throws RemoteException
  { 
    return targetId; 
  }

  @Override
  public String getSenderId() throws RemoteException
  { 
    return senderId; 
  }

  @Override
  public String getEventType() throws RemoteException 
  { 
    return eventType; 
  }

  @Override
  public String getMessageText () throws RemoteException
  { 
    return messageText; 
  }

  @Override
  public String getAdditionalText () throws RemoteException 
  { 
    return additionalText; 
  }

  @Override
  public Date getPublicationDate () throws RemoteException 
  { 
    return (Date)publicationDate.clone();
  }

  @Override
  public Object getAdditionalAttributeValue(String attributeName) 
       throws AttributeNotFoundException, RemoteException
  { 
    if (additionalData.containsKey(attributeName) == false)
      {
	throw (new AttributeNotFoundException("No attribute named " + attributeName + " is defined in event " + this));
      }
    return additionalData.get(attributeName); 
  }

  @Override
  public Enumeration getPassportStamps()  throws RemoteException
  {
    return passport.elements();
  }

  @Override
  public void addPassportStamp(String stamp) 
       throws StampAlreadyInPassportException, RemoteException
  {
    if (passport.contains(stamp) == true) 
      {
	throw new StampAlreadyInPassportException("Odie Event )" + this + 
						  ") already has stamp (" + stamp +
						  ") in its passport");
      }
    passport.add(stamp);
    dataChanged = true;
  }

  @Override
  public void setAdditionalAttributeValue (String attributeName, 
					   Serializable attributeValue, 
					   boolean overwrite) 
       throws AttributeAlreadyExistsException, RemoteException
  { 
    if (additionalData.containsKey(attributeName) == true)
      {
	if (overwrite == false)
	  {
	    throw (new AttributeAlreadyExistsException ("The attribute " + attributeName + " already exists."));
	  }
	else
	  {
	    additionalData.remove(attributeName);
	  }
      }
    additionalData.put(attributeName, attributeValue);
  }//end setEventAdditionalAttributeValue

  @Override
  public boolean getDataChanged() throws RemoteException
  {
    return dataChanged;
  }//end getDataChanged

  @Override
  public void clearDataChanged() throws RemoteException
  {
    dataChanged = false;
  }//end clearDataChanged

  //end OdieEvent interface

  public String toString()
  {
    StringBuffer s = new StringBuffer("eventType: " + eventType + "\n");
    s.append("targetId: " + targetId + "\n");
    s.append("senderId: " + senderId + "\n");
    s.append("messageText: " + messageText + "\n");
    s.append("additionalText: " + additionalText + "\n");
    s.append("publicationDate: " + publicationDate.toString() + "\n");
    s.append("passport stamps: ");
    for (Enumeration e = passport.elements(); e.hasMoreElements();)
      {
	s.append((String)e.nextElement());
	if (e.hasMoreElements() == true) 
	  {
	    s.append(", ");
	  }
      }
    s.append("\n");
    s.append("additionalData: ");
    String key;
    for(Enumeration keys = additionalData.keys(); keys.hasMoreElements();)
      {
	key = (String)keys.nextElement();
	s.append(key + ", " + additionalData.get(key));
	if (keys.hasMoreElements() == true) 
	  {
	    s.append("\n");
	  }
      }
    return s.toString();
  }
}




