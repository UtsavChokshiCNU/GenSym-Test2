// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "g2com.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IG2Gateway4 properties

/////////////////////////////////////////////////////////////////////////////
// IG2Gateway4 operations

long IG2Gateway4::Connect(BOOL WaitFlag)
{
	long result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		WaitFlag);
	return result;
}

void IG2Gateway4::Disconnect()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IG2Gateway4::GetNamedObject(LPCTSTR ObjectName, LPCTSTR ObjectClass)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ObjectName, ObjectClass);
	return result;
}

LPDISPATCH IG2Gateway4::CreateObjectInstance(LPCTSTR ClassName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ClassName);
	return result;
}

BOOL IG2Gateway4::GetIsG2Connected()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IG2Gateway4::GetIsG2Running()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IG2Gateway4::GetG2Location()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IG2Gateway4::SetG2Location(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IG2Gateway4::GetInterfaceClass()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IG2Gateway4::SetInterfaceClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IG2Gateway4::GetRemoteInitializationString()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IG2Gateway4::SetRemoteInitializationString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IG2Gateway4::GetCallTimeout()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IG2Gateway4::SetCallTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IG2Gateway4::PostMessage(VARIANT* Message)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Message);
}

void IG2Gateway4::OnStartPage(LPUNKNOWN piUnk)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 piUnk);
}

void IG2Gateway4::OnEndPage()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IG2Gateway4::GetG2RunState()
{
	long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL IG2Gateway4::GetG2Symbols()
{
	BOOL result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IG2Gateway4::SetG2Symbols(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IG2Gateway4::GetDisconnectOnReset()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IG2Gateway4::SetDisconnectOnReset(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}
