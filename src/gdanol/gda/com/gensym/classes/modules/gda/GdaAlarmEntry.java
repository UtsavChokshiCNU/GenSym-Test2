/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdaAlarmEntry.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 11:58:28 EDT 2000
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

public interface GdaAlarmEntry extends com.gensym.classes.modules.gda.GdaEntryWithUuid {

  public static final Symbol GDA_ALARM_ENTRY_ = Symbol.intern ("GDA-ALARM-ENTRY");
  static final Symbol g2ClassName = GDA_ALARM_ENTRY_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDA_ALARM_ENTRY_, GDA_ENTRY_WITH_UUID_, GQM_ENTRY_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- GDA-REQUIRE-ACKNOWLEDGEMENT
   * @return the value of the GDA-REQUIRE-ACKNOWLEDGEMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GDA-REQUIRE-ACKNOWLEDGEMENT is : 
   * BooleanTruthValue
   *
   */
  public boolean getGdaRequireAcknowledgement() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GDA-REQUIRE-ACKNOWLEDGEMENT
   * @param gdaRequireAcknowledgement new value to conclude for GDA-REQUIRE-ACKNOWLEDGEMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaRequireAcknowledgement(boolean gdaRequireAcknowledgement) throws G2AccessException;

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
   * Generated Property Getter for attribute -- GDA-ACKNOWLEDGE-TIME
   * @return the value of the GDA-ACKNOWLEDGE-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GDA-ACKNOWLEDGE-TIME is : 
   * Float
   *
   */
  public double getGdaAcknowledgeTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GDA-ACKNOWLEDGE-TIME
   * @param gdaAcknowledgeTime new value to conclude for GDA-ACKNOWLEDGE-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaAcknowledgeTime(double gdaAcknowledgeTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GDA-SEVERITY
   * @return the value of the GDA-SEVERITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GDA-SEVERITY is : 
   * Integer
   *
   */
  public int getGdaSeverity() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GDA-SEVERITY
   * @param gdaSeverity new value to conclude for GDA-SEVERITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaSeverity(int gdaSeverity) throws G2AccessException;

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
   * Generated Property Getter for attribute -- _GDA-ADVICE
   * @return the value of the _GDA-ADVICE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GDA-ADVICE is : 
   * Text
   *
   */
  public java.lang.String get_gdaAdvice() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GDA-ADVICE
   * @param _gdaAdvice new value to conclude for _GDA-ADVICE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaAdvice(java.lang.String _gdaAdvice) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GDA-HISTORY
   * @return the value of the _GDA-HISTORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GDA-HISTORY is : 
   * (Class TEXT-ARRAY)
   *
   */
  public com.gensym.classes.TextArray get_gdaHistory() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GDA-HISTORY
   * @param _gdaHistory new value to conclude for _GDA-HISTORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaHistory(com.gensym.classes.TextArray _gdaHistory) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GDA-EXPLANATION
   * @return the value of the _GDA-EXPLANATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GDA-EXPLANATION is : 
   * (Class TEXT-ARRAY)
   *
   */
  public com.gensym.classes.TextArray get_gdaExplanation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GDA-EXPLANATION
   * @param _gdaExplanation new value to conclude for _GDA-EXPLANATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaExplanation(com.gensym.classes.TextArray _gdaExplanation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GDA-ALARM-STATUS
   * @return the value of the _GDA-ALARM-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GDA-ALARM-STATUS is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol get_gdaAlarmStatus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GDA-ALARM-STATUS
   * @param _gdaAlarmStatus new value to conclude for _GDA-ALARM-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaAlarmStatus(com.gensym.util.Symbol _gdaAlarmStatus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GDA-COLLECTION-TIME
   * @return the value of the _GDA-COLLECTION-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GDA-COLLECTION-TIME is : 
   * Float
   *
   */
  public double get_gdaCollectionTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GDA-COLLECTION-TIME
   * @param _gdaCollectionTime new value to conclude for _GDA-COLLECTION-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gdaCollectionTime(double _gdaCollectionTime) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GDA-LOG-ALARM-SUMMARY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GDA-ALARM-QUEUE,arg2:CLASS OBJECT) = ()
   */
  public  void gdaLogAlarmSummary(com.gensym.classes.modules.gda.GdaAlarmQueue arg1,com.gensym.classes.Object arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQM-EXPIRE-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GDA-ALARM-QUEUE,arg2:CLASS GDL-ALARM-SOURCE,arg3:CLASS OBJECT) = ()
   */
  public  void gqmExpireEntry(com.gensym.classes.modules.gda.GdaAlarmQueue arg1,com.gensym.classes.modules.gdabasic.GdlAlarmSource arg2,com.gensym.classes.Object arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQSV-ACKNOWLEDGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gqsvAcknowledge(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQM-SAVE-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GDA-ALARM-QUEUE,arg2:TEXT,arg3:CLASS OBJECT) = ()
   */
  public  void gqmSaveEntry(com.gensym.classes.modules.gda.GdaAlarmQueue arg1,java.lang.String arg2,com.gensym.classes.Object arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQM-LOG-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GQM-QUEUE,arg2:CLASS GQM-LOGGING-MANAGER,arg3:CLASS OBJECT) = ()
   */
  public  void gqmLogEntry(com.gensym.classes.modules.gqm.GqmQueue arg1,com.gensym.classes.modules.gqm.GqmLoggingManager arg2,com.gensym.classes.Object arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GQM-ENTRY-CONSTRUCTOR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:CLASS GDA-ALARM-QUEUE,arg2:STRUCTURE,arg3:CLASS OBJECT) = ()
   */
  public  void gqmEntryConstructor(com.gensym.classes.modules.gda.GdaAlarmQueue arg1,com.gensym.util.Structure arg2,com.gensym.classes.Object arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-ENTRY::GDA-UPDATE-EXISTING-ALARM-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-ENTRY,arg1:STRUCTURE,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdaUpdateExistingAlarmEntry(com.gensym.util.Structure arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException;
  
}
