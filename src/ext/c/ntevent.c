/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      ntevent.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +   Rick Harris
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
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   12/17/07,  jv: adding this comment header
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
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#if !defined(WIN32)
#  error "ntevent.c is Windows only"
#endif

#include <string.h>
#include <math.h>
#include <windows.h>
#include "msincls.h"
#include "cprim.h"                /* need G2Pointer, etc. */
#include "graphics.h"
#include "networks.h"
#include "trace.h"

#define ne_initialize_network_interface n_ne_initialize_network_interface
#define ne_map_fd_to_handle n_ne_map_fd_to_handle
#define ne_unmap_fd n_ne_unmap_fd
#define ne_connect_ni n_ne_connect_ni
#define ne_register_active_ni n_ne_register_active_ni
#define ne_deregister_inactive_ni n_ne_deregister_inactive_ni
#define ne_enable_accept_events n_ne_enable_accept_events
#define ne_disable_accept_events n_ne_disable_accept_events
#define ne_enable_read_events n_ne_enable_read_events
#define ne_disable_read_events n_ne_disable_read_events
#define ne_enable_write_events n_ne_enable_write_events
#define ne_disable_write_events n_ne_disable_write_events
#define ne_enable_watch_events n_ne_enable_watch_events
#define ne_enable_display_events n_ne_enable_display_events
#define ne_disable_display_events n_ne_disable_display_events
#define ne_display_events_enabled n_ne_display_events_enabled
#define ne_initialize_display_events n_ne_initialize_display_events
#define g2_event_cycle n_g2_event_cycle
#define g2_event_wait n_g2_event_wait
#define g2_event_ready n_g2_event_ready
#define ne_initialize_event_handling n_ne_initialize_event_handling
#define ne_print_events n_ne_print_events
#define ne_sprint_events n_ne_sprint_events
#define ne_lookup_handle_for_fd n_ne_lookup_handle_for_fd
#define ne_enqueue_scheduler_event n_ne_enqueue_scheduler_event
#define ne_set_next_timer_event n_ne_set_next_timer_event
#define ne_last_error_length n_ne_last_error_length
#define ne_last_error_string n_ne_last_error_string

#include "netevent.h"

extern struct win32internet_error_code_struct {
  int code;
  char *name;
} win32internet_error_code_table [];

/* Globals */

BOOL g2ext_window_destroyed = FALSE;

static long mapped_socket_count = 0;           /* maintained by accessor and setter for previous table, */
static short int *ievents;
static short ne_event_handling_initialized_p = 0;

extern HWND GhwndWin;         /* the global window under mswindows */
extern HWND hwndClient;              /* The MDI client window, if Frame_is_MDI */
extern BOOL Frame_is_MDI;
extern int g2ext_max_number_of_sockets;
extern G2pointer *g2ext_socket_to_NI_handle_table; /* ne_initialize_event_handling() allocates this array. */

extern BOOL g2pvt_is_dialog_message (MSG *);
extern int g2ext_lookup_socket_index (unsigned);
extern void g2ext_initialize_socket_index_table ();
extern long g2ext_write_string_to_console(char *);

extern long handle_network_events;

/***************************************************************************\
* void g2ext_check_windows_platform ()
*
* PURPOSE: to make sure that we are running on a machine with a minimum OS
*   level which we can support.
*
* COMMENTS: HQ-4686097, "disallow G2 from running on Windows 95/98/Me".
*   I am initially adding this for 8.1a0.  The message in the message box is
*   a bit curt.  Others will have the opportunity to review these messages
*   before the final 8.1r0 release.  -jv, 1/18/05
*
\***************************************************************************/
void g2ext_check_windows_platform ()
{
#if defined(__WATCOMC__)
#   error "WATCOMC build no longer supported -jv, 1/18/05"
  MessageBox(NULL, "This build is not supported and will not run.",
             "Windows Version Error", MB_OK);
  exit(-1);
#endif

  if (WIN32_IS_WIN32S) {
    MessageBox(NULL, "This product is not supported under Win32s.",
               "Windows Version Error", MB_OK);
    exit(-2);
  }
  if (WIN32_IS_WIN95) {
    MessageBox(NULL, "This product is not supported under Windows 95/98/Me.",
               "Windows Version Error", MB_OK);
    exit(-3);
  }
}



