/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ShortSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>ShortSafeArray</code> is a representation in Java of a
* SAFEARRAY of ActiveX IDL type short. It must be put in a <code>Variant</code>
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
public class ShortSafeArray extends SafeArray implements ActiveXRuntimeConstants {

  /** Constructs an ShortSafeArray from an array of short values. */
  public ShortSafeArray(short values[]) {
    super(AX_I2, values.length);

    int indexes[] = {0};
    setShorts(indexes, values);
  }

  /** Constructs an empty multi dimensional ShortSafeArray. */
  public ShortSafeArray(int lBounds[], int uBounds[]) {
    super(AX_I2, lBounds, uBounds);
  }

  /** Constructs an empty single dimension ShortSafeArray. */
  public ShortSafeArray(int length) {
    super(AX_I2, length);
  }

  /** Constructs an ShortSafeArray from another ShortSafeArray. */
  public ShortSafeArray(ShortSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  ShortSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_I2;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new ShortSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional ShortSafeArray. */
  public void setShorts(int indexes[], short shorts[]){
     putElements(indexes, shorts);
  }

  /** Sets one element in a single dimension ShortSafeArray. <p>
      Note: This can be used on a multi dimensional ShortSafeArrays.
   */
  public void setShort(int index, short value) {
    int indexes[] = {index};
    short shorts[] = {value};

    putElements(indexes, shorts);
  }

  /** Gets all of the elements of the ShortSafeArray as an array of Shorts. */
  public short[] getAllShorts() {
    return (short[])getAllElements();
  }

  /** Gets multiple elements of the ShortSafeArray as an array of Shorts. */
  public short[] getShorts(int indexes[], int n) {
    return (short[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension ShortSafeArray. <p>
      Note: This can be used on a multi dimensional ShortSafeArrays.
   */
  public short getShort(int index) {
    int indexes[] = {index};
    short shorts[] = null;

    shorts = (short[])getElements(indexes, 1);
    if (shorts == null)
      return -1;

    return shorts[0];
  }

  @Override
  public String toString() {
    short shorts[];
    int i;
    String bigString;

    shorts = getAllShorts();
    if ((shorts == null) || (shorts.length == 0)) {
      return "{}";
    }

    bigString = "{" + shorts[0];
    for (i = 1; i < shorts.length ; i++)
      bigString = bigString + ", " + shorts[i];

    bigString = bigString + "}";
    return bigString;
  }
}
