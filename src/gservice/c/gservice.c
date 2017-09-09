//=========================================================================
// GSERVICE.C                                                      [source]
//=========================================================================
//
// Author: Robert J. Franceschini
//
// This is a Windows NT multi-threaded service. This service (parent
// process) will spawn a process (child process) to run a G2 process
// or bridge (or, in fact, any other executable.) The child process is
// an independent process and must be explicitly terminated by the
// parent.  The process will execute within its own thread.
// Notifications to both the parent and child processes are handled
// independently via separate event objects.
//
// Copyright (C) 1986-2017 Gensym Corporation.
//
//  gservice <command> <service-name> [<args...>]
//  gservice install xyzservice program=c:\myprog.exe logfile=c:\mylog.log 
//
//=========================================================================
//
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <locale.h>
#include "gservice.h"

// Service Manager Stuff
//
SERVICE_STATUS          ssStatus;             // service status
SERVICE_STATUS_HANDLE   sshStatusHandle = 0;  // service handle

// Event Handles
//
HANDLE     hEvent[]      = {NULL,       // 0 - process event handle
                            NULL};      // 1 - service manager event handle
// Other globals
//
PROCESS_INFORMATION pInfo;
WCHAR      fileBuffer[4096];
WCHAR      msgBuf[1024];
DWORD      dwGlobalErr;                 // last error code
WCHAR      szErr[256];
BOOL       bServiceProcess = FALSE;     // process run as service or from cmd?
BOOL       bDebug        = FALSE;       // debug mode flag
HANDLE     hFileOut      = NULL;        // log file handle
HANDLE     hConsoleOut   = NULL;        // console handle
BOOL       bConsoleReqd  = TRUE;        // console requested by user
BOOL       bRestart      = FALSE;       // restart flag
SC_HANDLE  schService;

//Support for restart flag, only available on Win2K.  Need to indirect
//calls so the entry points aren't attempted at startup on NT.
HMODULE advapi32 = NULL;	// Pointer to advapi.dll
FARPROC QuerySvcConfig2 = NULL; // Pointer to function QueryServiceConfig2
FARPROC ChangeSvcConfig2 = NULL;// Pointer to function ChangeServiceConfig2

SERVICE service;

//=========================================================================
//  main
//    - process input arguments
//    - call StartServiceCtrlDispatcher to register the parent service 
//      thread. When the dispatched function returns, the service has 
//      stopped, so exit.
//    - Arguments (Only valid during interactive session)
//        [1] = command
//                - install = install service in SCM with options
//                - remove = remove service from SCM
//                - start = start service manually
//                - stop = stop service manually
//                - info = display info on installed service
//                - debug = run service from console (does not start service
//                          in SCM)
//        [2] = service name
//        [n] = options
//                - program    = path + program to run as child process
//                - parameters = command line args of program
//                - module-search-path = 'path1' 'path2' ...
//                - logfile    = path + logfile to dump console messages
//                - console    = <true,false> allow process to interact
//                                with desktop (i.e. show a console window)
//                - restart    = <true,false> requests service system to 
//                               restart automatically upon exit of process
//=========================================================================
//
int wmain ( int argc, WCHAR *argv[] )
{
	SERVICE_TABLE_ENTRY dispatchTable[] = {
		{ SERVICENAME, (LPSERVICE_MAIN_FUNCTION)service_main },
		{ NULL, NULL }
	};

	HANDLE standard_out;

	// Update console output locale
	setlocale(LC_CTYPE, "");

	wprintf(L"\n==================================================\n");
	wprintf(L"GSERVICE Service Installation Utility for Intel NT\n");
	wprintf(L"   Version %s\n", get_module_version());
	wprintf(L"==================================================\n\n");

	// We will need to determine if we have been started from the
	// command line or from the SCM.  There seems to be no convenient
	// way to do this.  Prior to this code, we tried to create a
	// console, which would fail if created from the command line.  But
	// we want to not create a console if console=false, and it's ugly
	// to have it flash a console to create/delete.  So we use
	// GetStdHandle to check if there's standard output available.  The
	// documentation SAYS it'll return INVALID_HANDLE_VALUE if not.
	// But, in fact, it returns NULL.  NULL is, however, apparently an
	// invalid handle (experiments using NULL as a handle return
	// "invalid handle" error messages).  I wish I could find
	// verification in the doc that NULL is an invalid handle as well as
	// INVALID_HANDLE_VALUE.  --yduJ, Aug 2004

	standard_out = GetStdHandle(STD_OUTPUT_HANDLE);
	if (standard_out == NULL || standard_out == INVALID_HANDLE_VALUE) {
		//Started from SCM.
		bServiceProcess = TRUE;
	}

	// process command line arguments
	//
	if ( argc > 2)
	{
		// install
		if (!_wcsicmp(L"install",argv[1])) {
			if (ServiceSetConfig(argc, argv))
				ServiceInstall(argv[2]);
			exit(0);
		} else
			// remove
			if (!_wcsicmp(L"remove",argv[1])) {
				ServiceRemove(argv[2]);
				exit(0);
			} else
				// debug - (run service from console, don't start it in SCM)
				if (!_wcsicmp(L"debug",argv[1])) {
					bDebug = TRUE;
					ServiceStart(argv[2]);
					ServiceCleanup();
					exit(0);
				} else
					// start
					if (!_wcsicmp(L"start",argv[1])) {
						if (ServiceGetConfig(argv[2]))
							ServiceRun(argv[2]);
						exit(0);
					} else
						// stop
						if (!_wcsicmp(L"stop",argv[1])) {
							ServiceStop(argv[2]);
							ServiceCleanup();
							exit(0);
						} else
							// info
							if (!_wcsicmp(L"info",argv[1])) {
								ServiceInfo((LPTSTR) argv[2]);
								exit(0);
							} 
							else {
								ServiceHelp();
								exit(0);
							}
	}
	else if (!bServiceProcess) {
		ServiceHelp();
		exit(0);
	}

	// Connect the main thread of the service process to the service control
	// manager. This causes the thread to be the service control dispatcher
	// thread for the calling process.
	//
	if (!StartServiceCtrlDispatcher(dispatchTable))
		ServiceCleanup();
	//    StopJobService("StartServiceCtrlDispatcher failed");

}



//=========================================================================
//  service_main
//    - Entry point function of the service. It is designated by the
//      SERVICE_TABLE_ENTRY dispatchTable and invoked via the 
//      StartServiceCtrlDispatcher function. 
//    - Launches the child (or worker) thread and waits on the event that
//      the worker thread will signal at its termination
//    - Informs the service control manager of the status of the worker
//      thread. 
//    - When started from SCM, 1st argument is the service name. This 
//      function will never be called from the console as the service
//      control dispatcher will not function unless invoked via the SCM
//=========================================================================
//
VOID service_main (DWORD dwArgc, WCHAR **lpszArgv)
{
	_tcscpy(service.szServiceName,lpszArgv[0]);    // should check this 

	// initialize handles
	//
	hFileOut = NULL;

	// register a service control handler to handle service events
	//
	sshStatusHandle = RegisterServiceCtrlHandler(SERVICENAME,
		(LPHANDLER_FUNCTION)service_ctrl_handler );

	if (!sshStatusHandle) {
		ReportEventMsg(EVENTLOG_ERROR_TYPE, L"RegisterServiceCtrlHandler failed");
		ServiceCleanup();
	};

	// SERVICE_STATUS members that don't change
	//
	ssStatus.dwServiceType = GSERVICE_OPTIONS;
	ssStatus.dwServiceSpecificExitCode = 0;

	// report the status to Service Control Manager.
	//
	if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 1, 3000))
		ServiceCleanup();

	// start the service
	//
	ServiceStart(lpszArgv[0]);

	// deallocate all resources and exit. This will simply stop the 
	// service, it will not remove the service from the SCM
	//
	ServiceCleanup();
}


