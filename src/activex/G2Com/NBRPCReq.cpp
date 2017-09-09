// NBRPCReq.cpp: implementation of the NBRPCReq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2Com.h"
#include "Gateway.h"
#include "NBRPCReq.h"
#include "G2ItemRef.h"
#include "gsi_misc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NBRPCReq::NBRPCReq(GsiContext *Context, TCHAR *name, Datum *pArgs, int count,
                   requestType rt) : RPCRequest(Context, name, pArgs, count, rt)
{
    ATLTRACE("Start %S.\n", name) ;
    static int _callId = 1;
    callId = _callId++;
    VariantInit(&DeferredCallId);
}

NBRPCReq::~NBRPCReq()
{
    VariantClear(&DeferredCallId);
}

int NBRPCReq::invoke(void)
{
    Gatekeeper  gk(&mLocker) ;

    GsiContext *pContext = GsiContext::FindContext(mContextObjId);
    if (!pContext)
        return -10;
    int handle = pContext->declareRemote(mName);

    // Make sure we are sending any items over the same context in which
    // the were originally received.
    // -----------------------------------------------------------------
    if (FAILED(CG2ItemRef::RefCtxChk(mpArgsIn, mCount, (long)pContext)))
    {
        if (mpRetVals)
            delete [] mpRetVals ;
        mpRetVals = new Datum [2] ;
        mpRetVals[0].Symbol(_T("WRONG-CONTEXT")) ;
        mpRetVals[1].String(_T("Receipt and transmission of reference must be on same G2Gateway")) ;
        mErrorCode = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 21) ;
        error() ;
    }

    // Convert the input parameters to GSI, the form needed to send them
    // to a G2 procedure.
    // -----------------------------------------------------------------
    gsi_item    *pGsiItems = (mCount > 0) ? gsi_make_items(mCount) : NULL ;
    if (!pGsiItems) mCount = 0 ;
    for (long lX = 0 ; lX < mCount ; lX++)
         mpArgsIn[lX].toGsiItem(pGsiItems[lX]) ;


    // Start or Call the G2 procedure
    // ------------------------------
    gk.unLock() ;
    if (RequestType() == CallDeferred)
        gsi_rpc_call_with_count((void *) handle, pGsiItems, mCount, (void *) Id(), pContext->mContext);
    else
        gsi_rpc_start_with_count((void *) handle, pGsiItems, mCount, pContext->mContext);

    // Free up the memory used by the gsi_item sent to the G2 procedure
    // ----------------------------------------------------------------
    if (pGsiItems) GsiContext::deepReclaimGsiItems(pGsiItems, mCount);
    return 0;
}


void NBRPCReq::error(void)
{
    Gatekeeper  gk(&mLocker) ;

    USES_CONVERSION ;

    // Notify container of error
    // Since we can not signal the original caller, we can issue a error event
    GsiContext *pContext = GsiContext::FindContext(mContextObjId);
    if (!pContext)
        return;

    CallData *cd = new CallData;
    cd->CallId = callId;
    cd->ErrorCode = mErrorCode;


    if (mNrRetVals > 1)
    {
        TCHAR *pErrSym = mpRetVals[0].Symbol() ;
        TCHAR *pErrMsg = mpRetVals[1].String() ;

        ATLTRACE2(atrAxlMsgs, 0, "Error Symbol %s\n", T2A(pErrSym));
        delete [] pErrSym ;

        // This code works because ErrorMessage is a CComBSTR,
        // which makes a copy of the error message string
        // ---------------------------------------------------
        cd->ErrorMessage = T2OLE(pErrMsg);
        delete [] pErrMsg;
    }
    else
    {
        cd->ErrorMessage = OLESTR("Exception Object Returned from G2 RPC");
    }

    VariantCopy(&cd->DeferredCallId, &DeferredCallId);
    cd->EventCode = GSI_EVENT_ERROR;
    pContext->FireEventInThread(cd);
    stateToError() ;
}


/* ========================================================================== */ 
/*                                                                            */
/*   The only time this method is called when we receive the return values    */
/*                          from a CallDeferred                               */
/*                                                                            */
/* ========================================================================== */ 
void NBRPCReq::complete(void)
{
    Gatekeeper  gk(&mLocker) ;
    GsiContext *pContext = GsiContext::FindContext(mContextObjId);
    if (!pContext)
        return;

    // Attach the information the event handler will require to a CallData object
    // --------------------------------------------------------------------------
    CallData *cd = new CallData;
    cd->mCount = mNrRetVals;
    cd->mArgs = mpRetVals ;
    cd->CallId = callId;
    cd->EventCode = GSI_EVENT_RETURN;
    cd->Name = mName;
    cd->mContext = pContext->mObjId;
    VariantCopy(&cd->DeferredCallId, &DeferredCallId); // copy user data

    // Relieve this NBRPCReq of the responsibility of deleting *mpRetVals
    // ------------------------------------------------------------------
    mNrRetVals =  0;
    mpRetVals = NULL ;

    // Call the event handler
    // ----------------------
    pContext->FireEventInThread(cd);
    stateToProcessed() ;
}


//
// This is called when a non blocking request times out
// We want to remove the request object
//
void NBRPCReq::timeout(void)

{
    Gatekeeper  gk(&mLocker) ;
    GsiContext *pContext = GsiContext::FindContext(mContextObjId);
    if (!pContext)
        return;
    CallData *cd = new CallData;
    cd->CallId = callId;
    cd->ErrorCode = 0;
    cd->ErrorMessage = L"Timeout on deferred RPC call";
    cd->EventCode = GSI_EVENT_ERROR;
    pContext->FireEventInThread(cd);
    stateToError();
}

