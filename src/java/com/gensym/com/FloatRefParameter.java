/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.FloatRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>FloatRefParameter</code> is the Java representation for
* the ActiveX IDL type float* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class FloatRefParameter implements Cloneable {

  private float value;

  /** Constructs an in/out FloatRefParameter from a float value. */
  public FloatRefParameter(float value) {
    setFloat(value);
  }

  /** Constructs an out FloatRefParameter. */
  public FloatRefParameter() {
  }

  /** Sets the input float for the FloatRefParameter. */
  public void setFloat(float value) {
    this.value = value;
  }

  /** Gets the output float of a FloatRefParameter. */
  public float getFloat() {
    return value;
  }

  @Override
  public String toString() {
    return "FloatRef = " + value;
  }
}
