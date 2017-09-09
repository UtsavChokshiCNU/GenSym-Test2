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


public class IAccessible extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x618736e0, 0x3c3d, 0x11cf,
             (short) 0x81, (short) 0xc, (short) 0x0, (short) 0xaa,
             (short) 0x0, (short) 0x38, (short) 0x9b, (short) 0x71);

  public IAccessible (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #69
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: IAccessible
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    Type Info contains 28 functions.
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

@Override
public String toString() {
    return "<IAccessible, super = " + super.toString() + ">";
}


}

