//============================================================================//
//                                                                            //
//     A Datum object is a generic data object.  It can hold the same         //
//     information as a gsi_item.  However, it can be accessed and            //
//     modified without calling GSI routines.                                 //
//                                                                            //
//     GSI was written is Lisp and cannot be accessed safely from multiple    //
//     threads.  This class was written to serve as an intermediate data      //
/*     wrapper for applications that use GSI and multiple threads.            */
//                                                                            //
//============================================================================//

#include "stdafx.h"
#include "Datum.h"
#include "gsi_main.h"
#include "G2Com.h"
#include "G2Structure.h"
#include "GsiContext.h"

const long TYPE_MISMATCH = -1 ;
const long BAD_PARAMETER = -2 ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//============================================================================//
//                                                                            //
//                      New Datums are set to type NULL                       //
//                                                                            //
//============================================================================//
Datum::Datum()
{
    memset(this, 0, sizeof(Datum)) ;   
}


//============================================================================//
//                                                                            //
// Free any memory that was dynamically allocated before deleting this Datum  //
//                                                                            //
//============================================================================//
Datum::~Datum()
{
    Zap() ;
}



/* ===========================================================================*/
/*                                                                            */
/*  If this Datum is not a G2Item then this method will call valueToVariant   */
/*  to create the equivalent Variant.  Otherwise you will find most of the    */
/*  code to convert this Datum to a G2Item-containing Variant in this method. */
/*                                                                            */
/* ===========================================================================*/
HRESULT Datum::toVariant(VARIANT *pVar)
{

    ATLTRACE2(atrAxlMethodCalls, 3, "Datum::toVariant\n");

    USES_CONVERSION ;

    // Release any memory or interfaces used by *pVar
    // ----------------------------------------------
    VariantClear(pVar) ;

    // If this is not a G2 Item, let valueToVariant perform the conversion
    // -------------------------------------------------------------------
    if (!IsItem())
        return valueToVariant(pVar) ;

    // This is a G2 item.
    // ------------------
    Attribute   *pAttr ;
    Attribute   *pFrom ;
    bool        flgWkspc = false, flgWin = false ;


    // Determine if it is a workspace or window, then 
    // delete the foundation-class attribute.
    // ----------------------------------------------------------
    pAttr = FindAttributeNamed(_T("FOUNDATION-CLASS")) ;
    if (pAttr)
    {
        Datum*  pAttrItem = pAttr->ItemPtr() ;

        if (pAttrItem->Type() == dtySymbol)
        {
            TCHAR*  pFC = pAttrItem->Symbol() ;

            flgWkspc = !_tcscmp(pFC, _T("KB-WORKSPACE")) ;
            flgWin   = !_tcscmp(pFC, _T("G2-WINDOW")) ;
            delete [] pFC ;

            // If there is a foundation-class attribute, remove it as it should not be
            // visible from the Variant of type G2Item.
            // -----------------------------------------------------------------------
            pFrom = mpAttrs ;
            --mNrAttrs ;
            mpAttrs = (mNrAttrs > 0) ? new Attribute [mNrAttrs] : NULL ;
            if (mpAttrs)
                for (long lX = 0, lTo = 0 ; lX <= mNrAttrs ; lX++)
                    if (pFrom+lX != pAttr)
                        mpAttrs[lTo++].Confiscate(pFrom+lX) ;
            delete [] pFrom ;
        }
    } 

    //   Create the top-level COM item and get its IG2Item4 pointer.
    // -------------------------------------------------------------
    IDispatch       *pIDsp = NULL ;
    IG2Item4        *pIG2Item4 ;
    IG2ItemRef      *pRef ;
    IG2Window       *pIG2Win ;
    IG2Workspace    *pIG2Wkspc ;
    HRESULT         hr ;

    // The top level item will be a G2Window, a G2Workspace, or a G2Item
    // depending upon the type of this Datum.  The processing of each of these
    // types is pretty much the same except that Windows require an additional
    // attribute, USER-MODE.
    // -----------------------------------------------------------------------
    if (flgWkspc)
    {
        hr = CoCreateInstance(CLSID_G2Workspace,NULL,CLSCTX_INPROC_SERVER,IID_IG2Workspace,(void**)&pIG2Wkspc) ;
        if (FAILED(hr)) return hr ;
        hr = pIG2Wkspc->QueryInterface(IID_IG2Item4, reinterpret_cast<void**>(&pIG2Item4));
        pIG2Wkspc->Release() ;
        if (FAILED(hr)) return hr ;
    }

    // This is where we handle the special requirements of G2 Windows
    // --------------------------------------------------------------
    else if (flgWin)
    {
        hr = CoCreateInstance(CLSID_G2Window,NULL,CLSCTX_INPROC_SERVER,IID_IG2Window,(void**)&pIG2Win) ;
        if (FAILED(hr)) return hr ;
        hr = pIG2Win->QueryInterface(IID_IG2Item4, reinterpret_cast<void**>(&pIG2Item4));
        if (FAILED(hr))
        {
            pIG2Win->Release() ;
            return hr ;
        }
        Attribute *pUM = FindAttributeNamed(_T("G2-USER-MODE")) ;
        if (pUM)
        {
            Datum *pUMItem = pUM->ItemPtr() ;
            if (pUMItem->Type() == dtySymbol)
            {
                TCHAR*  tchUserMode = pUMItem->Symbol() ;
                BSTR    bstrUM = ::SysAllocString(T2OLE(tchUserMode)) ;
                pIG2Win->put_g2UserMode(bstrUM) ;
                ::SysFreeString(bstrUM) ;
                delete [] tchUserMode ;
                pIG2Win->Release() ;

                // We do not want the G2-USER-MODE attribute to be in the Datum
                // that is about to be wrapped by a G2Item.  We now remove this
                // attribute from this Datum.  This assumes that we will not need
                // the G2-USER-MODE attribute of the Datum again.
                // --------------------------------------------------------------
                pFrom = mpAttrs ;
                --mNrAttrs ;
                mpAttrs = (mNrAttrs > 0) ? new Attribute [mNrAttrs] : NULL ;
                if (mpAttrs)
                    for (long lX = 0, lTo = 0 ; lX <= mNrAttrs ; lX++)
                        if (pFrom+lX != pUM)
                            mpAttrs[lTo++].Confiscate(pFrom+lX) ;
                delete [] pFrom ;

            }
        }
    }

    // Create an empty G2Item object
    // -----------------------------
    else
    {
        hr = CoCreateInstance(CLSID_G2Item,NULL,CLSCTX_INPROC_SERVER,IID_IG2Item4,(void**)&pIG2Item4) ;
        if (FAILED(hr)) return hr ;
    }

    // Save its IDispatch pointer for later
    // ------------------------------------
    hr = pIG2Item4->QueryInterface(IID_IDispatch, (void**)&pIDsp) ;
    if (FAILED(hr))
    {
        pIG2Item4->Release() ;
        return hr ;
    }


    // If the UUID is present, we are going to want to link this item to the local copy
    // --------------------------------------------------------------------------------
    Attribute*  pUuidAttr ;
    pUuidAttr = FindAttributeNamed(_T("UUID")) ;

    if (pUuidAttr && pUuidAttr->ItemPtr()->Type() == dtyUSV)
    {
        Datum*          pUuidItem = pUuidAttr->ItemPtr() ;
        unsigned short  *pUuid = pUuidItem->USV() ;

        hr = CoCreateInstance(CLSID_G2ItemRef,NULL,CLSCTX_INPROC_SERVER,
                    IID_IG2ItemRef, reinterpret_cast<void**>(&pRef)) ;
        if (FAILED(hr)) goto releaseItem ;
        hr =pRef->Init(pUuid, (long)mpCtx) ;
        if (FAILED(hr)) goto releaseAll ;

        // Remove the UUID attribute from this Datum.  It should not be one
        // of the attributes of the Variant of type G2Item.
        // ----------------------------------------------------------------
       pFrom = mpAttrs ;
        --mNrAttrs ;
        mpAttrs = (mNrAttrs > 0) ? new Attribute [mNrAttrs] : NULL ;
        if (mpAttrs)
            for (long lX = 0, lTo = 0 ; lX <= mNrAttrs ; lX++)
                if (pFrom+lX != pUuidAttr)
                    mpAttrs[lTo++].Confiscate(pFrom+lX) ;
        delete [] pFrom ;

        // Wrap this Datum and its linkage info with a G2Item
        // --------------------------------------------------
        hr = pIG2Item4->Init3((long)this, pRef) ;
releaseAll: 
        pRef->Release() ;
releaseItem:
        pIG2Item4->Release() ;      // we still have pIDsp
        delete [] pUuid ;
    }

    // If the UUID is not present, just wrap this Datum in a G2Item
    // ------------------------------------------------------------
    else
    {
        hr = pIG2Item4->Init2((long)this) ; ;
        pIG2Item4->Release() ;       // we still have pIDsp
    }
    // Check for failure of Init
    // -------------------------
    if (FAILED(hr))
    {
        pIDsp->Release() ;
        return hr ;
    }

    // Pack the G2Item into the Variant
    // --------------------------------
    pVar->vt = VT_DISPATCH ;
    pVar->pdispVal = pIDsp ;

    return S_OK ;
}



/*============================================================================*/
/*                                                                            */
/*   This method is used both by G2Item::get_Value and by the toVariant       */
/*   method of Datum when the Datum is not a G2 item to create a Variant      */
/*   that is equivalent to this Datum.                                        */
/*                                                                            */
/*============================================================================*/
HRESULT Datum::valueToVariant(VARIANT *pVar)
{
    BSTR            bstrX ;
    HRESULT         hr ;
    IG2ItemRef      *pIG2ItRef ;
    IG2ListOrArray  *pILaw ;
    IG2Structure    *pIG2Struct ;
    IG2Symbol       *pIG2Sym ;
    long            lX ;
    VARIANT         var;

    USES_CONVERSION ;

    switch(mType)
    {
        case dtyNull:           pVar->vt = VT_NULL ;
                                break ;
        case dtyInteger:        pVar->vt = VT_I4 ;
                                pVar->lVal = mValue.lngVal ;
                                break ;
        case dtySymbol:         if (mG2Sym)
                                {
                                    hr = ::CoCreateInstance(CLSID_G2Symbol,NULL,CLSCTX_INPROC_SERVER,
                                                IID_IG2Symbol,reinterpret_cast<void**>(&pIG2Sym)) ;
                                    if (FAILED(hr)) return hr ;
                                    hr = pIG2Sym->put_UpperCase(VARIANT_FALSE) ;
                                    if (FAILED(hr)) goto SymFailed ;
                                    bstrX = ::SysAllocString(mValue.pString ? T2OLE(mValue.pString) : OLESTR("")) ;
                                    hr = pIG2Sym->put_Item(bstrX) ;
                                    ::SysFreeString(bstrX) ;
                                    if (FAILED(hr)) goto SymFailed ;
                                    hr = pIG2Sym->QueryInterface(IID_IDispatch, reinterpret_cast<void**>(&(pVar->pdispVal))) ;
SymFailed:                          pIG2Sym->Release() ;
                                    if (FAILED(hr)) return hr ;
                                    pVar->vt = VT_DISPATCH ;
                                }
                                else
                                {
                                    pVar->bstrVal = ::SysAllocString(mValue.pString ? T2OLE(mValue.pString) : OLESTR("")) ;
                                    pVar->vt = VT_BSTR ;
                                }
                                break ;
        case dtyString:         pVar->bstrVal = ::SysAllocString(mValue.pString ? T2OLE(mValue.pString) : OLESTR("")) ;
                                if (!pVar->bstrVal) return E_FAIL ;
                                pVar->vt = VT_BSTR ;
                                break ;
        case dtyLogical:        pVar->vt = VT_BOOL ;
                                pVar->boolVal = (mValue.lngVal < 0) ? VARIANT_FALSE : VARIANT_TRUE ;
                                break ;
        case dtyFloat:          pVar->vt = VT_R8 ;
                                pVar->dblVal = mValue.dblVal ;
                                break ;
        case dtyItem:           ATLTRACE("Conversion from gsi_item/type Item to Variant not supported.\n") ;
                                return E_FAIL ;
        case dtyValue:          ATLTRACE("Conversion from gsi_item/type Value to Variant not supported.\n") ;
                                return E_FAIL ;
        case dtyHandle:         ATLTRACE("Conversion from gsi_item/type Handle to Variant not supported.\n") ;
                                return E_FAIL ;
        case dtyQuantity:       ATLTRACE("Conversion from gsi_item/type Quantity to Variant not supported.\n") ;
                                return E_FAIL ;
        case dtyUSV:            hr = ::CoCreateInstance(CLSID_G2ItemRef,NULL, CLSCTX_INPROC_SERVER, IID_IG2ItemRef,
                                            reinterpret_cast<void**>(&pIG2ItRef)) ;
                                if (FAILED(hr)) return hr ;
                                hr = pIG2ItRef->Init(mValue.pUsv,mpCtx) ;
                                if (SUCCEEDED(hr))
                                    hr = pIG2ItRef->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&(pVar->punkVal))) ;
                                pIG2ItRef->Release() ;
                                if (FAILED(hr)) return hr ;
                                pVar->vt = VT_UNKNOWN ;
                                break ;
        case dtyIntegerArray:
        case dtySymbolArray:
        case dtyStringArray:
        case dtyLogicalArray:
        case dtyFloatArray:
        case dtyItemArray:
        case dtyValueArray:
        case dtyItemOrValArray:
        case dtyQuantityArray:
        case dtyIntegerList:
        case dtySymbolList:
        case dtyStringList:
        case dtyLogicalList:
        case dtyFloatList:
        case dtyItemList:
        case dtyValueList:
        case dtyItemOrValList:
        case dtyQuantityList:   hr = ::CoCreateInstance(CLSID_G2ListOrArray,NULL,CLSCTX_INPROC_SERVER, 
                                        IID_IG2ListOrArray, reinterpret_cast<void**>(&pILaw)) ;
                                if (FAILED(hr)) return hr ;
                                hr = pILaw->Init((long)this) ;           
                                if (FAILED(hr))  goto LawFailed ;
                                hr = pILaw->QueryInterface(IID_IDispatch, reinterpret_cast<void**>(&(pVar->pdispVal))) ;
