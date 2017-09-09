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


public class Name extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208b9, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Name (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #446
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Name
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
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

  public String getAx_Default ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x1e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxCategory ()
    throws ActiveXException {
    // memid = 0x3a6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a6, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCategory (String param1)
    throws ActiveXException {
    // memid = 0x3a6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3a6, AX_PROPERTYSET, true, args);
  }

  public String getAxCategoryLocal ()
    throws ActiveXException {
    // memid = 0x3a7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a7, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCategoryLocal (String param1)
    throws ActiveXException {
    // memid = 0x3a7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3a7, AX_PROPERTYSET, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

    // Enumeration type = XlXLMMacroType
  public int getAxMacroType ()
    throws ActiveXException {
    // memid = 0x3a8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a8, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMacroType (int param1)
    throws ActiveXException {
    // memid = 0x3a8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3a8, AX_PROPERTYSET, true, args);
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

  public Variant getAxRefersTo ()
    throws ActiveXException {
    // memid = 0x3aa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3aa, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxRefersTo (Variant param1)
    throws ActiveXException {
    // memid = 0x3aa

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3aa, AX_PROPERTYSET, true, args);
  }

  public String getAxShortcutKey ()
    throws ActiveXException {
    // memid = 0x255

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x255, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxShortcutKey (String param1)
    throws ActiveXException {
    // memid = 0x255

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x255, AX_PROPERTYSET, true, args);
  }

  public String getAxValue ()
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxValue (String param1)
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6, AX_PROPERTYSET, true, args);
  }

  public boolean getAxVisible ()
    throws ActiveXException {
    // memid = 0x22e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x22e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxVisible (boolean param1)
    throws ActiveXException {
    // memid = 0x22e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x22e, AX_PROPERTYSET, true, args);
  }

  public String getAxNameLocal ()
    throws ActiveXException {
    // memid = 0x3a9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a9, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxNameLocal (String param1)
    throws ActiveXException {
    // memid = 0x3a9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3a9, AX_PROPERTYSET, true, args);
  }

  public Variant getAxRefersToLocal ()
    throws ActiveXException {
    // memid = 0x3ab

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ab, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxRefersToLocal (Variant param1)
    throws ActiveXException {
    // memid = 0x3ab

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3ab, AX_PROPERTYSET, true, args);
  }

  public Variant getAxRefersToR1C1 ()
    throws ActiveXException {
    // memid = 0x3ac

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ac, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxRefersToR1C1 (Variant param1)
    throws ActiveXException {
    // memid = 0x3ac

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3ac, AX_PROPERTYSET, true, args);
  }

  public Variant getAxRefersToR1C1Local ()
    throws ActiveXException {
    // memid = 0x3ad

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ad, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxRefersToR1C1Local (Variant param1)
    throws ActiveXException {
    // memid = 0x3ad

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3ad, AX_PROPERTYSET, true, args);
  }

  public Range getAxRefersToRange ()
    throws ActiveXException {
    // memid = 0x488

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x488, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

@Override
public String toString() {
    return "<Name, super = " + super.toString() + ">";
}


}

