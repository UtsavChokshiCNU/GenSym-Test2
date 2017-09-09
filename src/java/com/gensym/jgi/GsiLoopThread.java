/****************************************************************************
 * 	 Class GsiLoopThread
 *
 *   Description: 
 *	   A class defined just to handle the run loop in a separate thread
 *     
 *
 *	   IF YOU CHANGE THESE CLASSES YOU MUST USE JAVAH AND REMAKE
 *     
 *   Public Methods:
 *     
 *   Private Methods:
 *	
 *   Public Attributes:
 *     
 *   Modifications:
 *
 *****************************************************************************/
// Class to deal with Gsi polling
// Only ever create one of these
/* 
 * We need to start up the interface in the same thread that runs the run loop.
 * This is necessary on Win32 because start opens up a window to listen to
 * network events. GetMessage only retrieves messages posted for windows created
 * by a *Thread*. After startup, the thread that spawned this is notfied so that
 * it can return */

package com.gensym.jgi;
import com.gensym.util.Structure; 
import com.gensym.util.Symbol; 
import com.gensym.classes.Item;
import java.util.Vector;
class GsiLoopThread extends Thread
{
  static boolean started = false;
  static volatile GsiLoopThread invocation = null;

  static volatile JGInterface intrface;
  private String []commandLine;
  private boolean option_debug = false;

  GsiLoopThread (JGInterface intf, String []cmdLine, boolean optionDebug) {
    super ("JavaLink GSI Loop");
    intrface = intf;
    commandLine = cmdLine;
    invocation = this;
    option_debug = optionDebug;
  }

  // Methods for handling the GSI polling status
	
  // gsi run loop thread, starts here
  @Override
  public void run() {

    int return_value;
//    setFulldebug(option_debug);
//    setFundebug(option_debug);
      if ((return_value = initialize_tickle ()) != 0)
	JGInterface.getJGInterface(new String[0]).communicationError(-1, -1, "failed to initialize JNI code: "+return_value, null);
      new GsiInitializeThread().start();
      yield();
      if ((return_value = finalize_tickle ()) != 0)
	JGInterface.getJGInterface(new String[0]).communicationError(-1, -1, "failed to initialize JNI code (final): "+return_value, null);
      // Ensure that GSI messages are turned off, during GSI startup
      // when option_debug = FALSE
      setInterfaceOutput(option_debug);

      // this function will actually set of a bunch of GSI options and
      // start GSI.  First, the above enqueued requests will be taken
      // care of.
      startInterface (intrface, commandLine);

      while(true) {
	try {
	  if (started) 
	    {
	      //look for work to do.  In the future, we will have some
	      //fancy notify thing, currently we are being very slow
	      //and waiting for GSI run loop to return.
	      Work work = dequeue ();
	      if (work != null) {
                //System.out.println ("work to do!  " + work.toString ());
                //System.out.flush ();
		try {
		  work.invoke ();
		} catch  (G2CommunicationException e) {
		  if (work instanceof WorkWithContext) {
		    //Caught an error from C code.  handleCommunicationError
		    //will eventually call the user's G2ConnectionListener with
		    //the error object.  Unfortunately there's no way to figure
		    //out the correct error code, thus the -1.
		    intrface.handleCommunicationError (((WorkWithContext)work).getContext(), -1, e.getMessage(), null);
		  }
		}
	      }
	      //If we have work to do, then we shouldn't call gsi_pause.  But we
	      //must call gsi_run_loop to check for work from the G2 side.
	      //gsi_run_loop will only pause if its boolean "pause" variable is
	      //true, i.e. if work is null.  Additionally, if we're about to
	      //come back and check the work queue without entering gsi_pause,
	      //there's no need for other user threads to call tickle_gsi to
	      //wake it up.  Tickling unnecessarily had a noticeable performance
	      //impact per issue HQ-4696151.  See more info about tickling in
	      //comments in jni_gi.c.
	      needsTickle = (work == null);
	      gsi_run_loop(needsTickle);
	      needsTickle = false;
	      //System.out.print ("<< Run Loop Done\n");
	      //System.out.println(Runtime.getRuntime().totalMemory() + "/" + Runtime.getRuntime().freeMemory());
	      //System.out.flush ();
	    }
	  else { // wait to be started
	    //System.out.println ("GSI loop waiting to be started");
	    //System.out.flush ();
	    sleep(500);

	  }
	}catch (Exception e) {
	  com.gensym.message.Trace.exception(e, "Exception raised during GsiLoop processing");
	  JGInterface jgi = JGInterface.getJGInterface(new String[0]);

	  if (jgi==null)
	    throw new RuntimeException(e.toString());
	  else
	    jgi.communicationError(-1, -1, e.toString(), null);

	}

      }
  }


  void enableRunLoop()
  {
    started = true;
  }

  // our work queue management

  native void tickle_gsi ();
  native int initialize_tickle ();
  native int finalize_tickle ();
  static native int connect_tickle ();

  protected boolean needsTickle = true;
  private Vector work_queue = new Vector();
  public void enqueue(Work work) {
    work_queue.addElement (work);
    if (needsTickle) {
      needsTickle = false;
      tickle_gsi ();
    }
  }
  public Work dequeue () {
    try {
      if (!work_queue.isEmpty())
	return (Work)work_queue.remove (0); 
      else return null;
    } catch (ArrayIndexOutOfBoundsException e) {
      return null;
    }
  }

  // management of return values from callbacks
  private Vector callbacks_queue = new Vector ();

  //native function declarations
  native int getCurrentContext ();
	
  final native void gsi_run_loop(boolean pauseP);


  // Methods providing access to Gsi
  // ***************************************

