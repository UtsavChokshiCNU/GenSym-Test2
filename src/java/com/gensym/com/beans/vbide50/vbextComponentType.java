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


public interface vbextComponentType
{

  public static final Guid classID =
    new Guid(0x70a9c5f1, 0x1f7e, 0x11cf,
             (short) 0x86, (short) 0x7f, (short) 0x0, (short) 0xaa,
             (short) 0x0, (short) 0x5f, (short) 0xf3, (short) 0x4a);

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic 5.0 Extensibility
    // Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    // There are 108 TypeInfos in the library

/* Type info #57
    An enumeration type.
    Type info name is: vbext_ComponentType
    Doc string is: Specifies the type of component.
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
 */

  public static final int VBEXT_CT_STD_MODULE = 1;

  public static final int VBEXT_CT_CLASS_MODULE = 2;

  public static final int VBEXT_CT_MS_FORM = 3;

  public static final int VBEXT_CT_RES_FILE = 4;

  public static final int VBEXT_CT_VB_FORM = 5;

  public static final int VBEXT_CT_VBMDI_FORM = 6;

  public static final int VBEXT_CT_PROP_PAGE = 7;

  public static final int VBEXT_CT_USER_CONTROL = 8;

  public static final int VBEXT_CT_DOC_OBJECT = 9;

  public static final int VBEXT_CT_RELATED_DOCUMENT = 10;

  public static final int VBEXT_CT_ACTIVEX_DESIGNER = 11;


}

