/* This file contains classes for calling C code.  Each C entry point has its
 * own subclass of the basic class Work (which doesn't do anything).  Each class
 * has private variables which correspond to the parameters of the C function to
 * be called.  JGInterface makes Work_*'s and enqueues them into GsiLoopThread,
 * which dequeues them and calls the invoke method to actually have the C
 * function called.
 *
 * Real java studs could probably figure out how to do this with reflection.
 */

package com.gensym.jgi;
import com.gensym.util.Symbol; 
import com.gensym.util.Structure; 
import com.gensym.classes.Item; 
import com.gensym.message.Trace;
abstract class Work {
  public abstract void invoke ();
}

abstract class WorkWithContext extends Work {
  protected int inner_context;
  public int getContext() { return inner_context; }
}
 

class Work_setFulldebug extends Work{
  private boolean innerstate;
  Work_setFulldebug(boolean state) {
    innerstate= state;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.setFulldebug (innerstate);
  }
}

class Work_startCollectingRPCStats0 extends Work {
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.startCollectingRPCStats0 ();
  }
}
class Work_stopCollectingRPCStats0 extends Work {
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.stopCollectingRPCStats0 ();
  }
}
class Work_clearProfilingData0 extends Work {
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.clearProfilingData0 ();
  }
}

class Work_writeRPCStats0 extends Work {
  String inner_filename;
  Work_writeRPCStats0(String fileName){
    inner_filename = fileName;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.writeRPCStats0(inner_filename);
  }
}

class Work_checkHandleType extends WorkWithContext {
  int inner_handle;
    public Work_checkHandleType(int context, int handle){
      inner_handle = handle;
      inner_context = context;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.checkHandleType (inner_context, inner_handle);
  }
}
class Work_closeConnectionNative extends WorkWithContext {
     public Work_closeConnectionNative(int context){
       inner_context = context;
   }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ()+ " context = "+ inner_context);
    GsiLoopThread.invocation.closeConnectionNative(inner_context);
  }
}
class Work_declareLocalRPCNative extends Work {
  Symbol inner_g2_RPD_name;
  boolean inner_connectionSpecific;
    public Work_declareLocalRPCNative(Symbol g2_RPD_name, boolean connectionSpecific){
      inner_connectionSpecific = connectionSpecific;
      inner_g2_RPD_name = g2_RPD_name;

  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString () + " GSI loop thread: " + GsiLoopThread.invocation.toString () + " called from " + Thread.currentThread ());
    GsiLoopThread.invocation.declareLocalRPCNative(inner_g2_RPD_name, inner_connectionSpecific);
  }
}
class Work_initializeStatBuffers0 extends Work {
  int inner_numCalls;
  public Work_initializeStatBuffers0(int numCalls){
    inner_numCalls = numCalls;
   }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.initializeStatBuffers0 (inner_numCalls);
  }
}
class Work_reportLogBookErrorMessage extends WorkWithContext {
  Symbol inner_error_symbol;
  String inner_error_message;
    public Work_reportLogBookErrorMessage(Symbol error_symbol, String error_message, int context){
      inner_error_message = error_message;
      inner_error_symbol = error_symbol;
      inner_context = context;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.reportLogBookErrorMessage(inner_error_symbol, inner_error_message, inner_context);
  }
}
class Work_returnAttrs extends WorkWithContext {
  Item inner_variable;
  Structure inner_attributesArray;
  Object inner_values;
  int inner_statusValues;
    public Work_returnAttrs(Item variable, Structure attributesArray, Object values, int statusValues, int context){
      inner_context = context;
      inner_statusValues = statusValues;
      inner_values = values;
      inner_attributesArray = attributesArray;
      inner_variable = variable;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.returnAttrs(inner_variable, inner_attributesArray, inner_values, inner_statusValues, inner_context);
  }
}
class Work_returnMessage extends WorkWithContext {
  String inner_message;
    public Work_returnMessage(String message, int context){
      inner_context = context;
      inner_message = message;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.returnMessage(inner_message, inner_context);
  }
}
class Work_setGSIContextLimit extends Work {
  int inner_limit;
    public Work_setGSIContextLimit(int limit){
      inner_limit = limit;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.setGSIContextLimit(inner_limit);
  }
}
class Work_nativeRegisterContextObject extends WorkWithContext {
  G2Connection inner_context_object;
  String inner_remote_string;
    public Work_nativeRegisterContextObject(G2Connection context_object, int context, String remote_process_string){
      inner_context = context;
      inner_context_object = context_object;
      inner_remote_string = remote_process_string;      
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.nativeRegisterContextObject(inner_context_object, inner_context, inner_remote_string);
  }
}
class Work_returnRPCValue extends WorkWithContext {
  long inner_call_index;
  Object inner_result;
  boolean inner_force_return_value;
  boolean inner_error;
  Symbol inner_error_symbol;
  String inner_error_text;
    public Work_returnRPCValue(long call_index, Object result, boolean force_return_value, boolean error, Symbol error_symbol, String error_text, int context){
      inner_context = context;
      inner_error_text = error_text;
      inner_error_symbol = error_symbol;
      inner_error = error;
      inner_force_return_value = force_return_value;
      inner_result = result;
      inner_call_index = call_index;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.returnRPCValue(inner_call_index, inner_result, inner_force_return_value, inner_error, inner_error_symbol, inner_error_text, inner_context);
  }
}
class Work_returnValues extends WorkWithContext {
  Object[] inner_variables;
  Structure[] inner_attributesArray;
  Object[] inner_values;
  int[] inner_statusValues;
    public Work_returnValues(Object[] variables, Structure[] attributesArray, Object[] values, int[] statusValues, int context){
      inner_context = context;
      inner_statusValues = statusValues;
      inner_values = values;
      inner_attributesArray = attributesArray;
      inner_variables = variables;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.returnValues(inner_variables, inner_attributesArray, inner_values, inner_statusValues, inner_context); 
  }
}
class Work_setFundebug extends Work {
  boolean inner_state;
     public Work_setFundebug(boolean state){
       inner_state = state;
   }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.setFundebug(inner_state);
  }
}
class Work_setConvdebug extends Work {
  boolean inner_state;
     public Work_setConvdebug(boolean state){
       inner_state = state;
   }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.setConvdebug(inner_state);
  }
}


