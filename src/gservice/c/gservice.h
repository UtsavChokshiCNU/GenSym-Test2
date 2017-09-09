//===========================================================================
// GSERVICE.H                                                        [header]
//===========================================================================
//
// Author: Robert J. Franceschini
//
// Copyright (C) 1986-2017 Gensym Corporation.
//
//===========================================================================

#ifndef _GSERVICE_H
#define _GSERVICE_H

#define MAX_PATH_X 2048 // adjusted for EDS (need to check)

// global structures
//
typedef struct SERVICE {
	WCHAR      szServiceName[MAX_PATH_X];     // service name displayed in SCM
	BOOL       bStatus;                       // configuration status of service
	WCHAR      szProgram[MAX_PATH_X];         // path & name of program executable
	WCHAR      szParameters[MAX_PATH_X];      // path & name of program executable
	WCHAR      szLogFile[MAX_PATH_X];         // path & name of logfile
	WCHAR      szAccount[MAX_PATH_X];         // account name running service
	WCHAR      szDependsOn[MAX_PATH_X];       // service dependencies
	DWORD      dwServiceType;                 // interactive or not
	DWORD      dwStartType;                   // auto-start, manual, etc.
} SERVICE;

// internal name of the service
//
#define SERVICENAME     L"GSERVICE"

// Default service configuration flags: separate process, and allow
// interaction with the desktop
#define GSERVICE_OPTIONS SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
// registry keys    
//    
#define DFLT_KEY          L"SYSTEM\\CurrentControlSet\\Services\\"
#define REG_STATUS        L"ConfigStatus"
#define REG_PROGRAM       L"Program"
#define REG_PARAMETERS    L"Parameters"
#define REG_LOGFILE       L"LogFilePath"
#define REG_ACCOUNT       L"ObjectName"
#define REG_SERVICE_TYPE  L"Type"
#define REG_RESTART       L"Restart"
#define REG_CONSOLE       L"Console"
// macros
//
#define  SBOOLEAN(n) n > 0 ? L"TRUE" : L"FALSE"
#define  SNULL(n) n[0] != 0 ? n : L"UNDEFINED"

// prototypes
//
BOOL  ServiceSetConfig(DWORD argc, WCHAR **argv);
VOID  ServiceInstall(WCHAR *serviceName);
VOID  ServiceRemove(WCHAR *serviceName);
VOID  ServiceStart(WCHAR *serviceName);
VOID  ServiceStop(WCHAR *serviceName);
VOID  ServiceRun(WCHAR *serviceName);
VOID  ServiceStop();
VOID  ServiceCleanup();
VOID  ServiceHelp();
VOID  ServiceInfo(WCHAR *serviceName);
BOOL  ServiceGetConfig(WCHAR *serviceName);

VOID  ReportEventMsg(WORD status, WCHAR *lpszMsg);
VOID  CmdDebugService(DWORD argc, WCHAR **argv);

VOID  service_main(DWORD dwArgc, WCHAR **lpszArgv);
VOID  service_ctrl_handler(DWORD dwCtrlCode);
BOOL  ReportStatusToSCMgr(DWORD dwCurrentState,
	DWORD dwWin32ExitCode,
	DWORD dwCheckPoint,
	DWORD dwWaitHint);

WCHAR*  GetLastErrorText(WCHAR *lpszBuf, DWORD dwSize);
BOOL  WSO (WCHAR *argtypes, ...);
WCHAR* time_stamp(WCHAR *result);
BOOL hasAdminPriv();
WCHAR *get_module_version();
BOOL restartAvailable();

#endif
