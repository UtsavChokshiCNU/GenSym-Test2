/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.BooleanRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>BooleanRefParameter</code> is the Java representation for
* the ActiveX IDL type VARIANT_BOOL* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class BooleanRefParameter implements Cloneable {

  private boolean value;

  /** Constructs an in/out BooleanRefParameter from a boolean value. */
  public BooleanRefParameter(boolean value) {
    setBoolean(value);
  }

  /** Constructs an out BooleanRefParameter. */
  public BooleanRefParameter() {
  }

  /** Sets the input boolean for the BooleanRefParameter. */
  public void setBoolean(boolean value) {
    this.value = value;
  }

  /** Gets the output boolean of a BooleanRefParameter. */
  public boolean getBoolean() {
    return value;
  }

  @Override
  public String toString() {
    return "BooleanRef = " + value;
  }
}
