/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXDispatchable.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

import java.util.Vector;

/** The interface <code>ActiveXDispatchable</code> is the generic
* automation interface that is used by the com.gensym.com module
* When <code>BeanXporter</code> exports a type library all types 
* that can be controlled by automation are emitted as classes that
* implement <code>ActiveXDispatchable</code>.  Default implementations 
* of <code>ActiveXDispatchable</code> are provided by the classes
* <code>ActiveXDispatchableImpl</code> and 
* <code>ActiveXDefaultComponentImpl</code>.
*<p>
* <code>ActiveXDispatchable</code> is one of a system of interfaces that
* can be used to describe the classes that are created by <code>BeanXporter</code>.
* Other important interfaces are:  <code>ActiveXComponent</code> which 
* provides a component interface and <code>ActiveXDisplayComponent</code>
* which provides an interface for a visual <code>ActiveXComponent</code>.
* Interfaces are used to specify these behaviors so that it is possible
* for the BeanXporter facility to be specified without reference to
* implementation issues, and to allow alternative implementations.
*<p>
* In order to implement this interface the developer requires access to
* two things:
* <ul>
* <li> An <code>ActiveXProxy</code> object
* <li> A dispatch pointer (an integer)
* </ul>   
* The developer can then use the axInvoke methods in <code>ActiveXProxy</code>
* to implement the methods required by this interface.
*<p>
* A user of an object that implements this interface can make automation calls to 
* methods and properties.  The classes that are emitted by <code>BeanXporter</code>
* are one such user.  They use the <code>memid</code> of a particular method and
* property which can be found in a type library.  It is also possible for users
* to use the name of a method or property.
*<p>
* @see ActiveXProxy
* @see ActiveXComponent
* @see ActiveXDisplayComponent
* @see ActiveXDispatchableImpl
* @see ActiveXDefaultComponentImpl
* @see BeanXporter
*/
public interface ActiveXDispatchable extends ActiveXRuntimeConstants {
  
  /** Get the <code>ActiveXProxy</code> object which is managing
  * the automation calls for this interface.
  */
  public ActiveXProxy getActiveXProxy();

  /** Get the integer which is passed to <code>ActiveXProxy</code>
  * for each automation call.  Normally this integer will represent an
  * <code>IDispatch</code> interface that is being managed by
  * JavaContainer.dll but that is not a requirement of this 
  * specification.  When the dispatch pointer does not exist
  * this should return ActiveXRuntimeConstants.AX_NO_DISPATCH.
  */
  public int getDispatchPointer();

  /**  Get the dispatch pointer to be used with a particular
  * ActiveXProxy.  An implementation of this will perform
  * any required marshalling to make sure that the dispatch 
  * pointer can be used by the specified proxy.
  */
  public int getDispatchPointer(ActiveXProxy proxy);

  /** Invoke a method using its name, passing in the required arguments
  * in a Vector.  This method uses the ActiveXRuntimeConstants.AX_INVOKE 
  * dispatch type and does not use the voidReturn optimization.
  */
  public Variant axInvoke(String methodName,
                          Vector args) 
                          throws ActiveXException;

  /** Invoke a method or property using its name, specifying 
  * the type of dispatch to use, whether the method is expected 
  * to return nothing, and passing in the required arguments in
  * a Vector.
  *<p>
  * The dispatch type is specified by an integer flag. 
  * The available dispatch types are specified by the following
  * constants:
  * <ul>
  * <li> ActiveXRuntimeConstants.AX_INVOKE
  * <li> ActiveXRuntimeConstants.AX_PROPERTYGET
  * <li> ActiveXRuntimeConstants.AX_PROPERTYSET
  * </ul>
  * The voidReturn flag allows the ActiveXProxy to optimize how the
  * automation call is made. 
  */
  public Variant axInvoke(String methodName,
                          int dispatchType,
                          boolean voidReturn,
                          Vector args)
                          throws ActiveXException;

  /** Invoke a method using a memid integer,
  * and passing in the required arguments in a Vector.
  *<p>
  * The memid integer can be derived by reading a type library.
  */
  public Variant axInvoke(int memid,
                          Vector args) 
                          throws ActiveXException;


  /** Invoke a method or property using its memid. and specifying 
  * the type of dispatch to use, whether the method is expected 
  * to return nothing, and passing in the required arguments in
  * a Vector.
  *<p>
  * The dispatch type is specified by an integer flag. 
  * The available dispatch types are specified by the following
  * final constants:
  * <ul>
  * <li> ActiveXRuntimeConstants.AX_INVOKE
  * <li> ActiveXRuntimeConstants.AX_PROPERTYGET
  * <li> ActiveXRuntimeConstants.AX_PROPERTYSET
  * </ul>
  * The voidReturn flag allows the ActiveXProxy to optimize how the
  * automation call is made. 
  *<p>
  * The memid integer can be derived by reading a type library.
  */
  public Variant axInvoke(int memid,
                          int dispatchType,
                          boolean voidReturn,
                          Vector args)
                          throws ActiveXException;


  /** Get a simple property using the name of the property. This method
  * is a convenience for properties that do not require any
  * arguments.  The dipstach type used by this method is
  * ActiveXRuntimeConstants.AX_PROPERTYGET.
  *<p>
  * This method is equivalent to:<br>
  * <code> axInvoke(propertyName, AX_PROPERTYHGET, false, null)</code>
  */
  public Variant getAxProperty(String propertyName)
                              throws ActiveXException;


  /** Get a simple property using the memid of the property. This method
  * is a convenience for properties that do not require any
  * arguments.  The dipstach type used by this method is
  * ActiveXRuntimeConstants.AX_PROPERTYGET.
  *<p>
  * This method is equivalent to:<br>
  * <code> axInvoke(memid, AX_PROPERTYHGET, false, null)</code>
  * <p>
  * The memid integer can be derived by reading a type library.
  */
  public Variant getAxProperty(int memid)
                              throws ActiveXException;

  /** Set a simple property using the name of the property. This method
  * is a convenience for properties that can be set with one
  * argument.  The dipstach type used by this method is
  * ActiveXRuntimeConstants.AX_PROPERTYSET.
  */
  public void setAxProperty(String propertyName,
                            Variant newValue)
                            throws ActiveXException;

 /** Set a simple property using the memid of the property. This method
  * is a convenience for properties that can be set with one
  * argument.  The dipstach type used by this method is
  * ActiveXRuntimeConstants.AX_PROPERTYSET.
  *<p>
  * The memid integer can be derived by reading a type library.
  */
  public void setAxProperty(int memid,
                            Variant newValue)
                            throws ActiveXException;

}
