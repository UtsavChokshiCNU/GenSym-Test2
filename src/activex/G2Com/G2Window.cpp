// G2Window.cpp : Implementation of CG2Window
#include "stdafx.h"
#include "G2Com.h"
#include "G2Window.h"
#include "G2Item.h"

/////////////////////////////////////////////////////////////////////////////
// CG2Window


/////////////////////////////////////////////////////////////////////////////
// IG2ComObject Methods:

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  get_WhatAmI: return string identifying this object as a G2Workspace       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Window::get_WhatAmI(BSTR *WhatAmI)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Window::WhatAmI\n");

    if (NULL == WhatAmI)
        return E_POINTER ;
    *WhatAmI = ::SysAllocString(OLESTR("G2Window"));
    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Create a duplicate instance of this object.                    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Window::Duplicate(IUnknown **pNewObj)
{
//     HRESULT     hr ;
    IUnknown    *pIUnk = NULL ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Window::Duplicate\n");
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

/////////////////////////////////////////////////////////////////////////////



#if _MSC_VER == 1200  //VC++ 6.0
STDMETHODIMP CG2Window::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2Window
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        if (::ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


#elif _MSC_VER >= 1300  //VC++ 7 or more
STDMETHODIMP CG2Window::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2Window
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
/*      Request that the associated G2Gateway receive an event when the       */
/*                           specified change occurs.                         */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Window::SubscribeToSelection(VARIANT userData, VARIANT *subscriptionHandle)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Window::SubscribeToSelection\n");

    // Get the pointer to the IG2Item4.
    // --------------------------------
    HRESULT         hr ;
    IG2Item4        *pG2It4 = NULL ;
    hr = m_pG2Item->QueryInterface(IID_IG2Item4, (void**)&pG2It4) ;
    if (FAILED(hr))
        return hr ;
    hr =((CG2Item*)pG2It4)->CommonSubscribe(stSelection, userData, subscriptionHandle) ;
    pG2It4->Release() ;
    return hr ;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*     Cancel all requests for item selection notification in this window     */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Window::UnsubscribeFromSelection()
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Window::UnsubscribeFromSelection\n");

    // Get the pointer to the IG2Item4.
    // --------------------------------
    HRESULT         hr ;
    IG2Item4        *pG2It4 = NULL ;
    VARIANT         vX ;

    hr = m_pG2Item->QueryInterface(IID_IG2Item4, (void**)&pG2It4) ;
    if (FAILED(hr))
        return hr ;
    VariantInit(&vX) ;
    return ((CG2Item*)pG2It4)->InternalUnsubscribe(vX, 1, stSelection) ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*             Retrieve the user mode attached to this G2Window              */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Window::get_g2UserMode(BSTR *pVal)
{
    if (pVal == NULL)
        return E_POINTER ;

    *pVal = ::SysAllocString(m_userMode.m_str) ;
    return S_OK ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                           Set the user mode                               */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Window::put_g2UserMode(BSTR newVal)
{
    CComBSTR    cbstrIn(newVal) ;
    HRESULT     hr ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Window::put_g2UserMode\n");
    hr = cbstrIn.ToUpper() ;
    if FAILED(hr) return hr ;
    m_userMode = cbstrIn ;
    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                   Callback routine for item selection                      */
/*                                                                            */
/* -------------------------------------------------------------------------- */
void axl_selection_callback(void * /*procedure_user_data_type*/ ud, 
                            void * /*gsi_item*/ *rpc_arguments, 
                            gsi_int/*gsi_int*/ count, 
                            void * /*call_identifier_type*/ call_identifier)
{
    gsi_int hndl = (count > 0) ? gsi_int_of(rpc_arguments[0]) : -1 ;

    ATLTRACE("Item selected, Subscription-handle: %ld\n", hndl);
    GsiContext *context = GsiContext::FindContext();
    if (!context)
    {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
        return;
    }

    Subscription    *pInCtx  = (Subscription*)(context->FindSubscription(hndl,true)) ;
    Subscription    *pInItem = NULL ;

    CallData *cd = new CallData;
    cd->EventCode = G2_SELECTION ;
    cd->mp_item = (IUnknown*)((IG2Item*)pInCtx->mp_Item) ;
    cd->mCount = count ;
    cd->mArgs = count ? new Datum [count] : NULL ;
    if (!cd->mArgs) cd->mCount = 0 ; // if out of memory
    for (long lX = 0 ; lX < cd->mCount ; lX++)
        cd->mArgs[lX] = rpc_arguments[lX] ;
    context->FireEventInThread(cd);
}


