// G2WorkspacePanel.cpp : Implementation of CG2WorkspacePanel
#include "G2Item.h"
#include "G2WorkspacePanel.h"
#include "G2UiGateway.h"
#include "convert.h"
#include "util.h"

/////////////////////////////////////////////////////////////////////////////
// CG2WorkspacePanel


CG2WorkspacePanel::CG2WorkspacePanel()
{
	// Set up all of the default values
    dwCookie = 0;
    m_Loading = false;
    m_MultipleWorkspacePanelEventsIID = IID_NULL;
}

CG2WorkspacePanel::~CG2WorkspacePanel()
{
    GatewayList.unsubscribe((BSTR) mWorkspaceGateway, this);

    // Clean up all of the cached pointers
    if (dwCookie != 0)
        subIConnectionPoint->Unadvise(dwCookie);

    if (mpConnector != NULL)
        mpConnector->RemoveWorkspaceShowingListener(this);
    
    ATLTRACE("Workspace Panel Destructed\n\n\n");
}

HRESULT CG2WorkspacePanel::FinalConstruct()
{
    CLSID CLSID_MultipleWorkspacePanel;
    SmartVariant varResult;

	ATLTRACE("\n\nNew Workspace Panel\n");

    if (FAILED(CLSIDFromProgID(L"MultipleWorkspacePanel.Bean",
        &CLSID_MultipleWorkspacePanel)))
    {
        ATLTRACE(" Can't get CLSID for Bean.");
        return E_CANT_GET_BEAN_CLSID;
    }

    // get a pointer to a bean, this does not create a java object yet
    //   the java object gets created at stream init() or load()
    if (FAILED(CoCreateInstance(CLSID_MultipleWorkspacePanel, NULL,
            CLSCTX_INPROC_SERVER, IID_IDispatch, (void **) &subBeanIDispatch)))
    {
        ATLTRACE(" Can't create the bean.");
        return E_CANT_CREATE_BEAN_OBJ;
    }

    // bean methods do not throw exceptions correctly, so use the real object
    // do not call any methods until we stream init
    if (FAILED(InvokeMethod(subBeanIDispatch, L"getThis", NULL, 0,
        &varResult)))
    {
        ATLTRACE(" Can't create the java object.");
        return E_CANT_CREATE_JAVA_OBJ;
    }
    
    subObjectIDispatch.Attach(varResult.DetachObject());

	// Now querry each needed interface
	subBeanIDispatch->QueryInterface(IID_IViewObject2,
        (void **) &subIViewObject2);
	subBeanIDispatch->QueryInterface(IID_IOleInPlaceObject,
        (void **) &subIOleInPlaceObject);
	subBeanIDispatch->QueryInterface(IID_IOleInPlaceActiveObject,
        (void **) &subIOleInPlaceActiveObject);
	subBeanIDispatch->QueryInterface(IID_IOleControl,
        (void **) &subIOleControl);
	subBeanIDispatch->QueryInterface(IID_IOleObject,
        (void **) &subIOleObject);
	subBeanIDispatch->QueryInterface(IID_IPersistStreamInit,
        (void **) &subIPersistStreamInit);

    // We can not longer get the connection point by interface ID since this changes too often
    SmartComPtr<IConnectionPointContainer> pIConnectionPointContainer;
    if (FAILED(subBeanIDispatch->QueryInterface(IID_IConnectionPointContainer,
          (void **) &pIConnectionPointContainer)))
    {
        ATLTRACE(" Can't get the connection point container.");
        return E_CANT_GET_CP_CONTAINER;
    }
    
    SmartComPtr<IEnumConnectionPoints> pEnumPoints;
    if (FAILED(pIConnectionPointContainer->EnumConnectionPoints(&pEnumPoints)))
    {
        ATLTRACE(" Can't enumerate the connection points.");
        return E_CANT_ENUM_CP;
    }
    
    ULONG num;
    if (FAILED(pEnumPoints->Next(1, &subIConnectionPoint, &num)))
    {
        ATLTRACE(" Can't get the first connection point.");
        return E_CANT_GET_CP;
    }
    
    if (num != 1)
    {
        ATLTRACE(" Unexpected number of connection points.");
        return E_CANT_GET_CP2;
    }
    
    // Now that we have the interface, lets do the following:
    //  Get the TypeInfo for the interface
    //  From the TypeInfo, get the TypeLib
    //  From the TypeLib, get the outgoing TypeInfo
    //  From the outgoing TypeInfo, map disp id's as they come in or build a map ahead of time
    
    SmartComPtr<ITypeInfo> pInfo;
    if (FAILED(subBeanIDispatch->GetTypeInfo(0, 0, &pInfo)))
    {
        ATLTRACE(" Can't get the bean's type info.");
        return E_CANT_GET_TYPEINFO;
    }
    
    SmartComPtr<ITypeLib> pLib;
    unsigned int pIndex;
    if (FAILED(pInfo->GetContainingTypeLib(&pLib, &pIndex)))
    {
        ATLTRACE(" Can't get the bean's type lib.");
        return E_CANT_GET_TYPELIB;
    }
    
    if (FAILED(subIConnectionPoint->GetConnectionInterface(&m_MultipleWorkspacePanelEventsIID)))
    {
        ATLTRACE(" Can't get the connection point interface ID");
        return E_CANT_GET_CP_ID;
    }
    
    if (FAILED(pLib->GetTypeInfoOfGuid(m_MultipleWorkspacePanelEventsIID, &eventInfo)))
    {
        ATLTRACE(" Can't get the event info.");
        return E_CANT_GET_EVENTINFO;
    }

    return S_OK;
}

