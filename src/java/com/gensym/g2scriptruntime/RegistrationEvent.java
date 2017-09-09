package com.gensym.g2scriptruntime;

import java.util.EventObject;

public class RegistrationEvent extends EventObject
{
  Object o;
  
  public RegistrationEvent(Object source, Object o)
  {
    super(source);
    this.o = o;
  }

  public Object getObject()
  {
    return o;
  }
}
