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


public class Range extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x20846, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Range (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #349
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Range
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 198 functions.
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

  public Variant getAxAddIndent ()
    throws ActiveXException {
    // memid = 0x427

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x427, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxAddIndent (Variant param1)
    throws ActiveXException {
    // memid = 0x427

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x427, AX_PROPERTYSET, true, args);
  }

  public String getAxAddress (Variant param1, Variant param2, int param3)
    throws ActiveXException {
    // memid = 0xec

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0xec, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxAddress (Variant param1, Variant param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0xec

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0xec, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxAddress (Variant param1, Variant param2, int param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0xec

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0xec, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxAddressLocal (Variant param1, Variant param2, int param3)
    throws ActiveXException {
    // memid = 0x1b5

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x1b5, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxAddressLocal (Variant param1, Variant param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0x1b5

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x1b5, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxAddressLocal (Variant param1, Variant param2, int param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x1b5

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x1b5, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void AdvancedFilter (int param1)
    throws ActiveXException {
    // memid = 0x36c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x36c, AX_INVOKE, true, args);
  }

  public void AdvancedFilter (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x36c

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x36c, AX_INVOKE, true, args);
  }

  public void AdvancedFilter (int param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x36c

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x36c, AX_INVOKE, true, args);
  }

  public void AdvancedFilter (int param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x36c

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x36c, AX_INVOKE, true, args);
  }

  public void ApplyNames (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6)
    throws ActiveXException {
    // memid = 0x1b9

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    axInvoke(0x1b9, AX_INVOKE, true, args);
  }

  public void ApplyNames (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6, Variant param7)
    throws ActiveXException {
    // memid = 0x1b9

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(param7);
    axInvoke(0x1b9, AX_INVOKE, true, args);
  }

  public void ApplyOutlineStyles ()
    throws ActiveXException {
    // memid = 0x1c0

    Vector args = new Vector(0);
    axInvoke(0x1c0, AX_INVOKE, true, args);
  }

  public Areas getAxAreas ()
    throws ActiveXException {
    // memid = 0x238

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x238, AX_PROPERTYGET, false, args);
    Areas result = new Areas(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String AutoComplete (String param1)
    throws ActiveXException {
    // memid = 0x4a1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x4a1, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void AutoFill (Range param1, int param2)
    throws ActiveXException {
    // memid = 0x1c1

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x1c1, AX_INVOKE, true, args);
  }

  public void AutoFilter (Variant param1, Variant param2, int param3)
    throws ActiveXException {
    // memid = 0x319

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    axInvoke(0x319, AX_INVOKE, true, args);
  }

  public void AutoFilter (Variant param1, Variant param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0x319

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0x319, AX_INVOKE, true, args);
  }

  public void AutoFilter (Variant param1, Variant param2, int param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x319

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x319, AX_INVOKE, true, args);
  }

  public void AutoFit ()
    throws ActiveXException {
    // memid = 0xed

    Vector args = new Vector(0);
    axInvoke(0xed, AX_INVOKE, true, args);
  }

  public void AutoFormat (int param1)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public void AutoFormat (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public void AutoFormat (int param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public void AutoFormat (int param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public void AutoFormat (int param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public void AutoFormat (int param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public void AutoFormat (int param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public void AutoOutline ()
    throws ActiveXException {
    // memid = 0x40c

    Vector args = new Vector(0);
    axInvoke(0x40c, AX_INVOKE, true, args);
  }

  public void BorderAround (Variant param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0x42b

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x42b, AX_INVOKE, true, args);
  }

  public void BorderAround (Variant param1, int param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0x42b

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0x42b, AX_INVOKE, true, args);
  }

  public Borders getAxBorders ()
    throws ActiveXException {
    // memid = 0x1b3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1b3, AX_PROPERTYGET, false, args);
    Borders result = new Borders(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Calculate ()
    throws ActiveXException {
    // memid = 0x117

    Vector args = new Vector(0);
    axInvoke(0x117, AX_INVOKE, true, args);
  }

  public Range getAxCells ()
    throws ActiveXException {
    // memid = 0xee

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xee, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Characters getAxCharacters ()
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x25b, AX_PROPERTYGET, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Characters getAxCharacters (Variant param1)
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x25b, AX_PROPERTYGET, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Characters getAxCharacters (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x25b

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x25b, AX_PROPERTYGET, false, args);
    Characters result = new Characters(vResult.getActiveXDispatchableValue());
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

  public void Clear ()
    throws ActiveXException {
    // memid = 0x6f

    Vector args = new Vector(0);
    axInvoke(0x6f, AX_INVOKE, true, args);
  }

  public void ClearContents ()
    throws ActiveXException {
    // memid = 0x71

    Vector args = new Vector(0);
    axInvoke(0x71, AX_INVOKE, true, args);
  }

  public void ClearFormats ()
    throws ActiveXException {
    // memid = 0x70

    Vector args = new Vector(0);
    axInvoke(0x70, AX_INVOKE, true, args);
  }

  public void ClearNotes ()
    throws ActiveXException {
    // memid = 0xef

    Vector args = new Vector(0);
    axInvoke(0xef, AX_INVOKE, true, args);
  }

  public void ClearOutline ()
    throws ActiveXException {
    // memid = 0x40d

    Vector args = new Vector(0);
    axInvoke(0x40d, AX_INVOKE, true, args);
  }

  public int getAxColumn ()
    throws ActiveXException {
    // memid = 0xf0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Range ColumnDifferences (Variant param1)
    throws ActiveXException {
    // memid = 0x1fe

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x1fe, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxColumns ()
    throws ActiveXException {
    // memid = 0xf1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf1, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxColumnWidth ()
    throws ActiveXException {
    // memid = 0xf2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf2, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxColumnWidth (Variant param1)
    throws ActiveXException {
    // memid = 0xf2

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xf2, AX_PROPERTYSET, true, args);
  }

  public void Consolidate ()
    throws ActiveXException {
    // memid = 0x1e2

    Vector args = new Vector(0);
    axInvoke(0x1e2, AX_INVOKE, true, args);
  }

  public void Consolidate (Variant param1)
    throws ActiveXException {
    // memid = 0x1e2

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x1e2, AX_INVOKE, true, args);
  }

  public void Consolidate (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x1e2

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x1e2, AX_INVOKE, true, args);
  }

  public void Consolidate (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x1e2

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x1e2, AX_INVOKE, true, args);
  }

  public void Consolidate (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x1e2

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x1e2, AX_INVOKE, true, args);
  }

  public void Consolidate (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x1e2

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x1e2, AX_INVOKE, true, args);
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

  public int CopyFromRecordset (Object param1)
    throws ActiveXException {
    // memid = 0x480

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x480, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int CopyFromRecordset (Object param1, Variant param2)
    throws ActiveXException {
    // memid = 0x480

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x480, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int CopyFromRecordset (Object param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x480

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x480, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void CopyPicture (int param1, int param2)
    throws ActiveXException {
    // memid = 0xd5

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0xd5, AX_INVOKE, true, args);
  }

  public int getAxCount ()
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x76, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void CreateNames ()
    throws ActiveXException {
    // memid = 0x1c9

    Vector args = new Vector(0);
    axInvoke(0x1c9, AX_INVOKE, true, args);
  }

  public void CreateNames (Variant param1)
    throws ActiveXException {
    // memid = 0x1c9

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x1c9, AX_INVOKE, true, args);
  }

  public void CreateNames (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x1c9

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x1c9, AX_INVOKE, true, args);
  }

  public void CreateNames (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x1c9

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x1c9, AX_INVOKE, true, args);
  }

  public void CreateNames (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x1c9

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x1c9, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2, Variant param3)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public void CreatePublisher (Variant param1, int param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x1ca

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x1ca, AX_INVOKE, true, args);
  }

  public Range getAxCurrentArray ()
    throws ActiveXException {
    // memid = 0x1f5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f5, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxCurrentRegion ()
    throws ActiveXException {
    // memid = 0xf3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf3, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Cut ()
    throws ActiveXException {
    // memid = 0x235

    Vector args = new Vector(0);
    axInvoke(0x235, AX_INVOKE, true, args);
  }

  public void Cut (Variant param1)
    throws ActiveXException {
    // memid = 0x235

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x235, AX_INVOKE, true, args);
  }

  public void DataSeries (Variant param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0x1d0

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x1d0, AX_INVOKE, true, args);
  }

  public void DataSeries (Variant param1, int param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0x1d0

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0x1d0, AX_INVOKE, true, args);
  }

  public void DataSeries (Variant param1, int param2, int param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x1d0

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x1d0, AX_INVOKE, true, args);
  }

  public void DataSeries (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x1d0

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x1d0, AX_INVOKE, true, args);
  }

  public Variant getAx_Default ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAx_Default (Variant param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAx_Default (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAx_Default (Variant param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x0, AX_PROPERTYSET, true, args);
  }

  public void setAx_Default (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x0, AX_PROPERTYSET, true, args);
  }

  public void setAx_Default (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x0, AX_PROPERTYSET, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public void Delete (Variant param1)
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public Range getAxDependents ()
    throws ActiveXException {
    // memid = 0x21f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x21f, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant DialogBox ()
    throws ActiveXException {
    // memid = 0xf5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf5, AX_INVOKE, false, args);
    return vResult;
  }

  public Range getAxDirectDependents ()
    throws ActiveXException {
    // memid = 0x221

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x221, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxDirectPrecedents ()
    throws ActiveXException {
    // memid = 0x222

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x222, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant EditionOptions (int param1, int param2, Variant param3, Variant param4, int param5, int param6)
    throws ActiveXException {
    // memid = 0x46b

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(new Variant(param6));
    Variant vResult = axInvoke(0x46b, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant EditionOptions (int param1, int param2, Variant param3, Variant param4, int param5, int param6, Variant param7)
    throws ActiveXException {
    // memid = 0x46b

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(new Variant(param6));
    args.addElement(param7);
    Variant vResult = axInvoke(0x46b, AX_INVOKE, false, args);
    return vResult;
  }

  public Range getAxEnd (int param1)
    throws ActiveXException {
    // memid = 0x1f4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x1f4, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxEntireColumn ()
    throws ActiveXException {
    // memid = 0xf6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf6, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxEntireRow ()
    throws ActiveXException {
    // memid = 0xf7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf7, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void FillDown ()
    throws ActiveXException {
    // memid = 0xf8

    Vector args = new Vector(0);
    axInvoke(0xf8, AX_INVOKE, true, args);
  }

  public void FillLeft ()
    throws ActiveXException {
    // memid = 0xf9

    Vector args = new Vector(0);
    axInvoke(0xf9, AX_INVOKE, true, args);
  }

  public void FillRight ()
    throws ActiveXException {
    // memid = 0xfa

    Vector args = new Vector(0);
    axInvoke(0xfa, AX_INVOKE, true, args);
  }

  public void FillUp ()
    throws ActiveXException {
    // memid = 0xfb

    Vector args = new Vector(0);
    axInvoke(0xfb, AX_INVOKE, true, args);
  }

  public Range Find (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6)
    throws ActiveXException {
    // memid = 0x18e

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    Variant vResult = axInvoke(0x18e, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Find (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6, Variant param7)
    throws ActiveXException {
    // memid = 0x18e

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(param7);
    Variant vResult = axInvoke(0x18e, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Find (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x18e

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x18e, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Find (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x18e

    Vector args = new Vector(9);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    Variant vResult = axInvoke(0x18e, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Find (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x18e

    Vector args = new Vector(10);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    Variant vResult = axInvoke(0x18e, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Find (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x18e

    Vector args = new Vector(11);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    Variant vResult = axInvoke(0x18e, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range Find (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, int param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x18e

    Vector args = new Vector(12);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(param12);
    Variant vResult = axInvoke(0x18e, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range FindNext ()
    throws ActiveXException {
    // memid = 0x18f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x18f, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range FindNext (Variant param1)
    throws ActiveXException {
    // memid = 0x18f

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x18f, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range FindPrevious ()
    throws ActiveXException {
    // memid = 0x190

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x190, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range FindPrevious (Variant param1)
    throws ActiveXException {
    // memid = 0x190

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x190, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Font getAxFont ()
    throws ActiveXException {
    // memid = 0x92

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x92, AX_PROPERTYGET, false, args);
    Font result = new Font(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxFormula ()
    throws ActiveXException {
    // memid = 0x105

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x105, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFormula (Variant param1)
    throws ActiveXException {
    // memid = 0x105

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x105, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFormulaArray ()
    throws ActiveXException {
    // memid = 0x24a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x24a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFormulaArray (Variant param1)
    throws ActiveXException {
    // memid = 0x24a

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x24a, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = XlFormulaLabel
  public int getAxFormulaLabel ()
    throws ActiveXException {
    // memid = 0x564

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x564, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxFormulaLabel (int param1)
    throws ActiveXException {
    // memid = 0x564

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x564, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFormulaHidden ()
    throws ActiveXException {
    // memid = 0x106

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x106, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFormulaHidden (Variant param1)
    throws ActiveXException {
    // memid = 0x106

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x106, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFormulaLocal ()
    throws ActiveXException {
    // memid = 0x107

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x107, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFormulaLocal (Variant param1)
    throws ActiveXException {
    // memid = 0x107

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x107, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFormulaR1C1 ()
    throws ActiveXException {
    // memid = 0x108

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x108, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFormulaR1C1 (Variant param1)
    throws ActiveXException {
    // memid = 0x108

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x108, AX_PROPERTYSET, true, args);
  }

  public Variant getAxFormulaR1C1Local ()
    throws ActiveXException {
    // memid = 0x109

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x109, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxFormulaR1C1Local (Variant param1)
    throws ActiveXException {
    // memid = 0x109

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x109, AX_PROPERTYSET, true, args);
  }

  public void FunctionWizard ()
    throws ActiveXException {
    // memid = 0x23b

    Vector args = new Vector(0);
    axInvoke(0x23b, AX_INVOKE, true, args);
  }

  public boolean GoalSeek (Variant param1, Range param2)
    throws ActiveXException {
    // memid = 0x1d8

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x1d8, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public Variant Group ()
    throws ActiveXException {
    // memid = 0x2e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2e, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Group (Variant param1)
    throws ActiveXException {
    // memid = 0x2e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x2e, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Group (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x2e

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x2e, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Group (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x2e

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x2e, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Group (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x2e

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x2e, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant getAxHasArray ()
    throws ActiveXException {
    // memid = 0x10a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxHasFormula ()
    throws ActiveXException {
    // memid = 0x10b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10b, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxHeight ()
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7b, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxHidden ()
    throws ActiveXException {
    // memid = 0x10c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10c, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxHidden (Variant param1)
    throws ActiveXException {
    // memid = 0x10c

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x10c, AX_PROPERTYSET, true, args);
  }

  public Variant getAxHorizontalAlignment ()
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x88, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxHorizontalAlignment (Variant param1)
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x88, AX_PROPERTYSET, true, args);
  }

  public Variant getAxIndentLevel ()
    throws ActiveXException {
    // memid = 0xc9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc9, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxIndentLevel (Variant param1)
    throws ActiveXException {
    // memid = 0xc9

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xc9, AX_PROPERTYSET, true, args);
  }

  public void InsertIndent (int param1)
    throws ActiveXException {
    // memid = 0x565

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x565, AX_INVOKE, true, args);
  }

  public void Insert ()
    throws ActiveXException {
    // memid = 0xfc

    Vector args = new Vector(0);
    axInvoke(0xfc, AX_INVOKE, true, args);
  }

  public void Insert (Variant param1)
    throws ActiveXException {
    // memid = 0xfc

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xfc, AX_INVOKE, true, args);
  }

  public Interior getAxInterior ()
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x81, AX_PROPERTYGET, false, args);
    Interior result = new Interior(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxItem (Variant param1)
    throws ActiveXException {
    // memid = 0xaa

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xaa, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxItem (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xaa

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0xaa, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxItem (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xaa

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0xaa, AX_PROPERTYSET, true, args);
  }

  public void setAxItem (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0xaa

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0xaa, AX_PROPERTYSET, true, args);
  }

  public void Justify ()
    throws ActiveXException {
    // memid = 0x1ef

    Vector args = new Vector(0);
    axInvoke(0x1ef, AX_INVOKE, true, args);
  }

  public Variant getAxLeft ()
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7f, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public int getAxListHeaderRows ()
    throws ActiveXException {
    // memid = 0x4a3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4a3, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void ListNames ()
    throws ActiveXException {
    // memid = 0xfd

    Vector args = new Vector(0);
    axInvoke(0xfd, AX_INVOKE, true, args);
  }

    // Enumeration type = XlLocationInTable
  public int getAxLocationInTable ()
    throws ActiveXException {
    // memid = 0x2b3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2b3, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Variant getAxLocked ()
    throws ActiveXException {
    // memid = 0x10d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10d, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxLocked (Variant param1)
    throws ActiveXException {
    // memid = 0x10d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x10d, AX_PROPERTYSET, true, args);
  }

  public void Merge ()
    throws ActiveXException {
    // memid = 0x234

    Vector args = new Vector(0);
    axInvoke(0x234, AX_INVOKE, true, args);
  }

  public void Merge (Variant param1)
    throws ActiveXException {
    // memid = 0x234

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x234, AX_INVOKE, true, args);
  }

  public void UnMerge ()
    throws ActiveXException {
    // memid = 0x568

    Vector args = new Vector(0);
    axInvoke(0x568, AX_INVOKE, true, args);
  }

  public Range getAxMergeArea ()
    throws ActiveXException {
    // memid = 0x569

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x569, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
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

  public Variant getAxName ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxName (Variant param1)
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6e, AX_PROPERTYSET, true, args);
  }

  public void NavigateArrow ()
    throws ActiveXException {
    // memid = 0x408

    Vector args = new Vector(0);
    axInvoke(0x408, AX_INVOKE, true, args);
  }

  public void NavigateArrow (Variant param1)
    throws ActiveXException {
    // memid = 0x408

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x408, AX_INVOKE, true, args);
  }

  public void NavigateArrow (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x408

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x408, AX_INVOKE, true, args);
  }

  public void NavigateArrow (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x408

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x408, AX_INVOKE, true, args);
  }

  public Object getAx_NewEnum ()
    throws ActiveXException {
    // memid = 0xfffffffc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xfffffffc, AX_PROPERTYGET, false, args);
    Object result = vResult.getGenericValue();
    return result;
  }

  public Range getAxNext ()
    throws ActiveXException {
    // memid = 0x1f6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f6, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String NoteText ()
    throws ActiveXException {
    // memid = 0x467

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x467, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String NoteText (Variant param1)
    throws ActiveXException {
    // memid = 0x467

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x467, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String NoteText (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x467

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x467, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String NoteText (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x467

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x467, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Variant getAxNumberFormat ()
    throws ActiveXException {
    // memid = 0xc1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc1, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxNumberFormat (Variant param1)
    throws ActiveXException {
    // memid = 0xc1

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xc1, AX_PROPERTYSET, true, args);
  }

  public Variant getAxNumberFormatLocal ()
    throws ActiveXException {
    // memid = 0x449

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x449, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxNumberFormatLocal (Variant param1)
    throws ActiveXException {
    // memid = 0x449

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x449, AX_PROPERTYSET, true, args);
  }

  public Range getAxOffset ()
    throws ActiveXException {
    // memid = 0xfe

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xfe, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxOffset (Variant param1)
    throws ActiveXException {
    // memid = 0xfe

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xfe, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxOffset (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xfe

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0xfe, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxOrientation ()
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x86, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxOrientation (Variant param1)
    throws ActiveXException {
    // memid = 0x86

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x86, AX_PROPERTYSET, true, args);
  }

  public Variant getAxOutlineLevel ()
    throws ActiveXException {
    // memid = 0x10f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10f, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxOutlineLevel (Variant param1)
    throws ActiveXException {
    // memid = 0x10f

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x10f, AX_PROPERTYSET, true, args);
  }

  public int getAxPageBreak ()
    throws ActiveXException {
    // memid = 0xff

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xff, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPageBreak (int param1)
    throws ActiveXException {
    // memid = 0xff

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xff, AX_PROPERTYSET, true, args);
  }

  public void Parse ()
    throws ActiveXException {
    // memid = 0x1dd

    Vector args = new Vector(0);
    axInvoke(0x1dd, AX_INVOKE, true, args);
  }

  public void Parse (Variant param1)
    throws ActiveXException {
    // memid = 0x1dd

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x1dd, AX_INVOKE, true, args);
  }

  public void Parse (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x1dd

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x1dd, AX_INVOKE, true, args);
  }

  public void PasteSpecial (int param1, int param2)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public void PasteSpecial (int param1, int param2, Variant param3)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public void PasteSpecial (int param1, int param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x403

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x403, AX_INVOKE, true, args);
  }

  public PivotField getAxPivotField ()
    throws ActiveXException {
    // memid = 0x2db

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2db, AX_PROPERTYGET, false, args);
    PivotField result = new PivotField(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotItem getAxPivotItem ()
    throws ActiveXException {
    // memid = 0x2e4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2e4, AX_PROPERTYGET, false, args);
    PivotItem result = new PivotItem(vResult.getActiveXDispatchableValue());
    return result;
  }

  public PivotTable getAxPivotTable ()
    throws ActiveXException {
    // memid = 0x2cc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2cc, AX_PROPERTYGET, false, args);
    PivotTable result = new PivotTable(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxPrecedents ()
    throws ActiveXException {
    // memid = 0x220

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x220, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxPrefixCharacter ()
    throws ActiveXException {
    // memid = 0x1f8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f8, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Range getAxPrevious ()
    throws ActiveXException {
    // memid = 0x1f7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1f7, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
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

  public Variant getAxQueryTable ()
    throws ActiveXException {
    // memid = 0x56a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x56a, AX_PROPERTYGET, false, args);
    return vResult;
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

  public void RemoveSubtotal ()
    throws ActiveXException {
    // memid = 0x373

    Vector args = new Vector(0);
    axInvoke(0x373, AX_INVOKE, true, args);
  }

  public boolean Replace (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xe2

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Replace (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0xe2

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Replace (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0xe2

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Replace (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0xe2

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Replace (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0xe2

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Replace (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0xe2

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Replace (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0xe2

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Replace (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0xe2

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
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean Replace (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0xe2

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
    Variant vResult = axInvoke(0xe2, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public Range getAxResize ()
    throws ActiveXException {
    // memid = 0x100

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x100, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxResize (Variant param1)
    throws ActiveXException {
    // memid = 0x100

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x100, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxResize (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x100

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x100, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxRow ()
    throws ActiveXException {
    // memid = 0x101

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x101, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Range RowDifferences (Variant param1)
    throws ActiveXException {
    // memid = 0x1ff

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x1ff, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxRowHeight ()
    throws ActiveXException {
    // memid = 0x110

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x110, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxRowHeight (Variant param1)
    throws ActiveXException {
    // memid = 0x110

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x110, AX_PROPERTYSET, true, args);
  }

  public Range getAxRows ()
    throws ActiveXException {
    // memid = 0x102

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x102, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant Run ()
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
    throws ActiveXException {
    // memid = 0x103

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
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(17);
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
    args.addElement(param17);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(18);
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
    args.addElement(param17);
    args.addElement(param18);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(19);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(20);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(21);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(22);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(23);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(24);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(25);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(26);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(27);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(28);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(29);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant Run (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16, Variant param17, Variant param18, Variant param19, Variant param20, Variant param21, Variant param22, Variant param23, Variant param24, Variant param25, Variant param26, Variant param27, Variant param28, Variant param29, Variant param30)
    throws ActiveXException {
    // memid = 0x103

    Vector args = new Vector(30);
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
    args.addElement(param17);
    args.addElement(param18);
    args.addElement(param19);
    args.addElement(param20);
    args.addElement(param21);
    args.addElement(param22);
    args.addElement(param23);
    args.addElement(param24);
    args.addElement(param25);
    args.addElement(param26);
    args.addElement(param27);
    args.addElement(param28);
    args.addElement(param29);
    args.addElement(param30);
    Variant vResult = axInvoke(0x103, AX_INVOKE, false, args);
    return vResult;
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(0);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public void Show ()
    throws ActiveXException {
    // memid = 0x1f0

    Vector args = new Vector(0);
    axInvoke(0x1f0, AX_INVOKE, true, args);
  }

  public void ShowDependents ()
    throws ActiveXException {
    // memid = 0x36d

    Vector args = new Vector(0);
    axInvoke(0x36d, AX_INVOKE, true, args);
  }

  public void ShowDependents (Variant param1)
    throws ActiveXException {
    // memid = 0x36d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x36d, AX_INVOKE, true, args);
  }

  public Variant getAxShowDetail ()
    throws ActiveXException {
    // memid = 0x249

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x249, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxShowDetail (Variant param1)
    throws ActiveXException {
    // memid = 0x249

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x249, AX_PROPERTYSET, true, args);
  }

  public void ShowErrors ()
    throws ActiveXException {
    // memid = 0x36e

    Vector args = new Vector(0);
    axInvoke(0x36e, AX_INVOKE, true, args);
  }

  public void ShowPrecedents ()
    throws ActiveXException {
    // memid = 0x36f

    Vector args = new Vector(0);
    axInvoke(0x36f, AX_INVOKE, true, args);
  }

  public void ShowPrecedents (Variant param1)
    throws ActiveXException {
    // memid = 0x36f

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x36f, AX_INVOKE, true, args);
  }

  public Variant getAxShrinkToFit ()
    throws ActiveXException {
    // memid = 0xd1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xd1, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxShrinkToFit (Variant param1)
    throws ActiveXException {
    // memid = 0xd1

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xd1, AX_PROPERTYSET, true, args);
  }

  public void Sort (Variant param1, int param2, Variant param3, Variant param4, int param5, Variant param6, int param7, int param8, Variant param9, Variant param10, int param11, int param12)
    throws ActiveXException {
    // memid = 0x370

    Vector args = new Vector(12);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(new Variant(param7));
    args.addElement(new Variant(param8));
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(new Variant(param11));
    args.addElement(new Variant(param12));
    axInvoke(0x370, AX_INVOKE, true, args);
  }

  public void Sort (Variant param1, int param2, Variant param3, Variant param4, int param5, Variant param6, int param7, int param8, Variant param9, Variant param10, int param11, int param12, Variant param13)
    throws ActiveXException {
    // memid = 0x370

    Vector args = new Vector(13);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(new Variant(param7));
    args.addElement(new Variant(param8));
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(new Variant(param11));
    args.addElement(new Variant(param12));
    args.addElement(param13);
    axInvoke(0x370, AX_INVOKE, true, args);
  }

  public void Sort (Variant param1, int param2, Variant param3, Variant param4, int param5, Variant param6, int param7, int param8, Variant param9, Variant param10, int param11, int param12, Variant param13, Variant param14)
    throws ActiveXException {
    // memid = 0x370

    Vector args = new Vector(14);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(new Variant(param7));
    args.addElement(new Variant(param8));
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(new Variant(param11));
    args.addElement(new Variant(param12));
    args.addElement(param13);
    args.addElement(param14);
    axInvoke(0x370, AX_INVOKE, true, args);
  }

  public void Sort (Variant param1, int param2, Variant param3, Variant param4, int param5, Variant param6, int param7, int param8, Variant param9, Variant param10, int param11, int param12, Variant param13, Variant param14, Variant param15)
    throws ActiveXException {
    // memid = 0x370

    Vector args = new Vector(15);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(new Variant(param5));
    args.addElement(param6);
    args.addElement(new Variant(param7));
    args.addElement(new Variant(param8));
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(new Variant(param11));
    args.addElement(new Variant(param12));
    args.addElement(param13);
    args.addElement(param14);
    args.addElement(param15);
    axInvoke(0x370, AX_INVOKE, true, args);
  }

  public void SortSpecial (int param1, Variant param2, int param3, Variant param4, Variant param5, int param6, Variant param7, int param8, int param9, Variant param10, Variant param11, int param12)
    throws ActiveXException {
    // memid = 0x371

    Vector args = new Vector(12);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    args.addElement(param7);
    args.addElement(new Variant(param8));
    args.addElement(new Variant(param9));
    args.addElement(param10);
    args.addElement(param11);
    args.addElement(new Variant(param12));
    axInvoke(0x371, AX_INVOKE, true, args);
  }

  public SoundNote getAxSoundNote ()
    throws ActiveXException {
    // memid = 0x394

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x394, AX_PROPERTYGET, false, args);
    SoundNote result = new SoundNote(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range SpecialCells (int param1)
    throws ActiveXException {
    // memid = 0x19a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x19a, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range SpecialCells (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x19a

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0x19a, AX_INVOKE, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxStyle ()
    throws ActiveXException {
    // memid = 0x104

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x104, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxStyle (Variant param1)
    throws ActiveXException {
    // memid = 0x104

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x104, AX_PROPERTYSET, true, args);
  }

  public void SubscribeTo (String param1, int param2)
    throws ActiveXException {
    // memid = 0x1e1

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x1e1, AX_INVOKE, true, args);
  }

  public void Subtotal (int param1, int param2, Variant param3, Variant param4, Variant param5, int param6)
    throws ActiveXException {
    // memid = 0x372

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(new Variant(param6));
    axInvoke(0x372, AX_INVOKE, true, args);
  }

  public Variant getAxSummary ()
    throws ActiveXException {
    // memid = 0x111

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x111, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void Table ()
    throws ActiveXException {
    // memid = 0x1f1

    Vector args = new Vector(0);
    axInvoke(0x1f1, AX_INVOKE, true, args);
  }

  public void Table (Variant param1)
    throws ActiveXException {
    // memid = 0x1f1

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x1f1, AX_INVOKE, true, args);
  }

  public void Table (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x1f1

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x1f1, AX_INVOKE, true, args);
  }

  public Variant getAxText ()
    throws ActiveXException {
    // memid = 0x8a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x8a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void TextToColumns (Variant param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public void TextToColumns (Variant param1, int param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public void TextToColumns (Variant param1, int param2, int param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public void TextToColumns (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public void TextToColumns (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public void TextToColumns (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public void TextToColumns (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(9);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public void TextToColumns (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(10);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public void TextToColumns (Variant param1, int param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x410

    Vector args = new Vector(11);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    axInvoke(0x410, AX_INVOKE, true, args);
  }

  public Variant getAxTop ()
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7e, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void Ungroup ()
    throws ActiveXException {
    // memid = 0xf4

    Vector args = new Vector(0);
    axInvoke(0xf4, AX_INVOKE, true, args);
  }

  public Variant getAxUseStandardHeight ()
    throws ActiveXException {
    // memid = 0x112

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x112, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxUseStandardHeight (Variant param1)
    throws ActiveXException {
    // memid = 0x112

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x112, AX_PROPERTYSET, true, args);
  }

  public Variant getAxUseStandardWidth ()
    throws ActiveXException {
    // memid = 0x113

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x113, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxUseStandardWidth (Variant param1)
    throws ActiveXException {
    // memid = 0x113

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x113, AX_PROPERTYSET, true, args);
  }

  public Validation getAxValidation ()
    throws ActiveXException {
    // memid = 0x56b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x56b, AX_PROPERTYGET, false, args);
    Validation result = new Validation(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxValue ()
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxValue (Variant param1)
    throws ActiveXException {
    // memid = 0x6

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6, AX_PROPERTYSET, true, args);
  }

  public Variant getAxValue2 ()
    throws ActiveXException {
    // memid = 0x56c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x56c, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxValue2 (Variant param1)
    throws ActiveXException {
    // memid = 0x56c

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x56c, AX_PROPERTYSET, true, args);
  }

  public Variant getAxVerticalAlignment ()
    throws ActiveXException {
    // memid = 0x89

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x89, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxVerticalAlignment (Variant param1)
    throws ActiveXException {
    // memid = 0x89

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x89, AX_PROPERTYSET, true, args);
  }

  public Variant getAxWidth ()
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7a, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public ExcelSheet getAxWorksheet ()
    throws ActiveXException {
    // memid = 0x15c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x15c, AX_PROPERTYGET, false, args);
    ExcelSheet result = new ExcelSheet(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxWrapText ()
    throws ActiveXException {
    // memid = 0x114

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x114, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxWrapText (Variant param1)
    throws ActiveXException {
    // memid = 0x114

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x114, AX_PROPERTYSET, true, args);
  }

  public Comment AddComment ()
    throws ActiveXException {
    // memid = 0x56d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x56d, AX_INVOKE, false, args);
    Comment result = new Comment(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Comment AddComment (Variant param1)
    throws ActiveXException {
    // memid = 0x56d

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x56d, AX_INVOKE, false, args);
    Comment result = new Comment(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Comment getAxComment ()
    throws ActiveXException {
    // memid = 0x38e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x38e, AX_PROPERTYGET, false, args);
    Comment result = new Comment(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void ClearComments ()
    throws ActiveXException {
    // memid = 0x56e

    Vector args = new Vector(0);
    axInvoke(0x56e, AX_INVOKE, true, args);
  }

  public Phonetic getAxPhonetic ()
    throws ActiveXException {
    // memid = 0x56f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x56f, AX_PROPERTYGET, false, args);
    Phonetic result = new Phonetic(vResult.getActiveXDispatchableValue());
    return result;
  }

  public FormatConditions getAxFormatConditions ()
    throws ActiveXException {
    // memid = 0x570

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x570, AX_PROPERTYGET, false, args);
    FormatConditions result = new FormatConditions(vResult.getActiveXDispatchableValue());
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

  public Hyperlinks getAxHyperlinks ()
    throws ActiveXException {
    // memid = 0x571

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x571, AX_PROPERTYGET, false, args);
    Hyperlinks result = new Hyperlinks(vResult.getActiveXDispatchableValue());
    return result;
  }

@Override
public String toString() {
    return "<Range, super = " + super.toString() + ">";
}


}

