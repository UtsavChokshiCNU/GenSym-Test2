/*----------------------------------------------------------------------
CLASS
    ConnectionAction

KEYWORDS
    Action

AUTHOR
    Allan Scott

DESCRIPTION
    A ConnectionAction is an Action which is associated with a 
    specific Connection object.

LAST MODIFIED
    
----------------------------------------------------------------------*/
#ifndef _CPP_LINK_CONNECTION_ACTION_H
#define _CPP_LINK_CONNECTION_ACTION_H

#include "Action.h"

namespace CppLink
{

class Connection;

class API ConnectionAction: public Action
{
public:
  ConnectionAction(Connection& pConnection);
  virtual ~ConnectionAction();
  Connection& getConnection();
  virtual void doAction();
protected:
    Connection *mConnection;
private:
    static const char * const sConnectionShutdown;
};

}


#endif // ifndef _CPP_LINK_CONNECTION_ACTION_H