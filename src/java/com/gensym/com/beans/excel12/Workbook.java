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


public class Workbook extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x208da, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Workbook (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #193
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _Workbook
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 154 functions.
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

  public boolean getAxAcceptLabelsInFormulas ()
    throws ActiveXException {
    // memid = 0x5a1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a1, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAcceptLabelsInFormulas (boolean param1)
    throws ActiveXException {
    // memid = 0x5a1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5a1, AX_PROPERTYSET, true, args);
  }

  public void Activate ()
    throws ActiveXException {
    // memid = 0x130

    Vector args = new Vector(0);
    axInvoke(0x130, AX_INVOKE, true, args);
  }

  public ExcelChart getAxActiveChart ()
    throws ActiveXException {
    // memid = 0xb7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xb7, AX_PROPERTYGET, false, args);
    ExcelChart result = new ExcelChart(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ActiveXDispatchable getAxActiveSheet ()
    throws ActiveXException {
    // memid = 0x133

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x133, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public String getAxAuthor ()
    throws ActiveXException {
    // memid = 0x23e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x23e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxAuthor (String param1)
    throws ActiveXException {
    // memid = 0x23e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x23e, AX_PROPERTYSET, true, args);
  }

  public int getAxAutoUpdateFrequency ()
    throws ActiveXException {
    // memid = 0x5a2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a2, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxAutoUpdateFrequency (int param1)
    throws ActiveXException {
    // memid = 0x5a2

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5a2, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAutoUpdateSaveChanges ()
    throws ActiveXException {
    // memid = 0x5a3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a3, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAutoUpdateSaveChanges (boolean param1)
    throws ActiveXException {
    // memid = 0x5a3

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5a3, AX_PROPERTYSET, true, args);
  }

  public int getAxChangeHistoryDuration ()
    throws ActiveXException {
    // memid = 0x5a4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a4, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxChangeHistoryDuration (int param1)
    throws ActiveXException {
    // memid = 0x5a4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5a4, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxBuiltinDocumentProperties ()
    throws ActiveXException {
    // memid = 0x498

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x498, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void ChangeFileAccess (int param1)
    throws ActiveXException {
    // memid = 0x3dd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3dd, AX_INVOKE, true, args);
  }

  public void ChangeFileAccess (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x3dd

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x3dd, AX_INVOKE, true, args);
  }

  public void ChangeFileAccess (int param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x3dd

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x3dd, AX_INVOKE, true, args);
  }

  public void ChangeLink (String param1, String param2, int param3)
    throws ActiveXException {
    // memid = 0x322

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x322, AX_INVOKE, true, args);
  }

  public Sheets getAxCharts ()
    throws ActiveXException {
    // memid = 0x79

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x79, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Close ()
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(0);
    axInvoke(0x115, AX_INVOKE, true, args);
  }

  public void Close (Variant param1)
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x115, AX_INVOKE, true, args);
  }

  public void Close (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x115, AX_INVOKE, true, args);
  }

  public void Close (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x115

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x115, AX_INVOKE, true, args);
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

  public Variant getAxColors ()
    throws ActiveXException {
    // memid = 0x11e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x11e, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxColors (Variant param1)
    throws ActiveXException {
    // memid = 0x11e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x11e, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void setAxColors (Variant param1)
    throws ActiveXException {
    // memid = 0x11e

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x11e, AX_PROPERTYSET, true, args);
  }

  public void setAxColors (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x11e

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x11e, AX_PROPERTYSET, true, args);
  }

  public com.gensym.com.beans.office20.CommandBars getAxCommandBars ()
    throws ActiveXException {
    // memid = 0x59f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x59f, AX_PROPERTYGET, false, args);
    com.gensym.com.beans.office20.CommandBars result = new com.gensym.com.beans.office20.CommandBars(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxComments ()
    throws ActiveXException {
    // memid = 0x23f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x23f, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxComments (String param1)
    throws ActiveXException {
    // memid = 0x23f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x23f, AX_PROPERTYSET, true, args);
  }

  public int getAxConflictResolution ()
    throws ActiveXException {
    // memid = 0x497

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x497, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxConflictResolution (int param1)
    throws ActiveXException {
    // memid = 0x497

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x497, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxContainer ()
    throws ActiveXException {
    // memid = 0x4a6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4a6, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxCreateBackup ()
    throws ActiveXException {
    // memid = 0x11f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x11f, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public ActiveXDispatchable getAxCustomDocumentProperties ()
    throws ActiveXException {
    // memid = 0x499

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x499, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public boolean getAxDate1904 ()
    throws ActiveXException {
    // memid = 0x193

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x193, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxDate1904 (boolean param1)
    throws ActiveXException {
    // memid = 0x193

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x193, AX_PROPERTYSET, true, args);
  }

  public void DeleteNumberFormat (String param1)
    throws ActiveXException {
    // memid = 0x18d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x18d, AX_INVOKE, true, args);
  }

  public Sheets getAxDialogSheets ()
    throws ActiveXException {
    // memid = 0x2fc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2fc, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlDisplayShapes
  public int getAxDisplayDrawingObjects ()
    throws ActiveXException {
    // memid = 0x194

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x194, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxDisplayDrawingObjects (int param1)
    throws ActiveXException {
    // memid = 0x194

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x194, AX_PROPERTYSET, true, args);
  }

  public boolean ExclusiveAccess ()
    throws ActiveXException {
    // memid = 0x490

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x490, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

    // Enumeration type = XlFileFormat
  public int getAxFileFormat ()
    throws ActiveXException {
    // memid = 0x120

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x120, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void ForwardMailer ()
    throws ActiveXException {
    // memid = 0x3cd

    Vector args = new Vector(0);
    axInvoke(0x3cd, AX_INVOKE, true, args);
  }

  public String getAxFullName ()
    throws ActiveXException {
    // memid = 0x121

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x121, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxHasMailer ()
    throws ActiveXException {
    // memid = 0x3d0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3d0, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasMailer (boolean param1)
    throws ActiveXException {
    // memid = 0x3d0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3d0, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHasPassword ()
    throws ActiveXException {
    // memid = 0x122

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x122, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxHasRoutingSlip ()
    throws ActiveXException {
    // memid = 0x3b6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3b6, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHasRoutingSlip (boolean param1)
    throws ActiveXException {
    // memid = 0x3b6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3b6, AX_PROPERTYSET, true, args);
  }

  public boolean getAxIsAddin ()
    throws ActiveXException {
    // memid = 0x5a5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIsAddin (boolean param1)
    throws ActiveXException {
    // memid = 0x5a5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5a5, AX_PROPERTYSET, true, args);
  }

  public String getAxKeywords ()
    throws ActiveXException {
    // memid = 0x241

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x241, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxKeywords (String param1)
    throws ActiveXException {
    // memid = 0x241

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x241, AX_PROPERTYSET, true, args);
  }

  public Variant LinkInfo (String param1, int param2)
    throws ActiveXException {
    // memid = 0x327

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x327, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LinkInfo (String param1, int param2, Variant param3)
    throws ActiveXException {
    // memid = 0x327

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    Variant vResult = axInvoke(0x327, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LinkInfo (String param1, int param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x327

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x327, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LinkSources ()
    throws ActiveXException {
    // memid = 0x328

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x328, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant LinkSources (Variant param1)
    throws ActiveXException {
    // memid = 0x328

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x328, AX_INVOKE, false, args);
    return vResult;
  }

  public Mailer getAxMailer ()
    throws ActiveXException {
    // memid = 0x3d3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3d3, AX_PROPERTYGET, false, args);
    Mailer result = new Mailer(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void MergeWorkbook (Variant param1)
    throws ActiveXException {
    // memid = 0x5a6

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5a6, AX_INVOKE, true, args);
  }

  public Sheets getAxModules ()
    throws ActiveXException {
    // memid = 0x246

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x246, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxMultiUserEditing ()
    throws ActiveXException {
    // memid = 0x491

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x491, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
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

  public Window NewWindow ()
    throws ActiveXException {
    // memid = 0x118

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x118, AX_INVOKE, false, args);
    Window result = new Window(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxOnSave ()
    throws ActiveXException {
    // memid = 0x49a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x49a, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnSave (String param1)
    throws ActiveXException {
    // memid = 0x49a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x49a, AX_PROPERTYSET, true, args);
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

  public void OpenLinks (String param1)
    throws ActiveXException {
    // memid = 0x323

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x323, AX_INVOKE, true, args);
  }

  public void OpenLinks (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x323

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x323, AX_INVOKE, true, args);
  }

  public void OpenLinks (String param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x323

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x323, AX_INVOKE, true, args);
  }

  public String getAxPath ()
    throws ActiveXException {
    // memid = 0x123

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x123, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxPersonalViewListSettings ()
    throws ActiveXException {
    // memid = 0x5a7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a7, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPersonalViewListSettings (boolean param1)
    throws ActiveXException {
    // memid = 0x5a7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5a7, AX_PROPERTYSET, true, args);
  }

  public boolean getAxPersonalViewPrintSettings ()
    throws ActiveXException {
    // memid = 0x5a8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a8, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPersonalViewPrintSettings (boolean param1)
    throws ActiveXException {
    // memid = 0x5a8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5a8, AX_PROPERTYSET, true, args);
  }

  public PivotCaches PivotCaches ()
    throws ActiveXException {
    // memid = 0x5a9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5a9, AX_INVOKE, false, args);
    PivotCaches result = new PivotCaches(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Post ()
    throws ActiveXException {
    // memid = 0x48e

    Vector args = new Vector(0);
    axInvoke(0x48e, AX_INVOKE, true, args);
  }

  public void Post (Variant param1)
    throws ActiveXException {
    // memid = 0x48e

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x48e, AX_INVOKE, true, args);
  }

  public boolean getAxPrecisionAsDisplayed ()
    throws ActiveXException {
    // memid = 0x195

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x195, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxPrecisionAsDisplayed (boolean param1)
    throws ActiveXException {
    // memid = 0x195

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x195, AX_PROPERTYSET, true, args);
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

  public void ProtectSharing ()
    throws ActiveXException {
    // memid = 0x5aa

    Vector args = new Vector(0);
    axInvoke(0x5aa, AX_INVOKE, true, args);
  }

  public void ProtectSharing (Variant param1)
    throws ActiveXException {
    // memid = 0x5aa

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5aa, AX_INVOKE, true, args);
  }

  public void ProtectSharing (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x5aa

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x5aa, AX_INVOKE, true, args);
  }

  public void ProtectSharing (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x5aa

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x5aa, AX_INVOKE, true, args);
  }

  public void ProtectSharing (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x5aa

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x5aa, AX_INVOKE, true, args);
  }

  public void ProtectSharing (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x5aa

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x5aa, AX_INVOKE, true, args);
  }

  public void ProtectSharing (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x5aa

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x5aa, AX_INVOKE, true, args);
  }

  public boolean getAxProtectStructure ()
    throws ActiveXException {
    // memid = 0x24c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x24c, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxProtectWindows ()
    throws ActiveXException {
    // memid = 0x127

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x127, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxReadOnly ()
    throws ActiveXException {
    // memid = 0x128

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x128, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public boolean getAxReadOnlyRecommended ()
    throws ActiveXException {
    // memid = 0x129

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x129, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void RefreshAll ()
    throws ActiveXException {
    // memid = 0x5ac

    Vector args = new Vector(0);
    axInvoke(0x5ac, AX_INVOKE, true, args);
  }

  public void Reply ()
    throws ActiveXException {
    // memid = 0x3d1

    Vector args = new Vector(0);
    axInvoke(0x3d1, AX_INVOKE, true, args);
  }

  public void ReplyAll ()
    throws ActiveXException {
    // memid = 0x3d2

    Vector args = new Vector(0);
    axInvoke(0x3d2, AX_INVOKE, true, args);
  }

  public void RemoveUser (int param1)
    throws ActiveXException {
    // memid = 0x5ad

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5ad, AX_INVOKE, true, args);
  }

  public int getAxRevisionNumber ()
    throws ActiveXException {
    // memid = 0x494

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x494, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void Route ()
    throws ActiveXException {
    // memid = 0x3b2

    Vector args = new Vector(0);
    axInvoke(0x3b2, AX_INVOKE, true, args);
  }

  public boolean getAxRouted ()
    throws ActiveXException {
    // memid = 0x3b7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3b7, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public RoutingSlip getAxRoutingSlip ()
    throws ActiveXException {
    // memid = 0x3b5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3b5, AX_PROPERTYGET, false, args);
    RoutingSlip result = new RoutingSlip(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void RunAutoMacros (int param1)
    throws ActiveXException {
    // memid = 0x27a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x27a, AX_INVOKE, true, args);
  }

  public void Save ()
    throws ActiveXException {
    // memid = 0x11b

    Vector args = new Vector(0);
    axInvoke(0x11b, AX_INVOKE, true, args);
  }

  public void SaveAs (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, int param7)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(7);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(new Variant(param7));
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, int param7, Variant param8)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(8);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(new Variant(param7));
    args.addElement(param8);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, int param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(9);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(new Variant(param7));
    args.addElement(param8);
    args.addElement(param9);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, int param7, Variant param8, Variant param9, Variant param10)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(10);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(new Variant(param7));
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveAs (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, int param7, Variant param8, Variant param9, Variant param10, Variant param11)
    throws ActiveXException {
    // memid = 0x11c

    Vector args = new Vector(11);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(new Variant(param7));
    args.addElement(param8);
    args.addElement(param9);
    args.addElement(param10);
    args.addElement(param11);
    axInvoke(0x11c, AX_INVOKE, true, args);
  }

  public void SaveCopyAs ()
    throws ActiveXException {
    // memid = 0xaf

    Vector args = new Vector(0);
    axInvoke(0xaf, AX_INVOKE, true, args);
  }

  public void SaveCopyAs (Variant param1)
    throws ActiveXException {
    // memid = 0xaf

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xaf, AX_INVOKE, true, args);
  }

  public boolean getAxSaved ()
    throws ActiveXException {
    // memid = 0x12a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x12a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSaved (boolean param1)
    throws ActiveXException {
    // memid = 0x12a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x12a, AX_PROPERTYSET, true, args);
  }

  public boolean getAxSaveLinkValues ()
    throws ActiveXException {
    // memid = 0x196

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x196, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSaveLinkValues (boolean param1)
    throws ActiveXException {
    // memid = 0x196

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x196, AX_PROPERTYSET, true, args);
  }

  public void SendMail (Variant param1)
    throws ActiveXException {
    // memid = 0x3b3

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x3b3, AX_INVOKE, true, args);
  }

  public void SendMail (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x3b3

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x3b3, AX_INVOKE, true, args);
  }

  public void SendMail (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x3b3

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x3b3, AX_INVOKE, true, args);
  }

  public void SendMailer (Variant param1, int param2)
    throws ActiveXException {
    // memid = 0x3d4

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0x3d4, AX_INVOKE, true, args);
  }

  public void SetLinkOnData (String param1)
    throws ActiveXException {
    // memid = 0x329

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x329, AX_INVOKE, true, args);
  }

  public void SetLinkOnData (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x329

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x329, AX_INVOKE, true, args);
  }

  public Sheets getAxSheets ()
    throws ActiveXException {
    // memid = 0x1e5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1e5, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxShowConflictHistory ()
    throws ActiveXException {
    // memid = 0x493

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x493, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxShowConflictHistory (boolean param1)
    throws ActiveXException {
    // memid = 0x493

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x493, AX_PROPERTYSET, true, args);
  }

  public Styles getAxStyles ()
    throws ActiveXException {
    // memid = 0x1ed

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1ed, AX_PROPERTYGET, false, args);
    Styles result = new Styles(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxSubject ()
    throws ActiveXException {
    // memid = 0x3b9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3b9, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxSubject (String param1)
    throws ActiveXException {
    // memid = 0x3b9

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3b9, AX_PROPERTYSET, true, args);
  }

  public String getAxTitle ()
    throws ActiveXException {
    // memid = 0xc7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc7, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxTitle (String param1)
    throws ActiveXException {
    // memid = 0xc7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xc7, AX_PROPERTYSET, true, args);
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

  public void UnprotectSharing ()
    throws ActiveXException {
    // memid = 0x5af

    Vector args = new Vector(0);
    axInvoke(0x5af, AX_INVOKE, true, args);
  }

  public void UnprotectSharing (Variant param1)
    throws ActiveXException {
    // memid = 0x5af

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5af, AX_INVOKE, true, args);
  }

  public void UpdateFromFile ()
    throws ActiveXException {
    // memid = 0x3e3

    Vector args = new Vector(0);
    axInvoke(0x3e3, AX_INVOKE, true, args);
  }

  public void UpdateLink ()
    throws ActiveXException {
    // memid = 0x324

    Vector args = new Vector(0);
    axInvoke(0x324, AX_INVOKE, true, args);
  }

  public void UpdateLink (Variant param1)
    throws ActiveXException {
    // memid = 0x324

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x324, AX_INVOKE, true, args);
  }

  public void UpdateLink (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x324

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x324, AX_INVOKE, true, args);
  }

  public boolean getAxUpdateRemoteReferences ()
    throws ActiveXException {
    // memid = 0x19b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x19b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxUpdateRemoteReferences (boolean param1)
    throws ActiveXException {
    // memid = 0x19b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x19b, AX_PROPERTYSET, true, args);
  }

  public boolean getAxUserControl ()
    throws ActiveXException {
    // memid = 0x4ba

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x4ba, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxUserControl (boolean param1)
    throws ActiveXException {
    // memid = 0x4ba

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x4ba, AX_PROPERTYSET, true, args);
  }

  public Variant getAxUserStatus ()
    throws ActiveXException {
    // memid = 0x495

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x495, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public CustomViews getAxCustomViews ()
    throws ActiveXException {
    // memid = 0x5b0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5b0, AX_PROPERTYGET, false, args);
    CustomViews result = new CustomViews(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Windows getAxWindows ()
    throws ActiveXException {
    // memid = 0x1ae

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1ae, AX_PROPERTYGET, false, args);
    Windows result = new Windows(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Sheets getAxWorksheets ()
    throws ActiveXException {
    // memid = 0x1ee

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1ee, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxWriteReserved ()
    throws ActiveXException {
    // memid = 0x12b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x12b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public String getAxWriteReservedBy ()
    throws ActiveXException {
    // memid = 0x12c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x12c, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Sheets getAxExcel4IntlMacroSheets ()
    throws ActiveXException {
    // memid = 0x245

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x245, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Sheets getAxExcel4MacroSheets ()
    throws ActiveXException {
    // memid = 0x243

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x243, AX_PROPERTYGET, false, args);
    Sheets result = new Sheets(vResult.getActiveXDispatchableValue());
    return result;
  }

  public boolean getAxTemplateRemoveExtData ()
    throws ActiveXException {
    // memid = 0x5b1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5b1, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxTemplateRemoveExtData (boolean param1)
    throws ActiveXException {
    // memid = 0x5b1

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5b1, AX_PROPERTYSET, true, args);
  }

  public void HighlightChangesOptions ()
    throws ActiveXException {
    // memid = 0x5b2

    Vector args = new Vector(0);
    axInvoke(0x5b2, AX_INVOKE, true, args);
  }

  public void HighlightChangesOptions (Variant param1)
    throws ActiveXException {
    // memid = 0x5b2

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5b2, AX_INVOKE, true, args);
  }

  public void HighlightChangesOptions (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x5b2

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x5b2, AX_INVOKE, true, args);
  }

  public void HighlightChangesOptions (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x5b2

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x5b2, AX_INVOKE, true, args);
  }

  public boolean getAxHighlightChangesOnScreen ()
    throws ActiveXException {
    // memid = 0x5b5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5b5, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHighlightChangesOnScreen (boolean param1)
    throws ActiveXException {
    // memid = 0x5b5

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5b5, AX_PROPERTYSET, true, args);
  }

  public boolean getAxKeepChangeHistory ()
    throws ActiveXException {
    // memid = 0x5b6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5b6, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxKeepChangeHistory (boolean param1)
    throws ActiveXException {
    // memid = 0x5b6

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5b6, AX_PROPERTYSET, true, args);
  }

  public boolean getAxListChangesOnNewSheet ()
    throws ActiveXException {
    // memid = 0x5b7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5b7, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxListChangesOnNewSheet (boolean param1)
    throws ActiveXException {
    // memid = 0x5b7

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5b7, AX_PROPERTYSET, true, args);
  }

  public void PurgeChangeHistoryNow (int param1)
    throws ActiveXException {
    // memid = 0x5b8

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5b8, AX_INVOKE, true, args);
  }

  public void PurgeChangeHistoryNow (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0x5b8

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x5b8, AX_INVOKE, true, args);
  }

  public void AcceptAllChanges ()
    throws ActiveXException {
    // memid = 0x5ba

    Vector args = new Vector(0);
    axInvoke(0x5ba, AX_INVOKE, true, args);
  }

  public void AcceptAllChanges (Variant param1)
    throws ActiveXException {
    // memid = 0x5ba

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5ba, AX_INVOKE, true, args);
  }

  public void AcceptAllChanges (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x5ba

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x5ba, AX_INVOKE, true, args);
  }

  public void AcceptAllChanges (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x5ba

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x5ba, AX_INVOKE, true, args);
  }

  public void RejectAllChanges ()
    throws ActiveXException {
    // memid = 0x5bb

    Vector args = new Vector(0);
    axInvoke(0x5bb, AX_INVOKE, true, args);
  }

  public void RejectAllChanges (Variant param1)
    throws ActiveXException {
    // memid = 0x5bb

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x5bb, AX_INVOKE, true, args);
  }

  public void RejectAllChanges (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x5bb

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x5bb, AX_INVOKE, true, args);
  }

  public void RejectAllChanges (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x5bb

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x5bb, AX_INVOKE, true, args);
  }

  public void PivotTableWizard ()
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(0);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x2ac

    Vector args = new Vector(6);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void PivotTableWizard (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9, Variant param10, Variant param11, Variant param12, Variant param13, Variant param14, Variant param15, Variant param16)
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
    axInvoke(0x2ac, AX_INVOKE, true, args);
  }

  public void ResetColors ()
    throws ActiveXException {
    // memid = 0x5bc

    Vector args = new Vector(0);
    axInvoke(0x5bc, AX_INVOKE, true, args);
  }

  public Variant getAxVBProject ()
    throws ActiveXException {
    // memid = 0x5bd

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5bd, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void FollowHyperlink (String param1)
    throws ActiveXException {
    // memid = 0x5be

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x5be, AX_INVOKE, true, args);
  }

  public void FollowHyperlink (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x5be

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x5be, AX_INVOKE, true, args);
  }

  public void FollowHyperlink (String param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x5be

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x5be, AX_INVOKE, true, args);
  }

  public void FollowHyperlink (String param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x5be

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x5be, AX_INVOKE, true, args);
  }

  public void FollowHyperlink (String param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x5be

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0x5be, AX_INVOKE, true, args);
  }

  public void FollowHyperlink (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x5be

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    axInvoke(0x5be, AX_INVOKE, true, args);
  }

  public void FollowHyperlink (String param1, Variant param2, Variant param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x5be

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    axInvoke(0x5be, AX_INVOKE, true, args);
  }

  public void AddToFavorites ()
    throws ActiveXException {
    // memid = 0x5c4

    Vector args = new Vector(0);
    axInvoke(0x5c4, AX_INVOKE, true, args);
  }

  public boolean getAxIsInplace ()
    throws ActiveXException {
    // memid = 0x6f4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6f4, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

@Override
public String toString() {
    return "<Workbook, super = " + super.toString() + ">";
}


}

