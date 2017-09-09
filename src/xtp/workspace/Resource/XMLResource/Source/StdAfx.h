// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A3D160AF_67CE_4152_ACAC_A2F79B25E8B6__INCLUDED_)
#define AFX_STDAFX_H__A3D160AF_67CE_4152_ACAC_A2F79B25E8B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>

#include <afxpriv.h>

#include <afxtempl.h>
#include <afxole.h>

#if (_MSC_VER >= 1300)
#include <..\src\mfc\afximpl.h> // Visual Studio .NET MFC Global data
#else
#include <..\src\afximpl.h>     // MFC Global data
#endif

#define _XTP_EXT_CLASS
#include "Common/XTPMacros.h"

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A3D160AF_67CE_4152_ACAC_A2F79B25E8B6__INCLUDED_)
