#pragma once

#include "DoughnutView.h"


// CDoughnut3DView form view

class CDoughnut3DView : public CDoughnutView
{
	DECLARE_DYNCREATE(CDoughnut3DView)

protected:
	CDoughnut3DView();           // protected constructor used by dynamic creation
	virtual ~CDoughnut3DView();

public:
	enum { IDD = IDD_VIEW_DOUGHNUT3D };
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


