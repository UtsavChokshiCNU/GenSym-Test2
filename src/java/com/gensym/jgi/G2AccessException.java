package com.gensym.jgi;

import java.io.PrintWriter;

/**
 * Signals that a problem has occured while accessing G2.
 *
 * @version     1.01 9-June-1998
 * @author      M.D.Gribble
 */

public class G2AccessException
       extends Exception {

  private Exception _nestedException = null;

  /**
   * Constructs a new <code>G2AccessException</code> with no detail message. 
   * 
   *
   */
  public G2AccessException () {
    super ();
  }


  /**
   * Constructs a new <code>G2AccessException</code> with the specified detail 
   * message. 
   *
   * @param   message   the detail message.
   */
  public G2AccessException (String key) {
    super (key);
  }

  /**
   * Constructs a new <code>G2AccessException</code> with a specified
   * nested exception and detail message. 
   *
   * @param   message   the detail message.
   * @param   nestedException a nested exception which caused the G2AccessException to be thrown
   */
  public G2AccessException (Exception nestedException, String key)
  {
    super(key);
    _nestedException = nestedException;
  }


 /**
   * Constructs a new <code>G2AccessException</code> with a sepcified 
   * nested exception.
   *
   * @param nestedException a nested exception which caused the G2AccessException to be thrown
   */ 
  public G2AccessException (Exception nestedException)
  {
    super();
    _nestedException = nestedException;
  }

  /**
   * Return any nested Exception.
   * @return the nested exception or null
   */
  public Exception getNestedException() {
    return _nestedException;
  }

  /**
   * Prints this <code>G2AccessException</code> and its backtrace to the 
   * specified print stream. The Stack Trace of any nested exception is also
   * included if present.
   *
   */
  @Override
  public void printStackTrace() {
    super.printStackTrace();
    if (_nestedException != null) {
      System.out.println("Nested Exception: ");
      _nestedException.printStackTrace();
    }
  }

 /**
  * Prints this <code>G2AccessException</code> and its backtrace to the specified
  * print writer. The Stack Trace of any nested exception is also
  * included if present.
  *
  */
  @Override
  public void printStackTrace(PrintWriter writer) {
    super.printStackTrace(writer);
    if (_nestedException != null) {
      writer.println("Nested Exception: ");
      _nestedException.printStackTrace(writer);
    }
  }
    
  /**
   * Produce the message, include the message from the nested
   * exception if there is one.
   */
  @Override
  public String getMessage() {
    String myMessage = super.getMessage();
    if (_nestedException == null) 
      return myMessage;
    else
      return (myMessage == null ? "" : myMessage + " ; ") + 
	"nested exception is: \n\t" +
	_nestedException.toString();
  }


}
