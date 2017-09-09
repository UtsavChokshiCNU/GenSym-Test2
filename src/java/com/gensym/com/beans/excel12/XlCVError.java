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


public interface XlCVError
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #91
    An enumeration type.
    Type info name is: XlCVError
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_ERR_DIV0 = 2007;

  public static final int XL_ERRNA = 2042;

  public static final int XL_ERR_NAME = 2029;

  public static final int XL_ERR_NULL = 2000;

  public static final int XL_ERR_NUM = 2036;

  public static final int XL_ERR_REF = 2023;

  public static final int XL_ERR_VALUE = 2015;


}

