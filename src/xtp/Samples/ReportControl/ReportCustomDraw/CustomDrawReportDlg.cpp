// CustomDrawReportDlg.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomDrawReport.h"
#include "CustomDrawReportDlg.h"
#include "MessageRecord.h"
#include "XTPCustomDrawReportPaintManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomDrawReportDlg dialog

CCustomDrawReportDlg::CCustomDrawReportDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CCustomDrawReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomDrawReportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nDrawingMethod = 1;
}

void CCustomDrawReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomDrawReportDlg)
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCustomDrawReportDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CCustomDrawReportDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_USE_DRAWFRAMECONTROL, OnUseDrawframecontrol)
	ON_COMMAND(IDM_USE_DRAWSTATE, OnUseDrawstate)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomDrawReportDlg message handlers

enum
{
	REPORTCOLUMN_NAME,
	REPORTCOLUMN_ATTR1,
	REPORTCOLUMN_ATTR2,
	REPORTCOLUMN_ATTR3,
};

const int COLUMN_MAIL_ICON   =  0;
const int COLUMN_CHECK_ICON  =  2;

BOOL CCustomDrawReportDlg::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//
	// create main menu.
	//
	CMenu* pMenu = GetMenu();
	if(pMenu)
	{
		CMenu* pSubMenu = pMenu->GetSubMenu(0);
		if(pSubMenu)
			pSubMenu->CheckMenuRadioItem(IDM_USE_DRAWFRAMECONTROL, IDM_USE_DRAWSTATE, IDM_USE_DRAWFRAMECONTROL, MF_BYCOMMAND);
	}

	//
	// create the image lists used by the report control.
	//

	if (!m_ilControls.Create(14, 14, ILC_COLOR24 | ILC_MASK, 0, 1))
		return -1;

	//
	// load the image bitmap and set the image list for the 
	// report control.
	//

	CBitmap bitmap;
	VERIFY(bitmap.LoadBitmap(IDB_CONTROLS));
	m_ilControls.Add(&bitmap, RGB(255, 0, 255));	

	//
	//  Add sample columns
	//

	m_wndReportCtrl.AddColumn(new CXTPReportColumn(REPORTCOLUMN_NAME, _T("Name"), 150));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(REPORTCOLUMN_ATTR1, _T("Attribute 1"), 150));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(REPORTCOLUMN_ATTR2, _T("Attribute 2"), 150));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(REPORTCOLUMN_ATTR3, _T("Attribute 3"), 150));
	m_wndReportCtrl.GetColumns()->GetAt(REPORTCOLUMN_ATTR3)->SetAlignment(DT_VCENTER);

	//
	//  Add sample records in tree
	//

	CString strName;
	CString strProgress;
	for(int i = 0; i < 10; i++)
	{
		strName.Format(_T("Parameter %d"), i);
		strProgress.Format(_T("Progress %d: (%d%%)"), i, 0);
		m_wndReportCtrl.AddRecord(new CMessageRecord(strName, 4, i, 4, 1 << (i & 3), strProgress, RGB(0, 0, 100), 15, 0, 100, i + 1, 0));
	}

	//
	// define style attributes for the report control.
	//

	m_wndReportCtrl.GetColumns()->Find(REPORTCOLUMN_NAME)->SetTreeColumn(TRUE);

	CXTPCustomDrawReportPaintManager* pPaintManager = new CXTPCustomDrawReportPaintManager(this);

	m_wndReportCtrl.SetPaintManager(pPaintManager);

	//
	// after columns and data have been added call Populate to 
	// populate all of the date for the control.
	//

	m_wndReportCtrl.Populate();

	m_wndReportCtrl.EnableDragDrop(_T("CustomDrawReport"), xtpReportAllowDrag | xtpReportAllowDrop);


	// Set control resizing.
	SetResize(IDC_REPORTCTRL, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDCANCEL, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);

	// Load window placement
	LoadPlacement(_T("CCustomDrawReportDlg"));

	// start timer
	SetTimer(0, 250, NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomDrawReportDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTPResizeDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCustomDrawReportDlg::OnPaint() 
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
HCURSOR CCustomDrawReportDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCustomDrawReportDlg::OnDestroy() 
{
	CXTPResizeDialog::OnDestroy();


	// Save window placement
	SavePlacement(_T("CCustomDrawReportDlg"));

}

unsigned int CCustomDrawReportDlg::GetControlsNumber(CXTPReportRecordItem* pItem)
{
	if(pItem && pItem->GetIndex() == 1)
		return ((CMessageRecordItemCheckGroup*)pItem)->GetControlsNumber();
	else if(pItem && pItem->GetIndex() == 2)
		return ((CMessageRecordItemRadioGroup*)pItem)->GetControlsNumber();

	return 0;
}

unsigned int CCustomDrawReportDlg::GetControlsNumber(CXTPReportRow* pRow)
{
	if(!pRow)
		return 0;

	unsigned int unControls = 0;

	CXTPReportRecordItem* pItem = pRow->GetRecord()->GetItem(1);
	unControls = GetControlsNumber(pItem);
	pItem = pRow->GetRecord()->GetItem(2);
	unControls = max(unControls, GetControlsNumber(pItem));

	return unControls;
}

int CCustomDrawReportDlg::GetRowHeight(CDC* /*pDC*/, CXTPReportRow* pRow)
{
	unsigned int unControls = 0;
	CXTPReportRecordItem* pItem = pRow->GetRecord()->GetItem(1);
	if(pItem)
		unControls = max(unControls, ((CMessageRecordItemCheckGroup*)pItem)->GetControlsNumber());
	pItem = pRow->GetRecord()->GetItem(2);
	if(pItem)
		unControls = max(unControls, ((CMessageRecordItemRadioGroup*)pItem)->GetControlsNumber());

	if (!pRow->IsGroupRow())
	{
		return unControls * 15 + (m_wndReportCtrl.GetPaintManager()->IsGridVisible(FALSE) ? 1 : 0);
	}

	if (m_wndReportCtrl.GetPaintManager()->m_bShadeGroupHeadings)
		return unControls * 15 + 6;

	return unControls * 15 + 16;
}

BOOL CCustomDrawReportDlg::DrawItem(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* /*pMetrics*/)
{
	if(pDrawArgs->pColumn->GetIndex() != REPORTCOLUMN_ATTR1 && pDrawArgs->pColumn->GetIndex() != REPORTCOLUMN_ATTR2)
		return FALSE;

	CRect rc = pDrawArgs->pRow->GetItemRect(pDrawArgs->pItem);
	rc.left += 5;
    rc.right = rc.left + 14;
    rc.bottom = rc.top + 14;
	for(unsigned int i = 0; i < GetControlsNumber(pDrawArgs->pItem); i++)
	{
		UINT unFlags;
		UINT unIconId;
		CString strText;

		if(pDrawArgs->pColumn->GetIndex() == 1)
		{
			strText.Format(_T("%s%d"), _T("T"), i + 1);
            unFlags = DFCS_BUTTONCHECK;
			CMessageRecordItemCheckGroup* pRecord = (CMessageRecordItemCheckGroup*)pDrawArgs->pItem;
			if(pRecord->GetValue() & (1 << i))
			{
				unFlags |= DFCS_CHECKED;
                unIconId = 1;
			}
			else
			{
				unFlags &= ~DFCS_CHECKED;
                unIconId = 0;
			}
		}
		else
		{
			strText.Format(_T("%s%d"), _T("V"), i + 1);
            unFlags = DFCS_BUTTONRADIO;
			CMessageRecordItemRadioGroup* pRecord = (CMessageRecordItemRadioGroup*)pDrawArgs->pItem;
			if(pRecord->GetValue() & (1 << i))
			{
				unFlags |= DFCS_CHECKED;
                unIconId = 3;
			}
			else
			{
				unFlags &= ~DFCS_CHECKED;
                unIconId = 2;
			}
		}
		if(m_nDrawingMethod == 1)
			::DrawFrameControl(pDrawArgs->pDC->GetSafeHdc(), rc, DFC_BUTTON, unFlags);
		else
			m_ilControls.Draw(pDrawArgs->pDC, unIconId, rc.TopLeft(), ILD_NORMAL);
        TextOut(pDrawArgs->pDC->GetSafeHdc(), rc.left + 20, rc.top, strText, strText.GetLength());
        rc.top += 15;
        rc.bottom += 15;
	}

	return TRUE;
}
BOOL CCustomDrawReportDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		CPoint pt = pMsg->pt;
		m_wndReportCtrl.ScreenToClient(&pt);
		CXTPReportRow* pRow = m_wndReportCtrl.HitTest(pt);
		if(pRow)
		{
			CXTPReportRecordItem* pItem = pRow->HitTest(pt);
			if(pItem)
			{
				if(pItem->GetIndex() < 1)
					return 0;
				unsigned int unControls = GetControlsNumber(pItem);
				if(unControls == 0)
					return 0;
				CRect rc = pRow->GetItemRect(pItem);
				rc.right = rc.left + 14 + 25;
				rc.bottom = rc.top + 14;
				for(unsigned int i = 0; i < unControls; i++)
				{
					if(rc.PtInRect(pt))
					{
						if(pItem->GetIndex() == 1)
						{
							((CMessageRecordItemCheckGroup*)pItem)->ToggleBit(i);
						}
						else
						{
							((CMessageRecordItemRadioGroup*)pItem)->SetValue(1 << i);
						}
					}
					rc.OffsetRect(0, 15);
				}
			}
		}
	}

	return CXTPResizeDialog::PreTranslateMessage(pMsg);
}

