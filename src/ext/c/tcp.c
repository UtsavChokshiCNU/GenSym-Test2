/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      tcp.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   John Hodgkinson, Nick Caruso
 +
 + Description: This module contains the tcp network functions.
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
 +   Section:      FUNCTION GROUP - Utility Functions
 +      ioctl()                            1111111 Conditionally Defined
 +      ucx_is_running()                   1111111 Conditionally Defined
 +
 +   Section:      FUNCTION GROUP - Partial IO Functions
 +      g2ext_lookup_socket_index()                       1111111
 +
 +   Section:      FUNCTION GROUP - Socket Functions
 +      g2pvt_tcpip_accept()                     0000000
 +      g2ext_set_tcp_connect_retry()            0000000
 +      g2pvt_tcpip_connect()                    0000000 Mixed Ifdefs
 +      g2pvt_tcpip_listen()                     0000000 Mixed Ifdefs
 +      g2pvt_tcpip_read()                       0000000 Mixed Ifdefs
 +      g2pvt_tcpip_write()                      0000000 Mixed Ifdefs
 +      g2pvt_tcpip_close()                      0000000
 *      g2pvt_tcpip_set_nodelay                  0000000
 +
 +   Section:      FUNCTION GROUP - Socket Functions
 +      g2ext_tcpip_accept_internals()           0000000
 +      g2pvt_tcpip_accept()                     0000000 Conditionally Defined
 +      g2pvt_tcpip_connect()                    0000000 Conditionally Defined
 +
 +   Section:      FUNCTION GROUP - Host Lookup Functions
 +      g2pvt_tcpip_gethostname()                0000000 Mixed Ifdefs
 +      g2pvt_tcpip_get_addresses()              0000000
 +      g2ext_get_peer_address_string()          0000000
 +      g2ext_get_peer_hostname()                0000000
 +
 + External Interface:
 +      long     g2pvt_tcpip_gethostname(buffer, maximum_length)
 +                 Writes the name of the node running this process into
 +                 buffer.
 +
 +      long     g2pvt_tcpip_accept(socket)
 +                 Accepts a pending TCP/IP connection on a listener if any.
 +                 Returns 0 if none pending.
 +                         negative number if any error occured 
 +                         pointer to a network interface associated with the
 *                         newly created socket
 *
 +      long     g2ext_tcpip_accept_internals(socket)
 +                 Accepts a pending TCP/IP connection on a listener if any.
 +                 Returns 0 if none pending.
 +                         negative number if any error occured 
 +                         positive number is a new socket for an accepted 
 +                         connection.
 +
 +      long     g2ext_set_tcp_connect_retry(new_retry_interval_in_ms)
 +                 Changes the interval that subsequent calls to
 +                 g2pvt_tcpip_connect() will wait for a connection.
 +                 Returns 1 for successful set.
 +
 +      long     g2pvt_tcpip_connect(host_name, port_number)
 +                 Attempts to connect to host, given host and display. 
 +                 Returns negative number if connection fails,
 +                         nonnegative socket if connection is successful.
 +
 +      long     g2pvt_tcpip_listen(port_number)
 +                 Sets up a pending TCP/IP connection at the given port number.
 +                 Returns negative number if setup fails,
 +                         nonnegative number if the setup is successful.
 +
 +      long     g2pvt_tcpip_read(socket, buffer, count)
 +                 Read from a TCP/IP socket at most count chars into buffer.
 +                 Returns 0 if no pending data,
 +                        -1 if any error occured during the read,
 +                         positive number is count of bytes placed into buffer
 +
 +      long     g2pvt_tcpip_write(socket, buffer, count)
 +                 Write to a TCP/IP socket at most count chars into buffer.
 +                 Returns 0 if the write would block,
 +                        -1 if any error occured during the write,
 +                         positive number is count of bytes written.
 +
 +      long     g2pvt_tcpip_close(socket)
 +                 Shut down and close a TCP socket, aborting all pending
 +                 operations.
 +                 Returns 0 if no error,
 +                        -1 if any error occurred.
 +
 +      long     g2pvt_tcpip_listen(port_number)
 +                 Establishes a listener at given port number which will then
 +                 notify the WndProc of incoming connections asynchronously.
 +                 Returns negative number if setup fails,
 +                         nonnegative number if the setup is successful.
 +
 +      long     g2pvt_tcpip_accept(listener_socket)
 +                 Accept a pending tcp/ip connection.
 +                 Returns a new socket fd for an accepted connection.
 +                         negative number if any error occured
 +
 +      long     g2pvt_tcpip_connect(host, port)
 +                 Attempts to connect to server, given host and display
 +                 Returns nonnegative socket if connection is successful
 +                         negative number if connection fails,
 +                         code if connection is in progress
 *      long     g2pvt_tcpip_set_nodelay(listener_socket)
 *                 Sets the socket to be nonblocking.
 +                 Returns 0 if no error,
 +                        -1 if any error occurred.
 +
 + Dependencies:
 +      This file has no external dependencies.
 +
 + Notes:
 +      mpc 7-29-93:  ifdef this entire file out if this is Windows 3.1.
 +   The PC TW fork of tcp.c is so alien that it would be beyond
 +   reasonable to incorporate it here. When Windows Sockets is proven to 
 +   work under Windows 3.1 then we can use that, but for now we'll happily 
 +   kludge away.
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +   3/07/96, mpc: Created new section, Socket Functions, for the
 +                asynchronous Winsock network functions.
 +   7/03/95, mpc: Major structural reorganization to improve code legibility
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
 %      jh, 3/25/93.  There appear to be two reasons we need to include 
 %   cprim.h: first, the RS6000 fails to #define the unix feature.
 %   -----
 %      jh, 7/8/94.  Another reason: g2ext_g2_gethostname() is externed there.
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#if defined(WIN32)
#   include <winsock2.h>
#   include <io.h>
#   include "msincls.h"
#endif

#include <errno.h>
#include <signal.h>

#include "cprim.h"
#include "networks.h"
#include "netevent.h"

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>
#include <sys/types.h>

#if !defined(WIN32)
#  include <sys/ioctl.h>
#  include <sys/socket.h>
#  include <net/if.h>
#  include <netinet/in.h>
#  include <netinet/tcp.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#  include <netdb.h>
#endif

#if defined(_IBMR2)
#   include <sys/select.h>
#endif



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section. 
 %
 % Notes:
 %    jh, 1/16/93.  TCPIP_CONNECT_SELECT_TIMEOUT_DECREMENT should be the same as
 %  the rate at which we expect to get SIGALRM signals.  This is currently equal
 %  to the Lisp variable milliseconds-of-graininess from the PRIMITIVES module.
 %  For further details, see the 1/14/94 note below.
 %   -----
 % Modifications:
 %       jh per jra, 3/29/95.  Changed NSOCKETS to depend on FD_SETSIZE rather
 %   than be a hard-wired 128.  This still could result in an unacceptably low
 %   ceiling on the number of open sockets on some obsolete platforms, but this
 %   modification makes some progress.
 %   -----
 %       mpc 4/30/93.  Added these socket error constant defines to map bsd 
 %   error names to win nt names. Watch future releases of winsock.h and 
 %   errno.h because perhaps  Microsoft will do this for us. (right...)
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#define TCPIP_CONNECT_SELECT_TIMEOUT_DECREMENT   50

#define INET_ADDR_FAILURE         -1
#define CONNECT_FAILURE           -1
#define LEAST_ACTUAL_SOCKET_VALUE  0

#define TCPIP_LISTEN_FAILURE -1

#define BIND_FAILURE           -1
#define SYSTEM_LISTEN_FAILURE  -1
#define MAX_LISTENER_BACKLOG    5

