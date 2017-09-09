#include "LinkThread.h"
#include "Utils.h"
#include "gsi_main_cpp.h"

// forward references to GSI functions defined later in the file
void gsi_open_fd(int fd);
void gsi_close_fd(int fd);
void receive_rpc_call(procedure_user_data_type procedure_user_data, 
                      gsi_item *rpc_arguments, 
                      gsi_int count, 
                      call_identifier_type call_identifier);
void receive_rpc_start(void *ud, gsi_item *rpc_arguments, gsi_int count, 
                       call_identifier_type call_identifier); 
 

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/



	///////////////////////////////////////////
	//
	//  LinkThread constructor
	//
LinkThread::LinkThread() :
  mStopFlag(false),
  mLink(NULL),
  mActionQueue(NULL)
{
}

	///////////////////////////////////////////
	//
	//  LinkThread destructor
	//
LinkThread::~LinkThread()
{
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  sNumFds
	//
int LinkThread::sNumFds = 0;


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  init
	//
void LinkThread::init(Link *pLink,
                      ActionQueue *pActionQueue)
{
  int result;
  mLink = pLink;
  mActionQueue = pActionQueue;
  if (result = mTickle.initialize()) {
    // FIND ME. Log an error here.
    Utils::debugLogException(result, "Failed to initialize Tickle object");
  }
  else {
    if (result = mTickle.finalize()) {
      Utils::debugLogException(result, "Failed to finalize Tickle object");    
    }
  }
}


	///////////////////////////////////////////
	//
	//  run
	//
void LinkThread::run()
{
  Action *nextAction;  
      
  sNumFds = 0;  
  GSI_INITIALIZE_DLL_CALLBACKS ;
    
  gsi_set_option(GSI_ONE_CYCLE);
  gsi_set_option(GSI_USER_DATA_FOR_CALLBACKS);
  gsi_set_option(GSI_SUPPRESS_OUTPUT);
      
  gsi_initialize_callbacks("gsi_open_fd",&gsi_open_fd,(char *)0);
  gsi_initialize_callbacks("gsi_close_fd",&gsi_close_fd,(char *)0);
    
  gsi_install_start_context(gsi_start_context);
  gsi_install_reset_context(gsi_reset_context);
      
  gsi_set_pause_timeout(mLink->getPauseTimeout());
   
  StartArgsArray *startArgsObj = mLink->getStartArgs();
 
  int numStartArgs = startArgsObj->getSize();
  char **startArgs = startArgsObj->getArgs();
      
  gsi_start(numStartArgs, (char **) startArgs);
    
  while(! mStopFlag) { 
    gsi_run_loop();
    mTickle.suckData();
    nextAction = mActionQueue->dequeue();
    if (nextAction) {
      nextAction->doAction();
    }
    if (sNumFds) {
      gsi_pause();
    }
    else {
      Sleep(10);
    }
  } 
      
  kill();
}


	///////////////////////////////////////////
	//
	//  tickle
	//
void LinkThread::tickle()
{
    mTickle.tickle();
}

	///////////////////////////////////////////
	//
	//  getTickleFd
	//
int LinkThread::getTickleFd()
{
  return mTickle.getTickleFd();
}


}


using namespace CppLink;

/*******************************************************************/
/**  Standard GSI callbacks.  Note all calls to GSI happen in the 
* GsiContainerThread therefore all callbacks happen in the 
* GSIContainerThread
*/

extern declare_gsi_start_context(gsi_start_context);
extern declare_gsi_reset_context(gsi_start_context);

void gsi_error_handler(gsi_int pContextId,
                       gsi_int pCode,
                       gsi_char *pMessage)
{
  Connection *connection 
    = Connection::findConnection((int)pContextId);

  if (connection) { 
    ConnectionCallback *callback = connection->getCallback();

    if (callback) {
      // FIND ME. Consider copying the message here
      callback->error(pCode, (char *)pMessage);
    }
  }
  else {
    // We were not able to discover which context generated the error.
    // So, we will fire the error event on all context objects
    
    // FIND ME.  Need to implement this case
    Utils::debugLogException(0, "gsi_error_handler: no context\n");
    Utils::debugLogException(0, "ErrorMessage: ");
    Utils::debugLogException(0, pMessage);
    Utils::debugLogException(0, "\n");
  }
}

