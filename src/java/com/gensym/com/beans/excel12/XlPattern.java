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


public interface XlPattern
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #48
    An enumeration type.
    Type info name is: XlPattern
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_PATTERN_AUTOMATIC = -4105;

  public static final int XL_PATTERN_CHECKER = 9;

  public static final int XL_PATTERN_CRISS_CROSS = 16;

  public static final int XL_PATTERN_DOWN = -4121;

  public static final int XL_PATTERN_GRAY16 = 17;

  public static final int XL_PATTERN_GRAY25 = -4124;

  public static final int XL_PATTERN_GRAY50 = -4125;

  public static final int XL_PATTERN_GRAY75 = -4126;

  public static final int XL_PATTERN_GRAY8 = 18;

  public static final int XL_PATTERN_GRID = 15;

  public static final int XL_PATTERN_HORIZONTAL = -4128;

  public static final int XL_PATTERN_LIGHT_DOWN = 13;

  public static final int XL_PATTERN_LIGHT_HORIZONTAL = 11;

  public static final int XL_PATTERN_LIGHT_UP = 14;

  public static final int XL_PATTERN_LIGHT_VERTICAL = 12;

  public static final int XL_PATTERN_NONE = -4142;

  public static final int XL_PATTERN_SEMI_GRAY75 = 10;

  public static final int XL_PATTERN_SOLID = 1;

  public static final int XL_PATTERN_UP = -4162;

  public static final int XL_PATTERN_VERTICAL = -4166;


}

