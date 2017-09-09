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


public class DataLabels extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208b3, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public DataLabels (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #485
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: DataLabels
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 49 functions.
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

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(0);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public Border getAxBorder ()
    throws ActiveXException {
    // memid = 0x80

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80, AX_PROPERTYGET, false, args);
    Border result = new Border(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public Interior getAxInterior ()
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x81, AX_PROPERTYGET, false, args);
    Interior result = new Interior(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ChartFillFormat getAxFill ()
    throws ActiveXException {
    // memid = 0x67f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67f, AX_PROPERTYGET, false, args);
    ChartFillFormat result = new ChartFillFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void _Dummy9 ()
    throws ActiveXException {
    // memid = 0x10009

    Vector args = new Vector(0);
    axInvoke(0x10009, AX_INVOKE, true, args);
  }

  public void _Dummy10 ()
    throws ActiveXException {
    // memid = 0x1000a

    Vector args = new Vector(0);
    axInvoke(0x1000a, AX_INVOKE, true, args);
  }

  public Font getAxFont ()
    throws ActiveXException {
    // memid = 0x92

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x92, AX_PROPERTYGET, false, args);
    Font result = new Font(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxHorizontalAlignment ()
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x88, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxHorizontalAlignment (Variant param1)
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x88, AX_PROPERTYSET, true, args);
  }

  public void _Dummy13 ()
    throws ActiveXException {
    // memid = 0x1000d

    Vector args = new Vector(0);
    axInvoke(0x1000d, AX_INVOKE, true, args);
  }

  public Variant getAxOrientation ()
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x86, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxOrientation (Variant param1)
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x86, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShadow ()
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShadow (boolean param1)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67, AX_PROPERTYSET, true, args);
  }

  public void _Dummy16 ()
    throws ActiveXException {
    // memid = 0x10010

    Vector args = new Vector(0);
    axInvoke(0x10010, AX_INVOKE, true, args);
  }

  public void _Dummy17 ()
    throws ActiveXException {
    // memid = 0x10011

    Vector args = new Vector(0);
    axInvoke(0x10011, AX_INVOKE, true, args);
  }

  public Variant getAxVerticalAlignment ()
    throws ActiveXException {
    // memid = 0x89

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x89, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxVerticalAlignment (Variant param1)
    throws ActiveXException {
    // memid = 0x89

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x89, AX_PROPERTYSET, true, args);
  }

  public int getAxReadingOrder ()
    throws ActiveXException {
    // memid = 0x3cf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3cf, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxReadingOrder (int param1)
    throws ActiveXException {
    // memid = 0x3cf

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3cf, AX_PROPERTYSET, true, args);
  }

  public Variant getAxAutoScaleFont ()
    throws ActiveXException {
    // memid = 0x5f5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5f5, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxAutoScaleFont (Variant param1)
    throws ActiveXException {
    // memid = 0x5f5

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5f5, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAutoText ()
    throws ActiveXException {
    // memid = 0x87

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x87, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoText (boolean param1)
    throws ActiveXException {
    // memid = 0x87

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x87, AX_PROPERTYSET, true, args);
  }

  public String getAxNumberFormat ()
    throws ActiveXException {
    // memid = 0xc1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc1, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxNumberFormat (String param1)
    throws ActiveXException {
    // memid = 0xc1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc1, AX_PROPERTYSET, true, args);
  }

  public boolean getAxNumberFormatLinked ()
    throws ActiveXException {
    // memid = 0xc2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc2, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxNumberFormatLinked (boolean param1)
    throws ActiveXException {
    // memid = 0xc2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc2, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShowLegendKey ()
    throws ActiveXException {
    // memid = 0xab

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xab, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowLegendKey (boolean param1)
    throws ActiveXException {
    // memid = 0xab

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xab, AX_PROPERTYSET, true, args);
  }

  public Variant getAxType ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxType (Variant param1)
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6c, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlDataLabelPosition
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

  public int getAxCount ()
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x76, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public DataLabel Item (Variant param1)
    throws ActiveXException {
    // memid = 0xaa

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xaa, AX_INVOKE, false, args);
    DataLabel result = new DataLabel(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Object _NewEnum ()
    throws ActiveXException {
    // memid = 0xfffffffc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xfffffffc, AX_INVOKE, false, args);
    Object result = vResult.getGenericValue();
    return result;
  }

@Override
public String toString() {
    return "<DataLabels, super = " + super.toString() + ">";
}


}

