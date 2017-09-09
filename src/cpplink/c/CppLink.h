/*----------------------------------------------------------
LIBRARY
  CppLink

AUTHOR
  Allan Scott

KEYWORDS
  Link Item Attribute ItemArray AttributeArray Connection 
  ConnectionCallback Action ActionCallback Session SessionCallback

OVERVIEW
  CppLink is a thread safe C++ interface to the most commonly used aspects 
  of the non thread safe GSI API.
  
  Users of CppLink interact with G2 using C++ classes that are provided in
  the CppLink library without refering to any symbols in GSI.

  The aspects of GSI that have been added to this API currently are those that 
  were used by ActiveX link version 1.0r7.  Support for the features required by
  ActiveX link 1.1 is expected for G2 8.1 (see the FUTURE DEVELOPMENTS 
  section below).

  CppLink is intended to be portable between platforms - although the initial 
  implementation is for Windows NT/2000/XP only.
   
OVERVIEW OF IMPORTANT CLASSES

   The Link class follows the singleton pattern and is used to 
   initialize CppLink.  The Link class may be configured with
   start up options and with start up arguments that affect how
   CppLink will use the underlying GSI API.

   G2 data is represented in CppLink using the Item class and the
   Attribute subclass.  An Item can represent any G2 type.  An
   Attribute is used to represent an attribute of a structure or
   an Item.

   Arrays of Items and Attributes are managed be the ItemArray and
   AttributeArray objects which wrap an underlying C++ array and include
   information about the size of the array.

   The Connection class represents a connection to a G2.   Users may 
   subscribe to changes in the state of a connection by
   registering on the Connection an object that implements the 
   ConnectionCallback interface.

   CppLink interacts with G2 by performing actions which are represented
   by instances of the Action class.   Subclasses of Action include:
   Connect, Disconnect, Call, Start and ReturnValues.  

   Actions are queued in the singleton Link object. Actions are placed in 
   an internal queue by CppLink.   When an action
   fails (due to an error or a timeout) or completes the result of the 
   action is communicated through the ActionCallback interface.

   Most users will interact with CppLink using the Session class rather
   than by directly constructing and queueing actions themselves.
   The Session class manages the creation and queueing of CppLink
   actions such as Connect, Disconnect, Start, Call and ReturnValues.
   
.
USING CPPLINK

  This section contains a brief overview of how to use 
  CppLink.  For more details on the classes mentioned here see
  their respective documentation pages.  For a complete working
  example that includes the examples below see the Test class
  and project.

  Include the CppLink.h header file, for example:

  #include "CppLink.h"

  Import the symbols in the CPPLink library with a namespace 
  declaration, for example:

  using namespace CppLink;

  
  The singleton Link object needs to be retrieved, 
  for example:


  Link *link = Link::getInstance();


  Users may then choose to configure the options of CppLink using 
  the OptionsArray class or start arguments of CppLink using the
  StartArgumentsArray class, for example:

  link->setOptions(&sOptionsArray);

  link->setStartArgs(&sStartArgsArray);


  If the user wishes to receive starts and calls from G2 then they must
  register the name of the start and call methods that G2 will use 
  when communicating with CppLink,  for example:

  link->setLocalCallRPCName("CppLink-Call");
  link->setLocalStartRPCName("CppLink-Call")

  
  After being configured CppLink may be started. Note that it will only
  ever be started once for a particular executable:

  link->start();

  Most users will interact with CppLink using the Session class.
  The Session class provides the simplest interface to the 
  features of CppLink such as connecting to a G2, disconnecting,
  performing an RPC call or start.

  The example below shows how to perform a blocking connect using
  the Session class:

  Session *session = 
      new Session((SessionCallback *) new BaseSessionHandler());

  session->connect(
      "",
      "GSI-INTERFACE",
      host,
      port,
      "");
      
  Once a Session is connected users may then perform Calls and Starts,
  for example:
   
  ItemArray *result = session->call("GETRESULT");
  
  session->start("CALLME", &itemArray);


CPPLINK EXAMPLE

  An example bridge using CppLink is provided in the Test
  class (Test.h and Test.cpp) which can be built on Windows 
  using the testcpplink workspace.  The example bridge shows
  how to use the Session class to connect to G2 and perform
  starts and calls.
  
  The KB test-cpplink.kb must be loaded in a G2 of version 7.1
  or later.   To connect the example to G2 run the following
  from the commandline:

  testcpplink <host> <port>


ERROR HANDLING
  Error handling in CppLink consists of either synchronous instances of
  SessionException that are thrown from methods in the Session class 
  or asynchronous callbacks to error methods in the ConnectionCallback 
  and ActionCallback interfaces


NAMING CONVENTIONS
  The following variable naming conventions are used throughout 
  CppLink.

  pX  - a parameter to a method or function
  mX  - a member variable of a class
  sX  - a static member variable of a class


RUNTIME REQUIREMENTS
  At runtime make sure the CppLink dynamic library (cpplink.dll) and 
  the Gsi dynamic library (gsi.dll) are on your load path.


TESTING REQUIREMENTS
  A regression test suite for CppLink needs to be developed that will
  cover all the data types, all the possible actions and all the
  likely sequences of actions performed in CppLink.
   

FUTURE DEVELOPMENTS
 
  For G2 version 8.1 item passing and support for unicode will be
  added.  In addition other changes are likely to be made to the
  API as the next version of ActiveXLink uses the API.

  A Unix version of CppLink will also be completed for G2 version
  8.1.

  For versions of G2 beyond 8.1 it is expected that CppLink will
  contain a native implementation of ICP to provide performance
  benefits.


----------------------------------------------------------*/

#ifndef _CPP_LINK_H
#define _CPP_LINK_H

#include "Link.h"
#include "Connection.h"
#include "ItemArray.h"
#include "Item.h"
#include "AttributeArray.h"
#include "Attribute.h"
#include "Action.h"
#include "LinkAction.h"
#include "Connect.h"
#include "ConnectionAction.h"
#include "Disconnect.h"
#include "RPC.h"
#include "Call.h"
#include "Start.h"
#include "ReturnValues.h"
#include "LinkCallback.h"
#include "ConnectionCallback.h"
#include "SessionCallback.h"
#include "ActionCallback.h"
#include "Session.h"
#include "SessionException.h"


/////////////////////////////////////////
//
//  CppLink namespace
//
//  The CppLink namespace contains all the 
//  symbols defined in the CppLink library.
namespace CppLink
{

}

#endif // ifndef _CPP_LINK_H