/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      java_gi.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               06-Jan-97   M.D.Gribble
 +
 + Description:  This file contains the GSI entry points for
 +				 Java GSI
 +
 +
 +
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
 +   ??????? Function existence is questionable.
 +
 +   A function banner may contain the following:
 +      Multiply Defined       Function appears multiple times, each definition
 +                             for an #ifdef specified platform.
 +      Conditionally Defined  Defined for some but not all platforms
 +      Mixed Ifdefs           Single definition for function containing
 +                             platform specific code #ifdef's.
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - Window Management Functions
 +      AFUNCTION		1111111 Conditionally Defined
 +
 +
 + External Interface:
 +
 +
 +
 + Dependencies:
 +      This file contains the functions required for GSI callbacks and
 +		Java native method objects using JNI
 +		If either GSIs API is altered or any Java Gsi native interface
 +		object is changed then file must be re-inspected
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifdef WIN32
#include <winsock2.h>
#endif
#include "jni_gi.h"
#include <memory.h>
#include <sys/types.h>
#ifdef WIN32
#include <time.h>
#include <sys/timeb.h>
#else
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#endif

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  %
  % Section:      DEFINES
  %
  % Description:  Module specific macros defined in this section.
  %
  % Notes:
  %
  % Modifications:
  %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* Predeclare Java Methods called */
#define LOADCLASS_METHODNAME				"loadJavaClass"
#define CREATEINSTANCE_METHODNAME			"createObjectInstanceHandle"
#define GETOBJECTFROMHANDLE_METHODNAME		"getObjectFromHandle"
#define DELETEINSTANCE_METHODNAME			"deleteObjectFromHandle"
/* Predeclared RPC names that G2 can call in this GSI */
#define CREATEJAVAINSTANCE_G2RPCNAME		"CREATE-JAVA-INSTANCE"
#define LOADJAVACLASS_G2RPCNAME				"LOAD-JAVA-CLASS"
#define CALLJAVAMETHOD_G2RPCNAME			"CALL-JAVA-METHOD"
#define DELETEJAVAINSTANCE_G2RPCNAME		"DELETE-JAVA-INSTANCE"

#define RPC_CALL_COMPLETED -1


/*
 * These are private state codes, which is why I have defined them here.
 */
#define JGI_STATE_PAUSED  0
#define JGI_STATE_RESUMED 1
#define JGI_STATE_RESET   2
#define JGI_STATE_STARTED 3
#define JGI_STATE_SHUTDOWN 10

/* hack */
#define GSI_DISABLE_INTERLEAVING  12

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
int fundebug = FALSE;
int fulldebug = FALSE;
int convdebug = FALSE;
int incompleteStubConversion = FALSE;

#ifdef WIN32
time_t currenttime, begintime;
extern void gsi_initialize_for_win32(HANDLE, char*);
extern void enable_network_io_trace();
extern void disable_network_io_trace();
extern void write_network_io_trace(char *);
#endif


JNIEnv *gsiRunLoopThreadEnv= NULL;   /* The Thread environment for GsiRunLoopThread */

#define MAX_CALL_INDEX_START 100
static gsi_int GsiErrorVariable = 0;

#define UNHAND_GLOBAL(ptr) ptr

int gsiRunning = FALSE;

static void jgi_missing_procedure_handler(gsi_char *name);
static void jgi_deregister_context_object(JNIEnv *env, int context);
static void gsi_shutdown_context_with_context(int context);

/*
 * Data structures for profiling
 */

#define MAX_CONCURRENT_CALLS 10

long   *rpc_indices;
int    *ts_call, *ts_return, *ts_done;
int    *dts_wire, *dts_unpack;
int    buffers_ok = FALSE, collect_rpc_stats = FALSE;
int    num_measured_calls = 0, stat_buffer_size = 0;

void save_stat_index (int, int);
int get_stat_index (int);
int jgi_get_timestamp ();
static gsi_int currentContextInJava = -1;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - gsi_watch_fd support
 %
 % Description:
 % 
 % the following three functions are a kluge to handle the fact that on
 % Windows, GSI is unwilling to watch a pipe fd, but only willing to watch
 % a network socket fd.
 %
 % The Windows implementation therefore deals with network connections.
 % Different java threads will call these things at different times, and
 % hopefully everything will work out okay.  The flow of control is that
 % the main GSI loop thread will call the initialize function, kickoff
 % GsiInitializeThread to call the connect function, and then it will call
 % the finalize function.
 %
 % For UNIX, we will have the initialize function create a pipe and assign
 % the fd of the ends of the pipe to tickle_in and tickle_out.  For
 % Windows, the ends of the network connection are assigned.  gsi_watch_fd
 % then gets called on tickle_in.  Then, when java has something for us to
 % do, it tickles GSI (fourth function below), and gsi_pause wakes up.
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


static int tickle_in = -1;
static int tickle_out = -1;
#ifdef WIN32
int listen_socket;
static struct sockaddr_in addr_in;
static unsigned short local_port = 1025;
#endif
JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_initialize_1tickle (JNIEnv * env, jobject caller){
#ifdef WIN32
  long sock_option_return;
  int i,errcode;
  WSADATA data;

  if((errcode=WSAStartup(MAKEWORD(2,2),&data))!=0)
    return errcode;
  listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  
  addr_in.sin_family = AF_INET;
  addr_in.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 
  addr_in.sin_port = htons (local_port);
  for (i = local_port; i < 65536; i++) {
    if (bind(listen_socket, (const struct sockaddr *)&addr_in, sizeof addr_in)) {
      errcode = WSAGetLastError ();
      if ((errcode == WSAEADDRINUSE) || (errcode == WSAEACCES)) {
	local_port++;
	addr_in.sin_port = htons(local_port);
      }else
	return errcode;
    } else
      break;
  }
  if (listen(listen_socket, 1) < 0)
    return WSAGetLastError ();
  if (fulldebug) {printf ("listening on %d\n", local_port); fflush (stdout);}
#else
  int fd[2], devnull;
  pid_t pid;
      
  if (pipe(fd) == -1)
    return errno;
  tickle_in = fd [0];
  tickle_out = fd [1];
  fcntl((tickle_in), F_SETFL, O_NONBLOCK | fcntl ((tickle_in), F_GETFL, 0));
  fcntl((tickle_out), F_SETFL, O_NONBLOCK | fcntl ((tickle_out), F_GETFL, 0));
#endif
  return 0;
}

JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_finalize_1tickle (JNIEnv * env, jobject caller){
#ifdef WIN32

  unsigned long temp = 1;
  int addrlen = sizeof(addr_in);

  tickle_in = accept(listen_socket, (struct sockaddr *)&addr_in, &addrlen);
  if (tickle_in < 0)
    return WSAGetLastError();
  if (ioctlsocket(tickle_in, FIONBIO, &temp)<0)
    return WSAGetLastError();
#else

#endif
  return 0;
}

JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_connect_1tickle (JNIEnv * env, jclass caller) {
#ifdef WIN32
  struct sockaddr_in addr_out;
  struct hostent    *host = NULL;

  if (fulldebug) printf ("connecting to %d\n", local_port);
  addr_out.sin_family = AF_INET;
  addr_out.sin_port = htons (local_port);
  addr_out.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if ((tickle_out = socket(AF_INET, SOCK_STREAM, 0))<0)
    return WSAGetLastError();
  if (connect(tickle_out, (const struct sockaddr *)&addr_out, sizeof addr_out)<0)
    return WSAGetLastError();
#else

#endif
  return 0;
}


JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_tickle_1gsi (JNIEnv *env, jclass intfClass)
{
  if (tickle_out != -1) {
    if (fulldebug) {
      printf ("tickling...\n");
      fflush(stdout);
    }
#ifdef WIN32
    send(tickle_out, "a", 1, 0);
#else
    write(tickle_out, "a", 1);
#endif

  }
}

static char tickle_buffer[100];
static int tickle_count = 0;

void suck_tickle_data ()
{
  int bytes = 0;

#ifdef WIN32
  /* The idea here is to only suck the tickle data out of the pipe
     occasionally, because it turns out to be slow. */
  if (tickle_count > 20) {
    tickle_count = 0;
    bytes = recv(tickle_in, tickle_buffer, 100, 0);
  } else
    tickle_count++;
#else
  bytes=read(tickle_in, tickle_buffer, 100);
#endif
  if (fulldebug && (bytes > 0)) {
    printf ("%d bytes of data read from tickle stream\n", bytes);
    fflush(stdout);
  }
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - GsiThreadLoop Java Object
 %
 % Description:
 %
 %		These functions provide the native interface hooks for the G2LoopThread
 %		Java Object
 %
 % Notes:
 %
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/******** Start of G2LoopThread section */


/*****************************************************************************
 *  G2LoopThread_gsi_1run_1loop
 *
 *   Description:
 *     Java Entry point for gsi network dispatching
 *
 *   Input Arguments:
 *     HJGInterface:		The Java JGInterface calling this function
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_gsi_1run_1loop
  (JNIEnv *env, jobject this_obj, jboolean pauseP)

{
  if (fundebug) {printf("Function G2LoopThread_gsi_run_loop \n"); fflush(stdout);}
  gsiRunning = TRUE;

  /* Record this threads environment, so callbacks can get at it */
  if (gsiRunLoopThreadEnv != NULL && gsiRunLoopThreadEnv != env)
    printf ("gsiRunLoopThreadEnv was %lx, setting to %lx\n", gsiRunLoopThreadEnv, env);
  gsiRunLoopThreadEnv = env;

  /* The gsi_run_loop is set to ONE_CYCLE mode, so that we return to Java after
     some network activity, to ensure that all JNI local references are released
     so the garbage collector can do its work.
     */
  if (pauseP){
    gsi_pause();  /* wait for network activity */
  }
  gsi_run_loop();
  suck_tickle_data ();
  
  if (fundebug) {
    printf("Just out of GSI run loop \n"); 
    fflush(stdout);
  }
  /* return to Java */
}

/******** End of G2LoopThread Section */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - JGInterface Java Object native methods
 %
 % Description:
 %
 %		These functions provide the native interface hooks for the JGInterface
 %		Java Object
 %
 % Notes:
 %
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/******** Start of JGInterface section */

/*****************************************************************************
 * void JGInterface_returnMessage
 *
 *   Description:
 *     Java Entry point for sending a message to a connected G2
 *
 *   Input Arguments:
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_returnMessage
  (JNIEnv *env, jobject this, jstring message, jint context)

{

  gsi_char *buffer = jgi_GetStringChars(env, message);

  if (fundebug) { printf("Function GsiLoopThread_returnMessage, context %d\n",context); fflush(stdout);}

  if (fulldebug)
    {
      /* To print we need non UNICODE chars */
      printf("Sent ");
      jgi_printStr(buffer);
      printf(" to G2 connection %i\n", context);
      fflush(stdout);
    }

  if (gsiRunning)
    gsi_return_message(buffer, context );

  if (buffer) free(buffer);
}


/*****************************************************************************
 * void JGInterface_setGSIContextLimit
 *
 *   Description:
 *     Java Entry point for gsi_set_context_limit
 *
 *   Input Arguments:
 *     int limit
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_setGSIContextLimit
  (JNIEnv *env, jobject this, jint limit)

{
  if (fundebug) {printf("Function GsiLoopThread_setGSIContextLimit (%d)\n",limit); fflush(stdout);}

  if (gsiRunning)
    gsi_set_context_limit(limit);
}


/*****************************************************************************
 * void GsiLoopThread_reportLogBookErrorMessage
 *
 *   Description:
 *     Java Entry point for sending a message to a connected G2
 *
 *   Input Arguments:
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_reportLogBookErrorMessage
  (JNIEnv *env, jobject this, jobject error_symbol, jstring error_message, jint context)

{


  if (fundebug) {printf("Function GsiLoopThread_reportG2LogBookErrorMessage \n"); fflush(stdout);}

  jgi_reportG2LogBookErrorMessage(env, error_symbol, error_message, CALL_HANDLE_OF_START, context );

}





/*****************************************************************************
 * jgi_check_and_return_g2_exception
 *
 *   Description:
 *    Check for any pending exceptions. Report any to G2 and clear
 *
 *   Input Arguments:
 *    env:    The Current JNI environment
 *    context: The context connection to send the error message
 *	
 *   Returns:
 *     JNU_TRUE if an eror has occured
 *   Modifications:
 *****************************************************************************/
