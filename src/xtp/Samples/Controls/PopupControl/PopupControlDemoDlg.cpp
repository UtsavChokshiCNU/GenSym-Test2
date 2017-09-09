// PopupControlDemoDlg.cpp : implementation file
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
#include "PopupControlDemo.h"
#include "PopupControlDemoDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_POPUP_CLOSE (-1)
#define ID_GOTO_SITE (-2)


/////////////////////////////////////////////////////////////////////////////
// CPopupControlDemoDlg dialog

CPopupControlDemoDlg::CPopupControlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopupControlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopupControlDemoDlg)
	m_nTheme = -1;
	m_nAnimStyle = -1;
	m_uAnimDelay = 0;
	m_uShowDelay = 0;
	m_bAllowMove = FALSE;
	m_nTrans = 0;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ptPopup = CPoint(-1,-1);
}

CPopupControlDemoDlg::~CPopupControlDemoDlg()
{
	while (!m_lstPopupControl.IsEmpty()) 
	{
		delete m_lstPopupControl.RemoveTail();
	}
}

void CPopupControlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupControlDemoDlg)
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENT, m_wndSlider);
	DDX_Slider(pDX, IDC_SLIDER_TRANSPARENT, m_nTrans);
	DDX_CBIndex(pDX, IDC_COMBO_ANIMATION, m_nAnimStyle);
	DDX_Text(pDX, IDC_EDIT_ANIMATIONDELAY, m_uAnimDelay);
	DDV_MinMaxUInt(pDX, m_uAnimDelay, 0, 60000);
	DDX_Text(pDX, IDC_EDIT_SHOWDELAY, m_uShowDelay);
	DDV_MinMaxUInt(pDX, m_uShowDelay, 0, 600000);
	DDX_Check(pDX, IDC_CHECK_ALLOWMOVE, m_bAllowMove);
	DDX_Text(pDX, IDC_TXT_TRANS, m_strTrans);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST_THEME, m_wndListBox);
}

BEGIN_MESSAGE_MAP(CPopupControlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CPopupControlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW, OnButtonShow)
	ON_CBN_SELCHANGE(IDC_COMBO_ANIMATION, OnSelchangeComboAnimation)
	ON_EN_CHANGE(IDC_EDIT_ANIMATIONDELAY, OnChangeEditAnimationdelay)
	ON_EN_CHANGE(IDC_EDIT_SHOWDELAY, OnChangeEditShowdelay)
	ON_BN_CLICKED(IDC_CHECK_ALLOWMOVE, OnCheckAllowMove)
	//}}AFX_MSG_MAP

	ON_MESSAGE(XTPWM_POPUPCONTROL_NOTIFY, OnPopUpNotify)
	ON_WM_HSCROLL()
	ON_LBN_SELCHANGE(IDC_LIST_THEME, OnLbnSelchangeListTheme)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupControlDemoDlg message handlers

BOOL CPopupControlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	// set slider transparency range.
	m_wndSlider.SetRange(0, 255, TRUE);

	// Fill list box with available popup styles.
	AddListItem(_T("Office 2000 Style"), xtpPopupThemeOffice2000);
	AddListItem(_T("Office XP Style"), xtpPopupThemeOfficeXP);
	AddListItem(_T("Office 2003 Style"), xtpPopupThemeOffice2003);
	AddListItem(_T("Office 2007 Style"), xtpPopupThemeOffice2007);
	AddListItem(_T("MSN Messenger Style"), xtpPopupThemeMSN);
	AddListItem(_T("Custom Blue Style"), xtpPopupThemeBlue);
	AddListItem(_T("Custom Black Style"), xtpPopupThemeBlack);
	AddListItem(_T("Custom Green Style"), xtpPopupThemeGreen);
	AddListItem(_T("Custom Red Style"), xtpPopupThemeRed);
	AddListItem(_T("Custom Tooltip Style"), xtpPopupThemeTooltip);
	AddListItem(_T("Custom Rich Text Style"), xtpPopupThemeRTF);
	AddListItem(_T("Custom XML Markup Style"), xtpPopupThemeMarkup);
	AddListItem(_T("Custom Image Layer"), xtpPopupThemeLayer);
	AddListItem(_T("Custom Codejock Message"), xtpPopupThemeCodejock, TRUE);

	OnButtonShow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPopupControlDemoDlg::AddListItem(LPCTSTR lpszItem, int nTheme, BOOL bSelect)
{
	int nIndex = m_wndListBox.AddString(lpszItem);
	m_wndListBox.SetItemData(nIndex, 100 + nTheme);

	if (bSelect)
	{
		m_wndListBox.SetCurSel(nIndex);
		OnLbnSelchangeListTheme();
	}
}

void CPopupControlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPopupControlDemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPopupControlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPopupControlDemoDlg::FindBestPosition(CXTPPopupControl* pPopup, CSize szPopup)
{
	if (m_ptPopup != CPoint(-1, -1)) 
		pPopup->SetPopupPos(m_ptPopup);

	CPoint ptPopup = pPopup->GetPopupPos();

	CRect rcActivePopup(CPoint(ptPopup.x - szPopup.cx, ptPopup.y - szPopup.cy), szPopup);

	
	BOOL bIntersect = FALSE;
	do 
	{
		bIntersect = FALSE;
		POSITION pos = m_lstPopupControl.GetHeadPosition();

		while(pos)
		{
			CXTPPopupControl* pPopup = m_lstPopupControl.GetNext(pos);
			if (pPopup)
			{
				CRect rcPopup(CPoint(pPopup->GetPopupPos().x - pPopup->GetPopupSize().cx, 
					pPopup->GetPopupPos().y - pPopup->GetPopupSize().cy), pPopup->GetPopupSize());

				if (CRect().IntersectRect(rcPopup, rcActivePopup))
				{
					ptPopup.y =  rcPopup.top;
					rcActivePopup = CRect(CPoint(ptPopup.x - szPopup.cx, ptPopup.y - szPopup.cy), szPopup);
					bIntersect = TRUE;
				}
			}
		}
	} while (bIntersect);

	pPopup->SetPopupPos(ptPopup);
}


void CPopupControlDemoDlg::OnButtonShow()
{
	UpdateData();
	EnableItems(FALSE);

	CXTPPopupControl* pPopup = new CXTPPopupControl();
	pPopup->SetTransparency(m_nTrans);
	pPopup->AllowMove(m_bAllowMove);
	pPopup->SetAnimateDelay(m_uAnimDelay);
	pPopup->SetPopupAnimation((XTPPopupAnimation)m_nAnimStyle);
	pPopup->SetShowDelay(m_uShowDelay);

	if (m_nTheme == xtpPopupThemeLayer)
	{
		UINT nCommands[] = {100};
		VERIFY(pPopup->GetImageManager()->SetIcons(_T("IDB_PUZZLE"), nCommands, 1, CSize(0, 0)));

		pPopup->SetBackgroundBitmap(nCommands[0]);
		pPopup->SetPopupSize(m_sizePopup);
		pPopup->ShowModal(this);

		SAFE_DELETE(pPopup);
		EnableItems(TRUE);
	}
	else
	{
		SetTheme(pPopup);

		pPopup->SetPopupSize(m_sizePopup);
		FindBestPosition(pPopup, m_sizePopup);
		pPopup->Show(this);

		m_lstPopupControl.AddTail(pPopup);
	}
}

void CPopupControlDemoDlg::EnableItems(BOOL bEnable)
{
	CWnd* pWnd = GetWindow(GW_CHILD);
	while (pWnd)
	{
		pWnd->EnableWindow(bEnable);
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}

	if (m_nTheme != xtpPopupThemeLayer)
	{
		GetDlgItem(IDC_BUTTON_SHOW)->EnableWindow(TRUE);
	}
}