#define LEAST_SELECT_SUCCESS_VALUE  0
#define SET_NON_BLOCKING_FAILURE   -1

#define TCPIP_CONNECT_MAX_SELECT_RETRIES         10

#define TCPIP_TEMPORARY_WRITE_BUFFER_SIZE 4096
#define TCPIP_WRITE_FAILURE -1

#define SOCKET_OUT_OF_BOUNDS           -1
#define NO_MORE_PARTIAL_WRITE_ENTRIES -10

/*--------------- WIN32 -------------*/
#if defined(_WINSOCKAPI_)
#   undef EINTR
#   undef EBADF
#   undef EINVAL
#   undef EWOULDBLOCK
#   undef EINPROGRESS
#   undef EISCONN

#   define EWOULDBLOCK	WSAEWOULDBLOCK
#   define EINPROGRESS	WSAEINPROGRESS
#   define EISCONN	WSAEISCONN
#   define EINTR	WSAEINTR
#   define EBADF	WSAEBADF
#   define EINVAL	WSAEINVAL
#   define NO_FLAGS_SET	0	/* Used with send()/recv() */
#   define TCP_READ(fd,buf,len)  recv(fd,buf,len,NO_FLAGS_SET)
#   define TCP_PEEK(fd,buf,len)  recv(fd,buf,len,MSG_PEEK)
#   define TCP_WRITE(fd,buf,len) send(fd,buf,len,NO_FLAGS_SET)
#   define TCP_ERRNO WSAGetLastError()
#   define TCPCLOSE_INTERNAL(socket)  closesocket(socket) /* XXX */
#   define TCP_SET_NON_BLOCKING(socket, nonblocking_flag) \
        ioctlsocket((int)(socket), FIONBIO, (unsigned long *) &(nonblocking_flag))
#else
/*--------------- UNIX --------------*/
#   define TCP_READ(fd,buf,len)  read(fd,buf,len)             /* Why not recv() here? */
#   define TCP_PEEK(fd,buf,len)  recv(fd,buf,len,MSG_PEEK)
#   define TCP_WRITE(fd,buf,len) write(fd,buf,len)
#   define TCP_ERRNO errno
#   define TCPCLOSE_INTERNAL(socket)  close(socket)
#   if defined(Platform_Solaris)
#      define TCP_SET_NON_BLOCKING(socket, nonblocking_flag) \
             fcntl((socket), F_SETFL, O_NDELAY | fcntl ((socket), F_GETFL, 0))
#   elif defined(Platform_Linux)
#      define TCP_SET_NON_BLOCKING(socket, nonblocking_flag) \
             fcntl((socket), F_SETFL, O_NONBLOCK | fcntl ((socket), F_GETFL, 0))
#   else
#      define TCP_SET_NON_BLOCKING(socket, nonblocking_flag) \
             ioctl((socket), FIONBIO, (char *) &(nonblocking_flag))
#   endif
#endif

