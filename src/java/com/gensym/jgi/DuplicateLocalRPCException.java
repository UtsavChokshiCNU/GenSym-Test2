package com.gensym.jgi;

/**
 * Signals that a Local Java method can not be declared
 * because a method of this name has already been predeclared
 * 
 * @version     1.00, 28-Feb-1997
 * @author      M.D.Gribble
 */
public class DuplicateLocalRPCException extends RuntimeException {

  /* NOTE Class extends RuntimeException, compiler does not moan if is
     not caught at compile time */

  /**
   * Constructs a DuplicateLocalRPCException with no detail message.
   * A detail message is a String that describes this particular exception.
   */
  public  DuplicateLocalRPCException () {
    super ();
  }

  /**
   * Constructs a DuplicateLocalRPCException with the specified detail message.
   * A detail message is a String that describes this particular exception.
   * @param details the detail message
   */
  public  DuplicateLocalRPCException (String details) {
    super (details);
  }
}
