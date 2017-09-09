//
// This file contains the socket routines for the CORBA project
//


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>

#if defined(hp9000s700) || defined(hp9000s800) || defined(linux)
#include <sys/param.h>
#include <arpa/inet.h>
#endif

#ifdef _AIX
#include <arpa/inet.h>
#include <sys/select.h>
#endif

#include <sys/types.h>

#ifdef WIN32
#include <winsock.h>
#define BAD_SOCKET(fd) (fd == INVALID_SOCKET)
#else
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <string.h>

typedef int SOCKET;
#define BAD_SOCKET(fd) (fd < 0)
#endif


#include "gsi_main_cpp.h"
#include "iiop.h"
#include "connections.h"
#include "corba_main.h"

#define BRIDGE_NAME "G2-SOCKET-MANAGER"
#define BRIDGE_VER "V1.1"
#define KIND_OF_BRIDGE_STRING "Socket Interface Bridge"
#define OS_STRING "generic"

#define MAX_CONTEXT 100
#ifdef nothing
#define AUTH yes
#define AUTH_REQ
#endif
 

unsigned long idle_timeout = 500;
unsigned long client_timeout = 400;
unsigned long server_timeout = 300;
unsigned long connect_timeout = 15;

time_t g_current_time; // Global time value, updated every trip through runloop


//
// Global Data
// 

	G2OrbContainer ContextObjs(50); //  Set of context objects
	G2OrbContainer RequestObjs; // Set of request objects
	G2OrbContainer ServReqObjs; // Set of Server requests
	G2OrbContainer Sockets;		// Set of sockets
	G2OrbContainer Objects(1000);		// Collection of server objects
	G2OrbContainer SocketMaps;  // Set of socket map objects
	G2OrbContainer LocateReqObjs; // Collection of locate request objects

/*
 * Data structures:
 *
 * This is a multiple context bridge.  The bridge may support more than one
 * connection to g2's.  Each context will have a link id string.  The string
 * is is stored in a array of context data.  Also, there will be a array of
 * socket id's and the associated context number.
 *
 */


int debug_mode = 0; /* set to 1 to enable prints */


#ifdef SunOS
void memmove(dest, src, length)

char *dest, *src;
int length;
{
	(void) memcpy(dest, src, length);
}
#endif
/* It's not #ifdef Solaris, really, it's if Solaris and not /usr/ucb/cc ... */


void bzero(char *ptr, int length)
{
	(void) memset(ptr, length, 0);
}


void bcopy(char *source, char *destination, int len)
{
	memcpy(destination, source, len);
}


/* interpret the return code resulting from attempted socket operation */
void get_socket_error(int sock_ret_code)
{


  switch (sock_ret_code) {

#ifdef WIN32
    case WSANOTINITIALISED:
      cout << "A successful WSAStartup must occur before using this function" << endl;
      break;
    case WSAENETDOWN:
      cout << "The network subsystem has failed" << endl;
      break;
    case WSAEADDRINUSE:
      cout << "The specified address is already in use." << endl;
      break;
    case WSAEFAULT:
      cout << "The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains incorrect address format for the associated address family, or the first two bytes of the memory block specified by name does not match the address family associated with the socket descriptor s." << endl; 
      break;
    case WSAEINPROGRESS: 
      cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function." << endl;
      break;
    case WSAEINVAL: 
      cout << "The socket is already bound to an address." << endl;
      break;
    case WSAENOBUFS:
      cout << "Not enough buffers available, too many connections." << endl;
      break;
    case WSAENOTSOCK:
      cout << "The descriptor is not a socket." << endl;
      break;
    case WSAEISCONN:
      cout << "The socket is already connected." << endl;
      break;
    case WSAEMFILE:
      cout << "No more socket descriptors are available." << endl;
      break;
    case WSAEOPNOTSUPP:
      cout << "The referenced socket is not of a type that supports the listen operation." << endl;
      break;
#else
    case ENETDOWN:
      cout << "The network subsystem has failed" << endl;
      break;
    case EADDRINUSE:
      cout << "The specified address is already in use." << endl;
      break;
    case EFAULT:
      cout << "The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains incorrect address format for the associated address family, or the first two bytes of the memory block specified by name does not match the address family associated with the socket descriptor s." << endl; 
      break;
    case EINPROGRESS: 
      cout << "A blocking call is in progress, or the service provider is still processing a callback function." << endl;
      break;
    case EINVAL: 
      cout << "The socket is already bound to an address." << endl;
      break;
    case ENOBUFS:
      cout << "Not enough buffers available, too many connections." << endl;
      break;
    case ENOTSOCK:
      cout << "The descriptor is not a socket." << endl;
      break;
    case EISCONN:
      cout << "The socket is already connected." << endl;
      break;
    case EMFILE:
      cout << "No more socket descriptors are available." << endl;
      break;
    case EOPNOTSUPP:
      cout << "The referenced socket is not of a type that supports the listen operation." << endl;
      break;
#endif
    default: 
      cout << "Unknown socket error" << endl;
      break;
  } 

}

  
/*
 * Look for message start.  If the message start is found, then we
 * start the timer and remove anything before the start of the message.
 * If we have a zero length search string, then it will succeed if we have
 * any data in the buffer.
 */
