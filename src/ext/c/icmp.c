/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      icmp.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   yduJ
 +
 + Description: This module contains the ICMP network functions for
 +              ping and traceroute.
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if defined(WIN32)
/* we need to use Winsock 2 for ICMP, and it turns out that if we include it
   first, then other include files such as stdio will do the right thing,
   whereas if we allow them to be included first, Winsock 2 explodes. */
#   include <winsock2.h>
#   include <ws2tcpip.h>
#   include "msincls.h"
#endif

#include "cprim.h"
#include "networks.h"
#include "netevent.h"
#include <errno.h>

#if !defined(_WINSOCKAPI_)
#  include <stdlib.h>
#  include <sys/types.h>
#  include <sys/ioctl.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <netinet/ip.h>
#  include <netinet/tcp.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#  include <netdb.h>
#  include <string.h>
#endif

#include "icmp.h"

extern long g2pvt_tcpip_set_nodelay(long listener_socket);
extern long g2pvt_initialize_network_interface();
extern int g2ext_allocate_socket_index(unsigned s /* a socket identifier */);

/*****************************************************************************
 * long g2ext_icmp_open(char *host, char *dotted_addr, int buflen)
 *
 *   Description:
 *     Opens a raw TCP socket for ICMP requests, and associates it with a 
 *     network handle.
 *   Input Arguments:
 *     host: the host to eventually be connected to for this.  Connection is not
 *     actually made at this time, but host information from gethostbyname is
 *     copied to the nw_raw slot.
 *   Output Arguments:
 *     dotted_addr: we translate the raw host information to dotted notation for
 *     ease of comparison in return packets.
 *   Returns: 
 *     return value:The handle
 *****************************************************************************/
extern int g2pvt_snprintf();

/* deal with errno/WSAGetLastError dichotomy for error messages.  Todo: get the
   error message out of WSA.  But that's a fair bit of work. */
#if defined(_WINSOCKAPI_)
#define ICMP_ERROR_MESSAGE(buffer, buflen, message) g2pvt_snprintf(buffer, buflen, message ":  Error code %d", WSAGetLastError());
#else
#define ICMP_ERROR_MESSAGE(buffer, buflen, message) g2pvt_snprintf(buffer, buflen, message ":  %s", strerror(errno));
#endif
long g2ext_icmp_open(char *host, char *dotted_addr, int buflen)
{
  long tcp_handle;
  struct protoent *prot;
  G2pointer ni_g2pointer;
  NETWORK_INTERFACE * ni;
#if !defined(linux)
  struct hostent *hostdata;
#else
  struct addrinfo hints, *result;
  struct sockaddr_in *result_in;
#endif
  struct sockaddr_in *addr;
  unsigned char *data;

#if !defined(linux)
  hostdata = gethostbyname(host);

#if defined(_WINSOCKAPI_)
  if (!hostdata) {
    ICMP_ERROR_MESSAGE(dotted_addr, buflen, "Failed to resolve hostname");
    return ICP_FAIL;
  }
#else
  if (!hostdata) {
    switch (h_errno) {
    case HOST_NOT_FOUND:
      /* most common case */
      g2pvt_snprintf(dotted_addr, buflen, "Host not found");
      break;
    case TRY_AGAIN:
      g2pvt_snprintf(dotted_addr, buflen, "Host not found (non-authoritative)");
      break;
    case NO_RECOVERY:
      g2pvt_snprintf(dotted_addr, buflen, "Non-recoverable error");
      break;
    case NO_DATA:
      g2pvt_snprintf(dotted_addr, buflen, "Valid name but no address information");
      break;
    }
    return ICP_FAIL;
  }
#endif

#else /* defined(linux) */
  /* GENSYMCID-453: Fix all LSB compatibility issues of the Gensym Linux bundle */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_flags = AI_CANONNAME;
  hints.ai_family = AF_INET;

  if (getaddrinfo(host, "domain", &hints, &result) != 0) {
    switch (h_errno) {
    case HOST_NOT_FOUND:
      /* most common case */
      g2pvt_snprintf(dotted_addr, buflen, "Host not found");
      break;
    case TRY_AGAIN:
      g2pvt_snprintf(dotted_addr, buflen, "Host not found (non-authoritative)");
      break;
    case NO_RECOVERY:
      g2pvt_snprintf(dotted_addr, buflen, "Non-recoverable error");
      break;
    case NO_DATA:
      g2pvt_snprintf(dotted_addr, buflen, "Valid name but no address information");
      break;
    }
    return ICP_FAIL;
  }
#endif

  addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

  if (NULL == addr) {
    ICMP_ERROR_MESSAGE(dotted_addr, buflen, "Out of memory");
    return ICP_FAIL;
  }

#if !defined(linux)
  memcpy(&(addr->sin_addr),hostdata->h_addr,hostdata->h_length);
  addr->sin_family = hostdata->h_addrtype;
#else
  result_in = (struct sockaddr_in*) result->ai_addr;
  memcpy((char*) &(addr->sin_addr),
	 (char*) &(result_in->sin_addr),
	 sizeof(struct in_addr));
  addr->sin_family = result->ai_family;
#endif

  data = (unsigned char *)&(addr->sin_addr);

  g2pvt_snprintf(dotted_addr, buflen, "%u.%u.%u.%u", data[0], data[1], data[2], data[3]);

  prot = getprotobyname("icmp");
  if (prot == NULL) {
    free(addr);
    ICMP_ERROR_MESSAGE(dotted_addr, buflen, "Can't get protocol");
    return ICP_FAIL;
  }

#if defined(_WINSOCKAPI_)
  tcp_handle = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);