//=========================================================================
//  service_ctrl_handler
//    - this function is called by the Service Controller whenever
//      someone (SCM or manual call) calls ControlService in reference to 
//      this service.
//    - the service controller is accessible via the WINNT 'control-panel'
//=========================================================================
//
VOID service_ctrl_handler (DWORD dwCtrlCode)
{
	DWORD  dwState = SERVICE_RUNNING;

	// Handle the requested control code.
	//
	switch (dwCtrlCode) {

	// Pause the service if it is running.
	//
	case SERVICE_CONTROL_PAUSE:
		if (ssStatus.dwCurrentState == SERVICE_RUNNING)
			dwState = SERVICE_PAUSED;
		WSO(L"%s", L"SERVICE_CONTROL_PAUSE");
		break;

	// Resume the paused service.
	//
	case SERVICE_CONTROL_CONTINUE:
		if (ssStatus.dwCurrentState == SERVICE_PAUSED)
			dwState = SERVICE_RUNNING;
		WSO(L"%s", L"SERVICE_CONTROL_CONTINUE");
		break;

	// Stop the service.
	//
	case SERVICE_CONTROL_STOP:
		dwState = SERVICE_STOP_PENDING;
		bRestart = FALSE; //don't try to restart on a manual stop!

		// Report the status, specifying the checkpoint and waithint,
		// before setting the termination event.
		//
		ReportStatusToSCMgr(dwState, NO_ERROR, 1, 3000);
		WSO(L"%s", L"SERVICE_CONTROL_STOP");

		// kill the process and thread
		//
		WSO(L"%s", L"Kill the service process & thread");

		SetEvent(hEvent[1]);

		break;

	// Update the service status.
	//
	case SERVICE_CONTROL_INTERROGATE:
		dwState = SERVICE_RUNNING;
		WSO(L"%s", L"SERVICE_CONTROL_INTERROGATE");
		break;

		// invalid control code
		//
	default:
		WSO(L"%s", L"SERVICE_CONTROL_DEFAULT");
		break;

	}

	// report status to SCM
	//
	ReportStatusToSCMgr(dwState, NO_ERROR, 1, 3000);

}



//=========================================================================
//  ServiceSetConfig
//    - process command line arguments and load values into 'service'
//      structure for use by ServiceInstall
//    - arguments must be in the following format: token=value
//=========================================================================
//
BOOL  ServiceSetConfig( DWORD argc, WCHAR **argv )
{
	DWORD    argCount;
	TCHAR     tmpArgv[MAX_PATH_X];
	LPTSTR    token, value;

	// Initialize 'service' struct
	//
	memset(&service, 0, sizeof(SERVICE));
	service.dwServiceType = GSERVICE_OPTIONS;
	service.dwStartType = SERVICE_AUTO_START;

	WSO(L"%s%s", L"CONFIGURING SERVICE '%'", argv[2]);

	// Extract tokens and values from command line args. Update 'service'
	// structure with values
	//
	if (argc > 3) 
	{
		for (argCount=3; argCount<argc; argCount++) 
		{
			wprintf(L"%2d> %s\n", argCount, argv[argCount]);

			wcscpy(tmpArgv, argv[argCount]);

			// get the token
			token = wcstok(tmpArgv, L"=");

			if (token != NULL) {
				// program
				if (!_wcsicmp(token, L"program")) {   // should check prog location before approval
					value = wcstok(NULL, L"=");
					if (value != NULL)
						wcscpy(service.szProgram, value); 
				}
				// parameters
				if (!_wcsicmp(token, L"parameters")) {
					value = wcstok(NULL, L"=");
					if (value != NULL) {
						if (service.szParameters[0] != 0)
							//already has something from module search path, just append.
							wcscat(service.szParameters, value);
						else {
							wcscat(service.szParameters, L"RESERVED ");
							wcscat(service.szParameters, value);
						}
					}
				}
				// module-search-path
				if (!_wcsicmp(token, L"module-search-path")) {
					value = wcstok(NULL, L"=");
					if (value != NULL) {
						if (service.szParameters[0] != 0) {
							//already has something from parameters, append, but with quotes
							wcscat(service.szParameters, L" -module-search-path \"");
							wcscat(service.szParameters, value);
							wcscat(service.szParameters, L"\"");
						} else {
							//Create anew
							wcscat(service.szParameters, L"RESERVED -module-search-path \"");
							wcscat(service.szParameters, value);
							wcscat(service.szParameters, L"\"");
						}
					}
				}
				// logfile
				if (!wcscmp(token, L"logfile")) {   // should check logfile location before approval
					value = wcstok(NULL, L"=");
					if (value != NULL)
						wcscpy(service.szLogFile, value); 
				}
				// console
				if (!_wcsicmp(token, L"console")) {
					value = wcstok(NULL, L"=");
					if (value != NULL) {
						if (!_wcsicmp(L"false", value))
							bConsoleReqd = FALSE;
					}
				}
				// restart
				if (!_wcsicmp(token, L"restart")) {
					value = wcstok(NULL, L"=");
					if (value != NULL) {
						if (!_wcsicmp(L"true", value)) {
							if (restartAvailable())		    
								bRestart = TRUE;
							else
								WSO(L"%s", L"WARNING:  Restart option is only available on Windows 2000.  Not selecting.");
						}		
					}
				}
				// dependson (for service dependencies)
				if (!_wcsicmp(token, L"dependson")) {
					value = wcstok(NULL, L"=");
					if (value != NULL) {
						wcscpy(service.szDependsOn,value);
					}
				}
			}
		}
	}

	if (service.szProgram[0] == 0) {
		WSO(L"%s", L"ERROR: Service configuration has failed.");
		ReportEventMsg(EVENTLOG_ERROR_TYPE, L"ERROR: Program to run from this service has not been specified");
		if (!hasAdminPriv())
			WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
		return(FALSE);
	}

	WSO(L"%s", L"Service configuration has succeeded.");
	return(TRUE);
}


//=========================================================================
//  GetDependencies
//
//  Dependencies are entered as a comma-separated string, but they
//  need to be passed to CreateService as a "Pointer to a double
//  null-terminated array of null-separated names of services or load
//  ordering groups that the system must start before this service."
//  This function creates that "string" of null separated names.
//
//  We are using strtok, and so it's important that this gets called a
//  different time than the original parsing of the commandline, since
//  strtok is not reentrant, according to the Microsoft documentation.
//=========================================================================
WCHAR* GetDependencies(WCHAR *dependencies)
{
	WCHAR *token;
	WCHAR *returnval = NULL, *pointer;

	token = wcstok(dependencies, L",");
	if (token != NULL) {
		returnval = (TCHAR *)malloc(MAX_PATH_X * sizeof(TCHAR));
		pointer = returnval;
		while (token != NULL) {
			wcscpy(pointer, token);
			pointer += _tcslen(token);
			*pointer = L'\0';
			pointer++;
			token = _tcstok(NULL, L",");
		}
		//Add a second null
		*pointer = L'\0';
	}
	return returnval;
}

//=========================================================================
//  UnpackDependencies
//    - Reconstructs the comma separated string of dependencies by 
//      parsing the null-separated (and double-null terminated) list of
//      dependencies.
//=========================================================================
WCHAR* UnpackDependencies(WCHAR *dependencies)
{
	WCHAR *returnval, *pointer;

	returnval = (LPTSTR)malloc(MAX_PATH_X * sizeof(LPTSTR));
	memset(returnval, 0, MAX_PATH_X);
	pointer = dependencies;
	while (pointer && *pointer) {
		if (pointer != dependencies) //Skip the first time, put comma in otherwise
			wcscat(returnval, L",");
		wcscat(returnval, pointer);
		pointer = pointer + _tcslen(pointer);
		pointer++; // skip the null.
	}
	return returnval;
}


