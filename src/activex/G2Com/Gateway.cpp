// Gateway.cpp : Implementation of CG2Gateway

#include "stdafx.h"
#include "Converter.h"
#include "G2Com.h"
#include "Gateway.h"
#include "BConReq.h"
#include "Converter.h"
#include "Datum.h"
#include "DisconReq.h"
#include "NBConReq.h"
#include "BRPCReq.h"
#include "NBRPCReq.h"
#include "RetValsReq.h"
#include "GsiThread.h"
#include "GsiContext.h"
#include "G2Item.h"
#include "G2ItemRef.h"
#include "Subscription.h"
#include <crtdbg.h>


//
// Thread safety and locking must be handled very carefully.  We have locking placed around gsi in the gsiWrapper object
// This is not enough since there are other data structures that must be safely updated.  Placing locks on all of these
// data structures is not enough either, since this may result in deadlocks.  It would be bad for the runloop to cycle,
// take the lock on gsi and try to access some other data stucture that is locked by a thread waiting to use gsi.
//
// Instead, we have one lock for the entire system and obtain it before touching any data structures or gsi.  While
// we own the lock, the run loop will not be able to cycle, nor will any other clients be able to launch their threads.

//
// I put the constructor/destructors here
//

//
// Request objects have their own lock.  This lets the invoke() methods, which make block to release
// the lock on the run loop before calling gsi.  This lets us choose when to yield the processor.
//

CG2Gateway::CG2Gateway(): m_TWHandle(0L), m_TWLockIsInUse(false)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Gateway constructor\n");
    // We only want one thread object that is shared by all instances
    if (!GsiThreadObj)
    {
        GsiThreadObj = new GsiThread; // create and start GSI interface
        GsiThreadObj->start() ;
    }
    GsiThreadObj->addRef();

    // Now create a GsiContext Object
    mpContext = new GsiContext;
    Contexts.Add(mpContext);
    mpContext->mThreadObj = NULL;

    m_bAutoSize = 1 ;

    SIZE sz = { 50, 50 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);
    m_sizeNatural = m_sizeExtent;
}

CG2Gateway::~CG2Gateway()
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Gateway Destructor\n");

    if (mpContext)
    {
        if (GsiThreadObj)
            EnterCriticalSection(&GsiThreadObj->m_NoVanishingReqs) ;
        Contexts.Remove(mpContext);
        if (GsiThreadObj)
            LeaveCriticalSection(&GsiThreadObj->m_NoVanishingReqs) ;
    }
    if (GsiThreadObj)
        GsiThreadObj->delRef();

}

// ========================================================================== //
//                                                                            //
//        Force a disconnect from G2 if the containing form is closed         //
//                                                                            //
// ========================================================================== //
STDMETHODIMP CG2Gateway::SetClientSite(IOleClientSite *pClientSite)
{
    if (pClientSite == NULL)
        Disconnect() ;
    return IOleObjectImpl<CG2Gateway>::SetClientSite(pClientSite) ;
}


/////////////////////////////////////////////////////////////////////////////
// CGateway


#if _MSC_VER == 1200  //VC++ 6.0
STDMETHODIMP CG2Gateway::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] =
        {
            &IID_IG2Gateway4,
        };
    for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
    {
        if (::ATL::InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}


#elif _MSC_VER >= 1300  //VC++ 7 or more
STDMETHODIMP CG2Gateway::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] =
	{
		&IID_IG2Gateway4,
	};
    for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}
#endif


HRESULT CG2Gateway::OnDraw(ATL_DRAWINFO& di)
{
    HBRUSH  hbrush, holdbrush ;
    HPEN    holdpen ;

    hbrush = CreateSolidBrush(RGB(0,128,128)) ;
    holdbrush = (HBRUSH)SelectObject(di.hdcDraw, hbrush) ;
    holdpen = (HPEN)SelectObject(di.hdcDraw, GetStockObject(BLACK_PEN) ) ;
    RECT& rc = *(RECT*)di.prcBounds;
    Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
    SetTextColor(di.hdcDraw,RGB(0,255,63)) ;
    SetBkColor(di.hdcDraw, RGB(0,128,128)) ;
    DrawText(di.hdcDraw, _T("G2-AXL"), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    SelectObject(di.hdcDraw, holdpen) ;
    SelectObject(di.hdcDraw, holdbrush) ;
    DeleteObject(hbrush) ;
    return S_OK;
}

//
// This overrides the default implementation of close
//
HRESULT CG2Gateway::Close( DWORD dwSaveOption )
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Gateway::Close\n");
    if (mpContext)
    {
        if (mpContext->mThreadObj)
        {  // release thread object
            mpContext->mThreadObj->releaseObj();
            mpContext->mThreadObj = NULL;
        }
        Disconnect();  // make sure we break the connection
    }
    HRESULT hr = IOleObjectImpl<CG2Gateway>::Close(dwSaveOption);
    return hr;
}

/* ========================================================================== */
/*                                                                            */
/*               Issue a blocking connect request, if needed.                 */
/*                                                                            */
/* ========================================================================== */
int CG2Gateway::AutoConnect()
{
    USES_CONVERSION;
    if (!mpContext)
        return -1;
    if (!mpContext->mThreadObj)
        mpContext->mThreadObj = new EventThread((IG2Gateway*)this);
    if (mpContext->mIsConnected)
        return 0;

    // launch the event thread if it is not there already

    CComBSTR ClassName = mpContext->ClassName();
    CComBSTR Host = mpContext->Host();
    int Port = mpContext->Port();
    CComBSTR Ris = mpContext->RemoteInitString();

    BConReq *req = new BConReq(mpContext, NULL, OLE2T(ClassName),OLE2T(Host), Port, OLE2T(Ris));
    if (!req) return E_FAIL;
    req->usedBy(RequestObj::ContainerThread) ;
    if (req->prepare())
    {
        req->stopUseBy(RequestObj::ContainerThread) ;
        return E_FAIL ;
    }
    mpContext->mConnReqId = req->Id() ;

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    mpContext->Requests.Add(req);
    Queue.Add2(req) ;
    GsiThreadObj->wakePauseUp() ;

    // Wait for the connection or timeout
    int ret = WaitForSingleObject(req->mEventHandle, mpContext->mBlockingTimeout*1000);
    CloseHandle(req->mEventHandle); // Release handle, we are done with it
    mpContext->mConnReqId = 0;  // cancel the request object
    mpContext->Requests.RemoveOnly(req) ;

    long    rc = S_OK ;
    if (ret)
    {
        SetComError(OLESTR("Timeout on Connect"));
        rc = E_FAIL ;
    } 
    else if (req->errorFlag)
    {
        SetComError(req->mErrorMessage);
        rc = E_FAIL; // error detected
    }
    if (rc == S_OK)
        req->stateToProcessed() ;
    else
        req->stateToError() ;
    req->stopUseBy(RequestObj::ContainerThread) ;
    return rc;
}


