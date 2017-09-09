/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.DateSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

import java.util.Date;

/** The class <code>DateSafeArray</code> is a representation in Java of a
* SAFEARRAY of ActiveX IDL type DATE.  It must be put in a <code>Variant</code>
* when passing array data to and from ActiveX.<p>
* Some methods take bounds or index parameters as arrays, where each element
* of the arrays corresponds to a dimension of a multi-dimensional safe
* array.<p>
* When getting more than one element of a multi-dimensional safe array the
* elements will be returned as a single dimensioned array with the elements
* in column-major order. For example getting all the elements of a [2][3] array
* would yield an array of elements stored in this order: 
*          [0,0], [1,0], [0,1], [1,1], [0,2], [1,2] 
*/
public class DateSafeArray extends SafeArray implements ActiveXRuntimeConstants {

  /** Constructs an DateSafeArray from an array of date values. */
  public DateSafeArray(Date values[]) {
    super(AX_DATE, values.length);

    int indexes[] = {0};
    setDates(indexes, values);
  }

  /** Constructs an empty multi dimensional DateSafeArray. */
  public DateSafeArray(int lBounds[], int uBounds[]) {
    super(AX_DATE, lBounds, uBounds);
  }

  /** Constructs an empty single dimension DateSafeArray. */
  public DateSafeArray(int length) {
    super(AX_DATE, length);
  }

  /** Constructs an DateSafeArray from another DateSafeArray. */
  public DateSafeArray(DateSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  DateSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_DATE;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new DateSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional DateSafeArray. */
  public void setDates(int indexes[], Date dates[]){
     putElements(indexes, dates);
  }

  /** Sets one element in a single dimension DateSafeArray. <p>
      Note: This can be used on a multi dimensional DateSafeArrays.
   */
  public void setDate(int index, Date value) {
    int indexes[] = {index};
    Date dates[] = {value};

    putElements(indexes, dates);
  }

  /** Gets all of the elements of the DateSafeArray as an array of Dates. */
  public Date[] getAllDates() {
    return (Date[])getAllElements();
  }

  /** Gets multiple elements of the DateSafeArray as an array of Dates. */
  public Date[] getDates(int indexes[], int n) {
    return (Date[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension DateSafeArray. <p>
      Note: This can be used on a multi dimensional DateSafeArrays.
   */
  public Date getDate(int index) {
    int indexes[] = {index};
    Date dates[] = null;

    dates = (Date[])getElements(indexes, 1);
    if (dates == null)
      return null;

    return dates[0];
  }

  @Override
  public String toString() {
    Date dates[];
    int i;
    String bigString;

    dates = getAllDates();
    if ((dates == null) || (dates.length == 0)) {
      return "{}";
    }

    bigString = "{" + dates[0];
    for (i = 1; i < dates.length ; i++)
      bigString = bigString + ", " + dates[i];

    bigString = bigString + "}";
    return bigString;
  }
}
