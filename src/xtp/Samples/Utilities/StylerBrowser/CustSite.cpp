
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=


// 
// NOTE: 
// Some of the code in this file is MFC implementation specific.
// Changes in future versions of MFC implementation may require
// the code to be changed. Please check the readme of this
// sample for more information 
// 

#include "stdafx.h"
#include "StylerView.h"
#include "Styler.h"


static CLSID const Styler_CGID_DocHostCommandHandler
	= { 0xf38bc242, 0xb950, 0x11d1, { 0x89,0x18,0x00,0xc0,0x4f,0xc2,0xc8,0x36 } };

BEGIN_INTERFACE_MAP(CStylerView, CCmdTarget)
	INTERFACE_PART(CStylerView, IID_IDocHostUIHandler, DocHostUIHandler)
	INTERFACE_PART(CStylerView, IID_IOleClientSite, OleClientSite)
	INTERFACE_PART(CStylerView, IID_IOleCommandTarget, OleCommandTarget)
	INTERFACE_PART(CStylerView, IID_IDispatch, Dispatch)
END_INTERFACE_MAP()

	



#define DOCHOSTUIFLAG_ENABLE_FORMS_AUTOCOMPLETE 16384


#define IMPLEMENT_INTERFACE_PART(theClass, localClass)\
STDMETHODIMP_(ULONG) theClass::X##localClass::AddRef()\
{\
	METHOD_PROLOGUE(theClass, localClass)\
	return pThis->ExternalAddRef();\
}\
STDMETHODIMP_(ULONG) theClass::X##localClass::Release()\
{\
    METHOD_PROLOGUE(theClass, localClass)\
	return pThis->ExternalRelease();\
}\
STDMETHODIMP theClass::X##localClass::QueryInterface(REFIID riid, void **ppvObj)\
{\
	METHOD_PROLOGUE(theClass, localClass)\
    HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);\
	return hr;\
}


IMPLEMENT_INTERFACE_PART(CStylerView, DocHostUIHandler)
IMPLEMENT_INTERFACE_PART(CStylerView, OleClientSite)
IMPLEMENT_INTERFACE_PART(CStylerView, OleCommandTarget)
IMPLEMENT_INTERFACE_PART(CStylerView, Dispatch)

