package com.gensym.cbu.messageserver;

import java.beans.PropertyChangeSupport;
import java.beans.PropertyChangeListener;
import java.util.Vector;
import java.util.Enumeration;
import java.io.Serializable;
import java.util.Date;

public class MessageImpl implements Serializable, Message, MessageStore
{
  Vector listeners = new Vector();
  String mainText;
  String additionalText;
  String eventType;
  int priority;
  String target;
  String sender;
  Date publicationDate;
  Date acknowledgementDate;
  String acknowledger;
  MessageServer messageServer;
  
  public MessageImpl(MessageServer messageServer,
		     String target, 
		     String sender,
		     String eventType,
		     String mainText, 
		     String additionalText, 
		     int priority)
  {
    this.messageServer = messageServer;
    this.target = target;
    this.sender = sender;
    this.eventType = eventType;
    this.mainText = mainText;
    this.additionalText = additionalText;
    this.priority = priority;
    this.publicationDate = new Date();
  }

  //Message Interface
  @Override
  public MessageServer getMessageServer()
  {
    return messageServer;
  }

  @Override
  public String getTargetId()
  {
    return target;
  }

  @Override
  public String getSenderId()
  {
    return sender;
  }

  @Override
  public String getEventType()
  {
    return eventType;
  }

  @Override
  public String getMainText()
  {
    return mainText;
  }

  @Override
  public String getAdditionalText()
  {
    return additionalText;
  }

  @Override
  public int getPriority()
  {
    return priority;
  }

  @Override
  public Date getPublicationDate()
  {
    return (Date)publicationDate.clone();
  }

  @Override
  public Date getAcknowledgementDate() throws MessageNotAcknowledgedException
  {
    if (acknowledgementDate == null) 
      throw new MessageNotAcknowledgedException("Message has not yet been acknowledged."); 
    return (Date)acknowledgementDate.clone();
  }

  @Override
  public String getAcknowledger() throws MessageNotAcknowledgedException
  {
    if (acknowledgementDate == null) 
      throw new MessageNotAcknowledgedException("Message has not yet been acknowledged."); 
    return acknowledger;
  }
  //end Message Interface

  //MessageStore Interface

  @Override
  public void setPriority(int newPriority)
  {
    this.priority = newPriority;;
  }

  @Override
  public void acknowledge(String acknowledger, Date acknowledgementDate) 
       throws MessageAlreadyAcknowledgedException
  {
    if (this.acknowledgementDate != null)
      throw new MessageAlreadyAcknowledgedException ("Message already acknowledged by " +
						     acknowledger + 
						     " on " + this.acknowledgementDate + ".");
    this.acknowledger = acknowledger;
    this.acknowledgementDate = acknowledgementDate;
  }
  //end MessageStore Interface
}
