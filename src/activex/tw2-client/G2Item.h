// G2Item.h : Declaration of the CG2Item

#ifndef __G2ITEM_H_
#define __G2ITEM_H_

#include "stdafx.h"
#include "AXClient.h"
#include "resource.h"       // main symbols
#include "helpers.h"

/////////////////////////////////////////////////////////////////////////////
// CG2Item
class ATL_NO_VTABLE CG2Item : 
	public IDispatchImpl<G2Item2, &IID_G2Item2, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CG2Item, &CLSID_G2Item>
{
public:
	CG2Item();
	~CG2Item();
    HRESULT FinalConstruct();
    HRESULT subConstruct();

    SmartComPtr<IDispatch> subIDispatch; // Java Item

private:
    void init();
    void subDestruct();

    long m_call_timeout;

public:
    // This is a class can't be created by COCreateInstance()
    // so don't register the class
    BEGIN_COM_MAP(CG2Item)
    	COM_INTERFACE_ENTRY(G2Item2)
    	COM_INTERFACE_ENTRY(IG2Item)
	    COM_INTERFACE_ENTRY(IDispatch)
	    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// G2Item2
public:
	STDMETHOD(Equals)(/*[in]*/ IG2Item * Item, /*[out, retval]*/ VARIANT_BOOL * pVal);
// IG2Item
	STDMETHOD(get_Transient)(/*[out, retval]*/ VARIANT_BOOL * pVal);
	STDMETHOD(get_ManuallyDisabled)(/*[out, retval]*/ VARIANT_BOOL * pVal);
	STDMETHOD(RestoreNormalSize)();
	STDMETHOD(TransferToWorkspace)(/*[in]*/ IG2Item * Workspace, /*[in]*/ long X, /*[in]*/ long Y, /*[out, retval]*/ VARIANT_BOOL * Successful);
	STDMETHOD(TransferToItem)(/*[in]*/ IG2Item * Item, /*[in]*/ BSTR AttributeName, /*[in, optional]*/ BSTR ClassQualifier, /*[out, retval]*/ VARIANT_BOOL * Successful);
	STDMETHOD(TransferOff)(/*[out, retval]*/ VARIANT_BOOL * Successful);
	STDMETHOD(SetBounds)(/*[in]*/ long Left, /*[in]*/ long Top, /*[in]*/ long Right, /*[in]*/ long Bottom);
	STDMETHOD(Move)(/*[in]*/ long X, /*[in]*/ long Y, /*[in]*/ VARIANT_BOOL EnlargeWorkspaceIfNecessary, /*[out, retval]*/ VARIANT_BOOL * Successful);
	STDMETHOD(MoveBy)(/*[in]*/ long XDelta, /*[in]*/ long YDelta, /*[in]*/ VARIANT_BOOL EnlargeWorkspaceIfNecessary, /*[out, retval]*/ VARIANT_BOOL * Successful);
	STDMETHOD(MakePermanent)();
	STDMETHOD(MakeTransient)();
	STDMETHOD(G2Clone)(/*[out, retval]*/ IG2Item ** ReturnedItem);
	STDMETHOD(LiftToTop)();
	STDMETHOD(DropToBottom)();
	STDMETHOD(Enable)();
	STDMETHOD(Disable)();
	STDMETHOD(Delete)(/*[in]*/ VARIANT_BOOL WithPermanencyChecksDisabled, /*[in]*/ VARIANT_BOOL WithoutLeavingStubs);
	STDMETHOD(String)(/*[out, retval]*/ BSTR *StringValue);
	STDMETHOD(IsInstanceOfClass)(/*[in]*/ BSTR ClassName, /*[out, retval]*/ VARIANT_BOOL *Result);
	STDMETHOD(get_Self)(/*[out, retval]*/ IG2Item **pVal);
	STDMETHOD(_subObject)(/*[out, retval]*/ IDispatch **subObject);
	STDMETHOD(get_CallTimeout)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CallTimeout)(/*[in]*/ long newVal);
	STDMETHOD(Structure)(/*[in, optional]*/ SAFEARRAY **NameValuePairs, /*[out, retval]*/ IG2Structure **Structure);
	STDMETHOD(Symbol)(/*[in]*/ BSTR SymbolName, /*[out, retval]*/ IG2Symbol **val);
	STDMETHOD(StartMethod)(/*[in]*/ BSTR MethodName, /*[in, optional]*/ SAFEARRAY **Arguments);
	STDMETHOD(CallMethod)(/*[in]*/ BSTR MethodName, /*[in, optional]*/ SAFEARRAY **InputArguments, /*[out, retval]*/ VARIANT *ReturnArguments);
	STDMETHOD(get_Elements)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Elements)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_Element)(/*[in]*/ long Index, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Element)(/*[in]*/ long Index, /*[in]*/ VARIANT newVal);
	STDMETHOD(get_ElementType)(/*[out, retval]*/ G2ElementType *pVal);
	STDMETHOD(get_ElementCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_AttributeNames)(/*[out, retval]*/ VARIANT *ListOfNames);
	STDMETHOD(get_Attribute)(/*[in]*/ BSTR AttributeName, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Attribute)(/*[in]*/ BSTR AttributeName, /*[in]*/ VARIANT newVal);
};

// this class is used when converting an existing item bean to our item
//    before this class is useable, subIDispatch must be set and
//    subConstruct() must be called.
class _CG2Item: public CG2Item
{
public:
    HRESULT FinalConstruct()
    {
        return S_OK;
    }
};

#endif //__G2ITEM_H_
