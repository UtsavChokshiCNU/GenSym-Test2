package com.gensym.com.beans.excel12;

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


public class Scenario extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20897, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Scenario (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #417
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Scenario
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 24 functions.
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

  public ExcelApplication getAxApplication ()
    throws ActiveXException {
    // memid = 0x94

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x94, AX_PROPERTYGET, false, args);
    ExcelApplication result = new ExcelApplication(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlCreator
  public int getAxCreator ()
    throws ActiveXException {
    // memid = 0x95

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x95, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ActiveXDispatchable getAxParent ()
    throws ActiveXException {
    // memid = 0x96

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x96, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void ChangeScenario (Variant param1)
    throws ActiveXException {
    // memid = 0x390

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x390, AX_INVOKE, true, args);
  }

  public void ChangeScenario (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x390

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x390, AX_INVOKE, true, args);
  }

  public Range getAxChangingCells ()
    throws ActiveXException {
    // memid = 0x38f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x38f, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxComment ()
    throws ActiveXException {
    // memid = 0x38e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x38e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxComment (String param1)
    throws ActiveXException {
    // memid = 0x38e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x38e, AX_PROPERTYSET, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public boolean getAxHidden ()
    throws ActiveXException {
    // memid = 0x10c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHidden (boolean param1)
    throws ActiveXException {
    // memid = 0x10c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x10c, AX_PROPERTYSET, true, args);
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x1e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxLocked ()
    throws ActiveXException {
    // memid = 0x10d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxLocked (boolean param1)
    throws ActiveXException {
    // memid = 0x10d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x10d, AX_PROPERTYSET, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6e, AX_PROPERTYSET, true, args);
  }

  public void Show ()
    throws ActiveXException {
    // memid = 0x1f0

    Vector args = new Vector(0);
    axInvoke(0x1f0, AX_INVOKE, true, args);
  }

  public Variant getAxValues ()
    throws ActiveXException {
    // memid = 0xa4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xa4, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxValues (Variant param1)
    throws ActiveXException {
    // memid = 0xa4

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xa4, AX_PROPERTYGET, false, args);
    return vResult;
  }

@Override
public String toString() {
    return "<Scenario, super = " + super.toString() + ">";
}


}

