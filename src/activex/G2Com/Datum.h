// Datum.h: interface for the Datum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Datum_H__322AD2DE_ADE8_4FAC_9917_CD9F2A4262BB__INCLUDED_)
#define AFX_Datum_H__322AD2DE_ADE8_4FAC_9917_CD9F2A4262BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gsi_main.h>

class Attribute ;
class CG2Item ;


// ===================================================================
//
// Enumerator used to specity type of datum stored within datum object
//
// ===================================================================
enum DataType
{
    dtyNull           = GSI_NULL_TAG,
    dtyInteger        = GSI_INTEGER_TAG,
    dtySymbol         = GSI_SYMBOL_TAG,
    dtyString         = GSI_STRING_TAG,
    dtyLogical        = GSI_LOGICAL_TAG,
    dtyFloat          = GSI_FLOAT64_TAG,
    dtyItem           = GSI_ITEM_TAG,
    dtyValue          = GSI_VALUE_TAG,
    dtyHandle         = GSI_HANDLE_TAG,
    dtyQuantity       = GSI_QUANTITY_TAG,
    dtyUSV            = GSI_UNSIGNED_SHORT_VECTOR_TAG,
    dtyIntegerArray   = GSI_INTEGER_ARRAY_TAG,
    dtySymbolArray    = GSI_SYMBOL_ARRAY_TAG,
    dtyStringArray    = GSI_STRING_ARRAY_TAG,
    dtyLogicalArray   = GSI_LOGICAL_ARRAY_TAG,
    dtyFloatArray     = GSI_FLOAT64_ARRAY_TAG,
    dtyItemArray      = GSI_ITEM_ARRAY_TAG,
    dtyValueArray     = GSI_VALUE_ARRAY_TAG,
    dtyItemOrValArray = GSI_ITEM_OR_VALUE_ARRAY_TAG,
    dtyQuantityArray  = GSI_QUANTITY_ARRAY_TAG,    
    dtyIntegerList    = GSI_INTEGER_LIST_TAG,
    dtySymbolList     = GSI_SYMBOL_LIST_TAG,
    dtyStringList     = GSI_STRING_LIST_TAG,
    dtyLogicalList    = GSI_LOGICAL_LIST_TAG,
    dtyFloatList      = GSI_FLOAT64_LIST_TAG,
    dtyItemList       = GSI_ITEM_LIST_TAG,
    dtyValueList      = GSI_VALUE_LIST_TAG,
    dtyItemOrValList  = GSI_ITEM_OR_VALUE_LIST_TAG,
    dtyQuantityList   = GSI_QUANTITY_LIST_TAG,
    dtySequence       = GSI_SEQUENCE_TAG,
    dtyStructure      = GSI_STRUCTURE_TAG
} ;

class Datum
{
    friend class CG2Item ;

    // Private member variables
    // ------------------------
    DataType                            mType ;
    union wrapper
    {
        long            lngVal;
        double          dblVal;
        TCHAR*          pString;
        Datum*          pElements ;
        unsigned short  *pUsv;
                                   }    mValue ;
    long                                mLength;
    Attribute*                          mpAttrs ;
    long                                mNrAttrs ;
    bool                                mIsItem ;
    TCHAR*                              mpClassName ;
    TCHAR*                              mpName ;
    Datum*                              mpUserData ;
    long                                mpCtx ;
    bool                                mG2Sym ;

public:
    Datum();
    ~Datum();

    // Accessors
    // ---------
    TCHAR*          ClassName();
    TCHAR*          Name();
    DataType        Type();
    long            Long();
    double          Float();
    bool            Boolean();
    TCHAR*          String();
    TCHAR*          Symbol();
    unsigned short* USV();
    long            Length() { return mLength ; }
    long            Count() { return mLength; }
    long            NrAttrs() ;
    Datum*          LAElements();
    Datum*          Sequence() ;
    Datum*          UserDataPtr() ;
    Attribute*      Structure() ;
    Attribute*      Attributes();
    bool            IsItem() ;
    TCHAR*          CopyOfString() ;
    bool            G2Symbols() ;