jboolean jgi_check_and_return_g2_exception
  (JNIEnv *env, jint context)

{
  static char *error_heading = "Java LINK Exception";
  jobject exception;

  if (fundebug) {printf("Function GsiLoopThread_returnException \n"); fflush(stdout);}

  if (exception = (*env)->ExceptionOccurred(env))
    {
      /* get the exception text that occured */
      jstring message = (*env)->CallObjectMethod (env,
						  exception,
						  throwableClassInfo->toString_MethodID);

      if (fulldebug)
	(*env)->ExceptionDescribe(env);


      if (gsiRunning)
	{

	  jgi_reportG2LogBookErrorMessage(env, NULL, message, CALL_HANDLE_OF_START, context );
	
	}


      (*env)->ExceptionClear(env);

      return JNI_TRUE;

    }

   return JNI_FALSE;
}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_initiateConnection
 *
 *   Description:
 *     Java Entry point for initiating a connection with a G2
 *
 *   Input Arguments:
 *     HJGInterface:		The Java JGInterface calling this function
 *	   interface_name:		The name of the Gsi interface object created
 *	   class_name:			The class_name of a GSI-INTERFACE subclass
 *	   keep_connection:		Not supported
 *	   network:				Specify TCP-IP or DECNET
 *	   host:				The host G2 connection to
 *	   port:				The network port to connection to
 *	   rpis:				The remote process initialisation string
 *	
 *   Returns:
 *     True if the connection is established, false if not
 *   Modifications:
 *****************************************************************************/

JNIEXPORT jboolean JNICALL Java_com_gensym_jgi_GsiLoopThread_initiateConnectionNative
                  (JNIEnv *env,
		   jobject this,
		   jstring interface_name,
		   jstring class_name,
		   jboolean keep_connection,
		   jstring  network,
		   jstring  host,
		   jstring  port,
		   jstring  rpis,
		   jstring  callback_identification,
		   jboolean secure)
{
  int len = 0;
  gsi_char *interface_name_str;
  gsi_char *class_name_str;
  gsi_char *network_str;
  gsi_char *host_str;
  gsi_char *port_str;
  gsi_char *rpis_str;
  long result;
  jstring callback_id_gbl = (*env)->NewGlobalRef(env, callback_identification);

  if (fundebug) {printf("Function GsiLoopThread_initiateConnection (identification %lx)\n", callback_id_gbl); fflush(stdout);}

  interface_name_str = jgi_GetStringChars(env,interface_name);
  class_name_str =     jgi_GetStringChars(env, class_name);
  network_str =        jgi_GetStringChars(env,network);
  host_str =           jgi_GetStringChars(env,host);
  port_str =           jgi_GetStringChars(env,port);
  rpis_str =           jgi_GetStringChars(env,rpis);

  if (secure)
    result = gsi_initiate_secure_connection_with_user_data(interface_name_str,
				    class_name_str,
				    (gsi_int)keep_connection,
				    network_str,
				    host_str,
				    port_str,
				    rpis_str,
				    (context_user_data_type)callback_id_gbl);
  else
    result = gsi_initiate_connection_with_user_data(interface_name_str,
				    class_name_str,
				    (gsi_int)keep_connection,
				    network_str,
				    host_str,
				    port_str,
				    rpis_str,
				    (context_user_data_type)callback_id_gbl);
  if (fulldebug)
    {
      /* need non unicode strings to print */
       printf("Trying to connect to G2\n");
       printf("Interface_name    : '");
       jgi_printStr(interface_name_str); printf("'\n");
       printf("Class_name        : '");
       jgi_printStr(class_name_str); printf("'\n");
       printf("keep_connection   : %d \n", keep_connection);
       printf("Network           : '");
       jgi_printStr(network_str); printf("'\n");
       printf("Host              : '");
       jgi_printStr(host_str); printf("'\n");
       printf("Port              : '");
       jgi_printStr(port_str); printf("'\n");
       printf("Rpis              : '");
       jgi_printStr(rpis_str); printf("'\n");
       fflush(stdout);
       printf("secure            : %d \n", secure);
       fflush(stdout);
    }


  if (interface_name_str) free(interface_name_str);
  if (class_name_str) free(class_name_str);
  if (host_str) free(host_str);
  if (port_str) free(port_str);
  if (rpis_str) free(rpis_str);


  if (result)
    return JNI_FALSE;
  else
    return JNI_TRUE;
}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_closeConnectionNative
 *
 *   Description:
 *     Kill the connection for the given context
 *
 *   Input Arguments:
 *     this:		The Java JGInterface calling this function
 *     context:         The context number of the connection to close
 *	
 *   Returns:
 *     Nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_closeConnectionNative
                  (JNIEnv *env,
		   jobject this,
		   jint context)
{
  if (fundebug) {printf("GsiLoopThread_closeConnectionNative \n"); fflush(stdout);}

  gsi_kill_context(context);

}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_setInterfaceOutput
 *
 *   Description:
 *    Suppress GSI output
 *
 *   Input Arguments:
 *     this:		The Java GsiLoopThread calling this function
 *     set:             true for GSI output on
 *	
 *   Returns:
 *     Nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_setInterfaceOutput
                  (JNIEnv *env,
		   jobject this,
		   jboolean set)
{
  if (fundebug) {printf("GsiLoopThread GsiLoopThread_setGSIOutput \n" ); fflush(stdout);}

  if (gsiRunLoopThreadEnv) {
    if (set)
      gsi_reset_option(GSI_SUPPRESS_OUTPUT);
    else
      gsi_set_option(GSI_SUPPRESS_OUTPUT);
  } else {
    /* We have not started up gsi thread yet*/
    if (set)
      gsi_reset_option(GSI_SUPPRESS_OUTPUT);
    else
      gsi_set_option(GSI_SUPPRESS_OUTPUT);
  }
  
  
}

/*****************************************************************************
 * jgi_deregister_context_object
 *
 *   Description:
 *     Unassocaite a java object as the context object associated with
 *     context connection (connection has been closed or invalid).
 *
 *   Input Arguments:
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

static void jgi_deregister_context_object
  (JNIEnv *env, int context)
{
  if (fundebug) {printf("Function jgi_deregister_context_object (context %d)\n", context); fflush(stdout);}

  if (contextDataLookup != NULL && context < contextDataLookup_Size) {
 
    if (contextDataLookup[context] != NULL) {
      /* loose global reference to old context _object */
      (*env)->DeleteGlobalRef(env, (JREF(contextDataLookup[context])));  
      JREF(contextDataLookup[context]) = NULL;
    }
  }
}
  

/*****************************************************************************
 * jgi_register_context_object
 *
 *   Description:
 *     Associate a java object as the context object associated with
 *     context connection
 *
 *   Input Arguments:
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_nativeRegisterContextObject
  (JNIEnv *env, jobject this_obj, jobject context_object, jint context, jstring jremote_string)
{
  ContextData contextData;
  int i;
  jstring jconnection_id;

  if (fundebug) {printf("Function jgi_register_context_object (context %d) \n", context); fflush(stdout);}

  if (contextDataLookup == NULL)
    {
      contextDataLookup = (ContextData *)malloc(sizeof(ContextData *) * 20);
      contextDataLookup_Size = 20;
      for (i=0; i<contextDataLookup_Size; i++)
	{
	  contextDataLookup[i] = (ContextData)malloc(sizeof(struct ContextData_Struct));
	  JREF(contextDataLookup[i]) = NULL;
	}
    }


  if (context >= contextDataLookup_Size)
    {
      int new_contextDataLookup_Size = contextDataLookup_Size + context;
      contextDataLookup = (ContextData *)realloc(contextDataLookup,
						 sizeof(ContextData *) * new_contextDataLookup_Size);
      for (i=contextDataLookup_Size; i<new_contextDataLookup_Size; i++)
	{
	  contextDataLookup[i] = (ContextData)malloc(sizeof(struct ContextData_Struct));
	  JREF(contextDataLookup[i]) = NULL;
	}

      contextDataLookup_Size = new_contextDataLookup_Size;
    }


  /* We may be reusing a context */
  /* loose global reference to old context _object */
  if (JREF(contextDataLookup[context]) != NULL)
    (*env)->DeleteGlobalRef(env, (JREF(contextDataLookup[context])));

  contextData = contextDataLookup[context];

  contextData->clazz = (*env)->GetObjectClass(env, context_object);

  contextData->context = context;

  contextData->receiveRegistrations = JNI_TRUE;
  contextData->authorizedforjlp = JNI_FALSE;
  contextData->authorizedforjl  = JNI_FALSE;

  JREF(contextData) = (*env)->NewGlobalRef(env, context_object);

  /* fprintf (stdout, "Context = %lx (%lx)\n", contextData, JREF(contextData));
     jgi_describeJavaObject (env, JREF(contextData));
     jgi_describeJavaObject (env, contextData->clazz); */
  

  /**
   * Warning, Item getG2Stub(Symbol, int, G2Access, Structure) and
   *          void invalidateG2Stub(int, G2Access)
   * must be availbale on the context object...i.e. currently G2Gateway
   * It would be ideal if we defined an interface that context_data must declare
   * but that would mean making these methods public !
   */

  contextData->createStub_MethodID = (*env)->GetMethodID(env,
							 contextData->clazz,
							 "getG2Stub",
							 "(Lcom/gensym/util/Symbol;ILcom/gensym/jgi/G2Access;Lcom/gensym/util/Structure;Z)Lcom/gensym/classes/Item;");
  /* printf ("Got StubCreation Method = %lx\n", contextData->createStub_MethodID); */
  /* PRINT_EXCEPTION (env); */

  contextData->invalidateStub_MethodID = (*env)->GetMethodID (env,
							      contextData->clazz,
							      "invalidateG2Stub",
							      "(ILcom/gensym/jgi/G2Access;)V");
  /* printf ("Got StubInvalidation Method = %lx\n", contextData->invalidateStub_MethodID); */
  /* PRINT_EXCEPTION (env); */

  contextData->remoteInitString = (*env)->NewGlobalRef(gsiRunLoopThreadEnv, jremote_string);



  jconnection_id =
    (jstring)gsi_context_user_data(context);

  if (jconnection_id) {
    (*gsiRunLoopThreadEnv)->DeleteGlobalRef(gsiRunLoopThreadEnv, jconnection_id);
    gsi_set_context_user_data(context, NULL);
  }

  /** send of asychronous checks for authorization javalink and jlp */
  /* what this seems to end up doing is finishing the initialization of
     the connection by calling G2, which then calls the C callback
     gsi_check_valid_connection_callback which calls the java callback
     JGInterface.G2InitializeConnection.  
     Can you say "needs marinara sauce"? */
  Java_com_gensym_jgi_GsiLoopThread_checkHandleType(env,
						    NULL,
						    context,
						    0); /* Javalink */
  Java_com_gensym_jgi_GsiLoopThread_checkHandleType(env,
						    NULL,
						    context,
						    1); /* JLP */


}


