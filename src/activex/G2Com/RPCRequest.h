// RPCRequest.h: interface for the RPCRequest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RPCREQUEST_H__14AF22C7_4427_11D1_8523_000086078EFB__INCLUDED_)
#define AFX_RPCREQUEST_H__14AF22C7_4427_11D1_8523_000086078EFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RequestObj.h"
#include "g2string.h"
#include "Datum.h"

class RPCRequest : public RequestObj
{
public:
    RPCRequest(GsiContext *Context, TCHAR *name, Datum *pInArgs, long nrArgsIn, requestType rt);
    virtual ~RPCRequest();

    G2String    mName;
    Datum*      mpArgsIn;
    long        mCount;
    Datum*	    mpRetVals ;
    long		mNrRetVals ;
};

#endif // !defined(AFX_RPCREQUEST_H__14AF22C7_4427_11D1_8523_000086078EFB__INCLUDED_)
