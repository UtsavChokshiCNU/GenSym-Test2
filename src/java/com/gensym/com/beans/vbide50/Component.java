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


public class Component extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xef404e1f, 0xeda6, 0x101a,
             (short) 0x8d, (short) 0xaf, (short) 0x0, (short) 0xdd,
             (short) 0x1, (short) 0xf, (short) 0x7e, (short) 0xbb);

  public Component (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #63
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _Component
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
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

  public Application getAxApplication ()
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1, AX_PROPERTYGET, false, args);
    Application result = new Application(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxParent ()
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public boolean getAxIsDirty ()
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIsDirty (boolean param1)
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xa, AX_PROPERTYSET, true, args);
  }

  public String getAxFileNames (short param1)
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0xb, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean SaveAs (String param1)
    throws ActiveXException {
    // memid = 0xc

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0xc, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public short getAxFileCount ()
    throws ActiveXException {
    // memid = 0xd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xd, AX_PROPERTYGET, false, args);
    short result = vResult.getShortValue();
    return result;
  }

  public int getAxIconState ()
    throws ActiveXException {
    // memid = 0xe

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xe, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxIconState (int param1)
    throws ActiveXException {
    // memid = 0xe

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xe, AX_PROPERTYSET, true, args);
  }

  public void InsertFile (String param1)
    throws ActiveXException {
    // memid = 0x2e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2e, AX_INVOKE, true, args);
  }

  public void Reload ()
    throws ActiveXException {
    // memid = 0x2f

    Vector args = new Vector(0);
    axInvoke(0x2f, AX_INVOKE, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x30

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x30, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x30

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x30, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<Component, super = " + super.toString() + ">";
}


}

