// ForcedDisconReq.cpp: implementation of the ForcedDisconReq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ForcedDisconReq.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ForcedDisconReq::ForcedDisconReq(long ctxNr) : RequestObj(NULL, ForcedDisconnect), m_CtxNr(ctxNr)
{

}

ForcedDisconReq::~ForcedDisconReq()
{

}

void ForcedDisconReq::complete()
{
    Gatekeeper  gk(&mLocker) ;
    stateToProcessed() ;
}

void ForcedDisconReq::error()
{
    Gatekeeper  gk(&mLocker) ;
    stateToError() ;
}

int ForcedDisconReq::invoke()
{
    Gatekeeper  gk(&mLocker) ;
    gsi_kill_context(m_CtxNr) ;
    return 0 ;
}

