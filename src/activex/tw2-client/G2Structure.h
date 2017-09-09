// G2Structure.h: Definition of the G2Structure class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G2STRUCTURE_H__2B010C08_09E5_11D2_869E_00008618F471__INCLUDED_)
#define AFX_G2STRUCTURE_H__2B010C08_09E5_11D2_869E_00008618F471__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "stdafx.h"
#include "AXClient.h"
#include "resource.h"       // main symbols
#include "helpers.h"

#define JAVA_STRUCTURE_CLASS L"com.gensym.util.Structure"

/////////////////////////////////////////////////////////////////////////////
// G2Structure

class G2Structure : 
	public IDispatchImpl<IG2Structure, &IID_IG2Structure, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<G2Structure, &CLSID_G2Structure>
{
public:	
	G2Structure();
	~G2Structure();
    HRESULT FinalConstruct();
    HRESULT subConstruct();

	SmartComPtr<IDispatch> subIDispatch;

private:
    void subDestruct();

public:
    DECLARE_REGISTRY_RESOURCEID(IDR_G2Structure)

    BEGIN_COM_MAP(G2Structure)
	    COM_INTERFACE_ENTRY(IDispatch)
    	COM_INTERFACE_ENTRY(IG2Structure)
	    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IG2Structure
public:
	STDMETHOD(String)(/*[out, retval]*/ BSTR *StringValue);
	STDMETHOD(get_Self)(/*[out, retval]*/ IG2Structure **pVal);
	STDMETHOD(_subObject)(/*[out, retval]*/ IDispatch **subObject);
	STDMETHOD(ClearMember)(/*[in, optional]*/ BSTR MemberName);
	STDMETHOD(get_Member)(/*[in]*/ BSTR MemberName, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Member)(/*[in]*/ BSTR MemberName, /*[in]*/ VARIANT newVal);
	STDMETHOD(get_MemberNames)(/*[out, retval]*/ VARIANT *ListOfNames);
};

// this class is used when converting an existing java object to our object
//    before this class is useable, subIDispatch must be set and
//    subConstruct() must be called.
class _G2Structure: public G2Structure
{
public:
    HRESULT FinalConstruct()
    {
        return S_OK;
    }
};

#endif // !defined(AFX_G2STRUCTURE_H__2B010C08_09E5_11D2_869E_00008618F471__INCLUDED_)
