// G2Structure.cpp : Implementation of CG2Structure
#include "stdafx.h"
#include "G2Com.h"
#include "g2string.h"
#include "Gateway.h"
#include "G2Structure.h"
#include "G2StructureEntry.h"
#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
// IG2Structure Methods:

/* ========================================================================= */
/*                   The Accessor Method for Item.                           */
/*                                                                           */
/*  Although the G2Structure object is a collection of G2StructureEntry      */
/*  objects, get_Item returns the Value member (a VARIANT) of the indexed    */
/*  entry, not the entire G2StructureEntry itself.  Thus it is possible to   */
/*  retrieve the value of a property with a Visual Basic instruction like    */
/*                                                                           */
/*                    valueVar = structVar(index)                        .   */
/*                                                                           */
/*  The index may be either the property name (as a BSTR) or an integer.     */
/*  Allowing the use of an integer as an index makes it possible to          */
/*  iterate over the name/value pairs based upon the number of entries       */
/*  in this collection, as returned by structVar.count.                      */
/* ========================================================================= */
STDMETHODIMP CG2Structure::get_Item(VARIANT index, VARIANT *pItem)
{
    HRESULT             hr ;
    IG2StructureEntry*  pOneEntry ;
    long                lX ;

    /* Get a pointer to the appropriate G2Structure Entry */
    /* -------------------------------------------------- */
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Structure::get_Item: ");
    if (index.vt == VT_UI1 || index.vt == VT_I2 || index.vt == VT_I4)
    {
        lX = (index.vt==VT_I2) ? index.iVal :
             ((index.vt==VT_I4) ? index.lVal : index.uiVal );
        ATLTRACE2(atrAxlMethodCalls, 3, " (index == %ld)\n", lX);
        EXEC(getPtrWithLongIdx(lX, &pOneEntry), hr);
    }
    else if (index.vt == VT_BSTR)
    {
        ATLTRACE2(atrAxlMethodCalls, 3, " (index == %S)\n", index.bstrVal);
        EXEC(getPtrWithStrIdx(index.bstrVal, &pOneEntry), hr);
    }
    else
    {
        ATLTRACE2 (atrAxlMsgs, 1, "** (bad index to get_Item: %d)\n", index.vt);
        return E_INVALIDARG ;
    }

    // Now use get_Value to retrieve the value
    // ---------------------------------------
    ATLASSERT(pOneEntry != NULL);
    hr = pOneEntry->get_Value(pItem);
    lX = pOneEntry->Release();
    return hr ;
}

/* ========================================================================= */
/*                                                                           */
/*                     The Item Mutator Method                               */
/*                                                                           */
/*  Set the Value member of the referenced G2StructureEntry.  The index may  */
/*  be the property name (which is found in the Name member of the           */
/*  G2StructureEntry) or an integer index.                                   */
/*                                                                           */
/*  This method makes it possible to change the value of a structure         */
/*  property with a Visual Basic instruction such as:                        */
/*                                                                           */
/*                    structVar(index) = valueVar                        .   */
/*                                                                           */
/* ========================================================================= */
STDMETHODIMP CG2Structure::put_Item(VARIANT index, VARIANT valx)
{
    HRESULT             hr ;
    IG2StructureEntry*  pOneEntry ;
    long                lX ;

    ATLTRACE2 (atrAxlMethodCalls, 3, "CG2Structure::put_Item\n");

    /* Get a pointer to the appropriate G2Structure Entry */
    /* -------------------------------------------------- */
    if (index.vt == VT_I2 || index.vt == VT_I4 || index.vt==VT_UI1)
    {
        lX = (index.vt==VT_I2) ? index.iVal :
             ((index.vt==VT_I4) ? index.lVal : index.uiVal );
        ATLTRACE2(atrAxlMethodCalls, 3, " (index == %ld)\n", lX);
        EXEC(getPtrWithLongIdx(lX, &pOneEntry), hr);
    }
    else if (index.vt == VT_BSTR)
    {
        ATLTRACE2(atrAxlMethodCalls, 3, " (index == %S)\n", index.bstrVal);
        EXEC(getPtrWithStrIdx(index.bstrVal, &pOneEntry),hr);
    }
    else
    {
        ATLTRACE2 (atrAxlMsgs, 1, "** (bad index to put_Item: %d)\n", index.vt);
        return E_INVALIDARG ;
    }

    ATLASSERT(pOneEntry != NULL);
    hr = pOneEntry->put_Value(valx);
    lX = pOneEntry->Release();
    return hr ;
}

