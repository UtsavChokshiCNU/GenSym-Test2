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


public interface vbextProjectProtection
{

  public static final Guid classID =
    new Guid(0x2e129, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic for Applications Extensibility
    // Help file is: C:\Program Files\Common Files\Microsoft Shared\VBA\VEENOB3.HLP
    // There are 55 TypeInfos in the library

/* Type info #23
    An enumeration type.
    Type info name is: vbext_ProjectProtection
    Help file is: C:\Program Files\Common Files\Microsoft Shared\VBA\VEENOB3.HLP
 */

  public static final int VBEXT_PP_NONE = 0;

  public static final int VBEXT_PP_LOCKED = 1;


}

