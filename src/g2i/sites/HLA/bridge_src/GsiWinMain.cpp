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
#include <io.h>
#include <fcntl.h>


extern "C"
{
#include <gsi_main.h>
}

#include "G2Hla.h"

extern void restore_stdout();
extern void load_version();

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

  /*
   * gsi_initialize_for_win32() may allocate new console window
   *  so STDOUT should be re-initialized
   */
  restore_stdout();

  /*
   * Load Version string from resources
   */

  load_version();

  main(argc, argv);

  //free G2HLA_VERSION string if it is allocated by load_version()
  if (G2HLA_VERSION != DEFAULT_G2HLA_VERSION)
  {
      delete[] G2HLA_VERSION;
  }

  return (0);       
}


/***************************************************************************\
*    restore_stdout()
*
*        Routine that restores STDOUT from STD_OUTPUT_HANDLE
*
\***************************************************************************/
void restore_stdout()
{
  HANDLE	hout = GetStdHandle(STD_OUTPUT_HANDLE);
  int		fdstdout = _open_osfhandle((long) hout, _O_TEXT);
  FILE		*fp = _fdopen(fdstdout, "w");
 
  *stdout = *fp;
}

/***************************************************************************\
*    load_version()
*
*         Function that loads HLA version from resources and save it to the
*        G2HLA_VERSION global variable.
*
\***************************************************************************/
void load_version()
{
  char		fileName[MAX_PATH];
  DWORD		verInfoHandle = 0;
  DWORD		verSize = 0;
  char		*buffer = NULL;

  GetModuleFileName(NULL, fileName, MAX_PATH);

  verSize = GetFileVersionInfoSize(fileName, &verInfoHandle);

  if (verSize == 0)
  {
      return;
  }

  buffer = new char[verSize];
  
  if (GetFileVersionInfo(fileName, verInfoHandle, verSize, buffer))
  {
      struct LangInfo
      {
          WORD language;
          WORD codepage;
      };
	  
      UINT		len = 0;
      LangInfo	*info = NULL;

      if (VerQueryValue(buffer, "\\VarFileInfo\\Translation", (LPVOID*) &info, &len)
          && len >= sizeof LangInfo)
      {
          //use 1st lang info
          char path[0x100];
          sprintf(path, "\\StringFileInfo\\%04x%04x\\ProductVersion",
              info->language, info->codepage);

          char *version = NULL;
			  
          if (VerQueryValue(buffer, path, (LPVOID*) &version, &len) && len > 0)
          {
              G2HLA_VERSION = new char [len + 1];
              strncpy(G2HLA_VERSION, version, len);
          }
      }
  }

  delete[] buffer;
}