void gsi_set_up()
{
  Link *link = Link::getInstance();
  // Set options from the link
  OptionsArray *options = link->getOptions();
  int optionsCount = options->getSize();
    
  for (int i=0; i<optionsCount; i++) {
    gsi_set_option(options->option(i));
  }
    
  int pauseTimeout = link->getPauseTimeout();
  gsi_set_pause_timeout(pauseTimeout);
    
  gsi_install_error_handler(&gsi_error_handler);
        
  // Declare local RPCs from the container here
  gsi_rpc_declare_local(&receive_rpc_call, NULL, link->getLocalCallRPCName());
  gsi_rpc_declare_local(&receive_rpc_start, NULL, link->getLocalStartRPCName());

  gsi_watch_fd(link->getWatchFd());
}

gsi_int gsi_get_tcp_port(void)
{
    return Link::getInstance()->getTcpPort();
}

gsi_int gsi_initialize_context(gsi_char *init_string, gsi_int length)
{
  int contextId = gsi_current_context();
      
  long pendingConnectId = 
    (long) gsi_context_user_data(contextId);
      
  Connect *connect = 
    Connect::getPendingConnect(pendingConnectId);
    
  if(! connect) {
    // FIND ME. Log an error here.
    Utils::debugLogException(0, "gsi_initialize_context: getPendingConnect failed.\n");
    return GSI_REJECT;
  }
    
  Connection *connection =
    new Connection(contextId);
    
  connect->setConnection(connection);
      
  connect->setStatus(ACTION_COMPLETE); 
    
  ActionCallback *callback =
    connect->getCallback();
     
  if (callback) {
    callback->actionCompleted(*connect);
  }
    
  Connect::removePendingConnect(pendingConnectId);
  
  connect->notify();
  if (connect->getDeleteAfterCallback())
    delete connect;
  return GSI_ACCEPT;
}

void gsi_receive_registration(gsi_registration reg)
{
}

void gsi_receive_deregistrations(gsi_registered_item regs[], gsi_int count)
{
}

void gsi_get_data(gsi_registered_item regs[], gsi_int count)
{
}

void gsi_set_data(gsi_registered_item regs[], gsi_int count)
{
}

void gsi_pause_context()
{
  Connection *connection =
    Connection::findConnection(gsi_current_context());
  
  if (! connection) {
    return;
  }
  
  ConnectionCallback *callback = 
    connection->getCallback();
  
  if(callback) {
    callback->contextPaused(*connection);
  }
}

void gsi_reset_context()
{
  Connection *connection =
    Connection::findConnection(gsi_current_context());
    
  if (! connection) {
    return;
  }
    
  ConnectionCallback *callback = 
    connection->getCallback();
  
  if (callback) {
    callback->contextReset(*connection);
  }
}

void gsi_start_context()
{
  Connection *connection =
    Connection::findConnection(gsi_current_context());
    
  if (!connection) {
    return;
  }
  ConnectionCallback *callback = 
    connection->getCallback();
    
  if (callback) {
    callback->contextStarted(*connection);
  } 
}

void gsi_resume_context()
{
  Connection *connection =
    Connection::findConnection(gsi_current_context());
  
  if (! connection) {
    return;
  }
  
  ConnectionCallback *callback = 
    connection->getCallback();
  
  if (callback) {
    callback->contextResumed(*connection);
  }
}

void gsi_shutdown_context()
{
  Connection *connection =
    Connection::findConnection(gsi_current_context());
  
  if (! connection) {
    return;
  }
  
  ConnectionCallback *callback = 
    connection->getCallback();
  if (callback) {
    callback->contextShutdown(*connection);
  }
  // Set a flag on the context to say that it has been shutdown.
  connection->setShutdown(true);
}


void gsi_g2_poll()
{
}

void gsi_receive_message(char *message, gsi_int length)
{
  Connection *connection =
    Connection::findConnection(gsi_current_context());
    
  if (!connection) {
    return;
  }
  ConnectionCallback *callback = 
    connection->getCallback();
      
  if (!callback) {
    return;
  }
  callback->message(message, length);
} 

void gsi_open_fd(int fd) 
{
  LinkThread::sNumFds++;
}

void gsi_close_fd(int fd)
{
  LinkThread::sNumFds--;
}


