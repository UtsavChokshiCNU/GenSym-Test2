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


public class Shape extends com.gensym.com.ActiveXDispatchableImpl
{
  private static Guid classID =
    new Guid(0x24439, 0x0, 0x0,
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

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #508
    A set of methods and properties that are accessible through IDispatch::Invoke.
    Type info name is: Shape
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    Type Info contains 81 functions.
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

  public void Apply ()
    throws ActiveXException {
    // memid = 0x68b

    Vector args = new Vector(0);
    axInvoke(0x68b, AX_INVOKE, true, args);
  }

  public void Delete ()
    throws ActiveXException {
    // memid = 0x75

    Vector args = new Vector(0);
    axInvoke(0x75, AX_INVOKE, true, args);
  }

  public Shape Duplicate ()
    throws ActiveXException {
    // memid = 0x40f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x40f, AX_INVOKE, false, args);
    Shape result = new Shape(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void Flip (int param1)
    throws ActiveXException {
    // memid = 0x68c

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x68c, AX_INVOKE, true, args);
  }

  public void IncrementLeft (float param1)
    throws ActiveXException {
    // memid = 0x68e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x68e, AX_INVOKE, true, args);
  }

  public void IncrementRotation (float param1)
    throws ActiveXException {
    // memid = 0x690

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x690, AX_INVOKE, true, args);
  }

  public void IncrementTop (float param1)
    throws ActiveXException {
    // memid = 0x691

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x691, AX_INVOKE, true, args);
  }

  public void PickUp ()
    throws ActiveXException {
    // memid = 0x692

    Vector args = new Vector(0);
    axInvoke(0x692, AX_INVOKE, true, args);
  }

  public void RerouteConnections ()
    throws ActiveXException {
    // memid = 0x693

    Vector args = new Vector(0);
    axInvoke(0x693, AX_INVOKE, true, args);
  }

