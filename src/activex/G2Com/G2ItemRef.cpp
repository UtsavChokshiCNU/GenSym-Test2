// G2ItemRef.cpp : Implementation of CG2ItemRef
#include "stdafx.h"
#include "G2Com.h"
#include "G2ItemRef.h"
#include "gsi_main_cpp.h"
#include "Gateway.h"
#include <wchar.h>

/////////////////////////////////////////////////////////////////////////////
// IG2ItemRef

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*     Fill in this G2ItemRef from a pointer to a 128-bit UUID (8 unsigned    */
/*            shorts) and a pointer to a GsiContext cast as a long.           */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ItemRef::Init(unsigned short *pUUIDin, long pCtx)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2ItemRet::Init\n");
    memcpy(uuid,pUUIDin,16) ;

    mp_ctx = pCtx ;
    if (NULL != pCtx)
    {
        m_Host = ((GsiContext*)pCtx)->Host() ;
        m_Port = ((GsiContext*)pCtx)->Port() ;
    }

	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Retrieve the (non-textual) UUID and the context pointer (cast as a long)  */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ItemRef::Git(unsigned short *pUUID, long *pCtx)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2ItemRet::Git\n");
    if (!pUUID || !pCtx)
        return E_POINTER ;
    memcpy(pUUID, (unsigned short *)uuid, 16) ;
    *pCtx = mp_ctx ;
	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                        Retrieve the UUID as text                           */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ItemRef::get_UUID(BSTR *pVal)
{
    wchar_t mid[33] ;
    int     i ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2ItemRet::get_UUID\n");
    USES_CONVERSION ;
    for (i = 0 ; i < 8 ; i++)
        swprintf(mid+4*i, L"%04x", uuid[i]) ;

    *pVal = ::SysAllocString(W2OLE(mid)) ;

	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*       Set the internal representation of the UUID from a text string       */
/*     The string must be exactly 32 characters long with every character     */
/*                 representing a valid hexadecimal digit.                    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ItemRef::put_UUID(BSTR newVal)
{
   ATLTRACE2(atrAxlMethodCalls, 3, "G2ItemRet::put_UUID\n");

   long            uil = ::SysStringLen(newVal) ;

    if (uil != 32)
        return E_INVALIDARG ;

    CComBSTR        tou = newVal ;
    int             ii = 0 , oi = 0 ;
    char            cs[32] ;

    WCHAR           c1, c2, c3, c4 ;

    tou.ToUpper() ;
    while (ii < 32)
    {
        c1 = *(tou.m_str + ii++) ;
        if (c1 >= '0'  && c1 <= '9')
            c1 -= '0' ;
        else if (c1 >= 'A'  && c1 <= 'F')
            c1 -= ('A' - 10) ;
        else
            return E_INVALIDARG ;

        c2 = *(tou.m_str + ii++) ;
        if (c2 >= '0'  && c2 <= '9')
            c2 -= '0' ;
        else if (c2 >= 'A'  && c2 <= 'F')
            c2 -= ('A' - 10) ;
        else
            return E_INVALIDARG ;

        c3 = *(tou.m_str + ii++) ;
        if (c3 >= '0'  && c3 <= '9')
            c3 -= '0' ;
        else if (c3 >= 'A'  && c3 <= 'F')
            c3 -= ('A' - 10) ;
        else
            return E_INVALIDARG ;

        c4 = *(tou.m_str + ii++) ;
        if (c4 >= '0'  && c4 <= '9')
            c4 -= '0' ;
        else if (c4 >= 'A'  && c4 <= 'F')
            c4 -= ('A' - 10) ;
        else
            return E_INVALIDARG ;

        cs[oi++] = (unsigned char)((c3 << 4) + c4) ;
        cs[oi++] = (unsigned char)((c1 << 4) + c2) ;
  }

    memcpy(uuid, cs, 16) ;

	return S_OK;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Set the context pointer from the Gateway object                */
/*                                                                            */
/*  Note that Gateway is a write-only property.  Since we store a pointer to  */
/*  a context object, not a G2Gateway, in the reference, we do not currently  */
/*  have any way to go from the G2ItemRef to the associated G2Gateway.        */
/*                                                                            */
/*  NOTE ALSO THAT THE TYPE OF pGateway SHOULD BE UPDATED ANY TIME THE        */
/*  DEFAULT INTERFACE OF G2Gateway IS CHANGED.                                */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ItemRef::put_Gateway(IG2Gateway4 *pGateway)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2ItemRet::put_UUID\n");

    if (NULL == pGateway)
        return E_POINTER ;

    // Due to the way Visual Basic wraps objects we need to query the pointer
    // for its default interface to get the true address of the object.
    // ----------------------------------------------------------------------
    IG2Gateway4 *pIGW4 = NULL ;
    CG2Gateway  *pGW   = NULL ;
    HRESULT hr = pGateway->QueryInterface(IID_IG2Gateway4, (void**)&pIGW4) ;
    pGW = (CG2Gateway*)pIGW4 ;
    mp_ctx = (long)(pGW->mpContext) ;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IG2ComObject

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   get_WhatAmI: return string identifying this object as a G2Item           */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ItemRef::get_WhatAmI(BSTR *WhatAmI)
{
    if (NULL == WhatAmI)
        return E_POINTER ;
    *WhatAmI = ::SysAllocString(OLESTR("G2ItemRef"));
    return S_OK ;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Create a duplicate instance of this object.                    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2ItemRef::Duplicate(IUnknown **pNewObj)
{
    HRESULT         hr ;
    IG2ItemRef      *pNewItemRef = NULL ;
    IUnknown        *pIUnk = NULL ;
    long            pCtx ;
    unsigned short  uuid[8] ;

    hr = ::CoCreateInstance(CLSID_G2ItemRef,NULL,CLSCTX_INPROC_SERVER, IID_IG2ItemRef, (void**)&pNewItemRef) ;
    if (FAILED(hr)) return hr ;

    hr = Git((unsigned short *)uuid, &pCtx) ;
	if (FAILED(hr))
	{
		pNewItemRef->Release() ;
		return hr ;
	}
    hr = pNewItemRef->Init((unsigned short *)uuid, pCtx) ;
	if (FAILED(hr))
	{
		pNewItemRef->Release() ;
		return hr ;
	}
	hr = pNewItemRef->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(*pNewObj)) ;
	pNewItemRef->Release() ;
	return hr ;
}

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo
/* ---------------------------------------------------------------------------- */
/*                                                                              */
/*  Standard method for declaring capacity to return error info to COM clients  */
/*                                                                              */
/* ---------------------------------------------------------------------------- */
#if _MSC_VER == 1200  //VC++ 6.0
STDMETHODIMP CG2ItemRef::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2ItemRef
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        if (::ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

#elif  _MSC_VER >= 1300  // VC++ 7 or more
STDMETHODIMP CG2ItemRef::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2ItemRef
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

#endif

/* ---------------------------------------------------------------------------- */
/*                                                                              */
/*  Function to make sure that any transmitted references are going out on the  */
/*                     same context they came in on.                            */
/*                                                                              */
/* ---------------------------------------------------------------------------- */
#define is_array_type(type)             ((type & 0x30) == 0x10)
#define is_list_type(type)		        ((type & 0x30) == 0x20)

HRESULT CG2ItemRef::RefCtxChk(Datum *pItems, gsi_int count, long ctx)
{
    long        giX, gity ;
    HRESULT     hr = S_OK ;


    return S_OK ;
    for (giX=0 ; giX < count ; giX++)
    {
        gity = pItems[giX].Type() ;

        if (gity != GSI_NULL_TAG && !is_simple_value_type(gity) && 
            gity != GSI_VALUE_TAG && gity != GSI_QUANTITY_TAG)
        {
            if (gity == GSI_UNSIGNED_SHORT_VECTOR_TAG || gity==GSI_HANDLE_TAG)
            {
                Datum    *pWrappedCtx = pItems[giX].UserDataPtr() ;
                if (pWrappedCtx->Type() != GSI_INTEGER_TAG)
                    return E_FAIL ;
                long ctxIn = pWrappedCtx->Long() ;
                if (ctxIn != ctx)
                    return E_FAIL ;
            }
            else if (is_array_type(gity) || is_list_type(gity) || gity == GSI_SEQUENCE_TAG)
            {
                if (gity == GSI_ITEM_ARRAY_TAG || gity == GSI_ITEM_OR_VALUE_ARRAY_TAG || gity == GSI_SEQUENCE_TAG ||
                     gity == GSI_ITEM_LIST_TAG  || gity == GSI_ITEM_OR_VALUE_LIST_TAG  )
                {
                    long elementCt = pItems[giX].Length() ;
                    if (elementCt > 0)
                    {
                        Datum    *pElements = pItems[giX].LAElements() ;
                        hr = RefCtxChk(pElements, elementCt, ctx) ;
                        if (FAILED(hr))
                            return hr ;
                    }
                }
            }
        }

        // Check the attributes of items
        // -----------------------------
        if (pItems[giX].IsItem() || gity == GSI_STRUCTURE_TAG)
        {
            long        attrCt = pItems[giX].NrAttrs() ;
            Attribute   *pAttrs = pItems[giX].Attributes() ;
            
            if (attrCt > 0)
                for (long giX3 = 0 ; giX3 < attrCt ; giX3++)
                {
                    Datum   *pioa = pAttrs[giX3].ItemPtr() ;
                    hr = RefCtxChk(pioa, 1, ctx) ;
                    if (FAILED(hr))
                        return hr ;
                }
        }
    }
    return S_OK ;
}

