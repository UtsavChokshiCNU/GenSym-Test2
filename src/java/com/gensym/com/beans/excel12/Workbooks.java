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


public class Workbooks extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208db, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Workbooks (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #194
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Workbooks
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 18 functions.
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

  public Variant Add ()
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public void Close ()
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(0);
    axInvoke(0x115, AX_INVOKE, true, args);
  }

  public int getAxCount ()
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x76, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Variant getAxItem (Variant param1)
    throws ActiveXException {
    // memid = 0xaa

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xaa, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Object getAx_NewEnum ()
    throws ActiveXException {
    // memid = 0xfffffffc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xfffffffc, AX_PROPERTYGET, false, args);
    Object result = vResult.getGenericValue();
    return result;
  }

  public Variant Open (String param1)
    throws ActiveXException {
    // memid = 0x2aa

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x2aa

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x2aa

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x2aa

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x2aa

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x2aa

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x2aa

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x2aa

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x2aa

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
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x2aa

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
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x2aa

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
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x2aa

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
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Open (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x2aa

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
    Variant vResult = axInvoke(0x2aa, AX_INVOKE, false, args);
    return vResult;
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(9);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(10);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(11);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(12);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(13);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    args.addElement(param13);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public void OpenText (String param1, Variant param2, Variant param3, Variant param4, int param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x2ab

    Vector args = new Vector(14);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    args.addElement(param13);
    args.addElement(param14);
    axInvoke(0x2ab, AX_INVOKE, true, args);
  }

  public Variant getAx_Default (Variant param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    return vResult;
  }

@Override
public String toString() {
    return "<Workbooks, super = " + super.toString() + ">";
}


}

