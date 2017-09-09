// Converter.cpp: implementation of the Converter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Converter.h"
#include "G2Com.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Converter::Converter()
{

}


Converter::~Converter()
{

}


//============================================================================//
//                                                                            //
//     Convert the array of Datums pointed to by pRetVals to either a         //
//     Variant containing a SafeArray of Variants or, if there is just        //
//     one Datum, to the equivalent Variant.                                  //
//                                                                            //
//============================================================================//
void Converter::DatumsToArrayVarOrVar(Datum *pRetVals, long lNrRetVals, VARIANT *pOutVar)
{

    if (lNrRetVals  == 1)    
        pRetVals[0].toVariant(pOutVar) ;
    else
    {
        SAFEARRAYBOUND  sab[1] ;
        SAFEARRAY*      pSA ;
        VARIANT         varX ;

        sab[0].lLbound = 1 ;
        sab[0].cElements = lNrRetVals ;
        pSA = ::SafeArrayCreate(VT_VARIANT, 1, sab) ;
        VariantInit(&varX) ;
        VariantClear(pOutVar) ;
        if (!pSA) return ;

        long lX = 0 ;
        while (lX < lNrRetVals)
        {
            pRetVals[lX++].toVariant(&varX) ;
            HRESULT hr = ::SafeArrayPutElement(pSA, &lX, &varX) ;
            if (FAILED(hr))
                ATLTRACE("*** Failed to store element in SafeArray.\n") ;
            VariantClear(&varX) ;
        }
        pOutVar->vt =  VT_VARIANT | VT_ARRAY ;
        pOutVar->parray = pSA ;
    }
    return ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*     Convert the VARIANTs in the SafeArray pointed to by pSA to an array    */
/*     of Datums.                                                        .    */
/*                                                                            */
/* ---------------------------------------------------------------------------*/     
HRESULT Converter::SafeArrayToDatumArray(SAFEARRAY *pSA, Datum **ppDatum, long *pNrArgs)
{
    Datum   *pUnpackedArgs ;
    HRESULT hr ;
    long    lLBound ;
    long    lUBound ;
    long    nrArgs ;
    VARIANT varX ;

    // Determine the number of elements in the SafeArray
    // -------------------------------------------------
    hr = SafeArrayGetLBound(pSA, 1, &lLBound) ;
    if (FAILED(hr)) return hr ;
    hr = SafeArrayGetUBound(pSA, 1, &lUBound) ;
    if (FAILED(hr)) return hr ;
    nrArgs = lUBound - lLBound + 1 ;


    // If there are any elements in the SafeArray,
    // allocate the array of Datums.
    // -------------------------------------------
    if (nrArgs > 0)
    {
        pUnpackedArgs = new Datum[nrArgs] ;
        if (!pUnpackedArgs)
            return E_OUTOFMEMORY ;

        // Convert the Variants to Datums in this loop
        // -------------------------------------------
        for (long lX = lLBound ; lX <= lUBound ; lX++)
        {
            hr = ::SafeArrayGetElement(pSA, &lX, &varX) ;
            if (FAILED(hr))
            {
                delete [] pUnpackedArgs ;
                return hr ;
            }
            pUnpackedArgs[lX-lLBound] = varX ;
            VariantClear(&varX) ;
        }
        // Return the number of elements and the pointer
        // to the array of Datums to the caller.
        // ---------------------------------------------
        *ppDatum = pUnpackedArgs ;
        *pNrArgs = nrArgs ;
    }

    // Set the pointer to the array of Datums to NULL if 
    // there are not any elements in the SafeArray.
    // -------------------------------------------------
    else
    {
        *ppDatum = NULL ;
        *pNrArgs = 0 ;
    }
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/*  When VariantCopyInd is used to copy a VARIANT of type VT_DISPATCH or      */
/*  VT_UNKNOWN, it copies the pointer to the object, not the object itself.   */
/*  Generally, when the object pointed to is a G2ComObject, we need a copy    */
/*  of the object.                                                            */
/*                                                                            */
/*  BetterVariantCopyInd is used by G2StructureEntry::put_Value to provide us */
/*  with the required behavior.                                               */
/*                                                                            */
/* ========================================================================== */
HRESULT Converter::BetterVariantCopyInd(VARIANT *pvDst, VARIANT *pvSrc)
{
    HRESULT         hr ;
    IDispatch*      pIDsp ;
    G2ComObject*    pG2ComObj ;
    IUnknown*       pIUnk ;
    IUnknown*       pIUnk2 ;
    unsigned short  vttype ;
    VARIANT         *pvFrom ;

    // If the source is a pointer to a Variant, dereference it
    // -------------------------------------------------------
    pvFrom = (pvSrc->vt == (VT_VARIANT | VT_BYREF)) ? pvSrc->pvarVal : pvSrc ; 

    // We can use VariantCopyInd to perform the copy as long as
    // we are not dealing with an array of Variants or a pointer
    // to an IDispatch or IUnknown
    // ---------------------------------------------------------
    vttype = pvFrom->vt & VT_TYPEMASK;
    if (vttype != VT_VARIANT && vttype != VT_DISPATCH && vttype != VT_UNKNOWN)
        return VariantCopyInd(pvDst, pvSrc) ;


    // First, let's deal with the case where the source Variant wraps a
    // pointer to another Variant.  Use recursion to copy the pointed-to
    // Variant to the destination.
    // -----------------------------------------------------------------
    if (pvFrom->vt == (VT_VARIANT | VT_BYREF))
        return Converter::BetterVariantCopyInd(pvDst, pvFrom->pvarVal) ;  

    // The other non-array case of interest is when the Variant wraps
    // a pointer (or a pointer to a pointer) to an IDispatch or IUnknown.
    // This is section of code that does something functionally different
    // than VariantCopyInd.
    // It will get the G2ComObject pointer for the object, call its
    // duplicate method, and put the pointer to the new object in the
    // destination Variant.  (VariantCopyInd just copies the interface
    // pointer and updates the original object's reference count.)
    // ----------------------------------------------------------------
    if ((pvFrom->vt & VT_ARRAY)==0)
    {
        if (vttype == VT_DISPATCH)
        {
            pIDsp = (pvFrom->vt & VT_BYREF) ? *pvFrom->ppdispVal : pvFrom->pdispVal ;
            hr = pIDsp->QueryInterface(IID_G2ComObject, reinterpret_cast<void**>(&pG2ComObj)) ;
            if (FAILED(hr))
            {
                ATLTRACE("** Pointed-to IDispatch is not a G2ComObject!\n") ;
                return VariantCopyInd(pvDst, pvSrc) ;
            }
        }
        else
        {
            pIUnk = (pvFrom->vt & VT_BYREF) ? *pvFrom->ppunkVal : pvFrom->punkVal ;
            hr = pIUnk->QueryInterface(IID_G2ComObject, reinterpret_cast<void**>(&pG2ComObj)) ;
            if (FAILED(hr))
            {
                ATLTRACE("** Pointed-to IUnknown is not a G2ComObject!\n") ;
                return VariantCopyInd(pvDst, pvSrc) ;
            }
        }
        hr = pG2ComObj->Duplicate(&pIUnk2) ;
        pG2ComObj->Release() ;
        if (FAILED(hr))
        {
            ATLTRACE("** G2ComObject.Duplicate() Failed!\n") ;
            return VariantCopyInd(pvDst, pvSrc) ;
        }

        pvDst->vt = vttype ;  
        if (vttype == VT_UNKNOWN)
            pvDst->punkVal = pIUnk2 ;  
        else
        {
            hr = pIUnk2->QueryInterface(IID_IDispatch,reinterpret_cast<void**>(&pIDsp)) ;
            pIUnk2->Release() ;
            if (FAILED(hr))
            {
                ATLTRACE("** G2ComObject.Duplicate type mismatch!\n") ;
                return VariantCopyInd(pvDst, pvSrc) ;
            }
            pvDst->pdispVal = pIDsp ;  
        }
        return S_OK ;
    }


    // If we get here, we are dealing with a wrapped SafeArray of Variants,
    // IDispatch pointers or IUnknown pointers (direct or indirect).
    // We will copy the source SafeArray to a destination SafeArray,
    // dereferencing the references, if necessary.  The first step is to
    // determine the size of the source SafeArray.
    // ---------------------------------------------------------------------
    SAFEARRAY       *pSA = (pvFrom->vt & VT_BYREF) ? *pvFrom->pparray : pvFrom->parray ;
    long            lDims = SafeArrayGetDim(pSA) ;
    long            lLBound ;
    long            lUBound ;
    long            nrArgs ;
    long            lX, lY ;
    SAFEARRAYBOUND  *pSAb = new SAFEARRAYBOUND[lDims];
    SAFEARRAY       *pSAOut = NULL ;

    for (lY = 0 ; lY < lDims ; lY++)
    {
        hr = SafeArrayGetLBound(pSA, 1, &lLBound) ;
        if (FAILED(hr)) return hr ;
        hr = SafeArrayGetUBound(pSA, 1, &lUBound) ;
        if (FAILED(hr)) return hr ;
        nrArgs = lUBound - lLBound + 1 ;
        pSAb[lY].cElements = nrArgs ;
        pSAb[lY].lLbound = lLBound ;
    }
    pSAOut = SafeArrayCreate(vttype, lDims, pSAb) ;
    if (!pSAOut)
    {
        ATLTRACE("** Failed to copy sequence\n") ;
        return VariantCopyInd(pvDst, pvSrc) ;
    }
    pvDst->vt = (vttype | VT_ARRAY) ; 
    pvDst->parray = pSAOut ;           
    
    // Copy each element from the source SafeArray to the destination
    // --------------------------------------------------------------
    VARIANT         vX, vY, *pvX ;
    IDispatch       *pIDspSA ;
    IUnknown        *pIUnkSA ;
    long            *indices = new long [lDims] ;

    // Initialize to step through indices
    // ----------------------------------
    bool    done = false ;
    VariantInit(&vX) ;
    VariantInit(&vY) ;
    for (long iX = 0 ; iX < lDims ; iX++)
    {
        indices[iX] = pSAb[iX].lLbound ;
        if (pSAb[iX].cElements <= 0)
            done = true ;
    }

    // Loop through the elements of the source array,
    // copying them to the destination
    // ----------------------------------------------
    while (!done)
    {
        switch(vttype)
        {
            case VT_VARIANT:                
                                SafeArrayGetElement(pSA, indices, &vX) ;
                                pvX = &vX ;
                                BetterVariantCopyInd(&vY, pvX) ; 
                                hr = SafeArrayPutElement(pSAOut, indices, &vY) ;
                                break ;
            case VT_DISPATCH:
                                SafeArrayGetElement(pSA, indices, &pIDspSA) ;
                                vX.vt = VT_DISPATCH ;
                                vX.pdispVal = pIDspSA ;
                                BetterVariantCopyInd(&vY, &vX) ;
                                hr = SafeArrayPutElement(pSAOut, indices, vY.pdispVal) ;
                                break ;
            case VT_UNKNOWN:
                                SafeArrayGetElement(pSA, indices, &pIUnkSA) ;
                                vX.vt = VT_UNKNOWN ;
                                vX.punkVal = pIUnkSA ;
                                BetterVariantCopyInd(&vY, &vX) ;
                                hr = SafeArrayPutElement(pSAOut, indices, vY.punkVal) ;
                                break ;
        }
        VariantClear(&vX) ;
        VariantClear(&vY) ;

        // Update indices
        // --------------
        for (lX=0; lX < lDims; lX++)
            if (indices[lX] == pSAb[lX].lLbound + (long)pSAb[lX].cElements - 1)
            {
                indices[lX] = pSAb[lX].lLbound ;
            }
            else
            {
                indices[lX]++ ;
                break ;
            }
        if (lX == lDims)
            done = true ;
    }         
    
    
    delete [] pSAb ;
    delete [] indices ;
    return S_OK ;
}
