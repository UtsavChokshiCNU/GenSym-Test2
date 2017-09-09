#pragma once

#include "HighLowView.h"

// CCandleStickView form view

class CCandleStickView : public CHighLowView
{
	DECLARE_DYNCREATE(CCandleStickView)

protected:
	CCandleStickView();           // protected constructor used by dynamic creation
	virtual ~CCandleStickView();

public:
	enum { IDD = IDD_VIEW_CANDLESTICK };
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


