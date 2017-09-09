// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently


#if !defined(AFX_STDAFX_H__A71ACD07_3B6E_11D1_8AB3_00609703E60F__INCLUDED_)
#define AFX_STDAFX_H__A71ACD07_3B6E_11D1_8AB3_00609703E60F__INCLUDED_

//#define _ATL_DEBUG_INTERFACES
//#define _ATL_DEBUG_QI

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


// #define _WIN32_WINNT 0x0400  We hope that this fixes the install problem
#define _ATL_APARTMENT_THREADED


#define ATL_TRACE_LEVEL        4
#define atrAxlMsgs          0x00000001
#define atrG2ObjLife        0x00000002
#define atrAxlMethodCalls   0x00000004
#define atrLockHistory      0x00000008
#define ATL_TRACE_CATEGORY  0xFFFFFFF0

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include "GsiContext.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A71ACD07_3B6E_11D1_8AB3_00609703E60F__INCLUDED)
