#include "cprim.h"
#include <signal.h>
#include <string.h>

#if defined(WIN32)
#  include <windows.h>
#  include "msincls.h"
#else
#  include <stdlib.h>
#  include <errno.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <netinet/tcp.h>
#  include <arpa/inet.h>
#endif

#if defined(unix)
#  include <sys/time.h> /* for timeout interrupts */
#  include <sys/signal.h>
#  include <sys/types.h>
#  ifdef __STDC__
#        include <unistd.h>
#  endif
#endif /* unix */

#include "networks.h"
#include "netevent.h"
#include "trace.h"

NETWORK_INTERFACE *g2ext_Listeners = NULL;
NETWORK_INTERFACE *g2ext_primary_listener = NULL;
NETWORK_INTERFACE *g2ext_Watchers = NULL;
NETWORK_INTERFACE *g2ext_Others = NULL;
PENDING_CONNECTION *g2ext_Pending_connections = NULL;

/* No_window is a C global which when TRUE (set by g2ext_x11_preinitialize) causes
 * the graphic routines in this module to be NOPs, to behave as if the
 * screen is dimmed, and the user never types anything.  This is the 
 * implementation of the command line's -nowindow switch.
 */
int No_window = TRUE;

extern long g2ext_cache_cpointer();
extern Gensym_Long g2ext_map_g2pointer_to_cpointer();

extern long g2pvt_tcpip_gethostname();
extern long g2pvt_tcpip_read();
extern long g2pvt_tcpip_write();
extern long g2pvt_tcpip_close();
extern long g2ext_icmp_read();
extern long g2ext_icmp_write();

extern long g2ext_udp_close();

extern long g2pvt_tcpip_listen();
extern long g2pvt_tcpip_accept();
extern long g2pvt_tcpip_connect();
extern long g2pvt_tcpip_set_nodelay();

extern void g2pvt_notify_now_listening();

extern long cc_accept_license_option_query();
extern long cc_license_close_listener();

extern int g2ext_network_io_trace_p;

int g2ext_max_number_of_sockets = 0;
TLS int g2ext_socket_is_connected;
TLS long  g2pvt_resolver_handle = 0;
TLS char* g2pvt_resolver_hostent;
extern int cache_socket_to_NI_handle(long resolver_handle, G2pointer g2_pointer);
extern G2pointer get_and_decache_socket_to_NI_handle(long resolver_handle);

int g2ext_too_many_fds = FALSE;
extern void g2ext_set_too_many_fds();
extern void g2ext_unset_too_many_fds();
#define NOTICE_FD_CLOSE() if(g2ext_too_many_fds)g2ext_unset_too_many_fds()

extern void g2ext_trace_network_interface();

extern void g2ext_deallocate_socket_index(unsigned);
extern int g2ext_allocate_socket_index(unsigned /* a socket identifier */);

#if defined(_WINSOCKAPI_)
extern int g2ext_lookup_socket_index ();
#endif

#ifdef WIN32
extern void g2pvt_nt_enqueue_read_event(int sock);
extern void g2pvt_nt_enqueue_write_event(int sock);
#endif

extern long g2ext_write_string_to_console(char *str);

/*******************************************************************************
 *   INTERNAL FUNCTIONS:
 */

/* various small housekeeping functions, some part of the LISP API. */

/* see definitions in (socket-next-event.c, qio-next-event.c, nt-next-event.c) for:
 *  void ne_initialize_event_handling()
 * void ne_set_next_timer_event (milliseconds_to_go)
 * void ne_map_fd_to_handle(fd, ni_handle)
 * NETWORK_INTERFACE * ne_lookup_handle_for_fd(fd)
 * NETWORK_INTERFACE * ne_unmap_fd(fd)
 * void ne_register_active_ni(ni_handle)
 * void ne_deregister_inactive_ni(ni_handle)
 * void ne_enable_read_events(handle)
 * void ne_disable_read_events(handle)
 * void ne_enable_write_events(handle)
 * void ne_disable_write_events(handle)
 * void ne_enable_except_events(handle)
 * void ne_disable_except_events(handle)
 * int ne_close_reset_p()
 * void ne_close_socket_handle (socket_handle, reset_connection)
 **/

/*******************************************************************************
 * API FUNCTIONS:
 */


NETWORK_INTERFACE *g2pvt_get_listener(count)
long count;
{
  NETWORK_INTERFACE *l;
  int i = 0;

  l = g2ext_Listeners;

  while (l && (i++ != count)) {
    l = l->parent_listener;
  }
  return l;
}


long ne_get_listener_handle(count)
long count;
{
  NETWORK_INTERFACE *l;

  l = g2pvt_get_listener(count);
  if (l) {
    return (ne_lookup_handle_for_fd(l->handle));
  }
  else
    return ((long) -1);
}





/* ****************************************

   function: g2ext_sys_sleep(msec)

   This function allows the process to sleep for msec milliseconds.

   ************************************************/


/*
 * jh, 7/26/94
 * By the way, in response to my 5/19/93 note above, I no longer think there is
 * much need to worry about a possible fork between Chestnut code and ours,
 * since we no longer call a Lisp sleep function anywhere, but instead call
 * either rdf's homegrown interruptible sleep function c_pause() or the
 * uninterruptible g2ext_sys_sleep() defined immediately below. */


/* 
 * jh, 8/22/97.  The "defining declarations" of the following two globals (as
 * opposed to their "extern declarations") need to be somewhere shared between
 * the foreign function library and the cprim library.
 */
long g2ext_gensym_SIGALARM_was_seen = FALSE;
int g2ext_licensing_event_flag;
int g2ext_license_socket = -1;

