
package com.gensym.dlgruntime;

/**
 * Exception thrown when an error occurs in interpreting a resource
 * @author rpenny
 * @version 1.0 10/22/98
 */

public class ResourceDescriptionException extends Exception {

  private Exception nestedException;

  /**
   * Constructs a new ResourceDescriptionException with a specified
   * nested exception
   */
  public ResourceDescriptionException (Exception e) {
    super ();
    nestedException = e;
  }

  /**
   * Constructs a new ResourceDescriptionException with a specified detail message
   * and a specified nested exception.
   */
  public ResourceDescriptionException (String details, Exception e) {
    super (details);
    nestedException = e;
  }

  /**
   * Returns the Exception that occured during resource description that
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
