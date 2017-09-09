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


public interface vbextWrite
{

  public static final Guid classID =
    new Guid(0x77932f0, 0x2369, 0x11ce,
             (short) 0xbf, (short) 0xdc, (short) 0x8, (short) 0x0,
             (short) 0x2b, (short) 0x2b, (short) 0x8c, (short) 0xda);

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic 5.0 Extensibility
    // Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    // There are 108 TypeInfos in the library

/* Type info #3
    An enumeration type.
    Type info name is: vbextWrite
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
 */

  public static final int VBEXT_WRITE_SUCCESS = 0;

  public static final int VBEXT_WRITE_CANCELLED = 1;

  public static final int VBEXT_WRITE_FAILED = 2;


}

