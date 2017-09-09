package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;

public class ConstantReference extends SimpleReference
{
  private Object constant;

  public ConstantReference(Object constant)
  {
    super(constant.getClass());
    this.constant = constant;
  }
  
  public ConstantReference(Class type, Object constant)
  {
    super(type!=null?type:constant.getClass());
    this.constant = constant;
  }

  public Object getValue(DispatchTable table)
  {
    return getValue();
  }

  @Override
  public Object getValue(Object obj) {
    return getValue();
  }
				    
  public Object getValue()
  {
    return constant;
  }

  @Override
  public String toString()
  {
    if (constant instanceof String)
      return "\"" + constant + "\"";
    else if (constant instanceof com.gensym.util.Symbol)
      return "com.gensym.util.Symbol.intern(\"" + constant + "\")";
    else if (constant instanceof Class) {
      Class cls = ((Class)constant);
      if (cls.isPrimitive())
	return cls.getName() + ".TYPE";
      else
	return cls.getName() + ".class";
    }
    return constant.toString();
  }
  
}
