// FlowGraphSampleView.cpp : implementation of the CFlowGraphSampleView class
//

#include "stdafx.h"
#include "FlowGraphSample.h"

#include "FlowGraphSampleDoc.h"
#include "FlowGraphSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT ID_FLOWGRAPH_CONTROL = 100;

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView

IMPLEMENT_DYNCREATE(CFlowGraphSampleView, CView)

BEGIN_MESSAGE_MAP(CFlowGraphSampleView, CView)
	//{{AFX_MSG_MAP(CFlowGraphSampleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_FLOWGRAPH_SHOWNODEGROUPSALWAYS, OnFlowgraphShowNodegroupsAlways)
	ON_UPDATE_COMMAND_UI(ID_FLOWGRAPH_SHOWNODEGROUPSALWAYS, OnUpdateFlowgraphShowNodegroupsAlways)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)

	ON_NOTIFY(XTP_SBN_SCROLL, ID_INDICATOR_ZOOMSLIDER, OnZoomSliderScroll)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ZOOM, OnUpdateViewZoom)

	ON_COMMAND(ID_VIEW_ZOOM_TOSELECTION, OnZoomToSelection)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_TOSELECTION, OnUpdateHasSelection)
	ON_COMMAND(ID_VIEW_ZOOM_FITWINDOW, OnZoomFitToWindow)

	ON_COMMAND(ID_EDIT_ARRANGE, OnEditArrange)

	ON_NOTIFY(NM_RCLICK, ID_FLOWGRAPH_CONTROL, OnGraphRClick)


	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)

	ON_COMMAND(ID_FLOWGRAPH_METALLICTHEME, OnMetallicTheme)
	ON_UPDATE_COMMAND_UI(ID_FLOWGRAPH_METALLICTHEME, OnUpdateMetallicTheme)

	ON_COMMAND(ID_FLOWGRAPH_SHOWGRID, OnShowGrid)
	ON_UPDATE_COMMAND_UI(ID_FLOWGRAPH_SHOWGRID, OnUpdateShowGrid)

	ON_COMMAND_RANGE(ID_FLOWGRAPH_STRAIGHTCONNECTOR, ID_FLOWGRAPH_CURVEDCONNECTOR, OnConnectorType)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FLOWGRAPH_STRAIGHTCONNECTOR, ID_FLOWGRAPH_CURVEDCONNECTOR, OnUpdateConnectorType)
	
	ON_COMMAND_RANGE(ID_FLOWGRAPH_QUALITY_HIGHQUALITY, ID_FLOWGRAPH_QUALITY_AUTOQUALITY, OnQuality)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FLOWGRAPH_QUALITY_HIGHQUALITY, ID_FLOWGRAPH_QUALITY_AUTOQUALITY, OnUpdateQuality)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView construction/destruction

CFlowGraphSampleView::CFlowGraphSampleView()
{
	m_bMetallicTheme = TRUE;

}

CFlowGraphSampleView::~CFlowGraphSampleView()
{
}

BOOL CFlowGraphSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView drawing

void CFlowGraphSampleView::OnDraw(CDC* /*pDC*/)
{
	CFlowGraphSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}



/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView printing

void CFlowGraphSampleView::OnPrint(CDC* pDC, CPrintInfo*)
{
	CFlowGraphSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CXTPFlowGraphDrawContextGdiPlus dc(pDC->m_hDC, pDC->m_hAttribDC, TRUE);
	m_wndControl.OnDraw(&dc);
}

BOOL CFlowGraphSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->m_nNumPreviewPages = 1;
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	
	
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFlowGraphSampleView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	if (!pInfo)
		return;
	
	pDC->SetMapMode(MM_ANISOTROPIC);
	
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),	pDC->GetDeviceCaps(LOGPIXELSY));
	
	pDC->SetWindowExt(96, 96);
	
	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(0, 0);
	
}


void CFlowGraphSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFlowGraphSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFlowGraphSampleView::OnFilePrintPreview()
{
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.
	
	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;
	
	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.
	
	if ( !DoPrintPreview( XTP_IDD_PREVIEW_DIALOGBAR, this,
		RUNTIME_CLASS( CXTPPreviewView ), pState ))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		TRACE0( "Error: DoPrintPreview failed.\n" );
		AfxMessageBox( AFX_IDP_COMMAND_FAILURE );
		delete pState;      // preview failed to initialize, delete State now
		
	}

}

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView diagnostics

