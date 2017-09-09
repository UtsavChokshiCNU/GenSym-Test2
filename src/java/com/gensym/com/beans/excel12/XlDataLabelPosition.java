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


public interface XlDataLabelPosition
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #50
    An enumeration type.
    Type info name is: XlDataLabelPosition
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_LABEL_POSITION_CENTER = -4108;

  public static final int XL_LABEL_POSITION_ABOVE = 0;

  public static final int XL_LABEL_POSITION_BELOW = 1;

  public static final int XL_LABEL_POSITION_LEFT = -4131;

  public static final int XL_LABEL_POSITION_RIGHT = -4152;

  public static final int XL_LABEL_POSITION_OUTSIDE_END = 2;

  public static final int XL_LABEL_POSITION_INSIDE_END = 3;

  public static final int XL_LABEL_POSITION_INSIDE_BASE = 4;

  public static final int XL_LABEL_POSITION_BEST_FIT = 5;

  public static final int XL_LABEL_POSITION_MIXED = 6;

  public static final int XL_LABEL_POSITION_CUSTOM = 7;


}

