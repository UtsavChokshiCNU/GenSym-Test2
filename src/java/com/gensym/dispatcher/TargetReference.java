package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;

public class TargetReference extends SimpleReference
{
  public TargetReference()
  {
    this(java.lang.Object.class);
  }
  
  public TargetReference(Class type)
  {
    super(type);
  }

  public Object getValue(DispatchTable table)
       throws IllegalAccessException
  {
    return table.target;
  }

  @Override
  public Object getValue(Object table)
       throws IllegalAccessException
  {
    return getValue((DispatchTable)table);
  }

  @Override
  public String toString()
  {
   return "theTarget"; 
  }
}
