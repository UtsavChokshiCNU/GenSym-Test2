// G2UiGateway.cpp : Implementation of CG2UiGateway

#include "G2Symbol.h"
#include "G2Structure.h"
#include "G2UiGateway.h"
#include "convert.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////
// CG2UiGateway

CG2UiGateway::CG2UiGateway()
{
    // Set up all of the defualt values
    dwCookie = 0;
    m_connect_at_start = true;
    m_call_timeout = 30;
    m_connected = false;
    m_HostAndPort = L"localhost:1111";
    
    // set up the initial value for the id
    WCHAR name[100];
    GatewayList.getUniqueName(name);
    m_GatewayId = name;
    m_Loading = false;
    m_TwConnectorEventsIID = IID_NULL;
}

CG2UiGateway::~CG2UiGateway()
{
    GatewayList.unsubscribe((BSTR) m_GatewayId, this);
    
    if (dwCookie != 0)
        subIConnectionPoint->Unadvise(dwCookie);


    if (m_connected)
        Disconnect();
    
    ATLTRACE("UI Gateway Destructed\n\n\n");
}

HRESULT CG2UiGateway::FinalConstruct()
{
    CLSID CLSID_TwConnector;
    SmartVariant varResult;
    
    ATLTRACE("\n\nNew Ui Gateway\n");
    
    if (FAILED(CLSIDFromProgID(L"TwConnector.Bean", &CLSID_TwConnector)))
    {
        ATLTRACE(" Can't get CLSID for Bean.");
        return E_CANT_GET_BEAN_CLSID;
    }
    
    // get a pointer to a bean, this does not create a java object yet
    //   the java object gets created at stream init() or load()
    if (FAILED(CoCreateInstance(CLSID_TwConnector, NULL, CLSCTX_INPROC_SERVER,
            IID_IDispatch, (void **) &subBeanIDispatch)))
    {
        ATLTRACE(" Can't create the bean.");
        return E_CANT_CREATE_BEAN_OBJ;
    }
    
    // bean methods do not throw exceptions correctly, so use the real object
    if (FAILED(InvokeMethod(subBeanIDispatch, L"getThis", NULL, 0,
        &varResult)))
    {
        ATLTRACE(" Can't create the java object.");
        return E_CANT_CREATE_JAVA_OBJ;
    }
    
    subObjectIDispatch.Attach(varResult.DetachObject());
    
    // we want a different default interface name to separate us from Java
    setG2InterfaceName(L"G2-UI-GATEWAY-INTERFACE");

    // Now querry each needed interface
    subBeanIDispatch->QueryInterface(IID_IViewObject2, (void **) &subIViewObject2);
    subBeanIDispatch->QueryInterface(IID_IOleInPlaceObject, (void **) &subIOleInPlaceObject);
    subBeanIDispatch->QueryInterface(IID_IOleInPlaceActiveObject, (void **) &subIOleInPlaceActiveObject);
    subBeanIDispatch->QueryInterface(IID_IOleControl, (void **) &subIOleControl);
    subBeanIDispatch->QueryInterface(IID_IOleObject, (void **) &subIOleObject);
    subBeanIDispatch->QueryInterface(IID_IPersistStreamInit, (void **) &subIPersistStreamInit);
    
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
    
    if (FAILED(subIConnectionPoint->GetConnectionInterface(&m_TwConnectorEventsIID)))
    {
        ATLTRACE(" Can't get the connection point interface ID");
        return E_CANT_GET_CP_ID;
    }
    
    if (FAILED(pLib->GetTypeInfoOfGuid(m_TwConnectorEventsIID, &eventInfo)))
    {
        ATLTRACE(" Can't get the event info.");
        return E_CANT_GET_EVENTINFO;
    }
    
    return S_OK;
}

void CG2UiGateway::update_status(bool status)
{
    ATLTRACE("Got Update status\n");
};

