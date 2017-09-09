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


public class AppEvents extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x24413, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public AppEvents (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #347
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: AppEvents
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 27 functions.
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

  public void NewWorkbook (Variant param1)
    throws ActiveXException {
    // memid = 0x61d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x61d, AX_INVOKE, true, args);
  }

  public void SheetSelectionChange (ActiveXDispatchable param1, Range param2)
    throws ActiveXException {
    // memid = 0x616

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x616, AX_INVOKE, true, args);
  }

  public void SheetBeforeDoubleClick (ActiveXDispatchable param1, Range param2, Variant param3)
    throws ActiveXException {
    // memid = 0x617

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x617, AX_INVOKE, true, args);
  }

  public void SheetBeforeRightClick (ActiveXDispatchable param1, Range param2, Variant param3)
    throws ActiveXException {
    // memid = 0x618

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x618, AX_INVOKE, true, args);
  }

  public void SheetActivate (ActiveXDispatchable param1)
    throws ActiveXException {
    // memid = 0x619

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x619, AX_INVOKE, true, args);
  }

  public void SheetDeactivate (ActiveXDispatchable param1)
    throws ActiveXException {
    // memid = 0x61a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x61a, AX_INVOKE, true, args);
  }

  public void SheetCalculate (ActiveXDispatchable param1)
    throws ActiveXException {
    // memid = 0x61b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x61b, AX_INVOKE, true, args);
  }

  public void SheetChange (ActiveXDispatchable param1, Range param2)
    throws ActiveXException {
    // memid = 0x61c

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x61c, AX_INVOKE, true, args);
  }

  public void WorkbookOpen (Variant param1)
    throws ActiveXException {
    // memid = 0x61f

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x61f, AX_INVOKE, true, args);
  }

  public void WorkbookActivate (Variant param1)
    throws ActiveXException {
    // memid = 0x620

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x620, AX_INVOKE, true, args);
  }

  public void WorkbookDeactivate (Variant param1)
    throws ActiveXException {
    // memid = 0x621

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x621, AX_INVOKE, true, args);
  }

  public void WorkbookBeforeClose (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x622

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x622, AX_INVOKE, true, args);
  }

  public void WorkbookBeforeSave (Variant param1, boolean param2, Variant param3)
    throws ActiveXException {
    // memid = 0x623

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x623, AX_INVOKE, true, args);
  }

  public void WorkbookBeforePrint (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x624

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x624, AX_INVOKE, true, args);
  }

  public void WorkbookNewSheet (Variant param1, ActiveXDispatchable param2)
    throws ActiveXException {
    // memid = 0x625

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0x625, AX_INVOKE, true, args);
  }

  public void WorkbookAddinInstall (Variant param1)
    throws ActiveXException {
    // memid = 0x626

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x626, AX_INVOKE, true, args);
  }

  public void WorkbookAddinUninstall (Variant param1)
    throws ActiveXException {
    // memid = 0x627

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x627, AX_INVOKE, true, args);
  }

  public void WindowResize (Variant param1, Window param2)
    throws ActiveXException {
    // memid = 0x612

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0x612, AX_INVOKE, true, args);
  }

  public void WindowActivate (Variant param1, Window param2)
    throws ActiveXException {
    // memid = 0x614

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0x614, AX_INVOKE, true, args);
  }

  public void WindowDeactivate (Variant param1, Window param2)
    throws ActiveXException {
    // memid = 0x615

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0x615, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<AppEvents, super = " + super.toString() + ">";
}


}