void CPopupControlDemoDlg::SetDefaults()
{
	switch (m_nTheme)
	{
		case xtpPopupThemeOffice2000:
		case xtpPopupThemeOfficeXP:
			{
				m_nAnimStyle = xtpPopupAnimationFade;
				m_uAnimDelay = 500;
				m_uShowDelay = 3000;
				m_nTrans = 255;
				m_sizePopup = CSize(170,130);
			}
			break;
		case xtpPopupThemeOffice2003:
		case xtpPopupThemeOffice2007:
			{
				m_nAnimStyle = xtpPopupAnimationFade;
				m_uAnimDelay = 500;
				m_uShowDelay = 3000;
				m_nTrans = 200;
				m_sizePopup = CSize(329,74);
			}
			break;
		case xtpPopupThemeMSN:
		case xtpPopupThemeBlue:
		case xtpPopupThemeBlack:
		case xtpPopupThemeGreen:
		case xtpPopupThemeRed:
			{
				m_nAnimStyle = xtpPopupAnimationSlide;
				m_uAnimDelay = 350;
				m_uShowDelay = 3000;
				m_nTrans = 255;
				m_sizePopup = CSize(170,130);
			}
			break;
		case xtpPopupThemeTooltip:
			{
				m_nAnimStyle = xtpPopupAnimationUnfold;
				m_uAnimDelay = 500;
				m_uShowDelay = 3000;
				m_nTrans = 255;
				m_sizePopup = CSize(220,90);
			}
			break;
		case xtpPopupThemeRTF:
			{
				m_nAnimStyle = xtpPopupAnimationSlide;
				m_uAnimDelay = 250;
				m_uShowDelay = 7500;
				m_nTrans = 255;
				m_sizePopup = CSize(0,0);
			}
			break;
		case xtpPopupThemeMarkup:
			{
				m_nAnimStyle = xtpPopupAnimationSlide;
				m_uAnimDelay = 500;
				m_uShowDelay = 2000;
				m_nTrans = 200;
				m_sizePopup = CSize(0,0);
			}
			break;
		case xtpPopupThemeLayer:
			{
				m_nAnimStyle = xtpPopupAnimationFade;
				m_uAnimDelay = 500;
				m_uShowDelay = 1500;
				m_nTrans = 255;
				m_sizePopup = CSize(156,161);
			}
			break;
		case xtpPopupThemeCodejock:
			{
				m_nAnimStyle = xtpPopupAnimationSlide;
				m_uAnimDelay = 250;
				m_uShowDelay = 2500;
				m_nTrans = 255;
				m_sizePopup = CSize(250,200);
			}
			break;
	}

	m_strTrans.Format(_T("Transparency: %i"), m_nTrans);
	UpdateData(FALSE);
}

void CPopupControlDemoDlg::SetDefaultTheme(CXTPPopupControl* pPopup)
{
	pPopup->RemoveAllItems();

	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(25, 5, m_sizePopup.cx, 19), _T("Word 2000 Theme")));
	pItemText->SetTextAlignment(DT_LEFT);
	pItemText->CalculateHeight();
	pItemText->CalculateWidth();
	pItemText->SetHyperLink(FALSE);
	pItemText->SetTextColor(RGB(255,255,255));

	CXTPPopupItem * pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(4, 4, 20, 19)));
	pItemIcon->SetIcon(IDI_WORD2000 ,xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(14, 40, 20, 49)));
	pItemIcon->SetIcons(IDB_LOGOOFFICE, 0, xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(109, 55, 132, 78)));
	pItemIcon->SetIcon(IDI_OPEN, xtpPopupItemIconNormal);
	pItemIcon->CenterIcon();
	pItemIcon->SetButton(TRUE);

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(133, 55, 156, 78)));
	pItemIcon->SetIcon(IDI_SAVE, xtpPopupItemIconNormal);
	pItemIcon->CenterIcon();
	pItemIcon->SetButton(TRUE);

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEOFFICE, 0,
		xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(104, 30, m_sizePopup.cx, 45), _T("Parameters")));

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(65, 90, 105, 110), _T("OK")));
	pItemText->SetButton(TRUE);
	pItemText->SetTextAlignment(DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pItemText->SetHyperLink(FALSE);
	pItemText->SetID(IDOK);

	pPopup->SetTheme(xtpPopupThemeOffice2000);
	pPopup->RedrawControl();
}

void CPopupControlDemoDlg::SetOfficeXPTheme(CXTPPopupControl* pPopup)
{
	pPopup->RemoveAllItems();

	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(25, 5, m_sizePopup.cx, 19), _T("Word XP Theme")));
	pItemText->SetTextAlignment(DT_LEFT);
	pItemText->CalculateHeight();
	pItemText->CalculateWidth();
	pItemText->SetHyperLink(FALSE);
	pItemText->SetTextColor(RGB(255,255,255));

	CXTPPopupItem * pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(4, 4, 20, 19)));
	pItemIcon->SetIcon(IDI_WORD2000, xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(14, 40, 20, 49)));
	pItemIcon->SetIcons(IDB_LOGOOFFICE, 0, xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(109, 55, 132, 78)));
	pItemIcon->SetIcon(IDI_OPEN, xtpPopupItemIconNormal);
	pItemIcon->CenterIcon();
	pItemIcon->SetButton(TRUE);

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(133, 55, 156, 78)));
	pItemIcon->SetIcon(IDI_SAVE, xtpPopupItemIconNormal);
	pItemIcon->CenterIcon();
	pItemIcon->SetButton(TRUE);

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEOFFICE, 0,
		xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(104, 30, m_sizePopup.cx, 45), _T("Parameters")));

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(65, 90, 105, 110), _T("OK")));
	pItemText->SetButton(TRUE);
	pItemText->SetTextAlignment(DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pItemText->SetHyperLink(FALSE);
	pItemText->SetID(IDOK);

	pPopup->SetTheme(xtpPopupThemeOfficeXP);
	pPopup->RedrawControl();

}

