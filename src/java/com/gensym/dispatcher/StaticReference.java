package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.lang.reflect.*;

public class StaticReference extends SimpleReference
{
  private Field field;

  public StaticReference(String className,
			 String fieldName)
       throws ClassNotFoundException,
			   NoSuchFieldException,
			   NonStaticFieldException
  {
    this(Class.forName(className), fieldName);
  }
  
  public StaticReference(Class classObject,
			 String fieldName)
       throws NoSuchFieldException,
			   NonStaticFieldException
  {
    this(classObject.getField(fieldName));
  }

  public StaticReference(Field field)
       throws NonStaticFieldException
  {
    super(field.getType());
    this.field = field;
    if (!Modifier.isStatic(field.getModifiers()))
      throw new NonStaticFieldException();
  }

  @Override
  public Object getValue(Object obj)
       throws IllegalAccessException
  {
    return field.get(obj);
  }

  public Object getValue()
       throws IllegalAccessException
  {
    return getValue(null);
  }
  
}
