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


public interface MsoAnimationType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #58
    An enumeration type.
    Type info name is: MsoAnimationType
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_ANIMATION_IDLE = 1;

  public static final int MSO_ANIMATION_GREETING = 2;

  public static final int MSO_ANIMATION_GOODBYE = 3;

  public static final int MSO_ANIMATION_BEGIN_SPEAKING = 4;

  public static final int MSO_ANIMATION_CHARACTER_SUCCESS_MAJOR = 6;

  public static final int MSO_ANIMATION_GET_ATTENTION_MAJOR = 11;

  public static final int MSO_ANIMATION_GET_ATTENTION_MINOR = 12;

  public static final int MSO_ANIMATION_SEARCHING = 13;

  public static final int MSO_ANIMATION_PRINTING = 18;

  public static final int MSO_ANIMATION_GESTURE_RIGHT = 19;

  public static final int MSO_ANIMATION_WRITING_NOTING_SOMETHING = 22;

  public static final int MSO_ANIMATION_WORKING_AT_SOMETHING = 23;

  public static final int MSO_ANIMATION_THINKING = 24;

  public static final int MSO_ANIMATION_SENDING_MAIL = 25;

  public static final int MSO_ANIMATION_LISTENS_TO_COMPUTER = 26;

  public static final int MSO_ANIMATION_DISAPPEAR = 31;

  public static final int MSO_ANIMATION_APPEAR = 32;

  public static final int MSO_ANIMATION_GET_ARTSY = 100;

  public static final int MSO_ANIMATION_GET_TECHY = 101;

  public static final int MSO_ANIMATION_GET_WIZARDY = 102;

  public static final int MSO_ANIMATION_CHECKING_SOMETHING = 103;

  public static final int MSO_ANIMATION_LOOK_DOWN = 104;

  public static final int MSO_ANIMATION_LOOK_DOWN_LEFT = 105;

  public static final int MSO_ANIMATION_LOOK_DOWN_RIGHT = 106;

  public static final int MSO_ANIMATION_LOOK_LEFT = 107;

  public static final int MSO_ANIMATION_LOOK_RIGHT = 108;

  public static final int MSO_ANIMATION_LOOK_UP = 109;

  public static final int MSO_ANIMATION_LOOK_UP_LEFT = 110;

  public static final int MSO_ANIMATION_LOOK_UP_RIGHT = 111;

  public static final int MSO_ANIMATION_SAVING = 112;

  public static final int MSO_ANIMATION_GESTURE_DOWN = 113;

  public static final int MSO_ANIMATION_GESTURE_LEFT = 114;

  public static final int MSO_ANIMATION_GESTURE_UP = 115;

  public static final int MSO_ANIMATION_EMPTY_TRASH = 116;


}

