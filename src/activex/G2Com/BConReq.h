// BConReq.h: interface for the BConReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCONREQ_H__14AF22C5_4427_11D1_8523_000086078EFB__INCLUDED_)
#define AFX_BCONREQ_H__14AF22C5_4427_11D1_8523_000086078EFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ConnectingRequest.h"

class BConReq : public ConnectingRequest
{
public:
    HANDLE mEventHandle;
    unsigned char errorFlag;
    virtual void complete(void);
    virtual void error(void);
    virtual int prepare(void) ;
    virtual int invoke(void);
    BConReq(GsiContext *Context, TCHAR *InterfaceName, TCHAR *ClassName, TCHAR *Host,
            unsigned short Port, TCHAR *RemoteInitString);
    virtual ~BConReq();
};

#endif // !defined(AFX_BCONREQ_H__14AF22C5_4427_11D1_8523_000086078EFB__INCLUDED_)