/* ======================================================= */
/*                                                         */
/* Return the number of properties that this structure has */
/*                                                         */
/* ======================================================= */
STDMETHODIMP CG2Structure::get_Count(long *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Structure::get_Count\n");
    *pVal = m_vecG2StructureEntries.size();
    return S_OK;
}

/* ======================================================== */
/*                                                          */
/*  Make a temp array of VARIANTS and fill with the current */
/*  G2StructureEntries.  Then return an enumerator that can */
/*  be used to cycle through the list.                      */
/*                                                          */
/* ======================================================== */
STDMETHODIMP CG2Structure::get__NewEnum(LPUNKNOWN *pVal)
{
    int            size = m_vecG2StructureEntries.size();
    VARIANT*    pVar = new VARIANT[size];

    ATLTRACE2(atrAxlMethodCalls, 3,"CG2Structure::get__NewEnum\n");

    // Make the table
    // --------------
    for(int i = 0; i < size; i++)
    {
        pVar[i].vt = VT_DISPATCH;
        pVar[i].pdispVal = m_vecG2StructureEntries[i];
    }

    // Now make the enumerator
    // -----------------------
    typedef CComObject< CComEnum< IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy< VARIANT > > > enumVar;
    enumVar* pEnumVar = new enumVar;
    pEnumVar->Init(&pVar[0], &pVar[size], NULL, AtlFlagCopy);
    delete[] pVar;

    // return the enumerator
    // ---------------------
    return pEnumVar->QueryInterface(IID_IUnknown, (void**)pVal);
}