#else
  tcp_handle = socket(AF_INET, SOCK_RAW, prot->p_proto);
#endif

  if (tcp_handle < 0) {
    free(addr);
    ICMP_ERROR_MESSAGE(dotted_addr, buflen, "Can't open socket");
    return ICP_FAIL;
  }
  g2pvt_tcpip_set_nodelay(tcp_handle);
 
# if defined(_WINSOCKAPI_)
    g2ext_allocate_socket_index(tcp_handle);
# endif

  ni_g2pointer = g2pvt_initialize_network_interface(ICMP, tcp_handle, host, ICMP_INTERFACE_STATUS, 0);

  ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer (ni_g2pointer);

  ni->nw_raw = (unsigned char *)addr;

  return ni_g2pointer;
}

/*****************************************************************************
 * short g2pvt_in_cksum(int icmp_socket, char *buffer, long buflen)
 *
 *   Description:
 *       Turns out we have to write our own checksum routine.  So...
 *
 * From the web, http://www.ping127001.com/pingpage.htm and ping.shar:
 * Mike Muuss' in_cksum() function
 * and his comments from the original
 * ping program
 * Author -
 *	Mike Muuss
 *	U. S. Army Ballistic Research Laboratory
 *	December, 1983
 *
 * Checksum routine for Internet Protocol family headers
 *
 *****************************************************************************/

static u_short g2pvt_in_cksum(u_short *addr, int len)
{
  register int nleft = len;
  register u_short *w = addr;
  register u_short answer;
  register int sum = 0;

  /*
   *  Our algorithm is simple, using a 32 bit accumulator (sum),
   *  we add sequential 16 bit words to it, and at the end, fold
   *  back all the carry bits from the top 16 bits into the lower
   *  16 bits.
   */
  while( nleft > 1 )  {
    sum += *w++;
    nleft -= 2;
  }

  /* mop up an odd byte, if necessary */
  if( nleft == 1 ) {
    u_short	u = 0;

    *(u_char *)(&u) = *(u_char *)w ;
    sum += u;
  }

  /*
   * add back carry outs from top 16 bits to low 16 bits
   */
  sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
  sum += (sum >> 16);			/* add carry */
  answer = ~sum;			/* truncate to 16 bits */
  return (answer);
}


/*****************************************************************************
 * long g2ext_icmp_write(int icmp_socket, int ttl, int id, int seq,
 *                       char *buffer, long buflen)
 *
 *   Description:
 *     Constructs and writes an ICMP buffer to the socket.  The host information
 *     for connection is in ne_current_network_interface->nw_raw.
 *   Input Arguments:
 *     icmp_socket:  the socket handle
 *     ttl: The 'time-to-live' of the packet.  If 0, leaves it up to system default.
 *     id: the ID of the request
 *     seq: the sequence number of the request
 *     buffer: The data portion of the outgoing socket
 *     userbuflen:  length of user data in the buffer
 *     totalbuflen: total length of actual buffer, useful when we return an 
 *     error message in the space (user data length might be too small.)
 *   Returns: 
 *     return value:number of bytes written (what sendto returns) or ICP_FAIL
 *****************************************************************************/

long g2ext_icmp_write(G2pointer ni_handle, int ttl, int id, int seq,
		      char *buffer, long userbuflen, long totalbuflen)
{
  struct icmp *header;
  char outbuffer[1024];
  char *ptr;
  int success, total;
  NETWORK_INTERFACE *ni;
  int fd;

  ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(ni_handle);

  fd = ni->handle;

  /* Construct the ICMP headers. */
  header = (struct icmp *) outbuffer;
  header->icmp_type = ICMP_ECHO;
  header->icmp_code = 0;
  header->icmp_cksum = 0;
  header->icmp_id = id;
  header->icmp_seq = seq;
  
  ptr = outbuffer + sizeof(*header);
  
  memcpy(ptr, buffer, userbuflen);

  total = sizeof(*header) * sizeof(int);

  /* While the checksum claims to understand odd sizes, I got a crash when I 
     gave it an odd length.  So, make sure it's even. */
  if (total % 2 != 0)
    total++;

  header->icmp_cksum = g2pvt_in_cksum((u_short *)header,total);

  if (ttl) {
    success = setsockopt(fd, IPPROTO_IP, IP_TTL, (const char *)&ttl, sizeof(ttl));
    if (success < 0) {
      /* reuse the user buffer for this error message. */
      ICMP_ERROR_MESSAGE(buffer, totalbuflen, "setting TTL option");
      return ICP_FAIL;
    }
  }

  /* Send off the packet */
  success = sendto(fd, outbuffer, total, 0, (struct sockaddr *) ni->nw_raw, sizeof(struct sockaddr));

  if (success < 0) {
    /* reuse the user buffer for this error message. */
    ICMP_ERROR_MESSAGE(buffer, totalbuflen, "sendto");
    return ICP_FAIL;
  }
  ne_enable_read_events(ni_handle);
  return success;
}

