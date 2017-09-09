// BRPCReq.cpp: implementation of the BRPCReq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2Com.h"
#include "Gateway.h"
#include "GsiContext.h"
#include "BRPCReq.h"
#include "gsi_main_cpp.h"
#include "G2ItemRef.h"
#include "Converter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BRPCReq::BRPCReq(GsiContext *Context, TCHAR *name, Datum *pInArgs, long nrArgsIn) 
                : RPCRequest(Context, name, pInArgs, nrArgsIn, Call)
{
    mHadError = false;
}

BRPCReq::~BRPCReq()
{
}

// Create the handle that will be used to signal to the container
// thread that the return values have been received and are ready.
//
// ===============================================================
int BRPCReq::prepare()
{
    Gatekeeper  gk(&mLocker) ;

    mEventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
    return mEventHandle ? 0 : -1 ;
}

//============================================================================//
//                                                                            //
//     This method is responsible for the actual call to a G2 procedure.      //
//                  It should only be run in the GSI thread.                  //
//                                                                            //
//============================================================================//
int BRPCReq::invoke(void)
{
    Gatekeeper  gk(&mLocker) ;

    // Tell GSI which G2 procedure we will call
    // ----------------------------------------
    GsiContext  *pContext = getContext() ;
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
        error() ;
    }

    // Convert the input parameters to GSI, the form needed to send them
    // to a G2 procedure.
    // -----------------------------------------------------------------
    gsi_item    *pGsiItems = (mCount > 0) ? gsi_make_items(mCount) : NULL ;
    if (!pGsiItems) mCount = 0 ;
    for (long lX = 0 ; lX < mCount ; lX++)
        mpArgsIn[lX].toGsiItem(pGsiItems[lX]) ;


    // Call the G2 procedure
    // ---------------------
    gk.unLock() ;
    gsi_rpc_call_with_count((void *) handle, pGsiItems, mCount, (void *) Id(), pContext->mContext);

    // Free up the memory used by the gsi_item sent to the G2 procedure
    // ----------------------------------------------------------------
    if (pGsiItems) GsiContext::deepReclaimGsiItems(pGsiItems, mCount);

    return 0 ;
}


void BRPCReq::error(void)
{
    Gatekeeper  gk(&mLocker) ;
    // We just set a error flag and release the thread
    mHadError = true;
    SetEvent(mEventHandle);
}



//============================================================================//
//                                                                            //
//   This method is called from the Call callback function after the return   //
//     values have been converted to Datums and attached to this BRPCReq.     //
//                                                                            //
//============================================================================//
void BRPCReq::complete(void)
{
    Gatekeeper  gk(&mLocker) ;

    SetEvent(mEventHandle);  // Release the waiting thread
}


//============================================================================//
//                                                                            //
//   This method generates an array of VARIANTs which are equivalent to the   //
//   attached return values (which are Datums).  It is the responsibility of  //
//   the caller to delete the array of VARIANTs with delete [].               //
//                                                                            //
//============================================================================//
HRESULT BRPCReq::RetVars(VARIANT **ppRetVars, long *plNrVars)
{
    HRESULT     hr ;
    Gatekeeper  gk(&mLocker) ;

	if (mNrRetVals && mpRetVals)
	{
		*ppRetVars = new VARIANT [mNrRetVals] ;
		if (!(*ppRetVars))
			return E_OUTOFMEMORY ;

		VARIANT	*pWk = *ppRetVars ;
		for (long lX = 0 ; lX < mNrRetVals ; lX++)
		{
            hr = mpRetVals[lX].toVariant(pWk+lX) ;
			if (FAILED(hr))
			{
				delete [] *ppRetVars ;
				return hr ;
			}
		}
	}
	else
		*ppRetVars = NULL ;
	*plNrVars = mNrRetVals ;

	return S_OK ;
}


/*============================================================================*/
/*                                                                            */
/*  COM ofter works with a SafeArray of VARIANTS to pass a list of parameters */
/*  to a method.  This method converts the return values from a call to a G2  */
/*  procedure to a Variant that contains a SafeArray of VARIANTS.  The caller */
/*  is responsible for the allocation of *pRetArray.                          */
/*                                                                            */
/*============================================================================*/
HRESULT	BRPCReq::RetArrayVar(VARIANT *pRetArrayVar, long *plNrVars)
{
    HRESULT     hr ;
    VARIANT     *pRetVars ;
    Gatekeeper  gk(&mLocker) ;

    VariantClear(pRetArrayVar) ;
    hr = RetVars(&pRetVars, plNrVars) ;
    if (FAILED(hr)) return hr ;

    SAFEARRAYBOUND  sab[1] ;
    SAFEARRAY       *pSA = NULL ;

    sab[0].cElements = *plNrVars ;
    sab[0].lLbound = 0 ;
    pSA = ::SafeArrayCreate(VT_VARIANT,1,sab) ;
    if (!pSA)
    {
        delete [] pRetVars ;
        return E_FAIL ;
    }

    for (long lX = 0 ; lX < *plNrVars ; lX++)
    {
        hr = ::SafeArrayPutElement(pSA, &lX, pRetVars+lX) ;
        if (FAILED(hr))
        {
            ::SafeArrayDestroy(pSA) ;
            delete [] pRetVars ;
            return E_UNEXPECTED ;
        }
    }

    delete [] pRetVars ;
    pRetArrayVar->vt = (VT_ARRAY | VT_VARIANT) ;
    pRetArrayVar->parray = pSA ;

    return S_OK ;
}
