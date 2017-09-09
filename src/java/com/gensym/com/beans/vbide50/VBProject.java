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


public class VBProject extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x2e106, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public VBProject (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #51
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: _VBProject
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    Type Info contains 38 functions.
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

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x0, AX_PROPERTYSET, true, args);
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

  public String getAxHelpFile ()
    throws ActiveXException {
    // memid = 0x74

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x74, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxHelpFile (String param1)
    throws ActiveXException {
    // memid = 0x74

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x74, AX_PROPERTYSET, true, args);
  }

  public int getAxHelpContextID ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x75, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxHelpContextID (int param1)
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x75, AX_PROPERTYSET, true, args);
  }

  public String getAxDescription ()
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x76, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxDescription (String param1)
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x76, AX_PROPERTYSET, true, args);
  }

  public Variant getAxReferences ()
    throws ActiveXException {
    // memid = 0x78

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x78, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public VBE getAxVBE ()
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7a, AX_PROPERTYGET, false, args);
    VBE result = new VBE(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Variant getAxCollection ()
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7b, AX_PROPERTYGET, false, args);
    return vResult;
  }

    // Enumeration type = vbextProjectStartMode
  public int getAxStartMode ()
    throws ActiveXException {
    // memid = 0x7d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxStartMode (int param1)
    throws ActiveXException {
    // memid = 0x7d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7d, AX_PROPERTYSET, true, args);
  }

  public String getAxCompatibleOleServer ()
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxCompatibleOleServer (String param1)
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7e, AX_PROPERTYSET, true, args);
  }

  public void SaveAs (String param1)
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7f, AX_INVOKE, true, args);
  }

  public void MakeCompiledFile ()
    throws ActiveXException {
    // memid = 0x80

    Vector args = new Vector(0);
    axInvoke(0x80, AX_INVOKE, true, args);
  }

    // Enumeration type = vbextProjectType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x81, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxType (int param1)
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x81, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = vbextSCCStatus
  public int getAxIconState ()
    throws ActiveXException {
    // memid = 0x82

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x82, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxIconState (int param1)
    throws ActiveXException {
    // memid = 0x82

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x82, AX_PROPERTYSET, true, args);
  }

  public boolean getAxSaved ()
    throws ActiveXException {
    // memid = 0x85

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x85, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public Variant getAxVBComponents ()
    throws ActiveXException {
    // memid = 0x87

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x87, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public String getAxBuildFileName ()
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x88, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxBuildFileName (String param1)
    throws ActiveXException {
    // memid = 0x88

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x88, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<VBProject, super = " + super.toString() + ">";
}


}

