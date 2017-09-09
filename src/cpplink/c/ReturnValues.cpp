#include "ReturnValues.h"
#include "Connection.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  ReturnValues constructor
	//
ReturnValues::ReturnValues(
    Connection& pConnection,
    ItemArray* pValues,
    void *pCallId):
  ConnectionAction(pConnection),
  mValues(pValues),
  mCallId(pCallId),
  mDeleteValuesOnDeletion(false)
{
}

	///////////////////////////////////////////
	//
	//  ReturnValues destructor
	//
ReturnValues::~ReturnValues() 
{
  if (mValues &&
    mDeleteValuesOnDeletion) {
    delete mValues;
  }
}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

const char * const ReturnValues::sFailedToConvertReturnValues = 
"Failed to convert return values";

/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  doAction
	//

void ReturnValues::doAction()
{ 
  int numValues = 0;
  int result = 0;
  gsi_item *convertedArgs;

  ConnectionAction::doAction();    
  if (mStatus == ACTION_FAILED) {    
    if (mCallback) {
      mCallback->actionFailed(*this);
    }
    notify();
    delete this;
    return;
  }
  
  mStatus = ACTION_RUNNING;
  
  // Convert the data
  
  if (mValues) {
    numValues = mValues->getSize();
    convertedArgs = gsi_make_items(numValues);  
    int result = Item::convertArrayToGsi(*mValues, numValues, convertedArgs);
  }
  else {
    convertedArgs = gsi_make_items(numValues);  
  }

  if (result) {
    mErrorCode = result;
    mErrorString = copyErrorString(sFailedToConvertReturnValues);
    mStatus = ACTION_FAILED;
    
    if (mCallback) {
      mCallback->actionFailed(*this);
    }
  }
  else {
    mConvertedValues = convertedArgs;
    
    gsi_rpc_return_values(mConvertedValues, 
      numValues, (void *) mCallId, mConnection->getContextId());
    
    mStatus = ACTION_COMPLETE;
    
    if (mCallback) {
      mCallback->actionCompleted(*this);
    }
  }
  notify();
  delete this;
}

}