LawFailed:                      pILaw->Release() ;
                                if (FAILED(hr)) return hr ;
                                pVar->vt = VT_DISPATCH ;
                                break ;
        case dtySequence:       {
                                    SAFEARRAY       *pSA;
                                    SAFEARRAYBOUND  ab[1];

                                    ab[0].lLbound = 0 ;
                                    ab[0].cElements = mLength;
                                    pSA = SafeArrayCreate(VT_VARIANT, 1, ab);  // Make array
                                    if (!pSA) return E_FAIL ;

                                    VariantInit(&var);

                                    for (lX = 0; lX < mLength; lX++)
                                    {
                                        mValue.pElements[lX].toVariant(&var) ;
                                        hr = SafeArrayPutElement(pSA, &lX, &var);

                                        // since SafeArrayPutElement copies the variant, we must
                                        // clear this temporary copy to avoid a memory leak.
                                        // -----------------------------------------------------
                                        VariantClear(&var);
                                    }
                                    pVar->parray = pSA ;
                                    pVar->vt = (VT_ARRAY | VT_VARIANT) ;
                                    break ;
                                }
        case dtyStructure:      {

                                    //  If this is a structure mapped to a special COM type such
                                    //  as Currency or Date, process it in legacyStructure.
                                    //  ---------------------------------------------------------
                                    if (legacyStructure(pVar))
                                        break ;

                                    //  ============================================
                                    //  Return the structure as a G2Structure object
                                    //  ============================================
                                    IG2StructureEntry   *pIG2SE ;

                                    // Create an empty G2Structure object
                                    // ----------------------------------
                                    hr = ::CoCreateInstance(CLSID_G2Structure,NULL,CLSCTX_INPROC_SERVER,
                                           IID_IG2Structure,reinterpret_cast<void**>(&pIG2Struct));
                                    if (FAILED(hr)) return hr ;

                                    Attribute    *pStElement = mpAttrs ;
                                    VariantInit(&var);
                                    for (int lX = 0 ; lX < mNrAttrs ; lX++, pStElement++)
                                    {
                                        // Create the G2StructureEntry that will be held
                                        // by the Structure.
                                        // ---------------------------------------------
                                        hr = ::CoCreateInstance(CLSID_G2StructureEntry, NULL, CLSCTX_INPROC_SERVER,
                                           IID_IG2StructureEntry,reinterpret_cast<void**>(&pIG2SE));
                                        if FAILED(hr) 
                                        {
                                            pIG2Struct->Release() ;
                                            VariantClear(pVar) ;
                                            return hr ;
                                        }

                                        // Store the name of the attribute
                                        // -------------------------------
                                        TCHAR*  pAttrName = pStElement->AttrName() ;
                                        pIG2SE->put_Name(T2OLE(pAttrName)) ;
                                        delete [] pAttrName ;

                                        // Store the Attribute Value
                                        // -------------------------
                                        pStElement->ItemPtr()->toVariant(&var) ;
                                        pIG2SE->put_Value(var) ;
                                        VariantClear(&var);

                                        // Add this attribute to the structure
                                        // -----------------------------------
                                        ((CG2Structure*)pIG2Struct)->Confiscate(pIG2SE);
                                    }

                                    // Package the G2Structure for return
                                    // ----------------------------------
                                    hr = pIG2Struct->QueryInterface(IID_IDispatch, reinterpret_cast<void**>(&(pVar->pdispVal))) ;
                                    pIG2Struct->Release() ;
                                    if (FAILED(hr)) return hr ;
                                    pVar->vt = VT_DISPATCH ;
                                    break ;
                                }

        default:                ATLTRACE("Unknown Datum type ... returning NULL.\n") ;
                                break ;

    }
    return S_OK ;
}


/* ========================================================================== */
/*                                                                            */
/*            If this object holds a logical value, return it.                */
/*                      Otherwise throw an exception.                         */
/*                                                                            */
/* ========================================================================== */
bool Datum::Boolean()
{
    if (mType == GSI_LOGICAL_TAG)
        return (mValue.lngVal >= 0) ;
    ATLTRACE("Type mismatch. Type %ld, not a logical.\n" , mType) ;
#ifdef _DEBUG
    throw TYPE_MISMATCH ;
#endif
    return false ;
}


/* ========================================================================== */
/*                                                                            */
/*                  Return a copy of this Datum's attributes                  */
/*                                                                            */
/* ========================================================================== */
Attribute* Datum::CopyOfAttributes()
{
    Attribute *pRetVal = NULL ;
    if (mNrAttrs > 0)
        pRetVal = new Attribute [mNrAttrs] ;
    if (pRetVal)
        for (long lX = 0 ; lX < mNrAttrs ; lX++)
            pRetVal[lX] = mpAttrs[lX] ;

    return pRetVal ;
}


// Return a copy of the array of Datums contained in this object
//
// ===============================================================
Datum *Datum::CopyOfListOrArrayOrSequence()
{
    Datum *pRetVal = NULL ;

    if (mType >= GSI_INTEGER_ARRAY_TAG && mType <= GSI_SEQUENCE_TAG)
    {
        pRetVal = makeItems(mLength) ;
        if (pRetVal)
            for (long lX=0 ; lX < mLength ; lX++)
                pRetVal[lX] = mValue.pElements[lX] ;
    }
    else
    {
        ATLTRACE("Type mismatch. Type %ld, not a list or array.\n" , mType) ;
#ifdef _DEBUG
        throw TYPE_MISMATCH ;
#endif
    }
    return pRetVal ;
}


/*============================================================================*/
/*                                                                            */
/*                           Float value accessor.                            */
/*                                                                            */
/*     It is an error to request float value if object not of float type      */
/*                                                                            */
/*============================================================================*/
double Datum::Float()
{
    if (mType == GSI_FLOAT64_TAG)
        return mValue.dblVal ;

    ATLTRACE("Type mismatch. Type %ld, not a float.\n" , mType) ;
#ifdef _DEBUG
    throw TYPE_MISMATCH ;
#endif
    return 0.0 ;
}


/*============================================================================*/
/*                                                                            */
/*                Set this object to type float and set its value             */
/*                                                                            */
/*============================================================================*/
void Datum::Float(double dblVal, bool zapFlag)
{
    if (zapFlag)
        Zap() ;
    else
        zapValue() ;
    mType = dtyFloat ;
    mValue.dblVal = dblVal ;
}


/*============================================================================*/
/*                                                                            */
/*                          G2Symbols Flag Accessor                           */
/*                                                                            */
/*============================================================================*/
bool Datum::G2Symbols()
{
    return mG2Sym ;
}


/*============================================================================*/
/*                                                                            */
/* Set or clear flag indicating that symbols should be returned as IG2Symbols */
/*                                                                            */
/*============================================================================*/
void Datum::G2Symbols(bool wantIG2Symbol)
{
    mG2Sym = wantIG2Symbol ;
}


/* ========================================================================== */
/*                                                                            */
/*              Set this object to type logical and set its value             */
/*   from a long received from GSI which should be an integer with value      */
/*                 between -1000 (GSI_FALSE) & 1000 (GSI_TRUE).               */
/*                                                                            */
/* ========================================================================== */
void Datum::Logical(long gsiLog, bool zapFlag)
{
    if (zapFlag)
        Zap() ;
    else
        zapValue() ;
    mType = dtyLogical ;
    if (gsiLog >= GSI_FALSE && gsiLog <= GSI_TRUE)
        mValue.lngVal = gsiLog ;
    else
    {
        ATLTRACE ("*** Invalid value (%ld) received by Datum::Logical.\n", gsiLog) ;
        mValue.lngVal = (gsiLog < 0) ? GSI_FALSE : GSI_TRUE ;
    }
}


/* ========================================================== */
/*                                                            */
/* Long value accessor.  (A gsi_int is actually a long).      */
/* It is an an error to request the long value if this object */
/* is not set to GSI_INTEGER_TAG.                             */
/*                                                            */
/* ========================================================== */
long Datum::Long()
{
    if (mType == GSI_INTEGER_TAG || mType == GSI_LOGICAL_TAG)
        return mValue.lngVal ;
    ATLTRACE("Type mismatch. Type %ld, not a long.\n" , mType) ;
#ifdef _DEBUG
    throw TYPE_MISMATCH ;
#endif
    return 0 ;
}


/* Set this object to type gsi_int and set its value */
/*                                                   */
/* ================================================= */
void Datum::Long(long lVal, bool zapFlag)
{
    if (zapFlag)
        Zap() ;
    else
        zapValue() ;
    mType = dtyInteger ;
    mValue.lngVal = lVal ;
}


// Release any previously allocated memory then zero this object
//
// =============================================================
void Datum::setToNull()
{
    Zap() ;
}


// =========================================================
//
// If this is a string, return a copy of the string it holds.
// Otherwise, we have a program error.
//
// =========================================================
TCHAR* Datum::String()
{
    USES_CONVERSION ;

    if (mType == GSI_STRING_TAG || mType == GSI_SYMBOL_TAG)
        return CopyOfString() ;
    ATLTRACE("Type mismatch. Type %ld, not a string.\n" , mType) ;
#ifdef _DEBUG
    throw TYPE_MISMATCH ;
#endif
    return NULL ;
}


// ========================================================================== //
//                                                                            //
//               Set this object to type string and set its value             //
//                                                                            //
// ========================================================================== //
void Datum::String(TCHAR* newString, bool zapFlag)
{
    if (zapFlag)
        Zap() ;
    else
        zapValue() ;
    mType = dtyString ;
    if (newString)
    {
        mValue.pString = new TCHAR [_tcslen(newString)+1] ;
        if (mValue.pString)
            _tcscpy(mValue.pString, newString) ;
    }
}


// If this is a symbol, return a copy of the string it holds.
// Otherwise, we have a program error.
//
// =========================================================
TCHAR* Datum::Symbol()
{
    if (mType == GSI_SYMBOL_TAG || mType == GSI_STRING_TAG )
        return CopyOfString() ;
    ATLTRACE("Type mismatch. Type %ld, not a symbol.\n" , mType) ;
#ifdef _DEBUG
    throw TYPE_MISMATCH ;
#endif
    return NULL ;
}


// ========================================================================== //
//                                                                            //
//               Set this object to type symbol and set its value             //
//                                                                            //
// ========================================================================== //
void Datum::Symbol(TCHAR* newSymbol, bool zapFlag)
{
    if (zapFlag) 
        Zap() ;
    else
        zapValue() ;
    mType = dtySymbol ;
    if (newSymbol)
    {
        mValue.pString = new TCHAR [_tcslen(newSymbol)+1] ;
        if (mValue.pString)
            _tcscpy(mValue.pString, newSymbol) ;
    }
}


// Type Accessor
//
// =============
DataType Datum::Type()
{
    return mType ;
}


// If this object holds an unsigned short vector (UUID),
// return a copy of it.  Otherwise throw an exception.
//
// =====================================================
unsigned short * Datum::USV()
{
    if (mType != GSI_UNSIGNED_SHORT_VECTOR_TAG)
    {
        ATLTRACE("Type mismatch. Type %ld, not an unsigned short vector.\n" , mType) ;
#ifdef _DEBUG
        throw TYPE_MISMATCH ;
#endif
        return NULL ;
    }

    unsigned short *pUsv = NULL ;

    if (mLength)
    {
        pUsv = new unsigned short [mLength] ;
        if (pUsv)
            memcpy(pUsv, mValue.pUsv, mLength * sizeof(unsigned short)) ;
    }
    return pUsv ;
}


//============================================================================//
//                                                                            //
//      Set this object to type Unsigned Short Vector, and set its value.     //
//                                                                            //
//============================================================================//
void Datum::USV(unsigned short *pUSV, long lLen, bool zapFlag)
{
    if (zapFlag) 
        Zap() ;
    else
        zapValue() ;
    mType = dtyUSV ;
    if (pUSV)
    {
        mValue.pUsv = new unsigned short [ lLen ] ;
        if (mValue.pUsv)
        {
            mLength = lLen ;
            memcpy(mValue.pUsv, pUSV, lLen * sizeof(unsigned short)) ;
            return ;
        }
    }
    mValue.pUsv = NULL ;
    mLength = 0 ;
}


//============================================================================//
//                                                                            //
//   Return the pointer to the array of Datums holding the elements of this   //
//                               list or array.                               //
//                                                                            //
//============================================================================//
Datum* Datum::LAElements()
{
    if (mType < GSI_INTEGER_ARRAY_TAG || mType > GSI_SEQUENCE_TAG)
    {
        ATLTRACE("Type mismatch. Type %ld, not a list or array.\n" , mType) ;
#ifdef _DEBUG
        throw TYPE_MISMATCH ;
#endif
        return NULL ;
    }
    return mValue.pElements ;
}


// Set the elements of this object to a copy of those pointed to by pElements.
// Also set the number of elements and the type of this object.
//
// ===========================================================================
void Datum::ListOrArray(DataType typeCode, Datum *pElements, long nrElements, bool zapFlag)
{
    if (typeCode < GSI_INTEGER_ARRAY_TAG || typeCode > GSI_SEQUENCE_TAG || nrElements < 0)
    {
        ATLTRACE("Type mismatch. Type %ld, not a list or array.\n" , typeCode) ;
#ifdef _DEBUG
        throw BAD_PARAMETER ;
#endif
        return ;
    }
    if (zapFlag)
        Zap() ;
    else
        zapValue() ;
    mType = typeCode ;
    mValue.pElements = nrElements ? new Datum[nrElements] : NULL ;
    mLength = mValue.pElements ? nrElements : 0 ;
    if (mLength)
        for (long lX=0 ; lX < nrElements ; lX++)
            mValue.pElements[lX] = pElements[lX] ;
}


// ========================================================================== //
//                                                                            //
//         Return the pointer to this structure's or item's attributes.       //
//                                                                            //
// ========================================================================== //
Attribute* Datum::Attributes()
{
    if (!mIsItem && mType != GSI_STRUCTURE_TAG)
    {
        ATLTRACE("Type mismatch. Not an item or structure.\n" , mType) ;
#ifdef _DEBUG
        throw TYPE_MISMATCH ;
#endif
        return NULL ;
    }
    return mpAttrs ;
}


