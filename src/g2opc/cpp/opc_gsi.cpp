/***************************************************************************
:
:  OPC_GSI.cpp  -- The GSI loop & callback routines for OPCLink.
:
:
:..........................................................................*/

#include "stdafx.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <opcda.h>
#include <opcerror.h>
#include <opcda_i.c>
#include <tchar.h>
#include "gsi_main.h"
#include "opc_rpcs.h"
#include "opc_utils.h" 

/* gsi_show_callback and gsi_show_registered_items are utility functions */
/* defined at the end of this file.                                      */
extern void gsi_show_callback(char *name); 
extern void gsi_show_registered_items(char *name, gsi_registered_item registered_items[], gsi_int count) ;

#define TCPIP_PORT_NUMBER  0
#define MAX_CONSOLE_LINES  250
#define MAX_TITLE_STR      64
#define GENSYM_PHONE      "(781) 265-7301"

#define HR_ERROR_CODE(hr)  (((hr) & 0x1FFFFFF) | 0x2000000)

// Globals
// -------
bool                g_chkServerStatus = true ;
long                g_srvrCheckFreq = 5 ;
bool                g_useG2TimeStamp = false ;
bool                g_initSecurity = true ;
short               g_defaultQualityFilter = 0 ;
bool                g_lev1_good = false ;
bool                g_lev1_bad = false ;
bool                g_lev1_uncertain = false;
bool                g_dlg_open = false ;

wchar_t*            g_pServerNameW = NULL ;

DWORD               g_asyncRqstNr = 0 ;
context_info        context[MAX_GDB_CONTEXTS] ;
gsi_int             g_shutdown_ctx_nr = -1 ;
bool                g_shutdown_request ;
CRITICAL_SECTION    crtsec_items ;
GSINTQUEUE          async_processing_queue ;

int                 g_nr_servers = 0;
CServer             g_servers[MAX_GDB_CONTEXTS] ;

struct  status_nt   {   long    number ;
                        wchar_t *text ; } ;
status_nt           status_table[] = { {   0, L"OK" },
                                       { 101, L"No Server" },
                                       { 102, L"No Group"},
                                       { 103, L"Allocation failure.  Out of memory?"},
                                       { 104, L"General read failure.  hr=%ld." },
                                       { 105, L"Item not registered with group" },
                                       { 106, L"OPC Server returned unsupported data type" },
                                       { 107, L"General write failure.  hr=%ld." },
                                       { 108, L"Unsupported data type"} };



// Prototypes
// ----------
void gsi_next_async_update() ;
void gsi_async_update(gsi_int ctx_nr) ;


/* =========================================================================== */
/*                                                                             */
/*         Open a Console, Validate the Bridge License, Initialize COM,        */
/*                      Configure GSI, & run the GSI Loop                      */
/*                                                                             */
/* =========================================================================== */
void GsiLoop(LPSTR lpCmdLine)
{
    char                        shortVer[4] ;
    int                         hConHandle;
    long                        lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO  coninfo;
    FILE                        *fp;
    HRESULT                     hr = E_FAIL ;
    TCHAR                       TitleStr[MAX_TITLE_STR] ;
    TCHAR                       tchBuildCode[5]=TEXT("") ;
    UINT                        verMajor, verMinor, typeCode, revCode ;
    ProgramVersion              *pPV = NULL ;

    // Zap the array of context & server information
    // ---------------------------------------------
    memset(context,0,sizeof(context)) ;

    // Get program version
    // -------------------
    pPV = new ProgramVersion ;
    if (!pPV || !pPV->Ready() || FAILED(pPV->GetVersion(verMajor, verMinor, typeCode, revCode)))
    {
        MessageBox(NULL,TEXT("Unable to Read Program Version"),TEXT("Fatal Error"),0) ;
        PostQuitMessage(0) ;
    }
    if (pPV)
        hr = pPV->GetBuildCode(tchBuildCode,5) ;

    if (pPV && SUCCEEDED(hr))
#if _MSC_VER >= 1400 /* VS2005+ */
        _stprintf_s(TitleStr, MAX_TITLE_STR, L"G2-OPC Client Bridge Ver. %d.%d%s%d (%s)",verMajor, verMinor,
            (typeCode == 128) ? L" rev. " : (typeCode == 64) ? L" beta " : L" alpha ",
            revCode, tchBuildCode) ;
#else
        _stprintf(TitleStr, L"G2-OPC Client Bridge Ver. %d.%d%s%d (%s)",verMajor, verMinor,
            (typeCode == 128) ? L" rev. " : (typeCode == 64) ? L" beta " : L" alpha ",
            revCode, tchBuildCode) ;
#endif
    else
#if _MSC_VER >= 1400 /* VS2005+ */
        _stprintf_s(TitleStr, MAX_TITLE_STR, L"G2-OPC Client Bridge Ver. %d.%d%s%d",verMajor, verMinor,
            (typeCode == 128) ? L" rev. " : (typeCode == 64) ? L" beta " : L" alpha ",
            revCode) ;
#else
        _stprintf(TitleStr, L"G2-OPC Client Bridge Ver. %d.%d%s%d",verMajor, verMinor,
            (typeCode == 128) ? L" rev. " : (typeCode == 64) ? L" beta " : L" alpha ",
            revCode) ;
#endif

    // Allocate a console for this app & set OPCLink & the version as the title
    // ------------------------------------------------------------------------
    AllocConsole();
    SetConsoleTitle(TitleStr) ;

    // Set the screen buffer to be big enough to let us scroll text
    // ------------------------------------------------------------
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = MAX_CONSOLE_LINES;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

    // redirect unbuffered STDOUT to the console
    // -----------------------------------------
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // Intercept requests to close the console
    // ---------------------------------------
    SetConsoleCtrlHandler(ConsoleCtrlHandler,TRUE);

    //  Prevent the system from displaying a dialog box to the user during
    // terminating of application
    SetProcessShutdownParameters(0x280, //default shutdown level
                    SHUTDOWN_NORETRY);

    // Validate the license
    // --------------------
    sprintf(shortVer, "V12");

    if (!stage1("G2-OPCLINK", shortVer) || !stage2() )
    {
        MessageBox(NULL,TEXT("Valid License Not Found"),TEXT("Not Authorized"),0) ;
        g_license_status = -1;
        ConsoleCtrlHandler(0);
        FreeConsole() ;
        ExitThread(-1) ;
    }
    else
        g_license_status = 1 ;

    // Initialize COM & GSI
    // ---------------------
    CoInitialize(NULL) ;
    GSI_SET_OPTIONS_FROM_COMPILE();
    gsi_initialize_for_win32(NULL, NULL);
    gsi_set_option(GSI_NO_SIGNAL_HANDLERS);
    gsi_set_option(GSI_ONE_CYCLE);
    gsi_set_option(GSI_WIDE_STRING_API) ;
    gsi_set_option(GSI_NEW_SYMBOL_API) ;
    // GENSYMCID-1222: G2 Opc client is not updating values in async. mode
    //                 when update rate is set below 1 second.
    gsi_set_pause_timeout(50);
    InitializeCriticalSection(&crtsec_items) ;

    // Convert the Windows Command-Line to the C Style Command Line
    // Required by gsi_start.
    // ------------------------------------------------------------
    int             nrArgs = 0 ;
    char            **xargv = NULL ;
    CCommandLine    *pCcommandLine = new CCommandLine(lpCmdLine) ;

    if (pCcommandLine)
    {
        nrArgs = pCcommandLine->NrArgs() ;
        xargv = pCcommandLine->argv() ;
    }
    else
        printf("*** Unable to decode command line! ***\n") ;

    gsi_start(nrArgs,xargv);
    delete pCcommandLine ; // (OK if NULL)

    while (1)
    {
        if (g_shutdown_ctx_nr >= 0 && context[g_shutdown_ctx_nr].icon_hndlr_proc)
        {
            gsi_rpc_start(context[g_shutdown_ctx_nr].icon_hndlr_proc,NULL, g_shutdown_ctx_nr) ;
            g_shutdown_ctx_nr = -1 ;
        }
        gsi_next_async_update() ;
        gsi_pause();
        gsi_run_loop() ;
        if (g_shutdown_request)
        {
            for (int i=0 ; i < MAX_GDB_CONTEXTS ; i++)
                if (context[i].pServer)
                {
                    shutdown_context(i, true) ;
                    gsi_run_loop() ;
                }
            g_shutdown_request = false ;

            ExitThread(-1) ;
        }
    }
}