  // Methods that are declared public to be visible by native method code
  // but are infact private
  // Dont use double ** so that they dont get documented
  /*
   * Call the standard GSI start up function.  */
  final native void startInterface(Object JGInterface, String []cmdline);


  /**
   * Predeclare a g2 procedure name so that the JGInterface can call it.
   *
   * @param g2_procedure_name   The G2 function nane to call
   * @param remote_arg_count   The number of arguments of the remote procedure
   * @param return_arg_count   The number of return arguments expected
   */
  final native long declareRemoteRPCNative(String g2_procedure_name, 
						       int remote_arg_count,
						       int return_arg_count,
						       String java_receiver_method_name,
						       int context);

  /**
   * Call a G2 predeclared G2 procedure and return immediately.
   * The G2 procedure is executed asynchrounsly. GSI will call a
   * predefined method with any return values once G2 has executed the
   * procedure.  Or, if user_data is passed in, when the GSI callback
   * is invoked to report the return values, it will signal the
   * user_data object.
   *
   * @param function_handle  The identification of the predeclared G2 procedure
   * @param arguments   The arguments to pass to the G2 procedure
   * @param user_data   an instance of G2RemoteRPCThreadData, or null.
   * @param start_proc  set true to make G2 start the procedure, false for call
   *
   * @return the call_index of the call */
  final native void callRPCNative(long function_handle, 
						 Object arguments[],
						 boolean start_proc,
						 Object user_data,
						 int context);

  /**
   * Return a value as a result of a G2 RPC call, given its call_index
   *
   */
  final native void returnRPCValue(long call_index, 
						Object result,
						boolean force_return_value,
						boolean error,
						Symbol error_symbol,
						String error_text,
						int context);

  /**
   * Switch the status of fulldebug native 
   * information appearing on the Java console.
   */
  public static native void setFulldebug(boolean state);

  /**
   * Switch the status of function level native debugging 
   * appearing 0n the Java console
   */
  public static native void setFundebug(boolean state);

  /**
   * Switch the status of data conversion conversion function level native debugging 
   * appearing 0n the Java console
   */
  public static native void setConvdebug(boolean state);

  /**
   * Switch the status of low level interface messages, warnings, errors to stdout
   */
  public static native void setInterfaceOutput(boolean state);

 
  /**
   * PRIVATE METHOD - Set the return value kind of a remote RPC parameter
   */
  native void setRPCRemoteReturnValueKindNative (long g2_function_handle,
						    int return_value_index,
						    int return_value_type,
								     int context);


  /**
   * PRIVATE METHOD - Intiate a connection will a G2 
   */
  native boolean initiateConnectionNative(String interface_name,
   							String class_name,
							boolean keep_connection,
							String network,
							String host,
							String port,
							String rpis,
						        String callback_identification,
                           			 	boolean secure);

  /**
   * PRIVATE METHOD = update variables with new values
   */
  native void returnValues(Object[] variables,
					Structure[] attributesArray,
					Object[] values,
					int[] statusValues,
					int context);

  
  /**
   * PRIVATE METHOD = update item with new value and attributes
   */
  native void returnAttrs(Item variable,
					Structure attributesArray,
					Object values,
					int statusValues,
					int context);
  /** Sets if receiveRegistrations is called when an item is first registered */
  final native void setReceiveRegistrations(int context, boolean status);



  /**
   * Return a message to a connected G2
   * 
   * <P> The message text is sent to the MESSAGE-BOARD item in the current KB 
   * of the connected G2.
   *
   * @param message the message to send to G2's message board
   * @param context the context number of the G2 connection to send the message
   */
  final native void returnMessage(String mesage, int context);



  /**
   * Set the maximum number of G2 Gateway (GSI) Contexts we will allow in this client.
   *
   * @param limit An integer limit.  Default (inherited from G2 Gateway) is 50.
   *
   */
  final native void setGSIContextLimit(int limit);


  /**
   * Return the listener Socket that GSI is waiting for G2 connections on 
   */
  final native int getListenerSocket(); 


  /**
   * Report an Error message to the Logbook of a connected G2
   *
   */
  final native void reportLogBookErrorMessage(Symbol error_symbol, String error_message, int context);


    
  /**
   * Shutdown an existing connection  - native call
   */
  final native void closeConnectionNative(int context);

  /** Get remote Host name for a connection */
  final native String getRemoteHostNative(int context);

  /** get remote port for a connection */
  final native int getRemotePortNative(int context);

  /** get context security status */
  final native int getRemoteSecureContext(int context);
     
  /**
   * Predeclare a method so that it can be called by a connected G2.
   *
   * <P>Any connected G2 can call the public methods in a Java 
   * application that have been declared using <B>declareRPCLocalNative</B>. 
   *
   * @param g2_RPD_name The G2 name to refer to this method
   * @param connecionSpecific Set true if the connection is intended for a conenciton only
   */
  final native void declareLocalRPCNative(Symbol g2_RPD_name,
							       boolean connectionSpecific);


  final native void nativeRegisterContextObject (G2Connection context_object, int context, String remote_string);

 
  // Initiate auth check (not normally needed, as the native lib will do this on connection)
  native void checkHandleType (int context, int handle);
  // Check if authorization has passed (the native lib will have already killed the context if not 
  // authorized for Javalink, handle = 0 for Javalink, handle = 1 for Jlp
  native String checkForHandleOK(int context, int handle);
  static native void initializeStatBuffers0 (int numCalls);
  static native void startCollectingRPCStats0 ();
  static native void stopCollectingRPCStats0 ();
  static native void writeRPCStats0 (String fileName);
  static native void clearProfilingData0 ();
}

