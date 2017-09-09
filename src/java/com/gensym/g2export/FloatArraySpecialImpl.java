/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      FloatArraySpecialImpl.java
 *
 *      Author: Gensym Corp.
 *
 */


package com.gensym.g2export;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public class FloatArraySpecialImpl extends QuantityArraySpecialImpl {
  
  protected java.lang.Object internalArray;

  /**
   * This methods will return the internal array, or create one
   * if internalArray is null. This method should be overridden
   * to ensure that each subclass of G2Array creates the correct type
   * of array.
   */
  @Override
  protected java.lang.Object getInternalArray(int size) {
    if (internalArray == null)
      internalArray = new double[size];

    return internalArray;
  }
}