/* ========================================================================== */
/*                                                                            */
/*                Display a message on the G2 message board  .                */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Gateway::PostMessage(VARIANT *Message)
{
    if (!mpContext)
        return E_FAIL;
    if (AutoConnect())
        return E_FAIL;  // make sure we are connected

    Datum     *pVar = new Datum[1] ;
    *pVar = *Message ;

    USES_CONVERSION ;
    NBRPCReq *req = new NBRPCReq(mpContext, _T("_g2com-rpc-post-message"), pVar, 1, 
        RequestObj::Start);
    if (!req)
        return E_FAIL;
    req->usedBy(RequestObj::ContainerThread) ;
    if (req->prepare()) return E_FAIL ;  // Generic behavior, not used.

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    mpContext->Requests.Add(req) ;
    Queue.Add2(req) ;
    GsiThreadObj->wakePauseUp() ;
    req->stopUseBy(RequestObj::ContainerThread) ;
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/* Add either a blocking or non-blocking connect request to the queue         */
/* depending upon the setting of bWaitflag.  If it was a blocking connect     */
/* wait in this routine for the completion of the connection or timeout.      */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Gateway::Connect(VARIANT_BOOL bWaitflag)
{
    // An event thread which is necessary to fire events is only necessary once
    // the first connection is made.  There is one event thread per context.
    //
    // If we have not yet created an event thread, this is the place to do it.
    // -----------------------------------------------------------------------
    if (!mpContext->mThreadObj)
        mpContext->mThreadObj = new EventThread((IG2Gateway*)this);

    // Deal with connect in progress.  If this is a request for a blocking
    // connect, replace the prior (non-blocking) request with this one.  Otherwise
    // forget about this request.
    //
    // Note that this means if the request that is in progress failed, you 
    // normally would have to wait for timeout before a new connect request
    // would be processed.  The way around this is to call disconnect before
    // trying the new connect.  Disconnect has been designed to abort an
    // in-process connection request.
    // ---------------------------------------------------------------------
    if (mpContext->mConnReqId > 0)
    {
        if (bWaitflag == VARIANT_FALSE)
            return S_OK ;
        try
        {
            ConnectingRequest* req = (ConnectingRequest *)Queue.FindObj(mpContext->mConnReqId) ;
            if (req)
                req->stateToError() ;
            else
            {
                req = (ConnectingRequest *) mpContext->Requests.FindObj(mpContext->mConnReqId);
                if (req)
                    req->stateToError() ;
            }
            mpContext->mConnReqId = 0 ;
        }
        catch (...)
        {
        }
    }

    // If we are already connected, then there is nothing more to do
    // -------------------------------------------------------------
    if (mpContext->mIsConnected)
    {
        return S_OK;
    }


    // Create the correct type of Connecting Request object
    // ----------------------------------------------------
    CComBSTR ClassName = mpContext->ClassName();
    CComBSTR Host = mpContext->Host();
    int Port = mpContext->Port();
    CComBSTR Ris = mpContext->RemoteInitString();

    USES_CONVERSION ;
    ConnectingRequest  *req ;
    if (bWaitflag)
        req = new BConReq(mpContext, NULL, OLE2T(ClassName), OLE2T(Host), Port, OLE2T(Ris));
    else
        req = new NBConReq(mpContext, NULL, OLE2T(ClassName), OLE2T(Host), Port, OLE2T(Ris));
    if (!req)
    {
        return E_FAIL;
    }

    // If this is a blocking request, create an event handle.
    // ------------------------------------------------------
    if (req->prepare()) 
    {
        return E_FAIL ;
    }
    mpContext->mConnReqId = req->Id() ;

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    req->usedBy(RequestObj::ContainerThread) ;
    mpContext->Requests.Add(req);
    Queue.Add2(req) ;
    GsiThreadObj->wakePauseUp() ;

    // We are done if performing Connect(FALSE)
    // ----------------------------------------
    if (!bWaitflag)
    {
        req->stopUseBy(RequestObj::ContainerThread) ;
        return S_OK;
    }

    // Wait for the connection or timeout
    // ----------------------------------
    BConReq *pBCon = (BConReq*)req ;
    int ret = WaitForSingleObject(pBCon->mEventHandle,
                                mpContext->mBlockingTimeout*1000);
    CloseHandle(pBCon->mEventHandle); // Release handle, we are done with it
    mpContext->mConnReqId = 0;  // cancel the request object

    // If there was an error or timeout, remove the Connecting
    // Request Object from Request and return an error to the caller
    // -------------------------------------------------------------
    long rc = S_OK ;
    if (ret)
    {
        SetComError(OLESTR("Timeout while connecting to G2"));
        rc = E_FAIL ;
    }
    else if (pBCon->errorFlag)
    {
        SetComError(pBCon->mErrorMessage);
        rc = E_FAIL ;
    }
    if (rc)
        req->stateToError() ;
    else
        req->stateToProcessed() ;
    req->stopUseBy(RequestObj::ContainerThread) ;
    return rc ;
}

/* ========================================================================== */
/*                                                                            */
/*     Request a call to gsi_shutdown_context to break the G2 connection      */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Gateway::Disconnect()
{
    if (!mpContext)
        return S_OK;

    // If a connection is in process, abort it, if possible.
    // -----------------------------------------------------
    if (mpContext->mConnReqId > 0) 
        return E_PENDING ;

    // Ignore this request if a disconnect is already in process
    // ---------------------------------------------------------
    else if (mpContext->mConnReqId < 0)
        return S_OK ;

    // We are already disconnected when mContext == -1
    // -----------------------------------------------
    else if (mpContext->mContext == -1)
    {
        mpContext->mIsConnected = false ;
        return S_OK;
    }

    // Remember this disconnect object so we can detect completion or failure
    // ----------------------------------------------------------------------
    DisconReq   *pDiscon = new DisconReq(mpContext) ;
    pDiscon->usedBy(RequestObj::ContainerThread) ;
    mpContext->Requests.Add(pDiscon) ;

    // Flag this context as disconnecting
    // and as not available
    // ----------------------------------
    mpContext->mConnReqId = - pDiscon->Id() ;
    mpContext->mIsConnected = false ;
   
    // Tell GSI Thread to disconnect
    // -----------------------------
    Queue.Add2(pDiscon) ;
    GsiThreadObj->wakePauseUp() ;
    if (mpContext->mContext != -1) {
        WaitForSingleObject(pDiscon->mEventHandle,mpContext->mBlockingTimeout*1000);
        CloseHandle(pDiscon->mEventHandle);
        pDiscon->mEventHandle = NULL;
    }
    pDiscon->stopUseBy(RequestObj::ContainerThread) ;
    return S_OK;

}



/* ========================================================================== */
/*                                                                            */
/*            Call a G2 procedure and wait for the return values              */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Gateway::Call(BSTR sRPCName, SAFEARRAY **pInArgs, VARIANT *pOutArgs)
{
    USES_CONVERSION ;

    Datum*      pUnpackedArgs = NULL ;
    HRESULT     hr ;
    long        nrArgs;
    SAFEARRAY   *pSA = *pInArgs;

    if (!mpContext)
        return E_FAIL;
    if (AutoConnect())
        return E_FAIL;


    // Create the Array of Datums that will
    // be passed to the BRPCReq constructor.
    // -------------------------------------
    if (FAILED(hr = Converter::SafeArrayToDatumArray(pSA, &pUnpackedArgs, &nrArgs)))
        return hr ;


    // Create the Blocking RPC Request object that tracks this Call
    // ------------------------------------------------------------
    BRPCReq *req = new BRPCReq(mpContext, OLE2T(sRPCName), pUnpackedArgs, nrArgs);
    if (!req)
        return E_FAIL;

    // Create an event handle.
    // -----------------------
    if (req->prepare()) return E_FAIL ;
    req->usedBy(RequestObj::ContainerThread) ;

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    mpContext->Requests.Add(req);
    Queue.Add2(req) ;
 
    // Wait for the return values or timeout
    // -------------------------------------
    int ret = WaitForSingleObject(req->mEventHandle, 
                            mpContext->mBlockingTimeout * 1000);

    // Release handle, we are done with it
    //  ----------------------------------
    CloseHandle(req->mEventHandle);

    // Detect & report timeout
    // -----------------------
    if (ret)
    {
        req->stateToError() ;
        SetComError(OLESTR("Timeout on RPC Request"),&IID_IG2Gateway,L"G2Gateway.G2Gateway");
        ret = -ret ;
    }

    // RPC Failed
    // ----------
    else if (req->mHadError)
    { 
        req->stateToError() ;

        // Error information was returned
        // ------------------------------
        if (req->mNrRetVals > 1 && req->RetValPtr()[0].Type() == dtySymbol && req->RetValPtr()[1].Type() == dtyString)
        { 
            TCHAR *pErrSym = req->RetValPtr()[0].Symbol() ;
            TCHAR *pErrMsg = req->RetValPtr()[1].String() ;

            ATLTRACE2(atrAxlMsgs, 0, "Error Symbol %s\n", T2A(pErrSym));
            SetComError(T2OLE(pErrMsg));
            delete [] pErrSym ;
            delete [] pErrMsg ;
        }

        // No error info.  Give generic messsage.
        // --------------------------------------
        else
        { 
            SetComError(OLESTR("Exception Object Returned from G2 RPC"));
        }
        ret = -20 ;
    }

    // No known errors
    // Convert the Array of Datums containing the return values to a
    // Variant containing either the value (just one value returned)
    // or a SafeArray of Variants.(multiple values returned)
    // -------------------------------------------------------------
    else
    {
        Converter::DatumsToArrayVarOrVar(req->RetValPtr(),req->NrRetVals(),pOutArgs) ;
        req->stateToProcessed() ;
    }

    // Remove the BRPCReq from Requests & flag OK to delete.
    // ----------------------------------------------------
    req->stopUseBy(RequestObj::ContainerThread) ;
    return ret;
}



/* ========================================================================== */
/*                                                                            */
/*         Call a G2 procedure, but don't wait for the return values.         */
/*            The caller will get the return values via an event.             */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Gateway::CallDeferred(BSTR sRPCName, VARIANT *DeferredCallIdentifier, SAFEARRAY **pInArgs)
{
    Datum       *pUnpackedArgs ;
    HRESULT     hr ;
    long        nrArgs ;
    SAFEARRAY   *pSA = *pInArgs;

    USES_CONVERSION ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Gateway::CallDeferred: %S\n", mpContext->Host());
    if (!mpContext)
        return E_FAIL;
    if (AutoConnect())
        return E_FAIL;

    // Create a NBRPCReq and put it into the Requests queue so the code
    // can find out about this Call when it receives the return values.
    // -----------------------------------------------------------------
    if (FAILED(hr = Converter::SafeArrayToDatumArray(pSA, &pUnpackedArgs, &nrArgs)))
        return hr ;
    NBRPCReq *req = new NBRPCReq(mpContext, OLE2T(sRPCName), pUnpackedArgs, nrArgs, 
                                                            RequestObj::CallDeferred);
    if (!req)
        return E_FAIL;
    req->usedBy(RequestObj::ContainerThread);
    VariantCopy(&req->DeferredCallId, DeferredCallIdentifier);
    if (req->prepare()) 
    {
        req->stopUseBy(RequestObj::ContainerThread);
        return E_FAIL ;  // Generic behavior, not used.
    }
    mpContext->Requests.Add(req);

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    Queue.Add2(req) ;
    GsiThreadObj->wakePauseUp() ;
    req->stopUseBy(RequestObj::ContainerThread);
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/*                           Start a G2 procedure                             */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Gateway::Start(BSTR sRPCName, SAFEARRAY **pArgs)
{
    Datum       *pUnpackedArgs ;
    HRESULT     hr ;
    long        nrArgs ;
    SAFEARRAY   *pSA = *pArgs;

    USES_CONVERSION ;

    // The implementation of the Start method is almost the same as that of
    // the CallDeferred method.  However Start does not use a user-provided
    // call ID and the NBRPCReq object is not put in the Request queue.
    // --------------------------------------------------------------------
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Gateway::Start: %S\n", mpContext->Host());
    if (!mpContext)
        return E_FAIL;
    if (AutoConnect())
        return E_FAIL;

    // Create a NBRPCReq and put it into the Requests queue so the code
    // can find out about this Call when it receives the return values.
    // -----------------------------------------------------------------
    if (FAILED(hr = Converter::SafeArrayToDatumArray(pSA, &pUnpackedArgs, &nrArgs)))
        return hr ;
    NBRPCReq *req = new NBRPCReq(mpContext, OLE2T(sRPCName), pUnpackedArgs, nrArgs, 
                                                                    RequestObj::Start);
    if (!req)
        return E_FAIL;
    if (req->prepare()) return E_FAIL ;  // Generic behavior, not used.

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    mpContext->Requests.Add(req) ;
    Queue.Add2(req) ;
    GsiThreadObj->wakePauseUp() ;
    return S_OK ;
}


STDMETHODIMP CG2Gateway::GetNamedObject(BSTR sObjName, BSTR sObjClass, LPDISPATCH * pObj)
{
    return E_NOTIMPL ;
}

STDMETHODIMP CG2Gateway::CreateObjectInstance(BSTR sClassName, LPDISPATCH * pObj)
{
    return E_NOTIMPL;
}

STDMETHODIMP CG2Gateway::get_IsG2Connected(VARIANT_BOOL * pVal)
{
    *pVal = mpContext->IsConnected() ? VARIANT_TRUE : VARIANT_FALSE;

    return S_OK;
}

STDMETHODIMP CG2Gateway::get_IsG2Running(VARIANT_BOOL * pVal)
{
    *pVal = mpContext->IsRunning() ? VARIANT_TRUE : VARIANT_FALSE;

    return S_OK;
}

STDMETHODIMP CG2Gateway::get_G2Location(BSTR * pVal)
{
    USES_CONVERSION;
    char buf[100];

    CComBSTR sHostAndPort;
    // Assemble Host and Port from the GsiContext Object
    sHostAndPort = mpContext->Host();
    sHostAndPort += _T(":");
    sHostAndPort += _itoa(mpContext->Port(), buf, 10);

    *pVal = SysAllocString((BSTR) sHostAndPort);

    return S_OK;
}

STDMETHODIMP CG2Gateway::put_G2Location(BSTR newVal)
{
    int newValLen;
    WCHAR* pPort;
    int hostLen;
    CComBSTR host;


    ATLTRACE2(atrAxlMethodCalls, 3, "CGateway::put_Host(%ws)\n", newVal);

    newValLen = SysStringLen(newVal);
    if (newValLen == 0)
        return Error("G2 Host must contain an entry.");

    // Disassemble Host:Port for GsiContext Object without changing
    // the input string.
    pPort = wcschr(newVal, L':');
    if (pPort != NULL)
    {
        // determine the host length before we do anything else
        hostLen = pPort - newVal;

        // move past the : and check the first digit or the port
        pPort++;

        ATLTRACE2(atrAxlMethodCalls, 1, "new port = %ws\n", pPort);
        if (iswdigit(*pPort))
        {
            mpContext->Port(_wtoi(pPort));
        }
        else
        {
            return Error(L"Invalid location format, the port is not numeric.");
            return E_INVALIDARG;
        }
    }
    else
    {
        // Assume default G2 port of 1111.
        mpContext->Port(1111);
        hostLen = newValLen;
    }

    host.Attach(SysAllocStringLen(newVal, hostLen));
    ATLTRACE2(atrAxlMethodCalls, 1, "new host = %ws\n", host);
    mpContext->Host(host);

    SetDirty(TRUE);
    SendOnDataChange();
    FireOnChanged(10);
    return S_OK;
}

STDMETHODIMP CG2Gateway::get_InterfaceClass(BSTR * pVal)
{
    *pVal = SysAllocString(mpContext->ClassName());

    return S_OK;
}

STDMETHODIMP CG2Gateway::put_InterfaceClass(BSTR newVal)
{
    mpContext->ClassName(newVal);
    SetDirty(TRUE);
    SendOnDataChange();
    FireOnChanged(11);

    return S_OK;
}

STDMETHODIMP CG2Gateway::get_RemoteInitializationString(BSTR * pVal)
{
    *pVal = SysAllocString(mpContext->RemoteInitString());

    return S_OK;
}

STDMETHODIMP CG2Gateway::put_RemoteInitializationString(BSTR newVal)
{
    mpContext->RemoteInitString(newVal);
    SetDirty(TRUE);
    SendOnDataChange();
    FireOnChanged(12);

    return S_OK;
}

STDMETHODIMP CG2Gateway::get_CallTimeout(long * pVal)
{
    *pVal = mpContext->mBlockingTimeout;

    return S_OK;
}

STDMETHODIMP CG2Gateway::put_CallTimeout(long newVal)
{
    mpContext->mBlockingTimeout = newVal;
    SetDirty(TRUE);
    SendOnDataChange();
    FireOnChanged(13);

    return S_OK;
}

STDMETHODIMP CG2Gateway::OnStartPage (IUnknown* pUnk)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Gateway::OnStartPage");
    if(!pUnk)
        return E_POINTER;

    CComPtr<IScriptingContext> spContext;
    HRESULT hr;

    // Get the IScriptingContext Interface
    hr = pUnk->QueryInterface(IID_IScriptingContext, (void **)&spContext);
    if(FAILED(hr))
        return hr;

    // Get Request Object Pointer
    hr = spContext->get_Request(&m_piRequest);
    if(FAILED(hr))
    {
        spContext.Release();
        return hr;
    }

    // Get Response Object Pointer
    hr = spContext->get_Response(&m_piResponse);
    if(FAILED(hr))
    {
        m_piRequest.Release();
        return hr;
    }

    // Get Server Object Pointer
    hr = spContext->get_Server(&m_piServer);
    if(FAILED(hr))
    {
        m_piRequest.Release();
        m_piResponse.Release();
        return hr;
    }

    // Get Session Object Pointer
    hr = spContext->get_Session(&m_piSession);
    if(FAILED(hr))
    {
        m_piRequest.Release();
        m_piResponse.Release();
        m_piServer.Release();
        return hr;
    }

    // Get Application Object Pointer
    hr = spContext->get_Application(&m_piApplication);
    if(FAILED(hr))
    {
        m_piRequest.Release();
        m_piResponse.Release();
        m_piServer.Release();
        m_piSession.Release();
        return hr;
    }
    m_bOnStartPageCalled = TRUE;
    return S_OK;
}

STDMETHODIMP CG2Gateway::OnEndPage ()
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Gateway::OnEndPage");
    m_bOnStartPageCalled = FALSE;

    // Release all interfaces
    // ----------------------
    m_piRequest.Release();
    m_piResponse.Release();
    m_piServer.Release();
    m_piSession.Release();
    m_piApplication.Release();

    // Shutdown the GSI-processing event thread
    // ----------------------------------------
    return Close(TRUE);
}

