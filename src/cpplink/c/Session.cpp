#include "Session.h"
#include "Synchronize.h"
#include "Link.h"
#include "Connect.h"
#include "Start.h"
#include "Call.h"
#include "ReturnValues.h"

#include <string.h>

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Session constructor
	//
Session::Session(SessionCallback* pCallback) :
mConnection(NULL),
mIsConnected(false),
mIsConnecting(false),
mIsShuttingDown(false),
mIsPaused(false),
mIsShutdown(false),
mCallback(pCallback)
{
  mMutex = new Mutex();
  mHandler = new ConnectionCallbackHandler(*this);
}

  ///////////////////////////////////////////
	//
	//  Session destructor
	//
Session::~Session()
{
  // FIND ME. Consider disconnecting the connection
  // here
  delete mMutex;
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  
	//

/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  isConnected()  
	//
bool Session::isConnected()
{
  Synchronize sync = Synchronize(mMutex);
  return 
    (mConnection &&
      ! mConnection->isShutdown() &&
      mIsConnected);
}


	///////////////////////////////////////////
	//
	//  isShutdown()  
	//
bool Session::isShutdown()
{
  Synchronize sync = Synchronize(mMutex);
  return 
    (mConnection &&
      mConnection->isShutdown() &&
      ! mIsConnected);
}

	///////////////////////////////////////////
	//
	//  isConnecting()  
	//
bool Session::isConnecting()
{
  Synchronize sync = Synchronize(mMutex);
  return mIsConnecting;
}

	///////////////////////////////////////////
	//
	//  isRunning()  
	//
bool Session::isRunning()
{
  
  Synchronize sync = Synchronize(mMutex);
  return mIsRunning;
}


	///////////////////////////////////////////
	//
	//  isPaused()  
	//
bool Session::isPaused()
{  
  Synchronize sync = Synchronize(mMutex);
  return mIsPaused;
}

	///////////////////////////////////////////
	//
	//  isShuttingDown()  
	//
bool Session::isShuttingDown()
{  
  Synchronize sync = Synchronize(mMutex);
  return mIsShuttingDown;
}

	///////////////////////////////////////////
	//
	//  setCallback()  
	//
void Session::setCallback(SessionCallback* pCallback)
{
  Synchronize sync = Synchronize(mMutex);
  mCallback = pCallback;  
}

	///////////////////////////////////////////
	//
	//  connect
	//
void Session::connect(char *pInterfaceName,
                      char *pClassName,
                      char *pHost,
                      char *pPort,
                      char *pInitializationString,
                      bool pBlock,
                      ActionCallback* pCallback)
{  
  if (! pBlock) {
    SessionException *exc = new SessionException(*this,
      1,  // Choose a better code here
      "Non Blocking connect is not currently implemented");
    throw *exc;
  }
  if (mIsConnecting) {
    SessionException *exc = new SessionException(*this,
      1,  // Choose a better code here
      "Cannot perform connect session is already connecting");
    throw *exc;
  }
  if (mIsConnected) {
    SessionException *exc = new SessionException(*this,
      1,  // Choose a better code here
      "Cannot perform connect session is already connected");
    throw *exc;
  }

  mIsConnecting = true;
  Link* link = Link::getInstance();
  Connect *connect = 
    new Connect(pInterfaceName,
    pClassName,
    pHost, 
    pPort,
    pInitializationString);

  if (pBlock) {
    connect->setDeleteAfterCallback(false);    
  }

  if (pCallback) {
    connect->setCallback(pCallback);
  }

  link->queueAction(connect);
    
  if (pBlock) {
    connect->waitFor();
    
    if (connect->getErrorCode()) {
        SessionException *exc =
            new SessionException(*this,
            connect->getErrorCode(),
            connect->getErrorString());
        mIsConnecting = false;
        mIsConnected = false;
        delete connect;
        throw *exc;
    }
    else {
      mConnection = connect->getConnection();
      mConnection->setCallback(mHandler);
      delete connect;
    }
  }
}

	///////////////////////////////////////////
	//
	//  disconnect
	//
void Session::disconnect(bool pBlock,
                         ActionCallback* pCallback)
{
  if (! pBlock) {
    SessionException *exc = new SessionException(*this,
      1,  // Choose a better code here
      "Non Blocking disconnect is not currently implemented");
    throw *exc;
  }
  if (mIsShuttingDown || 
    mIsShutdown ||
    ! mConnection) {
    SessionException *exc = new SessionException(*this,
      1,  // Choose a better code here
      "Cannot perform disconnect session is already disconnected");
  }
  
  Link *link = Link::getInstance();
   
  mIsShuttingDown = true;
  Disconnect * disconnect = 
    new Disconnect(*mConnection);

  if (pBlock) {
    disconnect->setDeleteAfterCallback(false);    
  }

  if (pCallback) {
    disconnect->setCallback(pCallback);
  }

  link->queueAction(disconnect);

  if (pBlock) {
    disconnect->waitFor();
    
    if (disconnect->getErrorCode()) {
      SessionException * exc =
          new SessionException(*this,
                           disconnect->getErrorCode(),
                           disconnect->getErrorString());

      delete disconnect;
      mConnection->setCallback(NULL);
      throw *exc;
    }
  }
}

	///////////////////////////////////////////
	//
	//  start
	//    
void Session::start(char *pRpcName, 
                    ItemArray* pArgs,
                    bool pBlock,
                    ActionCallback* pCallback)
{
  if (mIsShuttingDown || 
    mIsShutdown ||
    ! mConnection) {
    SessionException *exc = new SessionException(*this,
      1,  // Choose a better code here
      "Cannot start RPC, session is not connected");
    throw *exc;
  }

  Link* link = Link::getInstance(); 
  Start *start =  new Start(*mConnection,
                            pRpcName,
                            pArgs);

  if (pBlock) {
    start->setDeleteAfterCallback(false);    
  }
  
  if (pCallback) {
    start->setCallback(pCallback);
  }

  link->queueAction(start);
  
  if (pBlock){
    start->waitFor();
    if (start->getErrorCode()) {
      SessionException *exc = 
       new  SessionException(*this,
                         start->getErrorCode(),
                         start->getErrorString());
      delete start;
      throw *exc;
    }
    delete start;
  } 
}

	///////////////////////////////////////////
	//
	//  call
	//    
 ItemArray* Session::call(char *pRpcName, 
   ItemArray* pArgs,
   ActionCallback* pCallback)
{ 
  if (mIsShuttingDown || 
    mIsShutdown ||
    ! mConnection) {
    SessionException *exc = new SessionException(*this,
      1,  // Choose a better code here
      "Cannot make nonBlockingCall session is not connected");
    throw *exc;
  }

  Link* link = Link::getInstance();   

  Call *call =  new Call(*mConnection,
    pRpcName,
    pArgs);

  call->setDeleteAfterCallback(false);

  if (pCallback)
    call->setCallback(pCallback);

  link->queueAction(call);

  call->waitFor();

  if (call->getErrorCode()) {
    SessionException *exc = new SessionException(*this,
      call->getErrorCode(),
      call->getErrorString());
    delete call; 
    throw *exc;
  }

  ItemArray * results =  call->getResults();

  delete call;

  return results;
}

	///////////////////////////////////////////
	//
	//  nonBlockingCall
	//    
 
void Session::nonBlockingCall(char *pRpcName, 
                              ItemArray* pArgs,
                              ActionCallback* pCallback)
{ 
  if (mIsShuttingDown || 
    mIsShutdown ||
    ! mConnection) {
    SessionException *exc
      = new SessionException(*this,
      1,  // Choose a better code here
      "Cannot make nonBlockingCall session is not connected");
    throw *exc;
  }

  Link* link = Link::getInstance();   

  Call *call =  new Call(*mConnection,
    pRpcName,
    pArgs);

  if (pCallback)
    call->setCallback(pCallback);

  link->queueAction(call);
}

	///////////////////////////////////////////
	//
	//  returnValues
	//    
void Session::returnValues(void *pCallId,
                           ItemArray* pArgs,
                           bool pBlock,
                           ActionCallback* pCallback)
{
  if (mIsShuttingDown || 
    mIsShutdown ||
    ! mConnection) {
    SessionException *exc
      = new SessionException(*this,
      1,  // Choose a better code here
      "Cannot make nonBlockingCall session is not connected");
    throw *exc;
  }

  Link* link = Link::getInstance();

  ReturnValues *returnValues = 
    new ReturnValues(*mConnection,
                     pArgs,
                     pCallId);

  if (pBlock) {
    returnValues->setDeleteAfterCallback(false);
  }

  if (pCallback)
      returnValues->setCallback(pCallback);

  link->queueAction(returnValues);

  if (pBlock) {
    returnValues->waitFor();
   
    if (returnValues->getErrorCode()) {
      SessionException *exc = new SessionException(*this,
        returnValues->getErrorCode(),
        returnValues->getErrorString());
      delete returnValues;
      throw *exc;
    }
  }
}


/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  ConnectionCallbackHandler constructor
	//
ConnectionCallbackHandler::ConnectionCallbackHandler(Session& pSession) :
mSession(pSession)
{
}


	///////////////////////////////////////////
	//
	//  ConnectionCallbackHandler destructor
	//
ConnectionCallbackHandler::~ConnectionCallbackHandler()
{
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE METHODS
----------------------------------------------------------------------*/
	///////////////////////////////////////////
	//
	//  contextStarted
	//    
void ConnectionCallbackHandler::contextStarted(Connection& pConnection)
{
  mSession.mConnection = &pConnection;
  mSession.mIsConnected = true;
  mSession.mIsRunning = true;  

  if (mSession.mCallback)
    mSession.mCallback->contextStarted(pConnection);
}

	///////////////////////////////////////////
	//
	//  contextPaused
	//    
void ConnectionCallbackHandler::contextPaused(Connection& pConnection)
{
  mSession.mIsRunning = false;
  mSession.mIsPaused = true;

  if (mSession.mCallback)
    mSession.mCallback->contextPaused(pConnection);
}

	///////////////////////////////////////////
	//
	//  contextResumed
	//    
void ConnectionCallbackHandler::contextResumed(Connection& pConnection)
{
  mSession.mIsRunning = true; 
  if (mSession.mCallback)
    mSession.mCallback->contextResumed(pConnection);
}

	///////////////////////////////////////////
	//
	//  contextReset
	//    
void ConnectionCallbackHandler::contextReset(Connection& pConnection)
{
  mSession.mIsRunning = false;

  if (mSession.mCallback)
    mSession.mCallback->contextReset(pConnection);
}

	///////////////////////////////////////////
	//
	//  contextShutdown
	//    
void ConnectionCallbackHandler::contextShutdown(Connection& pConnection)
{
  mSession.mIsConnected = false;
  mSession.mIsShutdown = true;

  if (mSession.mCallback)
    mSession.mCallback->contextShutdown(pConnection);
}

	///////////////////////////////////////////
	//
	//  call
	//      
void ConnectionCallbackHandler::call(ItemArray& pArgs, void *pCallId)
{
  if (mSession.mCallback)
    mSession.mCallback->call(pArgs, pCallId);
}

	///////////////////////////////////////////
	//
	//  start
	//      
void ConnectionCallbackHandler::start(ItemArray &pArgs, void *pCallId)
{
  if (mSession.mCallback)
    mSession.mCallback->call(pArgs, pCallId);  
}

	///////////////////////////////////////////
	//
	//  message
	//      
void ConnectionCallbackHandler::message(char *pMessage, int pLength)
{
  if (mSession.mCallback)
    mSession.mCallback->message(pMessage, pLength);
}

	///////////////////////////////////////////
	//
	//  error

void ConnectionCallbackHandler::error(int pCode, char *pMessage)
{
  if (mSession.mCallback)
    mSession.mCallback->error(pCode, pMessage);  
}

}
