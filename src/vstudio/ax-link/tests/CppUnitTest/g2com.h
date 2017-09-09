// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IG2Gateway4 wrapper class

class IG2Gateway4 : public COleDispatchDriver
{
public:
	IG2Gateway4() {}		// Calls COleDispatchDriver default constructor
	IG2Gateway4(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IG2Gateway4(const IG2Gateway4& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long Connect(BOOL WaitFlag);
	void Disconnect();
	// method 'Call' not emitted because of invalid return type or parameter type
	// method 'CallDeferred' not emitted because of invalid return type or parameter type
	// method 'Start' not emitted because of invalid return type or parameter type
	LPDISPATCH GetNamedObject(LPCTSTR ObjectName, LPCTSTR ObjectClass);
	LPDISPATCH CreateObjectInstance(LPCTSTR ClassName);
	BOOL GetIsG2Connected();
	BOOL GetIsG2Running();
	CString GetG2Location();
	void SetG2Location(LPCTSTR lpszNewValue);
	CString GetInterfaceClass();
	void SetInterfaceClass(LPCTSTR lpszNewValue);
	CString GetRemoteInitializationString();
	void SetRemoteInitializationString(LPCTSTR lpszNewValue);
	long GetCallTimeout();
	void SetCallTimeout(long nNewValue);
	void PostMessage(VARIANT* Message);
	void OnStartPage(LPUNKNOWN piUnk);
	void OnEndPage();
	// method 'MakeG2ComVariable' not emitted because of invalid return type or parameter type
	long GetG2RunState();
	BOOL GetG2Symbols();
	void SetG2Symbols(BOOL bNewValue);
	BOOL GetDisconnectOnReset();
	void SetDisconnectOnReset(BOOL bNewValue);
};