void CPopupControlDemoDlg::SetMSNTheme(CXTPPopupControl* pPopup)
{
	pPopup->RemoveAllItems();

	// add caption icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(7, 6, 20, 19)));
	pItemIcon->SetIcons(IDB_CAPTIONMSN, 0, xtpPopupItemIconNormal);
	pItemIcon->SetButton(FALSE);

	// add caption text.
	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(25, 6, m_sizePopup.cx-25, 19), _T("Popup Control Demo")));

	pItemText->SetTextAlignment(DT_LEFT);
	pItemText->CalculateHeight();
	pItemText->CalculateWidth();
	pItemText->SetHyperLink(FALSE);

	// add close button
	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(m_sizePopup.cx - 19, 6, m_sizePopup.cx - 6, 19)));
	pItemIcon->SetIcons(IDB_CLOSEMSN, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	// add options link text.
	int y = 27;
	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(m_sizePopup.cx - 66, y, m_sizePopup.cx - 10, 25), _T("Options")));

	pItemText->SetTextAlignment(DT_RIGHT);
	pItemText->FitToContent();

	// add message text.
	CSize sizeText = pItemText->GetRect().Size();
	y += sizeText.cy + 5;

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(5, y, m_sizePopup.cx - 5, 25), _T("Please visit our website for additional product information including registration details.")));

	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetID(ID_GOTO_SITE);
	pItemText->FitToContent();

	// add MSN logo.
	sizeText = pItemText->GetRect().Size();
	y += sizeText.cy + 5;

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(m_sizePopup.cx - 55, y, m_sizePopup.cx - 10, y + 18)));
	pItemIcon->SetIcons(IDB_LOGOMSN, 0, xtpPopupItemIconNormal);

	// adjust window height.
	m_sizePopup.cy = y + 18 + 10;

	pPopup->SetTheme(xtpPopupThemeMSN);
	pPopup->RedrawControl();
}

void CPopupControlDemoDlg::SetOffice2003Theme(CXTPPopupControl* pPopup)
{
	pPopup->RemoveAllItems();

	// add text items.
	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(46, 16, 270, 41), _T("Peter Parker")));
	pItemText->SetBold(TRUE);

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(46, 29, 270, 54), _T("RE: Week reports 12/04/2004 - 17/04/2004")));
	pItemText->SetHyperLink(FALSE);

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(46, 42, 270, 92), _T("See comments below.\nThanks.")));
	pItemText->SetHyperLink(FALSE);

	pItemText->SetTextColor(RGB(0, 61, 178));
	pItemText->SetTextAlignment(DT_LEFT|DT_WORDBREAK);

	// letter icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(5, 12, 17, 24)));
	pItemIcon->SetIcon(IDI_LETTER);
	pItemIcon->SetButton(FALSE);

	// close icon.
	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(308, 14, 324, 30)));
	pItemIcon->SetIcon(IDI_CLOSE);
	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	// flag icon.
	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(4, 49, 20, 65)));
	pItemIcon->SetIcon(IDI_FLAG);
	pItemIcon->SetButton(TRUE);

	// cross icon.
	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(23, 49, 39, 65)));
	pItemIcon->SetIcon(IDI_CROSS);
	pItemIcon->SetButton(TRUE);

	pPopup->SetTheme(xtpPopupThemeOffice2003);
	pPopup->RedrawControl();
}

void CPopupControlDemoDlg::SetOffice2007Theme(CXTPPopupControl* pPopup)
{
	SetOffice2003Theme(pPopup);

	pPopup->SetTheme(xtpPopupThemeOffice2007);
	pPopup->RedrawControl();
}

