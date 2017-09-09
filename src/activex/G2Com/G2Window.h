// G2Window.h : Declaration of the CG2Window

#ifndef __G2WINDOW_H_
#define __G2WINDOW_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CG2Window
class ATL_NO_VTABLE CG2Window : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2Window, &CLSID_G2Window>,
	public ISupportErrorInfo,
	public IDispatchImpl<IG2Window, &IID_IG2Window, &LIBID_GensymAxl, 2, 0>
{
public:
	STDMETHOD(get_g2UserMode)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_g2UserMode)(/*[in]*/ BSTR newVal);
    CG2Window() : m_userMode("")
	{
	}

    HRESULT FinalConstruct()
    {
        HRESULT hr = ::CoCreateInstance(CLSID_G2Item, GetControllingUnknown(), 
            CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&m_pG2Item) ;
        if (SUCCEEDED(hr))
        {
            IG2Item *pIt ;
            hr = m_pG2Item->QueryInterface(IID_IG2Item, (void**)&pIt) ;
            if (SUCCEEDED(hr))
            {
                CComBSTR    bws = "G2-WINDOW";
                hr = pIt->put_ClassName(bws.m_str) ;
            }
        }
        return hr ;
    }

    void FinalRelease()
    {
        m_pG2Item->Release() ;
    }


DECLARE_REGISTRY_RESOURCEID(IDR_G2WINDOW)
DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CG2Window)
	COM_INTERFACE_ENTRY(IG2Window)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(G2ComObject)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IG2Item4, m_pG2Item)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IG2Item3, m_pG2Item)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IG2Item2, m_pG2Item)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IG2Item,  m_pG2Item)   
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IG2Window
	STDMETHOD(SubscribeToSelection)(/*[in]*/ VARIANT userData, /*[out,retval]*/ VARIANT *subscriptionHandle);
	STDMETHOD(UnsubscribeFromSelection)();


// G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);

private:
    LPUNKNOWN   m_pG2Item ;
    CComBSTR    m_userMode;
};

#endif //__G2WINDOW_H_
