package com.gensym.cbu.messageserver;

public class MessageAlreadyAcknowledgedException extends Exception
{
  MessageAlreadyAcknowledgedException (String message)
  {
    super(message);
  }
}
