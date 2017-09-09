/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      clipboard.c
 +
 + Multiplatform Cut and Paste
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Notes
 +   Carved out of graphics.c on 7/11/02
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if defined(WIN32)
#    include <string.h>
#    include <math.h>
#    include <windows.h>
#    include "msincls.h"
#else
#    include <signal.h>
#    include <stdlib.h>
#endif

#include "cprim.h"
#include "graphics.h"

#define Min(a,b) (((a)<(b)) ? (a) : (b))

extern int No_window;

#if defined(XWINDOWS)
extern long g2ext_sys_sleep (/* long */);  /* networks.c */
#endif

/* 
** Cut and Paste Constants
** These constants have to be maintained in parallel with those in 
** the lisp module PLATFORMS:
** (defconstant latin-1-clipboard-read-results-entry 0)
** (defconstant x-compound-text-clipboard-read-results-entry 1)
** (defconstant unicode-text-clipboard-read-results-entry 2)
** (defconstant clipboard-read-results-failure-code #xFFFF)
** (defconstant specified-max-clipboard-text-length #.(- (expt 2 15) 1))
*/
#define LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY 0
#define COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY 1
#define UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY 2
#define CLIPBOARD_READ_RESULTS_FAILURE_CODE 0xFFFF
/* clipboard length is in terms of characters, not bytes */
#define SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH 65535


/* These globals are used for both X Windows and MS Windows */
long latin_1_clipboard_char_count = 0;
long compound_text_clipboard_char_count = 0;
long unicode_text_clipboard_char_count = 0;

#ifdef MSWINDOWS
 static BOOL need_to_init = TRUE;
#endif

#ifdef XWINDOWS
 unsigned char  *latin_1_clipboard = (unsigned char*)NULL;
 unsigned char  *compound_text_clipboard = (unsigned char*)NULL;
 unsigned short *unicode_text_clipboard = (unsigned short*)NULL;
 Atom            selection_atom = None;
 /* the atom we use for latin-1 is named XA_STRING, pre-defined in X */
 Atom	    compound_text_atom = None; 
 Atom	    unicode_text_atom = None;
 /* to do:  targets_atom unused: remove all references */
 Atom	    targets_atom = None;
 Atom	    data_prop = None;
 /* to do:  rep_types unused: remove */
 Atom	   *rep_types = (Atom*)NULL;	/* memory allocated later */
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Cut and Paste
 %
 % Description:
 %   These functions provide cut and paste functionality for MS Windows and X
 % Windows. Both systems support a buffer used to cut and paste text and 
 % graphics called the Clipboard, however, it is used quite differently on 
 % either system. In addition, X Windows has a text-only set of buffers called
 % cut buffers. 
 %
 % The recomended multiplatform interfaces provided in this section are
 % g2ext_write_clipboards() and  g2ext_read_clipboards(), which use the Clipboard
 % (see their description below). To  determine whether there is 
 % something available to paste (useful to determine when to display a
 % paste button), use g2ext_x11_clipboard_has_text() (named from an  old 
 % tradition: it does work on MS Windows). 
 %
 % The X cut buffer 0 is used in some parts of G2. Access is provided through 
 % g2ext_x11_read_cut_buffer() and g2ext_x11_write_cut_buffer() (on MS Windows, these 
 % functions use the Clipboard). The X cut buffer interface is a simple system
 % call: see the above mentioned functions for more details.
 %
 % HOW DOES THE CLIPBOARD WORK?
 %
 % As stated above, both MS Windows and X Windows have a buffer used for 
 % transferring text and graphics between or within applications called
 % the Clipboard. The MS Windows Clipboard system calls are quite
 % straightforward. The use of the X Windows Clipboard is quite complex
 % and requires event handling. Unlike the MS Windows Clipboard, each
 % client is repsonsible for handling requests for clipboard data and
 % serving them up in the requested formats.  Here is an overview of
 % both Clipboards.
 %
 % THE MS WINDOWS CLIPBOARD
 %
 % Under MS Windows, you are encouraged to write your data to the clipboard 
 % in as many formats as you have. However, Micosoft claims to do automatic 
 % conversion between text (CF_TEXT) and UNICODE (CF_UNICODETEXT). I think we 
 % will ignore that for now. 
 % To copy info to the clipboard:
 % 1. OpenClipboard()
 % 2. EmptyClipboard() -- you become owner
 % 3. SetClipboardData() -- 
 %      you are encouraged to write to the clipboard with as many data formats 
 %      as you have, but you must do it all at once, because for one thing this
 %      routine clears the clipboard, but also any successive OpenClipboard is 
 %      probably seen as new data (not old data in new format). 
 % 4. CloseClipboard()
 % Documentation on these functions and the Clipboard can be found on-line in
 % Microsoft Developer Studio. After closing the Clipboard, the OS handles 
 % all requests for clipboard data, and you don't  even know that people are
 % reading your data. 
 %
 % What happens if the Clipboard owner dies? (MS Windows): the clipboard data 
 % remains available because the MS OS is managing the clipboard.
 % 
 % The text format used under MS Windows is called CF_TEXT (to be used for 
 % ANSI text). MS Windows also has Unicode. Both are a "Text format. Each 
 % line ends with a carriage return/linefeed (CR-LF) combination. A null 
 % character signals the end of the data." To see definitions of these MS
 % Windows formats, see Microsoft Developer Studio: help; search; 
 % SetClipboardData.
 % 
 % THE X WINDOWS CLIPBOARD
 %
 % X Windows has two ways to transfer text between applications: cut 
 % buffers and selections. We mentioned above that G2 uses cut buffers
 % in some cases. The standard X selections are PRIMARY, SECONDARY and
 % CLIPBOARD (an application can also define its own). Most X
 % applications are using the PRIMARY selection when some text has 
 % been highlighted by the mouse, and the CLIPBOARD when a menu choice
 % of cut, copy or paste has been selected (these menu choices are
 % usually on an edit menu). The Clipboard functions in this section
 % use the CLIPBOARD selection under X Windows (as you might have guessed). 
 %
 % To copy data to the Clipboard:
 %
 % 1. XSetSelectionOwner() -- set yourself as owner
 % 2. XGetSelectionOwner() -- to verify #1 worked
 % 3. Copy data to some local storage place in whatever formats you
 % have. (In the following code we store data in several different 
 % formats, in global variables.) Now you have to serve X selection
 % requests (even ones from yourself!). When you get them (in events.c),
 % you serve requests for data in whatever format was requested, if you
 % happen to have that format stored. 
 %
 % To read from the Clipboard:
 % 
 % (more needed here)
 %
 % What happens if the Clipboard owner dies? (X Windows): clipboard data is
 % lost, and the clipboard is empty (unless there is a special clipboard client 
 % running on that particular machine).
 %
 % HOW LONG IS MY DATA?
 %
 % The length of the data depends on the underlying platform.  MS Windows
 % defines the end of text to be the null character  (see above paragraphs), 
 % so the MS Windows implementation does not handle embedded nulls at the 
 % moment.  The X windows platform does handle embedded nulls. So, if
 % cross-platform use is a concern, this may not be usable for all purposes.
 % Ordinarily, text data does not contain nulls, and so this should be
 % universally usable for the purpose of ordinary text data exchange.
 % 
 % TO DO
 %
 % (X Windows) Instead of storing all data formats upon copy, store 
 % one format and convert upon demand. This requires more message passing
 % between Lisp and C; right now when the C code gets a request for clipboard
 % contents, it can serve them up without Lisp getting involved at all. With
 % convert-on-demand, C would have to request conversion from Lisp.
 % 
 % Notes:
 %
 %   This section has some routines defined only for MS Windows, and some 
 %   defined only for X Windows. Some of these separate routines have no 
 %   counterpart in the other OS.
 %
 %
 % Modifications:
 %
 % To do:
 %   Remove code that is ifdef'ed out.
 %
 %
 %
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*****************************************************************************
 * long g2ext_x11_clipboard_has_text(window_index)
 *
 *   Description: 
 *     Determines if there is anything available to "paste" from the
 *     OS clipboard. Used to determine when it is ok to display
 *     the paste button in the editor. Checks for either UNICODE or
 *     TEXT formats.
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return value: 0 if paste not available, 1 if paste available
 *   Notes:
 *     - XGetSelectionOwner() calls select() (can take time). 
 *     - Later, code that calls this function may want to know about other 
 *       types of data that can go in the clipboard (e.g. bitmaps, graphics). 
 *     - no need to actually get the data or number of bytes in the data.
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_clipboard_has_text(window_index)
    long window_index;
{

  if (No_window)
    return 0;

#if defined(MSWINDOWS)
  /* If CF_UNICODETEXT is available, MS Windows will report CF_TEXT 
   * available too, I think,
   * because it automatically converts between those formats. (lgibson)
   */
    if (IsClipboardFormatAvailable(CF_TEXT))
        return 1;
    else
        return 0;      
#else /* XWindows */

    {
    GensymXWindow *gensym_window;
    gensym_window = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

    if (None == selection_atom)
        selection_atom = XInternAtom(gensym_window->display_ptr, 
				   "CLIPBOARD", False); /* "PRIMARY" */
    if (None != XGetSelectionOwner(gensym_window->display_ptr, selection_atom))
        return 1;
    else 
        return 0;

    /* the above means: someone owns the selection, but it could be
     * empty. But this step saves
     * fetching the data and checking for null, which is expensive. We
     * have to prepare to have NULL pasted in anyway, so no great
     * loss.  
     */


#ifdef ORIGINAL
    /* The following obselete code checked if there was anything in the
     * CUT BUFFER (not the CLIPBOARD).
     */
    GensymXWindow *gensym_window;
    Display *display;
    char *buf;
    int nbytes;

    if (No_window)
      return 0;

    gensym_window = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    display = gensym_window->display_ptr;

    buf = XFetchBytes(display, &nbytes);
    if (nbytes > 0) {
      XFree(buf);		/* (Issue discussed at same call site below!) */
      return nbytes;
    }
    else
      return 0;
#endif /* ORIGINAL */
    }
#endif
}    

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/
/*****************************************************************************
 * int g2ext_x11_clipboard_x_targets_p(window_index)
 *
 *   Description: 
 *     Return 1 if (really) X Windows; 0 if not (i.e., really MS Windows)
 *   Input Arguments: window_index
 *     Currently ignored, but may be needed in the future.
 *   Notes:
 *     If this returns 1, the then G2's X clipboard formats
 *     should be used (x-string, x-compound-text, and unicode); otherwise,
 *     G2's MS Windows clipboard formats should be used (cf-text and
 *     cf-unicode).  Used by write-clipboard in platforms.lisp.
 *****************************************************************************/