#define NOTICE_FD_CLOSE() if(g2ext_too_many_fds)g2ext_unset_too_many_fds()
#define TCPCLOSE(socket,do_shutdown) \
 if(do_shutdown)shutdown(socket,1); \
 TCPCLOSE_INTERNAL(socket); \
 NOTICE_FD_CLOSE(); \
 g2int_close_fd_callback(socket)



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %     Does arg_struct serve any purpose?
 %   -----
 %     Each entry in the lookup table socktable is a socket identifier. Its
 %   position in the table corresponds to where its data is in the
 %   in_bufpos/out_bufpos arrays.
 %   -----
 %     jh, 10/28/94.  See if colliding retries are the reason that the Multinet
 %   implementation of TCP (oddly, not the UCX implementation) leaks on VMS.
 %   The switch g2pvt_tcpip_connect_dont_retry will only be set when I am debugging
 %   this problem.  Eventually. we may have to distinguish between these two
 %   implementations at runtime if UCX needs to retry.
 % Modifications:
 %
 %     jh, 6/23/94.  Made TCPIP_CONNECT_RETRY_INTERVAL_IN_MS into a global
 %   variable, g2pvt_tcp_connect_retry_in_ms so Telewindows (and possibly other 
 %   products in the future) can set it via command line.
 %   -----
 %      11/4/93, mpc: Increased length of these buffers by 1 to support NT 
 %   index lookup. This will not affect the existing code because only 
 %   positions up to NSOCKETS are referenced. For the lookup scheme, if an
 %   index is sought for an invalid socket, the number NSOCKETS is returned,
 %   which will result in access to these (unused) positions. (This will
 %   avoid out of bounds errors or stomping on some other sockets' data.)
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* external dependencies */
extern void g2ext_network_io_trace_note(char *note_string);
extern void g2ext_network_io_trace_note_s(char *note_string, char *arg);
extern void g2ext_network_io_trace_note_d(char *note_string, long arg);
extern void g2ext_set_too_many_fds();
extern void g2ext_unset_too_many_fds();
extern int  g2int_close_fd_callback(fd_type);
extern int  g2int_open_fd_callback(fd_type);
extern long g2pvt_initialize_network_interface();
extern long g2pvt_tcpip_close(long);

#ifndef WIN32
extern int errno;
#endif

extern int        g2ext_max_number_of_sockets;
extern TLS int    g2ext_no_connect_event_pending;
extern TLS long   g2pvt_resolver_handle;
extern TLS char  *g2pvt_resolver_hostent;
extern TLS int    g2ext_socket_is_connected;
extern G2pointer *g2ext_socket_to_NI_handle_table;
extern int        g2ext_too_many_fds;

extern NETWORK_INTERFACE *ne_current_network_interface;


/* externally accessible global variables */
#if defined(WIN32)
/* GhwndWin is the global window under MS Windows.  It is defined here because
 * it needs to be part of libtcp, even though most of its usage is in files not
 * concerned with networking.
 */
HWND                 GhwndWin = NULL;
#endif

struct sockaddr_in   g2ext_peeraddr_in;	/* for peer socket address */
struct sockaddr_in   g2ext_myaddr_in;	/* for local socket address */
long                 g2pvt_tcp_connect_retry_in_ms = 0;
long                 g2pvt_tcpip_connect_dont_retry = 0;

/* data static to this file */
static int           lastslot = 0;       /* Index of highest used slot */
static unsigned int *socktable;

#if defined(_WINSOCKAPI_)
//socket data
typedef struct SocketDataStruct {
  WSAOVERLAPPED overlapped;
  WSABUF data;
  int blocked;
} SocketData;

static SocketData** pSocketData;

#endif
int socket_buffer_size = 0x25000;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Partial IO Functions
 %
 % Description:
 %      These functions manage the partial-io and socket mapping
 %      tables
 %
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
 * static int g2ext_lookup_socket_index(unsigned socket)
 *
 *   Description: 
 *     Find the lookup table location for a given socket
 *   Input Arguments:
 *     socket:  a socket identifier
 *   Returns:
 *     return value: a positive table index on success
 *                   NSOCKETS, the last table entry (for errors), on error
 *   Notes:
 *        If we've reached the last slot, and it's not what we're looking for 
 *     then return error condition. Because this error condition will be 
 *     used as an array index, we have a dummy control slot at array index 
 *     NSOCKET, i.e., the (NSOCKET+1)th element.
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/
void g2ext_initialize_socket_index_table()
{
  int i;
  socktable = (unsigned int *)malloc(g2ext_max_number_of_sockets*sizeof(unsigned int));

#if defined(_WINSOCKAPI_)
  pSocketData = (SocketData**) malloc(g2ext_max_number_of_sockets * sizeof(SocketData*));
#endif

  for(i=0; i<g2ext_max_number_of_sockets; i++) {
    socktable[i] = (unsigned int)-1;

#if defined(_WINSOCKAPI_)
	pSocketData[i] = NULL;
#endif

  }
}

int g2ext_lookup_socket_index(socket)
     unsigned socket;
{
  int i;

  for(i=0; i<=lastslot && socktable[i] != socket; i++);
  return ( (i > lastslot) ? -1 : i);
}

int g2ext_allocate_socket_index(s)
     unsigned s;   /* a socket identifier */
{
  /* Scan the lookup table for an unused slot. When we find it, set the 
   *  slot value to be the sock id. If this slot number is greater
   *  than lastslot, have lastslot point here.
   * Note that currently we do not check for the "out of sockets"
   *  condition. 
   */
  int i;
  for(i=0; i<g2ext_max_number_of_sockets; i++)
    if (socktable[i] == (unsigned int)-1) {
      socktable[i] = s;
      if ( i > lastslot ) lastslot = i;

#if defined(_WINSOCKAPI_)
      // allocate socket data
      pSocketData[i] = (SocketData*) malloc(sizeof(SocketData));
      memset(&pSocketData[i]->overlapped, 0, sizeof(WSAOVERLAPPED));

      pSocketData[i]->overlapped.hEvent = WSACreateEvent();
      WSAResetEvent(pSocketData[i]->overlapped.hEvent);
	  
      memset(&pSocketData[i]->data, 0, sizeof(WSABUF));
      pSocketData[i]->blocked = 0;
#endif

      return i;
    }
  return -1;
}

void g2ext_deallocate_socket_index(s)
     unsigned s;
{ 
  int i = g2ext_lookup_socket_index(s);
  socktable[i] = (unsigned int)-1;
  for( ; lastslot>0 && socktable[lastslot] == (unsigned int)-1; lastslot--);

#if defined(_WINSOCKAPI_)
  WSACloseEvent(pSocketData[i]->overlapped.hEvent);
  if (pSocketData[i]->data.buf) {
	  free(pSocketData[i]->data.buf);
  }
  free(pSocketData[i]);
  pSocketData[i] = NULL;
#endif
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Socket Functions
 %
 % Description:
 %      These functions create, manage, utilize TCP sockets for 
 %      network communication.
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/
#if !defined(vms)
int g2pvt_tcpip_nodelay = 1;

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_tcpip_accept_internals(long listener_socket)
 *
 *   Description:
 *     see calling function g2pvt_tcpip_accept for description.  This will
 *     return an actual file descriptor integer rather than a G2 pointer to a
 *     network interface.  This was needed by weblink, so the internals were
 *     exposed
 *     
 *   Input Arguments:
 *     listener_socket:  listener on which to check for connections
 *   Returns: 
 *     return value: 0 if none pending
 *                   negative number if any error occured during the accept
 *                   a new socket fd for an accepted connection.
 *   Notes:
 *   Modifications:
 *      split from g2pvt_tcpip_accept by yduJ, 3/04
 *****************************************************************************/

long g2ext_tcpip_accept_internals(listener_socket)
    long listener_socket;
{
  int accept_socket, option_value;

#ifdef _IBMR2
  unsigned long size_of_inet_address = sizeof(struct sockaddr_in);
#else
  int size_of_inet_address = sizeof(struct sockaddr_in);
#endif
#if defined(_WINSOCKAPI_) || !defined(Platform_Solaris)
  int noblock_flag = 1;
#endif

  memset((char *) &g2ext_peeraddr_in, 0, size_of_inet_address);

  accept_socket = accept(listener_socket,
			 (struct sockaddr *) &g2ext_peeraddr_in,
			 &size_of_inet_address);

  if (accept_socket < 0) {
    errno = TCP_ERRNO;
    if (errno == EMFILE) g2ext_set_too_many_fds();
    return -1;
  }

#if defined(_WINSOCKAPI_)
  // Gensym-508: make socket uninheritable
  SetHandleInformation((HANDLE)accept_socket, HANDLE_FLAG_INHERIT, FALSE);
#endif

  g2int_open_fd_callback(accept_socket);

# if defined(vms) || defined(_WINSOCKAPI_)
  if (-1 == g2ext_allocate_socket_index(accept_socket)) {
    TCPCLOSE(accept_socket,TRUE);
    return NO_MORE_PARTIAL_WRITE_ENTRIES;
  }
# endif

  if (  TCP_SET_NON_BLOCKING(accept_socket, noblock_flag) 
	== SET_NON_BLOCKING_FAILURE) {
    g2pvt_tcpip_close(accept_socket);
    return TCPIP_ACCEPT_CANT_MAKE_NONBLOCKING;
  }

  option_value = 1;
  setsockopt (accept_socket, SOL_SOCKET, SO_KEEPALIVE, 
	      (char *) &option_value, sizeof(int));
    
  if (g2pvt_tcpip_nodelay) {
    option_value = 1;
    setsockopt(accept_socket, IPPROTO_TCP, TCP_NODELAY, 
	       (char *) &option_value, sizeof(int));
  }

  // Set sends and receivers buffer size
  option_value = socket_buffer_size;
  setsockopt(accept_socket, SOL_SOCKET, SO_SNDBUF, (char *) &option_value, sizeof(int));
  setsockopt(accept_socket, SOL_SOCKET, SO_RCVBUF, (char *) &option_value, sizeof(int));

  return accept_socket;
}

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/
/*****************************************************************************
 * long g2pvt_tcpip_accept(long listener_socket)
 *
 *   Description:
 *     Accept a pending tcp/ip connection on a listener.  In this version, we
 *     ALWAYS know there's a connection waiting before the accept call is made.
 *     Added '_ed' suffix to indicate that this function is used by the "event
 *     driven" code.
 *     -ncc, 15 Apr 1996
 *     
 *   Input Arguments:
 *     listener_socket:  listener on which to check for connections
 *   Returns: 
 *     return value: 0 if none pending
 *                   negative number if any error occured during the accept
 *                   a network interface associated with the socket if successful
 *   Notes:
 *   Modifications:
 *      split from g2pvt_tcpip_accept by ncc, 15 Apr 1996.
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

G2pointer g2pvt_tcpip_accept(listener_socket)
   long listener_socket;
{
	int accept_socket;
  /* int size_of_inet_address = sizeof(struct sockaddr_in); */

  G2pointer ni_g2pointer;
  NETWORK_INTERFACE * ni;

  char pathname[80];

#if defined(_WINSOCKAPI_)
  if (GhwndWin == NULL && !ne_use_sck) {
    /* If this process has no window, there is nowhere to post */
    /* asynchronous messages! This is bad. */
    return TCPIP_ACCEPT_NONE_PENDING;
  }
#endif

  accept_socket = g2ext_tcpip_accept_internals(listener_socket);
  if (accept_socket < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      return TCPIP_ACCEPT_NONE_PENDING;
    else 
      return accept_socket;
  }
  /* now do the lisp pointer fussing. */
  {
    struct hostent *host = 0;
    char *host_name;
    /* When the following statement is uncommented, the first connection
       attempt never completes (on the sun4).  Subsequent ones are OK. */
    /*
    host = gethostbyaddr((char *)&(g2ext_peeraddr_in.sin_addr), 
			 size_of_inet_address, 
			 AF_INET);
    */
    host_name = (host==0)?"ACCEPT":host->h_name;
    strcpy(pathname,"TCP_IP:");
    strcpy(pathname+7,host_name);
    sprintf(pathname+7+strlen(host_name),":fd=%ld", (long) accept_socket);
  }

  ni_g2pointer = g2pvt_initialize_network_interface(TCP_IP,
					      (long)accept_socket,
					      (char *)pathname,
					      ACTIVE_INTERFACE_STATUS,
					      0);
  ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer (ni_g2pointer);


  return ni_g2pointer;
}

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_set_tcp_connect_retry(long new_retry_interval_in_ms)
 *
 *   Description:
 *     Changes the interval that subsequent calls to g2pvt_tcpip_connect() will
 *     wait for a connection.
 *   Input Arguments:
 *     new_retry_interval_in_ms: retry interval in milliseconds
 *   Returns: 
 *     return value: 1 if successful, 0 if not.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

long g2ext_set_tcp_connect_retry(new_retry_interval_in_ms)
     long     new_retry_interval_in_ms;
{
    g2pvt_tcp_connect_retry_in_ms = new_retry_interval_in_ms; 
    return 1;
}
/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*****************************************************************************
 * long g2pvt_tcpip_connect(char *host, long port)
 *
 *   Description:
 *     Attempts to connect to server, given host and display
 *   Input Arguments:
 *     host:   target host for connection
 *     post:   target port number of connection
 *   Returns: 
 *     return value: negative number if connection fails,
 *                   nonnegative socket if connection is successful.
 *   Notes:
 *     [Note: adapted from X11 beta network connection code.]
 *       -----
 *        18 May 1995, ncc:  When this function returns connect_socket we 
 *     know that the connect process hasn't finished. We don't know whether or
 *     not it will succeed. This will be checked later, periodically, from 
 *     the ICP layer.
 *       -----
 *        mpc 6/22/93: Explicitly defining gethostbyname() causes a conflict
 *     with Windows NT's definition.
 *       -----
 *         jh, 1/27/95.  Use of the SO_REUSEADDR socket option here was 
 *     suggested by TGV to make closed socket socket numbers reusable more 
 *     quickly on Alpha VMS. Note the problem does not occur on their Vax VMS 
 *     implementation, despite their assertion that a four-minute wait before 
 *     address reuse is mandatory per RFC-793.  I did "MULTINET SHOW /
 *     CONNECTIONS" to verify that MultiNet (rather than UCX) was indeed running
 *     on the Vax.
 *     I am not confortable with wreaking this change on all our platforms at
 *     this late stage in the second 4.0 beta release.  I am especially wary of
 *     the Solaris - see my 7/19/94 note in g2pvt_tcpip_listen().  Someday, however,
 *     we should abstract this site to adhere to the ban on "abstractions that
 *     are shared by a few platforms but not used on others" that appears in the
 *     intro to this file.
 *     Furthermore, since long waits may be a TCP/IP standard, we should use
 *     that abstraction to try SO_REUSEADDR out on other platforms.
 *       -----
 *        jh, 3/25/93.  The following are old notes (circa 1990).  I believe
 *     they are concerned with proving that the multiple calls to connect() and 
 *     select() do no harm on any platform, despite the variety of behaviors 
 *     thereon.
 *
 *     I386 and sun4 will respond with a valid connect or complete failure.
 *
 *     HP will fail with EINPROGRESS but can be tested with another connect 
 *     call for EISCONN after some delay.
 *
 *     HP never waits on the select call but the second connect call is a valid
 *     indication of a successful connection.
 *       -----
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

static long g2pvt_tcpip_connect_internal (long, struct sockaddr *);

long g2pvt_tcpip_connect(host, port)
     char      *host;
     long       port;
{
    struct sockaddr_in        inet_address;
    struct sockaddr          *connect_address;
#if !defined(linux)
    struct hostent           *host_info;
#else
    struct addrinfo           hints, *result, *presult;
    char                      string_of_port[20], string_of_addr[100];
    void                     *paddr;
#endif
    long                      connect_socket;

#if defined(_WINSOCKAPI_)
    if (GhwndWin == NULL && !ne_use_sck) {
	/* If this process has no window, there is nowhere to post */
	/* asynchronous messages! This is bad. */
	return TCPIP_CONNECT_FELL_OFF_END;
    }
#endif

    if (!strcmp("", host))
	return TCPIP_CONNECT_EMPTY_HOST;

    connect_address = (struct sockaddr *) &inet_address;
    inet_address.sin_port = htons((unsigned short) port);

    connect_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (connect_socket < LEAST_ACTUAL_SOCKET_VALUE)
	return TCPIP_CONNECT_CANT_MAKE_SOCKET;

#if defined(_WINSOCKAPI_)
	//FIX G2-window for tw and twng remains after unexpected shutdown
	//set HANDLE_FLAG_INHERIT flag to 0 for connect_socket
	SetHandleInformation((HANDLE)connect_socket, HANDLE_FLAG_INHERIT, 0);
#endif

    g2int_open_fd_callback(connect_socket);

#   if defined(_WINSOCKAPI_) || defined(vms)
    if (-1 == g2ext_allocate_socket_index(connect_socket)) {
        TCPCLOSE(connect_socket,FALSE);
        return NO_MORE_PARTIAL_WRITE_ENTRIES;
    }
#   endif

    g2ext_no_connect_event_pending = FALSE;

    /* Get the statistics on the specified host. */
    g2ext_network_io_trace_note_s("Calling inet_addr or gethostbyname for \"%s\"", host);
    if ((inet_address.sin_addr.s_addr = inet_addr(host)) == INET_ADDR_FAILURE) {
#if defined(_WINSOCKAPI_)
	/* WSAAsync functions can only be used when ne_use_sck is FALSE */
	if (ne_use_sck)
	  goto next_method;

	/* GENSYMCID-1026: Network-interface connection attempt freezes G2. */
	g2pvt_resolver_hostent = (char*) malloc(MAXGETHOSTSTRUCT);
	host_info = (struct hostent*) g2pvt_resolver_hostent;
	g2pvt_resolver_handle = (long)
	    WSAAsyncGetHostByName(GhwndWin, WSA_NETEVENT_NS, host, g2pvt_resolver_hostent, MAXGETHOSTSTRUCT);
	return connect_socket;
next_method:
#endif
#if !defined(linux)
	if ((host_info = gethostbyname(host)) == NULL) {
	  g2ext_network_io_trace_note("gethostbyname failed: no such host");
	  errno = TCPIP_CONNECT_NO_SUCH_HOST;
	  return connect_socket;
	}

	/* Check the address type for an internet host. */
	if (host_info->h_addrtype != AF_INET) {
	  g2ext_network_io_trace_note("gethostbyname failed: not an internet host");
	  errno = TCPIP_CONNECT_NOT_INTERNET_HOST;
	  return connect_socket;
	}

	/* Set up the socket data. */
	inet_address.sin_family = host_info->h_addrtype;
	memcpy((char *) &inet_address.sin_addr, 
	       (char *) host_info->h_addr, 
	       sizeof(inet_address.sin_addr));
	g2ext_network_io_trace_note_d("gethostbyname succeeded: %x",*(int *)(&inet_address.sin_addr));
#else
        /* LSB requires using getaddrinfo() instead of gethostbyname */
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_flags = AI_CANONNAME;
        hints.ai_family = AF_INET;
        snprintf(string_of_port, sizeof string_of_port, "%d", port);
        if (getaddrinfo(host, string_of_port, &hints, &result) != 0) {
            g2ext_network_io_trace_note("getaddrinfo failed: no such host");
            errno = TCPIP_CONNECT_NO_SUCH_HOST;
            return connect_socket;
        }

        for (presult = result; presult != NULL; presult = presult->ai_next) {
            paddr = presult->ai_family == AF_INET ? &((struct sockaddr_in *)presult->ai_addr)->sin_addr.s_addr :
                                                    &((struct sockaddr_in6 *)presult->ai_addr)->sin6_addr.s6_addr;
            inet_ntop(presult->ai_family, paddr, string_of_addr, sizeof string_of_addr);
            /* Try connecting */
            g2pvt_tcpip_connect_internal(connect_socket, presult->ai_addr);
            if (errno == 0) {
                g2ext_network_io_trace_note_d("connection establishment succeeded: %s", string_of_addr);
                break;
            }
            g2ext_network_io_trace_note_d("connection establishment failed: %s", string_of_addr);
        }
        if (result == NULL || errno != 0) {
            g2ext_network_io_trace_note("getaddrinfo failed: has no available internet host");
            if (0 == errno) {
                errno = TCPIP_CONNECT_NOT_INTERNET_HOST;
            }
        }
        freeaddrinfo(result);
        return connect_socket;
#endif /* !defined(linux) */

    } else {
        g2ext_network_io_trace_note_d("inet_addr succeeded: %x",*(int *)(&inet_address.sin_addr));
	inet_address.sin_family = AF_INET;
    }

    return g2pvt_tcpip_connect_internal (connect_socket, connect_address);
}

static long g2pvt_tcpip_connect_internal (long connect_socket, struct sockaddr *connect_address)
{
    int noblock_flag;
    int option_value;
    int size_of_inet_address = sizeof (struct sockaddr_in);

    /* set non-blocking IO for the socket */
    noblock_flag = 1;
    if (TCP_SET_NON_BLOCKING(connect_socket, noblock_flag) ==
	SET_NON_BLOCKING_FAILURE) {
      errno = TCPIP_CONNECT_CANT_MAKE_NONBLOCK_CONNECT;
      return connect_socket;
    }

#   if defined(__ALPHA) && defined(vms)
    option_value = 1;
    setsockopt(connect_socket, SOL_SOCKET, SO_REUSEADDR,
	       (char *) &option_value, sizeof(int));
#   endif

    option_value = 1;
    setsockopt (connect_socket, SOL_SOCKET, SO_KEEPALIVE, 
		(char *) &option_value, sizeof(int));

    if (g2pvt_tcpip_nodelay) {
      option_value = 1;
      setsockopt(connect_socket, IPPROTO_TCP, TCP_NODELAY, 
		 (char *) &option_value, sizeof(int));
    }

#   if defined(_WINSOCKAPI_)
    if (!ne_use_sck)
      WSAAsyncSelect(connect_socket, GhwndWin, WSA_NETEVENT, FD_CONNECT);
#   endif

    // Set sends and receivers buffer size
    option_value = socket_buffer_size;
    setsockopt(connect_socket, SOL_SOCKET, SO_SNDBUF, (char *) &option_value, sizeof(int));
    setsockopt(connect_socket, SOL_SOCKET, SO_RCVBUF, (char *) &option_value, sizeof(int));

    if (connect(connect_socket, connect_address, size_of_inet_address) !=
	CONNECT_FAILURE) {
      g2ext_no_connect_event_pending = TRUE;
      errno = 0;
      return connect_socket;
    }

    errno = TCP_ERRNO;

    if ((errno == EWOULDBLOCK) ||
	(errno == EINPROGRESS) ||
	(errno == EAGAIN)) {
      /* GENSYMCID-712: Linux Enterprise: g2i kbs cannot be built by G2 server (release build)
       * Following line broke AAR on Windows when G2/TWNG start in parallel. -- Chun Tian (binghe), 2012/06/09
       */
#ifndef WIN32
      g2ext_no_connect_event_pending = TRUE;
#endif
      errno = 0;
    }

    return connect_socket;
}

void g2pvt_tcpip_reconnect (NETWORK_INTERFACE *ni)
{
    struct sockaddr_in        inet_address;
    struct sockaddr          *connect_address;
    struct hostent           *host_info;
    int                       connect_socket;

    connect_address = (struct sockaddr *) &inet_address;
    connect_socket = ni->handle;
    inet_address.sin_port = htons((unsigned short) ni->port);
    host_info = (struct hostent*) ni->resolver_hostent;

    /* Check the address type for an internet host. */
    if (host_info->h_addrtype != AF_INET) {
	g2ext_network_io_trace_note("gethostbyname failed: not an internet host");
	errno = TCPIP_CONNECT_NOT_INTERNET_HOST;
	return;
    }

    /* Set up the socket data. */
    inet_address.sin_family = host_info->h_addrtype;
    memcpy((char *) &inet_address.sin_addr, 
	   (char *) host_info->h_addr, 
	   sizeof(inet_address.sin_addr));
    g2ext_network_io_trace_note_d("gethostbyname succeeded: %x",*(int *)(&inet_address.sin_addr));

    g2ext_no_connect_event_pending = FALSE;
    g2pvt_tcpip_connect_internal (connect_socket, connect_address);

    ni->connect_status = errno;
    ni->connected_p = g2ext_no_connect_event_pending;
}

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2pvt_tcpip_listen(long port_number)
 *
 *   Description:
 *     Sets up a pending TCP/IP connection at the given port number.
 *   Input Arguments:
 *     port_number: port at which to establish a listener
 *   Returns: 
 *     return value: negative number if setup fails,
 *                   nonnegative number if the setup is successful.
 *   Notes:
 *       The server should listen on the wildcard address, rather than its own
 *     internet address.  This is generally good practice for servers, because
 *     on systems which are connected to more than one network at once will be
 *     able to have one server listening on all networks at once.  Even when
 *     the host is connected to only one network, this is good practice,
 *     because it makes the server program more portable.
 *
 *   Modifications: css, 6/15/01, enabled the use of SO_REUSEADDR on all
 *       platforms.  Removed erroneous comments from the notes section above.
 *       
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2pvt_tcpip_listen(long port_number)
{
  struct sockaddr_in srv_addr;
#ifdef _WINSOCKAPI_
  SOCKET sock;
#else
  int sock;
#endif
  int err;
  const int on = 1;

#if defined(vms)
  if (!ucx_is_running())
    return TCPIP_LISTEN_FAILURE;
#endif

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    return TCPIP_LISTEN_FAILURE;

#if defined(_WINSOCKAPI_)
  /* GENSYMCID-717: G2 port blocked by a spawned GSI */
  SetHandleInformation((HANDLE) sock, HANDLE_FLAG_INHERIT, 0);
#endif

  memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  srv_addr.sin_port = htons((unsigned short)port_number);

  g2int_open_fd_callback(sock);

#if defined(vms) || defined(_WINSOCKAPI_)
  if (g2ext_allocate_socket_index(sock) == -1) {
    g2pvt_tcpip_close(sock);
    return NO_MORE_PARTIAL_WRITE_ENTRIES;
  }
#endif

#ifndef _WINSOCKAPI_
  /* broken on Win32, see HQ-4137048 */
  err = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *) &on, sizeof(on));
  if (err != 0)
    perror("g2pvt_tcpip_listen");
