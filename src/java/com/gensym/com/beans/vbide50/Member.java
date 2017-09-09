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


public class Member extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e182, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Member (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #107
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Member
    Doc string is: Represents a mixture of code-based properties and type library-based attributes of public members.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 38 functions.
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
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public VBE getAxVBE ()
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1, AX_PROPERTYGET, false, args);
    VBE result = new VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

    // Enumeration type = vbextMemberType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = vbextScope
  public int getAxScope ()
    throws ActiveXException {
    // memid = 0x4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxStatic ()
    throws ActiveXException {
    // memid = 0x5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public int getAxCodeLocation ()
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxDescription ()
    throws ActiveXException {
    // memid = 0x7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxDescription (String param1)
    throws ActiveXException {
    // memid = 0x7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7, AX_PROPERTYSET, true, args);
  }

  public int getAxHelpContextID ()
    throws ActiveXException {
    // memid = 0x8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHelpContextID (int param1)
    throws ActiveXException {
    // memid = 0x8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHidden ()
    throws ActiveXException {
    // memid = 0x9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x9, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHidden (boolean param1)
    throws ActiveXException {
    // memid = 0x9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x9, AX_PROPERTYSET, true, args);
  }

  public boolean getAxBrowsable ()
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxBrowsable (boolean param1)
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xa, AX_PROPERTYSET, true, args);
  }

  public boolean getAxUIDefault ()
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxUIDefault (boolean param1)
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xb, AX_PROPERTYSET, true, args);
  }

  public int getAxStandardMethod ()
    throws ActiveXException {
    // memid = 0xc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxStandardMethod (int param1)
    throws ActiveXException {
    // memid = 0xc

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc, AX_PROPERTYSET, true, args);
  }

  public boolean getAxBindable ()
    throws ActiveXException {
    // memid = 0xd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xd, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxBindable (boolean param1)
    throws ActiveXException {
    // memid = 0xd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xd, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDefaultBind ()
    throws ActiveXException {
    // memid = 0xe

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xe, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDefaultBind (boolean param1)
    throws ActiveXException {
    // memid = 0xe

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xe, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayBind ()
    throws ActiveXException {
    // memid = 0xf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayBind (boolean param1)
    throws ActiveXException {
    // memid = 0xf

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xf, AX_PROPERTYSET, true, args);
  }

  public boolean getAxRequestEdit ()
    throws ActiveXException {
    // memid = 0x10

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxRequestEdit (boolean param1)
    throws ActiveXException {
    // memid = 0x10

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x10, AX_PROPERTYSET, true, args);
  }

  public String getAxCategory ()
    throws ActiveXException {
    // memid = 0x11

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x11, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCategory (String param1)
    throws ActiveXException {
    // memid = 0x11

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x11, AX_PROPERTYSET, true, args);
  }

  public String getAxPropertyPage ()
    throws ActiveXException {
    // memid = 0x12

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x12, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxPropertyPage (String param1)
    throws ActiveXException {
    // memid = 0x12

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x12, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<Member, super = " + super.toString() + ">";
}


}