/*****************************************************************************
 * void gsi_jgi_error_handler
 *										
 *   Description:
 *     JGI GSI error handler, called by GSI when errors occur
 *
 *   Input Arguments:
 *     error_context:   context where the context occurred
 *     error_code:      error code associated with the error
 *     error_message:   error message asscociated with the error
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
static void gsi_jgi_error_handler (gsi_int error_context,
				   gsi_int error_code,
				   gsi_char *gsi_error_message)
{
jstring jerror_message;
jobject initId;
jobject initiatingConnectionId = NULL;

#ifdef GSI_USE_WIDE_STRING_API
  char *error_message = jgi_unicode2str(gsi_error_message);
#else
  char *error_message = gsi_error_message;
#endif

  if (fundebug) {
    printf("Function gsi_jgi_error_handler, error was \n %s \n", error_message);
    printf("Call identifier, error was \n %lx \n", gsi_last_error_call_handle());
    fflush(stdout);
  }

  jerror_message = jgi_NewString(gsiRunLoopThreadEnv, gsi_error_message );

  initiatingConnectionId = (jstring)gsi_context_user_data(error_context);

  /* Special case during a connection error, we have no context
   * but may have a connection id from the client initiateConnection
   */
  if (initiatingConnectionId != NULL &&
      (error_code == GSI_INVALID_NETWORK_COMBO ||
       error_code ==  GSI_INVALID_TCP_PORT_NUMBER ||
       error_code == GSI_INVALID_NETWORK_ADDRESS ||
       error_code == GSI_CONNECTION_DENIED ||
       error_code == GSI_ERROR_IN_CONNECT))
    initId = initiatingConnectionId;
  else
    initId = NULL;

  (*gsiRunLoopThreadEnv)->CallVoidMethod(gsiRunLoopThreadEnv,
					 JREF(registeredJGInterface),
					 registeredJGInterface->communicationError_MethodID,
					 (jint)error_context,
					 (jint)error_code,
					 jerror_message,
					 initId);

  if (initId != NULL) {
    /* finished with globalref, created during initiate_connection */
    (*gsiRunLoopThreadEnv)->DeleteGlobalRef(gsiRunLoopThreadEnv, initId);
    gsi_set_context_user_data(error_context, NULL);
  }

#ifdef GSI_USE_WIDE_STRING_API
  free(error_message);
#endif


}


/*****************************************************************************
 * void jgi_get_defined_context_object
 *										
 *   Description:
 *     Return the context object associated with a given context even if the
 *     the Java context is not available
 *
 *   Modifications:
 *****************************************************************************/
ContextData jgi_get_contextData(JNIEnv *env, gsi_int context)
{
short error = 0;

 if (fundebug) {printf("Function jgi_get_contextData for context %d \n", context);fflush(stdout);}


  if (context >= contextDataLookup_Size)
    return NULL;
  else if (contextDataLookup == NULL )
    return NULL;
  else if (contextDataLookup[context] == NULL)
    return NULL;
  else 
    return contextDataLookup[context];
}

/*****************************************************************************
 * void jgi_get_context_object
 *										
 *   Description:
 *     Return the context object associated with a given context
 *
 *   Modifications:
 *****************************************************************************/
ContextData jgi_get_context_object(JNIEnv *env, gsi_int context)
{
short error = 0;

  if (fundebug) printf("Function jgi_get_context_object for context %d \n", context);


  if (context >= contextDataLookup_Size)
    error = 1;
  else if (contextDataLookup == NULL )
    error = 1;
  else if (contextDataLookup[context] == NULL)
    error = 1;
  else if (JREF(contextDataLookup[context]) == NULL)
    error = 1;

  if (fulldebug && !error)
    {
      fprintf (stdout, "Found context object %lx (%lx).\n", contextDataLookup[context], JREF(contextDataLookup[context]));
      fflush (stdout);
    }

  if (error)
    {
      THROW_G2COMS_EXCEPTION(env, "Cant find context object for context \n");

      FULLDEBUG_PRINT_EXCEPTION(env);

      return NULL;
    }
  else
    return contextDataLookup[context];

}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_startInterface
 *
 *   Description:
 *     Java Entry point for statring GSI
 *
 *   Input Arguments:
 *     HJGInterface:		The Java JGInterface calling this function
 *     Hjava_lang_string:	The message to be send (as a java string)
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_startInterface
  (JNIEnv *env, jobject gsi_interface, jobject jgi_interface, jarray java_args)
{

  gsi_int argc = (gsi_int)((*env)->GetArrayLength(env, (jarray)java_args));
  char **argv = (char **)malloc((argc + 1) * sizeof(char *));
  jstring vobj;
  int i;

  if (fundebug) {printf("Function GsiLoopThread_startInterface \n"); fflush(stdout);}

  if (!argv)
    {
      fprintf (stderr, "Error in Java_com_gensym_jgi_GsiLoopThread_startInterface : Cant Malloc !!!!.");
      fflush  (stderr);
      return;
    }

  for (i = 0; i < argc; i++)
    {
      /* Get the String representing the Java String */
      vobj = (*env)->GetObjectArrayElement(env, java_args, (jsize)i);
      if (vobj)
	{
	  argv[i+1] = (char *)((*env)->GetStringUTFChars(env, vobj, NULL));
	}
      else
	argv[i+1] = "";
    }


  argv[0] = "gsi"; /* standard "c" commandline has first parameter as exec command */
  argc = argc + 1;


  /*
   *  Set the version control variables to the values defined in gsi_main.h.
   *  Though optional, this is recommended to ensure version consistency between
   *  the GSI object libraries, and the include file used to compile your
   *  application code.
   */
  gsi_include_file_major_version = GSI_INCLUDE_MAJ_VER_NUM;
  gsi_include_file_minor_version = GSI_INCLUDE_MIN_VER_NUM;
  gsi_include_file_revision_version = GSI_INCLUDE_REV_VER_NUM;

  /* #define USE_ASYNCSELECT_ON_WINDOWS */

#if defined(USE_ASYNCSELECT_ON_WINDOWS) && defined(WIN32)
  {
    HANDLE hInstance;
    /* Initialize gsi on win32 only */
    hInstance = GetModuleHandle (NULL);
    gsi_initialize_for_win32(hInstance, "");
  }
#endif

  /* Install error variable */
  gsi_initialize_error_variable(&GsiErrorVariable);

  /* Install a missign procedure handler */
  gsi_install_missing_procedure_handler(jgi_missing_procedure_handler);

  /* Set the GSI run loop to one_shot so we return to java for this call and after each
     gsi_run_loop activity, this ensures that local JNI references are deallocated
     on return to Java */
  gsi_set_option(GSI_ONE_CYCLE);

  gsi_set_option(GSI_DISABLE_INTERLEAVING);

  gsi_set_option (GSI_NO_SIGNAL_HANDLERS);

  /*  gsi_set_option(GSI_TRACE_RUN_STATE); */

  /* Set up callbacks for the START and RESET state changes.
     This is new in G2/GSI 5.0 Rev. 3
     */
  gsi_install_start_context (&gsi_start_context);

  gsi_install_reset_context (&gsi_reset_context);

#if defined(GSI_USE_WIDE_STRING_API)
  gsi_set_option(GSI_WIDE_STRING_API);
#endif

#if defined(GSI_USE_NEW_SYMBOL_API)
  gsi_set_option(GSI_NEW_SYMBOL_API);
#endif


#if defined(GSI_USE_USER_DATA_FOR_CALLBACKS)
  gsi_set_option(GSI_USER_DATA_FOR_CALLBACKS);
#endif

#if defined(GSI_DO_NOT_REFORMAT_MESSAGES)
  gsi_set_option(GSI_DO_NOT_REFORMAT_MESSAGES);
#endif

  /* Ensure that all strings are converted to "c" string characters */
  gsi_set_option(GSI_STRING_CHECK);

  /* Register the gsi JGInterface and load classes information used by JGI */

  construct_pre_lookup_class_information(env, jgi_interface,gsi_interface);

  /* the gsi dispatch needs a thread env */
  if (gsiRunLoopThreadEnv != NULL && gsiRunLoopThreadEnv != env)
    printf ("gsiRunLoopThreadEnv was %lx, setting to %lx\n", gsiRunLoopThreadEnv, env);
  gsiRunLoopThreadEnv = env;

  /* Can only handle errors after we have looked up class info */
  gsi_install_error_handler(&gsi_jgi_error_handler);

  gsi_start(argc,argv);

  /* There is a chance that we will get Memory Messages from GSI when 
     GSI symbols are assigned here so we turn GSI OUTPUT OFF */
  gsi_set_option(GSI_SUPPRESS_OUTPUT);
  construct_pre_lookup_symbol_gsi_information(env);

  /* must release chars message converted from jstring */
  for (i = i; i < (argc-1); i++)
    {
      vobj = (*env)->GetObjectArrayElement(env, java_args, (jsize)i);
      if (vobj && argv[i+1])
	  (*env)->ReleaseStringUTFChars(env, vobj, argv[i+1]);
    }


  /* We only enter the gsi_run_loop when there is activity, after waiting for the pause timeout */
  /* gsi_set_pause_timeout (24*60*60*1000); 24hours */
  gsi_set_pause_timeout (1000); /* MDG - 1 second wakeup, as GSI (5.1rev1) locks in 
					 select when sending large amounts of data to G2 */

  gsi_watch_fd (tickle_in);
  if (fulldebug)
    printf("GSI started ok... \n");

}


/*****************************************************************************
 * JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_getCurrentContext
 *										
 *   Description:
 *     Return the current operational GSI context
 *
 *   Input Arguments:
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_getCurrentContext
					 (JNIEnv *env, jobject hthis)
{
  if (fundebug) {
    printf ("GsiLoopThread_getCurrentContext called. Returning %d.\n",
				 gsi_current_context ());
    fflush (stdout);
  }
  return (jint)gsi_current_context ();
}

/*****************************************************************************
 * JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_getListenerSocket
 *										
 *   Description:
 *     Return the socket that GSI is listening for connections
 *
 *   Input Arguments:
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_getListenerSocket
					 (JNIEnv *env, jobject hthis)
{
  if (fundebug) {
    printf ("GsiLoopThread_getlistenerSocket called. Returning %d.\n",
				 gsi_listener_socket());
    fflush (stdout);
  }
  return (jint)gsi_listener_socket();
}

/*****************************************************************************
 * JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_returnRPCValue
 *										
 *   Description:
 *     Returns an java method return value to an outstanding RPC.
 *
 *   Input Arguments:
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_returnRPCValue
					 (JNIEnv *env,
					  jobject hthis,
					  jlong call_index,
					  jobject RPC_return_value,
					  jboolean force_return_value,
					  jboolean error,
					  jobject error_symbol,
					  jstring error_text,
					  jint context)
{
  jvalue jval;
  jval.l = RPC_return_value;

  if (fundebug) {
    printf ("Function GsiLoopThread_returnRPCValue, context %d\n",context);
    fflush (stdout);
  }

  return_gsi_values_from_java_method_call(env,
					  jval,
					  force_return_value,
					  JAVA_LANGOBJECT_SIGNATURE,
					  (gsi_int)call_index,
					  error,
					  error_symbol,
					  error_text,
					  context);

}

/*****************************************************************************
 * void gsi_missing_rpc_local_call_function(gsi_item args[], gsi_int cnt)
 *										
 *   Description:
 *     Generic G2 entry point for calling handling a local proc that has not
 *     been defined
 *
 *   Input Arguments:
 *     declared_user_data:              user data defined on declaration of local
 *     args:				The arguments to passed to the Java Method
 *     gsi_int:				The count of the number of arguments
 *	   call_handle			Handle of the call instance
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/


static void gsi_missing_rpc_local_call_function(void *declared_user_data,
					   gsi_item args[],
					   gsi_int cnt,
					   gsi_int call_handle)
{
  /* So we are strict, and force all Java methods to be pre declared */
  /* release the G2 call with an error message */

  JNIEnv *env = gsiRunLoopThreadEnv;
  gsi_item *transient_gsi_items = gsi_make_items(2);
  gsi_char *value;
  gsi_char *g2_name = (gsi_char *)declared_user_data;

  if (fundebug) {printf("gsi_missing_rpc_local_call_function \n"); fflush(stdout);}

    if (transient_gsi_items)
      {

	gsi_symbol errorsym;
	gsi_char *cstr;
	int size1;
	int size2;

	/* Have no error symbol send a NONE string */
#ifdef  GSI_USE_WIDE_STRING_API
	value = jgi_str2unicode("RPCERROR");
#else
	value = "RPCERROR";
#endif

	errorsym = gsi_make_symbol(value);
	gsi_set_sym(*transient_gsi_items, errorsym);

#ifdef  GSI_USE_WIDE_STRING_API
	free(value);
#endif
	
#ifdef GSI_USE_WIDE_STRING_API
	value = jgi_str2unicode("Could not find Java Method to invoke for ");
	size1 = jgi_wstrlen(value);
	size2 = jgi_wstrlen(g2_name);
	cstr = (gsi_char *)malloc((size1 + size2 + 10) * sizeof(gsi_char));
	/* printf("len is %d \n",((size1 + size2 + 10) * sizeof(gsi_char))); */
	memcpy(cstr, value, size1*sizeof(gsi_char));
	memcpy(cstr + size1, g2_name, (size2+1)*sizeof(gsi_char));
#else
	value = "Could not find Java Method to invoke for";
	cstr = malloc((strlen(value) + strlen(g2_name) + 2));
	sprintf(cstr, "%s %s", value, g2_name);
#endif

	gsi_set_str(transient_gsi_items[1], cstr);

	gsi_rpc_return_error_values(transient_gsi_items,
				     2,
				     (call_identifier_type)call_handle,
				     gsi_current_context());

#ifdef GSI_USE_WIDE_STRING_API
	free(value);
#endif
	free(cstr);

	gsi_reclaim_items(transient_gsi_items);
      }
}


