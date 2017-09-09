// RequestObj.cpp: implementation of the RequestObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2Com.h"
#include "Gateway.h"
#include "RequestObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
// #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RequestObj::RequestObj(GsiContext *Context, requestType rt) 
                                 : mpCtx(Context), mState(Queued), mType(rt),
                                   mpPrev2(NULL), mpNext2(NULL), secondIsContained(0),
                                   mpPrevHash2(NULL), mpNextHash2(NULL), mUsedBy(0)
{
    if (mType != ForcedDisconnect)
    {
        mContextObjId = Context->mObjId;
        mTimeout = time(NULL) + Context->mBlockingTimeout;  // when to expire
    }
    else
    {
        mContextObjId = -1 ;
        mTimeout = 30 ;
    }
    static int nextId = 1;
    mObjId = nextId++;
}

RequestObj::~RequestObj()
{
}


long RequestObj::Id()
{
    Gatekeeper      gk(&mLocker) ;
    return mObjId ;
}

GsiContext* RequestObj::getContext()
{
    Gatekeeper      gk(&mLocker) ;
    return mpCtx ;
}

int RequestObj::prepare()
{
    return 0 ;
}

void RequestObj::timeout(void)
{
    return;
}
 
gsi_int RequestObj::GetHash(void)
{
    Gatekeeper      gk(&mLocker) ;
    return Id();
}

void RequestObj::stateToInvoked()
{
    Gatekeeper      gk(&mLocker) ;
    mState = Invoked ;
}

void RequestObj::stateToProcessed()
{
    Gatekeeper      gk(&mLocker) ;
    mState = Processed ;
}

void RequestObj::stateToError()
{
    Gatekeeper      gk(&mLocker) ;
    mState = Error ;
}

bool RequestObj::Ready()
{
    Gatekeeper      gk(&mLocker) ;
    return (mState == Queued) ;
}

bool RequestObj::Done()
{
    Gatekeeper      gk(&mLocker) ;
    return (mState == Processed || mState == Error) ;
}

bool RequestObj::deleteAfterInvoke()
{
    Gatekeeper      gk(&mLocker) ;
    return (mType == Start || mType == RetVals || mType == ForcedDisconnect) ;
}

bool RequestObj::IsForcedDiscon()
{
    return (mType == ForcedDisconnect) ;
}

unsigned char RequestObj::usedBy()
{
    Gatekeeper      gk(&mLocker) ;
    return mUsedBy ;
}

bool RequestObj::usedBy(users userCode)
{
    Gatekeeper      gk(&mLocker) ;
    unsigned char   x = (unsigned char)userCode ;

    mUsedBy |= (x & 0x07) ;
    return true ;
}

bool RequestObj::stopUseBy(users userCode)
{
    Gatekeeper      gk(&mLocker) ;
    unsigned char   x = (unsigned char)userCode ;

    mUsedBy &= (~x & 0x07) ;
    return true ;
}
