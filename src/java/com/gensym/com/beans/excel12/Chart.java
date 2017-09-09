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


public class Chart extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208d6, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Chart (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #171
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _Chart
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 158 functions.
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

  public void Copy ()
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(0);
    axInvoke(0x227, AX_INVOKE, true, args);
  }

  public void Copy (Variant param1)
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x227, AX_INVOKE, true, args);
  }

  public void Copy (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x227, AX_INVOKE, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public String getAxCodeName ()
    throws ActiveXException {
    // memid = 0x55d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x55d, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAx_CodeName ()
    throws ActiveXException {
    // memid = 0x80010000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010000, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAx_CodeName (String param1)
    throws ActiveXException {
    // memid = 0x80010000

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x80010000, AX_PROPERTYSET, true, args);
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x1e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void Move ()
    throws ActiveXException {
    // memid = 0x27d

    Vector args = new Vector(0);
    axInvoke(0x27d, AX_INVOKE, true, args);
  }

  public void Move (Variant param1)
    throws ActiveXException {
    // memid = 0x27d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x27d, AX_INVOKE, true, args);
  }

  public void Move (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x27d

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x27d, AX_INVOKE, true, args);
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

  public ActiveXDispatchable getAxNext ()
    throws ActiveXException {
    // memid = 0x1f6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f6, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public String getAxOnDoubleClick ()
    throws ActiveXException {
    // memid = 0x274

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x274, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnDoubleClick (String param1)
    throws ActiveXException {
    // memid = 0x274

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x274, AX_PROPERTYSET, true, args);
  }

  public String getAxOnSheetActivate ()
    throws ActiveXException {
    // memid = 0x407

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x407, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnSheetActivate (String param1)
    throws ActiveXException {
    // memid = 0x407

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x407, AX_PROPERTYSET, true, args);
  }

  public String getAxOnSheetDeactivate ()
    throws ActiveXException {
    // memid = 0x439

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x439, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnSheetDeactivate (String param1)
    throws ActiveXException {
    // memid = 0x439

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x439, AX_PROPERTYSET, true, args);
  }

  public PageSetup getAxPageSetup ()
    throws ActiveXException {
    // memid = 0x3e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e6, AX_PROPERTYGET, false, args);
    PageSetup result = new PageSetup(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable getAxPrevious ()
    throws ActiveXException {
    // memid = 0x1f7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f7, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
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

  public void Protect ()
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(0);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public boolean getAxProtectContents ()
    throws ActiveXException {
    // memid = 0x124

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x124, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxProtectDrawingObjects ()
    throws ActiveXException {
    // memid = 0x125

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x125, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxProtectionMode ()
    throws ActiveXException {
    // memid = 0x487

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x487, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void _Dummy23 ()
    throws ActiveXException {
    // memid = 0x10017

    Vector args = new Vector(0);
    axInvoke(0x10017, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(9);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(0);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public void Select (Variant param1)
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public void Unprotect ()
    throws ActiveXException {
    // memid = 0x11d

    Vector args = new Vector(0);
    axInvoke(0x11d, AX_INVOKE, true, args);
  }

  public void Unprotect (Variant param1)
    throws ActiveXException {
    // memid = 0x11d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x11d, AX_INVOKE, true, args);
  }

    // Enumeration type = XlSheetVisibility
  public int getAxVisible ()
    throws ActiveXException {
    // memid = 0x22e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x22e, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxVisible (int param1)
    throws ActiveXException {
    // memid = 0x22e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x22e, AX_PROPERTYSET, true, args);
  }

  public Shapes getAxShapes ()
    throws ActiveXException {
    // memid = 0x561

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x561, AX_PROPERTYGET, false, args);
    Shapes result = new Shapes(vResult.getActiveXDispatchableValue());
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

  public void ApplyDataLabels (int param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x97

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x97, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable Arcs ()
    throws ActiveXException {
    // memid = 0x2f8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2f8, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Arcs (Variant param1)
    throws ActiveXException {
    // memid = 0x2f8

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2f8, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ChartGroup getAxArea3DGroup ()
    throws ActiveXException {
    // memid = 0x11

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x11, AX_PROPERTYGET, false, args);
    ChartGroup result = new ChartGroup(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable AreaGroups ()
    throws ActiveXException {
    // memid = 0x9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x9, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable AreaGroups (Variant param1)
    throws ActiveXException {
    // memid = 0x9

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x9, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void AutoFormat (int param1)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public void AutoFormat (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public boolean getAxAutoScaling ()
    throws ActiveXException {
    // memid = 0x6b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoScaling (boolean param1)
    throws ActiveXException {
    // memid = 0x6b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6b, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable Axes (Variant param1, int param2)
    throws ActiveXException {
    // memid = 0x17

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x17, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void SetBackgroundPicture (String param1)
    throws ActiveXException {
    // memid = 0x4a4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4a4, AX_INVOKE, true, args);
  }

  public ChartGroup getAxBar3DGroup ()
    throws ActiveXException {
    // memid = 0x12

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x12, AX_PROPERTYGET, false, args);
    ChartGroup result = new ChartGroup(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable BarGroups ()
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable BarGroups (Variant param1)
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xa, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Buttons ()
    throws ActiveXException {
    // memid = 0x22d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x22d, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Buttons (Variant param1)
    throws ActiveXException {
    // memid = 0x22d

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x22d, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ChartArea getAxChartArea ()
    throws ActiveXException {
    // memid = 0x50

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x50, AX_PROPERTYGET, false, args);
    ChartArea result = new ChartArea(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable ChartGroups ()
    throws ActiveXException {
    // memid = 0x8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ChartGroups (Variant param1)
    throws ActiveXException {
    // memid = 0x8

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x8, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ChartObjects ()
    throws ActiveXException {
    // memid = 0x424

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x424, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ChartObjects (Variant param1)
    throws ActiveXException {
    // memid = 0x424

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x424, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ChartTitle getAxChartTitle ()
    throws ActiveXException {
    // memid = 0x51

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x51, AX_PROPERTYGET, false, args);
    ChartTitle result = new ChartTitle(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void ChartWizard ()
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(0);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1)
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0xc4

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0xc4

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
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0xc4

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
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public void ChartWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0xc4

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
    axInvoke(0xc4, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable CheckBoxes ()
    throws ActiveXException {
    // memid = 0x338

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x338, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable CheckBoxes (Variant param1)
    throws ActiveXException {
    // memid = 0x338

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x338, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void CheckSpelling ()
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(0);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public ChartGroup getAxColumn3DGroup ()
    throws ActiveXException {
    // memid = 0x13

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x13, AX_PROPERTYGET, false, args);
    ChartGroup result = new ChartGroup(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable ColumnGroups ()
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ColumnGroups (Variant param1)
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xb, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void CopyPicture (int param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0xd5

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0xd5, AX_INVOKE, true, args);
  }

  public Corners getAxCorners ()
    throws ActiveXException {
    // memid = 0x4f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4f, AX_PROPERTYGET, false, args);
    Corners result = new Corners(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void CreatePublisher (Variant param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2, int param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public DataTable getAxDataTable ()
    throws ActiveXException {
    // memid = 0x573

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x573, AX_PROPERTYGET, false, args);
    DataTable result = new DataTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxDepthPercent ()
    throws ActiveXException {
    // memid = 0x30

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x30, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDepthPercent (int param1)
    throws ActiveXException {
    // memid = 0x30

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x30, AX_PROPERTYSET, true, args);
  }

  public void Deselect ()
    throws ActiveXException {
    // memid = 0x460

    Vector args = new Vector(0);
    axInvoke(0x460, AX_INVOKE, true, args);
  }

    // Enumeration type = XlDisplayBlanksAs
  public int getAxDisplayBlanksAs ()
    throws ActiveXException {
    // memid = 0x5d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDisplayBlanksAs (int param1)
    throws ActiveXException {
    // memid = 0x5d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5d, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable DoughnutGroups ()
    throws ActiveXException {
    // memid = 0xe

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xe, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DoughnutGroups (Variant param1)
    throws ActiveXException {
    // memid = 0xe

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xe, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Drawings ()
    throws ActiveXException {
    // memid = 0x304

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x304, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Drawings (Variant param1)
    throws ActiveXException {
    // memid = 0x304

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x304, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DrawingObjects ()
    throws ActiveXException {
    // memid = 0x58

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x58, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DrawingObjects (Variant param1)
    throws ActiveXException {
    // memid = 0x58

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x58, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DropDowns ()
    throws ActiveXException {
    // memid = 0x344

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x344, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DropDowns (Variant param1)
    throws ActiveXException {
    // memid = 0x344

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x344, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public int getAxElevation ()
    throws ActiveXException {
    // memid = 0x31

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x31, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxElevation (int param1)
    throws ActiveXException {
    // memid = 0x31

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x31, AX_PROPERTYSET, true, args);
  }

  public Variant Evaluate (Variant param1)
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x1, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Evaluate (Variant param1)
    throws ActiveXException {
    // memid = 0xfffffffb

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xfffffffb, AX_INVOKE, false, args);
    return vResult;
  }

  public Floor getAxFloor ()
    throws ActiveXException {
    // memid = 0x53

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x53, AX_PROPERTYGET, false, args);
    Floor result = new Floor(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxGapDepth ()
    throws ActiveXException {
    // memid = 0x32

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x32, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxGapDepth (int param1)
    throws ActiveXException {
    // memid = 0x32

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x32, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable GroupBoxes ()
    throws ActiveXException {
    // memid = 0x342

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x342, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable GroupBoxes (Variant param1)
    throws ActiveXException {
    // memid = 0x342

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x342, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable GroupObjects ()
    throws ActiveXException {
    // memid = 0x459

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x459, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable GroupObjects (Variant param1)
    throws ActiveXException {
    // memid = 0x459

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x459, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Variant getAxHasAxis ()
    throws ActiveXException {
    // memid = 0x34

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x34, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxHasAxis (Variant param1)
    throws ActiveXException {
    // memid = 0x34

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x34, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxHasAxis (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x34

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x34, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxHasAxis (Variant param1)
    throws ActiveXException {
    // memid = 0x34

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x34, AX_PROPERTYSET, true, args);
  }

  public void setAxHasAxis (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x34

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x34, AX_PROPERTYSET, true, args);
  }

  public void setAxHasAxis (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x34

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x34, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasDataTable ()
    throws ActiveXException {
    // memid = 0x574

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x574, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasDataTable (boolean param1)
    throws ActiveXException {
    // memid = 0x574

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x574, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasLegend ()
    throws ActiveXException {
    // memid = 0x35

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x35, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasLegend (boolean param1)
    throws ActiveXException {
    // memid = 0x35

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x35, AX_PROPERTYSET, true, args);
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

  public int getAxHeightPercent ()
    throws ActiveXException {
    // memid = 0x37

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x37, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHeightPercent (int param1)
    throws ActiveXException {
    // memid = 0x37

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x37, AX_PROPERTYSET, true, args);
  }

  public Hyperlinks getAxHyperlinks ()
    throws ActiveXException {
    // memid = 0x571

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x571, AX_PROPERTYGET, false, args);
    Hyperlinks result = new Hyperlinks(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable Labels ()
    throws ActiveXException {
    // memid = 0x349

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x349, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Labels (Variant param1)
    throws ActiveXException {
    // memid = 0x349

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x349, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Legend getAxLegend ()
    throws ActiveXException {
    // memid = 0x54

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x54, AX_PROPERTYGET, false, args);
    Legend result = new Legend(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ChartGroup getAxLine3DGroup ()
    throws ActiveXException {
    // memid = 0x14

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x14, AX_PROPERTYGET, false, args);
    ChartGroup result = new ChartGroup(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable LineGroups ()
    throws ActiveXException {
    // memid = 0xc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable LineGroups (Variant param1)
    throws ActiveXException {
    // memid = 0xc

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xc, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Lines ()
    throws ActiveXException {
    // memid = 0x2ff

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2ff, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Lines (Variant param1)
    throws ActiveXException {
    // memid = 0x2ff

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2ff, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ListBoxes ()
    throws ActiveXException {
    // memid = 0x340

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x340, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ListBoxes (Variant param1)
    throws ActiveXException {
    // memid = 0x340

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x340, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ExcelChart Location (int param1)
    throws ActiveXException {
    // memid = 0x575

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x575, AX_INVOKE, false, args);
    ExcelChart result = new ExcelChart(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ExcelChart Location (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x575

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x575, AX_INVOKE, false, args);
    ExcelChart result = new ExcelChart(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable OLEObjects ()
    throws ActiveXException {
    // memid = 0x31f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x31f, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable OLEObjects (Variant param1)
    throws ActiveXException {
    // memid = 0x31f

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x31f, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable OptionButtons ()
    throws ActiveXException {
    // memid = 0x33a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x33a, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable OptionButtons (Variant param1)
    throws ActiveXException {
    // memid = 0x33a

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x33a, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Ovals ()
    throws ActiveXException {
    // memid = 0x321

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x321, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Ovals (Variant param1)
    throws ActiveXException {
    // memid = 0x321

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x321, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void Paste ()
    throws ActiveXException {
    // memid = 0xd3

    Vector args = new Vector(0);
    axInvoke(0xd3, AX_INVOKE, true, args);
  }

  public void Paste (Variant param1)
    throws ActiveXException {
    // memid = 0xd3

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xd3, AX_INVOKE, true, args);
  }

  public int getAxPerspective ()
    throws ActiveXException {
    // memid = 0x39

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x39, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPerspective (int param1)
    throws ActiveXException {
    // memid = 0x39

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x39, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable Pictures ()
    throws ActiveXException {
    // memid = 0x303

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x303, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Pictures (Variant param1)
    throws ActiveXException {
    // memid = 0x303

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x303, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ChartGroup getAxPie3DGroup ()
    throws ActiveXException {
    // memid = 0x15

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x15, AX_PROPERTYGET, false, args);
    ChartGroup result = new ChartGroup(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable PieGroups ()
    throws ActiveXException {
    // memid = 0xd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xd, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable PieGroups (Variant param1)
    throws ActiveXException {
    // memid = 0xd

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xd, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public PlotArea getAxPlotArea ()
    throws ActiveXException {
    // memid = 0x55

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x55, AX_PROPERTYGET, false, args);
    PlotArea result = new PlotArea(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxPlotVisibleOnly ()
    throws ActiveXException {
    // memid = 0x5c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPlotVisibleOnly (boolean param1)
    throws ActiveXException {
    // memid = 0x5c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5c, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable RadarGroups ()
    throws ActiveXException {
    // memid = 0xf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable RadarGroups (Variant param1)
    throws ActiveXException {
    // memid = 0xf

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xf, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Rectangles ()
    throws ActiveXException {
    // memid = 0x306

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x306, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Rectangles (Variant param1)
    throws ActiveXException {
    // memid = 0x306

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x306, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Variant getAxRightAngleAxes ()
    throws ActiveXException {
    // memid = 0x3a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxRightAngleAxes (Variant param1)
    throws ActiveXException {
    // memid = 0x3a

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3a, AX_PROPERTYSET, true, args);
  }

  public Variant getAxRotation ()
    throws ActiveXException {
    // memid = 0x3b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3b, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxRotation (Variant param1)
    throws ActiveXException {
    // memid = 0x3b

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3b, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable ScrollBars ()
    throws ActiveXException {
    // memid = 0x33e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x33e, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ScrollBars (Variant param1)
    throws ActiveXException {
    // memid = 0x33e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x33e, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
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

  public boolean getAxSizeWithWindow ()
    throws ActiveXException {
    // memid = 0x5e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSizeWithWindow (boolean param1)
    throws ActiveXException {
    // memid = 0x5e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5e, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShowWindow ()
    throws ActiveXException {
    // memid = 0x577

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x577, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowWindow (boolean param1)
    throws ActiveXException {
    // memid = 0x577

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x577, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable Spinners ()
    throws ActiveXException {
    // memid = 0x346

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x346, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Spinners (Variant param1)
    throws ActiveXException {
    // memid = 0x346

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x346, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
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

  public ChartGroup getAxSurfaceGroup ()
    throws ActiveXException {
    // memid = 0x16

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x16, AX_PROPERTYGET, false, args);
    ChartGroup result = new ChartGroup(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable TextBoxes ()
    throws ActiveXException {
    // memid = 0x309

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x309, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable TextBoxes (Variant param1)
    throws ActiveXException {
    // memid = 0x309

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x309, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
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

    // Enumeration type = XlChartType
  public int getAxChartType ()
    throws ActiveXException {
    // memid = 0x578

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x578, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxChartType (int param1)
    throws ActiveXException {
    // memid = 0x578

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x578, AX_PROPERTYSET, true, args);
  }

  public void ApplyCustomType (int param1)
    throws ActiveXException {
    // memid = 0x579

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x579, AX_INVOKE, true, args);
  }

  public void ApplyCustomType (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x579

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x579, AX_INVOKE, true, args);
  }

  public Walls getAxWalls ()
    throws ActiveXException {
    // memid = 0x56

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x56, AX_PROPERTYGET, false, args);
    Walls result = new Walls(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxWallsAndGridlines2D ()
    throws ActiveXException {
    // memid = 0xd2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xd2, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxWallsAndGridlines2D (boolean param1)
    throws ActiveXException {
    // memid = 0xd2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xd2, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable XYGroups ()
    throws ActiveXException {
    // memid = 0x10

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable XYGroups (Variant param1)
    throws ActiveXException {
    // memid = 0x10

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x10, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

    // Enumeration type = XlBarShape
  public int getAxBarShape ()
    throws ActiveXException {
    // memid = 0x57b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x57b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxBarShape (int param1)
    throws ActiveXException {
    // memid = 0x57b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x57b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlRowCol
  public int getAxPlotBy ()
    throws ActiveXException {
    // memid = 0xca

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xca, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPlotBy (int param1)
    throws ActiveXException {
    // memid = 0xca

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xca, AX_PROPERTYSET, true, args);
  }

  public void CopyChartBuild ()
    throws ActiveXException {
    // memid = 0x57c

    Vector args = new Vector(0);
    axInvoke(0x57c, AX_INVOKE, true, args);
  }

  public boolean getAxProtectFormatting ()
    throws ActiveXException {
    // memid = 0x57d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x57d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxProtectFormatting (boolean param1)
    throws ActiveXException {
    // memid = 0x57d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x57d, AX_PROPERTYSET, true, args);
  }

  public boolean getAxProtectData ()
    throws ActiveXException {
    // memid = 0x57e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x57e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxProtectData (boolean param1)
    throws ActiveXException {
    // memid = 0x57e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x57e, AX_PROPERTYSET, true, args);
  }

  public boolean getAxProtectGoalSeek ()
    throws ActiveXException {
    // memid = 0x57f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x57f, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxProtectGoalSeek (boolean param1)
    throws ActiveXException {
    // memid = 0x57f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x57f, AX_PROPERTYSET, true, args);
  }

  public boolean getAxProtectSelection ()
    throws ActiveXException {
    // memid = 0x580

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x580, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxProtectSelection (boolean param1)
    throws ActiveXException {
    // memid = 0x580

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x580, AX_PROPERTYSET, true, args);
  }

  public void GetChartElement (int param1, int param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x581

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x581, AX_INVOKE, true, args);
  }

  public void SetSourceData (Range param1)
    throws ActiveXException {
    // memid = 0x585

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x585, AX_INVOKE, true, args);
  }

  public void SetSourceData (Range param1, Variant param2)
    throws ActiveXException {
    // memid = 0x585

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x585, AX_INVOKE, true, args);
  }

  public boolean Export (String param1)
    throws ActiveXException {
    // memid = 0x586

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x586, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Export (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x586

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x586, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Export (String param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x586

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x586, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void Refresh ()
    throws ActiveXException {
    // memid = 0x589

    Vector args = new Vector(0);
    axInvoke(0x589, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<Chart, super = " + super.toString() + ">";
}


}

