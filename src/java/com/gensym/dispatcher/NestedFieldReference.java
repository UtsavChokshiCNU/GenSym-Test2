package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.lang.reflect.*;
import com.gensym.message.Trace;

public class NestedFieldReference extends NestedReference
{
  private String fieldName;
  
  public NestedFieldReference(Class type,
			      String fieldName,
			      Reference reference)
  {
    super(type, reference);
    this.fieldName = fieldName;
  }

  @Override
  public Object getValue(Object rootObject)
       throws IllegalAccessException
  {
    try {
      Object obj = reference.getValue(rootObject);
      Class clazz = obj.getClass();
      Field field = clazz.getField(fieldName);
      return field.get(obj);
    } catch (NoSuchFieldException nsfe) {
      Trace.exception(nsfe);
      return null;
    }
  }

}