//=========================================================================
//  ServiceInstall
//    - Creates a service object and adds it to the specified service
//      control manager database. 
//    - Updates registry with values extracted from ServiceSetConfig.
//      These values are used when the service is started.
//=========================================================================
//
VOID ServiceInstall (WCHAR *serviceName)
{
	SECURITY_ATTRIBUTES saAttr;
	SC_HANDLE   schSCManager;
	WCHAR       szPath[MAX_PATH_X];
	HKEY        hKey = NULL;
	WCHAR       szKey[256];
	BOOL        bStatus = TRUE;
	LPSERVICE_FAILURE_ACTIONS lpfailActBuf = NULL;
	LPSC_ACTION lpfailActions = NULL;
	LPCTSTR     lpDependencies;
	DWORD       lpdwDisposition;

	WSO(L"%s%s", L"INSTALLING SERVICE '%'", serviceName);

	if ( !GetModuleFileName( NULL, szPath, MAX_PATH_X ) ) {
		WSO(L"%s%s%s", L"ERROR: Unable to install service '%' - %", serviceName, GetLastErrorText(szErr,256));
		if (!hasAdminPriv())
			WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
		return;
	}

	// establish connection to the service control manager on the local 
	// computer and open the default database
	//
	WSO(L"%s", L"  Connecting to SCM");
	schSCManager = OpenSCManager(
		NULL,                      // machine (NULL == local)
		NULL,                      // database (NULL == default)
		SC_MANAGER_ALL_ACCESS      // access required
		);

	// create the service named by serviceName 
	//
	WSO(L"%s", L"  Creating Service");
	if ( schSCManager != NULL )
	{
		lpDependencies = GetDependencies(service.szDependsOn);
		schService = CreateService(schSCManager,              // SCManager database (use default)
			serviceName,               // name of service
			serviceName,               // name to display in SCM
			SERVICE_ALL_ACCESS,        // desired access
			service.dwServiceType,     // service type (interactive,etc.)
			service.dwStartType,       // start type (auto,manual,etc.)
			SERVICE_ERROR_NORMAL,      // error control type
			szPath,                    // service's binary
			NULL,                      // no load ordering group
			NULL,                      // no tag identifier
			lpDependencies,            // dependencies
			NULL,                      // user account (NULL = LocalSystem account)
			NULL                       // user password
			);

		if ( schService != NULL ) {

			// Initialize the security structure. The security structure contains the 
			// security descriptor for an object and specifies whether the handle 
			// retrieved by specifying this structure is inheritable.
			//
			memset(&saAttr, 0, sizeof(SECURITY_ATTRIBUTES));
			saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
			saAttr.bInheritHandle = TRUE;
			saAttr.lpSecurityDescriptor = NULL;

			WSO(L"%s", L"  Updating registry");

			// Add service configuration parameters to the service registry key.
			// Open the 'serviceName' service key.
			//
			wsprintf(szKey, L"SYSTEM\\CurrentControlSet\\Services\\%s", serviceName);
			RegCreateKeyEx(
				HKEY_LOCAL_MACHINE,
				szKey,
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS,
				&saAttr,
				&hKey,
				&lpdwDisposition);

			if (hKey == NULL) {
				WSO(L"%s", L"ERROR: Unable to open registry service key");
				WSO(L"%s%s%s", L"ERROR: Unable to install service '%' - %", serviceName, GetLastErrorText(szErr,256));
				CloseServiceHandle(schSCManager);
				ServiceRemove(serviceName);
				if (!hasAdminPriv())
					WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
				return;
			}

			// program (bridge)
			//
			if (service.szProgram[0] != 0) 
			{
				WSO(L"%s%s", L"    Adding - Program = %", service.szProgram);
				if (!RegSetValueEx(
					hKey,
					REG_PROGRAM,
					0,
					REG_SZ,
					(CONST BYTE *) service.szProgram,
					2 * (lstrlen(service.szProgram) +1) ) == ERROR_SUCCESS)
					bStatus = FALSE;
			}

			// parameters
			//
			if (service.szParameters[0] != 0) 
			{
				WSO(L"%s%s", L"    Adding - Parameters = %",service.szParameters);
				if (!RegSetValueEx(
					hKey,
					REG_PARAMETERS,
					0,
					REG_SZ,
					(CONST BYTE *) service.szParameters,
					2 * (lstrlen(service.szParameters) +1) ) == ERROR_SUCCESS)
					// bStatus = FALSE;
					bStatus = TRUE;
			}

			// logfile
			//
			if (service.szLogFile[0] != 0) 
			{
				WSO(L"%s%s", L"    Adding - LogFilePath = %",service.szLogFile);
				if (!RegSetValueEx(
					hKey,
					REG_LOGFILE,
					0,
					REG_SZ,
					(CONST BYTE *) service.szLogFile,
					2 * (lstrlen(service.szLogFile) +1) ) == ERROR_SUCCESS)
					bStatus = FALSE;
			}

			// bConsoleReqd
			WSO(L"%s%d", L"    Adding - Console flag = %",bConsoleReqd);
			//First, tell the registry about the command line flag.
			if (!RegSetValueEx(
				hKey,
				REG_CONSOLE,
				0,
				REG_DWORD,
				(CONST BYTE *) &bConsoleReqd,
				sizeof(BOOL) ) == ERROR_SUCCESS)
				bStatus = FALSE;

			// bRestart
			if (bRestart && restartAvailable()) {
				DWORD dwBytesNeeded;
				WSO(L"%s%d", L"    Adding - Restart flag = %",bRestart);
				//First, tell the registry about the command line flag.
				if (!RegSetValueEx(
					hKey,
					REG_RESTART,
					0,
					REG_DWORD,
					(CONST BYTE *) &bRestart,
					sizeof(BOOL) ) == ERROR_SUCCESS)
					bStatus = FALSE;

				//Next, tell the SCM to actually DO the restart.  (See the
				//Recovery tab on properties of a service.)

				//Get the current configuration and modify it, rather than
				//trying to construct it entirely ourselves.

				lpfailActBuf = (LPSERVICE_FAILURE_ACTIONS) LocalAlloc(LPTR, sizeof(SERVICE_FAILURE_ACTIONS)); 

				if (! (*QuerySvcConfig2)(schService,
					SERVICE_CONFIG_FAILURE_ACTIONS,
					(char *)lpfailActBuf, 
					sizeof(SERVICE_FAILURE_ACTIONS),
					&dwBytesNeeded))
				{
					bStatus = FALSE;
					WSO(L"%s%s", L"ERROR: Failure in QueryServiceConfig2 - %", GetLastErrorText(szErr,256));
				} else {
					if (lpfailActBuf->cActions == 0) {
						//If there's a preexisting set of actions, modify
						//them.  Otherwise we need to set up our own buffer.
						lpfailActBuf->cActions = 3;
						lpfailActions = (LPSC_ACTION) LocalAlloc(LPTR, sizeof(SC_ACTION) * 3);
						lpfailActBuf->lpsaActions = lpfailActions;
					}
					lpfailActBuf->lpsaActions[0].Type = SC_ACTION_RESTART;
					//delay one minute, whch is the default if you do it manually.
					lpfailActBuf->lpsaActions[0].Delay = 60000;

					if (! (*ChangeSvcConfig2)(schService, SERVICE_CONFIG_FAILURE_ACTIONS, lpfailActBuf)) {
						WSO(L"%s%s", L"ERROR: Failed to set up system restart - %", GetLastErrorText(szErr,256));
						WSO(L"%s", L"You must use the Properties dialog in the Services tool for this service to manually set up automatic restart.");
					}
					if (lpfailActions != NULL)
						LocalFree(lpfailActions);
				}
				LocalFree(lpfailActBuf);
			}

			// bStatus
			//
			WSO(L"%s%d", L"    Adding - ConfigStatus = %",bStatus);
			if (!RegSetValueEx(hKey,
				REG_STATUS,
				0,
				REG_DWORD,
				(CONST BYTE *) &bStatus,
				sizeof(BOOL) ) == ERROR_SUCCESS) {
					WSO(L"%s%s%s", L"ERROR: Unable to install service '%' - %", serviceName, GetLastErrorText(szErr,256));
					if (!hasAdminPriv())
						WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
			}
			else {
				RegCloseKey(hKey);
				WSO(L"%s", L"  Done updating registry");
				WSO(L"%s%s", L"Service '%' successfully installed.", serviceName);
			}

			CloseServiceHandle(schService);
		}
		else {
			WSO(L"%s%s%s", L"ERROR: Unable to install service '%' - %", serviceName, GetLastErrorText(szErr,256));
			if (!hasAdminPriv())
				WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
		}
		CloseServiceHandle(schSCManager);
	}
	else {
		WSO(L"%s%s%s", L"ERROR: Unable to install service '%' - %", serviceName, GetLastErrorText(szErr,256));
		if (!hasAdminPriv())
			WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
	}
	Sleep(5000);

}   



