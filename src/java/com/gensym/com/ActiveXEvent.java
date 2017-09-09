/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXEvent.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

import java.util.Vector;
import java.util.EventObject;

public class ActiveXEvent extends EventObject  
{
  private String eventName;
  private Variant[] arguments;
  private int memid = -1;

  public ActiveXEvent(Object source,
                      String eventName,
                      Variant[] arguments)
  {
      super(source);
      this.eventName = eventName;
      if (arguments == null)
        this.arguments = null;
      else this.arguments = arguments;
  }

  public ActiveXEvent(Object source,
                      int memid,
                      String eventName,
                      Variant[] arguments)
  {
      this(source, eventName, arguments);
      this.memid = memid;
  }

  public Variant[] getArguments()
  {
     return arguments;
  }

  public String getEventName()
  {
      return eventName;
  }

  public int getMemid()
  {
      return memid;
  }
}
