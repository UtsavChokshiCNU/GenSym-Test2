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


public interface Constants
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #11
    An enumeration type.
    Type info name is: Constants
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_ALL = -4104;

  public static final int XL_AUTOMATIC = -4105;

  public static final int XL_BOTH = 1;

  public static final int XL_CENTER = -4108;

  public static final int XL_CHECKER = 9;

  public static final int XL_CIRCLE = 8;

  public static final int XL_CORNER = 2;

  public static final int XL_CRISS_CROSS = 16;

  public static final int XL_CROSS = 4;

  public static final int XL_DIAMOND = 2;

  public static final int XL_DISTRIBUTED = -4117;

  public static final int XL_DOUBLE_ACCOUNTING = 5;

  public static final int XL_FIXED_VALUE = 1;

  public static final int XL_FORMATS = -4122;

  public static final int XL_GRAY16 = 17;

  public static final int XL_GRAY8 = 18;

  public static final int XL_GRID = 15;

  public static final int XL_HIGH = -4127;

  public static final int XL_INSIDE = 2;

  public static final int XL_JUSTIFY = -4130;

  public static final int XL_LIGHT_DOWN = 13;

  public static final int XL_LIGHT_HORIZONTAL = 11;

  public static final int XL_LIGHT_UP = 14;

  public static final int XL_LIGHT_VERTICAL = 12;

  public static final int XL_LOW = -4134;

  public static final int XL_MANUAL = -4135;

  public static final int XL_MINUS_VALUES = 3;

  public static final int XL_MODULE = -4141;

  public static final int XL_NEXT_TO_AXIS = 4;

  public static final int XL_NONE = -4142;

  public static final int XL_NOTES = -4144;

  public static final int XL_OFF = -4146;

  public static final int XL_ON = 1;

  public static final int XL_PERCENT = 2;

  public static final int XL_PLUS = 9;

  public static final int XL_PLUS_VALUES = 2;

  public static final int XL_SEMI_GRAY75 = 10;

  public static final int XL_SHOW_LABEL = 4;

  public static final int XL_SHOW_LABEL_AND_PERCENT = 5;

  public static final int XL_SHOW_PERCENT = 3;

  public static final int XL_SHOW_VALUE = 2;

  public static final int XL_SIMPLE = -4154;

  public static final int XL_SINGLE = 2;

  public static final int XL_SINGLE_ACCOUNTING = 4;

  public static final int XL_SOLID = 1;

  public static final int XL_SQUARE = 1;

  public static final int XL_STAR = 5;

  public static final int XL_ST_ERROR = 4;

  public static final int XL_TOOLBAR_BUTTON = 2;

  public static final int XL_TRIANGLE = 3;

  public static final int XL_GRAY25 = -4124;

  public static final int XL_GRAY50 = -4125;

  public static final int XL_GRAY75 = -4126;

  public static final int XL_BOTTOM = -4107;

  public static final int XL_LEFT = -4131;

  public static final int XL_RIGHT = -4152;

  public static final int XL_TOP = -4160;

  public static final int XL3_D_BAR = -4099;

  public static final int XL3_D_SURFACE = -4103;

  public static final int XL_BAR = 2;

  public static final int XL_COLUMN = 3;

  public static final int XL_COMBINATION = -4111;

  public static final int XL_CUSTOM = -4114;

  public static final int XL_DEFAULT_AUTO_FORMAT = -1;

  public static final int XL_MAXIMUM = 2;

  public static final int XL_MINIMUM = 4;

  public static final int XL_OPAQUE = 3;

  public static final int XL_TRANSPARENT = 2;

  public static final int XL_BIDI = -5000;

  public static final int XL_LATIN = -5001;

  public static final int XL_CONTEXT = -5002;

  public static final int XL_LTR = -5003;

  public static final int XL_RTL = -5004;

  public static final int XL_VISUAL_CURSOR = 2;

  public static final int XL_LOGICAL_CURSOR = 1;

  public static final int XL_SYSTEM = 1;

  public static final int XL_PARTIAL = 3;

  public static final int XL_HINDI_NUMERALS = 3;

  public static final int XL_BIDI_CALENDAR = 3;

  public static final int XL_GREGORIAN = 2;

  public static final int XL_COMPLETE = 4;

  public static final int XL_SCALE = 3;

  public static final int XL_CLOSED = 3;

  public static final int XL_COLOR1 = 7;

  public static final int XL_COLOR2 = 8;

  public static final int XL_COLOR3 = 9;

  public static final int XL_CONSTANTS = 2;

  public static final int XL_CONTENTS = 2;

  public static final int XL_BELOW = 1;

  public static final int XL_CASCADE = 7;

  public static final int XL_CENTER_ACROSS_SELECTION = 7;

  public static final int XL_CHART4 = 2;

  public static final int XL_CHART_SERIES = 17;

  public static final int XL_CHART_SHORT = 6;

  public static final int XL_CHART_TITLES = 18;

  public static final int XL_CLASSIC1 = 1;

  public static final int XL_CLASSIC2 = 2;

  public static final int XL_CLASSIC3 = 3;

  public static final int XL3_D_EFFECTS1 = 13;

  public static final int XL3_D_EFFECTS2 = 14;

  public static final int XL_ABOVE = 0;

  public static final int XL_ACCOUNTING1 = 4;

  public static final int XL_ACCOUNTING2 = 5;

  public static final int XL_ACCOUNTING3 = 6;

  public static final int XL_ACCOUNTING4 = 17;

  public static final int XL_ADD = 2;

  public static final int XL_DEBUG_CODE_PANE = 13;

  public static final int XL_DESKTOP = 9;

  public static final int XL_DIRECT = 1;

  public static final int XL_DIVIDE = 5;

  public static final int XL_DOUBLE_CLOSED = 5;

  public static final int XL_DOUBLE_OPEN = 4;

  public static final int XL_DOUBLE_QUOTE = 1;

  public static final int XL_ENTIRE_CHART = 20;

  public static final int XL_EXCEL_MENUS = 1;

  public static final int XL_EXTENDED = 3;

  public static final int XL_FILL = 5;

  public static final int XL_FIRST = 0;

  public static final int XL_FLOATING = 5;

  public static final int XL_FORMULA = 5;

  public static final int XL_GENERAL = 1;

  public static final int XL_GRIDLINE = 22;

  public static final int XL_ICONS = 1;

  public static final int XL_IMMEDIATE_PANE = 12;

  public static final int XL_INTEGER = 2;

  public static final int XL_LAST = 1;

  public static final int XL_LAST_CELL = 11;

  public static final int XL_LIST1 = 10;

  public static final int XL_LIST2 = 11;

  public static final int XL_LIST3 = 12;

  public static final int XL_LOCAL_FORMAT1 = 15;

  public static final int XL_LOCAL_FORMAT2 = 16;

  public static final int XL_LONG = 3;

  public static final int XL_LOTUS_HELP = 2;

  public static final int XL_MACROSHEET_CELL = 7;

  public static final int XL_MIXED = 2;

  public static final int XL_MULTIPLY = 4;

  public static final int XL_NARROW = 1;

  public static final int XL_NO_DOCUMENTS = 3;

  public static final int XL_OPEN = 2;

  public static final int XL_OUTSIDE = 3;

  public static final int XL_REFERENCE = 4;

  public static final int XL_SEMIAUTOMATIC = 2;

  public static final int XL_SHORT = 1;

  public static final int XL_SINGLE_QUOTE = 2;

  public static final int XL_STRICT = 2;

  public static final int XL_SUBTRACT = 3;

  public static final int XL_TEXT_BOX = 16;

  public static final int XL_TILED = 1;

  public static final int XL_TITLE_BAR = 8;

  public static final int XL_TOOLBAR = 1;

  public static final int XL_VISIBLE = 12;

  public static final int XL_WATCH_PANE = 11;

  public static final int XL_WIDE = 3;

  public static final int XL_WORKBOOK_TAB = 6;

  public static final int XL_WORKSHEET4 = 1;

  public static final int XL_WORKSHEET_CELL = 3;

  public static final int XL_WORKSHEET_SHORT = 5;

  public static final int XL_ALL_EXCEPT_BORDERS = 6;

  public static final int XL_LEFT_TO_RIGHT = 2;

  public static final int XL_TOP_TO_BOTTOM = 1;

  public static final int XL_VERY_HIDDEN = 2;

  public static final int XL_DRAWING_OBJECT = 14;


}

