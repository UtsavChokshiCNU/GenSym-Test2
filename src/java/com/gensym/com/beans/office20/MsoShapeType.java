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


public interface MsoShapeType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #32
    An enumeration type.
    Type info name is: MsoShapeType
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_SHAPE_TYPE_MIXED = -2;

  public static final int MSO_AUTO_SHAPE = 1;

  public static final int MSO_CALLOUT = 2;

  public static final int MSO_CHART = 3;

  public static final int MSO_COMMENT = 4;

  public static final int MSO_FREEFORM = 5;

  public static final int MSO_GROUP = 6;

  public static final int MSO_EMBEDDEDOLE_OBJECT = 7;

  public static final int MSO_FORM_CONTROL = 8;

  public static final int MSO_LINE = 9;

  public static final int MSO_LINKEDOLE_OBJECT = 10;

  public static final int MSO_LINKED_PICTURE = 11;

  public static final int MSO_OLE_CONTROL_OBJECT = 12;

  public static final int MSO_PICTURE = 13;

  public static final int MSO_PLACEHOLDER = 14;

  public static final int MSO_TEXT_EFFECT = 15;

  public static final int MSO_MEDIA = 16;

  public static final int MSO_TEXT_BOX = 17;


}

