/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.NativeMethodBroker.java
 *
 *   Authors: John Valente, Allan Scott
 */
package com.gensym.com;

import java.awt.Color;
import java.util.Date;
import java.util.Vector;

/** The class <code>Variant</code> is a representation in Java of 
* the C structure VARIANT.  It is used throughout the com.gensym.com
* package as the generic way of representing data that is passed to
* and received from ActiveX.
* <p>
* The method getVartype() of <code>Variant</code> returns an integer flag that 
* indicates the type of data that the Variant represents. These flags
* are defined in <code>ActiveXRuntimeConstants</code>.  Associated with
* each different type of Variant there is a different constructor and
* get method.  For example a Variant of type AX_DATE can be constructed
* with the Variant(java.util.Date) constructor, and the date associated with
* that Variant can be found by calling getDateValue().
* <p>
* @see ActiveXRuntimeConstants
*/
public class Variant implements ActiveXRuntimeConstants
{
  private static final boolean doErrorTracing = false;

  private int vartype = AX_EMPTY;
  private Object varValue = null;

  //**********************************************************************
  // Constructors

  /** Construct a Variant of type AX_HERROR with an error code of
  *  AX_E_PARAMNOTFOUND, to be passed for missing optional parmeters.
  */
  public Variant () {
    if (doErrorTracing)
      traceln("default constructor");

    setErrorValue(AX_E_PARAMNOTFOUND);
  }

  /** Construct a Variant of type AX_SHORT
  */
  public Variant (short value) {
    if (doErrorTracing)
      traceln("short " + value);

    setValue(value);
  }

  /** Construct a Variant of type AX_INTEGER
  */
  public Variant (int value) {
    if (doErrorTracing)
      traceln("int " + value);

    setValue(value);
  }

  /** Construct a Variant of type AX_FLOAT 
   */
  public Variant (float value) {
    if (doErrorTracing)
      traceln("float");

    setValue(value);
  }

  /** Construct a Variant of type AX_DOUBLE 
   */
  public Variant (double value) {
    if (doErrorTracing)
      traceln("double");

    setValue(value);
  }

  /** Construct a Variant of type AX_DATE 
  */
  public Variant (Date value) {
    if (doErrorTracing)
      traceln("date");

    setValue(value);
  }

  /** Construct a Variant of type AX_STRING 
  */
  public Variant (String value) {
    if (doErrorTracing)
      traceln("string");

    setValue(value);
  }

  /** Construct a Variant of type AX_DISPATCH from
   * an object that implements the ActiveXDispatchable
   * interface.
   */
  public Variant (ActiveXDispatchable value) {
    setValue(value);
  }
 
  /** Construct a Variant of type AX_DISPATCH
  * from a dispatch pointer and an ActiveXProxy.
  */
  public Variant (int value, ActiveXProxy oleObject) {
    setValue(new ActiveXDispatchableImpl(value, oleObject));
  }

  /** Construct a Variant of type AX_BOOLEAN 
  */
  public Variant (boolean value) {
    if (doErrorTracing)
      traceln("boolean " + value);

    setValue(value);
  }

  /** Construct a Variant from another Variant, does not copy safe arrays. 
  */
  public Variant (Variant value) {
    setEqualTo(value);
  }

  /** Construct a Variant of type AX_BYTE 
  */
  public Variant (byte value) {
    if (doErrorTracing)
      traceln("boolean " + value);

    setValue(value);
  }