    // Mutators
    // --------
    void            ClassName(TCHAR* newClassName);
    void            Name(TCHAR* newName) ;
    void            setToNull();
    void            Long(long lVal, bool zapFlag=true);
    void            Float(double dblVal, bool zapFlag=true);
    void            G2Symbols(bool wantIG2Symbol);
    void            Logical(long gsiLog, bool zapFlag=true);
    void            String(TCHAR* String, bool zapFlag=true);
    void            Symbol(TCHAR* Symbol, bool zapFlag=true);
    void            USV(unsigned short *pUSV, long lLen, bool zapFlag=true);
    void            Sequence(Datum *pElements, long lNrElements, bool zapFlag=true);
    void            ListOrArray(DataType typecode, Datum *pElements, long nrElements, bool zapFlag=true);
    void            Structure(Attribute *pAttributes, long nrAttrs);
    void            Attributes(Attribute *pAttributes, long nrAttributes);
    void            UserData(Datum* pUserData) ;
    void            G2ComItem(IDispatch *pIDsp);
    void            Itemize(bool isItem=true);
    void            Currency(CURRENCY *pCy);
    void            Date(DATE dt) ;
    void            ErrorCode(SCODE sc) ;
    void            Stringify();


    // Type Conversion methods
    // -----------------------
    void            toGsiItem(gsi_item gsiItem) ;
    HRESULT         toVariant(VARIANT *pVar);
    HRESULT         valueToVariant(VARIANT *pVar) ;
    static HRESULT  ArrayElement2Var(VARTYPE vt, long elNr, void* startOfArray, VARIANT *pOut);
    bool            legacyStructure(VARIANT *pVar);
    Datum&          internalAssignSA(SAFEARRAY *pSA, bool zapFlag) ;
    Datum&          internalVariantToDatum(VARIANT& varSrc, bool zapFlag) ;


    // Overridden Assignment Operators
    // -------------------------------
    Datum&           operator=(Datum&       axlSrc);
    Datum&           operator=(gsi_item&    gsiSrc) ;
    Datum&           operator=(VARIANT&     varSrc) ;
    Datum&           operator<<(VARIANT&    varSrc) ;
    Datum&           operator=(SAFEARRAY    *pSA) ;
    Datum&           operator<<(SAFEARRAY   *pSA) ;

    // Copy helpers
    // ------------
    Datum*          CopyOfListOrArrayOrSequence();
    Attribute*      CopyOfAttributes();
    static Datum*   makeItems(long nrItems) ;

    // Other helper methods
    // --------------------
    void            Confiscate(Datum *pSrc) ;
    Attribute*      FindAttributeNamed(TCHAR *pAttrName) ;
    void            Symbolize() ;
    void            Zap();
    void            zapValue() ;
};


// Thread-safe representation of gsi_attr
//
// ======================================
class Attribute  
{
private:
    TCHAR       *mpName;
    Datum       mDatum;
public:
    void Stringify();
    Attribute();
    ~Attribute();

    TCHAR*      AttrName();
    void        AttrName(TCHAR *pNewName);
    Datum*      ItemPtr();
    void        FillIn(TCHAR *pName, VARIANT varX) ;
    void        Symbolize() ;
    void        Confiscate(Attribute *pSrc) ;
    void        ConfiscateItem(Datum *pSrc) ;

    Attribute&  operator=(Attribute& src) ;
    Attribute&  operator=(gsi_attr srcAttr) ;

    static void Attribute2gsiAttr(Attribute& src, gsi_attr& dst) ;
};

#endif // !defined(AFX_Datum_H__322AD2DE_ADE8_4FAC_9917_CD9F2A4262BB__INCLUDED_)
