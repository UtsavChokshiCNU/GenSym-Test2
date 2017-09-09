// Gateway.h : Declaration of the CG2Gateway

#ifndef __GATEWAY_H_
#define __GATEWAY_H_

#include "resource.h"       // main symbols
#include "CPG2Com.h"        // proxy class for events
#include "GatewayProp.h"    // property page
#include "GsiThread.h"
#include "GsiContext.h"
#include <asptlb.h>
#include "NBRPCReq.h"

#define EXEC(cmd,ec) if (FAILED(hr = cmd)) return ec
#define ERGO(cmd,el) if (FAILED(hr = cmd)) goto el

void axl_notification_callback(procedure_user_data_type procedure_user_data, 
                               gsi_item *pItemsIn, gsi_int count, 
                               call_identifier_type call_index) ;

/////////////////////////////////////////////////////////////////////////////
// CG2Gateway
class ATL_NO_VTABLE CG2Gateway :
            public CComObjectRootEx<CComSingleThreadModel>,
            public CComCoClass<CG2Gateway, &CLSID_G2Gateway>,
            public CComControl<CG2Gateway>,
            public IDispatchImpl<IG2Gateway4, &IID_IG2Gateway4, &LIBID_GensymAxl,2,0>,
            public IProvideClassInfo2Impl<&CLSID_G2Gateway, &DIID__G2Events, &LIBID_GensymAxl,2,0>,
            public IPersistStreamInitImpl<CG2Gateway>,
            public IPersistStorageImpl<CG2Gateway>,
            //public IPersistPropertyBagImpl<CG2Gateway>,  use stream storage rather than property bag
            public IQuickActivateImpl<CG2Gateway>,
            public IOleControlImpl<CG2Gateway>,
            public IOleObjectImpl<CG2Gateway>,
            public IOleInPlaceActiveObjectImpl<CG2Gateway>,
            public IViewObjectExImpl<CG2Gateway>,
            public IOleInPlaceObjectWindowlessImpl<CG2Gateway>,
            public IDataObjectImpl<CG2Gateway>,
            public ISupportErrorInfoImpl<&IID_IG2Gateway4>,
            public CProxy_G2Events<CG2Gateway>,
            public IConnectionPointContainerImpl<CG2Gateway>,
            public ISpecifyPropertyPagesImpl<CG2Gateway>,
            public IPerPropertyBrowsingImpl<CG2Gateway>,
            public IObjectSafetyImpl<CG2Gateway, INTERFACESAFE_FOR_UNTRUSTED_CALLER |
            INTERFACESAFE_FOR_UNTRUSTED_DATA>,
            public IPropertyNotifySinkCP<CG2Gateway>
{
public:
    GsiContext * mpContext; // pointer to context object
    CG2Gateway();
    ~CG2Gateway();
    STDMETHOD(SetClientSite)(IOleClientSite *pClientSite) ;
    

    DECLARE_REGISTRY_RESOURCEID(IDR_G2GATEWAY)

    BEGIN_COM_MAP(CG2Gateway)
    COM_INTERFACE_ENTRY(IG2Gateway)
    COM_INTERFACE_ENTRY(IG2Gateway4)
    COM_INTERFACE_ENTRY(IG2Gateway3)
    COM_INTERFACE_ENTRY(IG2Gateway2)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
    COM_INTERFACE_ENTRY_IMPL(IOleControl)
    COM_INTERFACE_ENTRY_IMPL(IOleObject)
    COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
    //    COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
    COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
    COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
    COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
    COM_INTERFACE_ENTRY_IMPL(IDataObject)
    COM_INTERFACE_ENTRY(IProvideClassInfo)
    COM_INTERFACE_ENTRY(IProvideClassInfo2)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
    COM_INTERFACE_ENTRY_IMPL(IPerPropertyBrowsing)
    COM_INTERFACE_ENTRY(IObjectSafety)
    END_COM_MAP()

    BEGIN_PROPERTY_MAP(CG2Gateway)

    //    PROP_ENTRY("IsG2Connected", 8, CLSID_GatewayProp)
    //    PROP_ENTRY("IsG2Running", 9, CLSID_GatewayProp)
    PROP_ENTRY("HostAndPort", 10, CLSID_GatewayProp)
    PROP_ENTRY("InterfaceClass", 11, CLSID_GatewayProp)
    PROP_ENTRY("InitializationString", 12, CLSID_GatewayProp)
    PROP_ENTRY("CallTimeout", 13, CLSID_GatewayProp)
    PROP_ENTRY("G2Symbols", 24, CLSID_GatewayProp)
    PROP_ENTRY("DisconnectOnReset", 25, CLSID_GatewayProp)

    PROP_PAGE(CLSID_GatewayProp)
    //    PROP_PAGE(CLSID_StockColorPage)
    END_PROPERTY_MAP()


    BEGIN_CONNECTION_POINT_MAP(CG2Gateway)
    CONNECTION_POINT_ENTRY(DIID__G2Events)
    CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
    END_CONNECTION_POINT_MAP()


    BEGIN_MSG_MAP(CG2Gateway)
    MESSAGE_HANDLER(WM_PAINT, OnPaint)
    MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
    MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
    END_MSG_MAP()


    // ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

    // IViewObjectEx
    STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
    {
        ATLTRACE2(atrAxlMethodCalls,3,_T("IViewObjectExImpl::GetViewStatus\n"));
        *pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
        return S_OK;
    }

    // Hack so that Delphi will work.
    STDMETHOD(GetClientSite)(IOleClientSite **ppClientSite)
    {
        ATLTRACE2(atrAxlMethodCalls,3,"Overloaded GetClientSite");
        if (!m_spClientSite)
        {
            *ppClientSite = NULL;
            return S_OK;
        }
        return IOleObjectImpl<CG2Gateway>::GetClientSite(ppClientSite);
    }



    // IG2Gateway
public:
    STDMETHOD(PostMessage)(VARIANT *Message);
    STDMETHOD(_FireEvents)();
    STDMETHOD(get_CallTimeout)(/*[out, retval]*/ long *pVal);
    STDMETHOD(put_CallTimeout)(/*[in]*/ long newVal);
    STDMETHOD(get_RemoteInitializationString)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_RemoteInitializationString)(/*[in]*/ BSTR newVal);
    STDMETHOD(get_InterfaceClass)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_InterfaceClass)(/*[in]*/ BSTR newVal);
    STDMETHOD(get_G2Location)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(put_G2Location)(/*[in]*/ BSTR newVal);
    STDMETHOD(get_IsG2Running)(/*[out, retval]*/ VARIANT_BOOL *pVal);
    STDMETHOD(get_IsG2Connected)(/*[out, retval]*/ VARIANT_BOOL *pVal);
    STDMETHOD(CreateObjectInstance)(/*[in]*/ BSTR sClassName, /*[out, retval]*/ LPDISPATCH *pObj);
    STDMETHOD(GetNamedObject)(/*[in]*/ BSTR sObjName, /*[in,optional]*/ BSTR sObjClass, /*[out, retval]*/ LPDISPATCH *pObj);
    STDMETHOD(Start)(/*[in]*/ BSTR sRPCName, /*[in]*/ SAFEARRAY **pArgs);
    STDMETHOD(CallDeferred)(/*[in]*/ BSTR sRPCName, /*[In]*/ VARIANT *DeferredCallIdentifier, /*[in, optional]*/ SAFEARRAY **pInArgs);
    STDMETHOD(Call)(/*[in]*/ BSTR RPCName, /*[in, optional]*/ SAFEARRAY **InArgs, /*[out, retval]*/ VARIANT *OutArgs);
    STDMETHOD(Disconnect)();
    STDMETHOD(Connect)(VARIANT_BOOL bWaitflag);
    HRESULT OnDraw(ATL_DRAWINFO& di);
    STDMETHOD(Close( DWORD dwSaveOption));

    //  IG2Gateway2
    //  ----------
    STDMETHOD(OnStartPage)(/*[in]*/ IUnknown* piUnk);
    STDMETHOD(OnEndPage)();

    //  IG2Gateway3
    //  -----------
    STDMETHOD(MakeG2ComVariable)(/*[in]*/ G2Type G2ComType, /*[in, optional]*/ SAFEARRAY **InArgs, /*[out, retval]*/ VARIANT *OutArg);
    STDMETHOD(DbgMsg)(/*[in]*/ BSTR msg);
    STDMETHOD(get_G2RunState)(/*[out,retval]*/G2RunStateType *pG2rs);

    // IG2Gateway4
    // -----------
	STDMETHOD(get_TWHandle)(/*[out, retval]*/ long *plHWnd);
	STDMETHOD(put_TWHandle)(/*[in]*/ long TWHWnd);
    STDMETHOD(ObtainTWLockIfUnused)(/*[out, retval]*/ VARIANT_BOOL *pResult) ;
    STDMETHOD(ClearTWLock)() ;
	STDMETHOD(get_G2Symbols)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_G2Symbols)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DisconnectOnReset)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DisconnectOnReset)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(SetContextLimit)(long limit);

    // Other method calls
    // ------------------
    STDMETHOD(GetDisplayString)(DISPID dispid, BSTR *pBstr) ;
