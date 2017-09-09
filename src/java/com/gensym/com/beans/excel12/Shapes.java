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


public class Shapes extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2443a, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Shapes (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #509
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Shapes
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 29 functions.
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

  public int getAxCount ()
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x76, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Shape Item (Variant param1)
    throws ActiveXException {
    // memid = 0xaa

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xaa, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape _Default (Variant param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x0, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Object getAx_NewEnum ()
    throws ActiveXException {
    // memid = 0xfffffffc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xfffffffc, AX_PROPERTYGET, false, args);
    Object result = vResult.getGenericValue();
    return result;
  }

  public Shape AddCallout (int param1, float param2, float param3, float param4, float param5)
    throws ActiveXException {
    // memid = 0x6b1

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    Variant vResult = axInvoke(0x6b1, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddConnector (int param1, float param2, float param3, float param4, float param5)
    throws ActiveXException {
    // memid = 0x6b2

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    Variant vResult = axInvoke(0x6b2, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddCurve (Variant param1)
    throws ActiveXException {
    // memid = 0x6b7

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x6b7, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddLabel (int param1, float param2, float param3, float param4, float param5)
    throws ActiveXException {
    // memid = 0x6b9

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    Variant vResult = axInvoke(0x6b9, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddLine (float param1, float param2, float param3, float param4)
    throws ActiveXException {
    // memid = 0x6ba

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    Variant vResult = axInvoke(0x6ba, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddPicture (String param1, int param2, int param3, float param4, float param5, float param6, float param7)
    throws ActiveXException {
    // memid = 0x6bb

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    args.addElement(new Variant(param6));
    args.addElement(new Variant(param7));
    Variant vResult = axInvoke(0x6bb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddPolyline (Variant param1)
    throws ActiveXException {
    // memid = 0x6be

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x6be, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddShape (int param1, float param2, float param3, float param4, float param5)
    throws ActiveXException {
    // memid = 0x6bf

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    Variant vResult = axInvoke(0x6bf, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddTextEffect (int param1, String param2, String param3, float param4, int param5, int param6, float param7, float param8)
    throws ActiveXException {
    // memid = 0x6c0

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    args.addElement(new Variant(param6));
    args.addElement(new Variant(param7));
    args.addElement(new Variant(param8));
    Variant vResult = axInvoke(0x6c0, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddTextbox (int param1, float param2, float param3, float param4, float param5)
    throws ActiveXException {
    // memid = 0x6c6

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    Variant vResult = axInvoke(0x6c6, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public FreeformBuilder BuildFreeform (int param1, float param2, float param3)
    throws ActiveXException {
    // memid = 0x6c7

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x6c7, AX_INVOKE, false, args);
    FreeformBuilder result = new FreeformBuilder(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ShapeRange getAxRange (Variant param1)
    throws ActiveXException {
    // memid = 0xc5

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xc5, AX_PROPERTYGET, false, args);
    ShapeRange result = new ShapeRange(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void SelectAll ()
    throws ActiveXException {
    // memid = 0x6c9

    Vector args = new Vector(0);
    axInvoke(0x6c9, AX_INVOKE, true, args);
  }

  public Shape AddFormControl (int param1, int param2, int param3, int param4, int param5)
    throws ActiveXException {
    // memid = 0x6ca

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    args.addElement(new Variant(param5));
    Variant vResult = axInvoke(0x6ca, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject ()
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1)
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x6cb

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x6cb

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
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x6cb

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
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Shape AddOLEObject (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x6cb

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
    Variant vResult = axInvoke(0x6cb, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

@Override
public String toString() {
    return "<Shapes, super = " + super.toString() + ">";
}


}

