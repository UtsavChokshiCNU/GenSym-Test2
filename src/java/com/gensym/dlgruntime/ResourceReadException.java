
package com.gensym.dlgruntime;

/**
 * Exception thrown when an error occurs in instantiating a resource
 * after the data has been read
 *
 * @author vkp
 * @version 1.0 12/24/97
 */

public class ResourceReadException extends Exception {

  private Exception nestedException;

  /**
   * Constructs a new ResourceReadException with a specified
   * nested exception
   */
  public ResourceReadException (Exception e) {
    super ();
    nestedException = e;
  }

  /**
   * Constructs a new ResourceReadException with a specified detail message
   * and a specified nested exception.
   */
  public ResourceReadException (String details, Exception e) {
    super (details);
    nestedException = e;
  }

  /**
   * Returns the Exception that occured during resource read that
   * caused this Exception to be thrown
   */
  public Exception getNestedException () {
    return nestedException;
  }

  /**
   * Return a description of this exception
   */
  @Override
  public String toString () {
    System.out.println ("Stack of nested Exception ");
    nestedException.printStackTrace (System.out);
    return super.toString () + "\n  NestedException is " + nestedException;
  }
  

}
