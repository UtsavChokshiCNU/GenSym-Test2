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


public class Validation extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2442f, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Validation (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #463
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Validation
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 37 functions.
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

  public void Add (int param1)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xb5, AX_INVOKE, true, args);
  }

  public void Add (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0xb5, AX_INVOKE, true, args);
  }

  public void Add (int param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0xb5, AX_INVOKE, true, args);
  }

  public void Add (int param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0xb5, AX_INVOKE, true, args);
  }

  public void Add (int param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0xb5

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0xb5, AX_INVOKE, true, args);
  }

  public int getAxAlertStyle ()
    throws ActiveXException {
    // memid = 0x645

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x645, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxIgnoreBlank ()
    throws ActiveXException {
    // memid = 0x646

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x646, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIgnoreBlank (boolean param1)
    throws ActiveXException {
    // memid = 0x646

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x646, AX_PROPERTYSET, true, args);
  }

  public int getAxIMEMode ()
    throws ActiveXException {
    // memid = 0x647

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x647, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxIMEMode (int param1)
    throws ActiveXException {
    // memid = 0x647

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x647, AX_PROPERTYSET, true, args);
  }

  public boolean getAxInCellDropdown ()
    throws ActiveXException {
    // memid = 0x648

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x648, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxInCellDropdown (boolean param1)
    throws ActiveXException {
    // memid = 0x648

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x648, AX_PROPERTYSET, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public String getAxErrorMessage ()
    throws ActiveXException {
    // memid = 0x649

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x649, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxErrorMessage (String param1)
    throws ActiveXException {
    // memid = 0x649

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x649, AX_PROPERTYSET, true, args);
  }

  public String getAxErrorTitle ()
    throws ActiveXException {
    // memid = 0x64a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64a, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxErrorTitle (String param1)
    throws ActiveXException {
    // memid = 0x64a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x64a, AX_PROPERTYSET, true, args);
  }

  public String getAxInputMessage ()
    throws ActiveXException {
    // memid = 0x64b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64b, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxInputMessage (String param1)
    throws ActiveXException {
    // memid = 0x64b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x64b, AX_PROPERTYSET, true, args);
  }

  public String getAxInputTitle ()
    throws ActiveXException {
    // memid = 0x64c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64c, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxInputTitle (String param1)
    throws ActiveXException {
    // memid = 0x64c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x64c, AX_PROPERTYSET, true, args);
  }

  public String getAxFormula1 ()
    throws ActiveXException {
    // memid = 0x62b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x62b, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxFormula2 ()
    throws ActiveXException {
    // memid = 0x62c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x62c, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void Modify ()
    throws ActiveXException {
    // memid = 0x62d

    Vector args = new Vector(0);
    axInvoke(0x62d, AX_INVOKE, true, args);
  }

  public void Modify (Variant param1)
    throws ActiveXException {
    // memid = 0x62d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x62d, AX_INVOKE, true, args);
  }

  public void Modify (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x62d

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x62d, AX_INVOKE, true, args);
  }

  public void Modify (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x62d

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x62d, AX_INVOKE, true, args);
  }

  public void Modify (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x62d

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x62d, AX_INVOKE, true, args);
  }

  public void Modify (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x62d

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x62d, AX_INVOKE, true, args);
  }

  public int getAxOperator ()
    throws ActiveXException {
    // memid = 0x31d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x31d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxShowError ()
    throws ActiveXException {
    // memid = 0x64d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowError (boolean param1)
    throws ActiveXException {
    // memid = 0x64d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x64d, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShowInput ()
    throws ActiveXException {
    // memid = 0x64e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowInput (boolean param1)
    throws ActiveXException {
    // memid = 0x64e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x64e, AX_PROPERTYSET, true, args);
  }

  public int getAxType ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxValue ()
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

@Override
public String toString() {
    return "<Validation, super = " + super.toString() + ">";
}


}