long g2ext_sys_sleep (msec)
    long msec;
{
#if defined(unix)
    struct timeval   timeout;

    g2ext_network_io_trace_note("Begin g2ext_sys_sleep");
    if (msec > 0) {
        long seconds = msec / 1000;
	int select_result;

        timeout.tv_sec = seconds;
        timeout.tv_usec = (long) ((msec - seconds * 1000)* 1000);
	g2ext_gensym_SIGALARM_was_seen = FALSE;
        select_result = select((int) 0, 0, 0, 0, &timeout);
	if ((select_result < 0) && (errno == EINTR || errno == EAGAIN)) {
          /* note that at most one EINTR will occur due to
           * G2's cached time invalidation mechanism, so
           * there's no point in making this a loop.
           * -ncc, 4 Aug 1997 
           */
	  if (g2ext_gensym_SIGALARM_was_seen) 
             select_result = select((int) 0, 0, 0, 0, &timeout);
	}
    }
#endif /* unix */

#if defined(WIN32)
    DWORD st;
    MSG msg;

    /* 11/15/94, mpc: Here's the scoop on sleeping: In all apps on NT
     *   we want to Sleep(). When an NT app is running under Win32s, the
     *   API call Sleep() falls thru to the API call Yield(). Since Yield() 
     *   ONLY DOES SO IF THE MESSAGE QUEUE IS EMPTY, it cannot be relied on 
     *   to do anything in a windowed app. Therefore, we use the same method 
     *   as under Windows 3.1, set a timer and give up control untili the 
     *   timer message comes back.
     *   Since a Console App running under Win32s is somewhat of an anomaly,
     *   combined with the fact we have no message queue which to send a Timer
     *   or to block a Yield(), it is best to call Sleep() in a Win32 console
     *   app.
     */
    g2ext_network_io_trace_note("Begin g2ext_sys_sleep");
    if (WIN32_IS_WIN32S && !ne_use_sck) {
      /* SetTimer(WindowAppHwnd, 1, msec, NULL);
	 WaitMessage();
	 */
      for( st = GetTickCount() + msec; st > GetTickCount(); )
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
	  /* If we are G2, then we may want to do some other stuff here.
	   * such as translating menu accelerators.  A bug egg. */
	  TranslateMessage(&msg);
	  DispatchMessage(&msg);
	}
    } else {
      Sleep(msec);
    }
#endif /* Win32 */

   g2ext_network_io_trace_note("End g2ext_sys_sleep");
   return 0L;
}

long g2ext_gensym_strpos(buffer, the_char)
char *buffer;
char the_char;
{
  int index;
  
  index = 0;
  while (buffer[index] != the_char) 
    index++;
  
  return(index);
}


void g2ext_get_next_token(buffer, buffer_length, string, current_string_position)
char *buffer, *string;
long *buffer_length;
long *current_string_position;
{
  long buffer_index, string_index, string_length;

  string_index = *current_string_position;
  string_length = strlen(string);
  buffer_index = 0;

  while ((buffer_index < BUFFER_LEN) && (string_index < string_length) &&
	 (string[string_index] != ':'))  {
    buffer[buffer_index++] = string[string_index++];
  }

  buffer[buffer_index] = '\0';

  *buffer_length = buffer_index;
  *current_string_position = string_index+1;

/* add 1 to current_string_position to account for the skipped ':' character */

}



