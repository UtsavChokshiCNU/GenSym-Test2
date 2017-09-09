// ForcedDisconReq.h: interface for the ForcedDisconReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORCEDDISCONREQ_H__EBBE6C8A_0760_4419_B37E_C517015655A1__INCLUDED_)
#define AFX_FORCEDDISCONREQ_H__EBBE6C8A_0760_4419_B37E_C517015655A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RequestObj.h"

class ForcedDisconReq : public RequestObj  
{
private:
    long    m_CtxNr ;
public:
	virtual void complete();
	virtual void error();
	virtual int invoke();
public:
	ForcedDisconReq(long ctxNr);
	virtual ~ForcedDisconReq();
};

#endif // !defined(AFX_FORCEDDISCONREQ_H__EBBE6C8A_0760_4419_B37E_C517015655A1__INCLUDED_)
