/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UiClientSessionImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:49 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class UiClientSessionImpl extends com.gensym.classes.ObjectImpl implements UiClientSession {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public UiClientSessionImpl() {
    super();
  }

  public UiClientSessionImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UiClientSessionImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UI-CLIENT-SESSION-USER-MODE
   * @param uiClientSessionUserMode new value to conclude for UI-CLIENT-SESSION-USER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUiClientSessionUserMode(com.gensym.util.Symbol uiClientSessionUserMode) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_USER_MODE_, uiClientSessionUserMode);
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-USER-MODE
   * @return the value of the UI-CLIENT-SESSION-USER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientSessionUserMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_USER_MODE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-USER-NAME
   * @return the value of the UI-CLIENT-SESSION-USER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientSessionUserName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_USER_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-USER-NAME-IN-OPERATING-SYSTEM
   * @return the value of the UI-CLIENT-SESSION-USER-NAME-IN-OPERATING-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUiClientSessionUserNameInOperatingSystem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_USER_NAME_IN_OPERATING_SYSTEM_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-TIME-OF-LAST-CONNECTION
   * @return the value of the UI-CLIENT-SESSION-TIME-OF-LAST-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getUiClientSessionTimeOfLastConnection() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_TIME_OF_LAST_CONNECTION_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-NETWORK-HOST-NAME
   * @return the value of the UI-CLIENT-SESSION-NETWORK-HOST-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getUiClientSessionNetworkHostName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_NETWORK_HOST_NAME_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-OPERATING-SYSTEM-TYPE
   * @return the value of the UI-CLIENT-SESSION-OPERATING-SYSTEM-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientSessionOperatingSystemType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_OPERATING_SYSTEM_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-USER-IS-VALID
   * @return the value of the UI-CLIENT-SESSION-USER-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getUiClientSessionUserIsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_USER_IS_VALID_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-MODE-IS-VALID
   * @return the value of the UI-CLIENT-SESSION-MODE-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getUiClientSessionModeIsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SESSION_MODE_IS_VALID_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-INTERFACE
   * @return the value of the UI-CLIENT-INTERFACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUiClientInterface() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_INTERFACE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- USES-FLOATING-LICENSE
   * @return the value of the USES-FLOATING-LICENSE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Boolean getUsesFloatingLicense() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.USES_FLOATING_LICENSE_);
    return (java.lang.Boolean)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-MODE-IS-VALID
   * @return the value of the UI-CLIENT-MODE-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Boolean getUiClientModeIsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_MODE_IS_VALID_);
    return (java.lang.Boolean)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-IS-VALID
   * @return the value of the UI-CLIENT-USER-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Boolean getUiClientUserIsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_IS_VALID_);
    return (java.lang.Boolean)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-CONNECTION-STATUS
   * @return the value of the UI-CLIENT-CONNECTION-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientConnectionStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_CONNECTION_STATUS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SPECIFIC-LANGUAGE
   * @return the value of the UI-CLIENT-SPECIFIC-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientSpecificLanguage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_SPECIFIC_LANGUAGE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM
   * @return the value of the UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getUiClientUserNameInOperatingSystem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_NAME_IN_OPERATING_SYSTEM_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-TIME-OF-LAST-CONNECTION
   * @return the value of the UI-CLIENT-TIME-OF-LAST-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getUiClientTimeOfLastConnection() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_TIME_OF_LAST_CONNECTION_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-OPERATING-SYSTEM-TYPE
   * @return the value of the UI-CLIENT-OPERATING-SYSTEM-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientOperatingSystemType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_OPERATING_SYSTEM_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-REMOTE-HOST-NAME
   * @return the value of the UI-CLIENT-REMOTE-HOST-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getUiClientRemoteHostName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_REMOTE_HOST_NAME_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-NAME
   * @return the value of the UI-CLIENT-USER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientUserName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UI-CLIENT-USER-MODE
   * @param uiClientUserMode new value to conclude for UI-CLIENT-USER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUiClientUserMode(com.gensym.util.Symbol uiClientUserMode) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_MODE_, uiClientUserMode);
  }

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-MODE
   * @return the value of the UI-CLIENT-USER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUiClientUserMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UI_CLIENT_USER_MODE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
