/*
 * Bouncing ball sample for Microsoft Windows
 */
#include <windows.h>

#if _MSC_VER
	#pragma comment(lib, "gdi32.lib")
	#pragma comment(lib, "user32.lib")
#endif

static int velx = 10;
static int vely = 10;

static void ball_update(HWND hWnd)
{
	HDC hDC = GetDC(hWnd);
	SetROP2(hDC, R2_XORPEN);
	/* erase old image */
	static RECT r_old;
	Ellipse(hDC, r_old.left, r_old.top, r_old.right, r_old.bottom);
	/* draw new image */
	static RECT r_new = { 0, 0, 50, 50 };
	Ellipse(hDC, r_new.left, r_new.top, r_new.right, r_new.bottom);
	ReleaseDC(hWnd, hDC);
	r_old = r_new;
	/* bounce off window edges */
	RECT client;
	GetClientRect(hWnd, &client);
	if (r_new.left   < client.left)   velx = -velx;
	if (r_new.top    < client.top)    vely = -vely;
	if (r_new.right  > client.right)  velx = -velx;
	if (r_new.bottom > client.bottom) vely = -vely;
	r_new.left   += velx;
	r_new.top    += vely;
	r_new.right  += velx;
	r_new.bottom += vely;
}

/* window message handler */
static LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	LRESULT result = 0;
	switch (message) {
	case WM_TIMER:
		/* update ball position */
		ball_update(hWnd);
		break;
	case WM_LBUTTONDOWN:
		/* reverse ball x direction */
		velx = -velx;
		break;
	case WM_RBUTTONDOWN:
		/* reverse ball y direction */
		vely = -vely;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		result = DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd)
{
	/* register window class */
	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "BounceWClass";
	RegisterClass(&wc);

	/* create window */
	const HWND hWnd = CreateWindow("BounceWClass", "Bouncing Ball", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	MSG msg;
	if (hWnd == 0) {
		msg.wParam = 0;
		MessageBox(0, "Error creating window", NULL, MB_OK);
	} else {
		/* show the window */
		ShowWindow(hWnd, nShowCmd);
		UpdateWindow(hWnd);

		/* create timer */
		SetTimer(hWnd, 0, 50, 0);

		/* message pump */
		while (GetMessage(&msg, 0, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
