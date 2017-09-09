/* This file implements next_event & friends for non-NT, pure socket-based systems */

/* all API functions prefixed with "ne_" */

#if defined(sgi) || defined(WIN32)
#define FD_SETSIZE 4096
#endif

#include <sys/types.h>

#include "cprim.h"
#include "networks.h"
#include "trace.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#if !defined(WIN32) && !defined(__APPLE__)
#  include <sys/resource.h> /* getrlimit support */
#endif

#if !defined(WIN32)
#  include <sys/socket.h>
#  include <sys/time.h>
#endif

#include <memory.h>
#include <errno.h>

#if defined(sun) && !defined(__SVR4)
#   include <sys/ioctl.h>
#   include <netdni/dni.h>
#endif

#if defined(_IBMR2)
#  include <sys/select.h> /* only needed on this platform */
#endif

#ifdef WIN32
extern struct win32internet_error_code_struct {
  int code;
  char *name;
} win32internet_error_code_table [];
#endif

#if defined(WIN32)
#  define NOTSOCK_ERROR (WSAENOTSOCK - WSABASEERR)
#else
#  if defined(ENOTSOCK)
#    define NOTSOCK_ERROR EBADF
#  else
#    define NOTSOCK_ERROR -1000
#  endif
#endif

#define ne_initialize_network_interface g2ext_s_ne_initialize_network_interface
#define ne_map_fd_to_handle g2ext_s_ne_map_fd_to_handle
#define ne_unmap_fd g2ext_s_ne_unmap_fd
#define ne_connect_ni g2ext_s_ne_connect_ni
#define ne_register_active_ni g2ext_s_ne_register_active_ni
#define ne_deregister_inactive_ni g2ext_s_ne_deregister_inactive_ni
#define ne_enable_accept_events g2ext_s_ne_enable_accept_events
#define ne_disable_accept_events g2ext_s_ne_disable_accept_events
#define ne_enable_read_events g2ext_s_ne_enable_read_events
#define ne_disable_read_events g2ext_s_ne_disable_read_events
#define ne_enable_write_events g2ext_s_ne_enable_write_events
#define ne_disable_write_events g2ext_s_ne_disable_write_events
#define ne_enable_watch_events s_ne_enable_watch_events
#define ne_enable_display_events g2ext_s_ne_enable_display_events
#define ne_disable_display_events s_ne_disable_display_events
#define ne_display_events_enabled s_ne_display_events_enabled
#define ne_initialize_display_events s_ne_initialize_display_events
#define g2_event_cycle g2ext_s_g2_event_cycle
#define g2_event_wait g2ext_s_g2_event_wait
#define g2_event_ready g2ext_s_g2_event_ready
#define ne_initialize_event_handling g2ext_s_ne_initialize_event_handling
#define ne_print_events g2ext_s_ne_print_events
#define ne_sprint_events g2ext_s_ne_sprint_events
#define ne_lookup_handle_for_fd g2ext_s_ne_lookup_handle_for_fd
#define ne_enqueue_scheduler_event g2ext_s_ne_enqueue_scheduler_event
#define ne_set_next_timer_event g2ext_s_ne_set_next_timer_event
#define ne_last_error_length g2ext_s_ne_last_error_length
#define ne_last_error_string g2ext_s_ne_last_error_string

#include "netevent.h"

extern int g2ext_max_number_of_sockets;

extern int g2int_open_fd_callback(fd_type);
extern int g2int_close_fd_callback(fd_type);

extern long g2int_writing_fd_callback(fd_type);
extern long g2int_not_writing_fd_callback(fd_type);
extern void g2ext_network_unwatch_fd(fd_type);

extern long g2ext_write_string_to_console(char * string);
extern void g2ext_initialize_socket_index_table(/* void */);
extern long g2pvt_initialize_network_interface();



#ifdef unix
extern int g2ext_is_XPendingp();  /* windows.c */
extern int errno;
#endif

extern NETWORK_INTERFACE *g2ext_Watchers;

#if !defined(WIN32) && !defined(__APPLE__) && !defined(linux) && !(defined(Platform_Solaris) || defined(Platform_64bit))
extern int sys_nerr;
extern char *sys_errlist[];
#endif

#if defined(_WINSOCKAPI_)
extern int g2ext_lookup_socket_index (unsigned);
#endif

extern int g2ext_licensing_event_flag; /* defined in networks.c */
extern int g2ext_license_socket;         /* likewise */

G2pointer *g2ext_socket_to_NI_handle_table; /* ne_initialize_event_handling() allocates this array. */ 

static long mapped_socket_count = 0;           /* maintained by accessor and setter for previous table */
static int queued_events = 0;

static long milliseconds_til_next_timer_event;

static fd_type last_socket_served = 0;
static int last_event_type_returned = scheduler_event; 
static int scheduler_event_pending_p = 0;
static fd_type max_fd_so_far = 0;

/* NOTE THE IMPLICIT DISTINCTION between "active fds", sets of file descriptors
   associated with sockets, which we are potentially interested in, and "queued
   events", which are also fd_set structures, but which represent 1 deep queues
   of events, per socket, since they are the output of a call to select().  This
   is key to understanding the tcp next-event code.  -ncc, 27 May 1996 
   *****************/

static
fd_set active_fds,                   /* fd's we're interested in seeing events on */

       read_event_mask,                   /* masks to support disabling read, etc., events */
       write_event_mask,
       except_event_mask,

       queued_read_events,           /* 1 deep x g2ext_max_number_of_sockets wide "queues" of socket-events. */
       queued_write_events,           /* i.e., the returned values from select when ready_count > 0 */
       queued_except_events;

#define fdset_size_in_bytes sizeof(fd_set)
#define SOCKET_size_in_bytes sizeof(SOCKET)
#define u_int_size_in_bytes sizeof(u_int)

#ifdef NE_DEBUG_SELECT
static int bits_are_set_p(fdset)
fd_set * fdset;
{
  fd_type i;
  for (i = 0; i < (fd_type)g2ext_max_number_of_sockets; i++)
    if (FD_ISSET(i, fdset))
      return TRUE;
  return FALSE;
}
#endif