#ifdef _DEBUG
void CFlowGraphSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CFlowGraphSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFlowGraphSampleDoc* CFlowGraphSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlowGraphSampleDoc)));
	return (CFlowGraphSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView message handlers

COLORREF clrOfficeColors[] = 
{
	RGB(79, 129,189),	// Blue
	RGB(192, 80, 77),	// Red
	RGB(155, 187, 89),	// Green
	RGB(128, 100, 162), // Purple
	RGB(75, 172, 198),  // Aqua
	RGB(247, 150, 70), // Orange
	RGB(31, 73, 125),
}; 

void CFlowGraphSampleView::CreateDatabaseRelationships()
{
	m_wndControl.GetPages()->RemoveAll();

	CXTPFlowGraphPage* pPage = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());

	CXTPFlowGraphNode* pTableCustomers = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableCustomers->SetCaption(_T("Customers"));
	pTableCustomers->SetTooltip(_T("Customers Table"));
	pTableCustomers->SetColor(clrOfficeColors[2]);
	pTableCustomers->SetLocation(CPoint(820, 360));
	pTableCustomers->SetImageIndex(0);

	CXTPFlowGraphConnectionPoint* pConnectionPoint;
	pConnectionPoint = pTableCustomers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointInput);

	pConnectionPoint = pTableCustomers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Company"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);
	
	pConnectionPoint = pTableCustomers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Last Name"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableCustomers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("First Name"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableCustomers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Job Title"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableCustomers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Business Phone"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);


	CXTPFlowGraphNode* pTableOrders = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableOrders->SetCaption(_T("Orders"));
	pTableOrders->SetTooltip(_T("Orders Table"));
	pTableOrders->SetLocation(CPoint(420, 90));
	//pTableOrders->SetColor(clrOfficeColors[1]);
	
	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Order ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointInput);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Employee ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointOutput);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Customer ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointOutput);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Order Date"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Shipped Date"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Shipper ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointOutput);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Taxes"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Payment Type"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Paid Date"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableOrders->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Notes"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	CXTPFlowGraphNode* pTableEmployees = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableEmployees->SetCaption(_T("Employees"));
	pTableEmployees->SetTooltip(_T("Employees Table"));
	pTableEmployees->SetLocation(CPoint(820, 90));
	pTableEmployees->SetColor(clrOfficeColors[4]);

	pConnectionPoint = pTableEmployees->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointInput);

	pConnectionPoint = pTableEmployees->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Company"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableEmployees->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Last Name"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableEmployees->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("First Name"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableEmployees->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("E-mail Address"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableEmployees->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Job Title"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableEmployees->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Business Phone"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	CXTPFlowGraphNode* pTableOrderDetails = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableOrderDetails->SetCaption(_T("Order Details"));
	pTableOrderDetails->SetTooltip(_T("Order Details Table"));
	pTableOrderDetails->SetLocation(CPoint(190, 200));
	pTableOrderDetails->SetColor(clrOfficeColors[1]);
	pTableOrderDetails->SetImageIndex(1);

	pConnectionPoint = pTableOrderDetails->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointInput);

	pConnectionPoint = pTableOrderDetails->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Order ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointOutput);

	pConnectionPoint = pTableOrderDetails->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Product ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointOutput);

	pConnectionPoint = pTableOrderDetails->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Quantity"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableOrderDetails->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Unit Price"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableOrderDetails->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Discount"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableOrderDetails->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Status ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);



	CXTPFlowGraphNode* pTableShippers = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableShippers->SetCaption(_T("Shippers"));
	pTableShippers->SetTooltip(_T("Shippers Table"));
	pTableShippers->SetLocation(CPoint(620, 360));
	//pTableShippers->SetColor(clrOfficeColors[3]);

	pConnectionPoint = pTableShippers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointInput);

	pConnectionPoint = pTableShippers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Company"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableShippers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Last Name"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableShippers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("First Name"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableShippers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("E-mail Address"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableShippers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Job Title"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableShippers->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Business Phone"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	CXTPFlowGraphNode* pTableProducts = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableProducts->SetCaption(_T("Products"));
	pTableProducts->SetTooltip(_T("Products Table"));
	pTableProducts->SetLocation(CPoint(420, 360));
	//pTableProducts->SetColor(clrOfficeColors[4]);
	
	pConnectionPoint = pTableProducts->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("ID"));
	pConnectionPoint->SetType(xtpFlowGraphPointInput);

	pConnectionPoint = pTableProducts->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Product Code"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableProducts->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Product Name"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableProducts->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Description"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);

	pConnectionPoint = pTableProducts->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Price"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);
	
	pConnectionPoint = pTableProducts->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Category"));
	pConnectionPoint->SetType(xtpFlowGraphPointNone);


	CXTPFlowGraphConnection* pConnection;
	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Customer ID")));
	pConnection->SetInputPoint(pTableCustomers->GetConnectionPoints()->FindConnectionPoint(_T("ID")));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Shipper ID")));
	pConnection->SetInputPoint(pTableShippers->GetConnectionPoints()->FindConnectionPoint(_T("ID")));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Employee ID")));
	pConnection->SetInputPoint(pTableEmployees->GetConnectionPoints()->FindConnectionPoint(_T("ID")));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrderDetails->GetConnectionPoints()->FindConnectionPoint(_T("Order ID")));
	pConnection->SetInputPoint(pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Order ID")));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrderDetails->GetConnectionPoints()->FindConnectionPoint(_T("Product ID")));
	pConnection->SetInputPoint(pTableProducts->GetConnectionPoints()->FindConnectionPoint(_T("ID")));


#if 0
	CXTPFlowGraphNodeGroups* pGroups = pPage->GetGroups();
	CXTPFlowGraphNodeGroup* pGroup = pGroups->AddGroup();
	pGroup->AddNode(pTableEmployees);
	pGroup->AddNode(pTableCustomers);
#endif

	m_wndControl.SetActivePage(pPage);

}

int CFlowGraphSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndControl.Create(WS_VSCROLL | WS_HSCROLL | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), 
		this, ID_FLOWGRAPH_CONTROL);

	CXTPFlowGraphImage* pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), IDB_NODEIMAGE_CUSTOMERS);

	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_ORDERDETAILS), _T("PNG"));

	CreateDatabaseRelationships();

	m_wndControl.SetPaintManager(new CXTPFlowGraphMetallicTheme());

	return 0;
}


void CFlowGraphSampleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}


void CFlowGraphSampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_wndControl.GetSafeHwnd())
	{
		m_wndControl.MoveWindow(0, 0, cx, cy);
	}
	
}

BOOL CFlowGraphSampleView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}



// Convert 0 -> 10%, 500 -> 100 %, 1000 -> 500 %

int PosToZoom(int nPos) {
	return nPos <= 500 ? 10 + MulDiv(nPos, 90, 500) : 100 + MulDiv(nPos - 500, 400, 500);
}
int ZoomToPos(int nZoom) {
	return nZoom < 100 ? MulDiv(nZoom - 10, 500, 90) : 500 + MulDiv(nZoom - 100, 500, 400);
}

void CFlowGraphSampleView::OnZoomSliderScroll(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPSCROLL* pNMScroll = (NMXTPSCROLL*)pNMHDR;

	CXTPStatusBarSliderPane* pPane = DYNAMIC_DOWNCAST(CXTPStatusBarSliderPane, pNMScroll->pSender);

	ASSERT(pPane);

	int nZoom = int(m_wndControl.GetZoomLevel() * 100);
	int nPrevZoom = nZoom;

	int nLineDelta = nZoom <= 100 ? 10 : 50;

	switch (pNMScroll->nSBCode)
	{
	case SB_TOP: nZoom = 10; break;
	case SB_BOTTOM: nZoom = 500; break;
		
	case SB_LINEUP: nZoom = max(((nZoom / nLineDelta) - 1) * nLineDelta, 10); break;
	case SB_LINEDOWN: nZoom = min(((nZoom / nLineDelta) + 1) * nLineDelta, 500); break;
		
	case SB_THUMBTRACK: nZoom = PosToZoom(pNMScroll->nPos); if (nZoom > 90 && nZoom < 150) nZoom = 100; break;
		
	case SB_PAGEUP: nZoom = max(nZoom - nLineDelta, 10); break;
	case SB_PAGEDOWN: nZoom = min(nZoom + nLineDelta, 500); break;
	}

	*pResult = TRUE; // Handled
	
	if (nZoom == nPrevZoom)
		return;
	
	pPane->SetPos(ZoomToPos(nZoom));
	
	CXTPStatusBar* pStatusBar = pPane->GetStatusBar();
	
	CXTPStatusBarPane* pPaneZoomIndicator = pStatusBar->FindPane(ID_INDICATOR_ZOOM);
	
	CString strZoom;
	strZoom.Format(_T("%i%%"), nZoom);
	pPaneZoomIndicator->SetText(strZoom);

	m_wndControl.SetZoomLevel(nZoom / 100.0);
}

