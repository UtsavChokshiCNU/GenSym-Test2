package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.lang.reflect.*;
import com.gensym.message.Trace;

public class NestedPropertyReference extends NestedReference
{
  private String methodName;

  private Method cachedMethod;

  public NestedPropertyReference(Class type,
				 String methodName,
				 Reference reference)
  {
    super(type, reference);
    this.methodName = methodName;
  }

  @Override
  public Object getValue(Object rootObject)
       throws IllegalAccessException
  {
    return getValue((DispatchTable) rootObject);
  }
  
  public Object getValue(DispatchTable table)
       throws IllegalAccessException
  {
    try {
      Object obj = reference.getValue(table);
      if (obj == null)
	return null;
      Method method;
      if (cachedMethod != null)
	method = cachedMethod;
      else {
	Class clazz = obj.getClass ();
	Class refClass = reference.getType ();
	method = clazz.getMethod(methodName, null);
	if (clazz.getClassLoader() == null && (clazz == refClass))
	  cachedMethod = method;
      }
      return method.invoke(obj, null);
    } catch (NoSuchMethodException nsme) {
      Trace.exception(nsme,
		      "\nMethod Name: " +
		      methodName +
		      "\nObject Class: " +
		      reference.getValue(table).getClass());
    } catch (InvocationTargetException ite) {
      Trace.exception(ite);
    }
    return null;
  }

  @Override
  public String toString()
  {
    return "(("+reference.getType().getName()+")"+
      reference + ")." + methodName + "()";
  }
  
}
