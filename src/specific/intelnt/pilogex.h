/*-----------------------------------------------------------------------------

$Archive: /pi/freeze/intel/piapi/pilogex.h $
$Revision: 5 $     $Date: 5/27/08 3:21p $

-------------------------------------------------------------------------------

Copyright (c) 1995-2006 OSIsoft, Inc. All rights reserved. 
Unpublished - rights reserved under the copyright law of the United States.

    Portions by:    1993 Omicron, Philadelphia, PA

THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF
OSIsoft, INC.  USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF OSIsoft, INC.

RESTRICTED RIGHTS LEGEND
Use, duplication, or disclosure by the Government is subject to re-
strictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227.7013

OSIsoft, Inc.
777 Davis St., San Leandro CA 94577

-------------------------------------------------------------------------------

Description:  Prototypes and definitions for login functions.

-----------------------------------------------------------------------------*/ 

#ifndef __PILOGEX_H__
#define __PILOGEX_H__

#include "pidefs.h"

#ifdef __cplusplus  
extern "C" {
#endif      

typedef long PIOBJID; 

typedef unsigned short USHORT; 

#ifdef _WIN32

    #ifdef _ALPHA_

        #define DllImport
        #define DllExport

    #else

        #define DllImport   __declspec( dllimport )
        #define DllExport   __declspec( dllexport )

    #endif

    #define EXPORTPIINT32   DllExport int32 PIPROC
    #define EXPORTHINSTANCE DllExport HINSTANCE PIPROC
    #define EXPORTLONG      DllExport long PIPROC
    #define EXPORTVOID      DllExport void PIPROC

#else

    #define EXPORTPIINT32   int32 PIPROC _export
    #define EXPORTHINSTANCE HINSTANCE PIPROC _export
    #define EXPORTLONG      LONG PIPROC _export
    #define EXPORTVOID      void PIPROC _export

#endif

#ifndef SUCCESS 
#define SUCCESS 0
#endif

// error codes 
#define ERR_NOT_ENOUGH_MEMORY  0   
#define ERR_PI_DISCONNECT_INVALID_DLL -1
#define ERR_ALREADY_LOGGED_IN -2        
#define ERR_UNKNOWN_SERVER -3      
#define ERR_PI_ALLOC -4            
#define ERR_SERVER_NOT_CONNECTED -5
#define ERR_INVALID_SERVER -6
#define ERR_INVALID_NODE_ID -7
#define ERR_PI_STRING_TRUNCATED -8 
#define ERR_BAD_VALID_STATUS -9
#define ERR_DLL_ALREADY_LOADED   22     
#define ERR_PI_REGISTER_INVALID_DLL 23
#define ERR_PI_LOGIN_INVALID_DLL -100
#define ERR_PI_INVALID_WND_HANDLE -101
#define ERR_LOGIN_CANCELLED -102
#define ERR_TASK_PI_NOT_REGISTERED -103
#define ERR_LOGIN_UNSUCCESSFUL -104
#define ERR_LOGIN_USERNOTFOUND -105
#define ERR_NO_PILOGIN_REG -106
#define ERR_DEFINE_DLG_CANCELLED -107
#define ERR_LOGININI_LOC_NOWRITE -108
#define ERR_NO_PIPCINI -109
#define ERR_NO_WINDOWS_DIR -110
#define ERR_NO_PIHOME_PIPCSHARE -111
#define ERR_SERVER_EXISTS -112
#define ERR_BAD_SERVER_TYPE -113
#define ERR_NO_MORE 1
#define ERR_GET_FIRST_NOT_ISSUED -1
#define GETFIRST 0
#define GETNEXT 1
#define MAX_POINT_NUM_LEN 16
#define MAX_TAGNAME_LEN 256
#define MAX_NODENAME_LEN 30
#define MAX_USERNAME_LEN 30
// dialog ids needed to identify the dialog for the proper handling
// of the help ids
#define PILOGIN_LOGIN_DLGID 1
#define PILOGIN_CONNECTIONS_DLGID 2
#define PILOGIN_DEFINE_SERVER_DLGID 3
#define PILOGIN_INFORMATION_DLGID 4
#define PILOGIN_TAGSEARCH_DLGID 5
#define PILOGIN_POINTATT_DLGID 6
// PI Server Types
#define PILOGIN_SERVER_TYPE_PI 1000

/***********************Global  definitions*****************/

typedef struct _taglist
{
   char m_szServer [MAX_NODENAME_LEN];
   int32 m_lNodeId; 
   char m_szTagName[MAX_TAGNAME_LEN];
   int32 m_lPoint;
   struct _taglist PIPTR* m_next;
} TAGLIST, *PTAGLIST, PIPTR* LPTAGLIST;

typedef struct _PiHelpIdList
{
   PIOBJID m_oidDlgId;
   int32 m_lHelpId;
   struct _PiHelpIdList PIPTR* m_next;
} PIHELPIDLIST, *PPIHELPIDLIST, PIPTR* LPPIHELPIDLIST;

/***********ENTRY Points in the DLL********************************/
// pilg_login - logs the user into a server
//////////////////////////////////////////////////////////////////
// codes returned by pilg_login:
// the return code from the actual piut_login, 
// piut_setservernode or
// ERR_LOGIN_CANCELLED -102
// ERR_UNKNOWN_SERVER -3
// ERR_PI_ALLOC -4
// ERR_PI_LOGIN_INVALID_DLL -100
// ERR_PI_INVALID_WND_HANDLE -101
// ERR_TASK_PI_NOT_REGISTERED -103
//////////////////////////////////////////////////////////////////
#if (defined(_WINDOWS) || defined(_WIN32))
EXPORTPIINT32
pilg_login
   (
   HWND hWndParent, // Application's parent window handle 
   LPCSTR lpszUserName, // user name 
   LPCSTR lpszNode, // node name
   LPCSTR lpszPassword,
   int32 PIPTR* valid
   );

typedef  int32 (PIPROC* TylpfnPiLogin)
   (
   HWND hWndParent, // Application's parent window handle 
   LPCSTR lpszUserName, // user name 
   LPCSTR lpszNode, // node name
   LPCSTR lpszPassword,
   int32 PIPTR* valid
   );
typedef  int32 (PIPROC* TYLPFNPILOGIN)
   (
   HWND hWndParent, // Application's parent window handle 
   LPCSTR lpszUserName, // user name 
   LPCSTR lpszNode, // node name
   LPCSTR lpszPassword,
   int32 PIPTR* valid
   );
#define PILOGIN "pilg_login"
#endif

/***************************************************************/
// pilg_getservername - gets server name given nodeId
///////////////////////////////////////////////////////////////
// codes returned by the pilg_getservername
// SUCCESS: 
// ERR_INVALID_NODE_ID if server not found;  lpszServerName = ""
// ERR_TASK_PI_NOT_REGISTERED -103
///////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_getservername
   (
   int32 lNodeId, // node id 
   char PIPTR* lpszServerName, // server name buffer
   int32 PIPTR* plBufSize  // size of the buffer  in/out
   );
typedef int32 (PIPROC* TylpfnPiGetServerName)
   (
   int32 lNodeId, // node id 
   char PIPTR* lpszServerName, // server name buffer
   int32 PIPTR* plBufSize  // size of the buffer  in/out
   );
typedef int32 (PIPROC* TYLPFNPIGETSERVERNAME)
   (
   int32 lNodeId, // node id 
   char PIPTR* lpszServerName, // server name buffer
   int32 PIPTR* plBufSize  // size of the buffer  in/out
   );

#define PIGETSERVERNAME "pilg_getservername"  

/**************************************************************/
// pilg_pointatt - point attribute dialog
///////////////////////////////////////////////////////////////
// codes returned by the pilg_pointatt:
// SUCCESS: if everything OK
// ERR_TASK_PI_NOT_REGISTERED -103
// ERR_PI_INVALID_WND_HANDLE -101
// ERR_PI_ALLOC -4
///////////////////////////////////////////////////////////////
#if (defined(_WINDOWS) || defined(_WIN32))
EXPORTPIINT32
pilg_pointattdlg
   (
   HWND hParentWnd, // parent window handle
   LPTAGLIST lptglstHead // head to the tag list
   );
typedef int32 (PIPROC* TylpfnPiPointAtt)
   (
   HWND hParentWnd, // parent window handle
   LPTAGLIST lptglstHead // head to the tag list
   );
typedef int32 (PIPROC* TYLPFNPIPOINTATT)
   (
   HWND hParentWnd, // parent window handle
   LPTAGLIST lptglstHead // head to the tag list
   );

#define PIPOINTATT "pilg_pointattdlg"  
#endif

/**************************************************************/
// pilg_getconnectedserver - gets all the connected servers  
// on GETFIRST/GETNEXT basis
////////////////////////////////////////////////////////////////////
// the info for the server is returned into
// lpszServerNameBuf, // server name buffer
// plBufSize, // buffer size - in/out
// plNodeId, // node id 
// plPort,   // port number
//
//
// Return codes:
// ERR_TASK_PI_NOT_REGISTERED -103,
// ERR_NO_MORE 1,
// ERR_GET_FIRST_NOT_ISSUED -1
// SUCCESS 0 if everything is OK
///////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_getconnectedserver
   (
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize, // buffer size - in/out
   int32 PIPTR* plNodeId, // node id 
   int32 PIPTR* plPort,   // port number
   int32  lSeq  // sequence GETFIRST, GETNEXT
   );
typedef int32(PIPROC* TylpfnPiGetConnectedServer)
   (
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize, // buffer size - in/out
   int32 PIPTR* plNodeId, // node id 
   int32 PIPTR* plPort,   // port number
   int32  lSeq  // sequence GETFIRST, GETNEXT
   );
typedef int32(PIPROC* TYLPFNPIGETCONNECTEDSERVER)
   (
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize, // buffer size - in/out
   int32 PIPTR* plNodeId, // node id 
   int32 PIPTR* plPort,   // port number
   int32  lSeq  // sequence GETFIRST, GETNEXT
   );
#define PIGETCONNECTEDSERVER "pilg_getconnectedserver" 

/**************************************************************/
// pilg_getselectedtag - gets all the seleccted tags by 
// the current task  on GETFIRST/GETNEXT basis
////////////////////////////////////////////////////////////////////
// the info for the server is returned into
// TAGLIST structure
//
// Return codes:
// ERR_TASK_PI_NOT_REGISTERED -103,
// ERR_NO_MORE 1,
// ERR_GET_FIRST_NOT_ISSUED -1
// SUCCESS 0 if everything is OK
///////////////////////////////////////////////////////////////
#if (defined(_WINDOWS) || defined(_WIN32))
EXPORTPIINT32
pilg_getselectedtag
   (
   LPTAGLIST lpcTagList, // tag list structure
   int32 lSeq  // sequence GETFIRST/GETNEXT
   );
typedef int32(PIPROC* TylpfnPiGetSelectedTag)
   (
   LPTAGLIST lpcTagList, // tag list structure
   int32 lSeq  // sequence GETFIRST/GETNEXT
   );
typedef int32(PIPROC* TYLPFNPIGETSELECTEDTAG)
   (
   LPTAGLIST lpcTagList, // tag list structure
   int32 lSeq  // sequence GETFIRST/GETNEXT
   );
#define PIGETSELECTEDTAG "pilg_getselectedtag"
#endif

/**************************************************************/
// pilg_getavailableserver - gets all the available servers  
// on GETFIRST/GETNEXT basis
////////////////////////////////////////////////////////////////////
// the info for the server is returned into
// lpszServerNameBuf, // server name buffer
// plBufSize, // buffer size - in/out
// plNodeId, // node id 
// plPort,   // port number
//
//
// Return codes:
// ERR_TASK_PI_NOT_REGISTERED -103,
// ERR_NO_MORE 1,
// ERR_GET_FIRST_NOT_ISSUED -1
// SUCCESS 0 if everything is OK
///////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_getavailableserver
   (
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize, // buffer size - in/out
   int32 PIPTR* plNodeId, // node id 
   int32 PIPTR* plPort,   // port number
   int32  lSeq  // sequence GETFIRST, GETNEXT
   );
typedef int32(PIPROC* TylpfnPiGetAvailableServer)
   (
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize, // buffer size - in/out
   int32 PIPTR* plNodeId, // node id 
   int32 PIPTR* plPort,   // port number
   int32  lSeq  // sequence GETFIRST, GETNEXT
   );
typedef int32(PIPROC* TYLPFNPIGETAVAILABLESERVER)
   (
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize, // buffer size - in/out
   int32 PIPTR* plNodeId, // node id 
   int32 PIPTR* plPort,   // port number
   int32  lSeq  // sequence GETFIRST, GETNEXT
   );
#define PIGETAVAILABLESERVER "pilg_getavailableserver"    

/**************************************************************/
// pilg_addnewserver - Adds a new server  
////////////////////////////////////////////////////////////////////
//   char PIPTR* lpszServerName,      // server name
//   UINT nServerType,          // Server Type
//   char PIPTR* lpszUserName,        // User name 
//   int32 lPortNum           // Port number for socket connection 
//
//
// Return codes:
// FALSE, Add Failed
// long node ID if everything went OK
///////////////////////////////////////////////////////////////
EXPORTLONG
pilg_addnewserver
   (
   char PIPTR* lpszServerName,        // server name
   UINT nServerType,            // Server Type
   char PIPTR* lpszUserName,          // User name 
   int32 lPortNum             // Port number for socket connection 
   );
typedef int32(PIPROC* TylpfnPiAddNewServer)
   (
   char PIPTR* lpszServerName,        // server name
   UINT nServerType,            // Server Type
   char PIPTR* lpszUserName,          // User name 
   int32 lPortNum             // Port number for socket connection 
   );
typedef int32(PIPROC* TYLPFNPIADDNEWSERVER)
   (
   char PIPTR* lpszServerName,        // server name
   UINT nServerType,            // Server Type
   char PIPTR* lpszUserName,          // User name 
   int32 lPortNum             // Port number for socket connection 
   );
#define PIADDNEWSERVER "pilg_addnewserver"       
// duplicate function for Installshield script to define same function in two DLLs
// 16 and 32 bit.
EXPORTLONG
pilg_addnewserver2
   (
   char PIPTR* lpszServerName,        // server name
   UINT nServerType,            // Server Type
   char PIPTR* lpszUserName,          // User name 
   int32 lPortNum             // Port number for socket connection 
   );
typedef int32(PIPROC* TylpfnPiAddNewServer2)
   (
   char PIPTR* lpszServerName,        // server name
   UINT nServerType,            // Server Type
   char PIPTR* lpszUserName,          // User name 
   int32 lPortNum             // Port number for socket connection 
   );
typedef int32(PIPROC* TYLPFNPIADDNEWSERVER2)
   (
   char PIPTR* lpszServerName,        // server name
   UINT nServerType,            // Server Type
   char PIPTR* lpszUserName,          // User name 
   int32 lPortNum             // Port number for socket connection 
   );
#define PIADDNEWSERVER2 "pilg_addnewserver2"       
/**********************************************************************/
// pilg_getdefserverinfo - gets default server info
////////////////////////////////////////////////////////////////////
// return  codes:  SUCCESS or
// ERR_TASK_PI_NOT_REGISTERED -103
// the total length of the server name is returned in
// *plBufSize.
/////////////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_getdefserverinfo
   ( 
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize,  // size of the buffer - in/out
   int32 PIPTR* plNodeId, // pointer to node id
   int32 PIPTR* plPort // pointer to port number
   );
typedef int32 (PIPROC* TylpfnPiGetDefServerInfo) 
   ( 
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize,  // size of the buffer - in/out
   int32 PIPTR* plNodeId, // pointer to node id
   int32 PIPTR* plPort // pointer to port number
   );
typedef int32 (PIPROC* TYLPFNPIGETDEFSERVERINFO) 
   ( 
   char PIPTR* lpszServerNameBuf, // server name buffer
   int32 PIPTR* plBufSize,  // size of the buffer - in/out
   int32 PIPTR* plNodeId, // pointer to node id
   int32 PIPTR* plPort // pointer to port number
   );
#define PIGETDEFSERVERINFO "pilg_getdefserverinfo"  

/**********************************************************************/
// pilg_getnodeid - gets the nodeid of the specified server
//    
// Returns: SUCCESS 0 
//          ERR_INVALID_SERVER -6
//       or ERR_TASK_PI_NOT_REGISTERED -103,
// the node id is returned in *plNodeId,
// if server not found *plNodeId = 0
////////////////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_getnodeid( 
   LPCSTR lpszServerName, // server name
   int32* plNodeId // pointer to node id 
   );