/*****************************************************************************
 * void jgi_missing_procedure_handler(gsi_char *name)
 *										
 *   Description:
 *     Generic G2 entry point for calling handling a local proc that has not
 *     been defined
 *
 *   Input Arguments:
 *     declared_user_data:              user data defined on declaration of local
 *     args:				The arguments to passed to the Java Method
 *     gsi_int:				The count of the number of arguments
 *	   call_handle			Handle of the call instance
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
static void jgi_missing_procedure_handler(gsi_char *name)
{
  JNIEnv *env = gsiRunLoopThreadEnv;

  /* We declare this proc, so that gsi_missing_rpc_local_call_function will get
     called, so we can inform G2
     */
  /* gsi_rpc_declare_local(env,
  		     (void (*))(&gsi_missing_rpc_local_call_function),
  		     (void *)name,
  		     name);
  */


   /* MDG - GSI 50rev0
     The idea above was to declare a procedure handler that would raise an error to G2
     that would abort the RPC call (as the call_handle is passed to RPC local functions)
     however, it looks like, once the RPC has been declared by JAVA, GSI does not use the
     new return function which is not good in a dynamic enviroment.
     So we just raise an error to the G2 log book by using CALL_HANDLE_OF_START.
     */
  gsi_missing_rpc_local_call_function((void *)name, NULL, 0, CALL_HANDLE_OF_START);

}




/*****************************************************************************
 * void gsi_conneciton_rpc_local_call_function(gsi_item args[], gsi_int cnt)
 *										
 *   Description:
 *     Generic G2 entry point for calling Java method for a localRPC declared
 *     for a particular connection
 *
 *   Input Arguments:
 *     declared_user_data:              user data defined on declaration of local
 *     args:				The arguments to passed to the Java Method
 *     gsi_int:				The count of the number of arguments
 *	   call_handle			Handle of the call instance
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/


static void gsi_connection_rpc_local_call_function(void *declared_user_data,
					   gsi_item args[],
					   gsi_int cnt,
					   gsi_int call_handle)
{


  JNIEnv *env = gsiRunLoopThreadEnv;
  ContextData contextData;
  gsi_int context = gsi_current_context();
  jobject G2_RPD_name = (jobject)declared_user_data;

  if (fundebug) {printf("Function gsi_connection_rpc_local_call_function (call_handle is %lx); user data is %lx)\n", call_handle, G2_RPD_name); fflush(stdout);}

  if (G2_RPD_name != NULL)
    {

      contextData = jgi_get_context_object(env, context);

      if (cnt >= 0 && contextData != NULL)
	{
	  if (context != currentContextInJava) {
	    (*env)->CallVoidMethod (env,
				    JREF(registeredJGInterface),
				    registeredJGInterface->setCurrentContext_MethodID,
				    context);
	    currentContextInJava = context;
	  }

	  /* The method will be called from Java, return values will be independantly passed back */
	  invoke_declared_java_method(env,
					JREF(contextData),
					G2_RPD_name,
					JNI_FALSE,
					args,
					cnt,
					call_handle,
					context);

	  jgi_check_and_return_g2_exception(env, (gsi_int)context);	

	}
    }


} /*** end of gsi_conneciton_rpc_local_call_function */

/*****************************************************************************
 * void gsi_nonconnection_rpc_local_call_function(gsi_item args[], gsi_int cnt)
 *										
 *   Description:
 *     Generic G2 entry point for calling Java method no connection specific
 *
 *   Input Arguments:
 *     declared_user_data:              user data defined on declaration of local
 *     args:				The arguments to passed to the Java Method
 *     gsi_int:				The count of the number of arguments
 *	   call_handle			Handle of the call instance
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/


static void gsi_nonconnection_rpc_local_call_function (void *declared_user_data,
						       gsi_item args[],
						       gsi_int cnt,
						       gsi_int call_handle)
{


  JNIEnv *env = gsiRunLoopThreadEnv;
  ContextData contextData;
  gsi_int context = gsi_current_context();
  jobject G2_RPD_name = (jobject)declared_user_data;

	
  if (fundebug) {printf("Function gsi_nonconnection_rpc_local_call_function (call_handle is %lx)\n", call_handle); fflush(stdout);}


  if (G2_RPD_name != NULL)
    {

      contextData = jgi_get_context_object(env, context);

      if (cnt >= 0 && contextData != NULL)
	{

	  if (context != currentContextInJava) {
	    (*env)->CallVoidMethod (env,
				    JREF(registeredJGInterface),
				    registeredJGInterface->setCurrentContext_MethodID,
				    context);
	    currentContextInJava = context;
	  }

	  /* The method will be called from Java, return values will be independantly passed back */
	  invoke_declared_java_method(env,
			     JREF(contextData),
			     G2_RPD_name,
			     JNI_TRUE, /* non conneciton specific*/
			     args,
			     cnt,
			     call_handle,
			     context);

	  jgi_check_and_return_g2_exception(env, (gsi_int)context);	

	}
    }

} /*** end of gsi_nonconnection_rpc_local_call_function */




/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_declareLocalRPCNative
 *
 *   Description:
 *     Java Entry point for declaring a java method name as being invocable
 *
 *   Input Arguments:
 *     this:		The Java JGInterface calling this function
 *     java_method_name: The name of the Java method to declare
 *     g2_RPD_name:     The name of the G2 RPD that will call this method
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_declareLocalRPCNative
  (JNIEnv *env,
   jobject this,
   jobject g2_RPD_symbol,
   jboolean connectionSpecific)
{
  void* userdata;
	
  if (fundebug) {printf("Function GsiLoopThread_declareLocalRPC\n"); fflush(stdout);}

  if (!g2_RPD_symbol)
    {
      THROW_G2COMS_EXCEPTION(env, "NUll g2_RPD_name \
Java_com_gensym_jgi_GsiLoopThread_declareLocalRPCNative");
      return;
    }
	
    {
      jstring g2_RPD_name = (jstring)(*env)->CallObjectMethod (env,
							       g2_RPD_symbol,
							       symbolClassInfo->getPrintValue_MethodID);

      gsi_char *g2_RPD_str = jgi_GetStringChars(env, g2_RPD_name);


      /* Assume that g2_RPD is upper case, as that is what G2 expects */

      userdata = (void *)((*env)->NewGlobalRef(env, g2_RPD_symbol));

      if (connectionSpecific) {
	gsi_rpc_declare_local((void (*)())(&gsi_connection_rpc_local_call_function),
		       userdata, g2_RPD_str);
      } else
	gsi_rpc_declare_local((void (*)())(&gsi_nonconnection_rpc_local_call_function),
		       userdata, g2_RPD_str);

      if (fundebug)
	{
	  /* need non unicode chars */
	  printf("Declared ");
	  jgi_printStr(g2_RPD_str);
	  printf(" as local RPC, user data %lx\n",userdata);
	  fflush(stdout);
	}

      if (g2_RPD_str) free(g2_RPD_str);
    }
}



/*****************************************************************************
 *  Java_com_gensym_jgi_GsiLoopThread_setRPCRemoteReturnValueKindNative
 *
 *   Description:
 *     Set the return value kind of a remote RPC return object parameter
 *
 *   Input Arguments:
 *     this:		The Java JGInterface calling this function
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_setRPCRemoteReturnValueKindNative
  (JNIEnv *env, jobject this, jlong function_handle,
   jint return_value_index, jint return_value_type, jint context)
{
  char* return_value_type_description;
  gsi_char* return_value_type_description_u;
  gsi_int cast_function_handle;

  if (fundebug) {printf ("Function GsiLoopThread_setRPCRemoteReturnValueKindNative, function handle %lx\n", function_handle); fflush(stdout);}

  if (return_value_type == 0)
    return_value_type_description = "HANDLE";
  else if (return_value_type == 1)
    return_value_type_description = "COPY";
  else if (return_value_type == 2)
    return_value_type_description = "BY-COPY-WITH-HANDLE";
  else
    return_value_type_description = "REFERENCE";


  if (fulldebug) {
    printf ("Setting Return #%2d of Fn %lx to be of type %s\n",
	    return_value_index,
	    function_handle,
	    return_value_type_description);
    fflush (stdout);
  }

#ifdef GSI_USE_WIDE_STRING_API
  return_value_type_description_u = jgi_str2unicode(return_value_type_description);
#else
  return_value_type_description_u = return_value_type_description;
#endif

  /* This cast_function_handle stuff is kind of ugly.  On a 64-bit machine, this
     does nothing, because function_handle, a jlong, is the same length as
     gsi_int.  However, on a 32-bit machine, we need to cast down (the upper
     bits are empty, so it's OK).  However, when I said to just cast with
     function_handle_type, I got compiler complaints, whereas if I use gsi_int
     here, and function_handle_type in the function call, I don't get those
     complaints.  yduJ, 1/06 */

  cast_function_handle = (gsi_int)function_handle;

  gsi_set_rpc_remote_return_value_kind ((function_handle_type)cast_function_handle,
					 return_value_index,
					 return_value_type_description_u);

#ifdef GSI_USE_WIDE_STRING_API
  free((char *)return_value_type_description_u);
#endif

  if (fundebug) {
    printf ("Exiting GsiLoopThread_setRPCRemoteReturnValueKindNative\n");
    fflush (stdout);
  }
}


/*****************************************************************************
 * void gsi_general_rpc_error_remote_return_function
 *										
 *   Description:
 *     Generic G2 entry point for calling a Java method with the results of a
 *     a previous G2 procedure call by java via GsiLoopThread_rpc_call_native
 *     where an error has occured
 *
 *   Input Arguments:
 *     args:				The arguments to passed to the Java Method
 *     gsi_int:				The count of the number of arguments
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
static void gsi_general_rpc_error_remote_return_function (void *declare_user_data,
							  gsi_item args[],
							  gsi_int cnt,
							  call_identifier_type input_call_data)
{
  /* Return function will be called from the dispatch thread */
  JNIEnv *env = gsiRunLoopThreadEnv;
  jobject call_data = (jobject)input_call_data;

  if (fundebug) {
    printf("Function gsi_general_rpc_error_remote_return_function \n");
    fflush (stdout);
  }


  if (call_data) { /* ran in a waiting thread */
    jobject ThreadData = call_data;
    jobject jerror_symbol = NULL;
    jobject jerror_message = NULL;

    if (fulldebug) {printf ("Thread Data %lx, Count %d, Flagging error", ThreadData, cnt); fflush(stdout);}

    if (cnt == 2) {
      gsi_item retnvalue = *args;
      jclass java_class;

      /* Symbols and text Strings are context independent
	 There are no embedded Items! We don't have to
	 switch "current" contexts */
      jerror_symbol = create_java_object_from_gsiitem (env,
						       args[0],
						       &java_class,
						       JNI_TRUE,
						       JNI_FALSE);

      jerror_message = create_java_object_from_gsiitem (env,
							args[1],
							&java_class,
							JNI_TRUE,
							JNI_FALSE);
    }

    if (fulldebug)  {printf ("%lx being notified of error return...\n", call_data); fflush (stdout);}
    
    (*env)->CallVoidMethod (env, ThreadData, remoteRPCThreadClassInfo->signalReturnError_MethodID,
			    jerror_symbol,
			    jerror_message);

    if (fulldebug)  {printf ("%lx return_call_data woken up?...\n", call_data); fflush (stdout);}

    /* finished with the Thread data global refences */
    (*env)->DeleteGlobalRef(env, ThreadData);

    return;
  }


}


