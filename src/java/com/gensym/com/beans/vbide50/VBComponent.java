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


public class VBComponent extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e148, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public VBComponent (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #65
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _VBComponent
    Doc string is: Represents a component, such as a class module or standard module, contained in a project.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 34 functions.
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

  public ActiveXDispatchable getAxDesigner ()
    throws ActiveXException {
    // memid = 0x31

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x31, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Variant getAxCodeModule ()
    throws ActiveXException {
    // memid = 0x32

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x32, AX_PROPERTYGET, false, args);
    return vResult;
  }

    // Enumeration type = vbextComponentType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x33

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x33, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public VBE getAxVBE ()
    throws ActiveXException {
    // memid = 0x35

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x35, AX_PROPERTYGET, false, args);
    VBE result = new VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxCollection ()
    throws ActiveXException {
    // memid = 0x36

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x36, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public boolean getAxHasOpenDesigner ()
    throws ActiveXException {
    // memid = 0x37

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x37, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public Variant getAxProperties ()
    throws ActiveXException {
    // memid = 0x38

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x38, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Window DesignerWindow ()
    throws ActiveXException {
    // memid = 0x39

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x39, AX_INVOKE, false, args);
    Window result = new Window(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String ReadProperty (String param1)
    throws ActiveXException {
    // memid = 0x3a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x3a, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void WriteProperty (String param1, String param2)
    throws ActiveXException {
    // memid = 0x3b

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x3b, AX_INVOKE, true, args);
  }

  public void Activate ()
    throws ActiveXException {
    // memid = 0x3c

    Vector args = new Vector(0);
    axInvoke(0x3c, AX_INVOKE, true, args);
  }

  public int getAxHelpContextID ()
    throws ActiveXException {
    // memid = 0x3d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHelpContextID (int param1)
    throws ActiveXException {
    // memid = 0x3d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3d, AX_PROPERTYSET, true, args);
  }

  public String getAxDescription ()
    throws ActiveXException {
    // memid = 0x3e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxDescription (String param1)
    throws ActiveXException {
    // memid = 0x3e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3e, AX_PROPERTYSET, true, args);
  }

  public String getAxDesignerID ()
    throws ActiveXException {
    // memid = 0x3f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

@Override
public String toString() {
    return "<VBComponent, super = " + super.toString() + ">";
}


}

