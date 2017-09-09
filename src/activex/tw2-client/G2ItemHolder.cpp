// G2ItemHolder.cpp : Implementation of CG2ItemHolder
#include "stdafx.h"
#include "AXClient.h"
#include "G2ItemHolder.h"
#include "G2UiGateway.h"
#include "convert.h"
#include "util.h"

#define SUB_ITEM_CHECK \
    { \
        if (m_item_deleted) \
            return Error("The item in the holder has been deleted."); \
        else if (!subItem) \
            return Error("The holder is empty, set the Item."); \
    }

/////////////////////////////////////////////////////////////////////////////
// CG2ItemHolder

CG2ItemHolder::CG2ItemHolder()
{
    // Set up all of the default values
    dwCookie = 0;
    m_call_timeout = 30;
    mItemClass = L"ITEM";
    m_Loading = false;
    m_item_deleted = false;
    m_ItemProxyEventsIID = IID_NULL;
}

CG2ItemHolder::~CG2ItemHolder()
{
    GatewayList.unsubscribe((BSTR) mItemGateway, this);
    
    // Clean up all of the cached pointers
    if (dwCookie != 0)
        subIConnectionPoint->Unadvise(dwCookie);

    ReleaseItem();

    ATLTRACE("Item Holder Destructed\n\n\n");
}

