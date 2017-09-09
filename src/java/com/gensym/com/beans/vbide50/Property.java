package com.gensym.com.beans.vbide50;

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


public class Property extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e18d, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Property (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic 5.0 Extensibility
    // Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    // There are 108 TypeInfos in the library

/* Type info #72
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Property
    Doc string is: Represents a property of an object.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 19 functions.
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

  public Variant getAxValue ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxValue (Variant param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x0, AX_PROPERTYSET, true, args);
  }

  public Variant getAxIndexedValue (Variant param1)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxIndexedValue (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxIndexedValue (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxIndexedValue (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxIndexedValue (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x3, AX_PROPERTYSET, true, args);
  }

  public void setAxIndexedValue (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x3, AX_PROPERTYSET, true, args);
  }

  public void setAxIndexedValue (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x3, AX_PROPERTYSET, true, args);
  }

  public void setAxIndexedValue (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x3, AX_PROPERTYSET, true, args);
  }

  public short getAxNumIndices ()
    throws ActiveXException {
    // memid = 0x4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4, AX_PROPERTYGET, false, args);
    short result = vResult.getShortValue();
    return result;
  }

  public ActiveXDispatchable getAxApplication ()
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Variant getAxParent ()
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x28

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x28, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public VBE getAxVBE ()
    throws ActiveXException {
    // memid = 0x29

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x29, AX_PROPERTYGET, false, args);
    VBE result = new VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxCollection ()
    throws ActiveXException {
    // memid = 0x2a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Object getAxObject ()
    throws ActiveXException {
    // memid = 0x2d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d, AX_PROPERTYGET, false, args);
    Object result = vResult.getGenericValue();
    return result;
  }

    // Currently unimplemented reference put: 0x2d

@Override
public String toString() {
    return "<Property, super = " + super.toString() + ">";
}


}