#ifdef NE_DEBUG_SELECT
static long pbits(initial_buffer,fdset)
char *initial_buffer;
fd_set * fdset;
{
  fd_type i;
  int firstp = TRUE;
  char *buffer = initial_buffer;
  sprintf (buffer,"<< ");
  buffer += strlen(buffer);
  for (i = 0; i < (fd_type) g2ext_max_number_of_sockets; i++)
    if (FD_ISSET(i, fdset)) {
      sprintf(buffer,"%s%d",firstp?"":",",i);
      buffer += strlen(buffer);
      firstp = FALSE;
    }
  sprintf(buffer," >> ");
  buffer += strlen(buffer);
  return buffer - initial_buffer;
}
#endif

/* various housekeeping functions, all part of the API. */

#ifdef NE_DEBUG
#define DEBUG_EVENT_CHANGE(name)  printf("%s: handle = %d, fd = %d.\n", name, handle, fd);  fflush(stdout);
#define DEBUG_FD_EVENT_CHANGE(name)  printf("%s: fd = %d.\n", name, fd);  fflush(stdout);
#else
#define DEBUG_EVENT_CHANGE(name)
#define DEBUG_FD_EVENT_CHANGE(name)
#endif

void ne_sprint_events(buffer,ni)
  char *buffer;
  NETWORK_INTERFACE *ni;
{
  fd_type fd = ni->handle;
  sprintf(buffer,
          "mask=%s%s%s pending=%s%s%s",
          FD_ISSET(fd, &read_event_mask)?"R":"",
          FD_ISSET(fd, &write_event_mask)?"W":"",
          FD_ISSET(fd, &except_event_mask)?"E":"",
          FD_ISSET(fd, &queued_read_events)?"R":"",
          FD_ISSET(fd, &queued_write_events)?"W":"",
          FD_ISSET(fd, &queued_except_events)?"E":"");
}

void ne_print_events(ni)
  NETWORK_INTERFACE *ni;
{
  char buffer[40];
  ne_sprint_events(buffer,ni);
  printf("%s",buffer);
}

void ne_enable_read_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;
  DEBUG_EVENT_CHANGE("ne_enable_read_events");
  FD_SET(fd, &read_event_mask);
}

void ne_disable_read_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;
  DEBUG_EVENT_CHANGE("ne_disable_read_events");
  FD_CLR(fd, &read_event_mask);
}

void ne_enable_write_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;
  DEBUG_EVENT_CHANGE("ne_enable_write_events");
  FD_SET(fd, &write_event_mask);
  g2int_writing_fd_callback(fd);
}

void ne_disable_write_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;
  DEBUG_EVENT_CHANGE("ne_disable_write_events");
  FD_CLR(fd, &write_event_mask);
  g2int_not_writing_fd_callback(fd);
}

void ne_enable_accept_events(handle)
G2pointer handle;
{

  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;

  DEBUG_EVENT_CHANGE("ne_enable_accept_events");

  /* a listener socket becomes readable when an incoming connection request is queued. */
  FD_CLR(fd, &write_event_mask);
  g2int_not_writing_fd_callback(fd);
  if ((net_interface->protocol_id == TCP_IP) ||
      (net_interface->protocol_id == UDP)) {
    FD_CLR(fd, &except_event_mask);
    FD_SET(fd, &read_event_mask);
  }
}

void ne_disable_accept_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;

  FD_CLR(fd, &write_event_mask);
  g2int_not_writing_fd_callback(fd);
  DEBUG_EVENT_CHANGE("ne_disable_accept_events");
  FD_CLR(fd, &except_event_mask);
  FD_CLR(fd, &read_event_mask);
}

static void ne_enable_connect_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;

  DEBUG_EVENT_CHANGE("ne_enable_connect_events");

  if (!(net_interface->connected_p || net_interface->listener_p || net_interface->watch_p)) {
    FD_SET(fd, &write_event_mask);
    g2int_writing_fd_callback(fd);
    FD_SET(fd, &except_event_mask);
  }
}

static void ne_disable_connect_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;

  DEBUG_EVENT_CHANGE("ne_disable_connect_events");

  if (!(net_interface->connected_p || net_interface->listener_p || net_interface->watch_p)) {
    FD_CLR(fd, &write_event_mask);
    g2int_not_writing_fd_callback(fd);
    FD_CLR(fd, &except_event_mask);
  }
}

static void ne_enable_except_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;

  DEBUG_EVENT_CHANGE("ne_enable_except_events");

  FD_SET(fd, &except_event_mask);
}

static int watchers_enabled_p = FALSE;

static void ne_enable_watch_events_fd(fd, for_writing_p)
   fd_type fd;
   int for_writing_p;
{
  if (!watchers_enabled_p) return;
  FD_SET(fd, &read_event_mask);
  if (for_writing_p)
    FD_SET(fd, &write_event_mask);
  else
    FD_CLR(fd, &write_event_mask);
  FD_SET(fd, &except_event_mask);
}

static void ne_disable_watch_events_fd(fd)
   fd_type fd;
{
  if (watchers_enabled_p) return;
  DEBUG_FD_EVENT_CHANGE("ne_disable_watch_events_fd");
  FD_CLR(fd, &read_event_mask);
  FD_CLR(fd, &write_event_mask);
  FD_CLR(fd, &except_event_mask);
}

void ne_enable_watch_events(handle)
G2pointer handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);
  fd_type fd = net_interface->handle;
  DEBUG_EVENT_CHANGE("ne_enable_watch_events");
  ne_enable_watch_events_fd(fd,net_interface->watch_for_writing_p);
}

