package com.gensym.wksp;

class FatalWorkspaceException extends Exception
{
  private Exception _nestedException = null;

  /**
   * Constructs a new <code>G2AccessException</code> with no detail message. 
   * 
   *
   */
  public FatalWorkspaceException () {
    super ();
  }


  /**
   * Constructs a new <code>FatalWorkspaceException</code> with the specified detail 
   * message. 
   *
   * @param   message   the detail message.
   */
  public FatalWorkspaceException (String message) {
    super (message);
  }

  /**
   * Constructs a new <code>FatalWorkspaceException</code> with a specified
   * nested exception and detail message. 
   *
   * @param   message   the detail message.
   * @param   nestedException a nested exception which caused the FatalWorkspaceException to be thrown
   */
  public FatalWorkspaceException (Exception nestedException, String message)
  {
    super(message);
    _nestedException = nestedException;
  }


 /**
   * Constructs a new <code>FatalWorkspaceException</code> with a sepcified 
   * nested exception.
   *
   * @param nestedException a nested exception which caused the FatalWorkspaceException to be thrown
   */ 
  public FatalWorkspaceException (Exception nestedException)
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
}
