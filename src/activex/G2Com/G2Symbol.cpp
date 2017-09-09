// G2Symbol.cpp : Implementation of CG2Symbol
#include "stdafx.h"
#include "G2Com.h"
#include "G2Symbol.h"
#include "Gateway.h"

/////////////////////////////////////////////////////////////////////////////
// CG2Symbol



/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Return a copy of the BSTR wrapped by this object to the caller.  Force    */
/*  it to uppercase if m_uc is set.
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Symbol::get_Item(BSTR *pVal)
{
    CComBSTR    cbstrUC ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Symbol::get_Item");

    if (NULL == pVal)
        return E_POINTER ;
    if (m_uc == VARIANT_FALSE)
        *pVal = m_cbstr.Copy() ;
    else
    {
        cbstrUC = m_cbstr.m_str ;
        cbstrUC.ToUpper() ;
        *pVal = cbstrUC.Copy() ;
    }

	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                      Store away newVal in this G2Symbol                    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Symbol::put_Item(BSTR newVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Symbol::put_Item");

    m_cbstr = newVal ;
	return S_OK;
}



/* -------------------------------------------------------------------------- */
/*                                                                            */
/*           Return the state of the "return in upper case" flag              */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Symbol::get_UpperCase(VARIANT_BOOL *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Symbol::get_upperCase");

    if (NULL == pVal)
        return E_POINTER ;
    *pVal = m_uc ;
	return S_OK;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*            Set or clear the "return in uppercase" flag                     */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Symbol::put_UpperCase(VARIANT_BOOL newVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Symbol::put_UpperCase");
    m_uc = newVal ;

	return S_OK;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  get_WhatAmI: return string identifying this object as a G2Structure       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Symbol::get_WhatAmI(BSTR *WhatAmI)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Symbol::get_WhatAmI");

    if (NULL == WhatAmI)
        return E_POINTER ;
    *WhatAmI = ::SysAllocString(L"G2Symbol");
    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Create a duplicate instance of this object.                    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Symbol::Duplicate(IUnknown **pNewObj)
{
    VARIANT_BOOL    uc ;
    HRESULT         hr ;
    IG2Symbol *     pIG2Sym = NULL ;
    IUnknown*       pIUk = NULL ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Symbol::Duplicate");
    EXEC(::CoCreateInstance(CLSID_G2Symbol, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)(&pIUk)),hr) ;
    EXEC(pIUk->QueryInterface(IID_IG2Symbol, (void**)&pIG2Sym), hr) ;
    get_UpperCase(&uc) ;
    pIG2Sym->put_UpperCase(uc) ;
    pIG2Sym->put_Item(m_cbstr.m_str) ;
    *pNewObj = pIUk ;

    return S_OK ;
}