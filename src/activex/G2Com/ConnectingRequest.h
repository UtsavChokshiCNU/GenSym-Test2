// ConnectingRequest.h: interface for the ConnectingRequest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONNECTINGREQUEST_H__14AF22C2_4427_11D1_8523_000086078EFB__INCLUDED_)
#define AFX_ONNECTINGREQUEST_H__14AF22C2_4427_11D1_8523_000086078EFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RequestObj.h"
#include "g2string.h"    // Added by ClassView

class ConnectingRequest : public RequestObj
{
public:
    G2String mRemoteInitString;
    unsigned short mPort;
    G2String mHost;
    G2String mClassName;
    G2String mInterfaceName;
    CComBSTR mErrorMessage;    // holds GSI error message
    ConnectingRequest(GsiContext *Context, TCHAR *InterfaceName, TCHAR *ClassName, TCHAR *Host,
                        unsigned short Port, TCHAR *RemoteInitString, requestType rt);
    virtual ~ConnectingRequest();
    long     mErrorCode;
};

#endif // !defined(AFX_ONNECTINGREQUEST_H__14AF22C2_4427_11D1_8523_000086078EFB__INCLUDED_)
