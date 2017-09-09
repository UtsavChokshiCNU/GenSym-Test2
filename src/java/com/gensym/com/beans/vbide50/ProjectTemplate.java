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


public class ProjectTemplate extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xef404e22, 0xeda6, 0x101a,
             (short) 0x8d, (short) 0xaf, (short) 0x0, (short) 0xdd,
             (short) 0x1, (short) 0xf, (short) 0x7e, (short) 0xbb);

  public ProjectTemplate (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #44
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _ProjectTemplate
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 27 functions.
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

  public FormTemplate getAxActiveForm ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    FormTemplate result = new FormTemplate(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Application getAxApplication ()
    throws ActiveXException {
    // memid = 0x1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1, AX_PROPERTYGET, false, args);
    Application result = new Application(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Application getAxParent ()
    throws ActiveXException {
    // memid = 0x2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x2, AX_PROPERTYGET, false, args);
    Application result = new Application(vResult.getActiveXDispatchableValue());
    return result;
  }

  public SelectedComponents getAxSelectedComponents ()
    throws ActiveXException {
    // memid = 0x64

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64, AX_PROPERTYGET, false, args);
    SelectedComponents result = new SelectedComponents(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String AddFile (String param1)
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x65, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean RemoveComponent (Variant param1, boolean param2)
    throws ActiveXException {
    // memid = 0x66

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x66, AX_INVOKE, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void AddReference ()
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(0);
    axInvoke(0x67, AX_INVOKE, true, args);
  }

  public void AddReference (Variant param1)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x67, AX_INVOKE, true, args);
  }

  public void AddReference (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0x67, AX_INVOKE, true, args);
  }

  public void AddReference (Variant param1, Variant param2, Variant param3)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(3);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    axInvoke(0x67, AX_INVOKE, true, args);
  }

  public void AddReference (Variant param1, Variant param2, Variant param3, Variant param4)
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(4);
    args.addElement(param1);
    args.addElement(param2);
    args.addElement(param3);
    args.addElement(param4);
    axInvoke(0x67, AX_INVOKE, true, args);
  }

  public void AddToolboxTypelib (String param1, short param2, short param3)
    throws ActiveXException {
    // memid = 0x68

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x68, AX_INVOKE, true, args);
  }

  public void AddToolboxTypelib (String param1, short param2, short param3, Variant param4)
    throws ActiveXException {
    // memid = 0x68

    Vector args = new Vector(4);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    args.addElement(param4);
    axInvoke(0x68, AX_INVOKE, true, args);
  }

  public void AddToolboxProgID (String param1)
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x69, AX_INVOKE, true, args);
  }

  public void AddToolboxProgID (String param1, Variant param2)
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(param2);
    axInvoke(0x69, AX_INVOKE, true, args);
  }

  public void AddToolboxVBX (String param1)
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6a, AX_INVOKE, true, args);
  }

  public FormTemplate AddFormTemplate ()
    throws ActiveXException {
    // memid = 0x6b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6b, AX_INVOKE, false, args);
    FormTemplate result = new FormTemplate(vResult.getActiveXDispatchableValue());
    return result;
  }

  public FormTemplate AddMDIFormTemplate ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_INVOKE, false, args);
    FormTemplate result = new FormTemplate(vResult.getActiveXDispatchableValue());
    return result;
  }

  public String getAxFileName ()
    throws ActiveXException {
    // memid = 0x6d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxIsDirty ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxIsDirty (boolean param1)
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6e, AX_PROPERTYSET, true, args);
  }

  public void WriteProperty (String param1, String param2, String param3)
    throws ActiveXException {
    // memid = 0x6f

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x6f, AX_INVOKE, true, args);
  }

  public String ReadProperty (String param1, String param2)
    throws ActiveXException {
    // memid = 0x70

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    Variant vResult = axInvoke(0x70, AX_INVOKE, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public int ConnectEvents (ActiveXDispatchable param1)
    throws ActiveXException {
    // memid = 0x71

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    Variant vResult = axInvoke(0x71, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void DisconnectEvents (int param1)
    throws ActiveXException {
    // memid = 0x72

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x72, AX_INVOKE, true, args);
  }

  public Variant getAxComponents ()
    throws ActiveXException {
    // memid = 0x73

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x73, AX_PROPERTYGET, false, args);
    return vResult;
  }

@Override
public String toString() {
    return "<ProjectTemplate, super = " + super.toString() + ">";
}


}

