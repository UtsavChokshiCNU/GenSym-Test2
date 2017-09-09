package com.gensym.jgi;

/**
 * Signals that a G2Gateway can not continue an operation as it has not
 * been initialized.
 *
 * @version     1.01 20-Aug-97
 * @author      M.D.Gribble
 */

public class G2GatewayNotInitializedError
       extends java.lang.Error {

  public G2GatewayNotInitializedError () {
    super ();
  }

  public G2GatewayNotInitializedError (String key) {
    super (key);
  }


}