void look_for_mesg_start(socket_data *ptr)

{
  int startloc;
  int temp;


  temp = ptr->get_data_length();
  if (debug_mode) {
    printf("Looking for message start: %d bytes in buffer\n", temp);
    ptr->count_data_buffers();
  }
  //
  // We look for the start of the IIOP packet
  startloc = ptr->find_string_match((char *)"GIOP", 0);
  if (startloc == -1) return; // could not find message start

  ptr->state = 2; /* looking for end of message */

  if (startloc) { /* flush some chars from the start of the buffer */
    ptr->free_socket_data(startloc); 
  }
}

/*
 * Look  for the end of the IIOP message.  
 * The header is 12 bytes long.  It contains a byte order flag and a message length
 * We need to look at the message length to determine if we have all of the data we need
 */

void look_for_mesg_end(socket_data *ptr)

{
  unsigned long temp;
  unsigned char mesg_header[13];
  unsigned long mesg_len;
  unsigned mesg_type;
  void *iiopmesg;
  unsigned char little_endian;

  temp = ptr->get_data_length();
  if (debug_mode) 
    printf("Looking for message end %d bytes in buffer\n", temp);

  if (temp < 12) return;  // we do not have a complete header yet.
  ptr->copy_socket_data((char *) mesg_header, 12, 0);  // get local copy of header

  little_endian = mesg_header[6];
  if (little_endian) {
	mesg_len = mesg_header[8] | (mesg_header[9] << 8) | (mesg_header[10] << 16) |
		  (mesg_header[11] << 24);
  } else {
	mesg_len = mesg_header[11] | (mesg_header[10] << 8) | (mesg_header[9] << 16) |
		  (mesg_header[8] << 24);
  }
  mesg_type = mesg_header[7];

  if (temp < 12 + mesg_len)
    return; // not all of the data is here yet

  iiopmesg = malloc(mesg_len + 12);
  ptr->copy_socket_data((char *) iiopmesg, mesg_len + 12, 0); 
  ptr->free_socket_data(mesg_len + 12);  // remove it from the buffer

  if (debug_mode) {
	  printf(">> Received a message of type %d, %d bytes long, %s\n",
      (int) mesg_type, (int) mesg_len,
      little_endian ? "little endian" : "big endian");
  }

  process_iiop_message(iiopmesg, mesg_len, little_endian, mesg_type,ptr);
  free(iiopmesg);

  ptr->state = 1;
  return;

}

  

/* entry point */
void parse_buffer(socket_data *ptr)

{
  while (1) {  /* look until we cant find a complete message */
    if (ptr->state == 1) {
      look_for_mesg_start(ptr);
      if (ptr->state == 1) break;  /* could not find message start */
    } 
    if (ptr->state == 2) {
     look_for_mesg_end(ptr);
     if (ptr->state == 2) break; /* could not find message end */
    }
  }
}

