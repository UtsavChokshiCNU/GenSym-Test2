package com.gensym.jgi;

/**
 * Signals that a Remote G2 RPC can not be called because
 * the G2 procedure/method has not been predeclared using
 * G2Gateway.declareRemoteRPC.
 * 
 * @version     1.00, 25-Feb-1997
 * @author      M.D.Gribble
 */
public class G2RemoteRPCNotPredeclaredException extends RuntimeException {

  /* NOTE Class extends RuntimeException, compiler does not moan if is
     not caught at compile time */

  /**
   * Constructs a G2RemoteRPCNotPredeclaredException with no detail message.
   * A detail message is a String that describes this particular exception.
   */
  public  G2RemoteRPCNotPredeclaredException () {
    super ();
  }

  /**
   * Constructs a G2RemoteRPCNotPredeclaredException with the specified detail message.
   * A detail message is a String that describes this particular exception.
   * @param details the detail message
   */
  public  G2RemoteRPCNotPredeclaredException (String details) {
    super (details);
  }
}
