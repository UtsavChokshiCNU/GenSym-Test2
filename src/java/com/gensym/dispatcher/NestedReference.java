package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.lang.reflect.*;
import com.gensym.message.Trace;

public abstract class NestedReference extends Reference
{
  protected Reference reference;
  
  public NestedReference(Class type,
			 Reference reference)
  {
    super(type);
    this.reference = reference;
  }

  @Override
  public abstract Object getValue(Object rootObject)
       throws IllegalAccessException;

}
