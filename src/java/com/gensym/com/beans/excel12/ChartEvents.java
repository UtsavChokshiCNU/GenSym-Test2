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


public class ChartEvents extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2440f, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public ChartEvents (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #350
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: ChartEvents
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 20 functions.
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

  public void Activate ()
    throws ActiveXException {
    // memid = 0x130

    Vector args = new Vector(0);
    axInvoke(0x130, AX_INVOKE, true, args);
  }

  public void Deactivate ()
    throws ActiveXException {
    // memid = 0x5fa

    Vector args = new Vector(0);
    axInvoke(0x5fa, AX_INVOKE, true, args);
  }

  public void Resize ()
    throws ActiveXException {
    // memid = 0x100

    Vector args = new Vector(0);
    axInvoke(0x100, AX_INVOKE, true, args);
  }

  public void MouseDown (int param1, int param2, int param3, int param4)
    throws ActiveXException {
    // memid = 0x5fb

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    axInvoke(0x5fb, AX_INVOKE, true, args);
  }

  public void MouseUp (int param1, int param2, int param3, int param4)
    throws ActiveXException {
    // memid = 0x5fc

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    axInvoke(0x5fc, AX_INVOKE, true, args);
  }

  public void MouseMove (int param1, int param2, int param3, int param4)
    throws ActiveXException {
    // memid = 0x5fd

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    axInvoke(0x5fd, AX_INVOKE, true, args);
  }

  public void BeforeRightClick (Variant param1)
    throws ActiveXException {
    // memid = 0x5fe

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5fe, AX_INVOKE, true, args);
  }

  public void DragPlot ()
    throws ActiveXException {
    // memid = 0x5ff

    Vector args = new Vector(0);
    axInvoke(0x5ff, AX_INVOKE, true, args);
  }

  public void DragOver ()
    throws ActiveXException {
    // memid = 0x600

    Vector args = new Vector(0);
    axInvoke(0x600, AX_INVOKE, true, args);
  }

  public void BeforeDoubleClick (int param1, int param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0x601

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0x601, AX_INVOKE, true, args);
  }

  public void Select (int param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public void SeriesChange (int param1, int param2)
    throws ActiveXException {
    // memid = 0x602

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x602, AX_INVOKE, true, args);
  }

  public void Calculate ()
    throws ActiveXException {
    // memid = 0x117

    Vector args = new Vector(0);
    axInvoke(0x117, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<ChartEvents, super = " + super.toString() + ">";
}


}

