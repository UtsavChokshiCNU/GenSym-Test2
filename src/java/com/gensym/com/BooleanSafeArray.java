/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.BooleanSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>BooleanSafeArray</code> is a representation in Java of a
* SAFEARRAY of ActiveX IDL type VARIANT_BOOL. It must be put in a
* <code>Variant</code> when passing array data to and from ActiveX.<p>
* Some methods take bounds or index parameters as arrays, where each element
* of the arrays corresponds to a dimension of a multi-dimensional safe
* array.<p>
* When getting more than one element of a multi-dimensional safe array the
* elements will be returned as a single dimensioned array with the elements
* in column-major order. For example getting all the elements of a [2][3] array
* would yield an array of elements stored in this order: 
*          [0,0], [1,0], [0,1], [1,1], [0,2], [1,2] 
*/
public class BooleanSafeArray extends SafeArray implements
  ActiveXRuntimeConstants {

  /** Constructs an BooleanSafeArray from an array of boolean values. */
  public BooleanSafeArray(boolean values[]) {
    super(AX_BOOL, values.length);

    int indexes[] = {0};
    setBooleans(indexes, values);
  }

  /** Constructs an empty multi dimensional BooleanSafeArray. */
  public BooleanSafeArray(int lBounds[], int uBounds[]) {
    super(AX_BOOL, lBounds, uBounds);
  }

  /** Constructs an empty single dimension BooleanSafeArray. */
  public BooleanSafeArray(int length) {
    super(AX_BOOL, length);
  }

  /** Constructs an BooleanSafeArray from another BooleanSafeArray. */
  public BooleanSafeArray(BooleanSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  BooleanSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_BOOL;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new BooleanSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional BooleanSafeArray. */
  public void setBooleans(int indexes[], boolean booleans[]){
     putElements(indexes, booleans);
  }

  /** Sets one element in a single dimension BooleanSafeArray. <p>
      Note: This can be used on a multi dimensional BooleanSafeArrays.
   */
  public void setBoolean(int index, boolean value) {
    int indexes[] = {index};
    boolean booleans[] = {value};

    putElements(indexes, booleans);
  }

  /** Gets all of the elements of the BooleanSafeArray as an array of Booleans. */
  public boolean[] getAllBooleans() {
    return (boolean[])getAllElements();
  }

  /** Gets multiple elements of the BooleanSafeArray as an array of Booleans. */
  public boolean[] getBooleans(int indexes[], int n) {
    return (boolean[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension BooleanSafeArray. <p>
      Note: This can be used on a multi dimensional BooleanSafeArrays.
   */
  public boolean getBoolean(int index) {
    int indexes[] = {index};
    boolean booleans[] = null;

    booleans = (boolean[])getElements(indexes, 1);
    if (booleans == null)
      return false;

    return booleans[0];
  }

  @Override
  public String toString() {
    boolean booleans[];
    int i;
    String bigString;

    booleans = getAllBooleans();
    if ((booleans == null) || (booleans.length == 0)) {
      return "{}";
    }

    bigString = "{" + booleans[0];
    for (i = 1; i < booleans.length ; i++)
      bigString = bigString + ", " + booleans[i];

    bigString = bigString + "}";
    return bigString;
  }
}
