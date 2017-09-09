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


public class ChartGroup extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20859, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public ChartGroup (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #477
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: ChartGroup
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 58 functions.
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

    // Enumeration type = XlAxisGroup
  public int getAxAxisGroup ()
    throws ActiveXException {
    // memid = 0x2f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxAxisGroup (int param1)
    throws ActiveXException {
    // memid = 0x2f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2f, AX_PROPERTYSET, true, args);
  }

  public int getAxDoughnutHoleSize ()
    throws ActiveXException {
    // memid = 0x466

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x466, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDoughnutHoleSize (int param1)
    throws ActiveXException {
    // memid = 0x466

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x466, AX_PROPERTYSET, true, args);
  }

  public DownBars getAxDownBars ()
    throws ActiveXException {
    // memid = 0x8d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8d, AX_PROPERTYGET, false, args);
    DownBars result = new DownBars(vResult.getActiveXDispatchableValue());
    return result;
  }

  public DropLines getAxDropLines ()
    throws ActiveXException {
    // memid = 0x8e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8e, AX_PROPERTYGET, false, args);
    DropLines result = new DropLines(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxFirstSliceAngle ()
    throws ActiveXException {
    // memid = 0x3f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxFirstSliceAngle (int param1)
    throws ActiveXException {
    // memid = 0x3f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f, AX_PROPERTYSET, true, args);
  }

  public int getAxGapWidth ()
    throws ActiveXException {
    // memid = 0x33

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x33, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxGapWidth (int param1)
    throws ActiveXException {
    // memid = 0x33

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x33, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasDropLines ()
    throws ActiveXException {
    // memid = 0x3d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasDropLines (boolean param1)
    throws ActiveXException {
    // memid = 0x3d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3d, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasHiLoLines ()
    throws ActiveXException {
    // memid = 0x3e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasHiLoLines (boolean param1)
    throws ActiveXException {
    // memid = 0x3e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3e, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasRadarAxisLabels ()
    throws ActiveXException {
    // memid = 0x40

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x40, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasRadarAxisLabels (boolean param1)
    throws ActiveXException {
    // memid = 0x40

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x40, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasSeriesLines ()
    throws ActiveXException {
    // memid = 0x41

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x41, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasSeriesLines (boolean param1)
    throws ActiveXException {
    // memid = 0x41

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x41, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasUpDownBars ()
    throws ActiveXException {
    // memid = 0x42

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x42, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasUpDownBars (boolean param1)
    throws ActiveXException {
    // memid = 0x42

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x42, AX_PROPERTYSET, true, args);
  }

  public HiLoLines getAxHiLoLines ()
    throws ActiveXException {
    // memid = 0x8f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8f, AX_PROPERTYGET, false, args);
    HiLoLines result = new HiLoLines(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x1e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxOverlap ()
    throws ActiveXException {
    // memid = 0x38

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x38, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxOverlap (int param1)
    throws ActiveXException {
    // memid = 0x38

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x38, AX_PROPERTYSET, true, args);
  }

  public TickLabels getAxRadarAxisLabels ()
    throws ActiveXException {
    // memid = 0x90

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x90, AX_PROPERTYGET, false, args);
    TickLabels result = new TickLabels(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable SeriesCollection ()
    throws ActiveXException {
    // memid = 0x44

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x44, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable SeriesCollection (Variant param1)
    throws ActiveXException {
    // memid = 0x44

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x44, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public SeriesLines getAxSeriesLines ()
    throws ActiveXException {
    // memid = 0x91

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x91, AX_PROPERTYGET, false, args);
    SeriesLines result = new SeriesLines(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxSubType ()
    throws ActiveXException {
    // memid = 0x6d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSubType (int param1)
    throws ActiveXException {
    // memid = 0x6d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6d, AX_PROPERTYSET, true, args);
  }

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

  public UpBars getAxUpBars ()
    throws ActiveXException {
    // memid = 0x8c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8c, AX_PROPERTYGET, false, args);
    UpBars result = new UpBars(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxVaryByCategories ()
    throws ActiveXException {
    // memid = 0x3c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxVaryByCategories (boolean param1)
    throws ActiveXException {
    // memid = 0x3c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3c, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlSieRepresents
  public int getAxSizeRepresents ()
    throws ActiveXException {
    // memid = 0x674

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x674, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSizeRepresents (int param1)
    throws ActiveXException {
    // memid = 0x674

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x674, AX_PROPERTYSET, true, args);
  }

  public int getAxBubbleScale ()
    throws ActiveXException {
    // memid = 0x675

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x675, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxBubbleScale (int param1)
    throws ActiveXException {
    // memid = 0x675

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x675, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShowNegativeBubbles ()
    throws ActiveXException {
    // memid = 0x676

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x676, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowNegativeBubbles (boolean param1)
    throws ActiveXException {
    // memid = 0x676

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x676, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlChartSplitType
  public int getAxSplitType ()
    throws ActiveXException {
    // memid = 0x677

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x677, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSplitType (int param1)
    throws ActiveXException {
    // memid = 0x677

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x677, AX_PROPERTYSET, true, args);
  }

  public Variant getAxSplitValue ()
    throws ActiveXException {
    // memid = 0x678

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x678, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxSplitValue (Variant param1)
    throws ActiveXException {
    // memid = 0x678

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x678, AX_PROPERTYSET, true, args);
  }

  public int getAxSecondPlotSize ()
    throws ActiveXException {
    // memid = 0x679

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x679, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSecondPlotSize (int param1)
    throws ActiveXException {
    // memid = 0x679

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x679, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHas3DShading ()
    throws ActiveXException {
    // memid = 0x67a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHas3DShading (boolean param1)
    throws ActiveXException {
    // memid = 0x67a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67a, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<ChartGroup, super = " + super.toString() + ">";
}


}

