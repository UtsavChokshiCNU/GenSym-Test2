/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.VariantRefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>VariantRefParameter</code> is the Java representation for
* the ActiveX IDL type VARIANT* used for [out] or [in/out] parameters.<p>
* When used as a parameter to an exported bean's method, the contained value
* will be copied into a temporary native memory location and address of that
* location used as the parameter to the native ActiveX method. After the
* native method returns the contained value will be set to the contents of the
* native location.
*/
public class VariantRefParameter implements Cloneable {

  private Variant value;

  /** Constructs an in/out VariantRefParameter from a variant value. */
  public VariantRefParameter(Variant value) {
    setVariant(value);
  }

  /** Constructs an out VariantRefParameter. */
  public VariantRefParameter() {
    /* Variants are really a primitive type and can't be null. */
    value = new Variant();
  }

  /** Sets the input variant for the VariantRefParameter. */
  public void setVariant(Variant value) {
    this.value = value;

    /* Variants are really a primitive type and can't be null. */
    if (this.value == null)
      this.value = new Variant();
  }

  /** Gets the output variant of a VariantRefParameter. */
  public Variant getVariant() {
    return value;
  }

  @Override
  public String toString() {
    return "VariantRef = " + value.toString();
  }
}
