/*----------------------------------------------------------------------
CLASS
    RPCAction

KEYWORDS
     Connection ItemArray Call Start

DESCRIPTION
     RPCAction is the superclass of Call and Start and contains the
     configuration that is common to both Call and Start actions.

     To construct an RPCAction a Connection object is needed as is the
     name of the remote procedure to invoke and optionally an ItemArray
     of arguments.


RECLAMATION OF ARGUMENTS
     By default when an RPCAction is deleted it will not delete the
     ItemArray that was passed to it as arguments for the procedure
     call.

     If users wish for the ItemArray of arguments to be deleted 
     automatically then they must call the setDeleteArgsOnDeletion() 
     method with true as the argument.
     
   
LAST MODIFIED

    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_RPC_ACTION_H
#define _CPP_LINK_RPC_ACTION_H

#include "api.h"
#include "ConnectionAction.h"
#include "Item.h"
#include "ItemArray.h"
#include "gsi_main_cpp.h"

namespace CppLink 
{
  
class Connection;
class Item;

class API RPCAction: public ConnectionAction
{
public:
  RPCAction(Connection& pConnection,
            char *pName,
            ItemArray *pArgs = NULL);
  virtual ~RPCAction();
 
  char *getName();
  int getNumArgs();
  ItemArray *getArgs();
  void setDeleteArgsOnDeletion(bool pDeleteArguments);
  bool getDeleteArgsOnDeletion();
protected:
    char *mName;
    ItemArray *mArgs;    
    gsi_item *mConvertedArgs;
    bool mDeleteArgsOnDeletion;
};

}


#endif // ifndef _CPP_LINK_ACTION_H