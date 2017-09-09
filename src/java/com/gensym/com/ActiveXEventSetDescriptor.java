/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXComponent.java
 *
 *  Author: Allan Scott
 */
package com.gensym.com;

import java.beans.EventSetDescriptor;
import java.beans.IntrospectionException;

import java.lang.reflect.Method;
import java.lang.reflect.Constructor;
import java.util.Hashtable;

public class ActiveXEventSetDescriptor 
	extends EventSetDescriptor 
{
    private Hashtable map = new Hashtable();
    private String eventName;
    private Class eventClass;
    private Guid iid;
    private int eventSetID;
    String beanClassName;
    
    public ActiveXEventSetDescriptor 
      (Class beanClass,
       Guid iid,
       String interf,
       Class listenerType,
       String[] methods,
       int[] dispIDs,
       String addMethod,
       String removeMethod)
       throws IntrospectionException
    {
      super(beanClass, interf, listenerType,
        methods, addMethod, removeMethod);

      if ((dispIDs == null)  ||
        (dispIDs.length != methods.length))
        throw new IntrospectionException(
        "Invalid dispids provided to ActiveXEventSetDescriptor");

      int length = dispIDs.length;
      for (int i = 0; i < dispIDs.length; i++)
      {
        map.put(new Integer(dispIDs[i]), methods[i]);  
      }

      String listenerName = listenerType.getName();
      int beginListener = listenerName.indexOf("Listener");
      eventName = listenerName.substring(0, beginListener) + "Event";

      beanClassName = beanClass.getName();
      this.iid = iid;
    }

    public Method getListenerMethod(int dispid) 
        throws NoSuchMethodException, ClassNotFoundException 
    {
        String methodName;

        methodName = (String) map.get(new Integer(dispid));
    
        if (methodName == null)
          throw new NoSuchMethodException();

        Class type = getListenerType();

        // Now try to retrieve the Method associated
        // with this type by reflection.
        
        getEventType(type.getClassLoader());
        return type.getMethod(methodName,new Class[] {eventClass});
    }


    public Constructor getEventConstructor()
          throws NoSuchMethodException, ClassNotFoundException 
    {

      getEventType(null);

      return eventClass.getConstructor(new Class [] {
                                       Object.class,
                                       String.class,
                                       Variant[].class
                                       });                                      
    }

    private Class getEventType(ClassLoader l)
            throws ClassNotFoundException
    {
      if (eventClass == null)
        if (l == null)
            eventClass = Class.forName(eventName);
        else eventClass = l.loadClass(eventName);
      return eventClass;
    }

    public Guid getIID()
    {
        return iid;
    }

    public int getEventSetID()
    {
        return eventSetID;
    }

    void setEventSetID(int eventSetID)
    {
        this.eventSetID = eventSetID; 
    }
      
    public String getBeanInfoClassName()
    {
        return beanClassName + "BeanInfo";
    }

}
