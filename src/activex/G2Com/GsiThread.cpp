// GsiThread.cpp: implementation of the GsiThread class.
//
// This class holds the application logic for the runloop and callbacks.
// The constructor creates a new thread, starts GSI and enters the run loop.
// We have to be carefull with the runloop and we can only access GSI through
// the wrapper object.
//
//////////////////////////////////////////////////////////////////////

#include <process.h>
#include "stdafx.h"
#include "GsiThread.h"
#include "GsiContext.h"
#include "ConnectingRequest.h"
#include "RPCRequest.h"
#include "NBConReq.h"
#include "G2Item.h"
//<Gensym-098>
#include "DisconReq.h"
//</Gensym-098>
//#include "Gateway.h"

// This is the queue that holds RequestObjects that request
// some some action be taken using GSI.
// --------------------------------------------------------
G2OrbContainer  Queue ;
//G2OrbContainer  OrphanedCtxs ;

// Number used to make sure the version of G2Com.kb in use matches
// this version of ActiveXLink.
//
// MAKE SURE TO UPDATE BOTH THIS VERSION ID AND THE VERSION ID IN
// THE TEXT PARAMETER _G2COM_KB_VER OF G2Com.kb WHENEVER YOU MAKE
// CHANGES TO G2Com.kb.
// -------------------------------------------------------------------
#define   AXL_VER   _T("8.2r1b")
// -------------------------------------------------------------------

/*void axl_selection_callback(procedure_user_data_type procedure_user_data, 
                               gsi_item *pItemsIn, gsi_int count, 
                               call_identifier_type call_index) ; */
declare_gsi_rpc_local_fn(axl_selection_callback) ;
declare_gsi_rpc_local_fn(axl_notification_callback);
extern declare_gsi_start_context(gsi_start_context);
extern declare_gsi_reset_context(gsi_reset_context);
//
// Create single global objects for thread class and gsi wrapper
//

GsiThread *GsiThreadObj = NULL;
HINSTANCE hGlobalInstance;


//
// This is the thread routine.  It manages the run loop
//

long GsiThread::sNumFds = 0 ;

//DWORD WINAPI ThreadRoutine(LPVOID val)
void ThreadRoutine(void *val)

{
    ((GsiThread *) val)->RunThread();
    _endthread();
}

void GsiThread::addRef(void)
{

    mRefCount++;
}

void GsiThread::delRef(void)
{

    mRefCount--;
    if (mRefCount == 1)
        mRefCount = 0;  // This gets around the problem of starting at zero and being
                        // destructed before we even start
}



void receive_rpc_call(procedure_user_data_type procedure_user_data, gsi_item *rpc_arguments, gsi_int count, call_identifier_type call_identifier)
{

    ATLTRACE2(atrAxlMethodCalls,3,"Got call from G2");
    USES_CONVERSION ;

    GsiContext *context = GsiContext::FindContext();
    if (!context)
    {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context for RPC\n");
        return;
    }

    if (count < 1)
    {
        ATLTRACE2(atlTraceGeneral,0,"Got wrong number of arguments\n");
        return;
    }

    CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_RPCCALL;
    cd->CallId = (long) call_identifier;

    TCHAR *name = (TCHAR *)gsi_str_of(rpc_arguments[0]);
    cd->Name = T2OLE(name);  // Setup BSTR

    cd->mCount = --count ;

    Datum*  pArgs = (count > 0) ? new Datum [count] : NULL ;
    for (long lX = 1 ; lX <= count ; lX++)
        pArgs[lX-1] = rpc_arguments[lX] ;
    cd->mArgs = pArgs ;
    context->FireEventInThread(cd);
}

