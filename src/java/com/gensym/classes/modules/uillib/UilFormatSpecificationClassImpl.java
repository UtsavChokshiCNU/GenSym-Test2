/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilFormatSpecificationClassImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:38 EDT 2007
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

public class UilFormatSpecificationClassImpl extends com.gensym.classes.modules.uilroot.UilObjectImpl implements UilFormatSpecificationClass {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_FORMAT_TYPE_ = Symbol.intern ("UIL-FORMAT-TYPE");
  private static final Symbol UIL_FORMAT_TEMPLATE_ = Symbol.intern ("UIL-FORMAT-TEMPLATE");
  private static final Symbol UIL_QUOTE_MARK_HANDLING_ = Symbol.intern ("UIL-QUOTE-MARK-HANDLING");
  private static final Symbol UIL_TEXT_CASE_HANDLING_ = Symbol.intern ("UIL-TEXT-CASE-HANDLING");
  private static final Symbol UIL_DEFAULT_VALUE_SPECIFICATION_ = Symbol.intern ("UIL-DEFAULT-VALUE-SPECIFICATION");
  private static final Symbol UIL_VALIDATION_FAILURE_METHOD_ = Symbol.intern ("UIL-VALIDATION-FAILURE-METHOD");
  private static final Symbol UIL_VALIDATION_TIME_FIELD_DELIMITER_ = Symbol.intern ("UIL-VALIDATION-TIME-FIELD-DELIMITER");
  private static final Symbol UIL_VALIDATION_DATE_FIELD_DELIMITER_ = Symbol.intern ("UIL-VALIDATION-DATE-FIELD-DELIMITER");
  private static final Symbol UIL_MINIMUM_VALUE_ = Symbol.intern ("UIL-MINIMUM-VALUE");
  private static final Symbol UIL_MAXIMUM_VALUE_ = Symbol.intern ("UIL-MAXIMUM-VALUE");
  private static final Symbol UIL_MINIMUM_LENGTH_ = Symbol.intern ("UIL-MINIMUM-LENGTH");
  private static final Symbol UIL_MAXIMUM_LENGTH_ = Symbol.intern ("UIL-MAXIMUM-LENGTH");
  private static final Symbol UIL_ALLOW_NONE_AS_VALID_ = Symbol.intern ("UIL-ALLOW-NONE-AS-VALID");
  private static final Symbol UIL_24_HOUR_CLOCK_ = Symbol.intern ("UIL-24-HOUR-CLOCK");
  private static final Symbol UIL_REVERT_VALUE_ON_ERROR_ = Symbol.intern ("UIL-REVERT-VALUE-ON-ERROR");
  private static final Symbol UIL_FLOAT_FORMAT_OUTPUT_FORMAT_ = Symbol.intern ("UIL-FLOAT-FORMAT-OUTPUT-FORMAT");
  private static final Symbol UIL_FLOAT_FORMAT_OUTPUT_PRECISION_ = Symbol.intern ("UIL-FLOAT-FORMAT-OUTPUT-PRECISION");
  private static final Symbol UIL_FLOAT_FORMAT_REMOVE_TRAILING_ZEROS_ = Symbol.intern ("UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS");
  private static final Symbol UIL_ARRAY_OF_LEGAL_SYMBOLIC_VALUES_ = Symbol.intern ("UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES");
  private static final Symbol UIL_ARRAY_OF_LEGAL_TEXT_VALUES_ = Symbol.intern ("UIL-ARRAY-OF-LEGAL-TEXT-VALUES");
  private static final Symbol UIL_ARRAY_OF_LEGAL_INTEGER_VALUES_ = Symbol.intern ("UIL-ARRAY-OF-LEGAL-INTEGER-VALUES");
  private static final Symbol UIL_ARRAY_OF_LEGAL_QUANTITY_VALUES_ = Symbol.intern ("UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES");

  /* Generated constructors */

  public UilFormatSpecificationClassImpl() {
    super();
  }

  public UilFormatSpecificationClassImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilFormatSpecificationClassImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-FORMAT-TYPE
   * @param uilFormatType new value to conclude for UIL-FORMAT-TYPE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilFormatType(java.lang.Object uilFormatType) throws G2AccessException {
    setAttributeValue (UIL_FORMAT_TYPE_, uilFormatType);
  }