/* ================================================================  */
/*                                                                   */
/*  A Helper Method to Create Complex Objects as Easily as Possible  */
/*                                                                   */
/*  At this time, only the G2Structure object is supported.          */
/*                                                                   */
/* ================================================================  */
STDMETHODIMP CG2Gateway::MakeG2ComVariable(G2Type G2ComType, SAFEARRAY **InArgs, VARIANT *OutArg)
{
    HRESULT             hr = S_OK ;
    IG2Structure        *pG2Struct ;
    int                 nameSrc, valSrc=0 ;
    long                lb, ub, lb1, ub1, lb2, ub2, lX ;
    long                nrEls, nrEls1, nrEls2 ;
    long                array1Type ;
    SAFEARRAY           *psa = *InArgs ;
    SAFEARRAY           *psa1, *psa2 ;
    SAFEARRAY           *pPkg ;
    UINT                nDims ;
    VARIANT             v0, v1, v2, *pv ;

#define VALIDATIONERR(ercode) { hr = ercode ; goto ValidationError ; }

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Gateway::MakeG2ComVariable\n");

    VariantInit(&v0);
    VariantInit(&v1);
    VariantInit(&v2);
    if (G2ComType == g2StructureType)
    {
        /* Gather information about the parameters */
        /* ---------------------------------------  */
        nDims = SafeArrayGetDim(psa);
        if (nDims != 1)
            return E_UNEXPECTED ;    // should never happen
        hr = SafeArrayGetLBound(psa, 1, &lb);
        if (FAILED(hr))
            return E_UNEXPECTED ;
        hr = SafeArrayGetUBound(psa, 1, &ub);
        if (FAILED(hr))
            return E_UNEXPECTED ;
        nrEls = ub-lb+1;
        if (nrEls <= 0)
            return E_INVALIDARG ;

        hr = SafeArrayGetElement(psa, &lb, &v0);
        if (FAILED(hr))
            return E_UNEXPECTED ;

        /* Dereference the first parameter, if necessary */
        /* --------------------------------------------- */
        VariantCopyInd(&v1, &v0);
        VariantClear(&v0);

        /* If the first parameter is an array, then we are going */
        /* to take the property names from the array.            */
        /* ----------------------------------------------------- */
        nameSrc = (v1.vt & VT_ARRAY) ? 1 : 0 ;
        if (nameSrc)
        {
            /* The array must be of type VARIANT or BSTR */
            /* ----------------------------------------- */
            array1Type = (v1.vt & VT_TYPEMASK);
            if ((array1Type != VT_VARIANT) && (array1Type != VT_BSTR))
                VALIDATIONERR(E_INVALIDARG) ;

            /* Save information about the name source array */
            /* -------------------------------------------- */
            psa1 = (v1.vt & VT_BYREF) ? *v1.pparray : v1.parray ;
            nDims = SafeArrayGetDim(psa1);
            if (nDims != 1)
                VALIDATIONERR(E_INVALIDARG) ;
            hr = SafeArrayGetLBound(psa1,1,&lb1);
            if (FAILED(hr))
                VALIDATIONERR(E_UNEXPECTED) ;
            hr = SafeArrayGetUBound(psa1,1,&ub1);
            if (FAILED(hr))
                VALIDATIONERR(E_UNEXPECTED);
            nrEls1 = ub1 - lb1 + 1 ;

            /* -------------------------------------------------------------- */
            /* If the only parameter (other than the object type) that has    */
            /* been passed to this method is the array that we are looking at,*/
            /* then the property values will also come from this array, i.e., */
            /* the array will contain property name, property value, property */
            /* name, ....  valSrc=1 means the source of the property values   */
            /* will be the first array, the one pointed to by psa1.           */
            /* -------------------------------------------------------------- */
            if (nrEls == 1)
                valSrc = 1 ;

            /* --------------------------------------------------------------- */
            /* If there are exactly 2 parameters and the second parameter is   */
            /* an array, then the property values will come from the 2nd array */
            /* --------------------------------------------------------------- */
            else if (nrEls == 2)
            {
                lX = lb + 1 ;
                hr = SafeArrayGetElement(psa, &lX, &v2);
                if (FAILED(hr))
                    VALIDATIONERR(E_UNEXPECTED);

                // Dereference the 2nd array if necessary
                // --------------------------------------
                if(v2.vt == (VT_VARIANT | VT_BYREF))
                {
                    VARIANT    *pTemp = v2.pvarVal ;
                    VariantCopy(&v2,pTemp);
                    VariantClear(pTemp) ;
                }

                // The values come either from the 2nd array (*psa2) or
                // the list of parameters (*psa).
                // -----------------------------------------------------
                valSrc = (v2.vt & VT_ARRAY) ? 2 : 0 ;

                // Save information about the value source array
                // ---------------------------------------------
                if (valSrc)
                {
                    psa2 = (v2.vt & VT_BYREF) ? *v2.pparray : v2.parray ;
                    nDims = SafeArrayGetDim(psa2);
                    if (nDims != 1)
                        valSrc=0 ;
                    else
                    {
                        hr = SafeArrayGetLBound(psa2,1,&lb2);
                        if (FAILED(hr))
                            return E_UNEXPECTED ;
                        hr = SafeArrayGetUBound(psa2,1,&ub2);
                        if (FAILED(hr))
                            return E_UNEXPECTED ;
                        nrEls2 = ub2 - lb2 + 1 ;
                    }
                }
            }
        }

        /* Since there are more than 2 parameters, the property values */
        /* must come from the parameter list.                          */
        /* ----------------------------------------------------------- */
        else
            valSrc = 0 ;

        /* There are 4 different ways to specify the property names  */
        /* and values when creating a G2 structure. If there is only */
        /* a single parameter after the type code, then it must be   */
        /* an array with elements that alternate between property    */
        /* name and value.                                           */
        /* --------------------------------------------------------- */
        if (ub == lb)
        {
            /* Validate the input */
            /* ------------------ */
            if ((v1.vt & VT_ARRAY) != VT_ARRAY)
                VALIDATIONERR(E_INVALIDARG) ;

            // There must be an even number of elements in the array
            if (nrEls1 % 2)
                VALIDATIONERR(E_INVALIDARG) ;

            // Make sure every other element is a valid property name
            if (array1Type == VT_VARIANT)
                if (!varStructNames(psa1, true))
                    VALIDATIONERR(E_INVALIDARG) ;
        }

        /* If the first specification parameter is not an array, then the   */
        /* names and values are specified on the as parameters to this      */
        /* method.  In this case, every other parameter should be a valid   */
        /* property name.                                                   */
        /* ---------------------------------------------------------------- */
        else if (!nameSrc)
        {
            // There must be an even number of elements in the array
            if (nrEls % 2)
                VALIDATIONERR(E_INVALIDARG) ;
            hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pv);
            if (FAILED(hr))
                VALIDATIONERR(E_INVALIDARG) ;
            for (lX=0 ; lX < nrEls ; lX += 2)
                if (!validStructName(pv+lX))
                {
                    SafeArrayUnaccessData(psa);
                    VALIDATIONERR(E_INVALIDARG) ;
                }
            SafeArrayUnaccessData(psa);
        }

        /* We have an array of property names and either an array of values */
        /* or the values listed as parameters to this method.               */
        /* ---------------------------------------------------------------- */
        else
        {
            // Validate the property name array */
            if ((array1Type == VT_VARIANT) && !varStructNames(psa1, false))
                VALIDATIONERR(E_INVALIDARG) ;

            if (valSrc && (nrEls1 != nrEls2))
                VALIDATIONERR(E_INVALIDARG) ;
            if (!valSrc && (nrEls1 != (nrEls-1)))
                VALIDATIONERR(E_INVALIDARG) ;
        }

ValidationError:
        if (FAILED(hr))
        {
            VariantClear(&v1) ;
            VariantClear(&v2) ;
            return hr ;
        }


        /*                We have finished validating the input.            */
        /*          The following code constructs the new G2Structure       */
        /* ---------------------------------------------------------------- */
        VARIANT         *pParams ;
        VARIANT         *pvNames ;
        BSTR            *pbNames ;
        VARIANT         *pvVals ;
        VARIANT         innerPkg ;
        CComBSTR        holdName ;
        long            nrStructEnts, lidx, saidx ;
        SAFEARRAYBOUND  bound[1] ;

        // Create an empty G2Structure
        // ---------------------------
        hr = ::CoCreateInstance(CLSID_G2Structure,NULL,CLSCTX_INPROC_SERVER,IID_IG2Structure,(void**)&pG2Struct);
        if (FAILED(hr))
            return E_FAIL ;

        // Initialize the pointers to the sources of the property names and values
        // -----------------------------------------------------------------------
        if (valSrc==0)
        {
            hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pParams);
            if (FAILED(hr))
                goto Error_FreeSomeMem ;
        }
        if (nameSrc)
        {
            SafeArrayAccessData(psa1, (array1Type==VT_BSTR) ? (void HUGEP* FAR*)&pbNames : (void HUGEP* FAR*)&pvNames);
            if (FAILED(hr))
                goto Error_FreeSomeMem ;
        }
        if (valSrc==2)
        {
            SafeArrayAccessData(psa2, (void HUGEP* FAR*)&pvVals);
            if (FAILED(hr))
                goto Error_FreeSomeMem ;
        }

        // Determine how many entries the structure will have
        // --------------------------------------------------
        if (!nameSrc)
            nrStructEnts = nrEls/2 ;
        else if (valSrc==1)
            nrStructEnts = nrEls1/2 ;
        else
            nrStructEnts = nrEls1 ;

        // Create the SafeArray needed to Add entries to G2Structure
        // ---------------------------------------------------------
        bound[0].lLbound = 0 ;
        bound[0].cElements = 2 ;
        pPkg = SafeArrayCreate(VT_VARIANT,1,bound);
        if (pPkg == NULL)
        {
            hr = E_UNEXPECTED ;
            goto Error_FreeSomeMem ;
        }

        // Get the name & property, store them in a SafeArray as Variants,
        // and them call G2Structure.Add to add them to the structure
        // ---------------------------------------------------------------
        for (lX = 0; lX < nrStructEnts ; lX++)
        {
            // --- Property Name ---
            lidx = ((valSrc==1)?2:1) * lX ;
            if (nameSrc)
                if (array1Type==VT_BSTR)
                    holdName = pbNames[lidx] ;
                else
                    holdName = (pvNames[lidx].vt & VT_BYREF) ?
                               *V_BSTRREF(pvNames+lidx) : V_BSTR(pvNames+lidx);
            else
            {
                lidx = 2 * lX ;
                switch (pParams[lidx].vt)
                {
                case (VT_VARIANT|VT_BYREF) : holdName = pParams[lidx].pvarVal->bstrVal ;
                    break ;
                case (VT_BSTR):                 holdName = pParams[lidx].bstrVal ;
                    break ;
                case (VT_BSTR | VT_BYREF):     holdName = *(pParams[lidx].pbstrVal);
                    break ;
                default:
                    hr = E_UNEXPECTED ;
                    goto Error_FreeMem ;
                }
            }
            innerPkg.vt = VT_BSTR ;
            innerPkg.bstrVal = holdName.Copy();
            saidx = 0 ;
            hr = SafeArrayPutElement(pPkg, &saidx, &innerPkg);
            if (FAILED(hr))
                goto Error_FreeMem ;


            // --- Property Value ---

            // Processing the values is more difficult than processing the names because:
            // 1. they can be coming from one of three locations
            // 2. if they are coming from a 2nd array, the array can be one of many types.
            // ---------------------------------------------------------------------------
            VariantClear(&innerPkg);
            if (!valSrc)
            {
                lidx = (nameSrc) ? lX+1 : 2*lX+1 ;

                VARIANT        *pVar = pParams+lidx ;
                BSTR        *pbs ;
                SAFEARRAY    *pt ;
                long vt = pVar->vt ;
                if (vt & VT_ARRAY)
                {
                    pt = (vt & VT_BYREF) ? *(pVar->pparray) : pVar->parray ;
                    SafeArrayAccessData(pt,(void**)&pbs);
                    SafeArrayUnaccessData(pt);
                }

                VariantCopyInd(&innerPkg, pParams+lidx);
                vt = innerPkg.vt ;
                if (vt & VT_ARRAY)
                {
                    pt = (vt & VT_BYREF) ? *(innerPkg.pparray) : innerPkg.parray ;
                    SafeArrayAccessData(pt,(void**)&pbs);
                    SafeArrayUnaccessData(pt);
                }

            }

            // Coming from an array specified immediately after the G2Type.
            // Either a BSTR or a VARIANT.
            // ------------------------------------------------------------
            else if (valSrc==1)
            {
                lidx++ ; // one beyond the name's entry
                if (array1Type==VT_BSTR)
                {
                    innerPkg.vt = VT_BSTR ;
                    innerPkg.bstrVal = pbNames[lidx] ;
                }
                else
                    VariantCopyInd(&innerPkg, pvNames+lidx);
            }

            // Coming from a second array.  Pack the value in a VARIANT
            // --------------------------------------------------------
            else
            {
                hr = GsiContext::ArrayElement2Var(v2.vt, lX, pvVals, &innerPkg);
                if (FAILED(hr))
                    goto Error_FreeMem ;
            }

            /* Add the entry to the SafeArray */
            /* ------------------------------ */
            saidx = 1 ;
            hr = SafeArrayPutElement(pPkg, &saidx, &innerPkg);
            VariantClear(&innerPkg);
            if (FAILED(hr))
                goto Error_FreeMem ;
            hr = pG2Struct->Add(&pPkg);
            if (FAILED(hr))
                goto Error_FreeMem ;
        }

        hr = SafeArrayDestroy(pPkg);

        // Unlock the source arrays
        // ------------------------
        if (!valSrc)
            SafeArrayUnaccessData(psa);
        if (nameSrc)
            SafeArrayUnaccessData(psa1);
        if (valSrc==2)
            SafeArrayUnaccessData(psa2);

        VariantClear(&v1) ;
        VariantClear(&v2) ;

        // Return the new G2Structure to the caller
        // ----------------------------------------
        VariantClear(OutArg);
        OutArg->vt = VT_DISPATCH ;
        hr = pG2Struct->QueryInterface(IID_IDispatch, (void**)&(OutArg->pdispVal) ) ;
        pG2Struct->Release() ;

        return S_OK ;
    }
    else
    {
        SetComError (OLESTR("Currently the only supported G2 type is \"G2StructureType\""));
        return E_INVALIDARG ;
    }
    return S_OK ;

    // Release allocated structures before returning error code
    // --------------------------------------------------------