void ne_initialize_network_interface (network_intfc)
NETWORK_INTERFACE * network_intfc;
{
  return;
}

void ne_initialize_event_handling()
{
  if (ne_event_handling_initialized_p) return; /* once only! */
  ne_event_handling_initialized_p = 1;
  g2ext_socket_to_NI_handle_table = (G2pointer *) calloc(g2ext_max_number_of_sockets, sizeof(G2pointer));
  ievents = (short int *) calloc(g2ext_max_number_of_sockets, sizeof(short int));
  g2ext_initialize_socket_index_table();
}


static char *ne_get_last_error_string(handle)
   long handle;
{
  /* return the string describing the last network error associated with this endpoint. */
  int err,i,c;

  NETWORK_INTERFACE *ni =  (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);

  if (ni == NULL) return "";
  err = ni->last_status;
  if (err == TCPIP_CONNECT_NO_SUCH_HOST)
    return "No such host";
  else if (err == TCPIP_CONNECT_NOT_INTERNET_HOST)
    return "Not an internet host";
  else if (err == TCPIP_CONNECT_CANT_MAKE_NONBLOCK_CONNECT)
    return "Can't make the socket non-blocking";
  else if (err == TCPIP_CONNECT_CANT_MAKE_SOCKET)
    return "Unable to make a socket";
  else if (err == TCPIP_CONNECT_FELL_OFF_END)
    return "Internal error: GhwndWin is NULL";
  else if (err == TCPIP_CONNECT_EMPTY_HOST)
    return "Empty host name";
  for(i=0; 0!=(c=win32internet_error_code_table[i].code) && c!=err; i++);
  if (c==err)
    return win32internet_error_code_table[i].name;
  else
    return "";
}

void ne_last_error_string(handle, buffer)
long handle;
char *buffer;
{
  strcpy(buffer, ne_get_last_error_string(handle));
}

long ne_last_error_length(handle)
    long handle;
{
  return (long)strlen(ne_get_last_error_string(handle));
}

static int scheduler_event_pending_p = 0;

void ne_enqueue_scheduler_event()
{
  g2ext_network_io_trace_note("ne_enqueue_scheduler_event");
  scheduler_event_pending_p = 1;
}

/* CTC Possible Scenario, -mhd, 1/04/05:

  { This whole comment added by jv, 1/05/05, based on notes Mark sent by email;
    note that this refers to the scenario where tick_count_at_expiry and
    new_tick_count_at_expiry were declared long (signed) rather than DWORD
    (unsigned).  Since we know that is a mistake, I am fixing it today.  But we
    have not yet determined if that mistake could cause the CTC sleep bug.  The
    following attempts to describe a scenario where it might.
  }

  1. scheduler_event_pending_p and timer_is_set are both FALSE
  2. Enter the then clause of the inner if statement.
  3. Set timer_is_set to TRUE.

  4. Let's say new_tick_count_at_expiry happens to be 2147483647 (i.e., 2^32 - 1).

  5. Let's say this is called again when timer_is_set (!timer_is_set is FALSE),
     and let's say new_tick_count_at_expiry has overflowed to be the negative
     number -2147483648 (i.e., 2^32).
       So (new_tick_count_at_expiry < tick_count_at_expiry) is true, so
     we enter the "then" clause, set a timer, set timer_is_set once again to
     TRUE, and set tick_count_at_expiry to -2147483648.

  6. Let's say this is called again when (!timer_is_set) is FALSE, and
     let's say new_tick_count_at_expiry has overflowed to be the negative
     number -2147483646 (i.e., 2^32 + 3).
       So (new_tick_count_at_expiry < tick_count_at_expiry) is FALSE, so we do
     not enter the "then" clause.  No timer is set, timer_is_set remains TRUE.

  7. But eventually the original timer set in step 5 should go off.  I don't see
     how that could fail to happen.  But if something sets it to happen in a
     really long time, I could see it seeming not to happen, or seem to take a
     really long time.  Does anything set it for a really long time from now?
     Fred wrote in email 12/14/04: G2 sleeps for 1 hour if it has nothing to do.
     See native-window-polling-interval-default (3600000 ms) in platforms.lisp.
     Nearby is native-window-polling-interval-fast (250 ms) which is how long we
     sleep when tracking the mouse.
*/