void CG2WorkspacePanel::update_status(bool status)
{
    ATLTRACE("Workspace Panel Got Update status\n");
	if (status)
        loadWorkspaceAddress();
};

HRESULT CG2WorkspacePanel::SinkInvoke(DISPID dispIdMember, REFIID riid, LCID lcid,
    WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult,
    EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr)
{
    SmartComPtr<IDispatch> pSelf;
	CComBSTR EventName;
	unsigned int num;

    ATLTRACE("Workspace Panel got sink invoke on outgoing interface: 0x%x\n",
        dispIdMember);

    // By referencing ourself, the VB event code can unload this object.
    // and the we will deleted when we exit this method.
    pSelf = (IDispatch*)this;

	// Find the name
    HRESULT hr = eventInfo->GetNames(dispIdMember, &EventName, 1, &num);
	if (FAILED(hr))
        return hr;

   	ATLTRACE(" Name of event: %ws\n", EventName);
	if (wcscmp(EventName, L"selectionChanged") == 0)
    {
    	ATLTRACE(" Fired SelectionChanged event.\n", EventName);
        Fire_SelectionChanged();
	}
    else
    {
        ATLTRACE(" Got, but did not process %ws event.\n", EventName);
    }

    return S_OK;
}

HRESULT CG2WorkspacePanel::AdviseCalled()
{
    CGenericEventSink *temp;
    
    // if we have a cookie then we have already
    // called advise on the underlying bean.
    if (dwCookie != 0)
        return S_OK;

    // for events Now create the call back sink

    // this does not add a reference
    temp = new CGenericEventSink;
    if (temp == NULL)
    {
        ATLTRACE(" Can't create the sink object.");
        return E_CANT_CREATE_SINK_OBJ;
    }
    
    // Tell the sink object to call this object back with events and
    //   act like a ItemProxy Event sink.
    temp->mp_parent_obj = this;
    temp->m_sinkIID = m_MultipleWorkspacePanelEventsIID;

    // this does add a reference
    sinkObject = (IDispatch*)temp;
    ATLTRACE("Created sink object\n");
    
    // Register Sink
    if (FAILED(subIConnectionPoint->Advise(sinkObject, &dwCookie)))
    {
        ATLTRACE(" Can't connect the sink object.");
        return E_CANT_CONNECT_SINK_OBJ;
    }
    
    ATLTRACE("Registered Sink\n");
    
    return S_OK;
}

