// GsiContext.cpp: implementation of the GsiContext class.
//
// This class represents a single GSI context.
// Methods on this class handles actions
//
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
//#define _ATL_DEBUG_QI
#endif

#include <process.h>
#include "stdafx.h"
#include "gsi_main_cpp.h"
#include "G2Com.h"
#include "G2Item.h"
#include "Gateway.h"
#include "GsiContext.h"
#include "BRPCReq.h"
#include "RPCRequest.h"
#include "g2string.h"
#include "G2Container.h"
#include "G2ListOrArray.h"
#include "BRPCReq.h"
#include "ForcedDisconReq.h"

G2OrbContainer Contexts;  // Collection of Context objects
int EventThreadCount = 0; // number of event threads still running

// This class is used to quickly find all of the members of a structure
// The problem is that we have no way to see if a member is in a structure
// or not.  gsi_attr_by_name() returns a error if we try to find a structure
// member that is not there.  This way, we can quicly run though all of the
// structures and build a index map to each member and find the members quickly

class StructureMapEl : public G2OrbContained
{
public:
    G2String mName;
    inline virtual TCHAR * GetKey(void)
    {
        return ((TCHAR *) mName);
    };
    StructureMapEl(TCHAR *name)
    {
        mName = name;
    };
    int mIndex;
};

class StructureMapClass : public G2OrbContainer
{
public:
    gsi_attr *mAttrs;
    void Load(gsi_item Item);
    gsi_attr FindByName(TCHAR *name);
};


// Load the structure map with the members of a structure

void StructureMapClass::Load(gsi_item Item)
{
    // Reset all indexes
    StructureMapEl *map;
    for (map = (StructureMapEl *) GetFirst(); map; map = (StructureMapEl *) map->GetNext())
    {
        map->mIndex = -1;
    }
    mAttrs = gsi_attrs_of(Item);
    int count = gsi_attr_count_of(Item);
    for (int i = 0; i < count; i++)
    {
        TCHAR *name = (TCHAR *)gsi_symbol_name(gsi_attr_name_of(mAttrs[i]));
        map = (StructureMapEl *) FindObj(name);
        if (map)
            map->mIndex = i;
    }
}

// Find the attribute object by member name or NULL if not found.
// This is fast and does not throw a error if not found

gsi_attr StructureMapClass::FindByName(TCHAR *name)
{
    StructureMapEl *map = (StructureMapEl *) FindObj(name);
    if (!map)
        return NULL;  // not a mapped name
    if (map->mIndex == -1)
        return NULL; // not in structure
    return mAttrs[map->mIndex];
}


StructureMapClass StructureMap;  // Used to decode special type structures


///////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GsiContext::GsiContext()
{
    static long nextId = 1;
    mObjId = nextId++;  // update unique object id

    mIsConnected = FALSE;
    mIsRunning = TRUE;
    mCtxKilled = TRUE ;
    m_g2RunState = g2UnknownState ;
    _mPort = 1111;                 // Default port
    mConnReqId = 0;
    mBlockingTimeout = 30;       // 30 second timeout
    _mClassName = _T( "G2COM-INTERFACE" );
    _mHost = L"localhost";
    mContext = -1;
    mThreadObj = NULL;
    m_g2syms = false ;
    m_dor = false ;

    // make sure that the structure map is populated
    if (!StructureMap.Count)
    {
        StructureMapEl *map = new StructureMapEl(_T("COM-YEAR"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-MONTH"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-DAY"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-HOUR"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-MINUTE"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-SECOND"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-SEVERITY"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-FACILITY"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-CODE"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-INTEGER"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-LONG"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-FLOAT"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-DOUBLE"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-BYTE"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-DIMENSIONS"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-LOWER-BOUNDS"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-ELEMENTS"));
        StructureMap.Add(map);
        map = new StructureMapEl(_T("COM-ARRAY-TYPE"));
        StructureMap.Add(map);
    }

}

