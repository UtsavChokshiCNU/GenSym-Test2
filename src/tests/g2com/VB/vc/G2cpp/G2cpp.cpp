// G2cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include "G2Com.h"
#include <conio.h>
//#include <atlbase.h>
//#include <ATLCOM.H>
#import "G2COM.dll"

int demoError(int errorCode, HRESULT hr) ;

int main(int argc, char* argv[])
{
	HRESULT hr ;
	IG2Gateway *pAxl ;
	try{
	
	// Initialize COM
	cout << "Test Case 24:  Example of the Use of ActiveXLink in a C++ Program" << endl;
	hr = ::CoInitialize(NULL) ;
	cout << "CoInitialize" <<endl;
	if (FAILED(hr))
	return demoError(0, hr) ;

	// Create an instance of G2Gateway
    hr = ::CoCreateInstance(CLSID_G2Gateway, NULL,CLSCTX_INPROC_SERVER,IID_IG2Gateway2,
                      reinterpret_cast<void**>(&pAxl));
	cout << "CoCreateInstance" <<endl;
	//hr = CreateInstance(CLSID_G2Gateway, NULL,&pAxl) ;
	if (FAILED(hr))
		return demoError(1, hr) ;

	// Specify location of G2
	BSTR g2Loc = ::SysAllocString(L"localhost:1111") ;
	hr = pAxl->put_G2Location(g2Loc) ;
	cout << "put_G2Location" <<endl;
	::SysFreeString(g2Loc) ;
	if (FAILED(hr))
		return demoError(2, hr) ;

	// Specify how long we should wait for a response from G2
	hr = pAxl->put_CallTimeout(15L) ;
	cout << "put_CallTimeout" <<endl;
	if (FAILED(hr))
		return demoError(3, hr) ;

	// Connect to G2, waiting for the connection.
	
	
	hr = pAxl->Connect(VARIANT_FALSE) ;
	cout << "Connect" <<endl;
	if (FAILED(hr))
		return demoError(4, hr) ;

	// Say hello to G2
	VARIANT Msg ;
	VariantInit(&Msg) ;
	Msg.vt = VT_BSTR ;
	Msg.bstrVal = ::SysAllocString(L"Hello, G2.") ;
	hr = pAxl->PostMessage(&Msg) ;
	cout << "PostMessage" <<endl;
	VariantClear(&Msg) ;
	if (FAILED(hr))
		return demoError(5, hr) ;

	// Disconnect from G2
	hr = pAxl->Disconnect() ;
	cout << "Disconnect" <<endl;
	if (FAILED(hr))
		return demoError(6, hr) ;
	}catch(...){
		cerr << "Unexpected exception" <<endl;
		//cin >> i;

	}
	// Release the COM resources
	::CoUninitialize() ;
//	cout << "Press any key to continue" <<endl;
//	getch();

	return 0 ;

}

char* errMsg[] = { "Unable to initialize COM.",
"Unable to create an instance of G2Gateway.", "Failed to specify location of G2.", "Failed to set timeout.", "Failed to connect to G2", "Failed to send message to message board.", "Disconnect from G2 failed."} ;
const int NR_ERR_CODES = sizeof(errMsg)/sizeof(char*) ;

int demoError(int errorCode, HRESULT hr)
{
	int retCode = -errorCode ;
	if (errorCode >= 0 && errorCode < NR_ERR_CODES)
		cerr << errMsg[errorCode] ;
	else
	{
		cerr << "Unknown error code (" << errorCode << ")." ;
		retCode = -NR_ERR_CODES ;
	}
	cerr << " (" << hex << hr << dec << ")." << endl ;
	if (errorCode > 0)
		::CoUninitialize() ;
	return retCode ;
}
