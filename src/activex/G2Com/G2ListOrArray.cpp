/* ========================================================================== */
/*                                                                            */
/*                          G 2 L i s t O r A r r a y                         */
/*                                                                            */
/*   A G2ListOrArray object is a list/array wrapper.  It provides the         */
/*   functionality we need to create and manipulate G2 arrays and lists.      */
/*                                                                            */
/* ========================================================================== */


// G2ListOrArray.cpp : Implementation of CG2ListOrArray
#include "stdafx.h"
#include "Converter.h"
#include "Datum.h"
#include "G2Com.h"
#include "G2ListOrArray.h"
#include "Gateway.h"
#include "gsi_main_cpp.h"
#include "GsiContext.h"

    struct lup
    {
        G2Type      type ;
        VARTYPE     vt ; } luptab[] = { {g2IntegerArray, VT_I4},
                                        {g2SymbolArray, VT_BSTR},
                                        {g2StringArray, VT_BSTR},
                                        {g2LogicalArray,VT_BOOL},
                                        {g2FloatArray, VT_R8},
                                        {g2ItemArray, VT_VARIANT},
                                        {g2ValueArray, VT_VARIANT},
                                        {g2ItemOrValueArray, VT_VARIANT},
                                        {g2QuantityArray, VT_VARIANT},
                                        {g2IntegerList, VT_I4},
                                        {g2SymbolList, VT_BSTR},
                                        {g2StringList,VT_BSTR},
                                        {g2LogicalList, VT_BOOL},
                                        {g2FloatList, VT_R8},
                                        {g2ItemList,  VT_VARIANT},
                                        {g2ValueList, VT_VARIANT},
                                        {g2ItemOrValueList, VT_VARIANT},
                                        {g2QuantityList, VT_VARIANT} } ;
    const int nrTypes = sizeof(luptab)/sizeof(struct lup) ;

