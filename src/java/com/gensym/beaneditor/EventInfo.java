package com.gensym.beaneditor;

import java.beans.*;
import java.awt.Color;
import java.lang.reflect.*;

public class EventInfo implements java.io.Serializable
{
  protected Class clazz;
  protected String name;
  protected Method method;
  protected MethodDescriptor methodDescriptor;
  // don't set the following directly
  // - do it through the method on BeanCanvas
  boolean isShown = false; 
  protected Color color;

  public EventInfo(String name, Class clazz, Method method, 
		   MethodDescriptor methodDescriptor,
		   Color color)
  {
    this.clazz = clazz;
    this.name = name;
    this.method = method;
    this.methodDescriptor = methodDescriptor;
    this.isShown = false;
    this.color = color;
  }

}