typedef int32 (PIPROC* TylpfnPiGetNodeId)
   ( 
   LPCSTR lpszServerName, // server name
   int32* plNodeId // pointer to node id 
   );
typedef int32 (PIPROC* TYLPFNPIGETNODEID)
   ( 
   LPCSTR lpszServerName, // server name
   int32* plNodeId // pointer to node id 
   );
#define PIGETNODEID "pilg_getnodeid"   

/**********************************************************************/
// pilg_setservernode - sets the server context 
////////////////////////////////////////////////////////////////////
// codes returned by pilg_setservernode:
// return code of the piut_setservernode
// ERR_TASK_PI_NOT_REGISTERED -103
/////////////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_setservernode
   ( 
   LPCSTR lpszServerName // server name 
   ); 
typedef int32 (PIPROC* TylpfnPiSetServerNode)
   (
   LPCSTR lpszServerName // server name 
   ); 
typedef int32 (PIPROC* TYLPFNPISETSERVERNODE)
   (
   LPCSTR lpszServerName // server name 
   ); 
#define PISETSERVERNODE "pilg_setservernode"  

/**********************************************************************/
// pilg_connectdlg - connections dialog
////////////////////////////////////////////////////////////////////////
// codes returned by pilg_connectdlg:
// 0 if everything is OK
// ERR_PI_INVALID_WND_HANDLE -101
// ERR_TASK_PI_NOT_REGISTERED -103  
////////////////////////////////////////////////////////////////////////
#if (defined(_WINDOWS) || defined(_WIN32))
EXPORTPIINT32
pilg_connectdlg
   (
   HWND hWndParent // parent window handle
   ); // call connections dialog
