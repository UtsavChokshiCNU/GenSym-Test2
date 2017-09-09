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


public class DialogFrame extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2088f, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public DialogFrame (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #411
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: DialogFrame
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 49 functions.
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

  public void _Dummy3 ()
    throws ActiveXException {
    // memid = 0x10003

    Vector args = new Vector(0);
    axInvoke(0x10003, AX_INVOKE, true, args);
  }

  public void _Dummy4 ()
    throws ActiveXException {
    // memid = 0x10004

    Vector args = new Vector(0);
    axInvoke(0x10004, AX_INVOKE, true, args);
  }

  public void _Dummy5 ()
    throws ActiveXException {
    // memid = 0x10005

    Vector args = new Vector(0);
    axInvoke(0x10005, AX_INVOKE, true, args);
  }

  public void CopyPicture (int param1, int param2)
    throws ActiveXException {
    // memid = 0xd5

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0xd5, AX_INVOKE, true, args);
  }

  public void _Dummy7 ()
    throws ActiveXException {
    // memid = 0x10007

    Vector args = new Vector(0);
    axInvoke(0x10007, AX_INVOKE, true, args);
  }

  public void _Dummy8 ()
    throws ActiveXException {
    // memid = 0x10008

    Vector args = new Vector(0);
    axInvoke(0x10008, AX_INVOKE, true, args);
  }

  public void _Dummy9 ()
    throws ActiveXException {
    // memid = 0x10009

    Vector args = new Vector(0);
    axInvoke(0x10009, AX_INVOKE, true, args);
  }

  public void _Dummy10 ()
    throws ActiveXException {
    // memid = 0x1000a

    Vector args = new Vector(0);
    axInvoke(0x1000a, AX_INVOKE, true, args);
  }

  public double getAxHeight ()
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7b, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxHeight (double param1)
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7b, AX_PROPERTYSET, true, args);
  }

  public void _Dummy12 ()
    throws ActiveXException {
    // memid = 0x1000c

    Vector args = new Vector(0);
    axInvoke(0x1000c, AX_INVOKE, true, args);
  }

  public double getAxLeft ()
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7f, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxLeft (double param1)
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7f, AX_PROPERTYSET, true, args);
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

  public String getAxOnAction ()
    throws ActiveXException {
    // memid = 0x254

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x254, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnAction (String param1)
    throws ActiveXException {
    // memid = 0x254

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x254, AX_PROPERTYSET, true, args);
  }

  public void _Dummy17 ()
    throws ActiveXException {
    // memid = 0x10011

    Vector args = new Vector(0);
    axInvoke(0x10011, AX_INVOKE, true, args);
  }

  public void _Dummy18 ()
    throws ActiveXException {
    // memid = 0x10012

    Vector args = new Vector(0);
    axInvoke(0x10012, AX_INVOKE, true, args);
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(0);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public void Select (Variant param1)
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public void _Dummy20 ()
    throws ActiveXException {
    // memid = 0x10014

    Vector args = new Vector(0);
    axInvoke(0x10014, AX_INVOKE, true, args);
  }

  public double getAxTop ()
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7e, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxTop (double param1)
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7e, AX_PROPERTYSET, true, args);
  }

  public void _Dummy22 ()
    throws ActiveXException {
    // memid = 0x10016

    Vector args = new Vector(0);
    axInvoke(0x10016, AX_INVOKE, true, args);
  }

  public void _Dummy23 ()
    throws ActiveXException {
    // memid = 0x10017

    Vector args = new Vector(0);
    axInvoke(0x10017, AX_INVOKE, true, args);
  }

  public double getAxWidth ()
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7a, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxWidth (double param1)
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7a, AX_PROPERTYSET, true, args);
  }

  public void _Dummy25 ()
    throws ActiveXException {
    // memid = 0x10019

    Vector args = new Vector(0);
    axInvoke(0x10019, AX_INVOKE, true, args);
  }

  public ShapeRange getAxShapeRange ()
    throws ActiveXException {
    // memid = 0x5f8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5f8, AX_PROPERTYGET, false, args);
    ShapeRange result = new ShapeRange(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxCaption ()
    throws ActiveXException {
    // memid = 0x8b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8b, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCaption (String param1)
    throws ActiveXException {
    // memid = 0x8b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8b, AX_PROPERTYSET, true, args);
  }

  public Characters getAxCharacters ()
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x25b, AX_PROPERTYGET, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Characters getAxCharacters (Variant param1)
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x25b, AX_PROPERTYGET, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Characters getAxCharacters (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x25b, AX_PROPERTYGET, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void CheckSpelling ()
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(0);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public void CheckSpelling (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x1f9

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x1f9, AX_INVOKE, true, args);
  }

  public boolean getAxLockedText ()
    throws ActiveXException {
    // memid = 0x268

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x268, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxLockedText (boolean param1)
    throws ActiveXException {
    // memid = 0x268

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x268, AX_PROPERTYSET, true, args);
  }

  public String getAxText ()
    throws ActiveXException {
    // memid = 0x8a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8a, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxText (String param1)
    throws ActiveXException {
    // memid = 0x8a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8a, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<DialogFrame, super = " + super.toString() + ">";
}


}

