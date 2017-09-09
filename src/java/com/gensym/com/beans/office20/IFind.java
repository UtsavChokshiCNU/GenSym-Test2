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


public class IFind extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc0337, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public IFind (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #110
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: IFind
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    Type Info contains 55 functions.
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

  public String getAxSearchPath ()
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x0, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x60020001

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020001, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxSubDir ()
    throws ActiveXException {
    // memid = 0x60020002

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020002, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public String getAxTitle ()
    throws ActiveXException {
    // memid = 0x60020003

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020003, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxAuthor ()
    throws ActiveXException {
    // memid = 0x60020004

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020004, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxKeywords ()
    throws ActiveXException {
    // memid = 0x60020005

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020005, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public String getAxSubject ()
    throws ActiveXException {
    // memid = 0x60020006

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020006, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

    // Enumeration type = MsoFileFindOptions
  public int getAxOptions ()
    throws ActiveXException {
    // memid = 0x60020007

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020007, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public boolean getAxMatchCase ()
    throws ActiveXException {
    // memid = 0x60020008

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020008, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public String getAxText ()
    throws ActiveXException {
    // memid = 0x60020009

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020009, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public boolean getAxPatternMatch ()
    throws ActiveXException {
    // memid = 0x6002000a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002000a, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public Variant getAxDateSavedFrom ()
    throws ActiveXException {
    // memid = 0x6002000b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002000b, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxDateSavedTo ()
    throws ActiveXException {
    // memid = 0x6002000c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002000c, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public String getAxSavedBy ()
    throws ActiveXException {
    // memid = 0x6002000d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002000d, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public Variant getAxDateCreatedFrom ()
    throws ActiveXException {
    // memid = 0x6002000e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002000e, AX_PROPERTYGET, false, args);
    return vResult;
  }

  public Variant getAxDateCreatedTo ()
    throws ActiveXException {
    // memid = 0x6002000f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002000f, AX_PROPERTYGET, false, args);
    return vResult;
  }

    // Enumeration type = MsoFileFindView
  public int getAxView ()
    throws ActiveXException {
    // memid = 0x60020010

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020010, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoFileFindSortBy
  public int getAxSortBy ()
    throws ActiveXException {
    // memid = 0x60020011

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020011, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoFileFindListBy
  public int getAxListBy ()
    throws ActiveXException {
    // memid = 0x60020012

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020012, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public int getAxSelectedFile ()
    throws ActiveXException {
    // memid = 0x60020013

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020013, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public IFoundFiles getAxResults ()
    throws ActiveXException {
    // memid = 0x60020014

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020014, AX_PROPERTYGET, false, args);
    IFoundFiles result = new IFoundFiles(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int Show ()
    throws ActiveXException {
    // memid = 0x60020015

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x60020015, AX_INVOKE, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxSearchPath (String param1)
    throws ActiveXException {
    // memid = 0x0

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x0, AX_PROPERTYSET, true, args);
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x60020001

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020001, AX_PROPERTYSET, true, args);
  }

  public void setAxSubDir (boolean param1)
    throws ActiveXException {
    // memid = 0x60020002

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020002, AX_PROPERTYSET, true, args);
  }

  public void setAxTitle (String param1)
    throws ActiveXException {
    // memid = 0x60020003

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020003, AX_PROPERTYSET, true, args);
  }

  public void setAxAuthor (String param1)
    throws ActiveXException {
    // memid = 0x60020004

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020004, AX_PROPERTYSET, true, args);
  }

  public void setAxKeywords (String param1)
    throws ActiveXException {
    // memid = 0x60020005

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020005, AX_PROPERTYSET, true, args);
  }

  public void setAxSubject (String param1)
    throws ActiveXException {
    // memid = 0x60020006

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020006, AX_PROPERTYSET, true, args);
  }

  public void setAxOptions (int param1)
    throws ActiveXException {
    // memid = 0x60020007

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020007, AX_PROPERTYSET, true, args);
  }

  public void setAxMatchCase (boolean param1)
    throws ActiveXException {
    // memid = 0x60020008

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020008, AX_PROPERTYSET, true, args);
  }

  public void setAxText (String param1)
    throws ActiveXException {
    // memid = 0x60020009

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020009, AX_PROPERTYSET, true, args);
  }

  public void setAxPatternMatch (boolean param1)
    throws ActiveXException {
    // memid = 0x6002000a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6002000a, AX_PROPERTYSET, true, args);
  }

  public void setAxDateSavedFrom (Variant param1)
    throws ActiveXException {
    // memid = 0x6002000b

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6002000b, AX_PROPERTYSET, true, args);
  }

  public void setAxDateSavedTo (Variant param1)
    throws ActiveXException {
    // memid = 0x6002000c

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6002000c, AX_PROPERTYSET, true, args);
  }

  public void setAxSavedBy (String param1)
    throws ActiveXException {
    // memid = 0x6002000d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6002000d, AX_PROPERTYSET, true, args);
  }

  public void setAxDateCreatedFrom (Variant param1)
    throws ActiveXException {
    // memid = 0x6002000e

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6002000e, AX_PROPERTYSET, true, args);
  }

  public void setAxDateCreatedTo (Variant param1)
    throws ActiveXException {
    // memid = 0x6002000f

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x6002000f, AX_PROPERTYSET, true, args);
  }

  public void setAxView (int param1)
    throws ActiveXException {
    // memid = 0x60020010

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020010, AX_PROPERTYSET, true, args);
  }

  public void setAxSortBy (int param1)
    throws ActiveXException {
    // memid = 0x60020011

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020011, AX_PROPERTYSET, true, args);
  }

  public void setAxListBy (int param1)
    throws ActiveXException {
    // memid = 0x60020012

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020012, AX_PROPERTYSET, true, args);
  }

  public void setAxSelectedFile (int param1)
    throws ActiveXException {
    // memid = 0x60020013

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x60020013, AX_PROPERTYSET, true, args);
  }

  public void Execute ()
    throws ActiveXException {
    // memid = 0x6002002a

    Vector args = new Vector(0);
    axInvoke(0x6002002a, AX_INVOKE, true, args);
  }

  public void Load (String param1)
    throws ActiveXException {
    // memid = 0x6002002b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6002002b, AX_INVOKE, true, args);
  }

  public void Save (String param1)
    throws ActiveXException {
    // memid = 0x6002002c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6002002c, AX_INVOKE, true, args);
  }

  public void Delete (String param1)
    throws ActiveXException {
    // memid = 0x6002002d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6002002d, AX_INVOKE, true, args);
  }

  public int getAxFileType ()
    throws ActiveXException {
    // memid = 0x6002002e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6002002e, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxFileType (int param1)
    throws ActiveXException {
    // memid = 0x6002002e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6002002e, AX_PROPERTYSET, true, args);
  }

@Override
public String toString() {
    return "<IFind, super = " + super.toString() + ">";
}


}

