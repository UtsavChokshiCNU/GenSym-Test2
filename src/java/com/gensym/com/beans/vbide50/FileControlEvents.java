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


public class FileControlEvents extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xef404e0a, 0xeda6, 0x101a,
             (short) 0x8d, (short) 0xaf, (short) 0x0, (short) 0xdd,
             (short) 0x1, (short) 0xf, (short) 0x7e, (short) 0xbb);

  public FileControlEvents (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #8
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _FileControlEvents
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 12 functions.
    Type Info contains zero properties.
 */

  public void AfterAddFile (String param1)
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1, AX_INVOKE, true, args);
  }

  public void AfterChangeFileName (short param1, String param2, String param3)
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x2, AX_INVOKE, true, args);
  }

  public void AfterCloseFile (Vector param1)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3, AX_INVOKE, true, args);
  }

  public void AfterWriteFile (String param1, short param2)
    throws ActiveXException {
    // memid = 0x4

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x4, AX_INVOKE, true, args);
  }

  public void AfterRemoveFile (String param1)
    throws ActiveXException {
    // memid = 0x5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5, AX_INVOKE, true, args);
  }

  public void BeforeLoadFile (Vector param1)
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6, AX_INVOKE, true, args);
  }

  public void DoGetAddFileName (Vector param1, Variant param2)
    throws ActiveXException {
    // memid = 0x7

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x7, AX_INVOKE, true, args);
  }

  public void DoGetNewFileName (short param1, Variant param2, String param3, Variant param4)
    throws ActiveXException {
    // memid = 0x8

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0x8, AX_INVOKE, true, args);
  }

  public void DoGetOpenProjectName (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x9

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x9, AX_INVOKE, true, args);
  }

  public void RequestChangeFileName (short param1, String param2, String param3, Variant param4)
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0xa, AX_INVOKE, true, args);
  }

  public void RequestWriteFile (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0xb, AX_INVOKE, true, args);
  }

  public void AfterNewProject (String param1)
    throws ActiveXException {
    // memid = 0xc

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<FileControlEvents, super = " + super.toString() + ">";
}


}