/*           Replace the attributes of this Datum with those provided.        */
/*                                                                            */
/* ========================================================================== */
void Datum::Attributes(Attribute *pAttributes, long nrAttributes) 
{
    if (mpAttrs)
        delete [] mpAttrs ;
    mpAttrs = pAttributes ;
    mNrAttrs = nrAttributes ;
}


// Accessor for Number of Attributes
//
// =================================
long Datum::NrAttrs()
{
    return mNrAttrs ;
}


// Return pointer to UserDatum element
//
// ==================================
Datum* Datum::UserDataPtr()
{
    return mpUserData ;
}

/* ========================================================================== */
/*                                                                            */
/*         Sets the User Data of this G2 Item to the Datum pointed to         */
/*       by pUserData. *pUserData must have been allocated dynamically.       */
/*                   The Datum destructor will delete it.                     */
/*                                                                            */
/* ========================================================================== */
void Datum::UserData(Datum *pUserData)
{
    mpUserData = pUserData ;
    Itemize() ;
}


// Return "is item" flag
//
// =====================
bool Datum::IsItem()
{
    return mIsItem ;
}


// The Axl/GSI representation of COM Currency is a structure with
// a single entry named COM-CURRENCY and with value of the amount.
//
// ==============================================================
void Datum::Currency(CURRENCY *pCy)
{
    Zap() ;
    mType = dtyStructure ;
    mpAttrs = new Attribute [1] ;
    mNrAttrs = 1 ;

    VARIANT val ;
    VariantInit(&val) ;
    val.vt= VT_R8 ;
    val.dblVal = ((pCy->Hi * 256.0 * 256.0 * 256.0 * 256.0) + pCy->Lo) / 10000.0;
    mpAttrs[0].FillIn(_T("COM-CURRENCY"), val) ;
}


// ========================================================================== //
//                                                                            //
//      Set this Datum to the Axl/Gsi representation of a COM error code.     //
//                                                                            //
// ========================================================================== //
void Datum::ErrorCode(SCODE sc)
{
    Zap() ;
    mType = dtyStructure ;
    mpAttrs = new Attribute [3] ;
    mNrAttrs = 3 ;

    VARIANT varX ;
    VariantInit(&varX) ;

    varX.vt= VT_BSTR ;
    varX.bstrVal = FAILED(sc) ? L"FAILED" : L"SUCCESS" ;
    mpAttrs[0].FillIn(_T("COM-SEVERITY"), varX) ;
    mpAttrs[0].Symbolize() ;

    varX.vt = VT_I4 ;
    varX.lVal = (sc >> 16) & 0x7FFF ;
    mpAttrs[1].FillIn(_T("COM-FACILITY"), varX) ;

    varX.lVal =  sc & 0xFFFF ;
    mpAttrs[2].FillIn(_T("COM-CODE"), varX) ;

}


// ========================================================================== //
//                                                                            //
//         Set this Datum to the Axl/Gsi representation of a COM date.        //
//                                                                            //
// ========================================================================== //
void Datum::Date(DATE dt)
{
    HRESULT     hr ;
    SYSTEMTIME  st ;
    hr = VariantTimeToSystemTime(dt, &st) ;
    if FAILED(hr)
        memset(&st, 0, sizeof(SYSTEMTIME) );

    Zap() ;
    mType = dtyStructure ;
    mpAttrs = new Attribute [7] ;
    mNrAttrs = 7 ;

    VARIANT varX ;
    VariantInit(&varX) ;

    varX.vt= VT_I4 ;
    varX.lVal = st.wDay ;
    mpAttrs[0].FillIn(_T("COM-DAY"), varX) ;

    varX.lVal = st.wMonth ;
    mpAttrs[1].FillIn(_T("COM-MONTH"), varX) ;

    varX.lVal =  st.wYear ;
    mpAttrs[2].FillIn(_T("COM-YEAR"), varX) ;

    varX.lVal =  st.wDayOfWeek ;
    mpAttrs[3].FillIn(_T("COM-DAY-OF-WEEK"), varX) ;

    varX.lVal =  st.wHour ;
    mpAttrs[4].FillIn(_T("COM-HOUR"), varX) ;

    varX.lVal =  st.wMinute ;
    mpAttrs[5].FillIn(_T("COM-MINUTE"), varX) ;

    varX.lVal =  st.wSecond ;
    mpAttrs[6].FillIn(_T("COM-SECOND"), varX) ;

}


//    Accessor for Attributes of a Structure.
//
// Returns pointer to original attributes, not a copy.
//
// ===================================================
Attribute*  Datum::Structure()
{
    if (mType != GSI_STRUCTURE_TAG)
    {
        ATLTRACE("Type mismatch. Type %ld, not a structure.\n" , mType) ;
#ifdef _DEBUG
        throw TYPE_MISMATCH ;
#endif
        return NULL ;
    }
    return mpAttrs ;
}


// =================================================================
//
//                 Make this Datum a Structure.
//
// Note: This method does not make a copy of the attributes pointed
//       to by pAttributes.  It takes ownership of them!
//
// =================================================================
void Datum::Structure(Attribute *pAttributes, long nrAttrs)
{
    if (mType) Zap() ;
    mNrAttrs = nrAttrs ;
    mpAttrs = pAttributes ;
    mType = dtyStructure ;
}


// ========================================================================== //
//                                                                            //
//                 Code shared by Symbols and Strings to                      //
//                   return a copy of the stored string.                      //
//                                                                            //
// ========================================================================== //
TCHAR* Datum::CopyOfString()
{   
    if (mValue.pString)
    {
        TCHAR*  retVal = new TCHAR [_tcslen(mValue.pString)+1] ;
        if (retVal)
            _tcscpy(retVal, mValue.pString) ;
        return retVal ;
    }
    else
        return NULL ;
}


// First free any memory that has been dynamically allocated by this object.
// Then erase the object which sets it type NULL.
//
// ========================================================================
void Datum::Zap()
{
    if (mType == GSI_STRING_TAG || mType == GSI_SYMBOL_TAG)
        delete [] mValue.pString ;
    else if (mType == GSI_UNSIGNED_SHORT_VECTOR_TAG)
        delete [] mValue.pUsv ;
    else if (mType >= GSI_INTEGER_ARRAY_TAG && mType <= GSI_SEQUENCE_TAG  && 
                                        mValue.pElements)
        delete [] mValue.pElements ;
    if (mpClassName)
        delete [] mpClassName ;
    if (mpName)
        delete [] mpName ;
    if (mpAttrs)
        delete [] mpAttrs ;
    if (mpUserData)
        delete mpUserData ;

    memset(this, 0, sizeof(Datum)) ;
}


/* ========================================================================== */
/*                                                                            */
/*              We are going to overwrite the value of this item              */
/*            but not its name, class name, attributes or user data.          */
/*                                                                            */
/* ========================================================================== */
void Datum::zapValue()
{
    if (mType == GSI_STRING_TAG || mType == GSI_SYMBOL_TAG)
        delete [] mValue.pString ;
    else if (mType == GSI_UNSIGNED_SHORT_VECTOR_TAG)
        delete [] mValue.pUsv ;
    else if (mType >= GSI_INTEGER_ARRAY_TAG && mType <= GSI_SEQUENCE_TAG  && 
                                        mValue.pElements)
        delete [] mValue.pElements ;
    memset(&mValue, 0, sizeof(mValue)) ;
}


// ========================================================================== //
//                                                                            //
//       Return a pointer to an array of the specified number of Datums       //
//                                                                            //
// ========================================================================== //
Datum* Datum::makeItems(long nrItems)
{
    if (nrItems > 0)
        return new Datum[nrItems] ;

    return NULL ;
}


//============================================================================//
//                                                                            //
//                      Implementation of Datum = Datum                       //
//                                                                            //
//                  Make this Datum a copy of another Datum                   //
//                                                                            //
//============================================================================//
Datum& Datum::operator=(Datum& src)
{
    if (this != &src)
    {
        // Release any memory that is pointed to by
        // this Datum before assigning the new value.
        // ------------------------------------------
        if (mType == GSI_STRING_TAG || mType == GSI_SYMBOL_TAG || mIsItem ||
                (mType >= GSI_UNSIGNED_SHORT_VECTOR_TAG && mType <= GSI_STRUCTURE_TAG))
            Zap() ;

        // Check for any of the types that require dynamic allocation
        // and process them accordingly.
        // ----------------------------------------------------------
        mType = src.Type() ;
        mLength = src.Length() ;
        mG2Sym = src.G2Symbols() ;
        mpCtx = src.mpCtx ;
        if (src.mpUserData)
        {
            Datum   *pNewUD = new Datum ;
            *pNewUD = *mpUserData ;
            mpUserData = pNewUD ;
        }
        if (mType == GSI_SYMBOL_TAG)
            mValue.pString = src.Symbol() ;
        else if (mType == GSI_STRING_TAG)
            mValue.pString = src.String() ;
        else if (mType == GSI_UNSIGNED_SHORT_VECTOR_TAG)
            mValue.pUsv = src.USV() ;
        else if (mType >= GSI_INTEGER_ARRAY_TAG && mType <= GSI_SEQUENCE_TAG)
            mValue.pElements = src.CopyOfListOrArrayOrSequence() ;
        else if (mType == GSI_STRUCTURE_TAG)
        {
            mNrAttrs = src.NrAttrs() ;
            mpAttrs = src.CopyOfAttributes() ;
            return *this ;
        }

        // No dynamic allocation
        // is required.  Copy the source object to this object.
        // ----------------------------------------------------
        else
            memcpy(&mValue, &src.mValue, sizeof(wrapper)) ;


        // If we got here and the source object has attributes then
        // it represents a G2 item and we need to make a local copy.
        // ---------------------------------------------------------
        if (mNrAttrs = src.NrAttrs())
            mpAttrs = src.CopyOfAttributes() ;

        // Take care of item-specific features
        // -----------------------------------
        if (src.mIsItem)
        {
            Itemize() ;
            if (src.mpClassName)
                mpClassName = src.ClassName() ;
            if (src.mpName)
                mpName = src.Name() ;
            if (src.mpUserData)
            {
                mpUserData = new Datum ;
                *mpUserData = *src.UserDataPtr() ;
            }
        }
    }
    return *this ;
}


