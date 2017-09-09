// NBRPCReq.h: interface for the NBRPCReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NBRPCREQ_H__14AF22C9_4427_11D1_8523_000086078EFB__INCLUDED_)
#define AFX_NBRPCREQ_H__14AF22C9_4427_11D1_8523_000086078EFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Datum.h"
#include "RPCRequest.h"

class NBRPCReq : public RPCRequest
{
public:
    NBRPCReq(GsiContext *Context, TCHAR *name, Datum *args, int count, requestType rt);
    virtual         ~NBRPCReq();
    virtual void    complete(void);
    virtual void    error(void);
    virtual int     invoke(void);
    virtual void    timeout(void);

    VARIANT         DeferredCallId;
    long            callId;
    long            mErrorCode;

};

#endif // !defined(AFX_NBRPCREQ_H__14AF22C9_4427_11D1_8523_000086078EFB__INCLUDED_)
