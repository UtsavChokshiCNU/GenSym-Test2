#include "stdafx.h"
#include "TestModalLoop.h"
#include "MainFrm.h"
#include "twng.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CTestModalLoop);

class CTestDockingPaneManager : public CG2DockingPaneManager
{
public:
	static CXTPDockingPaneBase* DoCreatePane(CXTPDockingPaneManager* pManager, XTPDockingPaneType type)
	{
		CTestDockingPaneManager* pManager2 = (CTestDockingPaneManager*) pManager;
		return pManager2->OnCreatePane(type, pManager2->m_pLayout);
	}
};

void CTestModalLoop::setUp()
{
	m_pMainFrame = GetMainWnd();
}

void CTestModalLoop::tearDown()
{
}

void CTestModalLoop::testCommandBars()
{
	CPPUNIT_ASSERT(m_pMainFrame != NULL);
	CPPUNIT_ASSERT(IsWindow(m_pMainFrame->m_hWnd));

	CPPUNIT_ASSERT(m_pMainFrame->GetCommandBars()->IsKindOf(RUNTIME_CLASS(CG2CommandBars)));
}

void CTestModalLoop::testDockingPanes()
{
	CPPUNIT_ASSERT(m_pMainFrame != NULL);
	CPPUNIT_ASSERT(IsWindow(m_pMainFrame->m_hWnd));

	CXTPDockingPaneManager* pManager = m_pMainFrame->GetDockingPaneManager();
	CPPUNIT_ASSERT(pManager != NULL);

	CPPUNIT_ASSERT(pManager->IsAlphaDockingContext());

	CXTPDockingPaneTabbedContainer* pTabbedContainerPane =
		(CXTPDockingPaneTabbedContainer*) CTestDockingPaneManager::DoCreatePane(pManager, xtpPaneTypeTabbedContainer);

	CPPUNIT_ASSERT(pTabbedContainerPane != NULL);
	CPPUNIT_ASSERT(pTabbedContainerPane->IsKindOf(RUNTIME_CLASS(CG2DockingPaneTabbedContainer)));

	CXTPDockingPaneMiniWnd* pMiniWndPane =
		(CXTPDockingPaneMiniWnd*) CTestDockingPaneManager::DoCreatePane(pManager, xtpPaneTypeMiniWnd);

	CPPUNIT_ASSERT(pMiniWndPane != NULL);
	CPPUNIT_ASSERT(pMiniWndPane->IsKindOf(RUNTIME_CLASS(CXTPDockingPaneMiniWnd)));
}

