 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      keypress.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +   XWindows portions:
 +              ??/??/?? - 07/15/88   Antony (Antony is not Jon Anthony)
 +              07/15/88 - ??/??/??   Brian Matthews, Mark H. David,
 +                                    Peng Tsin Ong
 +              ??/??/?? - 09/20/95   Ben Hyde, Fred White
 +              10/05/96 - 05/06/97   jv
 +   MS Windows portions:
 +              This code is all X-only; there are no MS Windows portions.
 +
 + Description:  This file contains the primitives used to perform keyboard
 +               event handling in XWindows only, and all definitions are
 +               conditionally compiled for X Windows only, while the Windows
 +               versions are generally in msmain.c and events.c.
 +
 +
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
 +   ??????? Function existence is questionable.
 +
 +   A function banner may contain the following:
 +      Multiply Defined       Function appears multiple times, each definition
 +                             for an #ifdef specified platform.
 +      Conditionally Defined  Defined for some but not all platforms
 +      Mixed Ifdefs           Single definition for function containing
 +                             platform specific code #ifdef's.
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - Event Functions
 +      g2pvt_initialize_event_handling   1111111 Conditionally Defined
 +      x11_adjusted_state_for_key_event  1111111 Conditionally Defined
 +      g2pvt_modifier_bits               1111111 Conditionally Defined
 +      g2_keycode_for_X_keysym           1111111 Conditionally Defined
 +      translate_broken_sun_keysyms      1111111 Conditionally Defined
 *      g2pvt_handle_keypress             1111111 Conditionally Defined
 +
 + External Interface:
 +      void     g2pvt_initialize_event_handling (display)
 +                 Determine how certain X events are handled for G2.
 +                 Returns: nothing
 +
 +      long     g2pvt_modifier_bits(state)
 +                 Compute the set of G2 modifier bits, given a set of X modifier bits.
 +                 Returns: return value
 +
 +      long     g2pvt_handle_keypress(event, display, gwindow)
 +                 Returns the value to return from g2ext_get_event for a keypress
 +                 Returns: the value to return from g2ext_get_event for a keypress
 +
 + Dependencies:
 +
 +
 + Notes:
 +   All functions in this file are XWINDOWS only.
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   07/12/96, mpc: Added calls to Windows code to perform translations
 +                between 32bit Handles and 30bit Lisp ints.
 +   09/28/95, mpc: Major structural reorganization to improve code legibility
 +                and maintainability.
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <signal.h>
#include "cprim.h"
#include "graphics.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/



#define ILLEGAL -1

/*
 * G2 Event Constants
 * This section defines the special G2 keycodes, ie, those
 * which differ from plain ASCII, as well as some masks
 * and modifier bits.
 */
/* Event times are 28 bits of non-negative milliseconds */
#define EVENT_TIME_MASK 0xFFFFFFF

#define BYTE_MASK 0xff
#define BYTE_SHIFT 8


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* handle_numlock_ourselves is set to 1 if we should check the modifier
   bits to translate keysyms which we expect to be default numeric
   keypad keysyms (Up, Down, Insert, etc.) into numeric numeric keypad
   keysyms (KP_8, KP_2, KP_0, etc.)  At this point, all we do to make
   that decision is check if we are talking to the Sun OpenWin X server.
   We assume, probably erroneously, that other X servers handle Num_Lock
   by themselves. */
static int handle_numlock_ourselves;

/* For debugging */
extern KeySym last_event_keysym;

/* For storing the last modifier keysym - used in g2ext_get_event */
static KeySym last_modifier_keysym;

/* X keysym to G2 keycode translation. */

/* Lookup tables for X keysyms, one for each recognized value of
 * the high byte. There are also vendor-specific keysyms, where the
 * high 16 bits are 0x100?, eg, 0x1000FF00 == DXK_Remove.  See
 * /usr/openwin/lib/XKeysymDB
 */
