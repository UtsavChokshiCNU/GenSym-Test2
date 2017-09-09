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


public interface XlChartItem
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #55
    An enumeration type.
    Type info name is: XlChartItem
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_DATA_LABEL = 0;

  public static final int XL_CHART_AREA = 2;

  public static final int XL_SERIES = 3;

  public static final int XL_CHART_TITLE = 4;

  public static final int XL_WALLS = 5;

  public static final int XL_CORNERS = 6;

  public static final int XL_DATA_TABLE = 7;

  public static final int XL_TRENDLINE = 8;

  public static final int XL_ERROR_BARS = 9;

  public static final int XL_X_ERROR_BARS = 10;

  public static final int XL_Y_ERROR_BARS = 11;

  public static final int XL_LEGEND_ENTRY = 12;

  public static final int XL_LEGEND_KEY = 13;

  public static final int XL_SHAPE = 14;

  public static final int XL_MAJOR_GRIDLINES = 15;

  public static final int XL_MINOR_GRIDLINES = 16;

  public static final int XL_AXIS_TITLE = 17;

  public static final int XL_UP_BARS = 18;

  public static final int XL_PLOT_AREA = 19;

  public static final int XL_DOWN_BARS = 20;

  public static final int XL_AXIS = 21;

  public static final int XL_SERIES_LINES = 22;

  public static final int XL_FLOOR = 23;

  public static final int XL_LEGEND = 24;

  public static final int XL_HI_LO_LINES = 25;

  public static final int XL_DROP_LINES = 26;

  public static final int XL_RADAR_AXIS_LABELS = 27;

  public static final int XL_NOTHING = 28;

  public static final int XL_LEADER_LINES = 29;


}

