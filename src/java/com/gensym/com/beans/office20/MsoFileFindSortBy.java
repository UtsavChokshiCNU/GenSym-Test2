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


public interface MsoFileFindSortBy
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Office
    // DocString is: Microsoft Office 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
    // There are 121 TypeInfos in the library

/* Type info #107
    An enumeration type.
    Type info name is: MsoFileFindSortBy
    Help file is: C:\Program Files\Microsoft Office\Office\vbaoff8.hlp
 */

  public static final int MSO_FILE_FIND_SORTBY_AUTHOR = 1;

  public static final int MSO_FILE_FIND_SORTBY_DATE_CREATED = 2;

  public static final int MSO_FILE_FIND_SORTBY_LAST_SAVED_BY = 3;

  public static final int MSO_FILE_FIND_SORTBY_DATE_SAVED = 4;

  public static final int MSO_FILE_FIND_SORTBY_FILE_NAME = 5;

  public static final int MSO_FILE_FIND_SORTBY_SIZE = 6;

  public static final int MSO_FILE_FIND_SORTBY_TITLE = 7;


}

