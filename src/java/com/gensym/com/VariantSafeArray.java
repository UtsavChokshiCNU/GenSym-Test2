/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.VariantSafeArray.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>VariantSafeArray</code> is a representation in Java of a
* SAFEARRAY of ActiveX IDL type VARIANT.  It must be put in a
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
public class VariantSafeArray extends SafeArray implements
    ActiveXRuntimeConstants {

  /** Constructs an VariantSafeArray from an array of variant values. */
  public VariantSafeArray(Variant values[]) {
    super(AX_VARIANT, values.length);

    int indexes[] = {0};
    setVariants(indexes, values);
  }

  /** Constructs an empty multi dimensional VariantSafeArray. */
  public VariantSafeArray(int lBounds[], int uBounds[]) {
    super(AX_VARIANT, lBounds, uBounds);
  }

  /** Constructs an empty single dimension VariantSafeArray. */
  public VariantSafeArray(int length) {
    super(AX_VARIANT, length);
  }

  /** Constructs an VariantSafeArray from another VariantSafeArray. */
  public VariantSafeArray(VariantSafeArray array) {
    super(array);
  }

  /** @undocumented
  * The native code will use this when an ActiveX method returns an
  * SafeArray of this type. We need a dummy parameter to avoid conflicting
  * with another constructor.
  */
  VariantSafeArray(int arrayHandle, byte dummy) {
    super(arrayHandle);
  }

  /** @undocumented Overrides SafeArray.getType */
  @Override
  short getType() {
    return AX_VARIANT;
  }

  /** @undocumented Overrides SafeArray.clone*/
  @Override
  public Object clone() {
    return new VariantSafeArray(this);
  }

  /** Sets multiple elements in a single or multi dimensional VariantSafeArray. */
  public void setVariants(int indexes[], Variant variants[]){
     putElements(indexes, variants);
  }

  /** Sets one element in a single dimension VariantSafeArray. <p>
      Note: This can be used on a multi dimensional VariantSafeArrays.
   */
  public void setVariant(int index, Variant value) {
    int indexes[] = {index};
    Variant variants[] = {value};

    putElements(indexes, variants);
  }

  /** Gets all of the elements of the VariantSafeArray as an array of Variants. */
  public Variant[] getAllVariants() {
    return (Variant[])getAllElements();
  }

  /** Gets multiple elements of the VariantSafeArray as an array of Variants. */
  public Variant[] getVariants(int indexes[], int n) {
    return (Variant[])getElements(indexes, n);
  }

  /** Gets one element of a single dimension VariantSafeArray. <p>
      Note: This can be used on a multi dimensional VariantSafeArrays.
   */
  public Variant getVariant(int index) {
    int indexes[] = {index};
    Variant variants[] = null;

    variants = (Variant[])getElements(indexes, 1);
    if (variants == null)
      return null;

    return variants[0];
  }

  @Override
  public String toString() {
    Variant variants[];
    int i;
    String bigString;

    variants = getAllVariants();
    if ((variants == null) || (variants.length == 0)) {
      return "{}";
    }

    bigString = "{" + variants[0];
    for (i = 1; i < variants.length ; i++)
      bigString = bigString + ", " + variants[i];

    bigString = bigString + "}";
    return bigString;
  }
}
