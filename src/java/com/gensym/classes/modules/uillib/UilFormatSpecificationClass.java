/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilFormatSpecificationClass.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:37 EDT 2007
 *
 */


package com.gensym.classes.modules.uillib;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilFormatSpecificationClass extends com.gensym.classes.modules.uilroot.UilObject {

  public static final Symbol UIL_FORMAT_SPECIFICATION_CLASS_ = Symbol.intern ("UIL-FORMAT-SPECIFICATION-CLASS");
  static final Symbol g2ClassName = UIL_FORMAT_SPECIFICATION_CLASS_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_FORMAT_SPECIFICATION_CLASS_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-FORMAT-TYPE
   * @return the value of the UIL-FORMAT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-FORMAT-TYPE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilFormatType() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-FORMAT-TYPE
   * @param uilFormatType new value to conclude for UIL-FORMAT-TYPE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilFormatType(java.lang.Object uilFormatType) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-FORMAT-TEMPLATE
   * @return the value of the UIL-FORMAT-TEMPLATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-FORMAT-TEMPLATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilFormatTemplate() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-FORMAT-TEMPLATE
   * @param uilFormatTemplate new value to conclude for UIL-FORMAT-TEMPLATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilFormatTemplate(java.lang.Object uilFormatTemplate) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-QUOTE-MARK-HANDLING
   * @return the value of the UIL-QUOTE-MARK-HANDLING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-QUOTE-MARK-HANDLING is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilQuoteMarkHandling() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-QUOTE-MARK-HANDLING
   * @param uilQuoteMarkHandling new value to conclude for UIL-QUOTE-MARK-HANDLING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilQuoteMarkHandling(java.lang.Object uilQuoteMarkHandling) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TEXT-CASE-HANDLING
   * @return the value of the UIL-TEXT-CASE-HANDLING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TEXT-CASE-HANDLING is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTextCaseHandling() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TEXT-CASE-HANDLING
   * @param uilTextCaseHandling new value to conclude for UIL-TEXT-CASE-HANDLING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTextCaseHandling(java.lang.Object uilTextCaseHandling) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DEFAULT-VALUE-SPECIFICATION
   * @return the value of the UIL-DEFAULT-VALUE-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DEFAULT-VALUE-SPECIFICATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDefaultValueSpecification() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DEFAULT-VALUE-SPECIFICATION
   * @param uilDefaultValueSpecification new value to conclude for UIL-DEFAULT-VALUE-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDefaultValueSpecification(java.lang.Object uilDefaultValueSpecification) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATION-FAILURE-METHOD
   * @return the value of the UIL-VALIDATION-FAILURE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-VALIDATION-FAILURE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilValidationFailureMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATION-FAILURE-METHOD
   * @param uilValidationFailureMethod new value to conclude for UIL-VALIDATION-FAILURE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilValidationFailureMethod(java.lang.Object uilValidationFailureMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATION-TIME-FIELD-DELIMITER
   * @return the value of the UIL-VALIDATION-TIME-FIELD-DELIMITER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-VALIDATION-TIME-FIELD-DELIMITER is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilValidationTimeFieldDelimiter() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATION-TIME-FIELD-DELIMITER
   * @param uilValidationTimeFieldDelimiter new value to conclude for UIL-VALIDATION-TIME-FIELD-DELIMITER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilValidationTimeFieldDelimiter(java.lang.Object uilValidationTimeFieldDelimiter) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATION-DATE-FIELD-DELIMITER
   * @return the value of the UIL-VALIDATION-DATE-FIELD-DELIMITER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-VALIDATION-DATE-FIELD-DELIMITER is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilValidationDateFieldDelimiter() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATION-DATE-FIELD-DELIMITER
   * @param uilValidationDateFieldDelimiter new value to conclude for UIL-VALIDATION-DATE-FIELD-DELIMITER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilValidationDateFieldDelimiter(java.lang.Object uilValidationDateFieldDelimiter) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MINIMUM-VALUE
   * @return the value of the UIL-MINIMUM-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MINIMUM-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMinimumValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MINIMUM-VALUE
   * @param uilMinimumValue new value to conclude for UIL-MINIMUM-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMinimumValue(java.lang.Object uilMinimumValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MAXIMUM-VALUE
   * @return the value of the UIL-MAXIMUM-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MAXIMUM-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMaximumValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MAXIMUM-VALUE
   * @param uilMaximumValue new value to conclude for UIL-MAXIMUM-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMaximumValue(java.lang.Object uilMaximumValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MINIMUM-LENGTH
   * @return the value of the UIL-MINIMUM-LENGTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MINIMUM-LENGTH is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMinimumLength() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MINIMUM-LENGTH
   * @param uilMinimumLength new value to conclude for UIL-MINIMUM-LENGTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMinimumLength(java.lang.Object uilMinimumLength) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MAXIMUM-LENGTH
   * @return the value of the UIL-MAXIMUM-LENGTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MAXIMUM-LENGTH is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMaximumLength() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MAXIMUM-LENGTH
   * @param uilMaximumLength new value to conclude for UIL-MAXIMUM-LENGTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMaximumLength(java.lang.Object uilMaximumLength) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-NONE-AS-VALID
   * @return the value of the UIL-ALLOW-NONE-AS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ALLOW-NONE-AS-VALID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAllowNoneAsValid() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-NONE-AS-VALID
   * @param uilAllowNoneAsValid new value to conclude for UIL-ALLOW-NONE-AS-VALID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAllowNoneAsValid(java.lang.Object uilAllowNoneAsValid) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-24-HOUR-CLOCK
   * @return the value of the UIL-24-HOUR-CLOCK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-24-HOUR-CLOCK is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUil24HourClock() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-24-HOUR-CLOCK
   * @param uil24HourClock new value to conclude for UIL-24-HOUR-CLOCK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUil24HourClock(java.lang.Object uil24HourClock) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-REVERT-VALUE-ON-ERROR
   * @return the value of the UIL-REVERT-VALUE-ON-ERROR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-REVERT-VALUE-ON-ERROR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilRevertValueOnError() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-REVERT-VALUE-ON-ERROR
   * @param uilRevertValueOnError new value to conclude for UIL-REVERT-VALUE-ON-ERROR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilRevertValueOnError(java.lang.Object uilRevertValueOnError) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-FLOAT-FORMAT-OUTPUT-FORMAT
   * @return the value of the UIL-FLOAT-FORMAT-OUTPUT-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-FLOAT-FORMAT-OUTPUT-FORMAT is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUilFloatFormatOutputFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-FLOAT-FORMAT-OUTPUT-FORMAT
   * @param uilFloatFormatOutputFormat new value to conclude for UIL-FLOAT-FORMAT-OUTPUT-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilFloatFormatOutputFormat(com.gensym.util.Symbol uilFloatFormatOutputFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-FLOAT-FORMAT-OUTPUT-PRECISION
   * @return the value of the UIL-FLOAT-FORMAT-OUTPUT-PRECISION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-FLOAT-FORMAT-OUTPUT-PRECISION is : 
   * Integer
   *
   */
  public int getUilFloatFormatOutputPrecision() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-FLOAT-FORMAT-OUTPUT-PRECISION
   * @param uilFloatFormatOutputPrecision new value to conclude for UIL-FLOAT-FORMAT-OUTPUT-PRECISION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilFloatFormatOutputPrecision(int uilFloatFormatOutputPrecision) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS
   * @return the value of the UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS is : 
   * BooleanTruthValue
   *
   */
  public boolean getUilFloatFormatRemoveTrailingZeros() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS
   * @param uilFloatFormatRemoveTrailingZeros new value to conclude for UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilFloatFormatRemoveTrailingZeros(boolean uilFloatFormatRemoveTrailingZeros) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES
   * @return the value of the UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilArrayOfLegalSymbolicValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES
   * @param uilArrayOfLegalSymbolicValues new value to conclude for UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilArrayOfLegalSymbolicValues(java.lang.Object uilArrayOfLegalSymbolicValues) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ARRAY-OF-LEGAL-TEXT-VALUES
   * @return the value of the UIL-ARRAY-OF-LEGAL-TEXT-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ARRAY-OF-LEGAL-TEXT-VALUES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilArrayOfLegalTextValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ARRAY-OF-LEGAL-TEXT-VALUES
   * @param uilArrayOfLegalTextValues new value to conclude for UIL-ARRAY-OF-LEGAL-TEXT-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilArrayOfLegalTextValues(java.lang.Object uilArrayOfLegalTextValues) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ARRAY-OF-LEGAL-INTEGER-VALUES
   * @return the value of the UIL-ARRAY-OF-LEGAL-INTEGER-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ARRAY-OF-LEGAL-INTEGER-VALUES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilArrayOfLegalIntegerValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ARRAY-OF-LEGAL-INTEGER-VALUES
   * @param uilArrayOfLegalIntegerValues new value to conclude for UIL-ARRAY-OF-LEGAL-INTEGER-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilArrayOfLegalIntegerValues(java.lang.Object uilArrayOfLegalIntegerValues) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES
   * @return the value of the UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilArrayOfLegalQuantityValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES
   * @param uilArrayOfLegalQuantityValues new value to conclude for UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilArrayOfLegalQuantityValues(java.lang.Object uilArrayOfLegalQuantityValues) throws G2AccessException;

}