#endif

  err = bind(sock, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
  if (err != 0) {
    g2pvt_tcpip_close(sock);
    return TCPIP_LISTEN_FAILURE;
  }

  err = listen(sock, SOMAXCONN);
  if (err != 0) {
    g2pvt_tcpip_close(sock);
    return TCPIP_LISTEN_FAILURE;
  }

  return sock;
}

/*****************************************************************************
 * long g2pvt_tcpip_set_nodelay(long listener_socket)
 *
 *   Description:
 *     Set a socket to be nonblocking.
 *     
 *   Input Arguments:
 *     listener_socket:  listener on which to check for connections
 *   Returns: 
 +             0 if no error,
 +             -1 if any error occurred.
 *   Notes:
 *     This is used by weblink, which wishes to process the listen/accept cycle
 *     within lisp differently than G2 processes it.
 *   Modifications:
 *****************************************************************************/
long g2pvt_tcpip_set_nodelay(listener_socket) 
    long listener_socket;
{
#if defined(_WINSOCKAPI_) || !defined(Platform_Solaris)
  int noblock_flag = 1;
#endif
  return TCP_SET_NON_BLOCKING(listener_socket, noblock_flag);
}


/*****************************************************************************
 * long incoming_connection_appears_to_be_ssl_p(int socket)
 *
 *   Description:
 *     Peek ahead up to 3 bytes to determine the protocol.
 *     
 *   Input Arguments:
 *     socket:  
 *   Returns: 
 +              0 if not SSL or don't know
 +              1 if SSL
 +             -1 if blocked; let's try again later.
 *   Notes:
 *   Modifications:
 *     6/8/06, yduJ: added blocked, stopped checking for ICP.
 *****************************************************************************/