gsi_int gsi_get_tcp_port()
{
    return(TCPIP_PORT_NUMBER);
}

	// ------------------------------------------
    // Break the name into machine & server parts
    // ------------------------------------------
void parse_server_and_machine_names(wchar_t* pWholeStrW, wchar_t **pMachineNameW, wchar_t **pServerNameW) 
{
    size_t          strLen = wcslen(pWholeStrW) ;
    size_t          colonLoc = wcscspn(pWholeStrW,L":") ;

    if (strLen == colonLoc)
    {
        *pMachineNameW = new WCHAR[10];
        wcscpy(*pMachineNameW, L"localhost");
        *pServerNameW = pWholeStrW ;
    }
    else
    {
        *pServerNameW = &pWholeStrW[colonLoc + 1] ;
        *pMachineNameW = new WCHAR[colonLoc + 1];
        wcsncpy(*pMachineNameW, pWholeStrW, colonLoc);
        (*pMachineNameW)[colonLoc] = L'\0';
    }
}


/* ========================================================================== */
/*                                                                            */
/*  A G2 interface object has connected to this bridge.  This is where much   */
/*  of the configuration of the OPC objects takes place.                      */
/*                                                                            */
/*  First we make sure the context number is OK and the bridge is still       */
/*  authorized.                                                               */
/*                                                                            */
/*  Next we use a CCommandLine object to parse the initialization string.  If */
/*  a server name has not been provided, this connection can only be used for */
/*  requesting a list of available servers (with rpc_opc_getserverlist).      */
/*                                                                            */
/*  If we have a server name, we look it up in the registry.  If found, we    */
/*  check whether we already a pointer to it from another context.  If so, we */
/*  use it.  If not, we instantiate the server and store pointers to it in    */
/*  both the server table and the information area for this context.          */
/*                                                                            */
/*  The next step is to create the group with the refresh and deadband values */
/*  that were specified in the initialization string.                         */
/*                                                                            */
/*  If this succeeds, we will try to connect the global data call back object */
/*  to the newly created OPCGroup.  If we succeed, the server will be able    */
/*  to asynchronously send values to this bridge.                             */
/*                                                                            */
/* ========================================================================== */
gsi_int gsi_initialize_context(gsi_char *remote_process_init_string, gsi_int length)
{
    int     iX ;
    short   connection_status = 0 ; // not connected

    gsi_int ctxNr = gsi_current_context();

    // In the event of a premature shutdown during context initializaton
    // -----------------------------------------------------------------
    if (ctxNr < 0)
    {
        printf("\nERROR::Connection has terminated during context initialization.\n\n");
        fflush(stdout);
        return( GSI_REJECT );    
    }

    // If this context exceeds maximum # of GSI contexts
    // -------------------------------------------------
    if (ctxNr >= MAX_GDB_CONTEXTS)
    {
        printf("\nERROR::Context %d exceeds maximum number of GDB contexts %d.\n\n",ctxNr,MAX_GDB_CONTEXTS);
        fflush(stdout);
        return( GSI_REJECT );    
    }

    // *** Check Authorization ***
    // ---------------------------
    if (periodic() != TRUE)
    {
        printf("\n===============================================\n");
        printf(" OPCLink Bridge Authorization has EXPIRED!\n");
        printf(" Please contact Gensym at %s\n",GENSYM_PHONE);
        printf("===============================================\n\n");
        fflush(stdout);
        ConsoleCtrlHandler(0);
    }


    // --------------------------------
    // Decode the initialization string
    // --------------------------------
    long    nr_wchars = wcslen((wchar_t*)remote_process_init_string) ;
    char*   ascii_init_str = new char[nr_wchars+1] ;
    long    nr_chars = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)remote_process_init_string,
                                        -1, ascii_init_str, nr_wchars+1, NULL, NULL ) ;
    CCommandLine    *pSrvrGrpParams = new CCommandLine(ascii_init_str) ;
    delete [] ascii_init_str ;
    if (!pSrvrGrpParams || pSrvrGrpParams->NrArgs() < 2) {
      delete pSrvrGrpParams;
      return GSI_ACCEPT ;
    }
    

    // ------------------------------------------
    // Break the name into machine & server parts
    // ------------------------------------------
    wchar_t         *pWholeStrW = pSrvrGrpParams->argW(1) ;
    wchar_t         *pMachineNameW, *pServerNameW ;
    
    parse_server_and_machine_names(pWholeStrW, &pMachineNameW, &pServerNameW);

    // what to do with the machine name
    if (g_pServerNameW)
      delete [] g_pServerNameW;
    g_pServerNameW = new wchar_t[wcslen(pServerNameW) + 1] ;
    wcscpy(g_pServerNameW, pServerNameW);

    // -------------------------------
    // Find the server in the registry
    // -------------------------------
    CLSID           clsid ;
    context_info    *ctxInfo = &(context[ctxNr]) ;
    HRESULT         hr = CLSIDFromProgID(pServerNameW, &clsid );
    if (FAILED(hr)) {
        delete [] pWholeStrW;
        delete [] pMachineNameW;
        delete pSrvrGrpParams;
        return GSI_ACCEPT ;
    }
                                // ctxInfo->serverCLSID = clsid ;


    // --------------------------------------------
    // Do we already have a pointer to this server?
    // --------------------------------------------
    CServer     *pServerObj = NULL ;
    IOPCServer  *pOPCServer = NULL ;
    int         nr_servers ;
    int         first_free_slot = -1 ;

    for (iX = 0, nr_servers = 0 ; nr_servers < g_nr_servers && iX < MAX_GDB_CONTEXTS ; iX++)
        if (!g_servers[iX].m_pOPCServer)
        {
            if (first_free_slot == -1)
                first_free_slot = iX ;
        }
        else if (clsid == g_servers[iX].m_clsid)
        {
            // We found it! remember that another context is using it
            // ------------------------------------------------------
            pServerObj = &g_servers[iX] ;
            pOPCServer = pServerObj->m_pOPCServer ; //temporary use.  Don't bother with AddRef()
            context[ctxNr].pServer = pServerObj ;
            g_servers[iX].m_nr_ctxs_using++ ;
            break ;
        }
        else
            nr_servers++ ;


    if (nr_servers == g_nr_servers)  // No: create it
    {
        MULTI_QI QIS[1];
        QIS[0].pIID = &IID_IOPCServer;
        QIS[0].hr = 0;
        QIS[0].pItf = NULL;

        COSERVERINFO coServerInfo;

        ZeroMemory (&coServerInfo, sizeof (coServerInfo));
        int len = wcslen (pMachineNameW) * sizeof (WCHAR);
        coServerInfo.pwszName = pMachineNameW;

        if (first_free_slot==-1)
          first_free_slot=g_nr_servers ;  // There aren't any holes in the CServer table
        hr = CoCreateInstanceEx (clsid, NULL, CLSCTX_SERVER, &coServerInfo, 1, QIS);
        if (coServerInfo.pwszName) {
            delete [] coServerInfo.pwszName;
            coServerInfo.pwszName = NULL;
            pMachineNameW = NULL;
        }

        if (FAILED(hr) || !SUCCEEDED(QIS[0].hr)) {
          delete [] pWholeStrW;
          delete pSrvrGrpParams;
          return GSI_ACCEPT ;
        }
        pOPCServer = (IOPCServer *)QIS[0].pItf;
        connection_status = 1 ;  // Connected to server
        log_message_s(TL_INFO,L"Connected to %s.", pServerNameW);
        pServerObj = &g_servers[first_free_slot] ;
        pServerObj->FirstUse(clsid, pOPCServer) ;
        context[ctxNr].pServer = pServerObj ;
        g_nr_servers++ ;

        /* If the server supports OPCShutdown (version 2+), connect the      */
        /* newly created OPCServer to the server's shutdown object.          */
        /* ----------------------------------------------------------------- */
        IConnectionPointContainer* ConnectionPointContainer;
        if (SUCCEEDED(hr = pOPCServer->QueryInterface(
                IID_IConnectionPointContainer, (void**)&ConnectionPointContainer)))
        {
            if (SUCCEEDED(hr = ConnectionPointContainer->FindConnectionPoint(IID_IOPCShutdown, &pServerObj->p_ShutdownConnectionPoint)))
            {
                IOPCShutdown        *pSDO = pServerObj->mp_shutdown_object ;
                IUnknown*           *pIUK ;



                hr = pSDO->QueryInterface(IID_IUnknown, (LPVOID*)&pIUK) ;


                if (SUCCEEDED(hr = pServerObj->p_ShutdownConnectionPoint->Advise(pSDO, &pServerObj->sd_cookie)))
                {
                    pServerObj->b_usesV2shutdown = TRUE;
                    // GENSYMCID-748: OPC bridge creates additional client connection on the OPC server after a g2 restart
                    pServerObj->p_ShutdownConnectionPoint->Release();
                    log_message_s(TL_INFO,L"%s connected to shutdown object",pServerNameW) ;
                }
                else
                {
                    pServerObj->sd_cookie = 0;
                    pServerObj->p_ShutdownConnectionPoint->Release();
                    pServerObj->p_ShutdownConnectionPoint = NULL ;
                    log_message_s(TL_INFO,L"%s does not support IOPCShutdown",pServerNameW) ;
                }
            }
            ConnectionPointContainer->Release(); 
        }
    }
    delete [] pWholeStrW ;

    gsi_rpc_declare_remote(&ctxInfo->icon_hndlr_proc,(gsi_char*)_T("UPDATE-ALL-OPC-INTERFACE-ICONS"),NULL,0,0,ctxNr) ;   

    while (1)   // Provides an easy way to jump to clean up code on an error
    {
        // ----------------------------------------------
        // Decode the group parameters & create the group
        // ----------------------------------------------
        if (pSrvrGrpParams->NrArgs() < 3)
            break ;
        wchar_t *pGroupNameW = pSrvrGrpParams->argW(2) ;

        // Validate & extract requested refresh rate
        // -----------------------------------------
        bool    refreshRateError = FALSE ;
        int rqstdRefreshRate = 0 ;
        if (pSrvrGrpParams->NrArgs() >= 4)
        {
            char *p = pSrvrGrpParams->argv()[3] ;
            if (*p == '+')
                p++ ;
            while (*p)
                if (*p < '0' || *p > '9')
                {
                    refreshRateError = TRUE ;
                    break ;
                }
                else
                    p++ ;
            if (!refreshRateError)
                rqstdRefreshRate = atoi(pSrvrGrpParams->argv()[3]) ;
        }

        // We will use 1 more than the context number as the local group handle
        // --------------------------------------------------------------------
        OPCHANDLE   hGrpL = ctxNr+1 ;

        // Validate & extract the deadband
        // ------------------------------- 
        bool    deadbandError = FALSE ;
        bool    haveDec = FALSE ;
        FLOAT   fltDeadband = 0.0 ;
        if (pSrvrGrpParams->NrArgs() >= 5)
        {
            char *p = pSrvrGrpParams->argv()[4] ;
            if (*p == '+')
                p++ ;
            while (*p)
            {
                if (*p < '0' || *p > '9')
                    if (haveDec || (*p != '.' && *p != ','))
                    {
                        deadbandError = TRUE ;
                        break ;
                    }
                    else
                        haveDec = true;
                p++ ;
            }
            if (!deadbandError)
                fltDeadband = (float)atof(pSrvrGrpParams->argv()[4]) ;
        }


        // Validate synchronous/asynchronous code & store in context information area
        // --------------------------------------------------------------------------
        if (pSrvrGrpParams->NrArgs() >= 6)
        {
            char    *p = pSrvrGrpParams->argv()[5] ;
            if (*p == 'S' || *p == 's')
                context[ctxNr].sync_mode = true ;
            else if (*p != 'A' && *p != 'a')
                log_message(TL_ERRORS, L"Invalid synchronous/asynchronous code.  Asynchronous selected.") ;
        }

        // Create the new OPCGroup
        // -----------------------
        OPCHANDLE   group_handle ;
        if (ctxInfo->pServer && ctxInfo->pServer->m_pOPCServer)
            hr = ctxInfo->pServer->m_pOPCServer->AddGroup(pGroupNameW,TRUE,rqstdRefreshRate,hGrpL,
                                                  NULL,&fltDeadband,0,&group_handle,
                                                  &ctxInfo->dwUpdRateS,IID_IOPCItemMgt,
                                                  (LPUNKNOWN*)(&ctxInfo->pItemMgt)) ;
        else
            hr = E_FAIL ;
        if (FAILED(hr))
        {
            log_message_sd(TL_ERRORS,L"Unable to create OPCGroup \"%s\".  hr = %ld.", pGroupNameW, hr) ;
            delete [] pGroupNameW ;
            break;
        }
        long dbgCt = ctxInfo->pItemMgt->AddRef() ;
        dbgCt = ctxInfo->pItemMgt->Release() ;
        ctxInfo->hGroupS = group_handle ;
        connection_status = 2 ;  // connected to both server & group


        // Log an information message reporting the creation of the group and its properties
        // ---------------------------------------------------------------------------------
        wchar_t *msg = new wchar_t[wcslen(pGroupNameW) + 60] ;
        swprintf(msg, L"Created group \"%s\" %d %f (%s)", pGroupNameW, rqstdRefreshRate, fltDeadband,
            context[ctxNr].sync_mode ? L"synchronous" : L"asynchronous") ;
        log_message(TL_INFO, msg) ;
        delete [] msg ;

        CGroup  *pGrp = new CGroup(gsi_current_context(),group_handle) ;
        if (pGrp)
            pServerObj->AddGroup2ServerList(pGrp) ;
        else
        {
            log_message_s(TL_ERRORS, L"Unable to create Group management object for \"%s\".  Out of memory?", pGroupNameW) ;
            delete [] pGroupNameW ;
            context[ctxNr].sync_mode = true ;  // Asynchrounous mode not possible with CGroup
            break ;
        }

        delete [] pGroupNameW ;

        /* If the server supports OPCDataCallbacks (version 2+), connect the      */
        /* newly created OPCGroup to the Groups callback object.                  */
        /* ---------------------------------------------------------------------- */
        IConnectionPointContainer* ConnectionPointContainer;
        if (SUCCEEDED(hr = ctxInfo->pItemMgt->QueryInterface(
                IID_IConnectionPointContainer, (void**)&ConnectionPointContainer)))
        {
            IUnknown    *pIUK = NULL ;

            if (SUCCEEDED(hr = ConnectionPointContainer->FindConnectionPoint(IID_IOPCDataCallback, &ctxInfo->p_ConnectionPoint)))
            {
                IOPCDataCallback    *pDCB = pGrp->mp_callback_object ;

                hr = pDCB->QueryInterface(IID_IUnknown, (LPVOID*)&pIUK) ;

                if (pIUK && SUCCEEDED(hr = ctxInfo->p_ConnectionPoint->Advise(pIUK, &ctxInfo->dcb_cookie)))
                {
                    ctxInfo->b_usesV2dcb = true;
                }
                else
                {
                    ctxInfo->dcb_cookie = 0;
                    ctxInfo->p_ConnectionPoint->Release();
                    ctxInfo->p_ConnectionPoint = NULL ;
                }
            }
            if (pIUK)
                pIUK->Release() ;
            ConnectionPointContainer->Release();
        }

        /* Should we try to use OPC 1.0A Callbacks ? */
        /* ----------------------------------------- */
        if (!ctxInfo->b_usesV2dcb)
        {
            FORMATETC       fmt ;
            IDataObject     *pDO  = NULL ;
            IAdviseSink     *pAS  = pGrp->mp_advise_sink ;
            IUnknown        *pIUK = NULL ;

            if (SUCCEEDED(hr = ctxInfo->pItemMgt->QueryInterface(IID_IDataObject, (void**)&pDO)))
            {
                //RegisterClipboardFormat(
                if (SUCCEEDED(hr))
                {
                    fmt.cfFormat = RegisterClipboardFormat(L"OPCSTMFORMATDATATIME") ;
                    fmt.dwAspect = DVASPECT_CONTENT ;
                    fmt.ptd = NULL ;
                    fmt.tymed = TYMED_HGLOBAL ;
                    fmt.lindex = -1 ;
                    if (FAILED(hr=pDO->DAdvise(&fmt, ADVF_PRIMEFIRST, pAS, &ctxInfo->dcb_cookie)))
                        ctxInfo->dcb_cookie = 0 ;
                }
            }
        }

        break ;
    }
    delete pSrvrGrpParams;
    return (GSI_ACCEPT);
}
 


