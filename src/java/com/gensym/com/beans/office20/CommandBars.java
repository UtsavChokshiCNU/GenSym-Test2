package com.gensym.com.beans.office20;

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


public class CommandBars extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc0302, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public CommandBars (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #72
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: CommandBars
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    Type Info contains 26 functions.
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

  public ActiveXDispatchable getAxApplication ()
    throws ActiveXException {
    // memid = 0x60020000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020000, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public int getAxCreator ()
    throws ActiveXException {
    // memid = 0x60020001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020001, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public CommandBarControl getAxActionControl ()
    throws ActiveXException {
    // memid = 0x60030000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030000, AX_PROPERTYGET, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBar getAxActiveMenuBar ()
    throws ActiveXException {
    // memid = 0x60030001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030001, AX_PROPERTYGET, false, args);
    CommandBar result = new CommandBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBar Add ()
    throws ActiveXException {
    // memid = 0x60030002

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030002, AX_INVOKE, false, args);
    CommandBar result = new CommandBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBar Add (Variant param1)
    throws ActiveXException {
    // memid = 0x60030002

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x60030002, AX_INVOKE, false, args);
    CommandBar result = new CommandBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBar Add (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x60030002

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x60030002, AX_INVOKE, false, args);
    CommandBar result = new CommandBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBar Add (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x60030002

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x60030002, AX_INVOKE, false, args);
    CommandBar result = new CommandBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBar Add (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x60030002

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x60030002, AX_INVOKE, false, args);
    CommandBar result = new CommandBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxCount ()
    throws ActiveXException {
    // memid = 0x60030003

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030003, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxDisplayTooltips ()
    throws ActiveXException {
    // memid = 0x60030004

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030004, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayTooltips (boolean param1)
    throws ActiveXException {
    // memid = 0x60030004

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030004, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplayKeysInTooltips ()
    throws ActiveXException {
    // memid = 0x60030006

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030006, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayKeysInTooltips (boolean param1)
    throws ActiveXException {
    // memid = 0x60030006

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030006, AX_PROPERTYSET, true, args);
  }

  public CommandBarControl FindControl ()
    throws ActiveXException {
    // memid = 0x60030008

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030008, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1)
    throws ActiveXException {
    // memid = 0x60030008

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x60030008, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x60030008

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x60030008, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x60030008

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x60030008, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x60030008

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x60030008, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBar getAxItem (Variant param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    CommandBar result = new CommandBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxLargeButtons ()
    throws ActiveXException {
    // memid = 0x6003000a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxLargeButtons (boolean param1)
    throws ActiveXException {
    // memid = 0x6003000a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003000a, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoMenuAnimation
  public int getAxMenuAnimationStyle ()
    throws ActiveXException {
    // memid = 0x6003000c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMenuAnimationStyle (int param1)
    throws ActiveXException {
    // memid = 0x6003000c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003000c, AX_PROPERTYSET, true, args);
  }

  public Object getAx_NewEnum ()
    throws ActiveXException {
    // memid = 0xfffffffc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xfffffffc, AX_PROPERTYGET, false, args);
    Object result = vResult.getGenericValue();
    return result;
  }

  public ActiveXDispatchable getAxParent ()
    throws ActiveXException {
    // memid = 0x6003000f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000f, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void ReleaseFocus ()
    throws ActiveXException {
    // memid = 0x60030010

    Vector args = new Vector(0);
    axInvoke(0x60030010, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<CommandBars, super = " + super.toString() + ">";
}


}