HRESULT CG2UiGateway::SinkInvoke(DISPID dispIdMember, REFIID riid, LCID lcid,
    WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult,
    EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr)
{
    SmartComPtr<IDispatch> pSelf;
	CComBSTR EventName;
	unsigned int num;
    IDispatch* pEventObj;

	ATLTRACE("Gateway got sink invoke on outgoing interface:%d\n", dispIdMember);

    // By referencing ourself, the VB event code can unload this object.
    // and the we will deleted when we exit this method.
    pSelf = (IDispatch*)this;

    // Find the name
	if (FAILED(eventInfo->GetNames(dispIdMember, &EventName, 1, &num)))
	    return S_OK;

    ATLTRACE("Name of event: %ws\n", (BSTR)EventName);

	if (!wcscmp(EventName, L"g2IsPaused"))
    {
		CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_G2StateChange(g2Paused);
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_G2StateChange(g2Paused);
	}
    else if (!wcscmp(EventName, L"g2IsResumed"))
    {
		CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_G2StateChange(g2Resumed);
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_G2StateChange(g2Resumed);
	}
    else if (!wcscmp(EventName, L"g2IsReset"))
    {
		CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_G2StateChange(g2Reset);
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_G2StateChange(g2Reset);
	}
    else if (!wcscmp(EventName, L"g2IsStarted"))
    {
		CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_G2StateChange(g2Running);
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_G2StateChange(g2Running);
	}
    else if (!wcscmp(EventName, L"g2ConnectionClosed"))
    {
        m_connected = false;
		CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_G2Disconnected();
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_G2Disconnected();
	}
    else if (!wcscmp(EventName, L"g2ConnectionInitialized"))
    {
        m_connected = true;
		CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_G2Connected();
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_G2Connected();
	}
    else if (!wcscmp(EventName, L"communicationError"))
    {
    	SmartVariant ComVariant;

        // arg check, 1 java object
        if (pDispParams->cArgs != 1)
        {
            ATLTRACE(" Did not get exactly 1 argument.\n");
            return S_OK;
        }

        if (pDispParams->rgvarg[0].vt != VT_DISPATCH)
        {
            ATLTRACE(" Did not get a dispatch pointer.\n");
            return S_OK;
        }

        pEventObj = pDispParams->rgvarg[0].pdispVal;

		if (FAILED(InvokeMethod(pEventObj, L"get_errorMessage", NULL, 0,
            &ComVariant)))
        {
            ATLTRACE(" get_errorMessage Failed.\n");
            return S_OK;
        }

        if (!ComVariant.IsString())
        {
            ATLTRACE(" Did not get a string.\n");
            return S_OK;
        }

        CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_Error(ComVariant.bstrVal);
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_Error(ComVariant.bstrVal);
	}
    else if (!wcscmp(EventName, L"loggedIn"))
    {
		CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_UserLoggedIn();
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_UserLoggedIn();
	}
    else if (!wcscmp(EventName, L"loggedOut"))
    {
		CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_UserLoggedOut();
		CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_UserLoggedOut();
	}
    else if (!wcscmp(EventName, L"g2MessageReceived"))
    {	
    	SmartVariant ComVariant;

        // arg check, 1 java object
        if (pDispParams->cArgs != 1)
        {
            ATLTRACE(" Did not get exactly 1 argument.\n");
            return S_OK;
        }

        if (pDispParams->rgvarg[0].vt != VT_DISPATCH)
        {
            ATLTRACE(" Did not get a dispatch pointer.\n");
            return S_OK;
        }

        pEventObj = pDispParams->rgvarg[0].pdispVal;

        InvokeMethod(pEventObj, L"getMessage", NULL, 0, &ComVariant);
        CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_GotMessage(ComVariant.bstrVal);
        CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_GotMessage(ComVariant.bstrVal);
	}
    else if (!wcscmp(EventName, L"userModeChanged"))
    {
		CComBSTR usermode;

		get_UserMode(&usermode);
		ATLTRACE("New User mode:%ws\n", (BSTR)usermode);
        CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_UserModeChanged(usermode);
        CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_UserModeChanged(usermode);
	}
    else if (!wcscmp(EventName, L"showWorkspace") ||
        !wcscmp(EventName, L"hideWorkspace"))
    {
    	SmartVariant ComVariant;
        SmartComPtr<G2Item2> pWorkspace;
        SmartComPtr<IG2Structure> pParticulars;

        // arg check, 1 java object
        if (pDispParams->cArgs != 1)
        {
            ATLTRACE(" Did not get exactly 1 argument.\n");
            return S_OK;
        }

        if (pDispParams->rgvarg[0].vt != VT_DISPATCH)
        {
            ATLTRACE(" Did not get a dispatch pointer.\n");
            return S_OK;
        }

        pEventObj = pDispParams->rgvarg[0].pdispVal;
        if (FAILED(CallDispatch(pEventObj, L"getWorkspace", NULL, 0,
            &ComVariant)))
        {
            ATLTRACE(" getWorkspace() FAILED\n");
            return S_OK;
        }

        // sometimes object return by getWorkspace gets ruined by the beans
        //   bridge, so check the object and try again if nessary
        if (FAILED(JavaToItem(ComVariant.pdispVal, &pWorkspace)))
        {
            ATLTRACE(" pEventObj.getWorkspace() returned a bad object.\n");
            ComVariant.Clear();
    		if (FAILED(CallDispatch(pEventObj, L"getWorkspace", NULL, 0,
                &ComVariant)))
            {
                ATLTRACE(" getWorkspace() FAILED again\n");
                return S_OK;
            }

            if (FAILED(JavaToItem(ComVariant.pdispVal, &pWorkspace)))
            {
                ATLTRACE(" pEventObj.getWorkspace() returned a bad object again.\n");
                CComBSTR ErrorMsg(L"Received an invalid workspace event.");
                CProxy_G2UiGatewaySource<CG2UiGateway>::Fire_Error(ErrorMsg);
                CProxy_G2UiGatewaySource2<CG2UiGateway>::Fire_Error(ErrorMsg);
                return S_OK;
            }
        }

        ComVariant.Clear();
        if (FAILED(InvokeMethod(pEventObj, L"getParticulars", NULL, 0,
            &ComVariant)))
        {
            ATLTRACE(" getParticulars() FAILED\n");
            return S_OK;
        }

        if (FAILED(JavaToStructure(ComVariant.pdispVal, &pParticulars)))
        {
            ATLTRACE(" JavaToStructure() FAILED\n");
            return S_OK;
        }

        if (!wcscmp(EventName, L"showWorkspace"))
        {
            CProxy_G2UiGatewaySource<CG2UiGateway>::
                Fire_ShowWorkspace(pWorkspace, pParticulars, pEventObj);
            CProxy_G2UiGatewaySource2<CG2UiGateway>::
                Fire_ShowWorkspace(pWorkspace, pParticulars, pEventObj);
        }
        else
        {
            CProxy_G2UiGatewaySource<CG2UiGateway>::
                Fire_HideWorkspace(pWorkspace, pEventObj);
            CProxy_G2UiGatewaySource2<CG2UiGateway>::
                Fire_HideWorkspace(pWorkspace, pEventObj);
        }
	}
    else
    {
        ATLTRACE("Got, but did not process %ws event\n", EventName);
    }

    return S_OK;
}

