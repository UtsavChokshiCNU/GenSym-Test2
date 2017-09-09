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


public interface XlParameterDataType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #161
    An enumeration type.
    Type info name is: XlParameterDataType
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_PARAM_TYPE_UNKNOWN = 0;

  public static final int XL_PARAM_TYPE_CHAR = 1;

  public static final int XL_PARAM_TYPE_NUMERIC = 2;

  public static final int XL_PARAM_TYPE_DECIMAL = 3;

  public static final int XL_PARAM_TYPE_INTEGER = 4;

  public static final int XL_PARAM_TYPE_SMALL_INT = 5;

  public static final int XL_PARAM_TYPE_FLOAT = 6;

  public static final int XL_PARAM_TYPE_REAL = 7;

  public static final int XL_PARAM_TYPE_DOUBLE = 8;

  public static final int XL_PARAM_TYPE_VAR_CHAR = 12;

  public static final int XL_PARAM_TYPE_DATE = 9;

  public static final int XL_PARAM_TYPE_TIME = 10;

  public static final int XL_PARAM_TYPE_TIMESTAMP = 11;

  public static final int XL_PARAM_TYPE_LONG_VAR_CHAR = -1;

  public static final int XL_PARAM_TYPE_BINARY = -2;

  public static final int XL_PARAM_TYPE_VAR_BINARY = -3;

  public static final int XL_PARAM_TYPE_LONG_VAR_BINARY = -4;

  public static final int XL_PARAM_TYPE_BIG_INT = -5;

  public static final int XL_PARAM_TYPE_TINY_INT = -6;

  public static final int XL_PARAM_TYPE_BIT = -7;


}