/* ===================================================================== */
/*                                                                       */
/* Add a G2StructureEntry to this collection.  The input may be a single */
/* G2StructureEntry or it may be a property name followed by its value.  */
/*                                                                       */
/* ===================================================================== */
STDMETHODIMP CG2Structure::Add(SAFEARRAY **pInpArgs)
{
    BSTR                        bstrName ;
    CComPtr<IG2StructureEntry>  pNew ;
    CComVariant                 varX ;
    HRESULT                     hr = S_OK ;
    IDispatch*                  pIDsp ;
    long                        lDim = 0L;
    long                        lLBound = 0L;
    long                        lUBound = 0L;
    SAFEARRAY                   *psa = *pInpArgs ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Structure::Add\n");

    // Make sure we received a one-dimensional SafeArray of Variants //
    // ------------------------------------------------------------- //
    if (!psa || psa->cbElements != 16)
        return E_INVALIDARG ;
    lDim = SafeArrayGetDim(psa);
    if (lDim != 1)
        return E_INVALIDARG ;

    // Get the SafeArray's lower and upper bounds
    // ------------------------------------------
    hr = SafeArrayGetLBound(psa, 1, &lLBound);
    if(FAILED(hr))
        return hr;
    hr = SafeArrayGetUBound(psa, 1, &lUBound);
    if(FAILED(hr))
        return hr;

    // If we have one argument, then it must be a G2StructureEntry.
    // If it is, add it to this G2Structure.
    // -----------------------------------------------------------
    if (lLBound == lUBound)
    {
        bool                        flgGleich ;
        BSTR                        bstrObjType ;
        CComBSTR                    sought=L"G2StructureEntry" ;
        CComPtr<G2ComObject>        pG2ComObj ;
        CComPtr<IG2StructureEntry>  pSrc ;
        CComVariant                 varC ;

        // Retrieve the only argument
        // --------------------------
        hr = SafeArrayGetElement(psa, &lLBound, &varX);
        if FAILED(hr)
            return hr ;

        // Verify that it is a G2StructureEntry
        // ------------------------------------
        if (varX.vt == VT_DISPATCH)
            if (varX.pdispVal == NULL)
                return E_UNEXPECTED ;
            else
                hr = varX.pdispVal->QueryInterface(IID_G2ComObject, (void**)(&pG2ComObj));
        else if (varX.vt == (VT_DISPATCH | VT_BYREF))
            if (varX.ppdispVal == NULL || *(varX.ppdispVal) == NULL)
                return E_UNEXPECTED ;
            else
            {
                pIDsp = *(varX.ppdispVal);
                hr = pIDsp->QueryInterface(IID_G2ComObject, (void**)(&pG2ComObj));
            }
        else
            return E_INVALIDARG ;
        pG2ComObj->get_WhatAmI(&bstrObjType);
        flgGleich = G2String:: bstrGleich(bstrObjType, sought.m_str) ;
        ::SysFreeString(bstrObjType) ;
        if(!flgGleich)
            return E_INVALIDARG ;


        // Make a new G2StructureEntry and copy the name and value to it.
        // Then add the new G2StructureEntry to the collection.
        // --------------------------------------------------------------
        hr = pG2ComObj->QueryInterface(IID_IG2StructureEntry, (void**)(&pSrc));
        pG2ComObj.Release();
        if (FAILED(hr))
            return E_INVALIDARG ;
        hr = pNew.CoCreateInstance(CLSID_G2StructureEntry,NULL,CLSCTX_INPROC_SERVER);
        if (FAILED(hr))
            return E_UNEXPECTED ;
        if (FAILED(pSrc->get_Name(&bstrName)) || FAILED(pNew->put_Name(bstrName))
                || FAILED(pSrc->get_Value(&varC)) || FAILED(pNew->put_Value(varC)))
            return E_UNEXPECTED ;
        if (FAILED(pNew->QueryInterface(IID_IDispatch, (void**)&pIDsp)))
            return E_UNEXPECTED ;
        m_vecG2StructureEntries.push_back(pIDsp);
    }

    // If there are two arguments, then the first one should be a BSTR
    // containing the property name.  The second one can be of any type.
    else if ((lUBound-lLBound)==1)
    {
        // Retrieve and check the first argument
        // -------------------------------------
        hr = SafeArrayGetElement(psa, &lLBound, &varX);
        if FAILED(hr)
            return hr ;
        if (varX.vt == VT_BSTR)
            bstrName = varX.bstrVal ;
        else if (varX.vt == (VT_BSTR|VT_BYREF))
            bstrName = *(varX.pbstrVal);
        else if (varX.vt == (VT_VARIANT|VT_BYREF) && varX.pvarVal->vt==VT_BSTR)
            bstrName = varX.pvarVal->bstrVal ;
        else
            return E_INVALIDARG ;


        // Create a CG2StructureEntry, fill it in, and add it to the collection
        // --------------------------------------------------------------------
        EXEC(pNew.CoCreateInstance(CLSID_G2StructureEntry,NULL,CLSCTX_INPROC_SERVER),hr);
        EXEC(pNew->put_Name(bstrName),hr);
        VariantClear(&varX) ;
        EXEC(SafeArrayGetElement(psa, &lUBound, &varX),hr);
        EXEC(pNew->put_Value(varX),hr);
        EXEC(pNew->QueryInterface(IID_IDispatch, (void**)&pIDsp),E_UNEXPECTED);
        m_vecG2StructureEntries.push_back(pIDsp);
        VariantClear(&varX) ;
    }
    else
        return E_INVALIDARG ;

    return hr ;
}

