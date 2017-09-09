package com.gensym.jgi;


import com.gensym.util.Symbol;


/**
 * This class is used to receive the results of an RPC call.
 */
class G2RemoteRPCThreadData {

  /**
   * These are magic markers indicating that a call failed because we sent
   * in an item that has been deleted.
   */
  private static final String
    ITEM_DELETION_MARKER_0 = "Cannot call",
    ITEM_DELETION_MARKER_1 = "an item sent by reference has been deleted";

  Object retnvalue;
  volatile boolean threadHasIncompleteConversionData = false;

  int timeout = 0;
  public boolean hasTimedOut = false;
  Symbol errorSymbol;
  String errorMessage;
  volatile boolean errorHasOccured = false;

  /**
   * Constructor
   * 
   * @param timeout The number millisecs to wait for RPC return value
   */
  G2RemoteRPCThreadData(int timeout)
  {
    // Default value for retnvalue is "this", so we can defect if
    // no value has been set...a timeout
    retnvalue = this;

  }


  Object getData() throws G2AccessException
  {
    // if retnvalue is still pointing to our instance, then a timeout must
    // of occured before G2 returned a value
    // raise a time exception if we have timedout
	if (retnvalue == this)
      {
    	retnvalue = null;
    	throw new TimeoutException();
      }

    if (errorHasOccured)
      {
	String message = (errorSymbol == null ? "" : errorSymbol.toString() + ": ") + 
	  (errorMessage == null ? "RPC error" : errorMessage );

	if (errorMessage.indexOf (ITEM_DELETION_MARKER_0) >= 0 &&
	    errorMessage.indexOf (ITEM_DELETION_MARKER_1) >= 0)
	  throw new G2ItemDeletedException (message);
	else
	  throw new G2AccessException (message);
      }
    else
      {
	// Everything was OK, so return the value received
	return retnvalue;
      }
  }

  @Override
  public String toString () 
  {
    if (retnvalue == this) 
    	return super.toString();
    return (retnvalue == null) ? "null" : retnvalue.toString ();
  }

    public boolean isRPCdone() {
    	return retnvalue != this;
    }

  /**
   * Record that an errior has occured
   */
  synchronized void signalReturnError(Symbol error_symbol, String error_message) 
  {
    errorSymbol = error_symbol;
    errorMessage = error_message;
    errorHasOccured = true;
    retnvalue = null;

    this.notifyAll();
  }

    /** Record that a value was returned from the remote procedure */
  synchronized void signalReturnValue (Object return_value, boolean incomplete_conversion) {
    retnvalue = return_value;
    threadHasIncompleteConversionData = incomplete_conversion;
    
    this.notifyAll();
  }

}

