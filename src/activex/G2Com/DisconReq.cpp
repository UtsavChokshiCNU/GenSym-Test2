// DisconReq.cpp: implementation of the DisconReq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GsiContext.h"
#include "DisconReq.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DisconReq::DisconReq(GsiContext *pCtx) : RequestObj(pCtx, Disconnect)
{
	//<Gensym-098> - create the event to notify disconnected event
	mEventHandle = CreateEvent(NULL,FALSE,FALSE,NULL);
	//</Gensym-098>
}

DisconReq::~DisconReq()
{
  if (NULL != mEventHandle) {
    CloseHandle(mEventHandle);
    mEventHandle = NULL;
  }
}

int DisconReq::invoke()
{
    Gatekeeper  gk(&mLocker) ;
    long    ctxNr = getContext()->mContext ;

    if (ctxNr >= 0)
        gsi_kill_context(ctxNr);
    getContext()->mCtxKilled = TRUE ;
    return 0 ;
}

void DisconReq::complete()
{
    Gatekeeper  gk(&mLocker) ;
    stateToProcessed() ;
	//<Gensym-098>
	SetEvent(mEventHandle);
	//</Gensym-098>
}


void DisconReq::error()
{
    Gatekeeper  gk(&mLocker) ;
    ATLTRACE ("Disconnect Error") ;

    GsiContext  *pCtx = getContext() ;

    // No longer disconnecting
    // -----------------------
    pCtx->mConnReqId = 0 ;

    // Notify container of error
    // -------------------------
    CallData *cd = new CallData;
    cd->CallId = -1;
    cd->EventCode = GSI_EVENT_ERROR;
    cd->ErrorCode = 2;
    cd->ErrorMessage = L"Error while disconnecting.";
    pCtx->FireEventInThread(cd);

    stateToError() ;
	//<Gensym-098>
	SetEvent(mEventHandle);
	//</Gensym-098>
}

void DisconReq::timeout()
{
    Gatekeeper  gk(&mLocker) ;
    getContext()->mConnReqId = 0 ;
    stateToError() ;
	//<Gensym-098>
	SetEvent(mEventHandle);
	//</Gensym-098>
}

