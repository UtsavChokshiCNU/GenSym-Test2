/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ParameterVector.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

import java.util.*;

/* This class lets us provide special handling of generic types of
   parameters without generating special at export time. The first special
   case is for an array of Variants, which we break up into single
   parameters. This emulates Visual Basic handling of variable arguments. */
public class ParameterVector extends Vector {

  /* This is the only constructor of Vector we need to inherit. */
  public ParameterVector(int initialCapacity) {
    super(initialCapacity);
  }

  /* This is the catch-all method for the types we do not support */
  public void addParameter(Object value) {
    super.addElement(new Variant(value));
  }

  /* This method is for vararg methods */
  public void addParameter(Variant[] variants) {
    int length;
    int i;

    length = variants.length;
    for (i = 0; i < length; i++) {
      addElement(variants[i]);
    }
  }
  
  /* We need one addParameter method per supported VARIANTARG type. */

  public void addParameter(short value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(int value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(float value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(double value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(Date value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(String value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(ActiveXDispatchable value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(boolean value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(Variant value) {
    super.addElement(value);
  }

  public void addParameter(byte value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(ShortRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(IntRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(FloatRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(DoubleRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(DateRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(StringRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(ActiveXDispatchableRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(BooleanRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(VariantRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(ByteRefParameter value) {
    super.addElement(new Variant(value));
  }

  public void addParameter(SARefParameter value) {
    super.addElement(new Variant(value));
  }
}