//============================================================================//
//                                                                            //
//                    Implementation of Datum = gsi_item                      //
//                                                                            //
//                    Fill in this Datum from a gsi_item                      //
//                                                                            //
//============================================================================//
Datum& Datum::operator =(gsi_item& gsiSrc)
{
    DataType    itemType = (DataType)gsi_type_of(gsiSrc);
    gsi_char*   *pTxt ;
    gsi_char    *pStr ;
    gsi_int     *pInt ;
    gsi_item    *pElements;
    gsi_symbol  *pSym ;
    gsi_attr    *pAttrs;
    double      *pFlt ;
    long        lX ;
    long        ctxNr = gsi_current_context() ;
    
    switch(itemType)
    {
        case GSI_NULL_TAG:      setToNull();
                                break;
        case GSI_INTEGER_TAG:   Long(gsi_int_of(gsiSrc)) ;
                                break;
        case GSI_SYMBOL_TAG:    {
                                    // The symbol NULL is treated as a Null Datum and Variant
                                    TCHAR   *pSymText = (TCHAR *)gsi_symbol_name(gsi_sym_of(gsiSrc)) ;
                                    if (!_tcscmp(pSymText, _T("NULL")))
                                        Zap() ;
                                    else
                                        Symbol(pSymText) ;
                                    break;
                                }
        case GSI_STRING_TAG:    String((TCHAR *)gsi_str_of(gsiSrc)) ;
                                break;
        case GSI_LOGICAL_TAG:   Logical(gsi_log_of(gsiSrc)) ;
                                break;
        case GSI_FLOAT64_TAG:   Float(gsi_flt_of(gsiSrc)) ;
                                break;
        case GSI_ITEM_TAG:      ATLTRACE("Datum of type ITEM not supported.  Returning NULL.\n") ;
                                Zap() ;
                                break ;
        case GSI_HANDLE_TAG:    ATLTRACE("Datum of type HANDLE not supported.  Returning NULL.\n") ;
                                Zap() ;
                                break ;
        case GSI_UNSIGNED_SHORT_VECTOR_TAG:
                                USV(gsi_usv_of(gsiSrc), gsi_usv_length_of(gsiSrc)) ;
                                mpCtx = ctxNr ;
                                break ;

        case GSI_INTEGER_ARRAY_TAG:
                                pInt = gsi_int_array_of(gsiSrc) ;
        case GSI_INTEGER_LIST_TAG:
                                if (itemType == GSI_INTEGER_LIST_TAG)
                                    pInt = gsi_int_list_of(gsiSrc) ;
        case GSI_LOGICAL_ARRAY_TAG:
                                if (itemType == GSI_LOGICAL_ARRAY_TAG)
                                    pInt = gsi_log_array_of(gsiSrc) ;
        case GSI_LOGICAL_LIST_TAG:
                                if (itemType == GSI_LOGICAL_LIST_TAG)
                                    pInt = gsi_log_list_of(gsiSrc) ;
                                mType = itemType ;
                                mLength = gsi_element_count_of(gsiSrc);
                                mValue.pElements = makeItems(mLength) ;
                                if (mValue.pElements)
                                    for (lX = 0 ; lX < mLength ; lX++)
                                        if (mType == dtyIntegerArray || mType == dtyIntegerList)
                                            mValue.pElements[lX].Long(pInt[lX]) ;
                                        else
                                            mValue.pElements[lX].Logical(pInt[lX]) ;
                                else
                                    mLength = 0 ;
                                break ;

        case GSI_STRING_ARRAY_TAG:
                                pTxt = gsi_str_array_of(gsiSrc) ;
        case GSI_STRING_LIST_TAG:
                                if (itemType == GSI_STRING_LIST_TAG)
                                    pTxt = gsi_str_list_of(gsiSrc) ;
                                mType = itemType ;
                                mLength = gsi_element_count_of(gsiSrc);
                                mValue.pElements = makeItems(mLength) ;
                                if (mValue.pElements)
                                    for (lX = 0 ; lX < mLength ; lX++)                                       
                                        mValue.pElements[lX].String((TCHAR *)pTxt[lX]) ;
                                else
                                    mLength = 0 ;
                                break ;

        case GSI_FLOAT64_ARRAY_TAG:
                                pFlt = gsi_flt_array_of(gsiSrc) ;
        case GSI_FLOAT64_LIST_TAG:
                                if (itemType == GSI_FLOAT64_LIST_TAG)
                                    pFlt = gsi_flt_list_of(gsiSrc) ;
                                mType = itemType ;
                                mLength = gsi_element_count_of(gsiSrc);
                                mValue.pElements = makeItems(mLength) ;
                                if (mValue.pElements)
                                    for (lX = 0 ; lX < mLength ; lX++)
                                        mValue.pElements[lX].Float(pFlt[lX]) ;
                                else
                                    mLength = 0 ;
                                break ;

        case GSI_SYMBOL_ARRAY_TAG:
                                pSym = gsi_sym_array_of(gsiSrc) ;
        case GSI_SYMBOL_LIST_TAG:
                                if (itemType == GSI_SYMBOL_LIST_TAG)
                                    pSym = gsi_sym_list_of(gsiSrc) ;
                                mType = itemType ;
                                mLength = gsi_element_count_of(gsiSrc);
                                mValue.pElements = makeItems(mLength) ;
                                if (mValue.pElements)
                                    for (lX = 0 ; lX < mLength ; lX++)
                                    {
                                        pStr = gsi_symbol_name(pSym[lX]) ;
                                        mValue.pElements[lX].Symbol((TCHAR *)pStr) ;
                                    }
                                else
                                    mLength = 0 ;
                                break ;


        case GSI_ITEM_LIST_TAG:
        case GSI_ITEM_ARRAY_TAG:
        case GSI_VALUE_ARRAY_TAG:
        case GSI_ITEM_OR_VALUE_ARRAY_TAG:
        case GSI_QUANTITY_ARRAY_TAG:
        case GSI_VALUE_LIST_TAG:
        case GSI_ITEM_OR_VALUE_LIST_TAG:
        case GSI_QUANTITY_LIST_TAG:
        case GSI_SEQUENCE_TAG:  mType = itemType ;
                                pElements = gsi_elements_of(gsiSrc);
                                mLength = gsi_element_count_of(gsiSrc);
                                mValue.pElements = makeItems(mLength) ;
                                if (mValue.pElements)
                                    for (lX = 0 ; lX < mLength ; lX++)
                                        mValue.pElements[lX] = pElements[lX] ;
                                else
                                    mLength = 0 ;
                                break ;
        case GSI_STRUCTURE_TAG: mType = dtyStructure ;
                                pAttrs = gsi_attrs_of(gsiSrc);
                                mNrAttrs = pAttrs ? gsi_attr_count_of(gsiSrc) : 0 ;
                                mpAttrs = mNrAttrs ?  new Attribute[mNrAttrs] : NULL ;
                                if (mpAttrs)
                                    for (lX = 0 ; lX < mNrAttrs ; lX++)
                                        mpAttrs[lX] = pAttrs[lX] ;
                                else
                                    mNrAttrs = 0 ;
                                break ;
        
    // Not valid.  Should never happen per gsi_type_of() spec.
    case GSI_VALUE_TAG:         ATLTRACE("Datum of type VALUE not supported.\n") ;
                                Zap() ;
                                break ;      

    // Not valid.  Should never happen per gsi_type_of() spec.
    case GSI_QUANTITY_TAG:      ATLTRACE("Datum of type QUANTITY not supported.\n") ;
                                Zap() ;
                                break ;

    default:                    ATLTRACE("UNKNOWN GSI type.  Datum set to NULL.\n") ;
                                Zap() ;
                                break ;
    }

    // Tag this Datum with a flag indicating whether symbols should be
    // presented to the container as G2Symbols or as BSTRs
    // ---------------------------------------------------------------
    GsiContext *context = GsiContext::FindContext();
    if (context)
        G2Symbols(context->g2syms()) ;
        
    // Store Item-specific information
    // -------------------------------
    if (gsi_is_item(gsiSrc))
    {
        mIsItem = true ;

        TCHAR*  pGsiClassName = (TCHAR *)gsi_symbol_name(gsi_class_name_of(gsiSrc)) ;
        mpClassName = pGsiClassName ? new TCHAR [_tcslen(pGsiClassName)+1] : NULL ;
        if (mpClassName)
            _tcscpy(mpClassName, pGsiClassName) ;

        TCHAR*  pGsiName = (TCHAR *)gsi_symbol_name(gsi_name_of(gsiSrc)) ;
        mpName = pGsiName ? new TCHAR [_tcslen(pGsiName)+1] : NULL ;
        if (mpName)
            _tcscpy(mpName, pGsiName) ;

        mNrAttrs = gsi_attr_count_of(gsiSrc) ;
        if (mNrAttrs)
            mpAttrs = new Attribute[mNrAttrs] ;
        if (!mpAttrs) mNrAttrs = 0 ;
        gsi_attr    *pItemAttr = gsi_attrs_of(gsiSrc) ;
        for (lX = 0 ; lX < mNrAttrs; lX++)
            mpAttrs[lX] = pItemAttr[lX] ;
    }

    // Save pointer to GsiContext object associated with this gsi_item
    // ---------------------------------------------------------------
    mpCtx = (long)GsiContext::FindContext() ;

    // Extract the user data.  Since the user data will not have user data,
    // this recursive call will end.
    // --------------------------------------------------------------------
    gsi_item    userData = gsi_user_data_of(gsiSrc) ;
    if (userData)
    {
        mpUserData = new Datum ;
        *mpUserData = userData ;
    }

    return *this ;
}



/* =========================================================================== */
/*                                                                             */
/*                      Implementation of Datum = Variant                      */
/*                                                                             */
/*    Replace the contents of this Datum with the equivalent of the Variant.   */
/*                                                                             */
/* =========================================================================== */
Datum&  Datum::operator=(VARIANT&   varSrc)
{
    return internalVariantToDatum(varSrc, true) ;
}


/* =========================================================================== */
/*                                                                             */
/*                      Implementation of Datum << Variant                     */
/*                           (Assigment of Value Only)                         */
/*                                                                             */
/*  If upon entry this Datum contains an item, then this method sets just the  */
/*  VALUE of the item with the following exceptions:                           */
/*                                                                             */
/*  1) if the input is some form of G2Item, all the information in this Datum  */
/*     is replaced by the information in the G2Item.                           */
/*  2) if the input holds a G2Structure or a Variant of a type that will be    */
/*     converted to a structure (Currency, Date, etc.), this Datum is replaced */
/*     by the structure information.  (A G2 structures cannot be an item).     */
/*  3) if the Variant is of type NULL this means to erase the information in   */
/*     this Datum.                                                             */
/*                                                                             */
/* When this Datum contains an item and these conditions are not met, we just  */
/* set the relevant information in this Datum without modifying any other      */
/* fields.  For example if the Variant contains an integer and we have already */
/* set this Datum's class name, name, and attributes, all we do is store the   */
/* integer as the Datum's value and set the type to dtyInteger.  This way, we  */
/* can set parts (class name, name, value, attributes, and user data) of the   */
/* in any sequence that is required or convenient.                             */
/*                                                                             */
/* =========================================================================== */
Datum&        Datum::operator<<(VARIANT&   varSrc)
{
    return internalVariantToDatum(varSrc, false) ;
}


/* =========================================================================== */
/*                                                                             */
/*    The shared implementation of "Datum = Variant" and "Datum << Variant"    */
/*                                                                             */
/* =========================================================================== */
Datum&  Datum::internalVariantToDatum(VARIANT& varSrc, bool zapFlag)
{
    double      dblX ;
    HRESULT     hr ;
    IDispatch   *pIDisp ;
    VARIANT     *pVar = &varSrc ;

    if (zapFlag) 
        Zap() ;
    else
        zapValue() ;

    USES_CONVERSION;
    switch (V_VT(pVar))
    {
        case VT_EMPTY:
        case VT_NULL:       setToNull() ;
                            break ;

        case VT_UI1:        Long(V_UI1(pVar),zapFlag) ;
                            break ;

        case VT_UI1 | VT_BYREF:
                            Long(*V_UI1REF(pVar),zapFlag);
                            break;

        case VT_I2:         Long(V_I2(pVar),zapFlag);
                            break;

        case VT_I2 | VT_BYREF:
                            Long(*V_I2REF(pVar),zapFlag);
                            break;

        case VT_I4:         Long(V_I4(pVar),zapFlag) ;
                            break ;

        case VT_I4 | VT_BYREF:
                            Long(*V_I4REF(pVar),zapFlag) ;
                            break;

        case VT_R4:         Float(V_R4(pVar),zapFlag) ;
                            break;

        case VT_R4 | VT_BYREF:
                            Float(*V_R4REF(pVar),zapFlag) ;
                            break;

        case VT_R8:         Float(V_R8(pVar),zapFlag) ;
                            break;

        case VT_R8 | VT_BYREF:
                            Float(*V_R8REF(pVar),zapFlag) ;
                            break;

        case VT_CY:         Currency(&(pVar->cyVal)) ;
                            break;

        case VT_CY | VT_BYREF:
                            Currency(pVar->pcyVal) ;
                            break;

        case VT_BSTR:       String(OLE2T(V_BSTR(pVar)),zapFlag) ;
                            break;

        case VT_BSTR | VT_BYREF:
                            String(OLE2T(*V_BSTRREF(pVar)),zapFlag) ;
                            break;

        case VT_ERROR:      ErrorCode(V_ERROR(pVar)) ;
                            break ;

        case VT_ERROR | VT_BYREF:
                            ErrorCode(*V_ERRORREF(pVar)) ;
                            break ;

        case VT_BOOL:       Logical(V_BOOL(pVar) == VARIANT_FALSE ? GSI_FALSE : GSI_TRUE, zapFlag) ;
                            break ;

        case VT_BOOL | VT_BYREF:
                            Logical(*V_BOOLREF(pVar) == VARIANT_FALSE ? GSI_FALSE : GSI_TRUE, zapFlag);
                            break ;

        case VT_DATE:       Date(pVar->date) ;
                            break ;

        case VT_DATE | VT_BYREF:
                            Date(*pVar->pdate) ;
                            break ;

        case VT_DISPATCH:
                            pIDisp = pVar->pdispVal ;

        case VT_DISPATCH | VT_BYREF:
                            if (V_VT(pVar) & VT_BYREF)        // we might have fallen through
                            {
                                if (pVar->ppdispVal == NULL)
                                {
                                    ATLTRACE("Invalid item.  Returning NULL.\n");
                                    break ;
                                }
                                pIDisp = *(pVar->ppdispVal);
                            }
                            G2ComItem(pIDisp) ;
                            break ;                            

        case VT_VARIANT | VT_BYREF:
                            *this = *V_VARIANTREF(pVar) ;
                            break;
        case VT_UNKNOWN:
                            ATLTRACE("conversion from UNKNOWN to Datum not supported.  Returning NULL.\n");
                            break;
        case VT_UNKNOWN | VT_BYREF:
                            ATLTRACE("conversion from UNKNOWN BYREF to Datum not supported.  Returning NULL.\n");
                            break;
        case VT_DECIMAL:    
                            hr = VarR8FromDec(&(pVar->decVal), &dblX) ;
                            goto decmrg ;
        case VT_DECIMAL | VT_BYREF:
                            hr = VarR8FromDec(pVar->pdecVal, &dblX) ;
decmrg:
                            if (FAILED(hr))
                            {
                                ATLTRACE("Conversion of decimal to double failed.  Returning NULL.\n");
                                break ;
                            }
                            Float(dblX, zapFlag) ;
                            break;

        // VT_ARRAY can be of type ANY except NULL or EMPTY.
        case VT_ARRAY | VT_UI1:
        case VT_ARRAY | VT_I2:
        case VT_ARRAY | VT_I4:
        case VT_ARRAY | VT_R4:
        case VT_ARRAY | VT_R8:
        case VT_ARRAY | VT_CY:
        case VT_ARRAY | VT_BSTR:
        case VT_ARRAY | VT_BOOL:
        case VT_ARRAY | VT_DATE:
        case VT_ARRAY | VT_VARIANT:
        case VT_ARRAY | VT_DISPATCH:
        case VT_ARRAY | VT_ERROR:

                            if (zapFlag)
                                *this = V_ARRAY(pVar) ;  // replace entire item
                            else
                                *this << V_ARRAY(pVar) ; // replace value only
                            break;

        // VT_ARRAY is always BYREF and can be of type ANY except NULL or EMPTY.
        case VT_ARRAY | VT_BYREF | VT_UI1:
        case VT_ARRAY | VT_BYREF | VT_I2:
        case VT_ARRAY | VT_BYREF | VT_I4:
        case VT_ARRAY | VT_BYREF | VT_R4:
        case VT_ARRAY | VT_BYREF | VT_R8:
        case VT_ARRAY | VT_BYREF | VT_CY:
        case VT_ARRAY | VT_BYREF | VT_BSTR:
        case VT_ARRAY | VT_BYREF | VT_BOOL:
        case VT_ARRAY | VT_BYREF | VT_DATE:
        case VT_ARRAY | VT_BYREF | VT_VARIANT:
        case VT_ARRAY | VT_BYREF | VT_DISPATCH:
        case VT_ARRAY | VT_BYREF | VT_ERROR:

                            if (zapFlag)
                                *this = *V_ARRAYREF(pVar) ;  // replace entire item
                            else
                                *this << *V_ARRAYREF(pVar) ; // replace value only
                            break;

        case VT_ARRAY | VT_UNKNOWN:
        case VT_ARRAY | VT_EMPTY:

                            ATLTRACE("Conversion of arrays of EMPTY or UNKNOWN to Datum not supported.  Returning NULL.\n");
                            break;

        case VT_ARRAY | VT_BYREF | VT_UNKNOWN:
        case VT_ARRAY | VT_BYREF | VT_EMPTY:

                            ATLTRACE("Conversion of arrays of EMPTY or UNKNOWN BYREF to Datum not supported.  Returning NULL.\n");
                            break;

        case VT_VARIANT:
        default:
                            ATLTRACE("Unknown or unsupported Variant type.  Returning NULL.\n") ;
    }

    return *this ;
}

