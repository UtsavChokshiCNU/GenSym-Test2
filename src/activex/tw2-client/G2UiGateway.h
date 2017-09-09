// G2UiGateway.h : Declaration of the CG2UiGateway

#ifndef __G2UIGATEWAY_H_
#define __G2UIGATEWAY_H_

#include "stdafx.h"
#include "AXClient.h"
#include "resource.h"       // main symbols
#include "IdManager.h"
#include "helpers.h"

#include "GenericEventSink.h"
#include "CProxy_G2UiGatewaySource.h"
#include "CProxy_G2UiGatewaySource2.h"

/////////////////////////////////////////////////////////////////////////////
// CG2UiGateway
class ATL_NO_VTABLE CG2UiGateway : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CProxy_G2UiGatewaySource2<CG2UiGateway>,
	public CProxy_G2UiGatewaySource<CG2UiGateway>,
	public CComCoClass<CG2UiGateway, &CLSID_G2UiGateway>,
	public CComControl<CG2UiGateway>,
	public IDispatchImpl<IG2UiGateway2, &IID_IG2UiGateway2, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>,
	public IProvideClassInfo2Impl<&CLSID_G2UiGateway, &DIID__G2UiGatewaySource, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>,
	public IPersistStreamInitImpl<CG2UiGateway>,
	public IPersistStorageImpl<CG2UiGateway>,
	public IOleControlImpl<CG2UiGateway>,
	public IOleObjectImpl<CG2UiGateway>,
	public IOleInPlaceActiveObjectImpl<CG2UiGateway>,
	public IViewObjectExImpl<CG2UiGateway>,
	public IOleInPlaceObjectWindowlessImpl<CG2UiGateway>,
	public IDataObjectImpl<CG2UiGateway>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CG2UiGateway>,
	public IPropertyNotifySinkCP<CG2UiGateway>,
