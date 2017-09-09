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


public class Shape extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0xc031c, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

  public Shape (ActiveXDispatchable axDispatch) throws ActiveXCastException
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

/* Type info #91
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Shape
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
    // memid = 0x1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x1, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public void Apply ()
    throws ActiveXException {
    // memid = 0xa

    Vector args = new Vector(0);
    axInvoke(0xa, AX_INVOKE, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0xb

    Vector args = new Vector(0);
    axInvoke(0xb, AX_INVOKE, true, args);
  }

  public Shape Duplicate ()
    throws ActiveXException {
    // memid = 0xc

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xc, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Flip (int param1)
    throws ActiveXException {
    // memid = 0xd

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xd, AX_INVOKE, true, args);
  }

  public void IncrementLeft (float param1)
    throws ActiveXException {
    // memid = 0xe

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xe, AX_INVOKE, true, args);
  }

  public void IncrementRotation (float param1)
    throws ActiveXException {
    // memid = 0xf

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0xf, AX_INVOKE, true, args);
  }

  public void IncrementTop (float param1)
    throws ActiveXException {
    // memid = 0x10

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x10, AX_INVOKE, true, args);
  }

  public void PickUp ()
    throws ActiveXException {
    // memid = 0x11

    Vector args = new Vector(0);
    axInvoke(0x11, AX_INVOKE, true, args);
  }

  public void RerouteConnections ()
    throws ActiveXException {
    // memid = 0x12

    Vector args = new Vector(0);
    axInvoke(0x12, AX_INVOKE, true, args);
  }

  public void ScaleHeight (float param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0x13

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x13, AX_INVOKE, true, args);
  }

  public void ScaleWidth (float param1, int param2, int param3)
    throws ActiveXException {
    // memid = 0x14

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(new Variant(param3));
    axInvoke(0x14, AX_INVOKE, true, args);
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0x15

    Vector args = new Vector(0);
    axInvoke(0x15, AX_INVOKE, true, args);
  }

  public void Select (Variant param1)
    throws ActiveXException {
    // memid = 0x15

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0x15, AX_INVOKE, true, args);
  }

  public void SetShapesDefaultProperties ()
    throws ActiveXException {
    // memid = 0x16

    Vector args = new Vector(0);
    axInvoke(0x16, AX_INVOKE, true, args);
  }

  public ShapeRange Ungroup ()
    throws ActiveXException {
    // memid = 0x17

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x17, AX_INVOKE, false, args);
    ShapeRange result = new ShapeRange(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void ZOrder (int param1)
    throws ActiveXException {
    // memid = 0x18

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x18, AX_INVOKE, true, args);
  }

  public Adjustments getAxAdjustments ()
    throws ActiveXException {
    // memid = 0x64

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x64, AX_PROPERTYGET, false, args);
    Adjustments result = new Adjustments(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = MsoAutoShapeType
  public int getAxAutoShapeType ()
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x65, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxAutoShapeType (int param1)
    throws ActiveXException {
    // memid = 0x65

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x65, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoBlackWhiteMode
  public int getAxBlackWhiteMode ()
    throws ActiveXException {
    // memid = 0x66

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x66, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxBlackWhiteMode (int param1)
    throws ActiveXException {
    // memid = 0x66

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x66, AX_PROPERTYSET, true, args);
  }

  public CalloutFormat getAxCallout ()
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67, AX_PROPERTYGET, false, args);
    CalloutFormat result = new CalloutFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxConnectionSiteCount ()
    throws ActiveXException {
    // memid = 0x68

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x68, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoTriState
  public int getAxConnector ()
    throws ActiveXException {
    // memid = 0x69

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ConnectorFormat getAxConnectorFormat ()
    throws ActiveXException {
    // memid = 0x6a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a, AX_PROPERTYGET, false, args);
    ConnectorFormat result = new ConnectorFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public FillFormat getAxFill ()
    throws ActiveXException {
    // memid = 0x6b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6b, AX_PROPERTYGET, false, args);
    FillFormat result = new FillFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public GroupShapes getAxGroupItems ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    GroupShapes result = new GroupShapes(vResult.getActiveXDispatchableValue());
    return result;
  }

  public float getAxHeight ()
    throws ActiveXException {
    // memid = 0x6d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6d, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxHeight (float param1)
    throws ActiveXException {
    // memid = 0x6d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6d, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoTriState
  public int getAxHorizontalFlip ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public float getAxLeft ()
    throws ActiveXException {
    // memid = 0x6f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6f, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxLeft (float param1)
    throws ActiveXException {
    // memid = 0x6f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6f, AX_PROPERTYSET, true, args);
  }

  public LineFormat getAxLine ()
    throws ActiveXException {
    // memid = 0x70

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x70, AX_PROPERTYGET, false, args);
    LineFormat result = new LineFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = MsoTriState
  public int getAxLockAspectRatio ()
    throws ActiveXException {
    // memid = 0x71

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x71, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxLockAspectRatio (int param1)
    throws ActiveXException {
    // memid = 0x71

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x71, AX_PROPERTYSET, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x73

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x73, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x73

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x73, AX_PROPERTYSET, true, args);
  }

  public ShapeNodes getAxNodes ()
    throws ActiveXException {
    // memid = 0x74

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x74, AX_PROPERTYGET, false, args);
    ShapeNodes result = new ShapeNodes(vResult.getActiveXDispatchableValue());
    return result;
  }

  public float getAxRotation ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x75, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxRotation (float param1)
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x75, AX_PROPERTYSET, true, args);
  }

  public PictureFormat getAxPictureFormat ()
    throws ActiveXException {
    // memid = 0x76

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x76, AX_PROPERTYGET, false, args);
    PictureFormat result = new PictureFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ShadowFormat getAxShadow ()
    throws ActiveXException {
    // memid = 0x77

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x77, AX_PROPERTYGET, false, args);
    ShadowFormat result = new ShadowFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public TextEffectFormat getAxTextEffect ()
    throws ActiveXException {
    // memid = 0x78

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x78, AX_PROPERTYGET, false, args);
    TextEffectFormat result = new TextEffectFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public TextFrame getAxTextFrame ()
    throws ActiveXException {
    // memid = 0x79

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x79, AX_PROPERTYGET, false, args);
    TextFrame result = new TextFrame(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ThreeDFormat getAxThreeD ()
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7a, AX_PROPERTYGET, false, args);
    ThreeDFormat result = new ThreeDFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public float getAxTop ()
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7b, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxTop (float param1)
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoShapeType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x7c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoTriState
  public int getAxVerticalFlip ()
    throws ActiveXException {
    // memid = 0x7d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Variant getAxVertices ()
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7e, AX_PROPERTYGET, false, args);
    return vResult;
  }

    // Enumeration type = MsoTriState
  public int getAxVisible ()
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxVisible (int param1)
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7f, AX_PROPERTYSET, true, args);
  }

  public float getAxWidth ()
    throws ActiveXException {
    // memid = 0x80

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x80, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxWidth (float param1)
    throws ActiveXException {
    // memid = 0x80

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x80, AX_PROPERTYSET, true, args);
  }

  public int getAxZOrderPosition ()
    throws ActiveXException {
    // memid = 0x81

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x81, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

@Override
public String toString() {
    return "<Shape, super = " + super.toString() + ">";
}


}

