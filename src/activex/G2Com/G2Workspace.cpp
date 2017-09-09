// G2Workspace.cpp : Implementation of CG2Workspace
#include "stdafx.h"
#include "BRPCReq.h"
#include "G2Com.h"
#include "G2Item.h"
#include "G2Workspace.h"
#include "Subscription.h"
#include "Gateway.h"

/////////////////////////////////////////////////////////////////////////////
// CG2Workspace

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      Request that the associated G2Gateway receive an event when an        */
/*  item is added to the g2-workspace that corresponds to this G2Workspace    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Workspace::SubscribeToItemAddition(VARIANT userData, VARIANT *subHdl)
{
    VARIANT     varX ;


    ATLTRACE2(atrAxlMethodCalls, 3, "G2Workspace::SubscribeToItemAddition\n");

    // Get the pointer to the IG2Item4.
    // --------------------------------
    HRESULT         hr ;
    IG2Item4        *pG2It4 = NULL ;
    EXEC(m_pG2Item->QueryInterface(IID_IG2Item4, (void**)&pG2It4), hr) ;

     // We can't Subscribe if we are not linked
    // ----------------------------------------
    VARIANT_BOOL    linked ;
    EXEC(pG2It4->get_Linked(&linked), hr) ;
    if (VARIANT_FALSE == linked)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Workspace");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    USES_CONVERSION ;
    VariantInit(&varX) ;
  
    // Get the pointer to the context
    // ------------------------------
    IG2ItemRef      *pRef = NULL ;
    GsiContext      *pCtx ;
    unsigned short  uuid[8] ;

    EXEC(pG2It4->get_Reference(&pRef), hr) ;
    pRef->Git( uuid, (long*)&pCtx) ;
    pRef->Release() ;
    if (NULL == pCtx)
        return E_POINTER ;

    if (((CG2Item*)pG2It4)->AutoConnect((long)pCtx))
        return E_FAIL;


    // Create BRPCRequest to send UUID to G2
    // -------------------------------------
    VARIANT vX ;
    VariantInit(&vX) ;

    Datum   *pParams = new Datum [5] ;
    Datum   *pUD = new Datum ;
    pParams[0].USV(uuid, 8) ;
    pUD->Long((long)pCtx) ;
    pParams[0].UserData(pUD) ;
    pParams[1].Symbol(_T("__G2COM-NOTIFY")) ;
    pParams[2].String(_T("WKSPC-ITEM_ADDED")) ;
    pParams[3].Long(0) ;
    pParams[4] = userData ;


    // "Call" _G2Item_Subscribe
    // ------------------------
    long    lNrRetVars ;
    VARIANT *pRetVars ;

    BRPCReq *req = new BRPCReq(pCtx, _T("_G2Item_Subscribe"), pParams, 5);

    hr = ((CG2Item*)pG2It4)->InternalCall(req, &pRetVars, &lNrRetVars) ;
    if (FAILED(hr))
        return hr ;
    if (lNrRetVars != 1)
    {
        delete [] pRetVars ;
        return E_UNEXPECTED ;
    }

    // If G2 returned an error message instead of a subscription handle
    // return the error message as part of a COM error.
    // ----------------------------------------------------------------
    if (pRetVars->vt == VT_BSTR)
    {
        SetComError(pRetVars->bstrVal,&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x0204);
    }

    // We need to create two Subscription items for each handle, one for the GsiContext
    // and one to store in this item's m_subscriptions container.  We cannot use the 
    // same Subscription item for each container because the Remove method deletes the
    // item and we will need to Remove from both container.
    // ---------------------------------------------------------------------------------
    varX = *pRetVars ;

    Subscription    *psub1, *psub2 ;

    psub1 = new Subscription(varX.lVal, stWkspcAdd, NULL, (CG2Item*)((IG2Item4*)m_pG2Item)) ;
    psub2 = new Subscription(varX.lVal, stWkspcAdd, NULL, (CG2Item*)((IG2Item4*)m_pG2Item)) ;
    ((CG2Item*)pG2It4)->m_subscriptions.Add(psub1) ;
    ((GsiContext*)pCtx)->Subscriptions.Add(psub2) ;

    if (pRetVars->vt != VT_I4)
    {
        SetComError(OLESTR("Unexpected response from G2"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x205);
    }

    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Request that the associated G2Gateway receive an event when an item      */
