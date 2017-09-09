#include "StdAfx.h"
#include "styler.h"
#include "explorerbar.h"
 
#include "StylerDoc.h"
#include "StylerView.h"



CExplorerBar::CExplorerBar(void)
{
	m_pSearch = 0;
}

CExplorerBar::~CExplorerBar(void)
{
	delete m_pSearch;
}


int CExplorerBar::OnViewSearch()
{
	if (!m_pSearch)
	{
		try
		{	
			m_pSearch = new CWebBrowserCtrl;
			if (!m_pSearch->Create(NULL, WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE,	CRect(0,0,0,0), this, AFX_IDW_PANE_FIRST))
				return -1;
			
			AfxEnableControlContainer();
			
			m_pSearch->ModifyStyle(0, WS_BORDER);
			
			LPDISPATCH lpDisp = m_pSearch->get_Application();
			if (lpDisp)
			{
				CComPtr<IOleObject> spOleObj;
				
				lpDisp->QueryInterface(IID_IOleObject, (void**)&spOleObj);
				if (spOleObj)
					spOleObj->SetClientSite(&m_xOleClientSite );
				lpDisp->Release();		
			}		
			
			CString strPath = GetModuleDir() + _T("search.htm");
			m_pSearch->Navigate2(strPath);
		}
		catch (...) 
		{
		}
	}

	return 0;
}


BEGIN_EVENTSINK_MAP(CExplorerBar, CWnd)
	ON_EVENT(CExplorerBar, AFX_IDW_PANE_FIRST, 251 /* NewWindow2 */, OnNewWindow2, VTS_PDISPATCH VTS_PBOOL)
END_EVENTSINK_MAP()


void CExplorerBar::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* /*bCancel*/)
{
   CWinApp* pApp = AfxGetApp();

   // Get the correct document template.
   POSITION pos = pApp->GetFirstDocTemplatePosition();
   CDocTemplate* pDocTemplate = pApp->GetNextDocTemplate( pos );

   
   CStylerDoc* pDoc = (CStylerDoc*)pDocTemplate->CreateNewDocument();
   pDoc->SetUrl(_T("Search Result"));

   // Create a new frame.
   CFrameWnd* pFrame = pDocTemplate->CreateNewFrame(pDoc, (CFrameWnd*)AfxGetMainWnd() );

   // Activate the frame.
   pDocTemplate->InitialUpdateFrame( pFrame, NULL );
   CStylerView* pView = (CStylerView*)pFrame->GetActiveView();

   // Pass pointer of WebBrowser object.
   pView->SetRegisterAsBrowser( TRUE );
   *ppDisp = pView->GetApplication();   
}



BOOL CExplorerBar::PreTranslateMessage(MSG* pMsg)
{
	if (CWnd::PreTranslateMessage(pMsg))
		return TRUE;

	if (pMsg->message == WM_KEYDOWN && m_pSearch)
	{		
		LPDISPATCH lpDisp = m_pSearch->get_Application();
		if (lpDisp)
		{
			CComQIPtr<IOleInPlaceActiveObject> spActiveObj(lpDisp);
			lpDisp->Release();

			if (spActiveObj && spActiveObj->TranslateAccelerator(pMsg) == S_OK)
				return TRUE;
		}

	}

	return FALSE;

}



BEGIN_INTERFACE_MAP(CExplorerBar, CCmdTarget)
	INTERFACE_PART(CExplorerBar, IID_IDocHostUIHandler, DocHostUIHandler)
	INTERFACE_PART(CExplorerBar, IID_IOleClientSite, OleClientSite)
END_INTERFACE_MAP()


