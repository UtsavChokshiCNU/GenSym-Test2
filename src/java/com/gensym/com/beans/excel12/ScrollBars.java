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


public class ScrollBars extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20886, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public ScrollBars (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #402
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: ScrollBars
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 65 functions.
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

  public int getAx_Default ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAx_Default (int param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x0, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDisplay3DShading ()
    throws ActiveXException {
    // memid = 0x462

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x462, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplay3DShading (boolean param1)
    throws ActiveXException {
    // memid = 0x462

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x462, AX_PROPERTYSET, true, args);
  }

  public String getAxLinkedCell ()
    throws ActiveXException {
    // memid = 0x422

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x422, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxLinkedCell (String param1)
    throws ActiveXException {
    // memid = 0x422

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x422, AX_PROPERTYSET, true, args);
  }

  public int getAxMax ()
    throws ActiveXException {
    // memid = 0x34a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x34a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMax (int param1)
    throws ActiveXException {
    // memid = 0x34a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x34a, AX_PROPERTYSET, true, args);
  }

  public int getAxMin ()
    throws ActiveXException {
    // memid = 0x34b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x34b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxMin (int param1)
    throws ActiveXException {
    // memid = 0x34b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x34b, AX_PROPERTYSET, true, args);
  }

  public int getAxSmallChange ()
    throws ActiveXException {
    // memid = 0x34c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x34c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSmallChange (int param1)
    throws ActiveXException {
    // memid = 0x34c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x34c, AX_PROPERTYSET, true, args);
  }

  public int getAxValue ()
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxValue (int param1)
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6, AX_PROPERTYSET, true, args);
  }

  public int getAxLargeChange ()
    throws ActiveXException {
    // memid = 0x34d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x34d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxLargeChange (int param1)
    throws ActiveXException {
    // memid = 0x34d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x34d, AX_PROPERTYSET, true, args);
  }

  public ScrollBar Add (double param1, double param2, double param3, double param4)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0xb5, AX_INVOKE, false, args);
    ScrollBar result = new ScrollBar(vResult.getActiveXDispatchableValue());
    return result;
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
    return "<ScrollBars, super = " + super.toString() + ">";
}


}

