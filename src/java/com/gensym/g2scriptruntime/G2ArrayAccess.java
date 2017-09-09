package com.gensym.g2scriptruntime;

public interface G2ArrayAccess {

  /**
   * Returns an array Object used internally to store the G2Array data.
   * Sub array types will return an array of the correct type, e.g.
   * IntegerArray will return an int[].
   */
  public java.lang.Object getArray();

  /**
   * Set the array Object used internally to store the G2Array data.
   * The original array Object will no longer be referenced by the G2Array.
   * If the G2Array is sub array type, then the array parameter must be an
   * array of the correct type, e.g. for FloatArray, the array parameter
must be 
   * a double[].
   */
  public void setArray(java.lang.Object array);

  /**
   * Gets the length of the array used internally to store G2Array data.
   */
  public int getArrayLength();

  /**
   * Sets the array length of the internal array to the new size, the
original internal array 
   * is copied into and then replaced by an array of the new size.
   */
  public void setArrayLength(int size);

}
