// GsiContext.h: interface for the GsiContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSICONTEXT_H__14AF22CA_4427_11D1_8523_000086078EFB__INCLUDED_)
#define AFX_GSICONTEXT_H__14AF22CA_4427_11D1_8523_000086078EFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include <string>
//#include <map>    // STL
#include "G2Com.h"
#include "G2Container.h"
#include "Subscription.h"
#include "Datum.h"
#include "RequestObj.h"


typedef gsi_item    GsiItem ;

// Defines for EventCode of CallData class
#define GSI_EVENT_PAUSE         1
#define GSI_EVENT_RESUME        2
#define GSI_EVENT_CONNECT       3
#define GSI_EVENT_DISCONNECT    4
#define GSI_EVENT_RPCSTART      5
#define GSI_EVENT_RPCCALL       6
#define GSI_EVENT_ERROR         7
#define GSI_EVENT_RETURN        8
#define GSI_EVENT_MESSAGE       9
#define GSI_EVENT_RESET        10
#define GSI_EVENT_START        11
#define G2_RESET               12
#define G2_PAUSED              13
#define G2_RUNNING             14
#define G2_RUN_STATE_KNOWN     15
#define G2_ITEM_MODIFIED       16
#define G2_ITEM_DELETED        17
#define G2_ICON_COLOR_CHG      18
#define G2_CUSTOM_EVENT        19
#define G2_WKSPCADD_EVENT      20
#define G2_WKSPCDEL_EVENT      21
#define G2_VALUE_CHG           22
#define G2_SELECTION           23

class ConnectingRequest; // Forward ref
class RPCRequest;
class CG2Gateway;
class CallData;
class RequestObj;
class EventThread;
class G2Item ;
class G2ItemRef ;


class GsiContext : public G2OrbContained
{
public:
    boolean         mIsConnected;
    boolean         mIsRunning;
    boolean         mCtxKilled ;
    EventThread     *mThreadObj;
    G2OrbContainer  Requests;        // Set of outstanding request objects
    G2OrbContainer  Events;
    G2OrbContainer  Items ;
    G2OrbContainer  Subscriptions ;
    G2RunStateType  m_g2RunState;
    int             mContext;
    long            mBlockingTimeout;
    long            mConnReqId;       // 0 if not connecting, or id of request object
    long            mObjId;           // unique object id used for searches

    GsiContext();
    virtual         ~GsiContext();
    boolean         IsRunning(void);
    boolean         IsConnected(void);
    BSTR            ClassName();
    void            ClassName(BSTR);
    BSTR            Host(void);
    void            Host(BSTR);
    BSTR            InterfaceName(void);
    void            InterfaceName(BSTR);
    BSTR            RemoteInitString(void);
    void            RemoteInitString(BSTR);
    int             declareRemote(TCHAR *procName);
    unsigned short  Port(void);
    void            Port(unsigned short);
    bool            g2syms() { return m_g2syms ; }
    G2RunStateType  G2RunState(void)
    {
        return m_g2RunState ;
    }

    Subscription   *FindSubscription(gsi_int handle, bool selectType)
    {
        Subscription   *pCurrentSub = (Subscription*)(Subscriptions.Head) ;

        while (pCurrentSub)
            if (pCurrentSub->m_handle == handle && 
                    (pCurrentSub->m_subscrType == stSelection)==selectType)
                return pCurrentSub ;
            else
                pCurrentSub = (Subscription*)(pCurrentSub->GetNext()) ;
        return NULL ;
    }


    virtual gsi_int GetHash(void)
    {
        return mObjId;
    }

    // used for search

    // Conversion routines to and from SAFEARRAYS
    // These are all static methods on the Gsi Context object, but
    // they really are just global functions.

    static GsiContext *FindContext(void);
    static GsiContext *FindContext(long ObjId);
    static void deepReclaimGsiItems(gsi_item *args, int count);
    static HRESULT ArrayElement2Var(VARTYPE vt, long elNr, void* startOfArray, VARIANT* pOut);
    static HRESULT fixVariant(VARIANT *pVar);
    static HRESULT fixPointer(void **pptr, unsigned short vttype);

    RequestObj *FindRequest(long ObjId);
    G2OrbContainer mRemoteProcMap;

    void FireEventInThread(CallData *);
    void setG2Syms(VARIANT_BOOL vbVal) ;
    VARIANT_BOOL getG2Syms() ;
    void setDiscOnReset(VARIANT_BOOL vbVal) ;
    VARIANT_BOOL getDiscOnReset() ;
    void setContextLimit(long limit);


private:
	bool        m_dor;
	bool        m_g2syms;
    CComBSTR    _mRemoteInitString;
    int         _mPort;
    CComBSTR    _mClassName;
    CComBSTR    _mInterfaceName;
    CComBSTR    _mHost;
};


class CallData : public G2OrbContained
{
public:
    long        CallId;
    VARIANT     DeferredCallId;
    Datum       *mArgs;
    int         mCount;
    CComBSTR    Name;
    long        mContext;       // context object id
    IStream     *Str;
    short       EventCode;
    long        ErrorCode;      // holds GSI error code upon RPC error.
    CComBSTR    ErrorMessage;   // holds GSI error message upon RPC error.
    IUnknown    *mp_item ;

    CallData() : mArgs(NULL), mp_item(NULL)
    {
        VariantInit(&DeferredCallId);
    };

    ~CallData()
    {
        VariantClear(&DeferredCallId);
        if (mArgs)
            delete [] mArgs ;
    }
};

//
// This is the event thread object.  One of these are created for each gsi context object and is shutdown
// when the Close method is called on the control
//
class EventThread
{
public:
    HANDLE mEventHandle;  // event object used to signal object
    IStream *mComStream;  // stream object to marshal com pointer
    IG2Gateway *mGateway;  // pointer to com object
    int mReleaseFlag;        // flag to indicate if the pointer should release
    EventThread(IG2Gateway *);  // constructor with com object
    virtual ~EventThread();
    void runloop(void);
    void releaseObj(void);
    void postEvent(GsiContext *context, CallData *cd);
};

// We maintain a colection of context objects

extern G2OrbContainer Contexts;
extern int EventThreadCount;

#endif // !defined(AFX_GSICONTEXT_H__14AF22CA_4427_11D1_8523_000086078EFB__INCLUDED_)
