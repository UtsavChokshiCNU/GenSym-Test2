package com.gensym.demos.dialogapplet;

import java.util.EventObject;

public class AlarmEvent extends EventObject implements java.io.Serializable
{
  
  public AlarmEvent()
  {
    super(new Integer (42));
  }

  
  public AlarmEvent(Object source)
  {
    super(source);
  }
}
