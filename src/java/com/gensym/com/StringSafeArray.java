/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.StringSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>StringSafeArray</code> is a representation in Java of a
* SAFEARRAY of ActiveX IDL type BSTR.  It must be put in a <code>Variant</code>
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
public class StringSafeArray extends SafeArray implements ActiveXRuntimeConstants {

  /** Constructs an StringSafeArray from an array of string values. */
  public StringSafeArray(String values[]) {
    super(AX_BSTR, values.length);

    int indexes[] = {0};
    setStrings(indexes, values);
  }

  /** Constructs an empty multi dimensional StringSafeArray. */
  public StringSafeArray(int lBounds[], int uBounds[]) {
    super(AX_BSTR, lBounds, uBounds);
  }

  /** Constructs an empty single dimension StringSafeArray. */
  public StringSafeArray(int length) {
    super(AX_BSTR, length);
  }

  /** Constructs an StringSafeArray from another StringSafeArray. */
  public StringSafeArray(StringSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  StringSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_STRING;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new StringSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional StringSafeArray. */
  public void setStrings(int indexes[], String strings[]){
     putElements(indexes, strings);
  }

  /** Sets one element in a single dimension StringSafeArray. <p>
      Note: This can be used on a multi dimensional StringSafeArrays.
   */
  public void setString(int index, String value) {
    int indexes[] = {index};
    String strings[] = {value};

    putElements(indexes, strings);
  }

  /** Gets all of the elements of the StringSafeArray as an array of Strings. */
  public String[] getAllStrings() {
    return (String[])getAllElements();
  }

  /** Gets multiple elements of the StringSafeArray as an array of Strings. */
  public String[] getStrings(int indexes[], int n) {
    return (String[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension StringSafeArray. <p>
      Note: This can be used on a multi dimensional StringSafeArrays.
   */
  public String getString(int index) {
    int indexes[] = {index};
    String strings[] = null;

    strings = (String[])getElements(indexes, 1);
    if (strings == null)
      return null;

    return strings[0];
  }

  @Override
  public String toString() {
    String strings[];
    int i;
    String bigString;

    strings = getAllStrings();
    if ((strings == null) || (strings.length == 0)) {
      return "{}";
    }

    bigString = "{\"" + strings[0] + "\"";
    for (i = 1; i < strings.length ; i++)
      bigString = bigString + ", \"" + strings[i] + "\"";

    bigString = bigString + "}";
    return bigString;
  }
}
