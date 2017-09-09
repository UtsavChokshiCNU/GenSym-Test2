// G2ItemRef.h : Declaration of the CG2ItemRef

#ifndef __G2ITEMREF_H_
#define __G2ITEMREF_H_

#include "resource.h"       // main symbols
#include "Gateway.h"

/////////////////////////////////////////////////////////////////////////////
// CG2ItemRef
class ATL_NO_VTABLE CG2ItemRef : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2ItemRef, &CLSID_G2ItemRef>,
	public ISupportErrorInfo,
	public IDispatchImpl<IG2ItemRef, &IID_IG2ItemRef, &LIBID_GensymAxl, 2, 0>
{
public:
	CG2ItemRef()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_G2ITEMREF)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CG2ItemRef)
	COM_INTERFACE_ENTRY(IG2ItemRef)
	COM_INTERFACE_ENTRY(G2ComObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
	CComBSTR        m_Host;
	int             m_Port;
    long            mp_ctx ;
    unsigned short  uuid[8] ;
public:
	static HRESULT  RefCtxChk(Datum *pItems, gsi_int count, long ctx);
// IG2ItemRef
	STDMETHOD(Init)(/*[in]*/ unsigned short *pUUIDin, /*[in]*/ long pCtx) ;
	STDMETHOD(Git)(/*[out]*/ unsigned short *pUUIDout, /*[out]*/ long *pCtx) ;
	STDMETHOD(get_UUID)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UUID)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_Gateway)(/*[in]*/ IG2Gateway4 *pGateway);

// G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out,retval]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
};

#endif //__G2ITEMREF_H_