long g2pvt_initialize_network_interface(network_type, connection_handle, network_pathname, interface_status, secure_p)
    long network_type;
    long connection_handle;
    char* network_pathname;
    long interface_status;
    int secure_p;
{
  NETWORK_INTERFACE *network_interface_ptr;
  G2pointer cached_g2_pointer;
  char *p;
  int status;

  if ((network_type != TCP_IP) && (network_type != ICMP) &&
      (network_type != UDP) && (network_type != WATCH)) {
    printf ("\nnetworks.c -- Unrecognized network type in g2pvt_initialize_network_interface 2nd.\n");
    return (ICP_FAIL);
  }
  if ((network_interface_ptr = (NETWORK_INTERFACE *) malloc(sizeof(NETWORK_INTERFACE))) == NULL) {
    printf ("\nnetworks.c -- Out of memory in g2pvt_initialize_network_interface 1st.\n");
    return (ICP_FAIL);
  }

  if ((p = (char *) malloc(strlen(network_pathname)+1)) == NULL) {
    free(network_interface_ptr);
    printf ("\nnetworks.c -- Out of memory in g2pvt_initialize_network_interface 2nd.\n");
    return (ICP_FAIL);
  }
  strcpy(p,network_pathname);
  network_interface_ptr->nw_pathname = p;
  network_interface_ptr->nw_raw = NULL; /* this will be filled in by ping hosts, if necessary, later.*/

  network_interface_ptr->protocol_id = network_type;
  network_interface_ptr->connected_p = (interface_status == ACTIVE_INTERFACE_STATUS ||
					interface_status == DISPLAY_INTERFACE_STATUS);
  network_interface_ptr->listener_p = interface_status == LISTEN_INTERFACE_STATUS;
  network_interface_ptr->watch_p = interface_status == WATCH_INTERFACE_STATUS;
  network_interface_ptr->watch_for_writing_p = FALSE;
  network_interface_ptr->display_event_interface_p = interface_status == DISPLAY_INTERFACE_STATUS;
  network_interface_ptr->icmp_p = interface_status == ICMP_INTERFACE_STATUS;
  network_interface_ptr->secure_connection_requested = secure_p;
  network_interface_ptr->ssl_pending_p = 0;
  network_interface_ptr->ssl = NULL;

  status = (connection_handle < 0)? connection_handle : errno;
  network_interface_ptr->last_status = status;
  network_interface_ptr->connect_status = status;
  network_interface_ptr->debug_status = 0;
  network_interface_ptr->handle = connection_handle;
  if (connection_handle < 0) {
    network_interface_ptr->socket_index = -1;
    network_interface_ptr->read_function = NULL;
    network_interface_ptr->write_function = NULL;
    network_interface_ptr->close_function = NULL;
  } else {
# if defined(_WINSOCKAPI_)
    network_interface_ptr->socket_index = g2ext_lookup_socket_index(connection_handle);
# else
    network_interface_ptr->socket_index = connection_handle;
# endif

    switch (network_type) {
    case UDP:  /* UDP sockets are used only for licensing, when counting # of G2 processes. */ 
      network_interface_ptr->read_function = NULL;
      network_interface_ptr->write_function = NULL;
      network_interface_ptr->close_function = g2ext_udp_close;
      break;
    case WATCH:
      network_interface_ptr->read_function = NULL;
      network_interface_ptr->write_function = NULL;
      network_interface_ptr->close_function = NULL;
      break;
    case TCP_IP:
      network_interface_ptr->read_function = 
	(network_interface_ptr->listener_p) ? g2pvt_tcpip_accept : g2pvt_tcpip_read;
      network_interface_ptr->write_function = g2pvt_tcpip_write;
      network_interface_ptr->close_function = g2pvt_tcpip_close;
      break;
    case ICMP:
      network_interface_ptr->read_function = g2ext_icmp_read;
      network_interface_ptr->write_function = g2ext_icmp_write;
      network_interface_ptr->close_function = g2pvt_tcpip_close;
      break;
    }
  }

  if (network_interface_ptr->listener_p) {
    network_interface_ptr->parent_listener = g2ext_Listeners;
    g2ext_Listeners = network_interface_ptr;
  } else if (network_interface_ptr->watch_p) {
    network_interface_ptr->parent_listener = g2ext_Watchers;
    g2ext_Watchers = network_interface_ptr;
  } else {
    network_interface_ptr->parent_listener = g2ext_Others;
    g2ext_Others = network_interface_ptr;
  }

  cached_g2_pointer = g2ext_cache_cpointer((long) network_interface_ptr);
  network_interface_ptr->g2_pointer_handle = cached_g2_pointer;

  if (g2pvt_resolver_handle) {
    network_interface_ptr->resolver_hostent = g2pvt_resolver_hostent;
    network_interface_ptr->resolver_handle = g2pvt_resolver_handle;
    cache_socket_to_NI_handle(g2pvt_resolver_handle, cached_g2_pointer);
    g2pvt_resolver_handle = 0;
  } else {
    network_interface_ptr->resolver_hostent = NULL;
    network_interface_ptr->resolver_handle = NULL;
  }

  if (connection_handle >= 0) {
    ne_initialize_network_interface(network_interface_ptr);
    ne_map_fd_to_handle(connection_handle, cached_g2_pointer);
    ne_register_active_ni(cached_g2_pointer);
  }

  g2ext_trace_network_interface("Opening",cached_g2_pointer);

  return cached_g2_pointer;    
}

long g2ext_udp_close(sck)
  int sck;
{
#ifdef unix
  close(sck);
#endif
  return 0;
}


long g2ext_network_listener_count()
{
  NETWORK_INTERFACE *l;
  long count = 0;

  l = g2ext_Listeners;

  while (l) {
    ++count;
    l = l->parent_listener;
  }
  return count;
}

static void remove_from_interface_list(netptr,interface_list)
  NETWORK_INTERFACE *netptr,**interface_list;
{
  if (*interface_list == netptr)
    *interface_list = netptr->parent_listener;
  else if (*interface_list != NULL) {
    NETWORK_INTERFACE *prev = *interface_list;
    NETWORK_INTERFACE *current = prev->parent_listener;
    for(;current != NULL;prev=current,current=current->parent_listener)
      if (netptr == current) {
	prev->parent_listener = netptr->parent_listener;
	break;
      }
  }
}

long g2ext_network_close(handle)
long handle;
{
  long ret = 0;

  NETWORK_INTERFACE *netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) handle);
  if (!netptr) return (ICP_FAIL);
  g2ext_network_io_trace_note_dd("g2ext_network_close  Handle: %d, fd: %d",handle,netptr->handle);

  if (netptr->watch_p) 
    remove_from_interface_list(netptr, &g2ext_Watchers);
  else {
    if (netptr->listener_p) 
      remove_from_interface_list(netptr, &g2ext_Listeners);
    else {
      remove_from_interface_list(netptr, &g2ext_Others);
      g2ext_socket_is_connected = netptr->connected_p && netptr->connect_status == 0;
    }
    errno = 0;

    if(netptr->ssl) {		/* Attempt to perform the SSL shutdown first. */
      g2pvt_ssl_close(netptr->ssl);
      netptr->ssl = NULL;
    }

    if (netptr->close_function != NULL)
      ret = (*netptr->close_function)((long) netptr->handle);
    if (ret == -1) 
	g2ext_network_io_trace_note_dd("errno for last close on handle %d was %d",netptr->handle,errno);
    if (netptr->nw_pathname != NULL)
      free(netptr->nw_pathname);
    if (netptr->nw_raw != NULL)
      free(netptr->nw_raw);
    if (netptr->resolver_hostent != NULL)
      free(netptr->resolver_hostent);
    if (netptr->resolver_handle) {
#if defined(_WINSOCKAPI_)
      WSACancelAsyncRequest((HANDLE)netptr->resolver_handle);
#endif
      get_and_decache_socket_to_NI_handle(netptr->resolver_handle);
    }

  }
  g2ext_unset_too_many_fds();

  if (netptr->handle >= 0) {
    ne_deregister_inactive_ni(handle);
    ne_unmap_fd(netptr->handle);
# if defined(_WINSOCKAPI_)
    g2ext_deallocate_socket_index(netptr->handle);
# endif
  }

  free(netptr);
  g2ext_decache_g2pointer((long) handle);

  return ret;
}