/* =========================================================================== */
/*                                                                             */
/*                    Implementation of Datum = SAFEARRAY*                     */
/*                     (Replace entire contents of Datum)                      */
/*                                                                             */
/* =========================================================================== */
Datum&        Datum::operator=(SAFEARRAY *pSA)
{
    return internalAssignSA(pSA, true) ;
}


/* =========================================================================== */
/*                                                                             */
/*                   Implementation of Datum << SAFEARRAY*                     */
/*   (Replace just the value of the Datum unless there is no other choice)     */
/*                                                                             */
/* =========================================================================== */
Datum& Datum::operator<<(SAFEARRAY *pSA)
{
    return internalAssignSA(pSA, false) ;
}


/* =========================================================================== */
/*                                                                             */
/* The shared implementation of "Datum = SafeArray*" and "Datum << SafeArray*" */
/*                                                                             */
/* =========================================================================== */
Datum& Datum::internalAssignSA(SAFEARRAY *pSA, bool zapFlag)
{
    HRESULT     hr ;
    void HUGEP  *psaDat;
    long        lDim = 0L;
    long        lElSize = 0L ;
    long        lLBound = 0L;
    long        lUBound = 0L;
    long        nrAgs = 0L ;
    VARTYPE     vtyp ;

    SafeArrayGetVartype(pSA, &vtyp) ;

    // Is it single-dimensional?
    // -------------------------
    lDim = ::SafeArrayGetDim(pSA) ;

    // Yes - construct a sequence of the elements
    // ------------------------------------------
    if (lDim == 1)
    {
        VARIANT varX ;
        VariantInit(&varX) ;

        if (zapFlag)
            Zap() ;
        else
            zapValue() ;

        hr = SafeArrayGetLBound(pSA, 1, &lLBound) ;
        if (FAILED(hr)) return *this;
        hr = SafeArrayGetUBound(pSA, 1, &lUBound) ;
        if (FAILED(hr)) return *this ;
        mLength = (lUBound - lLBound) + 1 ;

        hr = SafeArrayAccessData(pSA, &psaDat);
        if (FAILED(hr)) return *this ;
        mType = dtySequence ;
        if (mLength)
            mValue.pElements = new Datum[mLength] ;
        if (mValue.pElements)
            for (long lX = lLBound ; lX <= lUBound ; lX++)
            {
                hr = ArrayElement2Var(vtyp, lX-lLBound, psaDat, &varX);
                if (FAILED(hr)) VariantClear(&varX) ;
                mValue.pElements[lX-lLBound] = varX ;
                VariantClear(&varX) ;
            }
        hr = SafeArrayUnaccessData(pSA);
        return *this ;
    }
   
    // This should not happen
    // ----------------------
    if (lDim < 1)
        return *this ;

    // It's multi-dimensional.  The resulting Datum is complicated.
    // ------------------------------------------------------------

    //  this (sequence)  Attr[0] ->  COM-DIMENSIONS   / (sequence)   Item[0]      ->  # elements (integer)
    //                                                                  "                     "
    //                                                               Item[lDim-1] ->  # elements (integer)
    //                   Attr[1] ->  COM-LOWER-BOUNDS / (sequence)   Item[0]      ->  lower bound (integer)
    //                                                                  "                     "
    //                                                               Item[lDim-1] ->  lower bound (integer)
    //                   Attr[2] ->  COM-ELEMENTS     / (sequence)   Item[0]      ->  value (depends on input)
    //                                                               Item[1]      ->  value (depends on input)
    //                                                                  "                     "
    //                                                               Item[total # elements-1] -> va;ie
    //                   Attr[3] ->  COM-ARRAY-TYPE   / (symbol)     code for value type

    // This will be translated to a structure.  Since structures and G2 items
    // are incompatible, we release the entire Datum before beginning with
    // the translation.
    // -----------------------------------------------------------------------
    Zap() ;

    // Build the structure of the return value
    // ---------------------------------------
    Attribute     *pStructAttr = new Attribute[4] ;

    Structure(pStructAttr, 4) ;

    // Structure of Attr[0]
    // --------------------
    Datum     *pAttr0Item = new Datum ;
    Datum     *pDims = new Datum[lDim] ;  
    pAttr0Item->Sequence(pDims,lDim) ;
    pStructAttr[0].AttrName(_T("COM-DIMENSIONS")) ;
    pStructAttr[0].ConfiscateItem(pAttr0Item) ;
    delete pAttr0Item ;
    // we still need to fill in the elements pDims

    // Structure of Attr[1]
    // --------------------
    Datum     *pAttr1Item = new Datum ;
    Datum     *pBounds = new Datum[lDim] ;
    pAttr1Item->Sequence(pBounds,lDim) ;
    pStructAttr[1].AttrName(_T("COM-LOWER-BOUNDS")) ;
    pStructAttr[1].ConfiscateItem(pAttr1Item) ;
    delete pAttr1Item ;
    // we still need to fill in the elements of pBounds


    // Fill in the elements of the 2 sequences.
    // Determine how many elements there are.
    // ---------------------------------------
    long    totalElements = 1 ;
    for (long lX = 0 ; lX < lDim ; lX++)
    {
        totalElements *= pSA->rgsabound[lX].cElements;
        pDims[lDim-lX-1].Long(pSA->rgsabound[lX].cElements) ;
        pBounds[lDim-lX-1].Long(pSA->rgsabound[lX].lLbound) ;
    }

    // Structure of Attr[2]
    // --------------------
    Datum     *pAttr2Item = new Datum ;
    Datum     *pValues = new Datum[totalElements] ;
    pAttr2Item->Sequence(pValues, totalElements) ;
    pStructAttr[2].AttrName(_T("COM-ELEMENTS")) ;
    pStructAttr[2].ConfiscateItem(pAttr2Item) ;
    delete pAttr2Item ;

    // Fill in the elements of of the sequence in Attr[2]
    // --------------------------------------------------
    SafeArrayLock(pSA);
    void *ptr = pSA->pvData ;

    USES_CONVERSION ;
    for (long L2 = 0 ; L2 < totalElements ; L2++)
    {
        switch (vtyp)
        {
        case VT_UI1:
            pValues[L2].Long((long) *((unsigned char *) ptr));
            break;
        case VT_I2:
            pValues[L2].Long((long) *((short *) ptr));
            break;
        case VT_I4:
            pValues[L2].Long((long) *((long *) ptr));
            break;
        case VT_R4:
            pValues[L2].Float((double) *((float *) ptr));
            break;
        case VT_R8:
            pValues[L2].Float((double) *((double *) ptr));
            break;
        case VT_CY:
            pValues[L2].Currency((CURRENCY *) ptr);
            break;
        case VT_BSTR:
            pValues[L2].String(OLE2T(*((BSTR *) ptr)));
            break;
        case VT_BOOL:
            pValues[L2].Logical((*((VARIANT_BOOL*)ptr) == VARIANT_TRUE) ? GSI_TRUE : GSI_FALSE);
            break;
        case VT_DATE:
            pValues[L2].Date(*((DATE *) ptr));
            break;
        case VT_VARIANT:
            pValues[L2]= *((VARIANT *) ptr) ;
            break;
        default:
            setToNull() ;
            SafeArrayUnlock(pSA);
            return *this ;
        }
        ptr = (void *) (((char *) ptr) + pSA->cbElements);  // point to next item
    }
    SafeArrayUnlock(pSA);

    // Finally set the element type in the 4th attribute
    // -------------------------------------------------
    pStructAttr[3].AttrName(_T("COM-ARRAY-TYPE")) ;
    Datum *pType = new Datum ;
    switch (vtyp)
    {
        case VT_UI1:
            pType->Symbol(_T("COM-BYTE"));
            break;
        case VT_I2:
            pType->Symbol(_T("COM-INTEGER"));
            break;
        case VT_I4:
            pType->Symbol(_T("COM-LONG"));
            break;
        case VT_R4:
            pType->Symbol(_T("COM-FLOAT"));
            break;
        case VT_R8:
            pType->Symbol(_T("COM-DOUBLE"));
            break;
        case VT_CY:
            pType->Symbol(_T("COM-CURRENCY"));
            break;
        case VT_BSTR:
            pType->Symbol(_T("COM-STRING"));
            break;
        case VT_BOOL:
            pType->Symbol(_T("COM-BOOLEAN"));
            break;
        case VT_DATE:
            pType->Symbol(_T("COM-DATE"));
            break;
        case VT_VARIANT:
            pType->Symbol(_T("COM-VARIANT"));
            break;
        default:
            pType->setToNull() ;
            break;
    }
    pStructAttr[3].ConfiscateItem(pType) ;
    delete pType ;
    return *this ;
}


/* ========================================================================== */
/*                                                                            */
/*                Create the gsi_item equivalent of this Datum.               */
/*                                                                            */
/* Normally, it would be necessary to pass either the address of gsItem or a  */
/* reference to it.  However gsi_items are actually pointers, so this works.  */
/*                                                                            */
/* ========================================================================== */
void Datum::toGsiItem(gsi_item gsiItem)
{
    gsi_item    *pGsiElements;
    gsi_attr    *pGsiAttrs;
    gsi_char*   *pGsiTxt ;
    gsi_int     *pGsiInt ;
    gsi_symbol  *pGsiSym ;
    double      *pGsiFlt ;
    TCHAR       *pStr ;
    long        lX ;
    
    // If this an an item, set the class name, name, 
    // attributes & user data of the GsiItem
    // ---------------------------------------------
    if (mIsItem)
    {
        // Set the Class name of the gsi_item
        // ----------------------------------
        if (mpClassName)
            gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)mpClassName)) ;

        // Set the gsi_item's name
        // -----------------------
        if (mpName)
            gsi_set_name(gsiItem, gsi_make_symbol((gsi_char *)mpName)) ;

        // If there are attributes, attach them to the gsi_item
        // ----------------------------------------------------
        if (mpAttrs && mNrAttrs > 0)
        {
            gsi_attr    *pAttrs = gsi_make_attrs(mNrAttrs) ;
            if (pAttrs)
            {
                for (long lX=0 ; lX < mNrAttrs ; lX++)
                    Attribute::Attribute2gsiAttr(mpAttrs[lX], pAttrs[lX]) ;
            }
            gsi_set_attrs(gsiItem, pAttrs, mNrAttrs) ;
        }

        // Attach the user data, if present.
        // --------------------------------
        if (mpUserData)
        {
            gsi_item    ud = gsi_make_item() ;
            mpUserData->toGsiItem(ud) ;
            gsi_set_user_data(gsiItem, ud) ;
        }
    }

    switch(mType)
    {
        case GSI_NULL_TAG:      if (!mIsItem)
                                    gsi_set_sym(gsiItem, gsi_make_symbol((gsi_char *)_T("NULL"))) ;
                                break;
        case GSI_INTEGER_TAG:   gsi_set_int(gsiItem, Long()) ;
                                break;
        case GSI_SYMBOL_TAG:    pStr = Symbol() ;
                                gsi_set_sym(gsiItem, gsi_make_symbol((gsi_char *)pStr)) ;
                                delete [] pStr ;
                                break;
        case GSI_STRING_TAG:    pStr = String() ;
                                gsi_set_str(gsiItem, (gsi_char *)pStr) ;
                                delete [] pStr ;
                                break;
        case GSI_LOGICAL_TAG:   gsi_set_log(gsiItem, Boolean() ? GSI_TRUE : GSI_FALSE) ;
                                break;
        case GSI_FLOAT64_TAG:   gsi_set_flt(gsiItem, Float()) ;
                                break;
        case GSI_ITEM_TAG:      ATLTRACE("Datum of ITEM should be impossible.  gsi_item set to NULL.\n") ;
                                gsi_set_sym(gsiItem, gsi_make_symbol((gsi_char *)_T("NULL"))) ;
                                break;
        case GSI_HANDLE_TAG:    ATLTRACE("Datum of HANDLE should be impossible.  gsi_item set to NULL.\n") ;
                                gsi_set_sym(gsiItem, gsi_make_symbol((gsi_char *)_T("NULL"))) ;
                                break;
        case GSI_UNSIGNED_SHORT_VECTOR_TAG:
                                gsi_set_usv(gsiItem,USV(),Length()) ;
                                break ;
        case GSI_INTEGER_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("INTEGER-ARRAY"))) ;
                                goto intmerge ;
        case GSI_SYMBOL_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("SYMBOL-ARRAY"))) ;
                                goto symmerge ;
        case GSI_STRING_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("TEXT-ARRAY"))) ;
                                goto txtmerge ;
        case GSI_LOGICAL_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("TRUTH-VALUE-ARRAY"))) ;
                                goto intmerge ;
        case GSI_FLOAT64_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("FLOAT-ARRAY"))) ;
                                goto fltmerge ;
        case GSI_ITEM_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("ITEM-ARRAY"))) ;
                                goto itmerge ;
        case GSI_VALUE_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("VALUE-ARRAY"))) ;
                                goto itmerge ;
        case GSI_ITEM_OR_VALUE_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("G2-ARRAY"))) ;
                                goto itmerge ;
        case GSI_QUANTITY_ARRAY_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("QUANTITY-ARRAY"))) ;
                                goto itmerge ;
        case GSI_INTEGER_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("INTEGER-LIST"))) ;
                                goto intmerge ;
        case GSI_SYMBOL_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("SYMBOL-LIST"))) ;
symmerge:
                                pGsiSym = new gsi_symbol [mLength] ;
                                for (lX = 0 ; lX < mLength; lX++)
                                {
                                    pStr = mValue.pElements[lX].Symbol() ;
                                    pGsiSym[lX] = gsi_make_symbol((gsi_char *)pStr) ;
                                    delete [] pStr ;
                                }
                                gsi_set_type(gsiItem, mType) ;
                                if (mType==GSI_SYMBOL_ARRAY_TAG)
                                    gsi_set_sym_array(gsiItem, pGsiSym, mLength) ;
                                else if (mType==GSI_SYMBOL_LIST_TAG)
                                    gsi_set_sym_list(gsiItem, pGsiSym, mLength) ;
                                delete [] pGsiSym ;
                                break ;
        case GSI_STRING_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("TEXT-LIST"))) ;
