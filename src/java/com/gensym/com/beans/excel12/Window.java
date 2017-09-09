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


public class Window extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20893, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Window (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #345
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Window
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

  public void Activate ()
    throws ActiveXException {
    // memid = 0x130

    Vector args = new Vector(0);
    axInvoke(0x130, AX_INVOKE, true, args);
  }

  public void ActivateNext ()
    throws ActiveXException {
    // memid = 0x45b

    Vector args = new Vector(0);
    axInvoke(0x45b, AX_INVOKE, true, args);
  }

  public void ActivatePrevious ()
    throws ActiveXException {
    // memid = 0x45c

    Vector args = new Vector(0);
    axInvoke(0x45c, AX_INVOKE, true, args);
  }

  public Range getAxActiveCell ()
    throws ActiveXException {
    // memid = 0x131

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x131, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ExcelChart getAxActiveChart ()
    throws ActiveXException {
    // memid = 0xb7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb7, AX_PROPERTYGET, false, args);
    ExcelChart result = new ExcelChart(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Pane getAxActivePane ()
    throws ActiveXException {
    // memid = 0x282

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x282, AX_PROPERTYGET, false, args);
    Pane result = new Pane(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable getAxActiveSheet ()
    throws ActiveXException {
    // memid = 0x133

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x133, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Variant getAxCaption ()
    throws ActiveXException {
    // memid = 0x8b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8b, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxCaption (Variant param1)
    throws ActiveXException {
    // memid = 0x8b

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x8b, AX_PROPERTYSET, true, args);
  }

  public void Close ()
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(0);
    axInvoke(0x115, AX_INVOKE, true, args);
  }

  public void Close (Variant param1)
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x115, AX_INVOKE, true, args);
  }

  public void Close (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x115, AX_INVOKE, true, args);
  }

  public void Close (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x115, AX_INVOKE, true, args);
  }

  public boolean getAxDisplayFormulas ()
    throws ActiveXException {
    // memid = 0x284

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x284, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayFormulas (boolean param1)
    throws ActiveXException {
    // memid = 0x284

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x284, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayGridlines ()
    throws ActiveXException {
    // memid = 0x285

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x285, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayGridlines (boolean param1)
    throws ActiveXException {
    // memid = 0x285

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x285, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayHeadings ()
    throws ActiveXException {
    // memid = 0x286

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x286, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayHeadings (boolean param1)
    throws ActiveXException {
    // memid = 0x286

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x286, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayHorizontalScrollBar ()
    throws ActiveXException {
    // memid = 0x399

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x399, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayHorizontalScrollBar (boolean param1)
    throws ActiveXException {
    // memid = 0x399

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x399, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayOutline ()
    throws ActiveXException {
    // memid = 0x287

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x287, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayOutline (boolean param1)
    throws ActiveXException {
    // memid = 0x287

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x287, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayRightToLeft ()
    throws ActiveXException {
    // memid = 0x288

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x288, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayRightToLeft (boolean param1)
    throws ActiveXException {
    // memid = 0x288

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x288, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayVerticalScrollBar ()
    throws ActiveXException {
    // memid = 0x39a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x39a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayVerticalScrollBar (boolean param1)
    throws ActiveXException {
    // memid = 0x39a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x39a, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayWorkbookTabs ()
    throws ActiveXException {
    // memid = 0x39b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x39b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayWorkbookTabs (boolean param1)
    throws ActiveXException {
    // memid = 0x39b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x39b, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayZeros ()
    throws ActiveXException {
    // memid = 0x289

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x289, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayZeros (boolean param1)
    throws ActiveXException {
    // memid = 0x289

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x289, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableResize ()
    throws ActiveXException {
    // memid = 0x4a8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4a8, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableResize (boolean param1)
    throws ActiveXException {
    // memid = 0x4a8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4a8, AX_PROPERTYSET, true, args);
  }

  public boolean getAxFreezePanes ()
    throws ActiveXException {
    // memid = 0x28a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x28a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxFreezePanes (boolean param1)
    throws ActiveXException {
    // memid = 0x28a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x28a, AX_PROPERTYSET, true, args);
  }

  public int getAxGridlineColor ()
    throws ActiveXException {
    // memid = 0x28b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x28b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxGridlineColor (int param1)
    throws ActiveXException {
    // memid = 0x28b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x28b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlColorIndex
  public int getAxGridlineColorIndex ()
    throws ActiveXException {
    // memid = 0x28c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x28c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxGridlineColorIndex (int param1)
    throws ActiveXException {
    // memid = 0x28c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x28c, AX_PROPERTYSET, true, args);
  }

  public double getAxHeight ()
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7b, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxHeight (double param1)
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7b, AX_PROPERTYSET, true, args);
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x1e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void LargeScroll ()
    throws ActiveXException {
    // memid = 0x223

    Vector args = new Vector(0);
    axInvoke(0x223, AX_INVOKE, true, args);
  }

  public void LargeScroll (Variant param1)
    throws ActiveXException {
    // memid = 0x223

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x223, AX_INVOKE, true, args);
  }

  public void LargeScroll (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x223

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x223, AX_INVOKE, true, args);
  }

  public void LargeScroll (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x223

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x223, AX_INVOKE, true, args);
  }

  public void LargeScroll (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x223

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x223, AX_INVOKE, true, args);
  }

  public double getAxLeft ()
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7f, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxLeft (double param1)
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7f, AX_PROPERTYSET, true, args);
  }

  public Window NewWindow ()
    throws ActiveXException {
    // memid = 0x118

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x118, AX_INVOKE, false, args);
    Window result = new Window(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxOnWindow ()
    throws ActiveXException {
    // memid = 0x26f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x26f, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnWindow (String param1)
    throws ActiveXException {
    // memid = 0x26f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x26f, AX_PROPERTYSET, true, args);
  }

  public Panes getAxPanes ()
    throws ActiveXException {
    // memid = 0x28d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x28d, AX_PROPERTYGET, false, args);
    Panes result = new Panes(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void PrintOut ()
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(0);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintPreview ()
    throws ActiveXException {
    // memid = 0x119

    Vector args = new Vector(0);
    axInvoke(0x119, AX_INVOKE, true, args);
  }

  public void PrintPreview (Variant param1)
    throws ActiveXException {
    // memid = 0x119

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x119, AX_INVOKE, true, args);
  }

  public Range getAxRangeSelection ()
    throws ActiveXException {
    // memid = 0x4a5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4a5, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxScrollColumn ()
    throws ActiveXException {
    // memid = 0x28e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x28e, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxScrollColumn (int param1)
    throws ActiveXException {
    // memid = 0x28e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x28e, AX_PROPERTYSET, true, args);
  }

  public int getAxScrollRow ()
    throws ActiveXException {
    // memid = 0x28f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x28f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxScrollRow (int param1)
    throws ActiveXException {
    // memid = 0x28f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x28f, AX_PROPERTYSET, true, args);
  }

  public void ScrollWorkbookTabs ()
    throws ActiveXException {
    // memid = 0x296

    Vector args = new Vector(0);
    axInvoke(0x296, AX_INVOKE, true, args);
  }

  public void ScrollWorkbookTabs (Variant param1)
    throws ActiveXException {
    // memid = 0x296

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x296, AX_INVOKE, true, args);
  }

  public void ScrollWorkbookTabs (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x296

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x296, AX_INVOKE, true, args);
  }

  public Sheets getAxSelectedSheets ()
    throws ActiveXException {
    // memid = 0x290

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x290, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable getAxSelection ()
    throws ActiveXException {
    // memid = 0x93

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x93, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void SmallScroll ()
    throws ActiveXException {
    // memid = 0x224

    Vector args = new Vector(0);
    axInvoke(0x224, AX_INVOKE, true, args);
  }

  public void SmallScroll (Variant param1)
    throws ActiveXException {
    // memid = 0x224

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x224, AX_INVOKE, true, args);
  }

  public void SmallScroll (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x224

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x224, AX_INVOKE, true, args);
  }

  public void SmallScroll (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x224

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x224, AX_INVOKE, true, args);
  }

  public void SmallScroll (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x224

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x224, AX_INVOKE, true, args);
  }

  public boolean getAxSplit ()
    throws ActiveXException {
    // memid = 0x291

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x291, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSplit (boolean param1)
    throws ActiveXException {
    // memid = 0x291

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x291, AX_PROPERTYSET, true, args);
  }

  public int getAxSplitColumn ()
    throws ActiveXException {
    // memid = 0x292

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x292, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSplitColumn (int param1)
    throws ActiveXException {
    // memid = 0x292

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x292, AX_PROPERTYSET, true, args);
  }

  public double getAxSplitHorizontal ()
    throws ActiveXException {
    // memid = 0x293

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x293, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxSplitHorizontal (double param1)
    throws ActiveXException {
    // memid = 0x293

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x293, AX_PROPERTYSET, true, args);
  }

  public int getAxSplitRow ()
    throws ActiveXException {
    // memid = 0x294

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x294, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSplitRow (int param1)
    throws ActiveXException {
    // memid = 0x294

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x294, AX_PROPERTYSET, true, args);
  }

  public double getAxSplitVertical ()
    throws ActiveXException {
    // memid = 0x295

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x295, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxSplitVertical (double param1)
    throws ActiveXException {
    // memid = 0x295

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x295, AX_PROPERTYSET, true, args);
  }

  public double getAxTabRatio ()
    throws ActiveXException {
    // memid = 0x2a1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2a1, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxTabRatio (double param1)
    throws ActiveXException {
    // memid = 0x2a1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2a1, AX_PROPERTYSET, true, args);
  }

  public double getAxTop ()
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7e, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxTop (double param1)
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7e, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlWindowType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public double getAxUsableHeight ()
    throws ActiveXException {
    // memid = 0x185

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x185, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double getAxUsableWidth ()
    throws ActiveXException {
    // memid = 0x186

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x186, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
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

  public Range getAxVisibleRange ()
    throws ActiveXException {
    // memid = 0x45e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x45e, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
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

  public void setAxWidth (double param1)
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7a, AX_PROPERTYSET, true, args);
  }

  public int getAxWindowNumber ()
    throws ActiveXException {
    // memid = 0x45f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x45f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = XlWindowState
  public int getAxWindowState ()
    throws ActiveXException {
    // memid = 0x18c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x18c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxWindowState (int param1)
    throws ActiveXException {
    // memid = 0x18c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x18c, AX_PROPERTYSET, true, args);
  }

  public Variant getAxZoom ()
    throws ActiveXException {
    // memid = 0x297

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x297, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxZoom (Variant param1)
    throws ActiveXException {
    // memid = 0x297

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x297, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlWindowView
  public int getAxView ()
    throws ActiveXException {
    // memid = 0x4aa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4aa, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxView (int param1)
    throws ActiveXException {
    // memid = 0x4aa

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4aa, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<Window, super = " + super.toString() + ">";
}


}

