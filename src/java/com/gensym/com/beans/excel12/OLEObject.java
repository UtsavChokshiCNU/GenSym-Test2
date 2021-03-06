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


public class OLEObject extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208a2, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public OLEObject (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #429
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _OLEObject
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
    // memid = 0x80010094

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010094, AX_PROPERTYGET, false, args);
    ExcelApplication result = new ExcelApplication(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlCreator
  public int getAxCreator ()
    throws ActiveXException {
    // memid = 0x80010095

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010095, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ActiveXDispatchable getAxParent ()
    throws ActiveXException {
    // memid = 0x80010096

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010096, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Range getAxBottomRightCell ()
    throws ActiveXException {
    // memid = 0x80010267

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010267, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void BringToFront ()
    throws ActiveXException {
    // memid = 0x8001025a

    Vector args = new Vector(0);
    axInvoke(0x8001025a, AX_INVOKE, true, args);
  }

  public void Copy ()
    throws ActiveXException {
    // memid = 0x80010227

    Vector args = new Vector(0);
    axInvoke(0x80010227, AX_INVOKE, true, args);
  }

  public void CopyPicture (int param1, int param2)
    throws ActiveXException {
    // memid = 0x800100d5

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x800100d5, AX_INVOKE, true, args);
  }

  public void Cut ()
    throws ActiveXException {
    // memid = 0x80010235

    Vector args = new Vector(0);
    axInvoke(0x80010235, AX_INVOKE, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x80010075

    Vector args = new Vector(0);
    axInvoke(0x80010075, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable Duplicate ()
    throws ActiveXException {
    // memid = 0x8001040f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001040f, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxEnabled ()
    throws ActiveXException {
    // memid = 0x80010258

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010258, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnabled (boolean param1)
    throws ActiveXException {
    // memid = 0x80010258

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x80010258, AX_PROPERTYSET, true, args);
  }

  public double getAxHeight ()
    throws ActiveXException {
    // memid = 0x8001007b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001007b, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxHeight (double param1)
    throws ActiveXException {
    // memid = 0x8001007b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001007b, AX_PROPERTYSET, true, args);
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x800101e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x800101e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public double getAxLeft ()
    throws ActiveXException {
    // memid = 0x8001007f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001007f, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxLeft (double param1)
    throws ActiveXException {
    // memid = 0x8001007f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001007f, AX_PROPERTYSET, true, args);
  }

  public boolean getAxLocked ()
    throws ActiveXException {
    // memid = 0x8001010d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001010d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxLocked (boolean param1)
    throws ActiveXException {
    // memid = 0x8001010d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001010d, AX_PROPERTYSET, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x8001006e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001006e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x8001006e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001006e, AX_PROPERTYSET, true, args);
  }

  public String getAxOnAction ()
    throws ActiveXException {
    // memid = 0x80010254

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010254, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnAction (String param1)
    throws ActiveXException {
    // memid = 0x80010254

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x80010254, AX_PROPERTYSET, true, args);
  }

  public Variant getAxPlacement ()
    throws ActiveXException {
    // memid = 0x80010269

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010269, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxPlacement (Variant param1)
    throws ActiveXException {
    // memid = 0x80010269

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x80010269, AX_PROPERTYSET, true, args);
  }

  public boolean getAxPrintObject ()
    throws ActiveXException {
    // memid = 0x8001026a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001026a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPrintObject (boolean param1)
    throws ActiveXException {
    // memid = 0x8001026a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001026a, AX_PROPERTYSET, true, args);
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0x800100eb

    Vector args = new Vector(0);
    axInvoke(0x800100eb, AX_INVOKE, true, args);
  }

  public void Select (Variant param1)
    throws ActiveXException {
    // memid = 0x800100eb

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x800100eb, AX_INVOKE, true, args);
  }

  public void SendToBack ()
    throws ActiveXException {
    // memid = 0x8001025d

    Vector args = new Vector(0);
    axInvoke(0x8001025d, AX_INVOKE, true, args);
  }

  public double getAxTop ()
    throws ActiveXException {
    // memid = 0x8001007e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001007e, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxTop (double param1)
    throws ActiveXException {
    // memid = 0x8001007e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001007e, AX_PROPERTYSET, true, args);
  }

  public Range getAxTopLeftCell ()
    throws ActiveXException {
    // memid = 0x8001026c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001026c, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxVisible ()
    throws ActiveXException {
    // memid = 0x8001022e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001022e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxVisible (boolean param1)
    throws ActiveXException {
    // memid = 0x8001022e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001022e, AX_PROPERTYSET, true, args);
  }

  public double getAxWidth ()
    throws ActiveXException {
    // memid = 0x8001007a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001007a, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxWidth (double param1)
    throws ActiveXException {
    // memid = 0x8001007a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001007a, AX_PROPERTYSET, true, args);
  }

  public int getAxZOrder ()
    throws ActiveXException {
    // memid = 0x8001026e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001026e, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ShapeRange getAxShapeRange ()
    throws ActiveXException {
    // memid = 0x800105f8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x800105f8, AX_PROPERTYGET, false, args);
    ShapeRange result = new ShapeRange(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Border getAxBorder ()
    throws ActiveXException {
    // memid = 0x80010080

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010080, AX_PROPERTYGET, false, args);
    Border result = new Border(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Interior getAxInterior ()
    throws ActiveXException {
    // memid = 0x80010081

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010081, AX_PROPERTYGET, false, args);
    Interior result = new Interior(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxShadow ()
    throws ActiveXException {
    // memid = 0x80010067

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010067, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShadow (boolean param1)
    throws ActiveXException {
    // memid = 0x80010067

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x80010067, AX_PROPERTYSET, true, args);
  }

  public void Activate ()
    throws ActiveXException {
    // memid = 0x80010130

    Vector args = new Vector(0);
    axInvoke(0x80010130, AX_INVOKE, true, args);
  }

  public boolean getAxAutoLoad ()
    throws ActiveXException {
    // memid = 0x800104a2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x800104a2, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoLoad (boolean param1)
    throws ActiveXException {
    // memid = 0x800104a2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x800104a2, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAutoUpdate ()
    throws ActiveXException {
    // memid = 0x80010418

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010418, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoUpdate (boolean param1)
    throws ActiveXException {
    // memid = 0x80010418

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x80010418, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxObject ()
    throws ActiveXException {
    // memid = 0x80010419

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010419, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Variant getAxOLEType ()
    throws ActiveXException {
    // memid = 0x8001041e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001041e, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public String getAxSourceName ()
    throws ActiveXException {
    // memid = 0x800102d1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x800102d1, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxSourceName (String param1)
    throws ActiveXException {
    // memid = 0x800102d1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x800102d1, AX_PROPERTYSET, true, args);
  }

  public void Update ()
    throws ActiveXException {
    // memid = 0x800102a8

    Vector args = new Vector(0);
    axInvoke(0x800102a8, AX_INVOKE, true, args);
  }

  public void Verb (int param1)
    throws ActiveXException {
    // memid = 0x8001025e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001025e, AX_INVOKE, true, args);
  }

  public String getAxLinkedCell ()
    throws ActiveXException {
    // memid = 0x80010422

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010422, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxLinkedCell (String param1)
    throws ActiveXException {
    // memid = 0x80010422

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x80010422, AX_PROPERTYSET, true, args);
  }

  public String getAxListFillRange ()
    throws ActiveXException {
    // memid = 0x8001034f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8001034f, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxListFillRange (String param1)
    throws ActiveXException {
    // memid = 0x8001034f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x8001034f, AX_PROPERTYSET, true, args);
  }

  public String getAxProgId ()
    throws ActiveXException {
    // memid = 0x800105f3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x800105f3, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

@Override
public String toString() {
    return "<OLEObject, super = " + super.toString() + ">";
}


}

