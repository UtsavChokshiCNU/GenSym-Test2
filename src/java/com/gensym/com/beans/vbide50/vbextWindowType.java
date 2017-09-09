package com.gensym.com.beans.vbide50;

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


public interface vbextWindowType
{

  public static final Guid classID =
    new Guid(0x2e111, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic 5.0 Extensibility
    // Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    // There are 108 TypeInfos in the library

/* Type info #15
    An enumeration type.
    Type info name is: vbext_WindowType
    Doc string is: Specifies the kind window.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
 */

  public static final int VBEXT_WT_CODE_WINDOW = 0;

  public static final int VBEXT_WT_DESIGNER = 1;

  public static final int VBEXT_WT_BROWSER = 2;

  public static final int VBEXT_WT_WATCH = 3;

  public static final int VBEXT_WT_LOCALS = 4;

  public static final int VBEXT_WT_IMMEDIATE = 5;

  public static final int VBEXT_WT_PROJECT_WINDOW = 6;

  public static final int VBEXT_WT_PROPERTY_WINDOW = 7;

  public static final int VBEXT_WT_FIND = 8;

  public static final int VBEXT_WT_FIND_REPLACE = 9;

  public static final int VBEXT_WT_TOOLBOX = 10;

  public static final int VBEXT_WT_LINKED_WINDOW_FRAME = 11;

  public static final int VBEXT_WT_MAIN_WINDOW = 12;

  public static final int VBEXT_WT_PREVIEW = 13;

  public static final int VBEXT_WT_COLOR_PALETTE = 14;

  public static final int VBEXT_WT_TOOL_WINDOW = 15;


}

