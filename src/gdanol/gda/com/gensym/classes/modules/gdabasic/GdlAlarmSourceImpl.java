/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlAlarmSourceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 27 07:59:21 EDT 2000
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

public class GdlAlarmSourceImpl extends com.gensym.classes.modules.gdl.GdlObjectImpl implements GdlAlarmSource {


  static final long serialVersionUID = 2L;
  private static final Symbol ACKNOWLEDGED_ = Symbol.intern ("ACKNOWLEDGED");
  private static final Symbol ALARM_STATUS_ = Symbol.intern ("ALARM-STATUS");
  private static final Symbol SEVERITY_ = Symbol.intern ("SEVERITY");
  private static final Symbol TRIGGER_ON_ = Symbol.intern ("TRIGGER-ON");
  private static final Symbol SHOW_MESSAGES_ = Symbol.intern ("SHOW-MESSAGES");
  private static final Symbol REQUIRE_ACKNOWLEDGEMENT_ = Symbol.intern ("REQUIRE-ACKNOWLEDGEMENT");
  private static final Symbol GENERATE_AUTOMATIC_EXPLANATION_ = Symbol.intern ("GENERATE-AUTOMATIC-EXPLANATION");
  private static final Symbol GDL_DISPLAY_QUEUE_ = Symbol.intern ("GDL-DISPLAY-QUEUE");
  private static final Symbol ADVICE_ = Symbol.intern ("ADVICE");
  private static final Symbol GDL_FILTER_CLASS_ = Symbol.intern ("GDL-FILTER-CLASS");
  private static final Symbol GDL_FILTER_TAG_ = Symbol.intern ("GDL-FILTER-TAG");

  /* Generated constructors */

  public GdlAlarmSourceImpl() {
    super();
  }

  public GdlAlarmSourceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ACKNOWLEDGED
   * @param acknowledged new value to conclude for ACKNOWLEDGED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAcknowledged(boolean acknowledged) throws G2AccessException {
    setAttributeValue (ACKNOWLEDGED_, new Boolean (acknowledged));
  }

