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


public class MenuLineEvents extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xef404e1a, 0xeda6, 0x101a,
             (short) 0x8d, (short) 0xaf, (short) 0x0, (short) 0xdd,
             (short) 0x1, (short) 0xf, (short) 0x7e, (short) 0xbb);

  public MenuLineEvents (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #13
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: MenuLineEvents
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 1 functions.
    Type Info contains zero properties.
 */

  public void AfterClick ()
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(0);
    axInvoke(0x1, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<MenuLineEvents, super = " + super.toString() + ">";
}


}