//=========================================================================
//  ServiceRemove
//    - marks the specified service for deletion from the service control 
//      manager database. The database entry is not removed until all open 
//      handles to the service have been closed by calls to the 
//      CloseServiceHandle function, and the service is not running. A 
//      running service is stopped by a call to the ControlService function
//      with the SERVICE_CONTROL_STOP control code. If the service cannot 
//      be stopped, the database entry is removed when the system is 
//      restarted. 
//    - the service control manager deletes the service by deleting the 
//       service key and its subkeys from the registry
//=========================================================================
//
VOID ServiceRemove (WCHAR *serviceName)
{
	SC_HANDLE   schService;
	SC_HANDLE   schSCManager;

	WSO(L"%s%s", L"REMOVING SERVICE '%'", serviceName);

	schSCManager = OpenSCManager(NULL,                         // machine (NULL == local)
		NULL,                         // database (NULL == default)
		SC_MANAGER_ALL_ACCESS         // access required
		);

	if ( schSCManager != NULL )
	{
		schService = OpenService(schSCManager,       // handle to SCM database
			serviceName,        // name of service to open 
			SERVICE_ALL_ACCESS  // full access to service
			);

		if ( schService != NULL )
		{
			// try to stop the service
			//
			if ( ControlService(schService,               // handle to service
				SERVICE_CONTROL_STOP,     // control code
				&ssStatus ) )             // service status structure
			{
				wprintf(L"Stopping %s.", serviceName);
				Sleep( 1000 );

				// wait for service to stop
				//
				while( QueryServiceStatus( schService, &ssStatus ) )
				{
					if ( ssStatus.dwCurrentState == SERVICE_STOP_PENDING )
					{
						wprintf(L".");
						Sleep( 1000 );
					}
					else
						break;
				}

				wprintf(L"\n");
				if ( ssStatus.dwCurrentState == SERVICE_STOPPED )
					wprintf(L"%s stopped.\n", serviceName );
				else
					wprintf(L"%s failed to stop.\n", serviceName );
			}

			// now remove the service
			//
			if( DeleteService(schService) )
				wprintf(L"%s successfully removed.\n", serviceName );
			else
				wprintf(L"DeleteService failed - %s\n", GetLastErrorText(szErr,256));

			CloseServiceHandle(schService);
		}
		else {
			WSO(L"%s%s%s", L"ERROR: Unable to remove service % - %", serviceName, GetLastErrorText(szErr,256));
			if (!hasAdminPriv())
				WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
		}
		CloseServiceHandle(schSCManager);
	}
	else {
		WSO(L"%s%s%s", L"ERROR: Unable to remove service % - %", serviceName, GetLastErrorText(szErr,256));
		if (!hasAdminPriv())
			WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
	}
}



//=========================================================================
//  ServiceStart
//    - start the installed service from SCM
//    - open logfile if designated
//    - launch child process
//    - establish event object for the service
//    - establish event object for child process
//=========================================================================
//
VOID ServiceStart (WCHAR *serviceName)
{
	SECURITY_ATTRIBUTES saAttr;
	STARTUPINFO   siStartInfo;
	DWORD          pStatus;

	// gather service info from registry and load into service struct
	//
	if (!ServiceGetConfig(serviceName))
		exit(0);

	if (bConsoleReqd && bServiceProcess)
		AllocConsole();

	if (service.szLogFile[0] != 0) 
	{
		// Initialize the security structure. The security structure contains the 
		// security descriptor for an object and specifies whether the handle 
		// retrieved by specifying this structure is inheritable.
		//
		memset(&saAttr, 0, sizeof(SECURITY_ATTRIBUTES));
		saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
		saAttr.bInheritHandle = TRUE;
		saAttr.lpSecurityDescriptor = NULL;

		// Setup the logfile and handle
		//
		WSO(L"%s%s", L"Setup logfile '%'", service.szLogFile);

		DeleteFile(service.szLogFile);  // do here instead of CreateFile to avoid errors

		hFileOut = CreateFile(service.szLogFile,      // the logfile 
			GENERIC_WRITE,          // open for writing   
			FILE_SHARE_READ,        // share mode
			&saAttr,                // security        
			OPEN_ALWAYS,            // opens file if exists, create if not      
			FILE_ATTRIBUTE_NORMAL,  // normal file        
			(HANDLE) NULL);         // no attr. template 

		if (hFileOut == INVALID_HANDLE_VALUE) 
		{
			wsprintf(msgBuf, L"'%s' service unable to open log file '%s' - %s", serviceName,
				service.szLogFile, GetLastErrorText(szErr,256));
			ReportEventMsg(EVENTLOG_ERROR_TYPE,msgBuf);
			ServiceCleanup();
		}

		// Add header info to logfile    (????? NEED TIMESTAMP FOR LOGFILE)
		//
		if (!WSO(L"%s%s", L"******************** (%) LOG FILE ********************\r\n", service.szServiceName))
		{
			wsprintf(msgBuf, L"'%s' service unable to write to log file '%s' - %s", serviceName,
				service.szLogFile,GetLastErrorText(szErr,256));
			ReportEventMsg(EVENTLOG_ERROR_TYPE,(LPTSTR) msgBuf);
			CloseHandle(hFileOut);
			ServiceCleanup();
		}
		else 
			WSO(L"%s%s", L"Service started: %\r\n", time_stamp(msgBuf));

		WSO(L"%s%s", L">>> Output redirected to logfile '%'", service.szLogFile);
	}

	// Set up members of STARTUPINFO structure.
	//
	WSO(L"%s", L"initialize 'STARTUPINFO'");
	memset(&pInfo, 0, sizeof(PROCESS_INFORMATION));  // initialize process info too
	memset(&siStartInfo, 0, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);   // byte-size of STARTUPINFO structure
	siStartInfo.lpReserved = NULL;          // reserved
	siStartInfo.lpDesktop = NULL;
	siStartInfo.lpTitle = NULL;             // title bar (null=executable)
	siStartInfo.lpReserved2 = NULL;         // reserved
	siStartInfo.cbReserved2 = 0;            // reserved, must be 0
	siStartInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES; // window config bitfield
	siStartInfo.wShowWindow = SW_HIDE;      // how window will be shown
	siStartInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

	// If logfile is specified redirect output to logfile otherwise redirect output
	// to the std output (which is the console window by default)
	//
	if (service.szLogFile[0] != 0) {
		siStartInfo.hStdOutput = hFileOut;
		siStartInfo.hStdError = hFileOut;
	}
	else if (bConsoleReqd) {
		siStartInfo.hStdOutput = hConsoleOut;
		siStartInfo.hStdError = hConsoleOut;
	} else {
		// If there's no console or log, we better not try to inherit
		// stdout.  But remember to include STARTF_USESHOWWINDOW from above.
		siStartInfo.dwFlags = STARTF_USESHOWWINDOW;
	}

	// Launch a process thread using default security descriptor
	//
	WSO(L"%s", L"CREATE SERVICE PROCESS");
	if (!CreateProcess(
		service.szProgram,      // application to execute
		service.szParameters,   // command line                     
		NULL,                    // process security attributes       
		NULL,                    // primary thread security attributes
		TRUE,                   // handles are inherited             
		NORMAL_PRIORITY_CLASS,
		NULL,                   // environment variables          
		NULL,                   // current directory            
		&siStartInfo,            // STARTUPINFO pointer (input)              
		&pInfo))                // receives PROCESS_INFORMATION (output)    
	{
		WSO(L"%s", L"ERROR: Process could not be run");
		wsprintf(msgBuf, L"ERROR: Failed to start service process '%s' - %s",
			service.szProgram, GetLastErrorText(szErr,256));
		ReportEventMsg(EVENTLOG_ERROR_TYPE,(LPTSTR) msgBuf);

		ServiceCleanup();
	}

	// report the status to the service control manager.
	//
	if (!ReportStatusToSCMgr(SERVICE_RUNNING, NO_ERROR, 0, 0))
		ServiceCleanup();

	// Create an event object and enter infinite wait. If the service
	// control manager sends a 'stop', the service_ctrl_handler will
	// perform a SetEvent in order to set the state of the event object
	// to 'signalled'. If the process is terminated, the event
	// object will automatically become 'signalled'. In either case,
	// the wait will end and the service will be stopped.  
	//
	hEvent[0] = pInfo.hProcess;                     // the child process
	hEvent[1] = CreateEvent(NULL,FALSE,FALSE,NULL); // service process

	if (hEvent[1] == NULL)
		WSO(L"%s", L"ERROR: Error creating event object");
	else
		WSO(L"%s", L"Event object created");

	wsprintf(msgBuf, L"The '%s' service has started successfully", serviceName);
	ReportEventMsg(EVENTLOG_INFORMATION_TYPE,msgBuf);

	pStatus = WaitForMultipleObjects(
		2,           // # of handles in object handle array
		hEvent,     // event object-handle array
		FALSE,      // wait flag (return if ANY object is signalled)
		INFINITE ); // time-out interval in milliseconds

	WSO(L"%s", L"Event object has been signalled.");
}



