// AXClient.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f AXClientps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "AXClient.h"

#include "AXClient_i.c"
#include "G2UiGateway.h"
#include "G2Structure.h"
#include "G2Symbol.h"
#include "G2Item.h"
#include "G2WorkspacePanel.h"
#include "G2ItemHolder.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
    // G2Item is missing because it can be created by CoCreateInstance()
    //   it must be created by a Gateway to ensure that the implementation
    //   of the Item comes from the same dll as the 
	OBJECT_ENTRY(CLSID_G2Symbol, G2Symbol)
	OBJECT_ENTRY(CLSID_G2Structure, G2Structure)
	OBJECT_ENTRY(CLSID_G2UiGateway, CG2UiGateway)
	OBJECT_ENTRY(CLSID_G2WorkspacePanel, CG2WorkspacePanel)
	OBJECT_ENTRY(CLSID_G2ItemHolder, CG2ItemHolder)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved */)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();

    // UnregisterServer does not remove typelib and interfaces
    //   so we have to.
    UnRegisterTypeLib(LIBID_GensymTw2, LIB_MAJOR_VERSION_GensymTw2,
        LIB_MINOR_VERSION_GensymTw2, 0, SYS_WIN32);
	return S_OK;
}
