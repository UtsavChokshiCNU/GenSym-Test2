/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UiClientSession.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:46 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface UiClientSession extends com.gensym.classes.Object, com.gensym.classes.UiClientItem {

  public static final Symbol UI_CLIENT_SESSION_ = com.gensym.util.symbol.G2ClassSymbols.UI_CLIENT_SESSION_;
  static final Symbol g2ClassName = UI_CLIENT_SESSION_;
  static final Symbol[] classInheritancePath = new Symbol[] {UI_CLIENT_SESSION_, OBJECT_, UI_CLIENT_ITEM_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-USER-MODE
   * @return the value of the UI-CLIENT-SESSION-USER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SESSION-USER-MODE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUiClientSessionUserMode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UI-CLIENT-SESSION-USER-MODE
   * @param uiClientSessionUserMode new value to conclude for UI-CLIENT-SESSION-USER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUiClientSessionUserMode(com.gensym.util.Symbol uiClientSessionUserMode) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-USER-NAME
   * @return the value of the UI-CLIENT-SESSION-USER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SESSION-USER-NAME is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUiClientSessionUserName() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-USER-NAME-IN-OPERATING-SYSTEM
   * @return the value of the UI-CLIENT-SESSION-USER-NAME-IN-OPERATING-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SESSION-USER-NAME-IN-OPERATING-SYSTEM is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getUiClientSessionUserNameInOperatingSystem() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-TIME-OF-LAST-CONNECTION
   * @return the value of the UI-CLIENT-SESSION-TIME-OF-LAST-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SESSION-TIME-OF-LAST-CONNECTION is : 
   * (OR NoItem
      (Structure 
        SECOND Quantity
        MINUTE Quantity
        HOUR Quantity
        DATE Quantity
        MONTH Quantity
        YEAR Quantity))
   *
   */
  public com.gensym.util.Structure getUiClientSessionTimeOfLastConnection() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-NETWORK-HOST-NAME
   * @return the value of the UI-CLIENT-SESSION-NETWORK-HOST-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SESSION-NETWORK-HOST-NAME is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getUiClientSessionNetworkHostName() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-OPERATING-SYSTEM-TYPE
   * @return the value of the UI-CLIENT-SESSION-OPERATING-SYSTEM-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SESSION-OPERATING-SYSTEM-TYPE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUiClientSessionOperatingSystemType() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-USER-IS-VALID
   * @return the value of the UI-CLIENT-SESSION-USER-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SESSION-USER-IS-VALID is : 
   * BooleanTruthValue
   *
   */
  public boolean getUiClientSessionUserIsValid() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SESSION-MODE-IS-VALID
   * @return the value of the UI-CLIENT-SESSION-MODE-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SESSION-MODE-IS-VALID is : 
   * BooleanTruthValue
   *
   */
  public boolean getUiClientSessionModeIsValid() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-INTERFACE
   * @return the value of the UI-CLIENT-INTERFACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-INTERFACE is : 
   * (OR Value
      NoItem)
   *
   */
  public java.lang.Object getUiClientInterface() throws G2AccessException;

}