// **************************************************************************
// * IDocHostUIHandler methods
// **************************************************************************
ULONG FAR EXPORT  CExplorerBar::XDocHostUIHandler::AddRef()
{
METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
return pThis->ExternalAddRef();
}ULONG FAR EXPORT  CExplorerBar::XDocHostUIHandler::Release()
{                            
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return pThis->ExternalRelease();
}
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::QueryInterface
(REFIID riid, void **ppvObj)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
        return hr;
}// CImpIDocHostUIHandler::GetHostInfo
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::GetHostInfo
( DOCHOSTUIINFO* pInfo )
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        pInfo->dwFlags = DOCHOSTUIFLAG_NO3DBORDER | DOCHOSTUIFLAG_SCROLL_NO ;
        pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;
        return S_OK;
}// CImpIDocHostUIHandler::ShowUI
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::ShowUI(
				DWORD /*dwID*/, 
				IOleInPlaceActiveObject * /*pActiveObject*/,
				IOleCommandTarget * /*pCommandTarget*/,
				IOleInPlaceFrame * /*pFrame*/,
				IOleInPlaceUIWindow * /*pDoc*/)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return S_OK;
}// CImpIDocHostUIHandler::HideUI
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::HideUI(void)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return S_OK;
}// CImpIDocHostUIHandler::UpdateUI
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::UpdateUI(void)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return S_OK;
}// CImpIDocHostUIHandler::EnableModeless
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::EnableModeless
(BOOL /*fEnable*/)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return E_NOTIMPL;
}// CImpIDocHostUIHandler::OnDocWindowActivate
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::OnDocWindowActivate
(BOOL /*fActivate*/)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return E_NOTIMPL;
}// CImpIDocHostUIHandler::OnFrameWindowActivate
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::OnFrameWindowActivate
(BOOL /*fActivate*/)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return E_NOTIMPL;
}// CImpIDocHostUIHandler::ResizeBorder
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::ResizeBorder(
				LPCRECT /*prcBorder*/, 
				IOleInPlaceUIWindow* /*pUIWindow*/,
				BOOL /*fRameWindow*/)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return E_NOTIMPL;
}

// CImpIDocHostUIHandler::ShowContextMenu
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::ShowContextMenu(
				DWORD /*dwID*/, 
				POINT* /*pptPosition*/,
				IUnknown* /*pCommandTarget*/,
				IDispatch* /*pDispatchObjectHit*/)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return S_FALSE;
}

// CImpIDocHostUIHandler::TranslateAccelerator
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::TranslateAccelerator(LPMSG /*lpMsg*/,
            /* [in] */ const GUID __RPC_FAR* /*pguidCmdGroup*/,
            /* [in] */ DWORD /*nCmdID*/)
{
        METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
        return S_FALSE;
}

// CImpIDocHostUIHandler::GetOptionKeyPath
HRESULT FAR EXPORT  CExplorerBar::XDocHostUIHandler::GetOptionKeyPath
(BSTR* /*pbstrKey*/, DWORD)
{	
	METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
	return E_NOTIMPL;
}
STDMETHODIMP CExplorerBar::XDocHostUIHandler::GetDropTarget( 
            /* [in] */ IDropTarget __RPC_FAR* /*pDropTarget*/,
            /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR* /*ppDropTarget*/)
{	
	METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
	return E_NOTIMPL;
}

STDMETHODIMP CExplorerBar::XDocHostUIHandler::GetExternal( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR* /*ppDispatch*/)
{
	return E_NOTIMPL;
}
        
STDMETHODIMP CExplorerBar::XDocHostUIHandler::TranslateUrl( 
            /* [in] */ DWORD /*dwTranslate*/,
            /* [in] */ OLECHAR __RPC_FAR* /*pchURLIn*/,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR* /*ppchURLOut*/)
{
	METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
	return E_NOTIMPL;
}
        
STDMETHODIMP CExplorerBar::XDocHostUIHandler::FilterDataObject( 
            /* [in] */ IDataObject __RPC_FAR* /*pDO*/,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR* /*ppDORet*/)
{
	METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
	return E_NOTIMPL;
}
STDMETHODIMP CExplorerBar::XDocHostUIHandler::GetOverrideKeyPath(
    LPOLESTR* /*pchKey*/, DWORD /*dw*/)
{
	/*
	 * This is not called due to the bug.
	 */	
	METHOD_PROLOGUE(CExplorerBar, DocHostUIHandler)
	return E_NOTIMPL;
} 




ULONG FAR EXPORT  CExplorerBar::XOleClientSite::AddRef()
{
METHOD_PROLOGUE(CExplorerBar, OleClientSite)
return pThis->ExternalAddRef();
}ULONG FAR EXPORT  CExplorerBar::XOleClientSite::Release()
{                            
        METHOD_PROLOGUE(CExplorerBar, OleClientSite)
        return pThis->ExternalRelease();
}
HRESULT FAR EXPORT  CExplorerBar::XOleClientSite::QueryInterface
(REFIID riid, void **ppvObj)
{
        METHOD_PROLOGUE(CExplorerBar, OleClientSite)
        HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
        return hr;
}// CImpIDocHostUIHandler::GetHostInfo



BEGIN_MESSAGE_MAP(CExplorerBar, CWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CExplorerBar::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (m_pSearch)
	{
		m_pSearch->MoveWindow(0, 0, cx, cy);
	}
}
