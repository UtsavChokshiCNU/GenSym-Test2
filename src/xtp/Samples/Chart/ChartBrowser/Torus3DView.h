#pragma once

#include "DoughnutView.h"

// CTorus3DView form view

class CTorus3DView : public CDoughnutView
{
	DECLARE_DYNCREATE(CTorus3DView)

protected:
	CTorus3DView();           // protected constructor used by dynamic creation
	virtual ~CTorus3DView();

public:
	enum { IDD = IDD_VIEW_TORUS3D };
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


