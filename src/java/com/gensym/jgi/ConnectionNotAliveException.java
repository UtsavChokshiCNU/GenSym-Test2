package com.gensym.jgi;

/**
 * Signals that a problem has occured while attempting to access G2 via
 * a G2Connection that is not alive.
 *
 * @version     1.00 22-April-98
 * @author      M.D.Gribble
 */

public class ConnectionNotAliveException
       extends G2AccessException {

  public ConnectionNotAliveException () {
    super ();
  }

  public ConnectionNotAliveException (String key) {
    super (key);
  }

  public ConnectionNotAliveException (Exception target_exception, String key)
  {
    super(target_exception, key);
  }

  public ConnectionNotAliveException (Exception target_exception)
  {
    super(target_exception);
  }

}
