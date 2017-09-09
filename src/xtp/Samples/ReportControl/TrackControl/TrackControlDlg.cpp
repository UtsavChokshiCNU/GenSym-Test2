// TrackControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackControl.h"
#include "TrackControlDlg.h"
#include "DialogTimeLineProperties.h"
#include "DialogMarkerProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class CTrackControlPaintManager : public CXTPTrackPaintManager
{
public:
	CTrackControlPaintManager()
	{
		m_columnStyle = xtpReportColumnResource;

		RefreshMetrics();
	}

	void RefreshMetrics()
	{
		CXTPTrackPaintManager::RefreshMetrics();

		SetDrawGridForEmptySpace(TRUE);
		SetGridStyle(0, xtpReportGridSolid);
		SetGridStyle(1, xtpReportGridSolid);
		
		SetHeaderRowsDividerStyle(xtpReportFixedRowsDividerBold);
		SetFooterRowsDividerStyle(xtpReportFixedRowsDividerBold);
		m_clrHeaderRowsDivider = RGB(255,0,0);
		m_clrFooterRowsDivider = RGB(0,0,255);
		
		SetLastColumnWidthWYSIWYG(TRUE);
		
		
		SetHeaderRowsDividerStyle(xtpReportFixedRowsDividerBold);
		SetFooterRowsDividerStyle(xtpReportFixedRowsDividerBold);
		m_clrHeaderRowsDivider = RGB(0,255,0);
		m_clrFooterRowsDivider = RGB(0,0,255);
		
		SetDrawGridForEmptySpace(TRUE);
		m_bUseAlternativeBackground = TRUE;
		
		m_clrControlBack = RGB(166,166,166);
		m_clrAlternativeBackground = RGB(160,160,160);
		m_clrHighlight = RGB(145,145,145);
		m_clrSelectedRow = RGB(145,145,145);
		m_clrGroupBoxBack = RGB(128,128,128);
		m_clrGroupRowText = RGB(255,255,255);
		
		m_clrGridLine = RGB(193,193,193);
		
		m_clrColumnOffice2007CustomTheme = RGB(122,122,122);

		m_grcGradientColumnPushed.SetStandardValue(RGB(193,193,193), RGB(169, 169, 169));
		m_grcGradientColumnHot.SetStandardValue(RGB(193,193,193), RGB(169, 169, 169));
		m_grcGradientColumn.SetStandardValue(RGB(193,193,193), RGB(169, 169, 169));
		m_clrGradientColumnShadow.SetStandardValue(RGB(122,122,122));
		m_clrGradientColumnSeparator.SetStandardValue(RGB(122,122,122));
		m_clrGroupBoxBack.SetStandardValue(RGB(166,166,166));
		m_crlNoGroupByText.SetStandardValue(0);
		m_clrGroupShadeBack.SetStandardValue(RGB(166,166,166));
		

		m_bShadeSortColumn = FALSE;


		m_clrWorkArea = RGB(175, 175, 175);
		m_clrTrackHeader = RGB(166, 166, 166);
		m_clrTrackTimeArea = RGB(166, 166, 166);
		
		m_clrTimeHeaderDarkDark = RGB(70, 70, 70);
		m_clrTimeHeaderDark = RGB(122, 122, 122);
		m_clrTimeSliderBackground = RGB(96, 96, 96);
		
		m_clrTimeHeaderDivider = RGB(146, 146, 146);

		m_clrScrollBarLight = RGB(210, 210, 210);
		m_clrScrollBarDark = RGB(190, 190, 190);

		m_clrMarker = RGB(217, 217, 217);
		m_clrSelectedArea = RGB(70, 70, 70);
	}

};


static int COL_NUMBER = 4;
static int ROW_NUMBER = 20;

IMPLEMENT_SERIAL(CReportViewRecord, CXTPReportRecord, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)

CReportViewRecord::CReportViewRecord()
{
	int i;
	CString fieldStr;

	for (i = 0; i < COL_NUMBER; ++i) 
	{
		fieldStr.Format(_T("Field Col %d"),i);
		
		AddItem(new CXTPReportRecordItemText(fieldStr));
	}
}