/*****************************************************************************
 * void gsi_general_rpc_remote_return_function(gsi_item args[], gsi_int cnt)
 *										
 *   Description:
 *     Generic G2 entry point for calling a Java method with the results of a
 *		a previous G2 procedure call by java via GsiLoopThread_rpc_call_native
 *
 *   Input Arguments:
 *     args:				The arguments to passed to the Java Method
 *     gsi_int:				The count of the number of arguments
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/


static void gsi_general_rpc_remote_return_function (void *declare_user_data,
						    gsi_item args[],
						    gsi_int cnt,
						    call_identifier_type input_call_data)

{

  jobject call_data = (jobject)input_call_data;
  jobject java_return;
  int stat_index = -1;
  gsi_int contextID;

  /* Return function will be called from the dispatch thread */
  JNIEnv *env = gsiRunLoopThreadEnv;
  contextID = gsi_current_context ();
  if (fundebug)
    {
      printf("Function gsi_general_rpc_remote_return_function (call_data = %lx)\n" , call_data);
      fflush (stdout);
    }

  if (contextID != currentContextInJava) {
    (*env)->CallVoidMethod (env,
			    JREF(registeredJGInterface),
			    registeredJGInterface->setCurrentContext_MethodID,
			    contextID);
    currentContextInJava = contextID;
  }

  if (call_data) { /* ran in a waiting thread */

    if (collect_rpc_stats && buffers_ok) {
      int ts = jgi_get_timestamp ();
      stat_index = get_stat_index ((int)input_call_data);
      ts_return[stat_index] = ts;
    }

    if (fulldebug) {printf ("Call Data %lx, Returning %d values \n", call_data, cnt); fflush(stdout);}

    if (cnt == 1) {
      gsi_item retnvalue = *args;
      gsi_int retntype;
      jclass java_class;

      if (fulldebug) { printf ("Getting Type Of Item. %lx\n", retnvalue); fflush (stdout);}

      retntype = gsi_type_of (retnvalue);
      if (fulldebug) { printf ("RetnType = %d\n", retntype); fflush (stdout);}

      java_return = create_java_object_from_gsiitem (env,
						     retnvalue,
						     &java_class,
						     JNI_TRUE,
						     JNI_FALSE);

    } else
      java_return = create_java_sequence_from_gsiitems (env, args, cnt);

    if (fulldebug) {printf ("RetnValue = %lx\n", java_return); fflush (stdout);}

    (*env)->CallVoidMethod (env,
			    call_data,
			    remoteRPCThreadClassInfo->signalReturnValue_MethodID,
			    java_return, incompleteStubConversion);

    if (fulldebug)  {printf ("%lx return_call_data woken up?...\n", call_data); fflush (stdout);}
    PRINT_EXCEPTION (env);

    /* finished with the call data global refences */
    /*printf("Deleting call_data... %lx \n", call_data);*/
    (*env)->DeleteGlobalRef(env, call_data);

    if (stat_index != -1)
      ts_done[stat_index] = jgi_get_timestamp ();

    return;
  }

  /* The orginal call to a G2 RPC was asynchronous */
  /* we must call a receiver method, defined on declaration */
  else if (cnt > 0)
    {
      /* receiver method to call was declared via declare remote   */
      /* and the receiver method is passed in the declare_user_data*/
      /* of the function call */
	  jstring java_method = (jstring)declare_user_data;

	  ContextData contextData = jgi_get_context_object(env, gsi_current_context());
	  if (contextData == NULL) return;
	

	   /* The method will be called from Java, retrun values will be independantly passed back */
	  /*  Needs support in Java code for this*/ /*
	      invoke_java_method(
			     env,
			     JREF(contextData),
			     java_method,
			     NULL,
			     NULL,
			     args,
			     cnt,
			     JNI_FALSE,
			     JNI_TRUE,
			     JNI_TRUE,
			     CALL_HANDLE_OF_START,
			     gsi_current_context());
	  */

	  THROW_G2COMS_EXCEPTION(env,
  		    "callRPCAynchrounous to G2 is not supported in this release");

	  /* jgi_check_and_return_g2_exception(env, gsi_current_context()); */
    }

  if (fundebug) {printf("Exiting gsi_general_rpc_remote_return_function \n"); fflush(stdout);}

} /*** end of gsi_general_rpc_remote_return_function */



/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_declareRemoteRPCNative
 *
 *   Description:
 *     Java Entry point for declaring a java method of this as being invocable
 *
 *   Input Arguments:
 *     HJGInterface:		The Java JGInterface calling this function
 *     Hjava_lang_string:	The nam eof the Java method to declare
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

JNIEXPORT jlong JNICALL Java_com_gensym_jgi_GsiLoopThread_declareRemoteRPCNative
  (JNIEnv *env,
   jobject this,
   jstring g2_function_name,
   jint out_argcnt,
   jint callback_argcnt,
   jstring receiver_method_name,
   jint context)

{
  if (fundebug) {printf("Function Java_com_gensym_jgi_GsiLoopThread_declareRemoteRPCNative \n"); fflush(stdout);}

  if (gsiRunning)
    {
      gsi_int handle = 0;
      gsi_char *g2_func_str;
      jstring receiver_method_name_gbl;

      g2_func_str = jgi_GetStringChars(env, g2_function_name);

      if (fulldebug) {
	printf ("Registering ");
	jgi_printStr(g2_func_str);
	printf(" (%d) = (%d) as a remote call in g2.\n", out_argcnt, callback_argcnt);
	fflush(stdout);
      }

      /* Need to keep a global ref to receiver_method_name */
      receiver_method_name_gbl = (*env)->NewGlobalRef(env, receiver_method_name);

      gsi_rpc_declare_remote_with_error_handler_and_user_data
	((call_identifier_type *)&handle,
	 g2_func_str,
	 (&gsi_general_rpc_remote_return_function),
	 (&gsi_general_rpc_error_remote_return_function),
	 (void *)receiver_method_name_gbl,
	 out_argcnt,
	 callback_argcnt,
	 (gsi_int)context );

      if (g2_func_str) free(g2_func_str);

      if (fundebug) {printf("Returned %lx after 'c' call to gsi_rpc_declare_remote \n", handle); fflush(stdout);}

      return (jlong)handle;
    } else return 0;
}


/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_callRPCNative
 *
 *   Description:
 *     Java Native method entry point for calling a G2 remote procedure
 *
 *   Input Arguments:
 *     this:		The Java JGInterface calling this function
 *     handle:		The handle of the predefined remote procedure
 *     java_gsiitems_array: An array of java objects to be sent as args
 *							to the G2 procedure
 *     start_proc:	True to start the G2 procedure else call
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/


JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_callRPCNative
(JNIEnv *env,
   jobject this,
   jlong handle,
   jarray java_gsiitems_array,
   jboolean start_proc,
   jobject user_data,
   jint context)
{
  int i;
  int bad_args = FALSE;
  gsi_item *transient_gsi_items = NULL;
  gsi_item *return_value_ptr;
  gsi_int cast_function_handle;
  int numargs = (*env)->GetArrayLength(env, java_gsiitems_array);
  if (fundebug) {printf("Function  Java_com_gensym_jgi_GsiLoopThread_callRPCNative, orig user data =%lx \n", user_data); fflush (stdout);}

  if (user_data) user_data = (*env)->NewGlobalRef(env, user_data);

  if (fundebug) {printf("Function  Java_com_gensym_jgi_GsiLoopThread_callRPCNative, new user data =%lx \n", user_data); fflush (stdout);}

  /* do we have arguments */
  if (fulldebug) printf ("  There are %d arguments for this call.\n", numargs);

  /* we need to convert the item array list into a proper GsiItem list */
  /* Create some items */
  transient_gsi_items = gsi_make_array(numargs);

  return_value_ptr = transient_gsi_items;

  bad_args = get_gsiitems_from_java_objects (env,
					     java_gsiitems_array,
					     return_value_ptr,
					     numargs,
					     context);
  
  /* If we have not detected any bad arguments while parsing the java gsi items */
  /* then go for a start Huston ! */
  if (!bad_args)
    {

      /* refer to comments in setRPCRemoteReturnValueKindNative */
      cast_function_handle = (gsi_int)handle;

      if (start_proc)
	{
	  gsi_rpc_start_with_count ((function_handle_type)cast_function_handle,
				     transient_gsi_items,
				     numargs,
				     (gsi_int)context);
	}
      else {
	gsi_rpc_call_with_count_and_user_data ((function_handle_type)cast_function_handle,
						transient_gsi_items,
						numargs,
						(call_identifier_type)user_data,
						(gsi_int)context);
	if (collect_rpc_stats && buffers_ok && num_measured_calls < stat_buffer_size) {
	  int j = num_measured_calls++;
	  int ts = jgi_get_timestamp ();
	  save_stat_index ((int)user_data, j);
	  rpc_indices[j] = handle;
	  ts_call[j] = ts;
	}
      }
    } else
      {
	if (bad_args != JAVA_ITEM_BAD_ALREADY_THREW)
	  THROW_G2COMS_EXCEPTION(env, "Bad, null or non-G2-convertible Java object found while parsing arguments for remote G2 RPC call");
	if (fulldebug) fprintf(stderr, "Bad arguments found while parsing Java arguments to G2 RPC call\n");
      }

  /* Must clean up any gsi memory we have used */

  for (i=0; i<numargs; i++)
    {
      gsirtl_free_i_or_v_contents(transient_gsi_items[i]);
    }
  gsi_reclaim_items(transient_gsi_items);

  if (fundebug) {printf("Function Java_com_gensym_jgi_GsiLoopThread_callRPCNative returning.\n"); fflush (stdout);}
}


JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_setFulldebug
  (JNIEnv *env, jobject this, jboolean state)
{
  /*printf ("Setting FULLDEBUG to %d; was %d.\n", state, fulldebug);*/
  fulldebug = (int)state;
}

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_setFundebug
  (JNIEnv *env, jobject this, jboolean state)
{
  /*printf ("Setting FUNDEBUG to %d; was %d.\n", state, fundebug);*/
  fundebug = (int)state;
}

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_setConvdebug
  (JNIEnv *env, jobject this, jboolean state)
{
  /*printf ("Setting CONVDEBUG to %d; was %d.\n", state, convdebug);*/
  convdebug = (int)state;
}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_getRemoteHostNative
 *
 *   Description:
 *     Java Native method entry point for getting remote host for a context
 *
 *   Input Arguments:
 *     this:		The Java JGInterface calling this function
 *     context:         The context number
 *	
 *   Returns:
 *     the host string
 *   Modifications:
 *****************************************************************************/


JNIEXPORT jstring JNICALL Java_com_gensym_jgi_GsiLoopThread_getRemoteHostNative
(JNIEnv *env,
   jobject this,
   jint context)
{
  
  gsi_char *host_name = gsi_context_remote_host((gsi_int)context);

  if (host_name) {
    return jgi_NewString(gsiRunLoopThreadEnv, host_name );
  } else
    return NULL;
}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_getRemotePortNative
 *
 *   Description:
 *     Java Native method entry point for getting remote port for a context
 *
 *   Input Arguments:
 *     this:		The Java JGInterface calling this function
 *     context:         The context number
 *	
 *   Returns:
 *     the port number
 *   Modifications:
 *****************************************************************************/


JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_getRemotePortNative
(JNIEnv *env,
   jobject this,
   jint context)
{
  return gsi_context_remote_listener_port((gsi_int)context);
}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_getRemoteSecureContext
 *
 *   Description:
 *     Java Native method entry point for getting whether a context is secure.
 *     Sadly, bases decision on "current context" rather than accepting a 
 *     context number.
 *
 *   Input Arguments:
 *     this:		The Java JGInterface calling this function
 *	
 *   Returns:
 *     0 for insecure, 1 for secure
 *   Modifications:
 *****************************************************************************/