Error_FreeMem:
    SafeArrayDestroy(pPkg);
Error_FreeSomeMem:
    VariantClear(&v1) ;
    VariantClear(&v2) ;
    pG2Struct->Release();
    return hr ;
}

STDMETHODIMP CG2Gateway::get_TWHandle(long *pTWHandle)
{
    *pTWHandle = m_TWHandle ;
    return S_OK ;
}

STDMETHODIMP CG2Gateway::put_TWHandle(long TWHandle)
{
    if (m_TWHandle && TWHandle)
        return  E_FAIL ;
    else
        m_TWHandle = TWHandle ;
    return S_OK ;
}


/* ======================================================================== */
/* Check whether the elements of *psa that represent structure names are    */
/* strings.  If alternate is true, this will be every odd numbered element. */
/* Otherwise it applies to every element.                                   */
/* ======================================================================== */
bool CG2Gateway::varStructNames(SAFEARRAY *psa, bool alternate)
{
    bool    retval = true ; // assume success
    HRESULT    hr ;
    long    lb, ub, lx, nrEls ;
    VARIANT    vX ;
    VARIANT HUGEP *pv ;


    hr = SafeArrayGetLBound(psa, 1, &lb);
    if (FAILED(hr))
        goto UnexpectedError ;
    hr = SafeArrayGetUBound(psa, 1, &ub);
    if (FAILED(hr))
        goto UnexpectedError ;
    nrEls = ub - lb + 1;
    VariantInit(&vX);
    hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pv);
    if (FAILED(hr))
        goto UnexpectedError ;

    for (lx = 0; lx < nrEls ; lx += (alternate ? 2 : 1))
        if ((pv[lx].vt & VT_BSTR) != VT_BSTR)
        {
            retval = false ;
            break ;
        }
    SafeArrayUnaccessData(psa);
    return retval ;

