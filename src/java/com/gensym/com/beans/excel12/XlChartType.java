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


public interface XlChartType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #54
    An enumeration type.
    Type info name is: XlChartType
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_COLUMN_CLUSTERED = 51;

  public static final int XL_COLUMN_STACKED = 52;

  public static final int XL_COLUMN_STACKED100 = 53;

  public static final int XL3_D_COLUMN_CLUSTERED = 54;

  public static final int XL3_D_COLUMN_STACKED = 55;

  public static final int XL3_D_COLUMN_STACKED100 = 56;

  public static final int XL_BAR_CLUSTERED = 57;

  public static final int XL_BAR_STACKED = 58;

  public static final int XL_BAR_STACKED100 = 59;

  public static final int XL3_D_BAR_CLUSTERED = 60;

  public static final int XL3_D_BAR_STACKED = 61;

  public static final int XL3_D_BAR_STACKED100 = 62;

  public static final int XL_LINE_STACKED = 63;

  public static final int XL_LINE_STACKED100 = 64;

  public static final int XL_LINE_MARKERS = 65;

  public static final int XL_LINE_MARKERS_STACKED = 66;

  public static final int XL_LINE_MARKERS_STACKED100 = 67;

  public static final int XL_PIE_OF_PIE = 68;

  public static final int XL_PIE_EXPLODED = 69;

  public static final int XL3_D_PIE_EXPLODED = 70;

  public static final int XL_BAR_OF_PIE = 71;

  public static final int XL_XY_SCATTER_SMOOTH = 72;

  public static final int XL_XY_SCATTER_SMOOTH_NO_MARKERS = 73;

  public static final int XL_XY_SCATTER_LINES = 74;

  public static final int XL_XY_SCATTER_LINES_NO_MARKERS = 75;

  public static final int XL_AREA_STACKED = 76;

  public static final int XL_AREA_STACKED100 = 77;

  public static final int XL3_D_AREA_STACKED = 78;

  public static final int XL3_D_AREA_STACKED100 = 79;

  public static final int XL_DOUGHNUT_EXPLODED = 80;

  public static final int XL_RADAR_MARKERS = 81;

  public static final int XL_RADAR_FILLED = 82;

  public static final int XL_SURFACE = 83;

  public static final int XL_SURFACE_WIREFRAME = 84;

  public static final int XL_SURFACE_TOP_VIEW = 85;

  public static final int XL_SURFACE_TOP_VIEW_WIREFRAME = 86;

  public static final int XL_BUBBLE = 15;

  public static final int XL_BUBBLE3D_EFFECT = 87;

  public static final int XL_STOCKHLC = 88;

  public static final int XL_STOCKOHLC = 89;

  public static final int XL_STOCKVHLC = 90;

  public static final int XL_STOCKVOHLC = 91;

  public static final int XL_CYLINDER_COL_CLUSTERED = 92;

  public static final int XL_CYLINDER_COL_STACKED = 93;

  public static final int XL_CYLINDER_COL_STACKED100 = 94;

  public static final int XL_CYLINDER_BAR_CLUSTERED = 95;

  public static final int XL_CYLINDER_BAR_STACKED = 96;

  public static final int XL_CYLINDER_BAR_STACKED100 = 97;

  public static final int XL_CYLINDER_COL = 98;

  public static final int XL_CONE_COL_CLUSTERED = 99;

  public static final int XL_CONE_COL_STACKED = 100;

  public static final int XL_CONE_COL_STACKED100 = 101;

  public static final int XL_CONE_BAR_CLUSTERED = 102;

  public static final int XL_CONE_BAR_STACKED = 103;

  public static final int XL_CONE_BAR_STACKED100 = 104;

  public static final int XL_CONE_COL = 105;

  public static final int XL_PYRAMID_COL_CLUSTERED = 106;

  public static final int XL_PYRAMID_COL_STACKED = 107;

  public static final int XL_PYRAMID_COL_STACKED100 = 108;

  public static final int XL_PYRAMID_BAR_CLUSTERED = 109;

  public static final int XL_PYRAMID_BAR_STACKED = 110;

  public static final int XL_PYRAMID_BAR_STACKED100 = 111;

  public static final int XL_PYRAMID_COL = 112;

  public static final int XL3_D_COLUMN = -4100;

  public static final int XL_LINE = 4;

  public static final int XL3_D_LINE = -4101;

  public static final int XL3_D_PIE = -4102;

  public static final int XL_PIE = 5;

  public static final int XL_XY_SCATTER = -4169;

  public static final int XL3_D_AREA = -4098;

  public static final int XL_AREA = 1;

  public static final int XL_DOUGHNUT = -4120;

  public static final int XL_RADAR = -4151;


}

