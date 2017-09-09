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


public interface MsoBlackWhiteMode
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #40
    An enumeration type.
    Type info name is: MsoBlackWhiteMode
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_BLACK_WHITE_MIXED = -2;

  public static final int MSO_BLACK_WHITE_AUTOMATIC = 1;

  public static final int MSO_BLACK_WHITE_GRAY_SCALE = 2;

  public static final int MSO_BLACK_WHITE_LIGHT_GRAY_SCALE = 3;

  public static final int MSO_BLACK_WHITE_INVERSE_GRAY_SCALE = 4;

  public static final int MSO_BLACK_WHITE_GRAY_OUTLINE = 5;

  public static final int MSO_BLACK_WHITE_BLACK_TEXT_AND_LINE = 6;

  public static final int MSO_BLACK_WHITE_HIGH_CONTRAST = 7;

  public static final int MSO_BLACK_WHITE_BLACK = 8;

  public static final int MSO_BLACK_WHITE_WHITE = 9;

  public static final int MSO_BLACK_WHITE_DONT_SHOW = 10;


}

