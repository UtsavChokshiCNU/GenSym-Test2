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


public class PivotField extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20874, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public PivotField (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #383
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: PivotField
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 72 functions.
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

  public PivotTable getAxParent ()
    throws ActiveXException {
    // memid = 0x96

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x96, AX_PROPERTYGET, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlPivotFieldCalculation
  public int getAxCalculation ()
    throws ActiveXException {
    // memid = 0x13c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x13c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCalculation (int param1)
    throws ActiveXException {
    // memid = 0x13c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x13c, AX_PROPERTYSET, true, args);
  }

  public PivotField getAxChildField ()
    throws ActiveXException {
    // memid = 0x2e0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2e0, AX_PROPERTYGET, false, args);
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

  public String getAxCurrentPage ()
    throws ActiveXException {
    // memid = 0x2e2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2e2, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCurrentPage (String param1)
    throws ActiveXException {
    // memid = 0x2e2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2e2, AX_PROPERTYSET, true, args);
  }

  public Range getAxDataRange ()
    throws ActiveXException {
    // memid = 0x2d0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d0, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlPivotFieldDataType
  public int getAxDataType ()
    throws ActiveXException {
    // memid = 0x2d2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d2, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
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

    // Enumeration type = XlConsolidationFunction
  public int getAxFunction ()
    throws ActiveXException {
    // memid = 0x383

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x383, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxFunction (int param1)
    throws ActiveXException {
    // memid = 0x383

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x383, AX_PROPERTYSET, true, args);
  }

  public Variant getAxGroupLevel ()
    throws ActiveXException {
    // memid = 0x2d3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxHiddenItems ()
    throws ActiveXException {
    // memid = 0x2d8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d8, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxHiddenItems (Variant param1)
    throws ActiveXException {
    // memid = 0x2d8

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2d8, AX_PROPERTYGET, false, args);
    return vResult;
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

    // Enumeration type = XlPivotFieldOrientation
  public int getAxOrientation ()
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x86, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxOrientation (int param1)
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x86, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShowAllItems ()
    throws ActiveXException {
    // memid = 0x1c4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1c4, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowAllItems (boolean param1)
    throws ActiveXException {
    // memid = 0x1c4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1c4, AX_PROPERTYSET, true, args);
  }

  public PivotField getAxParentField ()
    throws ActiveXException {
    // memid = 0x2dc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2dc, AX_PROPERTYGET, false, args);
    PivotField result = new PivotField(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxParentItems ()
    throws ActiveXException {
    // memid = 0x2d9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d9, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxParentItems (Variant param1)
    throws ActiveXException {
    // memid = 0x2d9

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2d9, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant PivotItems ()
    throws ActiveXException {
    // memid = 0x2e1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2e1, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant PivotItems (Variant param1)
    throws ActiveXException {
    // memid = 0x2e1

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2e1, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant getAxPosition ()
    throws ActiveXException {
    // memid = 0x85

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x85, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxPosition (Variant param1)
    throws ActiveXException {
    // memid = 0x85

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x85, AX_PROPERTYSET, true, args);
  }

  public String getAxSourceName ()
    throws ActiveXException {
    // memid = 0x2d1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d1, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Variant Subtotals ()
    throws ActiveXException {
    // memid = 0x2dd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2dd, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Subtotals (Variant param1)
    throws ActiveXException {
    // memid = 0x2dd

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2dd, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant getAxBaseField ()
    throws ActiveXException {
    // memid = 0x2de

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2de, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxBaseField (Variant param1)
    throws ActiveXException {
    // memid = 0x2de

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x2de, AX_PROPERTYSET, true, args);
  }

  public Variant getAxBaseItem ()
    throws ActiveXException {
    // memid = 0x2df

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2df, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxBaseItem (Variant param1)
    throws ActiveXException {
    // memid = 0x2df

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x2df, AX_PROPERTYSET, true, args);
  }

  public Variant getAxTotalLevels ()
    throws ActiveXException {
    // memid = 0x2d4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d4, AX_PROPERTYGET, false, args);
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

  public Variant getAxVisibleItems ()
    throws ActiveXException {
    // memid = 0x2d7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d7, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxVisibleItems (Variant param1)
    throws ActiveXException {
    // memid = 0x2d7

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2d7, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public CalculatedItems CalculatedItems ()
    throws ActiveXException {
    // memid = 0x5e3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e3, AX_INVOKE, false, args);
    CalculatedItems result = new CalculatedItems(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public boolean getAxDragToColumn ()
    throws ActiveXException {
    // memid = 0x5e4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e4, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDragToColumn (boolean param1)
    throws ActiveXException {
    // memid = 0x5e4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e4, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDragToHide ()
    throws ActiveXException {
    // memid = 0x5e5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDragToHide (boolean param1)
    throws ActiveXException {
    // memid = 0x5e5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e5, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDragToPage ()
    throws ActiveXException {
    // memid = 0x5e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e6, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDragToPage (boolean param1)
    throws ActiveXException {
    // memid = 0x5e6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e6, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDragToRow ()
    throws ActiveXException {
    // memid = 0x5e7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e7, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDragToRow (boolean param1)
    throws ActiveXException {
    // memid = 0x5e7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e7, AX_PROPERTYSET, true, args);
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

  public boolean getAxIsCalculated ()
    throws ActiveXException {
    // memid = 0x5e8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e8, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
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

  public boolean getAxServerBased ()
    throws ActiveXException {
    // memid = 0x5e9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e9, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxServerBased (boolean param1)
    throws ActiveXException {
    // memid = 0x5e9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e9, AX_PROPERTYSET, true, args);
  }

  public void AutoSort (int param1, String param2)
    throws ActiveXException {
    // memid = 0x5ea

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x5ea, AX_INVOKE, true, args);
  }

  public void AutoShow (int param1, int param2, int param3, String param4)
    throws ActiveXException {
    // memid = 0x5eb

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    axInvoke(0x5eb, AX_INVOKE, true, args);
  }

  public int getAxAutoSortOrder ()
    throws ActiveXException {
    // memid = 0x5ec

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5ec, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxAutoSortField ()
    throws ActiveXException {
    // memid = 0x5ed

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5ed, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public int getAxAutoShowType ()
    throws ActiveXException {
    // memid = 0x5ee

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5ee, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxAutoShowRange ()
    throws ActiveXException {
    // memid = 0x5ef

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5ef, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxAutoShowCount ()
    throws ActiveXException {
    // memid = 0x5f0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5f0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxAutoShowField ()
    throws ActiveXException {
    // memid = 0x5f1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5f1, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

@Override
public String toString() {
    return "<PivotField, super = " + super.toString() + ">";
}


}

