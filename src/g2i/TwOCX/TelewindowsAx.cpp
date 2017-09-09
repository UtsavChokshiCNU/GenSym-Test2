// TelewindowsAx.cpp : Implementation of CTelewindowsAxApp and DLL registration.

#include "stdafx.h"
#include "TelewindowsAx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CTelewindowsAxApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xa29b880c, 0x6a2b, 0x4df6, { 0xa2, 0x76, 0xbb, 0xdd, 0x47, 0xba, 0xae, 0xc2 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 2;


////////////////////////////////////////////////////////////////////////////
// CTelewindowsAxApp::InitInstance - DLL initialization

BOOL CTelewindowsAxApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CTelewindowsAxApp::ExitInstance - DLL termination

int CTelewindowsAxApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}