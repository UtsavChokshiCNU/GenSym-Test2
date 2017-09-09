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


public class CommandBar extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc0304, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public CommandBar (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #73
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: CommandBar
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    Type Info contains 64 functions.
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

  public ActiveXDispatchable getAxaccParent ()
    throws ActiveXException {
    // memid = 0xffffec78

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec78, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public int getAxaccChildCount ()
    throws ActiveXException {
    // memid = 0xffffec77

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec77, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ActiveXDispatchable getAxaccChild (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec76

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec76, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public String getAxaccName ()
    throws ActiveXException {
    // memid = 0xffffec75

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec75, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxaccName (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec75

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec75, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxaccValue ()
    throws ActiveXException {
    // memid = 0xffffec74

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec74, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxaccValue (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec74

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec74, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxaccDescription ()
    throws ActiveXException {
    // memid = 0xffffec73

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec73, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxaccDescription (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec73

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec73, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Variant getAxaccRole ()
    throws ActiveXException {
    // memid = 0xffffec72

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec72, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxaccRole (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec72

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec72, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxaccState ()
    throws ActiveXException {
    // memid = 0xffffec71

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec71, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxaccState (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec71

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec71, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public String getAxaccHelp ()
    throws ActiveXException {
    // memid = 0xffffec70

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec70, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxaccHelp (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec70

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec70, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public int getAxaccHelpTopic (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec6f

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec6f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxaccHelpTopic (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xffffec6f

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0xffffec6f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public String getAxaccKeyboardShortcut ()
    throws ActiveXException {
    // memid = 0xffffec6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec6e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxaccKeyboardShortcut (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec6e

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec6e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Variant getAxaccFocus ()
    throws ActiveXException {
    // memid = 0xffffec6d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec6d, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxaccSelection ()
    throws ActiveXException {
    // memid = 0xffffec6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec6c, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public String getAxaccDefaultAction ()
    throws ActiveXException {
    // memid = 0xffffec6b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xffffec6b, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxaccDefaultAction (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec6b

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0xffffec6b, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void accSelect (int param1)
    throws ActiveXException {
    // memid = 0xffffec6a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xffffec6a, AX_INVOKE, true, args);
  }

  public void accSelect (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0xffffec6a

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0xffffec6a, AX_INVOKE, true, args);
  }

  public void accLocation (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0xffffec69

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0xffffec69, AX_INVOKE, true, args);
  }

  public void accLocation (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0xffffec69

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    axInvoke(0xffffec69, AX_INVOKE, true, args);
  }

  public Variant accNavigate (int param1)
    throws ActiveXException {
    // memid = 0xffffec68

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0xffffec68, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant accNavigate (int param1, Variant param2)
    throws ActiveXException {
    // memid = 0xffffec68

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    Variant vResult = axInvoke(0xffffec68, AX_INVOKE, false, args);
    return vResult;
  }

  public Variant accHitTest (int param1, int param2)
    throws ActiveXException {
    // memid = 0xffffec67

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0xffffec67, AX_INVOKE, false, args);
    return vResult;
  }

  public void accDoDefaultAction ()
    throws ActiveXException {
    // memid = 0xffffec66

    Vector args = new Vector(0);
    axInvoke(0xffffec66, AX_INVOKE, true, args);
  }

  public void accDoDefaultAction (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec66

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xffffec66, AX_INVOKE, true, args);
  }

  public void setAxaccName (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec75

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xffffec75, AX_PROPERTYSET, true, args);
  }

  public void setAxaccName (Variant param1, String param2)
    throws ActiveXException {
    // memid = 0xffffec75

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0xffffec75, AX_PROPERTYSET, true, args);
  }

  public void setAxaccValue (Variant param1)
    throws ActiveXException {
    // memid = 0xffffec74

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xffffec74, AX_PROPERTYSET, true, args);
  }

  public void setAxaccValue (Variant param1, String param2)
    throws ActiveXException {
    // memid = 0xffffec74

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    axInvoke(0xffffec74, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxApplication ()
    throws ActiveXException {
    // memid = 0x60030000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030000, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public int getAxCreator ()
    throws ActiveXException {
    // memid = 0x60030001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60030001, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxBuiltIn ()
    throws ActiveXException {
    // memid = 0x60040000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040000, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public String getAxContext ()
    throws ActiveXException {
    // memid = 0x60040001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040001, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxContext (String param1)
    throws ActiveXException {
    // memid = 0x60040001

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040001, AX_PROPERTYSET, true, args);
  }

  public CommandBarControls getAxControls ()
    throws ActiveXException {
    // memid = 0x60040003

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040003, AX_PROPERTYGET, false, args);
    CommandBarControls result = new CommandBarControls(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x60040004

    Vector args = new Vector(0);
    axInvoke(0x60040004, AX_INVOKE, true, args);
  }

  public boolean getAxEnabled ()
    throws ActiveXException {
    // memid = 0x60040005

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040005, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnabled (boolean param1)
    throws ActiveXException {
    // memid = 0x60040005

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040005, AX_PROPERTYSET, true, args);
  }

  public CommandBarControl FindControl ()
    throws ActiveXException {
    // memid = 0x60040007

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040007, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1)
    throws ActiveXException {
    // memid = 0x60040007

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x60040007, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x60040007

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x60040007, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x60040007

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    Variant vResult = axInvoke(0x60040007, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x60040007

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    Variant vResult = axInvoke(0x60040007, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl FindControl (Variant param1, Variant param2, Variant param3, Variant param4, Variant param5)
    throws ActiveXException {
    // memid = 0x60040007

    Vector args = new Vector(5);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    args.addElement(param5);
    Variant vResult = axInvoke(0x60040007, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxHeight ()
    throws ActiveXException {
    // memid = 0x60040008

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040008, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHeight (int param1)
    throws ActiveXException {
    // memid = 0x60040008

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040008, AX_PROPERTYSET, true, args);
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x6004000a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004000a, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxInstanceId ()
    throws ActiveXException {
    // memid = 0x6004000b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004000b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxLeft ()
    throws ActiveXException {
    // memid = 0x6004000c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004000c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxLeft (int param1)
    throws ActiveXException {
    // memid = 0x6004000c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004000c, AX_PROPERTYSET, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x6004000e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004000e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x6004000e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004000e, AX_PROPERTYSET, true, args);
  }

  public String getAxNameLocal ()
    throws ActiveXException {
    // memid = 0x60040010

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040010, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxNameLocal (String param1)
    throws ActiveXException {
    // memid = 0x60040010

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040010, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxParent ()
    throws ActiveXException {
    // memid = 0x60040012

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040012, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

    // Enumeration type = MsoBarPosition
  public int getAxPosition ()
    throws ActiveXException {
    // memid = 0x60040013

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040013, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPosition (int param1)
    throws ActiveXException {
    // memid = 0x60040013

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040013, AX_PROPERTYSET, true, args);
  }

  public int getAxRowIndex ()
    throws ActiveXException {
    // memid = 0x60040015

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040015, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxRowIndex (int param1)
    throws ActiveXException {
    // memid = 0x60040015

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040015, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoBarProtection
  public int getAxProtection ()
    throws ActiveXException {
    // memid = 0x60040017

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040017, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxProtection (int param1)
    throws ActiveXException {
    // memid = 0x60040017

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040017, AX_PROPERTYSET, true, args);
  }

  public void Reset ()
    throws ActiveXException {
    // memid = 0x60040019

    Vector args = new Vector(0);
    axInvoke(0x60040019, AX_INVOKE, true, args);
  }

  public void ShowPopup ()
    throws ActiveXException {
    // memid = 0x6004001a

    Vector args = new Vector(0);
    axInvoke(0x6004001a, AX_INVOKE, true, args);
  }

  public void ShowPopup (Variant param1)
    throws ActiveXException {
    // memid = 0x6004001a

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6004001a, AX_INVOKE, true, args);
  }

  public void ShowPopup (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x6004001a

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x6004001a, AX_INVOKE, true, args);
  }

  public int getAxTop ()
    throws ActiveXException {
    // memid = 0x6004001b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004001b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxTop (int param1)
    throws ActiveXException {
    // memid = 0x6004001b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004001b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoBarType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x6004001d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004001d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxVisible ()
    throws ActiveXException {
    // memid = 0x6004001e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004001e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxVisible (boolean param1)
    throws ActiveXException {
    // memid = 0x6004001e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004001e, AX_PROPERTYSET, true, args);
  }

  public int getAxWidth ()
    throws ActiveXException {
    // memid = 0x60040020

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040020, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxWidth (int param1)
    throws ActiveXException {
    // memid = 0x60040020

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040020, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<CommandBar, super = " + super.toString() + ">";
}


}