void CFlowGraphSampleView::OnUpdateViewZoom(CCmdUI* pCmdUI)
{
	CXTPStatusBar* pStatusBar = DYNAMIC_DOWNCAST(CXTPStatusBar, pCmdUI->m_pOther); 
	if (!pStatusBar)
		return;

	int nZoom = int(m_wndControl.GetZoomLevel() * 100);

	if (m_nZoom != nZoom)
	{
		CXTPStatusBarPane* pPane = pStatusBar->GetPane(pCmdUI->m_nIndex);

		m_nZoom = nZoom;

		CString strZoom;
		strZoom.Format(_T("%i%%"), m_nZoom);
		pPane->SetText(strZoom);

		CXTPStatusBarSliderPane* pSliderPane = (CXTPStatusBarSliderPane*)pStatusBar->GetPane(pCmdUI->m_nIndex + 1);

		pSliderPane->SetPos(ZoomToPos(nZoom));
	}
	
	
	pCmdUI->Enable(TRUE);
}


void CFlowGraphSampleView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	m_wndControl.SetFocus();
	
}

void CFlowGraphSampleView::OnUpdateHasSelection(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetActivePage()->GetSelection()->GetCount() > 0);
}

void CFlowGraphSampleView::OnZoomToSelection()
{
	m_wndControl.ZoomToSelection();
}

void CFlowGraphSampleView::OnZoomFitToWindow()
{
	m_wndControl.ZoomFitToWindow();
}
void CFlowGraphSampleView::OnEditSelectAll() 
{
	m_wndControl.SelectAll();
	
}

void CFlowGraphSampleView::OnEditArrange()
{
	m_wndControl.Arrange();
}


UINT CFlowGraphSampleView::TrackPopupMenu(CMenu* pMenu, UINT nFlags, int xPos, int yPos)
{
	return CXTPCommandBars::TrackPopupMenu(pMenu, nFlags, xPos, yPos, this);

};