//
// reset the idle connection timmer
//
void reset_idle_time(socket_data *sdata)

{
  if (!idle_timeout) sdata->timeout_time = 0;
  else sdata->timeout_time = g_current_time + idle_timeout;
}
 
/*
 * accept a connection from a port.  This will build a new socket entry
 * and make a rpc call to g2 to let it know.
 */

#if defined(Solaris) || defined(SunOS) || defined(OSF1) || (sun)
#include <arpa/inet.h>
#endif

void accept_connection(socket_data *ptr)

{
  SOCKET newfd;
  struct sockaddr_in cli_addr;
#if defined(rs6000)
  size_t clilen; /* for AIX 4.3 & linux */
#elif defined(linux)
  socklen_t clilen;
#else
  int    clilen; /* for all other platforms including AIX 4.1 */
#endif
  socket_data *sdata;
  char *addr;

  clilen = sizeof(cli_addr);
  newfd = accept(ptr->fd, (struct sockaddr *) &cli_addr, &clilen);
  printf("Accepted socket:%d\n", newfd);
  if (!BAD_SOCKET(newfd)) {
    addr = (char *) inet_ntoa(cli_addr.sin_addr); /* get dotted address */
    printf("Connected from %s\n", addr);
    gsi_watch_fd(newfd);  
    if (debug_mode) cout << "Watching:" << newfd << endl;
//	gsi_watch_fd_for_writing(newfd);
    sdata = new socket_data();
    sdata->fd = newfd;
    sdata->kind = 2;
    sdata->state = 1;
	sdata->connected_system = addr;
	reset_idle_time(sdata);
  }
}


/* 
 * read a buffer full of data
 */

void read_buffer(socket_data *ptr)

{
  socket_buffer *sbuf;
  int temp;

  if (debug_mode) printf("Reading a buffer on %d\n", ptr->fd);
  reset_idle_time(ptr);
  sbuf = new socket_buffer;
  ptr->bufs.Add(sbuf);
#ifdef WIN32
  temp = recv(ptr->fd, (char *) sbuf->dat, BUF_SIZE - 1, 0);
#else
  temp = read(ptr->fd, sbuf->dat, BUF_SIZE - 1);
#endif
  if (debug_mode) printf("Read got %d characters\n", temp);
  if (debug_mode) {
	  for (int i = 0; i < temp; i++) printf("%02x ",(unsigned) sbuf->dat[i]);
  }
  if (!temp) { /* got end of file. */
    Sockets.Remove(ptr);
  } else if (temp < 0) { /* got error on socket */
    if (ptr->kind == 4) { /* error while connecting */
		cout << "Error while connecting" << endl;
    }
    Sockets.Remove(ptr);
  } else {
    sbuf->start_idx = 0;
    sbuf->end_idx = temp; 
    parse_buffer(ptr);
  }
}



/*
 * Here we look at all open sockets for activity.  This does a select
 * to look to see if any of the sockets have data that is ready to
 * be sent to g2.  This will ready the data, and if a full message is
 * there, it will be sent via rpc.
 */
#ifdef AIX
#include <sys/select.h>
#include <isode/manifest.h>
#endif

/* build a fd list, dont include paused connections */
SOCKET set_fd_bits(fd_set *ptr, int kind)

{
  socket_data *sdata;
  SOCKET big;

  big = 0;
  FD_ZERO(ptr);
  for (sdata = (socket_data *) Sockets.GetFirst(); 
	sdata; sdata = (socket_data *) sdata->GetNext()) {
    if (kind == -1) {  // read fds
      FD_SET(sdata->fd, ptr);
      if (sdata->fd > big) big = sdata->fd;
	  // also add the G2 sockets
    }
    if (kind == -2) {  // We only care if we have to write
	  if (sdata->kind == 1) continue;  // dont worry about writting to the listener
      if (sdata->kind == 2 && !sdata->write_messages.Count) continue;
      if (sdata->kind == 3 && !sdata->write_messages.Count) continue;
      FD_SET(sdata->fd, ptr);
      if (sdata->fd > big) big = sdata->fd;
    }
  }
  return big;
}

