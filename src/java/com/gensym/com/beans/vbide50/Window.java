package com.gensym.com.beans.vbide50;

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


public class Window extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e10e, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Window (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic 5.0 Extensibility
    // Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    // There are 108 TypeInfos in the library

/* Type info #17
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Window
    Doc string is: Represents a Window object in Visual Basic.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 31 functions.
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

  public VBE getAxVBE ()
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1, AX_PROPERTYGET, false, args);
    VBE result = new VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxCollection ()
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public void Close ()
    throws ActiveXException {
    // memid = 0x63

    Vector args = new Vector(0);
    axInvoke(0x63, AX_INVOKE, true, args);
  }

  public String getAxCaption ()
    throws ActiveXException {
    // memid = 0x64

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxVisible ()
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxVisible (boolean param1)
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6a, AX_PROPERTYSET, true, args);
  }

  public int getAxLeft ()
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x65, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxLeft (int param1)
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x65, AX_PROPERTYSET, true, args);
  }

  public int getAxTop ()
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxTop (int param1)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x67, AX_PROPERTYSET, true, args);
  }

  public int getAxWidth ()
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxWidth (int param1)
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x69, AX_PROPERTYSET, true, args);
  }

  public int getAxHeight ()
    throws ActiveXException {
    // memid = 0x6b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6b, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHeight (int param1)
    throws ActiveXException {
    // memid = 0x6b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = vbextWindowState
  public int getAxWindowState ()
    throws ActiveXException {
    // memid = 0x6d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxWindowState (int param1)
    throws ActiveXException {
    // memid = 0x6d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6d, AX_PROPERTYSET, true, args);
  }

  public void SetFocus ()
    throws ActiveXException {
    // memid = 0x6f

    Vector args = new Vector(0);
    axInvoke(0x6f, AX_INVOKE, true, args);
  }

    // Enumeration type = vbextWindowType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x70

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x70, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void SetKind (int param1)
    throws ActiveXException {
    // memid = 0x71

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x71, AX_INVOKE, true, args);
  }

  public Variant getAxLinkedWindows ()
    throws ActiveXException {
    // memid = 0x74

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x74, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Window getAxLinkedWindowFrame ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x75, AX_PROPERTYGET, false, args);
    Window result = new Window(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Detach ()
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(0);
    axInvoke(0x76, AX_INVOKE, true, args);
  }

  public void Attach (int param1)
    throws ActiveXException {
    // memid = 0x77

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x77, AX_INVOKE, true, args);
  }

  public int getAxHWnd ()
    throws ActiveXException {
    // memid = 0x78

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x78, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

@Override
public String toString() {
    return "<Window, super = " + super.toString() + ">";
}


}

