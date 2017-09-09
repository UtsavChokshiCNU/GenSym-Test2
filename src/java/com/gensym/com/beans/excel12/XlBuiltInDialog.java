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


public interface XlBuiltInDialog
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #159
    An enumeration type.
    Type info name is: XlBuiltInDialog
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_DIALOG_OPEN = 1;

  public static final int XL_DIALOG_OPEN_LINKS = 2;

  public static final int XL_DIALOG_SAVE_AS = 5;

  public static final int XL_DIALOG_FILE_DELETE = 6;

  public static final int XL_DIALOG_PAGE_SETUP = 7;

  public static final int XL_DIALOG_PRINT = 8;

  public static final int XL_DIALOG_PRINTER_SETUP = 9;

  public static final int XL_DIALOG_ARRANGE_ALL = 12;

  public static final int XL_DIALOG_WINDOW_SIZE = 13;

  public static final int XL_DIALOG_WINDOW_MOVE = 14;

  public static final int XL_DIALOG_RUN = 17;

  public static final int XL_DIALOG_SET_PRINT_TITLES = 23;

  public static final int XL_DIALOG_FONT = 26;

  public static final int XL_DIALOG_DISPLAY = 27;

  public static final int XL_DIALOG_PROTECT_DOCUMENT = 28;

  public static final int XL_DIALOG_CALCULATION = 32;

  public static final int XL_DIALOG_EXTRACT = 35;

  public static final int XL_DIALOG_DATA_DELETE = 36;

  public static final int XL_DIALOG_SORT = 39;

  public static final int XL_DIALOG_DATA_SERIES = 40;

  public static final int XL_DIALOG_TABLE = 41;

  public static final int XL_DIALOG_FORMAT_NUMBER = 42;

  public static final int XL_DIALOG_ALIGNMENT = 43;

  public static final int XL_DIALOG_STYLE = 44;

  public static final int XL_DIALOG_BORDER = 45;

  public static final int XL_DIALOG_CELL_PROTECTION = 46;

  public static final int XL_DIALOG_COLUMN_WIDTH = 47;

  public static final int XL_DIALOG_CLEAR = 52;

  public static final int XL_DIALOG_PASTE_SPECIAL = 53;

  public static final int XL_DIALOG_EDIT_DELETE = 54;

  public static final int XL_DIALOG_INSERT = 55;

  public static final int XL_DIALOG_PASTE_NAMES = 58;

  public static final int XL_DIALOG_DEFINE_NAME = 61;

  public static final int XL_DIALOG_CREATE_NAMES = 62;

  public static final int XL_DIALOG_FORMULA_GOTO = 63;

  public static final int XL_DIALOG_FORMULA_FIND = 64;

  public static final int XL_DIALOG_GALLERY_AREA = 67;

  public static final int XL_DIALOG_GALLERY_BAR = 68;

  public static final int XL_DIALOG_GALLERY_COLUMN = 69;

  public static final int XL_DIALOG_GALLERY_LINE = 70;

  public static final int XL_DIALOG_GALLERY_PIE = 71;

  public static final int XL_DIALOG_GALLERY_SCATTER = 72;

  public static final int XL_DIALOG_COMBINATION = 73;

  public static final int XL_DIALOG_GRIDLINES = 76;

  public static final int XL_DIALOG_AXES = 78;

  public static final int XL_DIALOG_ATTACH_TEXT = 80;

  public static final int XL_DIALOG_PATTERNS = 84;

  public static final int XL_DIALOG_MAIN_CHART = 85;

  public static final int XL_DIALOG_OVERLAY = 86;

  public static final int XL_DIALOG_SCALE = 87;

  public static final int XL_DIALOG_FORMAT_LEGEND = 88;

  public static final int XL_DIALOG_FORMAT_TEXT = 89;

  public static final int XL_DIALOG_PARSE = 91;

  public static final int XL_DIALOG_UNHIDE = 94;

  public static final int XL_DIALOG_WORKSPACE = 95;

  public static final int XL_DIALOG_ACTIVATE = 103;

  public static final int XL_DIALOG_COPY_PICTURE = 108;

  public static final int XL_DIALOG_DELETE_NAME = 110;

  public static final int XL_DIALOG_DELETE_FORMAT = 111;

  public static final int XL_DIALOG_NEW = 119;

  public static final int XL_DIALOG_ROW_HEIGHT = 127;

  public static final int XL_DIALOG_FORMAT_MOVE = 128;

  public static final int XL_DIALOG_FORMAT_SIZE = 129;

  public static final int XL_DIALOG_FORMULA_REPLACE = 130;

  public static final int XL_DIALOG_SELECT_SPECIAL = 132;

  public static final int XL_DIALOG_APPLY_NAMES = 133;

  public static final int XL_DIALOG_REPLACE_FONT = 134;

  public static final int XL_DIALOG_SPLIT = 137;

  public static final int XL_DIALOG_OUTLINE = 142;

  public static final int XL_DIALOG_SAVE_WORKBOOK = 145;

  public static final int XL_DIALOG_COPY_CHART = 147;

  public static final int XL_DIALOG_FORMAT_FONT = 150;

  public static final int XL_DIALOG_NOTE = 154;

  public static final int XL_DIALOG_SET_UPDATE_STATUS = 159;

  public static final int XL_DIALOG_COLOR_PALETTE = 161;

  public static final int XL_DIALOG_CHANGE_LINK = 166;

  public static final int XL_DIALOG_APP_MOVE = 170;

  public static final int XL_DIALOG_APP_SIZE = 171;

  public static final int XL_DIALOG_MAIN_CHART_TYPE = 185;

  public static final int XL_DIALOG_OVERLAY_CHART_TYPE = 186;

  public static final int XL_DIALOG_OPEN_MAIL = 188;

  public static final int XL_DIALOG_SEND_MAIL = 189;

  public static final int XL_DIALOG_STANDARD_FONT = 190;

  public static final int XL_DIALOG_CONSOLIDATE = 191;

  public static final int XL_DIALOG_SORT_SPECIAL = 192;

  public static final int XL_DIALOG_GALLERY3D_AREA = 193;

  public static final int XL_DIALOG_GALLERY3D_COLUMN = 194;

  public static final int XL_DIALOG_GALLERY3D_LINE = 195;

  public static final int XL_DIALOG_GALLERY3D_PIE = 196;

  public static final int XL_DIALOG_VIEW3D = 197;

  public static final int XL_DIALOG_GOAL_SEEK = 198;

  public static final int XL_DIALOG_WORKGROUP = 199;

  public static final int XL_DIALOG_FILL_GROUP = 200;

  public static final int XL_DIALOG_UPDATE_LINK = 201;

  public static final int XL_DIALOG_PROMOTE = 202;

  public static final int XL_DIALOG_DEMOTE = 203;

  public static final int XL_DIALOG_SHOW_DETAIL = 204;

  public static final int XL_DIALOG_OBJECT_PROPERTIES = 207;

  public static final int XL_DIALOG_SAVE_NEW_OBJECT = 208;

  public static final int XL_DIALOG_APPLY_STYLE = 212;

  public static final int XL_DIALOG_ASSIGN_TO_OBJECT = 213;

  public static final int XL_DIALOG_OBJECT_PROTECTION = 214;

  public static final int XL_DIALOG_CREATE_PUBLISHER = 217;

  public static final int XL_DIALOG_SUBSCRIBE_TO = 218;

  public static final int XL_DIALOG_SHOW_TOOLBAR = 220;

  public static final int XL_DIALOG_PRINT_PREVIEW = 222;

  public static final int XL_DIALOG_EDIT_COLOR = 223;

  public static final int XL_DIALOG_FORMAT_MAIN = 225;

  public static final int XL_DIALOG_FORMAT_OVERLAY = 226;

  public static final int XL_DIALOG_EDIT_SERIES = 228;

  public static final int XL_DIALOG_DEFINE_STYLE = 229;

  public static final int XL_DIALOG_GALLERY_RADAR = 249;

  public static final int XL_DIALOG_EDITION_OPTIONS = 251;

  public static final int XL_DIALOG_ZOOM = 256;

  public static final int XL_DIALOG_INSERT_OBJECT = 259;

  public static final int XL_DIALOG_SIZE = 261;

  public static final int XL_DIALOG_MOVE = 262;

  public static final int XL_DIALOG_FORMAT_AUTO = 269;

  public static final int XL_DIALOG_GALLERY3D_BAR = 272;

  public static final int XL_DIALOG_GALLERY3D_SURFACE = 273;

  public static final int XL_DIALOG_CUSTOMIZE_TOOLBAR = 276;

  public static final int XL_DIALOG_WORKBOOK_ADD = 281;

  public static final int XL_DIALOG_WORKBOOK_MOVE = 282;

  public static final int XL_DIALOG_WORKBOOK_COPY = 283;

  public static final int XL_DIALOG_WORKBOOK_OPTIONS = 284;

  public static final int XL_DIALOG_SAVE_WORKSPACE = 285;

  public static final int XL_DIALOG_CHART_WIZARD = 288;

  public static final int XL_DIALOG_ASSIGN_TO_TOOL = 293;

  public static final int XL_DIALOG_PLACEMENT = 300;

  public static final int XL_DIALOG_FILL_WORKGROUP = 301;

  public static final int XL_DIALOG_WORKBOOK_NEW = 302;

  public static final int XL_DIALOG_SCENARIO_CELLS = 305;

  public static final int XL_DIALOG_SCENARIO_ADD = 307;

  public static final int XL_DIALOG_SCENARIO_EDIT = 308;

  public static final int XL_DIALOG_SCENARIO_SUMMARY = 311;

  public static final int XL_DIALOG_PIVOT_TABLE_WIZARD = 312;

  public static final int XL_DIALOG_PIVOT_FIELD_PROPERTIES = 313;

  public static final int XL_DIALOG_OPTIONS_CALCULATION = 318;

  public static final int XL_DIALOG_OPTIONS_EDIT = 319;

  public static final int XL_DIALOG_OPTIONS_VIEW = 320;

  public static final int XL_DIALOG_ADDIN_MANAGER = 321;

  public static final int XL_DIALOG_MENU_EDITOR = 322;

  public static final int XL_DIALOG_ATTACH_TOOLBARS = 323;

  public static final int XL_DIALOG_OPTIONS_CHART = 325;

  public static final int XL_DIALOG_VBA_INSERT_FILE = 328;

  public static final int XL_DIALOG_VBA_PROCEDURE_DEFINITION = 330;

  public static final int XL_DIALOG_ROUTING_SLIP = 336;

  public static final int XL_DIALOG_MAIL_LOGON = 339;

  public static final int XL_DIALOG_INSERT_PICTURE = 342;

  public static final int XL_DIALOG_GALLERY_DOUGHNUT = 344;

  public static final int XL_DIALOG_CHART_TREND = 350;

  public static final int XL_DIALOG_WORKBOOK_INSERT = 354;

  public static final int XL_DIALOG_OPTIONS_TRANSITION = 355;

  public static final int XL_DIALOG_OPTIONS_GENERAL = 356;

  public static final int XL_DIALOG_FILTER_ADVANCED = 370;

  public static final int XL_DIALOG_MAIL_NEXT_LETTER = 378;

  public static final int XL_DIALOG_DATA_LABEL = 379;

  public static final int XL_DIALOG_INSERT_TITLE = 380;

  public static final int XL_DIALOG_FONT_PROPERTIES = 381;

  public static final int XL_DIALOG_MACRO_OPTIONS = 382;

  public static final int XL_DIALOG_WORKBOOK_UNHIDE = 384;

  public static final int XL_DIALOG_WORKBOOK_NAME = 386;

  public static final int XL_DIALOG_GALLERY_CUSTOM = 388;

  public static final int XL_DIALOG_ADD_CHART_AUTOFORMAT = 390;

  public static final int XL_DIALOG_CHART_ADD_DATA = 392;

  public static final int XL_DIALOG_TAB_ORDER = 394;

  public static final int XL_DIALOG_SUBTOTAL_CREATE = 398;

  public static final int XL_DIALOG_WORKBOOK_TAB_SPLIT = 415;

  public static final int XL_DIALOG_WORKBOOK_PROTECT = 417;

  public static final int XL_DIALOG_SCROLLBAR_PROPERTIES = 420;

  public static final int XL_DIALOG_PIVOT_SHOW_PAGES = 421;

  public static final int XL_DIALOG_TEXT_TO_COLUMNS = 422;

  public static final int XL_DIALOG_FORMAT_CHARTTYPE = 423;

  public static final int XL_DIALOG_PIVOT_FIELD_GROUP = 433;

  public static final int XL_DIALOG_PIVOT_FIELD_UNGROUP = 434;

  public static final int XL_DIALOG_CHECKBOX_PROPERTIES = 435;

  public static final int XL_DIALOG_LABEL_PROPERTIES = 436;

  public static final int XL_DIALOG_LISTBOX_PROPERTIES = 437;

  public static final int XL_DIALOG_EDITBOX_PROPERTIES = 438;

  public static final int XL_DIALOG_OPEN_TEXT = 441;

  public static final int XL_DIALOG_PUSHBUTTON_PROPERTIES = 445;

  public static final int XL_DIALOG_FILTER = 447;

  public static final int XL_DIALOG_FUNCTION_WIZARD = 450;

  public static final int XL_DIALOG_SAVE_COPY_AS = 456;

  public static final int XL_DIALOG_OPTIONS_LISTS_ADD = 458;

  public static final int XL_DIALOG_SERIES_AXES = 460;

  public static final int XL_DIALOG_SERIESX = 461;

  public static final int XL_DIALOG_SERIESY = 462;

  public static final int XL_DIALOG_ERRORBARX = 463;

  public static final int XL_DIALOG_ERRORBARY = 464;

  public static final int XL_DIALOG_FORMAT_CHART = 465;

  public static final int XL_DIALOG_SERIES_ORDER = 466;

  public static final int XL_DIALOG_MAIL_EDIT_MAILER = 470;

  public static final int XL_DIALOG_STANDARD_WIDTH = 472;

  public static final int XL_DIALOG_SCENARIO_MERGE = 473;

  public static final int XL_DIALOG_PROPERTIES = 474;

  public static final int XL_DIALOG_SUMMARY_INFO = 474;

  public static final int XL_DIALOG_FIND_FILE = 475;

  public static final int XL_DIALOG_ACTIVE_CELL_FONT = 476;

  public static final int XL_DIALOG_VBA_MAKE_ADDIN = 478;

  public static final int XL_DIALOG_FILE_SHARING = 481;

  public static final int XL_DIALOG_AUTO_CORRECT = 485;

  public static final int XL_DIALOG_CUSTOM_VIEWS = 493;

  public static final int XL_DIALOG_INSERT_NAME_LABEL = 496;

  public static final int XL_DIALOG_SERIES_SHAPE = 504;

  public static final int XL_DIALOG_CHART_OPTIONS_DATA_LABELS = 505;

  public static final int XL_DIALOG_CHART_OPTIONS_DATA_TABLE = 506;

  public static final int XL_DIALOG_SET_BACKGROUND_PICTURE = 509;

  public static final int XL_DIALOG_DATA_VALIDATION = 525;

  public static final int XL_DIALOG_CHART_TYPE = 526;

  public static final int XL_DIALOG_CHART_LOCATION = 527;

  public static final int XL_DIALOG_PHONETIC = 538;

  public static final int XL_DIALOG_CHART_SOURCE_DATA = 541;

  public static final int XL_DIALOG_SERIES_OPTIONS = 557;

  public static final int XL_DIALOG_PIVOT_TABLE_OPTIONS = 567;

  public static final int XL_DIALOG_PIVOT_SOLVE_ORDER = 568;

  public static final int XL_DIALOG_PIVOT_CALCULATED_FIELD = 570;

  public static final int XL_DIALOG_PIVOT_CALCULATED_ITEM = 572;

  public static final int XL_DIALOG_CONDITIONAL_FORMATTING = 583;

  public static final int XL_DIALOG_INSERT_HYPERLINK = 596;

  public static final int XL_DIALOG_PROTECT_SHARING = 620;


}

