// DialogPerfomanceTest.cpp : implementation file
//

#include "stdafx.h"
#include "FlowGraphSample.h"
#include "DialogPerfomanceTest.h"


// CDialogPerfomanceTest dialog

IMPLEMENT_DYNAMIC(CDialogPerfomanceTest, CDialog)

CDialogPerfomanceTest::CDialogPerfomanceTest(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CDialogPerfomanceTest::IDD, pParent)
{
	m_nSmoothingMode = 0;

}

CDialogPerfomanceTest::~CDialogPerfomanceTest()
{
}

void CDialogPerfomanceTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPHCONTROL, m_wndControl);
	DDX_CBIndex(pDX, IDC_COMBO_SMOOTHING_MODE, m_nSmoothingMode);
}


BEGIN_MESSAGE_MAP(CDialogPerfomanceTest, CXTPResizeDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnBnClickedButtonArrange)
	ON_CBN_SELCHANGE(IDC_COMBO_SMOOTHING_MODE, OnSmoothingModeChanged)
END_MESSAGE_MAP()


// CDialogPerfomanceTest message handlers

BOOL CDialogPerfomanceTest::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	
	m_wndControl.GetPages()->RemoveAll();

	//m_wndControl.SetPaintManager(new CXTPFlowGraphMetallicTheme());

	CXTPFlowGraphPage* pPage = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());
	int i;

	for (i = 1; i <= 500; i++)
	{
		CXTPFlowGraphNode* pNode = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());

		CString strCaption;
		strCaption.Format(_T("Node %d"), i);
		pNode->SetCaption(strCaption);
		pNode->SetColor(clrOfficeColors[rand() % 5]);
		pNode->SetLocation(CPoint(rand() % 5000, rand() % 3000));

		CXTPFlowGraphConnectionPoint* pConnectionPoint;
		pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
		pConnectionPoint->SetCaption(_T("Item 1"));
		pConnectionPoint->SetType(xtpFlowGraphPointOutput);

		pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
		pConnectionPoint->SetCaption(_T("Item 2"));
		pConnectionPoint->SetType(xtpFlowGraphPointInput);
	}

	for (i = 0; i < 150; i++)
	{
		CXTPFlowGraphConnection* pConnection;
		pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());

		int nFrom = rand() % (500 - 1);
		int nTo = nFrom + 1 + (rand() % (500 - 1 - nFrom));

		pConnection->SetOutputPoint(pPage->GetNodes()->GetAt(nFrom)->GetConnectionPoints()->GetAt(0));
		pConnection->SetInputPoint(pPage->GetNodes()->GetAt(nTo)->GetConnectionPoints()->GetAt(1));
	}

	m_wndControl.SetActivePage(pPage);

	m_wndControl.SetZoomRange(0.5, 5.0);

#ifdef __XTPRESIZEDIALOG_H__
	SetResize(IDC_GRAPHCONTROL, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BUTTON_ARRANGE, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_COMBO_SMOOTHING_MODE, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
#endif


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogPerfomanceTest::OnBnClickedButtonArrange()
{
	m_wndControl.Arrange();
}

void CDialogPerfomanceTest::OnSmoothingModeChanged()
{
	UpdateData();

	m_wndControl.SetSmoothingMode((XTPFlowGraphSmoothingMode)m_nSmoothingMode);
	m_wndControl.RedrawControl();
}