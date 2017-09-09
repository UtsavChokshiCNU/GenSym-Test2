package com.gensym.cbu.experimental.cbudataviewer;

import com.gensym.cbu.messageserver.MessageServerListener;
import com.gensym.cbu.messageserver.Message;
import com.gensym.cbu.messageserver.MessageNotAcknowledgedException;
import java.util.Date;

public class MessageCbuData implements CbuData
{
  Message message;

  MessageCbuData (Message message)
  {
    this.message = message;
  }

  //CBU DATA INTERFACE
  @Override
  public Object getPropertyValue(String propertyName)
  {
    Object value = null;

    if (propertyName.equals("TargetId"))
      value = message.getTargetId();
    else if (propertyName.equals("SenderId"))
      value = message.getSenderId();
    else if (propertyName.equals("EventType"))
      value = message.getEventType();
    else if (propertyName.equals("MainText"))
      value = message.getMainText();
    else if (propertyName.equals("AdditionalText"))
      value = message.getAdditionalText();
    else if (propertyName.equals("Priority"))
      value = new Integer(message.getPriority());
    else if (propertyName.equals("PublicationDate"))
      value = message.getPublicationDate();
    else if (propertyName.equals("Acknowledger"))
      try
      {
	value = message.getAcknowledger();
      }
    catch (MessageNotAcknowledgedException e)
      {
      }
    else if (propertyName.equals("AcknowledgementDate"))
      try
      {
	value = message.getAcknowledgementDate();
      }
    catch (MessageNotAcknowledgedException e)
      {
      }

    return value;
  }

  @Override
  public Object getOriginalDataReference()
  {
    return message;
  }
}