/* ========================================================================== */
/*                                                                            */
/*                           Register a new G2 item                           */
/*                                                                            */
/*      We want to associate the item with an item in the OPC namespace.      *
/*    We will use item ID in the G2 item to add an OPCItem to the OPCGroup    */
/*              that was created when we initialize the context.              */
/*                                                                            */
/*   We use an array of item_value_ptrs that is attached to the context to    */
/*   keep track of both the item's GSI handle and the handle assigned to      */
/*                the corresponding OPCItem by the OPCServer.                 */
/*                                                                            */
/* ========================================================================== */
void gsi_receive_registration(gsi_registration item_registration)
{
    enum { validate, add, wrapup }  stage = validate ;
    gsi_int                         ctx_nr = gsi_current_context() ;
    gsi_int                         item_type = gsi_type_of(item_registration) ;
    gsi_int                         obj_handle ;
    gsi_int                         lX ;
    gsi_item                        item_id_attr ;
    gsi_item                        access_path_attr ;
    HRESULT                         hr, *pHRs ;
    item_id_attrs                   id_struct ;
    long                            stat_code = 0 ;
    OPCITEMDEF                      item_def ;
    OPCITEMRESULT                   *pItemInfo ;

    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    // Validation: See if we are connected to a server and a group and the
    //             item has an item id & access path
    // -------------------------------------------------------------------
    while (stage == validate)
    {
        obj_handle = gsi_handle_of(item_registration) ;

        // Make sure we have the pointers we need to create an OPCItem
        // -----------------------------------------------------------
        if (!context[ctx_nr].pServer || !context[ctx_nr].pServer->m_pOPCServer)
        {
			//{{suzsoft changed for Gensym-518
			if (g_pServerNameW)
				log_message_ds(TL_ERRORS, L"Unable to register item with handle %ld.  Context is not connected to an OPCServer [%s].",
					obj_handle,  g_pServerNameW) ;
			else
				log_message_d(TL_ERRORS, L"Unable to register item with handle %ld.  Context is not connected to an OPCServer.",
					obj_handle) ;
			//}}suzsoft
            stat_code = G2OPC_NO_SERVER_DEFINED ;
            break ;
        }
        if (!context[ctx_nr].pItemMgt)
        {
            log_message_d(TL_ERRORS, L"Unable to register item with handle %ld.  Context is not connected to an OPCGroup.", 
                      obj_handle) ;
            stat_code = G2OPC_NO_GROUP_DEFINED ;
            break ;
        }

        // Validate & extract the Item ID & Access Path
        // --------------------------------------------
        bool error_flag = false ;
        item_id_attr    =gsi_identifying_attr_of(item_registration,1) ;
        access_path_attr=gsi_identifying_attr_of(item_registration,2) ;

        lX = gsi_type_of(item_id_attr) ;
        if (lX == GSI_STRING_TAG)
        {
            id_struct.item_id = gsi_str_of(item_id_attr) ;
            if (!wcslen(id_struct.item_id))
                error_flag = true ;
            else
            {
                lX = gsi_type_of(access_path_attr) ;
                if (lX == GSI_STRING_TAG)
                    id_struct.access_path = gsi_str_of(access_path_attr) ;
                else
                    error_flag = true ;
            }
        }
        else
            error_flag = true ;
        if (error_flag)
        {
            log_message_d(TL_ERRORS, L"Unable to register item with handle %ld.  Invalid defining attributes.", obj_handle) ;
            stat_code = G2OPC_DEF_ATTR_BAD ;
            break ;
        }

        stage = add ;
        break ;
    }

    // Add the item to the group.  Remember the
    // client & server handles for this item
    // ----------------------------------------
    while (stage == add)
    {
        // Add the item to the group
        // -------------------------   
        item_def.bActive = true ;
        item_def.dwBlobSize = 0 ;
        item_def.hClient = obj_handle ;
        item_def.szAccessPath = id_struct.access_path ;
        item_def.szItemID = id_struct.item_id ;
        item_def.vtRequestedDataType = OpcUtils::GsiType2VT(item_type) ;

        if (item_def.vtRequestedDataType == VT_NULL)
        {
            log_message(TL_ERRORS, L"Invalid G2-OPC Variable.  Must have data type.") ;
            stat_code = GSI_UNSUPPORTED_TYPE ;
            break ;
        }

        // Here is where we attempt to add the item to the group
        // -----------------------------------------------------
        hr = context[ctx_nr].pItemMgt->AddItems(1,&item_def,&pItemInfo, &pHRs) ;
        
        // If this failed, determine what value to send to the variable's status
        // ---------------------------------------------------------------------
        if (FAILED(hr) || !pHRs)
        {
            if (hr == OPC_E_PUBLIC)
            {
                log_message_d(TL_ERRORS, L"Can't add item with handle %ld to public group.", obj_handle);
                stat_code = G2OPC_CANT_ADD_TO_PUB ;
            }
            else
            {
                log_message_dd(TL_ERRORS, L"Can't add item with handle %ld to group.  Code %ld.", obj_handle, hr);
                stat_code = G2OPC_ADD_ITEM_FAIL ;
            }
        }
        if (!stat_code && FAILED(pHRs[0]))
        {
            if (*pHRs == OPC_E_INVALIDITEMID)
                stat_code = G2OPC_INVALIDITEMID ;
            else if (*pHRs == OPC_E_UNKNOWNITEMID)
                stat_code = G2OPC_UNKNOWNITEMID ;
            else if (*pHRs == OPC_E_BADTYPE)
                stat_code = G2OPC_BADTYPE ;
            else if (*pHRs == OPC_E_UNKNOWNPATH)
                stat_code = G2OPC_BAD_ACCESSPATH ;
            else
                stat_code = G2OPC_ADD_ITEM_FAIL ;
        }

        // Store away the server & client handles
        // --------------------------------------
        if (!stat_code)
        {
            if (OpcUtils::AddItemHdl2Ctx((OPCHANDLE)obj_handle, pItemInfo[0].hServer, ctx_nr))
            {
                 log_message_d(TL_ERRORS, L"Failed to add item with handle %ld to context table.", obj_handle);
                 stat_code = G2OPC_UNEXPECTED ;
            }
            else
                log_message_ds(TL_INFO,L"Registered item: handle %ld (%s)",obj_handle, item_def.szItemID) ;
        }
        // GENSYMCID-1092: OPCClient crashing when cannot connect to OPC Server
        if (pHRs)
        {
            if ((pHRs[0] != OPC_E_UNKNOWNITEMID) && (hr != E_FAIL))
            {
                CoTaskMemFree(pItemInfo) ;
            }
            CoTaskMemFree(pHRs) ;
        }
        stage = wrapup ;
        break ;
    }

    
    // If there was an error, update the GSI variable status to indicate the problem
    // -----------------------------------------------------------------------------
    if (stat_code)
    {
        gsi_registered_item *variable ;
        variable = gsi_make_registered_items(1) ;
        gsi_set_handle(variable[0], obj_handle) ;
        gsi_set_type(variable[0], GSI_NULL_TAG) ;
        gsi_set_status(variable[0], stat_code) ;
        gsi_return_values(variable, 1, ctx_nr) ;
        gsi_reclaim_registered_items(variable);
    }

    /* The following code would be used if we updated the values of the G2 items  */
    /* as part of the registration process.  Since gsi_get_data is called         */
    /* immediately after the registration, since reading directly from the device */
    /* device could result in the bridge hanging for unacceptably long periods,   */
    /* and since reading from the cache would often result in "unavailable data", */
    /* this feature will only be implemented if we discover from usage in the     */
    /* field that it is really necessary.                                         */
    /* -------------------------------------------------------------------------- */
    /*  if (pItemInfo[0].hServer == 0)
        return ;

        IOPCSyncIO  *pISync = NULL ;
  
    hr = context[ctx_nr].pItemMgt->QueryInterface(IID_IOPCSyncIO, (LPVOID*)&pISync) ;
    if (SUCCEEDED(hr))
    {
        OPCDATASOURCE   ds = OPC_DS_CACHE ;  // or OPC_DS_DEVICE
        OPCHANDLE       hdlItemS = pItemInfo[0].hServer ;
        OPCITEMSTATE    *pVals ;
        hr = pISync->Read(ds, 1, &hdlItemS, &pVals, &pHRs) ;
        if (FAILED(hr))
        {
            // report error & set variable status   
        }
        else
        {
            // set value of variable based upon return type
            //         (same as gsi_get_data)
            CoTaskMemFree(pVals) ;
            CoTaskMemFree(pHRs) ;
        }
    }
    else
    {
        // set status
    }
    gsi_return_values(variable, 1, ctx_nr) ;
    gsi_reclaim_registered_items(variable); */
}




