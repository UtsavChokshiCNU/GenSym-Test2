package com.gensym.com.beans.office20;

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


public interface MsoAutoShapeType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #31
    An enumeration type.
    Type info name is: MsoAutoShapeType
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_SHAPE_MIXED = -2;

  public static final int MSO_SHAPE_RECTANGLE = 1;

  public static final int MSO_SHAPE_PARALLELOGRAM = 2;

  public static final int MSO_SHAPE_TRAPEZOID = 3;

  public static final int MSO_SHAPE_DIAMOND = 4;

  public static final int MSO_SHAPE_ROUNDED_RECTANGLE = 5;

  public static final int MSO_SHAPE_OCTAGON = 6;

  public static final int MSO_SHAPE_ISOSCELES_TRIANGLE = 7;

  public static final int MSO_SHAPE_RIGHT_TRIANGLE = 8;

  public static final int MSO_SHAPE_OVAL = 9;

  public static final int MSO_SHAPE_HEXAGON = 10;

  public static final int MSO_SHAPE_CROSS = 11;

  public static final int MSO_SHAPE_REGULAR_PENTAGON = 12;

  public static final int MSO_SHAPE_CAN = 13;

  public static final int MSO_SHAPE_CUBE = 14;

  public static final int MSO_SHAPE_BEVEL = 15;

  public static final int MSO_SHAPE_FOLDED_CORNER = 16;

  public static final int MSO_SHAPE_SMILEY_FACE = 17;

  public static final int MSO_SHAPE_DONUT = 18;

  public static final int MSO_SHAPE_NO_SYMBOL = 19;

  public static final int MSO_SHAPE_BLOCK_ARC = 20;

  public static final int MSO_SHAPE_HEART = 21;

  public static final int MSO_SHAPE_LIGHTNING_BOLT = 22;

  public static final int MSO_SHAPE_SUN = 23;

  public static final int MSO_SHAPE_MOON = 24;

  public static final int MSO_SHAPE_ARC = 25;

  public static final int MSO_SHAPE_DOUBLE_BRACKET = 26;

  public static final int MSO_SHAPE_DOUBLE_BRACE = 27;

  public static final int MSO_SHAPE_PLAQUE = 28;

  public static final int MSO_SHAPE_LEFT_BRACKET = 29;

  public static final int MSO_SHAPE_RIGHT_BRACKET = 30;

  public static final int MSO_SHAPE_LEFT_BRACE = 31;

  public static final int MSO_SHAPE_RIGHT_BRACE = 32;

  public static final int MSO_SHAPE_RIGHT_ARROW = 33;

  public static final int MSO_SHAPE_LEFT_ARROW = 34;

  public static final int MSO_SHAPE_UP_ARROW = 35;

  public static final int MSO_SHAPE_DOWN_ARROW = 36;

  public static final int MSO_SHAPE_LEFT_RIGHT_ARROW = 37;

  public static final int MSO_SHAPE_UP_DOWN_ARROW = 38;

  public static final int MSO_SHAPE_QUAD_ARROW = 39;

  public static final int MSO_SHAPE_LEFT_RIGHT_UP_ARROW = 40;

  public static final int MSO_SHAPE_BENT_ARROW = 41;

  public static final int MSO_SHAPEU_TURN_ARROW = 42;

  public static final int MSO_SHAPE_LEFT_UP_ARROW = 43;

  public static final int MSO_SHAPE_BENT_UP_ARROW = 44;

  public static final int MSO_SHAPE_CURVED_RIGHT_ARROW = 45;

  public static final int MSO_SHAPE_CURVED_LEFT_ARROW = 46;

  public static final int MSO_SHAPE_CURVED_UP_ARROW = 47;

  public static final int MSO_SHAPE_CURVED_DOWN_ARROW = 48;

  public static final int MSO_SHAPE_STRIPED_RIGHT_ARROW = 49;

  public static final int MSO_SHAPE_NOTCHED_RIGHT_ARROW = 50;

  public static final int MSO_SHAPE_PENTAGON = 51;

  public static final int MSO_SHAPE_CHEVRON = 52;

  public static final int MSO_SHAPE_RIGHT_ARROW_CALLOUT = 53;

  public static final int MSO_SHAPE_LEFT_ARROW_CALLOUT = 54;

  public static final int MSO_SHAPE_UP_ARROW_CALLOUT = 55;

  public static final int MSO_SHAPE_DOWN_ARROW_CALLOUT = 56;

  public static final int MSO_SHAPE_LEFT_RIGHT_ARROW_CALLOUT = 57;

  public static final int MSO_SHAPE_UP_DOWN_ARROW_CALLOUT = 58;

  public static final int MSO_SHAPE_QUAD_ARROW_CALLOUT = 59;

  public static final int MSO_SHAPE_CIRCULAR_ARROW = 60;

  public static final int MSO_SHAPE_FLOWCHART_PROCESS = 61;

  public static final int MSO_SHAPE_FLOWCHART_ALTERNATE_PROCESS = 62;

  public static final int MSO_SHAPE_FLOWCHART_DECISION = 63;

  public static final int MSO_SHAPE_FLOWCHART_DATA = 64;

  public static final int MSO_SHAPE_FLOWCHART_PREDEFINED_PROCESS = 65;

  public static final int MSO_SHAPE_FLOWCHART_INTERNAL_STORAGE = 66;

  public static final int MSO_SHAPE_FLOWCHART_DOCUMENT = 67;

  public static final int MSO_SHAPE_FLOWCHART_MULTIDOCUMENT = 68;

  public static final int MSO_SHAPE_FLOWCHART_TERMINATOR = 69;

  public static final int MSO_SHAPE_FLOWCHART_PREPARATION = 70;

  public static final int MSO_SHAPE_FLOWCHART_MANUAL_INPUT = 71;

  public static final int MSO_SHAPE_FLOWCHART_MANUAL_OPERATION = 72;

  public static final int MSO_SHAPE_FLOWCHART_CONNECTOR = 73;

  public static final int MSO_SHAPE_FLOWCHART_OFFPAGE_CONNECTOR = 74;

  public static final int MSO_SHAPE_FLOWCHART_CARD = 75;

  public static final int MSO_SHAPE_FLOWCHART_PUNCHED_TAPE = 76;

  public static final int MSO_SHAPE_FLOWCHART_SUMMING_JUNCTION = 77;

  public static final int MSO_SHAPE_FLOWCHART_OR = 78;

  public static final int MSO_SHAPE_FLOWCHART_COLLATE = 79;

  public static final int MSO_SHAPE_FLOWCHART_SORT = 80;

  public static final int MSO_SHAPE_FLOWCHART_EXTRACT = 81;

  public static final int MSO_SHAPE_FLOWCHART_MERGE = 82;

  public static final int MSO_SHAPE_FLOWCHART_STORED_DATA = 83;

  public static final int MSO_SHAPE_FLOWCHART_DELAY = 84;

  public static final int MSO_SHAPE_FLOWCHART_SEQUENTIAL_ACCESS_STORAGE = 85;

  public static final int MSO_SHAPE_FLOWCHART_MAGNETIC_DISK = 86;

  public static final int MSO_SHAPE_FLOWCHART_DIRECT_ACCESS_STORAGE = 87;

  public static final int MSO_SHAPE_FLOWCHART_DISPLAY = 88;

  public static final int MSO_SHAPE_EXPLOSION1 = 89;

  public static final int MSO_SHAPE_EXPLOSION2 = 90;

  public static final int MSO_SHAPE4POINT_STAR = 91;

  public static final int MSO_SHAPE5POINT_STAR = 92;

  public static final int MSO_SHAPE8POINT_STAR = 93;

  public static final int MSO_SHAPE16POINT_STAR = 94;

  public static final int MSO_SHAPE24POINT_STAR = 95;

  public static final int MSO_SHAPE32POINT_STAR = 96;

  public static final int MSO_SHAPE_UP_RIBBON = 97;

  public static final int MSO_SHAPE_DOWN_RIBBON = 98;

  public static final int MSO_SHAPE_CURVED_UP_RIBBON = 99;

  public static final int MSO_SHAPE_CURVED_DOWN_RIBBON = 100;

  public static final int MSO_SHAPE_VERTICAL_SCROLL = 101;

  public static final int MSO_SHAPE_HORIZONTAL_SCROLL = 102;

  public static final int MSO_SHAPE_WAVE = 103;

  public static final int MSO_SHAPE_DOUBLE_WAVE = 104;

  public static final int MSO_SHAPE_RECTANGULAR_CALLOUT = 105;

  public static final int MSO_SHAPE_ROUNDED_RECTANGULAR_CALLOUT = 106;

  public static final int MSO_SHAPE_OVAL_CALLOUT = 107;

  public static final int MSO_SHAPE_CLOUD_CALLOUT = 108;

  public static final int MSO_SHAPE_LINE_CALLOUT1 = 109;

  public static final int MSO_SHAPE_LINE_CALLOUT2 = 110;

  public static final int MSO_SHAPE_LINE_CALLOUT3 = 111;

  public static final int MSO_SHAPE_LINE_CALLOUT4 = 112;

  public static final int MSO_SHAPE_LINE_CALLOUT1_ACCENT_BAR = 113;

  public static final int MSO_SHAPE_LINE_CALLOUT2_ACCENT_BAR = 114;

  public static final int MSO_SHAPE_LINE_CALLOUT3_ACCENT_BAR = 115;

  public static final int MSO_SHAPE_LINE_CALLOUT4_ACCENT_BAR = 116;

  public static final int MSO_SHAPE_LINE_CALLOUT1_NO_BORDER = 117;

  public static final int MSO_SHAPE_LINE_CALLOUT2_NO_BORDER = 118;

  public static final int MSO_SHAPE_LINE_CALLOUT3_NO_BORDER = 119;

  public static final int MSO_SHAPE_LINE_CALLOUT4_NO_BORDER = 120;

  public static final int MSO_SHAPE_LINE_CALLOUT1_BORDERAND_ACCENT_BAR = 121;

  public static final int MSO_SHAPE_LINE_CALLOUT2_BORDERAND_ACCENT_BAR = 122;

  public static final int MSO_SHAPE_LINE_CALLOUT3_BORDERAND_ACCENT_BAR = 123;

  public static final int MSO_SHAPE_LINE_CALLOUT4_BORDERAND_ACCENT_BAR = 124;

  public static final int MSO_SHAPE_ACTION_BUTTON_CUSTOM = 125;

  public static final int MSO_SHAPE_ACTION_BUTTON_HOME = 126;

  public static final int MSO_SHAPE_ACTION_BUTTON_HELP = 127;

  public static final int MSO_SHAPE_ACTION_BUTTON_INFORMATION = 128;

  public static final int MSO_SHAPE_ACTION_BUTTON_BACKOR_PREVIOUS = 129;

  public static final int MSO_SHAPE_ACTION_BUTTON_FORWARDOR_NEXT = 130;

  public static final int MSO_SHAPE_ACTION_BUTTON_BEGINNING = 131;

  public static final int MSO_SHAPE_ACTION_BUTTON_END = 132;

  public static final int MSO_SHAPE_ACTION_BUTTON_RETURN = 133;

  public static final int MSO_SHAPE_ACTION_BUTTON_DOCUMENT = 134;

  public static final int MSO_SHAPE_ACTION_BUTTON_SOUND = 135;

  public static final int MSO_SHAPE_ACTION_BUTTON_MOVIE = 136;

  public static final int MSO_SHAPE_BALLOON = 137;

  public static final int MSO_SHAPE_NOT_PRIMITIVE = 138;


}

