// wrap.h : Declaration of the Cwrap

#ifndef __WRAP_H_
#define __WRAP_H_


typedef Font (void *);

#include "resource.h"       // main symbols
#include "CPBridgeTester.h"
#include "CPwraptest.h"
#include "Sink.h"



const CLSID CLSID_bridge = {0x3904AC20, 0x2DF5, 0x11D1, {0x89, 0x50, 0x00,0x80, 0x5F, 0x2A, 0xDE, 0x08}};
const IID IID_bridge = {0x95A884F1, 0xF4C8, 0x11D1, {0x86, 0x62, 0x00, 0x00, 0x86, 0x18, 0xF4, 0x71}};

/////////////////////////////////////////////////////////////////////////////
// Cwrap
class ATL_NO_VTABLE Cwrap : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CProxy_WrapEvents<Cwrap>, 
	public CComCoClass<Cwrap, &CLSID_wrap>,
	public CComControl<Cwrap>,
	public CStockPropImpl<Cwrap, Iwrap, &IID_Iwrap, &LIBID_WRAPTESTLib>,
	public IProvideClassInfo2Impl<&CLSID_wrap, &DIID__WrapEvents, &LIBID_WRAPTESTLib>,
	public IPersistStreamInitImpl<Cwrap>,
	public IPersistStorageImpl<Cwrap>,
//	public IQuickActivateImpl<Cwrap>,
	public IOleControlImpl<Cwrap>,
	public IOleObjectImpl<Cwrap>,
	public IOleInPlaceActiveObjectImpl<Cwrap>,
	public IViewObjectExImpl<Cwrap>,
	public IOleInPlaceObjectWindowlessImpl<Cwrap>,
	public IDataObjectImpl<Cwrap>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<Cwrap>,
	public IPropertyNotifySinkCP<Cwrap>,
	public ISpecifyPropertyPagesImpl<Cwrap>
{
	

public:
	IDispatch *subIDispatch;
	IViewObject2 *subIViewObject2;
	IOleInPlaceObject *subIOleInPlaceObject;
	IOleInPlaceActiveObject *subIOleInPlaceActiveObject;
	IOleControl *subIOleControl;
	IOleObject *subIOleObject;
	IPersistStreamInit *subIPersistStreamInit;
	IConnectionPointContainer *subIConnectionPointContainer;
	IUnknown *sinkObject;
	IConnectionPoint *subIConnectionPoint;
	DWORD dwCookie;  // Subscription cookie

	CProxyBridgeTesterDispatch subobj;
	Cwrap()
	{
		// Set up all of the defualt values
		subIDispatch = NULL;
		subIViewObject2 = NULL;
		subIOleInPlaceObject = NULL;
		subIOleInPlaceActiveObject = NULL;
		subIOleControl = NULL;
		subIOleObject = NULL;
		subIPersistStreamInit = NULL;
		subIConnectionPointContainer = NULL;
		sinkObject = NULL;
		subIConnectionPoint = NULL;
		dwCookie = 0;

		// First create the sub object
		ATLTRACE("\n\nNewControl\n");
		HRESULT hr = CoCreateInstance(CLSID_bridge, NULL, CLSCTX_INPROC_SERVER, IID_bridge, (void **) &subIDispatch);
		if (FAILED(hr)) return;
		subobj.p = subIDispatch;
		
		// Now querry each needed interface
		subIDispatch->QueryInterface(IID_IViewObject2, (void **) &subIViewObject2);
		subIDispatch->QueryInterface(IID_IOleInPlaceObject, (void **) &subIOleInPlaceObject);
		subIDispatch->QueryInterface(IID_IOleInPlaceActiveObject, (void **) &subIOleInPlaceActiveObject);
		subIDispatch->QueryInterface(IID_IOleControl, (void **) &subIOleControl);
		subIDispatch->QueryInterface(IID_IOleObject, (void **) &subIOleObject);
		subIDispatch->QueryInterface(IID_IPersistStreamInit, (void **) &subIPersistStreamInit);
		subIDispatch->QueryInterface(IID_IConnectionPointContainer, (void **) &subIConnectionPointContainer);

		// Now create the call back sink
		hr = CoCreateInstance(CLSID_Sink, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void **) &sinkObject);
		if (FAILED(hr)) return;
		ATLTRACE("Got sink object\n");
		((CSink *) sinkObject)->EventObj = this;

		// Get ConnectionPoint
		hr = subIConnectionPointContainer->FindConnectionPoint(IID_source, &subIConnectionPoint);
		if (FAILED(hr)) return;
		ATLTRACE("Got Connection Point\n");

		// Register Sink
		hr = subIConnectionPoint->Advise(sinkObject, &dwCookie);
		if (FAILED(hr)) return;
		ATLTRACE("Registered Sink\n");
	}

	~Cwrap() {
		// Clean up all of the cached pointers
		if (subIDispatch) subIDispatch->Release();
		if (subIViewObject2) subIViewObject2->Release();
		if (subIOleInPlaceObject) subIOleInPlaceObject->Release();
		if (subIOleInPlaceActiveObject) subIOleInPlaceActiveObject->Release();
		if (subIOleControl) subIOleControl->Release();
		if (subIOleObject) subIOleObject->Release();
		if (subIPersistStreamInit) subIPersistStreamInit->Release();
		if (subIConnectionPointContainer) subIConnectionPointContainer->Release();
		if (sinkObject) sinkObject->Release();

		if (dwCookie) subIConnectionPoint->Unadvise(dwCookie);
		if (subIConnectionPoint) subIConnectionPoint->Release();

		ATLTRACE("Control Destructed\n\n\n");
	}

