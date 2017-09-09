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


public class Global extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208d9, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Global (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #184
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _Global
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 57 functions.
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

  public ExcelApplication getAxParent ()
    throws ActiveXException {
    // memid = 0x96

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x96, AX_PROPERTYGET, false, args);
    ExcelApplication result = new ExcelApplication(vResult.getActiveXDispatchableValue());
    return result;
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

  public DialogSheet getAxActiveDialog ()
    throws ActiveXException {
    // memid = 0x32f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x32f, AX_PROPERTYGET, false, args);
    DialogSheet result = new DialogSheet(vResult.getActiveXDispatchableValue());
    return result;
  }

  public MenuBar getAxActiveMenuBar ()
    throws ActiveXException {
    // memid = 0x2f6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2f6, AX_PROPERTYGET, false, args);
    MenuBar result = new MenuBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxActivePrinter ()
    throws ActiveXException {
    // memid = 0x132

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x132, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxActivePrinter (String param1)
    throws ActiveXException {
    // memid = 0x132

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x132, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxActiveSheet ()
    throws ActiveXException {
    // memid = 0x133

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x133, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Window getAxActiveWindow ()
    throws ActiveXException {
    // memid = 0x2f7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2f7, AX_PROPERTYGET, false, args);
    Window result = new Window(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxActiveWorkbook ()
    throws ActiveXException {
    // memid = 0x134

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x134, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public AddIns getAxAddIns ()
    throws ActiveXException {
    // memid = 0x225

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x225, AX_PROPERTYGET, false, args);
    AddIns result = new AddIns(vResult.getActiveXDispatchableValue());
    return result;
  }

  public com.gensym.com.beans.office20.Assistant getAxAssistant ()
    throws ActiveXException {
    // memid = 0x59e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x59e, AX_PROPERTYGET, false, args);
    com.gensym.com.beans.office20.Assistant result = new com.gensym.com.beans.office20.Assistant(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Calculate ()
    throws ActiveXException {
    // memid = 0x117

    Vector args = new Vector(0);
    axInvoke(0x117, AX_INVOKE, true, args);
  }

  public Range getAxCells ()
    throws ActiveXException {
    // memid = 0xee

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xee, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Sheets getAxCharts ()
    throws ActiveXException {
    // memid = 0x79

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x79, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxColumns ()
    throws ActiveXException {
    // memid = 0xf1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf1, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public com.gensym.com.beans.office20.CommandBars getAxCommandBars ()
    throws ActiveXException {
    // memid = 0x59f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x59f, AX_PROPERTYGET, false, args);
    com.gensym.com.beans.office20.CommandBars result = new com.gensym.com.beans.office20.CommandBars(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxDDEAppReturnCode ()
    throws ActiveXException {
    // memid = 0x14c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x14c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void DDEExecute (int param1, String param2)
    throws ActiveXException {
    // memid = 0x14d

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x14d, AX_INVOKE, true, args);
  }

  public int DDEInitiate (String param1, String param2)
    throws ActiveXException {
    // memid = 0x14e

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x14e, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void DDEPoke (int param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x14f

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x14f, AX_INVOKE, true, args);
  }

  public Variant DDERequest (int param1, String param2)
    throws ActiveXException {
    // memid = 0x150

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x150, AX_INVOKE, false, args);
    return vResult;
  }

  public void DDETerminate (int param1)
    throws ActiveXException {
    // memid = 0x151

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x151, AX_INVOKE, true, args);
  }

  public Sheets getAxDialogSheets ()
    throws ActiveXException {
    // memid = 0x2fc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2fc, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
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

  public Variant ExecuteExcel4Macro (String param1)
    throws ActiveXException {
    // memid = 0x15e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x15e, AX_INVOKE, false, args);
    return vResult;
  }

  public Range Intersect (Range param1, Range param2)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(9);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(10);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(11);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(12);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(13);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(14);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(15);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(16);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(17);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(18);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(19);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(20);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(21);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(22);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(23);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(24);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(25);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(26);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(27);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(28);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(29);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Intersect (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x2fe

    Vector args = new Vector(30);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    args.addElement(param30);
    Variant vResult = axInvoke(0x2fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public MenuBars getAxMenuBars ()
    throws ActiveXException {
    // memid = 0x24d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x24d, AX_PROPERTYGET, false, args);
    MenuBars result = new MenuBars(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Modules getAxModules ()
    throws ActiveXException {
    // memid = 0x246

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x246, AX_PROPERTYGET, false, args);
    Modules result = new Modules(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Names getAxNames ()
    throws ActiveXException {
    // memid = 0x1ba

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1ba, AX_PROPERTYGET, false, args);
    Names result = new Names(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxRange (Variant param1)
    throws ActiveXException {
    // memid = 0xc5

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xc5, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxRange (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xc5

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0xc5, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxRows ()
    throws ActiveXException {
    // memid = 0x102

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x102, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant Run ()
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(17);
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
    args.addElement(param17);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(18);
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
    args.addElement(param17);
    args.addElement(param18);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(19);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(20);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(21);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(22);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(23);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(24);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(25);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(26);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(27);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(28);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(29);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(30);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    args.addElement(param30);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30, Variant param31)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(31);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    args.addElement(param30);
    args.addElement(param31);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 ()
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x326

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
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x326

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
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x326

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
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x326

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
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x326

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
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x326

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
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x326

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
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x326

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
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(17);
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
    args.addElement(param17);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(18);
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
    args.addElement(param17);
    args.addElement(param18);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(19);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(20);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(21);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(22);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(23);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(24);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(25);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(26);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(27);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(28);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(29);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(30);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    args.addElement(param30);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Run2 (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30, Variant param31)
    throws ActiveXException {
    // memid = 0x326

    Vector args = new Vector(31);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    args.addElement(param30);
    args.addElement(param31);
    Variant vResult = axInvoke(0x326, AX_INVOKE, false, args);
    return vResult;
  }

  public ActiveXDispatchable getAxSelection ()
    throws ActiveXException {
    // memid = 0x93

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x93, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void SendKeys (Variant param1)
    throws ActiveXException {
    // memid = 0x17f

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x17f, AX_INVOKE, true, args);
  }

  public void SendKeys (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x17f

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x17f, AX_INVOKE, true, args);
  }

  public Sheets getAxSheets ()
    throws ActiveXException {
    // memid = 0x1e5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e5, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Menu getAxShortcutMenus (int param1)
    throws ActiveXException {
    // memid = 0x308

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x308, AX_PROPERTYGET, false, args);
    Menu result = new Menu(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxThisWorkbook ()
    throws ActiveXException {
    // memid = 0x30a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x30a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Toolbars getAxToolbars ()
    throws ActiveXException {
    // memid = 0x228

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x228, AX_PROPERTYGET, false, args);
    Toolbars result = new Toolbars(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(9);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(10);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(11);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(12);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(13);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(14);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(15);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(16);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(17);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(18);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(19);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(20);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(21);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(22);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(23);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(24);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(25);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(26);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(27);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(28);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(29);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Union (Range param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x30b

    Vector args = new Vector(30);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    args.addElement(param30);
    Variant vResult = axInvoke(0x30b, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Windows getAxWindows ()
    throws ActiveXException {
    // memid = 0x1ae

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1ae, AX_PROPERTYGET, false, args);
    Windows result = new Windows(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Workbooks getAxWorkbooks ()
    throws ActiveXException {
    // memid = 0x23c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x23c, AX_PROPERTYGET, false, args);
    Workbooks result = new Workbooks(vResult.getActiveXDispatchableValue());
    return result;
  }

  public WorksheetFunction getAxWorksheetFunction ()
    throws ActiveXException {
    // memid = 0x5a0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a0, AX_PROPERTYGET, false, args);
    WorksheetFunction result = new WorksheetFunction(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Sheets getAxWorksheets ()
    throws ActiveXException {
    // memid = 0x1ee

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1ee, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Sheets getAxExcel4IntlMacroSheets ()
    throws ActiveXException {
    // memid = 0x245

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x245, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Sheets getAxExcel4MacroSheets ()
    throws ActiveXException {
    // memid = 0x243

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x243, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

@Override
public String toString() {
    return "<Global, super = " + super.toString() + ">";
}


}

