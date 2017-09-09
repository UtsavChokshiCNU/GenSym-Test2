package com.gensym.draw;

public class ColorTableEvent extends java.util.EventObject 
       implements java.io.Serializable
{
  private Object key = null;

  public ColorTableEvent()
  {
    super(new Integer (42));
  }

  public ColorTableEvent(Object source, Object key)
  {
    super(source);
    this.key = key;
  }
}