//=========================================================================
//  ServiceRun
//    - run the installed service
//=========================================================================
//
VOID ServiceRun (WCHAR *serviceName)
{
	SC_HANDLE   schService;
	SC_HANDLE   schSCManager;
	TCHAR       szMsgBuf[256];

	WSO(L"%s%s", L"RUNNING SERVICE '%'", serviceName);

	schSCManager = OpenSCManager(NULL,                         // machine (NULL == local)
		NULL,                         // database (NULL == default)
		SC_MANAGER_ALL_ACCESS         // access required
		);

	if ( schSCManager != NULL )
	{
		schService = OpenService(schSCManager,       // handle to SCM database
			serviceName,        // name of service to open 
			SERVICE_ALL_ACCESS  // full access to service
			);

		if ( schService != NULL )
		{
			WSO(L"%s%s", L"Starting '%'", serviceName);

			// try to start the service
			//
			if ( StartService(schService,               // handle of service
				0,                        // number of arguments
				NULL ) )                  // array of arguments
			{
				Sleep( 1000 );
				while( QueryServiceStatus( schService, &ssStatus ) )
				{
					if ( ssStatus.dwCurrentState == SERVICE_START_PENDING ) {
						WSO(L"%s", L".");
						Sleep( 1000 );
					}
					else
						break;
				}

				// Messages to the event log will be generated within ServiceStart which 
				// gets invoked by the installed service as a result of the call to
				// StartService
				//
				if ( ssStatus.dwCurrentState == SERVICE_RUNNING )
					WSO(L"%s%s", L"Service '%' successfully started", serviceName);
				else {
					// if there's an error here it probably means that the service started OK, but
					// the process started and then stopped (therefore the service probably
					// has stopped by now
					//
					wsprintf(szMsgBuf, L"ERROR: Problem launching process for service '%s'. Please examine the console or logfile for details", serviceName);
					//  WSO("%s%s%s","ERROR: Service '%' failed to start - %", serviceName, GetLastErrorText(szErr,256));
					ReportEventMsg(EVENTLOG_ERROR_TYPE,szMsgBuf);
					QueryServiceStatus(schService, &ssStatus);
					if (ssStatus.dwCurrentState == SERVICE_STOPPED || ssStatus.dwCurrentState == SERVICE_STOP_PENDING) {
						wsprintf(szMsgBuf, L"Service '%s' has stopped", serviceName);
						//  WSO("%s%s%s","ERROR: Service '%' failed to start - %", serviceName, GetLastErrorText(szErr,256));
						ReportEventMsg(EVENTLOG_WARNING_TYPE,szMsgBuf);
					}

				}
			}

			CloseServiceHandle(schService);
		}
		else {
			wsprintf(szMsgBuf, L"ERROR: Unable to start service '%s'", serviceName);
			ReportEventMsg(EVENTLOG_ERROR_TYPE,szMsgBuf);
		}

		CloseServiceHandle(schSCManager);
	}
	else
		WSO(L"%s%s%s", L"ERROR: Unable to start service '%' - %", serviceName, GetLastErrorText(szErr,256));

	Sleep(5000);
}



//=========================================================================
//  ServiceStop
//    - send request to SCM to stop the service
//=========================================================================
//
VOID ServiceStop (WCHAR *serviceName)
{
	SC_HANDLE   schService;
	SC_HANDLE   schSCManager;

	schSCManager = OpenSCManager(NULL,                         // machine (NULL == local)
		NULL,                         // database (NULL == default)
		SC_MANAGER_ALL_ACCESS         // access required
		);

	if ( schSCManager != NULL )
	{
		schService = OpenService(schSCManager,       // handle to SCM database
			serviceName,        // name of service to open 
			SERVICE_ALL_ACCESS  // full access to service
			);

		if ( schService != NULL )
		{
			if ( !ControlService(schService,             // handle to service
				SERVICE_CONTROL_STOP,   // control code
				&ssStatus ) )           // service status structure

				WSO(L"%s%s%s", L"ERROR:Unable to stop service '%' - %", serviceName, GetLastErrorText(szErr,256));
			else {
				WSO(L"%s%s", L"Service '%' has been stopped.\r\n", serviceName);
			}

			CloseServiceHandle(schService);
		}
		CloseServiceHandle(schSCManager);
	}
}



//=========================================================================
//  ServiceCleanup
//    - flush logfile buffer if open
//    - close all open handles
//    - kill the process if it still exists
//    - release the console
//    - stop the service
//=========================================================================
//
VOID ServiceCleanup ()
{
	DWORD processStatus = 0;

	WSO(L"%s", L"CLEAN UP & STOP SERVICE");
	WSO(L"%s%s", L"\r\nService stopped: %",time_stamp(msgBuf));

	if (pInfo.hProcess != NULL) {

		// Find out whether it exited yet.
		GetExitCodeProcess(pInfo.hProcess,&processStatus);

		if (processStatus == STILL_ACTIVE) {
			TerminateProcess(pInfo.hProcess,0);
			GetExitCodeProcess(pInfo.hProcess,&processStatus);
		}
	}

	// try to report the stopped status to the service control manager.
	if (dwGlobalErr != ERROR_SUCCESS)
		ReportStatusToSCMgr(SERVICE_STOP_PENDING, dwGlobalErr, 0, 0);
	else
		ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0, 0);
	// release the event object
	//
	if (hEvent[1] != INVALID_HANDLE_VALUE && hEvent[1] != NULL) 
		CloseHandle(hEvent[1]);

	// release the file object
	//
	if (hFileOut != INVALID_HANDLE_VALUE && hFileOut != NULL) {
		FlushFileBuffers(hFileOut);
		CloseHandle(hFileOut);
	}

	// release the console object
	//
	if (bServiceProcess)
		FreeConsole();
	if (hConsoleOut != INVALID_HANDLE_VALUE && hConsoleOut != NULL) 
		CloseHandle(hConsoleOut);

	// In the doc for the SERVICE_FAILURE_ACTIONS structure we find the
	// statement: "A service is considered failed when it terminates
	// without reporting a status of SERVICE_STOPPED to the service
	// controller."  Thus if we wish to be restarted (bRestart true), we
	// must not report SERVICE_STOPPED.
	if (!bRestart)
		ReportStatusToSCMgr(SERVICE_STOPPED, NO_ERROR, 0, 0);
	// When SERVICE MAIN FUNCTION returns in a single service
	// process, the StartServiceCtrlDispatcher function in
	// the main thread returns, terminating the process.

	exit(processStatus);
}


BOOL hasAdminPriv()
{
	HANDLE Token;
	DWORD BytesRequired;
	PTOKEN_GROUPS Groups;
	BOOL b;
	DWORD i;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;

	// Open the process token.
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&Token)) {
		return(GetLastError() == ERROR_CALL_NOT_IMPLEMENTED);   // Chicago 
	}

	b = FALSE;
	Groups = NULL;

	// Get group information.
	if(!GetTokenInformation(Token,TokenGroups,NULL,0,&BytesRequired)
		&& (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		&& (Groups = (PTOKEN_GROUPS)LocalAlloc(LPTR,BytesRequired))
		&& GetTokenInformation(Token,TokenGroups,Groups,BytesRequired,&BytesRequired)) {

			b = AllocateAndInitializeSid(&NtAuthority,
				2,
				SECURITY_BUILTIN_DOMAIN_RID,
				DOMAIN_ALIAS_RID_ADMINS,
				0, 0, 0, 0, 0, 0,
				&AdministratorsGroup);
			if(b) {
				/* See if the user has the administrator group.*/
				b = FALSE;
				for(i=0; i<Groups->GroupCount; i++) {
					if(EqualSid(Groups->Groups[i].Sid,AdministratorsGroup)) {
						b = TRUE;
						break;
					}
				}
				FreeSid(AdministratorsGroup);
			}
	}

	// Clean up and return.

	if(Groups) {
		LocalFree((HLOCAL)Groups);
	}

	CloseHandle(Token);

	return(b);
}

//=========================================================================
//  ServiceHelp
//    - display GSERVICE arguments and syntax to console
//=========================================================================
//
VOID  ServiceHelp()
{
	wprintf(L"GSERVICE Startup Options:\n");
	wprintf(L"------------------------\n");
	wprintf(L"\n" );
	wprintf(L"%s install <service name> [<args>]   to install service\n", SERVICENAME );
	wprintf(L"  args:\n" );
	wprintf(L"    program=<program path+name>\n" );
	wprintf(L"    parameters=<command line args of program>\n" );
	wprintf(L"    module-search-path='search path 1' 'search path 2' ...\n" );
	wprintf(L"    logfile=<logfile path+name>\n" );
	wprintf(L"    console=<true,[false]>\n" );
	if (restartAvailable())
		wprintf(L"    restart=<[true],false>\n" );
	wprintf(L"    dependson=\"service1,service2,...\"\n" );
	wprintf(L"\n" );
	wprintf(L"%s stop    <service name>     to stop service\n", SERVICENAME );
	wprintf(L"%s start   <service name>     to start service\n", SERVICENAME );
	wprintf(L"%s remove  <service name>     to remove service\n", SERVICENAME );
	wprintf(L"%s info    <service name>     to display installed service info\n", SERVICENAME );
	wprintf(L"%s debug   <service name>     to run installed service as a console app\n", SERVICENAME );
	if (!hasAdminPriv())
		wprintf(L"\nWarning!  GSERVICE requires Administrator privileges to operate!\nLogon as a user with administrator privileges in order to proceed.");
}



