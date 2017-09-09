/*----------------------------------------------------------------------
CLASS
    Session

KEYWORDS
    Action Link Connection SessionException
AUTHOR
    Allan Scott

DESCRIPTION
  	The Session class provides a simple interface on top of the rest
    of CppLink that does not require users to create of queue Action
    object.

    A Session can be constructed any time after the Link singleton
    has been started.
      
    The Session object is used to manage a single Connection object.

    To connect to G2 users call the connect() method on the Session
    specifying the interface name, class name, host, port, and initialization
    string to use when establishing the connection.

    The connect method may be specified to take place in a blocking or a
    non-blocking fashion (although currently blocking is only supported).

    Once the connection has been established the Session uses an 
    underlying Connection object to perform the other methods it provides.

    Using a Session object users may Disconnect the connection, perform
    a remote procedure call, perform a remote procedure start and return
    values to an incoming procedure call.

    The example Test class shows how the Session class can be used 
    easily to perform CppLink actions without directly creating or queueing
    them.

    It is possible to register a SessionCallback interface on a Session
    object.  The callbacks in the SessionCallback interface are currently
    the same as those in the ConnectionCallback interface but this may change
    in the future.

ERROR HANDLING
    All methods in the Session object can throw a SessionException.
    If there is a synchronous error in performing an underlying Action
    then a SessionException will be thrown.
    
LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_SESSION_H
#define _CPP_LINK_SESSION_H

#include "api.h"
#include "ConnectionCallback.h"
#include "Connection.h"
#include "SessionCallback.h"
#include "Mutex.h"

namespace CppLink
{
  class SessionException;

  class API Session
  {
    friend class ConnectionCallbackHandler;
    friend class SessionCallbackHandler;

  public:
    Session(SessionCallback* pCallback = NULL);
    ~Session();

    bool isPendingConnect();
    bool isConnected();
    bool isConnecting();
    bool isRunning();
    bool isPaused();
    bool isShuttingDown();
    bool isShutdown();

    void connect(char *pInterfaceName,
      char *pClassName,
      char *pHost,
      char *pPort,
      char *pInitializationString,
      bool pBlock = true,
      ActionCallback* pCallback = NULL);

    void disconnect(bool pBlock = true,
      ActionCallback* pCallback = NULL);
    
    void start(char *pRpcName, 
               ItemArray* pArgs = NULL,
               bool pBlock = false,
               ActionCallback* pCallback = NULL);

    ItemArray* call(char *pRpcName, 
      ItemArray* pArgs = NULL,
      ActionCallback* pCallback = NULL);

    void nonBlockingCall(char *pRpcName, 
      ItemArray* pArgs = NULL,
      ActionCallback* pCallback = NULL);


    void returnValues(void *pCallId,
                      ItemArray* pArgs = NULL,
                      bool pBlock = true,
                      ActionCallback* pCallback = NULL);

    void setCallback(SessionCallback* pCallback);

  private:
    ConnectionCallbackHandler* mHandler;
    SessionCallback* mCallback;
    Connection* mConnection;
    volatile bool mIsConnected;
    volatile bool mIsConnecting;
    volatile bool mIsShuttingDown;
    volatile bool mIsPaused;
    volatile bool mIsShutdown;
    volatile bool mIsRunning;
    Mutex *mMutex;
  };

  class ConnectionCallbackHandler: public ConnectionCallback
  {
   public:
     ConnectionCallbackHandler(Session& pSession);
     ~ConnectionCallbackHandler();

     // Connection callback methods
    virtual void contextStarted(Connection& pConnection);
    virtual void contextPaused(Connection& pConnection);
    virtual void contextResumed(Connection& pConnection);
    virtual void contextReset(Connection& pConnection);
    virtual void contextShutdown(Connection& pConnection);
  
    virtual void call(ItemArray& pArgs, void *pCallId);
    virtual void start(ItemArray& pArgs, void *pCallId);
    virtual void message(char *message, int pLength);
    virtual void error(int pCode, char *pMessage);

   private:
     Session& mSession;
  };

}

#endif // ifndef _CPP_LINK_SESSION_H



