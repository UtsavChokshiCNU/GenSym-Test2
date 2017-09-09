// SkinPropertySheet.h : header file
//
// This class defines custom modal property sheet 
// CSkinPropertySheet.
 
#ifndef __SKINPROPERTYSHEET_H__
#define __SKINPROPERTYSHEET_H__

#include "SkinPropertyPageControls.h"
#include "SkinPropertyPageThemes.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinPropertySheet

class CSkinPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSkinPropertySheet)

public:
	CSkinPropertySheet(CWnd* pWndParent = NULL);

public:
	CSkinPropertyPageControls m_Page1;
	CSkinPropertyPageThemes m_Page2;

	//{{AFX_VIRTUAL(CSkinPropertySheet)
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

public:
	virtual ~CSkinPropertySheet();

protected:
	//{{AFX_MSG(CSkinPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __SKINPROPERTYSHEET_H__