int g2ext_secure_socket_p (handle)
  long handle;
{
  NETWORK_INTERFACE *netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) handle);
  if (!netptr) return (ICP_FAIL);
  /* note: listener sockets do not have a ssl structure */
  return (netptr->ssl != NULL || netptr->secure_connection_requested);
}


static void sprint_network_connection(op, initial_buffer, l)
  char *op;
  char *initial_buffer;
  NETWORK_INTERFACE *l;
{
  char *buffer = initial_buffer;
  sprintf(buffer,"%s%s%d, %s%s%s connected=%d cstatus=%d status=%d debug=%d handle=%d index=%d ",
	  op?op:"", op?":  ":"", (int) (l->g2_pointer_handle),
	  (l->listener_p)?"Listen ":(l->watch_p)?"Watch ":
	  (l->display_event_interface_p)?"Display ":"",
	  (l->protocol_id==UDP)?"UDP ":(l->protocol_id==TCP_IP)?"":
	  (l->protocol_id==WATCH)?"WATCH ":"Unknown ",
	  l->nw_pathname,
	  l->connected_p, l->connect_status, l->last_status, l->debug_status,
	  (int) l->handle, (int) l->socket_index);
  buffer += strlen(buffer);
  ne_sprint_events(buffer,l);
  return;
}

void g2ext_trace_network_interface(op,handle)
    char *op;
    long handle;
{
  NETWORK_INTERFACE *netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) handle);
  if (netptr && g2ext_network_io_trace_p) {
    char buffer[200];
    sprint_network_connection(op, buffer, netptr);
    g2ext_network_io_trace_note(buffer);
  }
}

static void print_network_connections(l)
  NETWORK_INTERFACE *l;
{
  char buffer[200];
  for (;l;l=l->parent_listener) {
    sprint_network_connection(NULL,buffer,l);
    printf("%s\n",buffer);
  }
}

void g2ext_print_network_connections()
{
  print_network_connections(g2ext_Watchers);
  print_network_connections(g2ext_Listeners);
  print_network_connections(g2ext_Others);
}

void g2ext_set_too_many_fds()
{
  NETWORK_INTERFACE *l;
  if (!g2ext_too_many_fds) {
    for (l=g2ext_Listeners; l!= NULL; l = l->parent_listener)
      ne_disable_accept_events(ne_lookup_handle_for_fd(l->handle));
    g2ext_too_many_fds = TRUE;
  }
}

void g2ext_unset_too_many_fds()
{
  NETWORK_INTERFACE *l;
  if (g2ext_too_many_fds) {
    for (l=g2ext_Listeners; l!= NULL; l = l->parent_listener)
      ne_enable_accept_events(ne_lookup_handle_for_fd(l->handle));
    g2ext_too_many_fds = FALSE;
  }
}

void g2ext_network_watch_fd(fd)
  int fd;
{
  NETWORK_INTERFACE *l = g2ext_Watchers;

  while (l && fd != l->handle)
    l = l->parent_listener;
  if (!l) {
    errno = 0;
# if defined(_WINSOCKAPI_)
    g2ext_allocate_socket_index(fd);
# endif
    g2pvt_initialize_network_interface(WATCH,
				       fd,
				       "watch",
				       WATCH_INTERFACE_STATUS,
				       0);
  }
}

void g2ext_network_unwatch_fd(fd)
  int fd;
{
  NETWORK_INTERFACE *l = g2ext_Watchers;

  while (l && fd != l->handle)
    l = l->parent_listener;
  if (l && l->watch_p)
    g2ext_network_close(ne_lookup_handle_for_fd(fd));
}

void g2ext_network_watch_fd_for_writing(fd)
  int fd;
{
  NETWORK_INTERFACE *l = g2ext_Watchers;

  while (l && fd != l->handle)
    l = l->parent_listener;
  if (l && l->watch_p) {
    l->watch_for_writing_p = TRUE;
    ne_enable_watch_events(ne_lookup_handle_for_fd(fd));
  }
}

void g2ext_network_unwatch_fd_for_writing(fd)
  int fd;
{
  NETWORK_INTERFACE *l = g2ext_Watchers;

  while (l && fd != l->handle)
    l = l->parent_listener;
  if (l && l->watch_p) {
    l->watch_for_writing_p = FALSE;
    ne_enable_watch_events(ne_lookup_handle_for_fd(fd));
  }
}

long g2ext_get_network_listener(count,buffer,size)
long count;
char *buffer;
long size;
{
  NETWORK_INTERFACE *lstnr;
  int len = 0;

  if (size < 1) return -1;

  buffer[0] = '\0';

  lstnr = g2pvt_get_listener(count);

  if (lstnr) {
    len = strlen(lstnr->nw_pathname);
    if (len < size) {
      strncpy(buffer, lstnr->nw_pathname, len);
      buffer[len] = '\0';
      return len;
    }
  }
  return -1;
}


/* Fills in the given buffer with JUST THE PORT portion of the listener
 * string.  We assume that the listener string has three components,
 * separated by colons, with the port being the third component.  See also
 * extract-network-address in Lisp.  -jv, 3/21/05
 *
 * yduJ, 6/8/06: change from using listener count to requiring caller to pass in
 * the listener they want destructured.
 */