/* Special characters: backspace, linefeed, etc. */
static short keysym_to_g2_keycode_ff[256] =
{
    ILLEGAL,                /* 0xFF00  */
    ILLEGAL,                /* 0xFF01  */
    ILLEGAL,                /* 0xFF02  */
    ILLEGAL,                /* 0xFF03  */
    ILLEGAL,                /* 0xFF04  */
    ILLEGAL,                /* 0xFF05  */
    ILLEGAL,                /* 0xFF06  */
    ILLEGAL,                /* 0xFF07  */
    GENSYM_BACKSPACE,        /* 0xFF08 BackSpace */
    GENSYM_TAB,                /* 0xFF09 Tab */
    GENSYM_LINEFEED,        /* 0xFF0A Linefeed */
    GENSYM_CLEAR,        /* 0xFF0B Clear  (clear-screen in G2)*/
    ILLEGAL,                /* 0xFF0C  */
    GENSYM_RETURN,        /* 0xFF0D Return */
    ILLEGAL,                /* 0xFF0E  */
    ILLEGAL,                /* 0xFF0F  */
    ILLEGAL,                /* 0xFF10  */
    ILLEGAL,                /* 0xFF11  */
    ILLEGAL,                /* 0xFF12  */
    GENSYM_PAUSE,        /* 0xFF13 Pause */
    ILLEGAL,                /* 0xFF14 Scroll_Lock */
    ILLEGAL,            /* 0xFF15  */
    ILLEGAL,                /* 0xFF16  */
    ILLEGAL,                /* 0xFF17  */
    ILLEGAL,                /* 0xFF18  */
    ILLEGAL,                /* 0xFF19  */
    ILLEGAL,                /* 0xFF1A  */
    GENSYM_ESCAPE,        /* 0xFF1B Escape */
    ILLEGAL,                /* 0xFF1C  */
    ILLEGAL,                /* 0xFF1D  */
    ILLEGAL,                /* 0xFF1E  */
    ILLEGAL,                /* 0xFF1F  */
    ILLEGAL,                /* 0xFF20 Multi_key */
    ILLEGAL,                /* 0xFF21 Kanji */
    ILLEGAL,                /* 0xFF22 Muhenkan */
    ILLEGAL,                /* 0xFF23 Henkan_Mode */
    ILLEGAL,                /* 0xFF24 Romaji */
    ILLEGAL,                /* 0xFF25 Hiragana */
    ILLEGAL,                /* 0xFF26 Katakana */
    ILLEGAL,                /* 0xFF27 Hiragana_Katakana */
    ILLEGAL,                /* 0xFF28 Zenkaku */
    ILLEGAL,                /* 0xFF29 Hankaku */
    ILLEGAL,                /* 0xFF2A Zenkaku_Hankaku */
    ILLEGAL,                /* 0xFF2B Touroku */
    ILLEGAL,                /* 0xFF2C Massyo */
    ILLEGAL,                /* 0xFF2D Kana_Lock */
    ILLEGAL,                /* 0xFF2E Kana_Shift */
    ILLEGAL,                /* 0xFF2F Eisu_Shift */
    ILLEGAL,                /* 0xFF30 Eisu_toggle */
    ILLEGAL,                /* 0xFF31  */
    ILLEGAL,                /* 0xFF32  */
    ILLEGAL,                /* 0xFF33  */
    ILLEGAL,                /* 0xFF34  */
    ILLEGAL,                /* 0xFF35  */
    ILLEGAL,                /* 0xFF36  */
    ILLEGAL,                /* 0xFF37  */
    ILLEGAL,                /* 0xFF38  */
    ILLEGAL,                /* 0xFF39  */
    ILLEGAL,                /* 0xFF3A  */
    ILLEGAL,                /* 0xFF3B  */
    ILLEGAL,                /* 0xFF3C  */
    ILLEGAL,                /* 0xFF3D  */
    ILLEGAL,                /* 0xFF3E  */
    ILLEGAL,                /* 0xFF3F  */
    ILLEGAL,                /* 0xFF40  */
    ILLEGAL,                /* 0xFF41  */
    ILLEGAL,                /* 0xFF42  */
    ILLEGAL,                /* 0xFF43  */
    ILLEGAL,                /* 0xFF44  */
    ILLEGAL,                /* 0xFF45  */
    ILLEGAL,                /* 0xFF46  */
    ILLEGAL,                /* 0xFF47  */
    ILLEGAL,                /* 0xFF48  */
    ILLEGAL,                /* 0xFF49  */
    ILLEGAL,                /* 0xFF4A  */
    ILLEGAL,                /* 0xFF4B  */
    ILLEGAL,                /* 0xFF4C  */
    ILLEGAL,                /* 0xFF4D  */
    ILLEGAL,                /* 0xFF4E  */
    ILLEGAL,                /* 0xFF4F  */
    GENSYM_HOME,        /* 0xFF50 Home */
    GENSYM_LEFT_ARROW,        /* 0xFF51 Left */
    GENSYM_UP_ARROW,        /* 0xFF52 Up */
    GENSYM_RIGHT_ARROW,        /* 0xFF53 Right */
    GENSYM_DOWN_ARROW,        /* 0xFF54 Down */
    GENSYM_PRIOR,        /* 0xFF55 Prior */
    GENSYM_NEXT,        /* 0xFF56 Next */
    GENSYM_END,                /* 0xFF57 End */
    GENSYM_BEGIN,        /* 0xFF58 Begin */
    ILLEGAL,                /* 0xFF59  */
    ILLEGAL,                /* 0xFF5A  */
    ILLEGAL,                /* 0xFF5B  */
    ILLEGAL,                /* 0xFF5C  */
    ILLEGAL,                /* 0xFF5D  */
    ILLEGAL,                /* 0xFF5E  */
    ILLEGAL,                /* 0xFF5F  */
    GENSYM_SELECT,        /* 0xFF60 Select */
    GENSYM_PRINT,        /* 0xFF61 Print */
    GENSYM_EXECUTE,        /* 0xFF62 Execute */
    GENSYM_INSERT,        /* 0xFF63 Insert */
    ILLEGAL,                /* 0xFF64  */
    GENSYM_UNDO,        /* 0xFF65 Undo */
    GENSYM_REDO,        /* 0xFF66 Redo */
    GENSYM_MENU,        /* 0xFF67 Menu */
    GENSYM_FIND,        /* 0xFF68 Find */
    GENSYM_CANCEL,        /* 0xFF69 Cancel  (Abort (c-a) in G2) */
    GENSYM_HELP,        /* 0xFF6A Help */
    GENSYM_BREAK,        /* 0xFF6B Break */
    ILLEGAL,                /* 0xFF6C  */
    ILLEGAL,                /* 0xFF6D  */
    ILLEGAL,                /* 0xFF6E  */
    ILLEGAL,                /* 0xFF6F  */
    ILLEGAL,                /* 0xFF70  */
    ILLEGAL,                /* 0xFF71  */
    ILLEGAL,                /* 0xFF72  */
    ILLEGAL,                /* 0xFF73  */
    ILLEGAL,                /* 0xFF74  */
    ILLEGAL,                /* 0xFF75  */
    ILLEGAL,                /* 0xFF76  */
    ILLEGAL,                /* 0xFF77  */
    ILLEGAL,                /* 0xFF78  */
    ILLEGAL,                /* 0xFF79  */
    ILLEGAL,                /* 0xFF7A  */
    ILLEGAL,                /* 0xFF7B  */
    ILLEGAL,                /* 0xFF7C  */
    ILLEGAL,                /* 0xFF7D  */
    ILLEGAL,                /* 0xFF7E Mode_switch */
    ILLEGAL,                /* 0xFF7F Num_Lock */
    GENSYM_KP_Space,        /* 0xFF80 KP_Space */
    ILLEGAL,                /* 0xFF81  */
    ILLEGAL,                /* 0xFF82  */
    ILLEGAL,                /* 0xFF83  */
    ILLEGAL,                /* 0xFF84  */
    ILLEGAL,                /* 0xFF85  */
    ILLEGAL,                /* 0xFF86  */
    ILLEGAL,                /* 0xFF87  */
    ILLEGAL,                /* 0xFF88  */
    GENSYM_KP_Tab,        /* 0xFF89 KP_Tab */
    ILLEGAL,                /* 0xFF8A  */
    ILLEGAL,                /* 0xFF8B  */
    ILLEGAL,                /* 0xFF8C  */
    GENSYM_KP_Enter,        /* 0xFF8D KP_Enter */
    ILLEGAL,                /* 0xFF8E  */
    ILLEGAL,                /* 0xFF8F  */
    ILLEGAL,                /* 0xFF90  */
    GENSYM_KP_F1,        /* 0xFF91 KP_F1 */
    GENSYM_KP_F2,        /* 0xFF92 KP_F2 */
    GENSYM_KP_F3,        /* 0xFF93 KP_F3 */
    GENSYM_KP_F4,        /* 0xFF94 KP_F4 */
    ILLEGAL,                /* 0xFF95  */
    ILLEGAL,                /* 0xFF96  */
    ILLEGAL,                /* 0xFF97  */
    ILLEGAL,                /* 0xFF98  */
    ILLEGAL,                /* 0xFF99  */
    ILLEGAL,                /* 0xFF9A  */
    ILLEGAL,                /* 0xFF9B  */
    ILLEGAL,                /* 0xFF9C  */
    ILLEGAL,                /* 0xFF9D  */
    ILLEGAL,                /* 0xFF9E  */
    ILLEGAL,                /* 0xFF9F  */
    ILLEGAL,                /* 0xFFA0  */
    ILLEGAL,                /* 0xFFA1  */
    ILLEGAL,                /* 0xFFA2  */
    ILLEGAL,                /* 0xFFA3  */
    ILLEGAL,                /* 0xFFA4  */
    ILLEGAL,                /* 0xFFA5  */
    ILLEGAL,                /* 0xFFA6  */
    ILLEGAL,                /* 0xFFA7  */
    ILLEGAL,                /* 0xFFA8  */
    ILLEGAL,                /* 0xFFA9  */
    GENSYM_KP_Multiply, /* 0xFFAA KP_Multiply */
    GENSYM_KP_Add,        /* 0xFFAB KP_Add  */
    GENSYM_KP_Separator, /* 0xFFAC KP_Separator */
    GENSYM_KP_Subtract, /* 0xFFAD KP_Subtract */
    GENSYM_KP_Decimal,        /* 0xFFAE KP_Decimal */
    GENSYM_KP_Divide,        /* 0xFFAF KP_Divide   */
    GENSYM_KP_0,        /* 0xFFB0 KP_0 */
    GENSYM_KP_1,        /* 0xFFB1 KP_1 */
    GENSYM_KP_2,        /* 0xFFB2 KP_2 */
    GENSYM_KP_3,        /* 0xFFB3 KP_3 */
    GENSYM_KP_4,        /* 0xFFB4 KP_4 */
    GENSYM_KP_5,        /* 0xFFB5 KP_5 */
    GENSYM_KP_6,        /* 0xFFB6 KP_6 */
    GENSYM_KP_7,        /* 0xFFB7 KP_7 */
    GENSYM_KP_8,        /* 0xFFB8 KP_8 */
    GENSYM_KP_9,        /* 0xFFB9 KP_9 */
    ILLEGAL,                /* 0xFFBA  */
    ILLEGAL,                /* 0xFFBB  */
    ILLEGAL,                /* 0xFFBC  */
    GENSYM_KP_Equal,        /* 0xFFBD KP_Equal */
    GENSYM_F1,                /* 0xFFBE F1 */
    GENSYM_F2,                /* 0xFFBF F2 */
    GENSYM_F3,                /* 0xFFC0 F3 */
    GENSYM_F4,                /* 0xFFC1 F4 */
    GENSYM_F5,                /* 0xFFC2 F5 */
    GENSYM_F6,                /* 0xFFC3 F6 */
    GENSYM_F7,                /* 0xFFC4 F7 */
    GENSYM_F8,                /* 0xFFC5 F8 */
    GENSYM_F9,                /* 0xFFC6 F9 */
    GENSYM_F10,                /* 0xFFC7 F10 */
    GENSYM_F11,                /* 0xFFC8 F11 */
    GENSYM_F12,                /* 0xFFC9 F12 */
    GENSYM_F13,                /* 0xFFCA F13 */
    GENSYM_F14,                /* 0xFFCB F14 */
    GENSYM_F15,                /* 0xFFCC F15 */
    GENSYM_F16,                /* 0xFFCD F16 */
    GENSYM_F17,                /* 0xFFCE F17 */
    GENSYM_F18,                /* 0xFFCF F18 */
    GENSYM_F19,                /* 0xFFD0 F19 */
    GENSYM_F20,                /* 0xFFD1 F20 */
    GENSYM_F21,                /* 0xFFD2 F21 */
    GENSYM_F22,                /* 0xFFD3 F22 */
    GENSYM_F23,                /* 0xFFD4 F23 */
    GENSYM_F24,                /* 0xFFD5 F24 */
    GENSYM_F25,                /* 0xFFD6 F25 */
    GENSYM_F26,                /* 0xFFD7 F26 */
    GENSYM_F27,                /* 0xFFD8 F27 */
    GENSYM_F28,                /* 0xFFD9 F28 */
    GENSYM_F29,                /* 0xFFDA F29 */
    GENSYM_F30,                /* 0xFFDB F30 */
    GENSYM_F31,                /* 0xFFDC F31 */
    GENSYM_F32,                /* 0xFFDD F32 */
    GENSYM_F33,                /* 0xFFDE F33 */
    GENSYM_F34,                /* 0xFFDF F34 */
    GENSYM_F35,                /* 0xFFE0 F35 */
    ILLEGAL,                /* 0xFFE1 Shift_L */
    ILLEGAL,                /* 0xFFE2 Shift_R */
    ILLEGAL,                /* 0xFFE3 Control_L */
    ILLEGAL,                /* 0xFFE4 Control_R */
    ILLEGAL,                /* 0xFFE5 Caps_Lock */
    ILLEGAL,                /* 0xFFE6 Shift_Lock */
    ILLEGAL,                /* 0xFFE7 Meta_L */
    ILLEGAL,                /* 0xFFE8 Meta_R */
    ILLEGAL,                /* 0xFFE9 Alt_L */
    ILLEGAL,                /* 0xFFEA Alt_R */
    ILLEGAL,                /* 0xFFEB Super_L */
    ILLEGAL,                /* 0xFFEC Super_R */
    ILLEGAL,                /* 0xFFED Hyper_L */
    ILLEGAL,                /* 0xFFEE Hyper_R */
    ILLEGAL,                /* 0xFFEF  */
    ILLEGAL,                /* 0xFFF0  */
    ILLEGAL,                /* 0xFFF1  */
    ILLEGAL,                /* 0xFFF2  */
    ILLEGAL,                /* 0xFFF3  */
    ILLEGAL,                /* 0xFFF4  */
    ILLEGAL,                /* 0xFFF5  */
    ILLEGAL,                /* 0xFFF6  */
    ILLEGAL,                /* 0xFFF7  */
    ILLEGAL,                /* 0xFFF8  */
    ILLEGAL,                /* 0xFFF9  */
    ILLEGAL,                /* 0xFFFA  */
    ILLEGAL,                /* 0xFFFB  */
    ILLEGAL,                /* 0xFFFC  */
    ILLEGAL,                /* 0xFFFD  */
    ILLEGAL,                /* 0xFFFE  */
    GENSYM_DELETE        /* 0xFFFF Delete */
};


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Event Functions
 %
 % Description:
 %   These functions are for event management
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * void g2pvt_initialize_event_handling (Display *display)
 *
 *   Description:
 *     Determine how certain X events are handled for G2. Only has any potential
 *     effect on Sun machines (even though it's not #ifdef'ed) that way.
 *   Input Arguments:
 *     display:
 *   Returns:
 *     nothing
 *   Notes: not to be confused with ne_initialize_event_handling, which lives
 *     in sckevent.c (for Unix, anyway).  Not to be confused, but perhaps to
 *     be combined with.  Or eliminated.  Is this even a problem any more?  Was
 *     it ever a problem on Solaris, or was it just SunOS 4?  Who knows.  Leave
 *     it like this until someone cares, which means forever.  -jv, 12/17/07
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
void g2pvt_initialize_event_handling (display)
     Display *display;
{
    if (ServerVendor(display) &&
        !strcmp(ServerVendor(display),"X11/NeWS - Sun Microsystems Inc."))
        handle_numlock_ourselves = 1;
    else
        handle_numlock_ourselves = 0;
}
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * int x11_adjusted_state_for_key_event (ke)
 *
 *   Description:
 *     Turns off the shift and/or Mod1 bits if they are implicit in the keysym.
 *   Input Arguments:
 *     ke
 *   Returns:
 *     return value: an adjusted key state
 *   Notes:
 *   Modifications:
 *     ajs, 4/26/96.  Restrict the fix for German keyboards in the function
 *       x11_adjusted_state_for_key_event to cases where Alt Graphics is the
 *       modifier.  Note this relies upon an event produced by X for the depression
 *       of the Alt Graphics key. See the related bugs HQ-544721 and HQ-416789.
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
static int x11_adjusted_state_for_key_event (ke, pkeysym)
     XKeyEvent *ke;
     KeySym *pkeysym;
{
  KeySym actual, other;
  int state = ke->state;
  int keysym_lookup_index;

  if (state & Mod1Mask) {
    /* The index into the list of keysyms for a given key event.
       Mostly documented to be none=0, shift=1, mod1=2, shift+mod1=3
       In any case, this is the way xemacs handles the problem.
       */
    keysym_lookup_index = (state & ShiftMask) ? 3 : 2;

    actual = XLookupKeysym(ke, keysym_lookup_index);

    /* If the Mod1 bit is set, but we'd get a different keysym if we cleared it,
       then the Mod1 bit is implicit. */
    other = XLookupKeysym(ke,keysym_lookup_index - 2);
    if (actual != NoSymbol && other != NoSymbol && actual != other)
      if ((last_modifier_keysym == XK_Alt_R) || (last_modifier_keysym == XK_Meta_R))
        state &= ~Mod1Mask;
      else
        *pkeysym = other;
  }
  return state;
}
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * long g2pvt_modifier_bits (state)
 *
 *   Description:
 *     Compute the set of G2 modifier bits, given a set of X modifier bits.
 *   Input Arguments:
 *     state
 *   Returns:
 *     return value:
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/
long g2pvt_modifier_bits (state)
     int state;
{
    long modifier_bits = 0;

    if (state & ControlMask)
        modifier_bits |= X11_CONTROL_BIT;

    if (state & ShiftMask)
        modifier_bits |= X11_SHIFT_BIT;

    if (state & LockMask)
        modifier_bits |= X11_CAPS_LOCK_BIT;

    if (state & Mod1Mask)    /* G2 considers this equivalent to ALT. */
        modifier_bits |= X11_META_BIT;

    if (state & Mod4Mask)
        modifier_bits |= X11_ALTERNATE_BIT;

    return modifier_bits;
}
/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*****************************************************************************
 * long g2_keycode_for_X_keysym(keysym,state)
 *
 *   Description:
 *     Compute the G2 keycode and modifier bits for a standard X keysym
 *   Input Arguments:
 *     keysym:  X keysym.
 *     state:   X modifier bits
 *   Returns:
 *     return value: keycode on success, -1 if no corresponding G2 character
 *   Notes:
 *       The printing ASCII characters are passed thru as their ASCII codes.
 *     However, other random keys which are not strictly ASCII, like linefeed,
 *     backspace, tab, (no these are not ASCII, c-j, c-h, and c-i are ASCII),
 *     are converted to COMPLETELY RANDOM, UNRELATED G2 key codes.  For example,
 *     linefeed should be returned as 280, backspace as 278, and so on.  This
 *     conversion, being so random, is implemented with the table lookup above.
 *     (The ASCII conversion is also done by table lookup, for convenience).
 *     -----
 *       Note: G2 does some further munching on the key code in lisp.  See
 *     get-local-event in platforms.lisp
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
static long g2_keycode_for_X_keysym(keysym,state)
     KeySym keysym;
     int state;
{
    int highbyte, lowbyte, key_code;

    highbyte = (keysym>>BYTE_SHIFT) & BYTE_MASK;
    lowbyte = keysym & BYTE_MASK;

    /* G2 does not want to see keypresses on modifier keys */
    if (IsModifierKey(keysym))
        return ILLEGAL;

    switch (highbyte) {
    case 0:
        key_code = lowbyte;
        break;

    case BYTE_MASK:
        key_code = keysym_to_g2_keycode_ff[lowbyte];
        if (key_code == ILLEGAL)
            key_code = keysym;
        break;

    default:
        key_code = keysym;
        break;
    }

    return g2pvt_modifier_bits(state) | key_code;
}
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * KeySym translate_broken_sun_keysyms (display, keycode, keysym, state)
 *
 *   Description:
 *     If we are talking to the brain-dead Sun Openwindows X server, then
 *     handle num_lock (mod3) and the number key pad ourselves,
 *   Input Arguments:
 *     display
 *     keycode
 *     keysym
 *     state
 *   Returns:
 *     return value:
 *   Notes:
 *       If we are talking to the brain-dead Sun Openwindows X server, then
 *     handle num_lock (mod3) and the number key pad ourselves, as all good
 *     OpenWindows clients are want to do.  G2 converts the KP numbers into
 *     real numbers itself.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