GsiContext::~GsiContext()
{
    ATLTRACE2(atrAxlMethodCalls,3,"GsiContext Destructor!\n");

    if (mCtxKilled == FALSE && mContext > -1)
    {
        ForcedDisconReq     *fdr = new ForcedDisconReq(mContext) ;
        Queue.Add2(fdr) ;
    }
    if (GsiThreadObj)
        EnterCriticalSection(&GsiThreadObj->m_NoVanishingReqs) ;
    RequestObj *pReq = (RequestObj*)Requests.GetFirst() ;
    while(pReq)
    {
        RequestObj  *pNext = (RequestObj*)pReq->GetNext() ;
        Queue.Remove2Only(pReq) ;
        if (GsiThreadObj)
        {
            Requests.RemoveOnly(pReq) ;
            GsiThreadObj->m_OrphanedReqs.Add(pReq) ;
        }
        else
            Requests.Remove(pReq) ;
        pReq = pNext ;
    }
    if (GsiThreadObj)
        LeaveCriticalSection(&GsiThreadObj->m_NoVanishingReqs) ;
}

BSTR GsiContext::ClassName()
{
    return (_mClassName.operator BSTR());
}

void GsiContext::ClassName(BSTR val)
{
    _mClassName = val;
}

BSTR GsiContext::InterfaceName()
{
    return (_mInterfaceName.operator BSTR());
}

void GsiContext::InterfaceName(BSTR val)
{
    _mInterfaceName = val;
}

boolean GsiContext::IsConnected()
{
    return mIsConnected;
}

BSTR GsiContext::Host()
{
    return (_mHost.operator BSTR());
}

void GsiContext::Host(BSTR val)
{
    _mHost = val;
}

BSTR GsiContext::RemoteInitString()
{
    return (_mRemoteInitString.operator BSTR());
}

void GsiContext::RemoteInitString(BSTR val)
{
    _mRemoteInitString = val;
}

unsigned short GsiContext::Port()
{
    return _mPort;
}

void GsiContext::Port(unsigned short val)
{
    _mPort = val;
}


boolean GsiContext::IsRunning()
{
    return mIsRunning;
}


// ========================================================================== //
//                                                                            //
//      The callback function that is called when G2 returns values to an     //
//                             ActiveXLink Call.                              //
//                                                                            //
// ========================================================================== //
void receive_rpc_return (procedure_user_data_type procedure_user_data,
                         gsi_item *rpc_arguments,
                         gsi_int count,
                         call_identifier_type call_identifier)
{

    // Get the BRPCRequest object that is associated with this Call
    // ------------------------------------------------------------
    GsiContext *context = GsiContext::FindContext();
    if (!context)
    {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context for RPC\n");
        return;
    }

    RPCRequest  *req = (RPCRequest*) context->FindRequest((long) call_identifier);
    if (!req) 
    {
        // This will happen if you Started a procedure that returned a value
        // -----------------------------------------------------------------
        if (count)
            ATLTRACE2(atlTraceGeneral,0,"Unable to recover req object for RPC\n");
        return;
    }

    // Convert return values from GSI to Datums 
    // so we can work with them in other threads.
    // ------------------------------------------
    req->usedBy(RequestObj::Callback) ;
    req->mNrRetVals = count;
    req->mpRetVals = (count > 0) ? new Datum [count] : NULL ;
    if (!req->mpRetVals)
        req->mNrRetVals = 0 ; // in case out-of-memory.
    for (long lX = 0 ; lX < count ; lX++)
        req->mpRetVals[lX] = rpc_arguments[lX] ;

    // The BRPCReq complete method will trigger an event to
    // release the hold on G2Gateway::Call in the container thread.
    // ------------------------------------------------------------
    req->complete();
    req->stopUseBy(RequestObj::Callback) ;
}



// This catches errors invoking RPC's to G2.