long g2pvt_network_listener_port (listener, buffer, size)
NETWORK_INTERFACE *listener;
char *buffer;
long size;
{
  char new_buf[BUFFER_LEN];
  char *seps = ":";
  char *token;
  long len;

  if (size < 1 || listener == NULL) return -1;

  buffer[0] = '\0';

  strcpy (new_buf, listener->nw_pathname);

  token = strtok(new_buf, seps);
  if (token == NULL) {
    return -1;
  }
  token = strtok(NULL, seps);
  if (token == NULL) {
    return -1;
  }
  token = strtok(NULL, seps);
  if (token == NULL) {
    return -1;
  }
  len = strlen(token);
  if (len >= size) {
    return -1;
  }
  strncpy(buffer, token, len);
  buffer[len] = '\0';
  return len;
}


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION g2ext_network_get_listener_fd:       Copyright (C) 1986-2017 Gensym Corporation
:
:  This function is new in the 4.0 rev 2 release.
:
:  It searches the global list of listeners for the first listener it finds
:  that is using TCP_IP protocol.  This assumes that there is at most one
:  TCP_IP protocol listener, since it makes no provision to find any others.
:  When it locates the first (and by assumption only) TCP-IP listener, it
:  returns the file descriptor of the socket associated with that listener.
:
:  This function is used only by GSI in the 4.0 rev 2 release, therefore the
:  assumption of a single TCP_IP listener holds as can be seen by inspecting
:  the code in gsi.lisp (see establish-gsi-extension-listeners & caller etc.).
:
:  Having found the TCP_IP listener, this function returns the file descriptor
:  representing the listener socket.  If no TCP_IP listener is found, -1
:  (ICP_FAIL) is returned (an invalid file descriptor) instead. 
:
:  Arguments:        none.
:
:  Return Behavior:  Returns unix file descriptor for tcp listener, if such
:                     exists , otherwise ICP_FAIL.
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  000  18Jan96  ncc        new feature for 4.0 rev 2 point release:
:                           gsi_listener_socket function. (defined in gsi.lisp)
:.............................................................................*/


long g2ext_network_get_listener_fd()
{
  NETWORK_INTERFACE *l = g2ext_Listeners;

  while (l) {
    if (l->protocol_id == TCP_IP)
      return(l->handle);
    l = l->NEXT;
  }
  return (ICP_FAIL);
}


/* g2ext_inetwork_listen is really hideous.  It calls directly into the tcp
 * layer, without using the dispatch mechanism built into network_interface
 * structures.  It should be rationalized sometime, but I don't have time to do
 * it now.  -ncc, 20 Jun 1996
 **/


G2pointer g2pvt_tcpip_listener = -1;

long g2ext_inetwork_listen(defaults,product)
  LISTENER_DEFAULTS *defaults;
  long               product;
{
  char protocol[BUFFER_LEN];
  long tcp_handle, count = 0;
  long local_tcpip_listener;
  long highest_tcpip_listener;
  char local_hostname[BUFFER_LEN];

  tcp_handle = -1;
  if ((defaults->protocol == TCP_IP) || (defaults->protocol == ALL))  {
    local_tcpip_listener = defaults->default_tcpip_listener;
    highest_tcpip_listener = local_tcpip_listener + 
      defaults->tcpip_max_iterations;

    if (defaults->exact_tcpip_port_required)
      tcp_handle = 
	g2pvt_tcpip_listen((long) local_tcpip_listener);
    else
      while ((local_tcpip_listener < highest_tcpip_listener) &&
	     ((tcp_handle = g2pvt_tcpip_listen((long) local_tcpip_listener)) <= -1))
	++local_tcpip_listener;

    if ((tcp_handle == NOOP_CODE_ATTEMPTED) &&
        (defaults->protocol == TCP_IP)) /* Occurs if stub within    */
      return(NOOP_CODE_ATTEMPTED);      /* tcpnoop.c was called.    */

    if (tcp_handle > -1) {
      errno = 0;
      g2pvt_tcpip_gethostname ((char *) local_hostname, (long) BUFFER_LEN);
      sprintf(protocol,"TCP_IP:%s:%ld",local_hostname,local_tcpip_listener);

      if (defaults->secure_connection_requested && !g2pvt_ssl_available(1)) {
	g2ext_write_string_to_console("Warning: SSL server requested, but not available.");
	defaults->secure_connection_requested = 0;
      }

      g2pvt_tcpip_listener = g2pvt_initialize_network_interface(TCP_IP, tcp_handle, protocol, LISTEN_INTERFACE_STATUS,defaults->secure_connection_requested);

      g2pvt_tcpip_set_nodelay(tcp_handle);

    } else if (defaults->exact_tcpip_port_required) {
      /* cc_close_all_network_listeners(); */ /* this socket is not open, there are no others */
      return (ICP_FAIL);
    }
  }

  if (g2ext_Listeners)
    return (ICP_SUCCEED);  
  else
    return (ICP_FAIL);
}



