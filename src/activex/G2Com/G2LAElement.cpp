// G2LAElement.cpp : Implementation of CG2LAElement
#include "stdafx.h"
#include "G2Com.h"
#include "G2LAElement.h"
#include "Gateway.h"

/////////////////////////////////////////////////////////////////////////////
// CG2LAElement


STDMETHODIMP CG2LAElement::Init(IG2ListOrArray *pLaw, long idx)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2LAElement::Init");
	m_pLaw = pLaw ;
    m_idx = idx ;

	return S_OK;
}

STDMETHODIMP CG2LAElement::get_Item(VARIANT *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2LAElement::get_Item\n");
    return m_pLaw->get_Item(m_idx, pVal) ;
}

STDMETHODIMP CG2LAElement::get_Value(VARIANT *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2LAElement::get_Value\n");
    return m_pLaw->get_Item(m_idx, pVal) ;
}

STDMETHODIMP CG2LAElement::put_Value(VARIANT newVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2LAElement::put_Value\n");
    return m_pLaw->put_Item(m_idx, newVal) ;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  get_WhatAmI: return string identifying this object as a G2Item            */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2LAElement::get_WhatAmI(BSTR *WhatAmI)
{
    ATLASSERT(WhatAmI != NULL);
    *WhatAmI = ::SysAllocString(L"G2LAElement");
    return S_OK ;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                Create a duplicate instance of this object.                 */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2LAElement::Duplicate(IUnknown **pNewObj)
{
    HRESULT         hr ;
    IG2LAElement    *pLAEl = NULL ;

    hr = ::CoCreateInstance(CLSID_G2LAElement, NULL,CLSCTX_INPROC_SERVER, IID_IG2LAElement, (void**)&pLAEl) ;
    if (FAILED(hr)) return hr ;
    
    hr = pLAEl->Init(m_pLaw, m_idx) ;
	if (SUCCEEDED(hr)) return S_OK ;
	pLAEl->Release() ;
	return hr ;

}
