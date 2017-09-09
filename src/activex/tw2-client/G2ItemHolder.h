// G2ItemHolder.h : Declaration of the CG2ItemHolder

#ifndef __G2ITEMHOLDER_H_
#define __G2ITEMHOLDER_H_

#include "stdafx.h"
#include "AXClient.h"
#include "resource.h"       // main symbols
#include "IdManager.h"
#include "helpers.h"

#include "GenericEventSink.h"
#include "CProxy_G2ItemEvents.h"
#include "CProxy_G2ItemEvents2.h"

/////////////////////////////////////////////////////////////////////////////
// CG2ItemHolder
class ATL_NO_VTABLE CG2ItemHolder : 
    public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2ItemHolder, &CLSID_G2ItemHolder>,
	public CComControl<CG2ItemHolder>,
	public IDispatchImpl<IG2ItemHolder2, &IID_IG2ItemHolder2, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>,
	public IProvideClassInfo2Impl<&CLSID_G2ItemHolder, &DIID__G2ItemEvents, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>,
	public IPersistStreamInitImpl<CG2ItemHolder>,
	public IPersistStorageImpl<CG2ItemHolder>,
	public IOleControlImpl<CG2ItemHolder>,
	public IOleObjectImpl<CG2ItemHolder>,
	public IOleInPlaceActiveObjectImpl<CG2ItemHolder>,
	public IViewObjectExImpl<CG2ItemHolder>,
	public IOleInPlaceObjectWindowlessImpl<CG2ItemHolder>,
	public IDataObjectImpl<CG2ItemHolder>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CG2ItemHolder>,
	public CProxy_G2ItemEvents<CG2ItemHolder>,
	public CProxy_G2ItemEvents2<CG2ItemHolder>,
	public IPropertyNotifySinkCP<CG2ItemHolder>,
//    public IObjectSafetyImpl<CG2ItemHolder,
  //      INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IdUpdateCallback,
    public CGenericSinkParent
{
public:
	CG2ItemHolder();
	~CG2ItemHolder();
    HRESULT FinalConstruct();
	virtual void update_status(bool status);
    HRESULT SinkInvoke(DISPID dispIdMember, REFIID riid, LCID lcid,
        WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult,
        EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr);
    virtual HRESULT AdviseCalled();

private:
	HRESULT OnDraw(ATL_DRAWINFO& di);
	void loadItemAddress(void);
    BSTR CG2ItemHolder::setAutoDownload(VARIANT_BOOL newVal);
    BSTR setItemInProxy();
    void PropertyChanged(DISPID dispid);

    SmartComPtr<IDispatch> subItemProxyBeanIDispatch;
	SmartComPtr<IViewObject2> subIViewObject2;
	SmartComPtr<IOleInPlaceObject> subIOleInPlaceObject;
	SmartComPtr<IOleInPlaceActiveObject> subIOleInPlaceActiveObject;
	SmartComPtr<IOleControl> subIOleControl;
	SmartComPtr<IOleObject> subIOleObject;
	SmartComPtr<IPersistStreamInit> subIPersistStreamInit;
    SmartComPtr<IDispatch> subItemProxyObjectIDispatch;
	SmartComPtr<IConnectionPoint> subIConnectionPoint;
	SmartComPtr<ITypeInfo> eventInfo;
	SmartComPtr<IDispatch> sinkObject;
	DWORD dwCookie;  // Subscription cookie

    SmartComPtr<IG2Item> subItem; // Java Item
	SmartComPtr<IDispatch> m_scriptUtilities;

    long m_call_timeout;
	CComBSTR mItemName;
	CComBSTR mItemGateway;
	CComBSTR mItemAddress;
	CComBSTR mItemClass;
    bool m_Loading;
    bool m_item_deleted;
    IID m_ItemProxyEventsIID;

public:
    DECLARE_REGISTRY_RESOURCEID(IDR_G2ITEMHOLDER)

    BEGIN_COM_MAP(CG2ItemHolder)
        COM_INTERFACE_ENTRY(IG2ItemHolder2)
        COM_INTERFACE_ENTRY(IG2ItemHolder)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
        COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
        COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
        COM_INTERFACE_ENTRY_IMPL(IOleControl)
        COM_INTERFACE_ENTRY_IMPL(IOleObject)
        COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
        COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
        COM_INTERFACE_ENTRY_IMPL(IDataObject)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
        COM_INTERFACE_ENTRY(IProvideClassInfo2)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
        COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
    //    COM_INTERFACE_ENTRY(IObjectSafety)
    END_COM_MAP()
        
    BEGIN_PROPERTY_MAP(CG2ItemHolder)
        PROP_ENTRY("AutoUpload", 25, IID_NULL)
        PROP_ENTRY("AutoDownload", 24, IID_NULL)
        PROP_ENTRY("CallTimeout", 22, IID_NULL)
        PROP_ENTRY("ObjectClass", 6, IID_NULL)
        PROP_ENTRY("ObjectAddress", 1, IID_NULL)
        PROP_ENTRY("SubscribedAttributes", 27, IID_NULL)
    END_PROPERTY_MAP()
        
        
    BEGIN_CONNECTION_POINT_MAP(CG2ItemHolder)
        CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
        CONNECTION_POINT_ENTRY(DIID__G2ItemEvents)
        CONNECTION_POINT_ENTRY(DIID__G2ItemEvents2)
    END_CONNECTION_POINT_MAP()
        
        
    BEGIN_MSG_MAP(CG2ItemHolder)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
	    MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	    MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
    END_MSG_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus);

