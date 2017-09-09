package com.gensym.com.beans.vbide50;

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


public class dispVBFileControlEvents extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e141, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public dispVBFileControlEvents (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic 5.0 Extensibility
    // Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    // There are 108 TypeInfos in the library

/* Type info #42
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _dispVBFileControlEvents
    Doc string is: Returned by the FileControlEvents property.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 9 functions.
    Type Info contains zero properties.
 */

  public void AfterAddFile (Variant param1, int param2, String param3)
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x1, AX_INVOKE, true, args);
  }

  public void AfterChangeFileName (Variant param1, int param2, String param3, String param4)
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    axInvoke(0x2, AX_INVOKE, true, args);
  }

  public void AfterCloseFile (Variant param1, int param2, String param3, boolean param4)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    axInvoke(0x3, AX_INVOKE, true, args);
  }

  public void AfterWriteFile (Variant param1, int param2, String param3, short param4)
    throws ActiveXException {
    // memid = 0x4

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    axInvoke(0x4, AX_INVOKE, true, args);
  }

  public void AfterRemoveFile (Variant param1, int param2, String param3)
    throws ActiveXException {
    // memid = 0x5

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x5, AX_INVOKE, true, args);
  }

  public void BeforeLoadFile (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x6, AX_INVOKE, true, args);
  }

  public void DoGetNewFileName (Variant param1, int param2, Variant param3, String param4, Variant param5)
    throws ActiveXException {
    // memid = 0x8

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(new Variant(param4));
    args.addElement(param5);
    axInvoke(0x8, AX_INVOKE, true, args);
  }

  public void RequestChangeFileName (Variant param1, int param2, String param3, String param4, Variant param5)
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(param5);
    axInvoke(0xa, AX_INVOKE, true, args);
  }

  public void RequestWriteFile (Variant param1, String param2, Variant param3)
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0xb, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<dispVBFileControlEvents, super = " + super.toString() + ">";
}


}

