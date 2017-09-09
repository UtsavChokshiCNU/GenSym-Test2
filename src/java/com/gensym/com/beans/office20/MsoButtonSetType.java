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


public interface MsoButtonSetType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #59
    An enumeration type.
    Type info name is: MsoButtonSetType
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_BUTTON_SET_NONE = 0;

  public static final int MSO_BUTTON_SETOK = 1;

  public static final int MSO_BUTTON_SET_CANCEL = 2;

  public static final int MSO_BUTTON_SET_OK_CANCEL = 3;

  public static final int MSO_BUTTON_SET_YES_NO = 4;

  public static final int MSO_BUTTON_SET_YES_NO_CANCEL = 5;

  public static final int MSO_BUTTON_SET_BACK_CLOSE = 6;

  public static final int MSO_BUTTON_SET_NEXT_CLOSE = 7;

  public static final int MSO_BUTTON_SET_BACK_NEXT_CLOSE = 8;

  public static final int MSO_BUTTON_SET_RETRY_CANCEL = 9;

  public static final int MSO_BUTTON_SET_ABORT_RETRY_IGNORE = 10;

  public static final int MSO_BUTTON_SET_SEARCH_CLOSE = 11;

  public static final int MSO_BUTTON_SET_BACK_NEXT_SNOOZE = 12;

  public static final int MSO_BUTTON_SET_TIPS_OPTIONS_CLOSE = 13;

  public static final int MSO_BUTTON_SET_YES_ALL_NO_CANCEL = 14;


}

