/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.DateRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

import java.util.*;

/** The class <code>DateRefParameter</code> is the Java representation for
* the ActiveX IDL type DATE* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class DateRefParameter implements Cloneable {

  private Date value;

  /** Constructs an in/out DateRefParameter from a date value. */
  public DateRefParameter(Date value) {
    setDate(value);
  }

  /** Constructs an out DateRefParameter. */
  public DateRefParameter() {
    /* Dates are really a primitive type and can't be null. */
    value = new Date();
  }

  /** Sets the input date for the DateRefParameter. */
  public void setDate(Date value) {
    this.value = value;

    /* Dates are really a primitive type and can't be null. */
    if (this.value == null)
      this.value = new Date();
  }

  /** Gets the output date of a DateRefParameter. */
  public Date getDate() {
    return value;
  }

  @Override
  public String toString() {
    return "DateRef = " + value.toString();
  }

  /** @undocumented The native code will call this to get the number of
   * seconds since 1970.
   */
  public long getDateSecondsValue () {
    if (value == null)
        return 0;

    return value.getTime();
  }
}
