package com.gensym.dispatcher;

public abstract class Reference
{
  Class type;

  public Reference(Class type)

  {
    this.type = type;
  }

  public Class getType()
  {
    return type;
  }

  public abstract Object getValue(Object obj)
       throws IllegalAccessException;
  
}