void CCustomDrawReportDlg::OnUseDrawframecontrol() 
{
	if(m_nDrawingMethod == 1)
		return;
	m_nDrawingMethod = 1;
	CMenu* pMenu = GetMenu();
	if(pMenu)
	{
		CMenu* pSubMenu = pMenu->GetSubMenu(0);
		if(pSubMenu)
			pSubMenu->CheckMenuRadioItem(IDM_USE_DRAWFRAMECONTROL, IDM_USE_DRAWSTATE, IDM_USE_DRAWFRAMECONTROL, MF_BYCOMMAND);
	}
	m_wndReportCtrl.RedrawControl();
}

void CCustomDrawReportDlg::OnUseDrawstate() 
{
	if(m_nDrawingMethod == 2)
		return;
	m_nDrawingMethod = 2;
	CMenu* pMenu = GetMenu();
	if(pMenu)
	{
		CMenu* pSubMenu = pMenu->GetSubMenu(0);
		if(pSubMenu)
			pSubMenu->CheckMenuRadioItem(IDM_USE_DRAWFRAMECONTROL, IDM_USE_DRAWSTATE, IDM_USE_DRAWSTATE, MF_BYCOMMAND);
	}
	m_wndReportCtrl.RedrawControl();
}

void CCustomDrawReportDlg::OnTimer(UINT_PTR nIDEvent)
{
	// advance progresses
	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CXTPReportRecordItemProgress* pItem = DYNAMIC_DOWNCAST(CXTPReportRecordItemProgress, m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(REPORTCOLUMN_ATTR3));
		pItem->StepProgressPos();
		int nLower, nUpper;
		pItem->GetProgressRange(nLower, nUpper);
		if(pItem->GetProgressPos() == nLower || pItem->GetProgressPos() == nUpper)
			pItem->SetProgressStep(-pItem->GetProgressStep());
		CString strProgress;
		strProgress.Format(_T("Progress %d: (%d%%)"), i, pItem->GetProgressPosPercent());
		pItem->SetValue(strProgress);		
	}

	m_wndReportCtrl.RedrawControl();

	CXTPResizeDialog::OnTimer(nIDEvent);
}
