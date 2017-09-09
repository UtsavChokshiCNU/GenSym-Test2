package com.gensym.jgi;

/**
 * Signals that a timeout occured with some connection.
 *
 * @version     1.00 7-may-97
 * @author      R. L. Penny
 */

public class ConnectionTimedOutException
       extends G2AccessInitiationException {

  public ConnectionTimedOutException () {
    super ();
  }

  public ConnectionTimedOutException (String key) {
    super (key);
  }

	 //public ConnectionTimedOutException (String key, Object[] args) {
	 //  super (key, args);
	 //}
}
