/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXBeanInfo.java
 *
 *  Author: Allan Scott
 */
package com.gensym.com;

import java.beans.SimpleBeanInfo;
import java.beans.EventSetDescriptor;
import java.beans.PropertyDescriptor;
import java.beans.MethodDescriptor;

import java.util.Vector;

public abstract class ActiveXBeanInfo extends SimpleBeanInfo
{
  private Vector methodDescriptors;
  private Vector eventSetDescriptors;
  private Vector propertyDescriptors;

  @Override
  public MethodDescriptor[] getMethodDescriptors()
  {
    if (methodDescriptors == null)
      return null;

    MethodDescriptor[] returnDescriptors = 
      new MethodDescriptor[methodDescriptors.size()];

    methodDescriptors.copyInto(returnDescriptors);

    return returnDescriptors;
  }

  @Override
  public EventSetDescriptor[] getEventSetDescriptors()
  {
    if (eventSetDescriptors == null)
      return null;

    EventSetDescriptor[] returnDescriptors = 
      new EventSetDescriptor[eventSetDescriptors.size()];

    eventSetDescriptors.copyInto(returnDescriptors);

    return returnDescriptors;
  }

  @Override
  public PropertyDescriptor[] getPropertyDescriptors()
  {
    if (propertyDescriptors == null)
      return null;

    PropertyDescriptor[] returnDescriptors = 
      new PropertyDescriptor[propertyDescriptors.size()];

    propertyDescriptors.copyInto(returnDescriptors);

    return returnDescriptors;
  }

  protected void addPropertyDescriptor(PropertyDescriptor descriptor)
  { 
    if (descriptor != null)
    {
       if (propertyDescriptors == null)
         propertyDescriptors = new Vector();
       propertyDescriptors.addElement(descriptor);
    }
  }

  protected void addEventSetDescriptor(EventSetDescriptor descriptor)
  {
    if (descriptor != null)
    {
      if (eventSetDescriptors == null)
         eventSetDescriptors = new Vector();
      eventSetDescriptors.addElement(descriptor);
      if (descriptor instanceof ActiveXEventSetDescriptor)
      {
        ((ActiveXEventSetDescriptor) descriptor).setEventSetID
          (eventSetDescriptors.size() - 1);
      }
    }
  }

  public ActiveXEventSetDescriptor getActiveXEventSetDescriptor(
                    int eventSetId)
  {
    EventSetDescriptor evt;
    if (eventSetDescriptors == null)
      return null;
    
    if (eventSetId < eventSetDescriptors.size())
    {
      evt = (EventSetDescriptor) eventSetDescriptors.elementAt(eventSetId);
      if (evt instanceof ActiveXEventSetDescriptor)
        return (ActiveXEventSetDescriptor) eventSetDescriptors.elementAt(eventSetId);
      return null;
    }
    else return null;
  }

  protected void addMethodDescriptor(MethodDescriptor descriptor)
  {
    if (descriptor != null)
    {
      if (methodDescriptors == null)
         methodDescriptors = new Vector();
      methodDescriptors.addElement(descriptor);
    }
  }
}
