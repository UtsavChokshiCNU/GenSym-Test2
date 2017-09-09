package com.gensym.cbu.odie;

class EventNotInHistoryException extends Exception
{
  EventNotInHistoryException (String message)
  {
    super (message);
  }
}