txtmerge:
                                pGsiTxt = new gsi_char* [mLength] ;
                                for (lX = 0 ; lX < mLength; lX++)
                                {
                                    pGsiTxt[lX] = (gsi_char *)mValue.pElements[lX].String() ;
                                }
                                gsi_set_type(gsiItem, mType) ;
                                if (mType==GSI_STRING_ARRAY_TAG)
                                    gsi_set_str_array(gsiItem, pGsiTxt, mLength) ;
                                else if (mType==GSI_STRING_LIST_TAG)
                                    gsi_set_str_list(gsiItem, pGsiTxt, mLength) ;
                                for (lX = 0 ; lX < mLength; lX++)
                                    delete [] pGsiTxt[lX] ;
                                delete [] pGsiTxt ;
                                break ;

        case GSI_LOGICAL_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("TRUTH-VALUE-LIST"))) ;
intmerge:
                                pGsiInt = new gsi_int [mLength] ;
                                for (lX = 0 ; lX < mLength; lX++)
                                    pGsiInt[lX] = mValue.pElements[lX].Long() ;
                                gsi_set_type(gsiItem, mType) ;
                                if (mType==GSI_INTEGER_ARRAY_TAG)
                                    gsi_set_int_array(gsiItem, pGsiInt, mLength) ;
                                else if (mType==GSI_INTEGER_LIST_TAG)
                                    gsi_set_int_list(gsiItem, pGsiInt, mLength) ;
                                else if (mType==GSI_LOGICAL_ARRAY_TAG)
                                    gsi_set_log_array(gsiItem, pGsiInt, mLength) ;
                                else if (mType==GSI_LOGICAL_LIST_TAG)
                                    gsi_set_log_list(gsiItem, pGsiInt, mLength) ;
                                delete[] pGsiInt ;
                                break ;
        case GSI_FLOAT64_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("FLOAT-LIST"))) ;
fltmerge:
                                pGsiFlt = new double[mLength] ;
                                for (lX = 0 ; lX < mLength ; lX++)
                                    pGsiFlt[lX] = mValue.pElements[lX].Float() ;
                                gsi_set_type(gsiItem, mType) ;
                                if (mType==GSI_FLOAT64_ARRAY_TAG)
                                    gsi_set_flt_array(gsiItem, pGsiFlt, mLength) ;
                                else 
                                    gsi_set_flt_list(gsiItem, pGsiFlt, mLength) ;
                                delete[] pGsiFlt ;
                                break ;

        case GSI_ITEM_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("ITEM-LIST"))) ;
                                goto itmerge ;
        case GSI_VALUE_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("VALUE-LIST"))) ;
                                goto itmerge ;
        case GSI_ITEM_OR_VALUE_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("G2-LIST"))) ;
                                goto itmerge ;
        case GSI_QUANTITY_LIST_TAG:
                                gsi_set_class_name(gsiItem, gsi_make_symbol((gsi_char *)_T("QUANTITY-LIST"))) ;
itmerge:
        case GSI_SEQUENCE_TAG:                     
                                pGsiElements = gsi_make_items(mLength) ;

                                for (lX = 0 ; lX < mLength ; lX++)
                                     mValue.pElements[lX].toGsiItem(pGsiElements[lX]) ;
                                gsi_set_elements(gsiItem, pGsiElements, mLength, mType) ;
                                break;
                                
        case GSI_STRUCTURE_TAG:
                                gsi_set_type(gsiItem, GSI_STRUCTURE_TAG) ;
                                pGsiAttrs = gsi_make_attrs(mNrAttrs) ;
                                for (lX = 0 ; lX < mNrAttrs ; lX++)
                                    Attribute::Attribute2gsiAttr(mpAttrs[lX], pGsiAttrs[lX]) ;
                                gsi_set_attrs(gsiItem, pGsiAttrs, mNrAttrs) ;
                                break;

        // Not valid.  Should never happen per gsi_type_of() spec.
        case GSI_VALUE_TAG:     ATLTRACE("Datum of type VALUE not supported.  Setting gsi_item to type NULL\n") ;
                                gsi_set_sym(gsiItem, gsi_make_symbol((gsi_char *)_T("NULL"))) ;
                                break ;      

        // Not valid.  Should never happen per gsi_type_of() spec.
        case GSI_QUANTITY_TAG:  ATLTRACE("Datum of type QUANTITY not supported.  Setting gsi_item to type NULL\n") ;
                                gsi_set_sym(gsiItem, gsi_make_symbol((gsi_char *)_T("NULL"))) ;
                                break ;      

        default:                ATLTRACE("UNKNOWN Datum type.  Setting gsi_item to type NULL\n") ;
                                gsi_set_sym(gsiItem, gsi_make_symbol((gsi_char *)_T("NULL"))) ;
                                break ;      
    }

}


//============================================================================//
//                                                                            //
//         If the type of this Datum is String, change it to Symbol           //
//                                                                            //
//============================================================================//
void Datum::Symbolize()
{
    if (mType == GSI_STRING_TAG)
        mType = dtySymbol ;
}


//============================================================================//
//                                                                            //
//         If the type of this Datum is Symbol, change it to String           //
//                                                                            //
//============================================================================//
void Datum::Stringify()
{
    if (mType == GSI_SYMBOL_TAG)
        mType = dtyString ;
}


// =================================================================
//
//                 Make this Datum a Sequence.
//
//   Note: This method does not make a copy of the Datums pointed
//         to by pElements.  It takes ownership of them!
//
// =================================================================
void Datum::Sequence(Datum *pElements, long lNrElements, bool zapFlag)
{
    if (zapFlag) 
        Zap() ;
    else
        zapValue() ;
    mLength = lNrElements;
    mValue.pElements = pElements ;
    mType = dtySequence ;
}


// ========================================================================== //
//                                                                            //
//     If this is a sequence, return a pointer to the sequence elements.      //
//                     Otherwise, throw an exception.                         //
//                                                                            //
// ========================================================================== //
Datum* Datum::Sequence()
{
    if (mType != GSI_SEQUENCE_TAG)
    {
        ATLTRACE("Type mismatch. Type %ld, not a sequence.\n" , mType) ;
#ifdef _DEBUG
        throw TYPE_MISMATCH ;
#endif
        return NULL ;
    }
	return mValue.pElements ;
}


// ============================================================================
//
// This is similar to the assignment operator, but instead of making a copy of
// dynamically allocated elements of the contained sub-elements, it takes them
// over.  It then zeros the source AxiItem so that it can be deleted without 
// erasing the elements that this Datum is now using.
//
// ============================================================================
void Datum::Confiscate(Datum *pSrc)
{
    memcpy(this, pSrc, sizeof(Datum)) ;
    memset(pSrc, 0, sizeof(Datum)) ;
}


/* ==================================================================================== */
/*                                                                                      */
/* Copy element # elNr from the specified SafeArray of type vt to the specified VARIANT */
/*                                                                                      */
/* ==================================================================================== */
HRESULT Datum::ArrayElement2Var(VARTYPE vt, long elNr, void* startOfArray, VARIANT *pOut)
{
    CComBSTR    helper ;
    HRESULT     hr ;
    IDispatch*  pIDsp ;
    IUnknown*   pIUnk ;
    long        elType = vt & VT_TYPEMASK ;

    switch (elType)
    {
        // integer
    case VT_I2:
        pOut->vt = VT_I2 ;
        pOut->iVal = ((short*)startOfArray)[elNr] ;
        break ;

        // long
    case VT_I4:
        pOut->vt = VT_I4 ;
        pOut->lVal = ((long*)startOfArray)[elNr] ;
        break ;

        // single
    case VT_R4:
        pOut->vt = VT_R4 ;
        pOut->fltVal = ((float*)startOfArray)[elNr] ;
        break ;

        // double
    case VT_R8:
        pOut->vt = VT_R8 ;
        pOut->dblVal = ((double*)startOfArray)[elNr] ;
        break ;

        // currency
    case VT_CY:
        pOut->vt = VT_CY ;
        pOut->cyVal = ((CY*)startOfArray)[elNr] ;
        break ;

        // date
    case VT_DATE:
        pOut->vt = VT_DATE ;
        pOut->date = ((DATE*)startOfArray)[elNr] ;
        break ;

        // text
    case VT_BSTR:
        pOut->vt = VT_BSTR ;
        helper = ((BSTR*)startOfArray)[elNr] ;
        pOut->bstrVal = helper.Copy();
        break ;

        // object
    case VT_DISPATCH:
        pOut->vt = VT_DISPATCH ;
        pOut->pdispVal = ((IDispatch**)startOfArray)[elNr] ;
        pOut->pdispVal->AddRef();
        break ;

        // boolean
    case VT_BOOL:
        pOut->vt = VT_BOOL ;
        pOut->boolVal = ((VARIANT_BOOL*)startOfArray)[elNr] ;
        break ;

        // variant
    case VT_VARIANT:
        VariantCopyInd(pOut,((VARIANT*)startOfArray)+elNr);
        break ;
        
        // IUnknown pointer of object.  Needed for .NET.
    case VT_UNKNOWN:
         pIUnk = ((IUnknown**)startOfArray)[elNr] ;
         hr = pIUnk->QueryInterface(IID_IDispatch, reinterpret_cast<void**>(&pIDsp)) ;
         if (SUCCEEDED(hr))
         {
            pOut->vt = VT_DISPATCH ;
            pOut->pdispVal = pIDsp ;
         }
         else
         {
            pOut->vt = VT_UNKNOWN ;
            pOut->punkVal = pIUnk ;
            pIUnk->AddRef();
         }
         break ;
        
        // byte
    case VT_UI1:
        pOut->vt = VT_UI1 ;
        pOut->uiVal =((UCHAR*)startOfArray)[elNr] ;
        break ;

        // The following types are not supported by Visual Basic.  They can,
        // however, be used with C++ clients.
        // -----------------------------------------------------------------

        // signed char
    case VT_I1:
        pOut->vt = VT_I1 ;
        pOut->cVal = ((CHAR*)startOfArray)[elNr] ;
        break ;

        // unsigned short
    case VT_UI2:
        pOut->vt = VT_UI2 ;
        pOut->uiVal = ((USHORT*)startOfArray)[elNr] ;
        break ;

        // unsigned int
    case VT_UI4:
        pOut->vt = VT_UI4 ;
        pOut->ulVal = ((ULONG*)startOfArray)[elNr] ;
        break ;

        // other types are not supported
    default:
        return E_INVALIDARG ;
    }
    return S_OK ;
}