const COLORREF clrTable[] =
{
	RGB(138, 168, 228), // xtpTabColorBlue    : Blue tab color used when OneNote colors enabled.
	RGB(255, 219, 117), // xtpTabColorYellow  : Yellow tab color used when OneNote colors enabled.
	RGB(189, 205, 159), // xtpTabColorGreen   : Green tab color used when OneNote colors enabled.
	RGB(240, 158, 159), // xtpTabColorRed     : Red tab color used when OneNote colors enabled.
	RGB(186, 166, 225), // xtpTabColorPurple  : Purple tab color used when OneNote colors enabled.
	RGB(154, 191, 180), // xtpTabColorCyan    : Cyan tab color used when OneNote colors enabled.
	RGB(247, 182, 131), // xtpTabColorOrange  : Orange tab color used when OneNote colors enabled.
	RGB(216, 171, 192)  // xtpTabColorMagenta : Magenta tab color used when OneNote colors enabled.
};

CReportViewRecord::CReportViewRecord(int j)
{
	CString fieldStr;
	
	CString ss(_T("IJKLMNOPABCDEFGHXXXX")), s;
	int l = ss.GetLength();

	for (int i = 0; i < COL_NUMBER; ++i) 
	{
		fieldStr.Format(_T("%c - R%02d"), ss[(l - j - 1) % 16], j);

		if (i < COL_NUMBER - 1)
		{
			CXTPReportRecordItem* pItem = AddItem(new CXTPReportRecordItemText(fieldStr));
			pItem->SetEditable(FALSE);
		}
		else
		{
			CXTPTrackControlItem* pItem = (CXTPTrackControlItem* ) AddItem(new CXTPTrackControlItem());
			pItem->SetEditable(FALSE);
			

			int nStep, nS;
			nS = 20;

			int xPos, xLen;

			int K = rand() % 5;

			CString strToolTip, strDescription;


			if (j != 4)
			{
				for (int k = 0; k < K; k ++)
				{
					nStep = rand() % 100;
					nS += nStep; 

					xLen = 0;
					xPos = nS;

					nStep = rand() % 100 + 10;
					nS += nStep; 
					xLen = nStep;
					CXTPTrackBlock* pBlock = new CXTPTrackBlock();
					pBlock->SetPosition(xPos);
					pBlock->SetLength(xLen);
					pBlock->SetColor(clrTable[rand() % 5]);

					pBlock->SetMinLength(10);
					pBlock->SetMaxLength(300);

					if ((rand() % 8) == 0)
						pBlock->SetLocked(TRUE);

					if (rand() % 10 == 0)
						pBlock->SetHeightPercent(2.0 / 3.0);

					strToolTip.Format(_T("Block#%d from Track#%d"), k, j);

					pBlock->SetTooltip(strToolTip);

					// Markup can be used:
					// pBlock->SetCaption(_T("<TextBlock>Markup</TextBlock>"));
					// pBlock->SetCaption(_T("<Ellipse Width='10' Height='10' Fill='Red'></Ellipse>"));

					strDescription.Format(_T("Description for Block#%d from Track#%d"), k, j);

					pBlock->SetDescriptionText(strDescription);

					pItem->Add(pBlock);
				}
			}
			else
			{
				for (int iK = 0; iK < 5; iK++)
				{
					nStep = rand() % 400;
					CXTPTrackKey* pMyKey = new CXTPTrackKey();
					
					pMyKey->SetPosition(nStep);
					pMyKey->SetColor(clrTable[iK]);

					CString strToolTip;
					strToolTip.Format(_T("Key#%d from Track#%d"), iK, j);

					pMyKey->SetTooltip(strToolTip);

					if (iK == 2) pMyKey->SetVerticalAlignment(DT_TOP);
					if (iK == 4) pMyKey->SetVerticalAlignment(DT_BOTTOM);

					pItem->Add(pMyKey);
				}
			}
			pItem->RecalcLayout();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTrackControlDlg dialog

CTrackControlDlg::CTrackControlDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CTrackControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrackControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	m_bClassicStyle = FALSE;
}

void CTrackControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackControlDlg)
	DDX_Control(pDX, IDC_SLIDER, m_wndSlider);
	DDX_Control(pDX, IDC_SCROLLBAR, m_wndScrollBar);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndTrackControl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrackControlDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CTrackControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_COMMAND(ID_MODE_TIMEOFFSET, OnUseTimeOffsetMode)
	ON_COMMAND(ID_EDIT_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateUndo)
	ON_COMMAND(ID_EDIT_REDO, OnRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateRedo)
	ON_COMMAND(ID_VIEW_GROUPBOX, OnViewGroupbox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GROUPBOX, OnUpdateViewGroupbox)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_VIEW_CLASSICSTYLE, OnViewClassicStyle)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TRACKCONTROL_FLEXIBLEDRAG, OnFlexibleDrag)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CLASSICSTYLE, OnUpdateViewClassicStyle)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_FLEXIBLEDRAG, OnUpdateFlexibleDrag)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_TRACKCONTROL_SNAPTOBLOCKS, OnSnapToBlocks)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_SNAPTOBLOCKS, OnUpdateSnapToBlocks)
	ON_COMMAND(ID_TRACKCONTROL_SNAPTOMARKERS, OnSnapToMarkers)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_SNAPTOMARKERS, OnUpdateSnapToMarkers)
	ON_COMMAND(ID_TRACKCONTROL_ALLOWBLOCKMOVE, OnAllowblockmove)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_ALLOWBLOCKMOVE, OnUpdateAllowblockmove)
	ON_COMMAND(ID_TRACKCONTROL_ALLOWBLOCKSCALE, OnAllowblockscale)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_ALLOWBLOCKSCALE, OnUpdateAllowblockscale)
	ON_COMMAND(ID_TRACKCONTROL_ALLOWROWRESIZE, OnAllowRowResize)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_ALLOWROWRESIZE, OnUpdateAllowRowResize)
	ON_COMMAND(ID_TRACKCONTROL_SCALEONRESIZE, OnScaleOnResize)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_SCALEONRESIZE, OnUpdateScaleOnResize)
	ON_COMMAND(ID_TRACKCONTROL_ALLOWBLOCKREMOVE, OnAllowblockRemove)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_ALLOWBLOCKREMOVE, OnUpdateAllowblockRemove)
	ON_WM_HSCROLL()
	ON_COMMAND(ID_TRACKCONTROL_SHOWWORKAREA, OnShowWorkarea)
	ON_UPDATE_COMMAND_UI(ID_TRACKCONTROL_SHOWWORKAREA, OnUpdateShowWorkarea)
	//}}AFX_MSG_MAP

	ON_NOTIFY(XTP_NM_REPORT_VALUECHANGED, IDC_REPORTCTRL, OnPropertyChanged)
	ON_NOTIFY(NM_RCLICK, IDC_REPORTCTRL, OnRClick)
	ON_NOTIFY(XTP_NM_REPORT_HEADER_RCLICK, IDC_REPORTCTRL, OnHeaderRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORTCTRL, OnDblClick)

	
	ON_NOTIFY(XTP_NM_TRACK_SLIDERCHANGED, IDC_REPORTCTRL, OnTrackSliderChanged)
	ON_NOTIFY(XTP_NM_TRACK_TIMELINECHANGED, IDC_REPORTCTRL, OnTrackTimeLineChanged)
	ON_NOTIFY(XTP_NM_TRACK_MARKERCHANGED, IDC_REPORTCTRL, OnTrackMarkerChanged)
	ON_NOTIFY(XTP_NM_TRACK_BLOCKCHANGED, IDC_REPORTCTRL, OnTrackBlockChanged)
	ON_NOTIFY(XTP_NM_TRACK_SELECTEDBLOCKSCHANGED, IDC_REPORTCTRL, OnTrackSelectedBlocksChanged)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackControlDlg message handlers