/* show fd list */
void show_fd_list(fd_set *ptr)

{
  socket_data *sdata;

  for (sdata = (socket_data *) Sockets.GetFirst(); 
	sdata; sdata = (socket_data *) sdata->GetNext()) {
    if (FD_ISSET(sdata->fd, ptr)) 
		printf("%d ", sdata->fd);
  }
}

/*
 * Handle readble fds
 * There must be a message on the port.
 */
void process_read_fds(fd_set *fds)

{
  socket_data *sdata, *nsdata;

  for (sdata = (socket_data *) Sockets.GetFirst(); sdata; sdata = nsdata) {
	nsdata = (socket_data *) sdata->GetNext();
    if (FD_ISSET(sdata->fd, fds)) { /* read buffer */
      if (debug_mode) printf("Socket %d is readable, kind is %d\n", sdata->fd, sdata->kind);
      if (sdata->kind == 1) accept_connection(sdata); /* got connection */
      else read_buffer(sdata);
    }
  }    
}

/*
 * Handle writable fds.  if we have something to write, then send it 
 */

void process_write_fds(fd_set *fds)

{
  socket_data *sdata;
  int temp;

  for (sdata = (socket_data *) Sockets.GetFirst(); sdata; 
		sdata = (socket_data *) sdata->GetNext()) {
    if (FD_ISSET(sdata->fd, fds)) {
      if (debug_mode) 
		printf("Socket %d is writeable, kind is %d\n", sdata->fd, sdata->kind); 
      if (sdata->kind == 4) { /* socket connected, tell g2. */
	    printf("Client connection completed!\n");
	    sdata->kind = 3; /* connected socket */
      }

	  Write_buffer *wObj, *nwObj;
	  for (wObj = (Write_buffer *) sdata->write_messages.GetFirst();
			wObj; wObj = nwObj) {
	    reset_idle_time(sdata);
		if (debug_mode) cout << "Sending buffer" << endl;
		nwObj = (Write_buffer *) wObj->GetNext();
		// We have a write buffer to send.  Send all that we can
	   int len = wObj->len - wObj->index;
	   if (len) {
#ifdef WIN32
		temp = send(sdata->fd, (char *) wObj->piiop->data_ptr, len, 0);
#else
		temp = write(sdata->fd, wObj->piiop->data_ptr, len);
#endif
		if (temp < 0) {
    		perror("Error writting to socket:"/* , errno */);
			continue;
		} else {
			wObj->index += temp;  // bump pointer
		}
	   } // if len
	   len = wObj->len - wObj->index;  // anything left?
	   if (!len) { // no, done with buffer 
	     if (wObj-> mode == 1) { // client request
		   G2CRequest *rObj = (G2CRequest *) RequestObjs.FindObj(wObj->req_id);
		   if (rObj) request_sent(rObj);
		 }
		 sdata->write_messages.Remove(wObj); // remove write buffer
	   } 
	  } /* for wObj */
	} // if fd set
  } /* for sdata */
}


/* 
 * Handle socket exceptions.  If we get an exception on a socket,
 * shut it down.
 */

void process_except_fds(fd_set *fds)

{
  socket_data *sdata, *nsdata;

  for (sdata = (socket_data *) Sockets.GetFirst(); sdata; sdata = nsdata) {
	nsdata = (socket_data *) sdata->GetNext();
    if (FD_ISSET(sdata->fd, fds)) { /* read buffer */
      if (debug_mode) printf("Socket %d has exception, kind is %d\n", sdata->fd, sdata->kind);
      if (sdata->kind == 1) {
		  cout << "Exception on listener socket!" << endl;
		  exit(1);
	  }
      else Sockets.Remove(sdata);  // kill it
    }
  }    
}



/* show count of socket structures in list */
void show_socket_count()