UnexpectedError:
    SetComError(OLESTR("Unexpected access error"));
    return false ;
}

bool CG2Gateway::validStructName(VARIANT *pv)
{
    return ((pv->vt & VT_BSTR) == VT_BSTR);
}

STDMETHODIMP CG2Gateway::fixUpArray(VARIANT *varBk, VARIANT *varIn)
{
    UINT            uiDims, uiX ;
    HRESULT            hr ;
    long            lX, lnrEls=1 ;
    SAFEARRAY        *psaIn, *psaOut ;
    SAFEARRAYBOUND    *bounds ;

    psaIn = (varIn->vt & VT_BYREF) ? *(varIn->pparray) : varIn->parray ;
    uiDims = SafeArrayGetDim(psaIn);
    if (!uiDims)
        return E_UNEXPECTED ;
    else
        bounds = new SAFEARRAYBOUND[uiDims] ;
    if (!bounds)
        return E_OUTOFMEMORY ;
    for (uiX=0 ; uiX < uiDims ; uiX++)
    {
        SafeArrayGetLBound(psaIn, uiX+1, &((bounds+uiX)->lLbound));
        SafeArrayGetUBound(psaIn, uiX+1, &lX);
        bounds[uiX].cElements = lX - bounds[uiX].lLbound + 1 ;
        lnrEls *= bounds[uiX].cElements ;
    }
    psaOut = SafeArrayCreate((varIn->vt) & VT_TYPEMASK, uiDims, bounds);
    if (!psaOut)
        return E_OUTOFMEMORY ;
    hr = SafeArrayLock(psaIn);
    if (FAILED(hr))
        return E_UNEXPECTED ;
    hr = SafeArrayLock(psaOut);
    if (FAILED(hr))
    {
        SafeArrayUnlock(psaIn);
        return E_UNEXPECTED ;
    }
    memcpy(psaOut->pvData, psaIn->pvData, psaIn->cbElements * lnrEls);
    SafeArrayUnlock(psaIn);
    SafeArrayUnlock(psaOut);

    varBk->vt = varIn->vt & ~VT_BYREF ;
    varBk->parray = psaOut ;
    return S_OK ;
}


