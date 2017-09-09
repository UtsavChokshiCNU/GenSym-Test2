#if !defined(AFX_TELEWINDOWSPPG_H__F6EBE518_CB6A_4808_BC63_4E8E028008FF__INCLUDED_)
#define AFX_TELEWINDOWSPPG_H__F6EBE518_CB6A_4808_BC63_4E8E028008FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WebSCORaxPpg.h : Declaration of the CTelewindowsAxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CTelewindowsAxPropPage : See WebSCORaxPpg.cpp.cpp for implementation.

class CTelewindowsAxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTelewindowsAxPropPage)
	DECLARE_OLECREATE_EX(CTelewindowsAxPropPage)

// Constructor
public:
	CTelewindowsAxPropPage();

// Dialog Data
	//{{AFX_DATA(CTelewindowsAxPropPage)
	enum { IDD = IDD_PROPPAGE_TELEWINDOWSAX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CTelewindowsAxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBSCORAXPPG_H__F6EBE518_CB6A_4808_BC63_4E8E028008FF__INCLUDED)