int g2ext_x11_clipboard_x_targets_p (window_index)
        int window_index;
{
  return(
#if defined(XWINDOWS)
	 1
#else
	 0
#endif
	 );
}


/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

#ifdef OLD_TARGETS_CODE
static Bool check_selection_notify(event)
    XEvent *event; 
{
    return (SelectionNotify == event->type)||(SelectionRequest == event->type);
}
#endif

/*****************************************************************************
 * static Bool fetch_event (display, event)
 *
 *   Description: 
 *     Check if this X event is a selection event.
 *     It's possible that the other end of the exchange doesn't 
 *     properly send us a SelectionNotify event, so hanging is a 
 *     possibility. So do our own blocking; but of course we raise
 *     a bunch of portability issues this way. To hopefully avoid 
 *     portability issues, call g2ext_sys_sleep. 
 *     Jim Allard says don't call g2ext_sys_sleep more often than 50 ms,
 *     wait (in total) no more than 250ms on G2, 5 seconds on TW.
 *     But current code doesn't know whether it is TW or G2. 
 *   Input Arguments:
 *   Returns:
 *     return value: Boolean. T means SelectionRequest or 
 *       SelectionNotify event found. 
 *     event: the selection event, if one was found in the time
 *       alloted; else the last X event.
 *   Notes: 
 *   To Do: instead of called g2ext_sys_sleep, call G2 task scheduler:
 *     see HQ-1425433
 *   Modifications:
 *****************************************************************************/

#if defined(XWINDOWS)
static Bool fetch_event (display, event)
    Display *display;
    XEvent *event;	/* RETURN */
{
  int count = 0;

  while (count < 80)	/* arbitrary: 80 X 50msec = 4 seconds */
    {
      count++;
      g2ext_sys_sleep(50);    /* sleep 50 milliseconds. Calls select() on unix */

      if (XCheckTypedEvent (display, SelectionRequest, event) ||
	  XCheckTypedEvent (display, SelectionNotify, event))
	return TRUE;	/* got it, else loop around again  */
    }
  return FALSE;         /* timeout */
}
#endif


