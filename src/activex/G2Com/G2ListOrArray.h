// G2ListOrArray.h : Declaration of the CG2ListOrArray

#ifndef __G2ListOrArray_H_
#define __G2ListOrArray_H_

#include "G2Com.h"
#include "resource.h"       // main symbols
#include "gsi_main_cpp.h"

/////////////////////////////////////////////////////////////////////////////
// CG2ListOrArray
class ATL_NO_VTABLE CG2ListOrArray : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2ListOrArray, &CLSID_G2ListOrArray>,
	public ISupportErrorInfo,
	public IDispatchImpl<IG2ListOrArray, &IID_IG2ListOrArray, &LIBID_GensymAxl, 2, 0>
{
public:
    CG2ListOrArray() : m_pSA(NULL), m_varType(VT_EMPTY), m_lawType(g2Null)
	{
        ATLTRACE2 (atrG2ObjLife, 4, "##> G2ListOrArray at %08x created.\n", this);
	}
    void FinalRelease() ;

DECLARE_REGISTRY_RESOURCEID(IDR_G2LISTORARRAY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CG2ListOrArray)
	COM_INTERFACE_ENTRY(IG2ListOrArray)
    COM_INTERFACE_ENTRY(G2ComObject)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

public:
// IG2ListOrArray
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ LPUNKNOWN *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ G2Type *pVal);
	STDMETHOD(put_Type)(/*[in]*/ G2Type newVal);
	STDMETHOD(get_Item)(/*[in]*/ long idx, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Item)(/*[in]*/ long idx, /*[in]*/ VARIANT newVal);
	STDMETHOD(Insert)(/*[in]*/ long idx, /*[in]*/ VARIANT varX);
	STDMETHOD(Append)(/*[in]*/ long idx, /*[in]*/ VARIANT varX);
	STDMETHOD(Add)(/*[in]*/ VARIANT varX);
	STDMETHOD(Remove)(/*[in]*/ long idx);
	STDMETHOD(Init)(/*[in]*/ long pGsiItem);

// G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);

private:
    STDMETHOD(castVal)(VARIANT valIn, VARIANT *pValOut) ;
    STDMETHOD(Redim)(unsigned long nrBefore, bool booNew, unsigned long nrAfter, VARIANT *newVal) ;

    G2Type      m_lawType ;
	VARTYPE     m_varType;
    SAFEARRAY * m_pSA ;
} ;
#endif //__G2ListOrArray_H_
