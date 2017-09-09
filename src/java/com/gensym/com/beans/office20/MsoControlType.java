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


public interface MsoControlType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #48
    An enumeration type.
    Type info name is: MsoControlType
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_CONTROL_CUSTOM = 0;

  public static final int MSO_CONTROL_BUTTON = 1;

  public static final int MSO_CONTROL_EDIT = 2;

  public static final int MSO_CONTROL_DROPDOWN = 3;

  public static final int MSO_CONTROL_COMBO_BOX = 4;

  public static final int MSO_CONTROL_BUTTON_DROPDOWN = 5;

  public static final int MSO_CONTROL_SPLIT_DROPDOWN = 6;

  public static final int MSO_CONTROLOCX_DROPDOWN = 7;

  public static final int MSO_CONTROL_GENERIC_DROPDOWN = 8;

  public static final int MSO_CONTROL_GRAPHIC_DROPDOWN = 9;

  public static final int MSO_CONTROL_POPUP = 10;

  public static final int MSO_CONTROL_GRAPHIC_POPUP = 11;

  public static final int MSO_CONTROL_BUTTON_POPUP = 12;

  public static final int MSO_CONTROL_SPLIT_BUTTON_POPUP = 13;

  public static final int MSO_CONTROL_SPLIT_BUTTONMRU_POPUP = 14;

  public static final int MSO_CONTROL_LABEL = 15;

  public static final int MSO_CONTROL_EXPANDING_GRID = 16;

  public static final int MSO_CONTROL_SPLIT_EXPANDING_GRID = 17;

  public static final int MSO_CONTROL_GRID = 18;

  public static final int MSO_CONTROL_GAUGE = 19;

  public static final int MSO_CONTROL_GRAPHIC_COMBO = 20;


}