HRESULT CG2UiGateway::AdviseCalled()
{
    CGenericEventSink *temp;
    HRESULT hresult;
    
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
    //   act like a TwConnector Event sink.
    temp->mp_parent_obj = this;
    temp->m_sinkIID = m_TwConnectorEventsIID;

    // this does add a reference
    sinkObject = temp;

    ATLTRACE("Created sink object\n");
    
    // Register Sink
    hresult = subIConnectionPoint->Advise(sinkObject, &dwCookie);
    if (FAILED(hresult))
    {
        ATLTRACE(" Can't connect the sink object.");
        return E_CANT_CONNECT_SINK_OBJ;
    }

    ATLTRACE("Registered Sink\n");
    
    GatewayList.subscribe((BSTR) m_GatewayId, this);

    return S_OK;
}

HRESULT CG2UiGateway::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	DrawText(di.hdcDraw, _T("Gensym Telewindows2 Connector"), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	return S_OK;
}

BSTR CG2UiGateway::setG2InterfaceName(BSTR newVal)
{
	SmartVariant pvars[1];

	if (FAILED(NewUpperCaseBSTR(newVal, &pvars[0])))
        return L"Out of memory";

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setGsiInterfaceName",
                        pvars, 1, NULL);
    return error_msg;
}

void CG2UiGateway::PropertyChanged(DISPID dispid)
{
    if (!m_Loading)
	    SetDirty(true);

	FireOnChanged(dispid);
}