BOOL CTrackControlDlg::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	m_wndTrackControl.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	
	int i;
	CString columnStr;

	for (i = 0; i < COL_NUMBER; ++i) 
	{
		columnStr.Format(_T("Column %d"),i);
		if (i == COL_NUMBER - 1)
			columnStr = "";
		CXTPReportColumn* pCol = m_wndTrackControl.AddColumn(new CXTPReportColumn(i, columnStr, 80, FALSE, XTP_REPORT_NOICON));
		pCol->EnableResize(TRUE);
		pCol->SetMinWidth(80);
	}
	
	for (i = 0; i < ROW_NUMBER; ++i) 
		m_wndTrackControl.AddRecord(new CReportViewRecord(i));

	m_wndTrackControl.GetReportHeader()->SetMaxColumnWidth(300);
	
	m_wndTrackControl.Populate();
	

	m_wndTrackControl.SetPaintManager(new CTrackControlPaintManager());
	m_wndTrackControl.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_wndTrackControl.m_bSortedDragDrop = TRUE;
	m_wndTrackControl.AllowEdit(TRUE);
	m_wndTrackControl.SetMultipleSelection(FALSE);

	m_wndTrackControl.EnableMarkup(TRUE);
		
	m_wndTrackControl.GetColumns()->GetFirstVisibleColumn()->SetAutoSize(TRUE);

	m_wndTrackControl.m_bFreeHeightMode = TRUE;

	m_wndTrackControl.EnableDragDrop(_T("DialogTrackView"), xtpReportAllowDrag | xtpReportAllowDrop);

	m_wndTrackControl.SetTimeLineRange(0, 1000);
	m_wndTrackControl.SetViewPort(0, 500);
	m_wndTrackControl.SetWorkArea(0, 450);
	
	m_wndTrackControl.SetTimeLinePosition(100);
	
	m_wndTrackControl.GetMarkers()->Add(50, _T("1"));
	m_wndTrackControl.GetMarkers()->Add(200, _T("2"));
	m_wndTrackControl.GetMarkers()->Add(400, _T("3"));

	m_wndTrackControl.GetReportHeader()->SetLastColumnExpand(TRUE, TRUE);
	m_wndTrackControl.GetReportHeader()->SetAutoColumnSizing(TRUE);

	m_wndTrackControl.GetColumns()->GetLastVisibleColumn()->SetAllowDrag(FALSE);
	m_wndTrackControl.GetColumns()->GetLastVisibleColumn()->SetSortable(FALSE);

	m_wndTrackControl.GetReportHeader()->AllowColumnRemove(FALSE);

	m_wndTrackControl.m_hMoveCursor = AfxGetApp()->LoadCursor(XTP_IDC_REPORT_MOVE);
	m_wndTrackControl.m_hResizeCursor = AfxGetApp()->LoadCursor(XTP_IDC_REPORT_RESIZE);

	m_wndTrackControl.m_bScaleOnResize = FALSE;

	RepositionControls();

	OnTrackSliderChanged(0, 0);

	m_wndTrackControl.GetUndoManager()->Clear();

	// Set Time Units
	// m_wndTrackControl.m_strTimeFormat = _T("%d ms");



	// Set control resizing.
	SetResize(IDC_REPORTCTRL, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDCANCEL, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_SLIDER, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_SCROLLBAR, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	
	// Load window placement
	LoadPlacement(_T("CTrackControlDlg"));


	m_hAccelTable = LoadAccelerators(AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDR_REPORTDIALOG_MENU));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrackControlDlg::RepositionControls()
{
	CXTPWindowRect rc(m_wndTrackControl);

	CRect rcSlider(rc.left + 240, rc.bottom, rc.left + 300, rc.bottom + GetSystemMetrics(SM_CYHSCROLL) + 5);
	CRect rcScrollBar(rcSlider.right, rc.bottom, rc.right - GetSystemMetrics(SM_CXVSCROLL), rc.bottom + GetSystemMetrics(SM_CYHSCROLL));
	
	ScreenToClient(&rcScrollBar);
	ScreenToClient(&rcSlider);
	
	m_wndSlider.MoveWindow(rcSlider);
	m_wndScrollBar.MoveWindow(rcScrollBar);

}

