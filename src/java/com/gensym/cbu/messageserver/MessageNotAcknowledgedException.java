package com.gensym.cbu.messageserver;

public class MessageNotAcknowledgedException extends Exception
{
  MessageNotAcknowledgedException (String message)
  {
    super(message);
  }
}
