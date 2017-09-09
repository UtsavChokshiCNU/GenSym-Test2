// ShortcutBarSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "shortcutbar.h"
#include "ShortcutBarSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarSplitter

IMPLEMENT_DYNCREATE(CShortcutBarSplitter, CXTPSplitterWndEx)

CShortcutBarSplitter::CShortcutBarSplitter()
{
	m_bShowTopBorder = FALSE;
	m_cyTopBorderGap = 2;
}

CShortcutBarSplitter::~CShortcutBarSplitter()
{
}

BEGIN_MESSAGE_MAP(CShortcutBarSplitter, CXTPSplitterWndEx)
	//{{AFX_MSG_MAP(CShortcutBarSplitter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarSplitter message handlers

void CShortcutBarSplitter::TrackColumnSize(int x, int col)
{
	ASSERT_VALID(this);
	ASSERT(m_nCols > 1);
	
	CPoint pt(x, 0);
	ClientToScreen(&pt);
	GetPane(0, col)->ScreenToClient(&pt);
	m_pColInfo[col].nIdealSize = pt.x;      // new size
	if (pt.x < 32)
	{
		// resized too small
		m_pColInfo[col].nIdealSize = 32; // make it go away
	}
}