BOOL CTrackControlDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_hAccelTable) 
	{
		if (::TranslateAccelerator(m_hWnd, m_hAccelTable, pMsg)) 
			return(TRUE);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTrackControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CXTPResizeDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrackControlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CXTPResizeDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrackControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTrackControlDlg::OnDestroy() 
{
	CXTPResizeDialog::OnDestroy();
	
	
	// Save window placement
	SavePlacement(_T("CTrackControlDlg"));
	
}

void CTrackControlDlg::OnAppAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
	
}


void CTrackControlDlg::OnInitMenuPopup(CMenu* pMenu, UINT /*nIndex*/, BOOL bSysMenu)
{
	if (bSysMenu)
		return;     // don't support system menu
	
	
	ASSERT(pMenu != NULL);
	// check the enabled state of various menu items
	
	CCmdUI state;
	state.m_pMenu = pMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);
	
	// determine if menu is popup in top-level menu and set m_pOther to
	//  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pMenu->m_hMenu)
		state.m_pParentMenu = pMenu;    // parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = GetTopLevelParent();
		// child windows don't have menus -- need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}
	
	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	state.m_nIndex++)
	{
		state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it
		
		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE);    // popups are never auto disabled
		}
		else
		{
			// normal menu item
			// Auto enable/disable if frame window has 'm_bAutoMenuEnable'
			//    set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE && state.m_nID < 0xF000);
		}
		
		// adjust for menu deletions and additions
		UINT nCount = pMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}


void CTrackControlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CXTPResizeDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar == (CScrollBar*)&m_wndSlider)
	{
		if (nSBCode != SB_THUMBTRACK)
			nPos = m_wndSlider.GetPos();
		{
			int nCenter = (m_wndTrackControl.GetViewPortMax() + m_wndTrackControl.GetViewPortMin()) / 2;

			int nDelta = (m_wndTrackControl.GetTimeLineMax() - m_wndTrackControl.GetTimeLineMin()) * (100 - nPos) / 100;
			if (nDelta == 0)
				nDelta = 1;
			
			int nViewPortMin = nCenter - nDelta / 2;
			if (nViewPortMin < m_wndTrackControl.GetTimeLineMin())
				nViewPortMin = m_wndTrackControl.GetTimeLineMin();

			if (nViewPortMin + nDelta > m_wndTrackControl.GetTimeLineMax())
				nViewPortMin = m_wndTrackControl.GetTimeLineMax() - nDelta;
			
			int nViewPortMax = nViewPortMin + nDelta;
			
			m_wndTrackControl.SetViewPort(nViewPortMin, nViewPortMax);
			m_wndTrackControl.RedrawControl();

			OnTrackSliderChanged(0, 0);
		}

		return;
	}

	if (pScrollBar == &m_wndScrollBar)
	{

		int nCurPos = m_wndTrackControl.GetViewPortMin();
		int nPage = m_wndTrackControl.GetViewPortMax() - m_wndTrackControl.GetViewPortMin();
		
		// decide what to do for each diffrent scroll event
		switch (nSBCode)
		{
		case SB_TOP:
			nCurPos = 0;
			break;
		case SB_BOTTOM:
			nCurPos = pScrollBar->GetScrollLimit();
			break;
		case SB_LINEUP:
			nCurPos = max(nCurPos - 1, 0);
			break;
		case SB_PAGEUP:
			nCurPos = max(nCurPos - nPage, 0);
			break;
		case SB_LINEDOWN:
			nCurPos = min(nCurPos + 1, pScrollBar->GetScrollLimit());
			break;
		case SB_PAGEDOWN:
			nCurPos = min(nCurPos + nPage, pScrollBar->GetScrollLimit());
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			{
				SCROLLINFO si;
				ZeroMemory(&si, sizeof(SCROLLINFO));
				si.cbSize = sizeof(SCROLLINFO);
				si.fMask = SIF_TRACKPOS;
				
				if (!pScrollBar->GetScrollInfo(&si))
					return;
				nCurPos = si.nTrackPos;
			}
			break;
		}


		m_wndTrackControl.SetViewPort(nCurPos, nCurPos + nPage);
		m_wndTrackControl.RedrawControl();
		OnTrackSliderChanged(0, 0);
	}
}


void CTrackControlDlg::OnUseTimeOffsetMode()
{
	CDialogTimeLineProperties dlg;

	dlg.m_nMin = m_wndTrackControl.GetTimeLineMin();
	dlg.m_nMax = m_wndTrackControl.GetTimeLineMax();
	
	if (dlg.DoModal() == IDOK)
	{
		m_wndTrackControl.SetTimeLineRange(dlg.m_nMin, dlg.m_nMax);
	}

	if (m_wndTrackControl.GetViewPortMin() < m_wndTrackControl.GetTimeLineMin() || m_wndTrackControl.GetViewPortMax() > m_wndTrackControl.GetTimeLineMax())
	{
		m_wndTrackControl.SetViewPort(m_wndTrackControl.GetTimeLineMin(), m_wndTrackControl.GetTimeLineMax());
	}


	m_wndTrackControl.RedrawControl();
}

void CTrackControlDlg::OnUndo()
{
	m_wndTrackControl.GetUndoManager()->Undo();
}

void CTrackControlDlg::OnUpdateUndo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_wndTrackControl.GetUndoManager()->CanUndo());
}

void CTrackControlDlg::OnRedo()
{
	m_wndTrackControl.GetUndoManager()->Redo();
}

void CTrackControlDlg::OnUpdateRedo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_wndTrackControl.GetUndoManager()->CanRedo());
}

CScrollBar* CTrackControlDlg::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pSB =  CXTPResizeDialog::GetScrollBarCtrl(nBar);
	return pSB;
}

void CTrackControlDlg::OnViewGroupbox() 
{
	m_wndTrackControl.ShowGroupBy(!m_wndTrackControl.IsGroupByVisible());
	
}