HRESULT CG2ItemHolder::FinalConstruct()
{
    HRESULT hresult;
    CLSID CLSID_Temp;
    SmartVariant varResult;
    
    ATLTRACE("\n\nNew Item Holder\n");
    
    hresult = CreateScriptUtilitiesInstance(&m_scriptUtilities);
    if (FAILED(hresult))
        return hresult;
    
    if (FAILED(CLSIDFromProgID(L"ItemProxy.Bean", &CLSID_Temp)))
    {
        ATLTRACE(" Can't get CLSID for Bean.");
        return E_CANT_GET_BEAN_CLSID;
    }
    
    // get a pointer to a bean, this does not create a java object yet
    //   the java object gets created at stream init() or load()
    if (FAILED(CoCreateInstance(CLSID_Temp, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch,
            (void **) &subItemProxyBeanIDispatch)))
    {
        ATLTRACE(" Can't create the bean.");
        return E_CANT_CREATE_BEAN_OBJ;
    }
    
    // bean methods do not throw exceptions correctly, so use the real object
    if (FAILED(InvokeMethod(subItemProxyBeanIDispatch, L"getThis", NULL, 0,
        &varResult)))
    {
        ATLTRACE(" Can't create the java object.");
        return E_CANT_CREATE_JAVA_OBJ;
    }
    
    subItemProxyObjectIDispatch.Attach(varResult.DetachObject());

    // Now querry each needed interface
    subItemProxyBeanIDispatch->QueryInterface(IID_IViewObject2, (void **) &subIViewObject2);
    subItemProxyBeanIDispatch->QueryInterface(IID_IOleInPlaceObject, (void **) &subIOleInPlaceObject);
    subItemProxyBeanIDispatch->QueryInterface(IID_IOleInPlaceActiveObject, (void **) &subIOleInPlaceActiveObject);
    subItemProxyBeanIDispatch->QueryInterface(IID_IOleControl, (void **) &subIOleControl);
    subItemProxyBeanIDispatch->QueryInterface(IID_IOleObject, (void **) &subIOleObject);
    subItemProxyBeanIDispatch->QueryInterface(IID_IPersistStreamInit, (void **) &subIPersistStreamInit);
    
    // We can not longer get the connection point by interface ID since this changes too often
    SmartComPtr<IConnectionPointContainer> pIConnectionPointContainer;
    if (FAILED(subItemProxyBeanIDispatch->QueryInterface(IID_IConnectionPointContainer,
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
    if (FAILED(subItemProxyBeanIDispatch->GetTypeInfo(0, 0, &pInfo)))
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
    
    if (FAILED(subIConnectionPoint->GetConnectionInterface(&m_ItemProxyEventsIID)))
    {
        ATLTRACE(" Can't get the connection point interface ID");
        return E_CANT_GET_CP_ID;
    }
    
    if (FAILED(pLib->GetTypeInfoOfGuid(m_ItemProxyEventsIID, &eventInfo)))
    {
        ATLTRACE(" Can't get the event info.");
        return E_CANT_GET_EVENTINFO;
    }
    
    return S_OK;
}

void CG2ItemHolder::update_status(bool status)
{
    ATLTRACE("Item Holder got Update status\n");
	if (status)
        loadItemAddress();
}

HRESULT CG2ItemHolder::SinkInvoke(DISPID dispIdMember, REFIID riid, LCID lcid,
    WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult,
    EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr)
{
    SmartComPtr<IDispatch> pSelf;
	CComBSTR EventName;
	unsigned int num;

    ATLTRACE("Item Holder got sink invoke on outgoing interface:%d\n",
        dispIdMember);

    // By referencing ourself, the VB event code can unload this object.
    // and the we will deleted when we exit this method.
    pSelf = (IDispatch*)this;

	// Find the name
    HRESULT hr = eventInfo->GetNames(dispIdMember, &EventName, 1, &num);
	if (FAILED(hr))
        return hr;

	ATLTRACE("Name of event: %ws\n", EventName);

	if (wcscmp(EventName, L"itemDeleted") == 0)
    {
        m_item_deleted = true;
        CProxy_G2ItemEvents<CG2ItemHolder>::Fire_ItemDeleted();
        CProxy_G2ItemEvents2<CG2ItemHolder>::Fire_ItemDeleted();
    }
	if (wcscmp(EventName, L"objectUpdated") == 0)
    {
        SmartVariant pvars[2];
        SmartVariant varResultValue;
        SmartVariant varResultName;
        SmartVariant varResultNameArray;
        SmartComPtr<IG2Structure> pStruct;
        SAFEARRAY *listOfNames;
        long last_struct;
        long i;

        // arg check, 1 java object
        if (pDispParams->cArgs != 1 ||
            pDispParams->rgvarg[0].vt != VT_DISPATCH)
        {
            return S_OK;
        }

        // Pass in null ref to get a structure of attributes of which one or
        //   all may have been updated.
        //     structure of attributes =
        //       ObjectUpdateEvent->getUpdatedValue(null, null)

        pvars[1].SetToNull();
        pvars[0].SetToNull();

 	    if (FAILED(InvokeMethod(pDispParams->rgvarg[0].pdispVal,
            L"getUpdatedValue", pvars, 2, &varResultValue)))
        {
            return S_OK;
        }

        if (!varResultValue.IsObject())
            return S_OK;

        if (FAILED(JavaToStructure(varResultValue.pdispVal, &pStruct)))
            return S_OK;

        // get the name of the attribute that was updated:
        //         nameString = ObjectUpdateEvent->getAttributeName()
        // if (nameString == NULL) then all attributes were updated.
        //    then only send that attribute.
	    if (FAILED(InvokeMethod(pDispParams->rgvarg[0].pdispVal,
            L"getAttributeName", NULL, 0, &varResultName)))
        {
            return S_OK;
        }

        if (varResultName.IsString() && varResultName.bstrVal != NULL)
        {
            CComBSTR p_name;

            // Just one attribute was updated
            p_name.Attach(varResultName.DetachString());
    	    ATLTRACE("The updated attribute is : %ws\n", p_name);

            if (SUCCEEDED(pStruct->get_Member(p_name, &varResultName)))
            {
                CProxy_G2ItemEvents<CG2ItemHolder>::
                    Fire_SubscribedAttributeChanged(p_name, &varResultName);
                CProxy_G2ItemEvents2<CG2ItemHolder>::
                    Fire_SubscribedAttributeChanged(p_name, &varResultName);
            }

            return S_OK;
        }

   	    ATLTRACE("All of the attributes were updated.\n");

        // get an array of attribute names
        if (FAILED(pStruct->get_MemberNames(&varResultNameArray)))
            return S_OK;

        // the array will be deleted with the variant
        listOfNames = varResultNameArray.parray;

        if (FAILED(SafeArrayGetUBound(listOfNames, 1, &last_struct)))
            return S_OK;

        for (i = 0; i <= last_struct; i++)
        {
            SmartVariant varResultMember;
            CComBSTR p_name;

            if (FAILED(SafeArrayGetElement(listOfNames, &i,
                (void*)(BSTR*)&p_name)))
            {
                break;
            }

            if (FAILED(pStruct->get_Member(p_name, &varResultMember)))
                break;

            CProxy_G2ItemEvents<CG2ItemHolder>::
                Fire_SubscribedAttributeChanged(p_name, &varResultMember);
            CProxy_G2ItemEvents2<CG2ItemHolder>::
                Fire_SubscribedAttributeChanged(p_name, &varResultMember);
        }

	}

    return S_OK;
}

HRESULT CG2ItemHolder::AdviseCalled()
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
    temp->m_sinkIID = m_ItemProxyEventsIID;

    // this does add a reference
    sinkObject = temp;
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
    
HRESULT CG2ItemHolder::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	DrawText(di.hdcDraw, _T("Gensym G2 ItemHolder Holder"), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	return S_OK;
}

//
// Fetch a named object from a connector.  This is only called after a connection is made.
//
void CG2ItemHolder::loadItemAddress(void)
{
    GatewayEntry *gEntry;
    CG2UiGateway *connector;
	SmartComPtr<IG2Item> item;
    HRESULT hr;

	USES_CONVERSION;

    if (!mItemGateway) return;

	// now we need to find the gateway object.
	gEntry = (GatewayEntry *) GatewayList.FindObj((BSTR) mItemGateway);
	if (!gEntry)
        return;

	if (!gEntry->obj)
        return;

	// ok, we now have a pointer to the connector object.
	connector = (CG2UiGateway *) gEntry->obj;

	// We need to get the named object from the 
	hr = connector->GetNamedItem((BSTR) mItemName, (BSTR) mItemClass, &item);
	if (FAILED(hr) || item == NULL)
        return;
	
	// stick the new item in the workspace
	put_Item(item);
}

BSTR CG2ItemHolder::setAutoDownload(VARIANT_BOOL newVal)
{
	SmartVariant pvars[2];

	pvars[1] = subItemProxyObjectIDispatch;

	pvars[0] = (long)newVal;

    return CallDispatch(m_scriptUtilities.p, L"setAutoDownloadForVB", pvars, 2,
        NULL);
}

BSTR CG2ItemHolder::setItemInProxy()
{
    SmartVariant pvars[1];
    
    if (!subItem)
        pvars[0].SetToNull();
    else
        SUBOBJECT_AS_VARIANT(subItem, &pvars[0]);

    BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"setProxy", pvars,
                    1, NULL);
    // if there is an object in the variant, this will decrement the ref count
    //  that _subObject incremented.
    return error_msg;
}

void CG2ItemHolder::PropertyChanged(DISPID dispid)
{
    if (!m_Loading)
	    SetDirty(true);

	FireOnChanged(dispid);
}

STDMETHODIMP CG2ItemHolder::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2ItemHolder,
		&IID_IG2ItemHolder2,
	};

    for (int i = 0; i < sizeof (arr) / sizeof (arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}

    return S_FALSE;
}

// IViewObjectEx
STDMETHODIMP CG2ItemHolder::GetViewStatus(DWORD* pdwStatus)
{
    ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
    *pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
    return S_OK;
}

// IOleControl
STDMETHODIMP CG2ItemHolder::FreezeEvents(BOOL bFreeze)
{
    ATLTRACE("Forwarded FreezeEvents\n");
    return subIOleControl->FreezeEvents(bFreeze);
}

// IPersistStreamInit
STDMETHODIMP CG2ItemHolder::InitNew(void)
{
	SIZEL sz;
    
    ATLTRACE("Called IPersistStreamInit::InitNew\n");
    
    // We do not save the beans so we do not have to
    // forward and InitNew. Also calling InitNew on the bean
    // will replace the java object in the COM object under us
    // which is bad.

    if (FAILED(IPersistStreamInitImpl<CG2ItemHolder>::InitNew()))
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

STDMETHODIMP CG2ItemHolder::Load(LPSTREAM pStm)
{
	SIZEL sz;
	BOOL userMode;
    
    ATLTRACE("Called IPersistStreamInit::Load\n");
    
    // We do not save the beans so we do not have to
    // forward Load.

    // now load the properties of our control but do set the dirty bit
    m_Loading = true;
    if (FAILED(IPersistStreamInitImpl<CG2ItemHolder>::Load(pStm)))
    {
        ATLTRACE(" Can't load from the stream.");
        return E_CANT_LOAD_FROM_STREAM;
    }
    
    m_Loading = false;

    // Set the true size
	IOleObjectImpl<CG2ItemHolder>::GetExtent(DVASPECT_CONTENT, &sz);
	subIOleObject->SetExtent(DVASPECT_CONTENT, &sz);

    // check the user mod, don't load in development mode
    if (SUCCEEDED(GetAmbientUserMode(userMode)) && userMode)
    {
	    // now load it if it is ready
	    loadItemAddress();
	}

    return S_OK;
}

// IOleObject
STDMETHODIMP CG2ItemHolder::SetExtent(DWORD aspect, SIZEL *sizel)
{
    ATLTRACE("Called and Forwarded:SetExtent\n");
    IOleObjectImpl<CG2ItemHolder>::SetExtent(aspect, sizel);
    return subIOleObject->SetExtent(aspect, sizel);
}

STDMETHODIMP CG2ItemHolder::DoVerb(LONG iVerb, LPMSG lpmsg,
    IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent,
    LPCRECT lprcPosRect)
{
    ATLTRACE("Forwarded DoVerb\n");
    return subIOleObject->DoVerb(iVerb, lpmsg, pActiveSite, lindex, hwndParent,
        lprcPosRect);
}

STDMETHODIMP CG2ItemHolder::SetClientSite(IOleClientSite *pClientSite)
{
    ATLTRACE("Called and Forwarded SetClientSite\n");
    IOleObjectImpl<CG2ItemHolder>::SetClientSite(pClientSite);
    return subIOleObject->SetClientSite(pClientSite);
}

STDMETHODIMP CG2ItemHolder::Close(DWORD dwSaveOption)
{
    ATLTRACE("Forwarded Close\n");
    return subIOleObject->Close(dwSaveOption);
}

// IOleInPlaceObject
STDMETHODIMP CG2ItemHolder::SetObjectRects(LPCRECT rec1, LPCRECT rec2)
{
    ATLTRACE("Forwarded:SetObjectRects\n");
    return subIOleInPlaceObject->SetObjectRects(rec1, rec2);
}

STDMETHODIMP CG2ItemHolder::GetWindow(HWND *phwnd)
{
    ATLTRACE("Forwarded: GetWindow()\n");
    return subIOleInPlaceObject->GetWindow(phwnd);
}

STDMETHODIMP CG2ItemHolder::InPlaceDeactivate(void)
{
    ATLTRACE("Forwarded InPlaceDeactivate\n");
    return subIOleInPlaceObject->InPlaceDeactivate();
}

//IViewObject
// Since the control has its own window, this is never called!
STDMETHODIMP CG2ItemHolder::Draw(DWORD dwDrawAspect, LONG lindex,
    void *pvAspect, DVTARGETDEVICE *ptd, HDC hicTargetDev, HDC hdcDraw,
    LPCRECTL prcBounds, LPCRECTL prcWBounds,
    BOOL (__stdcall * pfnContinue)(DWORD dwContinue), DWORD dwContinue)
{
    ATLTRACE("Forwarded Draw\n");
    return subIViewObject2->Draw(dwDrawAspect, lindex, pvAspect, ptd,
        hicTargetDev, hdcDraw, prcBounds, prcWBounds, pfnContinue,
        dwContinue);
}

STDMETHODIMP CG2ItemHolder::SetAdvise(DWORD dwAspect, DWORD advf,
    IAdviseSink *pAdvise)
{
    ATLTRACE("Forwarded:SetAdvise");
    return subIViewObject2->SetAdvise(dwAspect, advf, pAdvise);
}

STDMETHODIMP CG2ItemHolder::get_ObjectAddress(BSTR * pVal)
{
	*pVal = SysAllocString((BSTR) mItemAddress);
	return S_OK;
}

STDMETHODIMP CG2ItemHolder::put_ObjectAddress(BSTR newVal)
{
	USES_CONVERSION;
	char address[300];

	mItemAddress.Empty();
	mItemName.Empty();
	GatewayList.unsubscribe((BSTR) mItemGateway, this);
	mItemGateway.Empty();

	if (newVal != NULL) {
		mItemAddress = newVal;
		strcpy(address, W2A(newVal));

		char name[300];
		char gateway[300];
		for (char *ptr = address; *ptr; ptr++) {
			if (*ptr == '@') break;
		}

		if (*ptr) {
			*ptr = 0; *ptr++;
			strcpy(name, address);
			strcpy(gateway, ptr);

			mItemName = A2W(name);
			mItemGateway = A2W(gateway);
			GatewayList.subscribe((BSTR) mItemGateway, this);
		} 
	}

    PropertyChanged(1);
	return S_OK;
}


STDMETHODIMP CG2ItemHolder::get_Attribute(BSTR AttributeName, VARIANT * pVal)
{
    SmartVariant pvars[1];
    SmartVariant varResult;

    ATLTRACE("Getting attribute %ws\n\n", AttributeName);

    SUB_ITEM_CHECK;

    HRESULT hresult = NewUpperCaseBSTR(AttributeName, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

	BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch,
                        L"getPropertyValue", pvars, 1,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    JavaVariantToComVariant(varResult, pVal);
	return S_OK;
}

STDMETHODIMP CG2ItemHolder::put_Attribute(BSTR AttributeName, VARIANT newVal)
{
    int num_vars = 3;
	SmartVariant pvars[3];
    OLECHAR *method_name;
    BSTR error_msg;
    IDispatch* pObject = m_scriptUtilities.p;

    ATLTRACE("Setting attribute %ws\n\n", AttributeName);

    SUB_ITEM_CHECK;

    pvars[2] = subItemProxyObjectIDispatch;

    // convert input
    HRESULT hresult = NewUpperCaseBSTR(AttributeName, &pvars[1]);
    if (FAILED(hresult))
        return hresult;

    hresult = ComVariantToJavaVariant(newVal, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

    switch (pvars[0].vt)
    {
    case VT_I2:
        pvars[0] = (long)pvars[0].iVal;
    case VT_I4:
        method_name = L"setIntPropertyValue";
        break;

    case VT_BSTR:
        if (pvars[0].bstrVal != NULL && pvars[0].bstrVal[0] == 0)
        {
            // this method takes only 2 parameters
            method_name = L"setEmptyStringPropertyValue";
            pvars[0] = pvars[1];
            pvars[1] = pvars[2];
            num_vars = 2;
            break;
        }

        method_name = L"setStringPropertyValue";
        break;

    case VT_R4:
        pvars[0] = (double)pvars[0].fltVal;

    case VT_R8:
        method_name = L"setDoublePropertyValue";
        break;

    case VT_BOOL:
        // 9/3/98 there is a bug using booleans with the Bean bridge
        //method_name = L"setBooleanPropertyValue";

        pvars[0] = (long)pvars[0].boolVal;
        method_name = L"setPseudoBooleanPropertyValue";
        break;

    default:
        method_name = L"setPropertyValue";
        pObject = subItemProxyObjectIDispatch;
        num_vars = 2;
    }

    // void Item.setPropertyValue(Symbol, Object)
    error_msg = CallDispatch(pObject, method_name, pvars, num_vars,
                   NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2ItemHolder::get_AttributeNames(VARIANT *ListOfNames)
{
    SUB_ITEM_CHECK;

    return subItem->get_AttributeNames(ListOfNames);
}

STDMETHODIMP CG2ItemHolder::get_ObjectClass(BSTR * pVal)
{
	*pVal = SysAllocString((BSTR) mItemClass);
	return S_OK;
}

STDMETHODIMP CG2ItemHolder::put_ObjectClass(BSTR newVal)
{
	mItemClass = newVal;
	PropertyChanged(6);
	return S_OK;
}

STDMETHODIMP CG2ItemHolder::get_ElementCount(long * pVal)
{
    SUB_ITEM_CHECK;

   return subItem->get_ElementCount(pVal);
}

STDMETHODIMP CG2ItemHolder::get_ElementType(G2ElementType * pVal)
{
    SUB_ITEM_CHECK;

    return subItem->get_ElementType(pVal);
}

STDMETHODIMP CG2ItemHolder::get_Element(long Index, VARIANT * pVal)
{
    SUB_ITEM_CHECK;

	return subItem->get_Element(Index, pVal);
}

STDMETHODIMP CG2ItemHolder::put_Element(long Index, VARIANT newVal)
{
    SUB_ITEM_CHECK;

	return subItem->put_Element(Index, newVal);
}

STDMETHODIMP CG2ItemHolder::get_Elements(VARIANT * pVal)
{
    SUB_ITEM_CHECK;

    return subItem->get_Elements(pVal);
}

STDMETHODIMP CG2ItemHolder::put_Elements(VARIANT newVal)
{
    SUB_ITEM_CHECK;

	return subItem->put_Elements(newVal);
}

STDMETHODIMP CG2ItemHolder::SubscribeToAttribute(BSTR AttributeName)
{
	SmartVariant pvars[1];
	SmartVariant varResult;

    // get the symbol vector object from the proxy and invoke addElement(BSTR)
    // SymbolVector attributeNames = ItemProxy->getAttributes()
	BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"getAttributes",
                        NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsObject())
        return E_FAIL;

    error_msg = BSTRToJava(AttributeName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    // attributeNames->addSymbolElement(AttributeName)
	error_msg = CallDispatch(varResult.pdispVal, L"addSymbolElement",
                        pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(27);
	return S_OK;
}

STDMETHODIMP CG2ItemHolder::UnsubscribeToAttribute(BSTR AttributeName)
{
	SmartVariant pvars[1];
	SmartVariant varResult;

    // get the symbol vector object from the proxy and invoke addElement(BSTR)
    // SymbolVector attributeNames = ItemProxy->getAttributes()
	BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"getAttributes",
                        NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsObject())
        return E_FAIL;

    error_msg = BSTRToJava(AttributeName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    // attributeNames->removeSymbolElement(AttributeName)
	error_msg = CallDispatch(varResult.pdispVal, L"removeSymbolElement",
                        pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(27);
	return S_OK;
}

STDMETHODIMP CG2ItemHolder::CallMethod(BSTR MethodName, SAFEARRAY **InputArguments, VARIANT * ReturnArguments)
{
    SUB_ITEM_CHECK;

    subItem->put_CallTimeout(m_call_timeout);
	return subItem->CallMethod(MethodName, InputArguments, ReturnArguments);
}

STDMETHODIMP CG2ItemHolder::StartMethod(BSTR MethodName, SAFEARRAY **Arguments)
{
    SUB_ITEM_CHECK;

    subItem->put_CallTimeout(m_call_timeout);
	return subItem->StartMethod(MethodName, Arguments);
}


// This method creates a symbol object, populates the symbol state with the 
// passed value and returns it

STDMETHODIMP CG2ItemHolder::Symbol(BSTR SymbolName, IG2Symbol ** val)
{
    return CreateSymbol(SymbolName, val);
}

// Create a structure object

STDMETHODIMP CG2ItemHolder::Structure(SAFEARRAY **NameValuePairs, IG2Structure ** Structure)
{
    return CreateStructure(CLSID_G2ItemHolder, *NameValuePairs, Structure);
}

STDMETHODIMP CG2ItemHolder::get_CallTimeout(long *pVal)
{
	return m_call_timeout;
}

STDMETHODIMP CG2ItemHolder::put_CallTimeout(long newVal)
{
    m_call_timeout = newVal;
	PropertyChanged(22);
	return S_OK;
}

STDMETHODIMP CG2ItemHolder::get_Item(IG2Item **Item)
{
    SUB_ITEM_CHECK;

    subItem.CopyTo(Item);
    return S_OK;
}

STDMETHODIMP CG2ItemHolder::put_Item(IG2Item *Item)
{
    subItem = Item;

    m_item_deleted = false;

    BSTR error_msg = setItemInProxy();
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2ItemHolder::get_AutoDownload(VARIANT_BOOL *pVal)
{
	SmartVariant varResult;

    BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"getAutoDownload", NULL, 0,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*pVal = varResult.boolVal;
    return S_OK;
}

STDMETHODIMP CG2ItemHolder::put_AutoDownload(VARIANT_BOOL newVal)
{
    BSTR error_msg = setAutoDownload(newVal);
    if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(24);
    return S_OK;
}

STDMETHODIMP CG2ItemHolder::get_AutoUpload(VARIANT_BOOL *pVal)
{
	SmartVariant varResult;

    BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"getAutoUpload", NULL, 0,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*pVal = varResult.boolVal;
    return S_OK;
}

STDMETHODIMP CG2ItemHolder::put_AutoUpload(VARIANT_BOOL newVal)
{
	SmartVariant pvars[2];

	pvars[1] = subItemProxyObjectIDispatch;
	pvars[0] = (long)newVal;

    BSTR error_msg = CallDispatch(m_scriptUtilities.p, L"setAutoUploadForVB", pvars,
                        2, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	PropertyChanged(25);
    return S_OK;
}

STDMETHODIMP CG2ItemHolder::put_SubscribedAttributes(BSTR ListOfNames)
{
    SmartVariant varResult;
    BSTR error_msg;
    SmartComPtr<IDispatch> SymbolVector;
    CComBSTR tempList;
    wchar_t *token;

    // symbolVector attributeNames = ItemProxy->getAttributeNames()
	  error_msg = CallDispatch(subItemProxyObjectIDispatch, L"getAttributes",
                        NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsObject())
        return E_FAIL;

    SymbolVector.Attach(varResult.DetachObject());
	  error_msg = CallDispatch(SymbolVector, L"removeAllElements",
                        NULL, 0, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    if (ListOfNames == NULL)
    {
        token = NULL;
    }
    else
    {
        /* wcstok overwrites the tokens it finds with a zero, so do not use
           the string that was passed in, use a copy. By using a CComBSTR for
           the copy, it will automatically be freed when we it leaves the scope
           of this method. */
        tempList = ListOfNames;
        token = wcstok(tempList, L",");
    }

    while (token != NULL)
    {
    	SmartVariant pvars[1];

        ATLTRACE("token = %ws\n", token);
        if (FAILED(OLECHARToJavaSymbol(token, &pvars[0])))
            return E_OUTOFMEMORY;

        // SymbolVector->addElement(AttributeName)
	      error_msg = CallDispatch(SymbolVector, L"addSymbolElement",
                      pvars, 1, NULL);
        if (error_msg != NULL)
            return Error(error_msg);

        token = wcstok(NULL, L",");
    }

	  PropertyChanged(27);
    return S_OK;
}

STDMETHODIMP CG2ItemHolder::get_SubscribedAttributes(BSTR *ListOfNames)
{
    SmartVariant varResult;
    SmartComPtr<IDispatch> SymbolVector;
    long i, size;
    SmartVariant pvars[1];
	CComBSTR pSubscribedAttributes;

    // symbolVector attributeNames = ItemProxy->getAttributeNames()
	BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"getAttributes",
                        NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsObject())
        return E_FAIL;

    SymbolVector.Attach(varResult.DetachObject());

    // attributeNames->size()
	error_msg = CallDispatch(SymbolVector, L"size", NULL, 0, &varResult);
    if (!varResult.IsInteger())
        return E_FAIL;

    // put all attribute names into one big comma delimited string
    size = varResult.lVal;
    for (i = 0; i < size; i++)
    {
        SmartVariant varResultElement;
        CComBSTR name;

        // AttributeNameSymbol = attributeNames->elementAt()
        pvars[0] = i;
	    error_msg = CallDispatch(SymbolVector, L"elementAt",
                        pvars, 1, &varResultElement);
        if (error_msg != NULL)
            break;

        if (!varResultElement.IsObject() ||
            FAILED(JavaToBSTR(varResultElement.pdispVal, &name)))
        {
            error_msg = L"Unexpected Error";
            break;
        }

        if (i != 0)
            pSubscribedAttributes += L",";

        ATLTRACE("element = %ws\n", name);
        pSubscribedAttributes += name;
    }

    if (error_msg != NULL)
        return Error(error_msg);

    ATLTRACE("list = %ws\n", (BSTR)pSubscribedAttributes);

    *ListOfNames = pSubscribedAttributes.Detach();
	return S_OK;
}


STDMETHODIMP CG2ItemHolder::IsInstanceOfClass(BSTR ClassName, VARIANT_BOOL * Result)
{
	return subItem->IsInstanceOfClass(ClassName, Result);
}

STDMETHODIMP CG2ItemHolder::Download()
{
    BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"download", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2ItemHolder::Upload()
{
    BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"upload", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}
 
STDMETHODIMP CG2ItemHolder::ReleaseItem()
{
    ATLTRACE("CG2ItemHolder::ReleaseItem()\n");

    m_item_deleted = false;

    if (!subItem)
        return S_OK;

    subItem = NULL;

    BSTR error_msg = setItemInProxy();
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2ItemHolder::IsEmpty(VARIANT_BOOL * pVal)
{
	SmartVariant varResult;

    ATLTRACE("CG2ItemHolder::IsEmpty()\n");

	BSTR error_msg = CallDispatch(subItemProxyObjectIDispatch, L"getProxy", NULL,
                        0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (varResult.IsObject() && varResult.pdispVal != NULL)
    {
        *pVal = VARIANT_FALSE;
    }
    else
    {
        // make our state match.
        subItem = NULL;
        *pVal = VARIANT_TRUE;
    }

    return S_OK;
}

STDMETHODIMP CG2ItemHolder::_subObject(IDispatch * * subObject)
{
    _SUBOBJECT_METHOD_IMPL(subObject, subItemProxyObjectIDispatch);
}