// IOleControl
	STDMETHOD(FreezeEvents)(BOOL bFreeze);

// IPersistStreamInit
	STDMETHOD(InitNew)(void);
	STDMETHOD(Load)(LPSTREAM pStm);

// IOleObject
	STDMETHOD(SetExtent)(DWORD aspect, SIZEL *sizel);
	STDMETHOD(DoVerb)(LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite,
		LONG lindex, HWND hwndParent, LPCRECT lprcPosRect);
	STDMETHOD(SetClientSite)(IOleClientSite *pClientSite);
	STDMETHOD(Close)(DWORD dwSaveOption);

// IOleInPlaceObject
	STDMETHOD(SetObjectRects)(LPCRECT rec1, LPCRECT rec2);
	STDMETHOD(GetWindow)(HWND *phwnd);
	STDMETHOD(InPlaceDeactivate)(void);

//IViewObject
	STDMETHOD(Draw)(DWORD dwDrawAspect, LONG lindex, void *pvAspect,
					DVTARGETDEVICE *ptd, HDC hicTargetDev, HDC hdcDraw,
					LPCRECTL prcBounds, LPCRECTL prcWBounds,
					BOOL (__stdcall * pfnContinue)(DWORD dwContinue),
					DWORD dwContinue);
	STDMETHOD(SetAdvise)(DWORD dwAspect, DWORD advf, IAdviseSink *pAdvise);

// IG2ItemHolder2
public:
	STDMETHOD(_subObject)(/*[out, retval]*/ IDispatch **subObject);
    STDMETHOD(IsEmpty)(/*[out, retval]*/ VARIANT_BOOL *pVal);
    STDMETHOD(ReleaseItem)();
// IG2ItemHolder
    STDMETHOD(Upload)();
    STDMETHOD(Download)();
    STDMETHOD(IsInstanceOfClass)(/*[in]*/ BSTR ClassName, /*[out, retval]*/ VARIANT_BOOL *Result);
    STDMETHOD(get_AutoDownload)(/* [retval][out] */ VARIANT_BOOL *pVal);
    STDMETHOD(put_AutoDownload)(/* [in] */ VARIANT_BOOL newVal);
    STDMETHOD(get_AutoUpload)(/* [retval][out] */ VARIANT_BOOL *pVal);
    STDMETHOD(put_AutoUpload)(/* [in] */ VARIANT_BOOL newVal);
	STDMETHOD(get_Item)(/*[out, retval]*/ IG2Item **Item);
	STDMETHOD(put_Item)(/*[in]*/ IG2Item *Item);
	STDMETHOD(get_SubscribedAttributes)(/*[out, retval]*/ BSTR *ListOfNames);
	STDMETHOD(put_SubscribedAttributes)(/*[in]*/ BSTR ListOfNames);
	STDMETHOD(get_CallTimeout)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CallTimeout)(/*[in]*/ long newVal);
	STDMETHOD(Structure)(/*[in, optional]*/ SAFEARRAY **NameValuePairs, /*[out, retval]*/ IG2Structure **Structure);
	STDMETHOD(Symbol)(/*[in]*/ BSTR SymbolName, /*[out, retval]*/ IG2Symbol **val);
	STDMETHOD(StartMethod)(/*[in]*/ BSTR MethodName, /*[in, optional]*/ SAFEARRAY **Arguments);
	STDMETHOD(CallMethod)(/*[in]*/ BSTR MethodName, /*[in, optional]*/ SAFEARRAY **InputArguments, /*[out, retval]*/ VARIANT *ReturnArguments);
	STDMETHOD(UnsubscribeToAttribute)(/*[in, optional]*/ BSTR AttributeName);
	STDMETHOD(SubscribeToAttribute)(/*[in, optional]*/ BSTR AttributeName);
	STDMETHOD(get_Elements)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Elements)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_Element)(/*[in]*/ long Index, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Element)(/*[in]*/ long Index, /*[in]*/ VARIANT newVal);
	STDMETHOD(get_ElementType)(/*[out, retval]*/ G2ElementType *pVal);
	STDMETHOD(get_ElementCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_ObjectClass)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ObjectClass)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_AttributeNames)(/*[out, retval]*/ VARIANT *ListOfNames);
	STDMETHOD(get_Attribute)(/*[in]*/ BSTR AttributeName, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Attribute)(/*[in]*/ BSTR AttributeName, /*[in]*/ VARIANT newVal);
	STDMETHOD(get_ObjectAddress)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ObjectAddress)(/*[in]*/ BSTR newVal);
};

#endif //__G2ITEMHOLDER_H_
