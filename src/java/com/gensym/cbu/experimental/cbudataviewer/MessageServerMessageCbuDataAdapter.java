package com.gensym.cbu.experimental.cbudataviewer;

import com.gensym.cbu.messageserver.MessageServerListener;
import com.gensym.cbu.messageserver.Message;
import java.util.Date;

public class MessageServerMessageCbuDataAdapter extends AbstractCbuDataAdapter implements MessageServerListener
{
  //MessageServerListener Interface
  @Override
  public void messageAdded(Message newMessage)
  {
    CbuData cbuData = new MessageCbuData(newMessage);
    addDataElement(newMessage, cbuData);
  }
  
  @Override
  public void messageDeleted(Message deletedMessage)
  {
    removeDataElement(deletedMessage);
  }

  @Override
  public void messagesDeleted(Message[] deletedMessages)
  {
    for( int i = 0; i < deletedMessages.length; i++)
      removeDataElement(deletedMessages[i]);
  }

  @Override
  public void messageAcknowledged(Message acknowledgedMessage, String acknowledger, Date acknowledgementDate)
  {
    dataElementChanged(acknowledgedMessage, "acknowledger", acknowledger);
    dataElementChanged(acknowledgedMessage, "acknowledgementDate", acknowledgementDate);
  }
  
  @Override
  public void messagesAcknowledged(Message[] acknowledgedMessages, String acknowledger, Date acknowledgementDate)
  {
    for( int i = 0; i < acknowledgedMessages.length; i++)
	messageAcknowledged(acknowledgedMessages[i], acknowledger, acknowledgementDate);
  }

  @Override
  public void messagePriorityChanged(Message message, int newPriority)
  {
    dataElementChanged(message, "priority", new Integer(newPriority));
  }
  //end MessageServerListener Inteface
}
