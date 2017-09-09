package com.gensym.beansruntime;

import java.util.EventObject;

public class HookupEvent extends EventObject
{
  private Object innerEvent;
  
  public HookupEvent(Object source, Object innerEvent)
  {
    super(source);
    this.innerEvent = innerEvent;
  }

  @Override
  public String toString()
  {
    return "<HookupEvent of "+innerEvent.toString()+">";
  }
}
