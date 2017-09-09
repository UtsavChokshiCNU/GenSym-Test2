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


public class ConnectorFormat extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2443e, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public ConnectorFormat (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #513
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: ConnectorFormat
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 22 functions.
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

  public void BeginConnect (Shape param1, int param2)
    throws ActiveXException {
    // memid = 0x6d6

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x6d6, AX_INVOKE, true, args);
  }

  public void BeginDisconnect ()
    throws ActiveXException {
    // memid = 0x6d9

    Vector args = new Vector(0);
    axInvoke(0x6d9, AX_INVOKE, true, args);
  }

  public void EndConnect (Shape param1, int param2)
    throws ActiveXException {
    // memid = 0x6da

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x6da, AX_INVOKE, true, args);
  }

  public void EndDisconnect ()
    throws ActiveXException {
    // memid = 0x6db

    Vector args = new Vector(0);
    axInvoke(0x6db, AX_INVOKE, true, args);
  }

    // Enumeration type = MsoTriState
  public int getAxBeginConnected ()
    throws ActiveXException {
    // memid = 0x6dc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6dc, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Shape getAxBeginConnectedShape ()
    throws ActiveXException {
    // memid = 0x6dd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6dd, AX_PROPERTYGET, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxBeginConnectionSite ()
    throws ActiveXException {
    // memid = 0x6de

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6de, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoTriState
  public int getAxEndConnected ()
    throws ActiveXException {
    // memid = 0x6df

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6df, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Shape getAxEndConnectedShape ()
    throws ActiveXException {
    // memid = 0x6e0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e0, AX_PROPERTYGET, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxEndConnectionSite ()
    throws ActiveXException {
    // memid = 0x6e1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e1, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoConnectorType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxType (int param1)
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6c, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<ConnectorFormat, super = " + super.toString() + ">";
}


}

