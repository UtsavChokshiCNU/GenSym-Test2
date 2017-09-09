// G2Structure.h : Declaration of the CG2Structure

#ifndef __G2Structure_H_
#define __G2Structure_H_

#include <vector>
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CG2Structure
extern long nrStructs ;
extern long structID ;

class ATL_NO_VTABLE CG2Structure :
            public CComObjectRootEx<CComSingleThreadModel>,
            public CComCoClass<CG2Structure, &CLSID_G2Structure>,
            public ISupportErrorInfo,
            public IDispatchImpl<IG2Structure, &IID_IG2Structure, &LIBID_GensymAxl, 2, 0>
{
public:
    CG2Structure()
    {
        ATLTRACE2(atrG2ObjLife,3,"*** New G2Structure at %08x.\n", this);
    }
    void CG2Structure::FinalRelease();
    ~CG2Structure()
    {
        ATLTRACE2(atrAxlMethodCalls, 3, "*** CG2Structure Destructor.\n");
    }

    DECLARE_REGISTRY_RESOURCEID(IDR_G2STRUCTURE)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CG2Structure)
    COM_INTERFACE_ENTRY(IG2Structure)
    COM_INTERFACE_ENTRY(G2ComObject)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()

private:
    std::vector< IDispatch* >    m_vecG2StructureEntries ;
    STDMETHOD(getPtrWithLongIdx)(long idx, IG2StructureEntry** ppLine);
    STDMETHOD(getPtrWithStrIdx)(BSTR BSTRidx, IG2StructureEntry** ppLine);

public:
    HRESULT Confiscate(IG2StructureEntry* pIG2SE);
    // ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
    // G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);
    // G2Structure
    STDMETHOD(get_Item)(/*[in]*/ VARIANT index, /*[out, retval]*/ VARIANT* pItem);
    STDMETHOD(put_Item)(/*[in]*/ VARIANT index, /*[in]*/ VARIANT value);
    STDMETHOD(Remove)(/*[in]*/ VARIANT index);
    STDMETHOD(Add)(/*[in]*/ SAFEARRAY **pArgs);
    STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
    STDMETHOD(get__NewEnum)(/*[out, retval]*/ LPUNKNOWN *pVal);
    STDMETHOD(Names) (/*[out, retval]*/ SAFEARRAY **pNames);
    STDMETHOD(Values)(/*[out, retval]*/ SAFEARRAY **pValues);

};
#endif //__G2Structure_H_