class Work_startInterface extends Work {
  String[] inner_command;
  Object inner_interface;
     public Work_startInterface(Object intrface, String[] command){
       inner_interface = intrface;
       inner_command = command;
   }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.startInterface(inner_interface, inner_command);
  }
}

class Work_setInterfaceOutput extends Work {
  boolean inner_state;
     public Work_setInterfaceOutput(boolean state){
       inner_state = state;
   }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.setInterfaceOutput(inner_state);
  }
}
class Work_setRPCRemoteReturnValueKindNative extends WorkWithContext {
  long inner_g2_function_handle;
  int inner_return_value_index;
  int inner_return_value_type;
    public Work_setRPCRemoteReturnValueKindNative(long g2_function_handle, int return_value_index, int return_value_type, int context){
      inner_context = context;
      inner_return_value_type = return_value_type;
      inner_return_value_index = return_value_index;
      inner_g2_function_handle = g2_function_handle;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.setRPCRemoteReturnValueKindNative (inner_g2_function_handle, inner_return_value_index, inner_return_value_type, inner_context);
  }
  @Override
  public String toString () {
    return super.toString () + "[" + inner_g2_function_handle + "("+ inner_return_value_index +  "," + inner_return_value_type + ")]";
  }

}
class Work_setReceiveRegistrations extends WorkWithContext {
  boolean inner_status;
    public Work_setReceiveRegistrations(int context, boolean status){
      inner_status = status;
      inner_context = context;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.setReceiveRegistrations(inner_context, inner_status);
  }
}

class Work_getCurrentContext extends Work {
  Return_int inner_synchronizer;
  Work_getCurrentContext (Return_int synchronizer){
    inner_synchronizer = synchronizer;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    int value = GsiLoopThread.invocation.getCurrentContext();
    inner_synchronizer.setValue (value); 
  }
}