//=========================================================================
//  ServiceInfo
//    - report the values of each configuration parameter for this 
//      service
//    - report the startup parameters for this service
//=========================================================================
//
VOID  ServiceInfo( LPTSTR serviceName )
{
	LPQUERY_SERVICE_CONFIG lpqscBuf; 
	DWORD       dwBytesNeeded; 
	SC_HANDLE   schSCManager;
	WCHAR       szKey[256];
	HKEY        hKey = NULL;
	DWORD       bufSize;
	WCHAR       regData[MAX_PATH_X];
	LPSERVICE_FAILURE_ACTIONS lpfailActBuf;
	BOOL        bReallyRestart = FALSE;

	// Initialize 'service' struct
	//
	memset(&service, 0, sizeof(SERVICE));
	service.dwServiceType = GSERVICE_OPTIONS;

	schSCManager = OpenSCManager(
		NULL,                      // machine (NULL == local)
		NULL,                      // database (NULL == default)
		SC_MANAGER_ALL_ACCESS      // access required
		);

	if ( schSCManager != NULL )
	{
		schService = OpenService(schSCManager, 
			serviceName,
			SERVICE_ALL_ACCESS 
			);
		if (schService == NULL) {
			WSO(L"%s%s%s", L"ERROR: Unable to access service '%' - %", serviceName, GetLastErrorText(szErr,256));
			if (!hasAdminPriv())
				WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
			exit(0); 
		}
	}
	else {
		WSO(L"%s%s%s", L"ERROR: Unable to access service '%' - %", serviceName, GetLastErrorText(szErr,256));
		if (!hasAdminPriv())
			WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
		exit(0);
	}

	// Allocate a buffer for the information configuration. 
	//
	lpqscBuf = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, 4096); 
	if (lpqscBuf == NULL) 
		exit(0); // handle me ?????

	// get the service configuration from the SCM
	//
	if (! QueryServiceConfig( 
		schService, 
		lpqscBuf, 
		4096, 
		&dwBytesNeeded) ) 
	{
		LocalFree(lpqscBuf);

		if ( schService != NULL )
			CloseServiceHandle(schService);

		if ( schSCManager != NULL )
			CloseServiceHandle(schSCManager);

		exit(0);  // handle me ????? 
	}

	service.dwServiceType = lpqscBuf->dwServiceType;
	service.dwStartType = lpqscBuf->dwStartType;
	wcscpy(service.szDependsOn,UnpackDependencies(lpqscBuf->lpDependencies));
	LocalFree(lpqscBuf); 

	// open the registry key for this service
	//
	wsprintf(szKey, L"%s%s",DFLT_KEY,serviceName);
	RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		szKey,
		0,
		KEY_ALL_ACCESS,
		&hKey );

	if (hKey == NULL) {
		WSO(L"%s%s", L"ERROR: Unable to open registry service key for service '%'", service.szServiceName);
		WSO(L"%s%s%s", L"ERROR: Unable to start service '%' - %", service.szServiceName, GetLastErrorText(szErr,256));
		if (!hasAdminPriv())
			WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");

		if ( schService != NULL )
			CloseServiceHandle(schService);

		if ( schSCManager != NULL )
			CloseServiceHandle(schSCManager);
		return;
	}

	// get config status
	//
	bufSize = sizeof(BOOL);
	RegQueryValueEx(
		hKey,
		REG_STATUS,
		NULL, 
		NULL,
		(LPBYTE) &service.bStatus,
		&bufSize );

	// program
	//
	bufSize = sizeof(regData);
	if (RegQueryValueEx(
		hKey,
		REG_PROGRAM,
		NULL, 
		NULL,
		(LPBYTE) &regData,
		&bufSize ) == ERROR_SUCCESS)
		wcscpy(service.szProgram,regData);

	// parameters
	//
	bufSize = sizeof(regData);
	if (RegQueryValueEx(
		hKey,
		REG_PARAMETERS,
		NULL, 
		NULL,
		(LPBYTE) &regData,
		&bufSize ) == ERROR_SUCCESS)
		wcscpy(service.szParameters,regData);

	// logfile
	//
	bufSize = sizeof(regData);
	if (RegQueryValueEx(
		hKey,
		REG_LOGFILE,
		NULL, 
		NULL,
		(LPBYTE) &regData,
		&bufSize ) == ERROR_SUCCESS)
		wcscpy(service.szLogFile,regData);

	// account
	//
	bufSize = sizeof(regData);
	if (RegQueryValueEx(
		hKey,
		REG_ACCOUNT,
		NULL, 
		NULL,
		(LPBYTE) &regData,
		&bufSize ) == ERROR_SUCCESS)
		wcscpy(service.szAccount,regData);

	bufSize = sizeof(BOOL);
	RegQueryValueEx(
		hKey,
		REG_CONSOLE,
		NULL, 
		NULL,
		(LPBYTE) &bConsoleReqd,
		&bufSize );

	bufSize = sizeof(BOOL);
	RegQueryValueEx(
		hKey,
		REG_RESTART,
		NULL, 
		NULL,
		(LPBYTE) &bRestart,
		&bufSize );

	if (bRestart && restartAvailable()) {

		lpfailActBuf = (LPSERVICE_FAILURE_ACTIONS) LocalAlloc(LPTR, 4096); 

		if (! (*QuerySvcConfig2)(schService,
			SERVICE_CONFIG_FAILURE_ACTIONS,
			(char *)lpfailActBuf, 
			4096, 
			&dwBytesNeeded))
		{
			LocalFree(lpfailActBuf);
			WSO(L"%s%s", L"ERROR: Failure in QueryServiceConfig2 - %", GetLastErrorText(szErr,256));
		} else {
			if (lpfailActBuf->cActions > 0) {
				int i;
				for (i=0; i<3; i++)
					if (lpfailActBuf->lpsaActions[i].Type == SC_ACTION_RESTART)
						bReallyRestart = TRUE;
			}
			LocalFree(lpfailActBuf);
		}
	}

	// close all open handles
	//
	if ( hKey != NULL)
		RegCloseKey(hKey);

	if ( schService != NULL )
		CloseServiceHandle(schService);

	if ( schSCManager != NULL )
		CloseServiceHandle(schSCManager);

	// printout the service info
	//
	wprintf(L"\n");
	wprintf(L"GSERVICE Service Information\n");
	wprintf(L"----------------------------\n");
	wprintf(L"Note: If service settings change while the service is running the\n");
	wprintf(L"changes will not take effect until the service has been stopped\n");
	wprintf(L"and restarted.\n");

	wprintf(L"Name         : %s\n",serviceName);
	wprintf(L"Status       : %s\n",SBOOLEAN(service.bStatus));
	wprintf(L"Program      : %s\n",SNULL(service.szProgram));
	wprintf(L"Parameters   : %s\n",SNULL(service.szParameters));
	wprintf(L"Logfile      : %s\n",SNULL(service.szLogFile));
	wprintf(L"Account      : %s\n",SNULL(service.szAccount));

	if (bConsoleReqd) 
		wprintf(L"Console      : TRUE\n");
	else
		wprintf(L"Console      : FALSE\n");

	if (service.dwStartType == SERVICE_AUTO_START) 
		wprintf(L"Mode         : AUTO-START\n");
	else if (service.dwStartType == SERVICE_DEMAND_START) 
		wprintf(L"Mode         : MANUAL\n");
	else
		wprintf(L"Mode         : DISABLED\n");

	if (bRestart) {
		wprintf(L"Restart      : TRUE\n");
		if (bReallyRestart)
			wprintf(L"             : System will restart service on failure.\n");
		else
			wprintf(L"             : Note:  the system will NOT restart service on failure.\n");
	}
	else
		if (restartAvailable())
			wprintf(L"Restart      : FALSE\n");
		else
			wprintf(L"Restart      : Not Available\n");

	if (service.szDependsOn != NULL && service.szDependsOn[0] != 0)
		wprintf(L"Dependencies : %s\n", service.szDependsOn);
}



