// NBConReq.cpp: implementation of the NBConReq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2Com.h"
#include "Gateway.h"
#include "NBConReq.h"
#include "GsiContext.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


NBConReq::NBConReq(GsiContext *Context, TCHAR *InterfaceName, TCHAR *ClassName, 
                   TCHAR *Host, unsigned short Port, TCHAR *RemoteInitString)
                     : ConnectingRequest(Context, InterfaceName, ClassName, 
                                   Host, Port, RemoteInitString, NBConnect)
{}

NBConReq::~NBConReq()
{}


//
// Here is the logic to actually connect to the remote system
// Returns 0 or -1
//

int NBConReq::invoke()
{
    Gatekeeper  gk(&mLocker) ;

    GsiContext *pContext = GsiContext::FindContext(mContextObjId);
    if (!pContext)
    {
        SetComError(OLESTR("Internal Error"));
        return -9;
    }
    if (pContext->mIsConnected)
        return 0; // If we are already connected, ok, done

    TCHAR buf[100];
    _itot(mPort, buf, 10);  // Convert to string for GSI

    TCHAR buf2[1024];  // make the interface name upper case
    _tcscpy(buf2, mClassName);
    for (TCHAR *ptr = buf2; *ptr; ptr++)
    {
        *ptr = _totupper(*ptr);
    }
    pContext->mConnReqId = Id();
    gk.unLock() ;
    int ret = gsi_initiate_connection_with_user_data((gsi_char *)(TCHAR *)mInterfaceName, (gsi_char *)buf2,
        ((VARIANT_FALSE == pContext->getDiscOnReset()) ? TRUE : FALSE), 
        (gsi_char *)_T("TCP/IP"), (gsi_char *)(TCHAR *)mHost,(gsi_char *) buf, (gsi_char *)(TCHAR *)mRemoteInitString, (void *) pContext->mObjId);
    if (ret)
    {
        SetComError(OLESTR("Unable to create connection with G2"));
        return -1;
    }
    getContext()->mCtxKilled = FALSE ;
    return 0; // ok
}


void NBConReq::error()
{
    Gatekeeper  gk(&mLocker) ;
    GsiContext *pContext = GsiContext::FindContext(mContextObjId);
    if (!pContext)
        return;
    pContext->mConnReqId = 0; // no longer connecting

    CallData *cd = new CallData;
    // Notify container of error
    cd->CallId = -1;
    cd->EventCode = GSI_EVENT_ERROR;
    cd->ErrorCode = mErrorCode;
    USES_CONVERSION;
    //    cd->ErrorMessage = SysAllocString(A2W((char *) mErrorMessage));
    cd->ErrorMessage = mErrorMessage;
    pContext->FireEventInThread(cd);
    stateToError() ;
}

void NBConReq::timeout()
{
    Gatekeeper  gk(&mLocker) ;
    GsiContext *pContext = GsiContext::FindContext(mContextObjId);
    if (!pContext)
        return;
    pContext->mConnReqId = 0;

    CallData *cd = new CallData;
    cd->CallId = -1;
    cd->EventCode = GSI_EVENT_ERROR;
    cd->ErrorCode = 0;
    // cd->ErrorMessage = SysAllocString(L"Timeout on non blocking connection attempt");
    cd->ErrorMessage = L"Timeout on non blocking connection attempt";
    pContext->FireEventInThread(cd);
    stateToError() ;
}

//
// Ok, the request happened.
//
// This is called on the GSI run loop thread
//

void NBConReq::complete()
{
    Gatekeeper  gk(&mLocker) ;
    // int ThreadId = GetCurrentThreadId();
    GsiContext *pContext = getContext() ;
    if (!pContext)
        return;
    ATLTRACE2(atrAxlMsgs,1,"Connection Complete\n");
    pContext->mIsConnected = true; // now connecting
    pContext->mContext = gsi_current_context(); // save context number
    pContext->mConnReqId = 0; // no longer pending connection

    CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_CONNECT;
    pContext->FireEventInThread(cd);
    stateToProcessed() ;
}
