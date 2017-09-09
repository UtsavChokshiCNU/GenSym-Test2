/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.DoubleSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>DoubleSafeArray</code> is a representation in Java of a
* SAFEARRAY of ActiveX IDL type double. It must be put in a
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
public class DoubleSafeArray extends SafeArray implements ActiveXRuntimeConstants {

  /** Constructs an DoubleSafeArray from an array of double values. */
  public DoubleSafeArray(double values[]) {
    super(AX_R8, values.length);

    int indexes[] = {0};
    setDoubles(indexes, values);
  }

  /** Constructs an empty multi dimensional DoubleSafeArray. */
  public DoubleSafeArray(int lBounds[], int uBounds[]) {
    super(AX_R8, lBounds, uBounds);
  }

  /** Constructs an empty single dimension DoubleSafeArray. */
  public DoubleSafeArray(int length) {
    super(AX_R8, length);
  }

  /** Constructs an DoubleSafeArray from another DoubleSafeArray. */
  public DoubleSafeArray(DoubleSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  DoubleSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_R8;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new DoubleSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional DoubleSafeArray. */
  public void setDoubles(int indexes[], double doubles[]){
     putElements(indexes, doubles);
  }

  /** Sets one element in a single dimension DoubleSafeArray. <p>
      Note: This can be used on a multi dimensional DoubleSafeArrays.
   */
  public void setDouble(int index, double value) {
    int indexes[] = {index};
    double doubles[] = {value};

    putElements(indexes, doubles);
  }

  /** Gets all of the elements of the DoubleSafeArray as an array of Doubles. */
  public double[] getAllDoubles() {
    return (double[])getAllElements();
  }

  /** Gets multiple elements of the DoubleSafeArray as an array of Doubles. */
  public double[] getDoubles(int indexes[], int n) {
    return (double[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension DoubleSafeArray. <p>
      Note: This can be used on a multi dimensional DoubleSafeArrays.
   */
  public double getDouble(int index) {
    int indexes[] = {index};
    double doubles[] = null;

    doubles = (double[])getElements(indexes, 1);
    if (doubles == null)
      return -1;

    return doubles[0];
  }

  @Override
  public String toString() {
    double doubles[];
    int i;
    String bigString;

    doubles = getAllDoubles();
    if ((doubles == null) || (doubles.length == 0)) {
      return "{}";
    }

    bigString = "{" + doubles[0];
    for (i = 1; i < doubles.length ; i++)
      bigString = bigString + ", " + doubles[i];

    bigString = bigString + "}";
    return bigString;
  }
}