// ===============================================================
//
// Translate the received IDispatch* (which must be a G2ComObject)
// to its equivalent Datum type.
//
// ===============================================================
void Datum::G2ComItem(IDispatch *pIDisp)
{
    BSTR                bstrSymTxt ;
	G2ComObject			*pG2ComObj ;
	HRESULT				hr ;
    IEnumVARIANT        *pIEnumVar ;
    IG2Item4*           pIG2Item4 ;
    IG2ItemRef*         pIG2ItemRef = NULL ;
    IG2ListOrArray*     pIG2ListOrArray ;
    IG2Structure*       pG2Struct ;
    IG2StructureEntry*  pG2StructEnt ;
    IG2Symbol *         pIG2Sym ;
    long                lX ;
    LPUNKNOWN           pIEnum1 ;
    unsigned short      uuid[8] ;

	// Verify that it is a G2ComObject
	// -------------------------------
    hr = pIDisp->QueryInterface(IID_G2ComObject, (void**)&pG2ComObj);  // rc=2
    if (FAILED(hr))
    {
        ATLTRACE2(atlTraceGeneral,0,"DISPATCH only supported for G2ComObjects.  Returning NULL.\n");
        return ;
    }

	USES_CONVERSION ;

    // If it is a G2Symbol, fill in this Datum and return
    // ----------------------------------------------------
    hr = pG2ComObj->QueryInterface(IID_IG2Symbol, (void**)&pIG2Sym) ;  //rc=3 if successful
    if (SUCCEEDED(hr))
    {
        pG2ComObj->Release() ;                                         //rc=2
        pIG2Sym->get_Item(&bstrSymTxt) ;
        pIG2Sym->Release() ;                                           //rc=1
        Symbol(OLE2T(bstrSymTxt)) ;
        ::SysFreeString(bstrSymTxt) ;
        return ;
    }

    // IG2ItemRef -> UUID
    // ------------------
    hr = pG2ComObj->QueryInterface(IID_IG2ItemRef, (void**)&pIG2ItemRef); // rc=3 if successful
    if (SUCCEEDED(hr))
    {
        // Extract the UUID, validate the results, and manage the reference count
        // ----------------------------------------------------------------------
        pG2ComObj->Release() ;                                            // rc=2
        hr = pIG2ItemRef->Git(uuid, &lX) ;
        pIG2ItemRef->Release() ;                                          // rc=1 
        if (FAILED(hr))
        {
            ATLTRACE("G2ItemRef UUID extraction failed.  Returning NULL.\n");
            return;
        }

         short i, ored ;
         for (i=0, ored=0  ; i < 8 ; i++)
             ored |= uuid[i] ;
         if (!ored)
         {
             ATLTRACE("Invalid UUID.  Setting to NULL.");
             return  ;
         }

         // Set the type and value of this Datum
         // ------------------------------------
         USV(uuid, 8) ;
         mpCtx = lX ;
         return ;
    }    

    // G2Item -> Datum Item
    // ----------------------
    hr = pG2ComObj->QueryInterface(IID_IG2Item4, (void**)&pIG2Item4);
    if (SUCCEEDED(hr))
    {
        Datum   *pOrgDatum = NULL;

        pG2ComObj->Release() ;
        pIG2Item4->Git2((long*)&pOrgDatum) ;
        *this = *pOrgDatum ;

        // If it is a window, we need to attach the user mode attribute
        // ------------------------------------------------------------
        IG2Window   *pIWin ;

        hr = pIG2Item4->QueryInterface(IID_IG2Window, (void**)&pIWin) ;
        if (SUCCEEDED(hr))
        {
            BSTR    mode ;

            pIG2Item4->Release() ;
            hr = pIWin->get_g2UserMode(&mode) ;

            // Create a new block of pointers to attributes leaving an extra pointer
            // for the new g2-user-mode attribute.
            // ---------------------------------------------------------------------
            long        nrAttrs = mNrAttrs ; 
            Attribute   *pNewAttrs = new Attribute[nrAttrs+1] ;

            // Confiscate the original set of pointers.  Then zero the original set
            // so we can delete the block of memory without deleting the Attributes.
            // --------------------------------------------------------------------
            memcpy(pNewAttrs,mpAttrs, sizeof(Attribute*) * nrAttrs) ;
            memset(mpAttrs,0,sizeof(Attribute*) * nrAttrs) ;
            delete [] mpAttrs ;
            mpAttrs = pNewAttrs ;

            // Fill in the new g2-user-mode attribute.
            // ---------------------------------------
            mpAttrs[nrAttrs].AttrName(_T("G2-USER-MODE")) ;
            
            USES_CONVERSION ;
            Datum *pNewItemofAttr = new Datum ;
            pNewItemofAttr->Symbol(OLE2T(mode)) ;
            mpAttrs[nrAttrs].ConfiscateItem(pNewItemofAttr) ;
            delete pNewItemofAttr ;
            mNrAttrs++ ;
            pIWin->Release() ;
            return ;
        }
        return ;
    }

    // --------------------------------------------------------------
    // Convert G2ListOrArray to an Datum containing a list or array
    // --------------------------------------------------------------
    VARIANT     varX ;

    hr = pG2ComObj->QueryInterface(IID_IG2ListOrArray, (void**)&pIG2ListOrArray);
    if (SUCCEEDED(hr))
    {
        pG2ComObj->Release() ;
        hr = pIG2ListOrArray->get_Type((G2Type*)(&mType)) ;
        if (FAILED(hr))
        {
            ATLTRACE("Unable to get list/array type.  Returning NULL.\n") ;
            pIG2ListOrArray->Release() ;
            return ;
        }
        hr = pIG2ListOrArray->get_Count(&mLength) ;
        if (FAILED(hr))
        {
            mType = dtyNull ;
            pIG2ListOrArray->Release() ;
            ATLTRACE("Unable to get number of list/array elements.  Returning NULL.\n") ;
            return ;
        }

        mValue.pElements = (mLength > 0) ? new Datum[mLength] : NULL ;
        if (mLength && mValue.pElements == NULL) 
        {
            ATLTRACE("Element allocation failed.  Returning NULL.\n") ;
            mType = dtyNull ;
            mLength = 0 ;
            pIG2ListOrArray->Release() ;
            return ;
        }

        // Loop through the elements extracting them one-by-one into a Variant and then
        // copying the value from the Variant to the Datums pointed to by mValue.pElements.
        // ----------------------------------------------------------------------------------
        VariantInit(&varX) ;
        for (lX = 0 ; lX < mLength; lX++)
        {
            hr = pIG2ListOrArray->get_Item(lX, &varX) ;
            if (FAILED(hr))
            {
                ATLTRACE("Failed to read element of array or list.  Returing NULL.\n") ;
                pIG2ListOrArray->Release() ;
                Zap() ;
                return ;
            }
            mValue.pElements[lX] = varX ;
            VariantClear(&varX) ;
        }
        pIG2ListOrArray->Release() ;
        return ;
    }

    // ------------------------------------------
    // Initialize this Datum from a G2Structure
    // ------------------------------------------
    BSTR            bstrX ;
    unsigned long   nrFetched ;
    VARIANT         varVal ;

    hr = pG2ComObj->QueryInterface(IID_IG2Structure,reinterpret_cast<void**>(&pG2Struct));  // rc=3 on success
    if (SUCCEEDED(hr))
    {
        pG2ComObj->Release();                                                               // rc=2
        hr = pG2Struct->get_Count(&mNrAttrs);
        if (FAILED(hr))
        {
            pG2Struct->Release();
            ATLTRACE("*** Unable to read number of structure attributes.  Returning NULL.\n") ;
            return ;
        }

        // Get an enumerator that we can use to process each
        // G2StructureEntry in this G2Structure
        // -------------------------------------------------
        hr = pG2Struct->get__NewEnum(&pIEnum1);
        pG2Struct->Release();                                                                // rc=1 
        if (FAILED(hr))
        {
            ATLTRACE("Unable to get structure enumerator.  Returning NULL.\n") ;
            return ;
        }
        hr = pIEnum1->QueryInterface(IID_IEnumVARIANT, (void**)&pIEnumVar);
        pIEnum1->Release();
        if (FAILED(hr))
        {
            ATLTRACE("Unable to use structure enumerator.  Returning NULL.\n") ;
            return ;
        }

        // Create the Datum structure
        // ---------------------------
        mpAttrs = new Attribute[mNrAttrs];
        if (mNrAttrs && mpAttrs == NULL)
            goto noStruct ;
        hr = pIEnumVar->Reset();
        if (FAILED(hr))
            goto noStruct ;
        VariantInit(&varX);
        VariantInit(&varVal) ;
        for (lX = 0 ; lX < mNrAttrs ; lX++)
        {
            /* Get VARIANT that contains next G2StructureEntry */
            /* ----------------------------------------------- */
            pIEnumVar->Next(1, &varX, &nrFetched);
            if (!nrFetched)
                goto noStruct ;

            /* Make sure VARIANT contains a G2StructureEntry */
            /* --------------------------------------------- */
            if (varX.vt != VT_DISPATCH && varX.vt != (VT_DISPATCH|VT_BYREF))
            {
                VariantClear(&varX) ;
                goto noStruct ;
            }
            pIDisp = (varX.vt == VT_DISPATCH) ? varX.pdispVal : *(varX.ppdispVal);
            hr = pIDisp->QueryInterface(IID_IG2StructureEntry, (void**)&pG2StructEnt);
            VariantClear(&varX) ;
            if (FAILED(hr))
                goto noStruct ;

            /* Get Name and Value from this G2StructureEntry */
            /* --------------------------------------------- */
            hr = pG2StructEnt->get_Name(&bstrX);
            if (FAILED(hr))
            {
                pG2StructEnt->Release();
                goto noStruct ;
            }
            hr = pG2StructEnt->get_Value(&varVal);
            pG2StructEnt->Release();
            if (FAILED(hr))
            {
                ::SysFreeString(bstrX) ;
                goto noStruct ;
            }

            /* Store them in the attributes of the GSI structure */
            /* ------------------------------------------------- */
            mpAttrs[lX].FillIn(OLE2T(bstrX),varVal) ;
            SysFreeString(bstrX) ;
            VariantClear(&varVal);
        }
        pIEnumVar->Release();
        mType = dtyStructure ;
        return;
noStruct:
        pIEnumVar->Release();
        return ;
    }
    ATLTRACE("Forbidden or unknown object type.  Returning NULL.\n") ;
    return ;
}


//============================================================================//
//                                                                            //
//         Return a pointer to the Attribute with the specified name          //
//                            or NULL if not found.                           //
//   The caller is responsible for the capitalization of the attribute name.  // 
//                                                                            //
//============================================================================//
Attribute*  Datum::FindAttributeNamed(TCHAR *pSeek)
{
    Attribute*   retVal = NULL ;

    for (long lX = 0 ; lX < mNrAttrs ; lX++)
    {
        TCHAR   *pAttrName = mpAttrs[lX].AttrName() ;
        long    results = _tcscmp(pAttrName, pSeek) ;
        delete [] pAttrName ;
        if (!results)
            return mpAttrs + lX ;
    }
    return NULL ;
}


/* ========================================================================== */
/*                                                                            */
/*              Return a copy of the ClassName to the caller                  */
/*                                                                            */
/* ========================================================================== */
TCHAR* Datum::ClassName()
{
    TCHAR   *pRetVal = NULL ;

    if (mpClassName)
    {
        pRetVal = new TCHAR[_tcslen(mpClassName)+1] ;
        if (pRetVal)
            _tcscpy(pRetVal,mpClassName) ;
    }
    else
    {
        pRetVal = new TCHAR[1] ;
        if (pRetVal)
            pRetVal[0] = 0 ;
    }

    return pRetVal ;
}


/* ========================================================================== */
/*                                                                            */
/*                    Set the G2 class name of this Item.                     */ 
/*         This is meaningful only if the "Is a G2 Item" flag is set.         */
/*                                                                            */
/* ========================================================================== */
void Datum::ClassName(TCHAR *newClassName)
{
    if (mpClassName)
        delete [] mpClassName ;
    if (newClassName)
    {
        Itemize() ;
        mpClassName = new TCHAR[_tcslen(newClassName)+1] ;
        if (mpClassName)
            _tcscpy(mpClassName,newClassName) ;
    }
}


/* ========================================================================== */
/*                                                                            */
/*           Return a copy of the Name of this Item to the caller             */
/*                                                                            */
/* ========================================================================== */
TCHAR* Datum::Name()
{
    TCHAR   *pRetVal = NULL ;

    if (mpName)
    {
        pRetVal = new TCHAR[_tcslen(mpName)+1] ;
        if (pRetVal)
            _tcscpy(pRetVal,mpName) ;
    }
    else
    {
        pRetVal = new TCHAR[1] ;
        if (pRetVal)
            pRetVal[0] = 0 ;
    }

    return pRetVal ;
}


/* ========================================================================== */
/*                                                                            */
/*                        Set the name of this Item.                          */ 
/*         This is meaningful only if the "Is a G2 Item" flag is set.         */
/*                                                                            */
/* ========================================================================== */
void Datum::Name(TCHAR *newName)
{
    if (mpName)
        delete [] mpName ;
    if (newName)
    {
        Itemize() ;
        mpName = new TCHAR[_tcslen(newName)+1] ;
        if (mpName)
            _tcscpy(mpName,newName) ;
    }
}


/* ========================================================================== */
/*                                                                            */
/*             Set or clear the "Is a G2 Item" flag of this Datum.            */
/*                  The default (defined in header) is true.                  */
/*                                                                            */
/* ========================================================================== */
void Datum::Itemize(bool isItem)
{
    mIsItem = isItem ;
}


// =================================== A t t r i b u t e ==============================================

Attribute::Attribute()
{
    memset(this, 0, sizeof(Attribute)) ;   
}


//
// Release memory that holds the attribute name before
// destroying this object.
// 
// ====================================================
Attribute::~Attribute()
{
    if (mpName) 
        delete [] mpName ;
}


// Attribute Name Accessor
//
// =======================
TCHAR* Attribute::AttrName()
{
    TCHAR *pSrc = (mpName) ? mpName : _T("") ;
    TCHAR *pNameOut ;

    pNameOut = new TCHAR[_tcslen(pSrc)+1] ;
    _tcscpy(pNameOut, pSrc) ;

    return pNameOut ;
}


// Attribute Name Mutator
//
// ======================
void Attribute::AttrName(TCHAR *pNewName)
{
    if (mpName)
        delete [] mpName ;
    mpName = new TCHAR [_tcslen(pNewName)+1] ;
    if (mpName)
        _tcscpy(mpName, pNewName) ;
}


// ========================================================================== //
//                                                                            //
//                Make this Attribute a copy of another Attribute             //
//                                                                            //
// ========================================================================== //
Attribute& Attribute::operator=(Attribute& src)
{
    if (this != &src)
    {
        // If this Attribute is already in use, free the memory it is using
        // --------------------------------------------------------------
        if (mpName) 
            delete [] mpName ;
        if (mDatum.Type() != GSI_NULL_TAG)
            mDatum.setToNull() ;

        // Fill in the name & item of this object from the source object
        // -------------------------------------------------------------
        mpName = (src.mpName) ? new TCHAR [_tcslen(src.mpName)+1] : NULL ;
        if (mpName)
            _tcscpy(mpName, src.mpName) ;
        mDatum = src.mDatum ;
    }
    return *this ;
}


// ========================================================================== //
//                                                                            //
//            Fill in this Attribute from the specified gsi_attr              //
//                                                                            //
// ========================================================================== //
Attribute& Attribute::operator= (gsi_attr srcAttr)
{
    gsi_item    middleMan ;

    AttrName((TCHAR *)gsi_symbol_name(gsi_attr_name_of(srcAttr))) ;
    middleMan = gsi_item_of_attr(srcAttr) ;
    mDatum = middleMan ;

    return *this ;
}


// Fill in this Attribute's name and item value
//
// ==========================================
void Attribute::FillIn(TCHAR *pName, VARIANT val)
{
    AttrName(pName) ;
    mDatum = val ;
}


// Copy the Datum in this Attribute to an existing gsi_attr
//
// =====================================================
void Attribute::Attribute2gsiAttr(Attribute& src, gsi_attr& dst)
{
    gsi_set_attr_name(dst, gsi_make_symbol((gsi_char *)src.mpName)) ;

    gsi_item middleMan = gsi_make_item() ;
    src.mDatum.toGsiItem(middleMan) ;
    gsi_set_item_of_attr(dst, middleMan) ;
//  gsi_reclaim_item(middleMan) ;
}


// Careful: this returns a pointer to the original item, not a copy of it.
//
// =======================================================================
Datum* Attribute::ItemPtr()
{
    return &mDatum ;
}


// If the type of the contained Datum is String, change it to Symbol
//
// ===================================================================
void Attribute::Symbolize()
{
    mDatum.Symbolize() ;
}


// ============================================================================
//
// This is similar to the assignment operator, but instead of making a copy of
// dynamically allocated elements of the contained Datum, it takes them over.
// It then zeros the source AxiItem so that it can be deleted without erasing
// the elements that this Attribute is now using.
//
// ============================================================================
void Attribute::Confiscate(Attribute *pSrc)
{
    memcpy(this, pSrc, sizeof(Attribute)) ;
    memset(pSrc, 0, sizeof(Attribute)) ;
}


//============================================================================//
//                                                                            //
//         Similar to Confiscate except only the Datum is confiscated.        //
//                                                                            //
//                The caller is responsible for deleting *pSrc.               //
//                                                                            //
//============================================================================//
void Attribute::ConfiscateItem(Datum *pSrc)
{
    mDatum.Confiscate(pSrc) ;
}

//  If the value of this attribute is a symbol, change it to a string.
//
// ========================================================================== //
void Attribute::Stringify()
{
    mDatum.Stringify() ;
}


