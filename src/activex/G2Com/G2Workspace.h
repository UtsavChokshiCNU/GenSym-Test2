// G2Workspace.h : Declaration of the CG2Workspace

#ifndef __G2WORKSPACE_H_
#define __G2WORKSPACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CG2Workspace
class ATL_NO_VTABLE CG2Workspace : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2Workspace, &CLSID_G2Workspace>,
	public ISupportErrorInfo,
	public IDispatchImpl<IG2Workspace, &IID_IG2Workspace, &LIBID_GensymAxl, 2, 0>
{
public:
    CG2Workspace() : m_pG2Item(NULL)
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
                CComBSTR    bws = "KB-WORKSPACE";
                hr = pIt->put_ClassName(bws.m_str) ;
            }
        }
        return hr ;
    }

    void FinalRelease()
    {
        m_pG2Item->Release() ;
    }

DECLARE_REGISTRY_RESOURCEID(IDR_G2WORKSPACE)
DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN()


BEGIN_COM_MAP(CG2Workspace)
	COM_INTERFACE_ENTRY(IG2Workspace)
    COM_INTERFACE_ENTRY(G2ComObject)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IG2Item4, m_pG2Item)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IG2Item3, m_pG2Item)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IG2Item2, m_pG2Item)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IG2Item,  m_pG2Item)   
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// IG2Workspace
public:
	STDMETHOD(SubscribeToItemAddition)(VARIANT userData, VARIANT *subHdl);
	STDMETHOD(SubscribeToItemRemoval)(VARIANT userData, VARIANT *subHdl);
	STDMETHOD(UnsubscribeFromItemAddition)();
	STDMETHOD(UnsubscribeFromItemRemoval)();

// G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

private:
    LPUNKNOWN   m_pG2Item ;
};

#endif //__G2WORKSPACE_H_
