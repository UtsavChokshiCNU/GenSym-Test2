#include "CppLink.h"

#ifdef WIN32
#include "windows.h"
#endif

using namespace CppLink;

  ///////////////////////////////////////////
	//
	//  DllMain
	//
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{

	}
	else if (dwReason == DLL_PROCESS_DETACH) {

	}
	return TRUE;    // ok
}








