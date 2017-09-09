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


public class PageSetup extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208b4, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public PageSetup (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #444
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: PageSetup
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 73 functions.
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

  public boolean getAxBlackAndWhite ()
    throws ActiveXException {
    // memid = 0x3f1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f1, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxBlackAndWhite (boolean param1)
    throws ActiveXException {
    // memid = 0x3f1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f1, AX_PROPERTYSET, true, args);
  }

  public double getAxBottomMargin ()
    throws ActiveXException {
    // memid = 0x3ea

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ea, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxBottomMargin (double param1)
    throws ActiveXException {
    // memid = 0x3ea

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3ea, AX_PROPERTYSET, true, args);
  }

  public String getAxCenterFooter ()
    throws ActiveXException {
    // memid = 0x3f2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f2, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCenterFooter (String param1)
    throws ActiveXException {
    // memid = 0x3f2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f2, AX_PROPERTYSET, true, args);
  }

  public String getAxCenterHeader ()
    throws ActiveXException {
    // memid = 0x3f3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f3, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCenterHeader (String param1)
    throws ActiveXException {
    // memid = 0x3f3

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f3, AX_PROPERTYSET, true, args);
  }

  public boolean getAxCenterHorizontally ()
    throws ActiveXException {
    // memid = 0x3ed

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ed, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxCenterHorizontally (boolean param1)
    throws ActiveXException {
    // memid = 0x3ed

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3ed, AX_PROPERTYSET, true, args);
  }

  public boolean getAxCenterVertically ()
    throws ActiveXException {
    // memid = 0x3ee

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ee, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxCenterVertically (boolean param1)
    throws ActiveXException {
    // memid = 0x3ee

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3ee, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlObjectSie
  public int getAxChartSize ()
    throws ActiveXException {
    // memid = 0x3f4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f4, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxChartSize (int param1)
    throws ActiveXException {
    // memid = 0x3f4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f4, AX_PROPERTYSET, true, args);
  }

  public boolean getAxDraft ()
    throws ActiveXException {
    // memid = 0x3fc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3fc, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDraft (boolean param1)
    throws ActiveXException {
    // memid = 0x3fc

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3fc, AX_PROPERTYSET, true, args);
  }

  public int getAxFirstPageNumber ()
    throws ActiveXException {
    // memid = 0x3f0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxFirstPageNumber (int param1)
    throws ActiveXException {
    // memid = 0x3f0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f0, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFitToPagesTall ()
    throws ActiveXException {
    // memid = 0x3f5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f5, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFitToPagesTall (Variant param1)
    throws ActiveXException {
    // memid = 0x3f5

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3f5, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFitToPagesWide ()
    throws ActiveXException {
    // memid = 0x3f6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f6, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFitToPagesWide (Variant param1)
    throws ActiveXException {
    // memid = 0x3f6

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3f6, AX_PROPERTYSET, true, args);
  }

  public double getAxFooterMargin ()
    throws ActiveXException {
    // memid = 0x3f7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f7, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxFooterMargin (double param1)
    throws ActiveXException {
    // memid = 0x3f7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f7, AX_PROPERTYSET, true, args);
  }

  public double getAxHeaderMargin ()
    throws ActiveXException {
    // memid = 0x3f8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f8, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxHeaderMargin (double param1)
    throws ActiveXException {
    // memid = 0x3f8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f8, AX_PROPERTYSET, true, args);
  }

  public String getAxLeftFooter ()
    throws ActiveXException {
    // memid = 0x3f9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3f9, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxLeftFooter (String param1)
    throws ActiveXException {
    // memid = 0x3f9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3f9, AX_PROPERTYSET, true, args);
  }

  public String getAxLeftHeader ()
    throws ActiveXException {
    // memid = 0x3fa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3fa, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxLeftHeader (String param1)
    throws ActiveXException {
    // memid = 0x3fa

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3fa, AX_PROPERTYSET, true, args);
  }

  public double getAxLeftMargin ()
    throws ActiveXException {
    // memid = 0x3e7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e7, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxLeftMargin (double param1)
    throws ActiveXException {
    // memid = 0x3e7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3e7, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlOrder
  public int getAxOrder ()
    throws ActiveXException {
    // memid = 0xc0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxOrder (int param1)
    throws ActiveXException {
    // memid = 0xc0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc0, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlPageOrientation
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

    // Enumeration type = XlPaperSie
  public int getAxPaperSize ()
    throws ActiveXException {
    // memid = 0x3ef

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ef, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPaperSize (int param1)
    throws ActiveXException {
    // memid = 0x3ef

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3ef, AX_PROPERTYSET, true, args);
  }

  public String getAxPrintArea ()
    throws ActiveXException {
    // memid = 0x3fb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3fb, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxPrintArea (String param1)
    throws ActiveXException {
    // memid = 0x3fb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3fb, AX_PROPERTYSET, true, args);
  }

  public boolean getAxPrintGridlines ()
    throws ActiveXException {
    // memid = 0x3ec

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ec, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPrintGridlines (boolean param1)
    throws ActiveXException {
    // memid = 0x3ec

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3ec, AX_PROPERTYSET, true, args);
  }

  public boolean getAxPrintHeadings ()
    throws ActiveXException {
    // memid = 0x3eb

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3eb, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPrintHeadings (boolean param1)
    throws ActiveXException {
    // memid = 0x3eb

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3eb, AX_PROPERTYSET, true, args);
  }

  public boolean getAxPrintNotes ()
    throws ActiveXException {
    // memid = 0x3fd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3fd, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPrintNotes (boolean param1)
    throws ActiveXException {
    // memid = 0x3fd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3fd, AX_PROPERTYSET, true, args);
  }

  public Variant PrintQuality ()
    throws ActiveXException {
    // memid = 0x3fe

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3fe, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant PrintQuality (Variant param1)
    throws ActiveXException {
    // memid = 0x3fe

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x3fe, AX_INVOKE, false, args);
    return vResult;
  }

  public String getAxPrintTitleColumns ()
    throws ActiveXException {
    // memid = 0x3ff

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3ff, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxPrintTitleColumns (String param1)
    throws ActiveXException {
    // memid = 0x3ff

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3ff, AX_PROPERTYSET, true, args);
  }

  public String getAxPrintTitleRows ()
    throws ActiveXException {
    // memid = 0x400

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x400, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxPrintTitleRows (String param1)
    throws ActiveXException {
    // memid = 0x400

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x400, AX_PROPERTYSET, true, args);
  }

  public String getAxRightFooter ()
    throws ActiveXException {
    // memid = 0x401

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x401, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxRightFooter (String param1)
    throws ActiveXException {
    // memid = 0x401

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x401, AX_PROPERTYSET, true, args);
  }

  public String getAxRightHeader ()
    throws ActiveXException {
    // memid = 0x402

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x402, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxRightHeader (String param1)
    throws ActiveXException {
    // memid = 0x402

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x402, AX_PROPERTYSET, true, args);
  }

  public double getAxRightMargin ()
    throws ActiveXException {
    // memid = 0x3e8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e8, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxRightMargin (double param1)
    throws ActiveXException {
    // memid = 0x3e8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3e8, AX_PROPERTYSET, true, args);
  }

  public double getAxTopMargin ()
    throws ActiveXException {
    // memid = 0x3e9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3e9, AX_PROPERTYGET, false, args);
    double result = vResult.getDoubleValue();
    return result;
  }

  public void setAxTopMargin (double param1)
    throws ActiveXException {
    // memid = 0x3e9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3e9, AX_PROPERTYSET, true, args);
  }

  public Variant getAxZoom ()
    throws ActiveXException {
    // memid = 0x297

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x297, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxZoom (Variant param1)
    throws ActiveXException {
    // memid = 0x297

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x297, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlPrintLocation
  public int getAxPrintComments ()
    throws ActiveXException {
    // memid = 0x5f4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5f4, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPrintComments (int param1)
    throws ActiveXException {
    // memid = 0x5f4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5f4, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<PageSetup, super = " + super.toString() + ">";
}


}

