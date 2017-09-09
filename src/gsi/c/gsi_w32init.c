/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      gsi_w32init.c
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):   ncc, rh, yduj, jv
+
+ Description:
+
+ Key:
+   (obsolete)
+
+ File Organization:
+   Section:      INCLUDE FILES
+   Section:      DEFINES
+   Section:      GLOBALS
+   Section:      FUNCTION GROUP
+
+ External Interface:
+
+ Dependencies:
+
+ Notes:
+   This file is only compiled on Microsoft Windows.
+
+ Modifications:
+   usage: All modifications to this file should be listed here, with most
+          recent first. In general, modification comments should merely
+          provide a reference to a detailed modification comment in the
+          appropriate section/function header.
+
+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:  copied more or less from events.c -- may not be necessary *or* sufficient!
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <string.h>
#include <math.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "msincls.h"
#include "cprim.h"        /* need G2Pointer, etc. */
#include <stdio.h>
#include "graphics.h"
#include "networks.h"
#include "netevent.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      GLOBALS
%
% Description:  Module specific typedefs, variables, & externs defined here
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define DLLEXPORT __declspec( dllexport )

typedef void maybe_wait_for_return_key_type ();

static FILE *outstream = NULL;
static FILE *errstream = NULL;

int g2pvt_win32_initialized_p = 0;

extern maybe_wait_for_return_key_type *g2ext_maybe_wait_for_return_key_fn;

extern void ne_enqueue_next_event ();
extern void ne_set_ni_last_error ();
extern G2pointer ne_lookup_handle_for_fd (); /* defined in nt-next-event.c */
extern G2pointer get_and_decache_socket_to_NI_handle(long resolver_handle);
extern void g2pvt_tcpip_reconnect(NETWORK_INTERFACE *ni);
extern void g2ext_check_windows_platform ();

extern int ne_use_sck; /* console application? */
extern int g2ext_max_number_of_sockets;
extern int timer_is_set;
extern DWORD tick_count_at_expiry;


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* LONG GsiWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
*
*   Description:
*   Input Arguments:
*    HWND hWnd;             window handle
*    UINT message;          type of message
*    WPARAM wParam;         additional information
*    LPARAM lParam;         additional information
*   Returns:
*   Notes:
*
*****************************************************************************/
LONG WINAPI GsiWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    long            lReturn = 0;
    G2pointer       socket;

    /* These are static so we can swallow multiple Resize/Repaint messages
     * sent by NT 3.5 and push them after the ButtonUp event.
     */
    static BOOL            bSizeMove = FALSE, bResize = FALSE;
    static long            nWidth, nHeight;

    /* These are declared static so that WM_CHAR, KEYDOWN, and SYSKEYDOWN
     * can at least get at some recent mouse position, event though the key
     * events them do not hold x and y positions.
     */
    static long xPos = 0, yPos = 0;

    switch (message) {

    case NE_SCHEDULER_EVENT:
      ne_enqueue_next_event(scheduler_event,
                            0, /* scheduler events are global to all sockets. */
                            0);
      break;

    case WM_TIMER:
      KillTimer(hWnd, wParam);   /* make sure this timer is a one-shot. */
      timer_is_set = FALSE;
      tick_count_at_expiry = 0;
      ne_enqueue_next_event(scheduler_event,
                            0, /* scheduler events are global to all sockets. */
                            0);
      break;

    /* duplicated with ext/c/msmain.c */
    case WSA_NETEVENT:
      socket = ne_lookup_handle_for_fd(wParam);
      if (socket != -1) {
        int eventcode = 0;
        int err = WSAGETSELECTERROR(lParam);
        ne_set_ni_last_error(socket,err);
        switch (WSAGETSELECTEVENT(lParam)) {
        case FD_CONNECT: {
                           NETWORK_INTERFACE *ni =
                             (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(socket);
                           if (ni->connected_p) break; /* try to avoid a Windows 95 bug */
                           if (err == 0) ne_connect_ni(socket);
                           ni->connect_status = err;
                           eventcode = connect_event; break;
                         }
        case FD_ACCEPT:  eventcode = accept_event;
                         ne_set_next_timer_event(500); break;
        case FD_READ:    eventcode = read_and_block_event; break;
        case FD_WRITE:   eventcode = write_event;   break;
        case FD_CLOSE:   eventcode = close_event;   break;
        }
        if (eventcode)
          ne_enqueue_next_event(eventcode, socket, err);
      }
      break;

    /* duplicated with ext/c/msmain.c */
    case WSA_NETEVENT_NS: {
      int buflen, error;
      NETWORK_INTERFACE *ni;
      socket = get_and_decache_socket_to_NI_handle((long)wParam);
      if (!socket) break;
      ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(socket);
      if (!ni) break;
      ni->resolver_handle = 0;

      buflen = WSAGETASYNCBUFLEN(lParam);
      error = WSAGETASYNCERROR(lParam);

      if (error)
        errno = TCPIP_CONNECT_NO_SUCH_HOST;
      else
        g2pvt_tcpip_reconnect(ni);

      if (errno) {
        ni->connect_status = errno;
        ne_enqueue_next_event(connect_event, socket, errno);
      }
      break;
    }

    case WM_QUIT:
      ne_enqueue_next_event(quit_event,0,0);
      break;

    default:
      lReturn = DefWindowProc(hWnd, message, wParam, lParam);
    }

     return (lReturn);
}


