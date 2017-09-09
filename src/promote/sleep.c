// sleep.c

//
#include <stdio.h>           // Needed for printf()
#include <stdlib.h>          // Needed for exit() and atof()
#include <windows.h>         // Needed for Sleep()

//
void main(int argc, char *argv[])
{
  int    sleep_time;         // Number of milliseconds to sleep

  if (argc != 2)
  {
    printf("*** ERROR - incorrect number of command line arguments \n");
    printf("            usage is 'sleep number_of_seconds'         \n");
    exit(1);
  }

  // Sleep time in milliseconds
  sleep_time = (int) (1000.0 * atof(argv[1]));

  // Now sleep for sleep_time milliseconds
  Sleep(sleep_time);
}