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


public class Application extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208d5, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Application (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #167
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _Application
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 304 functions.
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

  public void ActivateMicrosoftApp (int param1)
    throws ActiveXException {
    // memid = 0x447

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x447, AX_INVOKE, true, args);
  }

  public void AddChartAutoFormat (Variant param1, String param2)
    throws ActiveXException {
    // memid = 0xd8

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0xd8, AX_INVOKE, true, args);
  }

  public void AddChartAutoFormat (Variant param1, String param2, Variant param3)
    throws ActiveXException {
    // memid = 0xd8

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0xd8, AX_INVOKE, true, args);
  }

  public void AddCustomList (Variant param1)
    throws ActiveXException {
    // memid = 0x30c

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x30c, AX_INVOKE, true, args);
  }

  public void AddCustomList (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x30c

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x30c, AX_INVOKE, true, args);
  }

  public boolean getAxAlertBeforeOverwriting ()
    throws ActiveXException {
    // memid = 0x3a2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a2, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAlertBeforeOverwriting (boolean param1)
    throws ActiveXException {
    // memid = 0x3a2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3a2, AX_PROPERTYSET, true, args);
  }

  public String getAxAltStartupPath ()
    throws ActiveXException {
    // memid = 0x139

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x139, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxAltStartupPath (String param1)
    throws ActiveXException {
    // memid = 0x139

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x139, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAskToUpdateLinks ()
    throws ActiveXException {
    // memid = 0x3e0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e0, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAskToUpdateLinks (boolean param1)
    throws ActiveXException {
    // memid = 0x3e0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3e0, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableAnimations ()
    throws ActiveXException {
    // memid = 0x49c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x49c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableAnimations (boolean param1)
    throws ActiveXException {
    // memid = 0x49c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x49c, AX_PROPERTYSET, true, args);
  }

  public AutoCorrect getAxAutoCorrect ()
    throws ActiveXException {
    // memid = 0x479

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x479, AX_PROPERTYGET, false, args);
    AutoCorrect result = new AutoCorrect(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxBuild ()
    throws ActiveXException {
    // memid = 0x13a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x13a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxCalculateBeforeSave ()
    throws ActiveXException {
    // memid = 0x13b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x13b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxCalculateBeforeSave (boolean param1)
    throws ActiveXException {
    // memid = 0x13b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x13b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlCalculation
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

  public Variant getAxCaller ()
    throws ActiveXException {
    // memid = 0x13d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x13d, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxCaller (Variant param1)
    throws ActiveXException {
    // memid = 0x13d

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x13d, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public boolean getAxCanPlaySounds ()
    throws ActiveXException {
    // memid = 0x13e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x13e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxCanRecordSounds ()
    throws ActiveXException {
    // memid = 0x13f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x13f, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public String getAxCaption ()
    throws ActiveXException {
    // memid = 0x8b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8b, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCaption (String param1)
    throws ActiveXException {
    // memid = 0x8b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8b, AX_PROPERTYSET, true, args);
  }

  public boolean getAxCellDragAndDrop ()
    throws ActiveXException {
    // memid = 0x140

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x140, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxCellDragAndDrop (boolean param1)
    throws ActiveXException {
    // memid = 0x140

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x140, AX_PROPERTYSET, true, args);
  }

  public double CentimetersToPoints (double param1)
    throws ActiveXException {
    // memid = 0x43e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x43e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public boolean CheckSpelling (String param1)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x1f9, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean CheckSpelling (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x1f9, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean CheckSpelling (String param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x1f9, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public Variant getAxClipboardFormats ()
    throws ActiveXException {
    // memid = 0x141

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x141, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxClipboardFormats (Variant param1)
    throws ActiveXException {
    // memid = 0x141

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x141, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public boolean getAxDisplayClipboardWindow ()
    throws ActiveXException {
    // memid = 0x142

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x142, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayClipboardWindow (boolean param1)
    throws ActiveXException {
    // memid = 0x142

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x142, AX_PROPERTYSET, true, args);
  }

  public boolean getAxColorButtons ()
    throws ActiveXException {
    // memid = 0x16d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x16d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxColorButtons (boolean param1)
    throws ActiveXException {
    // memid = 0x16d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x16d, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlCommandUnderlines
  public int getAxCommandUnderlines ()
    throws ActiveXException {
    // memid = 0x143

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x143, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCommandUnderlines (int param1)
    throws ActiveXException {
    // memid = 0x143

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x143, AX_PROPERTYSET, true, args);
  }

  public boolean getAxConstrainNumeric ()
    throws ActiveXException {
    // memid = 0x144

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x144, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxConstrainNumeric (boolean param1)
    throws ActiveXException {
    // memid = 0x144

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x144, AX_PROPERTYSET, true, args);
  }

  public Variant ConvertFormula (Variant param1, int param2)
    throws ActiveXException {
    // memid = 0x145

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x145, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant ConvertFormula (Variant param1, int param2, Variant param3)
    throws ActiveXException {
    // memid = 0x145

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x145, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant ConvertFormula (Variant param1, int param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x145

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x145, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant ConvertFormula (Variant param1, int param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x145

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x145, AX_INVOKE, false, args);
    return vResult;
  }

  public boolean getAxCopyObjectsWithCells ()
    throws ActiveXException {
    // memid = 0x3df

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3df, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxCopyObjectsWithCells (boolean param1)
    throws ActiveXException {
    // memid = 0x3df

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3df, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlMousePointer
  public int getAxCursor ()
    throws ActiveXException {
    // memid = 0x489

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x489, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCursor (int param1)
    throws ActiveXException {
    // memid = 0x489

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x489, AX_PROPERTYSET, true, args);
  }

  public int getAxCustomListCount ()
    throws ActiveXException {
    // memid = 0x313

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x313, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = XlCutCopyMode
  public int getAxCutCopyMode ()
    throws ActiveXException {
    // memid = 0x14a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x14a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCutCopyMode (int param1)
    throws ActiveXException {
    // memid = 0x14a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x14a, AX_PROPERTYSET, true, args);
  }

  public int getAxDataEntryMode ()
    throws ActiveXException {
    // memid = 0x14b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x14b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDataEntryMode (int param1)
    throws ActiveXException {
    // memid = 0x14b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x14b, AX_PROPERTYSET, true, args);
  }

  public void Dummy1 ()
    throws ActiveXException {
    // memid = 0x6e7

    Vector args = new Vector(0);
    axInvoke(0x6e7, AX_INVOKE, true, args);
  }

  public void Dummy2 ()
    throws ActiveXException {
    // memid = 0x6e8

    Vector args = new Vector(0);
    axInvoke(0x6e8, AX_INVOKE, true, args);
  }

  public void Dummy3 ()
    throws ActiveXException {
    // memid = 0x6e9

    Vector args = new Vector(0);
    axInvoke(0x6e9, AX_INVOKE, true, args);
  }

  public void Dummy4 ()
    throws ActiveXException {
    // memid = 0x6ea

    Vector args = new Vector(0);
    axInvoke(0x6ea, AX_INVOKE, true, args);
  }

  public void Dummy5 ()
    throws ActiveXException {
    // memid = 0x6eb

    Vector args = new Vector(0);
    axInvoke(0x6eb, AX_INVOKE, true, args);
  }

  public void Dummy6 ()
    throws ActiveXException {
    // memid = 0x6ec

    Vector args = new Vector(0);
    axInvoke(0x6ec, AX_INVOKE, true, args);
  }

  public void Dummy7 ()
    throws ActiveXException {
    // memid = 0x6ed

    Vector args = new Vector(0);
    axInvoke(0x6ed, AX_INVOKE, true, args);
  }

  public void Dummy8 ()
    throws ActiveXException {
    // memid = 0x6ee

    Vector args = new Vector(0);
    axInvoke(0x6ee, AX_INVOKE, true, args);
  }

  public void Dummy9 ()
    throws ActiveXException {
    // memid = 0x6ef

    Vector args = new Vector(0);
    axInvoke(0x6ef, AX_INVOKE, true, args);
  }

  public void Dummy10 ()
    throws ActiveXException {
    // memid = 0x6f0

    Vector args = new Vector(0);
    axInvoke(0x6f0, AX_INVOKE, true, args);
  }

  public void Dummy11 ()
    throws ActiveXException {
    // memid = 0x6f1

    Vector args = new Vector(0);
    axInvoke(0x6f1, AX_INVOKE, true, args);
  }

  public String getAx_Default ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxDefaultFilePath ()
    throws ActiveXException {
    // memid = 0x40e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x40e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxDefaultFilePath (String param1)
    throws ActiveXException {
    // memid = 0x40e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x40e, AX_PROPERTYSET, true, args);
  }

  public void DeleteChartAutoFormat (String param1)
    throws ActiveXException {
    // memid = 0xd9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xd9, AX_INVOKE, true, args);
  }

  public void DeleteCustomList (int param1)
    throws ActiveXException {
    // memid = 0x30f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x30f, AX_INVOKE, true, args);
  }

  public Dialogs getAxDialogs ()
    throws ActiveXException {
    // memid = 0x2f9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2f9, AX_PROPERTYGET, false, args);
    Dialogs result = new Dialogs(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxDisplayAlerts ()
    throws ActiveXException {
    // memid = 0x157

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x157, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayAlerts (boolean param1)
    throws ActiveXException {
    // memid = 0x157

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x157, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayFormulaBar ()
    throws ActiveXException {
    // memid = 0x158

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x158, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayFormulaBar (boolean param1)
    throws ActiveXException {
    // memid = 0x158

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x158, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayFullScreen ()
    throws ActiveXException {
    // memid = 0x425

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x425, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayFullScreen (boolean param1)
    throws ActiveXException {
    // memid = 0x425

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x425, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayNoteIndicator ()
    throws ActiveXException {
    // memid = 0x159

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x159, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayNoteIndicator (boolean param1)
    throws ActiveXException {
    // memid = 0x159

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x159, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlCommentDisplayMode
  public int getAxDisplayCommentIndicator ()
    throws ActiveXException {
    // memid = 0x4ac

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4ac, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDisplayCommentIndicator (int param1)
    throws ActiveXException {
    // memid = 0x4ac

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4ac, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayExcel4Menus ()
    throws ActiveXException {
    // memid = 0x39f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x39f, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayExcel4Menus (boolean param1)
    throws ActiveXException {
    // memid = 0x39f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x39f, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayRecentFiles ()
    throws ActiveXException {
    // memid = 0x39e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x39e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayRecentFiles (boolean param1)
    throws ActiveXException {
    // memid = 0x39e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x39e, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayScrollBars ()
    throws ActiveXException {
    // memid = 0x15a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x15a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayScrollBars (boolean param1)
    throws ActiveXException {
    // memid = 0x15a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x15a, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayStatusBar ()
    throws ActiveXException {
    // memid = 0x15b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x15b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayStatusBar (boolean param1)
    throws ActiveXException {
    // memid = 0x15b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x15b, AX_PROPERTYSET, true, args);
  }

  public void DoubleClick ()
    throws ActiveXException {
    // memid = 0x15d

    Vector args = new Vector(0);
    axInvoke(0x15d, AX_INVOKE, true, args);
  }

  public boolean getAxEditDirectlyInCell ()
    throws ActiveXException {
    // memid = 0x3a1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a1, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEditDirectlyInCell (boolean param1)
    throws ActiveXException {
    // memid = 0x3a1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3a1, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableAutoComplete ()
    throws ActiveXException {
    // memid = 0x49b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x49b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableAutoComplete (boolean param1)
    throws ActiveXException {
    // memid = 0x49b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x49b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlEnableCancelKey
  public int getAxEnableCancelKey ()
    throws ActiveXException {
    // memid = 0x448

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x448, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxEnableCancelKey (int param1)
    throws ActiveXException {
    // memid = 0x448

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x448, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableSound ()
    throws ActiveXException {
    // memid = 0x4ad

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4ad, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableSound (boolean param1)
    throws ActiveXException {
    // memid = 0x4ad

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4ad, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableTipWizard ()
    throws ActiveXException {
    // memid = 0x428

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x428, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableTipWizard (boolean param1)
    throws ActiveXException {
    // memid = 0x428

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x428, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFileConverters ()
    throws ActiveXException {
    // memid = 0x3a3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxFileConverters (Variant param1)
    throws ActiveXException {
    // memid = 0x3a3

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x3a3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxFileConverters (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x3a3

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x3a3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public com.gensym.com.beans.office20.FileSearch getAxFileSearch ()
    throws ActiveXException {
    // memid = 0x4b0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b0, AX_PROPERTYGET, false, args);
    com.gensym.com.beans.office20.FileSearch result = new com.gensym.com.beans.office20.FileSearch(vResult.getActiveXDispatchableValue());
    return result;
  }

  public com.gensym.com.beans.office20.IFind getAxFileFind ()
    throws ActiveXException {
    // memid = 0x4b1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b1, AX_PROPERTYGET, false, args);
    com.gensym.com.beans.office20.IFind result = new com.gensym.com.beans.office20.IFind(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void FindFile ()
    throws ActiveXException {
    // memid = 0x42c

    Vector args = new Vector(0);
    axInvoke(0x42c, AX_INVOKE, true, args);
  }

  public boolean getAxFixedDecimal ()
    throws ActiveXException {
    // memid = 0x15f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x15f, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxFixedDecimal (boolean param1)
    throws ActiveXException {
    // memid = 0x15f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x15f, AX_PROPERTYSET, true, args);
  }

  public int getAxFixedDecimalPlaces ()
    throws ActiveXException {
    // memid = 0x160

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x160, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxFixedDecimalPlaces (int param1)
    throws ActiveXException {
    // memid = 0x160

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x160, AX_PROPERTYSET, true, args);
  }

  public Variant GetCustomListContents (int param1)
    throws ActiveXException {
    // memid = 0x312

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x312, AX_INVOKE, false, args);
    return vResult;
  }

  public int GetCustomListNum (Variant param1)
    throws ActiveXException {
    // memid = 0x311

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x311, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Variant GetOpenFilename ()
    throws ActiveXException {
    // memid = 0x433

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x433, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetOpenFilename (Variant param1)
    throws ActiveXException {
    // memid = 0x433

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x433, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetOpenFilename (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x433

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x433, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetOpenFilename (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x433

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x433, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetOpenFilename (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x433

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x433, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetOpenFilename (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x433

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x433, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetSaveAsFilename ()
    throws ActiveXException {
    // memid = 0x434

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x434, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetSaveAsFilename (Variant param1)
    throws ActiveXException {
    // memid = 0x434

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x434, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetSaveAsFilename (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x434

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x434, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetSaveAsFilename (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x434

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x434, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetSaveAsFilename (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x434

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x434, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant GetSaveAsFilename (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x434

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x434, AX_INVOKE, false, args);
    return vResult;
  }

  public void Goto ()
    throws ActiveXException {
    // memid = 0x1db

    Vector args = new Vector(0);
    axInvoke(0x1db, AX_INVOKE, true, args);
  }

  public void Goto (Variant param1)
    throws ActiveXException {
    // memid = 0x1db

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x1db, AX_INVOKE, true, args);
  }

  public void Goto (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x1db

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x1db, AX_INVOKE, true, args);
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

  public void Help ()
    throws ActiveXException {
    // memid = 0x162

    Vector args = new Vector(0);
    axInvoke(0x162, AX_INVOKE, true, args);
  }

  public void Help (Variant param1)
    throws ActiveXException {
    // memid = 0x162

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x162, AX_INVOKE, true, args);
  }

  public void Help (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x162

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x162, AX_INVOKE, true, args);
  }

  public boolean getAxIgnoreRemoteRequests ()
    throws ActiveXException {
    // memid = 0x164

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x164, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIgnoreRemoteRequests (boolean param1)
    throws ActiveXException {
    // memid = 0x164

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x164, AX_PROPERTYSET, true, args);
  }

  public double InchesToPoints (double param1)
    throws ActiveXException {
    // memid = 0x43f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x43f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public Variant InputBox (String param1)
    throws ActiveXException {
    // memid = 0x165

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x165, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant InputBox (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x165

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x165, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant InputBox (String param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x165

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x165, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant InputBox (String param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x165

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x165, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant InputBox (String param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x165

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x165, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant InputBox (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x165

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x165, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant InputBox (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x165

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x165, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant InputBox (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x165

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x165, AX_INVOKE, false, args);
    return vResult;
  }

  public boolean getAxInteractive ()
    throws ActiveXException {
    // memid = 0x169

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x169, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxInteractive (boolean param1)
    throws ActiveXException {
    // memid = 0x169

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x169, AX_PROPERTYSET, true, args);
  }

  public Variant getAxInternational ()
    throws ActiveXException {
    // memid = 0x16a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x16a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxInternational (Variant param1)
    throws ActiveXException {
    // memid = 0x16a

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x16a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public boolean getAxIteration ()
    throws ActiveXException {
    // memid = 0x16b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x16b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIteration (boolean param1)
    throws ActiveXException {
    // memid = 0x16b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x16b, AX_PROPERTYSET, true, args);
  }

  public boolean getAxLargeButtons ()
    throws ActiveXException {
    // memid = 0x16c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x16c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxLargeButtons (boolean param1)
    throws ActiveXException {
    // memid = 0x16c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x16c, AX_PROPERTYSET, true, args);
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

  public String getAxLibraryPath ()
    throws ActiveXException {
    // memid = 0x16e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x16e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void MacroOptions ()
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(0);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1)
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x46f

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x46f

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
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MacroOptions (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x46f

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
    axInvoke(0x46f, AX_INVOKE, true, args);
  }

  public void MailLogoff ()
    throws ActiveXException {
    // memid = 0x3b1

    Vector args = new Vector(0);
    axInvoke(0x3b1, AX_INVOKE, true, args);
  }

  public void MailLogon ()
    throws ActiveXException {
    // memid = 0x3af

    Vector args = new Vector(0);
    axInvoke(0x3af, AX_INVOKE, true, args);
  }

  public void MailLogon (Variant param1)
    throws ActiveXException {
    // memid = 0x3af

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3af, AX_INVOKE, true, args);
  }

  public void MailLogon (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x3af

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x3af, AX_INVOKE, true, args);
  }

  public void MailLogon (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x3af

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x3af, AX_INVOKE, true, args);
  }

  public Variant getAxMailSession ()
    throws ActiveXException {
    // memid = 0x3ae

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ae, AX_PROPERTYGET, false, args);
    return vResult;
  }

    // Enumeration type = XlMailSystem
  public int getAxMailSystem ()
    throws ActiveXException {
    // memid = 0x3cb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3cb, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxMathCoprocessorAvailable ()
    throws ActiveXException {
    // memid = 0x16f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x16f, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public double getAxMaxChange ()
    throws ActiveXException {
    // memid = 0x170

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x170, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxMaxChange (double param1)
    throws ActiveXException {
    // memid = 0x170

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x170, AX_PROPERTYSET, true, args);
  }

  public int getAxMaxIterations ()
    throws ActiveXException {
    // memid = 0x171

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x171, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMaxIterations (int param1)
    throws ActiveXException {
    // memid = 0x171

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x171, AX_PROPERTYSET, true, args);
  }

  public int getAxMemoryFree ()
    throws ActiveXException {
    // memid = 0x172

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x172, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxMemoryTotal ()
    throws ActiveXException {
    // memid = 0x173

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x173, AX_PROPERTYGET, false, args);
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

  public boolean getAxMouseAvailable ()
    throws ActiveXException {
    // memid = 0x175

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x175, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxMoveAfterReturn ()
    throws ActiveXException {
    // memid = 0x176

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x176, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxMoveAfterReturn (boolean param1)
    throws ActiveXException {
    // memid = 0x176

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x176, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlDirection
  public int getAxMoveAfterReturnDirection ()
    throws ActiveXException {
    // memid = 0x478

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x478, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMoveAfterReturnDirection (int param1)
    throws ActiveXException {
    // memid = 0x478

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x478, AX_PROPERTYSET, true, args);
  }

  public RecentFiles getAxRecentFiles ()
    throws ActiveXException {
    // memid = 0x4b2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b2, AX_PROPERTYGET, false, args);
    RecentFiles result = new RecentFiles(vResult.getActiveXDispatchableValue());
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

  public Variant NextLetter ()
    throws ActiveXException {
    // memid = 0x3cc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3cc, AX_INVOKE, false, args);
    return vResult;
  }

  public String getAxNetworkTemplatesPath ()
    throws ActiveXException {
    // memid = 0x184

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x184, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public ODBCErrors getAxODBCErrors ()
    throws ActiveXException {
    // memid = 0x4b3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b3, AX_PROPERTYGET, false, args);
    ODBCErrors result = new ODBCErrors(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxODBCTimeout ()
    throws ActiveXException {
    // memid = 0x4b4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b4, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxODBCTimeout (int param1)
    throws ActiveXException {
    // memid = 0x4b4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4b4, AX_PROPERTYSET, true, args);
  }

  public String getAxOnCalculate ()
    throws ActiveXException {
    // memid = 0x271

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x271, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnCalculate (String param1)
    throws ActiveXException {
    // memid = 0x271

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x271, AX_PROPERTYSET, true, args);
  }

  public String getAxOnData ()
    throws ActiveXException {
    // memid = 0x275

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x275, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnData (String param1)
    throws ActiveXException {
    // memid = 0x275

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x275, AX_PROPERTYSET, true, args);
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

  public String getAxOnEntry ()
    throws ActiveXException {
    // memid = 0x273

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x273, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnEntry (String param1)
    throws ActiveXException {
    // memid = 0x273

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x273, AX_PROPERTYSET, true, args);
  }

  public void OnKey (String param1)
    throws ActiveXException {
    // memid = 0x272

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x272, AX_INVOKE, true, args);
  }

  public void OnKey (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x272

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x272, AX_INVOKE, true, args);
  }

  public void OnRepeat (String param1, String param2)
    throws ActiveXException {
    // memid = 0x301

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x301, AX_INVOKE, true, args);
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

  public void OnTime (Variant param1, String param2)
    throws ActiveXException {
    // memid = 0x270

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0x270, AX_INVOKE, true, args);
  }

  public void OnTime (Variant param1, String param2, Variant param3)
    throws ActiveXException {
    // memid = 0x270

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x270, AX_INVOKE, true, args);
  }

  public void OnTime (Variant param1, String param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x270

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x270, AX_INVOKE, true, args);
  }

  public void OnUndo (String param1, String param2)
    throws ActiveXException {
    // memid = 0x302

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x302, AX_INVOKE, true, args);
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

  public String getAxOperatingSystem ()
    throws ActiveXException {
    // memid = 0x177

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x177, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxOrganizationName ()
    throws ActiveXException {
    // memid = 0x178

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x178, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxPath ()
    throws ActiveXException {
    // memid = 0x123

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x123, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxPathSeparator ()
    throws ActiveXException {
    // memid = 0x179

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x179, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Variant getAxPreviousSelections ()
    throws ActiveXException {
    // memid = 0x17a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x17a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxPreviousSelections (Variant param1)
    throws ActiveXException {
    // memid = 0x17a

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x17a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public boolean getAxPivotTableSelection ()
    throws ActiveXException {
    // memid = 0x4b5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPivotTableSelection (boolean param1)
    throws ActiveXException {
    // memid = 0x4b5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4b5, AX_PROPERTYSET, true, args);
  }

  public boolean getAxPromptForSummaryInfo ()
    throws ActiveXException {
    // memid = 0x426

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x426, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPromptForSummaryInfo (boolean param1)
    throws ActiveXException {
    // memid = 0x426

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x426, AX_PROPERTYSET, true, args);
  }

  public void Quit ()
    throws ActiveXException {
    // memid = 0x12e

    Vector args = new Vector(0);
    axInvoke(0x12e, AX_INVOKE, true, args);
  }

  public void RecordMacro ()
    throws ActiveXException {
    // memid = 0x305

    Vector args = new Vector(0);
    axInvoke(0x305, AX_INVOKE, true, args);
  }

  public void RecordMacro (Variant param1)
    throws ActiveXException {
    // memid = 0x305

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x305, AX_INVOKE, true, args);
  }

  public void RecordMacro (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x305

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x305, AX_INVOKE, true, args);
  }

  public boolean getAxRecordRelative ()
    throws ActiveXException {
    // memid = 0x17b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x17b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

    // Enumeration type = XlReferenceStyle
  public int getAxReferenceStyle ()
    throws ActiveXException {
    // memid = 0x17c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x17c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxReferenceStyle (int param1)
    throws ActiveXException {
    // memid = 0x17c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x17c, AX_PROPERTYSET, true, args);
  }

  public Variant getAxRegisteredFunctions ()
    throws ActiveXException {
    // memid = 0x307

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x307, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxRegisteredFunctions (Variant param1)
    throws ActiveXException {
    // memid = 0x307

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x307, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxRegisteredFunctions (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x307

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x307, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public boolean RegisterXLL (String param1)
    throws ActiveXException {
    // memid = 0x1e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x1e, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void Repeat ()
    throws ActiveXException {
    // memid = 0x12d

    Vector args = new Vector(0);
    axInvoke(0x12d, AX_INVOKE, true, args);
  }

  public void ResetTipWizard ()
    throws ActiveXException {
    // memid = 0x3a0

    Vector args = new Vector(0);
    axInvoke(0x3a0, AX_INVOKE, true, args);
  }

  public boolean getAxRollZoom ()
    throws ActiveXException {
    // memid = 0x4b6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b6, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxRollZoom (boolean param1)
    throws ActiveXException {
    // memid = 0x4b6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4b6, AX_PROPERTYSET, true, args);
  }

  public void Save ()
    throws ActiveXException {
    // memid = 0x11b

    Vector args = new Vector(0);
    axInvoke(0x11b, AX_INVOKE, true, args);
  }

  public void Save (Variant param1)
    throws ActiveXException {
    // memid = 0x11b

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x11b, AX_INVOKE, true, args);
  }

  public void SaveWorkspace ()
    throws ActiveXException {
    // memid = 0xd4

    Vector args = new Vector(0);
    axInvoke(0xd4, AX_INVOKE, true, args);
  }

  public void SaveWorkspace (Variant param1)
    throws ActiveXException {
    // memid = 0xd4

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xd4, AX_INVOKE, true, args);
  }

  public boolean getAxScreenUpdating ()
    throws ActiveXException {
    // memid = 0x17e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x17e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxScreenUpdating (boolean param1)
    throws ActiveXException {
    // memid = 0x17e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x17e, AX_PROPERTYSET, true, args);
  }

  public void SetDefaultChart ()
    throws ActiveXException {
    // memid = 0xdb

    Vector args = new Vector(0);
    axInvoke(0xdb, AX_INVOKE, true, args);
  }

  public void SetDefaultChart (Variant param1)
    throws ActiveXException {
    // memid = 0xdb

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xdb, AX_INVOKE, true, args);
  }

  public void SetDefaultChart (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xdb

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0xdb, AX_INVOKE, true, args);
  }

  public int getAxSheetsInNewWorkbook ()
    throws ActiveXException {
    // memid = 0x3e1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e1, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSheetsInNewWorkbook (int param1)
    throws ActiveXException {
    // memid = 0x3e1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3e1, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShowChartTipNames ()
    throws ActiveXException {
    // memid = 0x4b7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b7, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowChartTipNames (boolean param1)
    throws ActiveXException {
    // memid = 0x4b7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4b7, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShowChartTipValues ()
    throws ActiveXException {
    // memid = 0x4b8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b8, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowChartTipValues (boolean param1)
    throws ActiveXException {
    // memid = 0x4b8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4b8, AX_PROPERTYSET, true, args);
  }

  public String getAxStandardFont ()
    throws ActiveXException {
    // memid = 0x39c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x39c, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxStandardFont (String param1)
    throws ActiveXException {
    // memid = 0x39c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x39c, AX_PROPERTYSET, true, args);
  }

  public double getAxStandardFontSize ()
    throws ActiveXException {
    // memid = 0x39d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x39d, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxStandardFontSize (double param1)
    throws ActiveXException {
    // memid = 0x39d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x39d, AX_PROPERTYSET, true, args);
  }

  public String getAxStartupPath ()
    throws ActiveXException {
    // memid = 0x181

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x181, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Variant getAxStatusBar ()
    throws ActiveXException {
    // memid = 0x182

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x182, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxStatusBar (Variant param1)
    throws ActiveXException {
    // memid = 0x182

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x182, AX_PROPERTYSET, true, args);
  }

  public String getAxTemplatesPath ()
    throws ActiveXException {
    // memid = 0x17d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x17d, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxShowToolTips ()
    throws ActiveXException {
    // memid = 0x183

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x183, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowToolTips (boolean param1)
    throws ActiveXException {
    // memid = 0x183

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x183, AX_PROPERTYSET, true, args);
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

    // Enumeration type = XlFileFormat
  public int getAxDefaultSaveFormat ()
    throws ActiveXException {
    // memid = 0x4b9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4b9, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDefaultSaveFormat (int param1)
    throws ActiveXException {
    // memid = 0x4b9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4b9, AX_PROPERTYSET, true, args);
  }

  public String getAxTransitionMenuKey ()
    throws ActiveXException {
    // memid = 0x136

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x136, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxTransitionMenuKey (String param1)
    throws ActiveXException {
    // memid = 0x136

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x136, AX_PROPERTYSET, true, args);
  }

  public int getAxTransitionMenuKeyAction ()
    throws ActiveXException {
    // memid = 0x137

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x137, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxTransitionMenuKeyAction (int param1)
    throws ActiveXException {
    // memid = 0x137

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x137, AX_PROPERTYSET, true, args);
  }

  public boolean getAxTransitionNavigKeys ()
    throws ActiveXException {
    // memid = 0x138

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x138, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxTransitionNavigKeys (boolean param1)
    throws ActiveXException {
    // memid = 0x138

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x138, AX_PROPERTYSET, true, args);
  }

  public void Undo ()
    throws ActiveXException {
    // memid = 0x12f

    Vector args = new Vector(0);
    axInvoke(0x12f, AX_INVOKE, true, args);
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

  public boolean getAxUserControl ()
    throws ActiveXException {
    // memid = 0x4ba

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4ba, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxUserControl (boolean param1)
    throws ActiveXException {
    // memid = 0x4ba

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4ba, AX_PROPERTYSET, true, args);
  }

  public String getAxUserName ()
    throws ActiveXException {
    // memid = 0x187

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x187, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxUserName (String param1)
    throws ActiveXException {
    // memid = 0x187

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x187, AX_PROPERTYSET, true, args);
  }

  public String getAxValue ()
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public com.gensym.com.beans.vbide50.VBE getAxVBE ()
    throws ActiveXException {
    // memid = 0x4bb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4bb, AX_PROPERTYGET, false, args);
    com.gensym.com.beans.vbide50.VBE result = new com.gensym.com.beans.vbide50.VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxVersion ()
    throws ActiveXException {
    // memid = 0x188

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x188, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
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

  public void Volatile ()
    throws ActiveXException {
    // memid = 0x314

    Vector args = new Vector(0);
    axInvoke(0x314, AX_INVOKE, true, args);
  }

  public void Volatile (Variant param1)
    throws ActiveXException {
    // memid = 0x314

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x314, AX_INVOKE, true, args);
  }

  public void Wait (Variant param1)
    throws ActiveXException {
    // memid = 0x189

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x189, AX_INVOKE, true, args);
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

  public boolean getAxWindowsForPens ()
    throws ActiveXException {
    // memid = 0x18b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x18b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
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

  public int getAxUILanguage ()
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxUILanguage (int param1)
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2, AX_PROPERTYSET, true, args);
  }

  public int getAxDefaultSheetDirection ()
    throws ActiveXException {
    // memid = 0xe5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xe5, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDefaultSheetDirection (int param1)
    throws ActiveXException {
    // memid = 0xe5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xe5, AX_PROPERTYSET, true, args);
  }

  public int getAxCursorMovement ()
    throws ActiveXException {
    // memid = 0xe8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xe8, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCursorMovement (int param1)
    throws ActiveXException {
    // memid = 0xe8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xe8, AX_PROPERTYSET, true, args);
  }

  public int getAxControlCharacters ()
    throws ActiveXException {
    // memid = 0xe9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xe9, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxControlCharacters (int param1)
    throws ActiveXException {
    // memid = 0xe9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xe9, AX_PROPERTYSET, true, args);
  }

  public Variant _WSFunction ()
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1)
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0xa9

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _WSFunction (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0xa9

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
    Variant vResult = axInvoke(0xa9, AX_INVOKE, false, args);
    return vResult;
  }

  public boolean getAxEnableEvents ()
    throws ActiveXException {
    // memid = 0x4bc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4bc, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableEvents (boolean param1)
    throws ActiveXException {
    // memid = 0x4bc

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4bc, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayInfoWindow ()
    throws ActiveXException {
    // memid = 0x4bd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4bd, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayInfoWindow (boolean param1)
    throws ActiveXException {
    // memid = 0x4bd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4bd, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<Application, super = " + super.toString() + ">";
}


}

