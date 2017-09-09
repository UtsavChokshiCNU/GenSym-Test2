#include "Call.h"
#include "RPC.h"
#include "Connection.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Call constructor
	//
Call::Call(Connection& pConnection,
           char *pName,
           ItemArray* pArgs) : 
RPCAction(pConnection, pName, pArgs),
mResults(NULL)
{
}
  
	///////////////////////////////////////////
	//
	//  Call destructor
	//
Call::~Call()
{
  
}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

const char * const Call::sFailedToConvertCallArguments = 
"Failed to convert arguments for call";

/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  setPendingCallId
	//
void Call::setPendingCallId(long pPendingCallId)
{
  mPendingCallId = pPendingCallId;
}

	///////////////////////////////////////////
	//
	//  getPendingCallId
	//
long Call::getPendingCallId()
{
  return mPendingCallId;
}

	///////////////////////////////////////////
	//
	//  setResults
	//
void Call::setResults(ItemArray* pResults)
{
  mResults = pResults; 
}

	///////////////////////////////////////////
	//
	//  getResults
	//
ItemArray* Call::getResults()
{
  return mResults;
}

	///////////////////////////////////////////
	//
	//  getNumResults
	//
long Call::getNumResults()
{
  if (mResults)
     return mResults->getSize();
  return 0;
}

  ///////////////////////////////////////////
	//
	//  doAction
	//

void Call::doAction()
{ 
  long numArgs = 0;
  gsi_item *convertedArgs;
  int result = 0;

  ConnectionAction::doAction();
  if (mStatus == ACTION_FAILED) {
    notify();
    if (mDeleteAfterCallback)
      delete this;
    return;
  }
  
  mStatus = ACTION_RUNNING;
  
  // Get a cached RPC declaration or create a new one..
  RPC *rpc = (RPC *) mConnection->declareRemote(mName);
  
  if (mArgs) {
    // Convert the data
    numArgs = mArgs->getSize();
    convertedArgs = gsi_make_items(numArgs);
  
    result = Item::convertArrayToGsi(*mArgs, numArgs, convertedArgs);
  }
  else {
    convertedArgs = gsi_make_items(0);
  }

  if (result)  {
    mErrorCode = result;
    mErrorString = copyErrorString(sFailedToConvertCallArguments);
    
    if (mCallback) {
      mCallback->actionFailed(*this);
    }
    notify();
    if (mDeleteAfterCallback)
      delete this;
  }
  else {
    mConvertedArgs = convertedArgs;
    mConnection->addPendingCall(this);
    
    // Make the RPC call
    gsi_rpc_call_with_count((void *) rpc->getHandle(), mConvertedArgs, 
      numArgs, (void *)mPendingCallId, mConnection->getContextId());  
  }
}

}