void g2ext_check_watched_fds()
{
  NETWORK_INTERFACE *w;

  for(w = g2ext_Watchers; w != 0; w = w->parent_listener)
    if (w->watch_p) {
      struct timeval timeout;
      fd_set fds;
      fd_type fd = w->handle;

      timeout.tv_sec = (long)0;
      timeout.tv_usec = (long)0;
      FD_ZERO(&fds);
      FD_SET(fd,&fds);
      if (-1 == select(g2ext_max_number_of_sockets,&fds,&fds,&fds,&timeout)) {
#if defined(_WINSOCKAPI_)
        errno = WSAGetLastError() - WSABASEERR;
#endif
        if (errno == NOTSOCK_ERROR) {
          char message[80];
          sprintf(message,"The fd %d is being watched, but is not open.  Calling gsi_unwatch_fd.",fd);
          g2ext_write_string_to_console(message);
          g2ext_network_unwatch_fd(fd);
        }
      }
    }
}

void ne_initialize_network_interface (network_intfc)
NETWORK_INTERFACE * network_intfc;
{
  fd_type fd = network_intfc->handle;

  /* initially, all events are disabled. */

  FD_CLR(fd, &write_event_mask);
  FD_CLR(fd, &except_event_mask);
  FD_CLR(fd, &read_event_mask);
}


static short ne_event_handling_initialized_p = 0;

void ne_initialize_event_handling()
{
  if (ne_event_handling_initialized_p) return; /* once only! */

  ne_event_handling_initialized_p = 1;

#ifdef WIN32
  {
    WSADATA WSAStartupData;
    if ((WSAStartup(MAKEWORD(1,1), &WSAStartupData)) == 0) {
      g2ext_max_number_of_sockets = WSAStartupData.iMaxSockets;
    } else {
      MessageBox(NULL, "Cannot start Winsock.", NULL, MB_OK);
    }
  }
#else
  g2ext_max_number_of_sockets = FD_SETSIZE;
#endif

  g2ext_socket_to_NI_handle_table = (G2pointer *) calloc(g2ext_max_number_of_sockets, sizeof(G2pointer));

  /* zero out various items of global state */
  FD_ZERO(&active_fds);

  FD_ZERO(&read_event_mask);
  FD_ZERO(&write_event_mask);
  FD_ZERO(&except_event_mask);

  FD_ZERO(&queued_read_events);
  FD_ZERO(&queued_write_events);
  FD_ZERO(&queued_except_events);

  queued_events = 0;

  g2ext_initialize_socket_index_table();
}

#if defined(sun) && !defined(__SVR4)
extern char *g2ext_dni_status_msg[];
#endif

static char unknown_code_message[40];

static char *ne_error_string(err,network_type)
  int err;
  int network_type;
{
  if (err < 0) 
    switch (network_type) {
    case TCP_IP: {
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
        return "Empty host name"; }
    } else {
#ifdef WIN32
      int i,c;
    retry:
      for(i=0; 0!=(c=win32internet_error_code_table[i].code) && c!=err; i++);
      if (c==err)
        return win32internet_error_code_table[i].name;
      else if (err < WSABASEERR) {
        err += WSABASEERR;
        goto retry;
      }
#elif defined(linux) || (defined(Platform_Solaris) && defined(Platform_64bit))
      char *error_text = strerror(err);
      if (0!=error_text)
	return error_text;
#else
      if (err < sys_nerr) {
        if (0!=sys_errlist[err]) 
          return (char *) sys_errlist[err];
      }
#endif
    }
#if defined(sun) && !defined(__SVR4) && defined(Platform_32bit)
  if (LOWEST_DNI_ERROR <= ((-err)-1024) && ((-err)-1024) <= HIGHEST_DNI_ERROR)
    return g2ext_dni_status_msg[((-err)-1024)-LOWEST_DNI_ERROR];    
  if (0 <= ((-err)-1024) && ((-err)-1024) < sys_nerr && 0 != sys_errlist[((-err)-1024)])
    return sys_errlist[((-err)-1024)];
#endif
  sprintf(unknown_code_message,"Unknown error code %d",err);
  return unknown_code_message;
}

static char *ne_get_last_error_string(handle)
    long handle;
{
  /* return the string describing the last network error associated with this endpoint,
     in the buffer pointed to by the buffer arg. */
  NETWORK_INTERFACE *ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(handle);

  if (ni == NULL) return "";
  return ne_error_string(ni->last_status,ni->protocol_id);
}

long ne_last_error_length(handle)
    long handle;
{
  return strlen(ne_get_last_error_string(handle));
}

void ne_last_error_string(handle, buffer)
  long handle;
  char *buffer;
{
  strcpy(buffer, ne_get_last_error_string(handle));    
}


/*
 * Trivial timer facility for ne_get_next_event() on Unix
 */

#ifdef unix
typedef struct {
  int activep;
  void (*callback)(void *);
  void *arg;
  struct timeval expiry;
} TimeoutCallback;

static TimeoutCallback cb_timeout;

#define IsTimeoutCallbackActive() (cb_timeout.activep)

int g2pvt_ensure_timeout_callback(int timeout, void (*callback)(void*), void *arg)
{
  if(cb_timeout.activep)
    return 0;
  cb_timeout.activep = TRUE;
  cb_timeout.callback = callback;
  cb_timeout.arg = arg;
  gettimeofday(&cb_timeout.expiry, 0);
  TIMEVAL_ADDMSEC(&cb_timeout.expiry, timeout);
  return 1;
}

static int g2pvt_get_timeout_callback_milliseconds_to_go()
{
  if(cb_timeout.activep) {
    struct timeval now, tem;
    tem.tv_sec = cb_timeout.expiry.tv_sec;
    tem.tv_usec = cb_timeout.expiry.tv_usec;
    gettimeofday(&now, NULL);
    TIMEVAL_SUB(&tem, &now);
    return 1000*tem.tv_sec + tem.tv_usec/1000;
  } else {
    return 0;
  }
}

static void g2pvt_maybe_trigger_timeout_callback()
{
  struct timeval now;
  if(!cb_timeout.activep || !cb_timeout.callback)
    return;
  gettimeofday(&now, NULL);
  if(TIMEVAL_GE(&now, &cb_timeout.expiry)) {
    cb_timeout.activep = FALSE;
    (*cb_timeout.callback)(cb_timeout.arg);
  }
}
#endif /* unix */