//    public IObjectSafetyImpl<CG2UiGateway,
//        INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IdUpdateCallback,
    public CGenericSinkParent
{
public:
	CG2UiGateway();
	~CG2UiGateway();
    HRESULT FinalConstruct();
    virtual void update_status(bool status);
    HRESULT SinkInvoke(DISPID dispIdMember, REFIID riid, LCID lcid,
        WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult,
        EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr);
    virtual HRESULT AdviseCalled();

private:
	HRESULT OnDraw(ATL_DRAWINFO& di);
    BSTR setG2InterfaceName(BSTR newVal);
    void PropertyChanged(DISPID dispid);
    HRESULT GetItemByHandle(long ItemHandle, long HandleVersion,
                            G2Item2 **ReturnItem);

    SmartComPtr<IDispatch> subBeanIDispatch;
	SmartComPtr<IViewObject2> subIViewObject2;
	SmartComPtr<IOleInPlaceObject> subIOleInPlaceObject;
	SmartComPtr<IOleInPlaceActiveObject> subIOleInPlaceActiveObject;
	SmartComPtr<IOleControl> subIOleControl;
	SmartComPtr<IOleObject> subIOleObject;
	SmartComPtr<IPersistStreamInit> subIPersistStreamInit;
	SmartComPtr<IDispatch> subObjectIDispatch;
	SmartComPtr<IConnectionPoint> subIConnectionPoint;
	SmartComPtr<ITypeInfo> eventInfo;
	SmartComPtr<IDispatch> sinkObject;
	DWORD dwCookie;  // Subscription cookie

    bool m_connect_at_start;
    long m_call_timeout;
	CComBSTR m_GatewayId;
	CComBSTR m_HostAndPort;
	CComBSTR m_UserMode;
    bool m_connected;
    bool m_Loading;
    IID m_TwConnectorEventsIID;

public:
    DECLARE_REGISTRY_RESOURCEID(IDR_G2UIGATEWAY)
        
    BEGIN_COM_MAP(CG2UiGateway)
        COM_INTERFACE_ENTRY(IG2UiGateway2)
        COM_INTERFACE_ENTRY(IG2UiGateway)
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
  //      COM_INTERFACE_ENTRY(IObjectSafety)
    END_COM_MAP()

    BEGIN_PROPERTY_MAP(CG2UiGateway)
        PROP_ENTRY("ConnectAtStart", 13, IID_NULL)
        PROP_ENTRY("CallTimeout", 24, IID_NULL)
        PROP_ENTRY("G2InterfaceClassName", 17, IID_NULL)
        PROP_ENTRY("GatewayId", 27, IID_NULL)
        PROP_ENTRY("RemoteInitializationString", 18, IID_NULL)
        PROP_ENTRY("G2Location", 19, IID_NULL)
        PROP_ENTRY("UserName", 28, IID_NULL)
        PROP_ENTRY("UserMode", 20, IID_NULL)
        PROP_ENTRY("G2InterfaceName", 30, IID_NULL)
    END_PROPERTY_MAP()

    BEGIN_CONNECTION_POINT_MAP(CG2UiGateway)
	    CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	    CONNECTION_POINT_ENTRY(DIID__G2UiGatewaySource2)
	    CONNECTION_POINT_ENTRY(DIID__G2UiGatewaySource)
    END_CONNECTION_POINT_MAP()

    BEGIN_MSG_MAP(CG2UiGateway)
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

// IG2UiGateway2
public:
	STDMETHOD(IsConnected)(/*[out, retval]*/ VARIANT_BOOL * pConnected);
	STDMETHOD(_subObject)(/*[out, retval]*/ IDispatch **subObject);
	STDMETHOD(RemoveWorkspaceShowingListener)(/*[in]*/ IG2WorkspacePanel2 * WorkspacePanel);
	STDMETHOD(AddWorkspaceShowingListener)(/*[in]*/ IG2WorkspacePanel2 * WorkspacePanel);
// IG2UiGateway
	STDMETHOD(get_G2InterfaceName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_G2InterfaceName)(/*[in]*/ BSTR newVal);
	STDMETHOD(SetUserPassword)(/*[in]*/ BSTR Password);
	STDMETHOD(get_UserName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserName)(/*[in]*/ BSTR newVal);
    STDMETHOD(get_GatewayId)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_GatewayId)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_CallTimeout)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CallTimeout)(/*[in]*/ long newVal);
	STDMETHOD(get_G2SoftwareVersion)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(GetNamedWorkspaces)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_UserMode)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserMode)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_G2Location)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_G2Location)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_RemoteInitializationString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_RemoteInitializationString)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_G2InterfaceClassName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_G2InterfaceClassName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_G2State)(/*[out, retval]*/ G2States *pVal);
	STDMETHOD(put_G2State)(/*[in]*/ G2States newVal);
	STDMETHOD(get_ConnectAtStart)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_ConnectAtStart)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(Structure)(/*[in, optional]*/ SAFEARRAY **NameValuePairs, /*[out, retval]*/ IG2Structure **ReturnStructure);
	STDMETHOD(Symbol)(/*[in]*/ BSTR SymbolName, /*[out, retval]*/ IG2Symbol **ReturnSymbol);
	STDMETHOD(DirectSubclasses)(/*[in]*/ BSTR ClassName, /*[out, retval]*/ VARIANT *RetArray);
	STDMETHOD(ClassInstances)(/*[in]*/ BSTR ClassName, /*[in, optional]*/ VARIANT_BOOL StrictClassOnly, /*[out, retval]*/ VARIANT *ReturnInstances);
	STDMETHOD(PostMessage)(/*[in]*/ BSTR Message);
	STDMETHOD(CreateItem)(/*[in]*/ BSTR ItemClass, /*[out, retval]*/ IG2Item **ReturnItem);
	STDMETHOD(Connect)();
	STDMETHOD(CallG2Procedure)(/*[in]*/ BSTR ProcedureName, /*[in, optional]*/ SAFEARRAY **Arguments, /*[out]*/ VARIANT *ReturnValues);
	STDMETHOD(StartG2Procedure)(/*[in]*/ BSTR ProcedureName, /*[in, optional]*/ SAFEARRAY **Arguments);
	STDMETHOD(GetNamedItem)(/*[in]*/ BSTR ItemName, /*[in, optional]*/ BSTR ItemClass, /*[out, retval]*/ IG2Item **ReturnItem);
	STDMETHOD(Disconnect)();
};

#endif //__G2UIGATEWAY_H_
