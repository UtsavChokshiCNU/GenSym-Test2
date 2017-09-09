/*----------------------------------------------------------------------
CLASS
    Connect

KEYWORDS
    Connection

AUTHOR
    Allan Scott
   
DESCRIPTION
    Action used to perform a connect to G2

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_CONNECT_H
#define _CPP_LINK_CONNECT_H

#include "LinkAction.h"
#include "LongHashtable.h"
#include "Connection.h"

namespace CppLink
{

class Connection;

class API Connect: public LinkAction
{
 friend class LinkThread;
 public:
  Connect(char *pInterfaceName,
          char *pClass,
          char *pHost,
          char *pPort,
          char *pInitString);
  virtual ~Connect();
  static void initialize();
  static Connect *getPendingConnect(long pId);
  static void removePendingConnect(long pId);
  Connection *getConnection();
  void setConnection(Connection *pConnection);
  void doAction();
 private:
   Connection *mConnection;
   char *mInterfaceName; 
   char *mClass;
   char *mHost;
   char *mPort;
   char *mInitString;
   long mPendingConnectId;
   static long sPendingConnectCounter;
   static LongHashtable sPendingConnects;
   static const char * const sConnectionError;
};

}

#endif // ifndef _CPP_LINK_CONNECT_H