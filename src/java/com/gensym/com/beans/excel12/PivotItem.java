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


public class PivotItem extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20876, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public PivotItem (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #386
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: PivotItem
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 33 functions.
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

  public PivotField getAxParent ()
    throws ActiveXException {
    // memid = 0x96

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x96, AX_PROPERTYGET, false, args);
    PivotField result = new PivotField(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxChildItems ()
    throws ActiveXException {
    // memid = 0x2da

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2da, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxChildItems (Variant param1)
    throws ActiveXException {
    // memid = 0x2da

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2da, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Range getAxDataRange ()
    throws ActiveXException {
    // memid = 0x2d0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d0, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAx_Default ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAx_Default (String param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x0, AX_PROPERTYSET, true, args);
  }

  public Range getAxLabelRange ()
    throws ActiveXException {
    // memid = 0x2cf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2cf, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
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

  public PivotItem getAxParentItem ()
    throws ActiveXException {
    // memid = 0x2e5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2e5, AX_PROPERTYGET, false, args);
    PivotItem result = new PivotItem(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxParentShowDetail ()
    throws ActiveXException {
    // memid = 0x2e3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2e3, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public int getAxPosition ()
    throws ActiveXException {
    // memid = 0x85

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x85, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPosition (int param1)
    throws ActiveXException {
    // memid = 0x85

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x85, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShowDetail ()
    throws ActiveXException {
    // memid = 0x249

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x249, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowDetail (boolean param1)
    throws ActiveXException {
    // memid = 0x249

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x249, AX_PROPERTYSET, true, args);
  }

  public Variant getAxSourceName ()
    throws ActiveXException {
    // memid = 0x2d1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d1, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public String getAxValue ()
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxValue (String param1)
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6, AX_PROPERTYSET, true, args);
  }

  public boolean getAxVisible ()
    throws ActiveXException {
    // memid = 0x22e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x22e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxVisible (boolean param1)
    throws ActiveXException {
    // memid = 0x22e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x22e, AX_PROPERTYSET, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public boolean getAxIsCalculated ()
    throws ActiveXException {
    // memid = 0x5e8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e8, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public int getAxRecordCount ()
    throws ActiveXException {
    // memid = 0x5c6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5c6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxFormula ()
    throws ActiveXException {
    // memid = 0x105

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x105, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxFormula (String param1)
    throws ActiveXException {
    // memid = 0x105

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x105, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<PivotItem, super = " + super.toString() + ">";
}


}

