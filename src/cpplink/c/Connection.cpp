#include "Connection.h"
#include "Item.h"
#include "ItemArray.h"
#include "RPC.h"
#include "Call.h"
#include "Utils.h"

// Defined in LinkThread
extern void receive_rpc_error_handler(gsi_procedure_user_data_type UD,
                               gsi_item *ErrorArgs,
                               gsi_int nArgCount,
                               gsi_call_identifier_type call_identifier);

extern void receive_rpc_return(procedure_user_data_type procedure_user_data, gsi_item *rpc_arguments, 
                               gsi_int count, call_identifier_type call_identifier); 


namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Connection constructor
	//
Connection::Connection(int pContextId) :
  mContextId(pContextId),
  mCallback(NULL),
  mPendingCallIdCounter(1),
  mShutdown(false) 
{
    mRpcMap.initialize(10);
    mRpcPendingCalls.initialize(50);
    putConnection(pContextId, this);
}


	///////////////////////////////////////////
	//
	//  Connection destructor
	//
Connection::~Connection()
{
    
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  sConnections
	//
LongHashtable Connection::sConnections;


	///////////////////////////////////////////
	//
	//  initialize
	//
void Connection::initialize()
{
    Connection::sConnections.initialize(50);
}

	///////////////////////////////////////////
	//
	//  findConnection
	//
Connection* Connection::findConnection(int pContextId)
{
  // FIND ME. Workaround for bug in hashtable where key is zero
  return (Connection *) sConnections.get((void *)(pContextId + 1)); 
}

	///////////////////////////////////////////
	//
	//  putConnection
	//
void
Connection::putConnection(int pContextId, 
                          Connection *pConnection)
{
  // FIND ME. Workaround for bug in hashtable where key is zero
  sConnections.add((void *)(pContextId + 1), pConnection); 
}


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  getContextId
	//
int Connection::getContextId()
{
  return mContextId;
}

	///////////////////////////////////////////
	//
	//  setCallback
	//
void Connection::setCallback
(ConnectionCallback *pCallback)
{
  mCallback = pCallback;
}

	///////////////////////////////////////////
	//
	//  getCallback
	//
ConnectionCallback *Connection::getCallback()
{
  return mCallback;
}

	///////////////////////////////////////////
	//
	//  isShutdown
	//
bool Connection::isShutdown()
{
  return mShutdown;
}

	///////////////////////////////////////////
	//
	//  setShutdown
	//
void Connection::setShutdown(bool pShutdown)
{
  mShutdown = pShutdown;
}

	///////////////////////////////////////////
	//
	//  addPendingCall
	//
void Connection::addPendingCall(Call* pCall)
{
    mPendingCallIdCounter++;
    pCall->setPendingCallId(mPendingCallIdCounter);
    mRpcPendingCalls.add((void *)mPendingCallIdCounter,
        (void *)pCall); 
}

	///////////////////////////////////////////
	//
	//  removePendingCall
	//
void Connection::removePendingCall(Call* pCall)
{
    mRpcPendingCalls.remove(
        (void *)pCall->getPendingCallId());
}

	///////////////////////////////////////////
	//
	//  getPendingCall
	//
Call* Connection::getPendingCall(long pCallId)
{
  return (Call *) mRpcPendingCalls.get((void *)pCallId);
}

	///////////////////////////////////////////
	//
	//  declareRemote
	//
RPC* Connection::declareRemote(char *pName)
{
  RPC *result = (RPC *) mRpcMap.get(pName);
    
  if (result)
    return result;

  char buf[1024];
  strcpy(buf, pName);
  Utils::toUpper(buf);

  result = (RPC *) mRpcMap.get(buf);
    
  if (result)
    return result;
  
  int handle;

  gsi_rpc_declare_remote_with_error_handler_and_user_data((void **) &handle, buf,
    &receive_rpc_return, &receive_rpc_error_handler, (void *) this, -1, -1, 
    mContextId);
    
  result = new RPC(pName, handle);
  mRpcMap.addKey(pName, (void *) result);
  return result;
}

}


