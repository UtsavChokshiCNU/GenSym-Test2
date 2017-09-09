#include "Start.h"
#include "RPC.h"
#include "Connection.h"
#include "gsi_main_cpp.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Start constructor
	//
Start::Start(Connection& pConnection,
      char *pName,
      ItemArray* pArgs) : RPCAction(pConnection, pName, pArgs)
 {
 }

	///////////////////////////////////////////
	//
	//  Start destructor
	//
Start::~Start() 
{

}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

const char * const Start::sFailedToConvertStartArguments = 
"Failed to convert arguments for start";


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  doAction
	//
void Start::doAction()
{ 
  long numArgs = 0;
  int result = 0;
  gsi_item *convertedArgs;

  ConnectionAction::doAction();
  if (mStatus == ACTION_FAILED) {
    notify();
    if (mDeleteAfterCallback)
      delete this;
    return;
  }
  
  mStatus = ACTION_RUNNING;
    
  // Get a cached RPC declaration or create a new one..
  RPC *rpc = mConnection->declareRemote(mName);
    
  // Convert the data 
  if (mArgs) {
    numArgs = mArgs->getSize();
    convertedArgs = gsi_make_items(numArgs);
    result = Item::convertArrayToGsi(*mArgs, numArgs, convertedArgs);
  }
  else {
    convertedArgs = gsi_make_items(0);
  }
  
  if (result)  {
    mErrorCode = result;
    mErrorString = copyErrorString(sFailedToConvertStartArguments);
    mStatus = ACTION_FAILED;
    if (mCallback) {
      mCallback->actionFailed(*this);
    }
  }
  else {
    mConvertedArgs = convertedArgs;
    // Make the RPC call
    
    gsi_rpc_start_with_count((void *) rpc->getHandle(), mConvertedArgs, 
      numArgs, mConnection->getContextId());
               
    // Release the memory used by the array of gsi_items
    // -------------------------------------------------
    Item::deepReclaimGsiItems(mConvertedArgs, numArgs) ;
    
    mStatus = ACTION_COMPLETE;
    if (mCallback) {
      mCallback->actionCompleted(*this);
    }
  }
  notify();
  if (mDeleteAfterCallback)
    delete this;
} 

}
