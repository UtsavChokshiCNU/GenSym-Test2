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


public class ChartFillFormat extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x24435, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public ChartFillFormat (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #472
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: ChartFillFormat
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 32 functions.
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

  public void OneColorGradient (int param1, int param2, float param3)
    throws ActiveXException {
    // memid = 0x655

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x655, AX_INVOKE, true, args);
  }

  public void TwoColorGradient (int param1, int param2)
    throws ActiveXException {
    // memid = 0x658

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x658, AX_INVOKE, true, args);
  }

  public void PresetTextured (int param1)
    throws ActiveXException {
    // memid = 0x659

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x659, AX_INVOKE, true, args);
  }

  public void Solid ()
    throws ActiveXException {
    // memid = 0x65b

    Vector args = new Vector(0);
    axInvoke(0x65b, AX_INVOKE, true, args);
  }

  public void Patterned (int param1)
    throws ActiveXException {
    // memid = 0x65c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x65c, AX_INVOKE, true, args);
  }

  public void UserPicture ()
    throws ActiveXException {
    // memid = 0x65d

    Vector args = new Vector(0);
    axInvoke(0x65d, AX_INVOKE, true, args);
  }

  public void UserPicture (Variant param1)
    throws ActiveXException {
    // memid = 0x65d

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x65d, AX_INVOKE, true, args);
  }

  public void UserPicture (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x65d

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x65d, AX_INVOKE, true, args);
  }

  public void UserPicture (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x65d

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x65d, AX_INVOKE, true, args);
  }

  public void UserPicture (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x65d

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x65d, AX_INVOKE, true, args);
  }

  public void UserTextured (String param1)
    throws ActiveXException {
    // memid = 0x662

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x662, AX_INVOKE, true, args);
  }

  public void PresetGradient (int param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0x664

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x664, AX_INVOKE, true, args);
  }

  public ChartColorFormat getAxBackColor ()
    throws ActiveXException {
    // memid = 0x666

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x666, AX_PROPERTYGET, false, args);
    ChartColorFormat result = new ChartColorFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ChartColorFormat getAxForeColor ()
    throws ActiveXException {
    // memid = 0x667

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x667, AX_PROPERTYGET, false, args);
    ChartColorFormat result = new ChartColorFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = MsoGradientColorType
  public int getAxGradientColorType ()
    throws ActiveXException {
    // memid = 0x668

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x668, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public float getAxGradientDegree ()
    throws ActiveXException {
    // memid = 0x669

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x669, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

    // Enumeration type = MsoGradientStyle
  public int getAxGradientStyle ()
    throws ActiveXException {
    // memid = 0x66a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x66a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxGradientVariant ()
    throws ActiveXException {
    // memid = 0x66b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x66b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoPatternType
  public int getAxPattern ()
    throws ActiveXException {
    // memid = 0x5f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x5f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoPresetGradientType
  public int getAxPresetGradientType ()
    throws ActiveXException {
    // memid = 0x665

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x665, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoPresetTexture
  public int getAxPresetTexture ()
    throws ActiveXException {
    // memid = 0x65a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x65a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxTextureName ()
    throws ActiveXException {
    // memid = 0x66c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x66c, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

    // Enumeration type = MsoTextureType
  public int getAxTextureType ()
    throws ActiveXException {
    // memid = 0x66d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x66d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoFillType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoTriState
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

@Override
public String toString() {
    return "<ChartFillFormat, super = " + super.toString() + ">";
}


}

