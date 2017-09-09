package com.gensym.cbu.messageserver;

import java.beans.PropertyChangeListener;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Enumeration;
import java.util.Date;

public interface MessageServer
{
  public String getName();

  public Enumeration getAllMessages();

  public Message addMessage(String target,
			    String sender,
			    String category,
			    String mainText,
			    String additionalText,
			    int priority) throws RemoteException;
  
  public void deleteMessage(Message message);

  public void deleteMessages(Message[] messagesToDelete);

  public void changeMessagePriority(Message message, int newPriority);

  public void acknowledgeMessage(Message messageToAcknowledge, 
				 String acknowledger,
				 Date acknowledgementDate) 
       throws MessageAlreadyAcknowledgedException;

  public void acknowledgeMessages(Message[] messagesToAcknowledge, 
				  String acknowledger,
				  Date acknowledgementDate) 
       throws MessageAlreadyAcknowledgedException;

  public void addPropertyChangeListener(PropertyChangeListener listener);

  public void removePropertyChangeListener(PropertyChangeListener listener);

  public void addMessageServerListener(MessageServerListener messageServerListener);

  public void removeMessageServerListener(MessageServerListener messageServerListener);       
}







