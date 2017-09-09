package com.gensym.wksp;

import java.awt.Container;
import java.util.EventObject;
import com.gensym.dispatcher.*;
import com.gensym.message.Trace;

public class DispatchSetAction extends Action
{
  private static boolean debug = false;
  private String variableName;
  private Object variableValue;
  private Class cls;
  
  public DispatchSetAction(String variableName,
			   Class cls,
			   Object variableValue)
  {
    this.variableName = variableName;
    this.variableValue = variableValue;
    this.cls = cls;
  }

  @Override
  public Object invoke(DispatchTable table) 
  {
    Object value = variableValue;
    if (debug)
      System.out.println("1. SETTING " + variableName + " to " + value);
    try {
      if (value instanceof Reference)
	value = ((Reference)value).getValue(table);
    } catch (IllegalAccessException iae) {
      Trace.exception(iae);
    }
    if (debug)
      System.out.println("2. SETTING " + variableName + " to " + value);
    try {
      table.setVariable(variableName, value);
    } catch (NoSuchVariableException nsve) {
      Trace.exception(nsve);
    }; 
    return null;
  }

  @Override
  public String toString()
  {
    return variableName + " = ("+cls.getName()+")"+variableValue+";";
  }

}
