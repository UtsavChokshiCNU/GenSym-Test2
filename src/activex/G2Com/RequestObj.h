// RequestObj.h: interface for the RequestObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REQUESTOBJ_H__14AF22C1_4427_11D1_8523_000086078EFB__INCLUDED_)
#define AFX_REQUESTOBJ_H__14AF22C1_4427_11D1_8523_000086078EFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class GsiContext; // forward ref

#include "time.h"
#include "G2Container.h"
#include "Lock.h"

enum requestState { Queued, Invoked, Processed, Error } ;

class RequestObj : public G2OrbContained
{
public:
    enum requestType { NBConnect, BConnect, Call, CallDeferred, Start, Disconnect, RetVals, ForcedDisconnect } ;
    enum users       { ContainerThread = 1, ProcessingLoop = 2, Callback = 4 } ;
private:
    long            mObjId;
    requestState    mState ;
    requestType     mType ;
    unsigned char   mUsedBy ;
protected:
    GsiContext*     mpCtx;
    requestType     RequestType() { return mType ; }
public:
    long            mContextObjId;  // ObjId of context, not context number!
    time_t          mTimeout;
    Lock            mLocker;
    unsigned char   secondIsContained ;
    RequestObj*     mpPrev2 ;
    RequestObj*     mpNext2 ;
    RequestObj*     mpNextHash2;
    RequestObj*     mpPrevHash2;

    RequestObj(GsiContext *Context, requestType rt);
    virtual ~RequestObj();

	virtual int     prepare() ;
    virtual int     invoke(void) = 0;
    virtual void    error(void) = 0;
    virtual void    complete() = 0;
    virtual void    timeout(void) ;
    virtual gsi_int GetHash(void) ;
	GsiContext*     getContext();
	long            Id();
	bool            deleteAfterInvoke();
    void            stateToInvoked() ;
    void            stateToProcessed();
    void            stateToError() ;
    bool            IsForcedDiscon() ;
    bool            Ready() ;
    bool            Done() ;
    bool            usedBy(users) ;
    bool            stopUseBy(users) ;
    unsigned char   usedBy() ;

};

#endif // !defined(AFX_REQUESTOBJ_H__14AF22C1_4427_11D1_8523_000086078EFB__INCLUDED_)
