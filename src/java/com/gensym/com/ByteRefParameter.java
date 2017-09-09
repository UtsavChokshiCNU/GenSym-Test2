/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ByteRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>ByteRefParameter</code> is the Java representation for
* the ActiveX IDL type unsigned char* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class ByteRefParameter implements Cloneable {

  private byte value;

  /** Constructs an in/out ByteRefParameter from a byte value. */
  public ByteRefParameter(byte value) {
    setByte(value);
  }

  /** Constructs an out ByteRefParameter. */
  public ByteRefParameter() {
  }

  /** Sets the input byte for the ByteRefParameter. */
  public void setByte(byte value) {
    this.value = value;
  }

  /** Gets the output byte of a ByteRefParameter. */
  public byte getByte() {
    return value;
  }

  @Override
  public String toString() {
    return "ByteRef = " + value;
  }
}
