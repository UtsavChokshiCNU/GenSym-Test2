package com.gensym.cbu.odie;

import java.util.EventObject;

public class OslConnectionEvent extends EventObject
{
  OdieEvent odieEvent;
  Manager manager;

  public OslConnectionEvent(Object source, OdieEvent odieEvent, Manager manager)
  {
    super(source);
    this.odieEvent = odieEvent;
    this.manager = manager;;
  }

  public OdieEvent getOdieEvent()
  {
    return odieEvent;
  }

  public Manager getManager()
  {
    return manager;
  }

  @Override
  public String toString()
  {
    return "<OdieEvent= ("+ odieEvent +") \nmanager = (" + manager + ")>";
  }
}