/*  is deleted from the g2-workspace that corresponds to this G2Workspace     */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Workspace::SubscribeToItemRemoval(VARIANT userData, VARIANT *subHdl)
{
    VARIANT     varX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Workspace::NotifyWhenItemDeleted\n");

    // Get the pointer to the IG2Item4.
    // --------------------------------
    HRESULT         hr ;
    IG2Item4        *pG2It4 = NULL ;
    EXEC(m_pG2Item->QueryInterface(IID_IG2Item4, (void**)&pG2It4), hr) ;

     // We can't Subscribe if we are not linked
    // ----------------------------------------
    VARIANT_BOOL    linked ;
    EXEC(pG2It4->get_Linked(&linked), hr) ;
    if (VARIANT_FALSE == linked)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Workspace");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    USES_CONVERSION ;
    VariantInit(&varX) ;
  
    // Get the pointer to the context
    // ------------------------------
    IG2ItemRef      *pRef = NULL ;
    GsiContext      *pCtx ;
    unsigned short  uuid[8] ;

    EXEC(pG2It4->get_Reference(&pRef), hr) ;
    pRef->Git( uuid, (long*)&pCtx) ;
    pRef->Release() ;
    if (NULL == pCtx)
        return E_POINTER ;

    if (((CG2Item*)pG2It4)->AutoConnect((long)pCtx))
        return E_FAIL;


    // Create BRPCRequest to send UUID to G2
    // -------------------------------------
    VARIANT vX ;
    VariantInit(&vX) ;

    gsi_item    *pGits = gsi_make_items(5) ;
    Datum       *pParams = new Datum[5] ;
    gsi_set_usv(pGits[0], (unsigned short*)(uuid), 8) ;
    gsi_set_user_data(pGits[0], (gsi_item_user_data_type)(pCtx)) ;
    gsi_set_sym(pGits[1], gsi_make_symbol((gsi_char *)_T("__G2COM-NOTIFY"))) ;
//  GsiContext::Var2GsiItem(&userData, pGits[4]) ;
    gsi_set_str(pGits[2], (gsi_char *)_T("WKSPC-ITEM_DEL")) ;
    gsi_set_int(pGits[3], 0) ;


    // "Call" _G2Item_Subscribe
    // ------------------------
    BRPCReq *req = new BRPCReq(pCtx, _T("_G2Item_Subscribe"), pParams, 5);
    if (!req)
        return E_FAIL;
    req->usedBy(RequestObj::ContainerThread) ;
    pCtx->Requests.Add(req);
    int ret = req->invoke();
    if (ret)
    {
        req->stateToError() ;
        req->stopUseBy(RequestObj::ContainerThread) ;
        return E_FAIL;
    }

    // Request the deletion of the BRPCReq
    // -----------------------------------
    req->stateToProcessed() ;
    req->stopUseBy(RequestObj::ContainerThread) ;   

    // If G2 returned an error message instead of a subscription handle
    // return the error message as part of a COM error.
    // ----------------------------------------------------------------
    if (subHdl->vt == VT_BSTR)
    {

        SetComError(subHdl->bstrVal,&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x0204);
    }

    // We need to create two Subscription items for each handle, one for the GsiContext
    // and one to store in this item's m_subscriptions container.  We cannot use the 
    // same Subscription item for each container because the Remove method deletes the
    // item and we will need to Remove from both container.
    // ---------------------------------------------------------------------------------
    varX = *subHdl ;

    Subscription    *psub1, *psub2 ;

    psub1 = new Subscription(varX.lVal, stWkspcDel, NULL, (CG2Item*)((IG2Item4*)m_pG2Item)) ;
    psub2 = new Subscription(varX.lVal, stWkspcDel, NULL, (CG2Item*)((IG2Item4*)m_pG2Item)) ;
    ((CG2Item*)pG2It4)->m_subscriptions.Add(psub1) ;
    ((GsiContext*)pCtx)->Subscriptions.Add(psub2) ;

    if (subHdl->vt != VT_I4)
    {
        SetComError(OLESTR("Unexpected response from G2"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x205);
    }

    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Cancel requests for notification when an item is added to this workspace  */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Workspace::UnsubscribeFromItemAddition()
{
    HRESULT     hr ;
    IG2Item4    *pI4 = NULL ;
    VARIANT     varX ;

  
    if (m_pG2Item)
    {
        hr = m_pG2Item->QueryInterface(IID_IG2Item4, (void**)&pI4) ;
        if (SUCCEEDED(hr))
        {
            VariantInit(&varX) ;
            return ((CG2Item*)pI4)->InternalUnsubscribe(varX, 1, stWkspcAdd) ;
        }
    }

	return E_UNEXPECTED;
}



/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                       Cancel requests for notification                     */
/*                when an item is removed from this workspace                 */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Workspace::UnsubscribeFromItemRemoval()
{
    HRESULT     hr ;
    IG2Item4    *pI4 = NULL ;
    VARIANT     varX ;

  
    if (m_pG2Item)
    {
        hr = m_pG2Item->QueryInterface(IID_IG2Item4, (void**)&pI4) ;
        if (SUCCEEDED(hr))
        {
            VariantInit(&varX) ;
            return ((CG2Item*)pI4)->InternalUnsubscribe(varX, 1, stWkspcDel) ;
        }
    }

	return E_UNEXPECTED;
}


/* ---------------------------------------------------------------------------- */
/*                                                                              */
/*  Standard method for declaring capacity to return error info to COM clients  */
/*                                                                              */
/* ---------------------------------------------------------------------------- */

#if _MSC_VER == 1200  //VC++ 6.0
STDMETHODIMP CG2Workspace::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2Workspace
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        if (::ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


#elif _MSC_VER >= 1300  //VC++ 7 or more
STDMETHODIMP CG2Workspace::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2Workspace
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
#endif

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  get_WhatAmI: return string identifying this object as a G2Workspace       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Workspace::get_WhatAmI(BSTR *WhatAmI)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::WhatAmI\n");

    if (NULL == WhatAmI)
        return E_POINTER ;
    *WhatAmI = ::SysAllocString(OLESTR("G2Workspace"));
    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Create a duplicate instance of this object.                    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Workspace::Duplicate(IUnknown **pNewObj)
{
//     HRESULT     hr ;
    IUnknown    *pIUnk = NULL ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Workspace::Duplicate\n");
/*    if (!m_linked)
    {
        IG2Item     *pNewItem = NULL ;

        EXEC(::CoCreateInstance(CLSID_G2Item,NULL,CLSCTX_INPROC_SERVER, IID_IG2Item, (void**)&pNewItem),hr) ;
        return pNewItem->Init((long)m_GsiItem) ;
    }
    else
    {
        IG2Item3    *pNewItem2 = NULL ;
        IG2ItemRef  *pRef = NULL ;

        EXEC(::CoCreateInstance(CLSID_G2Item,NULL,CLSCTX_INPROC_SERVER, IID_IG2Item3, (void**)&pNewItem2),hr) ;
        EXEC(get_Reference(&pRef),hr) ;
        hr = pNewItem2->Init((long)m_GsiItem, pRef ) ;
        pRef->Release() ;
        return hr ;
    } */
    return S_OK ;
}


