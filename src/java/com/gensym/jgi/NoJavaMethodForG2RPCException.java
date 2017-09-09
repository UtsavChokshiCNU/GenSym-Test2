package com.gensym.jgi;

/**
 * Signals that a a Java method could not be found
 * to invoke as a result of a G2 RPC.
 * Possibly due to a Java Method not being registered 
 * for the G2 RPC name for a particular G2Connection.
 *
 * @version     1.00 22-Feb-1998
 * @author      M.D.Gribble
 */

public class NoJavaMethodForG2RPCException
       extends java.lang.RuntimeException {

  public NoJavaMethodForG2RPCException () {
    super ();
  }

  public NoJavaMethodForG2RPCException (String key) {
    super (key);
  }

}