HRESULT CG2UiGateway::GetItemByHandle(long ItemHandle, long HandleVersion,
                                    G2Item2 **ReturnItem)
{
	SmartVariant varResult;
	SmartVariant pvars[2];

	ATLTRACE("Getting an item by handle 0x%08.8x, ver 0x%08.8x\n\n", ItemHandle,
        HandleVersion);

    pvars[1] = ItemHandle;

    pvars[0] = HandleVersion;

	BSTR error_msg = CallDispatch(subObjectIDispatch, L"getItem", pvars,
                        2, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

	if (FAILED(JavaToItem(varResult.pdispVal, (G2Item2**)ReturnItem)))
        return Error("Received an Invalid item from G2.");

    return S_OK;
}

STDMETHODIMP CG2UiGateway::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2UiGateway,
		&IID_IG2UiGateway2,
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
STDMETHODIMP CG2UiGateway::GetViewStatus(DWORD* pdwStatus)
{
    ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
    *pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
    return S_OK;
}

// IOleControl
STDMETHODIMP CG2UiGateway::FreezeEvents(BOOL bFreeze)
{
    ATLTRACE("Forwarded FreezeEvents\n");
    return subIOleControl->FreezeEvents(bFreeze);
}

// IPersistStreamInit
STDMETHODIMP CG2UiGateway::InitNew(void)
{
	SIZEL sz;
    
    ATLTRACE("Called IPersistStreamInit::InitNew\n");
    
    // We do not save the beans so we do not have to
    // forward and InitNew. Also calling InitNew on the bean
    // will replace the java object in the COM object under us
    // which is bad.
    
    if (FAILED(IPersistStreamInitImpl<CG2UiGateway>::InitNew()))
    {
        ATLTRACE(" Can't initialize.");
        return E_CANT_INIT_NEW;
    }

    // set the default size to the size of an icon
    sz.cx = 32;
    sz.cy = 32;
    AtlPixelToHiMetric(&sz, &m_sizeExtent);
    m_sizeNatural = m_sizeExtent;

    return S_OK;
}

STDMETHODIMP CG2UiGateway::Load(LPSTREAM pStm)
{
	SIZEL sz;
	BOOL userMode;
    
    ATLTRACE("Called IPersistStreamInit::Load\n");
    
    // We do not save the beans so we do not have to
    // forward Load.
    
    // now load the properties of our control
    m_Loading = true;
    if (FAILED(IPersistStreamInitImpl<CG2UiGateway>::Load(pStm)))
    {
        ATLTRACE(" Can't load from the stream.");
        return E_CANT_LOAD_FROM_STREAM;
    }
    
    m_Loading = false;

	// Set the true size
	IOleObjectImpl<CG2UiGateway>::GetExtent(DVASPECT_CONTENT, &sz);
	subIOleObject->SetExtent(DVASPECT_CONTENT, &sz);

    // check the user mod, don't load in development mode
    if (m_connect_at_start && SUCCEEDED(GetAmbientUserMode(userMode)) && userMode)
    {
		if (FAILED(Connect()))
        {
            ATLTRACE(" Can't connect to G2 at start.\n");
            // The user can call IsConnected() to find out if this connected
            // if we abort now VBA apps like Word and Excel may have problems
            return S_OK;
        }

        GatewayList.subscribe((BSTR) m_GatewayId, this);
        GatewayList.update_status((BSTR) m_GatewayId, true, this);
	}

    return S_OK;
}

// IOleObject
STDMETHODIMP CG2UiGateway::SetExtent(DWORD aspect, SIZEL *sizel)
{
    ATLTRACE("Called and Forwarded:SetExtent\n");
    IOleObjectImpl<CG2UiGateway>::SetExtent(aspect, sizel);
    return subIOleObject->SetExtent(aspect, sizel);
}

STDMETHODIMP CG2UiGateway::DoVerb(LONG iVerb, LPMSG lpmsg,
    IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent,
    LPCRECT lprcPosRect)
{
    ATLTRACE("Forwarded DoVerb\n");
    return subIOleObject->DoVerb(iVerb, lpmsg, pActiveSite, lindex, hwndParent,
        lprcPosRect);
}

STDMETHODIMP CG2UiGateway::SetClientSite(IOleClientSite *pClientSite)
{
    ATLTRACE("Called and Forwarded SetClientSite\n");
    IOleObjectImpl<CG2UiGateway>::SetClientSite(pClientSite);
    return subIOleObject->SetClientSite(pClientSite);
}

STDMETHODIMP CG2UiGateway::Close(DWORD dwSaveOption)
{
    ATLTRACE("Forwarded Close\n");
    return subIOleObject->Close(dwSaveOption);
}

// IOleInPlaceObject
STDMETHODIMP CG2UiGateway::SetObjectRects(LPCRECT rec1, LPCRECT rec2)
{
    ATLTRACE("Forwarded:SetObjectRects\n");
    return subIOleInPlaceObject->SetObjectRects(rec1, rec2);
}

STDMETHODIMP CG2UiGateway::GetWindow(HWND *phwnd)
{
    ATLTRACE("Forwarded: GetWindow()\n");
    return subIOleInPlaceObject->GetWindow(phwnd);
}

STDMETHODIMP CG2UiGateway::InPlaceDeactivate(void)
{
    ATLTRACE("Forwarded InPlaceDeactivate\n");
    return subIOleInPlaceObject->InPlaceDeactivate();
}

//IViewObject
// Since the control has its own window, this is never called!
STDMETHODIMP CG2UiGateway::Draw(DWORD dwDrawAspect, LONG lindex,
    void *pvAspect, DVTARGETDEVICE *ptd, HDC hicTargetDev, HDC hdcDraw,
    LPCRECTL prcBounds, LPCRECTL prcWBounds,
    BOOL (__stdcall * pfnContinue)(DWORD dwContinue), DWORD dwContinue)
{
    ATLTRACE("Forwarded Draw\n");
    return subIViewObject2->Draw(dwDrawAspect, lindex, pvAspect, ptd,
        hicTargetDev, hdcDraw, prcBounds, prcWBounds, pfnContinue,
        dwContinue);
}

STDMETHODIMP CG2UiGateway::SetAdvise(DWORD dwAspect, DWORD advf,
    IAdviseSink *pAdvise)
{
    ATLTRACE("Forwarded:SetAdvise");
    return subIViewObject2->SetAdvise(dwAspect, advf, pAdvise);
}

STDMETHODIMP CG2UiGateway::Disconnect()
{
    if (!m_connected)
        return S_OK;

    m_connected = false;

	BSTR error_msg = CallDispatch(subObjectIDispatch, L"closeConnection", NULL,
                        0, NULL);
	if (error_msg != NULL)
        return Error(error_msg);

    // we need to give java time right now to send us a connectionClosed event
    // or will will not get one later
    ::Sleep(1);

    return S_OK;
}

STDMETHODIMP CG2UiGateway::GetNamedItem(BSTR ItemName, BSTR ItemClass,
                                        IG2Item **ReturnItem)
{
	SmartVariant varResult;
	SmartVariant pvars[2];

	ATLTRACE("Getting named item %ws\n\n", ItemName);

    BSTR error_msg = BSTRToJava(ItemName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    if (ItemClass == NULL || ItemClass[0] == 0)
        error_msg = OLECHARToJavaSymbol(L"ITEM", &pvars[1]);  // default value
    else
        error_msg = BSTRToJava(ItemClass, &pvars[1]);

    if (error_msg != NULL)
        return Error(error_msg);

	error_msg = CallDispatch(subObjectIDispatch, L"getUniqueNamedItem", pvars,
                        2, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

	HRESULT hresult = JavaToItem(varResult.pdispVal, (G2Item2**)ReturnItem);
    if (FAILED(hresult))
        return Error("Received an Invalid item from G2.");

    return S_OK;
}

STDMETHODIMP CG2UiGateway::StartG2Procedure(BSTR ProcedureName,
                                          SAFEARRAY **Arguments)
{
	SmartVariant pvars[2];

    BSTR error_msg = BSTRToJava(ProcedureName, &pvars[1]);
    if (error_msg != NULL)
        return Error(error_msg);

    HRESULT hresult = ArrayToVariant(*Arguments, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

	error_msg = CallDispatch(subObjectIDispatch, L"startRPCForVB", pvars,
                      2, NULL);

    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2UiGateway::CallG2Procedure(BSTR ProcedureName, SAFEARRAY **Arguments, VARIANT *ReturnValues)
{
	SmartVariant pvars[3];
    SmartVariant varResult;

    BSTR error_msg = BSTRToJava(ProcedureName, &pvars[2]);
    if (error_msg != NULL)
        return Error(error_msg);

    HRESULT hresult = ArrayToVariant(*Arguments, &pvars[1]);
    if (FAILED(hresult))
        return hresult;

    pvars[0] = m_call_timeout * 1000;

    error_msg = CallDispatch(subObjectIDispatch, L"callRPCForVB", pvars, 3,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    return JavaVariantToComVariant(varResult, ReturnValues);
}

STDMETHODIMP CG2UiGateway::Connect()
{
    if (m_connected)
    {
        return Error(L"The gateway cannot connect while connected, "
            L"use the Disconnect method before reconnecting.");
    }

	BSTR error_msg = CallDispatch(subObjectIDispatch, L"createConnection", NULL, 0,
                        NULL);
	if (error_msg != NULL)
        return Error(error_msg);

    m_connected = true;
	return S_OK;
}

STDMETHODIMP CG2UiGateway::CreateItem(BSTR ItemClass, IG2Item **ReturnItem)
{
	SmartVariant pvars[1];
    SmartVariant varResult;

    BSTR error_msg = BSTRToJava(ItemClass, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    error_msg = CallDispatch(subObjectIDispatch, L"createItem", pvars, 1,
                        &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

    return JavaToItem(varResult.pdispVal, (G2Item2**)ReturnItem);
}

STDMETHODIMP CG2UiGateway::PostMessage(BSTR Message)
{
	SmartVariant pvars[1];
	
    pvars[0] = Message;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"returnMessage", pvars, 1,
                        NULL);
	if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2UiGateway::ClassInstances(BSTR ClassName, VARIANT_BOOL StrictClassOnly, VARIANT *ReturnInstances)
{
	SmartVariant pvars[1];
    SmartVariant varResult;

    // for later: what do we do when strict instances is false

    BSTR error_msg = BSTRToJava(ClassName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    error_msg = CallDispatch(subObjectIDispatch, L"getStrictInstancesOfClass",
                        pvars, 1, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

	return SequenceToVariant(varResult.pdispVal, ReturnInstances, 0, true);
}

STDMETHODIMP CG2UiGateway::DirectSubclasses(BSTR ClassName, VARIANT *RetArray)
{
	SmartVariant pvars[1];
    SmartVariant varResult;

    BSTR error_msg = BSTRToJava(ClassName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    error_msg = CallDispatch(subObjectIDispatch, L"getDirectSubclasses",
                        pvars, 1, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

	return SequenceToVariant(varResult.pdispVal, RetArray, 0, true);
}

STDMETHODIMP CG2UiGateway::Symbol(BSTR SymbolName, IG2Symbol **ReturnSymbol)
{
    return CreateSymbol(SymbolName, ReturnSymbol);
}

STDMETHODIMP CG2UiGateway::Structure(SAFEARRAY **NameValuePairs, IG2Structure **ReturnStructure)
{
    return CreateStructure(CLSID_G2UiGateway, *NameValuePairs, ReturnStructure);
}

STDMETHODIMP CG2UiGateway::get_ConnectAtStart(VARIANT_BOOL * pVal)
{
    ATLTRACE("CG2UiGateway::get_ConnectAtStart()\n");

    // true is 1, but VARIANT_TRUE is short -1 (0xFFFF), returning a 1 makes the
    //   VB "Not" operator not work for true values, because it is a bitwise not
    //   on 0x0001 becomes 0X100 which is still true.
    if (m_connect_at_start)
	    *pVal = VARIANT_TRUE;
    else
        *pVal = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_ConnectAtStart(VARIANT_BOOL newVal)
{
	m_connect_at_start = newVal == VARIANT_TRUE;

	PropertyChanged(13);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_G2State(G2States * pVal)
{
	SmartVariant varResult;
	CComBSTR bstring;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getG2State", NULL, 0,
                        &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

    (void)JavaToBSTR(varResult.pdispVal, &bstring);

	ATLTRACE("G2UiGateway::GetG2State() = %ws\n", (BSTR)bstring);

    // match up the string to a enum value
    if (wcscmp(bstring, L"RUNNING") == 0)
        *pVal = g2Running;
    else if (wcscmp(bstring, L"PAUSED") == 0)
        *pVal = g2Paused;
    else
        *pVal = g2Reset;

    return S_OK;
}

STDMETHODIMP CG2UiGateway::put_G2State(G2States newVal)
{
    OLECHAR* state;
	SmartVariant pvars[1];
    SmartVariant varResult;

    switch (newVal)
    {
    case g2Reset:
        state = L"RESET";
        break;

    case g2Paused:
        state = L"PAUSED";
        break;

    default:
    case g2Running:
        state = L"RUNNING";
        break;
    }

    BSTR error_msg = OLECHARToJavaSymbol(state, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    error_msg = CallDispatch(subObjectIDispatch, L"setG2State", pvars, 1,
                        &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_G2InterfaceClassName(BSTR * pVal)
{
	SmartVariant varResult;

    ATLTRACE("CG2UiGateway::get_G2InterfaceClassName()\n");

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getGsiInterfaceClassName",
                        NULL, 0, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

    *pVal = varResult.DetachString();
	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_G2InterfaceClassName(BSTR newVal)
{
	SmartVariant pvars[1];

	HRESULT hresult = NewUpperCaseBSTR(newVal, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setGsiInterfaceClassName",
                        pvars, 1, NULL);
	if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(17);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_RemoteInitializationString(BSTR * pVal)
{
	SmartVariant varResult;

    ATLTRACE("CG2UiGateway::get_RemoteInitializationString()\n");

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getRemoteProcessInitString",
                        NULL, 0, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

    *pVal = varResult.DetachString();
	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_RemoteInitializationString(BSTR newVal)
{
	SmartVariant pvars[1];

	pvars[0] = newVal;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setRemoteProcessInitString",
                        pvars, 1, NULL);
	if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(18);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_G2Location(BSTR * pVal)
{
    ATLTRACE("CG2UiGateway::get_G2Location()\n");
	*pVal = SysAllocString((BSTR) m_HostAndPort);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_G2Location(BSTR newVal)
{
    unsigned int newValLen;
    WCHAR* pPort;
    unsigned int nameLen;
    SmartVariant pvars[1];
    BSTR error_msg;

	ATLTRACE("CGateway::put_G2Location(%ws)\n", newVal);

	newValLen = SysStringLen(newVal);
	if (newValLen == 0)
		return Error("Invalid location format, the name is missing.");

	// Disassemble Host:Port for GsiContext Object
	// Establish string and get the first token which should be Host
    pPort = wcschr(newVal, L':');
    if (pPort == NULL)
    {
        // Assume default G2 port of 1111.
     	pPort= L"1111";
        nameLen = newValLen;
    }
    else
    {
        nameLen = pPort - newVal;
    
        // move past the : and check the first digit or the port
        pPort++;
	    if (!iswdigit(*pPort))
            return Error(L"Invalid location format, the port is not numeric.");
    }

    if (nameLen == 0)
        return Error(L"Invalid location format, the name is missing.");

    pvars[0] = pPort;
    ATLTRACE("  port = %ws\n", pvars[0].bstrVal);

    error_msg = CallDispatch(subObjectIDispatch, L"setPort", pvars,
                   1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    pvars[0].AttachString(SysAllocStringLen(newVal, nameLen));
    ATLTRACE("  name = %ws\n", pvars[0].bstrVal);

    error_msg = CallDispatch(subObjectIDispatch, L"setHost", pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);
    
	m_HostAndPort = newVal;  // save it for later
	PropertyChanged(19);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_UserMode(BSTR * pVal)
{
	SmartVariant varResult;

    ATLTRACE("CG2UiGateway::get_UserMode()\n");

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getUserMode",
                        NULL, 0, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

    *pVal = varResult.DetachString();
	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_UserMode(BSTR newVal)
{
	SmartVariant pvars[1];

	HRESULT hresult = NewUpperCaseBSTR(newVal, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setUserMode",
                        pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2UiGateway::GetNamedWorkspaces(VARIANT *pVal)
{
	SmartVariant varResult;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getNamedWorkspaces", NULL, 0,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

	return SequenceToVariant(varResult.pdispVal, pVal, 0, true);
}

STDMETHODIMP CG2UiGateway::get_G2SoftwareVersion(BSTR * pVal)
{
	SmartVariant varResult;

    ATLTRACE("CG2UiGateway::get_G2SoftwareVersion()\n");

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"g2GetSoftwareVersion", NULL,
                        0, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

    *pVal = varResult.DetachString();
	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_CallTimeout(long *pVal)
{
    ATLTRACE("CG2UiGateway::get_CallTimeout()\n");
    *pVal = m_call_timeout;
	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_CallTimeout(long newVal)
{
    m_call_timeout = newVal;
	PropertyChanged(24);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_GatewayId(BSTR * pVal)
{
	BSTR ret;

    ATLTRACE("CG2UiGateway::get_GatewayId()\n");
	ret = SysAllocString((BSTR) m_GatewayId);
	*pVal = ret;
	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_GatewayId(BSTR newVal)
{
	// unsubscribe the old value, if any

	GatewayList.unsubscribe((BSTR) m_GatewayId, this);
	m_GatewayId = newVal;
	GatewayList.subscribe((BSTR) m_GatewayId, this);
	PropertyChanged(27);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_UserName(BSTR * pVal)
{
	SmartVariant varResult;

    ATLTRACE("CG2UiGateway::get_UserName()\n");
    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getUserName",
                        NULL, 0, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

    *pVal = varResult.DetachString();
	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_UserName(BSTR newVal)
{
	SmartVariant pvars[1];

	HRESULT hresult = NewUpperCaseBSTR(newVal, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setUserName", pvars, 1,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(28);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::SetUserPassword(BSTR Password)
{
	SmartVariant pvars[1];

	HRESULT hresult = NewUpperCaseBSTR(Password, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"setUserPassword", pvars,
                        1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2UiGateway::get_G2InterfaceName(BSTR * pVal)
{
	SmartVariant varResult;

    ATLTRACE("CG2UiGateway::get_G2InterfaceName()\n");

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"getGsiInterfaceName",
                        NULL, 0, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

    *pVal = varResult.DetachString();
	return S_OK;
}

STDMETHODIMP CG2UiGateway::put_G2InterfaceName(BSTR newVal)
{
    BSTR error_msg = setG2InterfaceName(newVal);
    if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(30);
	return S_OK;
}

STDMETHODIMP CG2UiGateway::AddWorkspaceShowingListener(IG2WorkspacePanel2 * WorkspacePanel)
{
	SmartVariant pvars[1];

    ATLTRACE("CG2UiGateway::AddWorkspaceShowingListener()\n");

	SUBOBJECT_AS_VARIANT(WorkspacePanel, &pvars[0]);

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"addWorkspaceShowingListener", pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2UiGateway::RemoveWorkspaceShowingListener(IG2WorkspacePanel2 * WorkspacePanel)
{
	SmartVariant pvars[1];

    ATLTRACE("CG2UiGateway::RemoveWorkspaceShowingListener()\n");

	SUBOBJECT_AS_VARIANT(WorkspacePanel, &pvars[0]);

    BSTR error_msg = CallDispatch(subObjectIDispatch, L"removeWorkspaceShowingListener", pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2UiGateway::_subObject(IDispatch * * subObject)
{
    _SUBOBJECT_METHOD_IMPL(subObject, subObjectIDispatch);
}

STDMETHODIMP CG2UiGateway::IsConnected(VARIANT_BOOL * pConnected)
{
    ATLTRACE("CG2UiGateway::IsConnected()\n");

    // true is 1, but VARIANT_TRUE is short -1 (0xFFFF), returning a 1 makes the
    //   VB "Not" operator not work for true values, because it is a bitwise not
    //   on 0x0001 becomes 0X100 which is still true.
	if (m_connected)
    	*pConnected = VARIANT_TRUE;
    else
    	*pConnected = VARIANT_FALSE;

	return S_OK;
}
