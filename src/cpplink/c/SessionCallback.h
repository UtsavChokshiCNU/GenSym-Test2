/*----------------------------------------------------------------------
CLASS
    SessionCallback

KEYWORDS

AUTHOR
    Allan Scott

DESCRIPTION
    It is possible to register a SessionCallback interface on a Session
    object.  The callbacks in the SessionCallback interface are currently
    the same as those in the ConnectionCallback interface but this may change
    in the future.
  
LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_SESSION_CALLBACK_H
#define _CPP_LINK_SESSION_CALLBACK_H

#include "api.h"
#include "ConnectionCallback.h"

namespace CppLink
{
  class API SessionCallback : public ConnectionCallback
  {

  };

  class API BaseSessionHandler: public BaseConnectionHandler
  {
  
  };
}

#endif // ifndef _CPP_LINK_SESSION_CALLBACK_H



