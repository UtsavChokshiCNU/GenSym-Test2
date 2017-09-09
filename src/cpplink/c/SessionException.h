/*----------------------------------------------------------------------
CLASS
    SessionException

KEYWORDS
    Session

AUTHOR
   Allan Scott

DESCRIPTION
	 A SessionException can be thrown from a method in the Session class
   when a failure to perform an underlying action takes place.

   The SessionException wraps an error code and an error message.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_SESSION_EXCEPTION_H
#define _CPP_LINK_SESSION_EXCEPTION_H

#include "api.h"
#include "Session.h"

namespace CppLink
{
  class API SessionException
  {
  public:
    SessionException(Session& pSession,
                     int pCode, 
                     char *pMessage);
    ~SessionException();

    Session& getSession();
    int getErrorCode();
    char * getMessage();

  private:
    Session& mSession;
    int mCode;
    char *mMessage;
  };

}

#endif // ifndef _CPP_LINK_SESSION_EXCEPTION_H