void ne_set_next_timer_event(milliseconds_to_go)
    long milliseconds_to_go;
{
  g2ext_network_io_trace_note_d("ne_set_next_timer_event %d", milliseconds_to_go);

#ifdef unix
  if(milliseconds_to_go>0 && IsTimeoutCallbackActive())
    milliseconds_to_go = MAX(1,MIN(milliseconds_to_go, g2pvt_get_timeout_callback_milliseconds_to_go()));
#endif

  milliseconds_til_next_timer_event = milliseconds_to_go;
}

void ne_enqueue_scheduler_event()
{
  g2ext_network_io_trace_note("ne_enqueue_scheduler_event");
  scheduler_event_pending_p = 1;
}

void ne_map_fd_to_handle(fd, ni_handle)
    fd_type fd;
    G2pointer ni_handle;
{
  int si;
  if (max_fd_so_far < fd) max_fd_so_far = fd;
#if defined(_WINSOCKAPI_)
  si = g2ext_lookup_socket_index(fd);
#else
  si = fd;
#endif
  g2ext_socket_to_NI_handle_table[si] = ni_handle;
  mapped_socket_count ++;
}

G2pointer ne_lookup_handle_for_fd(fd)
    fd_type fd;
{
  int si;
#if defined(_WINSOCKAPI_)
  si = g2ext_lookup_socket_index(fd);
#else
  si = fd;
#endif
  return(g2ext_socket_to_NI_handle_table[si]);
}

G2pointer ne_unmap_fd(fd)
    fd_type fd;
{
  int si;
  G2pointer return_to_be_reclaimed;
#if defined(_WINSOCKAPI_)
  si = g2ext_lookup_socket_index(fd);
#else
  si = fd;
#endif
  return_to_be_reclaimed = g2ext_socket_to_NI_handle_table[si];
  g2ext_socket_to_NI_handle_table[si] = (G2pointer) -1;
  mapped_socket_count --;
  return(return_to_be_reclaimed);
}

#ifdef unix
G2pointer g2ext_window_network_interface_handle = -1;
static int have_window_network_interface_handle = FALSE;
static int display_events_disabled_p = FALSE;
#endif

void ne_enable_display_events()
{
#ifdef unix
  display_events_disabled_p = FALSE;
  if (have_window_network_interface_handle)
    ne_enable_read_events(g2ext_window_network_interface_handle);
#endif
}

void ne_disable_display_events()
{
#ifdef unix
  display_events_disabled_p = TRUE;
  if (have_window_network_interface_handle)
    ne_disable_read_events(g2ext_window_network_interface_handle);
#endif
}
  
long ne_display_events_enabled()
{
#ifdef unix
  return !display_events_disabled_p;
#else
  return 0;
#endif
}

void ne_initialize_display_events(window_connection_number)
    int window_connection_number;
{
#ifdef unix
  G2pointer handle;
  NETWORK_INTERFACE * netptr;

#ifdef NE_DEBUG  
  printf ("NEDE: window_connection_number: %d\n", window_connection_number);
  fflush(stdout);      
#endif
  g2int_open_fd_callback(window_connection_number);
  handle = g2pvt_initialize_network_interface( /* X windows transport protocol: */
                                              TCP_IP,
                                              (long) window_connection_number,
                                              "XWindow Socket",
                                              DISPLAY_INTERFACE_STATUS, 0);
  g2ext_window_network_interface_handle = handle;
  have_window_network_interface_handle = TRUE;

#ifdef NE_DEBUG  
  printf ("NEDE: handle: %d\n", handle);
  fflush(stdout);      

  if (handle < 0) {
    printf("\nEDE: could not initialize server interface.\n"); fflush(stdout);
    return;
  }
#endif

  netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long)handle);

#ifdef NE_DEBUG  
  if (netptr == NULL){
    printf("\nEDE: failed to map g2pointer for server interface.\n"); fflush(stdout);
    return;
  }
#endif
#endif
}


void ne_register_active_ni(ni_handle)
G2pointer ni_handle;
{

  NETWORK_INTERFACE *ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(ni_handle);
  int fd;

#ifdef NE_DEBUG  
  printf("ne_register_active_ni: handle = %d\n", ni_handle);
  fflush(stdout);
#endif

  fd = ni->handle;                /* socket file descriptor of this network interface.  */

  /* mark this fd as in use. */
  FD_SET(fd, &active_fds);

  if (ni->listener_p) 
    ne_enable_accept_events(ni_handle);
  else if (ni->connected_p) {
    ne_enable_read_events(ni_handle);
    ne_enable_except_events(ni_handle);
  }
  else if (ni->watch_p)
    ne_enable_watch_events(ni_handle);
  else if (!ni->icmp_p)
    ne_enable_connect_events(ni_handle);
}


static void clear_queued_events(fd_type fd)
{
  if (queued_events > 0) {
    if (FD_ISSET(fd, &queued_read_events)) {
      FD_CLR(fd, &queued_read_events);
      queued_events--;
    }
    if (FD_ISSET(fd, &queued_write_events)) {
      FD_CLR(fd, &queued_write_events);
      queued_events--;
    }
    if (FD_ISSET(fd, &queued_except_events)) {
      FD_CLR(fd, &queued_except_events);
      queued_events--;
    }
  }
}

void ne_deregister_inactive_ni(ni_handle)
G2pointer ni_handle;
{
  NETWORK_INTERFACE *net_interface = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(ni_handle);
  fd_type fd;

  fd = net_interface->handle;
  FD_CLR(fd, &active_fds);        /* we just don't care any more. */
  FD_CLR(fd, &read_event_mask);
  FD_CLR(fd, &write_event_mask);
  FD_CLR(fd, &except_event_mask);
  clear_queued_events(fd);
}

void ne_connect_ni(ni_handle)
G2pointer ni_handle;
{
  NETWORK_INTERFACE *ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(ni_handle);
  ne_disable_connect_events(ni_handle);
  ni->connected_p = 1;
  ne_enable_read_events(ni_handle);
  ne_enable_except_events(ni_handle);
}

