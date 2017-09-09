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


public class PivotCache extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2441c, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public PivotCache (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #377
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: PivotCache
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 32 functions.
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

  public boolean getAxBackgroundQuery ()
    throws ActiveXException {
    // memid = 0x593

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x593, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxBackgroundQuery (boolean param1)
    throws ActiveXException {
    // memid = 0x593

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x593, AX_PROPERTYSET, true, args);
  }

  public Variant getAxConnection ()
    throws ActiveXException {
    // memid = 0x598

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x598, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxConnection (Variant param1)
    throws ActiveXException {
    // memid = 0x598

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x598, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableRefresh ()
    throws ActiveXException {
    // memid = 0x5c5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5c5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableRefresh (boolean param1)
    throws ActiveXException {
    // memid = 0x5c5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5c5, AX_PROPERTYSET, true, args);
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x1e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxMemoryUsed ()
    throws ActiveXException {
    // memid = 0x174

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x174, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxOptimizeCache ()
    throws ActiveXException {
    // memid = 0x594

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x594, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxOptimizeCache (boolean param1)
    throws ActiveXException {
    // memid = 0x594

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x594, AX_PROPERTYSET, true, args);
  }

  public int getAxRecordCount ()
    throws ActiveXException {
    // memid = 0x5c6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5c6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void Refresh ()
    throws ActiveXException {
    // memid = 0x589

    Vector args = new Vector(0);
    axInvoke(0x589, AX_INVOKE, true, args);
  }

  public Date getAxRefreshDate ()
    throws ActiveXException {
    // memid = 0x2b8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b8, AX_PROPERTYGET, false, args);
    Date result = vResult.getDateValue();
    return result;
  }

  public String getAxRefreshName ()
    throws ActiveXException {
    // memid = 0x2b9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b9, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxRefreshOnFileOpen ()
    throws ActiveXException {
    // memid = 0x5c7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5c7, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxRefreshOnFileOpen (boolean param1)
    throws ActiveXException {
    // memid = 0x5c7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5c7, AX_PROPERTYSET, true, args);
  }

  public Variant getAxSql ()
    throws ActiveXException {
    // memid = 0x5c8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5c8, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxSql (Variant param1)
    throws ActiveXException {
    // memid = 0x5c8

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5c8, AX_PROPERTYSET, true, args);
  }

  public boolean getAxSavePassword ()
    throws ActiveXException {
    // memid = 0x5c9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5c9, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSavePassword (boolean param1)
    throws ActiveXException {
    // memid = 0x5c9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5c9, AX_PROPERTYSET, true, args);
  }

  public Variant getAxSourceData ()
    throws ActiveXException {
    // memid = 0x2ae

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2ae, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxSourceData (Variant param1)
    throws ActiveXException {
    // memid = 0x2ae

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x2ae, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<PivotCache, super = " + super.toString() + ">";
}


}