/*****************************************************************************
 * long g2ext_icmp_read(int icmp_socket, char *buffer, long buflen,
 *                      char *from, long fromlen, unsigned short *seqid)
 *
 *   Description:
 *     Reads an ICMP packet from the socket.
 *   Input Arguments:
 *     icmp_socket:  the socket handle
 *     buffer:  Buffer in which to store the data portion of the received packet
 *     buflen:  length of provided buffer
 *     frombuf: buffer to store the orginating IP address of the received packet
 *     fbuflen: length of same
 *     seqid:  a 3 element 16 bit array for returning the ID and Sequence 
 *   Returns: 
 *     buffer: data portion, whatever was included in the original ping 
 *             write request
 *     seqid: The sequence, ID, and TTL from the ICMP, either the real one from
 *            a regular return, or the inner ICMP from a ICMP_TIMXCEED packet.
 *     from:   null terminated string representing the dotted IP address
 *     return value:number of bytes read in the data portion.
 *****************************************************************************/

/* I had trouble with the results from recvfrom when I used a stack-allocated
   structure.  So make a variable here and malloc when needed. */
static struct sockaddr_in *fromaddr = NULL;

/* The inner ICMP from a TIMXCEED packet is the minimum size, not including any
   extra stuff that some platforms include.  So can't use sizeof(struct icmp).*/
#define BASE_ICMP_SIZE 8

long g2ext_icmp_read(G2pointer ni_handle, char *buffer, long buflen, char* frombuf, long fbuflen, unsigned short *seqid)
{
  int success, fromlen;
  struct ip *ipheader_in;
  struct icmp *header_in;
  unsigned char * data;
  NETWORK_INTERFACE  *ni;
  long typecode;
  int fd;
  struct icmp *inner_icmp;
  struct ip *inner_ip;
  
  if (fromaddr == NULL)
    fromaddr = (struct sockaddr_in*)calloc(sizeof(struct sockaddr_in),1);
  fromlen = sizeof(struct sockaddr_in);

  ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(ni_handle);

  fd = ni->handle;

  /* Use the user's buffer for data receipt.  Includes header. */
  success = recvfrom(fd, buffer, buflen, 0, (struct sockaddr *) fromaddr, &fromlen);

  if (success < 0) {
    /* deal with errno/WSAGetLastError dichotomy; windows doesn't define the
       same symbols */
#if !defined(_WINSOCKAPI_)
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK) || (errno == EINPROGRESS))
#else
    if (WSAGetLastError() == WSAEWOULDBLOCK)
#endif
      return NE_EOF_VALUE; /* can't use NE_BLOCKED, because 0 is a valid response */
    else
      return NE_ERROR_VALUE;
  }

  /* extract the from IP. */
  data = (unsigned char *)&(fromaddr->sin_addr);

  g2pvt_snprintf(frombuf, fbuflen, "%u.%u.%u.%u", data[0], data[1], data[2], data[3]);

  /* decode the header */
  ipheader_in =  (struct ip *) buffer;
  
  header_in = (struct icmp *) (buffer + (ipheader_in->ip_hl << 2));
    
  typecode = header_in->icmp_type;

  data = (unsigned char *)header_in + sizeof(*header_in);

  if (typecode == ICMP_TIMXCEED) {
          
    inner_ip = (struct ip *) (((char *) header_in) + BASE_ICMP_SIZE);

    inner_icmp = (struct icmp *) (((char *)inner_ip) + (inner_ip->ip_hl << 2));

    seqid[0] = inner_icmp->icmp_id;
    seqid[1] = inner_icmp->icmp_seq;
    seqid[2] = inner_ip->ip_ttl;
  } else {
    seqid[0] = header_in->icmp_id;
    seqid[1] = header_in->icmp_seq;
    seqid[2] = ipheader_in->ip_ttl;
  }

  /* Copy the data portion over the header portion; important bits from headers 
     have been extracted into seqid. */
  memcpy(buffer, data, buflen - ((long)data - (long)buffer));

  /* Enable more read events on this socket.  They've been disabled and we'll
     never get another chance to read anything if we don't. */
  ne_enable_read_events(ni_handle);

  return typecode;
}
