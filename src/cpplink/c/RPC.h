/*----------------------------------------------------------------------
CLASS
    RPC

KEYWORDS
    Connection Start Call

AUTHOR
    Allan Scott
   
DESCRIPTION
    The RPC class is used to wrap an underlying GSI handle to an 
    RPC that has been declared in GSI.

    The RPC class is used by the Connection class and by the
    Start and Call actions.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_RPC_H
#define _CPP_LINK_RPC_H

#include "api.h"
#include "gsi_main_cpp.h"

namespace CppLink 
{

typedef API gsi_int gint;

class API RPC
{
public:
  RPC(char *pName, gint pHandle);
  ~RPC();
  gint getHandle();
private:
  char *mName;
  gint mHandle;
};

}
#endif // ifndef _CPP_LINK_RPC_H