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


public class Font extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2084d, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Font (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #344
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Font
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

  public Variant getAxBackground ()
    throws ActiveXException {
    // memid = 0xb4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb4, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxBackground (Variant param1)
    throws ActiveXException {
    // memid = 0xb4

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xb4, AX_PROPERTYSET, true, args);
  }

  public Variant getAxBold ()
    throws ActiveXException {
    // memid = 0x60

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxBold (Variant param1)
    throws ActiveXException {
    // memid = 0x60

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x60, AX_PROPERTYSET, true, args);
  }

  public Variant getAxColor ()
    throws ActiveXException {
    // memid = 0x63

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x63, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxColor (Variant param1)
    throws ActiveXException {
    // memid = 0x63

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x63, AX_PROPERTYSET, true, args);
  }

  public Variant getAxColorIndex ()
    throws ActiveXException {
    // memid = 0x61

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x61, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxColorIndex (Variant param1)
    throws ActiveXException {
    // memid = 0x61

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x61, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFontStyle ()
    throws ActiveXException {
    // memid = 0xb1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb1, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFontStyle (Variant param1)
    throws ActiveXException {
    // memid = 0xb1

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xb1, AX_PROPERTYSET, true, args);
  }

  public Variant getAxItalic ()
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x65, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxItalic (Variant param1)
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x65, AX_PROPERTYSET, true, args);
  }

  public Variant getAxName ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxName (Variant param1)
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6e, AX_PROPERTYSET, true, args);
  }

  public Variant getAxOutlineFont ()
    throws ActiveXException {
    // memid = 0xdd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xdd, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxOutlineFont (Variant param1)
    throws ActiveXException {
    // memid = 0xdd

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xdd, AX_PROPERTYSET, true, args);
  }

  public Variant getAxShadow ()
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxShadow (Variant param1)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x67, AX_PROPERTYSET, true, args);
  }

  public Variant getAxSize ()
    throws ActiveXException {
    // memid = 0x68

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x68, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxSize (Variant param1)
    throws ActiveXException {
    // memid = 0x68

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x68, AX_PROPERTYSET, true, args);
  }

  public Variant getAxStrikethrough ()
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxStrikethrough (Variant param1)
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x69, AX_PROPERTYSET, true, args);
  }

  public Variant getAxSubscript ()
    throws ActiveXException {
    // memid = 0xb3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb3, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxSubscript (Variant param1)
    throws ActiveXException {
    // memid = 0xb3

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xb3, AX_PROPERTYSET, true, args);
  }

  public Variant getAxSuperscript ()
    throws ActiveXException {
    // memid = 0xb2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb2, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxSuperscript (Variant param1)
    throws ActiveXException {
    // memid = 0xb2

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xb2, AX_PROPERTYSET, true, args);
  }

  public Variant getAxUnderline ()
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxUnderline (Variant param1)
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6a, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<Font, super = " + super.toString() + ">";
}


}

