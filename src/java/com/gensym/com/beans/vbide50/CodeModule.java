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


public class CodeModule extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e16d, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public CodeModule (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #91
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _CodeModule
    Doc string is: Represents the code behind a component, such as a form, class, or document.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
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

  public Variant getAxParent ()
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
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x0, AX_PROPERTYSET, true, args);
  }

  public void AddFromString (String param1)
    throws ActiveXException {
    // memid = 0x60020004

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020004, AX_INVOKE, true, args);
  }

  public void AddFromFile (String param1)
    throws ActiveXException {
    // memid = 0x60020005

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020005, AX_INVOKE, true, args);
  }

  public String getAxLines (int param1, int param2)
    throws ActiveXException {
    // memid = 0x60020006

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x60020006, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public int getAxCountOfLines ()
    throws ActiveXException {
    // memid = 0x60020007

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020007, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void InsertLines (int param1, String param2)
    throws ActiveXException {
    // memid = 0x60020008

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x60020008, AX_INVOKE, true, args);
  }

  public void DeleteLines (int param1, int param2)
    throws ActiveXException {
    // memid = 0x60020009

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x60020009, AX_INVOKE, true, args);
  }

  public void ReplaceLine (int param1, String param2)
    throws ActiveXException {
    // memid = 0x6002000a

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x6002000a, AX_INVOKE, true, args);
  }

  public int getAxProcStartLine (String param1, int param2)
    throws ActiveXException {
    // memid = 0x6002000b

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x6002000b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxProcCountLines (String param1, int param2)
    throws ActiveXException {
    // memid = 0x6002000c

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x6002000c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxProcBodyLine (String param1, int param2)
    throws ActiveXException {
    // memid = 0x6002000d

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x6002000d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxProcOfLine (int param1, int param2)
    throws ActiveXException {
    // memid = 0x6002000e

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x6002000e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public int getAxCountOfDeclarationLines ()
    throws ActiveXException {
    // memid = 0x6002000f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002000f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int CreateEventProc (String param1, String param2)
    throws ActiveXException {
    // memid = 0x60020010

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x60020010, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean Find (String param1, Variant param2, Variant param3, Variant param4, Variant param5, boolean param6, boolean param7, boolean param8)
    throws ActiveXException {
    // memid = 0x60020011

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(new Variant(param7));
    args.addElement(new Variant(param8));
    Variant vResult = axInvoke(0x60020011, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public Variant getAxCodePane ()
    throws ActiveXException {
    // memid = 0x60020012

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020012, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxMembers ()
    throws ActiveXException {
    // memid = 0x60020013

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020013, AX_PROPERTYGET, false, args);
    return vResult;
  }

@Override
public String toString() {
    return "<CodeModule, super = " + super.toString() + ">";
}


}

