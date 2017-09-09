/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      winmain.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +   MS Windows portions:
 +              1993 - 2003      various
 +              maintained by:   fmw, jv, mhd
 +
 + Description:  Implementation of WinMain()
 +
 +
 + Key:
 +   (obsolete)
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP -- WinMain
 +
 + External Interface:
 +
 + Dependencies:
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   01/06/03,  jv: Created, to hold WinMain instead of msmain.c
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications: 
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <windows.h>


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %   This module should not contain any global, non-static variables.  All
 %   variables which need to be shared between this module and another should
 %   be defined in the other module, and referenced as externs here.
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

extern int g2ext_gensym_winmain (HINSTANCE, LPSTR, LPSTR);


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP -- WinMain
 %
 % Description: WinMain is the entry point for all Windows applications
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/***************************************************************************\
*
*       WinMain(HANDLE, HANDLE, LPSTR, int)
*
*       PURPOSE: main entry point.
*
*       COMMENTS:
*
*        Windows recognizes this function by name as the initial entry point
*        for the program.
*
\***************************************************************************/

int PASCAL WinMain (HINSTANCE hInstance, 
		    HINSTANCE hPrevInstance,
		    LPSTR lpCmdLine,
		    int nCmdShow)
{
  return g2ext_gensym_winmain(hInstance, lpCmdLine, "G2");
}
