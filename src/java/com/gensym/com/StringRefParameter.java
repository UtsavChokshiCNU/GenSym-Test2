/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.StringRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>StringRefParameter</code> is the Java representation for
* the ActiveX IDL type BSTR* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class StringRefParameter implements Cloneable {

  private String value;

  /** Constructs an in/out StringRefParameter from a string value. */
  public StringRefParameter(String value) {
    setString(value);
  }

  /** Constructs an out StringRefParameter. */
  public StringRefParameter() {
  }

  /** Sets the input string for the StringRefParameter. */
  public void setString(String value) {
    this.value = value;
  }

  /** Gets the output string of a StringRefParameter. */
  public String getString() {
    return value;
  }

  @Override
  public String toString() {
    if (value == null)
      return "StringRef = null";

    return "StringRef = " + value.toString();
  }
}
