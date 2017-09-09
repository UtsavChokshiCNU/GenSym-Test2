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


public class AutoCorrect extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208d4, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public AutoCorrect (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #469
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: AutoCorrect
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 23 functions.
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

  public void AddReplacement (String param1, String param2)
    throws ActiveXException {
    // memid = 0x47a

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x47a, AX_INVOKE, true, args);
  }

  public boolean getAxCapitalizeNamesOfDays ()
    throws ActiveXException {
    // memid = 0x47e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x47e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxCapitalizeNamesOfDays (boolean param1)
    throws ActiveXException {
    // memid = 0x47e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x47e, AX_PROPERTYSET, true, args);
  }

  public void DeleteReplacement (String param1)
    throws ActiveXException {
    // memid = 0x47b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x47b, AX_INVOKE, true, args);
  }

  public Variant ReplacementList ()
    throws ActiveXException {
    // memid = 0x47f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x47f, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant ReplacementList (Variant param1)
    throws ActiveXException {
    // memid = 0x47f

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x47f, AX_INVOKE, false, args);
    return vResult;
  }

  public boolean getAxReplaceText ()
    throws ActiveXException {
    // memid = 0x47c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x47c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxReplaceText (boolean param1)
    throws ActiveXException {
    // memid = 0x47c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x47c, AX_PROPERTYSET, true, args);
  }

  public boolean getAxTwoInitialCapitals ()
    throws ActiveXException {
    // memid = 0x47d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x47d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxTwoInitialCapitals (boolean param1)
    throws ActiveXException {
    // memid = 0x47d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x47d, AX_PROPERTYSET, true, args);
  }

  public boolean getAxCorrectSentenceCap ()
    throws ActiveXException {
    // memid = 0x653

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x653, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxCorrectSentenceCap (boolean param1)
    throws ActiveXException {
    // memid = 0x653

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x653, AX_PROPERTYSET, true, args);
  }

  public boolean getAxCorrectCapsLock ()
    throws ActiveXException {
    // memid = 0x654

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x654, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxCorrectCapsLock (boolean param1)
    throws ActiveXException {
    // memid = 0x654

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x654, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<AutoCorrect, super = " + super.toString() + ">";
}


}

