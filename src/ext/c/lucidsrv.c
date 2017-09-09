/* Server loop to be loaded into Lucid. */

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <strings.h>

#include "cprim.h"

#define OOPS(msg) {perror(msg); goto BYE;}

extern void g2int_lisp_server_loop(long, long);

int
  socket_open(int port)
{
  int sock = -1;
  struct sockaddr_in server;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock<0)
    OOPS("opening socket");

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = port;
  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    OOPS("bind");
  return sock;

 BYE:
  if (sock>=0)
    close(sock);
  return -1;
}


int
  c_server_loop(int sock, int type)
{
  int msgsock = -1;

  listen(sock,5);
  do {
    msgsock = accept(sock, NULL, NULL);
    if (msgsock == -1)		
      {
	if (errno != EINTR)	/* Seem to get an interrupted-system-call frequently. */
	  perror("accept");
	continue;
      }

    g2int_lisp_server_loop(msgsock,type);

  } while(1);

  return 0;
}


char *
  hostname ()
{
  static char name[128];
  static int once = 1;
  char *cp;

  if (once)
    {
      gethostname(name, 128);
      /* remove domain name. */
      if ((cp = strchr(name,'.')))
	*cp = '\0';
      once=0;
    }
  return name;
}

int
  socket_close(int sock)
{
  if (sock>=0)
    close(sock);
  return 0;
}
