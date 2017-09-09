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


public interface MsoBalloonErrorType
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #63
    An enumeration type.
    Type info name is: MsoBalloonErrorType
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_BALLOON_ERROR_NONE = 0;

  public static final int MSO_BALLOON_ERROR_OTHER = 1;

  public static final int MSO_BALLOON_ERROR_TOO_BIG = 2;

  public static final int MSO_BALLOON_ERROR_OUT_OF_MEMORY = 3;

  public static final int MSO_BALLOON_ERROR_BAD_PICTURE_REF = 4;

  public static final int MSO_BALLOON_ERROR_BAD_REFERENCE = 5;

  public static final int MSO_BALLOON_ERROR_BUTTONLESS_MODAL = 6;

  public static final int MSO_BALLOON_ERROR_BUTTON_MODELESS = 7;

  public static final int MSO_BALLOON_ERROR_BAD_CHARACTER = 8;


}