void receive_rpc_error_handler(gsi_procedure_user_data_type UD,
                               GsiItem *ErrorArgs,
                               gsi_int nArgCount,
                               gsi_call_identifier_type call_identifier)
{
    USES_CONVERSION;

    GsiContext *context = GsiContext::FindContext();
    if (!context) {
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover context\n");
        return;
    }

#ifdef _DEBUG
    if (nArgCount >=2)
    {
        gsi_int t1 = gsi_type_of(ErrorArgs[0]) ;
        gsi_int t2 = gsi_type_of(ErrorArgs[1]) ;
        gsi_char*   etype ;
        gsi_char*   eMsg ;

        if (t1==3)
            etype = gsi_symbol_name(gsi_sym_of(ErrorArgs[0])) ;
        if (t2==4)
            eMsg = gsi_str_of(ErrorArgs[1]) ;
    }
#endif

    // Obtain outstanding request object that triggered the error.
    RPCRequest *req = (RPCRequest *) context->FindRequest((long) call_identifier);
    if (!req) {
        // This would occure if the request object timed out or was removed before
        // gsi returned an error
        ATLTRACE2(atlTraceGeneral,0,"Unable to recover req object for RPC\n");
        return;


    }

    req->usedBy(RequestObj::Callback) ;
    Datum*  pDatumArgs = NULL ;
    if (nArgCount > 0)
        pDatumArgs = new Datum[nArgCount] ;
    if (!pDatumArgs) nArgCount = 0 ;
    for (long lX = 0 ; lX < nArgCount ; lX++)
        pDatumArgs[lX] = ErrorArgs[lX] ;
    req->mpRetVals = pDatumArgs;
    req->mNrRetVals = nArgCount;
    req->error();
    req->stopUseBy(RequestObj::Callback) ;
}


//
// Define a map class to map a string to a integer
//

class RemoteMap: public G2OrbContained {
public:
    G2String mStr;
    int mInt;
    RemoteMap(TCHAR *str, int val ) {mStr = str; mInt = val;};
	RemoteMap(void){}
    ~RemoteMap(void){};
    TCHAR *GetKey(void) {return mStr;};
};



//
// This returns a handle or -1

int GsiContext::declareRemote(TCHAR *procName)

{
    if (!procName)
        return -1 ;
    RemoteMap *map = (RemoteMap *) mRemoteProcMap.FindObj(procName);
    if (map)
        return map->mInt; // got it

    // ok, we have to declare it

    TCHAR buf[1024];
    _tcscpy(buf, procName);
    for (TCHAR *ptr = buf; *ptr; ptr++)
    {
        *ptr = _totupper(*ptr);
    }
    int handle;
    gsi_rpc_declare_remote_with_error_handler_and_user_data((void **) &handle, (gsi_char *)buf,
            &receive_rpc_return, &receive_rpc_error_handler, (void *) this, -1, -1, mContext);
    gsi_set_rpc_remote_return_value_kind((gsi_function_handle_type)handle, -1,(gsi_char *)_T("BY-COPY-WITH-HANDLE")) ;


    gsi_item    *pAttrList = gsi_make_items(5) ;
    gsi_set_sym(pAttrList[0], gsi_make_symbol((gsi_char *)_T("NAMES")) ) ;
    gsi_set_sym(pAttrList[1], gsi_make_symbol((gsi_char *)_T("VALUE-STRUCTURE-USING-UNIX-TIME"))) ;
    gsi_set_sym(pAttrList[2], gsi_make_symbol((gsi_char *)_T("UUID"))) ;
    gsi_set_sym(pAttrList[3], gsi_make_symbol((gsi_char *)_T("FOUNDATION-CLASS"))) ;
    gsi_set_sym(pAttrList[4], gsi_make_symbol((gsi_char *)_T("G2-USER-MODE"))) ;
    gsi_set_rpc_remote_return_include_system_attrs((gsi_function_handle_type)handle, pAttrList) ;

    ATLTRACE2(atrAxlMsgs,4 ,"declared remote\n");
    map = new RemoteMap(procName, handle);
    mRemoteProcMap.Add(map);
	//<Gensym-098> must free memory 
	gsi_reclaim_items(pAttrList);
	//</Gensym-098> must free memory
    return handle;
}


