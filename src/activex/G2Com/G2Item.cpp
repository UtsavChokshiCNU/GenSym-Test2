// G2Item.cpp : Implementation of CG2Item
#include "stdafx.h"
#include "Datum.h"
#include "G2Com.h"
#include "G2Item.h"
#include "g2string.h"
#include "Gateway.h"
#include "GsiContext.h"
#include "Lock.h"
#include "BConReq.h"
#include "BRPCReq.h" 
#include "NBRPCReq.h" 
#include "GsiContext.h"
#include "Subscription.h"
#include <comdef.h>
#include <math.h>


/////////////////////////////////////////////////////////////////////////////
// CG2Item

/* ========================================================================= */
/*                                                                           */
/*         I M P L E M E N T A T I O N   O F   I G 2 I t e m                 */
/*                                                                           */
/*                                                                           */
/*       - G2Item::get_ClassName   G2Item::put_ClassName                     */
/*       - G2Item::get_Name        G2Item::put_Name                          */
/*       - G2Item::get_Type        G2Item::put_Type                          */
/*       - G2Item::get_Value       G2Item::put_Value                         */
/*       - G2Item::get_Item        G2Item::put_Item                          */
/*       - G2Item::get_Count                                                 */
/*       - G2Item::get__NewEnum                                              */
/*       - G2Item::Add                                                       */
/*       - G2Item::Remove                                                    */
/*       - G2Item::AttrNames                                                 */
/*       - G2Item::AttrValues                                                */
/*       - G2Item::AttrTypes                                                 */
/*       - G2Item :Symbolize                                                 */
/*       - G2Item::Init (hidden; obsolete)                                   */
/*       - G2Item::Git (hidden; obsolete)                                    */
/*                                                                           */
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                Retrieve the class name of this item.                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_ClassName(BSTR *pClassName)
{
    ATLASSERT(pClassName != NULL);

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::get_ClassName\n");

    USES_CONVERSION ;
    TCHAR*  pCN = mp_Datum->ClassName() ;
    *pClassName = ::SysAllocString(T2OLE(pCN)) ;
    delete [] pCN ;
    return S_OK ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                   Set the class name of this item                         */
/*                                                                           */
/*   If you set it to the name of a non-existent class and then send this    */
/*   item to G2, G2 will report an error.                                    */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::put_ClassName(BSTR bstrClassName)
{
    CComBSTR    cbstrCN(bstrClassName) ;
    HRESULT     hr ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::put_ClassName\n");
    USES_CONVERSION ;
    EXEC(cbstrCN.ToUpper(),hr) ;
    mp_Datum->ClassName(OLE2T(cbstrCN.m_str)) ;
    return S_OK ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                   Retrieve the name of this item.                         */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_Name(BSTR *pObjName)
{
    ATLASSERT(pObjName != NULL);

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::get_Name\n");
    USES_CONVERSION ;
    TCHAR*  pName = mp_Datum->Name() ;
    *pObjName = ::SysAllocString(T2OLE(pName)) ;
    delete [] pName ;
    return S_OK ;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                      Set the name of this item                            */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::put_Name(BSTR bstrItemName)
{
    CComBSTR    cbstrIN(bstrItemName) ;
    HRESULT     hr ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::put_Name\n");
    USES_CONVERSION ;
    EXEC(cbstrIN.ToUpper(),hr) ;
    mp_Datum->Name(OLE2T(cbstrIN)) ;
    return S_OK ;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                 Retrieve the GSI Type of this item.                       */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_Type(G2Type *pGsiType)
{   
    ATLASSERT(pGsiType != NULL);

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::get_Type\n");
    *pGsiType = (G2Type)mp_Datum->Type() ;
    return S_OK ;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                    Set the GSI type of this item                          */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::put_Type(G2Type GsiType)
{

   // ************************** NEEDS DECISION & REWRITE ***********************

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::put_Type\n");
//    m_Data.Type(GsiType) ;
    return S_OK ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*              Retrieve the value of this item if it has one.               */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_Value(VARIANT *pVar)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::get_Value\n");
    if (NULL == pVar)
        return E_POINTER ;

    return mp_Datum->valueToVariant(pVar) ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                          Set m_Data from Var                           */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::put_Value(VARIANT Var)
{

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::put_Value\n");
    *mp_Datum << Var ;
    
    return S_OK ;
}

/* ------------------------------------------------------------------------- */
/*                   The Accessor Method for Item.                           */
/*                                                                           */
/*  Although the G2Item object is a collection of G2Attribute objects,       */
/*  get_Item returns the Value member (a VARIANT) of the indexed entry,      */
/*  not the entire G2Attribute itself.  Thus it is possible to retrieve      */
/*  the value of an attribute with a Visual Basic instruction like           */
/*                                                                           */
/*                    attrVal = G2ItemVar(index)                         .   */
/*                                                                           */
/*  The index may be either the attribute name (as a BSTR) or an integer.    */
/*  Allowing the use of an integer as an index makes it possible to          */
/*  iterate over the attributes based upon the number of entries in this     */
/*  collection, as returned by G2ItemVar.count.                              */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_Item(VARIANT varX, VARIANT *pItem)
{
    HRESULT                     hr ;
    Attribute                   *pAttribute ;
    Datum                       *pAxit ;
    long                        lX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::get_Item: ");

    /* Get a pointer to the appropriate G2Attribute Entry */
    /* -------------------------------------------------- */
    if (varX.vt == VT_UI1 || varX.vt == VT_I2 || varX.vt == VT_I4)
    {
        lX = (varX.vt==VT_I2) ? varX.iVal :
             ((varX.vt==VT_I4) ? varX.lVal : varX.uiVal );
        ATLTRACE2(atrAxlMethodCalls, 3, " (varX == %ld)\n", lX);
        EXEC(getAttrPtrWithLongIdx(lX, &pAttribute), hr);
    }
    else if (varX.vt == VT_BSTR)
    {
        ATLTRACE2(atrAxlMethodCalls, 3, " (varX == %S)\n", varX.bstrVal);
        EXEC(getAttrPtrWithStrIdx(varX.bstrVal, &pAttribute), hr);
    }
    else
    {
        ATLTRACE2 (atrAxlMsgs, 1, "** (bad index to get_Item: %d)\n", varX.vt);
        return E_INVALIDARG ;
    }

    // Now translate the value to COM
    // ------------------------------
    pAxit = pAttribute->ItemPtr() ;
    if (pAxit->IsItem())
    {
        Datum   *pCopy = new Datum ;
        *pCopy = *pAxit ;
        hr = pCopy->toVariant(pItem) ;
        delete pCopy ;
    }
    else
        hr = pAxit->toVariant(pItem) ;
    return hr ;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                     The Item Mutator Method                               */
/*                                                                           */
/*  Set the Value member of the referenced G2Attribute.  The index may be    */
/*  the attribute name (which is found in the Name member of the             */
/*  G2Attribute) or an integer index.                                        */
/*                                                                           */
/*  This method makes it possible to change the value of an attribute        */
/*  with a Visual Basic instruction such as:                                 */
/*                                                                           */
/*                    G2ItemVar(index) = valueVar                        .   */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::put_Item(VARIANT varIdx, VARIANT vItem)
{
    CComVariant                 varVal ;
    Attribute                   *pAttribute ;
    HRESULT                     hr ;
    long                        lX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::put_Item: ");

    /* Get a pointer to the appropriate G2Attribute Entry */
    /* -------------------------------------------------- */
    if (varIdx.vt == VT_UI1 || varIdx.vt == VT_I2 || varIdx.vt == VT_I4)
    {
        lX = (varIdx.vt==VT_I2) ? varIdx.iVal :
             ((varIdx.vt==VT_I4) ? varIdx.lVal : varIdx.uiVal );
        ATLTRACE2(atrAxlMethodCalls, 3, " (varIdx == %ld)\n", lX);
        hr = getAttrPtrWithLongIdx(lX, &pAttribute) ;
    }
    else if (varIdx.vt == VT_BSTR)
    {
        ATLTRACE2(atrAxlMethodCalls, 3, " (varIdx == %S)\n", varIdx.bstrVal);
        hr = getAttrPtrWithStrIdx(varIdx.bstrVal, &pAttribute) ;
    }
    else
    {
        ATLTRACE2 (atrAxlMsgs, 1, "** (bad index to put_Item: %d)\n", varIdx.vt);
        return E_INVALIDARG ;
    }

    /*              Set the attribute value               */
    /* -------------------------------------------------- */
    if (FAILED(hr))
        return hr ;

    Datum   intermediary  ;

    intermediary = vItem ;
    pAttribute->ConfiscateItem(&intermediary) ;

    return S_OK ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                  Return the number of visible attributes                  */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_Count(long *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::get_Count\n");
    *pVal = mp_Datum->NrAttrs() ;
    return S_OK;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*  Make a temp array of VARIANTS, create a G2Attribute for each attribute   */
/*  of this item, store the G2Attributes in the VARIANTS in the array, and   */
/*  then return an enumerator that can be used to cycle through the array.   */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get__NewEnum(LPUNKNOWN *pVal)
{
    Attribute*      pAttrs ;
    long            size ;   
    HRESULT         hr ;
    IG2Attribute    *pIAttr ;
    IDispatch       *pIDsp ;
    int             i ;
    VARIANT*        pVar ;

    ATLTRACE2(atrAxlMethodCalls, 3,"CG2Item::get__NewEnum\n");
    size = mp_Datum->NrAttrs() ;
    pAttrs = mp_Datum->Attributes() ;
    pVar = new VARIANT[size];

    // Make the table
    // --------------
    for(i = 0; i < size; i++)
    {
        hr = ::CoCreateInstance(CLSID_G2Attribute, NULL,CLSCTX_INPROC_SERVER,IID_IG2Attribute,
                          reinterpret_cast<void**>(&pIAttr));
        if (SUCCEEDED(hr))
        {
            pIAttr->Init((long)(pAttrs + i)) ;
            hr = pIAttr->QueryInterface(IID_IDispatch, reinterpret_cast<void**>(&pIDsp)) ;
        }
        if (FAILED(hr))
        {
            /* Release the new G2Attributes */
            /* ---------------------------- */
            for (int i2 = 0 ; i2 < i-1 ; i2++)
                pVar[i2].pdispVal->Release() ;

            /* Release the memory used by the array of VARIANTs */
            /* ------------------------------------------------ */
            delete[] pVar;

            /* Inform the caller of the problem */
            /* -------------------------------- */
            return E_UNEXPECTED ;
        }
        pVar[i].vt = VT_DISPATCH;
        pVar[i].pdispVal = pIDsp;
    }

    // Now make the enumerator
    // -----------------------
    typedef CComObject< CComEnum< IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy< VARIANT > > > enumVar;
    enumVar* pEnumVar = new enumVar;
    pEnumVar->Init(&pVar[0], &pVar[size], NULL, AtlFlagCopy);
    for (i = 0 ; i < size ; i++)
        pVar[i].pdispVal->Release() ;
    delete[] pVar;

    // return the enumerator
    // ---------------------
    return pEnumVar->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(pVal));
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*                       Add an attribute to this item.                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Add(BSTR bstrAttrName, VARIANT varAttrVal)
{
    CComBSTR    upIt(bstrAttrName) ;
    
    mp_Datum->Itemize() ;

    Attribute*  pOrgAttrs = mp_Datum->Attributes() ;
    Attribute*  pNewAttrs = NULL ;
    int         result ;
    long        nrAts = mp_Datum->NrAttrs() ;
    long        lX ;
    TCHAR*      tchNewAttrName ;
    TCHAR*      tchX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::Add\n");
    USES_CONVERSION ;
    upIt.ToUpper() ;
    tchNewAttrName = OLE2T(upIt.m_str) ;

    /* First, make sure an attribute with this name does not already exist */
    /* ------------------------------------------------------------------- */
    for (lX = 0 ; lX < nrAts ; lX++)
    {
        tchX = pOrgAttrs[lX].AttrName() ;
        result = _tcscmp(tchNewAttrName, tchX) ;
        delete [] tchX ;
        if (!result)
        {
            ATLTRACE2(atrAxlMsgs, 1, "An attribute with the name \"%s\" already exists.", T2A(tchNewAttrName)) ;
            return E_INVALIDARG ;
        }
    }

    /*  Allocate a new block of Attributes with space for the new Attribute  */
    /* --------------------------------------------------------------------- */
    pNewAttrs = new Attribute [nrAts + 1] ;
    if (!pNewAttrs)
        return E_OUTOFMEMORY ;

    /*     Copy the original Attributes to the new block, then zero the      */
    /*  original attributes so we can delete them without deleting sub-items */ 
    /* --------------------------------------------------------------------- */
    if (nrAts)
    {
        memcpy(pNewAttrs,pOrgAttrs,nrAts*sizeof(Attribute)) ;
        memset(pOrgAttrs,0,nrAts*sizeof(Attribute)) ;
    }

    /*            Fill in the values of the new Attribute                    */
    /* --------------------------------------------------------------------- */
    pNewAttrs[nrAts].FillIn(tchNewAttrName, varAttrVal) ;

    /*     Make the wrapped Datum point to the new block of Attributes       */
    /*        (This will delete the original block of attributes)            */
    /* --------------------------------------------------------------------- */
    mp_Datum->Attributes(pNewAttrs, nrAts + 1) ;

    return S_OK ;
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*   Remove an attribute from this G2Item.  The index that we use to         */
/*   select which attribute will be removed may have one of 2 types:         */
/*   1. integer/long specifying 0-based attribute number                     */
/*   2. a text string, specifying the name of the attribute                  */
/*                                                                           */
/* ------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Remove(VARIANT varIndex)
{
    Attribute*  pAttrs = mp_Datum->Attributes() ;
    Attribute*  pAttrToDel = NULL ;
    HRESULT     hr ;
    long        lNrAttrs = mp_Datum->NrAttrs() ;
    long        lDelNr ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::Remove\n");

    if (varIndex.vt == VT_UI1 || varIndex.vt == VT_I2 || varIndex.vt == VT_I4)
    {
        long    lIdx ;

        if (varIndex.vt==VT_UI1)        // VB Byte
            lIdx = (long)varIndex.bVal ;
        else if (varIndex.vt == VT_I2)  // VB Integer
            lIdx = (long)varIndex.iVal ;
        else
            lIdx = varIndex.lVal ;      // VB Long

        // Be sure we are in range.
        // -----------------------
        if(lIdx >=0 && lIdx < lNrAttrs)
        {
            // Find the correct G2Attribute
            // ---------------------------------
            hr = getAttrPtrWithLongIdx(lIdx, &pAttrToDel) ;
            lDelNr = lIdx ;
        }
        else
            return E_FAIL;
    }

    // Index is the property name
    // --------------------------
    else if (varIndex.vt == VT_BSTR)
    {
        EXEC(getAttrPtrWithStrIdx(varIndex.bstrVal, &pAttrToDel), hr);
        lDelNr = pAttrToDel - pAttrs ;
    }
    else
        // Not a valid index
        // -----------------
        return E_INVALIDARG ;


    //   Remove the specified attribute by allocation a new block of          //
    //   Attributes with one less then originally.  Copy the attributes       //
    //   we are keeping from the original block to the new block.  Set        //
    //   the Datum Attribute pointer to the new block with the Attributes     //
    //   method (which also deletes the original block and sets the           //
    //   attribute count).                                                    //
    // ---------------------------------------------------------------------- //
    Attribute   *pNewAttrs = (lNrAttrs <= 1) ? NULL : new Attribute [lNrAttrs-1] ;

    // Copy the pointers before the excluded pointer to the new array
    // --------------------------------------------------------------
    if (lDelNr && pNewAttrs)
        memcpy(pNewAttrs, pAttrs, lDelNr * sizeof(Attribute*)) ;

    // Copy the pointers after the excluded pointer to the new array
    // -------------------------------------------------------------
    if (lNrAttrs-1 > lDelNr && pNewAttrs)
        memcpy(pNewAttrs+lDelNr, pAttrs+lDelNr+1, (lNrAttrs-lDelNr-1) * sizeof(Attribute*)) ;

    // Prepare to erase the original table of Attribute pointers
    // ----------------------------------------------
    if (lNrAttrs)
        memset(pAttrs, 0, lNrAttrs * sizeof(Attribute*));

    // Update this Datum to point to the new table of Attributes
    // ---------------------------------------------------------
    mp_Datum->Attributes(pNewAttrs, (pNewAttrs ? lNrAttrs - 1 : 0)) ;

    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*               Retrieve a list of this items's attribute names              */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_AttrNames(SAFEARRAY **pNames)
{
    Attribute*      pAttrs = NULL  ;
    BSTR            bstrInter ;
    HRESULT         hr ;
    long            nrEnts = 0 ;
    long            lv ;
    TCHAR*          tchAttrName ;
    SAFEARRAYBOUND  aDim[1] ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::get_AttrNames\n");

    if (mp_Datum->Type() == dtyStructure || mp_Datum->IsItem())
    {
        pAttrs = mp_Datum->Attributes() ;
        nrEnts = mp_Datum->NrAttrs() ;
    }

    aDim[0].lLbound = 0 ;
    aDim[0].cElements = nrEnts ;
    *pNames = SafeArrayCreate(VT_BSTR, 1, aDim);
    if (*pNames == NULL)
        return E_FAIL ;

    USES_CONVERSION ;
    for (lv = 0 ; lv < nrEnts ; lv++)
    {
        tchAttrName = pAttrs[lv].AttrName() ;
        bstrInter = ::SysAllocString(T2OLE(tchAttrName)) ;       
        hr = SafeArrayPutElement(*pNames, &lv, bstrInter);
        ::SysFreeString(bstrInter) ;
        delete [] tchAttrName ;
        if (FAILED(hr))
            return hr ;
    }
    return S_OK ;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Retrieve a list of this item's attribute values                */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_AttrValues(SAFEARRAY **pValues)
{
    Attribute*      pAttrs = NULL ;
    HRESULT         hr ;
    long            nrEnts = 0 ;
    long            lv, lb ;
    SAFEARRAYBOUND  aDim[1] ;
    VARIANT         varX, varY ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::get_AttrValues\n");

    if (mp_Datum->Type() == dtyStructure || mp_Datum->IsItem())
    {
        pAttrs = mp_Datum->Attributes() ;
        nrEnts = mp_Datum->NrAttrs() ;
    }

    aDim[0].lLbound = 0 ;
    aDim[0].cElements = nrEnts ;
    *pValues = SafeArrayCreate(VT_VARIANT, 1, aDim);
    if (*pValues == NULL)
        return E_FAIL ;
    VariantInit(&varX);
    VariantInit(&varY);

    for (lv = 0, lb = 1 ; lv < nrEnts ; lv++, lb++)
    {
        if (pAttrs[lv].ItemPtr()->IsItem())
        {
            Datum   *pCopy = new Datum ;
            *pCopy = *(pAttrs[lv].ItemPtr()) ;
            hr = pCopy->toVariant(&varX) ;
            delete pCopy ;
        }
        else
            hr = pAttrs[lv].ItemPtr()->toVariant(&varX) ;
        if (FAILED(hr))
        {
            ::SafeArrayDestroy(*pValues) ;
            return hr ;
        }

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
        if (FAILED(hr))
        {
            ::SafeArrayDestroy(*pValues) ;
            return hr ;
        }
    }
    return S_OK ;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*            Retrieve a list of the types of this items's attributes         */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_AttrTypes(SAFEARRAY **pTypes)
{
    Attribute       *pAttrs = NULL ;
    HRESULT         hr ;
    long            attrType ;
    long            lv ;
    long            nrEnts = 0 ;
    SAFEARRAYBOUND  aDim[1] ;

    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::get_AttrTypes\n");
    if (mp_Datum->Type() == dtyStructure || mp_Datum->IsItem())
    {
        pAttrs = mp_Datum->Attributes() ;
        nrEnts = mp_Datum->NrAttrs() ;
    }
    aDim[0].lLbound = 0 ;
    aDim[0].cElements = nrEnts ;
    *pTypes = SafeArrayCreate(VT_I4, 1, aDim);
    if (*pTypes == NULL)
        return E_FAIL ;

    for (lv = 0 ; lv < nrEnts ; lv++)
    {
        attrType = (long)(pAttrs[lv].ItemPtr()->Type()) ;
        
        hr = SafeArrayPutElement(*pTypes, &lv, (long*)&attrType);
        if (FAILED(hr))
            return hr ;
    }
    return S_OK ; 
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                    Turn the indexed attribute into                         */
/*              a symbol (flgSym=true) or string (flgSym=false)               */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Symbolize(VARIANT idx, VARIANT_BOOL flgSym)
{
    HRESULT                     hr ;
    Attribute*                  pAttr ;
    G2Type                      atType ;
    long                        lX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::Symbolize ");

    /* Get a pointer to the appropriate Attribute */
    /* ------------------------------------------ */
    if (idx.vt == VT_UI1 || idx.vt == VT_I2 || idx.vt == VT_I4)
    {
        lX = (idx.vt==VT_I2) ? idx.iVal :
             ((idx.vt==VT_I4) ? idx.lVal : idx.uiVal );
        ATLTRACE2(atrAxlMethodCalls, 3, " (idx == %ld)\n", lX);
        EXEC(getAttrPtrWithLongIdx(lX, &pAttr), hr);
    }
    else if (idx.vt == VT_BSTR)
    {
        ATLTRACE2(atrAxlMethodCalls, 3, " (idx == %S)\n", idx.bstrVal);
        EXEC(getAttrPtrWithStrIdx(idx.bstrVal, &pAttr), hr);
    }
    else
    {
        ATLTRACE2 (atrAxlMsgs, 1, "** (bad index to get_Item: %d)\n", idx.vt);
        return E_INVALIDARG ;
    }

    atType = (G2Type)pAttr->ItemPtr()->Type() ;
    if (atType == GSI_STRING_TAG && flgSym == VARIANT_TRUE)
    {
        pAttr->Symbolize() ;
    }
    else if (atType == GSI_SYMBOL_TAG && flgSym == VARIANT_FALSE)
    {
        pAttr->Stringify() ;
    }

    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*       Previously a G2Item wrapped a gsi_item.  Now it wraps a Datum.       */
/*                        ** This method is obsolete **                       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Init(long p)
{

    ATLTRACE("*** CG2Item::Init(long pGsiItem) is obsolete! ***\n");

    return E_FAIL ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*       Previously a G2Item wrapped a gsi_item.  Now it wraps a Datum.       */
/*                        ** This method is obsolete **                       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Git(long *pGsiItem)
{
    ATLTRACE("*** CG2Item::Git(long *pGsiItem) is obsolete! ***\n");

    return E_FAIL ;
}


/* ========================================================================== */
/*                                                                            */
/*         I M P L E M E N T A T I O N   O F   I G 2 I t e m 2                */
/*                                                                            */
/*              - G2Item::Init(long p, IG2ItemRef *pIRef)                     */
/*              - G2Item::Refresh()                                           */
/*              - G2Item::Update()                                            */
/*              - G2Item::Create(LPDISPATCH pAxL)                             */
/*              - G2Item::Delete()                                            */
/*              - G2Item::get_Linked(VARIANT_BOOL *)                          */
/*              - G2Item::Link([IG2ItemRef *pRef)                             */
/*              - G2Item::Unlink()                                            */
/*              - G2Item::get_Reference                                       */
/*              - G2Item::get_AttrType(VARIANT, G2Type *)                     */
/*              - G2Item::Subscriptions(VARIANT *)                            */
/*                                                                            */
/* ========================================================================== */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Fill in a linked G2Item.  The first parameter is a gsi_item cast as a     */
/*  long.  The second is a pointer to a G2ItemRef which contains context and  */
/*  identification information.                                               */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Inix(long p, IG2ItemRef *pRef)
{

/*    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::Init(long GsiItem, IG2ItemRef *pRef)\n");
    if (!p) return E_INVALIDARG ;
    if (NULL == pRef) return E_POINTER ;


    // Insert the gsi_item in this G2Item
    // ----------------------------------
    if (m_GsiItem != NULL)
        gsi_reclaim_item(m_GsiItem) ;

    m_GsiItem = gsi_make_item() ;
    gsirtl_copy_item_or_value((gsi_item)(p), m_GsiItem, true);


    return Link(pRef) ;
*/
    return E_FAIL ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      Ask G2 to retransmit to us the item that is linked to this G2Item.    */
/*      Then use the attributes of the newly received gsi_item to update      */
/*      the attributes of this (G2Item).                                      */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Refresh()
{
	HRESULT		hr ;
        
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::Refresh\n");

     // We can't Refresh if we are not linked
    // --------------------------------------
    if (!m_linked || !mp_ctx)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    // Is the context connected?
    // -------------------------
    GsiContext *mpContext = (GsiContext*)mp_ctx ;
    if (AutoConnect(mp_ctx))
        return E_FAIL;

    // Create a one-element Datum array and store the UUID into it. 
    // -----------------------------------------------------------
	Datum	*pArgIn = new Datum [1] ;
	pArgIn[0].USV(m_compressedUUID, 8) ;
    Datum   *pUD = new Datum ;
    pUD->Long(mp_ctx) ;
    pArgIn[0].UserData(pUD) ;

    // Create the Blocking RPC Request object that tracks this Call
    // ------------------------------------------------------------
    BRPCReq *req = new BRPCReq(mpContext, _T("_G2Item_Refresh"), pArgIn, 1);
    req->usedBy(RequestObj::ContainerThread) ;

    long    lNrRetVals ;
    hr = InternalCall(req, &lNrRetVals) ;

    if (SUCCEEDED(hr))
    {
        // We should have received one return value
        // ----------------------------------------
        if (lNrRetVals == 1)
            hr = refreshWithDatum(req->RetValPtr()) ;
        else
        {
            ATLTRACE("Wrong number of arguments returned from _G2ITEM_REFRESH.\n") ;
            hr = E_UNEXPECTED ;
        }
    }

    // Inform the GSI thread that it should now delete this BRPCReq
    // ------------------------------------------------------------
    if (FAILED(hr))
        req->stateToError() ;
    else
        req->stateToProcessed() ;
    req->stopUseBy(RequestObj::ContainerThread) ;

    return hr ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  This code replaces the Datum that is wrapped by "this" with the Datum     */
/*  pointed to by pNewDatum.  This code is shared by the Create and Refresh   */
/*  methods.                                                                  */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Item::refreshWithDatum(Datum *pNewDatum)
{
    Datum       *pdtG2I ;
    HRESULT     hr = S_OK ;

    // Make sure that we got back an item of the same class as "this"
    // --------------------------------------------------------------
    if (!pNewDatum->IsItem())
        hr = E_UNEXPECTED ;
    else
    {
        TCHAR   *pLocalClassName = mp_Datum->ClassName() ;
        TCHAR   *pG2ClassName = pNewDatum->ClassName() ;
        if (_tcsicmp(pLocalClassName, pG2ClassName))
        {
            ATLTRACE("Refresh: Local & received items not of the same class.\n") ;
            hr = E_UNEXPECTED ;
        }
        delete [] pLocalClassName ;
        delete [] pG2ClassName ;
    }
    if (SUCCEEDED(hr))
    {
        // Take ownership of the Datum returned from G2
        // --------------------------------------------
        pdtG2I = new Datum ;
        if (pdtG2I)
        {
            pdtG2I->Confiscate(pNewDatum) ;
        }
        else
            hr = E_OUTOFMEMORY ;
    }
    if (FAILED(hr))
        return hr ;


    // We need to remove the UUID & FOUNDATION-CLASS attributes from the received Datum.
    // -----------------------------------------------------------------
    TCHAR   *attrsToExclude[] = { _T("UUID"), _T("FOUNDATION-CLASS") } ;
    const  int NR_ATTRS_TO_EXCLUDE = sizeof(attrsToExclude) / sizeof (TCHAR*) ;

    for (int iX = 0 ; iX < NR_ATTRS_TO_EXCLUDE ; iX++)
    {
        Attribute   *pAttr, *pFrom ;

        pAttr = pdtG2I->FindAttributeNamed(attrsToExclude[iX]) ;
        if (pAttr)
        {
            pFrom = pdtG2I->mpAttrs ;
            pdtG2I->mNrAttrs-- ;
            pdtG2I->mpAttrs = (pdtG2I->mNrAttrs > 0) ? new Attribute [pdtG2I->mNrAttrs] : NULL ;
            if (pdtG2I->mpAttrs)
                for (long lX = 0, lTo = 0 ; lX <= pdtG2I->mNrAttrs ; lX++)
                    if (pFrom+lX != pAttr)
                        pdtG2I->mpAttrs[lTo++].Confiscate(pFrom+lX) ;
            delete [] pFrom ;
        }
    }

    // Free up the old Datum & wrap the new Datum
    // ------------------------------------------
    delete mp_Datum ;
    mp_Datum = pdtG2I ;

    return hr ;
}
    
    /* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Transmit this G2Item to G2 and tell it to update the linked item        */
/*    with the value and attributes that are in this local item.              */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Update()
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::Update\n");

     // Is this G2Item linked?
    // ----------------------
    if (!m_linked || !mp_ctx)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    // Is the context connected?
    // -------------------------
    GsiContext *mpContext = (GsiContext*)mp_ctx ;
    if (AutoConnect(mp_ctx))
        return E_FAIL;

    // Create BRPCRequest to send UUID & item to G2
    // --------------------------------------------
    VARIANT *pvX  ;
    Datum    *pParams = new Datum [2] ;
	Datum	 *pUDCtx = new Datum ;
	long	lNrRetVars ;

    pParams[0].USV(m_compressedUUID, 8) ;
	pUDCtx->Long((long)mp_ctx) ;
	pParams[0].UserData(pUDCtx) ;
    copyMassagedItem(pParams+1) ;

    BRPCReq *req = new BRPCReq(mpContext, _T("_G2Item_Update"), pParams, 2);
    if (!req)
    {   
        delete [] pParams ;
        return E_FAIL;
    }

    // Create an event handle.
    // -----------------------
    if (req->prepare()) return E_FAIL ;

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    req->usedBy(RequestObj::ContainerThread) ;
    mpContext->Requests.Add(req);
    Queue.Add2(req) ;
    GsiThreadObj->wakePauseUp() ;
 
    // Wait for the return values or timeout
    // -------------------------------------
    int ret = WaitForSingleObject(req->mEventHandle, 
                            mpContext->mBlockingTimeout * 1000);
    // Release handle, we are done with it
    //  ----------------------------------
    CloseHandle(req->mEventHandle);

    
    // Check for errors
    // ----------------
    if (!ret)
    {
        // Convert the Array of Datums containing the return values to a
        // Variant containing a SafeArray of Variants.
        // --------------------------------------------------------------
        req->RetVars(&pvX, &lNrRetVars) ;


        // Check for invalid return values for value signalling error
        // ----------------------------------------------------------
        if (lNrRetVars != 1 || pvX->vt != VT_I4 || pvX->lVal != 0)
            ret = E_FAIL ;
    }

    // Inform the GSI thread that it should now delete this BRPCReq
    // ------------------------------------------------------------
    if (ret)
        req->stateToError() ;
    else
        req->stateToProcessed() ;
    req->stopUseBy(RequestObj::ContainerThread) ;

    return ret ? E_FAIL : S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      Create a copy of this item in G2.  Link this item to the new one.     */ 
/*                                                                            */
/* -------------------------------------------------------------------------- */
 STDMETHODIMP CG2Item::Create(LPDISPATCH pAxL)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::Create\n");

    // Is this G2Item linked?
    // ----------------------
    if (m_linked)
    {
        SetComError(OLESTR("Already linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x201);
    }


    // NOTE: WHENEVER THE DEFAULT INTERFACE OF G2GATEWAY IS CHANGED, THE
    //       FOLLOWING CODE MUST BE UPDATED TO REFLECT THE NEW DEFAULT.
    //       THIS IS A CONSEQUENCE OF HOW VISUAL BASIC 6 WRAPS REFERENCES
    //       TO ACTIVEX OBJECTS.
    // -------------------------------------------------------------------
    IG2Gateway4     *pIGW4 ;

    if (FAILED(pAxL->QueryInterface(IID_IG2Gateway4, (void**)&pIGW4) ) )
    {
        SetComError(OLESTR("Item passed to Create was not a G2Gateway"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x203);
    }

    mp_ctx = (long)((CG2Gateway*)pIGW4)->mpContext ;
    if (!mp_ctx)
        return E_UNEXPECTED ;

    // Is the context connected?
    // -------------------------
    if (AutoConnect(mp_ctx))
        return E_FAIL;

    // Call _G2ITEM_CREATE to create the item in G2.  The
    // return value should be the UUID of the new G2 item,
    // followed by a copy of the new item.
    // ---------------------------------------------------
    Datum*  pParams = new Datum[1] ;
    long    nrRetVals ;

    pParams[0] = *mp_Datum ;
    BRPCReq *req = new BRPCReq((GsiContext*)mp_ctx, _T("_G2ITEM_CREATE"), pParams, 1);
    req->usedBy(RequestObj::ContainerThread) ;
    HRESULT hr = InternalCall(req, &nrRetVals) ;
    delete [] pParams ;

    if (SUCCEEDED(hr))
        if (nrRetVals == 2)
        {
            // Make sure the return value is a UUID
            // ------------------------------------
            if (req->mpRetVals[0].mType != dtyUSV)
            {
                SetComError(OLESTR("Create method did not return UUID of new item"),&IID_IG2Item,L"G2Gateway.G2Item");
                hr=MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x207);
            }
            else
            {
                hr = refreshWithDatum(req->mpRetVals+1) ;
                if (SUCCEEDED(hr))
                {
                    // Store a pointer to this item in the context object
                    // --------------------------------------------------
                    if (NULL == mp_pG2Item)
                    {
                        if (mp_ctx)
                        {
                            mp_pG2Item = new G2ItemPtr ;
                            mp_pG2Item->mp_G2Item = this ;
                            ((GsiContext *)mp_ctx)->Items.Add(mp_pG2Item) ;
                        }
                    }
                    memcpy(m_compressedUUID,req->mpRetVals[0].mValue.pUsv,8*sizeof(unsigned short)) ;
                    m_Host = ((GsiContext*)mp_ctx)->Host() ;
                    m_Port = ((GsiContext*)mp_ctx) -> Port() ;
                    m_linked = true ;

                }
            }          
        }
        else
        {
            ATLTRACE("Wrong number of arguments returned from _G2ITEM_CREATE.\n") ;
            SetComError(OLESTR("Wrong number of arguments returned from _G2ITEM_CREATE."),&IID_IG2Item4,L"G2Gateway.G2Item");
            hr = MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x20A);
        }

    // Inform the GSI thread that it should now delete the BRPCReq
    // -----------------------------------------------------------
    if (SUCCEEDED(hr))
        req->stateToProcessed() ;
    else
        req->stateToError() ;
    req->stopUseBy(RequestObj::ContainerThread) ;

    // We're done
    // ----------
    return hr;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*        Tell G2 to delete the item to which this G2Item is linked.          */
/*                    Then mark this item as unlinked.                        */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Delete()
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::Delete\n") ;

     // Is this G2Item linked?
    // ----------------------
    if (!m_linked || !mp_ctx)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    // Is the context connected?
    // -------------------------
    GsiContext *mpContext = (GsiContext*)mp_ctx ;
    if (AutoConnect(mp_ctx))
        return E_FAIL;


    // Create BRPCRequest to send UUID & Class Name to G2
    // --------------------------------------------------
    Datum	*pParams = new Datum [2] ;
    Datum	*pUserData = new Datum ;
    TCHAR	*pClassName ;

    pParams[0].USV(m_compressedUUID,8) ;
    pUserData->Long((long)mp_ctx) ;
    pParams[0].UserData(pUserData) ;

    pClassName = mp_Datum->ClassName() ;
    pParams[1].Symbol(pClassName) ;
    delete [] pClassName ;

    BRPCReq *req = new BRPCReq(mpContext, _T("_G2Item_Delete"), pParams, 2);
    if (!req)
    {   
        delete [] pParams ;
        return E_FAIL;
    }

    // Create an event handle.
    // -----------------------
    if (req->prepare()) return E_FAIL ;

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    req->usedBy(RequestObj::ContainerThread) ;
    mpContext->Requests.Add(req);
    Queue.Add2(req) ;
    GsiThreadObj->wakePauseUp() ;
 
    //<Gensym-098>-replace waiting block code
    // Wait for the return values or timeout
    // -------------------------------------
    int ret = WaitForSingleObject(req->mEventHandle, 
                            mpContext->mBlockingTimeout * 1000);
    // Release handle, we are done with it
    //  ----------------------------------
    CloseHandle(req->mEventHandle);

    // Don't transform if there was an error
    // -------------------------------------
    if (!ret)
    {
        // Convert the Array of Datums containing the return values to a
        // Variant containing a SafeArray of Variants.
        // --------------------------------------------------------------
        long	lNrRetVars ;
        VARIANT	*pvX ;
        req->RetVars(&pvX, &lNrRetVars) ;

        // Unlink this G2Item from G2
        // --------------------------
        Unlink() ;

        // Check for errors
        // ----------------
        if (lNrRetVars != 1 || pvX->vt != VT_I4 || pvX->lVal != 0)
            ret = -1 ;
    }

    // Inform the GSI thread that it should now delete this BRPCReq
    // ------------------------------------------------------------
    if (ret)
        req->stateToError() ;
    else
        req->stateToProcessed() ;
    req->stopUseBy(RequestObj::ContainerThread) ;
    return  ret ? E_FAIL : S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/* Return COM Boolean indicating whether this item is linked to an item in G2 */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_Linked(VARIANT_BOOL *pflgLinked)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::get_Linked\n");
    *pflgLinked = m_linked ? VARIANT_TRUE : VARIANT_FALSE ;

    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Link this G2Item to the item in G2 that is referenced by the G2ItemRef    */ 
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Link(IG2ItemRef *pRef)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::Link\n");

    // Forget it if we are already linked
    // ----------------------------------
    if (m_linked)
    {
        SetComError(OLESTR("Already linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x201);
    }

    // Copy the UUID and context pointer into this item
    // ------------------------------------------------
    HRESULT     hr ;

    EXEC(pRef->Git(m_compressedUUID, &mp_ctx), hr) ;

    if (NULL == mp_ctx)
        return E_POINTER ;

    // Store a pointer to this item in the context object
    // --------------------------------------------------
    if (NULL == mp_pG2Item)
    {
        if (mp_ctx)
        {
            mp_pG2Item = new G2ItemPtr ;
            mp_pG2Item->mp_G2Item = this ;
            ((GsiContext *)mp_ctx)->Items.Add(mp_pG2Item) ;
        }
    }

    // Save host name and port number for future feature
    // -------------------------------------------------
    m_Port = ((GsiContext*)mp_ctx) -> Port() ;
    m_Host = ((GsiContext*)mp_ctx) -> Host() ;
    m_linked = true ;

    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*            Remove the connection from this item to a G2 item               */ 
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Unlink()
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::Unlink\n");

    // Cancel all subscriptions
    // ------------------------
    InternalUnsubscribeAll(true) ;
    
    if (m_linked && mp_ctx && mp_pG2Item)
    {
        // The following line will cause UnlinkOnly to be called
        // by the G2ItemPtr destructor.
        // -----------------------------------------------------
        ((GsiContext*)mp_ctx)->Items.Remove(mp_pG2Item) ;
        return S_OK ;
    }
    else
    {
        UnlinkOnly() ;
        return S_FALSE ;
    }
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  This function removes any reference to an item in G2, but does not cause  */
/*  the pointer to a G2ItemPtr to be removed from the Items collection in the */
/*  associated GsiContext.  It is intended to be called from the GItemPtr     */
/*  destructor and was need to prevent recursive calls to Unlink.             */
/*                                                                            */
/* -------------------------------------------------------------------------- */
void CG2Item::UnlinkOnly()
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::UnlinkOnly\n");
    m_linked = false ;
    memset(m_compressedUUID, 0, 16) ;
    mp_ctx = NULL ;
    mp_pG2Item = NULL ;
    m_Port = 0 ;
    m_Host = "" ;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*          Get the G2Type of the attribute with the specified index          */ 
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_AttrType(VARIANT idx, G2Type *pVal)
{
    HRESULT         hr ;
    Attribute       *pAttr ;
    long            lX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::get_AttrType\n");

    /* Get a pointer to the appropriate G2Attribute Entry */
    /* -------------------------------------------------- */
    if (idx.vt == VT_UI1 || idx.vt == VT_I2 || idx.vt == VT_I4)
    {
        lX = (idx.vt==VT_I2) ? idx.iVal :
             ((idx.vt==VT_I4) ? idx.lVal : idx.uiVal );
        ATLTRACE2(atrAxlMethodCalls, 3, " (idx == %ld)\n", lX);
        EXEC(getAttrPtrWithLongIdx(lX, &pAttr), hr);
    }
    else if (idx.vt == VT_BSTR)
    {
        ATLTRACE2(atrAxlMethodCalls, 3, " (idx == %S)\n", idx.bstrVal);
        EXEC(getAttrPtrWithStrIdx(idx.bstrVal, &pAttr), hr);
    }
    else
    {
        ATLTRACE2 (atrAxlMsgs, 1, "** (bad index to get_Item: %d)\n", idx.vt);
        return E_INVALIDARG ;
    }

    // Now translate the value to COM
    // ------------------------------
    *pVal = (G2Type)pAttr->ItemPtr()->Type() ;
    
    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      Request that the associated G2Gateway receive an event when the       */
/*                           specified change occurs.                         */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::SubscribeToAttributeModification(VARIANT AttrName, VARIANT userData, VARIANT *SubscripHndls)
{

    bool        parm1er = false ;
    bool        atlist = false ;
    BSTR        holdstr ;
    Datum       *pAttrNameList ;
    HRESULT     hr ;
    int         subType = stModify ;
    long        nrEls = 1;
    VARIANT     varX ;
    CComBSTR    *pAtNames ;


    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::Subscribe\n");

     // We can't Subscribe if we are not linked

    // ----------------------------------------
    if (!m_linked || !mp_ctx)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

        
    // AttrName specifies to what event we are subscribing.  If it specifies an
    // individual attribute name, then it should be a BSTR or a reference to a
    // BSTR.  If it specifies a list of attribute names then it must be an array
    // or a reference to an array of either BSTRs or VARIANTs (with each VARIANT
    // containing a BSTR).
    // -------------------------------------------------------------------------
    USES_CONVERSION ;
    VariantInit(&varX) ;

    // Process the specification of an individual event or attribute
    // -------------------------------------------------------------
    if (!(AttrName.vt & VT_ARRAY))
    {
        if (AttrName.vt == VT_BSTR)
            holdstr = AttrName.bstrVal ;
        else if (AttrName.vt == (VT_BSTR | VT_BYREF))
            holdstr = *(AttrName.pbstrVal) ;
        else
            parm1er = true ;
    }
    

    // This is where we process the list of attribute names that is passed to
    // this method as an array of BSTRs or VARIANTS
    // -----------------------------------------------------------------------
    else if (AttrName.vt == (VT_BSTR | VT_ARRAY) || 
             AttrName.vt == (VT_VARIANT | VT_ARRAY) || 
             AttrName.vt == (VT_BSTR | VT_ARRAY | VT_BYREF) ||
             AttrName.vt == (VT_VARIANT | VT_ARRAY | VT_BYREF))
    {
        SAFEARRAY   *psa ;
        UINT        nDims ;
        long        lb1, ub1 ; 

        // Determine how many attribute names are in the array
        // ---------------------------------------------------
        psa = (AttrName.vt & VT_BYREF) ? *AttrName.pparray : AttrName.parray ;
        nDims = SafeArrayGetDim(psa);
        if (nDims != 1)
            return E_INVALIDARG ;
        EXEC(SafeArrayGetLBound(psa,1,&lb1), E_UNEXPECTED) ;
        EXEC(SafeArrayGetUBound(psa,1,&ub1), E_UNEXPECTED) ;
        nrEls = ub1 - lb1 + 1 ;

        // Create an array of Datums and fill them in with the attribute
        // names.  These gsi_items will form the sequence that we send to G2.
        // ------------------------------------------------------------------
        if (nrEls > 1)
        {
            pAttrNameList = new Datum [nrEls] ;
            pAtNames = new CComBSTR[nrEls] ;

            for (long i = lb1 ; i <= ub1 ; i++)
            {
                if ((AttrName.vt & VT_TYPEMASK) == VT_VARIANT)
                {
                    ::SafeArrayGetElement(psa, &i, &varX) ;
                    if (varX.vt != VT_BSTR)
                    {
                        parm1er = true ;
                        break ;
                    }
                    holdstr = varX.bstrVal ;
                }
                else
                    ::SafeArrayGetElement(psa, &i, &holdstr) ;
                pAttrNameList[i-lb1].Symbol(OLE2T(holdstr)) ;
                pAtNames[i-lb1] = holdstr ; // makes copy (CComBSTR)
                ::SysFreeString(holdstr) ;
            }
            if (parm1er)
                delete [] pAttrNameList ;
            else
                atlist = true ;
        }

        // We deal here with the special case of receiving an array of 1 element
        // ---------------------------------------------------------------------
        else if (nrEls == 1)
        {
            if ((AttrName.vt & VT_TYPEMASK) == VT_VARIANT)
            {
                ::SafeArrayGetElement(psa, &nrEls, &varX) ;
                 if (varX.vt != VT_BSTR)
                    parm1er = true ;
                 else
                    holdstr = varX.bstrVal ;
            }
            else
                ::SafeArrayGetElement(psa, &nrEls, &holdstr) ;
            if (!parm1er)
            {
                AttrName.bstrVal = ::SysAllocString(holdstr) ;
                AttrName.vt = VT_BSTR ;
                ::SysFreeString(holdstr) ;
            }
        }
        else
            return E_INVALIDARG ;

    }

    // An empty array is an illegal argument
    // -------------------------------------
    else
        parm1er = true ;
    if (parm1er)
    {
        SetComError(OLESTR("First parameter must be \"All\", the name of an attribute, or an array of attribute names"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    // Is the context connected?
    // -------------------------
    GsiContext *mpContext = (GsiContext*)mp_ctx ;
    if (AutoConnect(mp_ctx))
        return E_FAIL;

    // Create BRPCRequest to send UUID to G2
    // -------------------------------------
    Datum   *pGits = new Datum [5] ;
    Datum	*pUD = new Datum ;

    pGits[0].USV(m_compressedUUID, 8) ;
	pUD->Long((long)(mp_ctx)) ;
	pGits[0].UserData(pUD) ;
    pGits[1].Symbol(_T("__G2COM-NOTIFY")) ;
    pGits[2].String(_T("MODIFY")) ;
	pGits[4] = userData ;

    CComBSTR    cbEvUp = AttrName.bstrVal ;

    cbEvUp.ToUpper() ;
    if (!atlist)
    {
        pGits[3].Symbol(OLE2T(cbEvUp.m_str)) ;
        pAtNames = new CComBSTR[1] ;
        pAtNames[0] = cbEvUp.m_str ;
    }
    else
        pGits[3].Sequence(pAttrNameList, nrEls) ;

    // "Call" _G2Item_Subscribe
    // ------------------------
	long	lNrRetVars ;

    BRPCReq *req = new BRPCReq(mpContext, _T("_G2Item_Subscribe"), pGits, 5);
    req->usedBy(RequestObj::ContainerThread) ;
	hr = InternalCall(req, &lNrRetVars) ;

    // If InternalCall succeeded, convert the return values
    // ----------------------------------------------------
    if (SUCCEEDED(hr))
        if (lNrRetVars == 1)
        {
            // Convert the Array of Datums containing the return values to a
            // Variant containing a SafeArray of Variants.  Release the BRPCReq.
            // -----------------------------------------------------------------
            req->mpRetVals[0].toVariant(SubscripHndls) ;
            req->stateToProcessed() ;
            req->stopUseBy(RequestObj::ContainerThread) ;
        }
        else
            hr = E_FAIL ;
  
    // We're done if there was an error
    // --------------------------------
	if (FAILED(hr))
    {
        if (nrEls > 0) delete [] pAtNames ;
        req->stateToProcessed() ;
        req->stopUseBy(RequestObj::ContainerThread) ;
        return hr;
    }

	// Verify that we received a single return value.
    // If G2 returned an error message instead of a subscription handle or list
    // of subscription handles, return the error message as part of a COM error.
    // -------------------------------------------------------------------------
    if (lNrRetVars != 1 || SubscripHndls->vt == VT_BSTR)
    {   
		if (lNrRetVars == 1)
			SetComError(OLESTR("Unexpected G2 return values"),&IID_IG2Item4,L"G2Gateway.G2Item");
		else
			SetComError(SubscripHndls->bstrVal,&IID_IG2Item4,L"G2Gateway.G2Item");
        if (nrEls > 0) delete [] pAtNames ;
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x020B);
    }

    // We need to create two Subscription items for each handle, one for the GsiContext
    // and one to store in this item's m_subscriptions container.  We cannot use the 
    // same Subscription item for each container because the Remove method deletes the
    // item and we will need to Remove from both container.
    // ---------------------------------------------------------------------------------
    bool        arraybk = (SubscripHndls->vt == (VT_VARIANT | VT_ARRAY)) ;
    bool        retvalOK = arraybk || (SubscripHndls->vt == VT_I4) ;
    long        lb2 = 0, ub2 = 0 ; // must be initialized in case this not an array
    SAFEARRAY   *psa2 = SubscripHndls->parray ;


    // If we got back an array, determine how many elements it has
    // -----------------------------------------------------------
    if (arraybk)
    {
        UINT        nDims2 = SafeArrayGetDim(psa2);

        // Determine bounds of array
        // -------------------------
        if (nDims2 != 1)
            retvalOK = false ;
        else
        {
            EXEC(SafeArrayGetLBound(psa2,1,&lb2), E_UNEXPECTED) ;
            EXEC(SafeArrayGetUBound(psa2,1,&ub2), E_UNEXPECTED) ;
        }
    }


    // For each subscription handle we have received,
    // build and store two Subscription items
    // ----------------------------------------------
    for (long iX=lb2 ; iX <= ub2 ; iX++)
    {
        if (arraybk)
        {
            ::SafeArrayGetElement(psa2, &iX, &varX) ;
            if (varX.vt != VT_I4)
            {
                retvalOK = false ;
                break ;
            }
        }
        else
            varX = *SubscripHndls ;

        Subscription    *psub1, *psub2 ;

        psub1 = new Subscription(varX.lVal, stModify, pAtNames[iX-lb2] , this) ;
        psub2 = new Subscription(varX.lVal, stModify, pAtNames[iX-lb2] , this) ;
        m_subscriptions.Add(psub1) ;
        ((GsiContext*)mp_ctx)->Subscriptions.Add(psub2) ;
    }
    if (nrEls > 0) delete [] pAtNames ;

    if (!retvalOK)
    {
        SetComError(OLESTR("Unexpected response from G2"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x205);
    }

    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      Request that the associated G2Gateway receive an event when the       */
/*                           specified change occurs.                         */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::SubscribeToDeletion(VARIANT userData, VARIANT *SubscripHndl)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::NotifyOnDelete\n");

    return CommonSubscribe(stDelete, userData, SubscripHndl) ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      Request that the associated G2Gateway receive an event when the       */
/*         a color of the icon of the associated item in G2 changes.          */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::SubscribeToIconColorChange(VARIANT userData, VARIANT *SubscripHndl)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::NotifyOnColorChange\n");

    return CommonSubscribe(stColorChg, userData, SubscripHndl) ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      Request that the associated G2Gateway receive an event when the       */
/*               the value of this parameter or value changes.                */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::SubscribeToValueChange(VARIANT userData, VARIANT *SubscripHndl)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::SubscribeToValueChange\n");

    return CommonSubscribe(stValueChg, userData, SubscripHndl) ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*          Implement most subscriptions methods in this function             */
/*                        in order to share common code                       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::CommonSubscribe(g2SubscriptionType subtyp, VARIANT userData, 
                                                          VARIANT *SubscripHndl)
{
    VARIANT     varX ;


     // We can't Subscribe if we are not linked
    // ----------------------------------------
    if (!m_linked || !mp_ctx)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    USES_CONVERSION ;
    VariantInit(&varX) ;
  
    // Is the context connected?
    // -------------------------
    GsiContext *mpContext = (GsiContext*)mp_ctx ;
    if (AutoConnect(mp_ctx))
        return E_FAIL;


    // Create BRPCRequest to send UUID to G2
    // -------------------------------------
    VARIANT vX ;
    VariantInit(&vX) ;

	Datum		*pGits = new Datum [5] ;
	Datum		*pUD = new Datum ;

	pGits[0].USV(m_compressedUUID, 8) ;
	pUD->Long((long)mp_ctx) ;
	pGits[0].UserData(pUD) ;
	pGits[1].Symbol(_T("__G2COM-NOTIFY")) ;
    pGits[4] = userData ;

    switch(subtyp)
    {
    case stDelete:      pGits[2].String(_T("DELETE")) ;
                        break ;
    case stColorChg:    pGits[2].String(_T("COLORCHANGE")) ;
                        break ;
    case stValueChg:    pGits[2].String(_T("VALUE")) ;
                        break ;
    case stSelection:   pGits[2].String(_T("SELECTION")) ;
                        break ;
    default:            return E_UNEXPECTED ;
    }
    pGits[3].Long(0) ;


    // "Call" _G2Item_Subscribe
    // ------------------------
	VARIANT	*pRetVars ;
	long	lNrRetVars ;

    BRPCReq *req = new BRPCReq(mpContext, _T("_G2Item_Subscribe"), pGits, 5);
    req->usedBy(RequestObj::ContainerThread) ;
	HRESULT hr = InternalCall(req, &pRetVars, &lNrRetVars) ; 
    if (FAILED(hr) || lNrRetVars != 1)
        return hr ;

    // If G2 returned an error message instead of a subscription handle
    // return the error message as part of a COM error.
    // ----------------------------------------------------------------
    if (pRetVars->vt == VT_BSTR)
    {
        SetComError(SubscripHndl->bstrVal,&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x0204);
    }

    // We need to create two Subscription items for each handle, one for the GsiContext
    // and one to store in this item's m_subscriptions container.  We cannot use the 
    // same Subscription item for each container because the Remove method deletes the
    // item and we will need to Remove from both container.
    // ---------------------------------------------------------------------------------
    bool        retvalOK = (pRetVars->vt == VT_I4) ;

    if (!retvalOK)
    {
        SetComError(OLESTR("Unexpected response from G2"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x205);
    }
	*SubscripHndl = *pRetVars ; // OK because pRetVars[0] is of type VT_I4
    if (SubscripHndl->lVal < 0)
    {
        SetComError(OLESTR("Subscription Failed"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x206);
    }

    // Build and store two Subscription items
    // --------------------------------------
    varX = *SubscripHndl ;

    Subscription    *psub1, *psub2 ;

    psub1 = new Subscription(varX.lVal, subtyp, NULL, this) ;
    psub2 = new Subscription(varX.lVal, subtyp, NULL, this) ;
    m_subscriptions.Add(psub1) ;
    ((GsiContext*)mp_ctx)->Subscriptions.Add(psub2) ;


    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*      Request that the associated G2Gateway receive an event when the       */
/*         a color of the icon of the associated item in G2 changes.          */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::SubscribeToCustomEvent(BSTR EventName, VARIANT UserData, VARIANT *SubscripHndl)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::NotifyOnCustomEvent\n");

    bool        parm1er = false ;
    int         subType = stCustom ;

     // We can't Subscribe if we are not linked
    // ----------------------------------------
    if (!m_linked || !mp_ctx)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    // Is the context connected?
    // -------------------------
    GsiContext *mpContext = (GsiContext*)mp_ctx ;
    if (AutoConnect(mp_ctx))
        return E_FAIL;


    // Create BRPCRequest to send subscription request to G2
    // -----------------------------------------------------
    VARIANT vX ;
    VariantInit(&vX) ;

    Datum   *pGits = new Datum[5] ;
	Datum	*pUD = new Datum ;
	pGits[0].USV(m_compressedUUID, 8) ;
	pUD->Long((long)mp_ctx) ;
	pGits[0].UserData(pUD) ;
    pGits[1].Symbol(_T("__G2COM-NOTIFY")) ;
    pGits[2].String(_T("CUSTOM")) ;

    USES_CONVERSION ;

    CComBSTR    cbEvUp = EventName ;
    cbEvUp.ToUpper() ;
    pGits[3].Symbol(OLE2T(cbEvUp.m_str)) ;

    pGits[4] = UserData ;

    // "Call" _G2Item_Subscribe
    // ------------------------
	long	lNrRetVars ;
	VARIANT	*pRetVars ;

    BRPCReq *req = new BRPCReq(mpContext, _T("_G2Item_Subscribe"), pGits, 5);
    req->usedBy(RequestObj::ContainerThread) ;
	HRESULT	hr = InternalCall(req, &pRetVars, &lNrRetVars) ;
    if (FAILED(hr) || lNrRetVars != 1)
        return E_FAIL;

    // If G2 returned an error message instead of a subscription handle or list
    // of subscription handles, return the error message as part of a COM error.
    // -------------------------------------------------------------------------
    if (pRetVars->vt == VT_BSTR)
    {
        SetComError(pRetVars->bstrVal,&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x204);
    }

    // We need to create two Subscription items for the handle, one for the GsiContext
    // and one to store in this item's m_subscriptions container.  We cannot use the 
    // same Subscription item for each container because the Remove method deletes the
    // item and we will need to Remove from both container.
    //
    // Note that with the change of architecture for AXL 8.1, the RemoveOnly method was
    // added.  We may want to rewrite this to use just one Subscription item.
    // ---------------------------------------------------------------------------------
    if (pRetVars->vt ==  VT_I4) 
    {
        *SubscripHndl = *pRetVars ;

        Subscription    *psub1, *psub2 ;

        psub1 = new Subscription(SubscripHndl->lVal, stCustom, cbEvUp.m_str, this) ;
        psub2 = new Subscription(SubscripHndl->lVal, stCustom, cbEvUp.m_str, this) ;
        m_subscriptions.Add(psub1) ;
        ((GsiContext*)mp_ctx)->Subscriptions.Add(psub2) ;
    }
    else
    {
        SetComError(OLESTR("Unexpected response from G2"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x20c);
    }

    return S_OK ;
}


// ============================================================================


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Unsubscribe to the specified event or events.  The specification may take */
/*  the form of a subscription handle, the name of an event, or an array      */
/*  containing any combination or both.                                       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::UnsubscribeFromAttributeModification(VARIANT varFromWhat)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::UnsubscribeFromAttributeModification\n");
    return InternalUnsubscribe(varFromWhat, 1, 1) ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Sometimes we only want to clean up internal records of subscriptions.     */
/*  For example, when we receive an event informing us that an item has been  */
/*  deleted, we know that G2 has removed all subscriptions for it.  We only   */
/*  need to update our local subscription records.                            */
/*                                                                            */
/*  InternalUnsubscribe lets us Unsubscribe with or without communicating the */
/*  cancelation of the subscription to G2.                                    */
/*                                                                            */
/*  "subset" specifies which subscriptions should be deleted:                 */
/*             0 - all subscriptions                                          */
/*      non-zero - type specified by subcriptionType enumeration              */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::InternalUnsubscribe(VARIANT varFromWhat, int G2Required, int subset)
{
    HRESULT hr ;
    long                *pSubHdl = NULL ;
    g2SubscriptionType  *pSubType = NULL ;
    long                nrHdls = 0;
    Subscription        *pLocal, *pTmp ;

     ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::InternalUnsubscribe(%d)\n", G2Required);

     // We must always unsubscribe before unlinking
    // ---------------------------------------------
    if (G2Required==1 && !m_linked)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    // We can't unsubscribe to anything if there are no active subscriptions
    // ---------------------------------------------------------------------
    if (m_subscriptions.Count == 0)
    {
        SetComError(OLESTR("No active subscriptions for this item"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x0208);
    }

    // Input can be the name of subscription event, a subscription
    // handle, or a list of subscription events/handle numbers.
    // Since we want to be able to inform the user which parameter
    // was incorrectly specified if there is a specification error,
    // we will break this process into two steps.  The first step
    // will validate the input and build an array of subscription
    // handles.  The second will use the array to repeatedly call
    // UnsubscribeFromOneEvent to perform the actual Unsubscribe.
    // ----------------------------------------------------------
    if (!(varFromWhat.vt & VT_ARRAY))
    {
        if (subset < 0 || subset > stSelection)
            return E_INVALIDARG ;
        else if ((subset != stModify && subset != stCustom) || 
                    ((varFromWhat.vt & VT_TYPEMASK) == VT_BSTR))
        {
            CComBSTR    wrk="" ;

            if (varFromWhat.vt == VT_BSTR)
                wrk = varFromWhat.bstrVal ;
            else if (varFromWhat.vt == (VT_BSTR | VT_BYREF))
                wrk = *(varFromWhat.pbstrVal) ;
            wrk.ToUpper() ;

            bool    foundOne = false ;

            // Step through the collection and look for Subscriptions
            // of the requested type.  Since it is possible to enter
            // the same subscription more than once, we will search
            // through the entire collection.
            // -------------------------------------------------------
            
            if (m_subscriptions.Count)
            {
                pSubHdl = new long [m_subscriptions.Count] ;
                pSubType= new g2SubscriptionType[m_subscriptions.Count] ;
                pLocal = (Subscription*)(m_subscriptions.Head);                

                while (pLocal)
                {
                    pTmp = (Subscription*)pLocal->Next ;
                    if ( subset==0 || 
                        ( pLocal->m_subscrType==subset && 
                            ((subset != stModify && subset != stCustom) || 
                             pLocal->m_attrName == wrk)))
                    {
                            pSubHdl[nrHdls] = pLocal->m_handle ;
                            pSubType[nrHdls++] = pLocal->m_subscrType ;
                    }
                    pLocal = pTmp ;
                }
            }

            // If the user specified the name of property to which
            // we are not subscribed, inform him by throwing a COM Error
            // ---------------------------------------------------------
            if (!nrHdls)
            {
                WCHAR   pMsg[65] ;

                _snwprintf(pMsg, 64, L"Not subscribed to \"%s\".", wrk.m_str) ;
                SetComError(W2OLE(pMsg),&IID_IG2Item4,L"G2Gateway.G2Item");
                if (m_subscriptions.Count)
                {
                    delete [] pSubHdl ;
                    delete [] pSubType ;
                }
                return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x0206);
            }
        }

        // If a handle number was specified, store it as the only
        // element in the array
        // ------------------------------------------------------
        else
        {
            long basType = varFromWhat.vt & VT_TYPEMASK ;
            if (basType == VT_I2 || basType == VT_I4 || basType == VT_UI1)
            {
                pSubHdl = new long[1] ;
                pSubType= new g2SubscriptionType[1] ;
                nrHdls = 1; 
                if (varFromWhat.vt == VT_UI1)
                    pSubHdl[0] = varFromWhat.uiVal ;
                else if (varFromWhat.vt == (VT_UI1 | VT_BYREF))
                    pSubHdl[0] = *varFromWhat.puiVal ;
                else if (varFromWhat.vt == VT_I2)
                    pSubHdl[0] = varFromWhat.iVal ;
                else if (varFromWhat.vt == (VT_I2 | VT_BYREF))
                    pSubHdl[0] = *varFromWhat.piVal ;
                else if (varFromWhat.vt == VT_I4)
                    pSubHdl[0] = varFromWhat.lVal ;
                else if (varFromWhat.vt == (VT_I4 | VT_BYREF))
                    pSubHdl[0] = *varFromWhat.plVal ;

                // **************** FIND TYPE ******************///
                bool    flgFound = false ;
                pLocal = (Subscription*)(m_subscriptions.Head);                

                while (pLocal)
                {
                    pTmp = (Subscription*)pLocal->Next ;
                    if ( pLocal->m_handle == pSubHdl[0] )
                    {
                        pSubType[0] = pLocal->m_subscrType ;
                        flgFound = true ;
                        break ;
                    }
                    pLocal = pTmp ;
                }
                if (!flgFound)
                {
                    delete [] pSubHdl ;
                    delete [] pSubType ;
                    return E_INVALIDARG ;
                }
            }
            else
                return E_INVALIDARG ;
        }

    }

    // Input is an array
    // -----------------
    else
    {
        long            arrayType = (varFromWhat.vt & VT_TYPEMASK) ;
        SAFEARRAY       *psa = varFromWhat.parray ;
        long            lb, ub ;
        VARIANT         vRcv ;
        unsigned char   ui1Rcv ;
        short           i2Rcv ;
        long            i4Rcv ;
        BSTR            bstrRcv ;
        bool            flgNumericType ;
        void            *pRcv = NULL ;

        // Validate the array type and prepare to retrieve elements.
        // Integer types, BSTRs, and VARIANTs are allowed.
        // --------------------------------------------------------
        if (arrayType == VT_UI1 )
            pRcv = &ui1Rcv ;
        else if (arrayType == VT_I2)
            pRcv = &i2Rcv ;
        else if (arrayType == VT_I4)
            pRcv = &i4Rcv ;
        flgNumericType = (pRcv == NULL) ? false : true ;
        if (!flgNumericType)
            if (arrayType == VT_VARIANT)
            {
                VariantInit(&vRcv) ;
                pRcv = &vRcv ;
            }
            else if (arrayType == VT_BSTR)
                pRcv = &bstrRcv ;
            else
                return E_INVALIDARG ;

            EXEC(::SafeArrayGetLBound(psa, 1, &lb), hr) ;
            EXEC(::SafeArrayGetUBound(psa, 1, &ub), hr) ;

            if (ub < lb)
                return E_INVALIDARG;
            pSubHdl = new long[m_subscriptions.Count] ;
            pSubType= new g2SubscriptionType[m_subscriptions.Count] ;


            // Loop through the elements, make sure there is a matching subscription
            // for each one, ignore it if it is a duplicate, and add it to the list
            // of handles that will be used to actually delete the subscriptions
            // ---------------------------------------------------------------------
            for (long lX = lb ; lX <= ub ; lX++)
            {
                bool        numCase ;
                long        hdl ;
                CComBSTR    cbName ;

                ::SafeArrayGetElement(psa, &lX, pRcv) ;

                if (arrayType == VT_UI1)        { numCase = true ;  hdl = ui1Rcv ;      }
                else if (arrayType == VT_I2)    { numCase = true ;  hdl = i2Rcv ;       }
                else if (arrayType == VT_I4)    { numCase = true ;  hdl = i4Rcv ;       }
                else if (arrayType == VT_BSTR)  { numCase = false ; cbName = bstrRcv ;  }
                else
                    if (vRcv.vt == VT_UI1)      { numCase = true ;  hdl = vRcv.uiVal ;  }
                    else if (vRcv.vt == VT_I2)  { numCase = true ;  hdl = vRcv.intVal ; }
                    else if (vRcv.vt == VT_I4)  { numCase = true ;  hdl = vRcv.lVal ;   }
                    else if (vRcv.vt == VT_BSTR){ numCase = false ; cbName = vRcv.bstrVal ; }
                    else 
                    {
                        delete [] pSubHdl ;
                        delete [] pSubType ;
                        return E_INVALIDARG ;
                    }

                // If we have been given a handle:
                if (numCase)
                {
                    // 1. Make sure we have a subscription with this handle
                    // ----------------------------------------------------
                    G2OrbContained *pInItem = m_subscriptions.FindObj(hdl) ;
                    if (pInItem == NULL)
                    {
                        WCHAR   pMsg[40] ;
                        _snwprintf(pMsg, 39, L"No subscription with handle %ld.", hdl) ;
                        SetComError(W2OLE(pMsg),&IID_IG2Item4,L"G2Gateway.G2Item");
                        delete [] pSubHdl ;
                        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x0209);
                    }

                    // 2. Make sure it is not already in the list for unsubscribing
                    // ------------------------------------------------------------
                    bool    flgAddIt = true ;
                    for (long l = 0; l < nrHdls ; l++)
                        if (pSubHdl[l] == hdl)
                        {
                            flgAddIt = false ;
                            break ;
                        }

                    // Add it to the list
                    // ------------------
                    if (flgAddIt)
                    {
                        pSubHdl[nrHdls] = hdl ;
                        pSubType[nrHdls++] = ((Subscription*)pInItem)->m_subscrType ;
                    }
                }   

                // We have been given the attribute or event name.
                // -----------------------------------------------
                else
                {
                    long                *pHdlList ;
                    g2SubscriptionType  *pTypList ;
                    long                lNrHdls ;

                    // Since it is possible to subscribe to the same event more than
                    // once, we need to go through the entire list of subscriptions
                    // to find every entry that should be deleted.
                    // --------------------------------------------------------------
                    cbName.ToUpper() ;
                    FindSubHdlsFor(cbName, &pHdlList, &pTypList, &lNrHdls) ;
                    if (!lNrHdls)
                    {
                        WCHAR   pMsg[65] ;

                        _snwprintf(pMsg, 64, L"Not subscribed to \"%s\".", cbName.m_str) ;
                        SetComError(W2OLE(pMsg),&IID_IG2Item4,L"G2Gateway.G2Item");
                        delete [] pHdlList ;
                        delete [] pSubHdl ;
                        delete [] pSubType ;
                        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x0207);
                    }


                    // Add each handle that is not already in the list
                    // -----------------------------------------------
                    for (long L1 = 0 ; L1 < lNrHdls ; L1++)
                    {
                        bool flgAdd2List = true ;
                        for (long L2 = 0 ; L2 < nrHdls ; L2++)
                            if (pHdlList[L1] == pSubHdl[L2])
                            {
                                flgAdd2List = false ;
                                break ;
                            }
                        if (flgAdd2List)
                            pSubHdl[nrHdls++] = pHdlList[L1] ;
                    }
                    delete [] pHdlList ;
                }
            }

    }

    // This is where we actually unsubscribe
    // -------------------------------------
    for (long lX = 0 ; lX < nrHdls ; lX++)
        UnsubscribeFromOneEvent(pSubHdl[lX], pSubType[lX], (G2Required >= 0) ) ;

    delete [] pSubHdl ;
    delete [] pSubType ;
    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Cancel all requests for item deletion notification             */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::UnsubscribeFromDeletion()
{
    VARIANT varX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::UnsubscribeFromDelete\n");
    if (m_subscriptions.Count)
    {
        VariantInit(&varX) ;
    	return InternalUnsubscribe(varX, 1, stDelete) ; //communicate with G2, deletes
    }
	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Cancel all requests for item deletion notification             */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::UnsubscribeFromIconColorChange()
{
    VARIANT varX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::UnsubscribeFromColorChange\n");
    if (m_subscriptions.Count)
    {
        VariantInit(&varX) ;
    	return InternalUnsubscribe(varX, 1, stColorChg) ;
    }
	return S_OK;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*             Cancel all requests for item deletion notification             */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::UnsubscribeFromCustomEvent(VARIANT EventName)
{
    VARIANT varX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::UnsubscribeFromCustomEvents\n");
    if (m_subscriptions.Count)
    {
        VariantInit(&varX) ;
    	return InternalUnsubscribe(EventName, 1, stCustom) ;
    }
	return S_OK;
}



/* -------------------------------------------------------------------------- */
/*                                                                            */
/*            Cancel all requests for notification of value change            */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::UnsubscribeFromValueChange()
{
    VARIANT varX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::UnsubscribeFromValueChange\n");
    if (m_subscriptions.Count)
    {
        VariantInit(&varX) ;
    	return InternalUnsubscribe(varX, 1, stValueChg) ;
    }
	return S_OK;
}
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                  Cancel all subscriptions for this item                    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::UnsubscribeFromAll()
{
    VARIANT varX ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::UnsubscribeFromAll\n");
    if (m_subscriptions.Count)
    {
        VariantInit(&varX) ;
    	return InternalUnsubscribe(varX, 1, 0) ;
    }
    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                 Cancel all subscriptions for this G2Item                   */
/*       Used internally.  Allows communication with G2 to be optional.       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Item::InternalUnsubscribeAll(bool tellG2)
{
    VARIANT varX ;

    // Cancel all subscriptions
    // ------------------------
    if (m_subscriptions.Count)
    {
        VariantInit(&varX) ;
        return InternalUnsubscribe(varX, tellG2 ? 1 : -1, 0) ;
    }
    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   This procedure is called to unsubscribe to the event for the specified   */
/*                 item with the specified subscription handle                */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Item::UnsubscribeFromOneEvent(long subHdl, g2SubscriptionType subType, bool tellG2)
{

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::UnsubscribeFromOneEvent(%ld)\n", subHdl);

    GsiContext *mpContext = (GsiContext*)mp_ctx ;

    if (tellG2)
    {
        // Is the context connected?
        // -------------------------
        if (AutoConnect(mp_ctx))
            return E_FAIL;

        // Create NBRPCRequest to send the subscription handle to G2
        // ---------------------------------------------------------
        Datum    *pSubHdl = new Datum[1] ;
        pSubHdl->Long(subHdl) ;

        NBRPCReq *req = new NBRPCReq(mpContext, ((subType == stSelection) ? 
                                                    _T("g2-ui-unregister-callback") :
                                                    _T("g2-deregister-subscription")),
                                                        pSubHdl, 1, RequestObj::Start);
        if (!req)
            return E_FAIL;

        // Start the G2 procedure
        // -----------------------
        if (req->prepare()) return E_FAIL ;  // At current time, this doesn't do anything
        Queue.Add2(req) ;
		GsiThreadObj->wakePauseUp() ;

        // The NBRPCReq::invoke method will execute this request from the GSI thread.
        // Afterwards, it will remove req from mpContext->Requests which will cause
        // req to be deleted along with the attached Datum
    }

    // We now need to remove the two subscription items we use to map among subscription
    // handles, items, and contexts.  We start with Subscription item that is stored in
    // the Subscriptions member of the context.
    // ----------------------------------------------------------------------------------
    G2OrbContained  *pInCtx = mpContext->Subscriptions.FindObj(subHdl) ;
    if (pInCtx)
        mpContext->Subscriptions.Remove(pInCtx) ;

    // Now find and remove the Subscription item for this handle that is stored in 
    // m_subscriptions collection of this item.
    // ----------------------------------------------------------------------------
    G2OrbContained  *pInItem = m_subscriptions.FindObj(subHdl) ;
    if (pInItem)
        m_subscriptions.Remove(pInItem) ;
    return S_OK ;
}

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Make a list of the subscription handles of all attribute modification    */
/*             subscriptions for the attribute named by cbName.               */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::FindSubHdlsFor(BSTR cbName, long **pHdlList, 
                                     g2SubscriptionType **pTypList, long *lNrHdls)
{
    Subscription    *pInItem = (Subscription*)m_subscriptions.Head ;

    *pHdlList = new long [m_subscriptions.Count] ;
    *lNrHdls = 0 ;

    while (pInItem)
    {
        if (pInItem->m_subscrType == stModify && pInItem->m_attrName == cbName)
            ((*pHdlList)[(*lNrHdls)++] = pInItem->m_handle) ;
        pInItem = (Subscription*)pInItem->Next ;
    }

    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  Build a G2ItemRef from the linkage information contained in this G2Item.  */
/*          If there is no linkage information, return a COM error.           */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_Reference(IG2ItemRef **pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::get_Reference\n");
    IG2ItemRef  *pLocRef ;

    // Return a COM error if not linked
    // --------------------------------
    if (!m_linked || !mp_ctx)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    HRESULT hr ;
    EXEC(::CoCreateInstance(CLSID_G2ItemRef, NULL, CLSCTX_INPROC_SERVER, IID_IG2ItemRef, (void**)&pLocRef), hr) ;
    EXEC(pLocRef->Init(m_compressedUUID, mp_ctx), hr) ;
    *pVal = pLocRef ;

    return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*       Build a 3 by x array of Variants listing current subscriptions       */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::Subscriptions(VARIANT *ArrayOfSubscriptions)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "CG2Item::Subscriptions\n");
    SAFEARRAY   *psa = NULL ;
    SAFEARRAYBOUND  aDim[2] ;

    aDim[0].lLbound = 0 ;
    aDim[0].cElements = m_subscriptions.Count ;
    aDim[1].lLbound = 0 ;
    aDim[1].cElements = 3 ;
    psa = ::SafeArrayCreate(VT_VARIANT, 2, aDim) ;
    if (!psa) return E_OUTOFMEMORY ;

    long            idx[2] = { 0, 0 } ;
    Subscription    *pInItem = (Subscription*)m_subscriptions.Head ;
    VARIANT         vX ;

    VariantInit(&vX) ;
    while (pInItem)
    {
        vX.vt = VT_I4 ;
        vX.lVal = pInItem->m_handle ;
        ::SafeArrayPutElement(psa, idx, &vX) ;
        idx[1] = 1 ;
        vX.vt = VT_I4 ;
        vX.lVal = pInItem->m_subscrType ;
        ::SafeArrayPutElement(psa, idx, &vX) ;
        idx[1] = 2 ;
        vX.vt = VT_BSTR ;
        vX.bstrVal = ::SysAllocString(pInItem->m_attrName) ;
        ::SafeArrayPutElement(psa, idx, &vX) ;
        VariantClear(&vX) ;
        idx[0]++ ;
        idx[1] = 0 ;
        pInItem = (Subscription*)pInItem->Next ;
    }

    ArrayOfSubscriptions->vt=(VT_VARIANT | VT_ARRAY) ;
    ArrayOfSubscriptions->parray = psa ;
    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// IG2Item3 Method:

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Method to generate a COM Picture object from the G2 icon of this item    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_Icon(long bkgrCor, LPDISPATCH *pVal)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::get_Icon\n");

     // Is this G2Item linked?
    // ----------------------
    if (!m_linked || !mp_ctx)
    {
        SetComError(OLESTR("Not Linked"),&IID_IG2Item4,L"G2Gateway.G2Item");
        return MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,0x202);
    }

    // Is the context connected?
    // -------------------------
    GsiContext *mpContext = (GsiContext*)mp_ctx ;
    if (AutoConnect(mp_ctx))
        return E_FAIL;

    // Create BRPCRequest to send UUID & item to G2
    // --------------------------------------------
    VARIANT vX ;
    VariantInit(&vX) ;
    Datum   *pParams = new Datum[2] ;
	Datum	*pUD = new Datum ;

    // Set UUID of item
    // ----------------
    pParams[0].USV(m_compressedUUID, 8) ;
	pUD->Long((long)mp_ctx) ;
    pParams[0].UserData(pUD) ;

    // set RGB value of background color
    // ---------------------------------
    if (bkgrCor & 0x80000000)
        bkgrCor = ::GetSysColor(bkgrCor & 0xFF) ;
    pParams[1].Long(bkgrCor) ;
    
	long	lNrRetVars = 0;
    BRPCReq *req = new BRPCReq(mpContext, _T("g2-get-icon-bitmap-for-gsi"), pParams, 2);
	HRESULT hr = InternalCall(req, &lNrRetVars) ;  // leave the return values attached to req
    if (FAILED(hr))
    {   
        req->stateToError() ;
        req->stopUseBy(RequestObj::ContainerThread) ;
        return E_FAIL;
    }

    // We should have received a binary buffer and 3 integers
    // ------------------------------------------------------
    hr = E_FAIL ;   // Will be S_OK if picture creation succeeds
	Datum			*pRetDats = req->RetValPtr() ;

    if (lNrRetVars == 4 && 
        pRetDats[0].Type() == GSI_UNSIGNED_SHORT_VECTOR_TAG  &&
        pRetDats[1].Type()  == GSI_INTEGER_TAG && 
        pRetDats[2].Type()  == GSI_INTEGER_TAG &&
        pRetDats[3].Type()  == GSI_INTEGER_TAG)
    {

        // Extract the data we will need to build the Picture
        // --------------------------------------------------
        unsigned short *pBitMap = pRetDats[0].USV() ;
        long           L = pRetDats[0].Length();
        long           x = pRetDats[1].Long() ;
        long           y = pRetDats[2].Long() ;
        long           bigEndian = pRetDats[3].Long() ;


        // Reverse the byte order if G2 is running on a big Endian machine
        // ---------------------------------------------------------------
        if (bigEndian)
            for (long j = 0 ; j < L ; j++)
            {
                unsigned short x = pBitMap[j] ;
                unsigned char  hb = (x & 0xFF00) >> 8 ;
                unsigned char  lb = (x & 0x00FF) ;

                pBitMap[j] = (lb << 8) | hb ;
            }

        // Build the BitMap
        // ----------------
        BITMAPINFO  bmi;
        HBITMAP     hbm ;
        HDC         hdc = GetDC(NULL);
        HDC         hdcMem = CreateCompatibleDC(hdc);

        ZeroMemory(&bmi, sizeof(bmi)); 
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = x;
        bmi.bmiHeader.biHeight = -y;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 24;
        bmi.bmiHeader.biCompression = BI_RGB; 

        hbm = CreateCompatibleBitmap (hdc, x, y);
        SetDIBits(hdc, hbm, 0, y, (unsigned char *)pBitMap, &bmi, DIB_RGB_COLORS);

        // Create the Picture
        // ------------------
        PICTDESC        pictDesc ;

        pictDesc.cbSizeofstruct = sizeof(pictDesc) ;
        pictDesc.picType = 1 ;  // bitmap
        pictDesc.bmp.hbitmap = hbm ;
        pictDesc.bmp.hpal = NULL ;
        hr = ::OleCreatePictureIndirect(&pictDesc, IID_IDispatch, 0, (void**)pVal) ;
        ReleaseDC(NULL,hdc) ;

    }

    // Request the deletion of req and the attached Datums
    // ---------------------------------------------------
    req->stateToProcessed() ;
    req->stopUseBy(RequestObj::ContainerThread) ;

    return hr ;

}

/////////////////////////////////////////////////////////////////////////////
// IG2ComObject Methods:

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  get_WhatAmI: return string identifying this object as a G2Item            */
/*                                                                            */
/* -------------------------------------------------------------------------- */
STDMETHODIMP CG2Item::get_WhatAmI(BSTR *WhatAmI)
{
    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::WhatAmI\n");

    if (NULL == WhatAmI)
        return E_POINTER ;
    *WhatAmI = ::SysAllocString(OLESTR("G2Item"));
    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                 Create a duplicate instance of this object.                */
/*            We deliberately do not copy the linkage information             */
/*            since Duplicate is used for making copies by value.             */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Item::Duplicate(IUnknown **pNewObj)
{
    Datum       *pCopy ;
    HRESULT     hr ;
    IG2Item4    *pNewItem = NULL ;
    IUnknown    *pIUnk = NULL ;

    ATLTRACE2(atrAxlMethodCalls, 3, "G2Item::Duplicate\n");
    *pNewObj = NULL ;   // Assume this is going to fail

    // Build the copy of "this"
    // ------------------------
    EXEC(::CoCreateInstance(CLSID_G2Item,NULL,CLSCTX_INPROC_SERVER, IID_IG2Item4, (void**)&pNewItem),hr) ;
    pCopy = new Datum ;
    *pCopy = *mp_Datum ;                // this copies the Datum
    hr = pNewItem->Init2((long)pCopy) ; // confiscate the data pointed to by pCopy
    delete pCopy ;

    // If this item is linked, we need to link the copy
    // ------------------------------------------------
    if (m_linked)
    {
        IG2ItemRef  *pItRef = NULL ;

        EXEC(get_Reference(&pItRef), hr) ;
        EXEC(pNewItem->Link(pItRef), hr) ;
        pItRef->Release() ;
    }


    // Return the IUnknown pointer required by the caller
    // -----------------------------------------------
    hr = pNewItem->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&pIUnk)) ;
    pNewItem->Release() ;
    if (SUCCEEDED(hr))
        *pNewObj = pIUnk ;
    return hr ;
}

/////////////////////////////////////////////////////////////////////////////

/* ---------------------------------------------------------------------------- */
/*                                                                              */
/*  Standard method for declaring capacity to return error info to COM clients  */
/*                                                                              */
/* ---------------------------------------------------------------------------- */
#if _MSC_VER == 1200  //VC++ 6.0

STDMETHODIMP CG2Item::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IG2Item,
        &IID_IG2Item2,
        &IID_IG2Item3,
        &IID_IG2Item4
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (::ATL::InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

#elif  _MSC_VER >= 1300  // VC++ 7 or more
STDMETHODIMP CG2Item::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IG2Item,
			&IID_IG2Item2,
			&IID_IG2Item3,
			&IID_IG2Item4
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
/*    Return the entry in the collection that is in the specified position    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Item::getAttrPtrWithLongIdx(long index, Attribute** ppAttr)
{
    long            lN = mp_Datum->NrAttrs() ;
    Attribute       *pAttrs = mp_Datum->mpAttrs ;

    // Be sure we are in range.
    // ------------------------
    if (index >= 0 && index < lN)
    {
        *ppAttr = pAttrs + index ;
        return S_OK ;
    }
    else
        return E_INVALIDARG ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                Find the attribute with the specified name                  */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Item::getAttrPtrWithStrIdx(BSTR BSTRidx, Attribute** ppAttr)
{
    Attribute       *pAttrs = NULL ;
    long            lN = 0 ;
    TCHAR           *pwkAttrName ;
    TCHAR           *ptcSought ;
    int             result ;

    if (mp_Datum->Type() == dtyStructure || mp_Datum->IsItem())
    {
        pAttrs = mp_Datum->Attributes() ;
        lN = mp_Datum->NrAttrs() ;
    }

    USES_CONVERSION ;

    ptcSought = OLE2T(BSTRidx) ;
    for (long lx = 0 ; lx < lN ; lx++)
    {
        pwkAttrName = pAttrs[lx].AttrName() ;
        result = _tcsicmp(ptcSought,pwkAttrName) ;
        delete [] pwkAttrName ;
        if (result == 0)
        {
            *ppAttr = &(pAttrs[lx]) ;
            return S_OK ;
        }
    }

    return E_INVALIDARG ;
}


/* ------------------------------------- */
/* Set new G2Item to uninitialized state */
/* ------------------------------------- */
HRESULT CG2Item::FinalConstruct()
{
    mp_Datum = new Datum ;
    mp_Datum->Itemize() ;
    m_linked   = false ;
    mp_ctx     = NULL ;
    mp_pG2Item = NULL ;
    return S_OK ;
}


/* Call Just Before Destructor */
/* --------------------------- */
void CG2Item::FinalRelease()
{
    if (m_subscriptions.Count)
       InternalUnsubscribeAll(true); 
    if (m_linked && mp_ctx)
        ((GsiContext *)mp_ctx)->Items.Remove(mp_pG2Item) ;
    if (mp_Datum)
        delete mp_Datum ;

    ATLTRACE2 (atrG2ObjLife, 4, "##< G2Item at %08x destroyed.\n", this);
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Similar to the G2Gateway's AutoConnect method, this method will cause    */
/*   the specified GsiContext object to connect to its destination if it is   */
/*   not already connected.   However, it starts with a context object, not   */
/*   a G2Gateway.                                                             */
/*                                                                            */
/* -------------------------------------------------------------------------- */
int CG2Item::AutoConnect(long pCtx)
{
    USES_CONVERSION ;
    GsiContext *mpContext = (GsiContext*)pCtx ;

    if (mpContext->mIsConnected)
        return 0;

    // Prepare the blocking connection request
    // ---------------------------------------
    CComBSTR ClassName = mpContext->ClassName();
    CComBSTR Host = mpContext->Host();
    int Port = mpContext->Port();
    CComBSTR Ris = mpContext->RemoteInitString();
    BConReq *req = new BConReq(mpContext, NULL, OLE2T(ClassName),OLE2T(Host), Port, OLE2T(Ris));
    if (!req)
    {
        return E_FAIL;
    }

    // Create the event handle used to signal completion
    // -------------------------------------------------
    if (req->prepare()) return E_FAIL ;
    mpContext->mConnReqId = req->Id() ;

    // Add it to the Queue which will cause the connection
    // request to be processed in the GSI thread.
    // ---------------------------------------------------
    req->usedBy(RequestObj::ContainerThread) ;
    mpContext->Requests.Add(req);
    Queue.Add2(req) ;
    GsiThreadObj->wakePauseUp() ;

    // Wait for the connection or timeout
    // ----------------------------------
    int ret = WaitForSingleObject(req->mEventHandle, mpContext->mBlockingTimeout*1000);
    CloseHandle(req->mEventHandle); // Release handle, we are done with it
    mpContext->mConnReqId = 0;  // cancel the request object
    mpContext->Requests.RemoveOnly(req) ;

    // Process any error or timeout, delete the request, and return
    // ------------------------------------------------------------
    if (ret)
    {
        SetComError(OLESTR("Timeout on Connect"));
    }
    else if (req->errorFlag)
    {
        SetComError(req->mErrorMessage);
        ret = -1 ;
    }

    // Inform the GSI thread that it should now delete this BConReq
    // ------------------------------------------------------------
    if (ret)
        req->stateToError() ;
    else
        req->stateToProcessed() ;
    req->stopUseBy(RequestObj::ContainerThread) ;
    return  ret ? E_FAIL : S_OK ;
}



/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Returns boolean value indicating whether or not this G2Item is of the    */
/*   same class as that of the G2Item pointed to by pOther.                   */
/*                                                                            */
/* -------------------------------------------------------------------------- */
bool CG2Item::SameClass(IG2Item4 *pOther)
{
    BSTR        myClName, otherClName ;
    bool        result ;

    USES_CONVERSION ;
    get_ClassName(&myClName) ;
    pOther->get_ClassName(&otherClName) ;
    result = G2String::bstrGleich(myClName, otherClName) ;
    ::SysFreeString(myClName) ;
    ::SysFreeString(otherClName) ;
    return result;

}


/*   Make a copy of this item and attach a G2-USER-MODE attribute */
/*   to the copied item if this is a G2Window                     */
/* -------------------------------------------------------------- */
void CG2Item::copyMassagedItem(Datum *pNewItem)
{
    *pNewItem = *mp_Datum ;

    USES_CONVERSION ;
    IG2Window   *pWin ;
    HRESULT     hr = QueryInterface(IID_IG2Window, (void**)&pWin) ;
    if (SUCCEEDED(hr))
    {
        BSTR    mode ;

        hr = pWin->get_g2UserMode(&mode) ;
        if (SUCCEEDED(hr))
        {
        
            // Create a new block of pointers to attributes leaving an extra pointer
            // for the new g2-user-mode attribute.
            // ---------------------------------------------------------------------
            long          nrAttrs = pNewItem->NrAttrs() ; 
            Attribute     *pNewAttrs = new Attribute[nrAttrs+1] ;

            // Confiscate the original set of pointers.  Then zero the original set
            // so we can delete the block of memory without deleting the Attributes.
            // --------------------------------------------------------------------
            memcpy(pNewAttrs,pNewItem->Attributes(), sizeof(Attribute*) * nrAttrs) ;
            memset(pNewItem->Attributes(),0,sizeof(Attribute*) * nrAttrs) ;
            delete [] pNewItem->Attributes() ;
            pNewItem->mpAttrs = pNewAttrs ;

            // Fill in the new g2-user-mode attribute.
            // ---------------------------------------
            pNewItem->mpAttrs[nrAttrs].AttrName(_T("G2-USER-MODE")) ;
        
            Datum *pNewItemofAttr = new Datum ;
            pNewItemofAttr->Symbol(OLE2T(mode)) ;
            pNewItem->mpAttrs[nrAttrs].ConfiscateItem(pNewItemofAttr) ;
            delete pNewItemofAttr ;
            pNewItem->mNrAttrs++ ;
            return ;
        }
    }
}

#ifdef _DEBUG
/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                           Print UUID of gsi_item                           */
/*           of type GSI_UNSIGNED_SHORT_VECTOR_TAG to debug output            */
/*                                                                            */
/* -------------------------------------------------------------------------- */
void traceUUID(gsi_item usvItem)
{
    gsi_int     itemType = gsi_type_of(usvItem) ;

    if (itemType != GSI_UNSIGNED_SHORT_VECTOR_TAG)
        return ;
    
    unsigned short  *pArray = gsi_usv_of(usvItem) ;
    gsi_int         lUUID = gsi_usv_length_of(usvItem) ;
    ATLTRACE ("UUID length = %ld\n", lUUID) ;
    for (int i = 0 ; i < 8 ; i++)
        ATLTRACE("%04X",pArray[i]) ;
    ATLTRACE("\n") ;
}
#endif

STDMETHODIMP CG2Item::Unhandle()
{
    ATLTRACE("G2Item::Unhandle is obsolete.\n") ;
    return S_OK;
}


/* ========================================================================== */
/*                                                                            */
/* For the sake of efficiency, Init2 will confiscate the Datum pointed to     */
/* pDatum.                                                                    */
/*                                                                            */
/* ========================================================================== */
STDMETHODIMP CG2Item::Init2(long pDatum)
{
    mp_Datum->Confiscate((Datum *)pDatum) ;
	return S_OK;
}

STDMETHODIMP CG2Item::Init3(long pDatum, IG2ItemRef *pRef)
{
    if (NULL == pRef) return E_POINTER ;
    mp_Datum->Confiscate((Datum *)pDatum) ;
    return Link(pRef) ;
}

STDMETHODIMP CG2Item::Git2(long *pDatum)
{
    *pDatum = (long)mp_Datum ;

	return S_OK;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/* There are two different versions of InternalCall.  This first version      */
/* performs the call on the G2 routine associated with the BRPCReq.  It       */
/* leaves the return values attached to the BRPCReq as an array of Datums.    */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Item::InternalCall(BRPCReq *req, long *pNrRetVars)
{
	// Make sure we have a valid pointer to a BRPCReq
	// ----------------------------------------------
	if (!req)
		return E_FAIL ;

    // Create an event handle.
    // -----------------------
    if (req->prepare()) return E_FAIL ;

    // Queue up the request for processing in the GSI thread
    // -----------------------------------------------------
    ((GsiContext*)mp_ctx)->Requests.Add(req);
    Queue.Add2(req) ;
	GsiThreadObj->wakePauseUp() ;

    // Wait for the return values or timeout
    // -------------------------------------
    int ret = WaitForSingleObject(req->mEventHandle, 
                            ((GsiContext*)mp_ctx)->mBlockingTimeout * 1000);
    // Release handle, we are done with it
    //  ----------------------------------
    CloseHandle(req->mEventHandle);

    // We need to hang onto the Blocking Request object to get the return
    // values.  However, we no longer need it attached to the context object.
    // ----------------------------------------------------------------------
    ((GsiContext*)mp_ctx)->Requests.RemoveOnly(req) ;
    
    // Check for errors
    // ----------------
    if (ret)
	{
        *pNrRetVars = 0 ;
		delete req ;
        return E_FAIL;
	}

    *pNrRetVars = req->NrRetVals() ;

    return S_OK ;
}


/* -------------------------------------------------------------------------- */
/*                                                                            */
/*  This version of InternalCall calls the G2 procedure associated with the   */
/*  BRPCReq, returns the values returned from the procedure to the caller as  */
/*  an array of Variants, and then requests the deletion of the BRPCReq.      */
/*                                                                            */
/* -------------------------------------------------------------------------- */
HRESULT CG2Item::InternalCall(BRPCReq *req, VARIANT **ppRetVars, long *pNrRetVars)
{
    HRESULT hr = InternalCall(req, pNrRetVars) ;

    // Convert the Array of Datums containing the return values to a
    // Variant containing a SafeArray of Variants.
    // --------------------------------------------------------------
    if (SUCCEEDED(hr))
    {
        req->RetVars(ppRetVars, pNrRetVars) ;
        req->stateToProcessed() ;
    }
    else
        req->stateToError() ;

    // Request the deletion of the BRPCReq object 
    // (which deletes the attached array of Datums)
    // --------------------------------------------
    req->stopUseBy(RequestObj::ContainerThread) ;

    return SUCCEEDED(hr) ? S_OK : E_FAIL ;
}
