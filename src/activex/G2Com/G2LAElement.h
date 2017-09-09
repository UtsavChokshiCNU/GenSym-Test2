// G2LAElement.h : Declaration of the CG2LAElement

#ifndef __G2LAELEMENT_H_
#define __G2LAELEMENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CG2LAElement
class ATL_NO_VTABLE CG2LAElement : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2LAElement, &CLSID_G2LAElement>,
	public IDispatchImpl<IG2LAElement, &IID_IG2LAElement, &LIBID_GensymAxl, 2, 0>
{
public:
	CG2LAElement()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_G2LAELEMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CG2LAElement)
	COM_INTERFACE_ENTRY(IG2LAElement)
	COM_INTERFACE_ENTRY(G2ComObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

public:
    // IG2LAElement
	STDMETHOD(get_Item)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_Value)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Value)(/*[in]*/ VARIANT newVal);
	STDMETHOD(Init)(/*[in]*/ IG2ListOrArray *pLaw, /*[in]*/ long idx);
    // G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);
private:
	long            m_idx;
	IG2ListOrArray* m_pLaw;
};

#endif //__G2LAELEMENT_H_