HRESULT CG2WorkspacePanel::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	DrawText(di.hdcDraw, _T("T2 Workspace Panel"), -1, &rc,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	return S_OK;
}

//
// Fetch a named object from a connector.  This is only called after a connection is made.
//
void CG2WorkspacePanel::loadWorkspaceAddress(void)
{
    GatewayEntry *gEntry;
	SmartComPtr<IG2Item> item;
    HRESULT hr;

    if (!mWorkspaceGateway)
        return;

	// now we need to find the gateway object.
	gEntry = (GatewayEntry *) GatewayList.FindObj((BSTR) mWorkspaceGateway);
	if (!gEntry)
        return;

	if (!gEntry->obj)
        return;

	// ok, we now have a pointer to the connector object.
	mpConnector = (IG2UiGateway2*)((CG2UiGateway*)gEntry->obj);

	// We need to get the named object from the 
	hr = mpConnector->GetNamedItem((BSTR) mWorkspaceName, L"KB-WORKSPACE", &item);
	if (FAILED(hr) || item == (IG2Item*)NULL)
    {
        ATLTRACE(" Can't get the initial workspace.");
        return;
    }

	// stick the new item in the workspace
	hr = AddWorkspace(item, false);
	if (FAILED(hr))
    {
        ATLTRACE(" Can't add the initial workspace.");
        return;
    }

    mpConnector->AddWorkspaceShowingListener(this);
    ShowWorkspace(item);
}

void CG2WorkspacePanel::PropertyChanged(DISPID dispid)
{
    if (!m_Loading)
	    SetDirty(true);

	FireOnChanged(dispid);
}

STDMETHODIMP CG2WorkspacePanel::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2WorkspacePanel,
		&IID_IG2WorkspacePanel2,
	};

    ATLTRACE("ISupportsErrorInfo::InterfaceSupportsErrorInfo\n");
    for (int i = 0; i < sizeof (arr) / sizeof (arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}

    return S_FALSE;
}

// IViewObjectEx
STDMETHODIMP CG2WorkspacePanel::GetViewStatus(DWORD* pdwStatus)
{
    ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
    *pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
    return S_OK;
}

// IOleControl
STDMETHODIMP CG2WorkspacePanel::FreezeEvents(BOOL bFreeze)
{
    ATLTRACE("Forwarded FreezeEvents\n");
    return subIOleControl->FreezeEvents(bFreeze);
}

