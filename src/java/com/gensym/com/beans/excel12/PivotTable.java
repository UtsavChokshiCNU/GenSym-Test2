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


public class PivotTable extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20872, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public PivotTable (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #381
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: PivotTable
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 96 functions.
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

  public void AddFields ()
    throws ActiveXException {
    // memid = 0x2c4

    Vector args = new Vector(0);
    axInvoke(0x2c4, AX_INVOKE, true, args);
  }

  public void AddFields (Variant param1)
    throws ActiveXException {
    // memid = 0x2c4

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x2c4, AX_INVOKE, true, args);
  }

  public void AddFields (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x2c4

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x2c4, AX_INVOKE, true, args);
  }

  public void AddFields (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x2c4

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x2c4, AX_INVOKE, true, args);
  }

  public void AddFields (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x2c4

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x2c4, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable getAxColumnFields ()
    throws ActiveXException {
    // memid = 0x2c9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2c9, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable getAxColumnFields (Variant param1)
    throws ActiveXException {
    // memid = 0x2c9

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2c9, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxColumnGrand ()
    throws ActiveXException {
    // memid = 0x2b6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b6, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxColumnGrand (boolean param1)
    throws ActiveXException {
    // memid = 0x2b6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2b6, AX_PROPERTYSET, true, args);
  }

  public Range getAxColumnRange ()
    throws ActiveXException {
    // memid = 0x2be

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2be, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void ShowPages ()
    throws ActiveXException {
    // memid = 0x2c2

    Vector args = new Vector(0);
    axInvoke(0x2c2, AX_INVOKE, true, args);
  }

  public void ShowPages (Variant param1)
    throws ActiveXException {
    // memid = 0x2c2

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x2c2, AX_INVOKE, true, args);
  }

  public Range getAxDataBodyRange ()
    throws ActiveXException {
    // memid = 0x2c1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2c1, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable getAxDataFields ()
    throws ActiveXException {
    // memid = 0x2cb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2cb, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable getAxDataFields (Variant param1)
    throws ActiveXException {
    // memid = 0x2cb

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2cb, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Range getAxDataLabelRange ()
    throws ActiveXException {
    // memid = 0x2c0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2c0, AX_PROPERTYGET, false, args);
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

  public boolean getAxHasAutoFormat ()
    throws ActiveXException {
    // memid = 0x2b7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b7, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasAutoFormat (boolean param1)
    throws ActiveXException {
    // memid = 0x2b7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2b7, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxHiddenFields ()
    throws ActiveXException {
    // memid = 0x2c7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2c7, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable getAxHiddenFields (Variant param1)
    throws ActiveXException {
    // memid = 0x2c7

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2c7, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public String getAxInnerDetail ()
    throws ActiveXException {
    // memid = 0x2ba

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2ba, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxInnerDetail (String param1)
    throws ActiveXException {
    // memid = 0x2ba

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2ba, AX_PROPERTYSET, true, args);
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

  public ActiveXDispatchable getAxPageFields ()
    throws ActiveXException {
    // memid = 0x2ca

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2ca, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable getAxPageFields (Variant param1)
    throws ActiveXException {
    // memid = 0x2ca

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2ca, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Range getAxPageRange ()
    throws ActiveXException {
    // memid = 0x2bf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2bf, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxPageRangeCells ()
    throws ActiveXException {
    // memid = 0x5ca

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5ca, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable PivotFields ()
    throws ActiveXException {
    // memid = 0x2ce

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2ce, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable PivotFields (Variant param1)
    throws ActiveXException {
    // memid = 0x2ce

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2ce, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
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

  public boolean RefreshTable ()
    throws ActiveXException {
    // memid = 0x2cd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2cd, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public ActiveXDispatchable getAxRowFields ()
    throws ActiveXException {
    // memid = 0x2c8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2c8, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable getAxRowFields (Variant param1)
    throws ActiveXException {
    // memid = 0x2c8

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2c8, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxRowGrand ()
    throws ActiveXException {
    // memid = 0x2b5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxRowGrand (boolean param1)
    throws ActiveXException {
    // memid = 0x2b5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2b5, AX_PROPERTYSET, true, args);
  }

  public Range getAxRowRange ()
    throws ActiveXException {
    // memid = 0x2bd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2bd, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxSaveData ()
    throws ActiveXException {
    // memid = 0x2b4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b4, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSaveData (boolean param1)
    throws ActiveXException {
    // memid = 0x2b4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2b4, AX_PROPERTYSET, true, args);
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

  public Range getAxTableRange1 ()
    throws ActiveXException {
    // memid = 0x2bb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2bb, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxTableRange2 ()
    throws ActiveXException {
    // memid = 0x2bc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2bc, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
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

  public ActiveXDispatchable getAxVisibleFields ()
    throws ActiveXException {
    // memid = 0x2c6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2c6, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable getAxVisibleFields (Variant param1)
    throws ActiveXException {
    // memid = 0x2c6

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2c6, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public int getAxCacheIndex ()
    throws ActiveXException {
    // memid = 0x5cb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5cb, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCacheIndex (int param1)
    throws ActiveXException {
    // memid = 0x5cb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5cb, AX_PROPERTYSET, true, args);
  }

  public CalculatedFields CalculatedFields ()
    throws ActiveXException {
    // memid = 0x5cc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5cc, AX_INVOKE, false, args);
    CalculatedFields result = new CalculatedFields(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxDisplayErrorString ()
    throws ActiveXException {
    // memid = 0x5cd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5cd, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayErrorString (boolean param1)
    throws ActiveXException {
    // memid = 0x5cd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5cd, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayNullString ()
    throws ActiveXException {
    // memid = 0x5ce

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5ce, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayNullString (boolean param1)
    throws ActiveXException {
    // memid = 0x5ce

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5ce, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableDrilldown ()
    throws ActiveXException {
    // memid = 0x5cf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5cf, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableDrilldown (boolean param1)
    throws ActiveXException {
    // memid = 0x5cf

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5cf, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableFieldDialog ()
    throws ActiveXException {
    // memid = 0x5d0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d0, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableFieldDialog (boolean param1)
    throws ActiveXException {
    // memid = 0x5d0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5d0, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableWizard ()
    throws ActiveXException {
    // memid = 0x5d1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d1, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableWizard (boolean param1)
    throws ActiveXException {
    // memid = 0x5d1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5d1, AX_PROPERTYSET, true, args);
  }

  public String getAxErrorString ()
    throws ActiveXException {
    // memid = 0x5d2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d2, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxErrorString (String param1)
    throws ActiveXException {
    // memid = 0x5d2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5d2, AX_PROPERTYSET, true, args);
  }

  public double GetData (String param1)
    throws ActiveXException {
    // memid = 0x5d3

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x5d3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void ListFormulas ()
    throws ActiveXException {
    // memid = 0x5d4

    Vector args = new Vector(0);
    axInvoke(0x5d4, AX_INVOKE, true, args);
  }

  public boolean getAxManualUpdate ()
    throws ActiveXException {
    // memid = 0x5d5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxManualUpdate (boolean param1)
    throws ActiveXException {
    // memid = 0x5d5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5d5, AX_PROPERTYSET, true, args);
  }

  public boolean getAxMergeLabels ()
    throws ActiveXException {
    // memid = 0x5d6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d6, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxMergeLabels (boolean param1)
    throws ActiveXException {
    // memid = 0x5d6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5d6, AX_PROPERTYSET, true, args);
  }

  public String getAxNullString ()
    throws ActiveXException {
    // memid = 0x5d7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d7, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxNullString (String param1)
    throws ActiveXException {
    // memid = 0x5d7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5d7, AX_PROPERTYSET, true, args);
  }

  public PivotCache PivotCache ()
    throws ActiveXException {
    // memid = 0x5d8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d8, AX_INVOKE, false, args);
    PivotCache result = new PivotCache(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotFormulas PivotFormulas ()
    throws ActiveXException {
    // memid = 0x5d9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d9, AX_INVOKE, false, args);
    PivotFormulas result = new PivotFormulas(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void PivotTableWizard ()
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(0);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(9);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(10);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(11);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(12);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(13);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    args.addElement(param13);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(14);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    args.addElement(param13);
    args.addElement(param14);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(15);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    args.addElement(param13);
    args.addElement(param14);
    args.addElement(param15);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(16);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    args.addElement(param13);
    args.addElement(param14);
    args.addElement(param15);
    args.addElement(param16);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public boolean getAxSubtotalHiddenPageItems ()
    throws ActiveXException {
    // memid = 0x5da

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5da, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSubtotalHiddenPageItems (boolean param1)
    throws ActiveXException {
    // memid = 0x5da

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5da, AX_PROPERTYSET, true, args);
  }

  public int getAxPageFieldOrder ()
    throws ActiveXException {
    // memid = 0x595

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x595, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPageFieldOrder (int param1)
    throws ActiveXException {
    // memid = 0x595

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x595, AX_PROPERTYSET, true, args);
  }

  public String getAxPageFieldStyle ()
    throws ActiveXException {
    // memid = 0x5db

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5db, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxPageFieldStyle (String param1)
    throws ActiveXException {
    // memid = 0x5db

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5db, AX_PROPERTYSET, true, args);
  }

  public int getAxPageFieldWrapCount ()
    throws ActiveXException {
    // memid = 0x596

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x596, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPageFieldWrapCount (int param1)
    throws ActiveXException {
    // memid = 0x596

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x596, AX_PROPERTYSET, true, args);
  }

  public boolean getAxPreserveFormatting ()
    throws ActiveXException {
    // memid = 0x5dc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5dc, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPreserveFormatting (boolean param1)
    throws ActiveXException {
    // memid = 0x5dc

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5dc, AX_PROPERTYSET, true, args);
  }

  public void PivotSelect (String param1, int param2)
    throws ActiveXException {
    // memid = 0x5dd

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x5dd, AX_INVOKE, true, args);
  }

  public String getAxPivotSelection ()
    throws ActiveXException {
    // memid = 0x5de

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5de, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxPivotSelection (String param1)
    throws ActiveXException {
    // memid = 0x5de

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5de, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlPTSelectionMode
  public int getAxSelectionMode ()
    throws ActiveXException {
    // memid = 0x5df

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5df, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSelectionMode (int param1)
    throws ActiveXException {
    // memid = 0x5df

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5df, AX_PROPERTYSET, true, args);
  }

  public String getAxTableStyle ()
    throws ActiveXException {
    // memid = 0x5e0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxTableStyle (String param1)
    throws ActiveXException {
    // memid = 0x5e0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e0, AX_PROPERTYSET, true, args);
  }

  public String getAxTag ()
    throws ActiveXException {
    // memid = 0x5e1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e1, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxTag (String param1)
    throws ActiveXException {
    // memid = 0x5e1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e1, AX_PROPERTYSET, true, args);
  }

  public void Update ()
    throws ActiveXException {
    // memid = 0x2a8

    Vector args = new Vector(0);
    axInvoke(0x2a8, AX_INVOKE, true, args);
  }

  public String getAxVacatedStyle ()
    throws ActiveXException {
    // memid = 0x5e2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e2, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxVacatedStyle (String param1)
    throws ActiveXException {
    // memid = 0x5e2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e2, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<PivotTable, super = " + super.toString() + ">";
}


}