/* ========================================================================== */
/*                                                                            */
/*     We are no longer going to monitor this item.  If we successfully       */
/*     registered it with the server, we need to tell the group to stop       */
/*     monitoring it and remove it from the context's list of items.          */
/*                                                                            */
/* ========================================================================== */
void gsi_receive_deregistrations(gsi_registered_item registered_items[], gsi_int count)
{
    bool        found ;
    gsi_int     ctx_nr = gsi_current_context() ;
    gsi_int     lngX, lngY, hItemC, hItemS, nrOKhandles ;
    HRESULT     hr, *pHrs ;
    OPCHANDLE   *pItemHandles ;
    
    // Make sure both the context number is valid, that we have an items table,
    // and that we pointers to the OPCServer & OPCGroup
    // ------------------------------------------------------------------------
    if (ctx_nr < 0 || ctx_nr > MAX_GDB_CONTEXTS)
        return ;
    context_info *pCtxInfo = &context[ctx_nr] ;
    if (!pCtxInfo->pServer || !pCtxInfo->pServer->m_pOPCServer || 
         pCtxInfo->pItemMgt == NULL || pCtxInfo->pItemTable == NULL || count <= 0)
        return ;
    pItemHandles = new OPCHANDLE [count] ;
    if (!pItemHandles)
        return ;

    nrOKhandles = 0 ;
    for (lngX = 0 ; lngX < count ; lngX++)
    {
        hItemC = gsi_handle_of(registered_items[lngX]) ;

        // Did we previously successfully register this item?
        // (look for the handle in the context's item table)
        // --------------------------------------------------
        EnterCriticalSection(&crtsec_items) ;
        item_values_ptr *pItemTableEntry = pCtxInfo->pItemTable ;
        for (lngY = 0, found=false ; lngY < pCtxInfo->nrItems ; lngY++, pItemTableEntry++)
            if (pItemTableEntry->hItem == (unsigned long)hItemC)
            {
                // Yes: we found the item in the table
                // -----------------------------------
                found = TRUE ;
                if (pItemTableEntry->pVals)
                {
                    VariantClear(&pItemTableEntry->pVals->value) ;
                    delete pItemTableEntry->pVals ;
                }
                hItemS = pItemTableEntry->hItemS ;
                pCtxInfo->nrItems-- ;
                if (lngY < pCtxInfo->nrItems )
                    memmove(pItemTableEntry, pItemTableEntry+1, (pCtxInfo->nrItems - lngY) * sizeof(item_values_ptr) ) ;
                else
                    memset(pItemTableEntry, 0, sizeof(item_values_ptr)) ;
                if (hItemS)
                    pItemHandles[nrOKhandles++] = hItemS ;
                else
                    log_message(TL_INFO, L"Unable to remove item from group.  It was not added.") ;
                break ;
            }
        if (!found)
            log_message(TL_ERRORS, L"gsi_receive_deregistration: Unable to find registered item") ;
        LeaveCriticalSection(&crtsec_items) ;
    }

    // Stop monitoring all these items
    // -------------------------------
    if (nrOKhandles)
    {
        hr = pCtxInfo->pItemMgt->RemoveItems(nrOKhandles, pItemHandles, &pHrs) ;
        if (FAILED(hr))
            log_message(TL_ERRORS, L"RemoveItems failed");
        else
            for (lngX = 0 ; lngX < nrOKhandles ; lngX++)
                if (FAILED(pHrs[lngX]))
                    log_message(TL_ERRORS, L"Failed to remove item from OPCGroup") ;
        CoTaskMemFree(pHrs);
    }

    delete [] pItemHandles ;
}




