/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.SARefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>SARefParameter</code> is the Java representation for
* the ActiveX IDL type SAFEARRAY *. When a subclass of this class is used as a
* parameter to an exported bean's method, the contained value
* is copied into a temporary native memory location and the address of
* that location is used as the parameter to the native ActiveX method. After
* the native method returns, the contained value is set to the contents
* of the native location.
*/
public abstract class SARefParameter implements ActiveXRuntimeConstants {

  private SafeArray sa;

  /** Set the input SafeArray. */
  void setSafeArray(SafeArray array) {
    sa = array;
  }

  /** Get the output SafeArray. */
  SafeArray getSafeArray() {
    return sa;
  } 

  /** Return the integer flag that indicates the type of the type of
  * safe array referenced.  The flags returned are defined in 
  * <code>ActiveXRuntimeConstants</code>
  */
  abstract short getType();
}