/* ***********************************************************************

   Function: g2ext_network_listen()
   args: none
         OBJPORT

   modified: A - pvl, 6/4/91  added the GSI specific network arguments

   This function originally used a base default for tcpip and decnet in order
   to register the process for the associated network. TCPIP defaulted to 1111
   and DECnet defaulted to G20. If the <network>_listen() function failed the 
   number (1111 or 0) would be tried again and another <network>_listen() would
   be attempted. 

   In order to make this usable by GSI, the g2ext_network_listen() function had to be
   modified to accept a pointer to an OBJPORT structure as an argument.  If is
   argument is 0 then the above description takes place. But if something is
   there an attempt is made to connect to the network by the associated tcpip
   reference. If it fails, the above approach is adopted.

   jh, 11/13/91.  Added two additional arguments to g2ext_network_listen to handle
   cases where the user doesn't want G2 to iterate upwards looking for ICP
   sockets.  RB and AC tell me that this won't affect GSI code, since they
   call g2ext_inetwork_listen.

   paf! 17apr95.  Added an additional argument to indicate product (currently
   G2 or GSI).  The argument is used to determine default auto-incrementation 
   of port numbers and object names. It is passed along to g2ext_inetwork_listen.

   **************************************************************************/

long g2ext_network_listen(which_protocols, tcp_port,
                    exact_tcp_only_p, product, secure_p)
  long which_protocols;
  long tcp_port;
  long exact_tcp_only_p;
  long product;
  long secure_p;
{
  LISTENER_DEFAULTS *defaults;
  long rval = -1;
  int first;

  /* We make the assumption that the first listener is the main one for ICP
     connections, and so only call the notifier for it.  This is a kluge; we
     might want to address different types of listeners some day.*/

  first = (g2ext_Listeners == NULL);
  if ((defaults = (LISTENER_DEFAULTS *) malloc(sizeof(LISTENER_DEFAULTS))) == NULL) {
    printf ("\nnetworks.c -- Out of memory in g2ext_network_listen 1st.\n");
    return (ICP_FAIL);
  }

  defaults->tcpip_max_iterations = 100;
  defaults->exact_tcpip_port_required = exact_tcp_only_p;
  defaults->protocol = which_protocols;
  defaults->secure_connection_requested = secure_p;

  if (product == GSI)
    defaults->default_tcpip_listener = (tcp_port ? tcp_port : GSI_TCP_LISTENER_START);
  else
    defaults->default_tcpip_listener = (tcp_port ? tcp_port : G2_TCP_LISTENER_START);

  rval = g2ext_inetwork_listen(defaults,product);
  if (first) {
    g2ext_primary_listener = g2pvt_get_listener(0);
    if (g2ext_primary_listener) {
      g2pvt_notify_now_listening();
    }
  }
  return rval;
}


/* slated for death in 5.0 */
long g2ext_get_next_connection()
{
  PENDING_CONNECTION *p;
  long handle;

  p = g2ext_Pending_connections;

  if (p) {
    handle = p->handle;
    g2ext_Pending_connections = p->next;
    free(p);
    return (handle);
  }
  else
    return ((long) -1);
}

long g2ext_get_connection_pathname (handle, network_pathname, size)
  long handle;
  char *network_pathname;
  long size;
{
  long len;
  NETWORK_INTERFACE *netptr;

  if (size < 1) return -1;

  netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long)handle);
  if (netptr) {
    len = (long)strlen(netptr->nw_pathname);
    if (len < size) {
      strncpy(network_pathname, netptr->nw_pathname, len);
      network_pathname[len] = '\0';
      return 1;
    }
  }
  return -1;
}

long g2ext_set_connection_pathname(handle,network_pathname)
  long handle;
  char *network_pathname;
{
  NETWORK_INTERFACE *netptr
    = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long)handle);

  if (netptr) {
    free(netptr->nw_pathname);
    netptr->nw_pathname = (char *)malloc(strlen(network_pathname)+1);
    strcpy(netptr->nw_pathname,network_pathname);
    return 1;
  } else
    return -1;
}

long g2ext_set_debug_status(handle,status)
  long handle;
  long status;
{
  NETWORK_INTERFACE *netptr
    = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long)handle);

  if (netptr) {
    netptr->debug_status = status;
    return 1;
  } else
    return -1;
}

long g2ext_number_of_pending_connections()
{
  PENDING_CONNECTION *p;
  long count = 0;

  p = g2ext_Pending_connections;

  while (p) {
    ++count;
    p = p->next;
  }
  return count;
}


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION g2ext_network_get_fd_from_handle:    Copyright (C) 1986-2017 Gensym Corporation
:
:  This function wraps around all the possible flavors of network transport, 
:  and returns a unix file descriptor that corresponds to the given connection
:  handle, if and only if the given connection handle is using the tcp/ip
:  transport.  Otherwise, this function returns ICP_FAIL.
:
:  Arguments:        An ICP connection handle, a long representing a pointer to
:                     a structure of type NETWORK_INTERFACE.
:  Return Behavior:  Returns unix file descriptor for handle, if handle uses
:  		      TCP/IP, otherwise ICP_FAIL.
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  000  9Jan1996 ncc        new feature for 4.0 rev 2 point release:
:                           gsi_context_socket function. (defined in gsi.lisp)
:  001  11Jun1996 ncc       Remember to modify this to return channel id under vms
:                           and fd elsewhere.
:.............................................................................*/
long g2ext_network_get_fd_from_handle(handle)
long handle;
{
  NETWORK_INTERFACE *netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) handle);

  if (netptr)
    return netptr->handle;
  else
    return ICP_FAIL;
}

    
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION g2ext_network_accept:         Copyright (C) 1986-2017 Gensym Corporation
:
:  This function wraps around all the possible flavors of network connection
:  accept functions
:
:  Arguments:        None.
:  Return Behavior:  If connections are accepted, the number of connections
:                    accepted is returned.  If no connections are accepted,
:                    zero is returned.  Negative values are never returned.
:  Users:            G2, TW, GSI, GSPAN and Foreign Functions (the latter three
:                    through the function extension_run_loop()).  GSI-to-GSI
:                    software (internal use only) also makes use in rpcstubs.c.
:  Memory Impact:    Indirect -- Memory is allocated by the various accept
:                    functions.
:
:  Rev  Date     Author     Notes
:  001  30sep93  P. Fandel  I removed a needless timewasting check to determine
:                           if connections were pending that was called before
:                           calling g2ext_number_of_pending_connections() - which
:                           correctly returns 0 if there are none.
:                           The local accept_state should be returned if it
:                           indicates an error (negative number), however until
:                           all of the network accept flavors can be modified
:                           to return unambiguous negative numbers enabling
:                           one to differentiate between a good order shutdown
:                           or lack of any new connections from a real error,
:                           this information can not be propagated.  This fix
:                           is slated for 4.0.
:  ??? 10Apr06  yduJ        Allowed for nonblocking listener sockets so that 
:                           accept will not block, and will instead return
:                           NE_BLOCKED_VALUE
:.............................................................................*/

