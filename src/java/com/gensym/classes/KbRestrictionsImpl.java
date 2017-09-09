/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      KbRestrictionsImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:00:17 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class KbRestrictionsImpl extends com.gensym.classes.SystemTableImpl implements KbRestrictions {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public KbRestrictionsImpl() {
    super();
  }

  public KbRestrictionsImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public KbRestrictionsImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- MAIN-MENU-USER-RESTRICTIONS
   * @param mainMenuUserRestrictions new value to conclude for MAIN-MENU-USER-RESTRICTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMainMenuUserRestrictions(com.gensym.util.Sequence mainMenuUserRestrictions) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAIN_MENU_USER_RESTRICTIONS_, mainMenuUserRestrictions);
  }

  /**
   * Generated Property Getter for attribute -- MAIN-MENU-USER-RESTRICTIONS
   * @return the value of the MAIN-MENU-USER-RESTRICTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getMainMenuUserRestrictions() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAIN_MENU_USER_RESTRICTIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- KEYBOARD-COMMAND-RESTRICTIONS
   * @param keyboardCommandRestrictions new value to conclude for KEYBOARD-COMMAND-RESTRICTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setKeyboardCommandRestrictions(com.gensym.util.Sequence keyboardCommandRestrictions) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.KEYBOARD_COMMAND_RESTRICTIONS_, keyboardCommandRestrictions);
  }

  /**
   * Generated Property Getter for attribute -- KEYBOARD-COMMAND-RESTRICTIONS
   * @return the value of the KEYBOARD-COMMAND-RESTRICTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getKeyboardCommandRestrictions() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.KEYBOARD_COMMAND_RESTRICTIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INITIAL-G2-USER-MODE-FOR-THIS-KB
   * @return the value of the INITIAL-G2-USER-MODE-FOR-THIS-KB attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getInitialG2UserModeForThisKb() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INITIAL_G2_USER_MODE_FOR_THIS_KB_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- AUTHORIZED-OPTIONAL-MODULES
   * @return the value of the AUTHORIZED-OPTIONAL-MODULES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getAuthorizedOptionalModules() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.AUTHORIZED_OPTIONAL_MODULES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SIMULATED-OPTIONAL-MODULES
   * @param simulatedOptionalModules new value to conclude for SIMULATED-OPTIONAL-MODULES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSimulatedOptionalModules(java.lang.Object simulatedOptionalModules) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SIMULATED_OPTIONAL_MODULES_, simulatedOptionalModules);
  }

  /**
   * Generated Property Getter for attribute -- SIMULATED-OPTIONAL-MODULES
   * @return the value of the SIMULATED-OPTIONAL-MODULES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSimulatedOptionalModules() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SIMULATED_OPTIONAL_MODULES_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
