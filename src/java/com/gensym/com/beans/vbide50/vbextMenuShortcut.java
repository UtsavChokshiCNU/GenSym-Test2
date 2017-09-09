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


public interface vbextMenuShortcut
{

  public static final Guid classID =
    new Guid(0x67c4d880, 0xbae5, 0x11ce,
             (short) 0x9a, (short) 0x59, (short) 0x0, (short) 0xaa,
             (short) 0x0, (short) 0x62, (short) 0xbb, (short) 0x4c);

    // Library name is: VBIDE
    // DocString is: Microsoft Visual Basic 5.0 Extensibility
    // Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
    // There are 108 TypeInfos in the library

/* Type info #83
    An enumeration type.
    Type info name is: vbextMenuShortcut
    Doc string is: User-defined shortcut keystrokes
    Help file is: C:\Program Files\DevStudio\VB\VB5EXT.HLP
 */

  public static final int VBEXT_MENU_SHORTCUT_CTRLA = 1;

  public static final int VBEXT_MENU_SHORTCUT_CTRLB = 2;

  public static final int VBEXT_MENU_SHORTCUT_CTRLC = 3;

  public static final int VBEXT_MENU_SHORTCUT_CTRLD = 4;

  public static final int VBEXT_MENU_SHORTCUT_CTRLE = 5;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF = 6;

  public static final int VBEXT_MENU_SHORTCUT_CTRLG = 7;

  public static final int VBEXT_MENU_SHORTCUT_CTRLH = 8;

  public static final int VBEXT_MENU_SHORTCUT_CTRLI = 9;

  public static final int VBEXT_MENU_SHORTCUT_CTRLJ = 10;

  public static final int VBEXT_MENU_SHORTCUT_CTRLK = 11;

  public static final int VBEXT_MENU_SHORTCUT_CTRLL = 12;

  public static final int VBEXT_MENU_SHORTCUT_CTRLM = 13;

  public static final int VBEXT_MENU_SHORTCUT_CTRLN = 14;

  public static final int VBEXT_MENU_SHORTCUT_CTRLO = 15;

  public static final int VBEXT_MENU_SHORTCUT_CTRLP = 16;

  public static final int VBEXT_MENU_SHORTCUT_CTRLQ = 17;

  public static final int VBEXT_MENU_SHORTCUT_CTRLR = 18;

  public static final int VBEXT_MENU_SHORTCUT_CTRLS = 19;

  public static final int VBEXT_MENU_SHORTCUT_CTRLT = 20;

  public static final int VBEXT_MENU_SHORTCUT_CTRLU = 21;

  public static final int VBEXT_MENU_SHORTCUT_CTRLV = 22;

  public static final int VBEXT_MENU_SHORTCUT_CTRLW = 23;

  public static final int VBEXT_MENU_SHORTCUT_CTRLX = 24;

  public static final int VBEXT_MENU_SHORTCUT_CTRLY = 25;

  public static final int VBEXT_MENU_SHORTCUT_CTRLZ = 26;

  public static final int VBEXT_MENU_SHORTCUTF1 = 27;

  public static final int VBEXT_MENU_SHORTCUTF2 = 28;

  public static final int VBEXT_MENU_SHORTCUTF3 = 29;

  public static final int VBEXT_MENU_SHORTCUTF4 = 30;

  public static final int VBEXT_MENU_SHORTCUTF5 = 31;

  public static final int VBEXT_MENU_SHORTCUTF6 = 32;

  public static final int VBEXT_MENU_SHORTCUTF7 = 33;

  public static final int VBEXT_MENU_SHORTCUTF8 = 34;

  public static final int VBEXT_MENU_SHORTCUTF9 = 35;

  public static final int VBEXT_MENU_SHORTCUTF11 = 37;

  public static final int VBEXT_MENU_SHORTCUTF12 = 38;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF1 = 39;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF2 = 40;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF3 = 41;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF4 = 42;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF5 = 43;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF6 = 44;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF7 = 45;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF8 = 46;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF9 = 47;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF11 = 49;

  public static final int VBEXT_MENU_SHORTCUT_CTRLF12 = 50;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF1 = 51;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF2 = 52;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF3 = 53;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF4 = 54;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF5 = 55;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF6 = 56;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF7 = 57;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF8 = 58;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF9 = 59;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF11 = 61;

  public static final int VBEXT_MENU_SHORTCUT_SHIFTF12 = 62;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF1 = 63;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF2 = 64;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF3 = 65;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF4 = 66;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF5 = 67;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF6 = 68;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF7 = 69;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF8 = 70;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF9 = 71;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF11 = 73;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_SHIFTF12 = 74;

  public static final int VBEXT_MENU_SHORTCUT_CTRL_INS = 75;

  public static final int VBEXT_MENU_SHORTCUT_SHIFT_INS = 76;

  public static final int VBEXT_MENU_SHORTCUT_DEL = 77;

  public static final int VBEXT_MENU_SHORTCUT_SHIFT_DEL = 78;

  public static final int VBEXT_MENU_SHORTCUT_ALT_BKSP = 79;


}

