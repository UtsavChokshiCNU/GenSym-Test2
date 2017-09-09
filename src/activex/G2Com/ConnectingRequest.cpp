// ConnectingRequest.cpp: implementation of the ConnectingRequest class.
//
// This is an abstract class for Connecting Requests.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2Com.h"
#include "Gateway.h"
#include "ConnectingRequest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
// #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConnectingRequest::ConnectingRequest(GsiContext *Context, TCHAR *InterfaceName, 
                    TCHAR *ClassName, TCHAR *Host, unsigned short Port, 
                    TCHAR *RemoteInitString, requestType rt)                
                                                            : RequestObj(Context, rt)
{
    mInterfaceName = InterfaceName;
    mClassName = ClassName;
    mHost = Host;
    mPort = Port;
    mRemoteInitString = RemoteInitString;
    mErrorMessage.m_str = NULL;
}

ConnectingRequest::~ConnectingRequest()
{
}
