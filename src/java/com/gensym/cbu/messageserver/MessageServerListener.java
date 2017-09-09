package com.gensym.cbu.messageserver;

import java.rmi.Remote;
import java.util.Date;

public interface MessageServerListener extends Remote
{
  public void messageAdded(Message newMessage);
  
  public void messageDeleted(Message deletedMessage);

  public void messagesDeleted(Message[] deletedMessages);

  public void messageAcknowledged(Message acknowledgedMessage, String acknowledger, Date acknowledgementDate);
  
  public void messagesAcknowledged(Message[] acknowledgedMessages, String acknowledger, Date acknowledgementDate);

  public void messagePriorityChanged(Message message, int newPriority);
}