/* ========================================================================== */
/*                                                                            */
/*      Update the list of variables with the values of the corresponding     */
/*                                  OPC items.                                */
/*                                                                            */
/* ========================================================================== */
void gsi_get_data(gsi_registered_item registered_items[], gsi_int count)
{
#define VALIDATING  1
#define READING     2
#define PACKING     3

    bool                    asyncIO = false ;
    bool                    found ;
    bool                    *good = NULL ;
    context_info            *pCtxInfo ;
    DWORD                   cancelID = 0 ;
    DWORD                   transId ;
    gsi_int                 ctx_nr = gsi_current_context() ;
    gsi_int                 ri_handle ;
    gsi_registered_item     registered_item ;
    HRESULT                 hr, *pHRs = NULL ;
    int                     lX, lY, lIdx ;
    int                     stage = VALIDATING ;
    IOPCAsyncIO             *pIOPCAsyncIO = NULL ;
    IOPCAsyncIO2            *pIOPCAsyncIO2 = NULL ;
    IOPCSyncIO              *pIOPCSyncIO = NULL ;
    long                    stat_code = 0 ;
    long                    nrOKhandles, loc, dbgCt ;
    OPCHANDLE               *pHandles = NULL ;
    OPCITEMSTATE            *pResults = NULL ;
    VARIANT                 vX ;
//  gsi_attr                *extraInfo ;
//  gsi_symbol              gsyX ;


    // ------------------------
    // Make sure we can do this
    // ------------------------
    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS || count <= 0)
        return ;

