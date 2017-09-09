// G2StructureEntry.cpp : Implementation of CG2StructureEntry
#include "stdafx.h"
#include "Converter.h"
#include "G2Com.h"
#include "G2StructureEntry.h"
#include "GsiContext.h"

/* ============ */
/* Constructors */
/* ============ */
CG2StructureEntry::CG2StructureEntry() : m_bstrName(NULL)
{
    ATLTRACE2 (atrG2ObjLife, 4, "##> New G2StructureEntry at %08x.\n", this);
    VariantInit(&m_varValue);
}

CG2StructureEntry::CG2StructureEntry(BSTR bstName, VARIANT varX)
{
    if (bstName == NULL)
        m_bstrName = NULL ;
    else
    {
        m_bstrName = ::SysAllocString(bstName) ;
        _wcsupr(m_bstrName) ; // assumes OLECHAR is WCHAR (no Win98)
    }
    VariantCopy(&m_varValue, &varX) ; 
}

CG2StructureEntry::CG2StructureEntry(CG2StructureEntry& g2seFrom)
{
    m_bstrName = ::SysAllocString(g2seFrom.m_bstrName) ;
    VariantCopy(&m_varValue, &(g2seFrom.m_varValue));
}

/* =========================== */
/* Call Just Before Destructor */
/* =========================== */
void CG2StructureEntry::FinalRelease()
{
    ::SysFreeString(m_bstrName) ;
    VariantClear(&m_varValue);
    ATLTRACE2 (atrG2ObjLife, 4, "##< G2StructureEntry at %08x destroyed.\n", this);
}

/////////////////////////////////////////////////////////////////////////////
// IG2StructureEntry

/* ================================= */
/* Return this entry's property name */
/* ================================= */
STDMETHODIMP CG2StructureEntry::get_Name(BSTR *pVal)
{
    *pVal = ::SysAllocString(m_bstrName) ;
    return S_OK ;
}

/* ================================ */
/*  Set this entry's property name  */
/* ================================ */
STDMETHODIMP CG2StructureEntry::put_Name(BSTR newVal)
{
    if (m_bstrName)
        ::SysFreeString(m_bstrName) ;
    if (newVal)
    {
        m_bstrName = ::SysAllocString(newVal) ;
        _wcsupr(m_bstrName) ;
    }
    else
        m_bstrName = NULL ;
    return S_OK ;
}

/* ===============================*/
/*  Return this property's value  */
/* ===============================*/
STDMETHODIMP CG2StructureEntry::get_Value(VARIANT *pVal)
{
    return VariantCopy(pVal, &m_varValue);
}

/* ============================*/
/*  Set this property's value  */
/* ============================*/
STDMETHODIMP CG2StructureEntry::put_Value(VARIANT newVal)
{
    HRESULT hr = Converter::BetterVariantCopyInd(&m_varValue,&newVal);
    return    hr ;
}

/////////////////////////////////////////////////////////////////////////////
// IG2ComObject
/* ========================================================================== */
/*                                                                            */
/*  get_WhatAmI: return string identifying this object as a G2StructureEntry  */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2StructureEntry::get_WhatAmI(BSTR *WhatAmI)
{
    *WhatAmI = ::SysAllocString(L"G2StructureEntry");
    return S_OK ;
}

/* ========================================================================== */
/*                                                                            */
/*             Create a duplicate instance of this object.                    */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2StructureEntry::Duplicate(IUnknown **pNewObj)
{
    HRESULT             hr = S_OK ;
    IUnknown            *pUK ;
    IG2StructureEntry   *pSE ;

    hr = CoCreateInstance(CLSID_G2StructureEntry,NULL,CLSCTX_INPROC_SERVER,IID_IUnknown,
                          reinterpret_cast<void**>(&pUK));
    if (FAILED(hr))
        return hr ;
    hr = pUK->QueryInterface(IID_IG2StructureEntry, reinterpret_cast<void**>(&pSE));
    if (FAILED(hr))
        goto release_pUK ;
    hr = pSE->put_Name(m_bstrName);
    if (FAILED(hr))
        goto release_pSE ;
    hr = pSE->put_Value(m_varValue);
    if (FAILED(hr))
        goto release_pSE ;  // and pUK
    pSE->Release();
    *pNewObj = pUK ;    // AddRef was performed by CoCreateIntance
    return S_OK;

    // Release all interfaces before error exit
release_pSE:
    pSE->Release();
release_pUK:
    pUK->Release();
    return hr ;
}

/* ============================================================================ */
/*                                                                              */
/*           Standard interface for returning error messages to client          */
/*                                                                              */
/* ============================================================================ */
#if _MSC_VER == 1200  //VC++ 6.0
STDMETHODIMP CG2StructureEntry::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] =
	{
		&IID_IG2StructureEntry
	};
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (::ATL::InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}


#elif _MSC_VER >= 1300  //VC++ 7 or more
STDMETHODIMP CG2StructureEntry::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] =
	{
		&IID_IG2StructureEntry
	};
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

#endif