// ===================================================================
// Remove a G2StructureEntry from this G2Structure.  The index that
// we use to select which G2StructureEntry will be removed may have
// one of 3 types:
// 1. integer/long specifying collection entry number
// 2. a text string, specifying the name of the property
// 3. a G2StructureEntry with the same name and value as the
//    entry we wish to remove.
// ===================================================================
STDMETHODIMP CG2Structure::Remove(VARIANT varIndex)
{
    long        lN = m_vecG2StructureEntries.size();
    long        lx ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Structure::Remove\n");

    if (varIndex.vt == VT_UI1 || varIndex.vt == VT_I2 || varIndex.vt == VT_I4)
    {
        long    iIdx ;

        if (varIndex.vt==VT_UI1)        // VB Byte
            iIdx = (long)varIndex.bVal ;
        else if (varIndex.vt == VT_I2)  // VB Integer
            iIdx = (long)varIndex.iVal ;
        else
            iIdx = varIndex.lVal ;      // VB Long

        // Be sure we are in range.
        // -----------------------
        if(iIdx >=0 && iIdx < lN)
        {
            // Find the correct G2StructureEntry
            // ---------------------------------
            IDispatch* pDisp = m_vecG2StructureEntries[iIdx];

            // Remove it.
            // ----------
            pDisp->Release();
            m_vecG2StructureEntries.erase(m_vecG2StructureEntries.begin() + iIdx);
            return S_OK;
        }
        return E_FAIL;
    }

    // Index is the property name
    // --------------------------
    else if (varIndex.vt == VT_BSTR)
    {
        CComBSTR                    bstrx ;
        CComPtr<IG2StructureEntry>    pSE ;
        IDispatch*                    pDisp ;
        HRESULT                        hr ;

        for (lx = 0 ; lx < lN ; lx++)
        {
            pDisp = m_vecG2StructureEntries[lx] ;
            EXEC(pDisp->QueryInterface(IID_IG2StructureEntry, (void**)&pSE), E_UNEXPECTED);
            EXEC(pSE->get_Name(&bstrx), hr);
            if (G2String::bstrGleich(varIndex.bstrVal, bstrx))
            {
                pDisp->Release();
                m_vecG2StructureEntries.erase(m_vecG2StructureEntries.begin() + lx);
                return S_OK;
            }
        }
        return E_FAIL ;
    }

    // Index could be a G2StructureEntry
    // ---------------------------------
    else if ((varIndex.vt & VT_DISPATCH) == VT_DISPATCH)
    {
        BSTR                 bstObjType, bstrName, bstrx ;
        CComBSTR            sought=L"G2StructureEntry" ;
        IG2StructureEntry*    pG2StructEnt ;
        G2ComObject         *pG2ComObject ;
        HRESULT                hr ;
        IDispatch*            pIDsp ;
        IUnknown*             pIUK ;
        VARIANT                varX ;
        _variant_t            varS ;

        // Verify that it is a G2StructureEntry
        // ------------------------------------
        if ((varIndex.vt & VT_BYREF) == VT_BYREF)
        {
            if (varIndex.ppdispVal == NULL)
                return E_UNEXPECTED ;
            pIDsp = *(varIndex.ppdispVal);
        }
        else
            pIDsp = varIndex.pdispVal ;
        pIUK = dynamic_cast<IUnknown*>(pIDsp);
        if (pIUK==NULL)
            return E_UNEXPECTED ;
        hr = pIUK->QueryInterface(IID_G2ComObject, (void**)&pG2ComObject);
        if (FAILED(hr))
            return E_INVALIDARG ;
        pG2ComObject->get_WhatAmI(&bstObjType);
        pG2ComObject->Release();
        if (!G2String::bstrGleich(bstObjType, sought.m_str))
            return E_INVALIDARG ;

        // Save the property name and value to simplify the search
        // -------------------------------------------------------
        pG2StructEnt = static_cast<IG2StructureEntry*>(pIDsp);
        pG2StructEnt->get_Name(&bstrName);
        VariantInit(&varX);
        pG2StructEnt->get_Value(&varX);
        varS = varX ;

        // Search for a matching entry & delete it if found
        // ------------------------------------------------
        for (lx = 0 ; lx < lN ; lx++)
        {
            pIDsp = m_vecG2StructureEntries[lx] ;
            hr = static_cast<IG2StructureEntry*>(pIDsp)->get_Name(&bstrx);
            if (FAILED(hr))
                return hr ;
            hr = static_cast<IG2StructureEntry*>(pIDsp)->get_Value(&varX);
            if (FAILED(hr))
                return hr ;
            if (G2String::bstrGleich(bstrName, bstrx) && varS==varX)
            {
                ::SysFreeString(bstrx);
                pIDsp->Release();
                m_vecG2StructureEntries.erase(m_vecG2StructureEntries.begin() + lx);
                return S_OK;
            }
            else
                ::SysFreeString(bstrx);
        }
        SetComError(OLESTR("Entry to remove not found"),&IID_IG2Structure,OLESTR("G2Gateway.G2Structure"));
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,ERROR_NO_MATCH);
    }

    // Not a valid index
    // -----------------
    return E_INVALIDARG ;

}


