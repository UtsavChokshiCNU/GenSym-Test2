package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;

public class VariableReference extends SimpleReference
{

  private String name;
  
  public VariableReference(String name)
  {
    this(name, java.lang.Object.class);

  }

  public VariableReference(String name, Class type)
  {
    super(type);
    this.name = name;
  }

   
  @Override
  public Object getValue(Object obj)
  {
    if (obj instanceof DispatchTable) {
      try {
	return getValue((DispatchTable)obj);
      } catch (NoSuchVariableException nsve) {
	return null;//bad, but I can't throw it
      }
    } else
      return null;

  }
  
  public Object getValue(DispatchTable table)
       throws NoSuchVariableException
  {
    return table.getVariable(name).getValue();
  }

  @Override
  public String toString()
  {
    return name;
  }
}
