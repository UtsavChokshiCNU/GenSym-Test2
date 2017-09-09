//
// Header file for Connection Structures
//
#ifndef CONNECTIONH
#define CONNECTIONH
#include <iostream_ver.h>
#include <time.h>
#include "gsi_main_cpp.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "iiop.h"
#ifdef WIN32
#include <winsock.h>
#define BAD_SOCKET(fd) (fd == INVALID_SOCKET)
#else
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
typedef int SOCKET;
#define BAD_SOCKET(fd) (fd < 0)
#endif

void kill_socket(SOCKET fd);

#define BUF_SIZE 1024

/*
 * Buffer data 
 */

class socket_buffer : public G2OrbContained {
public:
  unsigned char dat[BUF_SIZE];  /* buffer data */
  int start_idx;    /* index to next char to read */
  int end_idx;      /* index to next char to allocate */
};
  
/*
 * This structure describes everything that is known about a socket.
 * It forms a doubly linked list of socket information.
 */

class socket_data : public G2OrbContained {
public:
  SOCKET fd;      /* file des of socket */
  unsigned char kind;    /* 1= server, 2= connected server,
	               3= connected client, 4= connecting client */
  unsigned char state;   /* 1 = waiting for start, 2 = in message */ 
  unsigned long socket_id; // unique id for socket
  NoHashContainer write_messages; // collection of messages to write.
  time_t timeout_time; /* when to time out */
  NoHashContainer bufs;  // comm buffers for read
  G2String connected_system; // inet address of connected system
  G2OrbContainer private_ids; // id's that are private.

  int copy_socket_data(char *dest, int len, int offset);
  void free_socket_data(int len);
  int get_data_length(void);
  int count_data_buffers(void);
  int find_string_match(char *str, int offset);
  socket_data(void);
  virtual ~socket_data(void);
  virtual gsi_int GetHash(void) {return socket_id;};

};

class socket_map : public G2OrbContained {
public:
	unsigned long socket_id;
	G2String target_system;  // string in form of "host:port"
	virtual char *GetKey(void) {return (char *) target_system; }; 
};


//
// Used to hold a outgoing message.  The header is coded seperatly than the main body
//
class Write_buffer:public G2OrbContained {
public:
	iiop *piiop;
	unsigned long len;
	unsigned long index;	// where are we in writting the message?
	unsigned long req_id; // id of request so we can cancel it
	unsigned char mode;  // 1 = client, 2 = server

    // do not use the pointer from these constructors, it may have been deleted in
    //   the constructor. The write buffer will be placed in a sdata object
    //   automatically.
	//Write_buffer::Write_buffer(iiop *iiopPtr, int connection_id);
	Write_buffer(iiop *iiopPtr, int connection_id);
	//Write_buffer::Write_buffer(iiop *iiopPtr, G2CObject *pObj, G2CRequest *prObj);
	Write_buffer(iiop *iiopPtr, G2CObject *pObj, G2CRequest *prObj);

	virtual ~Write_buffer();
};


#endif

