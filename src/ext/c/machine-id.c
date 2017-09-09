/*
 * GENSYMCID-578: G2 authorization 'sees' strange non-existent machine id under Linux
 *
 * machine-id.c: This simple program prints the `machine-id' of current Linux system.
 *
 * Author: Chun Tian (binghe), Glority Software Ltd, 2011/11/16
 */

#include <stdio.h>

long g2ext_nsleep(char*);

long g2int_open_fd_callback(long fd)
{
    return 0L;
}

long g2int_close_fd_callback(long fd)
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

int main (int argc, char **argv)
{
  char machine_id[256];

  g2ext_nsleep(machine_id);

  printf("%s\n", machine_id);
  return 0;
}