  public void ScaleHeight (float param1, int param2)
    throws ActiveXException {
    // memid = 0x694

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x694, AX_INVOKE, true, args);
  }

  public void ScaleHeight (float param1, int param2, Variant param3)
    throws ActiveXException {
    // memid = 0x694

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x694, AX_INVOKE, true, args);
  }

  public void ScaleWidth (float param1, int param2)
    throws ActiveXException {
    // memid = 0x698

    Vector args = new Vector(2);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    axInvoke(0x698, AX_INVOKE, true, args);
  }

  public void ScaleWidth (float param1, int param2, Variant param3)
    throws ActiveXException {
    // memid = 0x698

    Vector args = new Vector(3);
    args.addElement(new Variant(param1));
    args.addElement(new Variant(param2));
    args.addElement(param3);
    axInvoke(0x698, AX_INVOKE, true, args);
  }

  public void Select ()
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(0);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public void Select (Variant param1)
    throws ActiveXException {
    // memid = 0xeb

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xeb, AX_INVOKE, true, args);
  }

  public void SetShapesDefaultProperties ()
    throws ActiveXException {
    // memid = 0x699

    Vector args = new Vector(0);
    axInvoke(0x699, AX_INVOKE, true, args);
  }

  public ShapeRange Ungroup ()
    throws ActiveXException {
    // memid = 0xf4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0xf4, AX_INVOKE, false, args);
    ShapeRange result = new ShapeRange(vResult.getActiveXDispatchableValue());
    return result;
  }

  public void ZOrder (int param1)
    throws ActiveXException {
    // memid = 0x26e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x26e, AX_INVOKE, true, args);
  }

  public Adjustments getAxAdjustments ()
    throws ActiveXException {
    // memid = 0x69b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69b, AX_PROPERTYGET, false, args);
    Adjustments result = new Adjustments(vResult.getActiveXDispatchableValue());
    return result;
  }

  public TextFrame getAxTextFrame ()
    throws ActiveXException {
    // memid = 0x69c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69c, AX_PROPERTYGET, false, args);
    TextFrame result = new TextFrame(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = MsoAutoShapeType
  public int getAxAutoShapeType ()
    throws ActiveXException {
    // memid = 0x69d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69d, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxAutoShapeType (int param1)
    throws ActiveXException {
    // memid = 0x69d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x69d, AX_PROPERTYSET, true, args);
  }

  public CalloutFormat getAxCallout ()
    throws ActiveXException {
    // memid = 0x69e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69e, AX_PROPERTYGET, false, args);
    CalloutFormat result = new CalloutFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public int getAxConnectionSiteCount ()
    throws ActiveXException {
    // memid = 0x69f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x69f, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoTriState
  public int getAxConnector ()
    throws ActiveXException {
    // memid = 0x6a0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public ConnectorFormat getAxConnectorFormat ()
    throws ActiveXException {
    // memid = 0x6a1

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a1, AX_PROPERTYGET, false, args);
    ConnectorFormat result = new ConnectorFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public FillFormat getAxFill ()
    throws ActiveXException {
    // memid = 0x67f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67f, AX_PROPERTYGET, false, args);
    FillFormat result = new FillFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public GroupShapes getAxGroupItems ()
    throws ActiveXException {
    // memid = 0x6a2

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a2, AX_PROPERTYGET, false, args);
    GroupShapes result = new GroupShapes(vResult.getActiveXDispatchableValue());
    return result;
  }

  public float getAxHeight ()
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7b, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxHeight (float param1)
    throws ActiveXException {
    // memid = 0x7b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7b, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoTriState
  public int getAxHorizontalFlip ()
    throws ActiveXException {
    // memid = 0x6a3

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a3, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public float getAxLeft ()
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7f, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxLeft (float param1)
    throws ActiveXException {
    // memid = 0x7f

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7f, AX_PROPERTYSET, true, args);
  }

  public LineFormat getAxLine ()
    throws ActiveXException {
    // memid = 0x331

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x331, AX_PROPERTYGET, false, args);
    LineFormat result = new LineFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = MsoTriState
  public int getAxLockAspectRatio ()
    throws ActiveXException {
    // memid = 0x6a4

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a4, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxLockAspectRatio (int param1)
    throws ActiveXException {
    // memid = 0x6a4

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6a4, AX_PROPERTYSET, true, args);
  }

  public String getAxName ()
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6e, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxName (String param1)
    throws ActiveXException {
    // memid = 0x6e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6e, AX_PROPERTYSET, true, args);
  }

  public ShapeNodes getAxNodes ()
    throws ActiveXException {
    // memid = 0x6a5

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a5, AX_PROPERTYGET, false, args);
    ShapeNodes result = new ShapeNodes(vResult.getActiveXDispatchableValue());
    return result;
  }

  public float getAxRotation ()
    throws ActiveXException {
    // memid = 0x3b

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x3b, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxRotation (float param1)
    throws ActiveXException {
    // memid = 0x3b

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x3b, AX_PROPERTYSET, true, args);
  }

  public PictureFormat getAxPictureFormat ()
    throws ActiveXException {
    // memid = 0x65f

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x65f, AX_PROPERTYGET, false, args);
    PictureFormat result = new PictureFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ShadowFormat getAxShadow ()
    throws ActiveXException {
    // memid = 0x67

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x67, AX_PROPERTYGET, false, args);
    ShadowFormat result = new ShadowFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public TextEffectFormat getAxTextEffect ()
    throws ActiveXException {
    // memid = 0x6a6

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a6, AX_PROPERTYGET, false, args);
    TextEffectFormat result = new TextEffectFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public ThreeDFormat getAxThreeD ()
    throws ActiveXException {
    // memid = 0x6a7

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a7, AX_PROPERTYGET, false, args);
    ThreeDFormat result = new ThreeDFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public float getAxTop ()
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7e, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxTop (float param1)
    throws ActiveXException {
    // memid = 0x7e

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7e, AX_PROPERTYSET, true, args);
  }

    // Enumeration type = MsoShapeType
  public int getAxType ()
    throws ActiveXException {
    // memid = 0x6c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6c, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

    // Enumeration type = MsoTriState
  public int getAxVerticalFlip ()
    throws ActiveXException {
    // memid = 0x6a8

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a8, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Variant getAxVertices ()
    throws ActiveXException {
    // memid = 0x26d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x26d, AX_PROPERTYGET, false, args);
    return vResult;
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

  public float getAxWidth ()
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x7a, AX_PROPERTYGET, false, args);
    float result = vResult.getFloatValue();
    return result;
  }

  public void setAxWidth (float param1)
    throws ActiveXException {
    // memid = 0x7a

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x7a, AX_PROPERTYSET, true, args);
  }

  public int getAxZOrderPosition ()
    throws ActiveXException {
    // memid = 0x6a9

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6a9, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public Hyperlink getAxHyperlink ()
    throws ActiveXException {
    // memid = 0x6aa

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6aa, AX_PROPERTYGET, false, args);
    Hyperlink result = new Hyperlink(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = MsoBlackWhiteMode
  public int getAxBlackWhiteMode ()
    throws ActiveXException {
    // memid = 0x6ab

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6ab, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxBlackWhiteMode (int param1)
    throws ActiveXException {
    // memid = 0x6ab

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x6ab, AX_PROPERTYSET, true, args);
  }

  public ActiveXDispatchable getAxDrawingObject ()
    throws ActiveXException {
    // memid = 0x6ac

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6ac, AX_PROPERTYGET, false, args);
    ActiveXDispatchable result = vResult.getActiveXDispatchableValue();
    return result;
  }

  public String getAxOnAction ()
    throws ActiveXException {
    // memid = 0x254

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x254, AX_PROPERTYGET, false, args);
    String result = vResult.getStringValue();
    return result;
  }

  public void setAxOnAction (String param1)
    throws ActiveXException {
    // memid = 0x254

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x254, AX_PROPERTYSET, true, args);
  }

  public boolean getAxLocked ()
    throws ActiveXException {
    // memid = 0x10d

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x10d, AX_PROPERTYGET, false, args);
    boolean result = vResult.getBooleanValue();
    return result;
  }

  public void setAxLocked (boolean param1)
    throws ActiveXException {
    // memid = 0x10d

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x10d, AX_PROPERTYSET, true, args);
  }

  public Range getAxTopLeftCell ()
    throws ActiveXException {
    // memid = 0x26c

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x26c, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

  public Range getAxBottomRightCell ()
    throws ActiveXException {
    // memid = 0x267

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x267, AX_PROPERTYGET, false, args);
    Range result = new Range(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlPlacement
  public int getAxPlacement ()
    throws ActiveXException {
    // memid = 0x269

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x269, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

  public void setAxPlacement (int param1)
    throws ActiveXException {
    // memid = 0x269

    Vector args = new Vector(1);
    args.addElement(new Variant(param1));
    axInvoke(0x269, AX_PROPERTYSET, true, args);
  }

  public void Copy ()
    throws ActiveXException {
    // memid = 0x227

    Vector args = new Vector(0);
    axInvoke(0x227, AX_INVOKE, true, args);
  }

  public void Cut ()
    throws ActiveXException {
    // memid = 0x235

    Vector args = new Vector(0);
    axInvoke(0x235, AX_INVOKE, true, args);
  }

  public void CopyPicture ()
    throws ActiveXException {
    // memid = 0xd5

    Vector args = new Vector(0);
    axInvoke(0xd5, AX_INVOKE, true, args);
  }

  public void CopyPicture (Variant param1)
    throws ActiveXException {
    // memid = 0xd5

    Vector args = new Vector(1);
    args.addElement(param1);
    axInvoke(0xd5, AX_INVOKE, true, args);
  }

  public void CopyPicture (Variant param1, Variant param2)
    throws ActiveXException {
    // memid = 0xd5

    Vector args = new Vector(2);
    args.addElement(param1);
    args.addElement(param2);
    axInvoke(0xd5, AX_INVOKE, true, args);
  }

  public ControlFormat getAxControlFormat ()
    throws ActiveXException {
    // memid = 0x6ad

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6ad, AX_PROPERTYGET, false, args);
    ControlFormat result = new ControlFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public LinkFormat getAxLinkFormat ()
    throws ActiveXException {
    // memid = 0x6ae

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6ae, AX_PROPERTYGET, false, args);
    LinkFormat result = new LinkFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

  public OLEFormat getAxOLEFormat ()
    throws ActiveXException {
    // memid = 0x6af

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6af, AX_PROPERTYGET, false, args);
    OLEFormat result = new OLEFormat(vResult.getActiveXDispatchableValue());
    return result;
  }

    // Enumeration type = XlFormControl
  public int getAxFormControlType ()
    throws ActiveXException {
    // memid = 0x6b0

    Vector args = new Vector(0);
    Variant vResult = axInvoke(0x6b0, AX_PROPERTYGET, false, args);
    int result = vResult.getIntValue();
    return result;
  }

@Override
public String toString() {
    return "<Shape, super = " + super.toString() + ">";
}


}