/*****************************************************************************
 * static unsigned short get_property_value(display, buffer, max_size, event)
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   To Do:
 *   Modifications:
 *****************************************************************************/

#if defined(XWINDOWS)
static unsigned short get_property_value(display, buffer, max_size, event)
  Display *display;
  char    *buffer;
  long     max_size;
  XEvent  *event;
{
  Atom           ret_type;
  int            ret_format;
  unsigned long  ret_len;
  unsigned long  ret_after;
  unsigned char *value;
  int            val;

  if (Success == (val = XGetWindowProperty(display,
					   event->xselection.requestor,
					   event->xselection.property,
					   0L, max_size-1, True,
					   AnyPropertyType, 
					   &ret_type, &ret_format, &ret_len,
					   &ret_after, &value)))
    {
      if ((ret_format==EIGHT_BIT_FORMAT) && (ret_len > 0))
	{
	  unsigned short number_of_bytes_to_copy = Min(ret_len, max_size-1);
	  memcpy(buffer,value,number_of_bytes_to_copy);
	  buffer[number_of_bytes_to_copy] = '\0';
	  XFree(value); /* is calling XFree a problem???? */
	  return number_of_bytes_to_copy;
	}
      else
	return (unsigned short)CLIPBOARD_READ_RESULTS_FAILURE_CODE;
    }
  else
    {
      return (unsigned short)CLIPBOARD_READ_RESULTS_FAILURE_CODE;
    }
}
#endif

/*****************************************************************************
 * static int fetch_8bit_data(display, buffer, max_size, gensym_window, which_atom)
 *
 *   Description: 
 *     
 *   Input Arguments:
 *   Returns:
 *     return value: 
 *   Notes:
 *     Does XGetWindowProperty retrieve strings with embedded nulls, if
 *     that is how they were stored? Hard to tell from doc.
 *   Modifications:
 *****************************************************************************/

#if defined(XWINDOWS)
static unsigned short fetch_8bit_data (display, buffer, max_size, gensym_window, which_atom)
  Display *display;
  char *buffer;
  long max_size;
  GensymXWindow *gensym_window;
  Atom which_atom;
{
  XEvent event;

  XConvertSelection(display, selection_atom, which_atom, 
		    data_prop, gensym_window->xwindow, 
		    gensym_window->last_event_time);
  if (fetch_event(display, &event))
    {
      if ((event.type == SelectionNotify) &&
	  (event.xselection.selection == selection_atom) &&
	  (event.xselection.property != None))
	{
	  return get_property_value(display, buffer, max_size, &event);
	}
    }
  return (unsigned short)CLIPBOARD_READ_RESULTS_FAILURE_CODE;
}
#endif


#if defined(XWINDOWS) && defined(TARGETS_CODE)
static Bool check_target(display, values,atom_count,which_atom)
        Display *display;
	Atom *values;
        unsigned long atom_count;
	Atom which_atom;
{
	int i;

	for (i=0;i<atom_count;i++)
	{

		if (0)	/* debug (inefficient) */
		{
		char *s1,*s2;
		printf ("\tchecking %s against %s\n",
			s1=XGetAtomName(display,which_atom),
			s2=XGetAtomName(display,values[i]));
		fflush (stdout);
		XFree(s1);
		XFree(s2);
		}
		if (values[i] == which_atom)
			return TRUE;
	}

	return FALSE;
}
#endif

#if defined(XWINDOWS) && defined(TARGETS_CODE)
static Atom *get_targets(display, event, atom_count)
	Display *display;
	XEvent *event;
	unsigned long *atom_count;	/* RETURN */
{
  Atom ret_type;
  int ret_format;
  unsigned long ret_after;
  unsigned char *value; /* should get freed by caller with XFree() */
  int val;
  if (Success == (val = XGetWindowProperty(display,
					   event->xselection.requestor,
					   event->xselection.property,
					   0L, 
					   8192, /* specifies max # data items to be 
						 ** retrieved: arbitrary
						 */
					   True,
					   AnyPropertyType, 
					   &ret_type, &ret_format, atom_count,
					   &ret_after, &value)))
    {
      if ((ret_format==32) && (*atom_count > 0))
	return (Atom*)value;
      else
	return (Atom*)NULL;
    }
  else
    {
      return NULL;
    }
}
#endif


/*****************************************************************************
 * long MS_windows_read_clipboard_latin_1(window_index, buffer, max_size)
 *
 *   Description: 
 *     Copy the current contents of the clipboard into the given buffer, 
 *     up to a maximum of max_size-1 characters.  
 *     MS Windows: read an ANSI text string from the clipboard.
 *   Input Arguments:
 *     window_index
 *     buffer
 *     max_size
 *   Returns:
 *     return value: number of characters copied or
 *       CLIPBOARD_READ_RESULTS_FAILURE_CODE for error
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/

#if defined(MSWINDOWS)
static long MS_windows_read_clipboard_latin_1 (window_index, buffer, max_size) 
    long window_index;
    char *buffer;
    long max_size;
{
  HWND      hwndServer;
  HGLOBAL   hglb; 
  LPTSTR    buf;   /* pointer to a null-terminated string */
  long      nbytes = 0;

  if (No_window)
    return 0;
  hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

  /* If this is not a legal window then don't continue. */

  if (!IsWindow (hwndServer))
    return CLIPBOARD_READ_RESULTS_FAILURE_CODE;
  if (!IsClipboardFormatAvailable(CF_TEXT)) 
    return CLIPBOARD_READ_RESULTS_FAILURE_CODE; 
  if (!OpenClipboard(hwndServer)) 
    return CLIPBOARD_READ_RESULTS_FAILURE_CODE; 
 
  hglb = GetClipboardData(CF_TEXT); 
  if (hglb != NULL) { 
    buf = GlobalLock(hglb); 
    /* Do the actual paste. */
    /* We don't seem to have access to the actual length of the string. */
    /* Could use strncpy, but that would always copy n characters. */
    /* Change this to memcpy as is done everywhere else? */
    /* except we use null to tell the end of the string */
    buffer[nbytes] = buf[nbytes];
    while ((buf[nbytes] != '\0') && (nbytes < (max_size - 1))) {
      nbytes++;
      buffer[nbytes] = buf[nbytes];
    }
    /* always put null in last buffer place: doesn't hurt anything */
    buffer[max_size - 1] = '\0';
    /* 
     * Documentation of GlobalLock says do not discard memory
     * returned because it is pointing to the object's memory
     * block. So no need to deallocate or free buf here.
     */
    GlobalUnlock(hglb); 
  } 
  CloseClipboard(); 
  return nbytes;
}
#endif /* MSWINDOWS */


