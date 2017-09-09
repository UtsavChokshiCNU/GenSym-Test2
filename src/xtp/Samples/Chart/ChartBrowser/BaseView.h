#pragma once

//#define  _XTP_INCLUDE_TOOLKIT

#ifndef _XTP_INCLUDE_TOOLKIT
#define CXTPButton CButton
#endif

class CResizeGroupBox : public CXTPButton
{
	DECLARE_DYNAMIC(CResizeGroupBox)
		
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPResizeGroupBox object
	//-----------------------------------------------------------------------
	CResizeGroupBox();
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTPResizeGroupBox object, handles cleanup and
	//     deallocation
	//-----------------------------------------------------------------------
	virtual ~CResizeGroupBox();
	
protected:
	//-----------------------------------------------------------------------
	// Summary:
	//     Called during paint operations to exclude the control windows
	//     that are grouped by this control.
	// Parameters:
	//     pDC      - Pointer to device context.
	//     rcClient - Client area of group box.
	//-----------------------------------------------------------------------
	virtual void Exclude(CDC* pDC, CRect& rcClient);

	
	
protected:
//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()
		
	//{{AFX_VIRTUAL(CXTPResizeGroupBox)
	//}}AFX_VIRTUAL
		
	//{{AFX_MSG(CXTPResizeGroupBox)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE
};



template <class TBase>
class CChartBorder : public TBase
{
public:
	CChartBorder()
	{
#ifdef _XTP_INCLUDE_TOOLKIT
		CXTPChartColor color;
		color.SetFromCOLORREF(0xcf9365);

		GetContent()->GetBorder()->SetColor(color);
#endif
	}

};
// CBaseView form view

class CBaseView : public CFormView
{
	DECLARE_DYNAMIC(CBaseView)

public:
	CBaseView(const UINT nID);           // protected constructor used by dynamic creation
	virtual ~CBaseView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	virtual void OnInitialUpdate();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	DECLARE_MESSAGE_MAP()

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	CString m_strCaption;
	CBrush m_hBrush;

	CChartBorder<CXTPChartControl> m_wndChartControl;

	CResizeGroupBox m_wndGroupBoxLabels;

	int m_nTopGap;
	int m_nLeftGap;
};


