
#include "stdafx.h"
#include "styler.h"
#include "IndicatorStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CIndicatorStatusBar::CIndicatorStatusBar()
{
	m_nProgress = 0;
}

CIndicatorStatusBar::~CIndicatorStatusBar()
{
}


/////////////////////////////////////////////////////////////////////////////
// CIndicatorStatusBar message handlers

void CIndicatorStatusBar::DrawPaneEntry(CDC* pDC, int nIndex, CRect rcItem)
{
	if (nIndex != 1 || m_nProgress != 0)
	{
		CXTPStatusBar::DrawPaneEntry(pDC, nIndex, rcItem);
	}
}

void CIndicatorStatusBar::SetProgress(int nProgress)
{
	if (m_nProgress != nProgress)
	{
		m_nProgress = nProgress;

		((CIndicatorStatusBarPane*)GetPane(1))->SetPos(nProgress);
	}

}

