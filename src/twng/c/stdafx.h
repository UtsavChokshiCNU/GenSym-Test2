// -*- Mode: C++ -*-

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif						

#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>		// MFC core and standard components

#include "TypeSafeMsgMap.h"	// Gensym addition for VC6 only

#include <afxext.h>		// MFC extensions
#include <afxdisp.h>		// MFC Automation classes
#include <afxtempl.h>		// MFC Automation templates
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <shlwapi.h>		// non-MFC Shell APIs

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>	        // MFC support for Windows Common Controls
#endif

#include <afxhtml.h>		// MFC CHtmlView control

// Codejock eXtreme Toolkit Pro

#define _XTP_STATICLINK		// Also defined in Resource.h

#include <XTToolkitPro.h>
#include "CommandBars/XTPControlExt.h"