{
  socket_data *ptr;
  int n;

  n = 0;
  for (ptr = (socket_data *) Sockets.GetFirst(); ptr; ptr = (socket_data *) ptr->GetNext()) {
    if (debug_mode) {
      printf("fd: %d, kind: %d\n", ptr->fd, ptr->kind);
    }
    n++;
  }
  printf("Number of socket structs:%d\n", n);
}

/*
 * Look for timeouts.  Writes can not time out, but connections
 * can.  We drop a connection after several minutes of no activity
 * Also, establishing a connection may timeout.  If we timeout, then
 * we drop the connection and reject any requests that are pending on 
 * the connection.
 */

void process_timeouts()

{
  socket_data *sdata, *nsdata;

  for (sdata = (socket_data *) Sockets.GetFirst();
		sdata; sdata = nsdata) {
	nsdata = (socket_data *) sdata->GetNext();
    if (!sdata->timeout_time) continue; /* no timeout */
	if (sdata->kind == 1) continue; // server, no timeout
    if (g_current_time > sdata->timeout_time) { /* timed out */
      printf("Timeout! id: %d, kind: %d\n",(char *) sdata->fd, (int) sdata->kind);
	  Sockets.Remove(sdata);  // kill socket
    }
  }
}


/* scan the sockets */
void check_sockets()

{
  fd_set readfds, writefds, exceptfds;
  struct timeval timeout;
  int maxfd;
  int nfd;

//  if (debug_mode) show_socket_count();
  set_fd_bits(&readfds,-1);
  set_fd_bits(&writefds,-2);
  maxfd = set_fd_bits(&exceptfds,-1);
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

//  if (debug_mode) printf("Selecting...\n");

  nfd = select(maxfd+1, &readfds, &writefds, &exceptfds, &timeout);
//  if (debug_mode) printf("Select returned %d\n", nfd);

  time(&g_current_time);  // there may have been a delay, update the time

  if (nfd > 0) { 

//	if (debug_mode) { 
//	  printf("Read ready sockets:");
//	  show_fd_list(&readfds);
//	  printf("\nWrite ready sockets:");
//	  show_fd_list(&writefds);
//	  printf("\nExceptions on:");
//	  show_fd_list(&exceptfds);
//	  printf("\n");
//	}

	process_read_fds(&readfds);
	process_write_fds(&writefds);
	process_except_fds(&exceptfds);
  }
  process_timeouts();
  timeout_serv_req();
  timeout_client_req();
}


/*
 * Main run loop.  Look for activity over any of the sockets and call
 * G2 rpc's if we get messages.
 */

void main_loop()

{
  while (1) { /* Never exit */
    gsi_run_loop(); /* give gsi a chance to look for g2 */
	  check_sockets();
	  gsi_pause();
  }
}

//
// Create the listener socket.  This is used to accept connections from clients
// If this fails, then we abort the bridge, since it can not run without this.
//

void create_listener(unsigned port_number)

