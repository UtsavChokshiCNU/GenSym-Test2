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


public class ProjectTemplateEvents extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x31de1170, 0x1602, 0x11ce,
             (short) 0xbf, (short) 0xdc, (short) 0x8, (short) 0x0,
             (short) 0x2b, (short) 0x2b, (short) 0x8c, (short) 0xda);

  public ProjectTemplateEvents (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #45
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: ProjectTemplateEvents
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 4 functions.
    Type Info contains zero properties.
 */

  public void CheckIn ()
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(0);
    axInvoke(0x1, AX_INVOKE, true, args);
  }

  public void CheckOut ()
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(0);
    axInvoke(0x2, AX_INVOKE, true, args);
  }

  public void Fetch ()
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(0);
    axInvoke(0x3, AX_INVOKE, true, args);
  }

  public void UncheckOut ()
    throws ActiveXException {
    // memid = 0x4

    Vector args = new Vector(0);
    axInvoke(0x4, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<ProjectTemplateEvents, super = " + super.toString() + ">";
}


}