void CTrackControlDlg::OnUpdateViewGroupbox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.IsGroupByVisible() ? 1 : 0);
	
}

void CTrackControlDlg::OnFileOpen() 
{
	CString strFilter = _T("XML Document (*.xml)|*.xml|All files (*.*)|*.*||");
	
	CFileDialog fd(TRUE, _T("xml"), NULL, OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, strFilter);
	if (fd.DoModal() != IDOK)
		return;
	
	CXTPPropExchangeXMLNode px(TRUE, NULL, _T("TrackControl"));
	
	if (!px.LoadFromFile(fd.GetPathName()))
		return;

	m_wndTrackControl.DoPropExchange(&px);
	
	CXTPPropExchangeSection sec(px.GetSection(_T("Tracks")));
	m_wndTrackControl.GetRecords()->DoPropExchange(&sec);

	m_wndTrackControl.Populate();		
}

void CTrackControlDlg::OnFileSave() 
{
	CString strFilter = _T("XML Document (*.xml)|*.xml|All files (*.*)|*.*||");
	
	CFileDialog fd(FALSE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() != IDOK)
		return;
	
	
	CXTPPropExchangeXMLNode px(FALSE, 0, _T("TrackControl"));


	m_wndTrackControl.DoPropExchange(&px);

	CXTPPropExchangeSection sec(px.GetSection(_T("Tracks")));
	m_wndTrackControl.GetRecords()->DoPropExchange(&sec);
	
	
	px.SaveToFile(fd.GetPathName());
	
}

void CTrackControlDlg::OnViewClassicStyle() 
{
	m_bClassicStyle = !m_bClassicStyle;

	if (m_bClassicStyle)
		m_wndTrackControl.SetPaintManager(new CXTPTrackPaintManager());
	else
		m_wndTrackControl.SetPaintManager(new CTrackControlPaintManager());

	m_wndTrackControl.SetGridStyle(0, xtpReportGridSolid);
	m_wndTrackControl.SetGridStyle(1, xtpReportGridSolid);
	
}

void CTrackControlDlg::OnFlexibleDrag() 
{
	m_wndTrackControl.m_bFlexibleDrag = !m_wndTrackControl.m_bFlexibleDrag;	
}

void CTrackControlDlg::OnUpdateViewClassicStyle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bClassicStyle);
	
}

void CTrackControlDlg::OnUpdateFlexibleDrag(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.m_bFlexibleDrag);
}



void CTrackControlDlg::OnTrackSliderChanged(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_wndScrollBar.SetScrollPos(0, 100);
	m_wndSlider.SetRange(0, 100);
	m_wndSlider.SetPos(100 - (m_wndTrackControl.GetViewPortMax() - m_wndTrackControl.GetViewPortMin()) * 100 / (m_wndTrackControl.GetTimeLineMax() - m_wndTrackControl.GetTimeLineMin()));
	
	
	SCROLLINFO si;
	si.fMask = SIF_ALL;
	si.nPos = m_wndTrackControl.GetViewPortMin();
	si.nMin = m_wndTrackControl.GetTimeLineMin();
	si.nMax = m_wndTrackControl.GetTimeLineMax() - 1;
	si.nPage = m_wndTrackControl.GetViewPortMax() - m_wndTrackControl.GetViewPortMin();
	
	m_wndScrollBar.SetScrollInfo(&si);
}

void CTrackControlDlg::OnPropertyChanged(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	//XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	//m_wndReportCtrl.Populate();
}


