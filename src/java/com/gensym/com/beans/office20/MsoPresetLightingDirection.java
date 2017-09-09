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


public interface MsoPresetLightingDirection
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #16
    An enumeration type.
    Type info name is: MsoPresetLightingDirection
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_PRESET_LIGHTING_DIRECTION_MIXED = -2;

  public static final int MSO_LIGHTING_TOP_LEFT = 1;

  public static final int MSO_LIGHTING_TOP = 2;

  public static final int MSO_LIGHTING_TOP_RIGHT = 3;

  public static final int MSO_LIGHTING_LEFT = 4;

  public static final int MSO_LIGHTING_NONE = 5;

  public static final int MSO_LIGHTING_RIGHT = 6;

  public static final int MSO_LIGHTING_BOTTOM_LEFT = 7;

  public static final int MSO_LIGHTING_BOTTOM = 8;

  public static final int MSO_LIGHTING_BOTTOM_RIGHT = 9;


}

