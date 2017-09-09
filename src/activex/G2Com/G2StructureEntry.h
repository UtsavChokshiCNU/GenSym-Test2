// G2StructureEntry.h : Declaration of the CG2StructureEntry

#ifndef __G2STRUCTUREENTRY_H_
#define __G2STRUCTUREENTRY_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CG2StructureEntry
class ATL_NO_VTABLE CG2StructureEntry :
            public CComObjectRootEx<CComSingleThreadModel>,
            public CComCoClass<CG2StructureEntry, &CLSID_G2StructureEntry>,
            public ISupportErrorInfo,
            public IDispatchImpl<IG2StructureEntry, &IID_IG2StructureEntry, &LIBID_GensymAxl, 2, 0>
{
public:
    CG2StructureEntry();
    CG2StructureEntry(BSTR bstName, VARIANT varX);
    CG2StructureEntry(CG2StructureEntry& g2seFrom);
    void CG2StructureEntry::FinalRelease();

    DECLARE_REGISTRY_RESOURCEID(IDR_G2STRUCTUREENTRY)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CG2StructureEntry)
    COM_INTERFACE_ENTRY(IG2StructureEntry)
    COM_INTERFACE_ENTRY(G2ComObject)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()

public:
    // ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
    // G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);
    // G2StructureEntry
    STDMETHOD(get_Value)(/*[out, retval]*/ VARIANT *pVal);
    STDMETHOD(put_Value)(/*[in]*/ VARIANT newVal);
    STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
private:
    BSTR        m_bstrName ;
    VARIANT     m_varValue ;
};

#endif //__G2STRUCTUREENTRY_H_
