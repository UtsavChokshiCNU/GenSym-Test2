/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXDispatchableImpl.java
 *
 *   Author: Allan Scott
 */

package com.gensym.com;

import java.util.Vector;

import java.lang.reflect.Method;
import java.lang.reflect.Constructor;

/** The class <code>ActiveXDispatchableImpl</code> provides an implementation
* of the <code>ActiveXDispatchable</code> interface.
* <p>
* <code>BeanXporter</code> uses this class when exporting types in a
* type library that are simply dispatch interfaces (TKIND_DISPATCH).
* <p>
* @see ActiveXDispatchable
* @see BeanXporter
*/
public class ActiveXDispatchableImpl implements ActiveXDispatchable,
                                                ActiveXTraceLevels
{

 /** The dispatch pointer through which all automation
  * calls made by this implementation class are made.  Note
  * that this is transient because dispatch pointers can not persist.
  */
  protected transient int dispatchPointer = AX_NO_DISPATCH;
  
  /** The <code>ActiveXProxy</code> through which all automation
  * calls made by this implementation class are made
  */
  protected ActiveXProxy axProxy = null;

  /** Construct a new <code>ActiveXDispatchableImpl</code> from a dispatch
   * pointer and an <code>ActiveXProxy</code> object
   */
  public ActiveXDispatchableImpl (int dispatchPointer, ActiveXProxy axProxy) {
    this.dispatchPointer = dispatchPointer;
    this.axProxy = axProxy; 
  }

  /** Construct a new <code>ActiveXDispatchableImpl</code> from an
   * object that implements ActiveXDispatchable
   */
  public ActiveXDispatchableImpl (ActiveXDispatchable axDispatch) {
    this.dispatchPointer = axDispatch.getDispatchPointer();
    this.axProxy = axDispatch.getActiveXProxy(); 
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public int getDispatchPointer()
  {
      return dispatchPointer;
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public int getDispatchPointer(ActiveXProxy proxy)
  {
  
  // If proxy is the same there is no need for marshalling
  if (proxy == this.axProxy)
  {
    return dispatchPointer;
  }
  // Otherwise need to marshall the pointer to the 
  // thread of my current proxy
  else {
    int stream = axProxy.marshalInterface(dispatchPointer);
    if (stream == 0)
      return dispatchPointer;

    return proxy.getMarshaledInterface(stream);
    }
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public ActiveXProxy getActiveXProxy()
  {
      return axProxy;
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public Variant axInvoke(String methodName,
                          Vector args)
                          throws ActiveXException
  {
    return axProxy.axInvoke(dispatchPointer, methodName, false, args);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public Variant axInvoke(String methodName,
                          int dispatchType,
                          boolean voidReturn,
                          Vector args) 
                          throws ActiveXException  
  {
    return axProxy.axInvoke(dispatchPointer, methodName, dispatchType, 
                             voidReturn, args);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public Variant axInvoke(int memid,
                          Vector args) 
                          throws ActiveXException  
  {
    return axProxy.axInvoke(dispatchPointer, memid, false, args);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public Variant axInvoke(int memid,
                          int dispatchType,
                          boolean voidReturn,
                          Vector args) 
                          throws ActiveXException
  {
    return axProxy.axInvoke(dispatchPointer, memid, dispatchType,
                               voidReturn,args);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public Variant getAxProperty(String propertyName) 
                                  throws ActiveXException
  {
    return axProxy.getAxProperty(dispatchPointer, propertyName);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public Variant getAxProperty(int memid) 
                                  throws ActiveXException
  {
    return axProxy.getAxProperty(dispatchPointer, memid);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public void setAxProperty(String propertyName,
                            Variant newValue) 
                            throws ActiveXException  
  {
    axProxy.setAxProperty(dispatchPointer, propertyName, newValue);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable */
  @Override
  public void setAxProperty(int memid,
                            Variant newValue) 
                            throws ActiveXException
  {
    axProxy.setAxProperty(dispatchPointer, memid, newValue);
  }

  /** Use Gensym's tracing mechanism to send a trace message at
  * a default trace level
  */
  protected void message(String m) {
    com.gensym.com.NativeMethodBroker.traceln(m);
  }

  /** Use Gensym's tracing mechanism to send a trace message at
  * a specified trace level.  The possible trace levels are defined
  * by <code>ActiveXTraceLevels</code>
  * @see ActiveXTraceLevels
  */
  protected void message(int d, String m) {
    com.gensym.com.NativeMethodBroker.traceln(d, m);
  }

  /** Return a string that represents this object.
  */
  @Override
  public String toString() {
      return "<ActiveXDispatchableImpl, dispatchPointer = " + 
             Integer.toHexString(dispatchPointer) +
             ", axProxy = " + axProxy +
             ">";
  }

}