typedef int32  (PIPROC* TylpfnPiConnectDlg)  
   (
   HWND hWndParent // parent window handle
   );
typedef int32  (PIPROC* TYLPFNPICONNECTDLG)
   (
   HWND hWndParent // parent window handle
   );
#define PICONNECTDLG "pilg_connectdlg"
#endif

/**********************************************************************/
// tagsearch dialog
////////////////////////////////////////////////////////////////////////
// codes returned by pilg_tagsearchdlg:
// ERR_PI_INVALID_WND_HANDLE -101
// ERR_TASK_PI_NOT_REGISTERED -103  
//
////////////////////////////////////////////////////////////////////////
#if (defined(_WINDOWS) || defined(_WIN32))
EXPORTPIINT32
pilg_tagsearchdlg
   (
   HWND hWndParent // parent window handle
   ); // call connections dialog 
typedef int32 (PIPROC* TylpfnPiTagSearchDlg) 
   (
   HWND hWndParent // parent window handle
   ); // call connections dialog 
typedef int32 (PIPROC* TYLPFNPITAGSEARCHDLG) 
   (
   HWND hWndParent // parent window handle
   ); // call connections dialog 
#define PITAGSEARCHDLG "pilg_tagsearchdlg" 
#endif

/**********************************************************************/
// pilg_disconnect - disconnects the curent task from the servers
//////////////////////////////////////////////////////////////////
// codes returned by pilg_disconnect
// the return code of piut_disconnect or
// ERR_TASK_PI_NOT_REGISTERED -103,
// ERR_PI_DISCONNECT_INVALID_DLL -1
//////////////////////////////////////////////////////////////////
EXPORTPIINT32 pilg_disconnect();
typedef  int32 (PIPROC* TylpfnPiDisconnect)();
typedef  int32 (PIPROC* TYLPFNPIDISCONNECT)();
#define PIDISCONNECT "pilg_disconnect"
// const CString cstrPiDisconnect = "PILG_DISCONNECT";
/**********************************************************************/
// pilg_disconnectnode - disconnects curent task from a server
//////////////////////////////////////////////////////////////////
// codes returned by pilg_disconnectnode
// the return code of piut_disconnectnode or
// ERR_TASK_PI_NOT_REGISTERED -103,
// ERR_PI_DISCONNECT_INVALID_DLL -1
//////////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_disconnectnode
   (
   LPCSTR szServerName
   );
