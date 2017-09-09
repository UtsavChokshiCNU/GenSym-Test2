package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;

public class EventReference extends SimpleReference
{
  public EventReference()
  {
    this(java.util.EventObject.class);
  }

  public EventReference(Class eventClass)
  {
    //check that it is a subclass of EventObject ???
    super(eventClass);
  }

  @Override
  public Object getValue(Object obj)
       throws IllegalAccessException
  {
    if (obj instanceof DispatchTable)
      return getValue((DispatchTable)obj);
    return null;
  }
  
  public Object getValue(DispatchTable table)
       throws IllegalAccessException
  {
    // System.out.println("EVENT REF in " + table + " = " + table.event);
    return table.event;
  }

  @Override
  public String toString()
  {
   return "theEvent"; 
  }
}
