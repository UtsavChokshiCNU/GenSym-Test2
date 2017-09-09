/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.IntRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>IntRefParameter</code> is the Java representation for
* the ActiveX IDL type long* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class IntRefParameter implements Cloneable {

  private int value;

  /** Constructs an in/out IntRefParameter from a int value. */
  public IntRefParameter(int value) {
    setInt(value);
  }

  /** Constructs an out IntRefParameter. */
  public IntRefParameter() {
  }

  /** Sets the input int for the IntRefParameter. */
  public void setInt(int value) {
    this.value = value;
  }

  /** Gets the output int of a IntRefParameter. */
  public int getInt() {
    return value;
  }

  @Override
  public String toString() {
    return "IntRef = " + value;
  }
}