/*  Some of the code demonstrating how to return additional */
/*  information during read process                         */
/*  ------------------------------------------------------- */
/*  extraInfo = gsi_make_attrs(3) ;
    gsyX = gsi_make_symbol(L"STATUS-DESCRIPTION") ;
    gsi_set_name(extraInfo[2], gsyX) ;
    gsi_set_str(extraInfo[2], L"OK") ; */

    while (stage == VALIDATING)
    {
        pCtxInfo = &context[ctx_nr] ;
        if (!pCtxInfo->pServer || !pCtxInfo->pServer->m_pOPCServer)
        {
            stat_code = GSI_UNREGISTERED ;
            break ;
        }
        if (pCtxInfo->pItemMgt == NULL)
        {
            stat_code = G2OPC_NO_GROUP_DEFINED ;
            break ;
        }

        if (!pCtxInfo->sync_mode)
        {
            asyncIO = true ;
            if (pCtxInfo->b_usesV2dcb)
            {
                hr = pCtxInfo->pItemMgt->QueryInterface(IID_IOPCAsyncIO2, (LPVOID*)&pIOPCAsyncIO2) ;
                if (FAILED(hr))
                {
                    log_message(TL_ERRORS, L"Read failed.  Unable to retrieve IOPCAsyncIO2 pointer.") ;
                    stat_code = G2OPC_QI_FAILED ;
                    break ;
                }
            }
            else
            {
                hr = pCtxInfo->pItemMgt->QueryInterface(IID_IOPCAsyncIO, (LPVOID*)&pIOPCAsyncIO) ;
                if (FAILED(hr))
                {
                    log_message(TL_ERRORS, L"Read failed.  Unable to retrieve IOPCAsyncIO pointer.") ;
                    stat_code = G2OPC_QI_FAILED ;
                    break ;
                }
            }
        }
        else
        {
            hr = pCtxInfo->pItemMgt->QueryInterface(IID_IOPCSyncIO, (LPVOID*)&pIOPCSyncIO) ;
            if (FAILED(hr))
            {
                log_message(TL_ERRORS, L"Read failed.  Unable to retrieve IOPCSyncIO pointer.") ;
                stat_code = G2OPC_QI_FAILED ;
                break ;
            }
        }
        
        pHandles = new OPCHANDLE[count] ;
        good = new bool[count] ;
        if (count && (pHandles == NULL || good == NULL))
        {
            log_message(TL_ERRORS, L"Read failed.  Memory allocation failure.") ;
            stat_code = G2OPC_MEM_ALLOC_FAILED ;
            break ;
        }
        stage = READING ;
        break ;
    }
    if (stage == VALIDATING)  // If we got here via an error "break", don't try to read
        stage = PACKING ;

    

    while (stage == READING)
    {
        // ---------------------------------------------------
        // Build list of server-assigned handles for the items
        // ---------------------------------------------------
        nrOKhandles = 0 ;
        for (lX = 0; lX < count ; lX++)
        {
            registered_item = registered_items[lX] ;
            ri_handle = gsi_handle_of(registered_item) ;    
            loc = OpcUtils::FindItemHdl((OPCHANDLE)ri_handle, ctx_nr, &found) ;
            if (found && pCtxInfo->pItemTable[loc].hItemS)
            {
                pHandles[nrOKhandles++] = pCtxInfo->pItemTable[loc].hItemS ;
                good[lX] = true ;
            }
            else
                good[lX] = false ;
        }

        // --------------------
        // Read the item values
        // --------------------
        if (nrOKhandles)
            if (asyncIO && pCtxInfo->b_usesV2dcb)
                hr = pIOPCAsyncIO2->Read((DWORD)nrOKhandles, pHandles, ++g_asyncRqstNr, &cancelID, &pHRs) ;
            else if (asyncIO)
                hr = pIOPCAsyncIO->Read(pCtxInfo->dcb_cookie, OPC_DS_CACHE, (DWORD)nrOKhandles, pHandles, &transId, &pHRs) ;
            else
                hr = pIOPCSyncIO->Read(OPC_DS_CACHE, (DWORD)nrOKhandles, pHandles, &pResults, &pHRs) ;
        delete [] pHandles ;
        if (FAILED(hr))
        {
            log_message_d(TL_ERRORS, L"Read Item failure. hr = %d.", hr) ;
            stat_code = G2OPC_READ_FAILURE ;  // General read failure
        }
        stage = PACKING ;
        break ;
    }


    // ----------------------------------------------------------------------
    // Pack the results into the registered items and send them back to G2
    //
    // We could use either gsi_return_values and return all the items in
    // one shot, or we could loop through the items and use gsi_return_attrs
    // to return them one at a time.  We chose the latter because this allows
    // us to return extended information such as the quality, the timestamp,
    // and text describing the status.  (Not yet implemented)
    // ----------------------------------------------------------------------
    lIdx = 0 ;
    for (lX = 0; lX < count ; lX++)
    {
        registered_item = registered_items[lX] ;
        VariantInit(&vX) ;

        if (!good || !good[lX])
            continue ;
        else if (stat_code)
            gsi_set_status(registered_item, stat_code) ;
        else
        {
            if (pHRs)
                hr = pHRs[lIdx] ;
            else
                hr = S_OK ; 
            if (hr == S_OK)
            {
                if (!asyncIO)
                {
                    stat_code = OpcUtils::OPCq2G2q(pResults[lIdx].wQuality) ;

                    // Apply the Quality Filter
                    // ------------------------
                    if (OpcUtils::QualityPasses(stat_code, ctx_nr))
                    {
                        VariantCopy(&vX, &pResults[lIdx].vDataValue) ;

                        if (stat_code < OPC_BAD_NONSPEC || stat_code >= OPC_UNC_NONSPEC)
                            switch (vX.vt)
                        {
                            case VT_I2: lY = long(vX.iVal) ;
                            case VT_I4: if (vX.vt==VT_I4) lY = vX.lVal ;
                                        if (lY >= MIN_G2_INTEGER && lY <= MAX_G2_INTEGER)
                                            gsi_set_int(registered_item, lY) ;
                                        else
                                            gsi_set_flt(registered_item, lY) ;
                                        break ;
                            case VT_R8: gsi_set_flt(registered_item, vX.dblVal) ;
                                        break ;
                            case VT_BOOL:
                                        if (vX.boolVal == VARIANT_TRUE)
                                            gsi_set_log(registered_item, GSI_TRUE) ;
                                        else
                                            gsi_set_log(registered_item, GSI_FALSE) ;
                                        break ;
                            case VT_BSTR:
                                        gsi_set_str(registered_item, vX.bstrVal) ;
                                        break ;
                            default:    stat_code = GSI_UNSUPPORTED_TYPE ;
                                        break ;
                        }
                    }
                    // GENSYMCID-927:  Timestamp of data received from OPC Server
                    // GENSYMCID-1080: OPC Data is being collected automatically by the OPC Client
                    //                 bridge although items are not configured to receive data.
                    if (!g_useG2TimeStamp) {
                        SYSTEMTIME st ;
                        FILETIME locale_ft ;
                        FileTimeToLocalFileTime(&pResults[lIdx].ftTimeStamp, &locale_ft) ;
                        FileTimeToSystemTime(&locale_ft, &st) ;
                        double g2_time = gsi_encode_timestamp(st.wYear, st.wMonth, st.wDay, 
                            st.wHour, st.wMinute, st.wSecond)  + (double)st.wMilliseconds / 1000.0 ;
                        gsi_set_timestamp(registered_item, g2_time) ;
                    }
                    gsi_set_status(registered_item, stat_code) ;
                }
            }
            else
            {
                if (hr == OPC_E_INVALIDITEMID)
                    stat_code = G2OPC_INVALIDITEMID ;
                else if (hr == OPC_E_UNKNOWNITEMID)
                    stat_code = G2OPC_UNKNOWNITEMID ;
                else if (hr == OPC_E_BADTYPE)
                    stat_code = G2OPC_BADTYPE ;
                else if (hr == OPC_E_UNKNOWNPATH)
                    stat_code = G2OPC_BAD_ACCESSPATH ;
                else
                    stat_code = G2OPC_READ_FAILURE ;
                gsi_set_status(registered_item, stat_code) ;
                log_message_d(TL_ERRORS,L"Read Failure. hr = %d.", hr) ;
            }
            lIdx++ ;
        }
        if (stat_code || !asyncIO) {
            if (g_useG2TimeStamp) {
                gsi_return_values(&registered_item, 1, ctx_nr) ;
            } else {
                gsi_return_timed_values(&registered_item, 1, ctx_nr) ;
            }
        }
        VariantClear(&vX) ;
    }

    // Clean up
    // --------
    if (good)
        delete [] good ;
    if (pResults)
        CoTaskMemFree(pResults) ;
    if (pHRs)
        CoTaskMemFree(pHRs) ;
    if (pIOPCAsyncIO)
        dbgCt = pIOPCAsyncIO->Release() ;
    if (pIOPCAsyncIO2)
        dbgCt = pIOPCAsyncIO2->Release() ;
    if (pIOPCSyncIO)
        dbgCt = pIOPCSyncIO->Release() ;


//  gsi_reclaim_attrs(extraInfo) ;
}