//=========================================================================
//  ServiceGetConfig
//    - extract service configuration parameters from NT registry
//    - parameters were set during service installation
//=========================================================================
//
BOOL  ServiceGetConfig(WCHAR *serviceName )
{
	HKEY       hKey = NULL;
	WCHAR      szKey[256];
	WCHAR      regData[MAX_PATH_X];
	DWORD      bufSize;

	// Initialize 'service' struct
	//
	memset(&service, 0, sizeof(SERVICE));
	wcscpy(service.szServiceName, serviceName);

	// open the registry key associated with this service
	//
	wsprintf(szKey, L"%s%s", DFLT_KEY, service.szServiceName);
	RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		szKey,
		0,
		KEY_ALL_ACCESS,
		&hKey );

	if (hKey == NULL) {
		WSO(L"%s%s", L"ERROR: Unable to open registry service key. Service '%' has not been installed.", service.szServiceName);
		WSO(L"%s%s%s", L"ERROR: Unable to start service '%' - %", service.szServiceName, GetLastErrorText(szErr,256));
		if (!hasAdminPriv())
			WSO(L"%s", L"WARNING: User does not have administrator privilege.\nLogon as a user with administrator privileges in order to proceed.");
		return(FALSE);
	}

	// get config status first. If status is bogus then return as the state of
	// the config parameters may be questionable
	//
	bufSize = sizeof(BOOL);
	RegQueryValueEx(
		hKey,
		REG_STATUS,
		NULL, 
		NULL,
		(LPBYTE) &service.bStatus,
		&bufSize );

	if (!service.bStatus) {
		RegCloseKey(hKey);
		WSO(L"%s%s", L"ERROR: Service '%' has not been properly installed",service.szServiceName);
		ReportEventMsg(EVENTLOG_ERROR_TYPE, L"ERROR: Service startup failed. Service has not been properly installed.");
		return(FALSE);
	}

	// program - get the path+program to run under this service
	//
	bufSize = sizeof(regData);
	if (RegQueryValueEx(
		hKey,
		REG_PROGRAM,
		NULL, 
		NULL,
		(LPBYTE) &regData,
		&bufSize ) == ERROR_SUCCESS)
		wcscpy(service.szProgram, regData);

	// parameters - get the command-line arguments for the program process
	//
	bufSize = sizeof(regData);
	if (RegQueryValueEx(
		hKey,
		REG_PARAMETERS,
		NULL, 
		NULL,
		(LPBYTE) &regData,
		&bufSize ) == ERROR_SUCCESS)
		wcscpy(service.szParameters, regData);

	// logfile - get the path+logfile for the service
	//
	bufSize = sizeof(regData);
	if (RegQueryValueEx(
		hKey,
		REG_LOGFILE,
		NULL, 
		NULL,
		(LPBYTE) &regData,
		&bufSize ) == ERROR_SUCCESS)
		wcscpy(service.szLogFile, regData);

	// restart -- whether to restart upon exit of process
	bufSize = sizeof(BOOL);
	RegQueryValueEx(
		hKey,
		REG_RESTART,
		NULL, 
		NULL,
		(LPBYTE) &bRestart,
		&bufSize );

	// ConsoleReqd -- does the user want to see the console for the service?
	bufSize = sizeof(BOOL);
	RegQueryValueEx(
		hKey,
		REG_CONSOLE,
		NULL, 
		NULL,
		(LPBYTE) &bConsoleReqd,
		&bufSize );

	if ( hKey != NULL)
		RegCloseKey(hKey);

	return(TRUE);
}



//=========================================================================
//  ReportStatusToSCMgr
//    - update the 'status' field of the service control manager
//=========================================================================
//
BOOL ReportStatusToSCMgr ( DWORD dwCurrentState,
	DWORD dwWin32ExitCode,
	DWORD dwCheckPoint,
	DWORD dwWaitHint )
{
	BOOL bResult = TRUE;

	// if service has not been started from the SCM then return as the
	// inquiry functions will crash if not connected to the SCM
	if (!bServiceProcess)
		return(bResult);

	// Disable control requests until the service is started.
	//
	if (dwCurrentState == SERVICE_START_PENDING)
		ssStatus.dwControlsAccepted = 0;
	else
		ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP |
		SERVICE_ACCEPT_PAUSE_CONTINUE;

	// These SERVICE_STATUS members are set from parameters.
	//
	ssStatus.dwCurrentState = dwCurrentState;
	if (dwWin32ExitCode == NO_ERROR)
		ssStatus.dwWin32ExitCode = NO_ERROR;
	else {
		ssStatus.dwServiceSpecificExitCode = dwWin32ExitCode;
		ssStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
	}
	ssStatus.dwCheckPoint = dwCheckPoint;
	ssStatus.dwWaitHint = dwWaitHint;

	// Report the status of the service to the service control manager.
	//
	if (!(bResult = SetServiceStatus( 
		sshStatusHandle,    // service reference handle
		&ssStatus))) {      // SERVICE_STATUS structure

			// If an error occurs, stop the service.
			//
			ServiceCleanup();
			//  StopJobService("SetServiceStatus");
	}
	return bResult;
}


//=========================================================================
//  ReportEventMsg
//    - report an error in the NT 'Event Log' under 'Application'
//      event detail
//    - can be used by any thread to report an error
//=========================================================================
//
VOID ReportEventMsg (WORD status, WCHAR *lpszMsg)
{
	WCHAR		chMsg[1024];
	WCHAR		chMsg2[1024];
	HANDLE	hEventSource;
	LPTSTR	lpszStrings[2];
	LPVOID	lpMessageBuffer;
	WORD		nStr;

	// EVENTLOG_ERROR_TYPE        Error event
	// EVENTLOG_WARNING_TYPE      Warning event
	// EVENTLOG_INFORMATION_TYPE  Information event

	dwGlobalErr = GetLastError();

	// Designate this service as the event source.
	//
	hEventSource = RegisterEventSource( 
		NULL,                   // local machine
		service.szServiceName); // the service name

	// format the event log message
	//
	if(!FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |       // alloc a buffer for the message
		FORMAT_MESSAGE_FROM_SYSTEM,            // search system message-table
		NULL,                                  // message definition location
		dwGlobalErr,                           // message ID
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // language ID
		(LPTSTR) &lpMessageBuffer,             // buffer for returned system message
		1024,                                  // minimum # bytes to alloc for output buffer
		NULL ))
	{
		lpMessageBuffer = NULL;
	}

	// compose the event message and log it. If it's not an info message then attach the
	// NT system error message and code to the end
	//

	nStr = 1;
	wsprintf(chMsg, L"\r\r%s", lpszMsg);
	if (status != EVENTLOG_INFORMATION_TYPE && dwGlobalErr != 5) {
		wsprintf(chMsg2, L"Windows NT Status: %d -- %s", dwGlobalErr, (WCHAR *)lpMessageBuffer);
		lpszStrings[1] = chMsg2;
		nStr++;
	}
	lpszStrings[0] = chMsg;

	// report the event to the event log
	//
	if (hEventSource != NULL) {
		ReportEvent(
			hEventSource,       // handle of event source
			status,             // event type
			0,                  // event category
			0,                   // event ID
			NULL,               // current user's SID
			nStr,               // strings in lpszStrings
			0,                  // no bytes of raw data
			lpszStrings,        // array of error strings
			NULL);              // no raw data

		// release the event source handle
		//
		DeregisterEventSource(hEventSource);
	}

	LocalFree(lpMessageBuffer);

	if (status != EVENTLOG_INFORMATION_TYPE) 
		WSO(L"%s%s", chMsg, chMsg2);

}



//=========================================================================
//  GetLastErrorText
//    - copies NT error message text and code to string
//=========================================================================
//
LPTSTR GetLastErrorText (WCHAR* lpszBuf, DWORD dwSize )
{
	DWORD   dwRet;
	LPTSTR  lpszTemp = NULL;

	dwRet = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL,
		GetLastError(),
		LANG_NEUTRAL,
		(LPTSTR)&lpszTemp,
		0,
		NULL );

	// supplied buffer is not long enough
	if ( !dwRet || ( (long)dwSize < (long)dwRet+14 ) )
		lpszBuf[0] = L'\0';
	else
	{
		lpszTemp[lstrlen(lpszTemp)-2] = L'\0';  //remove cr and newline character
		wsprintf( lpszBuf, L"%s (0x%x)", lpszTemp, GetLastError() );
	}

	if (lpszTemp)
		LocalFree((HLOCAL) lpszTemp );

	return lpszBuf;
}

