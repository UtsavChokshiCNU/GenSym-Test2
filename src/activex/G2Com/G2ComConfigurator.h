// G2ComConfigurator.h : Declaration of the CG2ComConfigurator

#ifndef __G2ComConfigurator_H_
#define __G2ComConfigurator_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CG2ComConfigurator
class ATL_NO_VTABLE CG2ComConfigurator : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2ComConfigurator, &CLSID_G2ComConfigurator>,
	public IDispatchImpl<IG2ComConfigurator, &IID_IG2ComConfigurator, &LIBID_GensymAxl>
{
public:
	CG2ComConfigurator()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_G2COMCONFIGURATOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CG2ComConfigurator)
	COM_INTERFACE_ENTRY(IG2ComConfigurator)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IG2ComConfigurator
public:
	STDMETHOD(get_HighThroughput)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_HighThroughput)(/*[in]*/ VARIANT_BOOL newVal);
};

#endif //__G2ComConfigurator_H_
