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


public class WorksheetFunction extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20845, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public WorksheetFunction (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #348
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: WorksheetFunction
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 185 functions.
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

  public double Count (Variant param1)
    throws ActiveXException {
    // memid = 0x4000

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4000

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4000

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4000

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4000

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4000

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4000

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4000

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Count (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4000

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
    Variant vResult = axInvoke(0x4000, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public boolean IsNA (Variant param1)
    throws ActiveXException {
    // memid = 0x4002

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4002, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean IsError (Variant param1)
    throws ActiveXException {
    // memid = 0x4003

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4003, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public double Sum (Variant param1)
    throws ActiveXException {
    // memid = 0x4004

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4004

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4004

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4004

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4004

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4004

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4004

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4004

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sum (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4004

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
    Variant vResult = axInvoke(0x4004, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1)
    throws ActiveXException {
    // memid = 0x4005

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4005

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4005

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4005

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4005

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4005

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4005

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4005

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Average (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4005

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
    Variant vResult = axInvoke(0x4005, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1)
    throws ActiveXException {
    // memid = 0x4006

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4006

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4006

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4006

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4006

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4006

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4006

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4006

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Min (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4006

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
    Variant vResult = axInvoke(0x4006, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1)
    throws ActiveXException {
    // memid = 0x4007

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4007

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4007

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4007

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4007

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4007

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4007

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4007

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Max (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4007

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
    Variant vResult = axInvoke(0x4007, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x400b

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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(10);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(11);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(12);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(13);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(14);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(15);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(16);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(17);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(18);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(19);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(20);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(21);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(22);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(23);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(24);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(25);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(26);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(27);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(28);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(29);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Npv (double param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x400b

    Vector args = new Vector(30);
    args.addElement(new Variant(param1));
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
    Variant vResult = axInvoke(0x400b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1)
    throws ActiveXException {
    // memid = 0x400c

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x400c

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x400c

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x400c

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x400c

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x400c

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x400c

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x400c

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x400c

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
    Variant vResult = axInvoke(0x400c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public String Dollar (double param1)
    throws ActiveXException {
    // memid = 0x400d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x400d, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Dollar (double param1, Variant param2)
    throws ActiveXException {
    // memid = 0x400d

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x400d, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Fixed (double param1)
    throws ActiveXException {
    // memid = 0x400e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x400e, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Fixed (double param1, Variant param2)
    throws ActiveXException {
    // memid = 0x400e

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x400e, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Fixed (double param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x400e

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x400e, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public double Pi ()
    throws ActiveXException {
    // memid = 0x4013

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4013, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ln (double param1)
    throws ActiveXException {
    // memid = 0x4016

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4016, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Log10 (double param1)
    throws ActiveXException {
    // memid = 0x4017

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4017, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Round (double param1, double param2)
    throws ActiveXException {
    // memid = 0x401b

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x401b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public Variant Lookup (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x401c

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x401c, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Lookup (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x401c

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x401c, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Index (Variant param1, double param2)
    throws ActiveXException {
    // memid = 0x401d

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x401d, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Index (Variant param1, double param2, Variant param3)
    throws ActiveXException {
    // memid = 0x401d

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x401d, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Index (Variant param1, double param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x401d

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x401d, AX_INVOKE, false, args);
    return vResult;
  }

  public String Rept (String param1, double param2)
    throws ActiveXException {
    // memid = 0x401e

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x401e, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean And (Variant param1)
    throws ActiveXException {
    // memid = 0x4024

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4024

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4024

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4024

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4024

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4024

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4024

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4024

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean And (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4024

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
    Variant vResult = axInvoke(0x4024, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1)
    throws ActiveXException {
    // memid = 0x4025

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4025

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4025

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4025

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4025

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4025

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4025

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4025

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Or (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4025

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
    Variant vResult = axInvoke(0x4025, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public double DCount (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4028

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4028, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DSum (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4029

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4029, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DAverage (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x402a

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x402a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DMin (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x402b

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x402b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DMax (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x402c

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x402c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DStDev (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x402d

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x402d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1)
    throws ActiveXException {
    // memid = 0x402e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x402e

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x402e

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x402e

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x402e

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x402e

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x402e

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x402e

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Var (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x402e

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
    Variant vResult = axInvoke(0x402e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DVar (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x402f

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x402f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public String Text (Variant param1, String param2)
    throws ActiveXException {
    // memid = 0x4030

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4030, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Variant LinEst (Variant param1)
    throws ActiveXException {
    // memid = 0x4031

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4031, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LinEst (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4031

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4031, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LinEst (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4031

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4031, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LinEst (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4031

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4031, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Trend (Variant param1)
    throws ActiveXException {
    // memid = 0x4032

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4032, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Trend (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4032

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4032, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Trend (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4032

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4032, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Trend (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4032

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4032, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LogEst (Variant param1)
    throws ActiveXException {
    // memid = 0x4033

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4033, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LogEst (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4033

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4033, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LogEst (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4033

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4033, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LogEst (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4033

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4033, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Growth (Variant param1)
    throws ActiveXException {
    // memid = 0x4034

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4034, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Growth (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4034

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4034, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Growth (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4034

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4034, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Growth (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4034

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4034, AX_INVOKE, false, args);
    return vResult;
  }

  public double Pv (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4038

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4038, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Pv (double param1, double param2, double param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4038

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x4038, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Pv (double param1, double param2, double param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4038

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4038, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Fv (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4039

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4039, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Fv (double param1, double param2, double param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4039

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x4039, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Fv (double param1, double param2, double param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4039

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4039, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double NPer (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x403a

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x403a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double NPer (double param1, double param2, double param3, Variant param4)
    throws ActiveXException {
    // memid = 0x403a

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x403a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double NPer (double param1, double param2, double param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x403a

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x403a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Pmt (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x403b

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x403b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Pmt (double param1, double param2, double param3, Variant param4)
    throws ActiveXException {
    // memid = 0x403b

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x403b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Pmt (double param1, double param2, double param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x403b

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x403b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Rate (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x403c

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x403c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Rate (double param1, double param2, double param3, Variant param4)
    throws ActiveXException {
    // memid = 0x403c

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x403c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Rate (double param1, double param2, double param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x403c

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x403c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Rate (double param1, double param2, double param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x403c

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x403c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double MIrr (Variant param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x403d

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x403d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Irr (Variant param1)
    throws ActiveXException {
    // memid = 0x403e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x403e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Irr (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x403e

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x403e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Match (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4040

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4040, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Match (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4040

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4040, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Weekday (Variant param1)
    throws ActiveXException {
    // memid = 0x4046

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4046, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Weekday (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4046

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4046, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Search (String param1, String param2)
    throws ActiveXException {
    // memid = 0x4052

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4052, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Search (String param1, String param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4052

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x4052, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public Variant Transpose (Variant param1)
    throws ActiveXException {
    // memid = 0x4053

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4053, AX_INVOKE, false, args);
    return vResult;
  }

  public double Atan2 (double param1, double param2)
    throws ActiveXException {
    // memid = 0x4061

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4061, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Asin (double param1)
    throws ActiveXException {
    // memid = 0x4062

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4062, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Acos (double param1)
    throws ActiveXException {
    // memid = 0x4063

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4063, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public Variant Choose (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4064

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4064

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4064

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4064

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4064

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4064

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4064

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Choose (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4064

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
    Variant vResult = axInvoke(0x4064, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant HLookup (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4065

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4065, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant HLookup (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4065

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4065, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant VLookup (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4066

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4066, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant VLookup (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4066

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4066, AX_INVOKE, false, args);
    return vResult;
  }

  public double Log (double param1)
    throws ActiveXException {
    // memid = 0x406d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x406d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Log (double param1, Variant param2)
    throws ActiveXException {
    // memid = 0x406d

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x406d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public String Proper (String param1)
    throws ActiveXException {
    // memid = 0x4072

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4072, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Trim (String param1)
    throws ActiveXException {
    // memid = 0x4076

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4076, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Replace (String param1, double param2, double param3, String param4)
    throws ActiveXException {
    // memid = 0x4077

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x4077, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Substitute (String param1, String param2, String param3)
    throws ActiveXException {
    // memid = 0x4078

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4078, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Substitute (String param1, String param2, String param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4078

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x4078, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public double Find (String param1, String param2)
    throws ActiveXException {
    // memid = 0x407c

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x407c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Find (String param1, String param2, Variant param3)
    throws ActiveXException {
    // memid = 0x407c

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x407c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public boolean IsErr (Variant param1)
    throws ActiveXException {
    // memid = 0x407e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x407e, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean IsText (Variant param1)
    throws ActiveXException {
    // memid = 0x407f

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x407f, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean IsNumber (Variant param1)
    throws ActiveXException {
    // memid = 0x4080

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4080, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public double Sln (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x408e

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x408e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Syd (double param1, double param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0x408f

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x408f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ddb (double param1, double param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0x4090

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x4090, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ddb (double param1, double param2, double param3, double param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4090

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    Variant vResult = axInvoke(0x4090, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public String Clean (String param1)
    throws ActiveXException {
    // memid = 0x40a2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40a2, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public double MDeterm (Variant param1)
    throws ActiveXException {
    // memid = 0x40a3

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40a3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public Variant MInverse (Variant param1)
    throws ActiveXException {
    // memid = 0x40a4

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40a4, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant MMult (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40a5

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40a5, AX_INVOKE, false, args);
    return vResult;
  }

  public double Ipmt (double param1, double param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0x40a7

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x40a7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ipmt (double param1, double param2, double param3, double param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40a7

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    Variant vResult = axInvoke(0x40a7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ipmt (double param1, double param2, double param3, double param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40a7

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x40a7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ppmt (double param1, double param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0x40a8

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x40a8, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ppmt (double param1, double param2, double param3, double param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40a8

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    Variant vResult = axInvoke(0x40a8, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ppmt (double param1, double param2, double param3, double param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40a8

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x40a8, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1)
    throws ActiveXException {
    // memid = 0x40a9

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40a9

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40a9

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x40a9

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40a9

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40a9

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x40a9

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x40a9

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountA (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x40a9

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
    Variant vResult = axInvoke(0x40a9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1)
    throws ActiveXException {
    // memid = 0x40b7

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40b7

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40b7

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x40b7

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40b7

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40b7

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x40b7

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x40b7

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Product (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x40b7

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
    Variant vResult = axInvoke(0x40b7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Fact (double param1)
    throws ActiveXException {
    // memid = 0x40b8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40b8, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DProduct (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40bd

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40bd, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public boolean IsNonText (Variant param1)
    throws ActiveXException {
    // memid = 0x40be

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40be, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public double StDevP (Variant param1)
    throws ActiveXException {
    // memid = 0x40c1

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40c1

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40c1

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x40c1

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40c1

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40c1

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x40c1

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x40c1

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StDevP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x40c1

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
    Variant vResult = axInvoke(0x40c1, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1)
    throws ActiveXException {
    // memid = 0x40c2

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40c2

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40c2

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x40c2

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40c2

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40c2

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x40c2

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x40c2

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double VarP (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x40c2

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
    Variant vResult = axInvoke(0x40c2, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DStDevP (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40c3

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40c3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DVarP (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40c4

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40c4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public boolean IsLogical (Variant param1)
    throws ActiveXException {
    // memid = 0x40c6

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40c6, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public double DCountA (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40c7

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40c7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public String USDollar (double param1, double param2)
    throws ActiveXException {
    // memid = 0x40cc

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x40cc, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public double FindB (String param1, String param2)
    throws ActiveXException {
    // memid = 0x40cd

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x40cd, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double FindB (String param1, String param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40cd

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x40cd, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SearchB (String param1, String param2)
    throws ActiveXException {
    // memid = 0x40ce

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x40ce, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SearchB (String param1, String param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40ce

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x40ce, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public String ReplaceB (String param1, double param2, double param3, String param4)
    throws ActiveXException {
    // memid = 0x40cf

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x40cf, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public double RoundUp (double param1, double param2)
    throws ActiveXException {
    // memid = 0x40d4

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x40d4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double RoundDown (double param1, double param2)
    throws ActiveXException {
    // memid = 0x40d5

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x40d5, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Rank (double param1, Range param2)
    throws ActiveXException {
    // memid = 0x40d8

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x40d8, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Rank (double param1, Range param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40d8

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x40d8, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Days360 (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40dc

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40dc, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Days360 (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40dc

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40dc, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Vdb (double param1, double param2, double param3, double param4, double param5)
    throws ActiveXException {
    // memid = 0x40de

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    Variant vResult = axInvoke(0x40de, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Vdb (double param1, double param2, double param3, double param4, double param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40de

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    args.addElement(param6);
    Variant vResult = axInvoke(0x40de, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Vdb (double param1, double param2, double param3, double param4, double param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x40de

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x40de, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1)
    throws ActiveXException {
    // memid = 0x40e3

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40e3

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40e3

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x40e3

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40e3

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40e3

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x40e3

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x40e3

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Median (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x40e3

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
    Variant vResult = axInvoke(0x40e3, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1)
    throws ActiveXException {
    // memid = 0x40e4

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40e4

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40e4

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x40e4

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40e4

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x40e4

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x40e4

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x40e4

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumProduct (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x40e4

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
    Variant vResult = axInvoke(0x40e4, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Sinh (double param1)
    throws ActiveXException {
    // memid = 0x40e5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40e5, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Cosh (double param1)
    throws ActiveXException {
    // memid = 0x40e6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40e6, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Tanh (double param1)
    throws ActiveXException {
    // memid = 0x40e7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40e7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Asinh (double param1)
    throws ActiveXException {
    // memid = 0x40e8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40e8, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Acosh (double param1)
    throws ActiveXException {
    // memid = 0x40e9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40e9, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Atanh (double param1)
    throws ActiveXException {
    // memid = 0x40ea

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40ea, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public Variant DGet (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x40eb

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x40eb, AX_INVOKE, false, args);
    return vResult;
  }

  public double Db (double param1, double param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0x40f7

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x40f7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Db (double param1, double param2, double param3, double param4, Variant param5)
    throws ActiveXException {
    // memid = 0x40f7

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    Variant vResult = axInvoke(0x40f7, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public Variant Frequency (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x40fc

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x40fc, AX_INVOKE, false, args);
    return vResult;
  }

  public double AveDev (Variant param1)
    throws ActiveXException {
    // memid = 0x410d

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x410d

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x410d

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x410d

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x410d

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x410d

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x410d

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x410d

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double AveDev (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x410d

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
    Variant vResult = axInvoke(0x410d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double BetaDist (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x410e

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x410e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double BetaDist (double param1, double param2, double param3, Variant param4)
    throws ActiveXException {
    // memid = 0x410e

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x410e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double BetaDist (double param1, double param2, double param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x410e

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x410e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GammaLn (double param1)
    throws ActiveXException {
    // memid = 0x410f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x410f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double BetaInv (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4110

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4110, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double BetaInv (double param1, double param2, double param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4110

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x4110, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double BetaInv (double param1, double param2, double param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4110

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4110, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double BinomDist (double param1, double param2, double param3, boolean param4)
    throws ActiveXException {
    // memid = 0x4111

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x4111, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double ChiDist (double param1, double param2)
    throws ActiveXException {
    // memid = 0x4112

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4112, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double ChiInv (double param1, double param2)
    throws ActiveXException {
    // memid = 0x4113

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4113, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Combin (double param1, double param2)
    throws ActiveXException {
    // memid = 0x4114

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4114, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Confidence (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4115

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4115, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CritBinom (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4116

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4116, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Even (double param1)
    throws ActiveXException {
    // memid = 0x4117

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4117, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double ExponDist (double param1, double param2, boolean param3)
    throws ActiveXException {
    // memid = 0x4118

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4118, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double FDist (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4119

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4119, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double FInv (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x411a

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x411a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Fisher (double param1)
    throws ActiveXException {
    // memid = 0x411b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x411b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double FisherInv (double param1)
    throws ActiveXException {
    // memid = 0x411c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x411c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Floor (double param1, double param2)
    throws ActiveXException {
    // memid = 0x411d

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x411d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GammaDist (double param1, double param2, double param3, boolean param4)
    throws ActiveXException {
    // memid = 0x411e

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x411e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GammaInv (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x411f

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x411f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ceiling (double param1, double param2)
    throws ActiveXException {
    // memid = 0x4120

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4120, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HypGeomDist (double param1, double param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0x4121

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x4121, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double LogNormDist (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4122

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4122, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double LogInv (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4123

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4123, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double NegBinomDist (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4124

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4124, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double NormDist (double param1, double param2, double param3, boolean param4)
    throws ActiveXException {
    // memid = 0x4125

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x4125, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double NormSDist (double param1)
    throws ActiveXException {
    // memid = 0x4126

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4126, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double NormInv (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4127

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4127, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double NormSInv (double param1)
    throws ActiveXException {
    // memid = 0x4128

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4128, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Standardize (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x4129

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x4129, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Odd (double param1)
    throws ActiveXException {
    // memid = 0x412a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x412a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Permut (double param1, double param2)
    throws ActiveXException {
    // memid = 0x412b

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x412b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Poisson (double param1, double param2, boolean param3)
    throws ActiveXException {
    // memid = 0x412c

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x412c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double TDist (double param1, double param2, double param3)
    throws ActiveXException {
    // memid = 0x412d

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x412d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Weibull (double param1, double param2, double param3, boolean param4)
    throws ActiveXException {
    // memid = 0x412e

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x412e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumXMY2 (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x412f

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x412f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumX2MY2 (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4130

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4130, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumX2PY2 (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4131

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4131, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double ChiTest (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4132

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4132, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Correl (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4133

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4133, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Covar (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4134

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4134, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Forecast (double param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4135

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4135, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double FTest (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4136

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4136, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Intercept (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4137

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4137, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Pearson (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4138

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4138, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double RSq (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4139

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4139, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double StEyx (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x413a

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x413a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Slope (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x413b

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x413b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double TTest (Variant param1, Variant param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0x413c

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x413c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Prob (Variant param1, Variant param2, double param3)
    throws ActiveXException {
    // memid = 0x413d

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x413d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Prob (Variant param1, Variant param2, double param3, Variant param4)
    throws ActiveXException {
    // memid = 0x413d

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x413d, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1)
    throws ActiveXException {
    // memid = 0x413e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x413e

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x413e

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x413e

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x413e

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x413e

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x413e

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x413e

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double DevSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x413e

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
    Variant vResult = axInvoke(0x413e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1)
    throws ActiveXException {
    // memid = 0x413f

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x413f

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x413f

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x413f

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x413f

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x413f

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x413f

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x413f

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double GeoMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x413f

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
    Variant vResult = axInvoke(0x413f, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1)
    throws ActiveXException {
    // memid = 0x4140

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4140

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4140

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4140

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4140

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4140

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4140

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4140

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double HarMean (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4140

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
    Variant vResult = axInvoke(0x4140, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1)
    throws ActiveXException {
    // memid = 0x4141

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4141

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4141

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4141

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4141

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4141

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4141

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4141

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumSq (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4141

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
    Variant vResult = axInvoke(0x4141, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1)
    throws ActiveXException {
    // memid = 0x4142

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4142

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4142

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4142

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4142

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4142

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4142

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4142

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Kurt (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4142

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
    Variant vResult = axInvoke(0x4142, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1)
    throws ActiveXException {
    // memid = 0x4143

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4143

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4143

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4143

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4143

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4143

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4143

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4143

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Skew (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4143

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
    Variant vResult = axInvoke(0x4143, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double ZTest (Variant param1, double param2)
    throws ActiveXException {
    // memid = 0x4144

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4144, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double ZTest (Variant param1, double param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4144

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x4144, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Large (Variant param1, double param2)
    throws ActiveXException {
    // memid = 0x4145

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4145, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Small (Variant param1, double param2)
    throws ActiveXException {
    // memid = 0x4146

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4146, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Quartile (Variant param1, double param2)
    throws ActiveXException {
    // memid = 0x4147

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4147, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Percentile (Variant param1, double param2)
    throws ActiveXException {
    // memid = 0x4148

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4148, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double PercentRank (Variant param1, double param2)
    throws ActiveXException {
    // memid = 0x4149

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4149, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double PercentRank (Variant param1, double param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4149

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x4149, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1)
    throws ActiveXException {
    // memid = 0x414a

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x414a

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x414a

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x414a

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x414a

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x414a

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x414a

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x414a

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Mode (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x414a

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
    Variant vResult = axInvoke(0x414a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double TrimMean (Variant param1, double param2)
    throws ActiveXException {
    // memid = 0x414b

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x414b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double TInv (double param1, double param2)
    throws ActiveXException {
    // memid = 0x414c

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x414c, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Power (double param1, double param2)
    throws ActiveXException {
    // memid = 0x4151

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4151, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Radians (double param1)
    throws ActiveXException {
    // memid = 0x4156

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4156, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Degrees (double param1)
    throws ActiveXException {
    // memid = 0x4157

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4157, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2)
    throws ActiveXException {
    // memid = 0x4158

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4158

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x4158

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x4158

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x4158

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x4158

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x4158

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Subtotal (double param1, Range param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x4158

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
    Variant vResult = axInvoke(0x4158, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumIf (Range param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4159

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x4159, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double SumIf (Range param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x4159

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x4159, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountIf (Range param1, Variant param2)
    throws ActiveXException {
    // memid = 0x415a

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x415a, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double CountBlank (Range param1)
    throws ActiveXException {
    // memid = 0x415b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x415b, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double Ispmt (double param1, double param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0x415e

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x415e, AX_INVOKE, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public String Roman (double param1)
    throws ActiveXException {
    // memid = 0x4162

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4162, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Roman (double param1, Variant param2)
    throws ActiveXException {
    // memid = 0x4162

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x4162, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Asc (String param1)
    throws ActiveXException {
    // memid = 0x40d6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40d6, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String Dbcs (String param1)
    throws ActiveXException {
    // memid = 0x40d7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x40d7, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

@Override
public String toString() {
    return "<WorksheetFunction, super = " + super.toString() + ">";
}


}