/* timer_is_set is a global variable with an extremely simple contract.
 * When we call SetTimer (with NE_TIMER_ID), we set it to true.  When
 * we call KillTimer or receive a WM_TIMER message (with NE_TIMER_ID),
 * we set it to false.  -jv, 1/05/05
 */
int timer_is_set = FALSE;

/* tick_count_at_expiry is the tick-count at which the next NE_TIMER_ID timer
 * will fire.  Tick-count is the number of milliseconds since the system
 * started, which wraps around every 47 days or so.  So the number itself is
 * actually pretty meaningless; it is only useful relative to other numbers
 * calculated in similar ways.  -jv, 1/05/05
 */
DWORD tick_count_at_expiry = 0;

void ne_set_next_timer_event (long milliseconds_to_go)
{
  g2ext_network_io_trace_note_d("ne_set_next_timer_event %d", milliseconds_to_go);

  if (!scheduler_event_pending_p) {
    DWORD currentTickCount = GetTickCount();

    /* Note the signed comparison and subtraction, which handles wrap-around. */

    if (milliseconds_to_go < (long)(tick_count_at_expiry - currentTickCount)) {
      /* The new timer event is sooner than one pending; kill the old one.
       * A new one will be set for the new time in the next 'if' clause,
       * since here we set timer_is_set to FALSE.  -jv, 1/05/05
       */
      KillTimer(GhwndWin, NE_TIMER_ID);
      timer_is_set = FALSE;
    }

    if (!timer_is_set) {
      SetTimer(GhwndWin, NE_TIMER_ID, milliseconds_to_go, NULL);
      timer_is_set = TRUE;
      tick_count_at_expiry = currentTickCount + milliseconds_to_go;
    }
    /* else case: timer_is_set && tick_count_at_expiry >= new_tick_count_at_expiry.
     * That means that the new timer event is further in the future than one
     * already pending.  In that case, do nothing.  -jv, 1/05/05
     */
  }
  /* Note that if scheduler_event_pending_p is TRUE, this function essentially
   * becomes a no-op.  We never call SetTimer when scheduler_event_pending_p is
   * set.  It's not entirely clear to me why.  -jv, 1/05/05
   */
}


void ne_map_fd_to_handle(fd, ni_handle)
    fd_type fd;
    G2pointer ni_handle;
{
  g2ext_socket_to_NI_handle_table[g2ext_lookup_socket_index(fd)] = ni_handle;
  mapped_socket_count ++;
}


G2pointer ne_lookup_handle_for_fd(fd)
    fd_type fd;
{
  int si = g2ext_lookup_socket_index(fd);
  return (si == -1) ? -1 : g2ext_socket_to_NI_handle_table[si];
}

G2pointer ne_unmap_fd(fd)
    fd_type fd;
{
	G2pointer return_to_be_reclaimed;
  int socket_index = g2ext_lookup_socket_index(fd);
  return_to_be_reclaimed = g2ext_socket_to_NI_handle_table[socket_index];
  g2ext_socket_to_NI_handle_table[socket_index] = (G2pointer) -1;
  mapped_socket_count --;
  return return_to_be_reclaimed;
}

static void ne_print_queued_events();
static void ne_sprint_queued_events();

void ne_sprint_events(buffer,ni)
  char *buffer;
  NETWORK_INTERFACE *ni;
{
  short events = ievents[ni->socket_index];
  sprintf(buffer,"mask=%s%s%s%s%s pending=",
          (events&FD_READ)?"R":"",
          (events&FD_WRITE)?"W":"",
          (events&FD_ACCEPT)?"A":"",
          (events&FD_CONNECT)?"C":"",
          (events&FD_CLOSE)?"X":"");
  ne_sprint_queued_events(buffer,ni->handle);
}

