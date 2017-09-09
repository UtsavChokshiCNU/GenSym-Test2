/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXDispatchableRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>ActiveXDispatchableRefParameter</code> is the Java
* representation for the ActiveX IDL type IDispatch** used for [out] or
* [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class ActiveXDispatchableRefParameter implements Cloneable,
  ActiveXRuntimeConstants {

  private ActiveXDispatchable value;

  /** Constructs an in/out ActiveXDispatchableRefParameter from a
  * ActiveXDispatchable value.
  */
  public ActiveXDispatchableRefParameter(ActiveXDispatchable value) {
    setActiveXDispatchable(value);
  }

  /** Constructs an out ActiveXDispatchableRefParameter. */
  public ActiveXDispatchableRefParameter() {
  }

  /** Sets the input ActiveXDispatchable for the
  * ActiveXDispatchableRefParameter.
  */
  public void setActiveXDispatchable(ActiveXDispatchable value) {
    this.value = value;
  }

  /** Gets the output ActiveXDispatchable of a
  * ActiveXDispatchableRefParameter.
  */
  public ActiveXDispatchable getActiveXDispatchable() {
    return value;
  }

  @Override
  public String toString() {
    if (value == null)
      return "ActiveXDispatchableRef = null";

    return "ActiveXDispatchableRef = " + value.toString();
  }

  /** @undocumented, Constructor for the native code to use.
  * Needs a dispatch pointer and an ActiveXProxy.
  */
  public ActiveXDispatchableRefParameter (int value, ActiveXProxy oleObject) {
    setActiveXDispatchable(value, oleObject);
  }

  /** @undocumented  The native code calls this to set the output
  * ActiveXDispatchable value for the ActiveXDispatchableRefParameter.
  */
  public void setActiveXDispatchable (int value, ActiveXProxy oleObject) {
    setActiveXDispatchable(new ActiveXDispatchableImpl(value, oleObject));
  }

  /**
  * @undocumented
  * The native code will this method to get the input dispatch
  * pointer.
  */
  public int getDispatchPointer(ActiveXProxy proxy) 
  {
    if (value == null)
      return AX_NO_DISPATCH;

    return value.getDispatchPointer(proxy);
  }

  /**
  * @undocumented
  * The native code will this method to get the input dispatch
  * pointer.
  */
  public int getDispatchPointer() 
  {
    if (value == null)
      return AX_NO_DISPATCH;

    return value.getDispatchPointer();
  }
}
