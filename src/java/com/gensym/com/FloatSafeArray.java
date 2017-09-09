/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.FloatSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>FloatSafeArray</code> is a representation in Java of a
* SAFEARRAY of ActiveX IDL type float. It must be put in a <code>Variant</code>
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
public class FloatSafeArray extends SafeArray implements ActiveXRuntimeConstants {

  /** Constructs an FloatSafeArray from an array of float values. */
  public FloatSafeArray(float values[]) {
    super(AX_R4, values.length);

    int indexes[] = {0};
    setFloats(indexes, values);
  }

  /** Constructs an empty multi dimensional FloatSafeArray. */
  public FloatSafeArray(int lBounds[], int uBounds[]) {
    super(AX_R4, lBounds, uBounds);
  }

  /** Constructs an empty single dimension FloatSafeArray. */
  public FloatSafeArray(int length) {
    super(AX_R4, length);
  }

  /** Constructs an FloatSafeArray from another FloatSafeArray. */
  public FloatSafeArray(FloatSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  FloatSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_R4;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new FloatSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional FloatSafeArray. */
  public void setFloats(int indexes[], float floats[]){
     putElements(indexes, floats);
  }

  /** Sets one element in a single dimension FloatSafeArray. <p>
      Note: This can be used on a multi dimensional FloatSafeArrays.
   */
  public void setFloat(int index, float value) {
    int indexes[] = {index};
    float floats[] = {value};

    putElements(indexes, floats);
  }

  /** Gets all of the elements of the FloatSafeArray as an array of Floats. */
  public float[] getAllFloats() {
    return (float[])getAllElements();
  }

  /** Gets multiple elements of the FloatSafeArray as an array of Floats. */
  public float[] getFloats(int indexes[], int n) {
    return (float[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension FloatSafeArray. <p>
      Note: This can be used on a multi dimensional FloatSafeArrays.
   */
  public float getFloat(int index) {
    int indexes[] = {index};
    float floats[] = null;

    floats = (float[])getElements(indexes, 1);
    if (floats == null)
      return -1;

    return floats[0];
  }

  @Override
  public String toString() {
    float floats[];
    int i;
    String bigString;

    floats = getAllFloats();
    if ((floats == null) || (floats.length == 0)) {
      return "{}";
    }

    bigString = "{" + floats[0];
    for (i = 1; i < floats.length ; i++)
      bigString = bigString + ", " + floats[i];

    bigString = bigString + "}";
    return bigString;
  }
}
