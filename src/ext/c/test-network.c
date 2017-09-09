#include <stdio.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

long g2int_open_fd_callback(fd)
    long fd;
{
    return 0L;
}

long g2int_close_fd_callback(fd)
    long fd;
{
    return 0L;
}

long g2int_writing_fd_callback()
{
    return -1L;
}

long g2int_not_writing_fd_callback()
{
    return -1L;
}

long g2int_network_event_handler()
{
    return -1L;
}

long g2int_run_trace_function()
{
    return 0;
}

long g2int_unix_command_callback()
{
    return 0;
}

extern int g2pvt_tcpip_get_addresses(); /* tcp.c */

int test_g2pvt_tcpip_get_addresses ()
{
  int i, index;
  char **buffer;
  struct in_addr *paddr;

  i = g2pvt_tcpip_get_addresses(&buffer);
  printf("%d interfaces: \n", i);

  paddr = (struct in_addr *) buffer;

  for (index = 0; index < i; ++index) {
    unsigned char *temp = (unsigned char *) &paddr[index];
    printf("%d.%d.%d.%d\n", temp[0], temp[1], temp[2], temp[3]);
  }

  return 0;
}

int main (int argc, char **argv)
{
  printf("Hello, world!\n");

  printf("Test g2pvt_tcpip_get_addresses(), all interface addresses:\n");
  test_g2pvt_tcpip_get_addresses();
  return 0;
}
