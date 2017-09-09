// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _WIN32_WINNT 0x400 
#define _WIN32_IE 0x500

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <objbase.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>

// TODO: reference additional headers your program requires here
#include "FileOpenCommon.h"

int ListDirectoryAsync(LPCSTR directory, LPCSTR name, ListDirCallback callback, LPARAM lParam);


