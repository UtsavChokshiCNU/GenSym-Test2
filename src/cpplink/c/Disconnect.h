
/*----------------------------------------------------------------------
CLASS
    Disconnect

KEYWORDS
    ConnectionAction Connection

AUTHOR
    Allan Scott
   
DESCRIPTION
    The Disconnect action disconnects an existing Connection.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_DISCONNECT_H
#define _CPP_LINK_DISCONNECT_H

#include "ConnectionAction.h"

namespace CppLink
{

class API Disconnect : public ConnectionAction
{
public:
  Disconnect(Connection& pConnection);
  ~Disconnect();
  void doAction();
};

}

#endif // ifndef _CPP_LINK_DISCONNECT_H
