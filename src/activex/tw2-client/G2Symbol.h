// G2Symbol.h: Definition of the G2Symbol class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G2SYMBOL_H__2B010C0F_09E5_11D2_869E_00008618F471__INCLUDED_)
#define AFX_G2SYMBOL_H__2B010C0F_09E5_11D2_869E_00008618F471__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "stdafx.h"
#include "AXClient.h"
#include "resource.h"       // main symbols
#include "helpers.h"

/////////////////////////////////////////////////////////////////////////////
// G2Symbol

class G2Symbol : 
    public IDispatchImpl<IG2Symbol, &IID_IG2Symbol, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<G2Symbol, &CLSID_G2Symbol>
{
public:
    G2Symbol();
    ~G2Symbol();
    HRESULT FinalConstruct();

private:
	CComBSTR mValue;
	SmartComPtr<IDispatch> javaObject;

public:
    DECLARE_REGISTRY_RESOURCEID(IDR_G2Symbol)

    BEGIN_COM_MAP(G2Symbol)
	    COM_INTERFACE_ENTRY(IDispatch)
    	COM_INTERFACE_ENTRY(IG2Symbol)
	    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IG2Symbol
public:
	STDMETHOD(String)(/*[out, retval]*/ BSTR *StringValue);
	STDMETHOD(get_Self)(/*[out, retval]*/ IG2Symbol **pVal);
	STDMETHOD(_subObject)(/*[out, retval]*/ IDispatch **subObject);
	STDMETHOD(get_Value)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Value)(/*[in]*/ BSTR newVal);
};

#endif // !defined(AFX_G2SYMBOL_H__2B010C0F_09E5_11D2_869E_00008618F471__INCLUDED_)
