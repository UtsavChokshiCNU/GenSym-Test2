/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ShortRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>ShortRefParameter</code> is the Java representation for
* the ActiveX IDL type short* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class ShortRefParameter implements Cloneable {

  private short value;

  /** Constructs an in/out ShortRefParameter from a short value. */
  public ShortRefParameter(short value) {
    setShort(value);
  }

  /** Constructs an out ShortRefParameter. */
  public ShortRefParameter() {
  }

  /** Sets the input short for the ShortRefParameter. */
  public void setShort(short value) {
    this.value = value;
  }

  /** Gets the output short of a ShortRefParameter. */
  public short getShort() {
    return value;
  }

  @Override
  public String toString() {
    return "ShortRef = " + value;
  }
}
