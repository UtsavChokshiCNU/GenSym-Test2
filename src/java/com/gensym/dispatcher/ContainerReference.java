package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;

public class ContainerReference extends SimpleReference
{
  public ContainerReference()
  {
    this(Container.class);
  }

  public ContainerReference(Class type)
  {
    super(type);
  }

  public Object getValue(DispatchTable table)
       throws IllegalAccessException
  {
    return table.container;
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
   return "theContainer"; 
  }
}