/* ========================================================================== */
/*                                                                            */
/*               Set the corresponding OPC Items to the values                */
/*                      in the array of registered item                       */
/*                                                                            */
/* ========================================================================== */
void gsi_set_data(gsi_registered_item registered_items[], gsi_int count)
{
    bool                    found, *wrote ;
    context_info            *pCtxInfo ;
    gsi_char                *str ;
    gsi_int                 ctx_nr = gsi_current_context() ;
    gsi_int                 gsi_handle ;
    gsi_registered_item     registered_item ;
    HRESULT                 hr, hr2, *pHRs ;
    int                     stage = VALIDATING ;
    IOPCSyncIO              *pIOPCSyncIO = NULL ;
    long                    lngX, lRet, loc, nrOKhandles, error_code = 0, dbgCt;
    OPCHANDLE               *pHandles = NULL, hdl ;
    OPCITEMSTATE            *pResults = NULL ;
    VARIANT                 *pVars = NULL, *pVar ;

  
    // Initialize & Validate the input
    // -------------------------------
    if (ctx_nr < 0 || ctx_nr > MAX_GDB_CONTEXTS || count <= 0)
        return ;
    pCtxInfo = &context[ctx_nr] ;


    // If there is no server or group then the variable should have been
    // tagged with an error status when we tried to register it.
    // -----------------------------------------------------------------
    if (!pCtxInfo->pServer || !pCtxInfo->pServer->m_pOPCServer)
        return ;
    if (pCtxInfo->pItemMgt == NULL)
        return ;

    // Get the pointers & structures we need to write the values
    // ---------------------------------------------------------
    hr = pCtxInfo->pItemMgt->QueryInterface(IID_IOPCSyncIO, (LPVOID*)&pIOPCSyncIO) ;
    if FAILED(hr)
    {
        log_message_d(TL_ERRORS, L"Set failure.  Failed to retrieve IOPCSyncIO pointer. hr = %d", hr) ;
        error_code = G2OPC_QI_FAILED ;
    }
    else
    {
        if (!count) return ;
        pHandles = new OPCHANDLE [count] ;
        pVars = new VARIANT [count] ;
        wrote = new bool [count] ;
        if (pHandles == NULL || pVars == NULL)
        {
            log_message(TL_ERRORS, L"Allocation failure.  Out of memory?") ;
            error_code = G2OPC_MEM_ALLOC_FAILED ;
        }
    }


    // If there was not a validation error, prepare from the array of registered
    // items the arrays of item handles & values needed to set the OPC items.
    // If there was an error, set the status of each registered item to inform
    // G2 of the problem.
    // -------------------------------------------------------------------------
    nrOKhandles = 0 ;
    for (lngX = 0 ; lngX < count; lngX++)
    {
        registered_item = registered_items[lngX] ;
        gsi_handle = gsi_handle_of(registered_item) ;
        wrote[lngX] = false ;
        loc = OpcUtils::FindItemHdl(gsi_handle, ctx_nr, &found) ;
        if (found && (hdl=pCtxInfo->pItemTable[loc].hItemS))
            if (error_code)
                gsi_set_status(registered_item, error_code) ;
            else
            {
                pHandles[nrOKhandles] = hdl ;
                pVar = &pVars[nrOKhandles] ;
                VariantInit(pVar) ;
                switch(gsi_type_of(registered_item))
                {
                    case GSI_INTEGER_TAG : pVar->vt = VT_I4 ;
                                           pVar->lVal = gsi_int_of(registered_item) ;
                                           break ;
                    case GSI_FLOAT64_TAG : pVar->vt = VT_R8 ;
                                           pVar->dblVal = gsi_flt_of(registered_item) ;
                                           break ;
                    case GSI_LOGICAL_TAG : pVar->vt = VT_BOOL ;
                                           pVar->boolVal = (gsi_log_of(registered_item) < 0) ? VARIANT_FALSE : VARIANT_TRUE ;
                                           break ;
                    case GSI_STRING_TAG :  pVar->vt = VT_BSTR ;
                                           str = gsi_str_of(registered_item) ;
                                           pVar->bstrVal = SysAllocString(str) ;
                                           break ;
                    default:               log_message(TL_ERRORS, L"set data type not supported.") ;
                                           gsi_set_status(registered_item, GSI_UNSUPPORTED_TYPE) ;  // Unsupported data type
                                           continue ;
                }
                wrote[lngX] = true ;
                nrOKhandles++ ;
            }

//      If the handle for the variable is not in the context's table of variables, then
//      a code for the problem was stored in the variable's gsi status when we initally
//      tried to register the variable.
//      --------------------------------------------------------------------------------
//      else
//          ignore the problem for the reason explained in the above comment
    }

    // Tell OPC to write the values to the items.  If there are write errors,
    // update the status of each corresponding registered_item to inform G2.
    // ----------------------------------------------------------------------
    if (nrOKhandles)
    {
        hr = pIOPCSyncIO->Write(nrOKhandles, pHandles, pVars, &pHRs) ;
        if (FAILED(hr))
        {
            for (lngX = 0 ; lngX < count ; lngX++)
                if (wrote[lngX])
                    gsi_set_status(registered_items[lngX], G2OPC_WRITE_FAILURE) ;     // General write error
            log_message_d(TL_ERRORS, L"set failed with hr = %d.", hr) ;
        }
        else if (hr != S_OK)
        {
            long    idx = 0 ;

            for (lngX = 0 ; lngX < count ; lngX++)
                if (wrote[lngX])
                    if (FAILED(hr2=pHRs[idx++]))
                    {
                        gsi_set_status(registered_items[lngX], G2OPC_WRITE_FAILURE) ;
                        log_message_dd(TL_ERRORS,L"Failed to set variable with handle %d. hr=%d.",
                            gsi_handle_of(registered_items[lngX]), hr) ;
                    }
        }
        CoTaskMemFree(pHRs) ;
    }

    // Update the G2 items to reflect the new values & report the problems
    // --------------------------------------------------------------------
    // GENSYMCID-1498: double history update after set command
    //   when g_useG2TimeStamp is false, data returned from opc bridge should
    //   use timestamp of data and use gsi_return_timed_values instead of
    //   gsi_return_values.
    if (g_useG2TimeStamp)
        gsi_return_values(registered_items, count, ctx_nr);
    else {
        hr = pIOPCSyncIO->Read(OPC_DS_DEVICE, (DWORD)nrOKhandles, pHandles, &pResults, &pHRs);
        if (FAILED(hr)) {
            log_message_d(TL_ERRORS, L"Failed to get timestamp of OPC items with hr=%d.", hr);
            gsi_return_values(registered_items, count, ctx_nr);
        } else {
            lRet = 0;
            for (lngX = 0; lngX < count; lngX++) {
                gsi_registered_item register_item = registered_items[lngX];
                if (!wrote[lngX])
                    continue;
                SYSTEMTIME st ;
                FILETIME locale_ft ;
                FileTimeToLocalFileTime(&pResults[lRet].ftTimeStamp, &locale_ft) ;
                FileTimeToSystemTime(&locale_ft, &st) ;
                double g2_time = gsi_encode_timestamp(st.wYear, st.wMonth, st.wDay, st.wHour,
                    st.wMinute, st.wSecond) + (double)st.wMilliseconds / 1000.0 ;
                gsi_set_timestamp(registered_item, g2_time) ;
                lRet++;
            }
            gsi_return_timed_values(registered_items, count, ctx_nr);
        }
        if (pResults)
            CoTaskMemFree(pResults) ;
        if (pHRs)
            CoTaskMemFree(pHRs) ;
    }

    
    // Clean Up
    // --------
    if (pIOPCSyncIO)
        dbgCt = pIOPCSyncIO->Release();
    for (lngX = 0 ; lngX < nrOKhandles ; lngX++)
        VariantClear(&pVars[lngX]) ;
    if (pHandles) 
        delete [] pHandles ;
    if (pVars) 
        delete [] pVars ;
    if (wrote)
        delete [] wrote ;

    
//  gsi_show_registered_items("gsi_set_data", registered_items, count);
}

void gsi_pause_context()
{
    gsi_show_callback("gsi_pause_context");
}

void gsi_resume_context()
{
    gsi_show_callback("gsi_resume_context");
}


/* ========================================================================== */
/*                                                                            */
/* When a connection to OPCLink shuts down, we must release the context's     */
/* group and record that one less context is using this server.  If this is   */
/* the last context using the server, then we must release the server.        */
/*                                                                            */
/* ========================================================================== */
void gsi_shutdown_context()
{
    shutdown_context(gsi_current_context(), true) ;
}



void gsi_g2_poll()
{
}

void gsi_receive_message(gsi_char *message, gsi_int length)
{
    gsi_show_callback("gsi_receive_message");
    printf("message from G2:%s\n",message);
}


void gsi_next_async_update()
{
    EnterCriticalSection(&crtsec_items) ;
    if (async_processing_queue.size())
    {
        gsi_async_update(async_processing_queue.front()) ;
        async_processing_queue.pop() ;
    }
    LeaveCriticalSection(&crtsec_items) ;
}