static KeySym translate_broken_sun_keysyms (display, keycode, keysym, state)
     Display *display;
     int keycode;        /* Needed to disambiguate arrow keys and delete */
     KeySym keysym;
     int state;
{
    KeySym keysym2;

    /* The Num_Lock bit for this server (assuming no xmodmap remapping) is Mod3.
       This table assumes a Sun type 5 or type 4 keyboard.  I don't know what it
       might do to other keyboards.

       We could make home, pgup, end, and pgdn work while we are at it.
     */

    keysym2 = XKeycodeToKeysym(display, keycode, 1);

    if(state&Mod3Mask) {
        /* In these clauses, the first disjunct is the Sun Type5 keysym, and the
           second disjunct, if any, is the Sun Type4 keysym */
        if (keysym == XK_Insert)
            keysym = XK_KP_0;
        else if (keysym == XK_F33)
            keysym = XK_KP_1;
        else if (keysym == XK_Down && (keysym2 == XK_KP_2 || keysym2 == XK_F34))
            keysym = XK_KP_2;
        else if (keysym == XK_F35)
            keysym = XK_KP_3;
        else if (keysym == XK_Left && (keysym2 == XK_KP_4 || keysym2 == XK_F30))
            keysym = XK_KP_4;
        else if (keysym == XK_F31)
            keysym = XK_KP_5;
        else if (keysym == XK_Right && (keysym2 == XK_KP_6 || keysym2 == XK_F32))
            keysym = XK_KP_6;
        else if (keysym == XK_F27)
            keysym = XK_KP_7;
        else if (keysym == XK_Up && (keysym2 == XK_KP_8 || keysym2 == XK_F28))
            keysym = XK_KP_8;
        else if (keysym == XK_F29)
            keysym = XK_KP_9;
        else if (keysym == XK_F25)
            keysym = XK_KP_Divide;
        else if (keysym == XK_F26)
            keysym = XK_KP_Multiply;
        else if (keysym == XK_F24 || keysym == XK_KP_Subtract)
            keysym = XK_KP_Subtract;
        else if (keysym == XK_KP_Add)
            keysym = XK_KP_Add;
        else if (keysym == XK_KP_Enter)
            keysym = XK_KP_Enter;
        else if (keysym == XK_Delete &&
                 (keysym2 == XK_KP_Decimal || keysym2 == XK_Delete))
            keysym = XK_KP_Decimal;
    }
    return keysym;
}
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * long g2pvt_handle_keypress(event, display, gwindow)
 *
 *   Description:
 *     Handle an X keypress, putting it through all the munging we do to it.
 *   Input Arguments:
 *     event, display, gwindow
 *   Returns:
 *     the value to return from g2ext_get_event
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
long g2pvt_handle_keypress (event, display, gwindow)
     XEvent *event;
     Display *display;
     GensymXWindow *gwindow;
{
  XKeyEvent *k;
  unsigned int state;
  int keycode;
  long g2_keycode, return_value;

  KeySym keysym;
  static XComposeStatus compose;
  char buf[3];


  k = (XKeyEvent *)event;

  /* We use XLookupString to get the standard shift/meta handling,
     but we use only the keysym. */
  XLookupString((XKeyEvent *)event, buf, 2, &keysym, &compose);

  state = x11_adjusted_state_for_key_event(k, &keysym);

  gwindow->last_mouse_x = (long) k->x;
  gwindow->last_mouse_y = (long) k->y;
  gwindow->last_event_bits = g2pvt_modifier_bits(state);

  gwindow->last_event_time = k->time;

#ifdef TEST_CPRIM
  last_event_keysym = keysym;
#endif

  /* Store the last modifier keysym */
  if(IsModifierKey(keysym))
    last_modifier_keysym = keysym;

  if (keysym == NoSymbol)
    return X11_NULLEVENT;

  keycode = k->keycode;

  if (handle_numlock_ourselves)
    keysym = translate_broken_sun_keysyms(display,keycode,keysym,state);

  g2_keycode = g2_keycode_for_X_keysym(keysym,state);

  if (g2_keycode == -1)         /* Unknown or non-printing character */
    return X11_NULLEVENT;     /* (eg. the control key) */

  return_value = (g2_keycode << X11_NUMBER_OF_BITS_IN_EVENT_CODES)
    | X11_KEYPRESS;  /* for easy breakpointing and data examination */

  return return_value;
}
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

