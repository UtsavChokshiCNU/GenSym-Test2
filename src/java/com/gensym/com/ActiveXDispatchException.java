/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXDispatchException.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

/** The class <code>ActiveXDispatchException</code> is thrown
* when a failure to dispatch a method is encountered
*/
public class ActiveXDispatchException extends ActiveXException {
  
  private long errorCode;
  private Excepinfo excepInfo = null;

  /** Construct with a message, and an error code.*/  
  public ActiveXDispatchException(String message, long errorCode) {
      super(message);
      this.errorCode = errorCode; 
  }


  /** Construct with an Excepinfo, in the case that the dispatch
  * resulted in a DISP_E_EXCEPTION error code.
  */
  public ActiveXDispatchException(Excepinfo e)
  {
    super(e.description);
    this.errorCode = 0x80020009L;
    this.excepInfo = e;
  }

  public long getErrorCode()
  {
      return errorCode;
  }

  public Excepinfo getExcepinfo()
  {
    return excepInfo;
  }

  @Override
  public String toString()
  {
    if (excepInfo != null)
      return excepInfo.toString();
    else {
      return super.toString() + ", error code = 0x" + Long.toHexString(errorCode);
    }
  }
}