void CPopupControlDemoDlg::SetColorTheme(CXTPPopupControl* pPopup, CXTPPopupPaintManager* pPaintManager)
{
	pPopup->RemoveAllItems();

	// add caption text.
	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(5, 0, m_sizePopup.cx - 5, 25), _T("Message for You")));
	pItemText->SetTextAlignment(DT_LEFT|DT_SINGLELINE| DT_VCENTER);
	pItemText->SetBold(TRUE);
	pItemText->SetHyperLink(FALSE);
	pItemText->SetTextColor(RGB(255,255,255));

	// add close button.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(m_sizePopup.cx - 19, 6, m_sizePopup.cx - 6, 19)));
	pItemIcon->SetIcons(IDB_CLOSEMSN, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	// add letter icon.
	int y = 32;

	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(12, y, 44, y + 32)));

	pItemIcon->SetIcon(IDI_LETTER2);

	// add message text.
	y += 32 + 5;

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(10, y, m_sizePopup.cx - 10, 25), _T("Please visit our website for additional product information including registration details.")));

	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetID(ID_GOTO_SITE);
	pItemText->FitToContent();

	// add more link text.
	CSize sizeText = pItemText->GetRect().Size();
	y += sizeText.cy + 5;

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(m_sizePopup.cx - 71, y, m_sizePopup.cx - 15, 25), _T("more...")));

	pItemText->SetTextAlignment(DT_RIGHT);
	pItemText->FitToContent();

	// adjust popup height.
	sizeText = pItemText->GetRect().Size();
	m_sizePopup.cy = y + sizeText.cy + 10;

	pPopup->SetTheme(pPaintManager);
	pPopup->RedrawControl();
}

void CPopupControlDemoDlg::SetTooltipTheme(CXTPPopupControl* pPopup)
{
	pPopup->RemoveAllItems();

	pPopup->AddItem(new CXTPPopupItem(
		CRect(0, 0, 220, 90), NULL, RGB(255,255,225), 0));

	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(20, 30, 200, 100), _T("Please visit our website for additional product information including registration details.")));
	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetID(ID_GOTO_SITE);

	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(5, 0, m_sizePopup.cx, 25), _T("Codejock Information")));
	pItemText->SetTextAlignment(DT_LEFT|DT_SINGLELINE| DT_VCENTER);
	pItemText->SetBold(TRUE);
	pItemText->SetHyperLink(FALSE);

	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(220 - 20, 2, 220 - 2, 2 + 18)));
	pItemIcon->SetIcons(IDB_CLOSETOOLTIP, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	pPopup->SetTheme(xtpPopupThemeCustom);
	pPopup->RedrawControl();
}

void CPopupControlDemoDlg::SetRTFTheme(CXTPPopupControl* pPopup) 
{
	pPopup->RemoveAllItems();

	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(new CXTPPopupItem(CRect(8, 12, 500, 130)));
	pItemText->SetRTFText(IDR_MAINFRAME);
	pItemText->FitToContent();
	CSize sizePopup = pItemText->GetRect().Size();

	// close icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(sizePopup.cx + 2, 10, sizePopup.cx + 2 + 16, 10 + 16)));

	pPopup->GetImageManager()->SetIcon(IDI_POPUP_CLOSE, IDI_POPUP_CLOSE);
	pItemIcon->SetIconIndex(IDI_POPUP_CLOSE);

	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(XTP_ID_POPUP_CLOSE);

	m_sizePopup.cx = sizePopup.cx + 20;
	m_sizePopup.cy = sizePopup.cy + 20;

	pPopup->SetTheme(xtpPopupThemeOffice2003);
	pPopup->RedrawControl();
}


#ifdef _XTP_INCLUDE_MARKUP

void CPopupControlDemoDlg::OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs)
{
	if (pSender->IsKindOf(MARKUP_TYPE(CXTPMarkupHyperlink)))
	{
		CXTPMarkupRun* pRun = (CXTPMarkupRun*)((CXTPMarkupHyperlink*)pSender)->GetInlines()->GetInline(0);
		
		CString strText = pRun->GetText();
		
		pArgs->SetHandled();
	}
}
#endif