// void receive_rpc_start(procedure_user_data_type procedure_user_data, gsi_item *rpc_arguments, gsi_int count, call_identifier_type call_identifier) {
void receive_rpc_start(void *ud, gsi_item *rpc_arguments, gsi_int count, call_identifier_type call_identifier)
{

    ATLTRACE2(atrAxlMethodCalls,3,"Got start from G2\n");
    USES_CONVERSION ;
    GsiContext *context = GsiContext::FindContext();
    if (!context)
    {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
        return;
    }
    if (count < 1)
    {
        ATLTRACE2(atlTraceGeneral,0,"Got wrong number of arguments\n");
        return;
    }
    CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_RPCSTART;
    cd->CallId = (long) call_identifier;
    TCHAR *name = (TCHAR *)gsi_str_of(rpc_arguments[0]);
    cd->Name = T2OLE(name);  // Setup BSTR
    cd->mCount = --count ;
    Datum*  pArgs = (count > 0) ? new Datum [count] : NULL ;
    for (long lX = 1 ; lX <= count ; lX++)
        pArgs[lX-1] = rpc_arguments[lX] ;
    cd->mArgs = pArgs ;
    context->FireEventInThread(cd);
}


void throw_gsi_error_from_handler(GsiContext *context, gsi_int ErrorCode, TCHAR *ErrorMessage)

{
    USES_CONVERSION;
    CallData *cd = new CallData;
    cd->ErrorCode = ErrorCode;
    cd->ErrorMessage = T2OLE(ErrorMessage);
    cd->mContext = context->mObjId;
    cd->CallId = -1;
    cd->EventCode = GSI_EVENT_ERROR;
    context->FireEventInThread(cd);
}

//
// This defines the callbacks from GSI.
//
void gsi_error_handler(gsi_int ErrorContext,
                       gsi_int ErrorCode,
                       gsi_char *ErrorMessage)
{
    USES_CONVERSION ;
    if (ErrorCode == 90 && !_tcscmp((TCHAR *)ErrorMessage+_tcslen((TCHAR *)ErrorMessage)-2,_T("22")))
        return ;
    ATLTRACE2(atlTraceGeneral,0,"%S\n", T2OLE((LPTSTR)ErrorMessage));

    // Ok, the bug for connecting events has been found.  We can now report this problem back
    // to the user.
    if (ErrorContext != -1 && ErrorCode != 7 && ErrorCode != 72)
    {
        unsigned long ObjId = (unsigned long) gsi_context_user_data(ErrorContext);
        GsiContext *context = GsiContext::FindContext(ObjId);
        if (context)
        { // Got the context, generate the event
            // If the context is connecting, then we can fail the connecting request.
            if (context->mConnReqId > 0)
            { // connection not yet established
                // The connection must have failed, cancel it
                ConnectingRequest *req = (ConnectingRequest *) context->Requests.FindObj(context->mConnReqId);
                if (req)
                {
                    req->mErrorMessage = T2OLE((LPTSTR)ErrorMessage) ;
                    req->mErrorCode = ErrorCode;
                    req->error();
                    return;
                }
            }

            // Let the client know about the problem
            throw_gsi_error_from_handler(context, ErrorCode, (TCHAR *)ErrorMessage);
            return; // ok, done
        }
    }

    // We where not able to discover which context generated the error
    // So, we will fire the error event on all context objects

    for (GsiContext *cptr = (GsiContext *) Contexts.GetFirst(); cptr;
            cptr = (GsiContext *) cptr->GetNext())
    {

        throw_gsi_error_from_handler(cptr, ErrorCode, (TCHAR *)ErrorMessage);
    }
}


// We can only enter GSI after taking the global lock.  With one exception,
// whenever we leave GSI, we release the lock.
//
// The one exception is when the type is GSI_RUN_STATE_TYPE_WAIT.
// When GSI pauses inside gsi_wait, it calls this function with
// direction "...LEAVING_GSI".  It is essentially saying, "I am going
// to sleep for awhile.  I'll be back, but for now, some other thread
// may do its stuff."  The problem is that if we release the lock, another
// thread could call gsi_wait which could scrogg the gsi_wait that is in
// progress on this thread.  As a result, we do not release the lock when
// we leave a wait, nor take it back when we return.
// -----------------------------------------------------------------------
void gsi_run_state_change(gsi_int direction, gsi_int type, char *name)
{
}