/*****************************************************************************
 * long MS_windows_read_clipboard_unicode (window_index, buffer, max_size)
 *
 *   Description: 
 *     Copy the current contents of the clipboard into the given buffer, 
 *     up to a maximum of max_size-1 characters.  
 *     MS Windows: read an ANSI text string from the clipboard.
 *   Input Arguments:
 *     window_index
 *     buffer
 *     max_size in number of characters, not bytes.
 *   Returns:
 *     return value: number of characters copied or
 *       CLIPBOARD_READ_RESULTS_FAILURE_CODE for error
 *   Notes:
 *   Modifications:
 *
 *****************************************************************************/

#if defined(MSWINDOWS)
static long MS_windows_read_clipboard_unicode (window_index, buffer, max_size) 
    long window_index;
    unsigned short *buffer;
    long max_size;
{
  HWND      hwndServer;
  HGLOBAL   hglb; 
  unsigned  short   *buf;   /* pointer to a null-terminated string */
  long      nbytes = 0;

  if (No_window)
    return 0;
  hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

  /* If this is not a legal window then don't continue. */

  if (!IsWindow (hwndServer))
    return CLIPBOARD_READ_RESULTS_FAILURE_CODE;
  if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) 
    return CLIPBOARD_READ_RESULTS_FAILURE_CODE; 
  if (!OpenClipboard(hwndServer)) 
    return CLIPBOARD_READ_RESULTS_FAILURE_CODE; 
 
  hglb = GetClipboardData(CF_UNICODETEXT); 
  /* This loop copies two bytes at time (unsigned short) and
  ** max_size is in number of characters (not bytes)
  */
  if (hglb != NULL) { 
    buf = GlobalLock(hglb); 
    buffer[nbytes] = buf[nbytes];
    while ((buf[nbytes] != '\0') && (nbytes < (max_size - 1))) {
      nbytes++;
      buffer[nbytes] = buf[nbytes];
    }
    /* always put null in last buffer place: doesn't hurt anything */
    buffer[max_size - 1] = (unsigned short)'\0';
    /* 
     * Documentation of GlobalLock says do not discard memory
     * returned because it is pointing to the object's memory
     * block. So no need to deallocate or free buf here.
     */
    GlobalUnlock(hglb); 
  } 
  CloseClipboard(); 
  return nbytes; 
}
#endif /* MSWINDOWS */


#if defined(MSWINDOWS)
static long MS_windows_write_clipboard_latin_1 (window_index, 
		      latin_1_string, latin_1_string_length) 
     long window_index;
     char *latin_1_string;
     long latin_1_string_length;
{
    HWND      hwndServer;
    HGLOBAL   hglbCopy; 
    LPTSTR    lptstrCopy;
    DWORD     num_latin_bytes = (latin_1_string_length) * sizeof(char);
    long      return_val;

    if (No_window)
      return 0;
    /* This needs to be in initialization code somewhere !!! */
    /* Windows 95 does not support UNICODE, so maybe this
    ** will let us store UNICODE into the clipboard for our
    ** own purposes, at least (and any other app that does the
    ** same trick on Windows 95)
    */
    if (need_to_init) {
      need_to_init = FALSE;
      RegisterClipboardFormat("CF_UNICODETEXT");
    }
 
    hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
    /* If this is not a legal window then don't continue. */
    if (!IsWindow (hwndServer))
      return CLIPBOARD_READ_RESULTS_FAILURE_CODE;
    if (!OpenClipboard(hwndServer)) 
      return CLIPBOARD_READ_RESULTS_FAILURE_CODE; 
    EmptyClipboard();  /* in preparation to write to clipboard */

    /* Allocate a global memory object for the text. */ 

    /* GMEM_DDESHARE is the allocation attribute for clipboard */
    hglbCopy = GlobalAlloc(GMEM_DDESHARE, num_latin_bytes+1);
    if (hglbCopy == NULL) { 
      CloseClipboard(); 
      return CLIPBOARD_READ_RESULTS_FAILURE_CODE; 
    } 
 
    /* Lock the handle and copy the text to the buffer. */ 
 
    lptstrCopy = GlobalLock(hglbCopy); 
    memcpy(lptstrCopy, latin_1_string, num_latin_bytes);
    lptstrCopy[num_latin_bytes] = '\0';
    GlobalUnlock(hglbCopy); 
    return_val = (long)num_latin_bytes; 

    /* Place the handle on the clipboard. */ 

    if (SetClipboardData(CF_TEXT, hglbCopy) == NULL)
      /* signal error */
      return_val = CLIPBOARD_READ_RESULTS_FAILURE_CODE;  
    CloseClipboard(); 
    return return_val;
}
#endif /* MSWINDOWS */


/*****************************************************************************
 * long g2ext_x11_read_cut_buffer(window_index, buffer, max_size)
 *
 *   Description: 
 *     Copy the current contents of the clipboard
 *     into the given buffer, up to a maximum of max_size-1 characters.  
 *     MS Windows: read an ANSI text string from the clipboard.
 *     X  Windows: read a Latin-1 string from cut buffer 0.
 *     The length of the data is determined by means dependent on the underlying
 *     platform.  The MSWindows implementation is not handling embedded nulls 
 *     at the moment.  The X windows platform does handle embedded nulls.  
 *     So, if cross-platform use is a concern, this
 *     may not be usable for all purposes.  Ordinarily, text data does not
 *     contain nulls, and so this should be universally usable for the purpose
 *     of ordinary text data exchange.
 *   Input Arguments:
 *     window_index
 *     buffer
 *     max_size
 *   Returns:
 *     return value: number of characters copied or
 *       -1 for error
 *   Notes:
 *   Modifications:
 *       04/07/97, lgibson: replaced MS Windows stub with code to read
 *     from clipboard (now in a different routine).
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/
long g2ext_x11_read_cut_buffer(window_index, buffer, max_size)
    long window_index;
    char *buffer;
    long max_size;
{
    if (No_window)
      return 0;

#if defined(MSWINDOWS)
    return MS_windows_read_clipboard_latin_1 (window_index, buffer, max_size);

#else /* XWindows */

    {
    GensymXWindow *gensym_window;
    Display *display;
    char *buf;
    int nbytes, length;

    gensym_window = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    display = gensym_window->display_ptr;

    buf = XFetchBytes(display, &nbytes);
    if (nbytes > 0) {
      length = Min(nbytes,max_size-1);
      memcpy(buffer, buf, length);
      buffer[length] = '\0';
      XFree(buf);		/* No longer used only in development G2.
				   Is calling XFree a problem?  Review
				   with G2 architecture committee!
				   (MHD 4/8/97)
				   */
      return length;
    }
    else
      return -1;
    }
