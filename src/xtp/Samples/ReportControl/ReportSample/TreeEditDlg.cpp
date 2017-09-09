// TreeEditDlg.cpp : implementation of the CTreeEditDlg class
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

#include "StdAfx.h"
#include "Resource.h"
#include "TreeEditDlg.h"

#include "float.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const int COLUMN_MAIL_ICON   =  0;
const int COLUMN_CHECK_ICON  =  2;

/////////////////////////////////////////////////////////////////////////////
// CTreeEditDlg dialog


CTreeEditDlg::CTreeEditDlg(CWnd *pParent)
	: CDialog(CTreeEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeEditDlg)
	//}}AFX_DATA_INIT
}


void CTreeEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeEditDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeEditDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeEditDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportRClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeEditDlg message handlers


class CAnalysisCaptionRecord : public CXTPReportRecord
{
public:
	CAnalysisCaptionRecord(int ID, LPCTSTR Caption) {
		CXTPReportRecordItem* Item=AddItem(new CXTPReportRecordItemText(Caption));
		Item->SetEditable(FALSE);
		Item->SetFocusable(FALSE);
		Item=AddItem(new CXTPReportRecordItemText(_T("")));
		Item->SetEditable(FALSE);
		Item->SetFocusable(FALSE);
		Item=AddItem(new CXTPReportRecordItemText(_T("")));
		Item->SetEditable(FALSE);
		Item->SetFocusable(FALSE);
	}

private:
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) {
		if (!pDrawArgs->pRow->IsFocused()) {
			pItemMetrics->pFont = &pDrawArgs->pRow->GetControl()->GetPaintManager()->m_fontBoldText;
			if (pDrawArgs->pRow->GetTreeDepth()>=1)
				pItemMetrics->clrBackground=RGB(220,220,150);
			else
				pItemMetrics->clrBackground=RGB(150,220,220);
			pItemMetrics->clrForeground=RGB(255,255,255);
		}
	}
};

class CAnalysisResultRecord : public CXTPReportRecord
{
public:
	CAnalysisResultRecord(int ID, unsigned char NumDecimals, const COleVariant& Value) {
		CString Itemtext;
		Itemtext.Format(_T("%d. Measurement"), ID+1);
		CXTPReportRecordItem* Item=AddItem(new CXTPReportRecordItemText(Itemtext));
		Item->SetEditable(FALSE);
		Item->SetFocusable(FALSE);

		CString Form;
		Form.Format(_T("%%.%df"), NumDecimals);
		ASSERT(Value.vt==VT_R8);
		Item=AddItem(new CXTPReportRecordItemNumber(Value.dblVal));
		Item->SetFormatString(Form);

		Item=AddItem(new CXTPReportRecordItemText(_T("")));
		Item->SetEditable(FALSE);
		Item->SetFocusable(FALSE);

	}
};

class CAnalysisDetailRecord : public CXTPReportRecord
{
public:
	CAnalysisDetailRecord(int ID, LPCTSTR Caption, LPCTSTR Unit, unsigned char NumDecimals, std::vector<COleVariant>& Values);

private:
	int ID_;

};


CAnalysisDetailRecord::CAnalysisDetailRecord( int ID, LPCTSTR Caption, LPCTSTR Unit, unsigned char NumDecimals, std::vector<COleVariant>& Values) : ID_(ID) {
	CXTPReportRecordItem* Item=AddItem(new CXTPReportRecordItemText(Caption));
	Item->SetEditable(FALSE);
	Item->SetFocusable(FALSE);
	
	if (!Values.empty()) {

		CString Form;
		Form.Format(_T("%%.%df"), NumDecimals);

		if (Values.size()>1) {
			for (size_t i=0; i<Values.size(); i++) {
				GetChilds()->Add(new CAnalysisResultRecord((int) i, NumDecimals, Values[i]));
			}

			std::vector<double> Data;
			//std::for_each(Values.begin(), Values.end(), ExtractTo(Data));

			// The accumulator set which will calculate the properties for us:    
			//boost::accumulators::accumulator_set< double, boost::accumulators::features< boost::accumulators::tag::mean > > acc;

			// Use std::for_each to accumulate the statistical properties:
			//acc = std::for_each(Data.begin(), Data.end(), acc);

			Item=AddItem(new CXTPReportRecordItemNumber(3));
			Item->SetFormatString(Form);
			Item->SetEditable(FALSE);
			Item->SetFocusable(FALSE);

		} else {
			if (Values[0].vt!=VT_EMPTY) {
				if (Values[0].vt==VT_DATE) {
					CXTPReportRecordItem* Item=AddItem(new CXTPReportRecordItemDateTime(Values[0]));
					Item->SetFormatString(_T("%d.%m.%Y"));
				} else {
					ASSERT(Values[0].vt==VT_R8);
					CXTPReportRecordItem* Item=AddItem(new CXTPReportRecordItemNumber(Values[0].dblVal));
					Item->SetFormatString(Form);
				}
			}
			
		}
	} else {
		Item=AddItem(new CXTPReportRecordItemText(_T("")));
	}

	Item=AddItem(new CXTPReportRecordItemText(Unit));
	Item->SetEditable(FALSE);
	Item->SetFocusable(FALSE);

}


BOOL CTreeEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);

	m_wndReport.GetPaintManager()->m_treeStructureStyle=xtpReportTreeStructureDots;
	m_wndReport.GetPaintManager()->m_nTreeIndent = 10;

	m_wndReport.GetPaintManager()->m_nTreeTextIndentRowParent = 5;

	m_wndReport.ShowHeader(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnReorder(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnSort(FALSE);
	
	m_wndReport.GetColumns()->GetSortOrder()->Clear();

	// Description
	CXTPReportColumn* Column=m_wndReport.AddColumn(new CXTPReportColumn(0, _T(""), 200));
	Column->SetEditable(FALSE);
	Column->SetTreeColumn(TRUE);

	Column=m_wndReport.AddColumn(new CXTPReportColumn(1, _T(""), 80));
	Column->SetAlignment(xtpColumnTextRight);

	Column=m_wndReport.AddColumn(new CXTPReportColumn(2, _T(""), 50, FALSE));
	Column->SetEditable(FALSE);

	m_wndReport.LockExpand(TRUE);		// Row not expandable / collapsible

	//AddEntries(Entries_);
	CXTPReportRecord* Record=0;

	std::vector<COleVariant> values;
	values.push_back(COleVariant(1.0));
	values.push_back(COleVariant(2.0));
	values.push_back(COleVariant(3.0));

	for (int i=0; i<10; i++)
	{
		Record=m_wndReport.AddRecord(new CAnalysisCaptionRecord(i, _T("Entry")));
		Record->SetExpanded(TRUE);

		for (int d=0; d<3; d++)
		{
			CXTPReportRecord *pDetail;
			pDetail = Record->GetChilds()->Add(new CAnalysisDetailRecord(d, _T("Detail"), _T("Unit"), 3, values));
			pDetail->SetExpanded(TRUE);
		}
	}

	m_wndReport.Populate();

	return FALSE;
}

void CTreeEditDlg::OnOK()
{
	CDialog::OnOK();
}

void CTreeEditDlg::OnReportRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	
	if (pItemNotify->pRow)
	{
		TRACE(_T("Right click on row %d\n"), pItemNotify->pRow->GetIndex());
	}

}
