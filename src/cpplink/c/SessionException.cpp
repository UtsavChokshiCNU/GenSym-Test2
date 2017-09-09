#include "SessionException.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/
 
	///////////////////////////////////////////
	//
	//  SessionException constructor
	//
SessionException::SessionException(Session& pSession,
                     int pCode, 
                     char *pMessage) :
mSession(pSession),
mCode(pCode)
{
  mMessage = new char[strlen(pMessage) + 1];
  strcpy(mMessage, pMessage);
}
    
	///////////////////////////////////////////
	//
	//  SessionException destructor
	//
SessionException::~SessionException()
{
  delete [] mMessage;
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  getSession
	//
Session& SessionException::getSession()
{
  return mSession;
}


  ///////////////////////////////////////////
	//
	//  getErrorCode
	//
int SessionException::getErrorCode()
{
  return mCode;
}

  ///////////////////////////////////////////
	//
	//  getMessage
	//
char * SessionException::getMessage()
{
  return mMessage;
}

}

