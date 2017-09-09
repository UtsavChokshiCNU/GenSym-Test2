// G2WorkspacePanel.h : Declaration of the CG2WorkspacePanel

#ifndef __G2WORKSPACEPANEL_H_
#define __G2WORKSPACEPANEL_H_

#include "stdafx.h"
#include "AXClient.h"
#include "resource.h"       // main symbols
#include "IdManager.h"
#include "helpers.h"

#include "GenericEventSink.h"
#include "CProxy_G2WorkspacePanelSource.h"

/////////////////////////////////////////////////////////////////////////////
// CG2WorkspacePanel
class ATL_NO_VTABLE CG2WorkspacePanel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CG2WorkspacePanel, &CLSID_G2WorkspacePanel>,
	public CComControl<CG2WorkspacePanel>,
	public IDispatchImpl<IG2WorkspacePanel2, &IID_IG2WorkspacePanel2, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>,
	public IProvideClassInfo2Impl<&CLSID_G2WorkspacePanel, &DIID__G2WorkspacePanelSource, &LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2, LIB_MINOR_VERSION_GensymTw2>,
	public IPersistStreamInitImpl<CG2WorkspacePanel>,
	public IPersistStorageImpl<CG2WorkspacePanel>,
	public IOleControlImpl<CG2WorkspacePanel>,
	public IOleObjectImpl<CG2WorkspacePanel>,
	public IOleInPlaceActiveObjectImpl<CG2WorkspacePanel>,
	public IViewObjectExImpl<CG2WorkspacePanel>,
	public IOleInPlaceObjectWindowlessImpl<CG2WorkspacePanel>,
	public IDataObjectImpl<CG2WorkspacePanel>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CG2WorkspacePanel>,
	public CProxy_G2WorkspacePanelSource<CG2WorkspacePanel>,
	public IPropertyNotifySinkCP<CG2WorkspacePanel>,
//    public IObjectSafetyImpl<CG2WorkspacePanel,
  //      INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IdUpdateCallback,
    public CGenericSinkParent
{
public:
	CG2WorkspacePanel();
	~CG2WorkspacePanel();
    HRESULT FinalConstruct();
	virtual void update_status(bool status);
    HRESULT SinkInvoke(DISPID dispIdMember, REFIID riid, LCID lcid,
        WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult,
        EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr);
    virtual HRESULT AdviseCalled();

private:
	HRESULT OnDraw(ATL_DRAWINFO& di);
	void loadWorkspaceAddress(void);
    void PropertyChanged(DISPID dispid);

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

	CComBSTR mWorkspaceName;
	CComBSTR mWorkspaceGateway;
	CComBSTR mWorkspaceAddress;
    bool m_Loading;
    SmartComPtr<IG2UiGateway2> mpConnector;
    IID m_MultipleWorkspacePanelEventsIID;

public:
    DECLARE_REGISTRY_RESOURCEID(IDR_G2WORKSPACEPANEL)

    BEGIN_COM_MAP(CG2WorkspacePanel)
	    COM_INTERFACE_ENTRY(IG2WorkspacePanel2)
	    COM_INTERFACE_ENTRY(IG2WorkspacePanel)
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

    BEGIN_PROPERTY_MAP(CG2WorkspacePanel)
	    PROP_ENTRY("UpdateWhileHidden", 6, IID_NULL)
	    PROP_ENTRY("ShowNewWorkspaces", 7, IID_NULL)
	    PROP_ENTRY("WorkspaceAddress", 21, IID_NULL)
    END_PROPERTY_MAP()


    BEGIN_CONNECTION_POINT_MAP(CG2WorkspacePanel)
	    CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	    CONNECTION_POINT_ENTRY(DIID__G2WorkspacePanelSource)
    END_CONNECTION_POINT_MAP()


    BEGIN_MSG_MAP(CG2WorkspacePanel)
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
	STDMETHOD(SetColorScheme)(LOGPALETTE *pLogpal);

// IOleInPlaceObject
	STDMETHOD(SetObjectRects)(LPCRECT rec1, LPCRECT rec2);
	STDMETHOD(GetWindow)(HWND *phwnd);
	STDMETHOD(InPlaceDeactivate)(void);

//IViewObject
    // Since the control has its own window, this is never called!
	STDMETHOD(Draw)(DWORD dwDrawAspect, LONG lindex, void *pvAspect,
					DVTARGETDEVICE *ptd, HDC hicTargetDev, HDC hdcDraw,
					LPCRECTL prcBounds, LPCRECTL prcWBounds,
					BOOL (__stdcall * pfnContinue)(DWORD dwContinue),
					DWORD dwContinue);
	STDMETHOD(SetAdvise)(DWORD dwAspect, DWORD advf, IAdviseSink *pAdvise);

// IG2WorkspacePanel2
public:
	STDMETHOD(RemoveAllWorkspaces)();
	STDMETHOD(GetWorkspaces)(/*[out, retval]*/ VARIANT * ArrayOfG2Items);
	STDMETHOD(_subObject)(/*[out, retval]*/ IDispatch **subObject);
	STDMETHOD(ProcessHideWorkspaceEvent)(/*[in]*/ IDispatch* WorkspaceShowingEvent);
	STDMETHOD(ProcessShowWorkspaceEvent)(/*[in]*/ IDispatch* WorkspaceShowingEvent);
	STDMETHOD(ScrollToLocation)(/*[in]*/ long X, /*[in]*/ long Y);
// IG2WorkspacePanel
	STDMETHOD(RemoveElementFromSelection)(/*[in]*/ IG2Item * Item);
	STDMETHOD(AddElementToSelection)(/*[in]*/ IG2Item* Item);
	STDMETHOD(get_WorkspaceAddress)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_WorkspaceAddress)(/*[in]*/ BSTR newVal);
	STDMETHOD(ShowWorkspace)(/*[in]*/ IG2Item *Workspace);
	STDMETHOD(SelectAll)();
	STDMETHOD(RemoveWorkspace)(/*[in]*/ IG2Item *Workspace);
	STDMETHOD(PreviousWorkspace)();
	STDMETHOD(NextWorkspace)();
	STDMETHOD(MoveSelection)(/*[in]*/ long DeltaX, /*[in]*/ long DeltaY, /*[in]*/ VARIANT_BOOL EnlargeWorkspaceIfNecessary);
	STDMETHOD(GetSelection)(/*[out, retval]*/ VARIANT *pSelectedItems);
	STDMETHOD(DeleteSelection)();
	STDMETHOD(ClearSelection)();
	STDMETHOD(AddWorkspace)(/*[in]*/ IG2Item *Workspace, /*[in, optional]*/ VARIANT_BOOL UpdateWhileHidden);
	STDMETHOD(get_ShowNewWorkspaces)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_ShowNewWorkspaces)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_UpdateWhileHidden)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_UpdateWhileHidden)(/*[in]*/ VARIANT_BOOL newVal);
};

#endif //__G2WORKSPACEPANEL_H_