void CTrackControlDlg::OnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pNMRCLick = (XTP_NM_REPORTRECORDITEM*)pNotifyStruct;
	CPoint ptScreen = pNMRCLick->pt;
	
	CPoint point = ptScreen;
	m_wndTrackControl.ScreenToClient(&point);

	CXTPTrackControlItem* pItem = DYNAMIC_DOWNCAST(CXTPTrackControlItem, pNMRCLick->pItem);

	if (pItem)
	{
		CXTPTrackBlock* pBlock = pItem->HitTest(point);

		if (pBlock)
		{
			if (!pBlock->IsSelected())
			{
				m_wndTrackControl.GetSelectedBlocks()->RemoveAll();
				pBlock->Select();

				m_wndTrackControl.RedrawControl();
				m_wndTrackControl.UpdateWindow();
			}

			CMenu menu;
			menu.LoadMenu(IDR_MENU_POPUP);

			CMenu* pMenuPopup = menu.GetSubMenu(2);
			
			if (pItem->IsLocked()) pMenuPopup->CheckMenuItem(ID_ITEM_LOCKTRACK, MF_CHECKED | MF_BYCOMMAND);
			if (pBlock->IsLocked()) pMenuPopup->CheckMenuItem(ID_BLOCK_LOCKBLOCK, MF_CHECKED | MF_BYCOMMAND);

			
			int nResult = TrackPopupMenu(pMenuPopup->GetSafeHmenu(), TPM_RETURNCMD, ptScreen.x, ptScreen.y, 0, m_hWnd, 0);

			if (nResult == ID_BLOCK_LOCKBLOCK)
			{
				pBlock->SetLocked(!pBlock->IsLocked());
				m_wndTrackControl.RedrawControl();
			}

			if (nResult == ID_BLOCK_REMOVEBLOCK)
			{
				CXTPTrackSelectedBlocks* pSelected = m_wndTrackControl.GetSelectedBlocks();

				CString strMessage;
				strMessage.Format(_T("Are you sure you want to remove %d block(s)"), (int)pSelected->GetCount());
				
				if (AfxMessageBox(strMessage, MB_YESNO) == IDYES)				
				{
					m_wndTrackControl.GetUndoManager()->StartGroup();

					for (int i = 0; i < pSelected->GetCount(); i++)
					{
						pSelected->GetAt(i)->Remove();
					}
					m_wndTrackControl.GetUndoManager()->EndGroup();

					pSelected->RemoveAll();

					m_wndTrackControl.RedrawControl();
				}
			}

			if (nResult == ID_ITEM_LOCKTRACK)
			{
				pItem->SetLocked(!pItem->IsLocked());
				m_wndTrackControl.GetSelectedBlocks()->RemoveAll();
				m_wndTrackControl.RedrawControl();
			}
		}
		else
		{
			CMenu menu;
			menu.LoadMenu(IDR_MENU_POPUP);
			
			CMenu* pMenuPopup = menu.GetSubMenu(3);
			if (pItem->IsLocked()) pMenuPopup->CheckMenuItem(ID_ITEM_LOCKTRACK, MF_CHECKED | MF_BYCOMMAND);

			int nResult = TrackPopupMenu(pMenuPopup->GetSafeHmenu(), TPM_RETURNCMD, ptScreen.x, ptScreen.y, 0, m_hWnd, 0);
			
			if (nResult == ID_ITEM_ADDBLOCK)
			{
				CXTPTrackBlock* pBlock = new CXTPTrackBlock();
				pBlock->SetPosition(m_wndTrackControl.TrackToPosition(point.x));
				pBlock->SetLength(50);
				pBlock->SetColor(clrTable[(rand() % 3) + 5]);

				pItem->Add(pBlock);
				if (!m_wndTrackControl.m_bFlexibleDrag)
					pItem->AdjustBlockPosition(pBlock);

				pItem->RecalcLayout();

				m_wndTrackControl.RedrawControl();
			}
			if (nResult == ID_ITEM_LOCKTRACK)
			{
				pItem->SetLocked(!pItem->IsLocked());
				m_wndTrackControl.GetSelectedBlocks()->RemoveAll();
				m_wndTrackControl.RedrawControl();
			}
		}
	}
}

void CTrackControlDlg::OnDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pNMRCLick = (XTP_NM_REPORTRECORDITEM*)pNotifyStruct;
	CPoint point = pNMRCLick->pt;

	int nMarker = m_wndTrackControl.GetMarkers()->HitTest(point);

	if (nMarker != -1)
	{
		CXTPTrackMarker* pMarker = m_wndTrackControl.GetMarkers()->GetAt(nMarker);

		CDialogMarkerProperties dp;
		dp.m_strCaption = pMarker->GetCaption();
		dp.m_nPosition = pMarker->GetPosition();

		if (dp.DoModal() == IDOK)
		{
			pMarker->SetCaption(dp.m_strCaption);
			pMarker->SetPosition(dp.m_nPosition);		
		}	
	}
}

