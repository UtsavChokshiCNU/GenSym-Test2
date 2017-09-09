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


public class Assistant extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc0322, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Assistant (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #97
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Assistant
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    Type Info contains 56 functions.
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

  public void Move (int param1, int param2)
    throws ActiveXException {
    // memid = 0x60030001

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x60030001, AX_INVOKE, true, args);
  }

  public void setAxTop (int param1)
    throws ActiveXException {
    // memid = 0x60030002

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030002, AX_PROPERTYSET, true, args);
  }

  public int getAxTop ()
    throws ActiveXException {
    // memid = 0x60030002

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030002, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxLeft (int param1)
    throws ActiveXException {
    // memid = 0x60030004

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030004, AX_PROPERTYSET, true, args);
  }

  public int getAxLeft ()
    throws ActiveXException {
    // memid = 0x60030004

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030004, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void Help ()
    throws ActiveXException {
    // memid = 0x60030006

    Vector args = new Vector(0);
    axInvoke(0x60030006, AX_INVOKE, true, args);
  }

  public int StartWizard (boolean param1, String param2, int param3)
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    Variant vResult = axInvoke(0x60030007, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int StartWizard (boolean param1, String param2, int param3, Variant param4)
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    Variant vResult = axInvoke(0x60030007, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int StartWizard (boolean param1, String param2, int param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(5);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x60030007, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int StartWizard (boolean param1, String param2, int param3, Variant param4, Variant param5, Variant param6)
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(6);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    Variant vResult = axInvoke(0x60030007, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int StartWizard (boolean param1, String param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7)
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(7);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    Variant vResult = axInvoke(0x60030007, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int StartWizard (boolean param1, String param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8)
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(8);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    Variant vResult = axInvoke(0x60030007, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int StartWizard (boolean param1, String param2, int param3, Variant param4, Variant param5, Variant param6, Variant param7, Variant param8, Variant param9)
    throws ActiveXException {
    // memid = 0x60030007

    Vector args = new Vector(9);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    args.addElement(param5);
    args.addElement(param6);
    args.addElement(param7);
    args.addElement(param8);
    args.addElement(param9);
    Variant vResult = axInvoke(0x60030007, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void EndWizard (int param1, boolean param2)
    throws ActiveXException {
    // memid = 0x60030008

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x60030008, AX_INVOKE, true, args);
  }

  public void EndWizard (int param1, boolean param2, Variant param3)
    throws ActiveXException {
    // memid = 0x60030008

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x60030008, AX_INVOKE, true, args);
  }

  public void ActivateWizard (int param1, int param2)
    throws ActiveXException {
    // memid = 0x60030009

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x60030009, AX_INVOKE, true, args);
  }

  public void ActivateWizard (int param1, int param2, Variant param3)
    throws ActiveXException {
    // memid = 0x60030009

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x60030009, AX_INVOKE, true, args);
  }

  public void ResetTips ()
    throws ActiveXException {
    // memid = 0x6003000a

    Vector args = new Vector(0);
    axInvoke(0x6003000a, AX_INVOKE, true, args);
  }

  public ActiveXDispatchable getAxNewBalloon ()
    throws ActiveXException {
    // memid = 0x6003000b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000b, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

    // Enumeration type = MsoBalloonErrorType
  public int getAxBalloonError ()
    throws ActiveXException {
    // memid = 0x6003000c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxVisible ()
    throws ActiveXException {
    // memid = 0x6003000d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxVisible (boolean param1)
    throws ActiveXException {
    // memid = 0x6003000d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003000d, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoAnimationType
  public int getAxAnimation ()
    throws ActiveXException {
    // memid = 0x6003000f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003000f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxAnimation (int param1)
    throws ActiveXException {
    // memid = 0x6003000f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003000f, AX_PROPERTYSET, true, args);
  }

  public boolean getAxReduced ()
    throws ActiveXException {
    // memid = 0x60030011

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030011, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxReduced (boolean param1)
    throws ActiveXException {
    // memid = 0x60030011

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030011, AX_PROPERTYSET, true, args);
  }

  public void setAxAssistWithHelp (boolean param1)
    throws ActiveXException {
    // memid = 0x60030013

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030013, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAssistWithHelp ()
    throws ActiveXException {
    // memid = 0x60030013

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030013, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAssistWithWizards (boolean param1)
    throws ActiveXException {
    // memid = 0x60030015

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030015, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAssistWithWizards ()
    throws ActiveXException {
    // memid = 0x60030015

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030015, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxAssistWithAlerts (boolean param1)
    throws ActiveXException {
    // memid = 0x60030017

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030017, AX_PROPERTYSET, true, args);
  }

  public boolean getAxAssistWithAlerts ()
    throws ActiveXException {
    // memid = 0x60030017

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030017, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxMoveWhenInTheWay (boolean param1)
    throws ActiveXException {
    // memid = 0x60030019

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030019, AX_PROPERTYSET, true, args);
  }

  public boolean getAxMoveWhenInTheWay ()
    throws ActiveXException {
    // memid = 0x60030019

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030019, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSounds (boolean param1)
    throws ActiveXException {
    // memid = 0x6003001b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003001b, AX_PROPERTYSET, true, args);
  }

  public boolean getAxSounds ()
    throws ActiveXException {
    // memid = 0x6003001b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003001b, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxFeatureTips (boolean param1)
    throws ActiveXException {
    // memid = 0x6003001d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003001d, AX_PROPERTYSET, true, args);
  }

  public boolean getAxFeatureTips ()
    throws ActiveXException {
    // memid = 0x6003001d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003001d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxMouseTips (boolean param1)
    throws ActiveXException {
    // memid = 0x6003001f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003001f, AX_PROPERTYSET, true, args);
  }

  public boolean getAxMouseTips ()
    throws ActiveXException {
    // memid = 0x6003001f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003001f, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxKeyboardShortcutTips (boolean param1)
    throws ActiveXException {
    // memid = 0x60030021

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030021, AX_PROPERTYSET, true, args);
  }

  public boolean getAxKeyboardShortcutTips ()
    throws ActiveXException {
    // memid = 0x60030021

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030021, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxHighPriorityTips (boolean param1)
    throws ActiveXException {
    // memid = 0x60030023

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030023, AX_PROPERTYSET, true, args);
  }

  public boolean getAxHighPriorityTips ()
    throws ActiveXException {
    // memid = 0x60030023

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030023, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxTipOfDay (boolean param1)
    throws ActiveXException {
    // memid = 0x60030025

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030025, AX_PROPERTYSET, true, args);
  }

  public boolean getAxTipOfDay ()
    throws ActiveXException {
    // memid = 0x60030025

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030025, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxGuessHelp (boolean param1)
    throws ActiveXException {
    // memid = 0x60030027

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030027, AX_PROPERTYSET, true, args);
  }

  public boolean getAxGuessHelp ()
    throws ActiveXException {
    // memid = 0x60030027

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030027, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxSearchWhenProgramming (boolean param1)
    throws ActiveXException {
    // memid = 0x60030029

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60030029, AX_PROPERTYSET, true, args);
  }

  public boolean getAxSearchWhenProgramming ()
    throws ActiveXException {
    // memid = 0x60030029

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030029, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public String getAxItem ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxFileName ()
    throws ActiveXException {
    // memid = 0x6003002c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003002c, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxFileName (String param1)
    throws ActiveXException {
    // memid = 0x6003002c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6003002c, AX_PROPERTYSET, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x6003002e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6003002e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

@Override
public String toString() {
    return "<Assistant, super = " + super.toString() + ">";
}


}