typedef  int32 (PIPROC* TylpfnPiDisconnectNode)(
   LPCSTR szServerName
   );
typedef  int32 (PIPROC* TYLPFNPIDISCONNECTNODE)(
   LPCSTR szServerName
   );
#define PIDISCONNECTNODE "pilg_disconnectnode"
// const CString cstrPiDisconnectNode = "PILG_DISCONNECTNODE"; 
    
/**********************************************************************/
// pilg_registerapp - registers the application, without registration
// the appliation does not have access to any of the services provided
// by the current DLL
//////////////////////////////////////////////////////////////////
// codes returned by pilg_registerapp:
// the instsance handle of the loaded DLL or
// ERR_NOT_ENOUGH_MEMORY  0 
// ERR_DLL_LOADED  22
// ERR_PI_REGISTER_INVALID_DLL 23
//////////////////////////////////////////////////////////////////
EXPORTHINSTANCE
pilg_registerapp
   (
   LPCSTR lpszDLLName // PI DLL Name
   );
typedef  HINSTANCE (PIPROC* TylpfnPiRegisterApp)
   (
   LPCSTR lpszDLLName  // PI DLL Name
   );
typedef  HINSTANCE (PIPROC* TYLPFNPIREGISTERAPP)
   (
   LPCSTR lpszDLLName  // PI DLL Name
   );
