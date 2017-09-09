package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.lang.reflect.*;
import com.gensym.message.Trace;

public class NestedMethodReference extends NestedReference
{
  private String methodName;
  private Reference[] args;

  private static Class[] getTypes(Reference[] refs)
  {
    if (refs == null)
      return null;
    Class[] types = new Class[refs.length];
    for (int i=0;i<refs.length;i++) {
      types[i]=refs[i].getType();
    }
    return types;
  }

  private String pprintArgs()
  {
    if (args == null) return "";
    String str = "";
    for (int i=0;i<args.length;i++) {
      String type = args[i].getType().getName();
      str = str + "("+type+")" + " " + args[i];
      if (i < args.length-1)
	str+=",";
    }
    return str;
  }

  private Object[] getArgumentValues(DispatchTable table)
       throws IllegalAccessException
  {
    if (args == null)
      return null;
    Object[] argValues = new Object[args.length];
    for (int i=0;i<args.length;i++) {
      argValues[i] = args[i].getValue(table);
    }
    return argValues;
  }

  public NestedMethodReference(Class type,
			       String methodName,
			       Reference reference,
			       Reference[] args)
  {
    super(type, reference);
    this.methodName = methodName;
    this.args = args;
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
      Class clazz = obj.getClass();
      Class[] argTypes = getTypes(args);
      Method method = clazz.getMethod(methodName, argTypes);
      Object[] argumentValues = getArgumentValues(table);
      return method.invoke(obj, argumentValues);
    } catch (NoSuchMethodException nsme) {
      //System.out.println("COULDNT FIND METHOD FOR " + methodName);
      Trace.exception(nsme);
    } catch (InvocationTargetException ite) {
      Trace.exception(ite);
    }
    return null;
  }

  @Override
  public String toString()
  {
    return reference + "." + methodName + "(" + pprintArgs()+ ")";
  }
  
}
