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


public class Style extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20852, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Style (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #358
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Style
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 57 functions.
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

  public boolean getAxAddIndent ()
    throws ActiveXException {
    // memid = 0x427

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x427, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAddIndent (boolean param1)
    throws ActiveXException {
    // memid = 0x427

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x427, AX_PROPERTYSET, true, args);
  }

  public boolean getAxBuiltIn ()
    throws ActiveXException {
    // memid = 0x229

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x229, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public Borders getAxBorders ()
    throws ActiveXException {
    // memid = 0x1b3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1b3, AX_PROPERTYGET, false, args);
    Borders result = new Borders(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public Font getAxFont ()
    throws ActiveXException {
    // memid = 0x92

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x92, AX_PROPERTYGET, false, args);
    Font result = new Font(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxFormulaHidden ()
    throws ActiveXException {
    // memid = 0x106

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x106, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxFormulaHidden (boolean param1)
    throws ActiveXException {
    // memid = 0x106

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x106, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlHAlign
  public int getAxHorizontalAlignment ()
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x88, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHorizontalAlignment (int param1)
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x88, AX_PROPERTYSET, true, args);
  }

  public boolean getAxIncludeAlignment ()
    throws ActiveXException {
    // memid = 0x19d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x19d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIncludeAlignment (boolean param1)
    throws ActiveXException {
    // memid = 0x19d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x19d, AX_PROPERTYSET, true, args);
  }

  public boolean getAxIncludeBorder ()
    throws ActiveXException {
    // memid = 0x19e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x19e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIncludeBorder (boolean param1)
    throws ActiveXException {
    // memid = 0x19e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x19e, AX_PROPERTYSET, true, args);
  }

  public boolean getAxIncludeFont ()
    throws ActiveXException {
    // memid = 0x19f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x19f, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIncludeFont (boolean param1)
    throws ActiveXException {
    // memid = 0x19f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x19f, AX_PROPERTYSET, true, args);
  }

  public boolean getAxIncludeNumber ()
    throws ActiveXException {
    // memid = 0x1a0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1a0, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIncludeNumber (boolean param1)
    throws ActiveXException {
    // memid = 0x1a0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1a0, AX_PROPERTYSET, true, args);
  }

  public boolean getAxIncludePatterns ()
    throws ActiveXException {
    // memid = 0x1a1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1a1, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIncludePatterns (boolean param1)
    throws ActiveXException {
    // memid = 0x1a1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1a1, AX_PROPERTYSET, true, args);
  }

  public boolean getAxIncludeProtection ()
    throws ActiveXException {
    // memid = 0x1a2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1a2, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIncludeProtection (boolean param1)
    throws ActiveXException {
    // memid = 0x1a2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x1a2, AX_PROPERTYSET, true, args);
  }

  public int getAxIndentLevel ()
    throws ActiveXException {
    // memid = 0xc9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc9, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxIndentLevel (int param1)
    throws ActiveXException {
    // memid = 0xc9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc9, AX_PROPERTYSET, true, args);
  }

  public Interior getAxInterior ()
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x81, AX_PROPERTYGET, false, args);
    Interior result = new Interior(vResult.getActiveXDispatchableValue());
    return result;
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

  public Variant getAxMergeCells ()
    throws ActiveXException {
    // memid = 0xd0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xd0, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxMergeCells (Variant param1)
    throws ActiveXException {
    // memid = 0xd0

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xd0, AX_PROPERTYSET, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxNameLocal ()
    throws ActiveXException {
    // memid = 0x3a9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3a9, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxNumberFormat ()
    throws ActiveXException {
    // memid = 0xc1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc1, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxNumberFormat (String param1)
    throws ActiveXException {
    // memid = 0xc1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc1, AX_PROPERTYSET, true, args);
  }

  public String getAxNumberFormatLocal ()
    throws ActiveXException {
    // memid = 0x449

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x449, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxNumberFormatLocal (String param1)
    throws ActiveXException {
    // memid = 0x449

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x449, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlOrientation
  public int getAxOrientation ()
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x86, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxOrientation (int param1)
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x86, AX_PROPERTYSET, true, args);
  }

  public boolean getAxShrinkToFit ()
    throws ActiveXException {
    // memid = 0xd1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xd1, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShrinkToFit (boolean param1)
    throws ActiveXException {
    // memid = 0xd1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xd1, AX_PROPERTYSET, true, args);
  }

  public String getAxValue ()
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

    // Enumeration type = XlVAlign
  public int getAxVerticalAlignment ()
    throws ActiveXException {
    // memid = 0x89

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x89, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxVerticalAlignment (int param1)
    throws ActiveXException {
    // memid = 0x89

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x89, AX_PROPERTYSET, true, args);
  }

  public boolean getAxWrapText ()
    throws ActiveXException {
    // memid = 0x114

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x114, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxWrapText (boolean param1)
    throws ActiveXException {
    // memid = 0x114

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x114, AX_PROPERTYSET, true, args);
  }

  public String getAx_Default ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public int getAxReadingOrder ()
    throws ActiveXException {
    // memid = 0x3cf

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3cf, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxReadingOrder (int param1)
    throws ActiveXException {
    // memid = 0x3cf

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3cf, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<Style, super = " + super.toString() + ">";
}


}