#define PIREGISTERAPP "pilg_registerapp"  

/**********************************************************************/
// pilg_unregisterapp - unregisters the application, cleans it up
// from the internal task login data base

EXPORTVOID pilg_unregisterapp();
typedef  void (PIPROC* TylpfnPiUnRegisterApp)();
typedef  void (PIPROC* TYLPFNPIUNREGISTERAPP)();

#define PIUNREGISTERAPP "pilg_unregisterapp"  

//////////////////////////////////////////////////////////////////
/**********************************************************************/
// pilg_registerhelp - registers the pilogin help for the application
// if pilg_registerhelp is not called the default help file ( from pilogin.ini)
// will be used.
// codes returned by pilg_registerhelp:
// SUCCESS if help registered 
// ERR_TASK_PI_NOT_REGISTERED if task not registered
//////////////////////////////////////////////////////////////////   
#if (defined(_WINDOWS) || defined(_WIN32))
EXPORTPIINT32
pilg_registerhelp
   (
   LPCSTR lpszHelpFile, // name for the help file
   LPPIHELPIDLIST lplstHelpId // pointer to help id list
   );
typedef  int32 (PIPROC* TylpfnPiRegisterHelp)
   (
   LPCSTR lpszHelpFile, // name for the help file
   LPPIHELPIDLIST lplstHelpId // pointer to help id list
   );