#endif /* MSWindows */
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*****************************************************************************
 * long g2ext_x11_write_cut_buffer(window_index, string, length)
 *
 *   Description: 
 *     Copy the given string into the clipboard.
 *     Note that a string with embedded nulls is perfectly valid; however,
 *     note also that the reading side (i.e., g2ext_x11_read_cut_buffer, q.v.)
 *     cannot, in general, handle buffers with embedded null characters.
 *   Input Arguments:
 *     window_index
 *     string to copy
 *     length of the data to write from string (should not include a null
 *     termination character that is not part of the data, if any)
 *   Returns:
 *     return value: number of chars written or -1 for failure. Calling function 
 *     is expected to see if "length" number of characters got written. 
 *     In the case of writing large amounts of data, some data could be lost. 
 *   Modifications:
 *       04/07/97, lgibson: replaced MS Windows stub with code to
 *     write to the clipboard.
 *       05/01/97, lgibson: changed signature; additional length arg
 *     now required; previously, this just used the null character to
 *     determine the length, but that unnecessarily limits the use of this
 *     to only data without embedded nulls.
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_write_cut_buffer(window_index, string, length)
     long window_index;
     char *string;
     long length;
{
    if (No_window)
	return 0;

#if defined(MSWINDOWS)

    return MS_windows_write_clipboard_latin_1 (window_index, string, length);

#else /* XWindows */

    {
    GensymXWindow *gensym_window;

    gensym_window = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

    XStoreBytes(gensym_window->display_ptr, string, length);

    return 1;
    }
#endif /* MSWINDOWS */
}

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/********************************************************************************
 * long g2ext_read_clipboards (window_index,  
 *		     latin_1_string, 
 *		     latin_1_string_max_length, 
 *		     latin_1_desired_p,
 *		     compound_text_string, 
 *		     compound_text_string_max_length, 
 *		     compound_text_desired_p,
 *		     unicode_text_string, 
 *		     unicode_text_string_max_length, 
 *		     unicode_desired_p,
 *		     result_wide_string)
 *
 *
 *
 *   Description: 
 *
 *   Input Arguments:
 *     _max_length is in terms of characters, not bytes.
 *   Returns:
 *     1 for success and 0 for failure (some kind of X event failure)
 * 
 * 
 * result_wide_string is a wide string (type (unsigned short *)), and
 * we set elements as follows 
 * 
 *    element 0:
 *      if (latin_1_desired_p) and we got clipboard data
 *        then element 0 =  length of the resulting latin_1 text
 *      else
 *        element 0 = 0xFFFF (which would not be a valid length);
 *  element 1:
 *       if (compound_text_desired_p) and we were successful in getting it
 *         then element 0 =  length of the resulting compound text
 *      else
 *        element 0 = 0xFFFF (which would not be a valid length);
 *  element 2 is the same, but applies to Unicode text
 *
 * This may be extended in the future.  (Note that a different
 * type of array might have been used; its only requirement is
 * that it handle 16 bit integers.)
 *   Notes:
 *     We could request the target TARGETS, but it doesn't really help us 
 *     avoid any work because we read several formats at once anyway. In 
 *     fact, it is an extra call we don't need (we just request the targets 
 *     we want, and if they fail, they fail). Also, requesting TARGETS 
 *     actually crashes the VMS applications Notepad and Mail. This can be
 *     confirmed by noticing that Framemaker crashes these two applications 
 *     as well, because Framemaker requests TARGETS (to prove that Framemaker 
 *     requests targets, put a printf in the SelectionRequest in events.c).
 *     To paste from Notepad into Framemaker, remotely display Notepad on a 
 *     Unix machine that runs Framemaker.
 *
 *   Modifications:
 *****************************************************************************/
