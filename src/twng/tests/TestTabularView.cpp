#include "stdafx.h"
#include "TestTabularView.h"

#include "Twng.h"
#include "NativeView.h"
#include "TabularView.h"
#include"MainFrm.h"



/*class TestFrame: public CMainFrame
{
public:
	static const AFX_MSGMAP* GetFrameMessageMap()
	{
		return &CMainFrame::messageMap;
	}
};
*/
CPPUNIT_TEST_SUITE_REGISTRATION(TestTabularView);

void TestTabularView::test()
{
	CMainFrame *pFrame = GetMainWnd();
	G2TabularView *pTV = new G2TabularView(0);
  
	pTV->Create(WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SHAREIMAGELISTS,
	      WinSize(200,300), pFrame, 0);
  // LVS_EX_HEADERDRAGDROP
	pTV->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	pTV->m_g2pointer = SavePtr(pTV->m_hWnd);  

	int iFontSize = pTV->GetRowTextFontSize();
	CPPUNIT_ASSERT(iFontSize == 14);
	pTV->SetRowTextFontSize(15);
	iFontSize = pTV->GetRowTextFontSize();
	CPPUNIT_ASSERT(iFontSize == 15);
	

}

void TestTabularView::setUp()
{
}

void TestTabularView::tearDown()
{
}
