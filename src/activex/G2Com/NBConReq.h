// NBConReq.h: interface for the NBConReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NBCONREQ_H__14AF22C6_4427_11D1_8523_000086078EFB__INCLUDED_)
#define AFX_NBCONREQ_H__14AF22C6_4427_11D1_8523_000086078EFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectingRequest.h"

class NBConReq : public ConnectingRequest
{
public:
    NBConReq(GsiContext *Context, TCHAR *InterfaceName, TCHAR *ClassName, TCHAR *Host,
             unsigned short Port, TCHAR *RemoteInitString);
    virtual ~NBConReq();
    virtual void complete(void);
    virtual void error(void);
    virtual int invoke(void);
    virtual void timeout(void);
};


#endif // !defined(AFX_NBCONREQ_H__14AF22C6_4427_11D1_8523_000086078EFB__INCLUDED_)
