#if !defined(_GENSYM_WSV_AFX_STUFF_)
#define _GENSYM_WSV_AFX_STUFF_

#if _MSC_VER > 1000
#  pragma once
#endif // _MSC_VER > 1000


#define VC_EXTRALEAN      // Exclude rarely-used stuff from Windows headers
#include <afxctl.h>       // MFC support for ActiveX Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#  include <afxcmn.h>       // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxpriv.h>

#ifdef L_IMPL_OBJECTSAFETY
#  include <objsafe.h>
#endif// L_IMPL_OBJECTSAFETY

#include "G2Com.h"

#ifdef _DEBUG
#  define new DEBUG_NEW
#endif

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately
// before the previous line.

#endif // !defined(_GENSYM_WSV_AFX_STUFF_)