static int ne_event_poll = FALSE;
extern long g2ext_gensym_SIGALARM_was_seen;

static int recent_null_callback_p = 0;

void g2ext_note_null_write_callbacks ()
{
  recent_null_callback_p = 1;
}


static long ne_get_next_event(NI_handle_out, event_status_out)
G2pointer *NI_handle_out;        /* a pointer to a G2pointer (to a NETWORK_INTERFACE). */
long *event_status_out;                /* a pointer to a long. */
{
  fd_type i;
  int ready_count;
  int si;
  struct timeval timeout;
  NETWORK_INTERFACE * network_interface = NULL;
#ifdef _IBMR2
  unsigned long optlen = sizeof(int);
#else
  int optlen = sizeof(int);
#endif
#ifdef NE_DEBUG_SELECT
  char mbuffer[400];
  char *buffer;
#endif

  /* set output args to reasonable default values */
  (*NI_handle_out) = (G2pointer) 0;
  (*event_status_out) = 0L;
  g2ext_licensing_event_flag = FALSE; 

  if (queued_events == 0) {

    /* if we just finished emptying a queue of network events,
       we now return a scheduler event to allow G2 to react. */
    if (scheduler_event_pending_p && (last_event_type_returned != scheduler_event))
      {
        scheduler_event_pending_p = 0;
        milliseconds_til_next_timer_event = 0;
        last_event_type_returned = scheduler_event;
        return scheduler_event;
      } 
#ifdef unix
    else if (!display_events_disabled_p && g2ext_is_XPendingp())
      {
        milliseconds_til_next_timer_event = 0;
        last_event_type_returned = display_event;
        return display_event;
      } 
#endif
    if (ne_event_poll || scheduler_event_pending_p) {
      timeout.tv_sec = (long)0;
      timeout.tv_usec = (long)0;
    } else if (milliseconds_til_next_timer_event >= 1000) {
      timeout.tv_sec = (long) milliseconds_til_next_timer_event / 1000;
      timeout.tv_usec = (long) (milliseconds_til_next_timer_event -
                                (timeout.tv_sec * 1000)) * 1000;
    } else {
      timeout.tv_sec = (long)0;
      timeout.tv_usec = (long)milliseconds_til_next_timer_event * 1000;
    }

#if defined(_WINSOCKAPI_) && defined(PACKAGING_G2_ENTERPRISE) //We don't need to copy whoole fd_sets under the WinSock.
    if(read_event_mask.fd_count)
      memcpy((char *)&queued_read_events, (char *)&read_event_mask, u_int_size_in_bytes + read_event_mask.fd_count * SOCKET_size_in_bytes);
    else
      queued_read_events.fd_count = 0;

    if(write_event_mask.fd_count)
      memcpy((char *)&queued_write_events, (char *)&write_event_mask, u_int_size_in_bytes + write_event_mask.fd_count * SOCKET_size_in_bytes);
    else
      queued_write_events.fd_count = 0;

    if(except_event_mask.fd_count)
      memcpy((char *)&queued_except_events, (char *)&except_event_mask, u_int_size_in_bytes + except_event_mask.fd_count * SOCKET_size_in_bytes);
    else
      queued_except_events.fd_count = 0;
#else
    memcpy((char *)&queued_read_events, (char *)&read_event_mask, fdset_size_in_bytes);
    memcpy((char *)&queued_write_events, (char *)&write_event_mask, fdset_size_in_bytes);
    memcpy((char *)&queued_except_events, (char *)&except_event_mask, fdset_size_in_bytes);
#endif

#ifdef NE_DEBUG_SELECT
    buffer = mbuffer;
    sprintf(buffer,"<masks for select>  ");
    buffer += strlen(buffer);
    buffer += pbits(buffer,&queued_read_events);
    buffer += pbits(buffer,&queued_write_events);
    buffer += pbits(buffer,&queued_except_events);
    g2ext_network_io_trace_note(mbuffer);
#endif
    
    g2ext_gensym_SIGALARM_was_seen = FALSE;
  retry:

#if defined(_WINSOCKAPI_)
    if ((queued_read_events.fd_count == 0) &&
        (queued_write_events.fd_count == 0)) {
      fd_type i;
    
      if (queued_except_events.fd_count == 0) {
        /* Bug HQ-5286255 "GSI ErrorCode 90 socket-handle is 0, event-status is 22" */
        return no_event;
      }
    
      if (recent_null_callback_p) {
        /* Bug HQ-5293253 "GSI: socket gets blocked, never gets unblocked" */
        for (i = 0; i < (fd_type)g2ext_max_number_of_sockets; i++) {
          if (FD_ISSET(i, &queued_except_events)) {
            FD_SET(i, &queued_read_events);
            FD_SET(i, &read_event_mask);
            recent_null_callback_p = 0;
          }
        }
      }
    }
#endif

    ready_count = select(g2ext_max_number_of_sockets,
                         &queued_read_events,
                         &queued_write_events,
                         &queued_except_events,
                         &timeout);
    if (ready_count < 0) {
#if defined(_WINSOCKAPI_)
       errno = WSAGetLastError() - WSABASEERR;
#endif
       if (errno == EINTR) {
         if (g2ext_gensym_SIGALARM_was_seen) goto retry;
         ready_count = 0;
         errno = 0;
       }
    }

#ifdef NE_DEBUG_SELECT
    if (ready_count > 0 ||
        bits_are_set_p(&queued_read_events) ||
        bits_are_set_p(&queued_write_events) ||
        bits_are_set_p(&queued_except_events)) {
      buffer = mbuffer;
      sprintf(buffer,"<select returned %d> ",ready_count);
      buffer += strlen(buffer);
      buffer += pbits(buffer,&queued_read_events);
      buffer += pbits(buffer,&queued_write_events);
      buffer += pbits(buffer,&queued_except_events);
      g2ext_network_io_trace_note(mbuffer);
    }
#endif

#ifdef unix
    if(IsTimeoutCallbackActive())  /* Only ever true for Unix G2 or Telewindows */
      g2pvt_maybe_trigger_timeout_callback();
#endif

    if (ready_count == 0) {        /* timed out */
      (*NI_handle_out) = 0;
      (*event_status_out) = 0L;
      if (ne_event_poll && !scheduler_event_pending_p) {
        return no_event;
      } else {
        scheduler_event_pending_p = 0;
        milliseconds_til_next_timer_event = 0;
        last_event_type_returned = scheduler_event;
        return scheduler_event;
      }
    } else if (ready_count < 0) {  /* error during select. */
      queued_events = 0;
      (*event_status_out) = (long)errno;
      last_event_type_returned = error_event;
      return error_event;
    } 

    /* if we're here, ready_count must be > 0, thus there are some events to dispatch. */
    queued_events = ready_count; /* count is count of all bits set in all descriptors. */
  }
  
#if defined(_WINSOCKAPI_) && defined(PACKAGING_G2_ENTERPRISE)
  /* return next event off the internal queue. */
  if(!queued_events)
    return no_event;

  if(queued_read_events.fd_count)
    last_socket_served = queued_read_events.fd_array[0];
  else if(queued_write_events.fd_count)
    last_socket_served = queued_write_events.fd_array[0];
  else if(queued_except_events.fd_count)
    last_socket_served = queued_except_events.fd_array[0];
  else
    return no_event;
#else
  for (i = 0; (queued_events >  0) && (i <= max_fd_so_far); i++) {

    if (last_socket_served == max_fd_so_far) /* round robin */
      last_socket_served = 0;
    else
      last_socket_served++;
#endif
  if (FD_ISSET(last_socket_served, &queued_read_events)) {
    FD_CLR(last_socket_served, &queued_read_events);
    queued_events--;

    /* see if this is a licensing event. */
    if (last_socket_served == (fd_type)g2ext_license_socket)
    {
      g2ext_licensing_event_flag = TRUE;
      (*NI_handle_out) = 0;
      (*event_status_out) = 0L;
      scheduler_event_pending_p = 0;
      milliseconds_til_next_timer_event = 0;
      last_event_type_returned = scheduler_event;
      return scheduler_event;
    }
#if defined(_WINSOCKAPI_)
    si = g2ext_lookup_socket_index(last_socket_served);
#else
    si = last_socket_served;
#endif
    (*NI_handle_out) = g2ext_socket_to_NI_handle_table[si];
    network_interface = (NETWORK_INTERFACE *)g2ext_map_g2pointer_to_cpointer(*NI_handle_out);
    /* Check for incoming connection on listener, or EOF (nothing to read when
        the read bit set) on a connected socket: */
    if (network_interface->listener_p) {
      last_event_type_returned = accept_event;
      ne_disable_read_events(*NI_handle_out);
    } else if (network_interface->display_event_interface_p) {
      last_event_type_returned = display_event;
      ne_disable_read_events(*NI_handle_out);
    } else if (network_interface->watch_p) {
      last_event_type_returned = watch_event;
    } else {
      last_event_type_returned = read_event;
      ne_disable_read_events(*NI_handle_out);
    }
#if !defined(_WINSOCKAPI_) || !defined(PACKAGING_G2_ENTERPRISE)
    break;
#endif
  } else if (FD_ISSET(last_socket_served, &queued_write_events)) {
    FD_CLR(last_socket_served, &queued_write_events);
    queued_events--;
#if defined(_WINSOCKAPI_)
    si = g2ext_lookup_socket_index(last_socket_served);
#else
    si = last_socket_served;
#endif
    (*NI_handle_out) = g2ext_socket_to_NI_handle_table[si];
    network_interface = (NETWORK_INTERFACE *)g2ext_map_g2pointer_to_cpointer(*NI_handle_out);
    if (!network_interface->watch_p)
      ne_disable_write_events(*NI_handle_out); /* write events are one-shot affairs. */
    /* Check for connect or write events: */
    if (network_interface->listener_p) {
      /* write event on a listener!  This is a problem.  Deal with it at a higher level. */
      last_event_type_returned = write_event;
    } else if (network_interface->connected_p) {
      last_event_type_returned = write_event;
    } else if (network_interface->watch_p) {
      last_event_type_returned = watch_event;
    } else {
      /* gotta check for failed connections! */
	    if (getsockopt(last_socket_served, 
		            SOL_SOCKET,
		            SO_ERROR, 
		            (char *)event_status_out,
		            &optlen) != 0) {
                  (*event_status_out) = errno;
                  network_interface->last_status = errno;
	    } else if (*event_status_out != 0) {
	      network_interface->last_status = (*event_status_out);
	    }
      ne_connect_ni(*NI_handle_out);
      last_event_type_returned = connect_event;
    }
#if !defined(_WINSOCKAPI_) || !defined(PACKAGING_G2_ENTERPRISE)
    break;
#endif
  }
  else if (FD_ISSET(last_socket_served, &queued_except_events)) {
    FD_CLR(last_socket_served, &queued_except_events);
    queued_events--;
#if defined(_WINSOCKAPI_)
    si = g2ext_lookup_socket_index(last_socket_served);
#else
    si = last_socket_served;
#endif
    (*NI_handle_out) = g2ext_socket_to_NI_handle_table[si];
    network_interface = (NETWORK_INTERFACE *)g2ext_map_g2pointer_to_cpointer(*NI_handle_out);
    if (!network_interface) {
      last_event_type_returned = no_event;
    } else if (network_interface->listener_p) {
      last_event_type_returned = accept_event;
    } else if (network_interface->watch_p) {
      last_event_type_returned = watch_event;
    } else {
 	    if (getsockopt(last_socket_served, 
 		            SOL_SOCKET,
 		            SO_ERROR, 
 		            (char *)event_status_out,
 		            &optlen) != 0) {
 	      (*event_status_out) = errno;
 	      network_interface->last_status = errno;
 	      network_interface->connect_status = errno;
 	    } else if (*event_status_out != 0) {
 	      network_interface->last_status = (*event_status_out);
 	      network_interface->connect_status = (*event_status_out);
 	    }
      last_event_type_returned = close_event;
    }
#if !defined(_WINSOCKAPI_) || !defined(PACKAGING_G2_ENTERPRISE)
    break;
#endif
  }
#if !defined(_WINSOCKAPI_) || !defined(PACKAGING_G2_ENTERPRISE)
  } /* end of for loop */
#endif
  return last_event_type_returned;
}