/* ==================================================================================== */
/*                                                                                      */
/* Copy element # elNr from the specified SafeArray of type vt to the specified VARIANT */
/*                                                                                      */
/* ==================================================================================== */
HRESULT GsiContext::ArrayElement2Var(VARTYPE vt, long elNr, void* startOfArray, VARIANT *pOut)
{
    long        elType = vt & VT_TYPEMASK ;
    CComBSTR    helper ;

    switch (elType)
    {
        // integer
    case VT_I2:
        pOut->vt = VT_I2 ;
        pOut->iVal = ((short*)startOfArray)[elNr] ;
        break ;

        // long
    case VT_I4:
        pOut->vt = VT_I4 ;
        pOut->lVal = ((long*)startOfArray)[elNr] ;
        break ;

        // single
    case VT_R4:
        pOut->vt = VT_R4 ;
        pOut->fltVal = ((float*)startOfArray)[elNr] ;
        break ;

        // double
    case VT_R8:
        pOut->vt = VT_R8 ;
        pOut->dblVal = ((double*)startOfArray)[elNr] ;
        break ;

        // currency
    case VT_CY:
        pOut->vt = VT_CY ;
        pOut->cyVal = ((CY*)startOfArray)[elNr] ;
        break ;

        // date
    case VT_DATE:
        pOut->vt = VT_DATE ;
        pOut->date = ((DATE*)startOfArray)[elNr] ;
        break ;

        // text
    case VT_BSTR:
        pOut->vt = VT_BSTR ;
        helper = ((BSTR*)startOfArray)[elNr] ;
        pOut->bstrVal = helper.Copy();
        break ;

        // object
    case VT_DISPATCH:
        pOut->vt = VT_DISPATCH ;
        pOut->pdispVal = ((IDispatch**)startOfArray)[elNr] ;
        pOut->pdispVal->AddRef();
        break ;

        // boolean
    case VT_BOOL:
        pOut->vt = VT_BOOL ;
        pOut->boolVal = ((VARIANT_BOOL*)startOfArray)[elNr] ;
        break ;

        // variant
    case VT_VARIANT:
        VariantCopyInd(pOut,((VARIANT*)startOfArray)+elNr);
        if (pOut->vt == VT_DISPATCH)
            pOut->pdispVal->AddRef() ;
        break ;

        // byte
    case VT_UI1:
        pOut->vt = VT_UI1 ;
        pOut->uiVal =((UCHAR*)startOfArray)[elNr] ;
        break ;

        // The following types are not supported by Visual Basic.  They can,
        // however, be used with C++ clients.
        // -----------------------------------------------------------------

        // signed char
    case VT_I1:
        pOut->vt = VT_I1 ;
        pOut->cVal = ((CHAR*)startOfArray)[elNr] ;
        break ;

        // unsigned short
    case VT_UI2:
        pOut->vt = VT_UI2 ;
        pOut->uiVal = ((USHORT*)startOfArray)[elNr] ;
        break ;

        // unsigned int
    case VT_UI4:
        pOut->vt = VT_UI4 ;
        pOut->ulVal = ((ULONG*)startOfArray)[elNr] ;
        break ;

        // other types are not supported
    default:
        return E_INVALIDARG ;
    }
    return S_OK ;
}


//
// This routine adds the event to the queue of events to be fired
// and signals the event thread to call the control from the
// proper client thread
// This prevents a deadlock condition if the event handler
// touches gsi.
//
// Also, the event is ensured to be called from the proper thread
// in the container.
//
void GsiContext::FireEventInThread(CallData *cd)
{
    ATLTRACE2(atrAxlMsgs,1,"Firing Event\n");

    if (mThreadObj)
        mThreadObj->postEvent(this, cd);
    else
        delete cd;
}

//
// This routine finds the context object of the current context.
//
GsiContext * GsiContext::FindContext(void)
{

    GsiContext *cp = (GsiContext *) Contexts.FindObj((long) gsi_context_user_data(gsi_current_context()));
    return cp;
}