{
#ifdef WIN32
  unsigned long block_flag = 1;
#endif
  struct sockaddr_in serv_addr;
  int temp;
	
  SOCKET fd = socket(AF_INET, SOCK_STREAM, 0);
  if (BAD_SOCKET(fd)) {
    cout << "Unable to open listener socket" << endl;
    get_socket_error(fd);
	  exit(1);
  }

#ifdef WIN32
  temp = ioctlsocket(fd, FIONBIO, &block_flag);
#else
  temp = fcntl(fd, F_SETFL, O_NDELAY); /* set non-blocking */
#endif
  if (temp == -1) {
    cout << "Unable to set non-blocking" << endl;
    get_socket_error(temp);
	  exit(1);
  }

  bzero((char *) &serv_addr, (int)sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons((unsigned short) port_number);

  temp = bind(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
  if (temp < 0) {
    cout << "Unable to bind socket" << endl;
#ifdef WIN32
    temp = WSAGetLastError() ;
    get_socket_error(temp);

#else

    get_socket_error(errno) ;
#endif
	exit(1);
  }
  temp = listen(fd, 5); /* wait for connection */
  if (temp < 0) {
    cout << "Unable to listen for connections" << endl;  // ~~~
    get_socket_error(temp);
	  exit(1);
  }
  gsi_watch_fd(fd); /* let gsi look for a connection */
  if (debug_mode) cout << "Watching:" << fd << endl;
//  gsi_watch_fd_for_writing(fd);
  socket_data *sdata = new socket_data();   //////// ~~ check this
  sdata->fd = fd;
  sdata->kind = 1;  // server socket
  sdata->state = 1;	// waiting for connection
  sdata->timeout_time = -1;
  cout << endl << "Created listener on port " << port_number << endl << endl;
}


//
// Create a connection to the target system.
// returns 1 if error
//
socket_data *create_connection(char *system_name, unsigned port_number)

{
  SOCKET fd;
  struct sockaddr_in tcp_srv_addr;
  unsigned long inaddr;
  int temp;
#if !defined(linux)
  struct hostent *hp;
#else
  struct addrinfo hints, *result;
  struct sockaddr_in *result_in;
  int error;
#endif
  socket_data *sdata;
#ifdef WIN32
  unsigned long block_flag = 1;
#endif

  /* create socket */

  printf("Connecting to %s at %d\n", system_name, port_number);
  bzero((char *) &tcp_srv_addr, (int)sizeof(tcp_srv_addr));
  tcp_srv_addr.sin_family = AF_INET;
  tcp_srv_addr.sin_port = htons((unsigned short) port_number);
  inaddr = inet_addr(system_name); /* dotted notation */
/* Confirm what POSIX now says.
  if (inaddr != INADDR_NONE) {
*/
  if (inaddr != -1 ) {
    bcopy((char *) &inaddr, (char *) &tcp_srv_addr.sin_addr, (int)sizeof(inaddr));
  } else {
#if !defined(linux)
    hp = gethostbyname(system_name); /* name lookup */
    if (hp) {
      bcopy(hp->h_addr, (char *) &tcp_srv_addr.sin_addr, hp->h_length);
    } else {
      printf("Unable to look up %s\n", system_name);
      return NULL;
    }
#else
    /* LSB requires using getaddrinfo() instead of gethostbyname */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_CANONNAME;
    hints.ai_family = AF_INET;
    error = getaddrinfo(system_name, "domain", &hints, &result);
  
    if (error == 0) {
      result_in = (struct sockaddr_in*) result->ai_addr;
      memcpy(&(tcp_srv_addr.sin_addr),&(result_in->sin_addr),result->ai_addrlen);
      tcp_srv_addr.sin_family = result->ai_family;
      freeaddrinfo(result);
    } else {
      printf("Unable to look up %s (error: %s)\n", system_name, gai_strerror(error));
      return NULL;
  }
#endif
  }

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (BAD_SOCKET(fd)) {
    return NULL;
  }

#ifdef WIN32
  temp = ioctlsocket(fd, FIONBIO, &block_flag);
#else
  temp = fcntl(fd, F_SETFL, O_NDELAY); /* set non-blocking */
#endif
  if (temp == -1) {
    printf("Unable to set non-blocking\n");
    return NULL;
  }
#ifdef WIN32
  int delay_flag = 1;
  temp = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &delay_flag, sizeof(int));
  if (temp) {
	  printf("Unable to set no delay\n");
	  return NULL;
  }
#endif
  temp = connect(fd, (struct sockaddr *) &tcp_srv_addr, sizeof(tcp_srv_addr));
  if (temp < 0) {
#ifdef WIN32
	if (WSAGetLastError() != WSAEWOULDBLOCK) {
#elif defined (sun)
	if (errno != 150) { // we expect a connection to block
#elif defined(_AIX) || defined(linux)
	if (errno != EINPROGRESS) { // operation is in progress
#else
	if (errno != 245 ) { /* we expect the connection to block */
#endif
      perror("Unable to connect: \n"/* , errno */);
      return NULL;
    } 
  }

  if (debug_mode) gsi_watch_fd(fd);  cout << "Watching:" << fd << endl;
//  gsi_watch_fd_for_writing(fd);
  sdata = new socket_data(); /* create new data structure */
  sdata->fd = fd;
  sdata->kind = 4; /* connecting client */
  sdata->state = 1;
  sdata->connected_system = (char *) inet_ntoa(tcp_srv_addr.sin_addr);
  if (!connect_timeout) sdata->timeout_time = 0;
  else sdata->timeout_time = g_current_time + connect_timeout;
  return sdata; // ok
}


/*
 * Remove a socket and data structure
 */

void kill_socket(SOCKET fd)

{
///  if (debug_mode) gsi_unwatch_fd(fd);  cout << "Unwatching:" << fd << endl;
 if (debug_mode) cout << "Unwatching (kill_socket):" << fd << endl;

gsi_unwatch_fd(fd);  // ~~needed to prevent endless loop

//  gsi_unwatch_fd_for_writing(fd);
#ifdef WIN32
  closesocket(fd);
#else
  close(fd);
#endif
}


/* empty function handler for functions that are started */
void null_func(gsi_item *rpc_arguments, gsi_int count)

{
}





#ifdef nothing

/*
 * Custom error handler.  This will just exit.  If the process is
 * in the /etc/inittab file, then the program will respawn.
 */
void handle_error(gsi_int error_context, gsi_int error_code, char *error_message)

{
  struct socket_data *sdata;
  struct socket_data *nsdata;
  int temp;

  printf("Error traped in context %d:%s\n", error_context, error_message);
  if (error_context != -1)  {
    remove_context_data(error_context);
    gsi_kill_context(error_context);
  }
  else {
    for (sdata = first_socket;sdata;sdata = nsdata) {  /* kill every context */
	  nsdata = sdata->flink;
      temp = sdata->context;
      remove_context_data(temp);
      gsi_kill_context(temp);
    }
  }
}
#endif

#ifdef nothing
/*
 * If G2 is paused, then it can not respond to requests.  So, rather than
 * bog it down in a lot of stacked up rpc calls, we will igonore the socket
 * while G2 is pased.
 */

void gsi_pause_context()

{
  struct socket_data *sdata;

  for (sdata = first_socket; sdata; sdata = sdata->flink) {
    if (sdata->context == current_context) {
//      if (debug_mode) gsi_unwatch_fd(sdata->fd);cout << "Unwatching:" << sdata->fd << endl;
      if (debug_mode) cout << "Unwatching (pause_context):" << sdata->fd << endl;

gsi_unwatch_fd(sdata->fd);  // ~~required to prevent endless loop
//	  gsi_unwatch_fd_for_writting(sdata->fd);
      sdata->context_paused = 1;
    }
  }
  printf("Paused context: %d\n", current_context);

}

void gsi_resume_context()

{
  struct socket_data *sdata;

  for (sdata = first_socket; sdata; sdata = sdata->flink) {
    if (sdata->context == current_context) {
      gsi_watch_fd(sdata->fd);
      if (debug_mode) cout << "Watching:" << sdata->fd << endl;
//	  gsi_watch_fd_for_writting(sdata->fd);
      sdata->context_paused = 0;
    }
  }
  printf("Resuming context: %d\n", current_context);
}

void gsi_shutdown_context()

{
  struct socket_data *sdata;
  struct socket_data *nsdata;

  printf("Shuting down context %d\n", current_context);
  for (sdata = first_socket; sdata; sdata = nsdata) {
    nsdata = sdata->flink;
    if (sdata->context == current_context) {
      if (debug_mode) cout << "Unwatching (shutdown-context): " << sdata->fd << endl;
      gsi_unwatch_fd(sdata->fd);
//	  gsi_unwatch_fd_for_writting(sdata->fd);
#ifdef WIN32
      closesocket(sdata->fd);
#else
	  close(sdata->fd);
#endif
      printf("Removed socket: %s\n", sdata->ref_id);
      remove_socket_data(sdata);
    }
  }
}

#endif