void gsi_set_up(void)

{
    gsi_set_option(GSI_SUPPRESS_OUTPUT);
    gsi_set_option(GSI_STRING_CHECK);
    gsi_set_option(GSI_NEW_SYMBOL_API) ;
    gsi_set_option(GSI_PROTECT_INNER_CALLS) ;
    GSI_SET_WIDE_STRING_OPTION 
    gsi_install_error_handler(&gsi_error_handler);
    gsi_install_run_state_change(&gsi_run_state_change)
    gsi_rpc_declare_local(&receive_rpc_call, NULL, (gsi_char *)_T("G2COM-CALL"));
    gsi_rpc_declare_local(&receive_rpc_start, NULL, (gsi_char *)_T("G2COM-START"));
    gsi_rpc_declare_local(&axl_notification_callback, NULL, (gsi_char *)_T("__G2COM-NOTIFY")) ;
    gsi_rpc_declare_local(&axl_selection_callback, NULL, (gsi_char *)_T("__G2COM-SELECT")) ;
    if (GsiThreadObj->getPauseTimeout() == WAKEUP_PAUSE)
        gsi_watch_fd(GsiThreadObj->getWakeupFd()) ;
}


gsi_int gsi_get_tcp_port(void)

{
    return 7000;
}


void init_final(void)
{
    gsi_int ctxNr = gsi_current_context() ;

    GsiContext *Context = GsiContext::FindContext();
    if (!Context)
    {
        if (ctxNr > 0)
            gsi_kill_context(ctxNr) ;
        return;
    }

    Context->mRemoteProcMap.Empty();  // erase the remote proc map list

    ConnectingRequest *req = (ConnectingRequest *) Context->FindRequest(Context->mConnReqId);
    if (req && Context->mConnReqId > 0)
        req->complete() ;
    else if (ctxNr >= 0)
        gsi_kill_context(ctxNr) ;
}


void init_fail(TCHAR *mesg)
{
    USES_CONVERSION ;

    GsiContext *Context = GsiContext::FindContext();
    if (!Context)
        return;

    gsi_kill_context(gsi_current_context());

    if (Context->mConnReqId > 0)
    {
        ConnectingRequest *req = (ConnectingRequest *) Context->FindRequest(Context->mConnReqId);
        if (req)
        {
            if (mesg)
                req->mErrorMessage = T2OLE(mesg);
            else
                req->mErrorMessage = OLESTR("The G2Com.kb module is not loaded into G2.  This module must be loaded to use G2-ActiveXLink");
            req->mErrorCode = 1000;
            req->error();
        }
    }

    // If a message was passed to init_fail, throw a COM exception
    // -----------------------------------------------------------
    if (mesg)
    {
        HRESULT             hr ;
        ICreateErrorInfo    *pCER = NULL ;
        IErrorInfo          *pEI  = NULL ;

        if (SUCCEEDED(CreateErrorInfo(&pCER)))
        {
            pCER->SetDescription(T2W(mesg)) ;
            hr = pCER->QueryInterface(IID_IErrorInfo, (LPVOID*)&pEI) ;
            if (SUCCEEDED(hr))
            {
                SetErrorInfo(NULL, pEI) ;
                pEI->Release() ;
            }
            pCER->Release() ;
        }
    }
}

void receive_init_error(gsi_procedure_user_data_type UD,
                        GsiItem *ErrorArgs,
                        gsi_int nArgCount,
                        gsi_call_identifier_type call_identifier)

{
    USES_CONVERSION ;
    if (nArgCount > 1)
    {
        ATLTRACE2(atlTraceGeneral,0,"Error Symbol %S\n", T2OLE((LPTSTR)gsi_symbol_name(gsi_sym_of(ErrorArgs[0]))));
        TCHAR *mesg = (TCHAR *)gsi_str_of(ErrorArgs[1]);
        ATLTRACE2(atlTraceGeneral,0,mesg);
        init_fail(mesg);
    }
}



