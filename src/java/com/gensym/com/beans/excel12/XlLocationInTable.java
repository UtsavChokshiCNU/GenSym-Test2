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


public interface XlLocationInTable
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #62
    An enumeration type.
    Type info name is: XlLocationInTable
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_COLUMN_HEADER = -4110;

  public static final int XL_COLUMN_ITEM = 5;

  public static final int XL_DATA_HEADER = 3;

  public static final int XL_DATA_ITEM = 7;

  public static final int XL_PAGE_HEADER = 2;

  public static final int XL_PAGE_ITEM = 6;

  public static final int XL_ROW_HEADER = -4153;

  public static final int XL_ROW_ITEM = 4;

  public static final int XL_TABLE_BODY = 8;


}