void ne_print_events(ni)
  NETWORK_INTERFACE *ni;
{
  char buffer[40];
  ne_sprint_events(buffer,ni);
  printf("%s",buffer);
}



/* Below, FD_CONNECT enable is apparently a special case, does not get the usual
   call to WSAAsycSelect. This could use some documentation!. -mhd */
#define ENABLE_NI_EVENTS(ni_handle, fd_event_type)                                           \
do {                                                                                         \
  NETWORK_INTERFACE *ni = (NETWORK_INTERFACE *)g2ext_map_g2pointer_to_cpointer(ni_handle);   \
  int si = ni->socket_index;                                                                 \
  int fd = ni->handle;                                                                       \
  ievents[si] |= fd_event_type;                                                              \
  if (fd_event_type != FD_CONNECT) WSAAsyncSelect(fd, GhwndWin, WSA_NETEVENT, ievents[si]);  \
} while (0)

#define DISABLE_NI_EVENTS(ni_handle, fd_event_type)                                         \
do {                                                                                        \
  NETWORK_INTERFACE *ni = (NETWORK_INTERFACE *)g2ext_map_g2pointer_to_cpointer(ni_handle);  \
  int si = ni->socket_index;                                                                \
  int fd = ni->handle;                                                                      \
  ievents[si] &= ~fd_event_type;                                                            \
  WSAAsyncSelect(fd, GhwndWin, WSA_NETEVENT, ievents[si]);                                  \
} while (0)


void ne_enable_read_events(G2pointer ni_handle)
{
  ENABLE_NI_EVENTS(ni_handle, FD_READ);
}

void ne_disable_read_events(G2pointer ni_handle)
{
  DISABLE_NI_EVENTS(ni_handle, FD_READ);
}

void ne_enable_write_events(G2pointer ni_handle)
{
  ENABLE_NI_EVENTS(ni_handle, FD_WRITE);
}

void ne_disable_write_events(G2pointer ni_handle)
{
  DISABLE_NI_EVENTS(ni_handle, FD_WRITE);
}

void ne_enable_accept_events(G2pointer ni_handle)
{
  ENABLE_NI_EVENTS(ni_handle, FD_ACCEPT);
}

void ne_disable_accept_events(G2pointer ni_handle)
{
  DISABLE_NI_EVENTS(ni_handle, FD_ACCEPT);
}

static void ne_enable_connect_events(G2pointer ni_handle)
{
  ENABLE_NI_EVENTS(ni_handle, FD_CONNECT);
}

static void ne_disable_connect_events(G2pointer ni_handle)
{
  DISABLE_NI_EVENTS(ni_handle, FD_CONNECT);
}

static void ne_enable_close_events(G2pointer ni_handle)
{
  ENABLE_NI_EVENTS(ni_handle, FD_CLOSE);
}

static void ne_disable_close_events(G2pointer ni_handle)
{
  DISABLE_NI_EVENTS(ni_handle, FD_CLOSE);
}

void ne_register_active_ni(ni_handle)
  G2pointer ni_handle;
{
  NETWORK_INTERFACE *ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(ni_handle);

  if (ni->listener_p)
    ne_enable_accept_events(ni_handle);
  else if (ni->connected_p) {
    ne_enable_read_events(ni_handle);
    ne_enable_write_events(ni_handle);
  } else if (!ni->watch_p && !ni->icmp_p)
    ne_enable_connect_events(ni_handle);
  if (!ni->watch_p)
    ne_enable_close_events(ni_handle);
}

void ne_connect_ni(ni_handle)
  G2pointer ni_handle;
{
  NETWORK_INTERFACE *ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(ni_handle);
  ni->connected_p = 1;
  ne_disable_connect_events(ni_handle);
  ne_enable_read_events(ni_handle);
  ne_enable_write_events(ni_handle);
  ne_enable_close_events(ni_handle);
}

void ne_deregister_inactive_ni(ni_handle)
G2pointer ni_handle;
{
}

void ne_enable_watch_events(ni_handle)
    G2pointer ni_handle;
{
}

