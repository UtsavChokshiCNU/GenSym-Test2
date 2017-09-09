package com.gensym.com.beans.excel12;

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


public interface XlClipboardFormat
{

  public static final Guid classID =
    new Guid(0x0, 0x0, 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0,
             (short) 0x0, (short) 0x0, (short) 0x0, (short) 0x0);

    // Library name is: Excel
    // DocString is: Microsoft Excel 8.0 Object Library
    // Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
    // There are 526 TypeInfos in the library

/* Type info #100
    An enumeration type.
    Type info name is: XlClipboardFormat
    Help file is: C:\Program Files\Microsoft Office\Office\VBAXL8.HLP
 */

  public static final int XL_CLIPBOARD_FORMATBIFF = 8;

  public static final int XL_CLIPBOARD_FORMATBIFF2 = 18;

  public static final int XL_CLIPBOARD_FORMATBIFF3 = 20;

  public static final int XL_CLIPBOARD_FORMATBIFF4 = 30;

  public static final int XL_CLIPBOARD_FORMAT_BINARY = 15;

  public static final int XL_CLIPBOARD_FORMAT_BITMAP = 9;

  public static final int XL_CLIPBOARD_FORMATCGM = 13;

  public static final int XL_CLIPBOARD_FORMATCSV = 5;

  public static final int XL_CLIPBOARD_FORMATDIF = 4;

  public static final int XL_CLIPBOARD_FORMAT_DSP_TEXT = 12;

  public static final int XL_CLIPBOARD_FORMAT_EMBEDDED_OBJECT = 21;

  public static final int XL_CLIPBOARD_FORMAT_EMBED_SOURCE = 22;

  public static final int XL_CLIPBOARD_FORMAT_LINK = 11;

  public static final int XL_CLIPBOARD_FORMAT_LINK_SOURCE = 23;

  public static final int XL_CLIPBOARD_FORMAT_LINK_SOURCE_DESC = 32;

  public static final int XL_CLIPBOARD_FORMAT_MOVIE = 24;

  public static final int XL_CLIPBOARD_FORMAT_NATIVE = 14;

  public static final int XL_CLIPBOARD_FORMAT_OBJECT_DESC = 31;

  public static final int XL_CLIPBOARD_FORMAT_OBJECT_LINK = 19;

  public static final int XL_CLIPBOARD_FORMAT_OWNER_LINK = 17;

  public static final int XL_CLIPBOARD_FORMATPICT = 2;

  public static final int XL_CLIPBOARD_FORMAT_PRINTPICT = 3;

  public static final int XL_CLIPBOARD_FORMATRTF = 7;

  public static final int XL_CLIPBOARD_FORMAT_SCREENPICT = 29;

  public static final int XL_CLIPBOARD_FORMAT_STANDARD_FONT = 28;

  public static final int XL_CLIPBOARD_FORMAT_STANDARD_SCALE = 27;

  public static final int XL_CLIPBOARD_FORMATSYLK = 6;

  public static final int XL_CLIPBOARD_FORMAT_TABLE = 16;

  public static final int XL_CLIPBOARD_FORMAT_TEXT = 0;

  public static final int XL_CLIPBOARD_FORMAT_TOOL_FACE = 25;

  public static final int XL_CLIPBOARD_FORMAT_TOOL_FACEPICT = 26;

  public static final int XL_CLIPBOARD_FORMATVALU = 1;

  public static final int XL_CLIPBOARD_FORMATWK1 = 10;


}

