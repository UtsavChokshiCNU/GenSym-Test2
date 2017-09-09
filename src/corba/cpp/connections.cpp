

//
// Connection Structure Methods
//

//
//  cpp dependencies:
//      G2Container.cpp
//      G2CorbaContainer.cpp
//      iiop.cpp
//
#include <stdio.h>
#include <iostream_ver.h>
#include <string.h>
#include "G2ContainerClass.h"
#include "connections.h"
#include "corba_main.h"


unsigned long next_socket_id = 1;

/* copy N characters from buffer */
/* copy data from buffers for socket to linear array, returns number of bytes copied */

int socket_data::copy_socket_data(char *dest, int len, int offset)

{
  int left;
  int copied;
  int in_buf;
  int to_skip;
  socket_buffer *buf;

  if (debug_mode) 
    printf("copy %d bytes from offset %d\n", len, offset);
  copied = 0;
  buf = (socket_buffer *) bufs.GetFirst();  /* pointer to first buffer for socket */
  to_skip  = offset;
  while (to_skip > 0) { /* skip offset bytes */
    if (!buf) return 0;  /* nothing to get */
    in_buf = buf->end_idx - buf->start_idx;  /* bytes avail in buffer */
    if (in_buf > to_skip) break;
    to_skip -= in_buf;
    buf = (socket_buffer *) buf->GetNext();  /* advance buffer if we have to skip more */
  }
  left = len;
  while (left > 0) {  /* more to copy? */
    if (!buf) {
      if (debug_mode)
        printf("Copied out %d bytes, %d left\n", copied, left);
      return copied; /* out of data */
    }
    in_buf = buf->end_idx - buf->start_idx - to_skip; /* bytes in buffer */
    to_skip = 0;
    if (in_buf > left) in_buf = left;
    memmove(dest, &(buf->dat[buf->start_idx]), in_buf); /* copy it */
    dest += in_buf;
    copied += in_buf;
    left -= in_buf;
    buf = (socket_buffer *) buf->GetNext(); /* next buffer */
  }
  if (debug_mode) 
    printf("Copied out all %d requested bytes\n", copied);
  return copied;
}

/* free N bytes from buffer */

void socket_data::free_socket_data(int len)

{
  int left;
  int in_buf;
  socket_buffer *buf;
  socket_buffer *nbuf;

  if (debug_mode) printf("freeing %d bytes from buffer\n", len);
  left = len;
  buf = (socket_buffer *) bufs.GetFirst(); 
  while (left > 0) {
    if (!buf) return;
    in_buf = buf->end_idx - buf->start_idx;
    if (in_buf > left) {  /* more data in buffer than we need */
      buf->start_idx += left;
      return;
    }
    left -= in_buf;  
    nbuf = (socket_buffer *) buf->GetNext(); /* next buffer */
	bufs.Remove(buf);
	buf = nbuf;
    if (debug_mode) printf("Free socket data\n");
  }
  return;
}     

/* find length of data in socket buffers */

int socket_data::get_data_length(void)

{
  socket_buffer *buf;
  int len;

  len = 0;
  for (buf = (socket_buffer *) bufs.GetFirst(); buf; 
	buf = (socket_buffer *) buf->GetNext()) {
    len += buf->end_idx - buf->start_idx;
  }
  return len;
}

/*Count the number of buffers */

int socket_data::count_data_buffers(void)

{
  socket_buffer *buf;
  int count;

  count = 0;
  for (buf = (socket_buffer *) bufs.GetFirst(); buf;
       buf = (socket_buffer *) buf->GetNext()) count++;
  if (debug_mode) printf("Counted %d buffers\n", count);
  return count;
}
    

  
/* 
 * Search socket buffer for string match.  This will return the offset in the buffer 
 * to the match.  It works by scanning the buffer for the first matching character, then
 * making a copy of the next N characters into a local array.
 *
 * Returns the offset from the start of the buffer of the match or -1
 * if no match was found.  If we have a null search string, then we 
 * return at once with a zero.
 */

