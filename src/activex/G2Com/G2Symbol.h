// G2Symbol.h : Declaration of the CG2Symbol

#ifndef __G2SYMBOL_H_
#define __G2SYMBOL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CG2Symbol
class ATL_NO_VTABLE CG2Symbol : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2Symbol, &CLSID_G2Symbol>,
	public IDispatchImpl<IG2Symbol, &IID_IG2Symbol, &LIBID_GensymAxl, 2, 0>
{
public:
    CG2Symbol() : m_uc(VARIANT_TRUE)  { }

DECLARE_REGISTRY_RESOURCEID(IDR_G2SYMBOL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CG2Symbol)
	COM_INTERFACE_ENTRY(IG2Symbol)
    COM_INTERFACE_ENTRY(G2ComObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

public:
    // IG2Symbol
    // ---------
	STDMETHOD(get_UpperCase)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_UpperCase)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Item)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Item)(/*[in]*/ BSTR newVal);

    // IG2ComObj
    // ---------
    STDMETHOD(get_WhatAmI)(BSTR *WhatAmI) ;
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);
private:
	VARIANT_BOOL    m_uc;
	CComBSTR        m_cbstr;
};

#endif //__G2SYMBOL_H_
