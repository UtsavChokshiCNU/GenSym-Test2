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


public class Worksheet extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208d8, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Worksheet (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #180
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _Worksheet
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 130 functions.
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

  public void PrintPreview ()
    throws ActiveXException {
    // memid = 0x119

    Vector args = new Vector(0);
    axInvoke(0x119, AX_INVOKE, true, args);
  }

  public void PrintPreview (Variant param1)
    throws ActiveXException {
    // memid = 0x119

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x119, AX_INVOKE, true, args);
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

  public boolean getAxProtectDrawingObjects ()
    throws ActiveXException {
    // memid = 0x125

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x125, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxProtectionMode ()
    throws ActiveXException {
    // memid = 0x487

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x487, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxProtectScenarios ()
    throws ActiveXException {
    // memid = 0x126

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x126, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
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

  public boolean getAxTransitionExpEval ()
    throws ActiveXException {
    // memid = 0x191

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x191, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxTransitionExpEval (boolean param1)
    throws ActiveXException {
    // memid = 0x191

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x191, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable Arcs ()
    throws ActiveXException {
    // memid = 0x2f8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2f8, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Arcs (Variant param1)
    throws ActiveXException {
    // memid = 0x2f8

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2f8, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxAutoFilterMode ()
    throws ActiveXException {
    // memid = 0x318

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x318, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoFilterMode (boolean param1)
    throws ActiveXException {
    // memid = 0x318

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x318, AX_PROPERTYSET, true, args);
  }

  public void SetBackgroundPicture (String param1)
    throws ActiveXException {
    // memid = 0x4a4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4a4, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable Buttons ()
    throws ActiveXException {
    // memid = 0x22d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x22d, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Buttons (Variant param1)
    throws ActiveXException {
    // memid = 0x22d

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x22d, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void Calculate ()
    throws ActiveXException {
    // memid = 0x117

    Vector args = new Vector(0);
    axInvoke(0x117, AX_INVOKE, true, args);
  }

  public boolean getAxEnableCalculation ()
    throws ActiveXException {
    // memid = 0x590

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x590, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableCalculation (boolean param1)
    throws ActiveXException {
    // memid = 0x590

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x590, AX_PROPERTYSET, true, args);
  }

  public Range getAxCells ()
    throws ActiveXException {
    // memid = 0xee

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xee, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable ChartObjects ()
    throws ActiveXException {
    // memid = 0x424

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x424, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ChartObjects (Variant param1)
    throws ActiveXException {
    // memid = 0x424

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x424, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable CheckBoxes ()
    throws ActiveXException {
    // memid = 0x338

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x338, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable CheckBoxes (Variant param1)
    throws ActiveXException {
    // memid = 0x338

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x338, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
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

  public Range getAxCircularReference ()
    throws ActiveXException {
    // memid = 0x42d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x42d, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void ClearArrows ()
    throws ActiveXException {
    // memid = 0x3ca

    Vector args = new Vector(0);
    axInvoke(0x3ca, AX_INVOKE, true, args);
  }

  public Range getAxColumns ()
    throws ActiveXException {
    // memid = 0xf1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf1, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlConsolidationFunction
  public int getAxConsolidationFunction ()
    throws ActiveXException {
    // memid = 0x315

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x315, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Variant getAxConsolidationOptions ()
    throws ActiveXException {
    // memid = 0x316

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x316, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxConsolidationSources ()
    throws ActiveXException {
    // memid = 0x317

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x317, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public boolean getAxDisplayAutomaticPageBreaks ()
    throws ActiveXException {
    // memid = 0x283

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x283, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayAutomaticPageBreaks (boolean param1)
    throws ActiveXException {
    // memid = 0x283

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x283, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable Drawings ()
    throws ActiveXException {
    // memid = 0x304

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x304, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Drawings (Variant param1)
    throws ActiveXException {
    // memid = 0x304

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x304, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DrawingObjects ()
    throws ActiveXException {
    // memid = 0x58

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x58, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DrawingObjects (Variant param1)
    throws ActiveXException {
    // memid = 0x58

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x58, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DropDowns ()
    throws ActiveXException {
    // memid = 0x344

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x344, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable DropDowns (Variant param1)
    throws ActiveXException {
    // memid = 0x344

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x344, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxEnableAutoFilter ()
    throws ActiveXException {
    // memid = 0x484

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x484, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableAutoFilter (boolean param1)
    throws ActiveXException {
    // memid = 0x484

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x484, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlEnableSelection
  public int getAxEnableSelection ()
    throws ActiveXException {
    // memid = 0x591

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x591, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxEnableSelection (int param1)
    throws ActiveXException {
    // memid = 0x591

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x591, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnableOutlining ()
    throws ActiveXException {
    // memid = 0x485

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x485, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnableOutlining (boolean param1)
    throws ActiveXException {
    // memid = 0x485

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x485, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnablePivotTable ()
    throws ActiveXException {
    // memid = 0x486

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x486, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnablePivotTable (boolean param1)
    throws ActiveXException {
    // memid = 0x486

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x486, AX_PROPERTYSET, true, args);
  }

  public Variant Evaluate (Variant param1)
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x1, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant _Evaluate (Variant param1)
    throws ActiveXException {
    // memid = 0xfffffffb

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xfffffffb, AX_INVOKE, false, args);
    return vResult;
  }

  public boolean getAxFilterMode ()
    throws ActiveXException {
    // memid = 0x320

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x320, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void ResetAllPageBreaks ()
    throws ActiveXException {
    // memid = 0x592

    Vector args = new Vector(0);
    axInvoke(0x592, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable GroupBoxes ()
    throws ActiveXException {
    // memid = 0x342

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x342, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable GroupBoxes (Variant param1)
    throws ActiveXException {
    // memid = 0x342

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x342, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable GroupObjects ()
    throws ActiveXException {
    // memid = 0x459

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x459, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable GroupObjects (Variant param1)
    throws ActiveXException {
    // memid = 0x459

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x459, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Labels ()
    throws ActiveXException {
    // memid = 0x349

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x349, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Labels (Variant param1)
    throws ActiveXException {
    // memid = 0x349

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x349, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Lines ()
    throws ActiveXException {
    // memid = 0x2ff

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2ff, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Lines (Variant param1)
    throws ActiveXException {
    // memid = 0x2ff

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2ff, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ListBoxes ()
    throws ActiveXException {
    // memid = 0x340

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x340, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ListBoxes (Variant param1)
    throws ActiveXException {
    // memid = 0x340

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x340, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Names getAxNames ()
    throws ActiveXException {
    // memid = 0x1ba

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1ba, AX_PROPERTYGET, false, args);
    Names result = new Names(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable OLEObjects ()
    throws ActiveXException {
    // memid = 0x31f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x31f, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable OLEObjects (Variant param1)
    throws ActiveXException {
    // memid = 0x31f

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x31f, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public String getAxOnCalculate ()
    throws ActiveXException {
    // memid = 0x271

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x271, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnCalculate (String param1)
    throws ActiveXException {
    // memid = 0x271

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x271, AX_PROPERTYSET, true, args);
  }

  public String getAxOnData ()
    throws ActiveXException {
    // memid = 0x275

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x275, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnData (String param1)
    throws ActiveXException {
    // memid = 0x275

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x275, AX_PROPERTYSET, true, args);
  }

  public String getAxOnEntry ()
    throws ActiveXException {
    // memid = 0x273

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x273, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnEntry (String param1)
    throws ActiveXException {
    // memid = 0x273

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x273, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable OptionButtons ()
    throws ActiveXException {
    // memid = 0x33a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x33a, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable OptionButtons (Variant param1)
    throws ActiveXException {
    // memid = 0x33a

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x33a, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Outline getAxOutline ()
    throws ActiveXException {
    // memid = 0x66

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x66, AX_PROPERTYGET, false, args);
    Outline result = new Outline(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable Ovals ()
    throws ActiveXException {
    // memid = 0x321

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x321, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Ovals (Variant param1)
    throws ActiveXException {
    // memid = 0x321

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x321, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void Paste ()
    throws ActiveXException {
    // memid = 0xd3

    Vector args = new Vector(0);
    axInvoke(0xd3, AX_INVOKE, true, args);
  }

  public void Paste (Variant param1)
    throws ActiveXException {
    // memid = 0xd3

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xd3, AX_INVOKE, true, args);
  }

  public void Paste (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xd3

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0xd3, AX_INVOKE, true, args);
  }

  public void PasteSpecial ()
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(0);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public void PasteSpecial (Variant param1)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public void PasteSpecial (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public void PasteSpecial (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public void PasteSpecial (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public void PasteSpecial (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public void PasteSpecial (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable Pictures ()
    throws ActiveXException {
    // memid = 0x303

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x303, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Pictures (Variant param1)
    throws ActiveXException {
    // memid = 0x303

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x303, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable PivotTables ()
    throws ActiveXException {
    // memid = 0x2b2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b2, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable PivotTables (Variant param1)
    throws ActiveXException {
    // memid = 0x2b2

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2b2, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public PivotTable PivotTableWizard ()
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x2ac

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
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x2ac

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
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x2ac

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
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(12);
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
    args.addElement(param12);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(13);
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
    args.addElement(param12);
    args.addElement(param13);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(14);
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
    args.addElement(param12);
    args.addElement(param13);
    args.addElement(param14);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(15);
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
    args.addElement(param12);
    args.addElement(param13);
    args.addElement(param14);
    args.addElement(param15);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(16);
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
    args.addElement(param12);
    args.addElement(param13);
    args.addElement(param14);
    args.addElement(param15);
    args.addElement(param16);
    Variant vResult = axInvoke(0x2ac, AX_INVOKE, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxRange (Variant param1)
    throws ActiveXException {
    // memid = 0xc5

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xc5, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxRange (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xc5

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0xc5, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable Rectangles ()
    throws ActiveXException {
    // memid = 0x306

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x306, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Rectangles (Variant param1)
    throws ActiveXException {
    // memid = 0x306

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x306, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public Range getAxRows ()
    throws ActiveXException {
    // memid = 0x102

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x102, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable Scenarios ()
    throws ActiveXException {
    // memid = 0x38c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x38c, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Scenarios (Variant param1)
    throws ActiveXException {
    // memid = 0x38c

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x38c, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public String getAxScrollArea ()
    throws ActiveXException {
    // memid = 0x599

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x599, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxScrollArea (String param1)
    throws ActiveXException {
    // memid = 0x599

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x599, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable ScrollBars ()
    throws ActiveXException {
    // memid = 0x33e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x33e, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable ScrollBars (Variant param1)
    throws ActiveXException {
    // memid = 0x33e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x33e, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void ShowAllData ()
    throws ActiveXException {
    // memid = 0x31a

    Vector args = new Vector(0);
    axInvoke(0x31a, AX_INVOKE, true, args);
  }

  public void ShowDataForm ()
    throws ActiveXException {
    // memid = 0x199

    Vector args = new Vector(0);
    axInvoke(0x199, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable Spinners ()
    throws ActiveXException {
    // memid = 0x346

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x346, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable Spinners (Variant param1)
    throws ActiveXException {
    // memid = 0x346

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x346, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public double getAxStandardHeight ()
    throws ActiveXException {
    // memid = 0x197

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x197, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public double getAxStandardWidth ()
    throws ActiveXException {
    // memid = 0x198

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x198, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxStandardWidth (double param1)
    throws ActiveXException {
    // memid = 0x198

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x198, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable TextBoxes ()
    throws ActiveXException {
    // memid = 0x309

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x309, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public ActiveXDispatchable TextBoxes (Variant param1)
    throws ActiveXException {
    // memid = 0x309

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x309, AX_INVOKE, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxTransitionFormEntry ()
    throws ActiveXException {
    // memid = 0x192

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x192, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxTransitionFormEntry (boolean param1)
    throws ActiveXException {
    // memid = 0x192

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x192, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlSheetType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Range getAxUsedRange ()
    throws ActiveXException {
    // memid = 0x19c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x19c, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public HPageBreaks getAxHPageBreaks ()
    throws ActiveXException {
    // memid = 0x58a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x58a, AX_PROPERTYGET, false, args);
    HPageBreaks result = new HPageBreaks(vResult.getActiveXDispatchableValue());
    return result;
  }

  public VPageBreaks getAxVPageBreaks ()
    throws ActiveXException {
    // memid = 0x58b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x58b, AX_PROPERTYGET, false, args);
    VPageBreaks result = new VPageBreaks(vResult.getActiveXDispatchableValue());
    return result;
  }

  public QueryTables getAxQueryTables ()
    throws ActiveXException {
    // memid = 0x59a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x59a, AX_PROPERTYGET, false, args);
    QueryTables result = new QueryTables(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxDisplayPageBreaks ()
    throws ActiveXException {
    // memid = 0x59b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x59b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDisplayPageBreaks (boolean param1)
    throws ActiveXException {
    // memid = 0x59b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x59b, AX_PROPERTYSET, true, args);
  }

  public Comments getAxComments ()
    throws ActiveXException {
    // memid = 0x23f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x23f, AX_PROPERTYGET, false, args);
    Comments result = new Comments(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Hyperlinks getAxHyperlinks ()
    throws ActiveXException {
    // memid = 0x571

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x571, AX_PROPERTYGET, false, args);
    Hyperlinks result = new Hyperlinks(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void ClearCircles ()
    throws ActiveXException {
    // memid = 0x59c

    Vector args = new Vector(0);
    axInvoke(0x59c, AX_INVOKE, true, args);
  }

  public void CircleInvalid ()
    throws ActiveXException {
    // memid = 0x59d

    Vector args = new Vector(0);
    axInvoke(0x59d, AX_INVOKE, true, args);
  }

  public int getAxDisplayRightToLeft ()
    throws ActiveXException {
    // memid = 0x288

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x288, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDisplayRightToLeft (int param1)
    throws ActiveXException {
    // memid = 0x288

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x288, AX_PROPERTYSET, true, args);
  }

  public AutoFilter getAxAutoFilter ()
    throws ActiveXException {
    // memid = 0x319

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x319, AX_PROPERTYGET, false, args);
    AutoFilter result = new AutoFilter(vResult.getActiveXDispatchableValue());
    return result;
  }

@Override
public String toString() {
    return "<Worksheet, super = " + super.toString() + ">";
}


}

