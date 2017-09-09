package com.gensym.cbu.messageserver;

import java.beans.PropertyChangeSupport;
import java.beans.PropertyChangeListener;
import java.util.Vector;
import java.util.Enumeration;
import java.io.Serializable;
import java.util.Date;

public class MessageServerImpl implements Serializable, MessageServer
{
  PropertyChangeSupport support = new PropertyChangeSupport(this);
  String name = "";
  Vector messageServerListeners = new Vector();
  Vector messages = new Vector();
  
  public MessageServerImpl()
  {
    //    support = new PropertyChangeSupport(this);
  }

  public void setName(String name)
  {
    String oldName = this.name;
    this.name = name;
    if (support != null) 
      support.firePropertyChange("name", oldName, name);
  }

  public PropertyChangeSupport getSupport()
  {
    return support;
  }

  public void setSupport(PropertyChangeSupport support)
  {
    this.support = support;
  }

  //MessageServer interface
  @Override
  public String getName()
  {
    return name;
  }

  @Override
  public Enumeration getAllMessages()
  {
    return messages.elements();
  }

  @Override
  public Message addMessage(String target,
			    String sender,
			    String category,
			    String mainText,
			    String additionalText,
			    int priority)
  {
    Message newMessage = (Message)new MessageImpl ((MessageServer)this, 
						target, 
						sender, 
						category, 
						mainText, 
						additionalText, 
						priority);
    messages.add(newMessage);
    for (Enumeration e = messageServerListeners.elements(); e.hasMoreElements();)
      ((MessageServerListener)e.nextElement()).messageAdded(newMessage);
    return newMessage;
  }
  
  @Override
  public void deleteMessage(Message messageToDelete)
  {
    messages.remove(messageToDelete);
    for (Enumeration e = messageServerListeners.elements(); e.hasMoreElements();)
      ((MessageServerListener)e.nextElement()).messageDeleted(messageToDelete);
  }

  @Override
  public void deleteMessages(Message[] messagesToDelete)
  {
    for (int i = 0; i < messagesToDelete.length; i++)
      {
	messages.remove(messagesToDelete[i]);
      }
    for (Enumeration e = messageServerListeners.elements(); e.hasMoreElements();)
      ((MessageServerListener)e.nextElement()).messagesDeleted(messagesToDelete);
  }

  @Override
  public void changeMessagePriority(Message message, int newPriority)
  {
    ((MessageStore)message).setPriority(newPriority);
    for (Enumeration e = messageServerListeners.elements(); e.hasMoreElements();)
      ((MessageServerListener)e.nextElement()).messagePriorityChanged(message, newPriority);
  }

  @Override
  public void acknowledgeMessage(Message messageToAcknowledge, String acknowledger, Date acknowledgementDate) 
       throws MessageAlreadyAcknowledgedException
  {    
    if (acknowledger == null)
      acknowledger = "Unknown";

    if (acknowledgementDate == null) 
      acknowledgementDate = new  Date();

    ((MessageStore)messageToAcknowledge).acknowledge(acknowledger, acknowledgementDate);

    for (Enumeration e = messageServerListeners.elements(); e.hasMoreElements();)
      ((MessageServerListener)e.nextElement()).messageAcknowledged(messageToAcknowledge, 
								    acknowledger, 
								    acknowledgementDate);
  }

  @Override
  public void acknowledgeMessages(Message[] messagesToAcknowledge, 
				  String acknowledger, 
				  Date acknowledgementDate)
       throws MessageAlreadyAcknowledgedException
  {
    if (acknowledger == null)
      acknowledger = "Unknown";

    if (acknowledgementDate == null) 
      acknowledgementDate = new  Date();

    for (int i = 0; i < messagesToAcknowledge.length; i++)
      {
	((MessageStore)messagesToAcknowledge[i]).acknowledge(acknowledger, acknowledgementDate);
      }

    for (Enumeration e = messageServerListeners.elements(); e.hasMoreElements();)
      ((MessageServerListener)e.nextElement()).messagesAcknowledged(messagesToAcknowledge, 
								    acknowledger, 
								    acknowledgementDate);
  }

  @Override
  public void addMessageServerListener(MessageServerListener messageServerListener)
  {
    messageServerListeners.add(messageServerListener);
    System.out.println("<MessageServer> MessageServerListener added");
  }

  @Override
  public void removeMessageServerListener(MessageServerListener messageServerListener)
  {
    messageServerListeners.remove(messageServerListener);
  }

  @Override
  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
    support.addPropertyChangeListener(listener);
  }

  @Override
  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
    support.removePropertyChangeListener(listener);
  }
  //end messageServer interface
}
