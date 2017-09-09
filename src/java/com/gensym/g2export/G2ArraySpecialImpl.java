/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ArraySpecialImpl.java
 *
 *      Author: Gensym Corp.
 *
 */


package com.gensym.g2export;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.g2scriptruntime.G2ArrayAccess;

public class G2ArraySpecialImpl extends G2__BaseImpl 
     implements com.gensym.g2scriptruntime.G2ArrayAccess {
  
  protected java.lang.Object internalArray;

  /**
   * This methods will return the internal array, or create one
   * if internalArray is null. This method should be overridden
   * to ensure that each subclass of G2Array creates the correct type
   * of array.
   */
  protected java.lang.Object getInternalArray(int size) {
    if (internalArray == null)
      internalArray = new Object[size];
    
    return internalArray;
  }

  /**
   * f1
   */
  public int arrayLength;

  /**
   * 1
   */
  @Override
  public java.lang.Object getArray() {
    G2ArrayAccess g2Array = (G2ArrayAccess)_getCurrentSelf();
    if (this != g2Array){
      return g2Array.getArray();
    }
    return getInternalArray(arrayLength);
  }

  /**
   * 2
   */
  @Override
  public void  setArray(java.lang.Object array) {

    G2ArrayAccess g2Array = (G2ArrayAccess)_getCurrentSelf();    
    if (this != g2Array){
      g2Array.setArray(array);
      return;
    }
    
    internalArray = array;

    if (array instanceof int[])
      arrayLength = ((int[])array).length;
    else if (array instanceof double[])
     arrayLength = ((double[])array).length;
    else if (array instanceof String[])
      arrayLength = ((String[])array).length;
    else if (array instanceof com.gensym.util.Symbol[])
      arrayLength = ((com.gensym.util.Symbol[])array).length;
    else if (array instanceof boolean[])
      arrayLength = ((boolean[])array).length;
    else if (array instanceof java.lang.Object[])
      arrayLength = ((java.lang.Object[])array).length;
    else if (array instanceof java.lang.Number[])
      arrayLength = ((Number[])array).length; 
  }

  /**
   * 3
   */
  @Override
  public synchronized void setArrayLength(int size) {
    G2ArrayAccess g2Array = (G2ArrayAccess)_getCurrentSelf();
    if (this != g2Array){
      g2Array.setArrayLength(size);
      return;
    }
    arrayLength = size;
    if (internalArray == null)
      internalArray = getInternalArray(size);
    else if (size != arrayLength && size >= 0) {
      java.lang.Object oldArray = internalArray;
      internalArray = null; // force new array creation 
      java.lang.Object newArray = getInternalArray(size);
      System.arraycopy(oldArray, 0, newArray, 0, size);
    }
  }

  /**
   * 4
   */
  @Override
  public int getArrayLength() {
    G2ArrayAccess g2Array = (G2ArrayAccess)_getCurrentSelf();
    if (this != g2Array){
      return g2Array.getArrayLength();
    }
    // Force creation if array has not been created yet
    java.lang.Object array = getInternalArray(arrayLength);
    return arrayLength;
  }

}