  /**
   * Generated Property Getter for attribute -- ACKNOWLEDGED
   * @return the value of the ACKNOWLEDGED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getAcknowledged() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ACKNOWLEDGED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- ALARM-STATUS
   * @param alarmStatus new value to conclude for ALARM-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAlarmStatus(com.gensym.util.Symbol alarmStatus) throws G2AccessException {
    setAttributeValue (ALARM_STATUS_, alarmStatus);
  }

  /**
   * Generated Property Getter for attribute -- ALARM-STATUS
   * @return the value of the ALARM-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getAlarmStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ALARM_STATUS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SEVERITY
   * @param severity new value to conclude for SEVERITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSeverity(int severity) throws G2AccessException {
    setAttributeValue (SEVERITY_, new Integer (severity));
  }

  /**
   * Generated Property Getter for attribute -- SEVERITY
   * @return the value of the SEVERITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getSeverity() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SEVERITY_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- TRIGGER-ON
   * @param triggerOn new value to conclude for TRIGGER-ON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTriggerOn(com.gensym.util.Symbol triggerOn) throws G2AccessException {
    setAttributeValue (TRIGGER_ON_, triggerOn);
  }

  /**
   * Generated Property Getter for attribute -- TRIGGER-ON
   * @return the value of the TRIGGER-ON attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getTriggerOn() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (TRIGGER_ON_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SHOW-MESSAGES
   * @param showMessages new value to conclude for SHOW-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowMessages(boolean showMessages) throws G2AccessException {
    setAttributeValue (SHOW_MESSAGES_, new Boolean (showMessages));
  }

  /**
   * Generated Property Getter for attribute -- SHOW-MESSAGES
   * @return the value of the SHOW-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getShowMessages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SHOW_MESSAGES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- REQUIRE-ACKNOWLEDGEMENT
   * @param requireAcknowledgement new value to conclude for REQUIRE-ACKNOWLEDGEMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRequireAcknowledgement(boolean requireAcknowledgement) throws G2AccessException {
    setAttributeValue (REQUIRE_ACKNOWLEDGEMENT_, new Boolean (requireAcknowledgement));
  }

  /**
   * Generated Property Getter for attribute -- REQUIRE-ACKNOWLEDGEMENT
   * @return the value of the REQUIRE-ACKNOWLEDGEMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getRequireAcknowledgement() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (REQUIRE_ACKNOWLEDGEMENT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GENERATE-AUTOMATIC-EXPLANATION
   * @param generateAutomaticExplanation new value to conclude for GENERATE-AUTOMATIC-EXPLANATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGenerateAutomaticExplanation(boolean generateAutomaticExplanation) throws G2AccessException {
    setAttributeValue (GENERATE_AUTOMATIC_EXPLANATION_, new Boolean (generateAutomaticExplanation));
  }

  /**
   * Generated Property Getter for attribute -- GENERATE-AUTOMATIC-EXPLANATION
   * @return the value of the GENERATE-AUTOMATIC-EXPLANATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGenerateAutomaticExplanation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GENERATE_AUTOMATIC_EXPLANATION_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GDL-DISPLAY-QUEUE
   * @param gdlDisplayQueue new value to conclude for GDL-DISPLAY-QUEUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdlDisplayQueue(com.gensym.util.Symbol gdlDisplayQueue) throws G2AccessException {
    setAttributeValue (GDL_DISPLAY_QUEUE_, gdlDisplayQueue);
  }

  /**
   * Generated Property Getter for attribute -- GDL-DISPLAY-QUEUE
   * @return the value of the GDL-DISPLAY-QUEUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGdlDisplayQueue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDL_DISPLAY_QUEUE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ADVICE
   * @param advice new value to conclude for ADVICE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAdvice(java.lang.String advice) throws G2AccessException {
    setAttributeValue (ADVICE_, advice);
  }

  /**
   * Generated Property Getter for attribute -- ADVICE
   * @return the value of the ADVICE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getAdvice() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ADVICE_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GDL-FILTER-CLASS
   * @param gdlFilterClass new value to conclude for GDL-FILTER-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdlFilterClass(com.gensym.util.Symbol gdlFilterClass) throws G2AccessException {
    setAttributeValue (GDL_FILTER_CLASS_, gdlFilterClass);
  }

  /**
   * Generated Property Getter for attribute -- GDL-FILTER-CLASS
   * @return the value of the GDL-FILTER-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGdlFilterClass() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDL_FILTER_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GDL-FILTER-TAG
   * @param gdlFilterTag new value to conclude for GDL-FILTER-TAG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdlFilterTag(com.gensym.util.Symbol gdlFilterTag) throws G2AccessException {
    setAttributeValue (GDL_FILTER_TAG_, gdlFilterTag);
  }

  /**
   * Generated Property Getter for attribute -- GDL-FILTER-TAG
   * @return the value of the GDL-FILTER-TAG attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGdlFilterTag() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDL_FILTER_TAG_);
    return (com.gensym.util.Symbol)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GDL_INITIALIZE_ = Symbol.intern ("GDL-INITIALIZE");
  private static final Symbol MethodName_GDA_ACKNOWLEDGE_ALARM_ = Symbol.intern ("GDA-ACKNOWLEDGE-ALARM");
  private static final Symbol MethodName_GDL_RESET_ = Symbol.intern ("GDL-RESET");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GDL-ALARM-SOURCE::GDL-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-ALARM-SOURCE,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlInitialize(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_INITIALIZE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-ALARM-SOURCE::GDA-ACKNOWLEDGE-ALARM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-ALARM-SOURCE,arg1:FLOAT,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdaAcknowledgeAlarm(double arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,new Double (arg1),arg2};
      result = (java.lang.Object)callRPC(MethodName_GDA_ACKNOWLEDGE_ALARM_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-ALARM-SOURCE::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-ALARM-SOURCE,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_RESET_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
