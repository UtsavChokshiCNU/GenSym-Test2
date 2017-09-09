// RetValsReq.h: interface for the RetValsReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RETVALSREQ_H__131E006F_9810_47D6_AAC6_7CA75D9E9B99__INCLUDED_)
#define AFX_RETVALSREQ_H__131E006F_9810_47D6_AAC6_7CA75D9E9B99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RequestObj.h"
#include "Datum.h"

class RetValsReq : public RequestObj  
{
public:
	RetValsReq(GsiContext* pCtx, Datum* pArgs, int iNrArgs, void* pCallId);
	virtual ~RetValsReq();

	int		invoke() ;
	void	complete() ;
	void	error() ;

	long    NrArgs() ; 
	Datum*	ArgsPtr() ;
private:
	void*	mpCallId ;
    Datum*	mpArgs;
    int     mCount;
};

#endif // !defined(AFX_RETVALSREQ_H__131E006F_9810_47D6_AAC6_7CA75D9E9B99__INCLUDED_)
