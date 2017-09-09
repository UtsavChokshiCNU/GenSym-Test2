#ifndef _CPRIM_H
#  error "You must include cprim.h before networks.h"
#endif

#include <stdio.h>
#if !defined(sun)
#  include <stdlib.h>
#endif

#include <ctype.h>
#include "ssl.h"

/* Solaris hack for green threads, used by JDK */
#if defined(sparcsol)
#  define recv _recv
#  define read _read
#  define write _write
#endif

#define UNKNOWN_PROTOCOL -1L   /* id for an unknown protocol.  MUST be < 0  */

#define UDP               11L        /* used in the network_interface struct. */
#define TCP_IP            13L        /* Arbitrary id number for TCP_IP protocol  */
#define ALL               14L
#define WATCH             15L
#define ICMP              16L


#define ICP_SUCCEED 1L
#define ICP_FAIL -1L
#define NOOP_CODE_ATTEMPTED -2L

#define BUFFER_LEN  300L     /* Size of local buffers for string operations */
#define ERROR_STATE -5L     /* Error flag */

#define MAX_LISTENERS 20L
#define MAX_PENDING_CONNECTIONS 20L

#define G2  1L
#define GSI 2L

#define G2_TCP_LISTENER_START   1111
#define GSI_TCP_LISTENER_START 22041

#define LISTENER_MAX_ITS   200L   /* Max number of times to attempt a socket */

#define LISTEN_INTERFACE_STATUS 1
#define CONNECT_INTERFACE_STATUS 2
#define ACTIVE_INTERFACE_STATUS 3
#define DISPLAY_INTERFACE_STATUS 4
#define WATCH_INTERFACE_STATUS 5
#define ERROR_INTERFACE_STATUS 6
#define ICMP_INTERFACE_STATUS 7


/* conversion from LISTENER structure: */
#define ACCEPT_FUNCTION read_function
#define GETHOSTNAME_FUNCTION write_function
#define NEXT parent_listener

typedef struct a_network_interface
{
  int listener_p;
  int connected_p;
  int display_event_interface_p;
  int watch_p;
  int watch_for_writing_p;
  int icmp_p;

  long handle;  /* this is the endpoint (for tcp, the socket fd; vms, chan) */
  long g2_pointer_handle;
  long socket_index;
  long protocol_id;
  char *nw_pathname;  /* nw = network; was protocol in LISTENER STRUCT */
  unsigned char *nw_raw; /* Sometimes we cache gethostbyname results here */
  char *resolver_hostent;         /* buffer passed to WSAAsyncGetHostByName */
  long resolver_handle;           /* handle return by WSAAsyncGetHostByName */
  int port;

  long (*read_function)();        /* accept_function for listeners */
  long (*write_function)();       /* gethostname_function for listeners */
  long (*close_function)();

  int last_status;
  int connect_status;
  int debug_status;

  struct a_network_interface *parent_listener; /* next field in LISTENER structure */

  int secure_connection_requested;             /* If true, attempt SSL when creating connections */
  int ssl_pending_p;			       /* If true, peek 4 bytes to guess SSL vs cleartext */
  G2SSL ssl;			               /* Pointer to SSL object, if this socket is secure. */
} NETWORK_INTERFACE;

typedef struct listener_defaults
{
  long tcpip_max_iterations;
  long default_tcpip_listener;
  long protocol;
  long exact_tcpip_port_required;
  long secure_connection_requested;
} LISTENER_DEFAULTS;


typedef struct pending_connection
{
  long handle;
  struct pending_connection *next;
} PENDING_CONNECTION;


#define TCPIP_CONNECT_NO_SUCH_HOST               -1
#define TCPIP_CONNECT_NOT_INTERNET_HOST          -2
#define TCPIP_CONNECT_CANT_MAKE_SOCKET           -3
#define TCPIP_CONNECT_CANT_MAKE_NONBLOCK_CONNECT -4
#define TCPIP_CONNECT_CANT_MAKE_NONBLOCK_SOCKET  -5  /* not used anywhere */
#define TCPIP_CONNECT_RETRY_SELECT_FAILED        -6
#define TCPIP_CONNECT_FELL_OFF_END               -7
#define TCPIP_CONNECT_WONT_RETRY                 -8
#define TCPIP_CONNECT_EMPTY_HOST                 -9
#define TCPIP_CONNECT_IN_PROGRESS                -99

#define TCPIP_ACCEPT_NONE_PENDING                 0
#define TCPIP_ACCEPT_CANT_MAKE_NONBLOCKING       -4

#define NE_BLOCKED_VALUE 0
#define NE_EOF_VALUE    -1
#define NE_ERROR_VALUE  -2

extern
#ifdef __cplusplus 
	"C" 
#endif
int g2ext_max_number_of_sockets;
