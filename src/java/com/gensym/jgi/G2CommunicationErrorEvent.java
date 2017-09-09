package com.gensym.jgi;

/**
 * An event raised when an asynchronous G2 communication error has occured.
 *
 * @version     1.00 18-June-1997
 * @author      M.D.Gribble
 */

public class G2CommunicationErrorEvent
       extends G2ConnectionEvent
{

  protected int errorCode;
  protected String errorMessage;

  public G2CommunicationErrorEvent(Object source, int id, int error_code, String error_message)
  {
    super(source, id, error_message, false);
    errorCode = error_code;
  } 
	 
  public int getErrorCode()
  {
    return errorCode;
  }


  @Override
  public String toString()
  {
    return super.toString() + " Error code: " + errorCode + ", Error Message: error_message: " + getMessage();
  }

}
