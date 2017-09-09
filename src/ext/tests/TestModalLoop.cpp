#include "TestModalLoop.h"
#include <windows.h>

extern "C" {
	#include "msincls.h"
}

CPPUNIT_TEST_SUITE_REGISTRATION(CTestModalLoop);


static bool bIsTimerCalled = false;
static bool bDoKillTimer = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_TIMER:
		if (wParam == ANTIMODAL_TIMER_ID)
		{
			bIsTimerCalled = true;
			if (bDoKillTimer)
			{
				g2pvt_exit_modal_loop();
			}
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void CreateTestWindow()
{
	HINSTANCE hInstance = (HINSTANCE) GetModuleHandle(NULL);
	static LPCSTR lpzWndClass = "TestModalLoopWnd";

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= lpzWndClass;
	wcex.hIconSm		= NULL;

	RegisterClassEx(&wcex);

	hwndFrame = CreateWindow(lpzWndClass, "", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

}

void MessageLoop()
{
	MSG msg;
	int nCount = 10000;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) && nCount > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		nCount--;
	}

}

void CTestModalLoop::setUp()
{
	hwndFrame = NULL;
	CreateTestWindow();
	MessageLoop();
}

void CTestModalLoop::tearDown()
{
	if (hwndFrame != NULL)
	{
		DestroyWindow(hwndFrame);
		hwndFrame = NULL;
		MessageLoop();
	}
}

void CTestModalLoop::testEnterModalLoop()
{
	bDoKillTimer = true;
	bIsTimerCalled = false;

	CPPUNIT_ASSERT(hwndFrame != NULL);

	g2pvt_enter_modal_loop();

	Sleep(10 * ANTIMODAL_TIMER_PERIOD);
	MessageLoop();

	CPPUNIT_ASSERT(bIsTimerCalled);
}

void CTestModalLoop::testExitModalLoop()
{
	bDoKillTimer = false;
	bIsTimerCalled = false;

	CPPUNIT_ASSERT(hwndFrame != NULL);

	g2pvt_enter_modal_loop();

	Sleep(10 * ANTIMODAL_TIMER_PERIOD);
	MessageLoop();

	CPPUNIT_ASSERT(bIsTimerCalled);

	g2pvt_exit_modal_loop();
	MessageLoop();

	bIsTimerCalled = false;
	Sleep(10 * ANTIMODAL_TIMER_PERIOD);
	MessageLoop();
	CPPUNIT_ASSERT(!bIsTimerCalled);
}

void CTestModalLoop::testEnterExitModalLoop()
{
	bDoKillTimer = false;
	bIsTimerCalled = false;

	CPPUNIT_ASSERT(hwndFrame != NULL);

	g2pvt_enter_modal_loop();
	g2pvt_enter_modal_loop();

	Sleep(10 * ANTIMODAL_TIMER_PERIOD);
	MessageLoop();

	CPPUNIT_ASSERT(bIsTimerCalled);

	g2pvt_exit_modal_loop();
	MessageLoop();

	bIsTimerCalled = false;
	Sleep(10 * ANTIMODAL_TIMER_PERIOD);
	MessageLoop();
	CPPUNIT_ASSERT(bIsTimerCalled);

	g2pvt_exit_modal_loop();
	MessageLoop();

	bIsTimerCalled = false;
	Sleep(10 * ANTIMODAL_TIMER_PERIOD);
	MessageLoop();
	CPPUNIT_ASSERT(!bIsTimerCalled);
}

