/***************************************************************************
:
:  gsi_main.c  --  Sample main function to link with GSI toolkit.
:
:  This is a functional main which is used to link with skeleton.c and other
:  GSI example programs.  Feel free to use this main as is, or modified to
:  suit your needs.
:
:  Although this software has been extensively tested, Gensym cannot
:  guarantee error-free performance in all applications.  Accordingly,
:  use of the software is at the customer's sole risk.
:
:..........................................................................*/

#include "gsi_main.h"

int main(argc, argv)
    int   argc;
    char *argv[];
{
  GSI_SET_OPTIONS_FROM_COMPILE();

#ifdef WIN32
  gsi_initialize_for_win32(NULL, NULL);
#endif
  gsi_start(argc, argv);
  return 0;
}
