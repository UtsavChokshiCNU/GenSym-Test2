/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.IntSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>IntSafeArray</code> is a representation in Java of a
* SAFEARRAY of ActiveX IDL type long.  It must be put in a <code>Variant</code>
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
public class IntSafeArray extends SafeArray implements ActiveXRuntimeConstants {

  /** Constructs an IntSafeArray from an array of int values. */
  public IntSafeArray(int values[]) {
    super(AX_I4, values.length);

    int indexes[] = {0};
    setInts(indexes, values);
  }

  /** Constructs an empty multi dimensional IntSafeArray. */
  public IntSafeArray(int lBounds[], int uBounds[]) {
    super(AX_I4, lBounds, uBounds);
  }

  /** Constructs an empty single dimension IntSafeArray. */
  public IntSafeArray(int length) {
    super(AX_I4, length);
  }

  /** Constructs an IntSafeArray from another IntSafeArray. */
  public IntSafeArray(IntSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  IntSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_I4;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new IntSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional IntSafeArray. */
  public void setInts(int indexes[], int ints[]){
     putElements(indexes, ints);
  }

  /** Sets one element in a single dimension IntSafeArray. <p>
      Note: This can be used on a multi dimensional IntSafeArrays.
   */
  public void setInt(int index, int value) {
    int indexes[] = {index};
    int ints[] = {value};

    putElements(indexes, ints);
  }

  /** Gets all of the elements of the IntSafeArray as an array of Ints. */
  public int[] getAllInts() {
    return (int[])getAllElements();
  }

  /** Gets multiple elements of the IntSafeArray as an array of Ints. */
  public int[] getInts(int indexes[], int n) {
    return (int[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension IntSafeArray. <p>
      Note: This can be used on a multi dimensional IntSafeArrays.
   */
  public int getInt(int index) {
    int indexes[] = {index};
    int ints[] = null;

    ints = (int[])getElements(indexes, 1);
    if (ints == null)
      return -1;

    return ints[0];
  }

  @Override
  public String toString() {
    int ints[];
    int i;
    String bigString;

    ints = getAllInts();
    if ((ints == null) || (ints.length == 0)) {
      return "{}";
    }

    bigString = "{" + ints[0];
    for (i = 1; i < ints.length ; i++)
      bigString = bigString + ", " + ints[i];

    bigString = bigString + "}";
    return bigString;
  }
}
