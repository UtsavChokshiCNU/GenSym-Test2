/*----------------------------------------------------------------------
CLASS
    ReturnValues

KEYWORDS
    ConnectionAction

AUTHOR
    Allan Scott

DESCRIPTION
    A ConnectionAction that is used to return values back to G2 as
    the result of an incoming remote procedure call.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_RETURN_VALUES_H
#define _CPP_LINK_RETURN_VALUES_H

#include "api.h"
#include "ConnectionAction.h"
#include "Item.h"

namespace CppLink
{

class API ReturnValues : public ConnectionAction
{
public:
  ReturnValues(
    Connection &pConnection,
    ItemArray* pValues,
    void *pCallId);
  ~ReturnValues();
  void doAction();
  void setDeleteValuesOnDeletion(bool pDeleteValuesOnDeletion);
  bool getDeleteValuesOnDeletion();
private:
  ItemArray *mValues;
  gsi_item *mConvertedValues;
  void *mCallId;
  static const char * const sFailedToConvertReturnValues;
  bool mDeleteValuesOnDeletion;
};

}

#endif // ifndef _CPP_LINK_RETURN_VALUES_H