class Work_declareRemoteRPCNative extends WorkWithContext {
  String inner_g2_procedure_name;
  int inner_remote_arg_count;
  int inner_return_arg_count;
  String inner_java_receiver_method_name;
  Return_long inner_synchronizer;

  Work_declareRemoteRPCNative(String g2_procedure_name, int remote_arg_count, int return_arg_count, String java_receiver_method_name, int context, Return_long synchronizer)
  {
    inner_g2_procedure_name = g2_procedure_name;
    inner_remote_arg_count = remote_arg_count;
    inner_return_arg_count = return_arg_count;
    inner_java_receiver_method_name = java_receiver_method_name;
    inner_context = context;
    inner_synchronizer = synchronizer;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    long value =
      GsiLoopThread.invocation.declareRemoteRPCNative(inner_g2_procedure_name,
					   inner_remote_arg_count,
					   inner_return_arg_count,
					   inner_java_receiver_method_name,
					   inner_context);
    inner_synchronizer.setValue (value);
  }
  @Override
  public String toString () {
    return super.toString () + "[" + inner_g2_procedure_name + "("+ inner_remote_arg_count +  "," + inner_return_arg_count + ")]";
  }


}




class Work_getListenerSocket extends Work {
  Return_int inner_synchronizer;
  Work_getListenerSocket(Return_int synchronizer){
    inner_synchronizer = synchronizer; 
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    int value = GsiLoopThread.invocation.getListenerSocket();
    inner_synchronizer.setValue (value);
  }
}

class Work_callRPCNative extends WorkWithContext {
  long inner_function_handle;
  Object inner_arguments[];
  boolean inner_start_proc;
  Object inner_user_data;
  Work_callRPCNative(long function_handle,  Object arguments[], boolean start_proc, Object user_data, int context){
    inner_function_handle = function_handle;
    inner_arguments = arguments;
    inner_start_proc = start_proc;
    inner_user_data = user_data;
    inner_context = context;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.invocation.callRPCNative(inner_function_handle, inner_arguments, inner_start_proc, inner_user_data, inner_context);
  }

  @Override
  public String toString () {
    return super.toString () + "[" + inner_function_handle + ", " + inner_user_data  + "]";
  }

}
class Work_checkForHandleOK extends WorkWithContext {
  Return_String inner_synchronizer;
  int inner_handle;
  Work_checkForHandleOK(int context, int handle,Return_String synchronizer){
    inner_synchronizer = synchronizer;
    inner_context = context;
    inner_handle = handle;
  }
  @Override
  public void invoke () {
    //System.out.println ("invoking " + this.toString ());
    String value = GsiLoopThread.invocation.checkForHandleOK(inner_context, inner_handle);
    //System.out.println (this.toString ()+ " returned "+ value);
    //System.out.flush();
    inner_synchronizer.setValue (value);
  }
}
class Work_getRemoteHostNative extends WorkWithContext {
  Return_String inner_synchronizer;
  Work_getRemoteHostNative(int context,Return_String synchronizer){
    inner_synchronizer = synchronizer;
    inner_context = context;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    String value = GsiLoopThread.invocation.getRemoteHostNative(inner_context);
    inner_synchronizer.setValue (value);
  }
}
class Work_initiateConnectionNative extends Work {
  Return_boolean inner_synchronizer;
  String inner_interface_name;
  String inner_class_name;
  boolean inner_keep_connection;
  String inner_network;
  String inner_host;
  String inner_port;
  String inner_rpis;
  String inner_callback_identification;
  boolean inner_secure;

