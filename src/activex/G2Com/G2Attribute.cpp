// G2Attribute.cpp : Implementation of CG2Attribute
#include "stdafx.h"
#include "G2Com.h"
#include "G2Attribute.h"
#include "Gateway.h"
#include "GsiContext.h"





/////////////////////////////////////////////////////////////////////////////
// CG2Attribute
/* =========== */
/* -------------------------------------------------------------------------- */
/* The only purpose of the G2Attribute object is to allow us to iterate over  */
/* the item's attributes using VB's "For Each x in itemX" construct.  As a    */
/* the Value property is read-only and we only allow the Type property to be  */
/* set when switching between String and Symbol types.                        */
/* -------------------------------------------------------------------------- */

/////////////////////////////////////////////////////////////////////////////
// IG2Attribute

/* Constructor */
/* =========== */
CG2Attribute::CG2Attribute() : m_pAttr(NULL)
{
    ATLTRACE2 (atrG2ObjLife, 4, "##> New G2Attribute at %08x.\n", this);
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                   Return the Name of this Attribute                       */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Attribute::get_Name(BSTR *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3,"CG2Attribute::get_Name");
    USES_CONVERSION ;

    if (m_pAttr)
    {
        TCHAR   *tchName = m_pAttr->AttrName() ;
        *pVal = ::SysAllocString(T2OLE(tchName)) ;
        delete [] tchName ;
        return S_OK ;
    }
    else
        return E_UNEXPECTED ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                   Return the Value of this Attribute                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Attribute::get_Value(VARIANT *pVal)
{
    HRESULT     hr ;

    ATLTRACE2(atrAxlMethodCalls, 3,"CG2Attribute::get_Value");
    if (m_pAttr)
    {
        if (m_pAttr->ItemPtr()->IsItem())
        {
            Datum   *pCopy = new Datum ;
            *pCopy = *(m_pAttr->ItemPtr()) ;
            hr = pCopy->toVariant(pVal) ;
        }
        else
            m_pAttr->ItemPtr()->toVariant(pVal) ;
        return hr;
    }
    else
        return E_UNEXPECTED ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                     Set the Value of this Attribute                       */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Attribute::put_Value(VARIANT newVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3,"CG2Attribute::put_Value\n");
    if (m_pAttr)
    {
        Datum*  pItemOfAttr = m_pAttr->ItemPtr() ;

        pItemOfAttr->Zap() ;
        *pItemOfAttr = newVal ;
        return S_OK ;
    }
    else
        return E_UNEXPECTED ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                  Return the G2Type Code for this Attribute                */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Attribute::get_Type(G2Type *pType)
{
    ATLTRACE2(atrAxlMethodCalls, 3,"CG2Attribute::get_Type");
    if (m_pAttr)
    {
        *pType = (G2Type)m_pAttr->ItemPtr()->Type() ;
        return S_OK ;
    }
    else
        return E_UNEXPECTED ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*          Method to change type between g2String and g2SymbolType          */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Attribute::put_Type(G2Type nType)
{
    ATLTRACE2(atrAxlMethodCalls, 3,"CG2Attribute::put_Type");
    if (m_pAttr)
    {
        Datum   *pItem = m_pAttr->ItemPtr() ;
        G2Type  orgType = (G2Type)pItem->Type() ;

        if ((nType == g2String || nType == g2SymbolType) && 
                (orgType == g2String || orgType == g2SymbolType))
        {
            if (nType == g2String && orgType == g2SymbolType)
            {
                pItem->Stringify() ;
            }
            else if (nType == g2SymbolType && orgType == g2String)
            {
                pItem->Symbolize() ;
            }
        }
        else
            return E_INVALIDARG ;

        return S_OK ;
    }
    else
        return E_POINTER ;
}


/* --------------------------------------------------------------------------- */
/*                                                                             */
/*         A G2Attribute is a wrapper for a pointer to an Attribute.           */
/*             This is where we store the pointer in the object.               */
/*                                                                             */
/* --------------------------------------------------------------------------- */
STDMETHODIMP CG2Attribute::Init(long pAttr)
{
    ATLTRACE2(atrAxlMethodCalls, 3,"CG2Attribute::Init");

    m_pAttr = (Attribute*)(pAttr) ;
    return S_OK ;
}


/////////////////////////////////////////////////////////////////////////////
// IG2ComObject
/* ========================================================================== */
/*                                                                            */
/*  get_WhatAmI: return string identifying this object as a G2Attribute       */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Attribute::get_WhatAmI(BSTR *WhatAmI)
{
    *WhatAmI = ::SysAllocString(L"G2Attribute");
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/*               Create a duplicate instance of this object.                  */
/*                                                                            */
/*             This creates a COPY of the pointed-to attribute.               */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Attribute::Duplicate(IUnknown **pNewObj)
{
    Attribute*          p2ndAttr ;
    HRESULT             hr = S_OK ;
    IUnknown            *pUK ;
    IG2Attribute        *pIAttr ;

    // Create the duplicate CG2Attribute object
    // ----------------------------------------
    hr = CoCreateInstance(CLSID_G2Attribute,NULL,CLSCTX_INPROC_SERVER,IID_IUnknown,
                          reinterpret_cast<void**>(&pUK));
    if (FAILED(hr))
        return hr ;
    hr = pUK->QueryInterface(IID_IG2Attribute, reinterpret_cast<void**>(&pIAttr));
    if (FAILED(hr))
    {
        pUK->Release();
        return hr ;
    }

    // Make a copy of the contained Attribute
    // --------------------------------------
    p2ndAttr = new Attribute ;
    *p2ndAttr = m_pAttr ;

    // Store the copy of the Attribute in the duplicate CG2Attribute object
    // --------------------------------------------------------------------
    hr = pIAttr->Init((long)p2ndAttr) ;
    pIAttr->Release() ;
    if (FAILED(hr))
    {
        delete p2ndAttr ;
        pUK->Release();
        return hr ;
    }

    // Pass the pointer to the duplicate object back to the caller
    // -----------------------------------------------------------
    *pNewObj = pUK ;    // AddRef was performed by CoCreateIntance   
    return S_OK ;
}


/* ============================================================================ */
/*                                                                              */
/*           Standard interface for returning error messages to client          */
/*                                                                              */
/* ============================================================================ */
#if _MSC_VER == 1200  //VC++ 6.0
STDMETHODIMP CG2Attribute::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2Attribute
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		
		if (::ATL::InlineIsEqualGUID(*arr[i],riid))
		return S_OK;
		
	}
	return S_FALSE;
}

#elif  _MSC_VER >= 1300  // VC++ 7 or more

STDMETHODIMP CG2Attribute::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2Attribute
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
		
	}
	return S_FALSE;
}
#endif