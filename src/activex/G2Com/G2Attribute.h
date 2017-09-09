// G2Attribute.h : Declaration of the CG2Attribute

#ifndef __G2ATTRIBUTE_H_
#define __G2ATTRIBUTE_H_

#include "resource.h"       // main symbols
#include "Datum.h"

/////////////////////////////////////////////////////////////////////////////
// CG2Attribute
class ATL_NO_VTABLE CG2Attribute : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2Attribute, &CLSID_G2Attribute>,
	public ISupportErrorInfo,
	public IDispatchImpl<IG2Attribute, &IID_IG2Attribute, &LIBID_GensymAxl, 2, 0>
{
public:
	CG2Attribute() ;

DECLARE_REGISTRY_RESOURCEID(IDR_G2ATTRIBUTE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CG2Attribute)
	COM_INTERFACE_ENTRY(IG2Attribute)
    COM_INTERFACE_ENTRY(G2ComObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IG2Attribute
    // G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);
    // G2Attribure
//  STDMETHOD(put_Name) (/*[in]*/           BSTR    attrName);
    STDMETHOD(get_Name) (/*[out, retval]*/  BSTR    *pName);
    STDMETHOD(put_Value) (/*[in]*/          VARIANT attrVal) ;
    STDMETHOD(get_Value) (/*[out, retval]*/ VARIANT *pVal);
    STDMETHOD(get_Type) (/*[out, retval]*/  G2Type  *pType);
    STDMETHOD(put_Type) (/*[in]*/           G2Type  nType);
    STDMETHOD(Init)(long pGsiAttr) ;
private:
    Attribute    *m_pAttr ;
public:
};

#endif //__G2ATTRIBUTE_H_
