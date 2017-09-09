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


public interface XlPivotFieldCalculation
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #122
    An enumeration type.
    Type info name is: XlPivotFieldCalculation
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_DIFFERENCE_FROM = 2;

  public static final int XL_INDEX = 9;

  public static final int XL_NO_ADDITIONAL_CALCULATION = -4143;

  public static final int XL_PERCENT_DIFFERENCE_FROM = 4;

  public static final int XL_PERCENT_OF = 3;

  public static final int XL_PERCENT_OF_COLUMN = 7;

  public static final int XL_PERCENT_OF_ROW = 6;

  public static final int XL_PERCENT_OF_TOTAL = 8;

  public static final int XL_RUNNING_TOTAL = 5;


}