void CFlowGraphSampleView::OnGraphRClick(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
	CPoint point;
	GetCursorPos(&point);

	m_wndControl.ScreenToClient(&point);

	CXTPFlowGraphNode* pNode = m_wndControl.HitTestNode(point);

	CXTPFlowGraphConnection* pConnection = m_wndControl.HitTestConnection(point);

	CXTPFlowGraphSelectedElements* pSelection = m_wndControl.GetActivePage()->GetSelection();

	if (pNode)
	{
		if (!pNode->IsSelected())
		{
			pSelection->Clear();
			pNode->Select();
		}
		m_wndControl.GetActivePage()->GetNodes()->MoveToFront(pNode);


		CMenu menu;
		menu.LoadMenu(IDR_MENU_CONTEXT);

		CPoint point;
		GetCursorPos(&point);

		CPoint pointClient = point;
		m_wndControl.ScreenToClient(&pointClient);

		CXTPFlowGraphConnectionPoint* pConnectionPoint = pNode->HitTestConnectionPoint(pointClient);

		UINT nCommand = TrackPopupMenu(menu.GetSubMenu(pConnectionPoint ? 3 : 0), TPM_RETURNCMD, point.x, point.y);

		if (nCommand >= ID_NODE_COLOR_BLUE && nCommand <= ID_NODE_COLOR_ORANGE)
		{
			pNode->SetColor(clrOfficeColors[nCommand - ID_NODE_COLOR_BLUE]);

		}
		else if (nCommand == ID_NODE_DELETE)
		{
			pNode->Remove();
		}
		else if (nCommand == ID_CONNECTIONPOINT_DELETE)
		{
			pConnectionPoint->Remove();
		}
		else if (nCommand == ID_NODE_RENAME)
		{
			m_wndControl.RenameNode(pNode);
		}
		else if (nCommand == ID_CONNECTIONPOINT_ADD)
		{
			pConnectionPoint = new CXTPFlowGraphConnectionPoint();
			pNode->GetConnectionPoints()->AddConnectionPoint(pConnectionPoint);

			m_wndControl.UpdateWindow();

			m_wndControl.RenameConnectionPoint(pConnectionPoint);
		}
		else if (nCommand == ID_CONNECTIONPOINT_RENAME)
		{
			m_wndControl.RenameConnectionPoint(pConnectionPoint);
		}
		else if (nCommand == ID_GROUP_UNGROUP)
		{
			for (int i = 0; i < pSelection->GetCount(); i++)
			{
				CXTPFlowGraphNode* pNode = DYNAMIC_DOWNCAST(CXTPFlowGraphNode, pSelection->GetAt(i));
				if (!pNode)
					continue;

				if (pNode->GetGroup() != NULL)
				{
					pNode->GetGroup()->RemoveNode(pNode);
				}
			}
		}
		else if (nCommand == ID_GROUP_GROUP)
		{
			CXTPFlowGraphNodeGroup* pGroup = m_wndControl.GetActivePage()->GetGroups()->AddGroup();

			for (int i = 0; i < pSelection->GetCount(); i++)
			{
				CXTPFlowGraphNode* pNode = DYNAMIC_DOWNCAST(CXTPFlowGraphNode, pSelection->GetAt(i));
				if (!pNode)
					continue;

				pGroup->AddNode(pNode);
			}

			if (pGroup->GetCount() < 2)
			{
				pGroup->Remove();
			}
			else
			{				
				pGroup->GetAt(0)->Select();			
			}
		}

	}
	else if (pConnection)
	{
		if (!pConnection->IsSelected())
		{
			pSelection->Clear();
			pSelection->AddSelection(pConnection);
		}

		CMenu menu;
		menu.LoadMenu(IDR_MENU_CONTEXT);

		CPoint point;
		GetCursorPos(&point);

		UINT nCommand = TrackPopupMenu(menu.GetSubMenu(2), TPM_RETURNCMD, point.x, point.y);

		if (nCommand == ID_CONNECTORTYPE_STRAIGHTCONNECTOR)
		{
			pConnection->SetStyle(xtpFlowGraphConnectorStraight);
		}
		else if (nCommand == ID_CONNECTORTYPE_CURVEDCONNECTOR)
		{
			pConnection->SetStyle(xtpFlowGraphConnectorCurved);
		}
		else if (nCommand == ID_CONNECTION_DELETECONNECTION)
		{
			pConnection->Remove();
		}
		else if (nCommand == ID_CONNECTION_CLEANCONTROLPOINTS)
		{
			pConnection->SetControlPoint(CPoint(-1, -1));
		}

	}
	else
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENU_CONTEXT);
		
		CPoint point;
		GetCursorPos(&point);
		
		UINT nCommand = TrackPopupMenu(menu.GetSubMenu(1), TPM_RETURNCMD, point.x, point.y);
		
		if (nCommand == ID_NODE_ADD)
		{
			m_wndControl.ScreenToClient(&point);
			point = m_wndControl.GetActivePage()->ScreenToPage(point);

			m_wndControl.GetUndoManager()->StartGroup();
			
			pNode= m_wndControl.GetActivePage()->GetNodes()->AddNode(new CXTPFlowGraphNode());
			pNode->SetLocation(point);
			pNode->SetCaption(_T("New Node"));
			pNode->SetColor(RGB(79, 129,189));
			
			CXTPFlowGraphConnectionPoint* pConnectionPoint;
			pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
			pConnectionPoint->SetCaption(_T("Output"));
			pConnectionPoint->SetType(xtpFlowGraphPointOutput);
			
			pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
			pConnectionPoint->SetCaption(_T("Input"));

			pSelection->SetSelection(pNode);

			m_wndControl.GetUndoManager()->EndGroup();
		}
	}

}
void CFlowGraphSampleView::OnEditCopy()
{
	m_wndControl.GetActivePage()->Copy();
}