typedef  int32 (PIPROC* TYLPFNPIREGISTERHELP)
   (
   LPCSTR lpszHelpFile, // name for the help file
   LPPIHELPIDLIST lplstHelpId // pointer to help id list
   );
#define PIREGISTERHELP "pilg_registerhelp" 
#endif

//////////////////////////////////////////////////////////////////
/**********************************************************************/
// pilg_odbcloginfo
// Descript: Returns user name and password for a specified server if
//           the current task has logged into this server.
// Returns:  SUCCESS if user name is found for the passed server - pw is 
//           returned.
//           otherwise: 
//           ERR_PI_STRING_TRUNCATED - if user name or/and password truncated,
//                                     this is conditionally successful
//           ERR_LOGIN_USERNOTFOUND - if user/server combination not found   
//           ERR_UNKNOWN_SERVER - if server is not found in map
/**********************************************************************/
///////////////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_odbcloginfo
   (
   LPCSTR lpszServerName, // in - server name 
   char PIPTR* lpszUserName, // out -  user name 
   USHORT* pusUnameLen, //in,out - user name length
   char PIPTR* lpszPassword, // out - password
   USHORT* pusPasswordLen,  // in, out - password len
   long*   valid       // out - valid status flag
   );
typedef  int32 (PIPROC* TylpfnOdbcLogInfo)
   (
   LPCSTR lpszServerName, // in - server name 
   char PIPTR* lpszUserName, // out -  user name 
   USHORT* pusUnameLen, //in,out - user name length
   char PIPTR* lpszPassword, // out - password
   USHORT* pusPasswordLen,  // in, out - password len
   long*   valid       // out - valid status flag
   );
typedef  int32 (PIPROC* TYLPFNODBCLOGINFO)
   (
   LPCSTR lpszServerName, // in - server name 
   char PIPTR* lpszUserName, // out -  user name 
   USHORT* pusUnameLen, //in,out - user name length
   char PIPTR* lpszPassword, // out - password
   USHORT* pusPasswordLen,  // in, out - password len
   long*   valid       // out - valid status flag
   );
#define PIODBCLOGINFO "pilg_odbcloginfo"

