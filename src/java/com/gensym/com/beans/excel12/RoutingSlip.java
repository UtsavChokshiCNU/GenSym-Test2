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


public class RoutingSlip extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208aa, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public RoutingSlip (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #437
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: RoutingSlip
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 23 functions.
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

  public ExcelApplication getAxApplication ()
    throws ActiveXException {
    // memid = 0x94

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x94, AX_PROPERTYGET, false, args);
    ExcelApplication result = new ExcelApplication(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlCreator
  public int getAxCreator ()
    throws ActiveXException {
    // memid = 0x95

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x95, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ActiveXDispatchable getAxParent ()
    throws ActiveXException {
    // memid = 0x96

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x96, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

    // Enumeration type = XlRoutingSlipDelivery
  public int getAxDelivery ()
    throws ActiveXException {
    // memid = 0x3bb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3bb, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDelivery (int param1)
    throws ActiveXException {
    // memid = 0x3bb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3bb, AX_PROPERTYSET, true, args);
  }

  public Variant getAxMessage ()
    throws ActiveXException {
    // memid = 0x3ba

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ba, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxMessage (Variant param1)
    throws ActiveXException {
    // memid = 0x3ba

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3ba, AX_PROPERTYSET, true, args);
  }

  public Variant Recipients ()
    throws ActiveXException {
    // memid = 0x3b8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3b8, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Recipients (Variant param1)
    throws ActiveXException {
    // memid = 0x3b8

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x3b8, AX_INVOKE, false, args);
    return vResult;
  }

  public void Reset ()
    throws ActiveXException {
    // memid = 0x22b

    Vector args = new Vector(0);
    axInvoke(0x22b, AX_INVOKE, true, args);
  }

  public boolean getAxReturnWhenDone ()
    throws ActiveXException {
    // memid = 0x3bc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3bc, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxReturnWhenDone (boolean param1)
    throws ActiveXException {
    // memid = 0x3bc

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3bc, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlRoutingSlipStatus
  public int getAxStatus ()
    throws ActiveXException {
    // memid = 0x3be

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3be, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Variant getAxSubject ()
    throws ActiveXException {
    // memid = 0x3b9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3b9, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxSubject (Variant param1)
    throws ActiveXException {
    // memid = 0x3b9

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3b9, AX_PROPERTYSET, true, args);
  }

  public boolean getAxTrackStatus ()
    throws ActiveXException {
    // memid = 0x3bd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3bd, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxTrackStatus (boolean param1)
    throws ActiveXException {
    // memid = 0x3bd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3bd, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<RoutingSlip, super = " + super.toString() + ">";
}


}

