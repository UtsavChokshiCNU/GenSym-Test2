/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UiClientItem.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:42 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface UiClientItem extends com.gensym.classes.Item {

  public static final Symbol UI_CLIENT_ITEM_ = com.gensym.util.symbol.G2ClassSymbols.UI_CLIENT_ITEM_;
  static final Symbol g2ClassName = UI_CLIENT_ITEM_;
  static final Symbol[] classInheritancePath = new Symbol[] {UI_CLIENT_ITEM_, ITEM_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- USES-FLOATING-LICENSE
   * @return the value of the USES-FLOATING-LICENSE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for USES-FLOATING-LICENSE is : 
   * (OR NoItem
      BooleanTruthValue)
   *
   */
  public java.lang.Boolean getUsesFloatingLicense() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-MODE-IS-VALID
   * @return the value of the UI-CLIENT-MODE-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-MODE-IS-VALID is : 
   * (OR NoItem
      BooleanTruthValue)
   *
   */
  public java.lang.Boolean getUiClientModeIsValid() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-IS-VALID
   * @return the value of the UI-CLIENT-USER-IS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-USER-IS-VALID is : 
   * (OR NoItem
      BooleanTruthValue)
   *
   */
  public java.lang.Boolean getUiClientUserIsValid() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-CONNECTION-STATUS
   * @return the value of the UI-CLIENT-CONNECTION-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-CONNECTION-STATUS is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getUiClientConnectionStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-SPECIFIC-LANGUAGE
   * @return the value of the UI-CLIENT-SPECIFIC-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-SPECIFIC-LANGUAGE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getUiClientSpecificLanguage() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM
   * @return the value of the UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getUiClientUserNameInOperatingSystem() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-TIME-OF-LAST-CONNECTION
   * @return the value of the UI-CLIENT-TIME-OF-LAST-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-TIME-OF-LAST-CONNECTION is : 
   * (OR NoItem
      (Structure))
   *
   */
  public com.gensym.util.Structure getUiClientTimeOfLastConnection() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-OPERATING-SYSTEM-TYPE
   * @return the value of the UI-CLIENT-OPERATING-SYSTEM-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-OPERATING-SYSTEM-TYPE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getUiClientOperatingSystemType() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-REMOTE-HOST-NAME
   * @return the value of the UI-CLIENT-REMOTE-HOST-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-REMOTE-HOST-NAME is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getUiClientRemoteHostName() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-NAME
   * @return the value of the UI-CLIENT-USER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-USER-NAME is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getUiClientUserName() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UI-CLIENT-USER-MODE
   * @return the value of the UI-CLIENT-USER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UI-CLIENT-USER-MODE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getUiClientUserMode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UI-CLIENT-USER-MODE
   * @param uiClientUserMode new value to conclude for UI-CLIENT-USER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUiClientUserMode(com.gensym.util.Symbol uiClientUserMode) throws G2AccessException;

}