/////////////////////////////////////////////////////////////////////////////
// CG2ListOrArray


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*               Get the value in the specified (idx) position                */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::get_Item(long idx, VARIANT *pVal)
{
    BSTR            bstrVal ;
    double          rVal ;
    HRESULT         hr ;
    long            nrEls ;
    long            lVal ;
    VARIANT_BOOL    varbooVal ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2ListOrArray::get_Item\n");
    hr = get_Count(&nrEls) ;
    if (FAILED(hr)) return hr ;
    if (idx < 0 || idx >= nrEls) return E_INVALIDARG ;
    VariantClear(pVal) ;
    pVal->vt = m_varType ;
    switch(m_varType)
    {
        case VT_I4:
            EXEC(::SafeArrayGetElement(m_pSA, &idx, &lVal), hr) ;
            pVal->lVal = lVal ;
            break ;
        case VT_BOOL:
            EXEC(::SafeArrayGetElement(m_pSA, &idx, &varbooVal), hr) ;            
            pVal->boolVal = varbooVal ;
            break ;
        case VT_R8:
            EXEC(::SafeArrayGetElement(m_pSA, &idx, &rVal), hr) ;
            pVal->dblVal = rVal ;
            break ;
        case VT_BSTR:
            EXEC(::SafeArrayGetElement(m_pSA, &idx, &bstrVal), hr) ;
            pVal->bstrVal = bstrVal ;
            break ;
        case VT_VARIANT:
            VariantInit(pVal) ;
            EXEC(::SafeArrayGetElement(m_pSA, &idx, pVal), hr) ;
            break ;
        default:
            return E_UNEXPECTED ;
    }
	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Store the provided item at the specified location of this list/array.   */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::put_Item(long idx, VARIANT newVal)
{
	HRESULT		hr ;
	long		nrEls ;
	VARIANT		fmtdVar ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2ListOrArray::put_Item");

    /* Validate Index */
    /* -------------- */
	get_Count(&nrEls) ;
	if (idx < 0 || idx >= nrEls)
		return E_INVALIDARG ;

    // Validate new value
    // ------------------
	VariantInit(&fmtdVar) ;
    EXEC(castVal(newVal, &fmtdVar), hr) ;

	switch(m_varType)
	{
	case VT_I4 :	::SafeArrayPutElement(m_pSA, &idx, &(fmtdVar.lVal)) ;
					break ;
	case VT_BOOL:   ::SafeArrayPutElement(m_pSA, &idx, &(fmtdVar.boolVal)) ;
					break ;
	case VT_R8 :	::SafeArrayPutElement(m_pSA, &idx, &(fmtdVar.dblVal)) ;
					break ;
	case VT_BSTR :	::SafeArrayPutElement(m_pSA, &idx, &(fmtdVar.bstrVal)) ;
					break ;
	case VT_VARIANT : ::SafeArrayPutElement(m_pSA, &idx, &newVal) ;
					break ;
	default:	 return E_UNEXPECTED ;
	}

	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                 Return the G2 type of this list or array                   */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::get_Type(G2Type *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2ListOrArray::get_Type");
	*pVal = m_lawType ;

	return S_OK;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*        Set the GSI and Variant types.  If they were previously set,       */
/*        all data that was stored in this object will be lost.              */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::put_Type(G2Type newType)
{
    bool        zapSA = false ;
    int         iX ;
    SAFEARRAY   *pSA ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2ListOrArray::put_Type");
    if (m_lawType)
        zapSA = true ;
    for (iX = 0 ; iX < nrTypes ; iX++)
        if (newType == luptab[iX].type)
        {
            m_lawType = newType ;
            m_varType = luptab[iX].vt ;
            if (zapSA)
            {
                pSA = m_pSA ;
                m_pSA = NULL ;
                return ::SafeArrayDestroy(pSA) ;
            }
            return S_OK ;
        }
    return E_INVALIDARG ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*          Determine how many elements are in this array or list            */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::get_Count(long *pVal)
{
    if (m_pSA == NULL)
        *pVal = 0 ;
    else
    {
        HRESULT hr ;
        long    lb, ub ;

        hr = ::SafeArrayGetLBound(m_pSA, 1, &lb) ;
        if (FAILED(hr)) return hr ;
        hr = ::SafeArrayGetUBound(m_pSA, 1, &ub) ;
        if (FAILED(hr)) return hr ;
        *pVal = ub - lb + 1 ;
    }
	return S_OK;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*      Insert an element into the array before the specified location       */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::Insert(long idx, VARIANT varX)
{
    HRESULT         hr ;
    long            nrEls ;

    // Validate index
    // --------------
    EXEC(get_Count(&nrEls), hr) ;
    if (idx < 0 || idx >= nrEls)
        return E_INVALIDARG ;

    // Call the helper function to do the work
    // ---------------------------------------
    EXEC(Redim(idx, true, nrEls-idx, &varX), hr) ;

	return S_OK;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*       Insert an element into the array after the specified location       */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::Append(long idx, VARIANT varX)
{
    HRESULT         hr ;
    long            nrEls ;

    // Validate index
    // --------------
    EXEC(get_Count(&nrEls), hr) ;
    if (idx < 0 || idx >= nrEls)
        return E_INVALIDARG ;

    // Validate new value
    // ------------------
    EXEC(castVal(varX, &varX), hr) ;

    // Call the helper function to do the work
    // ---------------------------------------
    EXEC(Redim(idx+1, true, nrEls-idx-1, &varX), hr) ;

    return S_OK ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                   Add an element to the end of the array                  */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::Add(VARIANT varX)
{   
    HRESULT     hr ;
    long        nrEls ;

    EXEC(get_Count(&nrEls), hr) ;
    EXEC(Redim(nrEls, true, 0, &varX), hr) ;

	return S_OK;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*     Remove the element at the specified location from the array/list.     */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::Remove(long idx)
{
    HRESULT     hr ;
    long        nrEls ;

    EXEC(get_Count(&nrEls), hr) ;
    EXEC(Redim(idx, false, nrEls-idx-1, NULL), hr) ;

	return S_OK;

}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*      The _NewEnum method required for COM collections.  It creates a      */
/*      SafeArray of Variants containing pointers to G2LAElement objects.    */
/*      Each G2LAElement contains a pointer to this G2ListOrArray and an     */
/*      index number.  They use the get_ & put_Item methods of this to       */
/*      access the list/array elements.                                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::get__NewEnum(LPUNKNOWN *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3,"CG2ListOrArray::get__NewEnum\n");

    typedef CComObject< CComEnum< IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy< VARIANT > > > enumVar;
    enumVar         *pEnumVar = new enumVar;
    HRESULT         hr ;
    IClassFactory   *pCF ;
    IG2LAElement    *pLAEl ;
    IG2ListOrArray  *pLaw ;
    long            nrEls, lX ;
    VARIANT*        pVar = NULL ;
      
    get_Count(&nrEls) ;
    if (nrEls > 0)
    {
        pVar = new VARIANT[nrEls];
        EXEC(::DllGetClassObject(CLSID_G2LAElement,IID_IClassFactory, (void**)&pCF), hr) ;
        for(lX = 0; lX < nrEls; lX++)
        {
            hr = pCF->CreateInstance(NULL,IID_IG2LAElement, (void**)&pLAEl) ;
            if (FAILED(hr)) goto failure ;
            hr = QueryInterface(IID_IG2ListOrArray, (void**)&pLaw) ;
            if (FAILED(hr)) goto failure ;
            pLAEl->Init(pLaw, lX) ;
            pVar[lX].vt = VT_DISPATCH;
            pVar[lX].pdispVal = pLAEl ;
        }
        pCF->Release() ;
    }

    // Now make the enumerator
    // -----------------------
    pEnumVar->Init(&pVar[0], &pVar[nrEls], NULL, AtlFlagCopy);
    delete[] pVar;

    // return the enumerator
    // ---------------------
    return pEnumVar->QueryInterface(IID_IUnknown, (void**)pVal);

failure:
    pCF->Release() ;
    delete [] pVar ;
    delete pEnumVar ;
    return hr ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Hidden method used to create a SafeArray that will be pointed to by      */
/*   this G2ListOrArray object and then to fill in the SafeArray with the     */
/*   elements of the associated array or list.                                */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::Init(long datumPtr)
{
    ATLASSERT(datumPtr) ;

	Datum*			pDatum = (Datum*)datumPtr ;
    HRESULT			hr = E_INVALIDARG;
    int				iX ;
    long			lX ;
    SAFEARRAYBOUND  bound[1] ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2ListOrArray::Init");

    // Record the list or array type and determine the
    // type of SafeArray that we need.
    // -----------------------------------------------
    m_lawType = (G2Type)(pDatum->Type()) ;
    if (m_lawType == GSI_SYMBOL_ARRAY_TAG || m_lawType == GSI_SYMBOL_LIST_TAG)
        m_varType = pDatum->G2Symbols() ? VT_VARIANT : VT_BSTR ;
    else
    {
        for (iX = 0 ; iX < nrTypes ; iX++)
            if (m_lawType == luptab[iX].type)
            {
                m_varType = luptab[iX].vt ;
                break ;
            }
        if (!m_varType)
            return E_INVALIDARG ;
    }


    // How many elements?
    // ------------------
    long	nrEls = pDatum->Count() ;

    if (m_pSA)
    {
        ::SafeArrayDestroy(m_pSA) ;
        m_pSA = NULL ;
    }


    // Create the SafeArray of the required type & size
    // ------------------------------------------------
    bound[0].lLbound = 0 ;
    bound[0].cElements = nrEls ;
    m_pSA = ::SafeArrayCreate(m_varType, 1, bound) ;
    if (!m_pSA) return E_OUTOFMEMORY ;

    // Fill in the SafeArray
    // ---------------------
	Datum*		pElements = pDatum->LAElements() ;
    BSTR        bstrX ;
    TCHAR*      pText ;
    VARIANT     varX ;

    USES_CONVERSION ;
    switch(m_lawType)
    {
        case GSI_INTEGER_ARRAY_TAG:
        case GSI_INTEGER_LIST_TAG:    
            {
                long    lX2 ;
                for (lX = 0 ; lX < nrEls ; lX++)
                {
                    lX2 = pElements[lX].Long() ;
                    ::SafeArrayPutElement(m_pSA, &lX, &lX2 ) ;
                }
                break ;
            }

        case GSI_LOGICAL_ARRAY_TAG:
        case GSI_LOGICAL_LIST_TAG:
            {
                bool            flgX ;
                VARIANT_BOOL    vtbTrue  = VARIANT_TRUE,
                                vtbFalse = VARIANT_FALSE ;

                for (lX = 0 ; lX < nrEls ; lX++)
                {
                    flgX = pElements[lX].Boolean() ;
                    ::SafeArrayPutElement(m_pSA, &lX, flgX ? &vtbTrue : &vtbFalse ) ;
                }
                break ;
            }
        
        case GSI_SYMBOL_ARRAY_TAG:
        case GSI_SYMBOL_LIST_TAG:
        case GSI_STRING_ARRAY_TAG:
        case GSI_STRING_LIST_TAG:
            {
                IDispatch*  pIDsp ;
                IG2Symbol*  pISym ;
                bool        syms = pDatum->G2Symbols() && 
                                (m_lawType == GSI_SYMBOL_ARRAY_TAG || m_lawType == GSI_SYMBOL_LIST_TAG) ;

                for (lX = 0 ; lX < nrEls ; lX++)
                {
                    if (m_lawType == GSI_SYMBOL_ARRAY_TAG || m_lawType == GSI_SYMBOL_LIST_TAG)
                        pText = pElements[lX].Symbol() ;
                    else
                        pText = pElements[lX].String() ;
                    bstrX = ::SysAllocString(T2OLE(pText)) ;
                    if (syms)
                    {
                        VARIANT     varX ;

                        VariantInit(&varX) ;
                        hr = CoCreateInstance(CLSID_G2Symbol,NULL,CLSCTX_INPROC_SERVER,IID_IG2Symbol,
                                reinterpret_cast<void**>(&pISym)) ;
                        if (SUCCEEDED(hr))
                            hr = pISym->QueryInterface(IID_IDispatch, reinterpret_cast<void**>(&pIDsp)) ;
                        if (SUCCEEDED(hr))
                        {
                            pISym->put_Item(bstrX) ;
                            pISym->Release() ;
                            varX.vt = VT_DISPATCH ;
                            varX.pdispVal = pIDsp ;
                            hr = ::SafeArrayPutElement(m_pSA, &lX, &varX) ;
                        }
                        VariantClear(&varX) ;
                    }
                    else
                        hr = ::SafeArrayPutElement(m_pSA, &lX, bstrX) ;
                    SysFreeString(bstrX) ;
                    delete [] pText ;
                }
                break ;
            }

        case GSI_FLOAT64_ARRAY_TAG:
        case GSI_FLOAT64_LIST_TAG:
            {
                double  dX ;
                for (lX = 0 ; lX < nrEls ; lX++)
                {
                    dX = pElements[lX].Float() ;
                    ::SafeArrayPutElement(m_pSA, &lX, &dX) ;
                }
                break ; 
            }

        default:
            VariantInit(&varX) ;
            for (lX = 0 ; lX < nrEls ; lX++)
            {
                hr = pElements[lX].toVariant(&varX) ;
                if (FAILED(hr))
                {
                    ::SafeArrayDestroy(m_pSA) ;
                    return hr ;
                }
                ::SafeArrayPutElement(m_pSA, &lX, &varX) ;
                VariantClear(&varX) ;
            }
    }

	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*           Standard interface for returning error messages to client        */
/*                                                                            */
/* -------------------------------------------------------------------------- */
#if _MSC_VER == 1200  //VC++ 6.0
STDMETHODIMP CG2ListOrArray::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2ListOrArray
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        if (::ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

#elif _MSC_VER >= 1300  //VC++ 7 or more
STDMETHODIMP CG2ListOrArray::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2ListOrArray
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

#endif


/* ========================================================================== */
/*                                                                            */
/*             Force the input into the format required by GSI.               */
/*                                                                            */
/* ========================================================================== */

HRESULT CG2ListOrArray::castVal(VARIANT newVal, VARIANT *pCast)
{
    HRESULT         hr = S_OK ;
    unsigned short  valType = newVal.vt ;

    switch(m_varType)
    {
        case VT_I4:
            
            if (valType == VT_I4)
                pCast->lVal = (long)newVal.lVal ;
            else if (valType == VT_UI1)
                pCast->lVal = (long)newVal.bVal ;
            else if (valType == VT_I2)
                pCast->lVal = (long)newVal.iVal ;
            else if (valType == VT_I1)
                pCast->lVal = (long)newVal.cVal ;
            else if (valType == VT_UI2)
                pCast->lVal = (long)newVal.uiVal ;
            else if (valType == VT_UI4)
                pCast->lVal = (long)newVal.ulVal ;
            else if (valType == VT_INT)
                pCast->lVal = (long)newVal.intVal ;
            else if (valType == VT_UINT)
                pCast->lVal = (long)newVal.uintVal ;
            else if (valType == (VT_BYREF|VT_UI1))
                pCast->lVal = (long)*(newVal.pbVal) ;
            else if (valType == (VT_BYREF|VT_I2))
                pCast->lVal = (long)*(newVal.piVal) ;
            else if (valType == (VT_BYREF|VT_I4))
                pCast->lVal = (long)*(newVal.plVal) ;
            else if (valType == (VT_BYREF|VT_I1))
                pCast->lVal = (long)*(newVal.pcVal) ;
            else if (valType == (VT_BYREF|VT_UI2))
                pCast->lVal = (long)*(newVal.puiVal) ;
            else if (valType == (VT_BYREF|VT_UI4))
                pCast->lVal = (long)*(newVal.pulVal) ;
            else if (valType == (VT_BYREF|VT_INT))
                pCast->lVal = (long)*(newVal.pintVal) ;
            else if (valType == (VT_BYREF|VT_UINT))
                pCast->lVal = (long)*(newVal.puintVal) ;
			else if (valType == VT_BOOL)
				if (newVal.boolVal == VARIANT_FALSE)
					pCast->lVal = -1000L ;
				else
					pCast->lVal = 1000L ;
			else if (valType == (VT_BOOL|VT_BYREF))
				if (*(newVal.pboolVal) == VARIANT_FALSE)
					pCast->lVal = -1000L ;
				else
					pCast->lVal = 1000L ;
            else
                hr = E_INVALIDARG ;
            break ;
        
        case VT_BOOL:
            if (valType == VT_BOOL)
                pCast->boolVal = newVal.boolVal ;
            else if (valType == (VT_BOOL|VT_BYREF))
                pCast->boolVal = *(newVal.pboolVal) ;
            else
                hr = E_INVALIDARG ;
            break ;
            

        case VT_R8:

            if (valType == VT_R4)
                pCast->dblVal = (double)newVal.fltVal ;
            else if (valType == VT_R8)
                pCast->dblVal = (double)newVal.dblVal ;
            else if (valType == (VT_BYREF|VT_UI1))
                pCast->dblVal = (double)*(newVal.pfltVal) ;
            else if (valType == (VT_BYREF|VT_I2))
                pCast->dblVal = (double)*(newVal.pdblVal) ;
            else
                hr = E_INVALIDARG ;
            break ;

        // No need to cast these two.  Original VARIANT will be used.
        // ---------------------------------------------------------
        case VT_BSTR:
        case VT_VARIANT:
            return S_OK ;

        default:
            hr = E_INVALIDARG ;
    }
    pCast->vt = m_varType ; // not if type is VT_VARIANT
    return hr ;

}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Generalized procedure for adding or deleting an element from a SafeArray. */
/* This is where most of the work of the Add, Insert, Append, and Remove     */
/* methods is performed.                                                     */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::Redim(unsigned long nrBefore, bool booNew, unsigned long nrAfter, VARIANT *pNewVal)
{
    HRESULT         hr ;
    long            nrEls, lX, idx=0 ;
    SAFEARRAY       *pSA2, *pSAx ;
    SAFEARRAYBOUND  bound[1] ;
    VARIANT         fmtdVar ;
    void *          pFromDat ;
    void *          pToDat ;
    void *          pFromX ;
    void *          pToX ;

    // Validate index
    // --------------
    EXEC(get_Count(&nrEls), hr) ;
    if (nrBefore + nrAfter > (unsigned)nrEls)
        return E_INVALIDARG ;
    if (!booNew)
        if ((nrBefore+nrAfter == (unsigned)nrEls) || nrEls==0)
        return E_INVALIDARG ;
    VariantInit(&fmtdVar) ;

    // If we are deleting the last element, zap the SafeArray & the pointer
    // --------------------------------------------------------------------
    if (!booNew && nrEls == 1)
    {
        EXEC(SafeArrayDestroy(m_pSA), hr) ;
        m_pSA = NULL ;
        return S_OK ;
    }

    // Validate new value
    // ------------------
    if (booNew)
        EXEC(castVal(*pNewVal, &fmtdVar), hr) ;

    // Create New SafeArray
    // --------------------
    bound[0].lLbound = 0 ;
    bound[0].cElements = nrEls + ((booNew) ? 1 : -1) ;
    pSA2 = ::SafeArrayCreate(m_varType, 1, bound) ;
    if (!pSA2) return E_OUTOFMEMORY ;

    // If this is the first time we are adding an element to this 
    // object attach it to its new SafeArray here.
    // ----------------------------------------------------------
    if (nrEls == 0)
    {
        m_pSA = pSA2 ;
        switch(m_varType)
        {
            case VT_I4:     EXEC(SafeArrayPutElement(m_pSA,&nrEls,&(fmtdVar.lVal)),hr) ;
                            break ;
            case VT_BOOL:   EXEC(SafeArrayPutElement(m_pSA,&nrEls,&(fmtdVar.boolVal)),hr) ;
                            break ;
            case VT_R8:     EXEC(SafeArrayPutElement(m_pSA,&nrEls,&(fmtdVar.dblVal)),hr) ;
                            break ;
            case VT_BSTR:   
                            // Deal with the special case of storing a G2Symbol
                            // in a list or array of symbols.
                            // ------------------------------------------------
                            if ((m_lawType  == g2SymbolArray || m_lawType == g2SymbolList) 
                                    && (pNewVal->vt == VT_DISPATCH || pNewVal->vt == (VT_DISPATCH | VT_BYREF)))
                            {
                                IG2Symbol   *pISym ;
                                IDispatch   *pIDsp ;
                                BSTR        symTxt ;

                                // Is it a G2Symbol?
                                // -----------------
                                pIDsp = (pNewVal->vt==VT_DISPATCH) ? pNewVal->pdispVal : *pNewVal->ppdispVal ;
                                EXEC(pIDsp->QueryInterface(IID_IG2Symbol, reinterpret_cast<void**>(&pISym)),hr) ;

                                // Get & store the text
                                // --------------------
                                hr = pISym->get_Item(&symTxt) ;
                                pISym->Release() ;
                                if (FAILED(hr))
                                    return hr ;
                                hr = SafeArrayPutElement(m_pSA, &nrEls, symTxt) ;        
                                SysFreeString(symTxt) ;
                                return hr ;
                            }
                            else
                                EXEC(SafeArrayPutElement(m_pSA,&nrEls, pNewVal->bstrVal),hr) ;
                            break ;
            case VT_VARIANT: EXEC(SafeArrayPutElement(m_pSA,&nrEls,pNewVal),hr) ;
                            break ;
            default:    return E_UNEXPECTED ;
        }
        return S_OK ;
    }

    /* If we are not dealing with a SafeArray of Variants, we will, for the   */           
    /* sake of efficiency, use memcpy to create the new SafeArray.            */
    /* ---------------------------------------------------------------------- */
    if (m_varType != VT_VARIANT)
    {
        // Point to data in both SafeArrays
        // ---------------------------------
        EXEC(::SafeArrayAccessData(m_pSA, &pFromDat), hr) ;
        EXEC(::SafeArrayAccessData(pSA2, &pToDat), hr) ;

        // Move data from before insert point to new SafeArray
        // ---------------------------------------------------
        lX = nrBefore * m_pSA->cbElements ;
        if (nrBefore > 0)
            memcpy((char*)pToDat, (char*)pFromDat, lX) ;
        pFromX = (char*)pFromDat + lX + (booNew ? 0 : m_pSA->cbElements) ;
        pToX   = (char*)pToDat + lX ;

        // Move new data into new SafeArray
        // --------------------------------
        if (booNew)
        {
            switch(m_varType)
            {
                case VT_I4:     memcpy((char*)pToX, &(fmtdVar.lVal), 4) ;
                                break ;
                case VT_BOOL:   memcpy((char*)pToX, &(fmtdVar.boolVal), 2) ;
                                break ;
                case VT_R8:     memcpy((char*)pToX, &(fmtdVar.dblVal), 8) ;
                                break ;
                case VT_BSTR:   {
                                    bool    workFromCopy = 
                                               (m_lawType  == g2SymbolArray || m_lawType == g2SymbolList) 
                                            && (pNewVal->vt == VT_DISPATCH || pNewVal->vt == (VT_DISPATCH | VT_BYREF)) ;
                                    BSTR    symTxt2 ;

                                    // If we are storing a G2Symbol in this list or array
                                    // get & work with a copy of the symbol text.
                                    // --------------------------------------------------
                                    if (workFromCopy)
                                    {
                                        IG2Symbol   *pISym ;
                                        IDispatch   *pIDsp ;

                                        // Is it a G2Symbol?
                                        // -----------------
                                        pIDsp = (pNewVal->vt==VT_DISPATCH) ? pNewVal->pdispVal : *pNewVal->ppdispVal ;
                                        EXEC(pIDsp->QueryInterface(IID_IG2Symbol, reinterpret_cast<void**>(&pISym)),hr) ;

                                        // Get the text
                                        // ------------
                                        hr = pISym->get_Item(&symTxt2) ;
                                        pISym->Release() ;
                                        if (FAILED(hr))
                                            return hr ;
                                    }
                                    else
                                        symTxt2 = pNewVal->bstrVal ;

                                    ::SafeArrayUnaccessData(pSA2) ;
                                    idx += nrBefore ;
                                    hr = ::SafeArrayPutElement(pSA2, &idx, symTxt2) ;
                                    EXEC(::SafeArrayAccessData(m_pSA, &pFromDat), hr) ;
                                    pFromX = (char*)pFromDat + (nrBefore+1)*m_pSA->cbElements ;

                                    // If we made a copy of the text, we are now done with it
                                    // ------------------------------------------------------
                                    if (workFromCopy)
                                        SysFreeString(symTxt2) ;
                                }
                                break ;
                default:    return E_UNEXPECTED ;
            }
            pToX = (char*)pToX + m_pSA->cbElements ;
        }

        // Move remaining data into new SafeArray
        // --------------------------------------
        lX = nrAfter * m_pSA->cbElements ;
        if (lX)
            memcpy((char*)pToX, (char*)pFromX, lX) ;

        // Unlock the SafeArrays
        // ---------------------
        SafeArrayUnaccessData(m_pSA) ;
        SafeArrayUnaccessData(pSA2) ;
    }
    
    /* ---------------------------------------------------------------------- */
    /*                                                                        */
    /* If we are working with a SafeArray of Variants, we cannot use memcpy   */
    /* to create the new SafeArray.  Doing so, would result in incorrect      */
    /* reference counts for the items that are embedded in the Variants.      */
    /*                                                                        */
    /* Instead, we loop through the original SafeArray, extracting the        */
    /* elements and depositing them in the new SafeArray.                     */
    /*                                                                        */
    /* ---------------------------------------------------------------------- */
    else
    {
        long            FromX=0, ToX=0 ;
        VARIANT         vX ;

        // Copy the elements before the element to be added or deleted
        // -----------------------------------------------------------
        VariantInit(&vX) ;
        for (long lX = 0; lX < (long)nrBefore ; lX++)
        {
            SafeArrayGetElement(m_pSA, &lX, &vX) ;
            SafeArrayPutElement(pSA2, &lX, &vX) ;
            VariantClear(&vX) ;
        }

        // Add the new element to the SafeArray
        // ------------------------------------
        if (booNew)
        {
            Converter::BetterVariantCopyInd(&vX, pNewVal) ;
            SafeArrayPutElement(pSA2, (long*)&nrBefore, &vX) ;
            VariantClear(&vX) ;
            FromX = nrBefore ;
            ToX = nrBefore+1 ;
        }

        // Skip over an element, thereby deleting it
        // -----------------------------------------
        else
        {
            FromX = nrBefore+1 ;
            ToX = nrBefore ;
        }

        // Copy the elements at the end
        // ----------------------------
        while (FromX < nrEls)
        {
            SafeArrayGetElement(m_pSA, &FromX, &vX) ;
            SafeArrayPutElement(pSA2, &ToX, &vX) ;
            VariantClear(&vX) ;
            FromX++ ; ToX++ ;
        }

    }

    // Point this G2ListOrArray to the new SafeArray
    // -------------------------------------
    pSAx = m_pSA ;
    m_pSA = pSA2 ;

    // Free the original SafeArray
    // ---------------------------
    ::SafeArrayDestroy(pSAx) ;

	return S_OK;
}


// -----------
// G2ComObject
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      get_WhatAmI: return string identifying this object as a G2ListOrArray         */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2ListOrArray::get_WhatAmI(BSTR *pVal)
{
	if (pVal == NULL)
		return E_POINTER;
		
    *pVal = ::SysAllocString(L"G2ListOrArray");
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/*           Create a duplicate instance of this CG2ListOrArray.              */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2ListOrArray::Duplicate(IUnknown * * pNewObj)
{
    CG2ListOrArray  *pCLaw ;
    HRESULT         hr ;
    IG2ListOrArray  *pIG2Law ;
    IUnknown        *pIUnk ;


    // Fail if the return address was not provided
    // -------------------------------------------
	if (pNewObj == NULL)
		return E_POINTER;

    *pNewObj = NULL ;  // assume failure

    // Create the new G2ListOrArray
    // ----------------------------
    hr = ::CoCreateInstance(CLSID_G2ListOrArray,NULL,CLSCTX_INPROC_SERVER,
                IID_IUnknown, reinterpret_cast<void**>(&pIUnk)) ;
    if (FAILED(hr))
        return hr ;

    // Get a pointer to the class
    // --------------------------
    hr = pIUnk->QueryInterface(IID_IG2ListOrArray, reinterpret_cast<void**>(&pIG2Law)) ;
    if (FAILED(hr))
    {
        pIUnk->Release() ;
        return hr ;
    }
    pCLaw = (CG2ListOrArray*)pIG2Law ;

    // Copy the List/Array type and the Variant Type to the new object
    // ---------------------------------------------------------------
    pCLaw->m_lawType = m_lawType ;
    pCLaw->m_varType = m_varType ;

    // Create the SafeArray that will be used by the copy
    // --------------------------------------------------
    SAFEARRAYBOUND      sab[1] ;

    long    lLBound, lUBound ;
    SafeArrayGetLBound(m_pSA,1,&lLBound) ;
    SafeArrayGetUBound(m_pSA,1,&lUBound) ;
    sab[0].cElements = lUBound-lLBound+1 ;
    sab[0].lLbound = lLBound ;
    pCLaw->m_pSA=SafeArrayCreate(m_varType,1,sab) ;
    if (!pCLaw->m_pSA)
    {
        pIUnk->Release() ;
        pIG2Law->Release() ;
        return E_OUTOFMEMORY ;
    }

    // Copy the elements of this list/array to the new list/array
    // ----------------------------------------------------------
    VARIANT vFrom, vTo ;
    VariantInit(&vFrom) ;
    VariantInit(&vTo) ;
    for (long lX = sab[0].lLbound; lX < sab[0].lLbound + (long)sab[0].cElements; lX++)
    {
        get_Item(lX, &vFrom) ;
        Converter::BetterVariantCopyInd(&vTo, &vFrom) ;
        VariantClear(&vFrom) ;
        pIG2Law->put_Item(lX, vTo) ;
        VariantClear(&vTo) ;
    }

    // Pass the new G2ListOrArray back to the caller 
    // and reduce the reference count to 1.
    // ---------------------------------------------
    *pNewObj = pIUnk ;
    pIG2Law->Release() ;
    return S_OK;
}


void CG2ListOrArray::FinalRelease()
{
    if (m_pSA)
        SafeArrayDestroy(m_pSA) ;
    ATLTRACE2 (atrG2ObjLife, 4, "##< G2ListOrArray at %08x destroyed.\n", this);
}
