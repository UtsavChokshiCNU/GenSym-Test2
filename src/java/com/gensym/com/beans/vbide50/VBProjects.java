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


public class VBProjects extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e102, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public VBProjects (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #54
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _VBProjects
    Doc string is: Represents all the projects that are open in the development environment.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 22 functions.
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

  public Variant Item (Variant param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x0, AX_INVOKE, false, args);
    return vResult;
  }

  public VBE getAxVBE ()
    throws ActiveXException {
    // memid = 0x14

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x14, AX_PROPERTYGET, false, args);
    VBE result = new VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public VBE getAxParent ()
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2, AX_PROPERTYGET, false, args);
    VBE result = new VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxCount ()
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Object _NewEnum ()
    throws ActiveXException {
    // memid = 0xfffffffc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xfffffffc, AX_INVOKE, false, args);
    Object result = vResult.getGenericValue();
    return result;
  }

  public Variant Add (int param1, boolean param2)
    throws ActiveXException {
    // memid = 0x80

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x80, AX_INVOKE, false, args);
    return vResult;
  }

  public VBNewProjects AddFromTemplate (String param1, boolean param2)
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x81, AX_INVOKE, false, args);
    VBNewProjects result = new VBNewProjects(vResult.getActiveXDispatchableValue());
    return result;
  }

  public VBNewProjects AddFromFile (String param1, boolean param2)
    throws ActiveXException {
    // memid = 0x82

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x82, AX_INVOKE, false, args);
    VBNewProjects result = new VBNewProjects(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Remove (Variant param1)
    throws ActiveXException {
    // memid = 0x83

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x83, AX_INVOKE, true, args);
  }

  public Variant getAxStartProject ()
    throws ActiveXException {
    // memid = 0x84

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x84, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxStartProject (Variant param1)
    throws ActiveXException {
    // memid = 0x84

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x84, AX_PROPERTYSET, true, args);
  }

  public String FileName ()
    throws ActiveXException {
    // memid = 0x85

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x85, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

    // Enumeration type = vbextSCCStatus
  public int getAxIconState ()
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x86, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxIconState (int param1)
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x86, AX_PROPERTYSET, true, args);
  }

  public void SaveAs (String param1)
    throws ActiveXException {
    // memid = 0x87

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x87, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<VBProjects, super = " + super.toString() + ">";
}


}