JNIEXPORT jint JNICALL Java_com_gensym_jgi_GsiLoopThread_getRemoteSecureContext
(JNIEnv *env,
   jobject this,
   jint context)
{
  return gsi_context_is_secure((gsi_int)context);
}


/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_returnValues
 *
 *   Description:
 *     Java Native method entry point for performing a gsi_return_values
 *
 *   Input Arguments:
 *     this:		The Java JGInterface calling this function
 *     context:         The context number
 *	
 *   Returns:
 *     the host string
 *   Modifications:
 *****************************************************************************/


JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_returnValues
(JNIEnv *env,
   jobject this,
   jobjectArray items,
   jobjectArray attributes,
   jobjectArray values,
   jintArray itemStatuses,
   jint context)
{


  return_java_values(env,
		     items,
		     attributes,
		     values,
		     itemStatuses,
		     context);
  
}

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_returnAttrs
(JNIEnv *env,
   jobject this,
   jobject item,
   jobject attributes,
   jobject value,
   jint    status,
   jint    context)
{


  return_java_value_and_attrs(env,
		     item,
		     attributes,
		     value,
		     status,
		     context);
  
}

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_setReceiveRegistrations
  (JNIEnv *env, jobject this, jint context, jboolean state)
{
  ContextData contextData = jgi_get_context_object(env, context);
  if (fulldebug)
    fprintf (stdout, "Java_com_gensym_jgi_GsiLoopThread_setReceiveRegistrations (%d).\n", state);
  if (contextData != NULL)
    contextData->receiveRegistrations = state;
}

/*****************************************************************************
 * void gsi_check_valid_connection_callback(gsi_item args[], gsi_int cnt)
 *										
 *   Description:
 *     Generic G2 entry point for ensuring that the G2 is authorized for this
 *     connection.
 * 
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

static void gsi_check_valid_connection_callback (void *declare_user_data,
						    gsi_item args[],
						    gsi_int cnt,
						    call_identifier_type input_call_data)

{
  gsi_int contextID;
  ContextData contextData;
  JNIEnv *env = gsiRunLoopThreadEnv;
  jboolean notAuthorized = JNI_TRUE;
  gsi_int type = (gsi_int)input_call_data;
  gsi_int result = 0;
  jboolean killContext = JNI_TRUE;

  if (JNI_FALSE) {
    printf("Function gsi_check_valid_connection_callback (input_call_data = %lx)\n" , input_call_data);
    fflush (stdout);
  }
  
  if (env != NULL) {

    contextID = gsi_current_context ();
    contextData = jgi_get_context_object(env, contextID);
    if (contextData != NULL) {
      killContext = JNI_FALSE;
      if (cnt >= 1) {
	result = gsi_int_of(args[0]);
      }

      if (type == 1) {
	contextData->authorizedforjlp = (result > 0 ? JNI_TRUE : JNI_FALSE);
      } else {
	contextData->authorizedforjl = (result > 0 ? JNI_TRUE : JNI_FALSE);
	notAuthorized = !(contextData->authorizedforjl);
      }
    }
  }

  if (killContext) {
    fprintf(stderr, "Error: Cant find Environment/Context Data for Authorization check, closing connection");
    gsi_kill_context(contextID);
    return;
  }

  if (fundebug) {printf("type is %d, notAuth is %d, result %d", type, notAuthorized, result); fflush(stdout);}

  if (type == 0 && notAuthorized) {
    char *g2str = "This G2 is not authorised to connect to G2JavaLink/Gateway";
    char *jlstr = "G2 JavaLink/Gateway could not connect to G2 (@host %s, port %d), as it is not authorized to connect to G2JavaLink/Gateway \n";
    /* Authorisation Check*/
    /* If raised an exception here, we let the user see the stack trace */
    gsi_char *host_name = gsi_context_remote_host((gsi_int)contextID);
#ifdef GSI_USE_WIDE_STRING_API
    char *host_str = jgi_unicode2str(host_name);
#else
    char *host_str = (char*)host_name;
#endif
    int port_num = gsi_context_remote_listener_port((gsi_int)contextID);
    fprintf(stderr, jlstr, host_str, port_num);
    THROW_G2COMS_EXCEPTION(env, jlstr);
    jgi_reportG2LogBookErrorMessage(env, 
				    NULL, 
				    (*env)->NewStringUTF(env, g2str), 
				    CALL_HANDLE_OF_START, 
				    contextID);
    gsi_kill_context(contextID); 
  }
  
  if (type == 0 && contextData != NULL) {
    /* Inform the connection of the initiation */
    (*gsiRunLoopThreadEnv)->CallVoidMethod(gsiRunLoopThreadEnv,
					     JREF(registeredJGInterface),
					     registeredJGInterface->G2InitializeConnection_MethodID,
					     JREF(contextData),
					     (jint)contextID,
					     contextData->remoteInitString);
    if (contextData->remoteInitString != NULL)
      (*env)->DeleteGlobalRef(env, contextData->remoteInitString);
  }
  
}

/*****************************************************************************
 * gsi_valid_connection_rpc_error_remote_return_function
 *
 * Called when a context can not call the authorization System RPC in G2
 * probably due to the G2 being an old version.
 */
static void gsi_valid_connection_rpc_error_remote_return_function (void *declare_user_data,
							  gsi_item args[],
							  gsi_int cnt,
							  call_identifier_type input_call_data) {
  gsi_int contextID = gsi_current_context ();
  ContextData contextData;
  JNIEnv *env = gsiRunLoopThreadEnv;

  if (fundebug) {printf("Function gsi_valid_connection_rpc_error_remote_return_function\n"); fflush(stdout);}

  fprintf(stderr, "\n****\nError:Can not perform Authorization checks on this version of G2, closing connection. ");
  fprintf(stderr, "JavaLink can only connect to G2 version 5.1 or greater.\n****\n");
  gsi_kill_context(contextID); 
  
  contextData = jgi_get_context_object(env, contextID);
  if (contextData != NULL)
    (*gsiRunLoopThreadEnv)->CallVoidMethod(gsiRunLoopThreadEnv,
					     JREF(registeredJGInterface),
					     registeredJGInterface->G2InitializeConnection_MethodID,
					     JREF(contextData),
					     (jint)contextID,
					     NULL);
   
  
}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_checkHandleType
 *
 *   Description:
 *     Java Entry point for authorization check
 *
 *   Input Arguments:
 *     type = 0 check for javalink authorization
 *     type = 1 check for javalink/professional authorization
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_checkHandleType
  (JNIEnv *env, jobject jgi_interface, jint context, jint type)
{
#ifdef GSI_USE_WIDE_STRING_API 
  gsi_char *rpcName = jgi_str2unicode("G2-CONFIRM-AVAILABLE-HANDLES-BY-TYPE");
#else
  gsi_char *rpcName = "G2-CONFIRM-AVAILABLE-HANDLES-BY-TYPE";
#endif
  call_identifier_type handle;
  gsi_item *transient_gsi_items = gsi_make_items(1);
  

  gsi_rpc_declare_remote_with_error_handler_and_user_data
    ((call_identifier_type *)&handle,
     rpcName,
     (&gsi_check_valid_connection_callback),
     (&gsi_valid_connection_rpc_error_remote_return_function),
     NULL,
     -1,
     -1,
     (gsi_int)context );

  gsi_set_sym(*transient_gsi_items, 
	       (type ? popup_gsisymbol : window_gsisymbol));
  /*                   javalink/professional   javalink */

  gsi_rpc_call_with_count_and_user_data 
    ((function_handle_type)handle,
     transient_gsi_items,
     1,
     (call_identifier_type)type,
     (gsi_int)context);
  
  gsi_reclaim_items(transient_gsi_items);

#ifdef GSI_USE_WIDE_STRING_API 
  free(rpcName);
#endif
}

/*****************************************************************************
 * Java_com_gensym_jgi_GsiLoopThread_checkForHandleOK
 *
 *   Description:
 *     Java Entry point for checking for authorization 
 *
 *   Input Arguments:
 *     type = 0 check for javalink authorization
 *     type = 1 check for javalink/professional authorization
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jstring JNICALL Java_com_gensym_jgi_GsiLoopThread_checkForHandleOK
  (JNIEnv *env, jobject jgi_interface, jint context, jint type)
{
  ContextData contextData;
  jboolean notAuthorized = JNI_TRUE;

  if (fundebug) {
    printf("Function Java_com_gensym_jgi_GsiLoopThread_checkForHandleOK\n");
    fflush (stdout);
  }

  if (env != NULL) {
    contextData = jgi_get_contextData(env, context);
    
    if (contextData == NULL || type > 1) return (*env)->NewStringUTF(env, 
							 "Error: Could not perform authorization checks");

    if (type == 1) {
      if (contextData->authorizedforjlp) 
	return NULL;
      else
	return (*env)->NewStringUTF(env, 
				    "G2JavaLink/Professional could not connect to the specified G2, as it is not authorized to connect to a G2JavaLink/Professional clients");
    } else {
      if (contextData->authorizedforjl)
	return NULL;
      else
	return (*env)->NewStringUTF(env, 
				    "G2JavaLink/Gateway could not connect to the specified G2, as it is not authorized to connect to G2JavaLink/Gateway clients");

    }
  } else return (*env)->NewStringUTF(env, 
				     "Error: Could not find environment to perform authorization checks");
}

/******** End of GsiLoopThread Java Object native method section */


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Predeclared GSI remote procedures
 %
 % Description:
 %
 %		These functions are predeclared GSI functions that can be called
 %      by G2
 %
 % Notes:
 %		Each Entry point must be defined by gsi_declare_local
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - G2 called GSI Function callbacks
 %
 % Description:
 %
 %		These functions are expected entry points for a standard GSI
 %
 % Notes:
 %		Each entry point is defined by the GSI API
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/******** Start of Gsi callbacks section */


void gsi_set_up ()
{
  if (fundebug) { printf("CB: Function gsi_set_up \n"); fflush (stdout); }


}

gsi_int gsi_get_tcp_port()
{
  if (fundebug) { printf("CB: Function gsi_get_tcp_port \n"); fflush (stdout); }
  if (fulldebug) printf("PORT NUMBER = %d\n", TCPIP_PORT_NUMBER);
  return(TCPIP_PORT_NUMBER);
}

/*****************************************************************************
 * gsi_int gsi_initialize_context(char *remote_process_init_string,
 *									gsi_int length
 *   Description:
 *     GSI entry point for informing Java that a context has been initialized
 *
 *   Input Arguments:
 *		remote_process_init_string:	From the interface remote string attribute
 *		length:						length of string
 *	
 *   Returns:
 *     GSI_ACCEPT if OK or GSI_REJECT to reject connection
 *
 *   Modifications:
 *
 *     yduj: mass quantities for "large objects a bug".  Left undone possibly is
 *     the issue of where to print error messages when you have a problem with a
 *     connection.  At present, I have copied a lot of stuff that used to be in
 *     gsi_initialize_context to a new function, nativeRegisterContextObject.
 *     However, that ends up being called asynchronously, and it's not clear
 *     whether it is appropriate to return error messages.  Check this function
 *     in version 1.64 of this file sometime in the future.
 *****************************************************************************/
gsi_int gsi_initialize_context(gsi_char *remote_process_init_string, gsi_int length)
{

  int context;
  ContextData contextData;


  if (fundebug)
    {
      printf ("CB: Function gsi_initialize_context in context %d\n",
	      gsi_current_context());
      fflush (stdout);
    }

  /* Ensure that we have the gsi_run_loop thread environment to work in */
  /* and the Java methiod id of the call back method */
  if (gsiRunLoopThreadEnv != NULL &&
      registeredJGInterface->G2InitializeConnection_MethodID != NULL)
    {

      jstring jconnection_id;

      jstring jremote_string =
	jgi_NewString(gsiRunLoopThreadEnv, remote_process_init_string);

      /* Record the context number for the connection */
      context = gsi_current_context();

      jconnection_id =
	(jstring)gsi_context_user_data(context);

      if (fundebug)
	{
	  printf ("new Context is %d; gsiRunLoopThreadEnv = %lx\n",
		  context,gsiRunLoopThreadEnv);
	  fflush (stdout);
	}
      
      (*gsiRunLoopThreadEnv)->CallVoidMethod(gsiRunLoopThreadEnv,
					       JREF(registeredJGInterface),
					       registeredJGInterface->registerIncomingConnection_MethodID,
					       (jint)context,
					       jremote_string,
					       jconnection_id);
      
      FULLDEBUG_PRINT_EXCEPTION(gsiRunLoopThreadEnv);
      return (GSI_ACCEPT);
    } else
      return (GSI_REJECT);
}