void receive_rpc_call(procedure_user_data_type procedure_user_data, 
                      gsi_item *rpc_arguments, 
                      gsi_int count, 
                      call_identifier_type call_identifier) 
{
  Link *link = Link::getInstance();
  if (! link) {
    // FIND ME. log an error here
    Utils::debugLogException(0, "receive_rpc_call: getInstance failed.\n");
    return;
  }
    
  int contextId = (int) gsi_current_context();
  Connection *connection = Connection::findConnection(contextId);
    if (! connection) {
      // FIND ME. log an error here
      Utils::debugLogException(0, 
        "receive_rpc_call: findContainerContext failed.\n");
      return;
    }
       
    ConnectionCallback *callback = connection->getCallback();
    
    if (!callback) {
      // FIND ME. log an warning here
      Utils::debugLogException(0, "receive_rpc_call: getCallback failed.\n");
      return;
    }
    
    ItemArray *convertedArguments = 
      new ItemArray(count);
    
    int result = Item::convertArrayFromGsi(rpc_arguments, count, *convertedArguments);
     
    if (result) {
      // FIND ME. log an error here
      Utils::debugLogException(0, "receive_rpc_call: convertArrayFromGsi failed.\n");
      return;
    }
      
    callback->call(*convertedArguments, call_identifier);
} 

// void receive_rpc_start(procedure_user_data_type procedure_user_data, gsi_item *rpc_arguments, gsi_int count, call_identifier_type call_identifier) {
void receive_rpc_start(void *ud, gsi_item *rpc_arguments, gsi_int count, 
                       call_identifier_type call_identifier) 
{
  Link *link = Link::getInstance();
  if (! link) {
    // FIND ME. log an error here
    Utils::debugLogException(0, "receive_rpc_start: getInstance failed.\n");
    return;
  }
    
  int contextId = (int) gsi_current_context();
  Connection *connection = Connection::findConnection(contextId);
  if (! connection) {
    // FIND ME. log an error here
    Utils::debugLogException(0, "receive_rpc_start: findContainerContext failed.\n");
    return;
  }
      
  ConnectionCallback *callback = connection->getCallback();
    
  if (!callback) {
    // FIND ME. log an warning here
    Utils::debugLogException(0, "receive_rpc_start: getCallback failed.\n");
    return;
  }
      
  ItemArray *convertedArguments = new ItemArray(count);
      
  int result = Item::convertArrayFromGsi(rpc_arguments, count, *convertedArguments);
    
  if (result) {
    // FIND ME. log an error here
    Utils::debugLogException(0, "receive_rpc_start: convertArrayFromGsi failed.\n");
    return;
  } 
    
  callback->start(*convertedArguments, call_identifier);
}





// This catches errors invoking RPC's to G2.
void receive_rpc_error_handler(gsi_procedure_user_data_type UD,
                               gsi_item *ErrorArgs,
                               gsi_int nArgCount,
                               gsi_call_identifier_type call_identifier)
{
    int contextId = (int) gsi_current_context();
    Connection *connection = Connection::findConnection(contextId);
    if (! connection) {
        // FIND ME. log an error here
      Utils::debugLogException(0, "receive_rpc_error_handler: findContainerContext failed.\n");
        return;
    }
    Call *call = connection->getPendingCall((long) call_identifier);
    if (! call) {
        // FIND ME. log an error here
      Utils::debugLogException(0, "receive_rpc_error_handler: getPendingCall failed.\n");
        return; 
    }
   
    ActionCallback *callback = call->getCallback();
    
    call->setStatus(ACTION_FAILED);
    if (callback) {
        callback->actionFailed(*call);
    }
    if (call->getDeleteAfterCallback())
      delete call;
}

void receive_rpc_return(procedure_user_data_type procedure_user_data, gsi_item *rpc_arguments, 
                        gsi_int count, call_identifier_type call_identifier) 
{
    int contextId = (int) gsi_current_context();
    Connection *connection = Connection::findConnection(contextId);
    if (! connection) {
        // FIND ME. log an error here
        Utils::debugLogException(0, "receive_rpc_return: findConnection failed.\n");
        return;
    }
    Call *call = connection->getPendingCall((long) call_identifier);
     if (! call) {
        //  FIND ME. log an error here
        Utils::debugLogException(0, "receive_rpc_return: getPendingCall failed.\n");
        return; 
    }

    call->setStatus(ACTION_COMPLETE);
    ActionCallback *callback = call->getCallback();

    // Convert the RPC return arguments
    ItemArray *results = new ItemArray(count);
    int result = Item::convertArrayFromGsi(rpc_arguments, count, *results);
 
    if (result) {
      call->setErrorCode(result);
      call->setErrorString("Failed to convert return arguments");
      if (callback)
        callback->actionFailed(*call);
    }
    else {
      call->setResults(results);
      if (callback)
        callback->actionCompleted(*call);
    }
    if (call->getDeleteAfterCallback())
        delete call;
}