// IPersistStreamInit
STDMETHODIMP CG2WorkspacePanel::InitNew(void)
{
    ATLTRACE("Called IPersistStreamInit::InitNew\n");
    
    // We do not save the beans so we do not have to
    // forward and InitNew. Also calling InitNew on the bean
    // will replace the java object in the COM object under us
    // which is bad.
    
    if (FAILED(IPersistStreamInitImpl<CG2WorkspacePanel>::InitNew()))
    {
        ATLTRACE(" Can't initialize.");
        return E_CANT_INIT_NEW;
    }
    
    return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::Load(LPSTREAM pStm)
{
    BOOL userMode;
    
    ATLTRACE("Called IPersistStreamInit::Load\n");
    
    // We do not save the beans so we do not have to
    // forward Load.
    
    // now load the properties of our control
    m_Loading = true;
    if (FAILED(IPersistStreamInitImpl<CG2WorkspacePanel>::Load(pStm)))
    {
        ATLTRACE(" Can't load from the stream.");
        return E_CANT_LOAD_FROM_STREAM;
    }
    
    m_Loading = false;

    // check the user mod, don't load in development mode
    if (SUCCEEDED(GetAmbientUserMode(userMode)) && userMode)
    {
        // now load it if it is ready
        loadWorkspaceAddress();
    }
    
    return S_OK;
}

// IOleObject
STDMETHODIMP CG2WorkspacePanel::SetExtent(DWORD aspect, SIZEL *sizel)
{
    ATLTRACE("Called and Forwarded:SetExtent\n");
    IOleObjectImpl<CG2WorkspacePanel>::SetExtent(aspect, sizel);
    return subIOleObject->SetExtent(aspect, sizel);
}

STDMETHODIMP CG2WorkspacePanel::DoVerb(LONG iVerb, LPMSG lpmsg,
    IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent,
    LPCRECT lprcPosRect)
{
    ATLTRACE("Forwarded DoVerb\n");
    return subIOleObject->DoVerb(iVerb, lpmsg, pActiveSite, lindex, hwndParent,
        lprcPosRect);
}

STDMETHODIMP CG2WorkspacePanel::SetClientSite(IOleClientSite *pClientSite)
{
    ATLTRACE("Called and Forwarded SetClientSite\n");
    IOleObjectImpl<CG2WorkspacePanel>::SetClientSite(pClientSite);
    return subIOleObject->SetClientSite(pClientSite);
}

STDMETHODIMP CG2WorkspacePanel::Close(DWORD dwSaveOption)
{
    ATLTRACE("Forwarded Close\n");
    return subIOleObject->Close(dwSaveOption);
}

STDMETHODIMP CG2WorkspacePanel::SetColorScheme(LOGPALETTE *pLogpal)
{
    ATLTRACE("Forwarded SetColorScheme\n");
    return subIOleObject->SetColorScheme(pLogpal);
}

//IOleWindow
STDMETHODIMP CG2WorkspacePanel::GetWindow(HWND *phwnd)
{
    ATLTRACE("Forwarded: GetWindow()\n");
    return subIOleInPlaceObject->GetWindow(phwnd);
}

// IOleInPlaceObject
STDMETHODIMP CG2WorkspacePanel::SetObjectRects(LPCRECT rec1, LPCRECT rec2)
{
    ATLTRACE("Forwarded:SetObjectRects\n");
    return subIOleInPlaceObject->SetObjectRects(rec1, rec2);
}

STDMETHODIMP CG2WorkspacePanel::InPlaceDeactivate(void)
{
    ATLTRACE("Forwarded InPlaceDeactivate\n");
    return subIOleInPlaceObject->InPlaceDeactivate();
}

//IViewObject
// Since the control has its own window, this is never called!
STDMETHODIMP CG2WorkspacePanel::Draw(DWORD dwDrawAspect, LONG lindex,
    void *pvAspect, DVTARGETDEVICE *ptd, HDC hicTargetDev, HDC hdcDraw,
    LPCRECTL prcBounds, LPCRECTL prcWBounds,
    BOOL (__stdcall * pfnContinue)(DWORD dwContinue), DWORD dwContinue)
{
    ATLTRACE("Forwarded Draw\n");
    return subIViewObject2->Draw(dwDrawAspect, lindex, pvAspect, ptd,
        hicTargetDev, hdcDraw, prcBounds, prcWBounds, pfnContinue,
        dwContinue);
}

STDMETHODIMP CG2WorkspacePanel::SetAdvise(DWORD dwAspect, DWORD advf,
    IAdviseSink *pAdvise)
{
    ATLTRACE("Forwarded:SetAdvise");
    return subIViewObject2->SetAdvise(dwAspect, advf, pAdvise);
}

// IG2WorkspacePanel
STDMETHODIMP CG2WorkspacePanel::get_UpdateWhileHidden(VARIANT_BOOL * pVal)
{
	SmartVariant varResult;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getUpdateWhileHidden", NULL, 0,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    *pVal = varResult.boolVal;
	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::put_UpdateWhileHidden(VARIANT_BOOL newVal)
{
	SmartVariant pvars[1];

	pvars[0] = (long)newVal;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setUpdateWhileHiddenForVB", pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(7);
	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::get_ShowNewWorkspaces(VARIANT_BOOL * pVal)
{
	SmartVariant varResult;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getShowNewWorkspaces", NULL, 0,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*pVal = varResult.boolVal;
    return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::put_ShowNewWorkspaces(VARIANT_BOOL newVal)
{
	SmartVariant pvars[1];

	pvars[0] = (long)newVal;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setShowNewWorkspacesForVB", pvars, 1,
                    NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(6);
	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::AddWorkspace(IG2Item *Workspace,
    VARIANT_BOOL UpdateWhileHidden)
{
	SmartVariant pvars[2];

	SUBOBJECT_AS_VARIANT(Workspace, &pvars[1]);

    pvars[0] = UpdateWhileHidden;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"addWorkspaceForVBTwo", pvars, 2, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::ClearSelection()
{
    BSTR error_msg = CallDispatch(subObjectIDispatch, L"clearSelection", NULL, 0, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::DeleteSelection()
{
    BSTR error_msg = CallDispatch(subObjectIDispatch, L"deleteSelection", NULL, 0, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::GetSelection(VARIANT *pSelectedItems)
{
	SmartVariant varResult;
    HRESULT hresult;
  
    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getSelectionAsSequence",
                        NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (varResult.IsNull())
    {
        VariantInit(pSelectedItems);
        return S_OK;
    }

    hresult = WorkspaceElementsToItems(varResult, &pSelectedItems->parray);
    if (FAILED(hresult))
        return hresult;

    pSelectedItems->vt = VT_ARRAY | VT_DISPATCH;

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::MoveSelection(long DeltaX, long DeltaY,
                                              VARIANT_BOOL EnlargeWorkspaceIfNecessary)
{
	SmartVariant pvars[3];

	pvars[2] = DeltaX;
	pvars[1] = DeltaY;
	pvars[0] = (long)EnlargeWorkspaceIfNecessary;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"moveSelectionForVB",
                      pvars, 3, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::NextWorkspace()
{
	BSTR error_msg = CallDispatch(subObjectIDispatch, L"nextWorkspace", NULL, 0, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::PreviousWorkspace()
{
    BSTR error_msg = CallDispatch(subObjectIDispatch, L"previousWorkspace", NULL, 0, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::RemoveWorkspace(IG2Item *Workspace)
{
	SmartVariant pvars[1];
    SmartVariant varResult;

    SUBOBJECT_AS_VARIANT(Workspace, &pvars[0]);

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"removeWorkspace", pvars, 1,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::SelectAll()
{
    BSTR error_msg = CallDispatch(subObjectIDispatch, L"selectAll", NULL, 0, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::ShowWorkspace(IG2Item *Workspace)
{
	SmartVariant pvars[1];

    SUBOBJECT_AS_VARIANT(Workspace, &pvars[0]);

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setCurrentWorkspace", pvars, 1,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::get_WorkspaceAddress(BSTR * pVal)
{
	*pVal = SysAllocString((BSTR) mWorkspaceAddress);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::put_WorkspaceAddress(BSTR newVal)
{	
	USES_CONVERSION;
	char address[300];
	
    mWorkspaceAddress.Empty();
    mWorkspaceName.Empty();
	GatewayList.unsubscribe((BSTR) mWorkspaceGateway, this);
    mWorkspaceGateway.Empty();

    if (newVal != NULL)
    {
	    mWorkspaceAddress = newVal;
        strcpy(address, W2A(newVal));

	    // now break the name into its parts
	    char name[300];
    	char gateway[300];
	    for (char *ptr = address; *ptr; ptr++) {
		    if (*ptr == '@') break;
    	}

        if (*ptr) {
            *ptr = 0; ptr++;
	        strcpy(name, address);  // get name
	        strcpy(gateway, ptr); 

	        mWorkspaceName = A2W(name);
	        mWorkspaceGateway = A2W(gateway);
	        GatewayList.subscribe((BSTR) mWorkspaceGateway, this);
        }
    }

	PropertyChanged(21);
	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::AddElementToSelection(IG2Item * Item)
{
    SmartVariant pvars[1];
    SmartVariant varResult;
    BSTR error_msg;

    SUBOBJECT_AS_VARIANT(Item, &pvars[0]);
    if (pvars[0].pdispVal == NULL)
        return S_OK;

    error_msg = CallDispatch(subObjectIDispatch, L"findElement", pvars, 1,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsObject())
        return S_OK;

    pvars[0] = varResult.pdispVal;

    error_msg = CallDispatch(subObjectIDispatch, L"addElementToSelection",
                        pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::RemoveElementFromSelection(IG2Item * Item)
{
    SmartVariant pvars[1];
    SmartVariant varResult;
    BSTR error_msg;

    SUBOBJECT_AS_VARIANT(Item, &pvars[0]);
    if (pvars[0].pdispVal == NULL)
        return S_OK;

    error_msg = CallDispatch(subObjectIDispatch, L"findElement", pvars, 1,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsObject())
        return S_OK;

    pvars[0] = varResult.pdispVal;

    error_msg = CallDispatch(subObjectIDispatch,
                        L"RemoveElementFromSelection", pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::ScrollToLocation(long X, long Y)
{
	SmartVariant pvars[2];

    ATLTRACE("CG2WorkspacePanel::ScrollToLocation()\n");

	pvars[1] = X;
	pvars[0] = Y;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"scrollToLocation", pvars, 2, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::ProcessShowWorkspaceEvent(IDispatch* WorkspaceShowingEvent)
{
	SmartVariant pvars[1];

    ATLTRACE("CG2WorkspacePanel::ProcessShowWorkspaceEvent()\n");

	pvars[0] = WorkspaceShowingEvent;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"showWorkspace", pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::ProcessHideWorkspaceEvent(IDispatch* WorkspaceShowingEvent)
{
	SmartVariant pvars[1];

    ATLTRACE("CG2WorkspacePanel::ProcessHideWorkspaceEvent()\n");

	pvars[0] = WorkspaceShowingEvent;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"hideWorkspace", pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::_subObject(IDispatch * * subObject)
{
    _SUBOBJECT_METHOD_IMPL(subObject, subObjectIDispatch);
}

STDMETHODIMP CG2WorkspacePanel::GetWorkspaces(VARIANT *ArrayOfG2Items)
{
	SmartVariant varResult;
    HRESULT hresult;
  
    ATLTRACE("CG2WorkspacePanel::GetWorkspaces()\n");

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getWorkspaces",
                        NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (varResult.IsNull())
    {
        VariantInit(ArrayOfG2Items);
        return S_OK;
    }

    hresult = JavaVariantArrayToItems(varResult.parray, ArrayOfG2Items);
    if (FAILED(hresult))
        return hresult;

	return S_OK;
}

STDMETHODIMP CG2WorkspacePanel::RemoveAllWorkspaces()
{
    HRESULT hresult;
	SmartVariant varResult;
    long LBound;
    long UBound;
    long i;

    ATLTRACE("CG2WorkspacePanel::RemoveAllWorkspaces()\n");

    hresult = GetWorkspaces(&varResult);
    if (FAILED(hresult) || varResult.IsEmpty())
        return hresult;

    if (!varResult.IsObjectArray())
        return Error("GetWorkspaces() did not return an array objects.\n");

    hresult = SafeArrayGetLBound(varResult.parray, 1, &LBound);
	if (FAILED(hresult))
        return hresult;

    hresult = SafeArrayGetUBound(varResult.parray, 1, &UBound);
	if (FAILED(hresult))
        return hresult;

    for (i = LBound; i <= UBound; i++)
    {
        SmartComPtr<IG2Item> pItem;

		SafeArrayGetElement(varResult.parray, &i, &pItem);

        RemoveWorkspace(pItem);
    }

	return S_OK;
}
