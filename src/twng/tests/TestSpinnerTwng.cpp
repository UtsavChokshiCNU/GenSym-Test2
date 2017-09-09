#include "TestSpinnerTwng.h"
#include "stdafx.h"
#include "twng.h"
#include "MainFrm.h"
#include "NativeView.h"
#include "MockDestroyListener.h"
#include "SpinWidget/SpinnerTwng.h"
CPPUNIT_TEST_SUITE_REGISTRATION(TestSpinnerTwng);


void TestSpinnerTwng::setUp()
{
	mainWindow = new CWnd();
	mainWindow->CreateEx(0, AfxRegisterWndClass(0), _T(""),
		WS_VISIBLE | WS_POPUP,	CRect(0, 0, 300, 300), NULL, 0);
	DWORD dwStyle = 0x500100b8;
	spinnertwng = new CSpinnerTwng;
	
	spinnertwng->Create(dwStyle,CRect(15, 16, 203, 36),mainWindow,0);
}

void TestSpinnerTwng::tearDown() {
	delete mainWindow;
}

void TestSpinnerTwng::testSpinnerResize()
{
	CRect rb,ra;
    spinnertwng->m_pSpinButtonCtrl->GetWindowRect(&rb);
	spinnertwng->RecalcLayout();
    spinnertwng->m_pSpinButtonCtrl->GetWindowRect(&ra);
    CPPUNIT_ASSERT(rb.left == ra.left);	
}