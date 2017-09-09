/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ByteSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>ByteSafeArray</code> is a representation in Java of a
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
public class ByteSafeArray extends SafeArray implements ActiveXRuntimeConstants {

  /** Constructs an ByteSafeArray from an array of byte values. */
  public ByteSafeArray(byte values[]) {
    super(AX_UI1, values.length);

    int indexes[] = {0};
    setBytes(indexes, values);
  }

  /** Constructs an empty multi dimensional ByteSafeArray. */
  public ByteSafeArray(int lBounds[], int uBounds[]) {
    super(AX_UI1, lBounds, uBounds);
  }

  /** Constructs an empty single dimension ByteSafeArray. */
  public ByteSafeArray(int length) {
    super(AX_UI1, length);
  }

  /** Constructs an ByteSafeArray from another ByteSafeArray. */
  public ByteSafeArray(ByteSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  ByteSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_UI1;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new ByteSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional ByteSafeArray. */
  public void setBytes(int indexes[], byte bytes[]){
     putElements(indexes, bytes);
  }

  /** Sets one element in a single dimension ByteSafeArray. <p>
      Note: This can be used on a multi dimensional ByteSafeArrays.
   */
  public void setByte(int index, byte value) {
    int indexes[] = {index};
    byte bytes[] = {value};

    putElements(indexes, bytes);
  }

  /** Gets all of the elements of the ByteSafeArray as an array of Bytes. */
  public byte[] getAllBytes() {
    return (byte[])getAllElements();
  }

  /** Gets multiple elements of the ByteSafeArray as an array of Bytes. */
  public byte[] getBytes(int indexes[], int n) {
    return (byte[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension ByteSafeArray. <p>
      Note: This can be used on a multi dimensional ByteSafeArrays.
   */
  public byte getByte(int index) {
    int indexes[] = {index};
    byte bytes[] = null;

    bytes = (byte[])getElements(indexes, 1);
    if (bytes == null)
      return -1;

    return bytes[0];
  }

  @Override
  public String toString() {
    byte bytes[];
    int i;
    String bigString;

    bytes = getAllBytes();
    if ((bytes == null) || (bytes.length == 0)) {
      return "{}";
    }

    bigString = "{" + bytes[0];
    for (i = 1; i < bytes.length ; i++)
      bigString = bigString + ", " + bytes[i];

    bigString = bigString + "}";
    return bigString;
  }
}
