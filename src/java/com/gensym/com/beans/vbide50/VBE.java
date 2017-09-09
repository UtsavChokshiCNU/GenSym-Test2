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


public class VBE extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e100, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public VBE (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #6
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: VBE
    Doc string is: The root object that contains all other objects and collections represented in Visual Basic for Applications.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 31 functions.
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

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxFullName ()
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxLastUsedPath ()
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxLastUsedPath (String param1)
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xb, AX_PROPERTYSET, true, args);
  }

  public String getAxVersion ()
    throws ActiveXException {
    // memid = 0x64

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public short getAxReadOnlyMode ()
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a, AX_PROPERTYGET, false, args);
    short result = vResult.getShortValue();
    return result;
  }

  public void setAxReadOnlyMode (short param1)
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6a, AX_PROPERTYSET, true, args);
  }

  public Variant getAxVBProjects ()
    throws ActiveXException {
    // memid = 0x6b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6b, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public com.gensym.com.beans.office20.CommandBars getAxCommandBars ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    com.gensym.com.beans.office20.CommandBars result = new com.gensym.com.beans.office20.CommandBars(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxCodePanes ()
    throws ActiveXException {
    // memid = 0x6d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxWindows ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Events getAxEvents ()
    throws ActiveXException {
    // memid = 0x6f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6f, AX_PROPERTYGET, false, args);
    Events result = new Events(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxAddins ()
    throws ActiveXException {
    // memid = 0xc8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc8, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxActiveVBProject ()
    throws ActiveXException {
    // memid = 0xc9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc9, AX_PROPERTYGET, false, args);
    return vResult;
  }

    // Currently unimplemented reference put: 0xc9

  public Variant getAxSelectedVBComponent ()
    throws ActiveXException {
    // memid = 0xca

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xca, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public String getAxTemplatePath ()
    throws ActiveXException {
    // memid = 0xcb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xcb, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Window getAxMainWindow ()
    throws ActiveXException {
    // memid = 0xcc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xcc, AX_PROPERTYGET, false, args);
    Window result = new Window(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Window getAxActiveWindow ()
    throws ActiveXException {
    // memid = 0xcd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xcd, AX_PROPERTYGET, false, args);
    Window result = new Window(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxActiveCodePane ()
    throws ActiveXException {
    // memid = 0xce

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xce, AX_PROPERTYGET, false, args);
    return vResult;
  }

    // Currently unimplemented reference put: 0xce

  public void Quit ()
    throws ActiveXException {
    // memid = 0xcf

    Vector args = new Vector(0);
    axInvoke(0xcf, AX_INVOKE, true, args);
  }

    // Enumeration type = vbextVBADisplayModel
  public int getAxDisplayModel ()
    throws ActiveXException {
    // memid = 0xd0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xd0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDisplayModel (int param1)
    throws ActiveXException {
    // memid = 0xd0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xd0, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<VBE, super = " + super.toString() + ">";
}


}