/* ------------------------------------------------------------------------- */
/*                                                                           */
/*   Make sure G2Com.kb is loaded and that its version matches this version  */
/*                            of ActiveXLink                                 */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void receive_init_return (procedure_user_data_type procedure_user_data,
                          gsi_item *rpc_arguments,
                          gsi_int count,
                          call_identifier_type call_identifier)
{
    if (count != 2) {
        init_fail(NULL);
        return;
    }
    if (gsi_type_of(rpc_arguments[0]) != GSI_STRING_TAG)
        init_fail(NULL) ;
    TCHAR *val = (TCHAR *)gsi_str_of(rpc_arguments[0]);
    if (!val || _tcscmp(val, _T("SDF33sDS323''a[ep")))
    {  // fail, return error
        init_fail(NULL);
        return;
    }

    // Check version
    // -------------
    if (gsi_type_of(rpc_arguments[1]) != GSI_STRING_TAG)
    {
        init_fail(_T("G2Com.kb did not return a valid version"));
        return ;
    }

    TCHAR *kbver = (TCHAR *)gsi_str_of(rpc_arguments[1]) ;
    if (_tcscmp(kbver, AXL_VER))
    {
        gsi_char    pMsg[121] ;
//      _tcscpy(pMsg, _T("Version of G2Com.kb does not match ActiveXLink")) ;

#ifdef UNICODE
        _snwprintf((wchar_t *)pMsg, 120, L"Versions of ActiveXLink and G2Com.kb do not match!  Axl: %s.  G2Com.kb: %s", AXL_VER, kbver) ;
#else
        _snprintf(pMsg, 120, "Versions of ActiveXLink and G2Com.kb do not match!  Axl: %s.  G2Com.kb: %s", AXL_VER, kbver) ;
#endif  
        // Tell G2 about the problem
        // -------------------------
        if (_tcscmp(kbver, _T("1.0")))
        {
            gsi_int                     ctxNr = gsi_current_context() ;
            gsi_function_handle_type    informG2Handle;
            gsi_item                    myVer = gsi_make_item() ;
        
            gsi_rpc_declare_remote((void **) &informG2Handle, (gsi_char *)_T("_G2COM-BAD-VERSION"), NULL, NULL, 1, 0, ctxNr);
            gsi_set_str(myVer, (gsi_char *)AXL_VER) ;
            gsi_rpc_start((void *) informG2Handle, &myVer, ctxNr);
            gsi_reclaim_item(myVer) ;
        }
        init_fail((TCHAR *)pMsg) ;
        return ;
    }

    init_final();
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*           When the G2 run state changes, this function is called.         */
/*            It will cause the correct event-handler to be called.          */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void receive_g2_state(procedure_user_data_type procedure_user_data, gsi_item *rpc_arguments, gsi_int count, call_identifier_type call_identifier) 
{
    USES_CONVERSION ;

    ATLTRACE2(atrAxlMethodCalls,3,"Get G2 Run State\n");

    if (count == 1 && gsi_type_of(rpc_arguments[0]) == GSI_SYMBOL_TAG)
    {
        gsi_symbol  grs = gsi_sym_of(rpc_arguments[0]);
           ATLTRACE2(atrAxlMethodCalls,3,"Determined run state to be %S.\n",
               T2OLE((LPTSTR)gsi_symbol_name(grs)));

        GsiContext  *context = GsiContext::FindContext();

        if (!context)
        {
            ATLTRACE2(atlTraceGeneral,0,"Unable to recover context for run state\n");
            return;
        }

        // Change the remembered run state from Unknown to whatever it is
        // --------------------------------------------------------------
        CallData *cd = new CallData;
#if _MSC_VER == 1200  //VC++ 6.0
		if (!_tcscmp(gsi_symbol_name(grs),_T("RUNNING")))
			cd->EventCode = G2_RUNNING ;
        else if (!_tcscmp(gsi_symbol_name(grs), _T("RESET")))
#elif _MSC_VER >= 1300   //VC++ 7.0 OR MORE
		if (!_tcscmp((const wchar_t *)gsi_symbol_name(grs),_T("RUNNING")))
			cd->EventCode = G2_RUNNING ;
        else if (!_tcscmp((const wchar_t *)gsi_symbol_name(grs), _T("RESET")))
#endif
          
            cd->EventCode = G2_RESET ;
        else
            cd->EventCode = G2_PAUSED ;
        context->FireEventInThread(cd);
           ATLTRACE2(atrAxlMethodCalls,3,"Fired state information event.\n");


        // Tell the client that we now know the run state
        // ----------------------------------------------
        CallData *cd2 = new CallData ;

        cd2->EventCode = G2_RUN_STATE_KNOWN ;
        context->FireEventInThread(cd2);
    }

}

gsi_int gsi_initialize_context(gsi_char *init_string, gsi_int length)

{
    gsi_function_handle_type    validateHandle;
    gsi_function_handle_type    stateReadHandle ;
    gsi_int    ctxNr = gsi_current_context();

  // Call to check for an undocumented G2 procedure in the ActiveX KB to enforce a license.
    gsi_rpc_declare_remote_with_error_handler_and_user_data((void **) &validateHandle, (gsi_char *)_T("_G2COM-RPC-INTERNAL-CONVERT"), &receive_init_return, &receive_init_error, NULL, 0, 2, ctxNr);
    gsi_rpc_call((void *) validateHandle,  NULL, NULL, ctxNr);
    gsi_rpc_declare_remote((void **)&stateReadHandle, (gsi_char *)_T("G2-GET-G2-STATE"),receive_g2_state, NULL, 0, 1, ctxNr);
    gsi_rpc_call_with_count((void *) stateReadHandle, NULL, (gsi_int)1, NULL, ctxNr );


    return GSI_ACCEPT;
}

void gsi_receive_registration(gsi_registration reg)
{
}

void gsi_receive_deregistrations(gsi_registered_item regs[], gsi_int count)
{
}

void gsi_get_data(gsi_registered_item regs[], gsi_int count)
{
}

void gsi_set_data(gsi_registered_item regs[], gsi_int count)
{
}

void gsi_pause_context(void)
{
    ATLTRACE2(atrAxlMethodCalls,3,"Got pause from g2\n");
    GsiContext *context = GsiContext::FindContext();
    if (!context) {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
        return;
    }
  CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_PAUSE;
    context->FireEventInThread(cd);
}

void gsi_reset_context(void)
{
    ATLTRACE2(atrAxlMethodCalls,3,"Got reset from g2\n");
    GsiContext *context = GsiContext::FindContext();
    if (!context) {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
        return;
    }
    CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_RESET;
    context->FireEventInThread(cd);
}

void gsi_start_context(void)
{
    ATLTRACE2(atrAxlMethodCalls,3,"Got start from g2\n");
    GsiContext *pContext = GsiContext::FindContext();
    if (!pContext) {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
        return;
    }
    CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_START;
    pContext->FireEventInThread(cd);
}

void gsi_resume_context(void)

{
    ATLTRACE2(atrAxlMethodCalls,3,"Got resume from g2\n");
    GsiContext *context = GsiContext::FindContext();
    if (!context) {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
        return;
    }
    CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_RESUME;
    context->FireEventInThread(cd);
}

void gsi_shutdown_context(void)
{
    GsiContext *context;

    long ContextNumber = gsi_current_context();

    // This works around a bug in 10r2 that we can not get user data
    // -------------------------------------------------------------
    for (context = (GsiContext *) Contexts.GetFirst(); context;
      context = (GsiContext *) context->GetNext())
    {
        if (context->mContext == ContextNumber) break;
    }

#ifdef nothing
    long Id = (long) gsi_context_user_data(ContextNumber);
    context = (class GsiContext *) Contexts.FindObj(Id);
#endif

    if (!context) {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context in shutdown context\n");
        return;
    }

    // Find & delete the associated DisconReq object
    // ---------------------------------------------
    if (context->mConnReqId < 0)
    { // make sure there is a request object
        ConnectingRequest *req = (ConnectingRequest *) context->FindRequest(-context->mConnReqId);
        if (req)
            req->complete();
    }

    DisconReq *req = NULL;
    if (context->mConnReqId < 0)
    {
        req=(DisconReq*) context->FindRequest(-context->mConnReqId);
    }

    // Mark this context as completely disconnected
    // --------------------------------------------
    context->mIsConnected = false;
    context->mContext = -1;

    // Allow for case where a new disconnect is in process
    // ---------------------------------------------------
    if (context->mConnReqId < 0)
        context->mConnReqId = 0;

    // Fire disconnection event
    // ------------------------
    CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_DISCONNECT;
    context->FireEventInThread(cd);

    if (req)
        req->complete();
}

void gsi_g2_poll(void)

{
}

void gsi_receive_message(gsi_char *message, gsi_int length)

{
    USES_CONVERSION ;

    ATLTRACE2(atrAxlMethodCalls,3,"Got message from G2: %S\n", T2OLE((LPTSTR)message));

    GsiContext *context = GsiContext::FindContext();
    if (!context) return; // nothing to do, cant find context
    CallData *cd = new CallData;
    cd->Name = T2OLE((LPTSTR)message);
    cd->EventCode = GSI_EVENT_MESSAGE;
    context->FireEventInThread(cd);
}


//
// These callbacks keep track of the number of open file descriptors
// This is important since if no files are open, gsi_pause will not pause
// and the run loop thread will eat every available cycle.
//

void gsi_open_fd(int fd) 

{
    ATLTRACE2(atrAxlMsgs,4,"Open fd:%d\n", fd);
    InterlockedIncrement(&GsiThread::sNumFds);
}

void gsi_close_fd(int fd)

{
    ATLTRACE2(atrAxlMsgs,4,"Close fd:%d\n", fd);
    InterlockedDecrement(&GsiThread::sNumFds);
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GsiThread::GsiThread()
{

    // Set up the system for waking up gsi_pause under our control.
    // This will improve system responsiveness.
    // ------------------------------------------------------------
    int     i, WfdErrCode;
    WSADATA data;

    mPauseTimeout = NO_WAKEUP_PAUSE ; // Assume the wakeup initialization will fail
    mCount = 25 ; ;
    if(!(WfdErrCode=WSAStartup(MAKEWORD(2,2),&data)))
    {
        mListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        mAddrIn.sin_family = AF_INET;
        mAddrIn.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 
        mAddrIn.sin_port = htons (mLocalPort);
        for (i = mLocalPort; i < 65536; i++)
        {
            if (bind(mListenSocket, (const sockaddr *)&mAddrIn, sizeof mAddrIn))
            {
                WfdErrCode = WSAGetLastError ();
                if ((WfdErrCode == WSAEADDRINUSE) || (WfdErrCode == WSAEACCES))
                {
                    mLocalPort++;
                    mAddrIn.sin_port = htons(mLocalPort);
                    continue ;
                }
            }
            break;
        }
        if (!WfdErrCode)
            WfdErrCode = listen(mListenSocket, 1);
    }
    if (WfdErrCode)
        ATLTRACE("Unable to connect initialize gsi_watch_fd system.  Errcode %d.\n.", WfdErrCode) ;

    // Connect
    // -------
    bool    notConnected = true ;
    int     tries = 0 ;

    while (notConnected && !WfdErrCode)
    {
        sockaddr_in addr_out;
        hostent     *host = NULL;

        addr_out.sin_family = AF_INET;
        addr_out.sin_port = htons (mLocalPort);
        addr_out.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if ((mOut = socket(AF_INET, SOCK_STREAM, 0)) >= 0 &&    
                connect(mOut, (const sockaddr *)&addr_out, sizeof addr_out) >= 0)
            notConnected = false ;
        else
            if (++tries >= 25)
        {
            ATLTRACE("Failed to connect to Tickle socket after 25 tries");
            WfdErrCode = -1;
        }
    } 

    // Finalize the Watch FD system
    // ----------------------------
    unsigned long   temp = 1;
    int             addrlen = sizeof(mAddrIn);

    if (!WfdErrCode)
    {
        mIn = accept(mListenSocket, (struct sockaddr *)&mAddrIn, &addrlen);
        if (mIn < 0)
            WfdErrCode = WSAGetLastError();
        else if (ioctlsocket(mIn, FIONBIO, &temp)<0)
            WfdErrCode = WSAGetLastError();
        if (WfdErrCode)
            ATLTRACE("Unable to finalize FD watch system.  ErrCode %d.\n.", WfdErrCode) ;
        else
            mPauseTimeout = WAKEUP_PAUSE ;
    }

}

void GsiThread::start()
{
//  gsi_symbol gsyX ;

    // Set the options and start GSI
    // -----------------------------
    InitializeCriticalSection(&m_NoVanishingReqs) ;
    sNumFds = 0;  
    gsi_initialize_callbacks(gsi_name_of_gsi_set_up(), &gsi_set_up, (char*)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_get_tcp_port(), &gsi_get_tcp_port, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_initialize_context(), &gsi_initialize_context, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_pause_context(), &gsi_pause_context, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_resume_context(), &gsi_resume_context, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_shutdown_context(), &gsi_shutdown_context, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_receive_registration(), &gsi_receive_registration, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_receive_deregistrations(), &gsi_receive_deregistrations, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_g2_poll(), &gsi_g2_poll, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_get_data(), &gsi_get_data, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_set_data(), &gsi_set_data, (char *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_receive_message(), &gsi_receive_message, (char *)0) ;
    gsi_set_option(GSI_ONE_CYCLE);
    gsi_set_option(GSI_USER_DATA_FOR_CALLBACKS);
    gsi_set_option(GSI_SUPPRESS_OUTPUT);
    gsi_initialize_callbacks(gsi_name_of_gsi_open_fd(),&gsi_open_fd,(unsigned short *)0);
    gsi_initialize_callbacks(gsi_name_of_gsi_close_fd(),&gsi_close_fd,(unsigned short *)0);
    gsi_install_start_context(gsi_start_context);
    gsi_install_reset_context(gsi_reset_context);
    gsi_set_pause_timeout(mPauseTimeout); 

    char *arr[] = {"-nolistener", "-nolistener"};
    gsi_start(2,arr);


    // Start the GSI thread
    // --------------------
    mRefCount = 1;
    _beginthread(ThreadRoutine, 0, this);
}

GsiThread::~GsiThread()
{
    struct linger { int l_onoff ;
                    int l_linger ; } lingerOpt ;

    ATLTRACE2(atrAxlMethodCalls,3,"In Thread Destructor\n");
    if (mListenSocket)
    {
        // Force an immediate abort
        // ------------------------
        lingerOpt.l_onoff = lingerOpt.l_linger = 1 ;
        setsockopt(mListenSocket,SOL_SOCKET,SO_LINGER,(char*)&lingerOpt,sizeof(linger)) ;
        int errorFlag = closesocket(mListenSocket) ;
    }
    DeleteCriticalSection(&m_NoVanishingReqs) ;
}


int GsiThread::getWakeupFd()
{
    return mIn ;
}

long GsiThread::getPauseTimeout()
{
    return mPauseTimeout ;
}

//
// Timeout requests
//
void GsiThread::RequestTimeoutOrDelete(void)
{
    time_t now = time(NULL);
    static time_t last_time  = 0;
    if (now == last_time) return;  // don't do this more than once per second
    last_time = now;

    // Ok, run though each context and look at the timeout time of the first request for each timeout
    // Since all requests for a given object have the same timeout, we dont need to look past the first one
    // that does not timeout

    GsiContext *context;
    for (context = (GsiContext *) Contexts.GetFirst(); context; context = (GsiContext *) context->GetNext())
    {
        RequestObj *req, *nReq;
        for (req = (RequestObj *) context->Requests.GetFirst(); req; req = nReq)
        {
            nReq = (RequestObj *) req->GetNext();  // in case we delete the request
            if (now > req->mTimeout)
                req->timeout();
            if (req->Done() && (req->usedBy() == 0))
            {
                Queue.Remove2Only(req) ;            // If it is in Queue, Remove it
                context->Requests.Remove(req) ;     // Remove it from Requests & Delete it
            }
        }
    }
}


// Global Value that can be changed by G2ComConfigurator::set_HighThroughput
// -------------------------------------------------------------------------
DWORD   sleepTime = 10 ;
bool    gLockGsiThread = true ;

void GsiThread::RunThread()
{
    RequestObj *pRequest ;

    for (;mRefCount || gLockGsiThread;)
    { 
        EnterCriticalSection(&m_NoVanishingReqs);
        gsi_run_loop();  // do some work
        LeaveCriticalSection(&m_NoVanishingReqs);
        retrieveData() ;

        // Get the next request from the queue and process it.
        // --------------------------------------------------
        EnterCriticalSection(&m_NoVanishingReqs) ;
        pRequest = (RequestObj*)Queue.GetFirst() ;
        if (pRequest)
        {
            pRequest->usedBy(RequestObj::ProcessingLoop) ;
            Queue.Remove2Only(pRequest) ;
            if (pRequest->Ready())
                pRequest->invoke() ;
			if (pRequest->deleteAfterInvoke())
                if (pRequest->IsForcedDiscon())
                    delete pRequest ;
                else
                    pRequest->getContext()->Requests.Remove(pRequest) ;
            else
            {
                pRequest->stateToInvoked() ;
                pRequest->stopUseBy(RequestObj::ProcessingLoop) ;
            }
        }
        LeaveCriticalSection(&m_NoVanishingReqs) ;

        /* When a GsiContext is deleted, all the RequestObjs in its */
        /* Requests collection are moved to OrphanedReqs.           */
        /* -------------------------------------------------------- */
        EnterCriticalSection(&m_NoVanishingReqs) ;
        pRequest = (RequestObj*)m_OrphanedReqs.GetFirst() ;
        while (pRequest)
        {
            RequestObj* pNext = (RequestObj*)pRequest->GetNext() ;
            m_OrphanedReqs.Remove(pRequest) ;
            pRequest = pNext ;
        }
        LeaveCriticalSection(&m_NoVanishingReqs) ;
        
        // There is a problem with gsi_pause() if there are
        // no open sockets.  It will return with a error at once.
        // To work around this, we track the number of open file descriptors
        // and sleep for 1 ms if there are no open sockets.
        // 
        // The call back for gsi_run_state_change monitors the 
        // the wait and releases the lock.  So, while we are waiting,
        // the lock is released and other threads are free take the lock.
        //
        EnterCriticalSection(&m_NoVanishingReqs) ;
        RequestTimeoutOrDelete() ;
        LeaveCriticalSection(&m_NoVanishingReqs) ;

         /* The following three lines are commented out as a workaround for    */
         /* HQ-5312910 "No return from gsi_pause after gsi_initiate_connection */
         /* on non-existent G2/port.  The lines should be restored when the    */
         /* problem is fixed in GSI.                                           */
         /* ------------------------------------------------------------------ */
 /*      if (sNumFds)
             gsi_pause();
         else */
             Sleep(sleepTime);
    }
    ATLTRACE2(atrAxlMsgs,4,"Closing Thread\n");
    GsiThreadObj = NULL;
    delete this;
}


void GsiThread::wakePauseUp()
{
    if (mOut != -1) 
        send(mOut, "a", 1, 0);
}


void GsiThread::retrieveData()
{
    /* Only retrieve the data occasionally because it is slow */
    /* ------------------------------------------------------ */
    if (mCount++ >= 25)
    {
        mCount = 0;
        int nrBytes = recv(mIn, mBuffer, 100, 0);
    } 
}
