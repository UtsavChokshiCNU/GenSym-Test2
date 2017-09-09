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


public class CommandBarControl extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc0308, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public CommandBarControl (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #75
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: CommandBarControl
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    Type Info contains 83 functions.
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

  public boolean getAxBeginGroup ()
    throws ActiveXException {
    // memid = 0x60040000

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040000, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxBeginGroup (boolean param1)
    throws ActiveXException {
    // memid = 0x60040000

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040000, AX_PROPERTYSET, true, args);
  }

  public boolean getAxBuiltIn ()
    throws ActiveXException {
    // memid = 0x60040002

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040002, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public String getAxCaption ()
    throws ActiveXException {
    // memid = 0x60040003

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040003, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCaption (String param1)
    throws ActiveXException {
    // memid = 0x60040003

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040003, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxControl ()
    throws ActiveXException {
    // memid = 0x60040005

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040005, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public CommandBarControl Copy ()
    throws ActiveXException {
    // memid = 0x60040006

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040006, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl Copy (Variant param1)
    throws ActiveXException {
    // memid = 0x60040006

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x60040006, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl Copy (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x60040006

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x60040006, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x60040007

    Vector args = new Vector(0);
    axInvoke(0x60040007, AX_INVOKE, true, args);
  }

  public void Delete (Variant param1)
    throws ActiveXException {
    // memid = 0x60040007

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x60040007, AX_INVOKE, true, args);
  }

  public String getAxDescriptionText ()
    throws ActiveXException {
    // memid = 0x60040008

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040008, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxDescriptionText (String param1)
    throws ActiveXException {
    // memid = 0x60040008

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040008, AX_PROPERTYSET, true, args);
  }

  public boolean getAxEnabled ()
    throws ActiveXException {
    // memid = 0x6004000a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004000a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxEnabled (boolean param1)
    throws ActiveXException {
    // memid = 0x6004000a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004000a, AX_PROPERTYSET, true, args);
  }

  public void Execute ()
    throws ActiveXException {
    // memid = 0x6004000c

    Vector args = new Vector(0);
    axInvoke(0x6004000c, AX_INVOKE, true, args);
  }

  public int getAxHeight ()
    throws ActiveXException {
    // memid = 0x6004000d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004000d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHeight (int param1)
    throws ActiveXException {
    // memid = 0x6004000d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004000d, AX_PROPERTYSET, true, args);
  }

  public int getAxHelpContextId ()
    throws ActiveXException {
    // memid = 0x6004000f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004000f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHelpContextId (int param1)
    throws ActiveXException {
    // memid = 0x6004000f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004000f, AX_PROPERTYSET, true, args);
  }

  public String getAxHelpFile ()
    throws ActiveXException {
    // memid = 0x60040011

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040011, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxHelpFile (String param1)
    throws ActiveXException {
    // memid = 0x60040011

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040011, AX_PROPERTYSET, true, args);
  }

  public int getAxId ()
    throws ActiveXException {
    // memid = 0x60040013

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040013, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxIndex ()
    throws ActiveXException {
    // memid = 0x60040014

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040014, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxInstanceId ()
    throws ActiveXException {
    // memid = 0x60040015

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040015, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public CommandBarControl Move ()
    throws ActiveXException {
    // memid = 0x60040016

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040016, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl Move (Variant param1)
    throws ActiveXException {
    // memid = 0x60040016

    Vector args = new Vector(1);
    args.addElement(param1);
    Variant vResult = axInvoke(0x60040016, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public CommandBarControl Move (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x60040016

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    Variant vResult = axInvoke(0x60040016, AX_INVOKE, false, args);
    CommandBarControl result = new CommandBarControl(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxLeft ()
    throws ActiveXException {
    // memid = 0x60040017

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040017, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoControlOLEUsage
  public int getAxOLEUsage ()
    throws ActiveXException {
    // memid = 0x60040018

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040018, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxOLEUsage (int param1)
    throws ActiveXException {
    // memid = 0x60040018

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040018, AX_PROPERTYSET, true, args);
  }

  public String getAxOnAction ()
    throws ActiveXException {
    // memid = 0x6004001a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004001a, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnAction (String param1)
    throws ActiveXException {
    // memid = 0x6004001a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004001a, AX_PROPERTYSET, true, args);
  }

  public CommandBar getAxParent ()
    throws ActiveXException {
    // memid = 0x6004001c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004001c, AX_PROPERTYGET, false, args);
    CommandBar result = new CommandBar(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxParameter ()
    throws ActiveXException {
    // memid = 0x6004001d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004001d, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxParameter (String param1)
    throws ActiveXException {
    // memid = 0x6004001d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004001d, AX_PROPERTYSET, true, args);
  }

  public int getAxPriority ()
    throws ActiveXException {
    // memid = 0x6004001f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004001f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPriority (int param1)
    throws ActiveXException {
    // memid = 0x6004001f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004001f, AX_PROPERTYSET, true, args);
  }

  public void Reset ()
    throws ActiveXException {
    // memid = 0x60040021

    Vector args = new Vector(0);
    axInvoke(0x60040021, AX_INVOKE, true, args);
  }

  public void SetFocus ()
    throws ActiveXException {
    // memid = 0x60040022

    Vector args = new Vector(0);
    axInvoke(0x60040022, AX_INVOKE, true, args);
  }

  public String getAxTag ()
    throws ActiveXException {
    // memid = 0x60040023

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040023, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxTag (String param1)
    throws ActiveXException {
    // memid = 0x60040023

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040023, AX_PROPERTYSET, true, args);
  }

  public String getAxTooltipText ()
    throws ActiveXException {
    // memid = 0x60040025

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040025, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxTooltipText (String param1)
    throws ActiveXException {
    // memid = 0x60040025

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040025, AX_PROPERTYSET, true, args);
  }

  public int getAxTop ()
    throws ActiveXException {
    // memid = 0x60040027

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040027, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoControlType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x60040028

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040028, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxVisible ()
    throws ActiveXException {
    // memid = 0x60040029

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60040029, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxVisible (boolean param1)
    throws ActiveXException {
    // memid = 0x60040029

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60040029, AX_PROPERTYSET, true, args);
  }

  public int getAxWidth ()
    throws ActiveXException {
    // memid = 0x6004002b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6004002b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxWidth (int param1)
    throws ActiveXException {
    // memid = 0x6004002b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6004002b, AX_PROPERTYSET, true, args);
  }

  public void Reserved1 ()
    throws ActiveXException {
    // memid = 0x6004002d

    Vector args = new Vector(0);
    axInvoke(0x6004002d, AX_INVOKE, true, args);
  }

  public void Reserved2 ()
    throws ActiveXException {
    // memid = 0x6004002e

    Vector args = new Vector(0);
    axInvoke(0x6004002e, AX_INVOKE, true, args);
  }

  public void Reserved3 ()
    throws ActiveXException {
    // memid = 0x6004002f

    Vector args = new Vector(0);
    axInvoke(0x6004002f, AX_INVOKE, true, args);
  }

  public void Reserved4 ()
    throws ActiveXException {
    // memid = 0x60040030

    Vector args = new Vector(0);
    axInvoke(0x60040030, AX_INVOKE, true, args);
  }

  public void Reserved5 ()
    throws ActiveXException {
    // memid = 0x60040031

    Vector args = new Vector(0);
    axInvoke(0x60040031, AX_INVOKE, true, args);
  }

  public void Reserved6 ()
    throws ActiveXException {
    // memid = 0x60040032

    Vector args = new Vector(0);
    axInvoke(0x60040032, AX_INVOKE, true, args);
  }

  public void Reserved7 ()
    throws ActiveXException {
    // memid = 0x60040033

    Vector args = new Vector(0);
    axInvoke(0x60040033, AX_INVOKE, true, args);
  }

  public void Reserved8 ()
    throws ActiveXException {
    // memid = 0x60040034

    Vector args = new Vector(0);
    axInvoke(0x60040034, AX_INVOKE, true, args);
  }

@Override
public String toString() {
    return "<CommandBarControl, super = " + super.toString() + ">";
}


}

