#if !defined(AFX_BACKSTAGEPAGEHELP_H__4B395902_6695_4B25_97E1_423271FE5CED__INCLUDED_)
#define AFX_BACKSTAGEPAGEHELP_H__4B395902_6695_4B25_97E1_423271FE5CED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackstagePageHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageHelp dialog

class CBackstagePageHelp : public CXTPRibbonBackstagePage
{

// Construction
public:
	CBackstagePageHelp();
	~CBackstagePageHelp();

// Dialog Data
	//{{AFX_DATA(CBackstagePageHelp)
	enum { IDD = IDD_BACKSTAGEPAGE_HELP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBackstagePageHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	BOOL OnInitDialog();

	void InitButton(CXTPRibbonBackstageButton& btn);
	
	CXTPRibbonBackstageLabel m_lblSupport;
	CXTPRibbonBackstageLabel m_lblTools;
	CXTPRibbonBackstageLabel m_lblAbout;

	CXTPRibbonBackstageSeparator m_lblSeparator1;
	CXTPRibbonBackstageSeparator m_lblSeparator2;
	CXTPRibbonBackstageSeparator m_lblSeparator3;
	CXTPRibbonBackstageSeparator m_lblSeparator4;
	
	CXTPRibbonBackstageButton m_btnHelp;
	CXTPRibbonBackstageButton m_btnGettingStarted;
	CXTPRibbonBackstageButton m_btnContactUs;
	CXTPRibbonBackstageButton m_btnOptions;
	CXTPRibbonBackstageButton m_btnCheckForUpdates;

	CXTPImageManager m_imagelist;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBackstagePageHelp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGEHELP_H__4B395902_6695_4B25_97E1_423271FE5CED__INCLUDED_)