static void enable_watchers()
{
  NETWORK_INTERFACE *w;

  if (watchers_enabled_p) return;
  watchers_enabled_p = TRUE;
  for(w = g2ext_Watchers; w != 0; w = w->parent_listener)
    if (w->watch_p)
      ne_enable_watch_events_fd(w->handle,w->watch_for_writing_p);
}

static void disable_watchers()
{
  NETWORK_INTERFACE *w;

  if (!watchers_enabled_p) return;
  watchers_enabled_p = FALSE;
  for(w = g2ext_Watchers; w != 0; w = w->parent_listener)
    if (w->watch_p)
      ne_disable_watch_events_fd(w->handle);
}

extern long g2int_network_event_handler(); /*  defined in LISP. */

static long have_next_event_p = FALSE;
static long next_event_ecode = 0L;
static long next_event_socket_handle;
static long next_event_status;

static Gensym_Long wait_interval = 0;

long g2ext_get_waited_period()
{
  return wait_interval;
}


void g2ext_reset_waited_period()
{
  wait_interval = 0;
}

long g2pvt_record_waits = 0;

void g2ext_set_record_waits(waitp)
     long waitp;
{
  g2pvt_record_waits = waitp;
}

void g2pvt_incf_waited_period(increment)
     long increment;
{
  wait_interval += increment;
}

