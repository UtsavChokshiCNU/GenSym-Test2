// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CEA712D8_3F25_46FD_ACD1_7CE500CD66FE__INCLUDED_)
#define AFX_STDAFX_H__CEA712D8_3F25_46FD_ACD1_7CE500CD66FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>

// Windows Header Files:
#include <windows.h>
#include <shellapi.h>

// Add support for ATL
#include <atlbase.h>
extern CComModule _Module ;
#include <atlwin.h>
#include <atlcom.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// STL Header Files
#include <list>
#include <queue>

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CEA712D8_3F25_46FD_ACD1_7CE500CD66FE__INCLUDED_)