void CPopupControlDemoDlg::SetMarkupTheme(CXTPPopupControl* pPopup) 
{
	pPopup->RemoveAllItems();

	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(new CXTPPopupItem(CRect(8, 12, 500, 130)));

	LPCTSTR lpszMarkup = 
		_T("<Grid VerticalAlignment='Center' HorizontalAlignment='Center'>")
		_T("    <Grid.ColumnDefinitions>")
		_T("        <ColumnDefinition/>")
		_T("        <ColumnDefinition/>")
		_T("        <ColumnDefinition/>")
		_T("        <ColumnDefinition/>")
		_T("    </Grid.ColumnDefinitions>")
		_T("    <Grid.RowDefinitions>")
		_T("        <RowDefinition/>")
		_T("        <RowDefinition/>")
		_T("        <RowDefinition/>")
		_T("        <RowDefinition/>")
		_T("        <RowDefinition/>")
		_T("        <RowDefinition/>")
		_T("     </Grid.RowDefinitions>")
		_T("    <Border Grid.Column='0' Grid.Row='0'><TextBlock><Hyperlink>FTSE 100</Hyperlink></TextBlock></Border>")
		_T("    <Border Grid.Column='0' Grid.Row='1'><TextBlock><Hyperlink>FTSE TechMark</Hyperlink></TextBlock></Border>")
		_T("    <Border Grid.Column='0' Grid.Row='2'><TextBlock><Hyperlink>Dow Jones</Hyperlink></TextBlock></Border>")
		_T("    <Border Grid.Column='0' Grid.Row='3'><TextBlock><Hyperlink>S&amp;P 500</Hyperlink></TextBlock></Border>")
		_T("    <Border Grid.Column='0' Grid.Row='4'><TextBlock><Hyperlink>Dollar</Hyperlink></TextBlock></Border>")
		_T("    <Border Grid.Column='0' Grid.Row='5'><TextBlock><Hyperlink>Euro</Hyperlink></TextBlock></Border>")
		_T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='0'><TextBlock TextAlignment='Right'>5,990.12</TextBlock></Border>")
		_T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='1'><TextBlock TextAlignment='Right'>804.10</TextBlock></Border>")
		_T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='2'><TextBlock TextAlignment='Right'>8,322.12</TextBlock></Border>")
		_T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='3'><TextBlock TextAlignment='Right'>860</TextBlock></Border>")
		_T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='4'><TextBlock TextAlignment='Right'>1.56</TextBlock></Border>")
		_T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='5'><TextBlock TextAlignment='Right'>1.59</TextBlock></Border>")
		_T("    <Border Grid.Column='2' Grid.Row='0'><TextBlock TextAlignment='Right' Foreground='Green'>+50.1</TextBlock></Border>")
		_T("    <Border Grid.Column='2' Grid.Row='1'><TextBlock TextAlignment='Right' Foreground='Red'>-0.4</TextBlock></Border>")
		_T("    <Border Grid.Column='2' Grid.Row='2'><TextBlock TextAlignment='Right' Foreground='Green'>+78</TextBlock></Border>")
		_T("    <Border Grid.Column='2' Grid.Row='3'><TextBlock TextAlignment='Right' Foreground='Green'>+15.43</TextBlock></Border>")
		_T("    <Border Grid.Column='2' Grid.Row='4'><TextBlock TextAlignment='Right' Foreground='Green'>+0.06</TextBlock></Border>")
		_T("    <Border Grid.Column='2' Grid.Row='5'><TextBlock TextAlignment='Right' Foreground='Red'>-0.11</TextBlock></Border>")
		_T("</Grid>");



	pItemText->SetMarkupText(lpszMarkup);
	pItemText->FitToContent();
	CSize sizePopup = pItemText->GetRect().Size();

	// close icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(sizePopup.cx + 10, 10, sizePopup.cx + 10 + 16, 10 + 16)));

	pPopup->GetImageManager()->SetIcon(IDI_POPUP_CLOSE, IDI_POPUP_CLOSE);
	pItemIcon->SetIconIndex(IDI_POPUP_CLOSE);

	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(XTP_ID_POPUP_CLOSE);

	m_sizePopup.cx = sizePopup.cx + 30;
	m_sizePopup.cy = sizePopup.cy + 20;

	pPopup->SetTheme(xtpPopupThemeOffice2003);
	pPopup->RedrawControl();

#ifdef _XTP_INCLUDE_MARKUP
	pPopup->GetMarkupContext()->AddHandler(CXTPMarkupHyperlink::m_pClickEvent,  CreateMarkupClassDelegate(this, &CPopupControlDemoDlg::OnHyperlinkClick));
#endif
}

void CPopupControlDemoDlg::SetCodejockTheme(CXTPPopupControl* pPopup) 
{
	pPopup->RemoveAllItems();

	// add caption text.
	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(5, 0, m_sizePopup.cx, 25), _T("Codejock Update Available")));

	pItemText->SetTextAlignment(DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	pItemText->SetBold(TRUE);
	pItemText->SetHyperLink(FALSE);
	pItemText->SetTextColor(RGB(0xff,0xff,0xff));

	int cy = 30;

	// add options link.
	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(15, cy, m_sizePopup.cx - 15, 25), _T("Options")));

	pItemText->SetTextAlignment(DT_RIGHT);
	pItemText->SetTextColor(RGB(0xb1,0xb1,0xb1));
	pItemText->FitToContent();
	pItemText->SetID(ID_GOTO_SITE);

	CSize sizeText = pItemText->GetRect().Size();
	cy += pItemText->GetRect().Size().cy + 25;

	// add message text.
	pItemText = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(15, cy, m_sizePopup.cx - 15, 25), _T("Click here to learn more about this update, and how you can download our latest product version.")));

	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetID(ID_GOTO_SITE);
	pItemText->FitToContent();

	sizeText = pItemText->GetRect().Size();
	cy += pItemText->GetRect().Size().cy + 25;

	// add codejock logo
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(10, cy, m_sizePopup.cx - 10, cy + 26)));

	pItemIcon->SetIcons(IDB_LOGOCODEJOCK, 0, xtpPopupItemIconNormal);

	// add close button
	pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(m_sizePopup.cx - 82, cy + 2, m_sizePopup.cx - 10, cy + 22)));

	pItemIcon->SetIcons(IDB_CLOSECODEJOCK, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	// set popup height to match contents.
	m_sizePopup.cy = cy + 36;

	pPopup->SetTheme(new CPopupThemeCodejock);
	pPopup->RedrawControl();
}

