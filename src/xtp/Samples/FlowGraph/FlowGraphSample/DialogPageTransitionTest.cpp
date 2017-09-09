// DialogPageTransitionTest.cpp : implementation file
//

#include "stdafx.h"
#include "FlowGraphSample.h"
#include "DialogPageTransitionTest.h"

#ifndef WM_APPCOMMAND
#define WM_APPCOMMAND 0x0319
#endif

// CDialogPageTransitionTest dialog

IMPLEMENT_DYNAMIC(CDialogPageTransitionTest, CXTPResizeDialog)

CDialogPageTransitionTest::CDialogPageTransitionTest(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CDialogPageTransitionTest::IDD, pParent)
{

}

CDialogPageTransitionTest::~CDialogPageTransitionTest()
{
}

void CDialogPageTransitionTest::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPHCONTROL, m_wndControl);
}


BEGIN_MESSAGE_MAP(CDialogPageTransitionTest, CXTPResizeDialog)
	ON_MESSAGE(WM_APPCOMMAND, OnAppCommand)
	ON_NOTIFY(NM_DBLCLK, IDC_GRAPHCONTROL, OnGraphDblClick)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnBnClickedButtonNext)
END_MESSAGE_MAP()

const int ID_NODE_DATABASE1 = 1;
const int ID_NODE_DATABASE2 = 2;
const int ID_PAGE_DATABASE = 3;
const int ID_PAGE_TABLE1 = 4;
const int ID_PAGE_TABLE2 = 5;

// CDialogPageTransitionTest message handlers

void CDialogPageTransitionTest::CreateTable1Page()
{
	CXTPFlowGraphPage* pPageTable = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());
	pPageTable->SetCaption(_T("Databases->Database1"));
	pPageTable->SetID(ID_PAGE_TABLE1);


	CXTPFlowGraphNode* pNode = pPageTable->GetNodes()->AddNode(new CXTPFlowGraphNode());

	pNode->SetCaption(_T("Database 1"));
	pNode->SetColor(clrOfficeColors[1]);
	pNode->SetLocation(CPoint(50, 50));
	pNode->SetID(ID_NODE_DATABASE1);

	CXTPFlowGraphConnectionPoint* pConnectionPoint;
	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 2"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);


	pNode = pPageTable->GetNodes()->AddNode(new CXTPFlowGraphNode());

	pNode->SetCaption(_T("Table 1"));
	pNode->SetColor(clrOfficeColors[1]);
	pNode->SetLocation(CPoint(200, 50));

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);


	pNode = pPageTable->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pNode->SetCaption(_T("Table 2"));
	pNode->SetColor(clrOfficeColors[2]);
	pNode->SetLocation(CPoint(200, 150));

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 2"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 3"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);


	CXTPFlowGraphConnection* pConnection;
	pConnection = pPageTable->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pPageTable->GetNodes()->GetAt(0)->GetConnectionPoints()->GetAt(0));
	pConnection->SetInputPoint(pPageTable->GetNodes()->GetAt(1)->GetConnectionPoints()->GetAt(0));

	pConnection = pPageTable->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pPageTable->GetNodes()->GetAt(0)->GetConnectionPoints()->GetAt(1));
	pConnection->SetInputPoint(pPageTable->GetNodes()->GetAt(2)->GetConnectionPoints()->GetAt(0));

}


void CDialogPageTransitionTest::CreateTable2Page()
{

	CXTPFlowGraphPage* pPageTable = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());
	pPageTable->SetCaption(_T("Databases->Database2"));
	pPageTable->SetID(ID_PAGE_TABLE2);


	CXTPFlowGraphNode* pNode = pPageTable->GetNodes()->AddNode(new CXTPFlowGraphNode());

	pNode->SetCaption(_T("Database 2"));
	pNode->SetColor(clrOfficeColors[1]);
	pNode->SetLocation(CPoint(300, -100));
	pNode->SetID(ID_NODE_DATABASE2);

	CXTPFlowGraphConnectionPoint* pConnectionPoint;
	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 2"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 3"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pNode = pPageTable->GetNodes()->AddNode(new CXTPFlowGraphNode());

	pNode->SetCaption(_T("Table 1"));
	pNode->SetColor(clrOfficeColors[1]);
	pNode->SetLocation(CPoint(50, 50));

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);


	pNode = pPageTable->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pNode->SetCaption(_T("Table 2"));
	pNode->SetColor(clrOfficeColors[2]);
	pNode->SetLocation(CPoint(200, 50));

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 2"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);



	pNode = pPageTable->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pNode->SetCaption(_T("Table 3"));
	pNode->SetColor(clrOfficeColors[3]);
	pNode->SetLocation(CPoint(400, 50));

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 2"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 3"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Item 4"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	CXTPFlowGraphConnection* pConnection;
	pConnection = pPageTable->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pPageTable->GetNodes()->GetAt(1)->GetConnectionPoints()->GetAt(0));
	pConnection->SetInputPoint(pPageTable->GetNodes()->GetAt(2)->GetConnectionPoints()->GetAt(1));
}