private:
    int AutoConnect();

    CComPtr<IRequest> m_piRequest;                  //Request Object
    CComPtr<IResponse> m_piResponse;                //Response Object
    CComPtr<ISessionObject> m_piSession;            //Session Object
    CComPtr<IServer> m_piServer;                    //Server Object
    CComPtr<IApplicationObject> m_piApplication;    //Application Object
    BOOL m_bOnStartPageCalled;                      //OnStartPage successful?
    bool varStructNames(SAFEARRAY *psa, bool alternate);
    bool validStructName(VARIANT *pv);
    long m_TWHandle ;
    bool m_TWLockIsInUse ;
    STDMETHOD(fixUpArray)(VARIANT *varTo, VARIANT *varFrom);
public:
    unsigned m_bAutoSize:1 ;
    SIZE     m_sizeExtent ;
    SIZE     m_sizeNatural ;
};

//
// This is a global function to throw a error.
// This creates a IErrorInfo object and sets it as the current error for
// the current thread.
// The caller must return a failing HRESULT back to the caller.
// This expects a string as a input that describes the error.  These
// errors are returned to the caller as a exception.  This is not
// used for async callbacks from GSI.  There is a event that does that.
//

void SetComError(LPCOLESTR error_mesg, const IID *pin=&IID_IG2Gateway4, OLECHAR *pObjName=OLESTR("G2Gateway.G2Gateway"));

#endif //__GATEWAY_H_
