package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXModes;
import com.gensym.com.ActiveXProxy;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXCastException;
import com.gensym.com.Guid;
import com.gensym.com.ActiveXDefaultComponentImpl;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXDispatchableImpl;
import com.gensym.com.NativeMethodBroker;
import com.gensym.com.Variant;

import com.gensym.com.Hwnd;

import java.awt.Color;

import java.util.Date;
import java.util.Vector;


public class ShadowFormat extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc031b, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public ShadowFormat (ActiveXDispatchable axDispatch) throws ActiveXCastException
  {
       super(axDispatch);
       axProxy.checkCast(getDispatchPointer(), classID);
  }

  public static Guid getStaticClassID ()
  {
      return classID;
  }

  public Guid getClassID ()
  {
      return classID;
  }

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #7
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: ShadowFormat
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 26 functions.
    Type Info contains zero properties.
 */

  public void QueryInterface (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x60000000

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x60000000, AX_INVOKE, true, args);
  }

  public long AddRef ()
    throws ActiveXException {
    // memid = 0x60000001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60000001, AX_INVOKE, false, args);
    long result = vResult.getLongValue();
    return result;
  }

  public long Release ()
    throws ActiveXException {
    // memid = 0x60000002

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60000002, AX_INVOKE, false, args);
    long result = vResult.getLongValue();
    return result;
  }

  public void GetTypeInfoCount (Variant param1)
    throws ActiveXException {
    // memid = 0x60010000

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x60010000, AX_INVOKE, true, args);
  }

  public void GetTypeInfo (long param1, long param2, Variant param3)
    throws ActiveXException {
    // memid = 0x60010001

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x60010001, AX_INVOKE, true, args);
  }

  public void GetIDsOfNames (Variant param1, Variant param2, long param3, long param4, Variant param5)
    throws ActiveXException {
    // memid = 0x60010002

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    axInvoke(0x60010002, AX_INVOKE, true, args);
  }

  public void Invoke (int param1, Variant param2, long param3, int param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x60010003

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    axInvoke(0x60010003, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable getAxApplication ()
    throws ActiveXException {
    // memid = 0x60020000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020000, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public int getAxCreator ()
    throws ActiveXException {
    // memid = 0x60020001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020001, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ActiveXDispatchable getAxParent ()
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void IncrementOffsetX (float param1)
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xa, AX_INVOKE, true, args);
  }

  public void IncrementOffsetY (float param1)
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xb, AX_INVOKE, true, args);
  }

  public ColorFormat getAxForeColor ()
    throws ActiveXException {
    // memid = 0x64

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64, AX_PROPERTYGET, false, args);
    ColorFormat result = new ColorFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void setAxForeColor (ColorFormat param1)
    throws ActiveXException {
    // memid = 0x64

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x64, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoTriState
  public int getAxObscured ()
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x65, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxObscured (int param1)
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x65, AX_PROPERTYSET, true, args);
  }

  public float getAxOffsetX ()
    throws ActiveXException {
    // memid = 0x66

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x66, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxOffsetX (float param1)
    throws ActiveXException {
    // memid = 0x66

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x66, AX_PROPERTYSET, true, args);
  }

  public float getAxOffsetY ()
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxOffsetY (float param1)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67, AX_PROPERTYSET, true, args);
  }

  public float getAxTransparency ()
    throws ActiveXException {
    // memid = 0x68

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x68, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxTransparency (float param1)
    throws ActiveXException {
    // memid = 0x68

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x68, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoShadowType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxType (int param1)
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x69, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoTriState
  public int getAxVisible ()
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxVisible (int param1)
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6a, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<ShadowFormat, super = " + super.toString() + ">";
}


}