/* ========================================================================== */
/*                                                                            */
/*  Translation rules:                                                        */
/*                                                                            */
/*  Has attribute named:           Optionally:   Of type:     Variant type    */
/*  --------------------           -----------   --------     ------------    */
/*  COM-CURRENCY                                 float          VT_CY         */
/*  COM-SEVERITY                                 symbol         VT_ERROR      */
/*                                 OM-FACILITY   integer                      */
/*                                   COM-CODE    integer                      */
/*  COM-YEAR, COM-MONTH, COM-DAY                 integer                      */
/*                                   COM-HOUR    integer                      */
/*                                  COM-MINUTE   integer                      */
/*                                  COM-SECOND   integer                      */
/*  COM-INTEGER                                  integer        VT_I4         */
/*  COM-LONG                                     integer        VT_I4         */
/*  COM-FLOAT                                    float          VT_R4         */
/*  COM-DOUBLE                                   float          VT_R8         */
/*  COM-BYTE                                     integer        VT_UI1        */
/*  COM-ELEMENTS                                 sequence     VT_ARRAY | type */
/*                               COM-DIMENSIONS  sequence of integer          */
/*                             COM-LOWER-BOUNDS  integer or seq of int        */
/*                                                                            */
/* ========================================================================== */
bool Datum::legacyStructure(VARIANT *pVar)
{
    struct lup  {   TCHAR* attrName ;
                    DataType dty ; } lupTab[] = { {_T("COM-CURRENCY"), dtyFloat },
                                                  {_T("COM-SEVERITY"), dtySymbol },
                                                  {_T("COM-YEAR"), dtyInteger },
                                                  {_T("COM-INTEGER"), dtyInteger}, 
                                                  {_T("COM-LONG"), dtyInteger},
                                                  {_T("COM-FLOAT"), dtyFloat},
                                                  {_T("COM-DOUBLE"), dtyFloat},
                                                  {_T("COM-BYTE"), dtyInteger},
                                                  {_T("COM-ELEMENTS"), dtySequence} } ;
    const int nrEntries = sizeof(lupTab) / sizeof (lup) ;
    Attribute *pAtr ;

    // This is only valid if this Datum is of type structure
    // -----------------------------------------------------
    if (Type() != dtyStructure)
        return false ;

    for (int iX = 0 ; iX < nrEntries ; iX++)
    {
        if ((pAtr=FindAttributeNamed(lupTab[iX].attrName)) && pAtr->ItemPtr()->Type() == lupTab[iX].dty)
        {
            switch(iX)
            {       // Currency
                    // --------
            case 0: {
                        double        fVal = pAtr->ItemPtr()->Float() * 10000.0 ;
                        long          valHi = ((long) (fVal / (256.0 * 256.0 * 256.0 * 256.0)));
                        unsigned long valLo = (unsigned long) (
                                           fVal - (valHi * 256.0 * 256.0 * 256.0 * 256.0) + 0.5);
                        pVar->vt = VT_CY;
                        pVar->cyVal.Hi = valHi;
                        pVar->cyVal.Lo = valLo;
                                   
                        return true ;
                    }
                    
                    // Error Code
                    // ----------
            case 1: {
                        SCODE s = 0;
                        if (!_tcscmp(pAtr->ItemPtr()->mValue.pString, _T("FAILED")))
                            s = 0x8000000;

                        pAtr = FindAttributeNamed(_T("COM-FACILITY"));
                        if (pAtr)
                        {
                            if (pAtr->ItemPtr()->Type() != dtyInteger)
                                break ;
                            s |= ((pAtr->ItemPtr()->Long() & 0x7fff) << 16);
                        }

                        pAtr = FindAttributeNamed(_T("COM-CODE"));
                        if (pAtr)
                        {
                            if (pAtr->ItemPtr()->Type() != dtyInteger)
                                break ;
                            s |= (pAtr->ItemPtr()->Long() & 0xffff);
                        }
                        pVar->vt = VT_ERROR;
                        pVar->scode = s;
                        return true; 
                    }
                        
                    // Date
                    // ----
            case 2: {
                        SYSTEMTIME st;
                        st.wYear = (short) pAtr->ItemPtr()->Long();

                        pAtr = FindAttributeNamed(_T("COM-MONTH"));
                        if (!pAtr || pAtr->ItemPtr()->Type() != dtyInteger)
                            break;
                        st.wMonth = (short) pAtr->ItemPtr()->Long();

                        pAtr = FindAttributeNamed(_T("COM-DAY"));
                        if (!pAtr || pAtr->ItemPtr()->Type() != dtyInteger)
                            break;
                        st.wDay = (short) pAtr->ItemPtr()->Long();

                        st.wHour = st.wMinute = st.wSecond = st.wMilliseconds = 0;
                        pAtr = FindAttributeNamed(_T("COM-HOUR"));
                        if (pAtr)
                        {
                            if (pAtr->ItemPtr()->Type() != dtyInteger)
                                break;
                            st.wHour = (short) pAtr->ItemPtr()->Long();
                        }

                        pAtr = FindAttributeNamed(_T("COM-MINUTE"));
                        if (pAtr)
                        {
                            if (pAtr->ItemPtr()->Type() != dtyInteger)
                                break;
                            st.wMinute = (short) pAtr->ItemPtr()->Long();
                        }

                        pAtr = FindAttributeNamed(_T("COM-SECOND"));
                        if (pAtr)
                        {
                            if (pAtr->ItemPtr()->Type() != dtyInteger)
                                break;
                            st.wSecond = (short) pAtr->ItemPtr()->Long();
                        }

                        // Ok, we built the structure, now make it a variant

                        pVar->vt = VT_DATE;
                        HRESULT hr = SystemTimeToVariantTime(&st, &pVar->date);
                        if (FAILED(hr))
                            break ;

                        return true ;
                    }

                    // COM Integer
                    // -----------
            case 3: {
                        pVar->vt = VT_I2;
                        pVar->iVal = (short)(pAtr->ItemPtr()->Long() & 0xffff);
                        return true ;
                    }

                    // COM Long
                    // --------
            case 4: {
                        pVar->vt = VT_I4;
                        pVar->lVal = pAtr->ItemPtr()->Long() ;
                        return true ;
                    }

                    // COM Float
                    // ---------
            case 5: {
                        pVar->vt = VT_R4;
                        pVar->fltVal = (float) pAtr->ItemPtr()->Float() ;
                        return true ;
                    }

                    // COM Double
                    // ----------
            case 6: {
                        pVar->vt = VT_R8;
                        pVar->dblVal = pAtr->ItemPtr()->Float() ;
                        return true ;
                    }

                    // COM Byte
                    // --------
            case 7: {
                        pVar->vt = VT_UI1;
                        pVar->bVal = (BYTE)(pAtr->ItemPtr()->Long() & 0xff);
                        return true ;
                    }

                    // Multi-dimensional array
                    // -----------------------
            case 8: {
                        long    num_elements = pAtr->ItemPtr()->Count() ;
                        Datum*  pElements = pAtr->ItemPtr()->Sequence() ;
                        SAFEARRAYBOUND FAR* rgsabound;
                        int     num_dim;

                        // first, we need to find how many dims we have
                        pAtr = FindAttributeNamed(_T("COM-DIMENSIONS"));
                        if (pAtr)
                        {
                            if (pAtr->ItemPtr()->Type() != dtySequence)
                                break ;
                            num_dim = pAtr->ItemPtr()->Count(); 
                            rgsabound = new SAFEARRAYBOUND[num_dim];
                            Datum *pCounts = pAtr->ItemPtr()->Sequence() ;

                            long total_elements = 1;
                            for (int i = 0; i < num_dim; i++)
                            {
                                if (pCounts[i].Type() != dtyInteger)
                                {
                                    delete[] rgsabound;
                                    break;
                                }
                                long num = pCounts[i].Long();
                                total_elements *= num;
                                rgsabound[i].cElements = num;
                                rgsabound[i].lLbound = 0;  // default to zero
                            }
                            if (num_elements > total_elements)
                                num_elements = total_elements;
                        }
                        else
                        {
                            num_dim = 1;
                            rgsabound = new SAFEARRAYBOUND[1];
                            rgsabound[0].cElements = num_elements;
                            rgsabound[0].lLbound = 0;
                        }

                        pAtr = FindAttributeNamed(_T("COM-LOWER-BOUNDS"));
                        if (pAtr)
                        {
                            switch (pAtr->ItemPtr()->Type())
                            {
                            case dtyInteger:
                                {  // all the same
                                    long val = pAtr->ItemPtr()->Long() ;
                                    for (int i = 0; i < num_dim; i++)
                                    {
                                        rgsabound[i].lLbound = val;
                                    }
                                    break;
                                }
                            case GSI_SEQUENCE_TAG:
                                {
                                    int max = (int)pAtr->ItemPtr()->Count();
                                    if (max > num_dim)
                                        max = num_dim;
                                    Datum *pLbs = pAtr->ItemPtr()->Sequence();
                                    for (int i = 0; i < max; i++)
                                    {
                                        if (pLbs[i].Type() != dtyInteger)
                                        {
                                            delete[] rgsabound;
                                            break;
                                        }
                                        rgsabound[i].lLbound = pLbs[i].Long();
                                    }
                                    break;
                                }
                            default:
                                delete[] rgsabound;
                                break;
                            }
                        }
                        if (!rgsabound)
                            break ;

                        // we now have all of the array bounds set up,
                        // look at the array type

                        int type = VT_VARIANT;  // default
                        pAtr = FindAttributeNamed(_T("COM-ARRAY-TYPE"));
                        if (pAtr)
                        {
                            if (pAtr->ItemPtr()->Type() != dtySymbol)
                            {
                                delete[] rgsabound;
                                break;
                            }
                            TCHAR *symbol = pAtr->ItemPtr()->Symbol() ;
                            if (!_tcscmp(symbol, _T("COM-BYTE")))
                                type = VT_UI1;
                            else if (!_tcscmp(symbol, _T("COM-INTEGER")))
                                type = VT_I2;
                            else if (!_tcscmp(symbol, _T("COM-LONG")))
                                type = VT_I4;
                            else if (!_tcscmp(symbol, _T("COM-FLOAT")))
                                type = VT_R4;
                            else if (!_tcscmp(symbol, _T("COM-DOUBLE")))
                                type = VT_R8;
                            else if (!_tcscmp(symbol, _T("COM-CURRENCY")))
                                type = VT_CY;
                            else if (!_tcscmp(symbol, _T("COM-STRING")))
                                type = VT_BSTR;
                            else if (!_tcscmp(symbol, _T("COM-BOOLEAN")))
                                type = VT_BOOL;
                            else if (!_tcscmp(symbol, _T("COM-DATE")))
                                type = VT_DATE;
                            else if (!_tcscmp(symbol, _T("COM-VARIANT")))
                                type = VT_VARIANT;
                            else
                            {
                                delete [] rgsabound;
                                delete [] symbol ;
                                break ;
                            }
                            delete [] symbol ;
                        }

                        // we are ready to create the actual array

                        SAFEARRAY *psa = SafeArrayCreate(type, num_dim, rgsabound);
                        if (!psa)
                        {
                            delete[] rgsabound;
                            break;
                        }

                        SafeArrayLock(psa);

                        USES_CONVERSION;
                        bool failed = false;
                        void *ptr = psa->pvData;
                        for (int j = 0; j < num_elements; j++)
                        {
                            switch (type)
                            {
                            case VT_UI1:
                                if (pElements[j].Type() != dtyInteger)
                                {
                                    failed = true;
                                    break;
                                }
                                *((unsigned char *) ptr) = (unsigned char) (255 & pElements[j].Long());
                                break;
                            case VT_I2:
                                if (pElements[j].Type() != dtyInteger)
                                {
                                    failed = true;
                                    break;
                                }
                                *((short *) ptr) = (short) (0xffff & pElements[j].Long());
                                break;
                            case VT_I4:
                                if (pElements[j].Type() != dtyInteger)
                                {
                                    failed = true;
                                    break;
                                }
                                *((long *) ptr) = pElements[j].Long();
                                break;
                            case VT_R4:
                                if (pElements[j].Type() != dtyFloat)
                                {
                                    failed = true;
                                    break;
                                }
                                *((float *) ptr) = (float) pElements[j].Float();
                                break;
                            case VT_R8:
                                if (pElements[j].Type() != dtyFloat)
                                {
                                    failed = true;
                                    break;
                                }
                                *((double *) ptr) = pElements[j].Float();
                                break;
                            case VT_CY:
                                {
                                    if (pElements[j].Type() != dtyStructure)
                                    {
                                        failed = true;
                                        break;
                                    }
                                    VARIANT myVt;
                                    VariantInit(&myVt);
                                    if FAILED(pElements[j].toVariant(&myVt))
                                    {
                                        failed = true;
                                        break;
                                    }
                                    *((CURRENCY *) ptr) = myVt.cyVal;
                                    VariantClear(&myVt);
                                    break;
                                }
                            case VT_BSTR:
                                if (pElements[j].Type() != GSI_STRING_TAG)
                                {
                                    failed = true;
                                    break;
                                }
                                *((BSTR *) ptr) = SysAllocString(T2OLE(pElements[j].mValue.pString));
                                break;
                            case VT_BOOL:
                                if (pElements[j].Type() != dtyLogical)
                                {
                                    failed = true;
                                    break;
                                }
                                *((VARIANT_BOOL *) ptr) = (pElements[j].Long() >= 0) ? VARIANT_TRUE : VARIANT_FALSE;
                                break;
                            case VT_DATE:
                                {
                                    if (pElements[j].Type() != dtyStructure)
                                    {
                                        failed = true;
                                        break;
                                    }
                                    VARIANT myVt;
                                    VariantInit(&myVt);
                                    if FAILED(pElements[j].toVariant(&myVt))
                                    {
                                        failed = true;
                                        break;
                                    }
                                    *((DATE *) ptr) = myVt.date;
                                    break;
                                }
                            case VT_VARIANT:
                                if (FAILED(pElements[j].toVariant((VARIANT *) ptr)))
                                {
                                    failed = true;
                                    break;
                                }
                                break;
                            }
                            if (failed)
                                break;
                            ptr = (void *) (((char *) ptr) + psa->cbElements);
                        }
                        SafeArrayUnlock(psa);
                        delete[] rgsabound;
                        if (failed)
                        {
                            SafeArrayDestroy(psa);
                            break;
                        }
                        pVar->vt = VT_ARRAY | type;
                        pVar->parray = psa;

                        return true;
                    }
             }
        }
    }


    return false ;
}

