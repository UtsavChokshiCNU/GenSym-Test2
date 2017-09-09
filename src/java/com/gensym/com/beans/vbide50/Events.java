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


public class Events extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e112, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Events (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #22
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Events
    Doc string is: Supplies properties that enable add-ins to connect to all events in Visual Basic for Applications.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 14 functions.
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

  public Variant getAxVBProjectsEvents ()
    throws ActiveXException {
    // memid = 0xc8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc8, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxVBComponentsEvents (Variant param1)
    throws ActiveXException {
    // memid = 0xc9

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xc9, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxReferencesEvents (Variant param1)
    throws ActiveXException {
    // memid = 0xca

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xca, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxVBControlsEvents (Variant param1, VBForm param2)
    throws ActiveXException {
    // memid = 0xcb

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0xcb, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxSelectedVBControlsEvents (Variant param1, VBForm param2)
    throws ActiveXException {
    // memid = 0xcc

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0xcc, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxCommandBarEvents (ActiveXDispatchable param1)
    throws ActiveXException {
    // memid = 0xcd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0xcd, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxFileControlEvents (Variant param1)
    throws ActiveXException {
    // memid = 0xce

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xce, AX_PROPERTYGET, false, args);
    return vResult;
  }

@Override
public String toString() {
    return "<Events, super = " + super.toString() + ">";
}


}