//
// This routine fires events from the proper thread
//
STDMETHODIMP CG2Gateway::_FireEvents(void)
{	
    //
    // Once we enter this routine, we get a lock and fire all queued events.
    //
    CallData    *cd, *ncd;
    CComBSTR    attrName("") ;
    BSTR        modAttrName = NULL, EventName = NULL ;
    HRESULT     hr ;
    IUnknown    *pIUnk ;
    IDispatch   *pIDsp ;
    IG2Item4    *pI4 ;
    IG2Item3    *pI3 ;
    IG2Window   *pWin = NULL ;
    long        lhdl ;
    VARIANT     varModStruct, varNewVal, varUserData, varSubscriptionHdl ;
    VARIANT     vt, dnseq ;
    VARIANT     ret,userData, hdl ;

    ATLTRACE2(atrAxlMsgs,1,"Processing event in CG2Gateway\n");
    if (!mpContext)
        return E_FAIL;

    this->AddRef(); // GENSYMCID-893
    VariantInit(&vt) ;
    VariantInit(&ret);
    for (cd = (CallData *) mpContext->Events.GetFirst();cd;cd = ncd)
    {
        ncd = (CallData *) cd->GetNext();

        switch (cd->EventCode)
        {
        case GSI_EVENT_PAUSE:
            ATLTRACE2(atrAxlMsgs,1,"Firing pause event\n");
            mpContext->mIsRunning = FALSE;
            mpContext->m_g2RunState = g2Paused ;
            SendOnDataChange();
            FireOnChanged(9);
            Fire_G2Paused();
            break;
        case GSI_EVENT_RESUME:
            ATLTRACE2(atrAxlMsgs,1,"Firing resume event\n");
            mpContext->mIsRunning = TRUE;
            mpContext->m_g2RunState = g2Running ;
            SendOnDataChange();
            FireOnChanged(9);
            Fire_G2Resumed();
            break;
        case GSI_EVENT_RESET:
            ATLTRACE2(atrAxlMsgs,1,"Firing reset event\n");
            mpContext->mIsRunning = FALSE;
            mpContext->m_g2RunState = g2Reset ;
            SendOnDataChange();
            FireOnChanged(9);
            Fire_G2Reset();
            break;
        case GSI_EVENT_START:
            ATLTRACE2(atrAxlMsgs,1,"Firing start event\n");
            mpContext->mIsRunning = TRUE;
            mpContext->m_g2RunState = g2Running ;
            SendOnDataChange();
            FireOnChanged(9);
            Fire_G2Started();
            break;
        case GSI_EVENT_CONNECT:
            ATLTRACE2(atrAxlMsgs,1,"Found connect event\n");
            mpContext->mIsConnected = TRUE;
            SendOnDataChange();
            FireOnChanged(8);
            Fire_G2Connected();
            break;
        case GSI_EVENT_DISCONNECT:
            ATLTRACE2(atrAxlMsgs,1,"Found disconnect event\n");
            mpContext->mIsConnected = FALSE;
            mpContext->m_g2RunState = g2UnknownState ;

            // Remove local subscription info for every item
            // attached to this G2Gateway
            // ---------------------------------------------
            G2ItemPtr *pIp ;

            pIp = (G2ItemPtr*)mpContext->Items.Head ;
            while (pIp)
            {
                pIp->mp_G2Item->InternalUnsubscribeAll(false) ;
                pIp = (G2ItemPtr*)pIp->Next ;
            }
            
            SendOnDataChange();
            FireOnChanged(8);
            Fire_G2Disconnected();
            break;
        case GSI_EVENT_RPCSTART:
            ATLTRACE2(atrAxlMsgs,1,"Firing start event\n");
            Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;
            Fire_RpcStarted(cd->Name.m_str, &vt);
            VariantClear(&vt);
            break;
        case GSI_EVENT_RPCCALL:
            {
                ATLTRACE2(atrAxlMsgs,1,"Firing rpc call event\n");
                Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;
                Fire_RpcCalled(cd->Name.m_str, &vt, &ret);
                VariantClear(&vt);

                // What we do depends on how many elements there are
                // We may have a null with zero elements, a safe array
                // of many values or a simple value
                // ---------------------------------------------------
                RetValsReq  *pRVReq ;
                Datum       *pRetVals ;
                long        nrRetVals ;

                // many values:
                // ------------
                if (ret.vt == (VT_ARRAY | VT_VARIANT) || 
                    ret.vt == (VT_ARRAY | VT_BYREF | VT_VARIANT) )
                { 
                    SAFEARRAY *pSA = 
                        (ret.vt == (VT_ARRAY | VT_VARIANT) ? ret.parray : *ret.pparray) ;
                    Converter::SafeArrayToDatumArray(pSA, &pRetVals, &nrRetVals) ;
                }

                // a single value:
                // ---------------
                else
                {
                    pRetVals = new Datum[1] ;
                    pRetVals[0] = ret ;
                    nrRetVals = 1 ;
                }
                VariantClear(&ret);

                // Create the "Return Values" request & queue it up
                // for execution in the GSI thread.
                // ------------------------------------------------
                pRVReq = new RetValsReq(mpContext,pRetVals,nrRetVals,(void*)cd->CallId);
                mpContext->Requests.Add(pRVReq) ;
                Queue.Add2(pRVReq) ;
                GsiThreadObj->wakePauseUp() ;
            }
            break;
        case GSI_EVENT_ERROR:
            ATLTRACE2(atrAxlMsgs,1,"Firing error event\n");
            // Perhaps in next version Error event will pass an error object
            // with more specific info on the 'context' of the exception.
            // I.e. the RPC call ID or RPC name.
            Fire_Error(cd->ErrorMessage.m_str, cd->ErrorCode, &cd->DeferredCallId);
            break;
        case GSI_EVENT_RETURN: 
            ATLTRACE2(atrAxlMsgs,1,"Firing return event\n");
            
            Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;
            Fire_RpcReturned(cd->Name.m_str, &vt, &cd->DeferredCallId);
            VariantClear(&vt);
            break;
        case GSI_EVENT_MESSAGE:
            ATLTRACE2(atrAxlMsgs,1,"Firing Got message event\n");
            Fire_GotMessage(cd->Name.m_str);
            break;
        case G2_PAUSED:
            ATLTRACE2(atrAxlMsgs,1,"Recording run state as PAUSED\n");
            mpContext->m_g2RunState = g2Paused ;
            break ;
        case G2_RESET:
            ATLTRACE2(atrAxlMsgs,1,"Recording run state as RESET\n");
            mpContext->m_g2RunState = g2Reset ;
            break ;
        case G2_RUNNING:
            ATLTRACE2(atrAxlMsgs,1,"Recording run state as RUN\n");
            mpContext->m_g2RunState = g2Running ;
            break ;
        case G2_RUN_STATE_KNOWN:
            ATLTRACE2(atrAxlMsgs,1,"Found run state known event\n");
            Fire_G2RunStateKnown();
            break ;
        case G2_ITEM_DELETED: {

            ATLTRACE2(atrAxlMsgs,1,"Notification of deletion of G2 item\n");

            pIUnk = (IUnknown *)cd->mp_item ;
            pI4 = NULL ;
            pI3 = NULL ;
            if (pIUnk)
                hr = pIUnk->QueryInterface(IID_IDispatch, (void**)&pIDsp) ;
            if (SUCCEEDED(hr)) 
                hr = pIDsp->QueryInterface(IID_IG2Item4, (void**)&pI4) ;
            
//            pIUnk->Release() ;
//            pIDsp->Release() ;

            lhdl = 0 ;
            VariantInit(&hdl) ;
            VariantInit(&userData) ;

            Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;
            if (vt.vt == (VT_VARIANT | VT_ARRAY))
            {
                long idx ;

                SAFEARRAY *psa = vt.parray ;
                idx = 5 ;
                ::SafeArrayGetElement(psa, &idx, &userData) ;
                idx = 6 ;
                ::SafeArrayGetElement(psa, &idx, &hdl ) ;
                if (hdl.vt == VT_I4)
                    lhdl = hdl.lVal ;
            }

            // Analyze pI4 for Debug purposes
            // ------------------------------
/*            Datum*  pWrappedDat;
            pI4->Git2((long*)&pWrappedDat) ;

            pWrappedDat = new Datum ;
            hr  = ::CoCreateInstance(CLSID_G2Item, NULL, CLSCTX_INPROC_SERVER, IID_IG2Item4, (void**)&pI4) ;
            pI4->Init2((long)pWrappedDat) ; */


            Fire_ItemDeleted((LPDISPATCH)pI4, lhdl, userData);
            VariantClear(&vt) ;
            VariantClear(&userData) ;
            break ; }
        case G2_ITEM_MODIFIED:

            ATLTRACE2(atrAxlMsgs,1,"Notification of modification of G2 item\n");

            pIUnk = (IUnknown *)cd->mp_item ;
            if (pIUnk)
                hr = pIUnk->QueryInterface(IID_IDispatch, (void**)&pIDsp) ;
            if (SUCCEEDED(hr)) 
                hr = pIDsp->QueryInterface(IID_IG2Item4, (void**)&pI4) ;
            lhdl = 0 ;
            VariantInit(&varModStruct) ;
            VariantInit(&varNewVal) ;
            VariantInit(&varUserData) ;
            VariantInit(&varSubscriptionHdl) ;

            // Extract the attribute name
            // --------------------------
            Datum    *pmIts ;

            pmIts = cd->mArgs ;
            if (cd->mCount >= 3)
            {
                long lDSTyp = (long)pmIts[2].Type() ;
                long lCtDS  = pmIts[2].Count() ;

                if (lDSTyp == GSI_SEQUENCE_TAG  && lCtDS >= 1)
                {
                    Datum   *pStr = pmIts[2].Sequence() ;
                    long    strtyp = pStr[0].Type() ;
                    USES_CONVERSION ;

                    if (strtyp == GSI_STRUCTURE_TAG)
                    {
                        Attribute    *pNameAttr ;

                        pNameAttr = pStr[0].FindAttributeNamed(_T("NAME")) ;
                        if (pNameAttr)
                        {
                            Datum*      pNameItem = pNameAttr->ItemPtr() ;
                            DataType    lastType = pNameItem->Type() ;
                            if (lastType == dtySymbol)
                            {
                                TCHAR*  ptchName = pNameItem->Symbol() ;
                                attrName = T2OLE(ptchName) ;
                                delete [] ptchName ;
                            }
                        }
                    }
                }
            }

            // Convert the rest of the input to COM variables
            // ----------------------------------------------
            Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;
            
            if (vt.vt == (VT_VARIANT | VT_ARRAY))
            {
                long idx ;

                SAFEARRAY *psa = vt.parray ;
 
                idx = 4 ;
                ::SafeArrayGetElement(psa, &idx, &varNewVal) ;
                idx = 5 ;
                ::SafeArrayGetElement(psa, &idx, &varUserData) ;
                idx = 6 ;
                ::SafeArrayGetElement(psa, &idx, &varSubscriptionHdl ) ;
                if (varSubscriptionHdl.vt == VT_I4)
                    lhdl = varSubscriptionHdl.lVal ;
            }
            Fire_ItemModified((LPDISPATCH)pI4, lhdl, attrName, varNewVal, varUserData);
            break ;
        case G2_ICON_COLOR_CHG:

            ATLTRACE2(atrAxlMsgs,1,"Notification of icon color change\n");

            pIUnk = (IUnknown *)cd->mp_item ;
            if (pIUnk)
                hr = pIUnk->QueryInterface(IID_IDispatch, (void**)&pIDsp) ;
            if (SUCCEEDED(hr)) 
                hr = pIDsp->QueryInterface(IID_IG2Item4, (void**)&pI4) ;
            lhdl = 0 ;
            VariantInit(&ret);
            VariantInit(&hdl) ;
            VariantInit(&userData) ;

            Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;
            if (vt.vt == (VT_VARIANT | VT_ARRAY))
            {
                long idx ;

                SAFEARRAY *psa = vt.parray ;
                idx = 4 ;
                ::SafeArrayGetElement(psa, &idx, &varNewVal) ;
                idx = 5 ;
                ::SafeArrayGetElement(psa, &idx, &userData) ;
                idx = 6 ;
                ::SafeArrayGetElement(psa, &idx, &hdl ) ;
                if (hdl.vt == VT_I4)
                    lhdl = hdl.lVal ;
            }
            Fire_IconColorChg((LPDISPATCH)pI4, lhdl, varNewVal, userData);
            break ;
        case G2_CUSTOM_EVENT:
            {
                ATLTRACE2(atrAxlMsgs,1,"Notification of custom event\n");

                pIUnk = (IUnknown *)cd->mp_item ;
                if (pIUnk)
                    hr = pIUnk->QueryInterface(IID_IDispatch, (void**)&pIDsp) ;
                if (SUCCEEDED(hr)) 
                    hr = pIDsp->QueryInterface(IID_IG2Item4, (void**)&pI4) ;
                lhdl = 0 ;
                VariantInit(&dnseq) ;
                VariantInit(&varNewVal) ;
                VariantInit(&hdl) ;
                VariantInit(&userData) ;


                // Extract the event name
                // ----------------------
                Datum*  pIts = cd->mArgs ;

                if (cd->mCount >= 3)
                {
                    DataType    iDSTyp = pIts[2].Type() ;
                    long        iCtDS = pIts[2].Count() ;

                    if (iDSTyp == GSI_SEQUENCE_TAG  && iCtDS >= 1)
                    {
                        Datum*      pStr = pIts[2].Sequence() ;
                        DataType    strtyp = pStr[0].Type() ;

                        if (strtyp == dtyStructure)
                        {
                            Attribute*  pNameAttr ;

                            pNameAttr = pStr[0].FindAttributeNamed(_T("CUSTOM-EVENT-NAME")) ;
                            if (pNameAttr)
                            {
                                USES_CONVERSION ;
                                Datum*      pNameItem = pNameAttr->ItemPtr() ;
                                DataType    lastType = pNameItem->Type() ;
                                if (lastType == dtySymbol)
                                {
                                    TCHAR*  ptchName = pNameItem->Symbol() ;
                                    EventName = ::SysAllocString(T2OLE(ptchName)) ;
                                    delete [] ptchName ;
                                }
                            }
                        }
                    }
                }
            
                // Convert the array of gsi_items to a SafeArray of Variants
                // ---------------------------------------------------------
                Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;

                if (vt.vt == (VT_VARIANT | VT_ARRAY))
                {
                    long idx ;

                    SAFEARRAY *psa = vt.parray ;

                    idx = 4 ;
                    ::SafeArrayGetElement(psa, &idx, &varNewVal) ;
                    idx = 5 ;
                    ::SafeArrayGetElement(psa, &idx, &userData) ;
                    idx = 6 ;
                    ::SafeArrayGetElement(psa, &idx, &hdl ) ;
                    if (hdl.vt == VT_I4)
                        lhdl = hdl.lVal ;
                }
                Fire_CustomEvent((LPDISPATCH)pI4, EventName, varNewVal, lhdl, userData);
                break ;
            }
        case G2_WKSPCADD_EVENT:
        case G2_WKSPCDEL_EVENT:

            ATLTRACE2(atrAxlMsgs,1,"Notification of addition or deletion of item to/from workspace\n");

            pIUnk = (IUnknown *)cd->mp_item ;
            if (pIUnk)
                hr = pIUnk->QueryInterface(IID_IDispatch, (void**)&pIDsp) ;
            if (FAILED(hr)) pIDsp = NULL ;


            lhdl = 0 ;
            VariantInit(&hdl) ;
            VariantInit(&userData) ;

            Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;
            if (vt.vt == (VT_VARIANT | VT_ARRAY))
            {
                long idx ;

                SAFEARRAY *psa = vt.parray ;
                idx = 5 ;
                ::SafeArrayGetElement(psa, &idx, &userData) ;
                idx = 6 ;
                ::SafeArrayGetElement(psa, &idx, &hdl ) ;
                if (hdl.vt == VT_I4)
                    lhdl = hdl.lVal ;
            }
            Fire_ItemAddedOrDeletedWorkspace(pIDsp, lhdl, userData, cd->EventCode);
            break ;
        case G2_VALUE_CHG:
            ATLTRACE2(atrAxlMsgs,1,"Notification of value change\n");

            pIUnk = (IUnknown *)cd->mp_item ;
            if (pIUnk)
                hr = pIUnk->QueryInterface(IID_IDispatch, (void**)&pIDsp) ;
            if (SUCCEEDED(hr)) 
                hr = pIDsp->QueryInterface(IID_IG2Item4, (void**)&pI4) ;
            lhdl = 0 ;
            VariantInit(&varNewVal) ;
            VariantInit(&hdl) ;
            VariantInit(&userData) ;

            Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;
            if (vt.vt == (VT_VARIANT | VT_ARRAY))
            {
                long idx ;

                SAFEARRAY *psa = vt.parray ;
                idx = 4 ;
                ::SafeArrayGetElement(psa, &idx, &varNewVal) ;
                idx = 5 ;
                ::SafeArrayGetElement(psa, &idx, &userData) ;
                idx = 6 ;
                ::SafeArrayGetElement(psa, &idx, &hdl ) ;
                if (hdl.vt == VT_I4)
                    lhdl = hdl.lVal ;
            }
            Fire_ValueChg((LPDISPATCH)pI4, varNewVal, lhdl, userData);
            VariantClear(&varNewVal);
            VariantClear(&hdl);
            VariantClear(&userData);
            break ;
        case G2_SELECTION:
           ATLTRACE2(atrAxlMsgs,1,"Notification of item selection\n");

            pIUnk = (IUnknown *)cd->mp_item ;
            if (pIUnk)
                hr = pIUnk->QueryInterface(IID_IDispatch, (void**)&pIDsp) ;
            if (SUCCEEDED(hr)) 
                hr = pIDsp->QueryInterface(IID_IG2Window, (void**)&pWin) ;
            lhdl = 0 ;
            VariantInit(&hdl) ;
            VariantInit(&userData) ;

            Converter::DatumsToArrayVarOrVar(cd->mArgs,cd->mCount,&vt) ;

            if (vt.vt == (VT_VARIANT | VT_ARRAY))
            {
                long idx ;

                SAFEARRAY *psa = vt.parray ;
                idx = 1 ;
                ::SafeArrayGetElement(psa, &idx, &hdl ) ;
                if (hdl.vt == VT_I4)
                    lhdl = hdl.lVal ;
                idx = 2;
                ::SafeArrayGetElement(psa, &idx, &userData) ;
            }
            Fire_ItemSelected((LPDISPATCH)pWin, lhdl, userData);
            break ;
        }
        VariantClear(&vt);
        mpContext->Events.Remove(cd);  // event complete, remove it from the queue
                                       // This deletes cd & the attached Datum
    } // loop to next event
    this->Release(); // GENSYMCID-893
    ATLTRACE2(atrAxlMsgs,2,"G2Gateway finished processing event\n");
    return S_OK;
}