extern void ne_enable_read_events();

G2pointer g2ext_network_accept(l)
G2pointer l;			/* the listener on which an accept event occurred. */
{
  NETWORK_INTERFACE  *listener_ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(l);
  G2pointer  new_handle;
  NETWORK_INTERFACE  *new_ni;

  if (!listener_ni) return ICP_FAIL;

  ne_enable_read_events(l);

  errno = 0;
  new_handle = (*listener_ni->ACCEPT_FUNCTION) (listener_ni->handle);
  if (new_handle == TCPIP_ACCEPT_NONE_PENDING) {
    g2ext_network_io_trace_note_d("g2ext_network_accept  listener %d: no pending connections", listener_ni->handle);
    return NE_BLOCKED_VALUE;
  } else if (new_handle < 0) {
    listener_ni->last_status = (new_handle==-1)?errno:new_handle;
    g2ext_network_io_trace_note_d("g2ext_network_accept  error code: %d", listener_ni->last_status);
    return new_handle;
  }

  new_ni  = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) new_handle);
  new_ni->connected_p = 1;	/* we accepted, it's connected now. */
  g2ext_network_io_trace_note_dd("g2ext_network_accept  Handle: %d, fd: %d", new_handle, new_ni->handle);

  /* Wrap the socket in SSL, if requested. */
  if(listener_ni->secure_connection_requested && new_ni->protocol_id == TCP_IP)
    new_ni->ssl_pending_p = 1;

  return new_handle;
} 

NETWORK_INTERFACE *ne_current_network_interface = 0;

long g2ext_network_read(handle,buffer,start,end)
long handle,start,end;
char *buffer;
{
  long read_result;
  NETWORK_INTERFACE *netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) handle);
  if (!netptr) return ICP_FAIL;
  ne_current_network_interface = netptr;

  network_io_trace_begin_read(handle,netptr->handle,end-start);
  errno = 0;
  read_result = (*netptr->read_function)((long)   netptr->handle,
					 buffer+start,
					 end-start);
  netptr->last_status = errno;
  network_io_trace_end_read(handle,netptr->handle,read_result,buffer+start);
  if (0!=errno) 
    g2ext_network_io_trace_note_dd("errno for last read on handle %d was %d",netptr->handle,netptr->last_status);

  return read_result;
}

long g2ext_network_write(handle,buffer,offset,length)
long handle,offset,length;
char *buffer;
{
  long write_result;
  NETWORK_INTERFACE *netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) handle);
  if (!netptr) return ICP_FAIL;
  ne_current_network_interface = netptr;

  buffer = &buffer[offset];

  network_io_trace_begin_write(handle,netptr->handle,length);
  errno = 0;
  write_result = (*netptr->write_function)((long)   netptr->handle,
					   (char *) buffer,
					   (long)   length);
  netptr->last_status = errno;
  network_io_trace_end_write(handle,netptr->handle,write_result,buffer);
  if (0!=errno) 
    g2ext_network_io_trace_note_dd("errno for last write on handle %d was %d",netptr->handle,netptr->last_status);

  return write_result;
}


TLS int g2ext_no_connect_event_pending;

/*  g2ext_network_connect
 * 
 *  Handles opening a network connection and 
 *  establishes a buffer for network io.
 *
 *  Returns the value of the connection_handle if successful,
 *  and a -1 if the connection failed. 
 *
 *  yduJ, May 2006, added positional arguments to specify connection rather than
 *  decoding a string.
 */

long g2ext_network_connect(network_pathname, host, port, secure_p)
char *network_pathname;
char *host;
char *port;
int secure_p;
{
  long network_type;
  long connection_handle, connection_state = -1;
  NETWORK_INTERFACE *ni;
  long numeric_port;

  /* We only support TCP these days.  Check that's what was requested. */
  if (strncmp(network_pathname, "TCP_IP", 6) != 0)
    return -1;
  else network_type = TCP_IP;

  g2ext_no_connect_event_pending = FALSE;
  errno = 0;

  numeric_port = atoi(port);
  connection_state = g2pvt_tcpip_connect(host, numeric_port);

  if (connection_state < 0 || errno != 0) 
    g2ext_no_connect_event_pending = TRUE;

  if (secure_p && !g2pvt_ssl_available(1)) {
    g2ext_write_string_to_console("Warning: SSL connection requested, but not available.");
    secure_p = 0;
  }

  connection_handle = 
    g2pvt_initialize_network_interface((long)network_type,
				 (long)connection_state,
				 (char *)network_pathname,
				 (connection_state < 0)?
				 ERROR_INTERFACE_STATUS:
				 (g2ext_no_connect_event_pending?
				  ACTIVE_INTERFACE_STATUS:
				  CONNECT_INTERFACE_STATUS),
				 secure_p);
  g2ext_network_io_trace_note_ddd("g2ext_network_connect  Handle: %d, fd: %d, Connect_event_pending: %d",
			    connection_handle,connection_state,!g2ext_no_connect_event_pending);

  ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(connection_handle);
  ni->port = numeric_port; /* for reconnect in the future */

  /* Wrap the socket in SSL, if requested. */
  if(secure_p && ni->protocol_id == TCP_IP && connection_state>0)
    ni->ssl = g2pvt_ssl_connect(ni->handle);

  return connection_handle;
}

