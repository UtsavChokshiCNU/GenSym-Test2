/*----------------------------------------------------------------------
CLASS
   Start

KEYWORDS
   RPCAction

AUTHOR
   Allan Scott

DESCRIPTION
   An RPCAction that is used to make a remote procedure start (where no
   return results are expected).
  
LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_START_H
#define _CPP_LINK_START_H

#include "api.h"
#include "RPCAction.h"

namespace CppLink
{

class API Start : public RPCAction
{
  public:
    Start(Connection& pConnection,
      char *pName,
      ItemArray* pArgs);
  virtual ~Start();
  void doAction();
  private:
    static const char * const sFailedToConvertStartArguments;
};

}
#endif // ifndef _CPP_LINK_START_H