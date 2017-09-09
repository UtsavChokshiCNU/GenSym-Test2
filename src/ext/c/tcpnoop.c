#include "cprim.h"

long getgsiport()
{
  return (-1L);
}


long int g2pvt_tcpip_gethostname(string_buffer, length)
  char *string_buffer;
  long int  length;
{
  string_buffer[0]= '\0';
  return (0);
}


long g2pvt_tcpip_accept(lsock)
  long lsock;
{
  return (-1L);
}

long g2pvt_tcpip_connect (host, port)
     char *host;
     long port;
{
  return (-1L);
}

long g2pvt_tcpip_listen (port)
long port;
{
  return (-2L);
}

long g2pvt_tcpip_read (lsock, buf, len)
long lsock;
char *buf;
long len;
{
  return (-1L);
}

long g2pvt_tcpip_write (lsock, buf, len)
long lsock;
char *buf;
long len;
{
  return (-1L);
}

long g2pvt_tcpip_close (lsock)
long lsock;
{
  return (-1L);
}

int g2pvt_tcpip_get_addresses(buffer)
char*** buffer;
{
  return 0;
}