//
// This routine is used to throw an exception message back to the client
//

void SetComError(LPCOLESTR error_mesg, const IID *pint, OLECHAR *pObjName)

{
    ICreateErrorInfo *eObj;
    CreateErrorInfo(&eObj);  // Get error object

    USES_CONVERSION;
    eObj->SetDescription(SysAllocString(error_mesg));
    eObj->SetGUID(*pint);
    eObj->SetSource(SysAllocString(pObjName));

    IErrorInfo *eiObj;
    HRESULT hr = eObj->QueryInterface(IID_IErrorInfo, (void **) &eiObj);
    if (SUCCEEDED(hr))
    {
        SetErrorInfo(0, eiObj);
        eiObj->Release();
    }
    eObj->Release();
}


STDMETHODIMP CG2Gateway::get_G2RunState(G2RunStateType *pVal)
{
    *pVal = mpContext->G2RunState();

    return S_OK;
}

STDMETHODIMP CG2Gateway::DbgMsg(BSTR msg)
{
    ATLTRACE("%S\n", msg);
    return S_OK ;
}

STDMETHODIMP CG2Gateway::ObtainTWLockIfUnused(VARIANT_BOOL *pResult)
{
    if (!m_TWLockIsInUse)
    {
        m_TWLockIsInUse = true;
        *pResult = VARIANT_TRUE;  // Success
    }
    else
        *pResult = VARIANT_FALSE ; // Failure -- lock is already in use

    return S_OK;
}