/* ========================================================================== */
/*                                                                            */
/*         We have received values for items in context ctx_num.              */
/*      We return them to G2 here to avoid GSI threading conflicts.           */
/*                                                                            */
/* ========================================================================== */
void gsi_async_update(gsi_int ctx_nr)
{
    long    lX, qc ;

    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    context_info        *pCtxInfo = &context[ctx_nr] ;
    gsi_registered_item *pG2Item = gsi_make_registered_items(1) ;

    EnterCriticalSection(&crtsec_items) ;
    for (long lngX = 0 ; lngX < pCtxInfo->nrItems ; lngX++)
    {
        bool error_flag = false ;
        if (pCtxInfo->pItemTable[lngX].pVals)
        {
            gsi_set_handle(*pG2Item, pCtxInfo->pItemTable[lngX].hItem) ;
            VARIANT *pV = &(pCtxInfo->pItemTable[lngX].pVals->value) ;
            qc = OpcUtils::OPCq2G2q(pCtxInfo->pItemTable[lngX].pVals->quality) ;
            if (OpcUtils::QualityPasses(qc, ctx_nr))
            {
                switch (pV->vt)
                {
                    case VT_I2: lX = pV->iVal ;
                    case VT_I4: if (pV->vt==VT_I4) lX = pV->lVal ;
                                if (lX >= MIN_G2_INTEGER && lX <= MAX_G2_INTEGER)
                                    gsi_set_int(*pG2Item, lX) ;
                                else
                                    gsi_set_flt(*pG2Item, lX) ;
                                break ;
                    case VT_R8: gsi_set_flt(*pG2Item, pV->dblVal) ;
                                break ;
                    case VT_BOOL:
                                if (pV->boolVal == VARIANT_TRUE)
                                    gsi_set_log(*pG2Item, GSI_TRUE) ;
                                else
                                    gsi_set_log(*pG2Item, GSI_FALSE) ;
                                break ;
                    case VT_BSTR:
                                gsi_set_str(*pG2Item, pV->bstrVal) ;
                                break ;
                    default:    error_flag = true ;
                                gsi_set_type(pG2Item[0], GSI_NULL_TAG) ;
                }
            }
            else
                gsi_set_type(pG2Item[0], GSI_NULL_TAG) ;
            if (!g_useG2TimeStamp) {
              SYSTEMTIME st ;
              FILETIME locale_ft ;
              FileTimeToLocalFileTime(&pCtxInfo->pItemTable[lngX].pVals->timestamp, &locale_ft) ;
              FileTimeToSystemTime(&locale_ft, &st) ;
              double g2_time = gsi_encode_timestamp(st.wYear, st.wMonth, st.wDay,
                  st.wHour, st.wMinute, st.wSecond) + (double)st.wMilliseconds / 1000.0;
              gsi_set_timestamp(*pG2Item, g2_time) ;
            }
            gsi_set_status(pG2Item[0], error_flag ?  GSI_UNSUPPORTED_TYPE : qc) ;
            if (g_useG2TimeStamp) {
                gsi_return_values(pG2Item, 1, ctx_nr) ;
            } else {
                gsi_return_timed_values(pG2Item, 1, ctx_nr) ;
            }

            VariantClear(pV);
            delete pCtxInfo->pItemTable[lngX].pVals ;
            pCtxInfo->pItemTable[lngX].pVals = NULL ;

        }
        pCtxInfo->queued_for_async_processing = false ;
    }
    LeaveCriticalSection(&crtsec_items) ;

    gsi_reclaim_registered_items(pG2Item) ;
}



/* ========================================================================== */
/*                                                                            */
/* The specified context is being shut down.  Stop & release its group, clear */
/* the pointer to the server, and release the server if this is the last      */
/* context using it.                                                          */
/*                                                                            */
/* This function is used both by GSI's context shutdown callback and during   */
/* processing of a shutdown request by the OPCServer.                         */
/*                                                                            */
/* ========================================================================== */
void shutdown_context(gsi_int ctxNr, bool gone)
{
    HRESULT         hr, *pHRs ;
    long            i ;

    context_info    *pCtxInfo = &context[ctxNr] ;

    // The items may have already been released (via gsi_receive_deregistrations)
    // but we need to remove them here when receiving a shutdown callback
    // --------------------------------------------------------------------------
    if (pCtxInfo->nrItems && pCtxInfo->pItemTable)
    {
        if (pCtxInfo->pServer && pCtxInfo->pServer->m_pOPCServer && pCtxInfo->pItemMgt)
        {
            long        nrOKhandles = 0 ;

            EnterCriticalSection(&crtsec_items) ;
            OPCHANDLE   *pHandles = new OPCHANDLE[pCtxInfo->nrItems];
            if (pHandles != NULL)
            {
                for (i = 0 ; i < pCtxInfo->nrItems && pHandles ; i++)
                {
                    if (pCtxInfo->pItemTable[i].pVals) {
                        VariantClear(&pCtxInfo->pItemTable[i].pVals->value);
                        delete pCtxInfo->pItemTable[i].pVals ;
                        pCtxInfo->pItemTable[i].pVals = NULL;
                    }
                    if (pCtxInfo->pItemTable[i].hItemS)
                        pHandles[nrOKhandles++] = pCtxInfo->pItemTable[i].hItemS ;
                }
            }
            LeaveCriticalSection(&crtsec_items) ;
            if (nrOKhandles)
            {
                hr = pCtxInfo->pItemMgt->RemoveItems(nrOKhandles, pHandles, &pHRs) ;
                if (pHRs)
                    CoTaskMemFree(pHRs);
            }
            delete [] pHandles ;
        }
        else
        {
            EnterCriticalSection(&crtsec_items) ;
            for (i = 0 ; i < pCtxInfo->nrItems ; i++)
            {
              if (pCtxInfo->pItemTable[i].pVals) {
                VariantClear(&pCtxInfo->pItemTable[i].pVals->value);
                delete pCtxInfo->pItemTable[i].pVals ;
                pCtxInfo->pItemTable[i].pVals = NULL;
              }
            }
            LeaveCriticalSection(&crtsec_items) ;
        }
        delete [] pCtxInfo->pItemTable ;
        pCtxInfo->pItemTable = NULL ;
        pCtxInfo->nrItems = 0 ;
    }


    // There is a one-to-one relationship between contexts and OPC Groups.
    // If we have a group pointer we want turn off (UnAdvise) callbacks on
    // the group, then Remove & Release it.
    // -------------------------------------------------------------------
    // Implemented in ~CGroup (via RemoveGroupFromServerList) for debug reasons
    // ------------------------------------------------------------------------
    /*if (pCtxInfo->p_ConnectionPoint)
    {
        hr = pCtxInfo->p_ConnectionPoint->Unadvise(pCtxInfo->dcb_cookie) ;
        dbgCt = pCtxInfo->p_ConnectionPoint->Release() ;
        pCtxInfo->p_ConnectionPoint = NULL ;
    }*/

    // RemoveGroupFromServerList will delete the associated CGroup
    // which will cause the group to be deregistered from the server
    // -------------------------------------------------------------
    if (pCtxInfo->pServer)
    {
        pCtxInfo->pServer->RemoveGroupFromServerList(pCtxInfo->hGroupS) ;
    }
    if (pCtxInfo->pItemMgt)
    {
        long qt=pCtxInfo->pItemMgt->Release() ;
        pCtxInfo->pItemMgt = NULL ;
    }


    // This context is no longer using the server.  Release this context's
    // pointer to it.  Then, if this was the last context using this server,
    // remove it from the server table and complete release it.

    if (context[ctxNr].pServer)
    {
        OpcUtils::ServerReleased(pCtxInfo->pServer->m_clsid) ;
    }
    gsi_int holdHdl = pCtxInfo->icon_hndlr_proc ;
    memset(pCtxInfo, 0, sizeof(context_info)) ;
    if (!gone)
    {
        pCtxInfo->icon_hndlr_proc = holdHdl ;
        g_shutdown_ctx_nr = ctxNr ;
    }
}

/* --------------------------------------------------------- */

/* Utility functions used in this file, to aid in debugging. */

void gsi_show_callback(char *name)
{
    printf("%s: context %d\n",name,gsi_current_context());
}

void gsi_show_registered_items(char *name, gsi_registered_item registered_items[], gsi_int count)
{
    printf("%s: context %d\n",name,gsi_current_context());
    if (0 < count)
    {
        int i;
        printf("   handles: ");
        printf("%d",gsi_handle_of(registered_items[0]));
        for(i=1; i < count; i++) 
            printf(",%d",gsi_handle_of(registered_items[i]));
        printf("\n");
    }
}

BOOL WINAPI ConsoleCtrlHandler(DWORD dwCtrlType)
{
    SendMessage(g_hWnd, WM_DESTROY,0,0) ;
    return TRUE ;
}
