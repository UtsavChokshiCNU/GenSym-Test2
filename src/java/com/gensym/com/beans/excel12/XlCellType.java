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


public interface XlCellType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #94
    An enumeration type.
    Type info name is: XlCellType
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_CELL_TYPE_BLANKS = 4;

  public static final int XL_CELL_TYPE_CONSTANTS = 2;

  public static final int XL_CELL_TYPE_FORMULAS = -4123;

  public static final int XL_CELL_TYPE_LAST_CELL = 11;

  public static final int XL_CELL_TYPE_COMMENTS = -4144;

  public static final int XL_CELL_TYPE_VISIBLE = 12;

  public static final int XL_CELL_TYPE_ALL_FORMAT_CONDITIONS = -4172;

  public static final int XL_CELL_TYPE_SAME_FORMAT_CONDITIONS = -4173;

  public static final int XL_CELL_TYPE_ALL_VALIDATION = -4174;

  public static final int XL_CELL_TYPE_SAME_VALIDATION = -4175;


}

