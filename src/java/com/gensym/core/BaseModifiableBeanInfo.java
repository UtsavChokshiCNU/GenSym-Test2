package com.gensym.core;

import java.beans.*;
import java.util.Hashtable;
import java.util.Vector;

/** ModifiableBeanInfo is a really useful hack that allows one to
 *  override the default behavior of Introspector.getBeanInfo().  It
 *  is not obvious to the author why Javasoft did not make the
 *  Introspector a little more open.  The implementation of this class
 *  seems to be a little bit hackish, but is hoped that it is at least
 *  has good hygiene.  
 *  <p> 
 *  It provides four protected methods to be
 *  overridden by subclasses.  getBeanClass() informs the parent class
 *  of what bean is being introspected.  The other three are methods
 *  that allow the subclasses to inspect and modify FeatureDescriptors
 *  that are created by the default Introspector getBeanInfo.  */

public abstract class BaseModifiableBeanInfo extends SimpleBeanInfo
{
  private static Hashtable threads = new Hashtable();
  private static final int EVENT = 1;
  private static final int PROPERTY = 2;
  private static final int METHOD = 4;

  /** Should return the class
   *  that this BeanInfo describes.
   */
  protected abstract Class getBeanClass();

  private static void setThreadInCall(int callID)
  {
    synchronized (threads)
      {
	Thread current = Thread.currentThread();
	Integer integer = (Integer) threads.get(current);
	if (integer == null)
	  threads.put(current,callID);
	else
	  threads.put(current, integer | callID);
      }
  }

  private static void clearThreadInCall(int callID)
  {
    synchronized (threads)
      {
	Thread current = Thread.currentThread();
	Integer integer = (Integer) threads.get(current);
	if (integer == null)
	  return;
	int bits = integer;
	int remainingBits = bits & ~callID;
	if (remainingBits == 0)
	  threads.remove(current);
	else
	  threads.put(current,remainingBits);
      }
  }
  
  private boolean isThreadInCall(int callID)
  {
    synchronized (threads)
      {
	Thread current = Thread.currentThread();
	Integer integer = (Integer) threads.get(current);
	if (integer == null)
	  return false;
	else
	  return ((integer & callID) != 0);
      }
  }

  private boolean isThreadInAnyCall()
  {
    synchronized (threads)
      {
	Thread current = Thread.currentThread();
	Integer integer = (Integer) threads.get(current);
	return integer != null;
     }
  }

  @Override
  public EventSetDescriptor[] getEventSetDescriptors()
  {
    // System.out.println("in getESD "+isThreadInCall(EVENT));
    // Thread.dumpStack();
    if (isThreadInAnyCall()) // isThreadInCall(EVENT))
      return null;
    else
      {
	EventSetDescriptor[] esds = null;
	try {
	  setThreadInCall(EVENT);
	  BeanInfo beanInfo = Introspector.getBeanInfo(getBeanClass(),
						       java.lang.Object.class);
	  esds = beanInfo.getEventSetDescriptors();
	  int i,length= esds.length;
	  for (i=0; i<length; i++)
	    modifyEventSetDescriptor(esds[i]);
	  // System.out.println("threads size = "+threads.size());
	} catch (Exception e)
	  {
	    e.printStackTrace();
	    return null;
	  }
	finally
	  {
	    clearThreadInCall(EVENT);
	  }
	  // System.out.println("final threads size = "+threads.size());
	  return esds;
      }
  }

  /** Specializing modifiyEventSetDescriptor allows subclasses of
   *  ModifiableBeanInfo to modify EventSetDescriptors that The
   *  java.beans.Introspector whips up.  */ 
  protected void modifyEventSetDescriptor(EventSetDescriptor eventSetDescriptor)
  {

  }  

  @Override
  public PropertyDescriptor[] getPropertyDescriptors()
  {
    if (isThreadInAnyCall()) // isThreadInCall(PROPERTY))
      return null;
    else
      {
	PropertyDescriptor[] propertyDescriptors = null;
	Vector remainingDescriptors = new Vector();
	try {
	  setThreadInCall(PROPERTY);
	  BeanInfo beanInfo = Introspector.getBeanInfo(getBeanClass(),
						       java.lang.Object.class);
	  propertyDescriptors
	    = beanInfo.getPropertyDescriptors();
	  int i,length= propertyDescriptors.length;
	  for (i=0; i<length; i++)
	    {
	      PropertyDescriptor descriptor 
		= modifyPropertyDescriptor(propertyDescriptors[i]);
	      if (descriptor != null)
		remainingDescriptors.addElement(descriptor);
	    }
	  // System.out.println("threads size = "+threads.size());
	} catch (IntrospectionException e)
	  {
	    return null;
	  }
	finally
	  {
	    clearThreadInCall(PROPERTY);
	  }
	PropertyDescriptor[] newDescriptors = new PropertyDescriptor[remainingDescriptors.size()];
	remainingDescriptors.copyInto(newDescriptors);
	return newDescriptors;
      }
  }

  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    return propertyDescriptor;
  }  

  @Override
  public MethodDescriptor[] getMethodDescriptors()
  {
    if (isThreadInAnyCall()) // isThreadInCall(METHOD))
      {
	return null;
      }
    else
      {
	MethodDescriptor[] methodDescriptors = null;
	try {
	  setThreadInCall(METHOD);
	  BeanInfo beanInfo = Introspector.getBeanInfo(getBeanClass(),
						       java.lang.Object.class);
	  methodDescriptors
	    = beanInfo.getMethodDescriptors();
	  int i,length= methodDescriptors.length;
	  for (i=0; i<length; i++)
	    {
	      modifyMethodDescriptor(methodDescriptors[i]);
	    }
	  // System.out.println("threads size = "+threads.size());
	  
	} catch (IntrospectionException e)
	  {
	    return null;
	  }
	finally
	  {
	    clearThreadInCall(METHOD);
	    // System.out.println("final threads size = "+threads.size());
	  }
    return methodDescriptors;
      }
  }

  protected void modifyMethodDescriptor(MethodDescriptor methodDescriptor)
  {

  }
}

