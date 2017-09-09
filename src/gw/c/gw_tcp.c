/* gw_tcp.c -- Misc TCP routines used in gw
 *     This file is compiled into libgw.a, and loaded into Lisp, as well as used
 *     in runtime images.
 */

#include <errno.h>
#include <signal.h>

#include "cprim.h"
#include "networks.h"

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>
#include <sys/types.h>

#if !defined(WIN32)
#  include <sys/ioctl.h>
#  include <sys/socket.h>
#  include <sys/time.h>
#  include <netinet/in.h>
#  include <netinet/tcp.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#  include <netdb.h>
#endif

#if defined(_IBMR2)
#   include <sys/select.h>
#endif

#if defined(WIN32)
#   include <winsock.h>
#   include <io.h>
#   include "msincls.h"
#   define NO_FLAGS_SET	0	/* Used with send()/recv() */
#endif

#include "gw_main.h"


#ifdef GSI41
extern long g2ext_tcpip_connection_check();
#endif


int enable_hostname_lookups = 0;

int gw_fetch_errno()
{
#  if defined(_WINSOCKAPI_)
     return WSAGetLastError()-WSABASEERR;
#  else
     return errno;
#  endif
}

int gw_socket_write(sock, buf, start, end)
int sock;
char *buf;
int start;
int end;
{
  if (start < end) {
#  if defined(_WINSOCKAPI_)
    return send(sock, buf + start, end - start, NO_FLAGS_SET);
#  else
    return write(sock, buf + start, end - start);
#  endif
  }
  return -1;
}

int gw_socket_read(sock,buf,n)
int sock;
char *buf;
int n;
{
#  if defined(_WINSOCKAPI_)
     return recv(sock, buf, n, NO_FLAGS_SET);
#  else
     return read(sock, buf, n);
#  endif
}

int gw_socket_poll_status(socket)
	int socket;
{ 
    int optlen = sizeof(int);
    fd_set   descriptor_bits;
    int error_var = 0;
    int errstat = 0;
    struct timeval select_poll;

#   if defined(_WINSOCKAPI_)
       errstat = WSAGetLastError();
       select_poll.tv_sec =  0;
       select_poll.tv_usec = 0;
       FD_ZERO(&descriptor_bits);
       FD_SET(socket, &descriptor_bits);

       if ((select((int)(socket + 1), NULL, NULL, &descriptor_bits, 
		   &select_poll)) >= 0)
	   if ( FD_ISSET(socket, &descriptor_bits) )
	       error_var = 1;

       WSASetLastError(errstat);
#   else
       if (getsockopt(socket, SOL_SOCKET, SO_ERROR, (void *)&error_var, &optlen) != 0)
	   error_var = errno;
#   endif

    return (error_var);
}


int gw_socket_data_available_p(sock)
	int sock;
{
  fd_set readmask;
  struct timeval timeout;

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  FD_ZERO(&readmask);
  FD_SET(sock,&readmask);

  select(1 + sock, &readmask, NULL, NULL, &timeout);
  if (FD_ISSET(sock,&readmask))
    return 1;
  else
    return 0;
}


/* */
int gw_flush_console_streams()
{
  fflush(stderr);
  fflush(stdout);
  return 0;
}

 
/*************************************************************
 * gw_tcpip_connection_check is the one remaining gsi 4.x API function that is
 * still called by weblink, from web.c.  Think about making it go away sometime.
 * yduJ, Mar. 2004
 *************************************************************/

/*************************************************************
 * gw_tcpip_connection_check
 *
 * Compare with g2ext_check_connect in ext/c/networks.c.  Perhaps this function
 * should not exist.
 *************************************************************/
long gw_tcpip_connection_check (connect_socket)
     int connect_socket;
{      
#ifdef GSI41
  return g2ext_tcpip_connection_check(connect_socket);
#else
  return 0L;
#endif
}
