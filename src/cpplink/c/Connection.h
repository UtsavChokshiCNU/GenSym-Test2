/*----------------------------------------------------------------------
CLASS
    Connection

KEYWORDS
    Connect Disconnect Hashtable ConnectionCallback
  
AUTHOR
    Allan Scott

DESCRIPTION 
    A Connection represents a single connection to a G2 from 
    CppLink.

    Connections are created as a result of successfull completion
    of the Connect action.

    Connections store the underlying GSI context ID.

    When using the Session class the Session class manages a single
    connection.

    Connections may be disconnected by using the Disconnect action.

    Connections manage a Hashtable of RPC objects that have been 
    declared for that connection and Call objects that have
    not yet completed.

    To get callbacks when the state of a connection changes or an
    RPC call or start has been received on a connection users must
    call the setCallback method to set a callback instance that implements
    the ConnectionCallback interface.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_CONNECTION_H
#define _CPP_LINK_CONNECTION_H

#include "api.h"
#include "Call.h"
#include "Start.h"
#include "ReturnValues.h"
#include "Disconnect.h"
#include "RPC.h"
#include "ConnectionCallback.h"
#include "StringHashtable.h"
#include "LongHashtable.h"


namespace CppLink
{

class Call;
class Start;
class ReturnValues;
class Disconnect;
class ConnectionAction;
class ConnectionCallback;
class RPC;

class API Connection
{
 public:
  Connection(int pContextId);
  ~Connection();
  static void initialize();
  static Connection *findConnection(int pContextId);
  static void putConnection(int pContextId,
                            Connection *pConnection);
  int getContextId();
  void setCallback
    (ConnectionCallback *pCallback);
  ConnectionCallback *getCallback();
  RPC *declareRemote(char *pName);
  void addPendingCall(Call *pCall);
  void removePendingCall(Call *pCall);
  Call *getPendingCall(long pId); 
  bool isShutdown();
  void setShutdown(bool pShutdown);
 private:
   static LongHashtable sConnections;
   int mContextId;
   StringHashtable mRpcMap;
   LongHashtable mRpcPendingCalls;
   long mPendingCallIdCounter;
   bool mShutdown;

 protected:
   ConnectionCallback* mCallback;
};

}

#endif // ifndef _CPP_LINK_CONNECTION_H