long g2ext_read_clipboards (window_index,  
		     latin_1_string, 
		     latin_1_string_max_length, 
		     latin_1_desired_p,
		     compound_text_string, 
		     compound_text_string_max_length, 
		     compound_text_desired_p,
		     unicode_text_string, 
		     unicode_text_string_max_length, 
		     unicode_desired_p,
		     result_wide_string)

    long	     window_index;
    char *	     latin_1_string;
    long             latin_1_string_max_length;
    long             latin_1_desired_p;
    char *           compound_text_string;
    long             compound_text_string_max_length;
    long             compound_text_desired_p;
    unsigned short * unicode_text_string;
    long             unicode_text_string_max_length;
    long             unicode_desired_p;
    unsigned short * result_wide_string;
{
  if (No_window)
    return 0;

#if defined(MSWINDOWS)
  result_wide_string[LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] = 
    (unsigned short)MS_windows_read_clipboard_latin_1 
      (window_index, latin_1_string, latin_1_string_max_length);
  result_wide_string[COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
    (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;
  compound_text_string[0] = '\0';
  result_wide_string[UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
    (unsigned short)MS_windows_read_clipboard_unicode
      (window_index, unicode_text_string, unicode_text_string_max_length);
  /* Might be slightly faster have a special MSWindows function here
  ** that reads both latin-1 and unicode all at once, but this is 
  ** much more clean and portable. 
  */
  return 1;

#else /* X Windows */

  {
  GensymXWindow  *gensym_window;
  Display        *display;
  unsigned short  number_of_bytes_to_copy;
  XEvent	  event;

  gensym_window = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
  display = gensym_window->display_ptr;
  
  if (None == selection_atom)
    selection_atom = XInternAtom(display, 
				 "CLIPBOARD", False); /* "PRIMARY" */
  if (None == compound_text_atom)
    compound_text_atom = XInternAtom(display,
				     "COMPOUND_TEXT", False); 
  if (None == unicode_text_atom)
    unicode_text_atom = XInternAtom(display,
				     "_GENSYM_CF_UNICODETEXT", False); 
  if (None == targets_atom)
    targets_atom = XInternAtom(display,
			       "TARGETS", False); 
  if (None == data_prop)
    data_prop = XInternAtom(display, 
			    "_GENSYM_CLIPBOARD_DATA", False); 

  if (latin_1_clipboard == NULL)
    {
      latin_1_clipboard = (unsigned char*)
	malloc(SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH+1);
      compound_text_clipboard = (unsigned char*)
	malloc(SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH+1);
      unicode_text_clipboard = (unsigned short*)
	malloc(SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH *
	       sizeof(unsigned short) +
	       sizeof(unsigned short));
    }

  /* TO DO: put above into an initialization section
     somewhere */
  /* _GENSYM_CLIPBOARD_DATA should be
  ** registered with the X Registry.
  ** Alternatively, we could confirm that
  ** the property doesn't exist on this
  ** window. But it is so unlikely that we
  ** don't bother.
  */

#ifdef OLD_TARGETS_CODE
  XConvertSelection(display,			
		    selection_atom, 
		    targets_atom,  /* works if XA_STRING */
		    data_prop, 
		    gensym_window->xwindow, 
		    gensym_window->last_event_time);
#endif
  /* request the most common target (string), then if that 
  ** works, try others.
  */
  XConvertSelection(display,			
		    selection_atom, 
		    XA_STRING,
		    data_prop, 
		    gensym_window->xwindow, 
		    gensym_window->last_event_time);

  if (fetch_event(display, &event))
    {
      if (event.type == SelectionRequest)
	{
	  /* gracious! we own the selection, and it's already
	  ** a STRING, so just return it
	  */
	  if (latin_1_desired_p)
	    {
	      number_of_bytes_to_copy = Min(latin_1_clipboard_char_count,
			                    latin_1_string_max_length-1);
	      memcpy(latin_1_string, latin_1_clipboard, 
		     number_of_bytes_to_copy);
	      latin_1_string[number_of_bytes_to_copy] = '\0';
	      result_wide_string[LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] = 
		(unsigned short) number_of_bytes_to_copy;
	    }
	  else 
	    {
	      latin_1_string[0] = '\0';
	      result_wide_string[LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] = 
		(unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

	    }
	  /* Compound text case */
	  if (compound_text_desired_p)
	    {
	      number_of_bytes_to_copy = Min(compound_text_clipboard_char_count,
					    compound_text_string_max_length-1);
	      memcpy(compound_text_string, 
		     compound_text_clipboard, 
		     number_of_bytes_to_copy); 
	      compound_text_string[number_of_bytes_to_copy] = '\0';
	      result_wide_string[COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY]=
		(unsigned short) number_of_bytes_to_copy;
	    }
	  else 
	    {
	      compound_text_string[0] = '\0';
	      result_wide_string[COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY]=
		(unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

	    }
	  /* Unicode case */
	  if (unicode_desired_p)
	    {
	      number_of_bytes_to_copy = Min((unicode_text_clipboard_char_count* 
					     sizeof(unsigned short)),
					    (unicode_text_string_max_length * 
					     sizeof(unsigned short) - 
					     sizeof(unsigned short)));
	      /* 
	      ** There is some dim possibility that the bytes should be
	      ** in the opposite order, (for byte swapping) but who cares now, 
	      ** because we are the only ones reading this kind of target type.
	      */
	      memcpy(unicode_text_string, 
		     unicode_text_clipboard, 
		     number_of_bytes_to_copy); 
	      unicode_text_string
		[number_of_bytes_to_copy/sizeof(unsigned short)] = 
		(unsigned short)'\0';
	      result_wide_string[UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
		(unsigned short) 
		(number_of_bytes_to_copy/sizeof(unsigned short));
	    }
	  else 
	    {
	      unicode_text_string[0] = (unsigned short)'\0';
	      result_wide_string[UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] =
		(unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

	    }
	  return 1; 
	} 
      else
	if ((event.type == SelectionNotify) &&
	    (event.xselection.selection == selection_atom)&&
	    (event.xselection.property != None))
	  { /* for obselete targets code, see TARGETS_CODE below */
	    if (latin_1_desired_p)
	      {
		/* here we do get_property_value() because we already
		** did a fetch_event(). After Latin1 (XA_STRING), we
		** do fetch_8bit_data(), which includes fetch_event().
		*/
		result_wide_string[LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] =
		  get_property_value(display, 
				     latin_1_string, 
				     latin_1_string_max_length, 
				     &event);
	      }
	    else 
	      {
		latin_1_string[0] = '\0';
		result_wide_string[LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] = 
		  (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

	      }
	    if (compound_text_desired_p)
	      {
		result_wide_string[COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY]=
		  fetch_8bit_data (display, 
				   compound_text_string, 
				   compound_text_string_max_length, 
				   gensym_window, 
				   compound_text_atom);
	      }
	    else 
	      {
		compound_text_string[0] = '\0';
		result_wide_string[COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY]=
		  (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

	      }
	    /* if someone else has the unicode_text_atom, its
		    ** got to be another G2 or TW
		    ** See also events.c: XChangeProperty
		    */
	    if (unicode_desired_p)
	      {
		result_wide_string[UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] =
		  fetch_8bit_data (display, 
				   (char *)unicode_text_string, 
				   (unicode_text_string_max_length *
				    sizeof(unsigned short)),
				   gensym_window, 
				   unicode_text_atom);
		/* must convert #bytes to #characters, unless error */
		if (result_wide_string
		    [UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] != 
		    (unsigned short)CLIPBOARD_READ_RESULTS_FAILURE_CODE)
		  result_wide_string
		    [UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] =
		    result_wide_string
		    [UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] / 
		    sizeof(unsigned short);
	      }
	    else 
	      {
		unicode_text_string[0] =  (unsigned short)'\0';
		result_wide_string[UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] =
		  (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

	      }
	    return 1;
	  }
      /* other failures fall through */
    }
  /* else failure; it timed out */
  latin_1_string[0] = '\0';
  result_wide_string[LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] = 
    (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;
  compound_text_string[0] = '\0';
  result_wide_string[COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
    (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;
  unicode_text_string[0] = (unsigned short)'\0';
  result_wide_string[UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
    (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;
  return 0; /* Some kind of error occured */
  }
#endif /* MSWINDOWS */
}

	  /* handy Debugging code
	    printf("latin_1_string=%s \n", latin_1_string); 
	    printf("latin_1_clipboard=%s \n", latin_1_clipboard);
	    printf("latin length=%u  \n", 
	      result_wide_string[LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY]); 
	    printf("compound_clipboard=%s \n", compound_text_clipboard);
	    printf("compound length=%u \n",
	      result_wide_string
	      [COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY]);
	    printf("unicode_clipboard=%s \n", unicode_text_clipboard);
	    printf("unicode characters read=%u (number_of_bytes_to_copy)  \n", 
	      number_of_bytes_to_copy);
	    fflush(stdout); 
	    */

#ifdef TARGETS_CODE
  /* this is the code that is responding to a request for TARGETS
  ** which we don't do anymore because it crashed Notepad on VMS
  */
	  { /* we got response to targets -- now read supported targets */
	    if (event.xselection.property != None)
	      {
		unsigned long atom_count;
		Atom *values = get_targets(display,&event,&atom_count);
		if (values)
		  {
		    if (latin_1_desired_p &&
			check_target(display, values, atom_count, XA_STRING))
		      {
			result_wide_string
			  [LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] =
			  fetch_8bit_data (display, 
					   latin_1_string, 
					   latin_1_string_max_length, 
					   gensym_window, 
					   XA_STRING);
		      }
		    else 
		      {
			latin_1_string[0] = '\0';
			result_wide_string
			  [LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] = 
			  (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

		      }
		    if (compound_text_desired_p &&
			check_target(display, values, atom_count, 
				     compound_text_atom))
		      {
			result_wide_string
			  [COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
			  fetch_8bit_data (display, 
					   compound_text_string, 
					   compound_text_string_max_length, 
					   gensym_window, 
					   compound_text_atom);
		      }
		    else 
		      {
			compound_text_string[0] = '\0';
			result_wide_string
			  [COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
			  (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

		      }
		    /* if someone else has the unicode_text_atom, its
		    ** got to be another G2 or TW
		    ** See also events.c: XChangeProperty
		    */
		    if (unicode_desired_p &&
			check_target(display, values, atom_count, 
				     unicode_text_atom))
		      {
			result_wide_string
			  [UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
			  (unsigned short) 			  
			  ((fetch_8bit_data (display, 
					    (char *)unicode_text_string, 
					    (unicode_text_string_max_length *
					     sizeof(unsigned short)),
					    gensym_window, 
					    unicode_text_atom)) 
			   / sizeof(unsigned short));
		      }
		    else 
		      {
			unicode_text_string[0] =  (unsigned short)'\0';
			result_wide_string
			  [UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
			  (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;

		      }
		    XFree (values); /* is calling XFree a problem???? */
		    return 1;
		  }
	      }
	    else
	      {
		/* try anyway; the other program may not support
		** TARGETS but does do STRING
		*/
		result_wide_string[LATIN_1_CLIPBOARD_READ_RESULTS_ENTRY] = 
		  fetch_8bit_data (display, 
				   latin_1_string, 
				   latin_1_string_max_length, 
				   gensym_window, 
				   XA_STRING);
		compound_text_string[0] = (unsigned short)'\0';
		result_wide_string
		  [COMPOUND_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
		  (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;
		unicode_text_string[0] = (unsigned short)'\0';
		result_wide_string
		  [UNICODE_TEXT_CLIPBOARD_READ_RESULTS_ENTRY] = 
		  (unsigned short) CLIPBOARD_READ_RESULTS_FAILURE_CODE;
		return 1;
	      }
	    XFree (values); /* is calling XFree a problem???? */
	  }
#endif 

/*****************************************************************************
 * long g2ext_write_clipboards (window_index,
 *    		          latin_1_string, 
 *		          latin_1_string_length,
 *		          compound_text_string, 
 *		          compound_text_string_length,
 *		          unicode_text_string, 
 *		          unicode_text_string_length)
 *   Description: 
 *	MS Windows: Attempt to write latin_1_string and unicode_text_string 
 *		    to the clipboard.
 *		    Note: MUST do all writes to MS Windows at once!
 *	X  Windows: Attempt to write all formats to the clipboard.
 *		    Write the latin_1_string to cut buffer 0.
 *			safer to write latin_1_string, since maybe others 
 *			can't read compound text
 *		    Code here writes to X clipboard, then calls  
 *			g2ext_x11_write_cut_buffer with latin-1-string
 *
 *   Input Arguments:
 *     If an input string is null, the corresponding clipboard gets length 0.
 *     _sting_length arguments are in terms of characters, not bytes. 
 *   Returns: number of latin-1 bytes written, or
 *     CLIPBOARD_READ_RESULTS_FAILURE_CODE for error.
 *   Modifications:
 *****************************************************************************/

long g2ext_write_clipboards (window_index,
		      latin_1_string, 
		      latin_1_string_length,
		      compound_text_string, 
		      compound_text_string_length,
		      unicode_text_string, 
		      unicode_text_string_length)

    long	     window_index;
    char *	     latin_1_string;
    long             latin_1_string_length;
    char *           compound_text_string;
    long             compound_text_string_length;
    unsigned short * unicode_text_string;
    long             unicode_text_string_length; /* in characters, not bytes */
{
  /* Don't count null byte here */
  latin_1_clipboard_char_count       = Min(latin_1_string_length,
					   (SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH - 
					    sizeof(char)));
  compound_text_clipboard_char_count = Min(compound_text_string_length,
					   (SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH - 
					    sizeof(char)));
  unicode_text_clipboard_char_count  = Min(unicode_text_string_length,
					   (SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH - 
					    sizeof(unsigned short)));
  if (No_window)
    return 0;
# if defined(MSWINDOWS)
  {
    HWND      hwndServer;
    HGLOBAL   hglbCopy; 
    LPTSTR    lptstrCopy;
    unsigned short *lptwstrCopy; /* wide string */

    /* This needs to be in initialization code somewhere !!! */
    /* Windows 95 does not support UNICODE, so maybe this
    ** will let us store UNICODE into the clipboard for our
    ** own purposes, at least (and any other app that does the
    ** same trick on Windows 95)
    */
    if (need_to_init) {
      need_to_init = FALSE;
      RegisterClipboardFormat("CF_UNICODETEXT");
    }



    hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
    /* If this is not a legal window then don't continue. */
    if (!IsWindow (hwndServer))
      return CLIPBOARD_READ_RESULTS_FAILURE_CODE;
    if (!OpenClipboard(hwndServer)) 
      return CLIPBOARD_READ_RESULTS_FAILURE_CODE; 
    EmptyClipboard();  /* in preparation to write to clipboard */

    /* First write Latin-1 (ANSI in this case) */
    /* Allocate a global memory object for the text. */ 

    /* GMEM_DDESHARE is the allocation attribute for clipboard */
    hglbCopy = GlobalAlloc(GMEM_DDESHARE, 
			   (latin_1_clipboard_char_count *
			    sizeof(char) +
			    sizeof(char)));
    if (hglbCopy == NULL) { 
      CloseClipboard(); 
      return CLIPBOARD_READ_RESULTS_FAILURE_CODE; 
    } 
 
    /* Lock the handle and copy the text to the buffer. */ 
 
    lptstrCopy = GlobalLock(hglbCopy); 
    memcpy(lptstrCopy, latin_1_string, (DWORD)latin_1_clipboard_char_count);
    lptstrCopy[latin_1_clipboard_char_count] = '\0';
    GlobalUnlock(hglbCopy); 
 
    /* Place the handle on the clipboard. */ 

    if (SetClipboardData(CF_TEXT, hglbCopy) == NULL)
      /* latin_1_clipboard_char_count is now our return value: signal error */
      latin_1_clipboard_char_count = CLIPBOARD_READ_RESULTS_FAILURE_CODE;  

    /* Now write UNICODE */

    hglbCopy = GlobalAlloc(GMEM_DDESHARE, 
			   (unicode_text_clipboard_char_count *
			    sizeof(unsigned short) +
			    sizeof(unsigned short)));
    if (hglbCopy == NULL) { 
      CloseClipboard(); 
      return latin_1_clipboard_char_count; /* our default return value */
    } 
 
    /* Lock the handle and copy the text to the buffer. */ 
 
    lptwstrCopy = GlobalLock(hglbCopy); 
    memcpy(lptwstrCopy, unicode_text_string, 
	   (DWORD)(unicode_text_clipboard_char_count * 
		   sizeof(unsigned short)));
    lptwstrCopy[unicode_text_clipboard_char_count] = 
      (unsigned short) '\0';
    GlobalUnlock(hglbCopy); 
 
    /* Place the handle on the clipboard. */ 
    /* UNICODE format is not supported on Windows 95. 
    ** To handle this, could do:
    **   OSVerInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    **   if (GetVersionEx (&OSVerInfo) &&
    **     (OSVerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) &&
    ** but I think the SetClipboardData will fail if it is sent 
    ** CF_UNICODETEXT on Win95.
    */
    if (SetClipboardData(CF_UNICODETEXT, hglbCopy) == NULL)
      /* length is now our return value: signal error */
      latin_1_clipboard_char_count = CLIPBOARD_READ_RESULTS_FAILURE_CODE;  
    CloseClipboard(); 
    return latin_1_clipboard_char_count;
  }

# else /* X Windows */

  {
    GensymXWindow *gensym_window;
    
    /* We write to the cut buffer in case other applications do not
    ** read the X Clipboard. 
    */
    g2ext_x11_write_cut_buffer (window_index, latin_1_string, 
			  latin_1_clipboard_char_count);

    gensym_window =(GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    
    if (None == selection_atom)
      /* could also use "PRIMARY" */
      selection_atom = XInternAtom(gensym_window->display_ptr, 
				   "CLIPBOARD", False); 
    if (None == compound_text_atom)
      compound_text_atom = XInternAtom(gensym_window->display_ptr,
				       "COMPOUND_TEXT", False); 
    if (None == unicode_text_atom)
      unicode_text_atom = XInternAtom(gensym_window->display_ptr,
				      "_GENSYM_CF_UNICODETEXT", False); 
    if (None == targets_atom)
      targets_atom = XInternAtom(gensym_window->display_ptr,
				 "TARGETS", False); 
    if (latin_1_clipboard == NULL)
      {
	latin_1_clipboard = (unsigned char*)
	  malloc(SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH+1);
	compound_text_clipboard = (unsigned char*)
	  malloc(SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH+1);
	unicode_text_clipboard = (unsigned short*)
	  malloc(SPECIFIED_MAX_CLIPBOARD_TEXT_LENGTH *
		 sizeof(unsigned short) +
		 sizeof(unsigned short));
      }

    /* note XSetSelectionOwner argument order:  */
    XSetSelectionOwner(gensym_window->display_ptr, 
		       selection_atom, gensym_window->xwindow,
		       gensym_window->last_event_time);  
    /* note: we really do want timestamp to be valid,
       but we will certainly have a valid event by this time */

    if (gensym_window->xwindow != 
	XGetSelectionOwner(gensym_window->display_ptr, selection_atom))
      { 
	/* printf ("This program failed to become selection owner \n"); */
	/* failure condition TO BE DETERMINED */ 
	return (unsigned short)CLIPBOARD_READ_RESULTS_FAILURE_CODE;
      }
    else
      {
	/* Once we are the selection owner, we store the data locally in 
	** whatever formats we like. We then have to serve selection 
	** requests from other X clients.
	**
	** Clipboard lengths (in vars _clipboard_char_count) have already
	** been initialized.
	*/
	if (unicode_text_string && (unicode_text_clipboard_char_count != 0))
	  {
	    memcpy(unicode_text_clipboard, 
		   unicode_text_string, 
		   (unicode_text_clipboard_char_count *
		    sizeof(unsigned short)));
	    unicode_text_clipboard
	      [unicode_text_clipboard_char_count] =
	      (unsigned short)'\0';
	  }
	if (compound_text_string && (compound_text_clipboard_char_count != 0))
	  {
	    memcpy(compound_text_clipboard, 
		   compound_text_string, 
		   compound_text_clipboard_char_count);
	    compound_text_clipboard[compound_text_clipboard_char_count] = '\0';
	  }
	if (latin_1_string && (latin_1_clipboard_char_count != 0))
	  {
	    memcpy(latin_1_clipboard, 
		   latin_1_string, 
		   latin_1_clipboard_char_count);
	    latin_1_clipboard[latin_1_clipboard_char_count] = '\0';
	  }
	return latin_1_clipboard_char_count;
	/* 
	   if we wanted to, we could have asserted ownership 
	   of the PRIMARY selection and then
	   just not cached it -- fetch it in the 
	   future when someone requests it (pastes)
	   The alternative is keeping enough information 
	   around to reconstruct this
	   data when it is fetched e.g. temporary global 
	   storage (one data structure which is
	   the contents of the selection)
	   */
      } /* end of if/else */
  } /* end of block */
# endif /* MSWINDOWS */
}