STDMETHODIMP CG2Gateway::ClearTWLock()
{
    m_TWLockIsInUse = false ;

    return S_OK;
}

STDMETHODIMP CG2Gateway::get_G2Symbols(VARIANT_BOOL *pVal)
{
    if (NULL == pVal)
        return E_POINTER ;

    *pVal = mpContext->getG2Syms() ;
    
    return S_OK;
}


STDMETHODIMP CG2Gateway::put_G2Symbols(VARIANT_BOOL newVal)
{
    mpContext->setG2Syms(newVal) ;  // store in GsiContext for use
    return S_OK;
}


STDMETHODIMP CG2Gateway::get_DisconnectOnReset(VARIANT_BOOL *pVal)
{
    if (NULL == pVal)
        return E_POINTER ;

    *pVal = mpContext->getDiscOnReset() ;
    return S_OK;
}

STDMETHODIMP CG2Gateway::put_DisconnectOnReset(VARIANT_BOOL newVal)
{
    mpContext->setDiscOnReset(newVal) ;

    return S_OK;
}

STDMETHODIMP CG2Gateway::GetDisplayString(DISPID dispid, BSTR *pBstr)
{
    ATLTRACE2(atlTraceControls,2,_T("CG2Gateway::GetDisplayString\n"));
    if (dispid==24)     // G2Symbols?
    {
        if (VARIANT_FALSE == mpContext->getG2Syms())
            *pBstr = ::SysAllocString(L"False") ;
        else
            *pBstr = ::SysAllocString(L"True") ;
        return S_OK ;
    }
    else if (dispid==25)     // DisconnectOnReset?
    {
        if (VARIANT_FALSE == mpContext->getDiscOnReset())
            *pBstr = ::SysAllocString(L"False") ;
        else
            *pBstr = ::SysAllocString(L"True") ;
        return S_OK ;
    }
    return S_FALSE ;
}

STDMETHODIMP CG2Gateway::SetContextLimit(long limit)
{
    if (mpContext)
    {
        if (GsiThreadObj)
            EnterCriticalSection(&GsiThreadObj->m_NoVanishingReqs);
        mpContext->setContextLimit(limit);
        if (GsiThreadObj)
            LeaveCriticalSection(&GsiThreadObj->m_NoVanishingReqs);
    }

    return S_OK;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*     This is where we receive the callback to changes to which we have      */
/*     subscribed.  It packages the information that will be required by      */
/*     the user's event handler in a CallData object and then calls           */
/*     FireEventInThread to tell the Windows thread to process it.            */
/*                                                                            */
/* -------------------------------------------------------------------------- */
void axl_notification_callback(void* /*procedure_user_data_type*/ procedure_user_data, 
                               void* /*gsi_item*/ *pItemsIn, gsi_int /*gsi_int*/ count, 
                               /*call_identifier_type*/ void *call_index)
{
    ATLTRACE("Event: %s, Subscription-handle: %d\n", 
            gsi_symbol_name(gsi_sym_of(pItemsIn[0])), gsi_int_of(pItemsIn[5]));
    GsiContext *context = GsiContext::FindContext();
    if (!context)
    {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
        return;
    }

    gsi_char        *pEvent = gsi_symbol_name(gsi_sym_of(pItemsIn[0])) ;
    gsi_int         subh2= gsi_int_of(pItemsIn[5]) ;
    
    Subscription    *pInCtx  = (Subscription*)(context->FindSubscription(subh2, false)) ;
    Subscription    *pInItem = NULL ;

    if (pInCtx)
        if (pInCtx->m_subscrType == stDelete)
        {
#if _MSC_VER == 1200  //VC++ 6.0
            if (!_tcscmp(_T("DELETE"),pEvent))
#elif _MSC_VER >= 1300 
			if (!_tcscmp(_T("DELETE"),(const wchar_t *)pEvent))
#endif
            {
                // Convert the array of gsi_items to an array of Datums
                // -----------------------------------------------------
                Datum *pDatumsIn = (count > 0) ? new Datum [count] : NULL ;
                if (!pDatumsIn)
                    count = 0 ;
                for (long lX = 0 ; lX < count; lX++)
                    pDatumsIn[lX] = pItemsIn[lX] ;

                // Prepare the CallData structure will we need to fire the event
                // -------------------------------------------------------------
                CallData *cd = new CallData;
                cd->EventCode = G2_ITEM_DELETED;
                cd->mp_item = (IUnknown*)((IG2Item*)pInCtx->mp_Item) ;
                cd->mArgs = pDatumsIn ;
                cd->mCount = count ;

                // Remove all local subscription records
                // -------------------------------------
                CG2Item *pHoldOn = pInCtx->mp_Item ;
                pHoldOn->InternalUnsubscribeAll(false) ;

                // Remove the reference to this item from the GsiContext
                // Unlink this item
                // -----------------------------------------------------
                GsiContext *pCtx = GsiContext::FindContext();
                if (!pCtx)
                    ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
                else
                    pCtx->Items.Remove(pHoldOn->mp_pG2Item) ;

                // Fire Event
                // ----------
                context->FireEventInThread(cd);
            }       
        }

        /* Modify Attribute /Icon Color Change/ Custom Event/ Value */
        /* -------------------------------------------------------- */
        else if (pInCtx->m_subscrType > 0 && pInCtx->m_subscrType <= stWkspcDel) 
        {
            CallData *cd = new CallData;
            switch (pInCtx->m_subscrType)
            {
                case stModify:
                    cd->EventCode = G2_ITEM_MODIFIED ;
                    break ;
                case stColorChg:
                    cd->EventCode = G2_ICON_COLOR_CHG ;
                    break ;
                case stCustom:
                    cd->EventCode = G2_CUSTOM_EVENT ;
                    break ;
                case stWkspcAdd:
                    cd->EventCode = G2_WKSPCADD_EVENT ;
                    break ;
                case stWkspcDel:
                    cd->EventCode = G2_WKSPCDEL_EVENT ;
                    break ;
                case stValueChg:
                    cd->EventCode = G2_VALUE_CHG ;
                    break ;
                default:
                    cd->EventCode = GSI_EVENT_ERROR ;
            }

            // Convert the array of gsi_items to an array of Datums
            // -----------------------------------------------------
            Datum *pDatumsIn = (count > 0) ? new Datum [count] : NULL ;
            if (!pDatumsIn)
                count = 0 ;
            for (long lX = 0 ; lX < count; lX++)
                pDatumsIn[lX] = pItemsIn[lX] ;

            cd->mp_item = (IUnknown*)((IG2Item*)pInCtx->mp_Item) ;
            cd->mArgs = pDatumsIn ;
            cd->mCount = count ;

            context->FireEventInThread(cd);
        }
}
