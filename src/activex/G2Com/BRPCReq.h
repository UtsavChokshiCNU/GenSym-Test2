// BRPCReq.h: interface for the BRPCReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRPCREQ_H__14AF22C8_4427_11D1_8523_000086078EFB__INCLUDED_)
#define AFX_BRPCREQ_H__14AF22C8_4427_11D1_8523_000086078EFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Datum.h"
#include "RPCRequest.h"

class BRPCReq : public RPCRequest
{
public:
    HANDLE			mEventHandle;

    BRPCReq(GsiContext *Context, TCHAR *name, Datum *pArgsIn, long nrArgsIn) ;
    virtual			~BRPCReq();
    virtual int		prepare() ;
    virtual int		invoke(void);
    virtual void	complete(void);
    virtual void	error(void);
	Datum*			RetValPtr() {     Gatekeeper  gk(&mLocker) ; return mpRetVals ; }
	HRESULT			RetVars(VARIANT **ppRetValVar, long *plNrVars);
	HRESULT			RetArrayVar(VARIANT *pRetArrayVar, long *plNrVars);
	long			NrRetVals() {    Gatekeeper  gk(&mLocker) ;  return mNrRetVals ; }
    boolean         mHadError;
};

#endif // !defined(AFX_BRPCREQ_H__14AF22C8_4427_11D1_8523_000086078EFB__INCLUDED_)
