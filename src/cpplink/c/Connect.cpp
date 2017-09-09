#include "Connect.h"
#include "ItemArray.h"
#include "gsi_main_cpp.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Connect constructor
	//
Connect::Connect(char *pInterfaceName,
          char *pClass,
          char *pHost,
          char *pPort,
          char *pInitString)
{
  if (!pInterfaceName) {
    mInterfaceName = NULL;
  } else {
    mInterfaceName = new char[strlen(pInterfaceName)+1];
    strcpy(mInterfaceName,pInterfaceName);
  }
  
  if (!pClass) 
    pClass="";
  mClass = new char[strlen(pClass)+1];
  strcpy(mClass,pClass);
  
  if (!pHost) 
    pHost="";
  mHost = new char[strlen(pHost)+1];
  strcpy(mHost, pHost);
        
  if (!pPort) 
    pPort="";
  mPort = new char[strlen(pPort)+1];
  strcpy(mPort, pPort);
  
  if (!pInitString) 
    pInitString="";
  mInitString = new char[strlen(pInitString)+1];
  strcpy(mInitString,pInitString);
}

	///////////////////////////////////////////
	//
	//  Connect destructor
	//
Connect::~Connect()
{
  delete []mInterfaceName;
  delete []mClass;
  delete []mHost;
  delete []mPort;
  delete []mInitString;
}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  sPendingConnectCounter
	//
long Connect::sPendingConnectCounter = 1;

  ///////////////////////////////////////////
	//
	//  sPendingConnects
	//
LongHashtable Connect::sPendingConnects;

  ///////////////////////////////////////////
	//
	//  initialize
	//
void Connect::initialize()
{
  sPendingConnects.initialize(50);
}

  ///////////////////////////////////////////
	//
	//  getPendingConnect
	//
Connect* Connect::getPendingConnect(long pId)
{
  return (Connect *) sPendingConnects.get((void *)pId);
}

  ///////////////////////////////////////////
	//
	//  removePendingConnect
	//
void Connect::removePendingConnect(long pId)
{
  sPendingConnects.remove((void *)pId);
}


const char * const Connect::sConnectionError = "Unable to create connection with G2";


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  getConnection
	//
Connection *Connect::getConnection()
{
  return mConnection; 
}

  ///////////////////////////////////////////
	//
	//  setConnection
	//
 void Connect::setConnection(Connection *pConnection)
 {
   mConnection = pConnection; 
 }

  ///////////////////////////////////////////
	//
	//  doAction
	//
void Connect::doAction()
{
  mStatus = ACTION_RUNNING;
    
  mPendingConnectId = sPendingConnectCounter++;
      
  sPendingConnects.add((void *)mPendingConnectId, (void *)this);
    
  int result =
    gsi_initiate_connection_with_user_data(
    mInterfaceName, 
    mClass,
    FALSE, 
    "TCP/IP", 
    mHost, 
    mPort, 
    mInitString, 
    (void *) mPendingConnectId);
      
  if (result)  {
    ActionCallback* callback = getCallback(); 
        
    mStatus = ACTION_FAILED;
    mErrorCode = result;
    mErrorString = copyErrorString(sConnectionError);

    if (callback) {
      callback->actionFailed(*this);
    }
    notify();
    if (mDeleteAfterCallback)
      delete this;
  }   
}

}