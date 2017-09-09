/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdaAlarmEntryImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jul 17 15:20:27 EDT 2000
 *
 */


package com.gensym.classes.modules.gda;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GdaAlarmEntryImpl extends com.gensym.classes.modules.gda.GdaEntryWithUuidImpl implements GdaAlarmEntry {


  static final long serialVersionUID = 2L;
  private static final Symbol GDA_REQUIRE_ACKNOWLEDGEMENT_ = Symbol.intern ("GDA-REQUIRE-ACKNOWLEDGEMENT");
  private static final Symbol ACKNOWLEDGED_ = Symbol.intern ("ACKNOWLEDGED");
  private static final Symbol GDA_ACKNOWLEDGE_TIME_ = Symbol.intern ("GDA-ACKNOWLEDGE-TIME");
  private static final Symbol GDA_SEVERITY_ = Symbol.intern ("GDA-SEVERITY");
  private static final Symbol GDL_FILTER_TAG_ = Symbol.intern ("GDL-FILTER-TAG");
  private static final Symbol _GDA_ADVICE_ = Symbol.intern ("_GDA-ADVICE");
  private static final Symbol _GDA_HISTORY_ = Symbol.intern ("_GDA-HISTORY");
  private static final Symbol _GDA_EXPLANATION_ = Symbol.intern ("_GDA-EXPLANATION");
  private static final Symbol _GDA_ALARM_STATUS_ = Symbol.intern ("_GDA-ALARM-STATUS");
  private static final Symbol _GDA_COLLECTION_TIME_ = Symbol.intern ("_GDA-COLLECTION-TIME");

  /* Generated constructors */

  public GdaAlarmEntryImpl() {
    super();
  }

  public GdaAlarmEntryImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GDA-REQUIRE-ACKNOWLEDGEMENT
   * @param gdaRequireAcknowledgement new value to conclude for GDA-REQUIRE-ACKNOWLEDGEMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaRequireAcknowledgement(boolean gdaRequireAcknowledgement) throws G2AccessException {
    setAttributeValue (GDA_REQUIRE_ACKNOWLEDGEMENT_, new Boolean (gdaRequireAcknowledgement));
  }

  /**
   * Generated Property Getter for attribute -- GDA-REQUIRE-ACKNOWLEDGEMENT
   * @return the value of the GDA-REQUIRE-ACKNOWLEDGEMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGdaRequireAcknowledgement() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDA_REQUIRE_ACKNOWLEDGEMENT_);
    return ((Boolean)retnValue).booleanValue ();
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
   * Generated Property Setter for attribute -- GDA-ACKNOWLEDGE-TIME
   * @param gdaAcknowledgeTime new value to conclude for GDA-ACKNOWLEDGE-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaAcknowledgeTime(double gdaAcknowledgeTime) throws G2AccessException {
    setAttributeValue (GDA_ACKNOWLEDGE_TIME_, new Double (gdaAcknowledgeTime));
  }

  /**
   * Generated Property Getter for attribute -- GDA-ACKNOWLEDGE-TIME
   * @return the value of the GDA-ACKNOWLEDGE-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public double getGdaAcknowledgeTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDA_ACKNOWLEDGE_TIME_);
    return ((Double)retnValue).doubleValue ();
  }

  /**
   * Generated Property Setter for attribute -- GDA-SEVERITY
   * @param gdaSeverity new value to conclude for GDA-SEVERITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaSeverity(int gdaSeverity) throws G2AccessException {
    setAttributeValue (GDA_SEVERITY_, new Integer (gdaSeverity));
  }

  /**
   * Generated Property Getter for attribute -- GDA-SEVERITY
   * @return the value of the GDA-SEVERITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getGdaSeverity() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDA_SEVERITY_);
    return ((Integer)retnValue).intValue ();
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

  /**
   * Generated Property Setter for attribute -- _GDA-ADVICE
   * @param _gdaAdvice new value to conclude for _GDA-ADVICE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaAdvice(java.lang.String _gdaAdvice) throws G2AccessException {
    setAttributeValue (_GDA_ADVICE_, _gdaAdvice);
  }

  /**
   * Generated Property Getter for attribute -- _GDA-ADVICE
   * @return the value of the _GDA-ADVICE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String get_gdaAdvice() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GDA_ADVICE_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _GDA-HISTORY
   * @param _gdaHistory new value to conclude for _GDA-HISTORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaHistory(com.gensym.classes.TextArray _gdaHistory) throws G2AccessException {
    setAttributeValue (_GDA_HISTORY_, _gdaHistory);
  }

  /**
   * Generated Property Getter for attribute -- _GDA-HISTORY
   * @return the value of the _GDA-HISTORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.TextArray get_gdaHistory() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GDA_HISTORY_);
    return (com.gensym.classes.TextArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _GDA-EXPLANATION
   * @param _gdaExplanation new value to conclude for _GDA-EXPLANATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaExplanation(com.gensym.classes.TextArray _gdaExplanation) throws G2AccessException {
    setAttributeValue (_GDA_EXPLANATION_, _gdaExplanation);
  }

  /**
   * Generated Property Getter for attribute -- _GDA-EXPLANATION
   * @return the value of the _GDA-EXPLANATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.TextArray get_gdaExplanation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GDA_EXPLANATION_);
    return (com.gensym.classes.TextArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _GDA-ALARM-STATUS
   * @param _gdaAlarmStatus new value to conclude for _GDA-ALARM-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaAlarmStatus(com.gensym.util.Symbol _gdaAlarmStatus) throws G2AccessException {
    setAttributeValue (_GDA_ALARM_STATUS_, _gdaAlarmStatus);
  }

  /**
   * Generated Property Getter for attribute -- _GDA-ALARM-STATUS
   * @return the value of the _GDA-ALARM-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol get_gdaAlarmStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GDA_ALARM_STATUS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _GDA-COLLECTION-TIME
   * @param _gdaCollectionTime new value to conclude for _GDA-COLLECTION-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaCollectionTime(double _gdaCollectionTime) throws G2AccessException {
    setAttributeValue (_GDA_COLLECTION_TIME_, new Double (_gdaCollectionTime));
  }

  /**
   * Generated Property Getter for attribute -- _GDA-COLLECTION-TIME
   * @return the value of the _GDA-COLLECTION-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public double get_gdaCollectionTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GDA_COLLECTION_TIME_);
    return ((Double)retnValue).doubleValue ();
  }

  // Method Name Constants
  private static final Symbol MethodName_GDA_LOG_ALARM_SUMMARY_ = Symbol.intern ("GDA-LOG-ALARM-SUMMARY");
  private static final Symbol MethodName_GQM_EXPIRE_ENTRY_ = Symbol.intern ("GQM-EXPIRE-ENTRY");
  private static final Symbol MethodName_GQSV_ACKNOWLEDGE_ = Symbol.intern ("GQSV-ACKNOWLEDGE");
  private static final Symbol MethodName_GQM_SAVE_ENTRY_ = Symbol.intern ("GQM-SAVE-ENTRY");
  private static final Symbol MethodName_GQM_LOG_ENTRY_ = Symbol.intern ("GQM-LOG-ENTRY");
  private static final Symbol MethodName_GQM_ENTRY_CONSTRUCTOR_ = Symbol.intern ("GQM-ENTRY-CONSTRUCTOR");
  private static final Symbol MethodName_GDA_UPDATE_EXISTING_ALARM_ENTRY_ = Symbol.intern ("GDA-UPDATE-EXISTING-ALARM-ENTRY");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GDA-LOG-ALARM-SUMMARY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GDA-ALARM-QUEUE,arg2:CLASS OBJECT) = ()
   */
  public  void gdaLogAlarmSummary(com.gensym.classes.modules.gda.GdaAlarmQueue arg1,com.gensym.classes.Object arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_GDA_LOG_ALARM_SUMMARY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQM-EXPIRE-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GDA-ALARM-QUEUE,arg2:CLASS GDL-ALARM-SOURCE,arg3:CLASS OBJECT) = ()
   */
  public  void gqmExpireEntry(com.gensym.classes.modules.gda.GdaAlarmQueue arg1,com.gensym.classes.modules.gdabasic.GdlAlarmSource arg2,com.gensym.classes.Object arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQM_EXPIRE_ENTRY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQSV-ACKNOWLEDGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gqsvAcknowledge(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GQSV_ACKNOWLEDGE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQM-SAVE-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GDA-ALARM-QUEUE,arg2:TEXT,arg3:CLASS OBJECT) = ()
   */
  public  void gqmSaveEntry(com.gensym.classes.modules.gda.GdaAlarmQueue arg1,java.lang.String arg2,com.gensym.classes.Object arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQM_SAVE_ENTRY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQM-LOG-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GQM-QUEUE,arg2:CLASS GQM-LOGGING-MANAGER,arg3:CLASS OBJECT) = ()
   */
  public  void gqmLogEntry(com.gensym.classes.modules.gqm.GqmQueue arg1,com.gensym.classes.modules.gqm.GqmLoggingManager arg2,com.gensym.classes.Object arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQM_LOG_ENTRY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQM-ENTRY-CONSTRUCTOR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GDA-ALARM-QUEUE,arg2:STRUCTURE,arg3:CLASS OBJECT) = ()
   */
  public  void gqmEntryConstructor(com.gensym.classes.modules.gda.GdaAlarmQueue arg1,com.gensym.util.Structure arg2,com.gensym.classes.Object arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQM_ENTRY_CONSTRUCTOR_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GDA-UPDATE-EXISTING-ALARM-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:STRUCTURE,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdaUpdateExistingAlarmEntry(com.gensym.util.Structure arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_GDA_UPDATE_EXISTING_ALARM_ENTRY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
