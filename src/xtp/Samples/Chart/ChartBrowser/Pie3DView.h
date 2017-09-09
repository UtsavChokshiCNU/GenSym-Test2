#pragma once


#include "PieView.h"
// CPie3DView form view

class CPie3DView : public CPieView
{
	DECLARE_DYNCREATE(CPie3DView)

protected:
	CPie3DView();           // protected constructor used by dynamic creation
	virtual ~CPie3DView();

public:
	enum { IDD = IDD_VIEW_PIE3D };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
};