void gsi_receive_registration(item_registration)
gsi_registration item_registration;
{
  gsi_int handle;
  ContextData contextData;
  JNIEnv *env = gsiRunLoopThreadEnv;

  if (fundebug) {
      printf ("CB: Function gsi_receive_registration in context %d\n",
			gsi_current_context());
      fflush (stdout);
  }
  handle = gsi_handle_of(item_registration);
  if (fulldebug) {
      printf ("  Handle for registration was %d %lx.\n", handle, gsi_registration_of_handle(handle, gsi_current_context()));
      printf ("    Class = ");
      jgi_printStr (gsi_symbol_name (gsi_class_name_of (gsi_registration_of_handle (handle, gsi_current_context ()))));
      printf ("\n");
      fflush (stdout);
      /* gsi_set_user_data(item_registration, (void *)5); */
  }

  /* Ensure that we have the method ID of the Java Call back method */
  if (env != NULL) {
    gsi_int context = gsi_current_context();
    contextData = jgi_get_context_object(env, context);

    /* printf("Reg with %d" , contextData->receiveRegistrations); */

    if (contextData != NULL && contextData->receiveRegistrations) {
      int i = 1;
      int y = 0;
      jclass javaClass;
      jobject identValue;
      jobject javaitem;
      gsi_item gsiitem;
      jobject identValues[6];
      gsi_item identValueGsiItem;
      jobjectArray identArray;

      if (context != currentContextInJava) {
	(*env)->CallVoidMethod (env,
				JREF(registeredJGInterface),
				registeredJGInterface->setCurrentContext_MethodID,
				context);
	currentContextInJava = context;
      }

      /* Ok GSI Lession...
	 A gsi_registration is passed here, we can not use our generic 
	 create_java_object_from_gsiitem on this, as it contains the
	 identifying attributes, which are nameless !!!
	 So we create a dummy gsi_item with handle and classname
	 */

      gsiitem = gsi_make_item();
      gsi_set_type(gsiitem, GSI_NULL_TAG);
      gsi_set_handle(gsiitem, gsi_handle_of(item_registration));
      gsi_set_class_name(gsiitem, gsi_class_name_of(item_registration));
      javaitem = create_java_object_from_gsiitem (env,
						  gsiitem,
						  &javaClass,
						  JNI_TRUE,
						  JNI_FALSE);  

      gsi_reclaim_item(gsiitem);
      
      /* All 6 atts may not be specified */
      for (i = 1; i<7 ; i++) {
	identValueGsiItem  = gsi_item_of_identifying_attr_of(item_registration, i);
        if (!identValueGsiItem) break;
	identValue = create_java_object_from_gsiitem 
	                    (env ,identValueGsiItem, &javaClass, JNI_TRUE, JNI_FALSE);
	if (!identValue) break;
	identValues[i-1] = identValue;
      }

      /*printf("Number of items is %d", i-1);*/
      identArray = (*env)->NewObjectArray(env, 
					  i-1, 
					  objectClassInfo->clazz, 
					  NULL); 
      
      for (y = 0; y<i-1; y++) {
	/* All item and values get wrapped as Java Objects for attribute values */
	identValue = identValues[y];
	if (identValue) {
	  (*env)->SetObjectArrayElement(env, identArray, y, identValue);      
	}

      }
   
      (*env)->CallVoidMethod (env,
			      JREF(registeredJGInterface),
			      registeredJGInterface->receiveRegistration_MethodID,
			      JREF(contextData),
			      context,
			      javaitem,
			      identArray,
			      incompleteStubConversion);

      incompleteStubConversion = JNI_FALSE;

    }
  }

  if (fundebug)
    {
      printf ("CB: Exiting gsi_receive_registration in context %d\n",
	      gsi_current_context());
      fflush (stdout);
    }
}


void callInterfaceMethodWithRegistrations (registeredItems, count, methodID)
gsi_registered_item  registeredItems[];
gsi_int              count;
jmethodID            methodID;
{
  ContextData contextData;
  JNIEnv *env = gsiRunLoopThreadEnv;
  jobjectArray jItemsArray;
  jobjectArray jValueArray;
  int i = 0;
  jclass javaClass;
  jobject javaItem;

  if (fundebug)
    {
      printf ("callInterfaceMethodWithRegistrations in context %d\n",gsi_current_context());
      fflush (stdout);
    }

  /* Ensure that we have the gsi_run_loop thread environment to work in */
  /* and the method ID of the Java Call back method */
  if (env != NULL && count > 0) {
      gsi_int context = gsi_current_context();
      contextData = jgi_get_context_object(env, context);
      if (contextData == NULL) return;

      if (context != currentContextInJava) {
	(*env)->CallVoidMethod (env,
				JREF(registeredJGInterface),
				registeredJGInterface->setCurrentContext_MethodID,
				context);
	currentContextInJava = context;
      }

      jItemsArray = (*env)->NewObjectArray(env, 
				      count, 
				      itemClassInfo->clazz, 
				      NULL); 

      for (i = 0; i<count; i++) {
	javaItem = create_java_object_from_gsiitem (env,
						    registeredItems[i],
						    &javaClass,
						    JNI_TRUE,
						    JNI_FALSE);
	(*env)->SetObjectArrayElement(env, jItemsArray, i, javaItem );
	
      }

      (*env)->CallVoidMethod (env,
			      JREF(registeredJGInterface),
			      methodID,
			      JREF(contextData),
			      context,
			      jItemsArray,
			      jValueArray,
			      incompleteStubConversion);

      incompleteStubConversion = JNI_FALSE;
  }
}

void gsi_get_data (registeredItems, count)
gsi_registered_item  registeredItems[];
gsi_int              count;
{
  if (fundebug)
    {
      printf ("CB: gsi_get_data in context %d\n",gsi_current_context());
      fflush (stdout);
    }
  callInterfaceMethodWithRegistrations(registeredItems, 
				       count, 
				       registeredJGInterface->getData_MethodID);
}

void gsi_set_data (registeredItems, count)
gsi_registered_item  registeredItems[];
gsi_int              count;
{ 
 if (fundebug)
    {
      printf ("CB: gsi_set_data in context %d\n",gsi_current_context());
      fflush (stdout);
    }
  callInterfaceMethodWithRegistrations(registeredItems, 
				       count, 
				       registeredJGInterface->setData_MethodID);
}

/*****************************************************************************
 * void dispatch_state_change_callback (gsi_int context, int state_change)
 *
 *   Description:
 *     GSI entry point for informing Java that a context state change has occurred
 *
 *   Input Arguments:
 *     a gsi_int indicating the context
 *     an integer indicating the type of state change
 *	
 *   Returns:
 *     nothing
 *
 *   Callers
 *     All GSI state change callbacks 
 *         gsi_pause_context
 *         gsi_resume_context
 *         gsi_reset_context
 *         gsi_start_context
 *         gsi_shutdown_context
 *
 *   Modifications:
 *****************************************************************************/

void dispatch_state_change_callback (gsi_int context, int state_change) {

  ContextData contextData;
  JNIEnv *env = gsiRunLoopThreadEnv;
  jmethodID callbackMethodID;

  if (fundebug)
    {
      printf ("Entering dispatch_state_change_callback in context %d\n",
	      context);
      fflush (stdout);
    }

  /* Ensure that we have the gsi_run_loop thread environment to work in */
  /* and the method ID of the Java Call back method */
  if (env != NULL)
    {
      contextData = jgi_get_context_object(env, context);
      if (contextData == NULL) return;

      switch (state_change)
	{
	case JGI_STATE_PAUSED:
	  callbackMethodID = registeredJGInterface->G2isPaused_MethodID;
	  break;
	case JGI_STATE_RESUMED:
	  callbackMethodID = registeredJGInterface->G2isResumed_MethodID;
	  break;
	case JGI_STATE_RESET:
	  callbackMethodID = registeredJGInterface->G2isReset_MethodID;
	  break;
	case JGI_STATE_STARTED:
	  callbackMethodID = registeredJGInterface->G2isStarted_MethodID;
	  break;
	case JGI_STATE_SHUTDOWN:
	  callbackMethodID = registeredJGInterface->G2ConnectionClosed_MethodID;
	  break;
	default:
	  fprintf (stderr, "Unknown state (%d) passed to dipatch_state_change_callback", state_change);
	  return;
      }

      (*env)->CallVoidMethod (env,
			      JREF(registeredJGInterface),
			      callbackMethodID,
			      JREF(contextData),
			      context);

      jgi_check_and_return_g2_exception(env, context);
    }
  else if (fulldebug)
    {
      printf("Failed calling Java Method: No thread environment \n");
      fflush(stdout);
    }

  if (fundebug)
    {
      printf ("Exiting dispatch_state_change_callback in context\n");
      fflush (stdout);
    }
}