/* Microsoft API functions are all actually defined as function_nameA
or function_nameW, whereas you would just type in function_name in
your code.  We need to get the actual name for two such functions,
QueryServiceConfig2 and ChangeServiceConfig2, as strings, so that
we can get their addresses in the DLL.  Here we use two levels of
macro indirection in order to stringify the macro name.  Kudos to
David Kuznick. */
#define stringifier(x) #x
#define macroizer(x) stringifier(x)

void fillInADVAPI32 () {
	if (advapi32 == NULL)
		advapi32 = GetModuleHandle(L"ADVAPI32.DLL");
	if (advapi32 == NULL) {
		WSO(L"ERROR:  Can't find ADVAPI32.DLL");
		return;
	}
	QuerySvcConfig2 = GetProcAddress(advapi32, macroizer(QueryServiceConfig2));
	ChangeSvcConfig2 = GetProcAddress(advapi32, macroizer(ChangeServiceConfig2));
}

BOOL restartAvailable() {
	if (advapi32 == NULL)
		fillInADVAPI32();
	return QuerySvcConfig2 != NULL;
}



//=========================================================================
//  WSO ( "Write Stuff Out" ? )
//    - format a dynamic message and send to appropriate output locations:
//      (1) The log file
//      (2) The console
//      (3) stdout with printf if that's not working
//
//  Returns true if it succeeded in writing to logfile and/or console
//  (if appropriate).  False if punted to printf or either WriteFile
//  or WriteConsole failed.
//=========================================================================
//

BOOL  WSO (WCHAR* argtypes,...)
{
#define MSG_SZ MAX_PATH_X
#define MAX_SUB 10
#define MSG_DELIM L'%'

	va_list   args;
	WCHAR     subbuf[MAX_SUB][MSG_SZ];
	WCHAR     *fptr;
	DWORD     len,num,msg_len,n;
	WCHAR     *ptr1,*ptr2,*ptr3;
	DWORD     replace_cnt;
	WCHAR     msg[MSG_SZ*MAX_SUB+1];
	DWORD     numBytesWritten;
	char      newMsg[4 * (MSG_SZ * MAX_SUB + 1)];
	int       newMsgLength = 0;

	/*** get argtypes (e.g. %d) from the dynamic format list ***/
	va_start(args,argtypes);

	msg[0] = 0;
	len = 0;
	num = 0;
	for (fptr = argtypes; *fptr; fptr++) {
		if (*fptr != MSG_DELIM)
			continue;

		switch (fptr[1])
		{
		case 's':
			wcsncpy(subbuf[num], va_arg(args, WCHAR*), MSG_SZ); 
			subbuf[num][MSG_SZ] = 0;
			num++;
			break;
		case 'd':
			wsprintf(subbuf[num], L"%d\0", va_arg(args, int));
			num++;
			break;
		case 'c':
			wsprintf(subbuf[num], L"%c\0", va_arg(args,int));
			num++;
			break;
		case 'f':
			wsprintf(subbuf[num], L"%f\0", va_arg(args,double));
			num++;
			break;
		}
		len += wcslen(subbuf[num-1]);
	} 
	va_end(args);

	// replace MSG_DELIM in 1st string with args from other strings if they exist
	//
	replace_cnt = 0;
	if (num > 1 && len < MSG_SZ) {
		ptr1 = subbuf[0];
		ptr2 = msg;
		ptr3 = subbuf[1];
		msg_len = 0;
		n = 1;  
		while (*ptr1 != 0 && msg_len < MSG_SZ) 
		{
			if (*ptr1 == MSG_DELIM && n <= num) {
				replace_cnt++;
				ptr1++;
				while (*ptr3 != 0 && msg_len < MSG_SZ) {
					*ptr2++ = *ptr3++;
					msg_len++;
				}
				n++;
				ptr3 = subbuf[n];
			}
			else {
				*ptr2++ = *ptr1++;
				msg_len++;
			}
		}
		*ptr2 = 0;  
	}
	else
		wcscpy(msg, subbuf[0]);

	//If we're SUPPOSED to have a log file, but we DON'T actually have one,
	//printf and return "false" to say failed.
	if (service.szLogFile[0] != 0) {
		if (*msg == 0 || hFileOut == NULL || hFileOut == INVALID_HANDLE_VALUE) {
			wprintf(L"%s\n", msg);
			return(FALSE);
		}

		//OK, now try writing it to the logfile.
		wsprintf(fileBuffer, L"%s\r\n", msg);

		/*
			G2-2011 April 2014 release - funny characters in OPCClient log files
			
			Currently, almost all G2 components used single byte width char (CHAR). If gservice write things
			to log file by two bytes width char (WCHAR), the content in the log file will be garbled. As a 
			fix for this issue, change output wide string into a char string and then output it.
		*/
		newMsgLength = wcstombs(newMsg, fileBuffer, 4 * (MSG_SZ * MAX_SUB + 1));

		if (!WriteFile(
			hFileOut,		// logfile handle
			newMsg,			// message
			newMsgLength,		// length of message
			&numBytesWritten,	// # bytes written to logfile
			NULL))			// unused
			// if the write failed, return "false" to say failed.
			return(FALSE);

		FlushFileBuffers(hFileOut);
	}

	// get the console handle for std output and make sure its valid
	//
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);  
	if ( msg[0] == 0 || bServiceProcess == FALSE ||
		(bConsoleReqd &&
		(hConsoleOut == NULL || hConsoleOut == INVALID_HANDLE_VALUE))) {
			wprintf(L"%s\n", msg);

			//We return false here if we are a command line process to
			//indicate "failure".  But if we're on the console (bDebug
			//true), we want to return true, because we are supposed be a
			//command line process.  But we still don't want to write to the
			//console below, so returning after printf is necessary.  So,
			//return "bDebug" as the proper value.
			return(bDebug);
	}

	//Now, we're done, and we succeeded if we aren't supposed to be
	//printing to the console.
	if (!bConsoleReqd)
		return TRUE;

	// Write string to console screen buffer. Can use either Unicode characters or 
	// 8-bit (ANSI) characters from the console's current codepage. The console's 
	// codepage defaults initially to the system's OEM codepage. To change the 
	// console's codepage, use the SetConsoleCP or SetConsoleOutputCP functions, or
	// use the chcp or mode con cp select= commands
	// 
	wsprintf(fileBuffer, L"%s\n", msg);
	//Return value is whether we succeeded, WriteConsole returns true if
	//it succeeded, and so will we.
	return WriteConsole(
		hConsoleOut,                 // console handle
		fileBuffer,                  // message
		2 * wcslen(fileBuffer),  // length of message
		&numBytesWritten,            // # bytes written to logfile
		NULL );                      // unused
}



//=========================================================================
//  time_stamp
//=========================================================================
//
WCHAR *time_stamp(WCHAR *result)
{
	time_t t;
	char temp_result[100];
	size_t converted;

	if (result == NULL)
		return ((WCHAR *)NULL);

	time(&t);
	strftime(temp_result,21,"%d-%b-%y %H:%M:%S",localtime(&t));    

	mbstowcs_s(&converted, result, strlen(temp_result) + 1, temp_result, _TRUNCATE);
	return (result);
}

WCHAR *get_module_version()
{
	int len;
	DWORD junk;
	WCHAR *info;
	UINT iLen;
	WCHAR *versionstring;
	static WCHAR buf[128];

	/* first, find out the filename from where we were launched */
	GetModuleFileName(NULL, buf, 128);

	/* now figure out about the actual version: first the size of the after we need */
	len = GetFileVersionInfoSize(buf, &junk);

	if (len <= 0){
		return NULL;
	}
	info = malloc(len);
	if (info <= 0)
		return NULL;
	/* and now retrieve the info */
	if (!GetFileVersionInfo(buf, 0, len, info)) {
		return NULL;
	}
	/* and query it */
	if (!VerQueryValue(info, L"\\StringFileInfo\\040904E4\\FileVersion", (LPVOID*)&versionstring, &iLen)) {
		free(info);
		return NULL;
	}
	wcscpy(buf, versionstring);
	free(info);
	/* the caller of this should copy this string (but really we know that all
	they're doing is printing it) */
	return buf;
}
