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


public interface XlPictureConvertorType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #47
    An enumeration type.
    Type info name is: XlPictureConvertorType
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_BMP = 1;

  public static final int XL_CGM = 7;

  public static final int XL_DRW = 4;

  public static final int XL_DXF = 5;

  public static final int XL_EPS = 8;

  public static final int XL_HGL = 6;

  public static final int XL_PCT = 13;

  public static final int XL_PCX = 10;

  public static final int XL_PIC = 11;

  public static final int XL_PLT = 12;

  public static final int XL_TIF = 9;

  public static final int XL_WMF = 2;

  public static final int XL_WPG = 3;


}