/*****************************************************************************
* void gsi_init_events_for_w32 (HANDLE hInstance)
*
*   Description: registers and creates our window, and starts Winsock.  It is
*     assumed that by calling this function, we will use the Winsock, window-
*     based event-handling code in ntevent.c, rather than the select-based,
*     socket-oriented event-handling code ("sck") in sckevent.c
*   Input Arguments:
*     HANDLE hInstance;
*   Returns: nothing
*   Notes: we claim that it is "required" for ALL Windows bridges to call
*     gsi_initialize_for_win32.  I'm not sure if, when we made that requirement,
*     we realized that meant that console applications would use Windows
*     events, rather than select().  But we also know that calling this code
*     makes ActiveX Link not work.  See Bug HQ-4951692, "GSI on Win32 should not
*     start if not initialized"
*
*****************************************************************************/
void gsi_init_events_for_w32 (HANDLE hInstance)
{
  WNDCLASS wc;
  WSADATA WSAStartupData;
  char GsiWindowClass[32] = "GSIClass";

  /* Fill in window class structure with parameters that describe the main
   * window. */
  memset((void *)&wc, '\0', sizeof(WNDCLASS));
  wc.style            = CS_NOCLOSE;
  wc.lpfnWndProc      = (WNDPROC) GsiWndProc;
  wc.hInstance        = hInstance;
  wc.lpszClassName    = GsiWindowClass;

  /* Register the window class and return success/failure code. */
  if (!RegisterClass(&wc)) {
    return;
  }

  /* Create the invisible GSI window (used for event dispatching only). */
  GhwndWin = CreateWindow(GsiWindowClass,
                           (LPSTR)"GSIEventWindow",
                           WS_OVERLAPPEDWINDOW,
                           0, 0, 0, 0,
                           NULL,     /* Parent window */
                           NULL,     /* Handle to top-level menubar */
                           hInstance,
                           NULL);
  if (GhwndWin == NULL) {
    return;
  }

  if ((WSAStartup(MAKEWORD(1,1), &WSAStartupData)) != 0) {
    MessageBox(NULL, "Cannot start Winsock.", NULL, MB_OK);
    return;
  }

  g2ext_max_number_of_sockets = WSAStartupData.iMaxSockets;
  /* Only at this point, after we're sure all the Windows networking stuff
   * has succeeded, do we actually determine that we will not use the select-
   * based networking code. */
  ne_use_sck = FALSE;
}


/***************************************************************************
 * void maybe_wait_for_return_key_internal ()
 *
 *   Purpose:
 *     If this is MS Windows, and there is no active logfile,
 *     pause execution until the user presses return.
 *   Input Arguments: none
 *   Returns: nothing
 *   Comments:
 *     GSI does not normally have standard input open, but
 *     we have to have it open to see a return key. To be
 *     safe, we open it here at the last possible moment.
 *
 *     This function is duplicated (with minor but important
 *     differences) in msmain.c. It might be nice to put
 *     this in gsimmain.c (which is only used for MS Windows),
 *     but GSI does not always link with gsimmain.c.
 *
 *   Assumption: next action is to exit the program.
 ***************************************************************************/
