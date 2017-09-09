/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.DoubleRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>DoubleRefParameter</code> is the Java representation for
* the ActiveX IDL type double* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class DoubleRefParameter implements Cloneable {

  private double value;

  /** Constructs an in/out DoubleRefParameter from a double value. */
  public DoubleRefParameter(double value) {
    setDouble(value);
  }

  /** Constructs an out DoubleRefParameter. */
  public DoubleRefParameter() {
  }

  /** Sets the input double for the DoubleRefParameter. */
  public void setDouble(double value) {
    this.value = value;
  }

  /** Gets the output double of a DoubleRefParameter. */
  public double getDouble() {
    return value;
  }

  @Override
  public String toString() {
    return "DoubleRef = " + value;
  }
}