GsiContext * GsiContext::FindContext(long ObjId)
{

    GsiContext *cp = (GsiContext *) Contexts.FindObj(ObjId);
    return cp;
}



void GsiContext::deepReclaimGsiItems(gsi_item *args, int count)

{
    for (int i = 0; i < count; i++)
        gsirtl_free_i_or_v_contents(args[i]);

    gsi_reclaim_items(args);
}


// Find a given request object

RequestObj * GsiContext::FindRequest(long ObjId)
{

    RequestObj *req = (RequestObj *) Requests.FindObj(ObjId);
    return req;
}


//
// Here lies the logic for the event thread.
// This thread is created when the GsiContext object is created
// and is used to signal the control that events are ready
//


//
// Thread entry point fo thread object, just call runloop method
void EventThreadEntry(void * ptr)
{
    ATLTRACE2(atrAxlMsgs,4,"Begining event thread\n");
    EventThread *objptr = (EventThread *) ptr;
    objptr->runloop();
    _endthread();
}



EventThread::EventThread(IG2Gateway * Comptr)
{
    EventThreadCount++;
    CoMarshalInterThreadInterfaceInStream(
        IID_IG2Gateway,
        Comptr,
        &mComStream);
    mGateway = NULL;  // null until we decode it in the thread
    mReleaseFlag = 0; // do not release until we exit
    mEventHandle = CreateEvent(NULL, false, false, NULL);
    _beginthread(EventThreadEntry, 0, this);
}


EventThread::~EventThread()
{
    ATLTRACE2(atrAxlMethodCalls,3,"In EventThread destructor\n");
    CloseHandle(mEventHandle);
    if (mGateway)
        mGateway->Release();
    CoUninitialize();

    //  *** TO DO: make thread-safe
    EventThreadCount--;
}

void EventThread::releaseObj(void)
{
    mReleaseFlag = 1;  // flag that we should release
    SetEvent(mEventHandle);
}

void EventThread::runloop(void)
{

    // we are in the new thread, first demarshal the pointer

    CoInitialize(NULL); // Init thread for COM
    CoGetInterfaceAndReleaseStream(
        mComStream,
        IID_IG2Gateway,
        (void **) &mGateway);
    mComStream = NULL;

    while (1)
    {  // loop forever
        DWORD res = MsgWaitForMultipleObjects(1, &mEventHandle, false, INFINITE, QS_ALLINPUT);
        if (res == (WAIT_OBJECT_0 + 1))
        { // got message
            ATLTRACE2(atrAxlMsgs,4,"Got message! in wait!\n");
            MSG msg;                    // make sure the message is serviced
            if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
            {
                GetMessage(&msg, NULL, 0, 0);
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                ATLTRACE2(atrAxlMsgs,0,"Message, not there\n");
            }
        }
        else
        { // got event
            if (mReleaseFlag)
                break;
            ATLTRACE2(atrAxlMsgs,1,"Calling FireEvents\n");
            mGateway->_FireEvents();
            ATLTRACE2(atrAxlMsgs,1,"Back from FireEvents\n");
        }
    }
    delete this;
    ATLTRACE2(atrAxlMsgs,1,"Ending event thread\n");
}


void EventThread::postEvent(GsiContext *context, CallData *cd)

{
    context->Events.Add(cd);
    SetEvent(mEventHandle);
}


void GsiContext::setG2Syms(VARIANT_BOOL vbVal)
{
    m_g2syms = (VARIANT_FALSE == vbVal) ? false : true ;
}


VARIANT_BOOL GsiContext::getG2Syms()
{
    return (m_g2syms ? VARIANT_TRUE : VARIANT_FALSE) ;
}


void GsiContext::setDiscOnReset(VARIANT_BOOL vbVal)
{
    m_dor = (VARIANT_FALSE == vbVal) ? false : true ;
}


VARIANT_BOOL GsiContext::getDiscOnReset()
{
    return (m_dor ? VARIANT_TRUE : VARIANT_FALSE) ;
}

void GsiContext::setContextLimit(long limit)
{
    gsi_set_context_limit(limit);
}
