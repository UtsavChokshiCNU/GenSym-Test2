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


public interface MsoBalloonButtonType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #66
    An enumeration type.
    Type info name is: MsoBalloonButtonType
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_BALLOON_BUTTON_YES_TO_ALL = -15;

  public static final int MSO_BALLOON_BUTTON_OPTIONS = -14;

  public static final int MSO_BALLOON_BUTTON_TIPS = -13;

  public static final int MSO_BALLOON_BUTTON_CLOSE = -12;

  public static final int MSO_BALLOON_BUTTON_SNOOZE = -11;

  public static final int MSO_BALLOON_BUTTON_SEARCH = -10;

  public static final int MSO_BALLOON_BUTTON_IGNORE = -9;

  public static final int MSO_BALLOON_BUTTON_ABORT = -8;

  public static final int MSO_BALLOON_BUTTON_RETRY = -7;

  public static final int MSO_BALLOON_BUTTON_NEXT = -6;

  public static final int MSO_BALLOON_BUTTON_BACK = -5;

  public static final int MSO_BALLOON_BUTTON_NO = -4;

  public static final int MSO_BALLOON_BUTTON_YES = -3;

  public static final int MSO_BALLOON_BUTTON_CANCEL = -2;

  public static final int MSO_BALLOON_BUTTONOK = -1;

  public static final int MSO_BALLOON_BUTTON_NULL = 0;


}