  /**
   * Generated Property Getter for attribute -- UIL-FORMAT-TYPE
   * @return the value of the UIL-FORMAT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilFormatType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_FORMAT_TYPE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-FORMAT-TEMPLATE
   * @param uilFormatTemplate new value to conclude for UIL-FORMAT-TEMPLATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilFormatTemplate(java.lang.Object uilFormatTemplate) throws G2AccessException {
    setAttributeValue (UIL_FORMAT_TEMPLATE_, uilFormatTemplate);
  }

  /**
   * Generated Property Getter for attribute -- UIL-FORMAT-TEMPLATE
   * @return the value of the UIL-FORMAT-TEMPLATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilFormatTemplate() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_FORMAT_TEMPLATE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-QUOTE-MARK-HANDLING
   * @param uilQuoteMarkHandling new value to conclude for UIL-QUOTE-MARK-HANDLING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilQuoteMarkHandling(java.lang.Object uilQuoteMarkHandling) throws G2AccessException {
    setAttributeValue (UIL_QUOTE_MARK_HANDLING_, uilQuoteMarkHandling);
  }

  /**
   * Generated Property Getter for attribute -- UIL-QUOTE-MARK-HANDLING
   * @return the value of the UIL-QUOTE-MARK-HANDLING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilQuoteMarkHandling() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_QUOTE_MARK_HANDLING_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-TEXT-CASE-HANDLING
   * @param uilTextCaseHandling new value to conclude for UIL-TEXT-CASE-HANDLING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTextCaseHandling(java.lang.Object uilTextCaseHandling) throws G2AccessException {
    setAttributeValue (UIL_TEXT_CASE_HANDLING_, uilTextCaseHandling);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TEXT-CASE-HANDLING
   * @return the value of the UIL-TEXT-CASE-HANDLING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilTextCaseHandling() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TEXT_CASE_HANDLING_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DEFAULT-VALUE-SPECIFICATION
   * @param uilDefaultValueSpecification new value to conclude for UIL-DEFAULT-VALUE-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDefaultValueSpecification(java.lang.Object uilDefaultValueSpecification) throws G2AccessException {
    setAttributeValue (UIL_DEFAULT_VALUE_SPECIFICATION_, uilDefaultValueSpecification);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DEFAULT-VALUE-SPECIFICATION
   * @return the value of the UIL-DEFAULT-VALUE-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDefaultValueSpecification() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DEFAULT_VALUE_SPECIFICATION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATION-FAILURE-METHOD
   * @param uilValidationFailureMethod new value to conclude for UIL-VALIDATION-FAILURE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilValidationFailureMethod(java.lang.Object uilValidationFailureMethod) throws G2AccessException {
    setAttributeValue (UIL_VALIDATION_FAILURE_METHOD_, uilValidationFailureMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATION-FAILURE-METHOD
   * @return the value of the UIL-VALIDATION-FAILURE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilValidationFailureMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_VALIDATION_FAILURE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATION-TIME-FIELD-DELIMITER
   * @param uilValidationTimeFieldDelimiter new value to conclude for UIL-VALIDATION-TIME-FIELD-DELIMITER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilValidationTimeFieldDelimiter(java.lang.Object uilValidationTimeFieldDelimiter) throws G2AccessException {
    setAttributeValue (UIL_VALIDATION_TIME_FIELD_DELIMITER_, uilValidationTimeFieldDelimiter);
  }

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATION-TIME-FIELD-DELIMITER
   * @return the value of the UIL-VALIDATION-TIME-FIELD-DELIMITER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilValidationTimeFieldDelimiter() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_VALIDATION_TIME_FIELD_DELIMITER_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATION-DATE-FIELD-DELIMITER
   * @param uilValidationDateFieldDelimiter new value to conclude for UIL-VALIDATION-DATE-FIELD-DELIMITER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilValidationDateFieldDelimiter(java.lang.Object uilValidationDateFieldDelimiter) throws G2AccessException {
    setAttributeValue (UIL_VALIDATION_DATE_FIELD_DELIMITER_, uilValidationDateFieldDelimiter);
  }

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATION-DATE-FIELD-DELIMITER
   * @return the value of the UIL-VALIDATION-DATE-FIELD-DELIMITER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilValidationDateFieldDelimiter() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_VALIDATION_DATE_FIELD_DELIMITER_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-MINIMUM-VALUE
   * @param uilMinimumValue new value to conclude for UIL-MINIMUM-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMinimumValue(java.lang.Object uilMinimumValue) throws G2AccessException {
    setAttributeValue (UIL_MINIMUM_VALUE_, uilMinimumValue);
  }

  /**
   * Generated Property Getter for attribute -- UIL-MINIMUM-VALUE
   * @return the value of the UIL-MINIMUM-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilMinimumValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MINIMUM_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-MAXIMUM-VALUE
   * @param uilMaximumValue new value to conclude for UIL-MAXIMUM-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMaximumValue(java.lang.Object uilMaximumValue) throws G2AccessException {
    setAttributeValue (UIL_MAXIMUM_VALUE_, uilMaximumValue);
  }

  /**
   * Generated Property Getter for attribute -- UIL-MAXIMUM-VALUE
   * @return the value of the UIL-MAXIMUM-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilMaximumValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MAXIMUM_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-MINIMUM-LENGTH
   * @param uilMinimumLength new value to conclude for UIL-MINIMUM-LENGTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMinimumLength(java.lang.Object uilMinimumLength) throws G2AccessException {
    setAttributeValue (UIL_MINIMUM_LENGTH_, uilMinimumLength);
  }

  /**
   * Generated Property Getter for attribute -- UIL-MINIMUM-LENGTH
   * @return the value of the UIL-MINIMUM-LENGTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilMinimumLength() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MINIMUM_LENGTH_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-MAXIMUM-LENGTH
   * @param uilMaximumLength new value to conclude for UIL-MAXIMUM-LENGTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMaximumLength(java.lang.Object uilMaximumLength) throws G2AccessException {
    setAttributeValue (UIL_MAXIMUM_LENGTH_, uilMaximumLength);
  }

  /**
   * Generated Property Getter for attribute -- UIL-MAXIMUM-LENGTH
   * @return the value of the UIL-MAXIMUM-LENGTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilMaximumLength() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MAXIMUM_LENGTH_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-NONE-AS-VALID
   * @param uilAllowNoneAsValid new value to conclude for UIL-ALLOW-NONE-AS-VALID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilAllowNoneAsValid(java.lang.Object uilAllowNoneAsValid) throws G2AccessException {
    setAttributeValue (UIL_ALLOW_NONE_AS_VALID_, uilAllowNoneAsValid);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-NONE-AS-VALID
   * @return the value of the UIL-ALLOW-NONE-AS-VALID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilAllowNoneAsValid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ALLOW_NONE_AS_VALID_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-24-HOUR-CLOCK
   * @param uil24HourClock new value to conclude for UIL-24-HOUR-CLOCK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUil24HourClock(java.lang.Object uil24HourClock) throws G2AccessException {
    setAttributeValue (UIL_24_HOUR_CLOCK_, uil24HourClock);
  }

  /**
   * Generated Property Getter for attribute -- UIL-24-HOUR-CLOCK
   * @return the value of the UIL-24-HOUR-CLOCK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUil24HourClock() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_24_HOUR_CLOCK_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-REVERT-VALUE-ON-ERROR
   * @param uilRevertValueOnError new value to conclude for UIL-REVERT-VALUE-ON-ERROR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilRevertValueOnError(java.lang.Object uilRevertValueOnError) throws G2AccessException {
    setAttributeValue (UIL_REVERT_VALUE_ON_ERROR_, uilRevertValueOnError);
  }

  /**
   * Generated Property Getter for attribute -- UIL-REVERT-VALUE-ON-ERROR
   * @return the value of the UIL-REVERT-VALUE-ON-ERROR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilRevertValueOnError() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_REVERT_VALUE_ON_ERROR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-FLOAT-FORMAT-OUTPUT-FORMAT
   * @param uilFloatFormatOutputFormat new value to conclude for UIL-FLOAT-FORMAT-OUTPUT-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilFloatFormatOutputFormat(com.gensym.util.Symbol uilFloatFormatOutputFormat) throws G2AccessException {
    setAttributeValue (UIL_FLOAT_FORMAT_OUTPUT_FORMAT_, uilFloatFormatOutputFormat);
  }

  /**
   * Generated Property Getter for attribute -- UIL-FLOAT-FORMAT-OUTPUT-FORMAT
   * @return the value of the UIL-FLOAT-FORMAT-OUTPUT-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUilFloatFormatOutputFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_FLOAT_FORMAT_OUTPUT_FORMAT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-FLOAT-FORMAT-OUTPUT-PRECISION
   * @param uilFloatFormatOutputPrecision new value to conclude for UIL-FLOAT-FORMAT-OUTPUT-PRECISION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilFloatFormatOutputPrecision(int uilFloatFormatOutputPrecision) throws G2AccessException {
    setAttributeValue (UIL_FLOAT_FORMAT_OUTPUT_PRECISION_, new Integer (uilFloatFormatOutputPrecision));
  }

  /**
   * Generated Property Getter for attribute -- UIL-FLOAT-FORMAT-OUTPUT-PRECISION
   * @return the value of the UIL-FLOAT-FORMAT-OUTPUT-PRECISION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getUilFloatFormatOutputPrecision() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_FLOAT_FORMAT_OUTPUT_PRECISION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS
   * @param uilFloatFormatRemoveTrailingZeros new value to conclude for UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilFloatFormatRemoveTrailingZeros(boolean uilFloatFormatRemoveTrailingZeros) throws G2AccessException {
    setAttributeValue (UIL_FLOAT_FORMAT_REMOVE_TRAILING_ZEROS_, new Boolean (uilFloatFormatRemoveTrailingZeros));
  }

  /**
   * Generated Property Getter for attribute -- UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS
   * @return the value of the UIL-FLOAT-FORMAT-REMOVE-TRAILING-ZEROS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getUilFloatFormatRemoveTrailingZeros() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_FLOAT_FORMAT_REMOVE_TRAILING_ZEROS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES
   * @param uilArrayOfLegalSymbolicValues new value to conclude for UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilArrayOfLegalSymbolicValues(java.lang.Object uilArrayOfLegalSymbolicValues) throws G2AccessException {
    setAttributeValue (UIL_ARRAY_OF_LEGAL_SYMBOLIC_VALUES_, uilArrayOfLegalSymbolicValues);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES
   * @return the value of the UIL-ARRAY-OF-LEGAL-SYMBOLIC-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilArrayOfLegalSymbolicValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ARRAY_OF_LEGAL_SYMBOLIC_VALUES_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ARRAY-OF-LEGAL-TEXT-VALUES
   * @param uilArrayOfLegalTextValues new value to conclude for UIL-ARRAY-OF-LEGAL-TEXT-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilArrayOfLegalTextValues(java.lang.Object uilArrayOfLegalTextValues) throws G2AccessException {
    setAttributeValue (UIL_ARRAY_OF_LEGAL_TEXT_VALUES_, uilArrayOfLegalTextValues);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ARRAY-OF-LEGAL-TEXT-VALUES
   * @return the value of the UIL-ARRAY-OF-LEGAL-TEXT-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilArrayOfLegalTextValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ARRAY_OF_LEGAL_TEXT_VALUES_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ARRAY-OF-LEGAL-INTEGER-VALUES
   * @param uilArrayOfLegalIntegerValues new value to conclude for UIL-ARRAY-OF-LEGAL-INTEGER-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilArrayOfLegalIntegerValues(java.lang.Object uilArrayOfLegalIntegerValues) throws G2AccessException {
    setAttributeValue (UIL_ARRAY_OF_LEGAL_INTEGER_VALUES_, uilArrayOfLegalIntegerValues);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ARRAY-OF-LEGAL-INTEGER-VALUES
   * @return the value of the UIL-ARRAY-OF-LEGAL-INTEGER-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilArrayOfLegalIntegerValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ARRAY_OF_LEGAL_INTEGER_VALUES_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES
   * @param uilArrayOfLegalQuantityValues new value to conclude for UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilArrayOfLegalQuantityValues(java.lang.Object uilArrayOfLegalQuantityValues) throws G2AccessException {
    setAttributeValue (UIL_ARRAY_OF_LEGAL_QUANTITY_VALUES_, uilArrayOfLegalQuantityValues);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES
   * @return the value of the UIL-ARRAY-OF-LEGAL-QUANTITY-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilArrayOfLegalQuantityValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ARRAY_OF_LEGAL_QUANTITY_VALUES_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
