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


public class Module extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208ad, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Module (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #439
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Module
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 43 functions.
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

  public void Activate ()
    throws ActiveXException {
    // memid = 0x130

    Vector args = new Vector(0);
    axInvoke(0x130, AX_INVOKE, true, args);
  }

  public void Copy ()
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(0);
    axInvoke(0x227, AX_INVOKE, true, args);
  }

  public void Copy (Variant param1)
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x227, AX_INVOKE, true, args);
  }

  public void Copy (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x227, AX_INVOKE, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public String getAxCodeName ()
    throws ActiveXException {
    // memid = 0x55d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x55d, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAx_CodeName ()
    throws ActiveXException {
    // memid = 0x80010000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80010000, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAx_CodeName (String param1)
    throws ActiveXException {
    // memid = 0x80010000

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x80010000, AX_PROPERTYSET, true, args);
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x1e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e6, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void Move ()
    throws ActiveXException {
    // memid = 0x27d

    Vector args = new Vector(0);
    axInvoke(0x27d, AX_INVOKE, true, args);
  }

  public void Move (Variant param1)
    throws ActiveXException {
    // memid = 0x27d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x27d, AX_INVOKE, true, args);
  }

  public void Move (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x27d

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x27d, AX_INVOKE, true, args);
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

  public ActiveXDispatchable getAxNext ()
    throws ActiveXException {
    // memid = 0x1f6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f6, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public String getAxOnDoubleClick ()
    throws ActiveXException {
    // memid = 0x274

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x274, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnDoubleClick (String param1)
    throws ActiveXException {
    // memid = 0x274

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x274, AX_PROPERTYSET, true, args);
  }

  public String getAxOnSheetActivate ()
    throws ActiveXException {
    // memid = 0x407

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x407, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnSheetActivate (String param1)
    throws ActiveXException {
    // memid = 0x407

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x407, AX_PROPERTYSET, true, args);
  }

  public String getAxOnSheetDeactivate ()
    throws ActiveXException {
    // memid = 0x439

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x439, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnSheetDeactivate (String param1)
    throws ActiveXException {
    // memid = 0x439

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x439, AX_PROPERTYSET, true, args);
  }

  public PageSetup getAxPageSetup ()
    throws ActiveXException {
    // memid = 0x3e6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e6, AX_PROPERTYGET, false, args);
    PageSetup result = new PageSetup(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable getAxPrevious ()
    throws ActiveXException {
    // memid = 0x1f7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f7, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void PrintOut ()
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(0);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void PrintOut (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x389

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x389, AX_INVOKE, true, args);
  }

  public void _Dummy18 ()
    throws ActiveXException {
    // memid = 0x10012

    Vector args = new Vector(0);
    axInvoke(0x10012, AX_INVOKE, true, args);
  }

  public void Protect ()
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(0);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public void Protect (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x11a

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x11a, AX_INVOKE, true, args);
  }

  public boolean getAxProtectContents ()
    throws ActiveXException {
    // memid = 0x124

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x124, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void _Dummy21 ()
    throws ActiveXException {
    // memid = 0x10015

    Vector args = new Vector(0);
    axInvoke(0x10015, AX_INVOKE, true, args);
  }

  public boolean getAxProtectionMode ()
    throws ActiveXException {
    // memid = 0x487

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x487, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void _Dummy23 ()
    throws ActiveXException {
    // memid = 0x10017

    Vector args = new Vector(0);
    axInvoke(0x10017, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(9);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    axInvoke(0x11c, AX_INVOKE, true, args);
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

  public void Unprotect ()
    throws ActiveXException {
    // memid = 0x11d

    Vector args = new Vector(0);
    axInvoke(0x11d, AX_INVOKE, true, args);
  }

  public void Unprotect (Variant param1)
    throws ActiveXException {
    // memid = 0x11d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x11d, AX_INVOKE, true, args);
  }

    // Enumeration type = XlSheetVisibility
  public int getAxVisible ()
    throws ActiveXException {
    // memid = 0x22e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x22e, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxVisible (int param1)
    throws ActiveXException {
    // memid = 0x22e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x22e, AX_PROPERTYSET, true, args);
  }

  public Shapes getAxShapes ()
    throws ActiveXException {
    // memid = 0x561

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x561, AX_PROPERTYGET, false, args);
    Shapes result = new Shapes(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void InsertFile (Variant param1)
    throws ActiveXException {
    // memid = 0x248

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x248, AX_INVOKE, true, args);
  }

  public void InsertFile (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x248

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x248, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<Module, super = " + super.toString() + ">";
}


}

