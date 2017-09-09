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


public interface vbextFileType
{

  public static final Guid classID =
    new Guid(0x2e150, 0x0, 0x0,
             (short) 0xc0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x46);

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic 5.0 Extensibility
    // Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    // There are 108 TypeInfos in the library

/* Type info #2
    An enumeration type.
    Type info name is: vbext_FileType
    Doc string is: Specifies the kind of file.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
 */

  public static final int VBEXT_FT_FORM = 0;

  public static final int VBEXT_FT_MODULE = 1;

  public static final int VBEXT_FT_CLASS = 2;

  public static final int VBEXT_FT_PROJECT = 3;

  public static final int VBEXT_FT_EXE = 4;

  public static final int VBEXT_FT_FRX = 5;

  public static final int VBEXT_FT_RES = 6;

  public static final int VBEXT_FT_USER_CONTROL = 7;

  public static final int VBEXT_FT_PROPERTY_PAGE = 8;

  public static final int VBEXT_FT_DOC_OBJECT = 9;

  public static final int VBEXT_FT_BINARY = 10;

  public static final int VBEXT_FT_GROUP_PROJECT = 11;

  public static final int VBEXT_FT_DESIGNERS = 12;


}