/* ========================================================================== */
/*                                                                            */
/*             Retrieve a list of this structure's property names             */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Structure::Names(SAFEARRAY **pNames)
{
    BSTR                bstrX ;
    HRESULT             hr ;
    IG2StructureEntry   *pIG2StrEnt ;
    long                nrEnts = m_vecG2StructureEntries.size();
    long                lv, lb ;
    SAFEARRAYBOUND      aDim[1] ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Structure::Names\n");

    aDim[0].lLbound = 0 ;
    aDim[0].cElements = nrEnts ;
    *pNames = SafeArrayCreate(VT_BSTR, 1, aDim);
    if (*pNames == NULL)
        return E_FAIL ;

    for (lv = 0, lb = 1 ; lv < nrEnts ; lv++, lb++)
    {
        IDispatch *pIDsp = m_vecG2StructureEntries[lv] ;
        hr = pIDsp->QueryInterface(IID_IG2StructureEntry,reinterpret_cast<void**>(&pIG2StrEnt)) ;
        if (SUCCEEDED(hr))
        {
            hr = pIG2StrEnt->get_Name(&bstrX) ;
            pIG2StrEnt->Release() ;
            if (SUCCEEDED(hr))
            {
                hr = SafeArrayPutElement(*pNames, &lv, bstrX);
                SysFreeString(bstrX) ;
            }
        }
        if (FAILED(hr))
        {
            SafeArrayDestroy(*pNames) ;
            *pNames = NULL ;
            return hr ;
        }
    }
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/*             Retrieve a list of this structure's property values            */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Structure::Values(SAFEARRAY **pValues)
{
    HRESULT             hr ;
    IG2StructureEntry   *pIG2StrEnt ;
    long                nrEnts = m_vecG2StructureEntries.size();
    long                lv, lb ;
    SAFEARRAYBOUND      aDim[1] ;
    VARIANT             varX, varY ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Structure::Values\n");

    aDim[0].lLbound = 0 ;
    aDim[0].cElements = nrEnts ;
    *pValues = SafeArrayCreate(VT_VARIANT, 1, aDim);
    if (*pValues == NULL)
        return E_FAIL ;
    VariantInit(&varX);
    VariantInit(&varY);

    for (lv = 0, lb = 1 ; lv < nrEnts ; lv++, lb++)
    {
        IDispatch *pIDsp = m_vecG2StructureEntries[lv] ;
        hr = pIDsp->QueryInterface(IID_IG2StructureEntry,reinterpret_cast<void**>(&pIG2StrEnt)) ;
        if (SUCCEEDED(hr))
        {
            hr = pIG2StrEnt->get_Value(&varX) ;
            pIG2StrEnt->Release() ;
            if (SUCCEEDED(hr))
            {
                // VB doesn't like VARIANTs containing VARIANTs
                // --------------------------------------------
                if (varX.vt==(VT_VARIANT|VT_BYREF))
                {
                    // Dereference the contained VARIANT ;
                    VariantCopy(&varY,varX.pvarVal);
                    hr = SafeArrayPutElement(*pValues, &lv, &varY);
                    VariantClear(&varY) ;
                }
                else
                    hr = SafeArrayPutElement(*pValues, &lv, &varX);
                VariantClear(&varX) ;
            }
            if (FAILED(hr))
            {
                SafeArrayDestroy(*pValues) ;
                return hr ;
            }
        }
    }
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/*           Standard interface for returning error messages to client        */
/*                                                                            */
/* ========================================================================== */
#if _MSC_VER == 1200  //VC++ 6.0
STDMETHODIMP CG2Structure::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] =
        {
            &IID_IG2Structure
        };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (::ATL::InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}


#elif _MSC_VER >= 1300  //VC++ 7 or more
STDMETHODIMP CG2Structure::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] =
	{
		&IID_IG2Structure
	};
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}


