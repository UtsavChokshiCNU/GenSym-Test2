package com.gensym.com.beans.office20;

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


public class FreeformBuilder extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc0315, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public FreeformBuilder (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #84
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: FreeformBuilder
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    Type Info contains 12 functions.
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

  public void AddNodes (int param1, int param2, float param3, float param4, float param5, float param6, float param7, float param8)
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    args.addElement(new Variant(param6));
    args.addElement(new Variant(param7));
    args.addElement(new Variant(param8));
    axInvoke(0xa, AX_INVOKE, true, args);
  }

  public Shape ConvertToShape ()
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

@Override
public String toString() {
    return "<FreeformBuilder, super = " + super.toString() + ">";
}


}

