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


public class Reference extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e17d, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Reference (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #100
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Reference
    Doc string is: Represents a reference to a type library or a project.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
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

  public Variant getAxCollection ()
    throws ActiveXException {
    // memid = 0x60020000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020000, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public VBE getAxVBE ()
    throws ActiveXException {
    // memid = 0x60020001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020001, AX_PROPERTYGET, false, args);
    VBE result = new VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x60020002

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020002, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxGuid ()
    throws ActiveXException {
    // memid = 0x60020003

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020003, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public int getAxMajor ()
    throws ActiveXException {
    // memid = 0x60020004

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020004, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxMinor ()
    throws ActiveXException {
    // memid = 0x60020005

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020005, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxFullPath ()
    throws ActiveXException {
    // memid = 0x60020006

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020006, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxBuiltIn ()
    throws ActiveXException {
    // memid = 0x60020007

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020007, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxIsBroken ()
    throws ActiveXException {
    // memid = 0x60020008

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020008, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

    // Enumeration type = vbextRefKind
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x60020009

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020009, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxDescription ()
    throws ActiveXException {
    // memid = 0x6002000a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002000a, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

@Override
public String toString() {
    return "<Reference, super = " + super.toString() + ">";
}


}

