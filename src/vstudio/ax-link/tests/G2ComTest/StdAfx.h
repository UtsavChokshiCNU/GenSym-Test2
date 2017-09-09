// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#include <winsock.h>

#include <atlbase.h>

extern CComModule _Module;

#define atrAxlMsgs          0x00000001
#define atrG2ObjLife        0x00000002
#define atrAxlMethodCalls   0x00000004
#define atrLockHistory      0x00000008

#include <atlcom.h>
#include <atlctl.h>
#include <process.h>
#include <atlconv.h>

#include "G2Com.h"
#include "GsiContext.h"

DWORD G2WaitForSingleObject(HANDLE hEvent,DWORD dwMilliseconds, GsiContext* context);
