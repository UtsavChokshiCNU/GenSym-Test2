#pragma once

#include "BaseView.h"

// CZoomAndScrollView form view

class CZoomAndScrollView : public CBaseView
{
	DECLARE_DYNCREATE(CZoomAndScrollView)

protected:
	CZoomAndScrollView();           // protected constructor used by dynamic creation
	virtual ~CZoomAndScrollView();

public:
	enum { IDD = IDD_VIEW_ZOOMANDSCROLL};
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	BOOL m_bShowLabels;
	BOOL m_bShowMarkers;
	BOOL m_bAllowZoom;
	BOOL m_bAllowScroll;

	void OnCheckShowLabels();
	void OnCheckShowMarkers();
	void OnCheckAllowScroll();
	void OnCheckAllowZoom();



	void CreateChart();

	void OnInitialUpdate();


	DECLARE_MESSAGE_MAP()
};


