// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


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

// Local Header Files

#include "opcda.h"
#include "gsi_main.h" 
#include "opc_start.h"
#include "group.h"
#include "server.h"
#include "opc_gsi.h"
#include "opc_gsi_brg.h"
#include "opc_log.h"
#include "opc_rpcs.h"
#include "opc_trayfunc.h"
#include "opc_utils.h" 
#include "CCommandLine.h"
#include "ProgramVersion.h"
#include "OPCDataCallback.h"
#include "OPCShutdown.h"
#include "G2OpcClientIcon.h"
#include "G2OpcHiddenWin.h"
#include "CtrlPanel.h"
#include "ServerList.h"

#define MAX_GDB_CONTEXTS   50L

using namespace std ;
typedef list<gsi_int, allocator<gsi_int> > GSINTLIST ;
typedef queue<gsi_int, GSINTLIST > GSINTQUEUE ;

extern context_info         context[MAX_GDB_CONTEXTS] ;
extern CRITICAL_SECTION     crtsec_items ;
extern CServer              g_servers[MAX_GDB_CONTEXTS] ;
extern int                  g_nr_servers ;
extern GSINTQUEUE           async_processing_queue ;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
