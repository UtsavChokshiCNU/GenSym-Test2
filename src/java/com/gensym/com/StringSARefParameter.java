/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.StringSARefParameter.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/** The class <code>StringSARefParameter</code> is the Java representation for
* the ActiveX IDL type SAFEARRAY(BSTR)* used for [out] or [in/out]
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
public class StringSARefParameter extends SARefParameter implements Cloneable {

  /** Constructs an in/out StringSARefParameter from a StringSafeArray. */
  public StringSARefParameter(StringSafeArray value) {
    setSafeArray(value);
  }

  /** Constructs an out StringSARefParameter. */
  public StringSARefParameter() {
  }

  /** @undocumented overrides SARefParameter.getType */
  @Override
  short getType() {
    return AX_STRING;
  }

  /** @undocumented overrides SARefParameter.setSafeArray to make sure only
  * correct type of SafeArrays get put in this reference parameter.
  */
  @Override
  public void setSafeArray(SafeArray array) {
    setStringSafeArray((StringSafeArray)array);
  }

  /** Sets the input StringArray for the StringSARefParameter. */
  public void setStringSafeArray(StringSafeArray value) {
    super.setSafeArray(value);
  }

  /** Gets the output StringSafeArray of a StringSARefParameter. */
  public StringSafeArray getStringSafeArray() {
    return (StringSafeArray)getSafeArray();
  }

  @Override
  public String toString() {
    return "StringSARef = " + getSafeArray();
  }
}