#define SEARCH_BUF_SIZE  30*1024

int socket_data::find_string_match(char *str, int offset)

{
  int inlen;
  int chars_in_buf;
  int j;
  char linbuf[SEARCH_BUF_SIZE];  /* buffer to search at one time */

  inlen = strlen(str);
  if (!inlen) return 0;  /* nothing to match */
  for (;1;) { /* loop forever */
    chars_in_buf = copy_socket_data(linbuf, SEARCH_BUF_SIZE, offset);
    if (!chars_in_buf) return -1;
    for (j = 0; j <= chars_in_buf - inlen; j++) {
      if (!memcmp(&linbuf[j], str, inlen)) return (offset + j); /* found it */
    }
    if (chars_in_buf <= inlen) return -1;
    offset += chars_in_buf - inlen; /* bump up offset */
  }
}

//
// Constructor
//
socket_data::socket_data(void)

{
	socket_id = next_socket_id++;
	timeout_time = -1;
	Sockets.Add(this);
}

//
// Destructor.  This shuts down the socket and rejects any 
// requests that are outstanding.  The socket might be shut down
// if the connection timed out or if the other end droped the
// connection.
//
socket_data::~socket_data(void)

{
	Write_buffer *wObj;
	kill_socket(fd);
	for (wObj = (Write_buffer *) write_messages.GetFirst();
			wObj; wObj = (Write_buffer *) wObj->GetNext()) {
				if (wObj->req_id) { // client request
					G2CRequest *prObj = (G2CRequest *) RequestObjs.FindObj(wObj->req_id);
					if (prObj) {
						request_failed(prObj,"COMM-FAILURE");
						cout << "Connection broken while request pending" << endl;
					}
				}
			}

}

//
// This is the constructor for a server reply

Write_buffer::Write_buffer(iiop *iiopPtr, int connection_id)

{
	mode = 2;
	req_id = 0;
	piiop = iiopPtr;
	index = 0;
	len = iiopPtr->len;

	socket_data *sdata = (socket_data *) Sockets.FindObj(connection_id);
    if (!sdata) {
        delete this;
        return; // connection no longer there, nothing we can do
    }

	sdata->write_messages.Add(this); // post it
}


//
// This is the constructor for a client side write buffer

Write_buffer::Write_buffer(iiop *iiopPtr, G2CObject *pObj, G2CRequest *prObj)
{
	req_id = prObj->request_id;
	mode = 1;
	piiop = iiopPtr;
	index = 0;
	len = iiopPtr->len;


	// Now, we need to find a socket to send the message on.
	// if we have a connection to use with the socket, then use that.

	socket_data *sdata = NULL;
	if (pObj->connection_id) { // we have a connection already
		sdata = (socket_data *) Sockets.FindObj(pObj->connection_id); // still there?
	}
	if (!sdata) { // no, try finding one already established
		char buf[1024];
		sprintf(buf, "%s:%d", (char *) pObj->Host, pObj->port_number);
		socket_map *smap = (socket_map *) SocketMaps.FindObj(buf);
		if (smap) { // found map, is the socket still there?
			sdata = (socket_data *) Sockets.FindObj(smap->socket_id);
		}
		if (!sdata) { // no we need to create a new one
			sdata = create_connection((char *) pObj->Host, pObj->port_number);
			if (!sdata) {
				request_failed(prObj,"COMM-FAILURE"); // creat failed
				cout << "Unable to create connection to " << (char *) pObj->Host << endl;
				delete this;
				return;
            }
		}
		pObj->connection_id = sdata->socket_id; // update connection id
		if (!smap) {
			smap = new socket_map;  // create new map object
			smap->target_system = buf;
			SocketMaps.Add(smap); // save map object for later
		}
		smap->socket_id = sdata->socket_id; // update map
	}
	sdata->write_messages.Add(this); // post message
}

Write_buffer::~Write_buffer()

{
	if (piiop) delete piiop;
}