static int incoming_connection_appears_to_be_ssl_p(int socket)
{
  unsigned char buf[3];
  int n;

  /*
    TLS1: 16 03 01
    SSL3: 16 03 00
    SSL2: 80 xx 01 
    ICP:  00 xx FA [But, we don't care what the non-SSL bits are.]
    TW4x: 0x xx FA
    */

  n = TCP_PEEK(socket, buf, sizeof(buf));
/* printf("Peek: [%d] %02x %02x %02x\n", n, buf[0], buf[1], buf[2]); fflush(stdout); */
  switch(n) {
   case 3:
     return ((buf[0] == 0x16 && buf[1] == 0x03) || (buf[0] == 0x80 && buf[2] == 0x01));
   case 2:
   case 1:
     return (buf[0] == 0x16 || buf[0] == 0x80);
   case -1:
     errno = TCP_ERRNO;
     if ((errno == EWOULDBLOCK) || (errno == EINPROGRESS)  || (errno == EAGAIN) || (errno == EINTR))
       return -1;
   default:
     return 0;
  }
}


/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2pvt_tcpip_read(long external_socket, char *buffer, long max_count_to_read)
 *
 *   Description:
 *     Read from a TCP/IP socket at most count chars into buffer.
 *   Input Arguments:
 *     external_socket:    socket to read from.
 *     buffer:             buffer to read into.
 *     max_count_to_read:  eponymous
 *   Returns: 
 *     return value: 0 if no pending data,
 *                  -1 if any error occured during the read,
 *                   positive number is count of bytes actually read.
 *   Notes:
 *       10/12/94, ncc: The call to check_async_error isn't doing anything.
 *     check_async_errno returns a value and it's being dropped upon the 
 *     floor.
 *     -----
 *       jh, 3/26/93.  The oddness test is because ICP bytes are 2 C bytes.
 *     It could be argued that a higher layer of abstraction should be 
 *     responsible for this.
 *   Modifications:
 *       10/14/94, ncc: Accordingly, I'm commenting the check_async_error call
 *     out until I understand more about asynchronous TCP errors on read.
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2pvt_tcpip_read(tcp_socket, buffer, max_count_to_read)
int       tcp_socket;
char     *buffer;
long      max_count_to_read;
{
  long actual_read_count;
  int count_already_read, count_to_read, ssl_p;
  char *buffer_to_read;
  NETWORK_INTERFACE *ni = ne_current_network_interface;
  G2SSL ssl;

  ni->last_status = 0;

  if(ni->ssl_pending_p) {
    ssl_p = incoming_connection_appears_to_be_ssl_p(tcp_socket);
    if (ssl_p > 0) {
      ni->ssl_pending_p = 0;
      ni->ssl = g2pvt_ssl_accept(ni->handle);
    } else if (ssl_p == -1)
      goto blocked;
    else
      ni->ssl_pending_p = 0;
  }

  ssl = ni->ssl;
  count_already_read = 0;
  buffer_to_read = buffer + count_already_read;
  count_to_read = max_count_to_read - count_already_read;
  
again:
   actual_read_count = 
     ssl ? g2pvt_ssl_read(ssl, buffer_to_read, count_to_read) :
           TCP_READ(tcp_socket, buffer_to_read, count_to_read);

  if (actual_read_count == 0) {	/* this means EOF on socket. */
    return NE_EOF_VALUE;
  }

  if (actual_read_count < 0) {   /* i.e., an error */
    errno = TCP_ERRNO;
    if (errno == EINTR)
      goto again;
    else if ((errno == EWOULDBLOCK) || (errno == EINPROGRESS)  || (errno == EAGAIN)) {
      goto blocked;
    }
    else {
      ni->last_status = errno;
      return NE_ERROR_VALUE;
    }
  }

  count_already_read += actual_read_count;
  buffer_to_read += actual_read_count;
  count_to_read -= actual_read_count;

  return count_already_read;

blocked:
#if !defined(vms)
  if (ne_use_sck)
    ne_enable_read_events(g2ext_socket_to_NI_handle_table[ne_current_network_interface->socket_index]);
#endif
  return NE_BLOCKED_VALUE;
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2pvt_tcpip_write(long external_socket, char *buffer, long max_count_to_write)
 *
 *   Description:
 *     Write to a TCP/IP socket.
 *   Input Arguments:
 *     external_socket:    socket to write to.
 *     buffer:             buffer to write from.
 *     max_count_to_write: eponymous
 *   Returns: 
 *     return value: 0 if the write would block,
 *                  -1 if any error occured during the write,
 *                   positive number is count of bytes written.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

#ifdef _WINSOCKAPI_

extern void g2pvt_enqueue_write_event();
#define SOCKET_TIMEOUT 10000

// Waits for non-finished send operation
int update_socket_data(s, data, timeout)
    SOCKET s;
    SocketData* data;
    int timeout;
{
  DWORD wait_res;
  DWORD data_send = 0;
  int result = -1;
  char* buffer;
  DWORD oflags = 0;

  if (data == 0)
  {
	  data = pSocketData[g2ext_lookup_socket_index(s)];
  }

  // wait
  wait_res = WSAWaitForMultipleEvents(1, &data->overlapped.hEvent, TRUE, timeout, TRUE);
  if (wait_res == WSA_WAIT_TIMEOUT)
    WSASetLastError(WSAEWOULDBLOCK);
  else if (wait_res != WSA_WAIT_FAILED)
    result = 0;

  // get result of send operation
  if (result!= -1)
  {
    if (WSAGetOverlappedResult(s, &data->overlapped, &data_send, FALSE, &oflags))
    {
      data->blocked = data_send < data->data.len;
      if (data->blocked)
      {
        // prepare data for next send operation
        data->data.len -= data_send;
        buffer = malloc(data->data.len);
        memcpy(buffer, ((char*) data->data.buf) + data_send, data->data.len);
        free(data->data.buf);
        data->data.buf = buffer;
      }
      else
      {
        data->data.len = 0;
        if (data->data.buf)
          free(data->data.buf);
        data->data.buf = 0;
      }

      result = data_send;
    }
    else
    {
      if (WSAGetLastError() == WSA_IO_INCOMPLETE)
        WSASetLastError(WSAEWOULDBLOCK);
      result = -1; // data have not been sent yet
    }
  }

  return result;
}

// Tests sockets status
// Calls g2pvt_enqueue_write_event() for blocket sockets
//  if their send operation has been finished
// Returns count of blocket sockets
int g2pvt_update_sockets_state()
{
  int i;
  int count = 0;

  for(i=0; i<=lastslot ; i++)
  {
    if (socktable[i] != (unsigned int)-1 &&
        pSocketData[i]->blocked)
    {
      if (update_socket_data(socktable[i], pSocketData[i], 10) > 0)
        g2pvt_enqueue_write_event(socktable[i]);
	  count++;
    }
  }

  return count;
}

// GENSYMCID-1109: G2 freezes passing data via G2-to-G2
// The function `g2_send' is not used any more, because it will block the whole G2 on large data buffers.
// We recovered macro TCP_WRITE back to `send', and let G2 to schedule more write events when write buffer
// is full. -- Chun Tian (binghe), 2013/10/10.

int g2_send(s, buf, len, flags)
        SOCKET s;
        char *buf;
        int len, flags;
{
  DWORD data_send = 0;
  int result = 0;
  char* buffer;
  SocketData* data;
  DWORD oflags = 0;

  data = pSocketData[g2ext_lookup_socket_index(s)];
  if (data->blocked)
  {
    result = update_socket_data(s, data, SOCKET_TIMEOUT);
    if (result < 0)
      return result;
  }

  WSAResetEvent(data->overlapped.hEvent);

  if (!data->blocked)
  {
    // make a new buffer
    buffer = malloc(len);
    memcpy(buffer, buf, len);
    if (data->data.buf)
      free(data->data.buf);
    data->data.buf = buffer;
    data->data.len = len;
  }

  // send data
  if (WSASend(s, &data->data, 1, &data_send, flags, &data->overlapped, NULL) == SOCKET_ERROR)
  {
    if (WSAGetLastError() != WSA_IO_PENDING)
      return -1;
  }

  if (data->blocked)
  {
    // just wait - all checks will be in next g2_send() call
    WSAWaitForMultipleEvents(1, &data->overlapped.hEvent, TRUE, SOCKET_TIMEOUT, TRUE);
    result = 0;
  }
#ifdef PACKAGING_G2_ENTERPRISE
  else if(data_send)
    /* GENSYMCID-663: Faster-201-TAMIstvan-Double-Performance-UC11RPC
       02/15/2012 vchefr We don't to wait for overlapped result if WSASend complete work immediatelly. */
    result = data_send;
#endif
  else
  {
    result = -1;

    if (WSAWaitForMultipleEvents(1, &data->overlapped.hEvent, TRUE, SOCKET_TIMEOUT, TRUE) != WSA_WAIT_FAILED)
    {
      if (WSAGetOverlappedResult(s, &data->overlapped, &data_send, FALSE, &oflags))
        result = data_send;
      else if (WSAGetLastError() == WSA_IO_INCOMPLETE)
      {
        // the send operation has been not finished yet, so return that all data have been sent
        // all data will be sent during next g2_send() calls
        result = len;
        data->blocked = 1;
      }
    }
  }

  return result;
}

#endif

long g2pvt_tcpip_write(tcp_socket, buffer, max_count_to_write)
int        tcp_socket;
char      *buffer;
long       max_count_to_write;
{
  int      count_actually_written, count_written_so_far, count_to_write;
  char    *write_buffer;
  G2SSL ssl = ne_current_network_interface->ssl;

  write_buffer = buffer;
  count_to_write = max_count_to_write;
  count_written_so_far = 0;

again:
   count_actually_written 
     = ssl ? g2pvt_ssl_write(ssl, write_buffer, count_to_write) : 
             TCP_WRITE((int)tcp_socket, write_buffer, count_to_write);

  if (count_actually_written < 0) { /* i.e., an error */
    errno = TCP_ERRNO;
    if (errno == EINTR)
      goto again;
    else if ((errno == EWOULDBLOCK) || (errno == EINPROGRESS) || (errno == EAGAIN)) {
      /* a "benign" error - the write has blocked but nothing else is wrong */
#if !defined(vms)
      if (ne_use_sck)
	ne_enable_write_events(g2ext_socket_to_NI_handle_table[ne_current_network_interface->socket_index]);
#endif
      return count_written_so_far;
    }
    else {
      /* a "malign" error - something is wrong with the connection */
      ne_current_network_interface->last_status = errno;
      return TCPIP_WRITE_FAILURE;
    }
  }

  write_buffer += count_actually_written;
  count_written_so_far += count_actually_written;
  count_to_write -= count_actually_written;
  if (0 < count_to_write)
    if (!ne_use_sck)
      goto again;
    else
      ne_enable_write_events(g2ext_socket_to_NI_handle_table[ne_current_network_interface->socket_index]);

  /* write of all chars completed */
  return count_written_so_far;
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2pvt_tcpip_close(long external_socket)
 *
 *   Description:
 *     Shut down and close a TCP socket, aborting all pending operations.
 *   Input Arguments:
 *     external_socket:  socket to close.
 *   Returns: 
 *     return value: 0 if no error,
 *                  -1 if any error occurred.
 *   Notes:
 *       10/12/94, ncc: The call to check_async_error isn't doing anything.
 *     check_async_errno returns a value and it's being dropped upon 
 *     the floor.
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

long g2pvt_tcpip_close(external_socket)
    long external_socket;
{
  int internal_socket = external_socket;

# if defined(WIN32)
  if (!ne_use_sck) {
    WSAAsyncSelect(internal_socket, GhwndWin, 0, 0); /* post no more events for this socket. */
  }
# endif

  TCPCLOSE(internal_socket,g2ext_socket_is_connected);

  return 0;
}


#endif /* ndef(vms) */


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Host Lookup Functions
 %
 % Description:
 %      These functions do host name/address lookups
 %
 % Notes:
 %
 % Modifications:  moved g2pvt_tcpip_gethostname to this new section, yduJ 6/06
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * long g2pvt_tcpip_gethostname(char *string_buffer, long length)
 *
 *   Description:
 *     Writes the name of the node running this process into buffer.
 *   Input Arguments:
 *     string_buffer:  Buffer in which to return host name
 *     length:         length of provided buffer
 *   Returns: 
 *     string_buffer: null terminated name of host
 *     return value:
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2pvt_tcpip_gethostname(string_buffer, length)
     char    *string_buffer;
     long     length;
{
    long status = 0;

#   if defined(_WINSOCKAPI_)
        if (gethostname(string_buffer, (int)length) != SOCKET_ERROR)
	    status = 0;
	else if (GetComputerName(string_buffer, (LPDWORD) &length) == FALSE)
	    status = -1;
#   endif

#   if defined(unix)
        status = gethostname(string_buffer, (int)length);
#   endif

    return(status);
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*****************************************************************************
 * long g2pvt_tcpip_get_addresses(char*** buffer)
 *
 * Description: 
 *     
 *   Input Arguments:
 *     buffer:  Pointer to buffer of pointers to strings (scary!  3 stars!)
 *   Returns: 
 +              number of addresses; 0 may mean unsuccessful, or no 
 *              addresses found.  Buffer filled in with address octets.
 *   Notes:
 *     Caller is responsible for copying the data: buffer belongs to the OS
 *
 *   Modifications:
 *****************************************************************************/

#ifndef Platform_Linux

/* GENSYMCID-474: "G2-Get-Network-Address-List() does not work in Linux"

   Note: this is the original version which works well on Win32, it try to get
   the hostname of current machine, and then resolve all its addresses using
   gethostbyname(). However, this logic won't work on any other platform, at
   least not on Linux.

   -- Chun Tian (binghe) for Glority,  Oct 6, 2011 (The Day Steve Jobs Died)
 */

int g2pvt_tcpip_get_addresses(char*** buffer)
{
  int i, r;
  struct hostent *h;
  char buf[128];

  r = g2pvt_tcpip_gethostname(buf,128);
  if (r < 0)
    return 0;

  h = gethostbyname(buf);
  *buffer = (char **)(h->h_addr_list);
  i = 0;
  while (h->h_addr_list[i] != NULL)
    ++i;

  return i;
}

#else /* defined(WIN32) */

/* GENSYMCID-474: "G2-Get-Network-Address-List() does not work in Linux"

   This is a UNIX-specific version of g2pvt_tcpip_get_addresses(), it gets
   addresses directly from interfaces, using BSD socket ioctl() calls.
   Note that, we cannot use more advanced Linux NETLINK APIs, because it's
   not defined in LSB (yet).

   As a result, only the "primiary" address on each interface (it can also
   be aliases of a interface, like eth0:0, eth0:1, ...) can be retrieved.
   This means, if user set a secondard address on a interface which already
   have an address, by using "ip addr add ..." commands, as the result, this
   secondard address won't be found by this function and so does G2 procedure
   G2-Get-Network-Address-List(). This should be considered as a known
   limitation of most Linux applications which trys to save/keep the maximum
   compatibility across older and newer Linux distributions.

   -- Chun Tian (binghe) for Glority,  Oct 6, 2011 (The Day Steve Jobs Died)
 */

struct ifi_info {
  struct sockaddr *ifi_addr;
  struct ifi_info *ifi_next;
};

static void free_ifi_info (struct ifi_info *ifihead)
{
  struct ifi_info *ifi, *ifinext;
  for (ifi = ifihead; ifi != NULL; ifi = ifinext) {
    if (ifi->ifi_addr != NULL)
      free(ifi->ifi_addr);
    ifinext = ifi->ifi_next;
    free(ifi);
  }
}

int g2pvt_tcpip_get_addresses(char*** buffer)
{
  struct ifi_info *ifi, *ifihead, **ifipnext;
  int i, index, sockfd, len, lastlen, flags;
  char *ptr, *buf, lastname[IFNAMSIZ], *cptr;
  struct ifconf ifc;
  struct ifreq *ifr, ifrcopy;
  struct sockaddr_in *sinptr;
  struct in_addr addr, *paddr;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  lastlen = 0;
  len = 100 * sizeof(struct ifreq); /* initial buffer size guess */

  for (;;) {
    buf = malloc(len);
    ifc.ifc_len = len;
    ifc.ifc_buf = buf;
    if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
      if (errno != EINVAL || lastlen != 0)
	perror("g2pvt_tcpip_get_addresses");
    } else {
      if (ifc.ifc_len == lastlen)
	break; /* success, len has not changed */
      lastlen = ifc.ifc_len;
    }
    len += 10 * sizeof(struct ifreq); /* increment */
    free(buf);
  }

  ifihead = NULL;
  ifipnext = &ifihead;
  i = 0; /* the variable i is used to count the ifi_info link table */

  for (ptr = buf; ptr < buf + ifc.ifc_len;) {
    ifr = (struct ifreq *) ptr;

    ptr += sizeof(struct ifreq); /* for next one in buffer */

    if (ifr->ifr_addr.sa_family != AF_INET) {
      /* TODO: on Mac OS X, it seems that no interface can pass this test. */
      continue;
    }

    ifrcopy = *ifr;
    ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy);
    flags = ifrcopy.ifr_flags;

    if ((flags & IFF_UP) == 0) {
      continue; /* ignore if interface not up */
    }

    ++i;
  
    ifrcopy = *ifr;
    ioctl(sockfd, SIOCGIFADDR, &ifrcopy);
    sinptr = (struct sockaddr_in *) &ifrcopy.ifr_addr;

    ifi = calloc(sizeof(struct ifi_info), 1);
    *ifipnext = ifi; /* prev points to this new one */
    ifipnext = &ifi->ifi_next; /* pointer to next one goes here */

    if (ifi->ifi_addr == NULL) {
      ifi->ifi_addr = calloc(sizeof(struct sockaddr_in), 1);
      memcpy(ifi->ifi_addr, sinptr, sizeof(struct sockaddr_in));
    }
  }

  free(buf);
  close(sockfd);

  /* make a array */
  if (i > 0) {
    /* Note: this space will be freed in initialize_net_addresses (networks.c) */
    *buffer = (char **) malloc(i * sizeof(struct in_addr));
    paddr = (struct in_addr *) (*buffer);

    for (index = 0, ifi = ifihead; ifi != NULL; ifi = ifi->ifi_next) {
      sinptr = (struct sockaddr_in *) ifi->ifi_addr;

      memcpy((char *) &paddr[index],
  	     (char *) &(sinptr->sin_addr),
	     sizeof(struct in_addr));

      ++index;
    }
  }

  free_ifi_info(ifihead);
  return i;
}

#endif /* Platform_Linux */

/*****************************************************************************
 * long g2ext_get_peer_address_string(int socket, char* buffer, int buflen)
 *
 * Description: gets the address of the guy on the other end of the given
 *     socket, put it in the string buffer given.  Used by Weblink.
 *     
 *   Input Arguments:
 *     socket: File descriptor of socket (not network handle; caller must call
 *             c-network-get-fd-from-handle).
 *     buffer:  8-bit character buffer to store return value
 *     buflen:  Length of buffer in bytes
 *   Returns: 
 +               0 if successful
 +              -1 if not
 *   Notes:
 *   Modifications:
 *****************************************************************************/

int g2ext_get_peer_address_string(socket, buffer, buflen)
    int socket;
    char *buffer;
    int buflen;
{
  struct sockaddr addr;
#if defined(__hpux) || defined(__osf__)
  int len = sizeof(struct sockaddr);
#elif defined(linux)
  socklen_t len = sizeof(struct sockaddr);
#else
  size_t len = sizeof(struct sockaddr);
#endif
  struct in_addr *iaddr;

  buffer[0]='\000';
  if (getpeername(socket, &addr, &len) < 0) {
    return -1;
  }
  iaddr = &(((struct sockaddr_in *)&addr)->sin_addr);
  {
    char *str = inet_ntoa(*iaddr);
    strcpy(buffer, str);
  }
  return 0;
}

/*****************************************************************************
 * long g2ext_get_peer_hostname(int socket, char* buffer, int buflen)
 *
 * Description: gets the host name of the guy on the other end of the given
 *     socket, put it in the string buffer given.  Used by Weblink.
 *     
 *   Input Arguments:
 *     socket: File descriptor of socket (not network handle; caller must call
 *             c-network-get-fd-from-handle).
 *     buffer:  8-bit character buffer to store return value
 *     buflen:  Length of buffer in bytes
 *   Returns: 
 +               0 if successful
 +              -1 if not
 *   Notes: This is different from the original gw_get_peer_name in that it
 *     is not conditionalized on "enable_hostname_lookups".  Said
 *     conditionalization is now done in lisp code.
 *   Modifications:
 *****************************************************************************/
int g2ext_get_peer_hostname(socket, buffer, buflen)
int socket;
char *buffer;
int buflen;
{
    struct sockaddr addr;
#if defined(__hpux) || defined(__osf__)
    int len = sizeof(struct sockaddr);
#elif defined(linux)
    socklen_t len = sizeof(struct sockaddr);
#else
    size_t len = sizeof(struct sockaddr);
#endif
    char *name = NULL;
    struct in_addr *iaddr;
#if !defined(linux)
    struct hostent *host_entry;
#else
    int result;
#endif

    buffer[0]='\000';
    /* Get the numeric address of the peer */
    if (getpeername(socket, &addr, &len) < 0) {
      return -1;
    }
    iaddr = &(((struct sockaddr_in *)&addr)->sin_addr);
#if !defined(linux)
    host_entry
      = gethostbyaddr((char *) iaddr, sizeof(struct in_addr), AF_INET);
    if (host_entry) {
      buffer[buflen-1] = '\000';
      strncpy(buffer, host_entry->h_name, buflen-1);
      return 0;
    } else { /* punt out to the dotted quad address */
      name = inet_ntoa(*iaddr);
      strcpy(buffer, name);
      return 0;
    }
#else
    result = getnameinfo(&addr, sizeof(struct sockaddr_in), name, NI_MAXHOST, NULL, 0, 0);
    if (result == 0) {
      buffer[buflen-1] = '\000';
      strncpy(buffer, name, buflen-1);
      return 0;
    } else {
      name = inet_ntoa(*iaddr);
      strcpy(buffer, name);
      return 0;
}
#endif
}

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/***********
 * testing *
 ***********/

#ifdef TEST_TCP_SELFCONTAINED
#endif

/* ... other testing suites, each with its own main() ... */