void CPopupControlDemoDlg::SetTheme(CXTPPopupControl* pPopup)
{
	switch (m_nTheme)
	{
	case xtpPopupThemeOffice2000:
		SetDefaultTheme(pPopup);
		break;
	case xtpPopupThemeOfficeXP:
		SetOfficeXPTheme(pPopup);
		break;
	case xtpPopupThemeOffice2003:
		SetOffice2003Theme(pPopup);
		break;
	case xtpPopupThemeOffice2007:
		SetOffice2007Theme(pPopup);
		break;
	case xtpPopupThemeMSN:
		SetMSNTheme(pPopup);
		break;
	case xtpPopupThemeBlue:
		SetColorTheme(pPopup, new CPopupThemeColorBlue);
		break;
	case xtpPopupThemeBlack:
		SetColorTheme(pPopup, new CPopupThemeColorBlack);
		break;
	case xtpPopupThemeGreen:
		SetColorTheme(pPopup, new CPopupThemeColorGreen);
		break;
	case xtpPopupThemeRed:
		SetColorTheme(pPopup, new CPopupThemeColorRed);
		break;
	case xtpPopupThemeTooltip:
		SetTooltipTheme(pPopup);
		break;
	case xtpPopupThemeRTF:
		SetRTFTheme(pPopup);
		break;
	case xtpPopupThemeMarkup:
		SetMarkupTheme(pPopup);
		break;
	case xtpPopupThemeCodejock:
		SetCodejockTheme(pPopup);
		break;
	}
}

void CPopupControlDemoDlg::OnCheckAllowMove()
{
	UpdateData();
}

void CPopupControlDemoDlg::OnSelchangeComboAnimation()
{
	UpdateData();
}

void CPopupControlDemoDlg::OnChangeEditAnimationdelay()
{
	UpdateData();
}

void CPopupControlDemoDlg::OnChangeEditShowdelay()
{
	UpdateData();
}

LRESULT CPopupControlDemoDlg::OnPopUpNotify(WPARAM wParam, LPARAM lParam)
{
	// process notify from popup wnd

	if(wParam == XTP_PCN_ITEMCLICK)
	{
		CXTPPopupItem* pItem = (CXTPPopupItem*)lParam;
		ASSERT(pItem);

		switch (pItem->GetID())
		{
		case ID_GOTO_SITE:
			::ShellExecute(NULL, _T("open"), _T("http://www.codejock.com/"), NULL, NULL, SW_SHOW);
			break;

		case ID_POPUP_CLOSE:
			pItem->GetPopupControl()->Close();
			break;
		}
	}
	else if(wParam == XTP_PCN_STATECHANGED)
	{
		CXTPPopupControl* pControl = (CXTPPopupControl*)lParam;
		ASSERT(pControl);

		switch (pControl->GetPopupState())
		{
			case xtpPopupStateClosed:
				{
					POSITION pos = m_lstPopupControl.Find(pControl);
					if (pos)
					{
						m_lstPopupControl.RemoveAt(pos);

						if (m_lstPopupControl.IsEmpty())
						{
							EnableItems(TRUE);				
						}

						delete pControl;
					}
				}
				break;
		}
	}
	else if (wParam == XTP_PCN_POSCHANGED)
	{
		CXTPPopupControl* pControl = (CXTPPopupControl*)lParam;
		ASSERT(pControl);
		
		m_ptPopup = pControl->GetPopupPos();
	}
		
	return TRUE;
}

void CPopupControlDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (nSBCode==TB_TOP || TB_BOTTOM || TB_LINEDOWN || TB_LINEUP || TB_PAGEDOWN || TB_PAGEUP || TB_THUMBTRACK || TB_THUMBPOSITION || TB_ENDTRACK)
	{
		UpdateData();
		m_strTrans.Format(_T("Transparency: %i"), m_nTrans);
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPopupControlDemoDlg::OnLbnSelchangeListTheme()
{
	DWORD_PTR dwData = m_wndListBox.GetItemData(m_wndListBox.GetCurSel());
	m_nTheme = int(dwData - 100);

	SetDefaults();
	UpdateData(FALSE);
}

// -------------------------------------------
// CPopupThemeColorBlue - Blue Color Custom Theme
// -------------------------------------------

void CPopupThemeColorBlue::DrawBackground(CDC* pDC, CXTPPopupControl* pControl, CRect rcClient)
{
	if (pControl->GetBackgroundBitmap() > 0)
	{
		CXTPPopupPaintManager::DrawBackground(pDC, pControl, rcClient);
		return;
	}

	pDC->FillSolidRect(rcClient, m_clrBackground);
	pDC->Draw3dRect(rcClient, m_clrFrame, m_clrFrame);
	rcClient.DeflateRect(5,25,5,5);

	pDC->FillSolidRect(rcClient, m_clrBackground2);
	pDC->Draw3dRect(rcClient, m_clrFrame2, m_clrFrame2);
}

void CPopupThemeColorBlue::RefreshMetrics()
{
	CXTPPopupPaintManager::RefreshMetrics();

	m_clrBackground.SetStandardValue(RGB(50,50,255));
	m_clrFrame.SetStandardValue(RGB(255,255,255));

	m_clrBackground2.SetStandardValue(RGB(70,70,250));
	m_clrFrame2.SetStandardValue(RGB(200,200,200));

	m_clrText = RGB(255,255,255);
}

// -------------------------------------------
// CPopupThemeColorBlack - Black Color Custom Theme
// -------------------------------------------

void CPopupThemeColorBlack::RefreshMetrics()
{
	CXTPPopupPaintManager::RefreshMetrics();

	m_clrBackground.SetStandardValue(RGB(10,10,10));
	m_clrFrame.SetStandardValue(RGB(255,255,255));

	m_clrBackground2.SetStandardValue(RGB(70,70,70));
	m_clrFrame2.SetStandardValue(RGB(200,200,200));

	m_clrText = RGB(255,255,255);
}

// -------------------------------------------
// CPopupThemeColorGreen - Green Color Custom Theme
// -------------------------------------------

void CPopupThemeColorGreen::RefreshMetrics()
{
	CXTPPopupPaintManager::RefreshMetrics();

	m_clrBackground.SetStandardValue(RGB(30,120,30));
	m_clrFrame.SetStandardValue(RGB(255,255,0));

	m_clrBackground2.SetStandardValue(RGB(70,130,70));
	m_clrFrame2.SetStandardValue(RGB(255,255,0));

	m_clrText = RGB(255,255,0);
}

// -------------------------------------------
// CPopupThemeColorRed - Red Color Custom Theme
// -------------------------------------------

void CPopupThemeColorRed::RefreshMetrics()
{
	CXTPPopupPaintManager::RefreshMetrics();

	m_clrBackground.SetStandardValue(RGB(255,50,50));
	m_clrFrame.SetStandardValue(RGB(255,255,0));

	m_clrBackground2.SetStandardValue(RGB(230,70,70));
	m_clrFrame2.SetStandardValue(RGB(255,255,0));

	m_clrText = RGB(255,255,255);
}

// -------------------------------------------
// CPopupThemeCodejock - Codejock Custom Theme
// -------------------------------------------

void CPopupThemeCodejock::DrawBackground(CDC* pDC, CXTPPopupControl* pControl, CRect rcClient)
{
	if (pControl->GetBackgroundBitmap() > 0)
	{
		CXTPPopupPaintManager::DrawBackground(pDC, pControl, rcClient);
		return;
	}

	//pDC->Draw3dRect(rcClient, RGB(0xff,0xff,0xff), RGB(0x00,0x00,0x00));
	//rcClient.DeflateRect(1,1);

	pDC->FillSolidRect(rcClient, RGB(0x74,0x74,0x74));
	rcClient.DeflateRect(3,25,3,3);

	pDC->FillSolidRect(rcClient, RGB(0xff,0xff,0xff));
	rcClient.DeflateRect(2,2); rcClient.bottom = rcClient.top + 30;

	XTPDrawHelpers()->GradientFill(pDC, rcClient, RGB(0xe7,0xe7,0xe7), RGB(0xff,0xff,0xff), FALSE);
}
