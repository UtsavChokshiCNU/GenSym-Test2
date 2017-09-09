/*----------------------------------------------------------------------
CLASS
   ConnectionCallback

KEYWORDS
   Connection BaseConnectionHandler

AUTHOR
   Allan Scott

DESCRIPTION
   The ConnectionCallback interface is implemented by user code
   to get callbacks in the following circumstances:

   - The underlying GSI context has started
   - The underlying GSI context has paused
   - The underlying GSI context has resumed
   - The underlying GSI context has been reset
   - The underlying GSI context has been shut down
   - An incoming RPC call is received
   - An incoming RPC start has been received
   - An incoming message has been received
   - An error has occurred on the connection

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_CONNECTION_CALLBACK_H
#define _CPP_LINK_CONNECTION_CALLBACK_H

#include "api.h"
#include "Connection.h"
#include "Item.h"

namespace CppLink 
{

class Connection;
class Item;

class API ConnectionCallback
{
 public:
  virtual void contextStarted(Connection& pConnection) = 0;
  virtual void contextPaused(Connection& pConnection) = 0;
  virtual void contextResumed(Connection& pConnection) = 0;
  virtual void contextReset(Connection& pConnection) = 0;
  virtual void contextShutdown(Connection& pConnection) = 0;
  
  virtual void call(ItemArray& pArgs, void *pCallId) = 0;
  virtual void start(ItemArray &pArgs, void *pCallId) = 0;
  virtual void message(char *message, int pLength) = 0;
  virtual void error(int pCode, char *pMessage) = 0;
};



/*----------------------------------------------------------------------
CLASS
   BaseConnectionHandler

KEYWORDS
   ConnectionCallback

AUTHOR
   Allan Scott

DESCRIPTION
   The BaseConectionHandler is a very simple implementation of the
   ConnectionCallback interface.   It prints to standard output
   all the information it receives in callbacks.

LAST MODIFIED
    
----------------------------------------------------------------------*/
class API BaseConnectionHandler: public ConnectionCallback
{
public:
  BaseConnectionHandler();
  ~BaseConnectionHandler();
  
  virtual void contextStarted(Connection& pConnection);
  virtual void contextPaused(Connection& pConnection);
  virtual void contextResumed(Connection& pConnection);
  virtual void contextReset(Connection& pConnection);
  virtual void contextShutdown(Connection& pConnection);
  
  virtual void call(ItemArray& pArgs, void *pCallId);
  virtual void start(ItemArray &pArgs, void *pCallId);
  virtual void message(char *message, int pLength);
  virtual void error(int pCode, char *pMessage);
};
}


#endif // ifndef _CPP_LINK_CONNECTION_CALLBACK_H