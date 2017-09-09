// RetValsReq.cpp: implementation of the RetValsReq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RetValsReq.h"
#include "GsiContext.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RetValsReq::RetValsReq(GsiContext* pCtx, Datum* pArgs, int iNrArgs, void* pCallId) :
	     RequestObj(pCtx, RetVals), mpArgs(pArgs), mCount(iNrArgs), mpCallId(pCallId)
{

}

RetValsReq::~RetValsReq()
{
    if (mpArgs)
        delete [] mpArgs ;
}

inline Datum *RetValsReq::ArgsPtr()
{
    Gatekeeper  gk(&mLocker) ;
	return mpArgs ;
}

inline long RetValsReq::NrArgs()
{
    Gatekeeper  gk(&mLocker) ;
	return mCount ;
}

// No need for prepare method

int RetValsReq::invoke()
{
    Gatekeeper  gk(&mLocker) ;

    // Tell GSI which G2 procedure we will call
    // ----------------------------------------
    GsiContext  *pContext = getContext() ;
    if (!pContext)
        return -10;

    // Convert the input parameters to GSI, the form needed to send them
    // to a G2 procedure.
    // -----------------------------------------------------------------
    gsi_item    *pGsiItems = (mCount > 0) ? gsi_make_items(mCount) : NULL ;
    if (!pGsiItems) mCount = 0 ;
    for (long lX = 0 ; lX < mCount ; lX++)
        mpArgs[lX].toGsiItem(pGsiItems[lX]) ;

    // Return the values to G2
    // -----------------------
    gsi_rpc_return_values(pGsiItems, mCount, (void *) mpCallId, pContext->mContext);

    // Free up the memory used by the gsi_item sent to the G2 procedure
    // ----------------------------------------------------------------
    if (pGsiItems) GsiContext::deepReclaimGsiItems(pGsiItems, mCount);

    return 0 ;
}

void RetValsReq::complete()
{
}

void RetValsReq::error()
{
}