void CFlowGraphSampleView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetActivePage()->GetSelection()->GetCount() > 0);
}

void CFlowGraphSampleView::OnEditCut()
{
	//if (AfxMessageBox(_T("Are you sure you want delete selected objects"), MB_YESNO) == IDYES)
	m_wndControl.GetActivePage()->Cut();
}

void CFlowGraphSampleView::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetActivePage()->GetSelection()->GetCount() > 0);
}

void CFlowGraphSampleView::OnEditPaste()
{
	m_wndControl.GetActivePage()->Paste();
}

void CFlowGraphSampleView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetActivePage()->CanPaste());
}

void CFlowGraphSampleView::OnEditUndo()
{
	m_wndControl.GetUndoManager()->Undo();
}

void CFlowGraphSampleView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetUndoManager()->CanUndo());
}

void CFlowGraphSampleView::OnEditRedo()
{
	m_wndControl.GetUndoManager()->Redo();
}

void CFlowGraphSampleView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetUndoManager()->CanRedo());
}

void CFlowGraphSampleView::OnMetallicTheme()
{
	m_bMetallicTheme ^= 1;

	if (m_bMetallicTheme)
	{
		m_wndControl.SetPaintManager(new CXTPFlowGraphMetallicTheme());
	}
	else
	{
		m_wndControl.SetPaintManager(new CXTPFlowGraphPaintManager());
	}
}

void CFlowGraphSampleView::OnUpdateMetallicTheme(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bMetallicTheme ? 1 : 0);
	
}

void CFlowGraphSampleView::OnShowGrid()
{
	m_wndControl.GetPaintManager()->m_bShowGrid ^= 1;
	
	m_wndControl.RedrawControl();
}

void CFlowGraphSampleView::OnUpdateShowGrid(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndControl.GetPaintManager()->m_bShowGrid ? 1 : 0);
	
}

void CFlowGraphSampleView::OnConnectorType(UINT nCmd)
{
	m_wndControl.GetPaintManager()->m_nConnectorType = 
		(XTPFlowGraphConnectorType) (nCmd - ID_FLOWGRAPH_STRAIGHTCONNECTOR);

	m_wndControl.GetActivePage()->OnGraphChanged();
}

void CFlowGraphSampleView::OnUpdateConnectorType(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndControl.GetPaintManager()->m_nConnectorType == 
		(XTPFlowGraphConnectorType)(pCmdUI->m_nID - ID_FLOWGRAPH_STRAIGHTCONNECTOR) ? 1 : 0);

}
void CFlowGraphSampleView::OnFlowgraphShowNodegroupsAlways() 
{
	m_wndControl.GetPaintManager()->m_bShowNodeGroupsAlways ^= 1;
	m_wndControl.RedrawControl();
}

void CFlowGraphSampleView::OnUpdateFlowgraphShowNodegroupsAlways(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndControl.GetPaintManager()->m_bShowNodeGroupsAlways ? 1 : 0);
}

void CFlowGraphSampleView::OnQuality(UINT nCmd)
{
	m_wndControl.SetSmoothingMode((XTPFlowGraphSmoothingMode)(nCmd - ID_FLOWGRAPH_QUALITY_HIGHQUALITY));	

}

void CFlowGraphSampleView::OnUpdateQuality(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndControl.GetSmoothingMode() == (XTPFlowGraphSmoothingMode)(pCmdUI->m_nID - ID_FLOWGRAPH_QUALITY_HIGHQUALITY) ? 1 : 0);
	
}
