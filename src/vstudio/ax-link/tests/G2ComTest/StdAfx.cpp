// stdafx.cpp : source file that includes just the standard includes
//	CppUnitTest.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#include <initguid.h>
#include <asptlb.h>

#include <windows.h>
#include "EventWindow.h"

DWORD G2WaitForSingleObject(HANDLE hEvent, DWORD dwMilliseconds, GsiContext* context)
{
	MSG msg;
	DWORD ret=0;
	DWORD s=GetTickCount();
	while(true)
	{
		ret=WaitForSingleObject(hEvent,0);
		if(ret==WAIT_OBJECT_0)
			break;
		while (PeekMessage(&msg, context->mpEvnObj->getHWND(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(dwMilliseconds==INFINITE)
			continue;
		DWORD e=GetTickCount();
		if((e-s)>=dwMilliseconds)
		{
			ret=WAIT_TIMEOUT;
			break;
		}
	}
	return ret;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}