void CTrackControlDlg::OnHeaderRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pNMRCLick = (XTP_NM_REPORTRECORDITEM*)pNotifyStruct;
	CPoint ptScreen = pNMRCLick->pt;
	
	CPoint point = ptScreen;
	m_wndTrackControl.ScreenToClient(&point);

	if (!m_wndTrackControl.GetTrackColumn()->GetRect().PtInRect(point))
		return;


	int nMarker = m_wndTrackControl.GetMarkers()->HitTest(point);
	
	CMenu menu;
	menu.LoadMenu(IDR_MENU_POPUP);
	

	if (nMarker != -1)
	{
		int nResult = TrackPopupMenu(menu.GetSubMenu(1)->GetSafeHmenu(), TPM_RETURNCMD, ptScreen.x, ptScreen.y, 0, m_hWnd, 0);

		if (nResult == ID_HEADER_REMOVEMARKER)
		{
			m_wndTrackControl.GetMarkers()->RemoveAt(nMarker);
		}
		if (nResult == ID_HEADER_DELETEALLMARKERS)
		{
			m_wndTrackControl.GetMarkers()->RemoveAll();
		}
	}
	else
	{
		int nResult = TrackPopupMenu(menu.GetSubMenu(0)->GetSafeHmenu(), TPM_RETURNCMD, ptScreen.x, ptScreen.y, 0, m_hWnd, 0);

		if (nResult == ID_HEADER_ADDMARKER)
		{
			CString strCaption;
			strCaption.Format(_T("%d"), 1 + m_wndTrackControl.GetMarkers()->GetCount());

			m_wndTrackControl.GetMarkers()->Add(m_wndTrackControl.TrackToPosition(point.x), strCaption);
		}

	}


}

void CTrackControlDlg::OnSnapToBlocks() 
{
m_wndTrackControl.m_bSnapToBlocks ^= 1;
	
}

void CTrackControlDlg::OnUpdateSnapToBlocks(CCmdUI* pCmdUI) 
{
pCmdUI->SetCheck(m_wndTrackControl.m_bSnapToBlocks ? 1 : 0);	
	
}

void CTrackControlDlg::OnSnapToMarkers() 
{
	m_wndTrackControl.m_bSnapToMarkers ^= 1;
	
}

void CTrackControlDlg::OnUpdateSnapToMarkers(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.m_bSnapToMarkers ? 1 : 0);	
}

void CTrackControlDlg::OnAllowblockmove() 
{
	m_wndTrackControl.m_bAllowBlockMove ^= 1;
	
}

void CTrackControlDlg::OnUpdateAllowblockmove(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.m_bAllowBlockMove);
	
}

void CTrackControlDlg::OnAllowblockscale() 
{
	m_wndTrackControl.m_bAllowBlockScale ^= 1;
	
}

void CTrackControlDlg::OnUpdateAllowblockscale(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.m_bAllowBlockScale);
	
}

void CTrackControlDlg::OnScaleOnResize() 
{
	m_wndTrackControl.m_bScaleOnResize ^= 1;
	
}

void CTrackControlDlg::OnUpdateScaleOnResize(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.m_bScaleOnResize);	
}

void CTrackControlDlg::OnAllowblockRemove() 
{
	m_wndTrackControl.m_bAllowBlockRemove ^= 1;
	
}

void CTrackControlDlg::OnUpdateAllowblockRemove(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.m_bAllowBlockRemove);
}



void CTrackControlDlg::OnAllowRowResize() 
{
	m_wndTrackControl.m_bFreeHeightMode = !m_wndTrackControl.m_bFreeHeightMode;
	
}

void CTrackControlDlg::OnUpdateAllowRowResize(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.m_bFreeHeightMode ? 1 : 0);
	
}

void CTrackControlDlg::OnShowWorkarea() 
{
	m_wndTrackControl.m_bShowWorkArea = !m_wndTrackControl.m_bShowWorkArea;
	m_wndTrackControl.RedrawControl();
}

void CTrackControlDlg::OnUpdateShowWorkarea(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndTrackControl.m_bShowWorkArea ? 1 : 0);
}


void CTrackControlDlg::OnTrackTimeLineChanged(NMHDR* /*pNotifyStruct*/, LRESULT * /*result*/)
{
	TRACE(_T("TimeLine Changed\n"));
}

void CTrackControlDlg::OnTrackMarkerChanged(NMHDR* /*pNotifyStruct*/, LRESULT * /*result*/)
{
	TRACE(_T("Marker Changed\n"));
}

void CTrackControlDlg::OnTrackBlockChanged(NMHDR* /*pNotifyStruct*/, LRESULT * /*result*/)
{
	TRACE(_T("Block Changed\n"));
}

void CTrackControlDlg::OnTrackSelectedBlocksChanged(NMHDR* /*pNotifyStruct*/, LRESULT * /*result*/)
{
	TRACE(_T("Selected Blocks Changed\n"));
}