/*****************************************************************************
 * void gsi_pause_context()
 *
 *   Description:
 *     GSI entry point for informing Java that a context has been paused
 *
 *   Input Arguments:
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void gsi_pause_context ()
{
  JNIEnv *env = gsiRunLoopThreadEnv;
  gsi_int context = gsi_current_context();

  if (fundebug)
    {
      printf ("CB: Function gsi_pause_context in context %d\n",
	      context);
      fflush (stdout);
    }

  dispatch_state_change_callback (context, JGI_STATE_PAUSED);

  if (fundebug)
    {
      printf ("CB: Exiting gsi_pause_context in context %d\n", context);
      fflush (stdout);
    }
}

/*****************************************************************************
 * void gsi_resume_context()
 *
 *   Description:
 *     GSI Entry point for informing Java that a context has been resumed
 *
 *   Input Arguments:
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void gsi_resume_context ()
{
  JNIEnv *env = gsiRunLoopThreadEnv;
  gsi_int context = gsi_current_context ();

  if (fundebug)
    {
      printf ("CB: Function gsi_resume_context in context %d\n",
	      context);
      fflush (stdout);
    }

  dispatch_state_change_callback (context, JGI_STATE_RESUMED);

  if (fundebug)
    {
      printf ("CB: Exiting gsi_resume_context in context %d\n",
	      context);
      fflush (stdout);
    }
}

/*****************************************************************************
 * void gsi_reset_context()
 *
 *   Description:
 *     GSI Entry point for informing Java that a context has been reset
 *
 *   Input Arguments:
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void gsi_reset_context ()
{
  JNIEnv *env = gsiRunLoopThreadEnv;
  gsi_int context = gsi_current_context ();

  if (fundebug)
    {
      printf ("CB: Function gsi_reset_context in context %d\n",
	      context);
      fflush (stdout);
    }

  dispatch_state_change_callback (context, JGI_STATE_RESET);

  if (fundebug)
    {
      printf ("CB: Exiting gsi_reset_context in context %d\n",
	      context);
      fflush (stdout);
    }
}


/*****************************************************************************
 * void gsi_start_context()
 *
 *   Description:
 *     GSI Entry point for informing Java that a context has been reset
 *
 *   Input Arguments:
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void gsi_start_context ()
{
  JNIEnv *env = gsiRunLoopThreadEnv;
  gsi_int context = gsi_current_context ();

  if (fundebug)
    {
      printf ("CB: Function gsi_start_context in context %d\n",
	      context);
      fflush (stdout);
    }

  dispatch_state_change_callback (context, JGI_STATE_STARTED);

  if (fundebug)
    {
      printf ("CB: Exiting gsi_start_context in context %d\n",
	      context);
      fflush (stdout);
    }
}

/*****************************************************************************
 * void gsi_shutdown_context()
 *
 *   Description:
 *     GSI entry point for informing Java that the connection has shutdown
 *
 *   Input Arguments:
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void gsi_shutdown_context ()
{
  JNIEnv *env = gsiRunLoopThreadEnv;
  gsi_int context = gsi_current_context ();

  if (fundebug)
    {
      printf ("CB: Function gsi_shutdown_context in context %d\n",
	      context);
      fflush (stdout);
    }

  gsi_shutdown_context_with_context(context);

  if (fundebug)
    {
      printf ("CB: Exiting gsi_shutdown_context in context %d\n",
	      context);
      fflush (stdout);
    }
}

static void gsi_shutdown_context_with_context(int context) {
  JNIEnv *env = gsiRunLoopThreadEnv;

  dispatch_state_change_callback (context, JGI_STATE_SHUTDOWN);

  jgi_deregister_context_object(env, context);
  if (currentContextInJava == context)
    currentContextInJava = -1;

}

/*****************************************************************************
 * void gsi_g2_poll()
 *
 *   Description:
 *     GSI entry point for calling the periodic gsi poll routine
 *
 *   Input Arguments:
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void gsi_g2_poll()
{
  if (fundebug)
    {
      printf ("CB: Function gsi_g2_poll in context %d\n",gsi_current_context());
      fflush (stdout);
    }


  if (fundebug)
    {
      printf ("CB: Exiting gsi_g2_poll in context %d\n",gsi_current_context());
      fflush (stdout);
    }
}

void gsi_receive_deregistrations(registered_items, count)
gsi_registered_item  registered_items[];
gsi_int              count;
{
  gsi_int handle;
  gsi_registered_item* item;

  if (fundebug)
    {
      printf ("CB: Function gsi_receive_deregistrations for %d items in context %d\n",
	      count, gsi_current_context());
      fflush (stdout);
    }

  handle = gsi_handle_of(registered_items[0]);
  /* 
   printf("user data (should be 5) : %d\n",
	 gsi_user_data_of(gsi_registration_of(handle, gsi_current_context())));
  */
  
  {
    JNIEnv *env = gsiRunLoopThreadEnv;
    ContextData context_data = jgi_get_context_object(env, gsi_current_context());

    if (fulldebug) {
      fprintf (stdout, "Deregistration: Context Data = %lx (%lx)\n", context_data, JREF(context_data));
      fflush (stdout);
    }
      if (context_data) {
	int i=0;
	for (item=registered_items; i<count; i++, item++) {
	  handle = gsi_handle_of (*item);
	  /* fprintf (stdout, "Deregistering %d\n", handle); */
	  (*env)->CallVoidMethod (env,
				  JREF(context_data),
				  context_data->invalidateStub_MethodID,
				  handle,
				  JREF(context_data));
	}
      }
  }

  if (fundebug)
    {
      printf ("CB: Exiting gsi_receive_deregistrations in context %d\n",
	      gsi_current_context());
      fflush (stdout);
    }
}


/*****************************************************************************
 * void gsi_receive_message
 *   Description:
 *     GSI Entry point for sending a message to a java JGInterface
 *
 *   Input Arguments:
 *		message:		The message from G2
 *		length:			The number of chars in the message
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void gsi_receive_message(gsi_char *message, gsi_int length)
{
ContextData contextData;
JNIEnv *env = gsiRunLoopThreadEnv;
gsi_int context = gsi_current_context();

  if (fundebug)
    {
      printf ("CB: Function gsi_receive_message in context %d\n",
	      context);
      fflush (stdout);
    }

  /* Ensure that we have the gsi_run_loop thread environment to work in */
  /* and the Java methiod id of the call back method */
  if (env != NULL)
    {
         jstring jmessage_string =
	   jgi_NewString(gsiRunLoopThreadEnv, message);


         contextData = jgi_get_context_object(env, context);
	 if (contextData == NULL) return;

	 (*env)->CallVoidMethod (env,
				 JREF(registeredJGInterface),
				 registeredJGInterface->receiveMessage_MethodID,
				 JREF(contextData),
				 context,
				 jmessage_string);


	 jgi_check_and_return_g2_exception(env, context);
    }
    else if (fulldebug)
    {
      printf("Failed Calling Java Method:");
      printf("No Thread environment \n");
      fflush(stdout);
    }


  if (fundebug)
    {
      printf ("CB: Exiting gsi_receive_message in context %d\n",
	      context);
      fflush (stdout);
    }
}


void gsi_write_callback(gsi_int context, gsi_int state)
{

ContextData contextData;
JNIEnv *env = gsiRunLoopThreadEnv;

  if (fundebug)
    {
      printf ("CB: Function gsi_write_callback in context %d\n",
	      context);
      fflush (stdout);
    }

  /* Ensure that we have the gsi_run_loop thread environment to work in */
  /* and the Java methiod id of the call back method */
  if (env != NULL)
    {
         contextData = jgi_get_context_object(env, context);
	 if (contextData == NULL) return;

	 (*env)->CallVoidMethod (env,
				 JREF(registeredJGInterface),
				 registeredJGInterface->writeCallback_MethodID,
				 JREF(contextData),
				 context,
				 (jboolean)state);

	 jgi_check_and_return_g2_exception(env, context);
    }
    else if (fulldebug)
    { printf("Failed Calling Java Method:");
        printf("No Thread environment \n");
        fflush(stdout);
    }


  if (fundebug)
    {
      printf ("CB: Exiting gsi_write_callback in context %d\n",
	      context);
      fflush (stdout);
    }

}


void gsi_read_callback(gsi_int context, gsi_int state)
{

ContextData contextData;
JNIEnv *env = gsiRunLoopThreadEnv;

  if (fundebug)
    {
      printf ("CB: Function gsi_read_callback in context %d\n",
	      context);
      fflush (stdout);
    }

  /* Ensure that we have the gsi_run_loop thread environment to work in */
  /* and the Java methiod id of the call back method */
  if (env != NULL)
    {
         contextData = jgi_get_context_object(env, context);
	 if (contextData == NULL) return;

	 (*env)->CallVoidMethod (env,
				 JREF(registeredJGInterface),
				 registeredJGInterface->readCallback_MethodID,
				 JREF(contextData),
				 context,
				 (jboolean)state);


	 jgi_check_and_return_g2_exception(env, context);
    }
    else if (fulldebug)
    { printf("Failed Calling Java Method:");
        printf("No Thread environment \n");
        fflush(stdout);
    }


  if (fundebug)
    {
      printf ("CB: Exiting gsi_read_callback in context %d\n",
	      context);
      fflush (stdout);
    }


}

/******** End of Gsi callbacks section */


void stopCollecting () {
  collect_rpc_stats = FALSE;
}

void allocateStatBuffers (int numCalls) {
  if ((rpc_indices = (long*)malloc (numCalls * sizeof (long))) == NULL)
    return;
  if ((ts_call = (int*)malloc (numCalls * sizeof (int))) == NULL)
    return;
  if ((ts_return = (int*)malloc (numCalls *sizeof (int))) == NULL)
    return;
  if ((ts_done = (int*)malloc (numCalls * sizeof (int))) == NULL)
    return;
  if ((dts_wire = (int*)malloc (numCalls *sizeof (int))) == NULL)
    return;
  if ((dts_unpack = (int*)malloc (numCalls *sizeof (int))) == NULL)
    return;
  stat_buffer_size = numCalls;
  buffers_ok = TRUE;
}

void resetStatBuffers () {
  buffers_ok = FALSE;
  free (rpc_indices);
  free (ts_call);
  free (ts_return);
  free (ts_done);
  free (dts_wire);
  free (dts_unpack);
}

void startCollecting () {
  if (buffers_ok)
    collect_rpc_stats = TRUE;
}

void writeStats (JNIEnv *env, jstring jfileName) {
  FILE* fp = NULL;
  char* fileName = NULL;
  int i;
  int d_wire, d_unpack, d_wire_sum = 0, d_unpack_sum = 0;

  if (buffers_ok == FALSE)
    return;

  fileName = jgi_unicode2str (jgi_GetStringChars(env, jfileName));
  fp = fopen ((const char *)fileName, "w");
  /*fprintf (stdout, "Writing RPC profiling stats to %s\n", fileName);*/
  if (fp == NULL)
    return;

  fprintf (fp, "\n--------------------------------------------------------------------------------\n");
  fprintf (fp, "Call ID      Call Time    Return Time  Done Time    Wire Time    Unpack Time\n");
  fprintf (fp, "--------------------------------------------------------------------------------\n");
  for (i=0; i<num_measured_calls; i++) {
    d_wire = ts_return[i]-ts_call[i];
    d_unpack = ts_done[i]-ts_return[i];
    fprintf (fp, "%10d    %10d    %10d    %10d    %10d    %10d\n",
	     rpc_indices[i],
	     ts_call[i],
	     ts_return[i],
	     ts_done[i],
	     d_wire,
	     d_unpack);
    d_wire_sum += d_wire;
    d_unpack_sum += d_unpack;
  }

  fprintf (fp, "--------------------------------------------------------------------------------\n");
  fprintf (fp, "Total                                                   %10d   %10d\n",
	   d_wire_sum, d_unpack_sum);
  fprintf (fp, "--------------------------------------------------------------------------------\n");
  fprintf (fp, "Average                                                 %10d   %10d\n",
	   d_wire_sum/num_measured_calls,
	   d_unpack_sum/num_measured_calls);
  fprintf (fp, "--------------------------------------------------------------------------------\n");
  free (fileName);
  fclose (fp);
}

void clearProfilingData () {
  num_measured_calls = 0;
}

/*
 * Class:     com_gensym_jgi_GsiLoopThread
 * Method:    initializeStatBuffers0
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_initializeStatBuffers0
(JNIEnv *env, jobject intf, jint numCalls) {
  resetStatBuffers ();
  allocateStatBuffers (numCalls);
}

/*
 * Class:     com_gensym_jgi_GsiLoopThread
 * Method:    startCollectingRPCStats0
 * Signature: ()V
 */

JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_startCollectingRPCStats0
(JNIEnv *env, jobject intf) {
  startCollecting ();
}

/*
 * Class:     com_gensym_jgi_GsiLoopThread
 * Method:    stopCollectingRPCStats0
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_stopCollectingRPCStats0
(JNIEnv *env, jobject intf) {
  stopCollecting ();
}

/*
 * Class:     com_gensym_jgi_GsiLoopThread
 * Method:    writeRPCStats0
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_writeRPCStats0
(JNIEnv *env, jobject intf, jstring fileName) {
  writeStats (env, fileName);
}


/*
 * Class:     com_gensym_jgi_GsiLoopThread
 * Method:    clearProfilingData0
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_gensym_jgi_GsiLoopThread_clearProfilingData0
(JNIEnv *env, jclass intfClass) {
  clearProfilingData ();
}

int concurrent_calls_data_table[MAX_CONCURRENT_CALLS],
    concurrent_calls_index_table[MAX_CONCURRENT_CALLS];

int get_stat_index (int thread_data_address) {
  int i;
  for (i=0; i<MAX_CONCURRENT_CALLS; i++) {
    if (concurrent_calls_data_table[i] == thread_data_address) {
      concurrent_calls_data_table[i] = 0;
      /*fprintf (stdout, "get_stat_index (%lx) = %2d\n", thread_data_address, concurrent_calls_index_table[i]);*/
      return concurrent_calls_index_table [i];
    }
  }
  fprintf (stderr, "ERROR in get_stat_index. No stat_index found for call %lx\n", thread_data_address);
  return 0;
}

void save_stat_index (int thread_data_address, int index) {
  int i;
  for (i=0; i<MAX_CONCURRENT_CALLS; i++) {
    if (concurrent_calls_data_table[i] == 0) {
      concurrent_calls_data_table[i] = thread_data_address;
      concurrent_calls_index_table[i] = index;
      /*fprintf (stdout, "save_stat_index (%lx, %2d)\n", thread_data_address, index);*/
      return;
    }
  }
  fprintf (stderr, "ERROR in save_stat_index. No open table slots!\n");
}
