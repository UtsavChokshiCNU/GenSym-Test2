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


public class dispContainedVBControlsEvents extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e122, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public dispContainedVBControlsEvents (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #33
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _dispContainedVBControlsEvents
    Doc string is: Returned by the VBControlsEvents property.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 3 functions.
    Type Info contains zero properties.
 */

  public void ItemAdded (VBControl param1)
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1, AX_INVOKE, true, args);
  }

  public void ItemRemoved (VBControl param1)
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2, AX_INVOKE, true, args);
  }

  public void ItemRenamed (VBControl param1, String param2, int param3)
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x3, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<dispContainedVBControlsEvents, super = " + super.toString() + ">";
}


}