//////////////////////////////////////////////////////////////////
/**********************************************************************/
// pilg_logindialog
// Descript: invokes the login dialog box.
// Returns:  SUCCESS if everything is OK ,
//           otherwise: 
//        ERR_PI_INVALID_WND_HANDLE   -101 no window handle
//        ERR_UNKNOWN_SERVER  -3 no server known
//        ERR_PI_ALLOC  -4 cannot allocate memory for dialog box display
//        IDOK if On Ok
//        IDCANCEL if on Cancel
/**********************************************************************/
///////////////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_logindialog
   (
        HWND    hWndParent,             // application's parent window handle
        char PIPTR*   lpszServerName,         // in server name
        int32 PIPTR* pusServerName,      // in, out server name length
        char PIPTR*       lpszUserName,       // in user name
        int32 PIPTR* pusUserName,       // in out user name length
        char PIPTR*       lpszPassword,           // out password
        int32 PIPTR* pisPasswordLen     // in, out password length
   );
typedef  int32 (PIPROC* TylpfnLoginDialog)
   (
        HWND    hWndParent,             // application's parent window handle
        char PIPTR*   lpszServerName,         // in server name
        int32 PIPTR* pusServerName,      // in, out server name length
        char PIPTR*       lpszUserName,       // in user name
        int32 PIPTR* pusUserName,       // in out user name length
        char PIPTR*       lpszPassword,           // out password
        int32 PIPTR* pisPasswordLen     // in, out password length
   );
typedef  int32 (PIPROC* TYLPFNLOGINDIALOG)
   (
        HWND    hWndParent,             // application's parent window handle
        char PIPTR*   lpszServerName,         // in server name
        int32 PIPTR* pusServerName,      // in, out server name length
        char PIPTR*       lpszUserName,       // in user name
        int32 PIPTR* pusUserName,       // in out user name length
        char PIPTR*       lpszPassword,           // out password
        int32 PIPTR* pisPasswordLen     // in, out password length
   );
#define PILOGINDIALOG "pilg_logindialog"

//////////////////////////////////////////////////////////////////
/**********************************************************************/
// pilg_setpassword
// check id user password pair exists for given server and create it if necessary
//        ERR_UNKNOWN_SERVER if it cannot recognize the server
//        ERR_PI_ALLOC if cannot create LoginData    
//        ERR_LOGIN_CANCELLED if if wrong password
//        ERR_ALREADY_LOGGED_IN if already there
//        SUCCESS if LoginData has been created and added    
/**********************************************************************/
///////////////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_setpassword( 
        char PIPTR*   lpszServerName,     // in server name
        char PIPTR*   lpszUserName,       // in user name
        char PIPTR*   lpszPassword,        // in password
        long    valid               // in valid status flag
   );
typedef  int32 (PIPROC* TylpfnSetPassword)
   (
        char PIPTR*   lpszServerName,     // in server name
        char PIPTR*   lpszUserName,       // in user name
        char PIPTR*   lpszPassword,        // in password
        long    valid               // in valid status flag
   );
typedef  int32 (PIPROC* TYLPFNSETPASSWORD)
   (
        char PIPTR*   lpszServerName,     // in server name
        char PIPTR*   lpszUserName,       // in user name
        char PIPTR*   lpszPassword,        // in password      
        long    valid               // in valid status flag
   );
#define PISETPASSWORD "pilg_setpassword"

//////////////////////////////////////////////////////////////////
/**********************************************************************/
// pilg_unsetpassword
// check id user password pair exists for given server and remove it if necessary
//    ERR_UNKNOWN_SERVER if it cannot recognize the server
//    ERR_LOGIN_USERNOTFOUND if it cannot find the LoginData
//    SUCCESS if it removed the LoginData from the the server logindata map
//                and the LoginData map.        
/**********************************************************************/
///////////////////////////////////////////////////////////////////////
EXPORTPIINT32
pilg_unsetpassword( 
        char PIPTR*   lpszServerName,         // in server name
        char PIPTR*       lpszUserName      // in user name
   );
typedef  int32 (PIPROC* TylpfnUnSetPassword)
   (
        char PIPTR*   lpszServerName,         // in server name
        char PIPTR*       lpszUserName     // in user name
   );
typedef  int32 (PIPROC* TYLPFNUNSETPASSWORD)
   (
        char PIPTR*   lpszServerName,         // in server name
        char PIPTR*       lpszUserName      // in user name
   );
#define PIUNSETPASSWORD "pilg_unsetpassword"


#ifdef __cplusplus
}           /* end extern "C" */
#endif

#endif // __PILOGEX_H__
