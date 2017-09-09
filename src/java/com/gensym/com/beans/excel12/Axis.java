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


public class Axis extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20848, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Axis (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #474
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Axis
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 78 functions.
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

  public boolean getAxAxisBetweenCategories ()
    throws ActiveXException {
    // memid = 0x2d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAxisBetweenCategories (boolean param1)
    throws ActiveXException {
    // memid = 0x2d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2d, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlAxisGroup
  public int getAxAxisGroup ()
    throws ActiveXException {
    // memid = 0x2f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public AxisTitle getAxAxisTitle ()
    throws ActiveXException {
    // memid = 0x52

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x52, AX_PROPERTYGET, false, args);
    AxisTitle result = new AxisTitle(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Border getAxBorder ()
    throws ActiveXException {
    // memid = 0x80

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80, AX_PROPERTYGET, false, args);
    Border result = new Border(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxCategoryNames ()
    throws ActiveXException {
    // memid = 0x9c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x9c, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxCategoryNames (Variant param1)
    throws ActiveXException {
    // memid = 0x9c

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x9c, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlAxisCrosses
  public int getAxCrosses ()
    throws ActiveXException {
    // memid = 0x2a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCrosses (int param1)
    throws ActiveXException {
    // memid = 0x2a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2a, AX_PROPERTYSET, true, args);
  }

  public double getAxCrossesAt ()
    throws ActiveXException {
    // memid = 0x2b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxCrossesAt (double param1)
    throws ActiveXException {
    // memid = 0x2b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2b, AX_PROPERTYSET, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public boolean getAxHasMajorGridlines ()
    throws ActiveXException {
    // memid = 0x18

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x18, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasMajorGridlines (boolean param1)
    throws ActiveXException {
    // memid = 0x18

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x18, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasMinorGridlines ()
    throws ActiveXException {
    // memid = 0x19

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x19, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasMinorGridlines (boolean param1)
    throws ActiveXException {
    // memid = 0x19

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x19, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasTitle ()
    throws ActiveXException {
    // memid = 0x36

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x36, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasTitle (boolean param1)
    throws ActiveXException {
    // memid = 0x36

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x36, AX_PROPERTYSET, true, args);
  }

  public Gridlines getAxMajorGridlines ()
    throws ActiveXException {
    // memid = 0x59

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x59, AX_PROPERTYGET, false, args);
    Gridlines result = new Gridlines(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlTickMark
  public int getAxMajorTickMark ()
    throws ActiveXException {
    // memid = 0x1a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMajorTickMark (int param1)
    throws ActiveXException {
    // memid = 0x1a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1a, AX_PROPERTYSET, true, args);
  }

  public double getAxMajorUnit ()
    throws ActiveXException {
    // memid = 0x25

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x25, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxMajorUnit (double param1)
    throws ActiveXException {
    // memid = 0x25

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x25, AX_PROPERTYSET, true, args);
  }

  public boolean getAxMajorUnitIsAuto ()
    throws ActiveXException {
    // memid = 0x26

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x26, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxMajorUnitIsAuto (boolean param1)
    throws ActiveXException {
    // memid = 0x26

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x26, AX_PROPERTYSET, true, args);
  }

  public double getAxMaximumScale ()
    throws ActiveXException {
    // memid = 0x23

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x23, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxMaximumScale (double param1)
    throws ActiveXException {
    // memid = 0x23

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x23, AX_PROPERTYSET, true, args);
  }

  public boolean getAxMaximumScaleIsAuto ()
    throws ActiveXException {
    // memid = 0x24

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x24, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxMaximumScaleIsAuto (boolean param1)
    throws ActiveXException {
    // memid = 0x24

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x24, AX_PROPERTYSET, true, args);
  }

  public double getAxMinimumScale ()
    throws ActiveXException {
    // memid = 0x21

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x21, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxMinimumScale (double param1)
    throws ActiveXException {
    // memid = 0x21

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x21, AX_PROPERTYSET, true, args);
  }

  public boolean getAxMinimumScaleIsAuto ()
    throws ActiveXException {
    // memid = 0x22

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x22, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxMinimumScaleIsAuto (boolean param1)
    throws ActiveXException {
    // memid = 0x22

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x22, AX_PROPERTYSET, true, args);
  }

  public Gridlines getAxMinorGridlines ()
    throws ActiveXException {
    // memid = 0x5a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a, AX_PROPERTYGET, false, args);
    Gridlines result = new Gridlines(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlTickMark
  public int getAxMinorTickMark ()
    throws ActiveXException {
    // memid = 0x1b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMinorTickMark (int param1)
    throws ActiveXException {
    // memid = 0x1b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1b, AX_PROPERTYSET, true, args);
  }

  public double getAxMinorUnit ()
    throws ActiveXException {
    // memid = 0x27

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x27, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxMinorUnit (double param1)
    throws ActiveXException {
    // memid = 0x27

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x27, AX_PROPERTYSET, true, args);
  }

  public boolean getAxMinorUnitIsAuto ()
    throws ActiveXException {
    // memid = 0x28

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x28, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxMinorUnitIsAuto (boolean param1)
    throws ActiveXException {
    // memid = 0x28

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x28, AX_PROPERTYSET, true, args);
  }

  public boolean getAxReversePlotOrder ()
    throws ActiveXException {
    // memid = 0x2c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxReversePlotOrder (boolean param1)
    throws ActiveXException {
    // memid = 0x2c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2c, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlScaleType
  public int getAxScaleType ()
    throws ActiveXException {
    // memid = 0x29

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x29, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxScaleType (int param1)
    throws ActiveXException {
    // memid = 0x29

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x29, AX_PROPERTYSET, true, args);
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(0);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

    // Enumeration type = XlTickLabelPosition
  public int getAxTickLabelPosition ()
    throws ActiveXException {
    // memid = 0x1c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxTickLabelPosition (int param1)
    throws ActiveXException {
    // memid = 0x1c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1c, AX_PROPERTYSET, true, args);
  }

  public TickLabels getAxTickLabels ()
    throws ActiveXException {
    // memid = 0x5b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5b, AX_PROPERTYGET, false, args);
    TickLabels result = new TickLabels(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxTickLabelSpacing ()
    throws ActiveXException {
    // memid = 0x1d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxTickLabelSpacing (int param1)
    throws ActiveXException {
    // memid = 0x1d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1d, AX_PROPERTYSET, true, args);
  }

  public int getAxTickMarkSpacing ()
    throws ActiveXException {
    // memid = 0x1f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxTickMarkSpacing (int param1)
    throws ActiveXException {
    // memid = 0x1f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1f, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlAxisType
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

    // Enumeration type = XlTimeUnit
  public int getAxBaseUnit ()
    throws ActiveXException {
    // memid = 0x66f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x66f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxBaseUnit (int param1)
    throws ActiveXException {
    // memid = 0x66f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x66f, AX_PROPERTYSET, true, args);
  }

  public boolean getAxBaseUnitIsAuto ()
    throws ActiveXException {
    // memid = 0x670

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x670, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxBaseUnitIsAuto (boolean param1)
    throws ActiveXException {
    // memid = 0x670

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x670, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlTimeUnit
  public int getAxMajorUnitScale ()
    throws ActiveXException {
    // memid = 0x671

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x671, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMajorUnitScale (int param1)
    throws ActiveXException {
    // memid = 0x671

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x671, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlTimeUnit
  public int getAxMinorUnitScale ()
    throws ActiveXException {
    // memid = 0x672

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x672, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMinorUnitScale (int param1)
    throws ActiveXException {
    // memid = 0x672

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x672, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlCategoryType
  public int getAxCategoryType ()
    throws ActiveXException {
    // memid = 0x673

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x673, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCategoryType (int param1)
    throws ActiveXException {
    // memid = 0x673

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x673, AX_PROPERTYSET, true, args);
  }

  public double getAxLeft ()
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7f, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double getAxTop ()
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7e, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double getAxWidth ()
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7a, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double getAxHeight ()
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7b, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

@Override
public String toString() {
    return "<Axis, super = " + super.toString() + ">";
}


}

