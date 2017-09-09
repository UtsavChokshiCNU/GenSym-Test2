/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ByteSARefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>ByteSARefParameter</code> is the Java representation for
* the ActiveX IDL type SAFEARRAY(unsigned char)* used for [out] or [in/out]
* parameters.<p>
* When used as a parameter to an exported bean's method, the address of the
* input safe array is obtained from the contained Java safe array wrapper
* object, the safe array is locked, the address of the safe array is put into
* a temporary native memory location, and the address of the native location 
* is used as the parameter to the native ActiveX method. <p>
* After the native method returns, the input safe array is unlocked, the new
* output safe array at the native location will be wrapped with a new Java
* object, and the reference parameter will be set to the new Java object.
*/
public class ByteSARefParameter extends SARefParameter implements Cloneable {

  /** Constructs an in/out ByteSARefParameter from a ByteSafeArray. */
  public ByteSARefParameter(ByteSafeArray value) {
    setSafeArray(value);
  }

  /** Constructs an out ByteSARefParameter. */
  public ByteSARefParameter() {
  }

  /** @undocumented overrides SARefParameter.getType */
  @Override
  short getType() {
    return AX_UI1;
  }

  /** @undocumented overrides SARefParameter.setSafeArray to make sure only
  * correct type of SafeArrays get put in this reference parameter.
  */
  @Override
  public void setSafeArray(SafeArray array) {
    setByteSafeArray((ByteSafeArray)array);
  }

  /** Sets the input ByteArray for the ByteSARefParameter. */
  public void setByteSafeArray(ByteSafeArray value) {
    super.setSafeArray(value);
  }

  /** Gets the output ByteSafeArray of a ByteSARefParameter. */
  public ByteSafeArray getByteSafeArray() {
    return (ByteSafeArray)getSafeArray();
  }

  @Override
  public String toString() {
    return "ByteSARef = " + getSafeArray();
  }
}