static void maybe_wait_for_return_key_internal ()
{
  HANDLE hin;
  char buffer[4];
  DWORD numRead;

  /* If outstream points to something, the logfile is active.
   * If ne_use_sck is FALSE, this is a console application.
   */

  if (outstream == NULL && !ne_use_sck) {
    hin = GetStdHandle(STD_INPUT_HANDLE);
    /* Note that ENABLE_LINE_INPUT is not listed, to enable single chars */
    SetConsoleMode(hin, ENABLE_ECHO_INPUT & ENABLE_PROCESSED_INPUT &
                   ENABLE_MOUSE_INPUT);
    printf("\nPRESS ANY KEY TO END \n");
    /* wait for return to be pressed */
    ReadFile(hin, &buffer, 1, &numRead, NULL);
  }
}


/*****************************************************************************
* char *gsi_logfile_name (char *lpCmdLine)
*
*   Description: determines the name of the logfile, if any, to use for GSI
*     logging.
*   Input Arguments: the command line to the GSI process
*   Returns: a freshly malloc'ed string naming the requested logfile, if found,
*     and NULL otherwise
*   Notes: iterates over the entire command line, but only looks for -log.  If
*     we add some more Windows-specific GSI command-line arguments, we'll
*     probably want to process them here, which means this function will then
*     be misnamed.  For now, "logfile name" is all it does.
*
*****************************************************************************/
static char *gsi_logfile_name (char *lpCmdLine)
{
  char *psToken, *psOptions, *logfile;
  size_t logfile_name_length;

  logfile = NULL;
  if (lpCmdLine == NULL) {
    psOptions = malloc(sizeof (char));
    psOptions[0] = '\0';
  } else {
    psOptions = malloc((strlen(lpCmdLine)+1) * sizeof (char));
    strcpy(psOptions, lpCmdLine);
  }

  for (psToken = strtok(psOptions, (char *) " \t");
       psToken != NULL;
       psToken = strtok(NULL, (char *) " \t"))
    {
      if (0 == stricmp(psToken, "-LOG")) {
        if ((psToken = strtok(NULL, (char *) " \t")) != '\0') {
          logfile_name_length = strlen(psToken);
          logfile = (char *)malloc(sizeof(char) * (1+logfile_name_length));
          strncpy(logfile, psToken, logfile_name_length);
          logfile[logfile_name_length] = '\0';
        }
        /* else parse error, but we don't say anything about it */
      }
    }
  free(psOptions);
  return logfile;
}


/*****************************************************************************
* BOOL open_gsi_console ()
*
*   Description: tries to allocate a console for GSI output
*   Input Arguments: none
*   Returns: the return value of the call to AllocConsole
*   Notes: the return value is ignored by its caller.  Not sure what we should
*     do if the call fails.
*
*****************************************************************************/
static BOOL open_gsi_console ()
{
  BOOL success_p;
  HANDLE  hout;
  FILE   *fp;
  int     fdstdout;

  success_p = AllocConsole();
  if (success_p) {
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    fdstdout = _open_osfhandle((long)hout, _O_TEXT);
    fp = _fdopen(fdstdout, "w");
    *stdout = *fp;

    printf("Initializing...\n");
  }
  return success_p;
}


/*****************************************************************************
* void gsi_initialize_for_win32 (HANDLE hInstance, char *lpCmdLine)
*
*   Description: a GSI API function, new in 5.0, which is only defined on
*     win32 platforms.
*   Input Arguments: the standard arguments passed by the OS to WinMain
*   Returns: nothing
*   Notes: we claim that it is "required" for all Windows bridges to call this
*     function, but in practice, most console applications do not.  Why do we
*     call gsi_init_events_for_w32 twice?
*
*****************************************************************************/
DLLEXPORT void gsi_initialize_for_win32 (HANDLE hInstance, char *lpCmdLine)
{
  char *logfile;

  if (g2pvt_win32_initialized_p == 1) {
    return;
  }
  g2pvt_win32_initialized_p = 1;

  g2ext_check_windows_platform();

  gsi_init_events_for_w32(hInstance); /* win32, GSI-specific: creates a window to dispatch events on. */
  ne_initialize_event_handling();     /* platform-indep event handling initialization */

  g2ext_maybe_wait_for_return_key_fn = maybe_wait_for_return_key_internal;

  logfile = gsi_logfile_name(lpCmdLine);
  if (logfile) {
    outstream = freopen(logfile, "w", stdout);
    errstream = freopen(logfile, "a", stderr);
  }
  if (outstream == NULL) {
    if (logfile) {
      printf("Could not open logfile \"%s\".\n\n",logfile);
    }
    open_gsi_console();
  }
  if (logfile) free(logfile);

  gsi_init_events_for_w32(hInstance);
}