long ne_connected_p(fd_handle)
long fd_handle;
{
  NETWORK_INTERFACE *netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) fd_handle);

  if (netptr) 
    return netptr->connected_p || netptr->handle < 0;
  else
    return 0;
}

void ne_set_ni_last_error(ni_handle,error_code)
  G2pointer ni_handle;
  int error_code;
{
  NETWORK_INTERFACE *ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(ni_handle);
  ni->last_status = error_code;
}

long ne_last_error_code(fd_handle)
long fd_handle;
{
  NETWORK_INTERFACE *netptr = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer((long) fd_handle);

  if (netptr) {
    return (netptr->handle < 0) ? netptr->handle : netptr->last_status;
  } else
    return 0;
}

/*
 * cc_close_all_network_listeners()
 */

/* 
 * jh, 8/20/93. Previously, we were relying on the operating system to clean up
 * after a listening process exited.  This will not work in Lucid development,
 * since we are allowed to re-launch a G2 image there.
 */

/* Now, listeners are individually closed, using close-and-disconnect-icp-socket-handle */


long g2ext_visible_window_is_present()
{
  return !No_window;
}

long g2ext_window_is_present()
{
#if defined(WIN32)
  return ne_use_sck;
#else
  return !No_window;
#endif
}


/*
 * Enable or disable secure connections. Only call this once/process.
 */
long g2ext_set_secure_icp(char *certificate)
{
  int rc = 0;

  rc = g2pvt_ssl_initialize(certificate);
  if(rc == 0)
    g2pvt_ssl_destroy();

  return rc;
}

/*
 * Acquire network address (typically IP address) for this machine.
 *
 * There can be more than one for a machine, so we access via indexing.  Returns
 * -1 if the index is out of bounds, or the length of the string if it was
 * found, filling in the provided buffer.  Initializes upon first call.
 */

static char **network_addresses = NULL;
static int number_of_network_addresses = 0;

extern int g2pvt_tcpip_get_addresses();

static void free_net_addresses()
{
  int i;
  if (network_addresses) {
    for (i = 0; i < number_of_network_addresses ; i++)
      free(network_addresses[i]);
    free (network_addresses);
    network_addresses = NULL;
  }
}

static void initialize_net_addresses()
{
  char **temp_addresses;
  int i,j = 0;
#if !defined(WIN32)
  struct in_addr *paddr;
#endif
  free_net_addresses();

  number_of_network_addresses = g2pvt_tcpip_get_addresses(&temp_addresses);
  network_addresses =
    (char **)malloc((number_of_network_addresses + 1) * sizeof(char*));

#if defined(WIN32)
  for (i = 0; i < number_of_network_addresses ; i++) {
    network_addresses[j] = (char*)malloc(4);
    memcpy(network_addresses[j], temp_addresses[i], 4);
    j++;
  }
#else
  paddr = (struct in_addr *) temp_addresses;
  for (i = 0; i < number_of_network_addresses ; i++) {
    unsigned char *temp = (unsigned char *) &paddr[i];
    /* Explicitly check for 127.0.0.0/8, which we get from Linux.  
       Don't store it. */
    if (temp[0] != 127) {
      network_addresses[j] = (char*)malloc(4);
      memcpy(network_addresses[j], temp, 4);
      j++;
    }
  }
#endif

  number_of_network_addresses = j; /* Reset if necessary */
  network_addresses[j] = NULL;
}

extern int g2pvt_snprintf();

long g2ext_nth_network_address (n,buffer,buflen)
long n,buflen;
char *buffer;
{
  /* Initialize upon first request -- we may have had a dynamic network address
     added or removed.  Make it consistent, though; caller will loop calling
     this until there are no more, and won't make random stabs.  So don't reinit
     every time. */
  if (n == 0)
    initialize_net_addresses();
  if (n >= number_of_network_addresses)
    return -1;
  return g2pvt_snprintf(buffer, buflen, "%u.%u.%u.%u", (unsigned char)network_addresses[n][0], (unsigned char)network_addresses[n][1], (unsigned char)network_addresses[n][2], (unsigned char)network_addresses[n][3]);
}
  
    

/*
 * Ensure that G2 will attempt another read on given socket.
 */
void g2pvt_enqueue_read_event(int sock)
{
#ifdef WIN32
  g2pvt_nt_enqueue_read_event(sock);
#endif
  /* TODO for sckevent connections.
  if(ne_use_sck)
    g2pvt_sck_enqueue_read_event(sock); */
}

void g2pvt_enqueue_write_event(int sock)
{
#ifdef WIN32
  g2pvt_nt_enqueue_write_event(sock);
#endif
  /* TODO for sckevent connections.
  if(ne_use_sck)
    g2pvt_sck_enqueue_write_event(sock); */
}

/* MQTT stubs */

long g2ext_mqtt_log_topic_data(G2pointer handle, int flag)
{
  return flag;
}

long g2ext_mqtt_log_packet_data(G2pointer handle, int flag)
{
  return flag;
}
