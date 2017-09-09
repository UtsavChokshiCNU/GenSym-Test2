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


public interface MsoCondition
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #115
    An enumeration type.
    Type info name is: MsoCondition
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_CONDITION_FILE_TYPE_ALL_FILES = 1;

  public static final int MSO_CONDITION_FILE_TYPE_OFFICE_FILES = 2;

  public static final int MSO_CONDITION_FILE_TYPE_WORD_DOCUMENTS = 3;

  public static final int MSO_CONDITION_FILE_TYPE_EXCEL_WORKBOOKS = 4;

  public static final int MSO_CONDITION_FILE_TYPE_POWER_POINT_PRESENTATIONS = 5;

  public static final int MSO_CONDITION_FILE_TYPE_BINDERS = 6;

  public static final int MSO_CONDITION_FILE_TYPE_DATABASES = 7;

  public static final int MSO_CONDITION_FILE_TYPE_TEMPLATES = 8;

  public static final int MSO_CONDITION_INCLUDES = 9;

  public static final int MSO_CONDITION_INCLUDES_PHRASE = 10;

  public static final int MSO_CONDITION_BEGINS_WITH = 11;

  public static final int MSO_CONDITION_ENDS_WITH = 12;

  public static final int MSO_CONDITION_INCLUDES_NEAR_EACH_OTHER = 13;

  public static final int MSO_CONDITION_IS_EXACTLY = 14;

  public static final int MSO_CONDITION_IS_NOT = 15;

  public static final int MSO_CONDITION_YESTERDAY = 16;

  public static final int MSO_CONDITION_TODAY = 17;

  public static final int MSO_CONDITION_TOMORROW = 18;

  public static final int MSO_CONDITION_LAST_WEEK = 19;

  public static final int MSO_CONDITION_THIS_WEEK = 20;

  public static final int MSO_CONDITION_NEXT_WEEK = 21;

  public static final int MSO_CONDITION_LAST_MONTH = 22;

  public static final int MSO_CONDITION_THIS_MONTH = 23;

  public static final int MSO_CONDITION_NEXT_MONTH = 24;

  public static final int MSO_CONDITION_ANYTIME = 25;

  public static final int MSO_CONDITION_ANYTIME_BETWEEN = 26;

  public static final int MSO_CONDITION_ON = 27;

  public static final int MSO_CONDITION_ON_OR_AFTER = 28;

  public static final int MSO_CONDITION_ON_OR_BEFORE = 29;

  public static final int MSO_CONDITION_IN_THE_NEXT = 30;

  public static final int MSO_CONDITION_IN_THE_LAST = 31;

  public static final int MSO_CONDITION_EQUALS = 32;

  public static final int MSO_CONDITION_DOES_NOT_EQUAL = 33;

  public static final int MSO_CONDITION_ANY_NUMBER_BETWEEN = 34;

  public static final int MSO_CONDITION_AT_MOST = 35;

  public static final int MSO_CONDITION_AT_LEAST = 36;

  public static final int MSO_CONDITION_MORE_THAN = 37;

  public static final int MSO_CONDITION_LESS_THAN = 38;

  public static final int MSO_CONDITION_IS_YES = 39;

  public static final int MSO_CONDITION_IS_NO = 40;


}