#endif
/////////////////////////////////////////////////////////////////////////////
// IG2ComObject Methods:

/* ========================================================================== */
/*                                                                            */
/*  get_WhatAmI: return string identifying this object as a G2Structure       */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Structure::get_WhatAmI(BSTR *WhatAmI)
{
    ATLASSERT(WhatAmI != NULL);
    *WhatAmI = ::SysAllocString(L"G2Structure");
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/*             Create a duplicate instance of this object.                    */
/*                                                                            */
/* ========================================================================== */
HRESULT CG2Structure::Duplicate(IUnknown **pNewObj)
{
    HRESULT             hr = S_OK;
    IDispatch           *pIDsp ;
    IG2Structure        *pIG2Struct ;
    IUnknown            *pNew ;
    CG2Structure        *pObj ;
    long                lCount, lX, idx=0 ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Structure::Duplicate\n");

    /* Create the new G2Structure object and get the interface */
    /* pointer that we will need to work with it.              */
    /* ------------------------------------------------------- */
    hr = ::CoCreateInstance(CLSID_G2Structure,NULL,CLSCTX_INPROC_SERVER,IID_IUnknown,
                            reinterpret_cast<void**>(&pNew));
    if (FAILED(hr))
        return hr ;
    hr = pNew->QueryInterface(IID_IG2Structure,reinterpret_cast<void**>(&pIG2Struct));
    if (FAILED(hr))
    {
        pNew->Release();
        return hr ;
    }
    pObj = (CG2Structure*)pIG2Struct ;

    /* Prepare to add duplicates of the G2StructureEntry:s in this */
    /* G2Structure to the new G2Structure.                         */
    /* ----------------------------------------------------------- */
    hr = get_Count(&lCount);
    for (lX = 0 ; lX < lCount ; lX++)
    {
        IG2StructureEntry   *pIG2SE ;
        IUnknown            *pIG2SEUnk ;
        IDispatch           *pIG2SEDsp ;

        pIDsp = m_vecG2StructureEntries[lX] ;
        hr = pIDsp->QueryInterface(IID_IG2StructureEntry, reinterpret_cast<void**>(&pIG2SE)) ;
        pIDsp->Release() ;
        if (SUCCEEDED(hr))
        {
            hr = pIG2SE->Duplicate(&pIG2SEUnk) ;
            if SUCCEEDED(hr)
            {
                hr = pIG2SEUnk->QueryInterface(IID_IDispatch,reinterpret_cast<void**>(&pIG2SEDsp)) ;
                pIG2SEUnk->Release() ;

                if (SUCCEEDED(hr))
                    pObj->m_vecG2StructureEntries.push_back(pIG2SEDsp) ;
            }
        }
        if FAILED(hr)
        {
            pIG2Struct->Release() ;
            pNew->Release() ;
            return hr ;
        }
    }

    pIG2Struct->Release() ;
    *pNewObj = pNew ;
    return S_OK ;
}

/////////////////////////////////////////////////////////////////////////////

/* ========================================================================== */
/*                                                                            */
/*    Return the entry in the collection that is in the specified position    */
/*                                                                            */
/* ========================================================================== */
HRESULT CG2Structure::getPtrWithLongIdx(long index, IG2StructureEntry** ppLine)
{
    HRESULT    hr ;
    long    lN = m_vecG2StructureEntries.size();
    IG2StructureEntry    *pHp ;

    // Be sure we are in range.
    // ------------------------
    if (index >= 0 && index < lN)
    {
        IDispatch* pDisp = m_vecG2StructureEntries[index] ;
        EXEC(pDisp->QueryInterface(IID_IG2StructureEntry, (void**)(&pHp)),hr);
        *ppLine = pHp ;
        return S_OK ;
    }
    else
        return E_INVALIDARG ;
}


/* ========================================================================== */
/*                                                                            */
/*  Find the first entry in the collection with the specified property name   */
/*                                                                            */
/* ========================================================================== */
HRESULT CG2Structure::getPtrWithStrIdx(BSTR BSTRidx, IG2StructureEntry** ppLine)
{
    long                        lN = m_vecG2StructureEntries.size();
    long                        lx ;
    bool                        flgGleich ;
    BSTR                        bstrx ;
    CComPtr<IG2StructureEntry>  pSE ;
    IDispatch*                  pDisp ;
    HRESULT                     hr ;

    for (lx = 0 ; lx < lN ; lx++)
    {
        pDisp = m_vecG2StructureEntries[lx] ;
        if (!pSE == FALSE)
            pSE.Release();
        EXEC(pDisp->QueryInterface(IID_IG2StructureEntry,(void**)&pSE), E_UNEXPECTED);
        EXEC(pSE->get_Name(&bstrx), hr);
        flgGleich = G2String::bstrGleich(BSTRidx, bstrx) ;
        ::SysFreeString(bstrx) ;
        if (flgGleich)
        {
            *ppLine = pSE.Detach();
            return S_OK ;
        }
    }
    return E_INVALIDARG ;
}

/* ========================================================================== */
/*                                                                            */
/*                  We are about to destroy this G2Structure.                 */
/*               First, release all the G2StructureEntries in it.             */
/*                                                                            */
/* ========================================================================== */
void CG2Structure::FinalRelease()
{
    HRESULT                hr ;
    int                    i ;
    long                nrProps ;
    VARIANT                varX ;

    ATLTRACE2(atrG2ObjLife, 4, "**< G2Structure at %08x being destroyed.\n", this);

    // Remove all the entries from this structure
    // ------------------------------------------
    hr = get_Count(&nrProps);
    if (FAILED(hr))
        goto leak ;
    VariantInit(&varX);
    varX.vt = VT_I4 ;
    for (i = nrProps-1 ; i >= 0 ; i--)
    {
        varX.lVal = i ;
        hr = Remove(varX);
        if (FAILED(hr))
            goto leak ;
    }
    return ;
leak:
    ATLTRACE2(atrAxlMsgs,0,"Failed to release all contents of G2Structure.\n");
    return ;
}


/* ========================================================================== */
/*                                                                            */
/*         Add the attribute represented by *pIG2SE to this Structure         */
/*                                                                            */
/* ========================================================================== */
HRESULT CG2Structure::Confiscate(IG2StructureEntry *pIG2SE)
{
    HRESULT     hr ;
    IDispatch*  pIDsp ;

    if (!pIG2SE)
        return E_POINTER ;
    hr = pIG2SE->QueryInterface(IID_IDispatch, reinterpret_cast<void**>(&pIDsp)) ;
    pIG2SE->Release() ;
    if (SUCCEEDED(hr))
        m_vecG2StructureEntries.push_back(pIDsp) ;
    return hr ;
}
