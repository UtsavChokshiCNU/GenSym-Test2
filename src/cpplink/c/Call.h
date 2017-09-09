/*----------------------------------------------------------------------
CLASS
    Call

KEYWORDS
    RPCAction

AUTHOR
    Allan Scott

DESCRIPTION
    Call is an RPCAction that is used to perform remote procedure calls
    that expect return values.
     
LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_CALL_H
#define _CPP_LINK_CALL_H

#include "api.h"
#include "RPCAction.h"

namespace CppLink
{

class API Call : public RPCAction
{
public:
  Call(Connection& pConnection,
    char *pName,
    ItemArray* pArgs);
  virtual ~Call();

  void setPendingCallId(long pPendingCallId);
  long getPendingCallId();
  void setResults(ItemArray* pResults);
  ItemArray* getResults();
  long getNumResults();
  void doAction();
private:
  long mPendingCallId;
  ItemArray *mResults;
  static const char * const sFailedToConvertCallArguments;
};

}

#endif // ifndef _CPP_LINK_CALL_H