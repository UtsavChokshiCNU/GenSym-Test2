#include "stdafx.h"
#include "TestIconSizeChanged.h"
#include "MainFrm.h"
#include "Twng.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestIconSizeChanged);

void TestIconSizeChanged::setUp()
{
	unsigned short result[2];
	g2ext_begin_item_menu();
	g2ext_nms_create_menu(0,result);
}

void TestIconSizeChanged::test()
{
	CXTPCommandBars* pCommandBars;
	CXTPCommandBarsOptions* pOptions;
	CSize size_to_set;
	CSize iconsize;

	for (int size=16;size<=96;size++)
	{
		size_to_set.cx = size_to_set.cy = size;
		g2ext_nms_set_iconsize(size);
		pCommandBars = GetMainWnd()->GetCommandBars();
		CPPUNIT_ASSERT(pCommandBars);
		iconsize = pCommandBars->GetMenuBar()->GetIconSize();
		CPPUNIT_ASSERT(size_to_set==iconsize);
	}

	//if the icon size is larger than 96x96, it can't be changed 
	size_to_set.cx = size_to_set.cy = size;
	g2ext_nms_set_iconsize(size);
	pCommandBars = GetMainWnd()->GetCommandBars();
	CPPUNIT_ASSERT(pCommandBars);
	iconsize = pCommandBars->GetMenuBar()->GetIconSize();
	CPPUNIT_ASSERT(size_to_set!=iconsize);
}

void TestIconSizeChanged::tearDown()
{

}