extern Gensym_Long g2ext_g2_clock_ticks(Gensym_Long);

long g2_event_ready(wait_allowed)
   long wait_allowed;
{
  long total, start;
  if (g2pvt_record_waits)
    start = g2ext_g2_clock_ticks(IMOST_POSITIVE_FIXNUM);
  if (!have_next_event_p) {
    ne_event_poll = !wait_allowed;
    next_event_ecode = ne_get_next_event (&next_event_socket_handle,
                                          &next_event_status);
    ne_event_poll = FALSE;
    have_next_event_p = (next_event_ecode != no_event);
  }
  if (g2pvt_record_waits) {  
    total = g2ext_g2_clock_ticks(IMOST_POSITIVE_FIXNUM) - start;
    if (total < 0) 
      total += IMOST_POSITIVE_FIXNUM;
    g2pvt_incf_waited_period(total);
  }
  return have_next_event_p;
}

void g2_event_wait()
{
  enable_watchers();
  g2_event_ready(TRUE);
  if (next_event_ecode == watch_event) {
    NETWORK_INTERFACE *w;

    have_next_event_p = FALSE;
    for(w = g2ext_Watchers; w != 0; w = w->parent_listener)
      if (w->watch_p)
        clear_queued_events(w->handle);
  }
}



/* vsnprintf, when given too small a buffer, is supposed to return "the number
 * of characters formatted, that is, the number of characters that would have
 * been written to the buffer if it were large enough."  Therefore, one can
 * obtain the required buffer size by calling vsnprintf first with a buffer
 * known to be too small.
 *
 * Platforms that define BROKEN_VSNPRINTF do not support this.  Therefore,
 * on those platforms, just statically allocate a buffer expected to be large
 * enough.  If *anything* goes wrong, we'll just post a default error message.
 * We will not risk going into an infinite loop or allocating a buffer
 * that's 100MB.
 *
 * As of this commit, only Windows is known to be broken in this way, but
 * it's easy to define BROKEN_VSNPRINTF on more platforms if need be.
 */
#if defined(WIN32)
#  define vsnprintf _vsnprintf
#endif

#if defined(WIN32) || defined(__osf__) || defined(_IBMR2) || defined(__hpux)
#  define BROKEN_VSNPRINTF
#endif

#ifdef BROKEN_VSNPRINTF
#  define SIZE_OF_DUMMY_STRING 1024
#else
#  define SIZE_OF_DUMMY_STRING    1
#endif

#define ERROR_WITHIN_AN_ERROR_TEXT "an unknown error has occurred"

static char dummy_format_string[SIZE_OF_DUMMY_STRING];

/* new_asprintf for Unix and Windows */
static int
new_asprintf(char **s, const char *format, ...)
{
  va_list ap;
  int n;

  va_start (ap, format);
  n = vsnprintf(dummy_format_string, SIZE_OF_DUMMY_STRING, format, ap);
  if (n > 0) {
    /* Whether or not the buffer was big enough, a positive value indicates
     * the size of the string we want to use.  Add one to make space for
     * the null character, and dynamically allocate a string to copy it into.
     */
    *s = (char *) malloc((n + 1) * sizeof(char));
    (*s)[n] = '\0';
#ifdef BROKEN_VSNPRINTF
    /* We wrote into a relatively big buffer and got a positive value back
     * in return.  Copy it into our new string. */
    strncpy(*s, dummy_format_string, n);
#else
    /* We wrote into an intentionally tiny buffer, then allocated a new buffer
     * based on the return value we got back.  We trust that this will work.
     */
    vsnprintf(*s, n, dummy_format_string, ap);
#endif
  } else {
    /* For whatever reason, we got an error value back from the first vsnprintf.
     * Just give it up, and create a dynamic buffer for a default error.
     */
    n = 1 + strlen(ERROR_WITHIN_AN_ERROR_TEXT);
    *s = (char *) malloc(n * sizeof(char));
    (*s)[n] = '\0';
    strncpy(*s, ERROR_WITHIN_AN_ERROR_TEXT, n);
  }
  va_end(ap);

  return n;
}