STDMETHODIMP  CStylerView::XDocHostUIHandler::GetHostInfo( DOCHOSTUIINFO* pInfo )
{
	pInfo->dwFlags = DOCHOSTUIFLAG_ENABLE_FORMS_AUTOCOMPLETE |DOCHOSTUIFLAG_FLAT_SCROLLBAR|0x40000;
    pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;
    return S_OK;
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::ShowUI(
				DWORD /*dwID*/, 
				IOleInPlaceActiveObject * /*pActiveObject*/,
				IOleCommandTarget * /*pCommandTarget*/,
				IOleInPlaceFrame * /*pFrame*/,
				IOleInPlaceUIWindow * /*pDoc*/)
{
    return S_OK;
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::HideUI(void)
{
    return S_OK;
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::UpdateUI(void)
{
	return S_OK;
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::EnableModeless(BOOL /*fEnable*/)
{
    return E_NOTIMPL;
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::OnDocWindowActivate(BOOL /*fActivate*/)
{
    return E_NOTIMPL;
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::OnFrameWindowActivate(BOOL /*fActivate*/)
{
    return E_NOTIMPL;
}

STDMETHODIMP CStylerView::XDocHostUIHandler::ResizeBorder(
				LPCRECT /*prcBorder*/, 
				IOleInPlaceUIWindow* /*pUIWindow*/,
				BOOL /*fRameWindow*/)
{
    return E_NOTIMPL;
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::ShowContextMenu(
				DWORD /*dwID*/, 
				POINT* /*pptPosition*/,
				IUnknown* /*pCommandTarget*/,
				IDispatch* /*pDispatchObjectHit*/)
{

    return E_NOTIMPL; // We've shown our own context menu. MSHTML.DLL will no longer try to show its own.
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::TranslateAccelerator(LPMSG /*lpMsg*/,
            /* [in] */ const GUID __RPC_FAR* /*pguidCmdGroup*/,
            /* [in] */ DWORD /*nCmdID*/)
{
    return S_FALSE;
}

STDMETHODIMP  CStylerView::XDocHostUIHandler::GetOptionKeyPath(BSTR* /*pbstrKey*/, DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CStylerView::XDocHostUIHandler::GetDropTarget( 
            /* [in] */ IDropTarget __RPC_FAR* /*pDropTarget*/,
            /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR* /*ppDropTarget*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP CStylerView::XDocHostUIHandler::GetExternal( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR* /*ppDispatch*/)
{
	return E_NOTIMPL;

}
        
STDMETHODIMP CStylerView::XDocHostUIHandler::TranslateUrl( 
            /* [in] */ DWORD /*dwTranslate*/,
            /* [in] */ OLECHAR __RPC_FAR* /*pchURLIn*/,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR* /*ppchURLOut*/)
{
    return E_NOTIMPL;
}
        
STDMETHODIMP CStylerView::XDocHostUIHandler::FilterDataObject( 
            /* [in] */ IDataObject __RPC_FAR* /*pDO*/,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR* /*ppDORet*/)
{
    return E_NOTIMPL;
}

STDMETHODIMP CStylerView::XOleCommandTarget::Exec(
	/* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
	/* [in] */ DWORD nCmdID,
	/* [in] */ DWORD /*nCmdexecopt*/,
	/* [unique][in] */ VARIANT __RPC_FAR *pvaIn,
	/* [unique][out][in] */ VARIANT __RPC_FAR *pvaOut
	)
{

	HRESULT hr = S_OK;
	BOOL bActiveX = FALSE;
	try
	{
		if (pguidCmdGroup && IsEqualGUID(*pguidCmdGroup, Styler_CGID_DocHostCommandHandler))
		{
			if( (nCmdID == 40 || nCmdID == 41) )// && pmf!=NULL && g_bSilent)//OLECMDID_SHOWSCRIPTERROR
			{
				if(nCmdID == 41)
				{
					IHTMLDocument2*             pDoc = NULL;
					IHTMLWindow2*               pWindow = NULL;
					IHTMLEventObj*              pEventObj = NULL;
					BSTR                        rgwszName = SysAllocString(L"messageText");
					DISPID                      rgDispID;
					VARIANT                     rgvaEventInfo;
					DISPPARAMS                  params;

					params.cArgs = 0;
					params.cNamedArgs = 0;

					// Get the document that is currently being viewed.
					hr = pvaIn->punkVal->QueryInterface(IID_IHTMLDocument2, (void **) &pDoc);				
					// Get document.parentWindow.
					hr = pDoc->get_parentWindow(&pWindow);
					pDoc->Release();
					// Get the window.event object.
					hr = pWindow->get_event(&pEventObj);
					// Get the error info from the window.event object.
					// Get the property's dispID.
					hr = pEventObj->GetIDsOfNames(IID_NULL, &rgwszName, 1, 
						LOCALE_SYSTEM_DEFAULT, &rgDispID);
					// Get the value of the property.
					hr = pEventObj->Invoke(rgDispID, IID_NULL,LOCALE_SYSTEM_DEFAULT,
						DISPATCH_PROPERTYGET, &params, &rgvaEventInfo,NULL, NULL);
					SysFreeString(rgwszName);
					pWindow->Release();
					pEventObj->Release();
					if(wcsstr(rgvaEventInfo.bstrVal, L" ActiveX ")!=NULL)
						bActiveX = TRUE;
					SysFreeString(rgvaEventInfo.bstrVal);
				}

				(*pvaOut).vt = VT_BOOL;
				// Continue running scripts on the page.
				(*pvaOut).boolVal = VARIANT_TRUE;

				CFrameWnd* pmf = (CFrameWnd*)AfxGetMainWnd();

				if(nCmdID == 40)
				{
					pmf->SetMessageText(_T("Script Error!"));
				}
				else
				{
					if(bActiveX)
					{
						pmf->SetMessageText(_T("ActiveX Denied!"));
					}
					else
					{
						(*pvaOut).boolVal = VARIANT_FALSE;
						return OLECMDERR_E_NOTSUPPORTED;
					}
				}
				return hr;
			}
		}
	}
	catch(...)
	{

	}

	return OLECMDERR_E_NOTSUPPORTED;
}

STDMETHODIMP CStylerView::XOleCommandTarget::QueryStatus(
	/* [unique][in] */ const GUID __RPC_FAR*,
	/* [in] */ ULONG,
	/* [out][in][size_is] */ OLECMD __RPC_FAR[],
	/* [unique][out][in] */ OLECMDTEXT __RPC_FAR*
	)
{
	METHOD_PROLOGUE(CStylerView, OleCommandTarget)
		return OLECMDERR_E_NOTSUPPORTED;
}



STDMETHODIMP CStylerView::XDispatch::GetTypeInfoCount(unsigned int*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CStylerView::XDispatch::GetTypeInfo(
	unsigned int, LCID, ITypeInfo**)
{
	return E_NOTIMPL;
}

STDMETHODIMP CStylerView::XDispatch::GetIDsOfNames(
	REFIID, LPOLESTR*, unsigned int, LCID, DISPID*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CStylerView::XDispatch::Invoke(
	DISPID dispid, REFIID, LCID, unsigned short /*wFlags*/,
	DISPPARAMS* /*pDispParams*/, VARIANT* pvarResult,
	EXCEPINFO*, unsigned int*)
{
    switch (dispid)
    {
	case DISPID_AMBIENT_DLCONTROL:
		pvarResult->lVal =  DLCTL_VIDEOS | DLCTL_BGSOUNDS;
		if (m_bShowImages) pvarResult->lVal |= DLCTL_DLIMAGES;
		
		pvarResult->vt = VT_I4;
		
		break;
		
	default:
		return DISP_E_MEMBERNOTFOUND;
    }
	
    return S_OK;
}