  /** Construct a Variant of type AX_SHORT + AX_ARRAY
  */
  public Variant (short[] value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_SHORT + AX_ARRAY
  */
  public Variant (ShortSafeArray value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_INTEGER + AX_ARRAY
  */
  public Variant (int[] value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_INTEGER + AX_ARRAY
  */
  public Variant (IntSafeArray value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_FLOAT + AX_ARRAY
  */
  public Variant (float[] value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_FLOAT + AX_ARRAY
  */
  public Variant (FloatSafeArray value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_DOUBLE + AX_ARRAY
  */
  public Variant (double[] value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_DOUBLE + AX_ARRAY
  */
  public Variant (DoubleSafeArray value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_DATE + AX_ARRAY
  */
  public Variant (Date[] value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_DATE + AX_ARRAY
  */
  public Variant (DateSafeArray value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_STRING + AX_ARRAY
  */
  public Variant (String[] value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_STRING + AX_ARRAY
  */
  public Variant (StringSafeArray value) {
    setValue(value);
  }

  /** Construct a Boolean of type AX_BOOLEAN + AX_ARRAY
  */
  public Variant (boolean[] value) {
    setValue(value);
  }

  /** Construct a Boolean of type AX_BOOLEAN + AX_ARRAY
  */
  public Variant (BooleanSafeArray value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_VARIANT + AX_ARRAY
  */
  public Variant (Variant[] value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_VARIANT + AX_ARRAY
  */
  public Variant (VariantSafeArray value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_BYTE + AX_ARRAY
  */
  public Variant (byte[] value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_BYTE + AX_ARRAY
  */
  public Variant (ByteSafeArray value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_SHORT + AX_BYREF
  */
  public Variant (ShortRefParameter value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_INTEGER + AX_BYREF
  */
  public Variant (IntRefParameter value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_FLOAT + AX_BYREF
  */
  public Variant (FloatRefParameter value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_DOUBLE + AX_BYREF
  */
  public Variant (DoubleRefParameter value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_DATE + AX_BYREF
  */
  public Variant (DateRefParameter value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_STRING + AX_BYREF
  */
  public Variant (StringRefParameter value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_DISPATCH + AX_BYREF
  */
  public Variant (ActiveXDispatchableRefParameter value) {
    setValue(value);
  }

  /** Construct a Boolean of type AX_BOOLEAN + AX_BYREF
  */
  public Variant (BooleanRefParameter value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_VARIANT + AX_BYREF
  */
  public Variant (VariantRefParameter value) {
    setValue(value);
  }

  /** Construct a Variant of type AX_BYTE + AX_BYREF
  */
  public Variant (ByteRefParameter value) {
    setValue(value);
  }

  /** @undocumented
  * Construct a Variant of type * + AX_ARRAY + AX_BYREF
  */
  public Variant (SARefParameter value) {
    if (value == null)
      return;

    varValue = value;
    vartype = value.getType() + AX_ARRAY + AX_BYREF;
  }

  /** @undocumented
  * For wrapping up parameters when invoking an ActiveX method.
  * This is not an OLE variant type.
  */
  public Variant (Vector value) {
    vartype = AX_VECTOR;

    varValue = value;
  }

  /** @undocumented
  * Construct a Variant of type AX_INTEGER, after converting the color
  * to an ActiveX I4 value.
  */
  public Variant (Color value ) {
    int reversedValue;
    int intValue;
    
    reversedValue = value.getRGB();
    // 1 of these 2 statements is unnecessary, I do not know which.
    intValue = ((reversedValue & 0xff) << 16) +
      (((reversedValue >> 8) & 0xff) << 8) +
      ((reversedValue >> 16) & 0xff);
    intValue = reversedValue;

    setValue(intValue);
  }

  /** @undocumented Construct a Variant of type AX_INTEGER
  * from a long for backwards compatiblity.
  */
  public Variant (long value) {
    if (doErrorTracing)
      traceln("long " + value);

    setValue((int)value);
  }

  /** @undocumented
  * This is a catch all method for types we do not support yet.
  */
  public Variant (Object value) {
    /* Construct a Variant of type AX_HERROR with an error code of
     *  AX_E_PARAMNOTFOUND, to be passed for missing optional parmeters.
     */
    if (doErrorTracing)
      traceln("unsupported type constructor");

    setErrorValue(AX_E_PARAMNOTFOUND);
  }

  //**********************************************************************

  private static void traceln (String message) {
      NativeMethodBroker.traceln(ActiveXTraceLevels.AX_DATA_DUMPS, message);
  }
  //**********************************************************************

  /** Return the integer flag that indicates the type of this
  * Variant.  The flags used by variant are defined in 
  * <code>ActiveXRuntimeConstants</code>
  */
  public short getVartype () {
    return (short)vartype;
  }

  //**********************************************************************

  /** Set the Variant to type AX_SHORT.
  */
  public void setValue (short value) {
    vartype = AX_SHORT;
    varValue = new Integer(value);
  }

  /** For a Variant of type AX_SHORT,
  * return a short associated with it. <p>
  * Note: This will also get a byte.
  */
  public short getShortValue () {
    if ((vartype != AX_SHORT) && (vartype != AX_BYTE))
      return (short)-1;

    return (short)(((Integer)varValue).intValue());
  }

  /** Set the Variant to type AX_INTEGER.
  */
  public void setValue (int value) {
    vartype = AX_INTEGER;
    varValue = new Integer(value);
  }

  /** For a Variant of type AX_INTEGER return an integer 
  * associated with it. <p>
  * Not this will get any type.
  */
  public int getIntValue () {
    if ((vartype != AX_INTEGER) &&
        (vartype != AX_HERROR) &&
        (vartype != AX_SHORT) &&
        (vartype != AX_BYTE)) {
      return -1;
    }

    return ((Integer)varValue).intValue();
  }

  /** Set the Variant to type AX_FLOAT.
  */
  public void setValue (float value) {
    vartype = AX_FLOAT;
    varValue = new Double(value);
  }

  /** For a Variant of type AX_FLOAT return a float 
  * associated with it. <p>
  */
  public float getFloatValue () {
    if (vartype != AX_FLOAT)
      return (float)-1.0;

    return ((Double)varValue).floatValue();
  }

  /** Set the Variant to type AX_DOUBLE.
  */
  public void setValue (double value) {
    vartype = AX_DOUBLE;
    varValue = new Double(value);
  }

  /** For a Variant of type AX_DOUBLE return a double 
  * associated with it. <p>
  * Note: This will also get float values.
  */
  public double getDoubleValue () {
    if ((vartype != AX_DOUBLE) && (vartype != AX_FLOAT))
      return -1.0;

    return ((Double)varValue).doubleValue();
  }

  /** Set the Variant to type AX_DATE.
  */
  public void setValue (Date value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_DATE;

    varValue = new Date(value.getTime());
  }

  /** For a Variant of type AX_DATE return a  
  * Date associated with it. <p>
  */
  public Date getDateValue () {
    if (vartype != AX_DATE)
        return null;

    return new Date(getDateSecondsValue());
  }

  /** @undocumented Return the number of seconds since 1970 represented
   * by this Variant.  If this Variant is not of type DATE 
   * this will return 0. If this Variant is of type DATE then
   * this will return the number of milli seconds since 1970.
   */
  public long getDateSecondsValue () {
    if (vartype != AX_DATE)
        return 0;

    return ((Date)varValue).getTime();
  }

  /** Set the Variant to type AX_STRING.
  */
  public void setValue (String value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_STRING;
    varValue = value;
  }

  /** For a Variant of type AX_STRING return a String 
  * associated with it. <p>
  */
  public String getStringValue () {
    if (vartype != AX_STRING)
      return null;

    return (String)varValue;
  }

  /** Set the Variant to type AX_DISPATCH.
  */
  public void setValue (ActiveXDispatchable value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_DISPATCH;
    varValue = value;
  }

  /** For a Variant of type AX_DISPATCH return an  
  * implementation of <code>ActiveXDispatchable</code>
  * associated with it. <p>
  */
  public ActiveXDispatchable getActiveXDispatchableValue () {
    if (vartype != AX_DISPATCH)
      return null;

    return (ActiveXDispatchable)varValue;
  }

  /** For a Variant of type AX_DISPATCH return only the
  * dispatch pointer associated with it.
  */
  public int getDispatchPointer() 
  {
    if (vartype != AX_DISPATCH)
      return AX_NO_DISPATCH;
    else
      return ((ActiveXDispatchable)varValue).getDispatchPointer();
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  public int getDispatchPointer(ActiveXProxy proxy) {
    if (vartype != AX_DISPATCH)
      return AX_NO_DISPATCH;
    else
      return ((ActiveXDispatchable)varValue).getDispatchPointer(proxy);
  }

  /** Set the Variant to type AX_HERROR.
  */
  public void setErrorValue (int value) {
    vartype = AX_HERROR;
    varValue = new Integer(value);
  }

  /** For a Variant of type AX_HERROR return a  
  * error associated with it. <p>
  */
  public int getErrorValue () {
    if (vartype != AX_HERROR)
        return 0;

    return ((Integer)varValue).intValue();
  }

  /** Set the Variant to type AX_BOOLEAN. <p>
  */
  public void setValue (boolean value) {
    vartype = AX_BOOLEAN;
    varValue = new Boolean(value);
  }

  /** For a Variant of type AX_BOOLEAN return a boolean 
  * associated with it. <p>
  */
  public boolean getBooleanValue () {
    if (vartype != AX_BOOLEAN)
        return false;

    return ((Boolean)varValue).booleanValue();
  }

  /** Set the Variant to type AX_BYTE.
  */
  public void setValue (byte value) {
    vartype = AX_BYTE;
    varValue = new Integer(value);
  }

  /** For a Variant of type AX_BYTE return a byte associated with it. <p>
  */
  public byte getByteValue () {
    if (vartype != AX_BYTE)
      return (byte)-1;

    return (byte)(((Integer)varValue).intValue());
  }

  /** For a Variant of type AX_* + AX_ARRAY return the safe array
  * associated with it. <p>
  */
  public SafeArray getSafeArrayValue () {
    if ((vartype & (int)AX_ARRAY) != (int)AX_ARRAY)
      return null;

    return (SafeArray)varValue;
  }

  /** Set the Variant to type AX_SHORT + AX_ARRAY.
  */
  public void setValue (short[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new ShortSafeArray(value));
  }

  /** Set the Variant to type AX_SHORT + AX_ARRAY.
  */
  public void setValue (ShortSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_SHORT + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_SHORT + AX_ARRAY return a Short array
  * associated with it. <p>
  */
  public short[] getShortArrayValue () {
    if (vartype != AX_SHORT + AX_ARRAY)
      return null;

    return ((ShortSafeArray)varValue).getAllShorts();
  }

  /** For a Variant of type AX_SHORT + AX_ARRAY return a Short safe array
  * associated with it. <p>
  */
  public ShortSafeArray getShortSafeArrayValue () {
    if (vartype != AX_SHORT + AX_ARRAY)
      return null;

    return (ShortSafeArray)varValue;
  }

  /** Set the Variant to type AX_INTEGER + AX_ARRAY.
  */
  public void setValue (int[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new IntSafeArray(value));
  }

  /** Set the Variant to type AX_INTEGER + AX_ARRAY.
  */
  public void setValue (IntSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_INTEGER + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_INTEGER + AX_ARRAY return a Int array
  * associated with it. <p>
  */
  public int[] getIntArrayValue () {
    if (vartype != AX_INTEGER + AX_ARRAY)
      return null;

    return ((IntSafeArray)varValue).getAllInts();
  }

  /** For a Variant of type AX_INTEGER + AX_ARRAY return a Int safe array
  * associated with it. <p>
  */
  public IntSafeArray getIntSafeArrayValue () {
    if (vartype != AX_INTEGER + AX_ARRAY)
      return null;

    return (IntSafeArray)varValue;
  }

  /** Set the Variant to type AX_FLOAT + AX_ARRAY.
  */
  public void setValue (float[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new FloatSafeArray(value));
  }

  /** Set the Variant to type AX_FLOAT + AX_ARRAY.
  */
  public void setValue (FloatSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_FLOAT + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_FLOAT + AX_ARRAY return a Float array
  * associated with it. <p>
  */
  public float[] getFloatArrayValue () {
    if (vartype != AX_FLOAT + AX_ARRAY)
      return null;

    return ((FloatSafeArray)varValue).getAllFloats();
  }

  /** For a Variant of type AX_FLOAT + AX_ARRAY return a Float safe array
  * associated with it. <p>
  */
  public FloatSafeArray getFloatSafeArrayValue () {
    if (vartype != AX_FLOAT + AX_ARRAY)
      return null;

    return (FloatSafeArray)varValue;
  }

  /** Set the Variant to type AX_DOUBLE + AX_ARRAY.
  */
  public void setValue (double[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new DoubleSafeArray(value));
  }

  /** Set the Variant to type AX_DOUBLE + AX_ARRAY.
  */
  public void setValue (DoubleSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_DOUBLE + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_DOUBLE + AX_ARRAY return a Double array
  * associated with it. <p>
  */
  public double[] getDoubleArrayValue () {
    if (vartype != AX_DOUBLE + AX_ARRAY)
      return null;

    return ((DoubleSafeArray)varValue).getAllDoubles();
  }

  /** For a Variant of type AX_DOUBLE + AX_ARRAY return a Double safe array
  * associated with it. <p>
  */
  public DoubleSafeArray getDoubleSafeArrayValue () {
    if (vartype != AX_DOUBLE + AX_ARRAY)
      return null;

    return (DoubleSafeArray)varValue;
  }

  /** Set the Variant to type AX_DATE + AX_ARRAY.
  */
  public void setValue (Date[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new DateSafeArray(value));
  }

  /** Set the Variant to type AX_DATE + AX_ARRAY.
  */
  public void setValue (DateSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_DATE + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_DATE + AX_ARRAY return a Date array
  * associated with it. <p>
  */
  public Date[] getDateArrayValue () {
    if (vartype != AX_DATE + AX_ARRAY)
      return null;

    return ((DateSafeArray)varValue).getAllDates();
  }

  /** For a Variant of type AX_DATE + AX_ARRAY return a Date safe array
  * associated with it. <p>
  */
  public DateSafeArray getDateSafeArrayValue () {
    if (vartype != AX_DATE + AX_ARRAY)
      return null;

    return (DateSafeArray)varValue;
  }

  /** Set the Variant to type AX_STRING + AX_ARRAY.
  */
  public void setValue (String[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new StringSafeArray(value));
  }

  /** Set the Variant to type AX_STRING + AX_ARRAY.
  */
  public void setValue (StringSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_STRING + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_STRING + AX_ARRAY return a String array
  * associated with it. <p>
  */
  public String[] getStringArrayValue () {
    if (vartype != AX_STRING + AX_ARRAY)
      return null;

    return ((StringSafeArray)varValue).getAllStrings();
  }

  /** For a Variant of type AX_STRING + AX_ARRAY return a String safe array
  * associated with it. <p>
  */
  public StringSafeArray getStringSafeArrayValue () {
    if (vartype != AX_STRING + AX_ARRAY)
      return null;

    return (StringSafeArray)varValue;
  }

  /** Set the Variant to type AX_BOOLEAN + AX_ARRAY.
  */
  public void setValue (boolean[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new BooleanSafeArray(value));
  }

  /** Set the Variant to type AX_BOOLEAN + AX_ARRAY.
  */
  public void setValue (BooleanSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_BOOLEAN + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_BOOLEAN + AX_ARRAY return a Boolean array
  * associated with it. <p>
  */
  public boolean[] getBooleanArrayValue () {
    if (vartype != AX_BOOLEAN + AX_ARRAY)
      return null;

    return ((BooleanSafeArray)varValue).getAllBooleans();
  }

  /** For a Variant of type AX_BOOLEAN + AX_ARRAY return a Boolean safe array
  * associated with it. <p>
  */
  public BooleanSafeArray getBooleanSafeArrayValue () {
    if (vartype != AX_BOOLEAN + AX_ARRAY)
      return null;

    return (BooleanSafeArray)varValue;
  }

  /** Set the Variant to type AX_VARIANT + AX_ARRAY.
  */
  public void setValue (Variant[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new VariantSafeArray(value));
  }

  /** Set the Variant to type AX_VARIANT + AX_ARRAY.
  */
  public void setValue (VariantSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_VARIANT + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_VARIANT + AX_ARRAY return a Variant array
  * associated with it. <p>
  */
  public Variant[] getVariantArrayValue () {
    if (vartype != AX_VARIANT + AX_ARRAY)
      return null;

    return ((VariantSafeArray)varValue).getAllVariants();
  }

  /** For a Variant of type AX_VARIANT + AX_ARRAY return a Variant safe array
  * associated with it. <p>
  */
  public VariantSafeArray getVariantSafeArrayValue () {
    if (vartype != AX_VARIANT + AX_ARRAY)
      return null;

    return (VariantSafeArray)varValue;
  }

  /** Set the Variant to type AX_BYTE + AX_ARRAY.
  */
  public void setValue (byte[] value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    setValue(new ByteSafeArray(value));
  }

  /** Set the Variant to type AX_BYTE + AX_ARRAY.
  */
  public void setValue (ByteSafeArray value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_BYTE + AX_ARRAY;
    varValue = value;
  }

  /** For a Variant of type AX_BYTE + AX_ARRAY return a Byte array
  * associated with it. <p>
  */
  public byte[] getByteArrayValue () {
    if (vartype != AX_BYTE + AX_ARRAY)
      return null;

    return ((ByteSafeArray)varValue).getAllBytes();
  }

  /** For a Variant of type AX_BYTE + AX_ARRAY return a Byte safe array
  * associated with it. <p>
  */
  public ByteSafeArray getByteSafeArrayValue () {
    if (vartype != AX_BYTE + AX_ARRAY)
      return null;

    return (ByteSafeArray)varValue;
  }

  /** Set the Variant to type AX_SHORT + AX_BYREF.
  */
  public void setValue (ShortRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_SHORT + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_SHORT + AX_BYREF return a short reference
  * parameter associated with it. <p>
  */
  public ShortRefParameter getShortRefParameterValue () {
    if (vartype != AX_SHORT + AX_BYREF)
      return null;

    return (ShortRefParameter)varValue;
  }

  /** Set the Variant to type AX_INTEGER + AX_BYREF.
  */
  public void setValue (IntRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_INTEGER + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_INTEGER + AX_BYREF return a int reference
  * parameter associated with it. <p>
  */
  public IntRefParameter getIntRefParameterValue () {
    if (vartype != AX_INTEGER + AX_BYREF)
      return null;

    return (IntRefParameter)varValue;
  }

  /** Set the Variant to type AX_FLOAT + AX_BYREF.
  */
  public void setValue (FloatRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_FLOAT + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_FLOAT + AX_BYREF return a float reference
  * parameter associated with it. <p>
  */
  public FloatRefParameter getFloatRefParameterValue () {
    if (vartype != AX_FLOAT + AX_BYREF)
      return null;

    return (FloatRefParameter)varValue;
  }

  /** Set the Variant to type AX_DOUBLE + AX_BYREF.
  */
  public void setValue (DoubleRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_DOUBLE + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_DOUBLE + AX_BYREF return a double reference
  * parameter associated with it. <p>
  */
  public DoubleRefParameter getDoubleRefParameterValue () {
    if (vartype != AX_DOUBLE + AX_BYREF)
      return null;

    return (DoubleRefParameter)varValue;
  }

  /** Set the Variant to type AX_DATE + AX_BYREF.
  */
  public void setValue (DateRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_DATE + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_DATE + AX_BYREF return a Date reference
  * parameter associated with it. <p>
  */
  public DateRefParameter getDateRefParameterValue () {
    if (vartype != AX_DATE + AX_BYREF)
      return null;

    return (DateRefParameter)varValue;
  }

  /** Set the Variant to type AX_STRING + AX_BYREF.
  */
  public void setValue (StringRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_STRING + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_STRING + AX_BYREF return a String reference
  * parameter associated with it. <p>
  */
  public StringRefParameter getStringRefParameterValue () {
    if (vartype != AX_STRING + AX_BYREF)
      return null;

    return (StringRefParameter)varValue;
  }

  /** Set the Variant to type AX_DISPATCH + AX_BYREF.
  */
  public void setValue (ActiveXDispatchableRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_DISPATCH + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_DISPATCH + AX_BYREF return the
  * ActiveXDispatchable reference parameter associated with it. <p>
  */
  public ActiveXDispatchableRefParameter
      getActiveXDispatchableRefParameterValue () {
    if (vartype != AX_DISPATCH + AX_BYREF)
      return null;

    return (ActiveXDispatchableRefParameter)varValue;
  }

  /** Set the Variant to type AX_BOOLEAN + AX_BYREF.
  */
  public void setValue (BooleanRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_BOOLEAN + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_BOOLEAN + AX_BYREF return a boolean reference
  * parameter associated with it. <p>
  */
  public BooleanRefParameter getBooleanRefParameterValue () {
    if (vartype != AX_BOOLEAN + AX_BYREF)
      return null;

    return (BooleanRefParameter)varValue;
  }

  /** Set the Variant to type AX_VARIANT + AX_BYREF.
  */
  public void setValue (VariantRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_VARIANT + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_VARIANT + AX_BYREF return a Variant reference
  * parameter associated with it. <p>
  */
  public VariantRefParameter getVariantRefParameterValue () {
    if (vartype != AX_VARIANT + AX_BYREF)
      return null;

    return (VariantRefParameter)varValue;
  }

  /** Set the Variant to type AX_BYTE + AX_BYREF.
  */
  public void setValue (ByteRefParameter value) {

    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    vartype = AX_BYTE + AX_BYREF;
    varValue = value;
  }

  /** For a Variant of type AX_BYTE + AX_BYREF return a byte reference
  * parameter associated with it. <p>
  */
  public ByteRefParameter getByteRefParameterValue () {
    if (vartype != AX_BYTE + AX_BYREF)
      return null;

    return (ByteRefParameter)varValue;
  }

  public SARefParameter getSARefParameterValue() {
    if ((vartype & (AX_ARRAY + AX_BYREF)) != (AX_ARRAY + AX_BYREF))
      return null;

    return (SARefParameter) varValue;
  }

  /** Set this equal a Variant to another Variant. Does not copy safe arrays.
  */
  public void setEqualTo (Variant value) {
    if (value == null) {
      vartype = AX_NULL;
      varValue = "null";
      return;
    }

    /* Dates in ActiveX variants are values so treat them like values in
       the Java Variant. */
    if (value.vartype == AX_DATE) {
      setValue((Date)value.varValue);
      return;
    }

    this.vartype = value.vartype;
    this.varValue = value.varValue;  
  }

  /** Get a copy of the variant. This method copies the safe arrays. */
  public Variant copy() {
    Variant var = new Variant(this);

    /* copy safe arrays */
    if ((vartype & AX_ARRAY) == AX_ARRAY) {
      var.varValue = ((SafeArray)varValue).clone();
    }

    return var;  
  }

  /** @undocumented For a Variant of type AX_VECTOR return a  
  * Vector associated with it. <p>
  */
  public Vector getVectorValue () {
    if (vartype != AX_VECTOR)
       return null;

    return (Vector)varValue;
  }

  /** For a Variant of type AX_INTEGER return a  
  * Color associated with it. <p>
  */
  public Color getColorValue () {
    int composedValue;

    traceln("getting color value from " + getIntValue());
    composedValue = getRGBValue();
    return new Color(composedValue);
  }

  /** For a Variant of type AX_INTEGER, but return a  
  * composed RGB value associated with it. <p>
  */
  public int getRGBValue () {
    int composedValue, value;

    if (vartype != AX_INTEGER) {
      /* Need to map OLE_COLOR values into rgb values
      * by making a callback into C and a call to
      * OleTranslateColor.  There are also pallette
      * issues to consider.  For now just treat these
      * as black.
      */
      return 0;
    } else {
      value = getIntValue();
    }

    composedValue = ((value & 0xff) << 16) +
      (((value >> 8) & 0xff) << 8) + ((value >> 16) & 0xff);
    return composedValue;
  }

  /** @undocumented, For a backwards compatiblity, returns
  * the value of a Variant of type AX_INTEGER as long
  * since activeX does not have a 64 bit value.
  */
  public long getLongValue () {
    return (long)getIntValue();
  }

  /** @undocumented */
  public Object getGenericValue () {
    return new Object();
  }

  //**********************************************************************

  /** Return a String that represents this Variant. 
  */
  @Override
  public String toString () {
    if (varValue == null)
        return "null";

    return varValue.toString();
  }

  /** Determinte if 2 Variants are equal. 
  */
  public boolean equals (Variant value) {
    return varValue.equals(value.varValue);
  }

  /** Return a String that represents the type of this
  * Variant.
  */
  public String getVartypeAsString () {
    switch (vartype | (short)0x0fff) {
    case AX_EMPTY:
      return "empty";
    case AX_NULL:
      return "null";
    case AX_BYTE:
      return "byte";
    case AX_SHORT:
      return "short";
    case AX_BOOLEAN:
      return "boolean";
    case AX_INTEGER:
      return "integer";
    case AX_LONG:
      return "long";
    case AX_FLOAT:
      return "float";
    case AX_DOUBLE:
      return "double";
    case AX_CURRENCY:
      return "currency";
    case AX_STRING:
      return "string";
    case AX_VECTOR:
      return "vector";
    case AX_IUNKNOWN:
      return "IUnknown";
    case AX_DISPATCH:
      return "IDispatch " + getDispatchPointer();
    case AX_DATE:
      return "date";
    case AX_INT:
      return "int";
    case AX_HERROR:
      return "error";
    case AX_UI2:
      return "UI2";
    case AX_UINT:
      return "UINT";
    case AX_VARIANT:
      return "variant";
    case AX_VOID:
      return "void";
    default:
      return "problem";
    }
  }


}
