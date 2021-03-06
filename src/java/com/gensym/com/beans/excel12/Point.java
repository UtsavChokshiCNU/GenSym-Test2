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


public class Point extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2086a, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Point (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #481
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Point
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 52 functions.
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

  public void ApplyDataLabels (int param1)
    throws ActiveXException {
    // memid = 0x97

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x97, AX_INVOKE, true, args);
  }

  public void ApplyDataLabels (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x97

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x97, AX_INVOKE, true, args);
  }

  public void ApplyDataLabels (int param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x97

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x97, AX_INVOKE, true, args);
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

  public void Copy ()
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(0);
    axInvoke(0x227, AX_INVOKE, true, args);
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

  public int getAxExplosion ()
    throws ActiveXException {
    // memid = 0xb6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxExplosion (int param1)
    throws ActiveXException {
    // memid = 0xb6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xb6, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasDataLabel ()
    throws ActiveXException {
    // memid = 0x4d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasDataLabel (boolean param1)
    throws ActiveXException {
    // memid = 0x4d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4d, AX_PROPERTYSET, true, args);
  }

  public Interior getAxInterior ()
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x81, AX_PROPERTYGET, false, args);
    Interior result = new Interior(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxInvertIfNegative ()
    throws ActiveXException {
    // memid = 0x84

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x84, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxInvertIfNegative (boolean param1)
    throws ActiveXException {
    // memid = 0x84

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x84, AX_PROPERTYSET, true, args);
  }

  public int getAxMarkerBackgroundColor ()
    throws ActiveXException {
    // memid = 0x49

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x49, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMarkerBackgroundColor (int param1)
    throws ActiveXException {
    // memid = 0x49

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x49, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlColorIndex
  public int getAxMarkerBackgroundColorIndex ()
    throws ActiveXException {
    // memid = 0x4a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMarkerBackgroundColorIndex (int param1)
    throws ActiveXException {
    // memid = 0x4a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4a, AX_PROPERTYSET, true, args);
  }

  public int getAxMarkerForegroundColor ()
    throws ActiveXException {
    // memid = 0x4b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMarkerForegroundColor (int param1)
    throws ActiveXException {
    // memid = 0x4b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlColorIndex
  public int getAxMarkerForegroundColorIndex ()
    throws ActiveXException {
    // memid = 0x4c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMarkerForegroundColorIndex (int param1)
    throws ActiveXException {
    // memid = 0x4c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4c, AX_PROPERTYSET, true, args);
  }

  public int getAxMarkerSize ()
    throws ActiveXException {
    // memid = 0xe7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xe7, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMarkerSize (int param1)
    throws ActiveXException {
    // memid = 0xe7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xe7, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlMarkerStyle
  public int getAxMarkerStyle ()
    throws ActiveXException {
    // memid = 0x48

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x48, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMarkerStyle (int param1)
    throws ActiveXException {
    // memid = 0x48

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x48, AX_PROPERTYSET, true, args);
  }

  public void Paste ()
    throws ActiveXException {
    // memid = 0xd3

    Vector args = new Vector(0);
    axInvoke(0xd3, AX_INVOKE, true, args);
  }

    // Enumeration type = XlChartPictureType
  public int getAxPictureType ()
    throws ActiveXException {
    // memid = 0xa1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa1, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPictureType (int param1)
    throws ActiveXException {
    // memid = 0xa1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xa1, AX_PROPERTYSET, true, args);
  }

  public int getAxPictureUnit ()
    throws ActiveXException {
    // memid = 0xa2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa2, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPictureUnit (int param1)
    throws ActiveXException {
    // memid = 0xa2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xa2, AX_PROPERTYSET, true, args);
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(0);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public boolean getAxApplyPictToSides ()
    throws ActiveXException {
    // memid = 0x67b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxApplyPictToSides (boolean param1)
    throws ActiveXException {
    // memid = 0x67b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67b, AX_PROPERTYSET, true, args);
  }

  public boolean getAxApplyPictToFront ()
    throws ActiveXException {
    // memid = 0x67c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxApplyPictToFront (boolean param1)
    throws ActiveXException {
    // memid = 0x67c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67c, AX_PROPERTYSET, true, args);
  }

  public boolean getAxApplyPictToEnd ()
    throws ActiveXException {
    // memid = 0x67d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxApplyPictToEnd (boolean param1)
    throws ActiveXException {
    // memid = 0x67d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67d, AX_PROPERTYSET, true, args);
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

  public boolean getAxSecondaryPlot ()
    throws ActiveXException {
    // memid = 0x67e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSecondaryPlot (boolean param1)
    throws ActiveXException {
    // memid = 0x67e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67e, AX_PROPERTYSET, true, args);
  }

  public ChartFillFormat getAxFill ()
    throws ActiveXException {
    // memid = 0x67f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67f, AX_PROPERTYGET, false, args);
    ChartFillFormat result = new ChartFillFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

@Override
public String toString() {
    return "<Point, super = " + super.toString() + ">";
}


}

