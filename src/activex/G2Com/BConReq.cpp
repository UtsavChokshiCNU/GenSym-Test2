// BConReq.cpp: implementation of the BConReq class.
//
// This code handles the logic for a blocking connection request.  This subclasses from
// the abstract class ConnectingRequest
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2Com.h"
#include "Gateway.h"
#include "BConReq.h"


#include "stdlib.h"
#include "GsiThread.h"
#include "GsiContext.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BConReq::BConReq(GsiContext *Context, TCHAR *InterfaceName, TCHAR *ClassName, TCHAR *Host,
                 unsigned short Port, TCHAR *RemoteInitString)
           : ConnectingRequest(Context, InterfaceName, ClassName, Host, Port, 
             RemoteInitString, BConnect)
{
    errorFlag = 0;  // no error
}

BConReq::~BConReq()
{}


// Create the Event Handle for Signalling Successful Connection
// ------------------------------------------------------------
int BConReq::prepare()
{
    Gatekeeper  gk(&mLocker) ;
    mEventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);

    // Return 0 is OK, 1 if an error
    // -----------------------------
    return (mEventHandle) ? 0 : 1 ;
}   

//
// Here is the logic to actually connect to the remote system
//
// ==========================================================
int BConReq::invoke()
{
    Gatekeeper  gk(&mLocker) ;
    GsiContext *pContext = getContext() ;
    if (!pContext)
    {
        SetComError(OLESTR("Internal Error"));
        return -9;  // not able to find context
    }

    if (pContext->mIsConnected)
        return 0;  // ok, already connected

    TCHAR buf[100];
    _itot(mPort, buf, 10);  // Convert to string for GSI

    TCHAR buf2[1024];
    _tcscpy(buf2, (TCHAR *) mClassName);
    for (TCHAR *ptr = buf2; *ptr; ptr++)
    {
        *ptr = _totupper(*ptr);
    }
    
    gk.unLock() ;
    int ret = gsi_initiate_connection_with_user_data((gsi_char *)(TCHAR *) mInterfaceName, (gsi_char *)buf2,
        ((VARIANT_FALSE == getContext()->getDiscOnReset()) ? TRUE : FALSE), 
        (gsi_char *)_T("TCP/IP"), (gsi_char *)(TCHAR *)mHost, (gsi_char *)buf, (gsi_char *)(TCHAR *)mRemoteInitString, (void *) pContext->mObjId);

    if (ret)
    {
        stateToError() ;
        SetComError(OLESTR("Unable to create connection with G2"));
        //CloseHandle(mEventHandle);
		SetEvent(mEventHandle);
        return -12;  // Error on connect
    }
    
    getContext()->mCtxKilled = FALSE ;
    stateToProcessed();

    return 0;
}

void BConReq::error()
{
    Gatekeeper  gk(&mLocker) ;
    GsiContext *pContext = GsiContext::FindContext(mContextObjId);
    if (!pContext)
        return; // nothing we can do
    pContext->mConnReqId = 0;  // no longer connecting
    pContext->mIsConnected = false;

    errorFlag = 1; // error happened
    SetEvent(mEventHandle);  // Release the waiting thread
}

//
// Ok, the request happened.
//
// This is called on the GSI run loop thread
//

void BConReq::complete()
{
    Gatekeeper  gk(&mLocker) ;
    GsiContext *pContext = getContext() ;
    if (!pContext)
        return;
    pContext->mConnReqId = 0; // no longer connecting
    pContext->mIsConnected = true; // now connecting
    pContext->mContext = gsi_current_context(); // save context number

    // This will fire the connected event even if we are
    // in a blocking connection
    CallData *cd = new CallData;
    cd->EventCode = GSI_EVENT_CONNECT;
    pContext->FireEventInThread(cd);
    SetEvent(mEventHandle);  // Release the waiting thread
}