void ne_enable_display_events()
{
}

void ne_disable_display_events()
{
}

long ne_display_events_enabled()
{
  return 0;
}

void ne_initialize_display_events(window_connection_number)
    int window_connection_number;
{
}

/* this parameter may need to be tweaked a bit. -ncc, 6 Jan 1997  */
#define MAX_PREF_UI_EVENT_COUNT 128


struct ne_queued_event {
  struct ne_queued_event *next;
  int ecode;
  int socket_handle;
  int status;
} *ne_newest_queued_event = 0,
  *ne_oldest_queued_event = 0,
  *ne_free_queued_events = 0;

static int non_scheduler_event_pending_p = FALSE;

void ne_enqueue_next_event(ecode,socket_handle,status)
  int ecode, socket_handle, status;
{
  struct ne_queued_event *event;

  if (ecode == scheduler_event) {
    scheduler_event_pending_p = TRUE;
  } else {
    if (ne_free_queued_events) {
      event = ne_free_queued_events;
      ne_free_queued_events = event->next;
    } else
      event = (struct ne_queued_event *)malloc(sizeof(struct ne_queued_event));
    if (!ne_oldest_queued_event)
      ne_oldest_queued_event = event;
    else
      ne_newest_queued_event->next = event;
    ne_newest_queued_event = event;
    event->next = 0;
    event->ecode = ecode;
    event->socket_handle = socket_handle;
    event->status = status;
    non_scheduler_event_pending_p = TRUE;
  }
}

static void ne_sprint_queued_events(initial_buffer,handle)
  char *initial_buffer;
  int handle;
{
  char *buffer = initial_buffer;
  struct ne_queued_event *event;
  for (event=ne_oldest_queued_event; event!=0; event=event->next)
    if (event->socket_handle == handle) {
      sprintf(buffer,"%c"," RWCAX  Rw"[event->ecode]);
      buffer += strlen(buffer);
    }
}

static int ne_next_event_ecode = 0;
static int ne_next_event_socket_handle;
static int ne_next_event_status;

/* if non_scheduler_event_pending_p is FALSE, don't call this */
static void ne_dequeue_next_event()
{
  struct ne_queued_event *event = ne_oldest_queued_event;
  ne_oldest_queued_event = event->next;
  if (ne_oldest_queued_event == 0) {
    ne_newest_queued_event = 0;
    non_scheduler_event_pending_p = FALSE;
  }
  ne_next_event_ecode = event->ecode;
  ne_next_event_socket_handle = event->socket_handle;
  ne_next_event_status = event->status;
  event->next = ne_free_queued_events;
  ne_free_queued_events = event;
}

void g2pvt_enqueue_display_event()
{
  ne_enqueue_next_event(display_event, 0, 0);
}

void g2pvt_nt_enqueue_read_event(int sock)
{
  G2pointer sockHandle = ne_lookup_handle_for_fd(sock);
  ne_enqueue_next_event(read_and_block_event, sockHandle, 0);
}

void g2pvt_nt_enqueue_write_event(int sock)
{
  G2pointer sockHandle = ne_lookup_handle_for_fd(sock);
  ne_enqueue_next_event(write_event, sockHandle, 0);
}


/*
 * Abstracted Windows message routines
 */

#ifndef CODEJOCK

extern Gensym_Long g2ext_g2_clock_ticks(Gensym_Long);
extern void g2pvt_incf_waited_period(long);
extern long g2pvt_record_waits;

int g2pvt_wait_message(void)
{
  Gensym_Long start, total;
  int returnval;
  if (g2pvt_record_waits)
    start = g2ext_g2_clock_ticks(IMOST_POSITIVE_FIXNUM);

#ifdef PACKAGING_G2_ENTERPRISE
  /* GENSYMCID-663: Faster-201-TAMIstvan-Double-Performance-UC11RPC
     02/15/2012 vchefr Check for Queue status before call to WaitMessage */
  returnval = GetQueueStatus(QS_ALLINPUT | QS_ALLPOSTMESSAGE) ? TRUE : WaitMessage();
#else
  returnval = WaitMessage();
#endif

  if (g2pvt_record_waits) {
    total = g2ext_g2_clock_ticks(IMOST_POSITIVE_FIXNUM) - start;
    if (total < 0) 
      total += IMOST_POSITIVE_FIXNUM;
    g2pvt_incf_waited_period(total);
  }
  return returnval;
}

