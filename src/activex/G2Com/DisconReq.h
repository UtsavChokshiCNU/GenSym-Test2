// DisconReq.h: interface for the DisconReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCONREQ_H__B0C4D50F_7F24_4EAA_A7E2_114F9AFD76D1__INCLUDED_)
#define AFX_DISCONREQ_H__B0C4D50F_7F24_4EAA_A7E2_114F9AFD76D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RequestObj.h"

class DisconReq : public RequestObj  
{
public:
	HANDLE mEventHandle;
	virtual void timeout();
	virtual void error();
	virtual void complete();
	virtual int invoke();
	DisconReq(GsiContext *pCtxt);
	virtual ~DisconReq();
private:
	UINT mTimerNr;
};

#endif // !defined(AFX_DISCONREQ_H__B0C4D50F_7F24_4EAA_A7E2_114F9AFD76D1__INCLUDED_)
