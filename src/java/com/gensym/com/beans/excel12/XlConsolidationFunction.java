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


public interface XlConsolidationFunction
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #60
    An enumeration type.
    Type info name is: XlConsolidationFunction
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_AVERAGE = -4106;

  public static final int XL_COUNT = -4112;

  public static final int XL_COUNT_NUMS = -4113;

  public static final int XL_MAX = -4136;

  public static final int XL_MIN = -4139;

  public static final int XL_PRODUCT = -4149;

  public static final int XL_ST_DEV = -4155;

  public static final int XL_ST_DEVP = -4156;

  public static final int XL_SUM = -4157;

  public static final int XL_VAR = -4164;

  public static final int XL_VARP = -4165;


}

