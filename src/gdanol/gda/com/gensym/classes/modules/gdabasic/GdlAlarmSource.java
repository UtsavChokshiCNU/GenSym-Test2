/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlAlarmSource.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 11:58:27 EDT 2000
 *
 */


package com.gensym.classes.modules.gdabasic;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GdlAlarmSource extends com.gensym.classes.modules.gdl.GdlObject {

  public static final Symbol GDL_ALARM_SOURCE_ = Symbol.intern ("GDL-ALARM-SOURCE");
  static final Symbol g2ClassName = GDL_ALARM_SOURCE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDL_ALARM_SOURCE_, GDL_OBJECT_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ACKNOWLEDGED
   * @return the value of the ACKNOWLEDGED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ACKNOWLEDGED is : 
   * BooleanTruthValue
   *
   */
  public boolean getAcknowledged() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ACKNOWLEDGED
   * @param acknowledged new value to conclude for ACKNOWLEDGED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAcknowledged(boolean acknowledged) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ALARM-STATUS
   * @return the value of the ALARM-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALARM-STATUS is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getAlarmStatus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALARM-STATUS
   * @param alarmStatus new value to conclude for ALARM-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAlarmStatus(com.gensym.util.Symbol alarmStatus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SEVERITY
   * @return the value of the SEVERITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SEVERITY is : 
   * Integer
   *
   */
  public int getSeverity() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SEVERITY
   * @param severity new value to conclude for SEVERITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSeverity(int severity) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TRIGGER-ON
   * @return the value of the TRIGGER-ON attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TRIGGER-ON is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getTriggerOn() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TRIGGER-ON
   * @param triggerOn new value to conclude for TRIGGER-ON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTriggerOn(com.gensym.util.Symbol triggerOn) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-MESSAGES
   * @return the value of the SHOW-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-MESSAGES is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-MESSAGES
   * @param showMessages new value to conclude for SHOW-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowMessages(boolean showMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- REQUIRE-ACKNOWLEDGEMENT
   * @return the value of the REQUIRE-ACKNOWLEDGEMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for REQUIRE-ACKNOWLEDGEMENT is : 
   * BooleanTruthValue
   *
   */
  public boolean getRequireAcknowledgement() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- REQUIRE-ACKNOWLEDGEMENT
   * @param requireAcknowledgement new value to conclude for REQUIRE-ACKNOWLEDGEMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRequireAcknowledgement(boolean requireAcknowledgement) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GENERATE-AUTOMATIC-EXPLANATION
   * @return the value of the GENERATE-AUTOMATIC-EXPLANATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GENERATE-AUTOMATIC-EXPLANATION is : 
   * BooleanTruthValue
   *
   */
  public boolean getGenerateAutomaticExplanation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GENERATE-AUTOMATIC-EXPLANATION
   * @param generateAutomaticExplanation new value to conclude for GENERATE-AUTOMATIC-EXPLANATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGenerateAutomaticExplanation(boolean generateAutomaticExplanation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GDL-DISPLAY-QUEUE
   * @return the value of the GDL-DISPLAY-QUEUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GDL-DISPLAY-QUEUE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGdlDisplayQueue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GDL-DISPLAY-QUEUE
   * @param gdlDisplayQueue new value to conclude for GDL-DISPLAY-QUEUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdlDisplayQueue(com.gensym.util.Symbol gdlDisplayQueue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ADVICE
   * @return the value of the ADVICE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ADVICE is : 
   * Text
   *
   */
  public java.lang.String getAdvice() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ADVICE
   * @param advice new value to conclude for ADVICE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAdvice(java.lang.String advice) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GDL-FILTER-CLASS
   * @return the value of the GDL-FILTER-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GDL-FILTER-CLASS is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGdlFilterClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GDL-FILTER-CLASS
   * @param gdlFilterClass new value to conclude for GDL-FILTER-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdlFilterClass(com.gensym.util.Symbol gdlFilterClass) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GDL-FILTER-TAG
   * @return the value of the GDL-FILTER-TAG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GDL-FILTER-TAG is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGdlFilterTag() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GDL-FILTER-TAG
   * @param gdlFilterTag new value to conclude for GDL-FILTER-TAG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdlFilterTag(com.gensym.util.Symbol gdlFilterTag) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GDL-ALARM-SOURCE::GDL-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-ALARM-SOURCE,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlInitialize(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-ALARM-SOURCE::GDA-ACKNOWLEDGE-ALARM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-ALARM-SOURCE,arg1:FLOAT,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdaAcknowledgeAlarm(double arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-ALARM-SOURCE::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-ALARM-SOURCE,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
}
