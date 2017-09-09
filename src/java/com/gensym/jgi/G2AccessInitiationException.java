package com.gensym.jgi;

import java.lang.Exception;

/**
 * Signals that a problem has occured while attempting an initial
 * connection to G2.
 *
 * @version     1.00 29-Oct-1997
 * @author      Robert Penny
 */

public class G2AccessInitiationException
       extends G2AccessException {

  public G2AccessInitiationException () {
    super ();
  }

  public G2AccessInitiationException (String key) {
    super (key);
  }

  public G2AccessInitiationException (Exception target_exception, String key)
  {
    super(target_exception, key);
  }

  public G2AccessInitiationException (Exception target_exception)
  {
    super(target_exception);
  }

}
