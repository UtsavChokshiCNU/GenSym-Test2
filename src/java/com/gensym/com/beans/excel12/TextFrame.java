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


public class TextFrame extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2443d, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public TextFrame (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #512
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: TextFrame
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
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

  public float getAxMarginBottom ()
    throws ActiveXException {
    // memid = 0x6d1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d1, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxMarginBottom (float param1)
    throws ActiveXException {
    // memid = 0x6d1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6d1, AX_PROPERTYSET, true, args);
  }

  public float getAxMarginLeft ()
    throws ActiveXException {
    // memid = 0x6d2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d2, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxMarginLeft (float param1)
    throws ActiveXException {
    // memid = 0x6d2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6d2, AX_PROPERTYSET, true, args);
  }

  public float getAxMarginRight ()
    throws ActiveXException {
    // memid = 0x6d3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d3, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxMarginRight (float param1)
    throws ActiveXException {
    // memid = 0x6d3

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6d3, AX_PROPERTYSET, true, args);
  }

  public float getAxMarginTop ()
    throws ActiveXException {
    // memid = 0x6d4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d4, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxMarginTop (float param1)
    throws ActiveXException {
    // memid = 0x6d4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6d4, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoTextOrientation
  public int getAxOrientation ()
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x86, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxOrientation (int param1)
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x86, AX_PROPERTYSET, true, args);
  }

  public Characters Characters ()
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x25b, AX_INVOKE, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Characters Characters (Variant param1)
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x25b, AX_INVOKE, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Characters Characters (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x25b, AX_INVOKE, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlHAlign
  public int getAxHorizontalAlignment ()
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x88, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHorizontalAlignment (int param1)
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x88, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlVAlign
  public int getAxVerticalAlignment ()
    throws ActiveXException {
    // memid = 0x89

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x89, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxVerticalAlignment (int param1)
    throws ActiveXException {
    // memid = 0x89

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x89, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAutoSize ()
    throws ActiveXException {
    // memid = 0x266

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x266, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoSize (boolean param1)
    throws ActiveXException {
    // memid = 0x266

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x266, AX_PROPERTYSET, true, args);
  }

  public int getAxReadingOrder ()
    throws ActiveXException {
    // memid = 0x3cf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3cf, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxReadingOrder (int param1)
    throws ActiveXException {
    // memid = 0x3cf

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3cf, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAutoMargins ()
    throws ActiveXException {
    // memid = 0x6d5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoMargins (boolean param1)
    throws ActiveXException {
    // memid = 0x6d5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6d5, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<TextFrame, super = " + super.toString() + ">";
}


}