void CDialogPageTransitionTest::CreateDatabasePage()
{
	CXTPFlowGraphPage* pPageDatabase = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());
	pPageDatabase->SetCaption(_T("Databases"));
	pPageDatabase->SetID(ID_PAGE_DATABASE);

	CXTPFlowGraphNode* pNode = pPageDatabase->GetNodes()->AddNode(new CXTPFlowGraphNode());

	pNode->SetCaption(_T("Database 1"));
	pNode->SetColor(clrOfficeColors[1]);
	pNode->SetLocation(CPoint(50, 50));
	pNode->SetID(ID_NODE_DATABASE1);

	CXTPFlowGraphConnectionPoint* pConnectionPoint;
	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 2"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);


	pNode = pPageDatabase->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pNode->SetCaption(_T("Database 2"));
	pNode->SetColor(clrOfficeColors[2]);
	pNode->SetLocation(CPoint(200, 50));
	pNode->SetID(ID_NODE_DATABASE2);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 1"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 2"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
	pConnectionPoint->SetCaption(_T("Table 3"));
	pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);

	CXTPFlowGraphConnection* pConnection;
	pConnection = pPageDatabase->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pPageDatabase->GetNodes()->GetAt(0)->GetConnectionPoints()->GetAt(0));
	pConnection->SetInputPoint(pPageDatabase->GetNodes()->GetAt(1)->GetConnectionPoints()->GetAt(1));
}

BOOL CDialogPageTransitionTest::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	//m_wndControl.SetPaintManager(new CXTPFlowGraphMetallicTheme());

	CreateDatabasePage();
	CreateTable1Page();
	CreateTable2Page();

	m_wndControl.SetActivePage(m_wndControl.GetPages()->GetAt(0));

	UpdateButtons();


#ifdef __XTPRESIZEDIALOG_H__
	SetResize(IDC_GRAPHCONTROL, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BUTTON_NEXT, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BUTTON_PREV, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
#endif


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogPageTransitionTest::UpdateButtons()
{
	GetDlgItem(IDC_BUTTON_PREV)->EnableWindow(m_wndControl.GetHistory()->CanGoBackward());
	GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(m_wndControl.GetHistory()->CanGoForward());

	CString strPage = _T("Active Page: ") + m_wndControl.GetActivePage()->GetCaption();
	GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(strPage);
}

void CDialogPageTransitionTest::OnGraphDblClick(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
	CPoint point;
	GetCursorPos(&point);

	m_wndControl.ScreenToClient(&point);

	CXTPFlowGraphNode* pNode = m_wndControl.HitTestNode(point);

	if (pNode)
	{
		if (pNode->GetID() == ID_NODE_DATABASE1 && m_wndControl.GetActivePage()->GetID() == ID_PAGE_DATABASE)
		{
			CXTPFlowGraphPage* pPageTo = m_wndControl.GetPages()->FindPage(ID_PAGE_TABLE1);

			CXTPFlowGraphNode* pNodeFrom = pNode;
			CXTPFlowGraphNode* pNodeTo = pPageTo->GetNodes()->FindNode(ID_NODE_DATABASE1);

			m_wndControl.GetHistory()->AnimatePageTransition(pNodeFrom, pNodeTo);

			UpdateButtons();			
		}

		if (pNode->GetID() == ID_NODE_DATABASE2 && m_wndControl.GetActivePage()->GetID() == ID_PAGE_DATABASE)
		{
			CXTPFlowGraphPage* pPageTo = m_wndControl.GetPages()->FindPage(ID_PAGE_TABLE2);

			CXTPFlowGraphNode* pNodeFrom = pNode;
			CXTPFlowGraphNode* pNodeTo = pPageTo->GetNodes()->FindNode(ID_NODE_DATABASE2);

			m_wndControl.GetHistory()->AnimatePageTransition(pNodeFrom, pNodeTo);

			UpdateButtons();
		}
	}
}
void CDialogPageTransitionTest::OnBnClickedButtonPrev()
{
	m_wndControl.GetHistory()->GoBackward();
	UpdateButtons();
}

void CDialogPageTransitionTest::OnBnClickedButtonNext()
{
	m_wndControl.GetHistory()->GoForward();
	UpdateButtons();
}

LRESULT CDialogPageTransitionTest::OnAppCommand(WPARAM /*wParam*/, LPARAM lParam)
{
	if (HIWORD(lParam) == 1)
	{
		OnBnClickedButtonPrev();
	}
	else if  (HIWORD(lParam) == 2)
	{
		OnBnClickedButtonNext();
	}
	
	return Default();
}