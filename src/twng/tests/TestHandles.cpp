#include "stdafx.h"
#include "TestHandles.h"

#include "MainFrm.h"

class TestFrame: public CMainFrame
{
public:
	static const AFX_MSGMAP* GetFrameMessageMap()
	{
		#if defined(_MFC_VER)&&_MFC_VER>=0x0900//VS2008 MFC and more	
		return CMainFrame::GetThisMessageMap();
        #else
		return &CMainFrame::messageMap;				
        #endif
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestHandles);

void TestHandles::test()
{
	long testId = 33000;
	const AFX_MSGMAP* msg_map = TestFrame::GetFrameMessageMap();

	bool processed_exec = false;
	bool processed_update = false;

	for (int i = 0;; i++)
	{
		const AFX_MSGMAP_ENTRY& entry = msg_map->lpEntries[i];

		if (entry.nSig == AfxSig_end)
		{
			break;
		}

		if (entry.nMessage == WM_NOTIFY)
		{
			if (entry.nCode == CBN_XTP_EXECUTE)
			{
				if (entry.nID <= testId && entry.nLastID >= testId)
				{
					processed_exec = true;
				}
			}

		}

		if (entry.nMessage == WM_COMMAND)
		{
			if (entry.nCode == CN_UPDATE_COMMAND_UI)
			{
				if (entry.nID <= testId && entry.nLastID >= testId)
				{
					processed_update = true;
				}
			}

		}

	}

	CPPUNIT_ASSERT(processed_exec);
	CPPUNIT_ASSERT(processed_update);
}

void TestHandles::setUp()
{
}

void TestHandles::tearDown()
{
}
