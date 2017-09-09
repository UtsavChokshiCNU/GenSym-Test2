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


public class Balloon extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc0324, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Balloon (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #98
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Balloon
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    Type Info contains 34 functions.
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

  public ActiveXDispatchable getAxParent ()
    throws ActiveXException {
    // memid = 0x60030000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030000, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable getAxCheckboxes ()
    throws ActiveXException {
    // memid = 0x60030001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030001, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable getAxLabels ()
    throws ActiveXException {
    // memid = 0x60030002

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030002, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void setAxBalloonType (int param1)
    throws ActiveXException {
    // memid = 0x60030003

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030003, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoBalloonType
  public int getAxBalloonType ()
    throws ActiveXException {
    // memid = 0x60030003

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030003, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxIcon (int param1)
    throws ActiveXException {
    // memid = 0x60030005

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030005, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoIconType
  public int getAxIcon ()
    throws ActiveXException {
    // memid = 0x60030005

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030005, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHeading (String param1)
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030007, AX_PROPERTYSET, true, args);
  }

  public String getAxHeading ()
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030007, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxText (String param1)
    throws ActiveXException {
    // memid = 0x60030009

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030009, AX_PROPERTYSET, true, args);
  }

  public String getAxText ()
    throws ActiveXException {
    // memid = 0x60030009

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030009, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxMode (int param1)
    throws ActiveXException {
    // memid = 0x6003000b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003000b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoModeType
  public int getAxMode ()
    throws ActiveXException {
    // memid = 0x6003000b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxAnimation (int param1)
    throws ActiveXException {
    // memid = 0x6003000d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003000d, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoAnimationType
  public int getAxAnimation ()
    throws ActiveXException {
    // memid = 0x6003000d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxButton (int param1)
    throws ActiveXException {
    // memid = 0x6003000f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003000f, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoButtonSetType
  public int getAxButton ()
    throws ActiveXException {
    // memid = 0x6003000f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxCallback (String param1)
    throws ActiveXException {
    // memid = 0x60030011

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030011, AX_PROPERTYSET, true, args);
  }

  public String getAxCallback ()
    throws ActiveXException {
    // memid = 0x60030011

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030011, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxPrivate (int param1)
    throws ActiveXException {
    // memid = 0x60030013

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030013, AX_PROPERTYSET, true, args);
  }

  public int getAxPrivate ()
    throws ActiveXException {
    // memid = 0x60030013

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030013, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void SetAvoidRectangle (int param1, int param2, int param3, int param4)
    throws ActiveXException {
    // memid = 0x60030015

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(new Variant(param4));
    axInvoke(0x60030015, AX_INVOKE, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x60030016

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030016, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

    // Enumeration type = MsoBalloonButtonType
  public int Show ()
    throws ActiveXException {
    // memid = 0x60030017

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030017, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void Close ()
    throws ActiveXException {
    // memid = 0x60030018

    Vector args = new Vector(0);
    axInvoke(0x60030018, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<Balloon, super = " + super.toString() + ">";
}


}

