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


public class Trendline extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208be, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Trendline (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #490
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Trendline
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 38 functions.
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

  public int getAxBackward ()
    throws ActiveXException {
    // memid = 0xb9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb9, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxBackward (int param1)
    throws ActiveXException {
    // memid = 0xb9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xb9, AX_PROPERTYSET, true, args);
  }

  public Border getAxBorder ()
    throws ActiveXException {
    // memid = 0x80

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80, AX_PROPERTYGET, false, args);
    Border result = new Border(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void ClearFormats ()
    throws ActiveXException {
    // memid = 0x70

    Vector args = new Vector(0);
    axInvoke(0x70, AX_INVOKE, true, args);
  }

  public DataLabel getAxDataLabel ()
    throws ActiveXException {
    // memid = 0x9e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x9e, AX_PROPERTYGET, false, args);
    DataLabel result = new DataLabel(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public boolean getAxDisplayEquation ()
    throws ActiveXException {
    // memid = 0xbe

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xbe, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayEquation (boolean param1)
    throws ActiveXException {
    // memid = 0xbe

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xbe, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayRSquared ()
    throws ActiveXException {
    // memid = 0xbd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xbd, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayRSquared (boolean param1)
    throws ActiveXException {
    // memid = 0xbd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xbd, AX_PROPERTYSET, true, args);
  }

  public int getAxForward ()
    throws ActiveXException {
    // memid = 0xbf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xbf, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxForward (int param1)
    throws ActiveXException {
    // memid = 0xbf

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xbf, AX_PROPERTYSET, true, args);
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x1e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public double getAxIntercept ()
    throws ActiveXException {
    // memid = 0xba

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xba, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxIntercept (double param1)
    throws ActiveXException {
    // memid = 0xba

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xba, AX_PROPERTYSET, true, args);
  }

  public boolean getAxInterceptIsAuto ()
    throws ActiveXException {
    // memid = 0xbb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xbb, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxInterceptIsAuto (boolean param1)
    throws ActiveXException {
    // memid = 0xbb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xbb, AX_PROPERTYSET, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6e, AX_PROPERTYSET, true, args);
  }

  public boolean getAxNameIsAuto ()
    throws ActiveXException {
    // memid = 0xbc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xbc, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxNameIsAuto (boolean param1)
    throws ActiveXException {
    // memid = 0xbc

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xbc, AX_PROPERTYSET, true, args);
  }

  public int getAxOrder ()
    throws ActiveXException {
    // memid = 0xc0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxOrder (int param1)
    throws ActiveXException {
    // memid = 0xc0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc0, AX_PROPERTYSET, true, args);
  }

  public int getAxPeriod ()
    throws ActiveXException {
    // memid = 0xb8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb8, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPeriod (int param1)
    throws ActiveXException {
    // memid = 0xb8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xb8, AX_PROPERTYSET, true, args);
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(0);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

    // Enumeration type = XlTrendlineType
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
    return "<Trendline, super = " + super.toString() + ">";
}


}