  Work_initiateConnectionNative(String interface_name, String class_name, boolean keep_connection, String network, String host, String port, String rpis, String callback_identification, boolean secure, Return_boolean synchronizer){
    inner_synchronizer = synchronizer;
    inner_interface_name = interface_name;
    inner_class_name = class_name;
    inner_keep_connection = keep_connection;
    inner_network = network;
    inner_host = host;
    inner_port = port;
    inner_rpis = rpis;
    inner_callback_identification = callback_identification;
    inner_secure = secure;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    boolean value = GsiLoopThread.invocation.initiateConnectionNative(inner_interface_name, inner_class_name, inner_keep_connection, inner_network, inner_host, inner_port, inner_rpis, inner_callback_identification, inner_secure);
//System.out.println ("returning from " + this.toString ());
    inner_synchronizer.setValue (value);
  }
  @Override
  public String toString () {
    return super.toString () + "[" + inner_callback_identification+ "]";
  }

}
class Work_getRemotePortNative extends WorkWithContext {
  Return_int inner_synchronizer;
  Work_getRemotePortNative(int context,Return_int synchronizer){
    inner_synchronizer = synchronizer;
    inner_context = context;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    int value = GsiLoopThread.invocation.getRemotePortNative(inner_context);
    inner_synchronizer.setValue (value);
  }
}

class Work_getRemoteSecureContext extends WorkWithContext {
  Return_int inner_synchronizer;
  Work_getRemoteSecureContext(int context, Return_int synchronizer){
    inner_synchronizer = synchronizer;
    inner_context = context;
  }
  @Override
  public void invoke () {
System.out.println ("invoking " + this.toString ());
    int value = GsiLoopThread.invocation.getRemoteSecureContext(inner_context);
    inner_synchronizer.setValue (value);
  }
}


//and here are some callback functions which are slightly different but still
//pretty much the same thing

class Work_communicationError extends WorkWithContext {
  int inner_error_code;
  String inner_error_message;
  String inner_initiate_connection;
    public Work_communicationError(int context, int error_code, String error_msg,
				String initiateConnectionId){
      inner_error_code = error_code;
      inner_context = context;
      inner_error_message = error_msg;
      inner_initiate_connection = initiateConnectionId;
  }
  @Override
  public void invoke () {
//System.out.println ("invoking " + this.toString ());
    GsiLoopThread.intrface.handleCommunicationError (inner_context, inner_error_code, inner_error_message, inner_initiate_connection);
  }
}

class Work_dispatchG2ConnectionClose extends WorkWithContext {
   G2Connection inner_connection;
   G2ConnectionEvent inner_event;
   public Work_dispatchG2ConnectionClose(G2Connection connection, int context, G2ConnectionEvent event) {
     inner_connection = connection;
     inner_context = context;
     inner_event = event;
   }
   @Override
   public void invoke () {
//System.out.println ("invoking " + this.toString ());
     GsiLoopThread.intrface.handleG2ConnectionClosed(inner_connection, inner_context, inner_event);
   }
  @Override
  public String toString () {
    return super.toString () + "[" + inner_context + "," + inner_event + "," + inner_connection+ "]";
  }

}

class Work_dispatchG2ConnectionEvent extends WorkWithContext {
   G2Connection inner_connection;
   G2ConnectionEvent inner_event;
   public Work_dispatchG2ConnectionEvent(G2Connection connection, int context, G2ConnectionEvent event) {
     inner_connection = connection;
     inner_context = context;
     inner_event = event;
   }
   @Override
   public void invoke () {
//System.out.println ("invoking " + this.toString ());
     GsiLoopThread.intrface.dispatchG2ConnectionEvent(inner_connection, inner_context, inner_event);
   }
  @Override
  public String toString () {
    return super.toString () + "[" + inner_context + "," + inner_event + inner_connection+ "]";
  }

}

class Work_registerIncomingConnection extends WorkWithContext {
   String inner_process_string;
   String inner_object_id;
   public Work_registerIncomingConnection(int context, 
							String remote_process_string, 
							String context_object_id) {
     inner_process_string = remote_process_string;
     inner_context = context;
     inner_object_id = context_object_id;
   }
   @Override
   public void invoke () {
     try {
//System.out.println ("invoking " + this.toString ());
       GsiLoopThread.intrface.handleRegisterIncomingConnection(inner_context, inner_process_string, inner_object_id);
     } catch (Exception e) {
     Trace.exception (e);
   }
   }
  @Override
  public String toString () {
    return super.toString () + "[" + inner_context + "]";
  }

}
