/*************************************************************************/
/* INCLUDES                                                              */
/*************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>    /* This is needed to make use of the portable */
                         /*  Message Crackers defined under Win32 and  */
                         /*  Win 3.1. They aid in writing generic code.*/
#include <malloc.h>
#include <string.h>


#ifdef	__cplusplus
extern "C" {
#endif

#include <gsi_main.h>

#ifdef	__cplusplus
}
#endif


/***************************************************************************\
*
*       WinMain(HANDLE, HANDLE, LPSTR, int)
*
*       PURPOSE: main entry point.
*
*       COMMENTS:
*
*        Windows recognizes this function by name as the initial entry point
*        for the program.  This function calls the application initialization
*        routine, if no other instance of the program is running, and always
*        calls the instance initialization routine.  It then executes a message
*        retrieval and dispatch loop that is the top-level control structure
*        for the remainder of execution.  The loop is terminated when a WM_QUIT
*        message is received, at which time this function exits the application
*        instance by returning the value passed by PostQuitMessage().
*
*        If this function must abort before entering the message loop, it
*        returns the conventional value NULL.
*
*		Feel free to use this code as is, or modified to suit your needs.
*		Although this software has been extensively tested, Gensym cannot
*		guarantee error-free performance in all applications.  Accordingly,
*		use of the software is at the customer's sole risk.
*
\***************************************************************************/

#define ARG_LENGTH 50
#define argc __argc
#define argv __argv



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  extern void	main(int, char *[]);
  extern int	argc;
  extern char	**argv;
  
  gsi_initialize_for_win32(hInstance, lpCmdLine);

  main(argc, argv);

  return (0);       
}