/* The following code, hilariously enough, does NOT define a function called
 * g2_event_cycle.  g2_event_cycle is defined in event.c.  Through the cunning
 * use of macros, this code actually defines a different function.  On Windows,
 * for GSI, this code defines a function called g2ext_s_g2_event_cycle.  Despite
 * the prominence of "g2" in that name, it is in fact an integral part of GSI.
 * On the other hand, on Windows at least, this code is NOT part of G2, whose
 * real event cycle is defined in ntevent.c.  -jv, 1/18/03
 */
long g2_event_cycle(wait_allowed)
  long wait_allowed;
{
  disable_watchers();
 again:
  if (g2_event_ready(wait_allowed)) {
    if (next_event_ecode < 0) {
      char *message;
#ifdef _WINSOCKAPI_
      int actual_errno = errno + WSABASEERR;
#else
      int actual_errno = errno;
#endif

      new_asprintf(&message, "event error: %s (errno = %d)",
                   ne_error_string(errno, 0),
                   actual_errno);
      /* zero is known to not be handled by ne_error_string, okay because we
         assume the first argument (errno) not to be synthetic error code */
      if (message) {
        g2ext_write_string_to_console(message);
        free(message);
      }

      if (errno == NOTSOCK_ERROR)
        g2ext_check_watched_fds();
    }
    
    have_next_event_p = FALSE;
    g2ext_note_network_event(next_event_ecode, next_event_socket_handle);
    if (next_event_ecode == watch_event) goto again;
    g2int_network_event_handler(next_event_ecode, next_event_socket_handle,
                                next_event_status);
  }
  
  return FALSE;
}

/*
 * Windows Implemention Only!
 * In Windows platform,the asynchronous task handle returned by `WSAAsyncGetHostByName'
 * is an increasing integer number,so we cache the mapping between `g2pvt_resolver_handle'
 * and `g2 pointer of network interface' in structure `SOCKET_TO_NI_HANDLE_TABLE',
 * and the g2 pointer can be accessed by handles[g2pvt_resolver_handle - start_index].
 * when the slot `used' is zero, G2 will reuse current structure before it allocate a new one.
 */

#define SOCKET_TO_NI_HANDLE_TABLE_SIZE 512L

typedef struct a_socket_to_NI_handle_table
{
  struct a_socket_to_NI_handle_table *next_node;
  long used; /* how many g2 pointers has been putted into array `handles'. */
  long start_index; /* the start index of `g2pvt_resolver_handle'. */
  G2pointer handles[SOCKET_TO_NI_HANDLE_TABLE_SIZE]; /* array to hold g2 pointers of network interface.*/
} SOCKET_TO_NI_HANDLE_TABLE;

SOCKET_TO_NI_HANDLE_TABLE *g2pvt_resolver_to_NI_handle_table = NULL;

int cache_socket_to_NI_handle(resolver_handle, g2_pointer)
    long resolver_handle;
    G2pointer g2_pointer;
{
  SOCKET_TO_NI_HANDLE_TABLE *pCurTable = g2pvt_resolver_to_NI_handle_table;
  SOCKET_TO_NI_HANDLE_TABLE *pPrevTable = NULL;

  /* try to find a suitable node */
  while (pCurTable) {
    if (pCurTable->used > 0 &&
        resolver_handle >= pCurTable->start_index &&
        resolver_handle < (pCurTable->start_index + SOCKET_TO_NI_HANDLE_TABLE_SIZE)) {
      break;
    }
    pPrevTable = pCurTable;
    pCurTable = pCurTable->next_node;
  }
  /* found, or reach the end of node chain */
  if (pCurTable == NULL) {
    pCurTable = g2pvt_resolver_to_NI_handle_table;
    /* try to find a empty node for reuse */
    while(pCurTable) {
      if (pCurTable->used == 0) {
        break;
      }
      pCurTable = pCurTable->next_node;
    }
    if (pCurTable) {
      /* reuse exist node */
      pCurTable->start_index = resolver_handle / SOCKET_TO_NI_HANDLE_TABLE_SIZE * SOCKET_TO_NI_HANDLE_TABLE_SIZE + 1;
      pCurTable->used = 1;
      pCurTable->handles[resolver_handle - pCurTable->start_index] = g2_pointer;
    } else {
      /* create new node */
      pCurTable = (SOCKET_TO_NI_HANDLE_TABLE *)calloc(1,sizeof(SOCKET_TO_NI_HANDLE_TABLE));
      if (pCurTable == NULL) {
        return -1;
      }
      pCurTable->start_index = resolver_handle / SOCKET_TO_NI_HANDLE_TABLE_SIZE * SOCKET_TO_NI_HANDLE_TABLE_SIZE + 1;
      pCurTable->used = 1;
      pCurTable->handles[resolver_handle - pCurTable->start_index] = g2_pointer;
      /* append the new node */
      if (pPrevTable) {
        pPrevTable->next_node = pCurTable;
      } else {
        g2pvt_resolver_to_NI_handle_table = pCurTable;
      }
    }
  } else {
    pCurTable->used += 1;
    pCurTable->handles[resolver_handle - pCurTable->start_index] = g2_pointer;
  }
  return 0;
}

G2pointer get_and_decache_socket_to_NI_handle(resolver_handle)
    long resolver_handle;
{
  SOCKET_TO_NI_HANDLE_TABLE *pCurTable = g2pvt_resolver_to_NI_handle_table;
  SOCKET_TO_NI_HANDLE_TABLE *pNextTable = NULL;
  G2pointer pointer = 0;

  while (pCurTable) {
    if (resolver_handle >= pCurTable->start_index &&
        resolver_handle < (pCurTable->start_index + SOCKET_TO_NI_HANDLE_TABLE_SIZE)) {
      pointer = pCurTable->handles[resolver_handle - pCurTable->start_index];
      pCurTable->handles[resolver_handle - pCurTable->start_index] = 0;
      if (pointer != 0) {
        pCurTable->used -= 1;
      }
      break;
    }
    pCurTable = pCurTable->next_node;
  }
  return pointer;
}