int g2pvt_peek_message(MSG* pMsg)
{
  return PeekMessageW(pMsg, NULL, 0, 0, PM_REMOVE);
}

int g2pvt_pump_message(MSG* pMsg)
{
  if (Frame_is_MDI && hwndClient && TranslateMDISysAccel(hwndClient,pMsg))
    return 0;

  /* We probably need to do this in the twng case too! */
  if (g2pvt_is_dialog_message(pMsg)) {
    return 0;
  }

  TranslateMessage(pMsg);
  DispatchMessageW(pMsg);

  return 0;
}

#else

extern int g2pvt_wait_message(void);         /* twng defines these */
extern int g2pvt_peek_message(MSG* pMsg);
extern int g2pvt_pump_message(MSG* pMsg);

#endif



/*
 * Since Win32 gives events posted to the app event queue priority over system
 * events, we need this inner loop to make sure we don't starve out UI input
 * events when the G2 scheduler is running continuously -- and so posting
 * NE_SCHEDULER_EVENT each time it's run. Note that this will process as many
 * network events as there are, since ui_event is not incremented for messages
 * in the range WM_USER..WM_APP, and network events lie there.  We believe this
 * can never starve out other events because of flow control and the exclusion
 * of the G2 scheduler.  At most one message group will be read, nothing will be
 * written, and the scheduler cannot process the group or write anything since
 * we're not calling it here.  -ncc, 6 Jan 1997, per discussion with jra and
 * mpc.
 */

extern long g2int_network_event_handler(); /*  defined in LISP. */

static int ui_event_count = 0;

long g2_event_ready (wait_allowed)
   long wait_allowed;
{
  MSG next_msg;

  while (!(non_scheduler_event_pending_p || scheduler_event_pending_p)) {

    if (wait_allowed) {
      g2pvt_wait_message();
      return TRUE;
    }
    /*If we are inside network event handling we do not process UI events*/
    if(handle_network_events != 1) {

      if(!g2pvt_peek_message(&next_msg))
        return FALSE;

      if (next_msg.message < WM_USER)
        ui_event_count++;
      else
        ui_event_count = 0;

      g2pvt_pump_message(&next_msg);
    } else {
      return FALSE;
    }
  }

  return TRUE;
}

void g2_event_wait ()
{
  g2_event_ready(TRUE);
}

extern void g2pvt_update_sockets_state();

long g2_event_cycle (wait_allowed)
   long wait_allowed;
{
  while (TRUE) {

    if (!scheduler_event_pending_p)
      g2_event_ready(FALSE);
    else if (ui_event_count < MAX_PREF_UI_EVENT_COUNT) {
      scheduler_event_pending_p = FALSE;
      g2_event_ready(FALSE);
      scheduler_event_pending_p = TRUE;
    }

    /* see note in msmain.c -- the quit_event is never actually
     * transmitted, because apparently posting the quit message does
     * not work.  So it also sets this variable so that we will know
     * to exit this loop. */
    if (g2ext_window_destroyed)
      return TRUE;

    if (non_scheduler_event_pending_p) {
      ne_dequeue_next_event();
      if (ne_next_event_ecode == quit_event)
        return TRUE;
      g2pvt_update_sockets_state();
      g2ext_note_network_event(ne_next_event_ecode, ne_next_event_socket_handle);
      g2int_network_event_handler(ne_next_event_ecode, ne_next_event_socket_handle, ne_next_event_status);
      return FALSE;
    }

    ui_event_count = 0;
    if (scheduler_event_pending_p) {
      scheduler_event_pending_p = 0;
      g2int_network_event_handler(scheduler_event, 0, 0);
      GdiFlush();
      return FALSE;
    }

    if (!wait_allowed)
      return FALSE;

    g2pvt_wait_message();
  }
}
