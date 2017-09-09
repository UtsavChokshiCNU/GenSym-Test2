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


public class OLEObjects extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208a3, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public OLEObjects (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #430
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: OLEObjects
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 66 functions.
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

  public void BringToFront ()
    throws ActiveXException {
    // memid = 0x25a

    Vector args = new Vector(0);
    axInvoke(0x25a, AX_INVOKE, true, args);
  }

  public void Copy ()
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(0);
    axInvoke(0x227, AX_INVOKE, true, args);
  }

  public void CopyPicture (int param1, int param2)
    throws ActiveXException {
    // memid = 0xd5

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0xd5, AX_INVOKE, true, args);
  }

  public void Cut ()
    throws ActiveXException {
    // memid = 0x235

    Vector args = new Vector(0);
    axInvoke(0x235, AX_INVOKE, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable Duplicate ()
    throws ActiveXException {
    // memid = 0x40f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x40f, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxEnabled ()
    throws ActiveXException {
    // memid = 0x258

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x258, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnabled (boolean param1)
    throws ActiveXException {
    // memid = 0x258

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x258, AX_PROPERTYSET, true, args);
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

  public void _Dummy15 ()
    throws ActiveXException {
    // memid = 0x1000f

    Vector args = new Vector(0);
    axInvoke(0x1000f, AX_INVOKE, true, args);
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

  public Variant getAxPlacement ()
    throws ActiveXException {
    // memid = 0x269

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x269, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxPlacement (Variant param1)
    throws ActiveXException {
    // memid = 0x269

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x269, AX_PROPERTYSET, true, args);
  }

  public boolean getAxPrintObject ()
    throws ActiveXException {
    // memid = 0x26a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x26a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPrintObject (boolean param1)
    throws ActiveXException {
    // memid = 0x26a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x26a, AX_PROPERTYSET, true, args);
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

  public void SendToBack ()
    throws ActiveXException {
    // memid = 0x25d

    Vector args = new Vector(0);
    axInvoke(0x25d, AX_INVOKE, true, args);
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

  public int getAxZOrder ()
    throws ActiveXException {
    // memid = 0x26e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x26e, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ShapeRange getAxShapeRange ()
    throws ActiveXException {
    // memid = 0x5f8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5f8, AX_PROPERTYGET, false, args);
    ShapeRange result = new ShapeRange(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Border getAxBorder ()
    throws ActiveXException {
    // memid = 0x80

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80, AX_PROPERTYGET, false, args);
    Border result = new Border(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Interior getAxInterior ()
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x81, AX_PROPERTYGET, false, args);
    Interior result = new Interior(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxShadow ()
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShadow (boolean param1)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67, AX_PROPERTYSET, true, args);
  }

  public void _Dummy30 ()
    throws ActiveXException {
    // memid = 0x1001e

    Vector args = new Vector(0);
    axInvoke(0x1001e, AX_INVOKE, true, args);
  }

  public boolean getAxAutoLoad ()
    throws ActiveXException {
    // memid = 0x4a2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4a2, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoLoad (boolean param1)
    throws ActiveXException {
    // memid = 0x4a2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4a2, AX_PROPERTYSET, true, args);
  }

  public void _Dummy32 ()
    throws ActiveXException {
    // memid = 0x10020

    Vector args = new Vector(0);
    axInvoke(0x10020, AX_INVOKE, true, args);
  }

  public void _Dummy33 ()
    throws ActiveXException {
    // memid = 0x10021

    Vector args = new Vector(0);
    axInvoke(0x10021, AX_INVOKE, true, args);
  }

  public void _Dummy34 ()
    throws ActiveXException {
    // memid = 0x10022

    Vector args = new Vector(0);
    axInvoke(0x10022, AX_INVOKE, true, args);
  }

  public String getAxSourceName ()
    throws ActiveXException {
    // memid = 0x2d1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2d1, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxSourceName (String param1)
    throws ActiveXException {
    // memid = 0x2d1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x2d1, AX_PROPERTYSET, true, args);
  }

  public void _Dummy36 ()
    throws ActiveXException {
    // memid = 0x10024

    Vector args = new Vector(0);
    axInvoke(0x10024, AX_INVOKE, true, args);
  }

  public void _Dummy37 ()
    throws ActiveXException {
    // memid = 0x10025

    Vector args = new Vector(0);
    axInvoke(0x10025, AX_INVOKE, true, args);
  }

  public void _Dummy38 ()
    throws ActiveXException {
    // memid = 0x10026

    Vector args = new Vector(0);
    axInvoke(0x10026, AX_INVOKE, true, args);
  }

  public void _Dummy39 ()
    throws ActiveXException {
    // memid = 0x10027

    Vector args = new Vector(0);
    axInvoke(0x10027, AX_INVOKE, true, args);
  }

  public void _Dummy40 ()
    throws ActiveXException {
    // memid = 0x10028

    Vector args = new Vector(0);
    axInvoke(0x10028, AX_INVOKE, true, args);
  }

  public Variant Add ()
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(9);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(10);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Add (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(11);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    return vResult;
  }

  public int getAxCount ()
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x76, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public GroupObject Group ()
    throws ActiveXException {
    // memid = 0x2e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2e, AX_INVOKE, false, args);
    GroupObject result = new GroupObject(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable Item (Variant param1)
    throws ActiveXException {
    // memid = 0xaa

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xaa, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
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

@Override
public String toString() {
    return "<OLEObjects, super = " + super.toString() + ">";
}


}

