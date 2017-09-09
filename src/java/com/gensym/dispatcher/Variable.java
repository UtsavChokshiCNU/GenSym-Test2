package com.gensym.dispatcher;

/**
 * Variable
 */

public class Variable
{
  private String name;
  private Object value;
  private Class type;
  private boolean setable;
  private static boolean debug = false;
  
  public Variable(String name,
		  Object value,
		  Class type,
		  boolean setable)
  {
    this.name = name;
    this.value = value;
    this.type = type;
    this.setable = setable;
  }

  @Override
  public boolean equals(Object obj)
  {
    return name.equals(obj);
  }
    
  public boolean isSetable()
  {
    return setable;
  }

  public void setSetable(boolean setable)
  {
    this.setable = setable;
  }

  public void setValue(Object value)
  {
    if (setable)
      this.value = value;
    if (debug)
      System.out.println("VARIABLE " + name + " == " + this.value);
  }
  
  public Object getValue()
  {
    return value;
  }
  
  public String getName()
  {
    return name;
  }

  public Class getType()
  {
    return type;
  }

  @Override
  public String toString()
  {
    return name;
  } 
}