DECLARE_REGISTRY_RESOURCEID(IDR_WRAP)

BEGIN_COM_MAP(Cwrap)
	COM_INTERFACE_ENTRY(Iwrap)
	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
//	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
//	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
//	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROPERTY_MAP(Cwrap)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()


BEGIN_CONNECTION_POINT_MAP(Cwrap)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__WrapEvents)
END_CONNECTION_POINT_MAP()


BEGIN_MSG_MAP(Cwrap)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
END_MSG_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IOleControl
	STDMETHOD(FreezeEvents)(BOOL bFreeze) {
		ATLTRACE("Forwarded FreezeEvents\n");
		return subIOleControl->FreezeEvents(bFreeze);
	}


// IPersistStreamInit
	STDMETHOD(InitNew)(void) {
		ATLTRACE("Forwarded IPersistStreamInit::InitNew\n");
		return subIPersistStreamInit->InitNew();
	}

	STDMETHOD(Load)(LPSTREAM pStm) {
		ATLTRACE("Forwarded IPersistStreamInit::Load\n");
		return subIPersistStreamInit->Load(pStm);
	}

	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty) {
		ATLTRACE("Forwarded IPersistStreamInit::Save\n");
		return subIPersistStreamInit->Save(pStm, fClearDirty);
	}

// IOleObject
	STDMETHOD(SetExtent)(DWORD aspect, SIZEL *sizel) {
		ATLTRACE("Forwarded:SetExtent\n");
		return subIOleObject->SetExtent(aspect, sizel);
	}

	STDMETHOD(DoVerb)(LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite,
		LONG lindex, HWND hwndParent, LPCRECT lprcPosRect) {
			ATLTRACE("Forwarded DoVerb\n");
			return subIOleObject->DoVerb(iVerb, lpmsg, pActiveSite, lindex, hwndParent, lprcPosRect);
	}

	STDMETHOD(SetClientSite)(IOleClientSite *pClientSite) {
		ATLTRACE("Forwarded SetClientSite\n");
		return subIOleObject->SetClientSite(pClientSite);
	}

	STDMETHOD(GetExtent)(DWORD dwDrawAspect, SIZEL *psizel) {

		ATLTRACE("Forwarded GetExtent\n");
		return subIOleObject->GetExtent(dwDrawAspect, psizel);
	}

	STDMETHOD(Close)(DWORD dwSaveOption) {
		ATLTRACE("Forwarded Close\n");
		return subIOleObject->Close(dwSaveOption);
	}

// IOleInPlaceObject
	STDMETHOD(SetObjectRects)(LPCRECT rec1, LPCRECT rec2) {
		ATLTRACE("Forwarded:SetObjectRects\n");
		return subIOleInPlaceObject->SetObjectRects(rec1, rec2);
	}

	STDMETHOD(GetWindow)(HWND *phwnd) {
		ATLTRACE("Forwarded: GetWindow()\n");
		return subIOleInPlaceObject->GetWindow(phwnd);
	}

	STDMETHOD(InPlaceDeactivate)(void) {
		ATLTRACE("Forwarded InPlaceDeactivate\n");
		return subIOleInPlaceObject->InPlaceDeactivate();
	}


//IViewObject

	STDMETHOD(Draw)(DWORD dwDrawAspect, LONG lindex, void *pvAspect,
					DVTARGETDEVICE *ptd, HDC hicTargetDev, HDC hdcDraw,
					LPCRECTL prcBounds, LPCRECTL prcWBounds,
					BOOL (__stdcall * pfnContinue)(DWORD dwContinue),
					DWORD dwContinue) {
			ATLTRACE("Forwarded Draw\n");
			return subIViewObject2->Draw(dwDrawAspect, lindex, pvAspect, ptd, hicTargetDev, hdcDraw,
				prcBounds, prcWBounds, pfnContinue, dwContinue);
	}
	
	STDMETHOD(SetAdvise)(DWORD dwAspect, DWORD advf, IAdviseSink *pAdvise) {
			ATLTRACE("Forwarded:SetAdvise");
			return subIViewObject2->SetAdvise(dwAspect, advf, pAdvise);
	}

#ifdef nothing
// We should not override these since we must manage our own connection point
// to stay in the event stream and change the parms

// IConnectionPointContainer

	STDMETHOD(EnumConnectionPoints)(IEnumConnectionPoints **ppEnum) {
			ATLTRACE("Forwarded EnumConnectionPoints\n");
			return subIConnectionPointContainer->EnumConnectionPoints(ppEnum);
	}

	STDMETHOD(FindConnectionPoint)(REFIID riid, IConnectionPoint **ppCP) {
			ATLTRACE("Forwarded FindConnectionPoint\n");
			return subIConnectionPointContainer->FindConnectionPoint(riid, ppCP);
	}
#endif

// Iwrap
public:
	STDMETHOD(get_prop1)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_prop1)(/*[in]*/ long newVal);
	STDMETHOD(op1)();
	HRESULT OnDraw(ATL_DRAWINFO& di);

};

#endif //__WRAP_H_
