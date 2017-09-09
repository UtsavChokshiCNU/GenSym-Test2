/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2rtMessageImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Aug 05 16:23:05 EDT 1999
 *
 */


package com.gensym.classes.modules.g2runtime;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class G2rtMessageImpl extends com.gensym.classes.ObjectImpl implements G2rtMessage {


  static final long serialVersionUID = 2L;
  private static final Symbol CATEGORY_ = Symbol.intern ("CATEGORY");
  private static final Symbol TIMESTAMP_ = Symbol.intern ("TIMESTAMP");
  private static final Symbol _REPLY_SEQ_ = Symbol.intern ("_REPLY-SEQ");
  private static final Symbol _REPLY_EXCEPTION_NAME_ = Symbol.intern ("_REPLY-EXCEPTION-NAME");
  private static final Symbol _REPLY_EXCEPTION_TEXT_ = Symbol.intern ("_REPLY-EXCEPTION-TEXT");
  private static final Symbol CONTENT_TYPE_ = Symbol.intern ("CONTENT-TYPE");
  private static final Symbol CONTENT_ = Symbol.intern ("CONTENT");
  private static final Symbol SUBSTITUTE_JAVA_INTERFACE_CLASS_NAME_FOR_CLASS_ = Symbol.intern ("SUBSTITUTE-JAVA-INTERFACE-CLASS-NAME");
  private static final Symbol SUBSTITUTE_JAVA_IMPLEMENTATION_CLASS_NAME_FOR_CLASS_ = Symbol.intern ("SUBSTITUTE-JAVA-IMPLEMENTATION-CLASS-NAME");
  private static final Symbol EXPORT_CLASS_METHODS_TO_JAVA_FOR_CLASS_ = Symbol.intern ("EXPORT-CLASS-METHODS-TO-JAVA");

  /* Generated constructors */

  public G2rtMessageImpl() {
    super();
  }

  public G2rtMessageImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- CATEGORY
   * @param category new value to conclude for CATEGORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCategory(java.lang.String category) throws G2AccessException {
    setAttributeValue (CATEGORY_, category);
  }

  /**
   * Generated Property Getter for attribute -- CATEGORY
   * @return the value of the CATEGORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getCategory() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CATEGORY_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TIMESTAMP
   * @param timestamp new value to conclude for TIMESTAMP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTimestamp(double timestamp) throws G2AccessException {
    setAttributeValue (TIMESTAMP_, new Double (timestamp));
  }

  /**
   * Generated Property Getter for attribute -- TIMESTAMP
   * @return the value of the TIMESTAMP attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public double getTimestamp() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (TIMESTAMP_);
    return ((Double)retnValue).doubleValue ();
  }

  /**
   * Generated Property Setter for attribute -- _REPLY-SEQ
   * @param _replySeq new value to conclude for _REPLY-SEQ
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_replySeq(com.gensym.util.Sequence _replySeq) throws G2AccessException {
    setAttributeValue (_REPLY_SEQ_, _replySeq);
  }

  /**
   * Generated Property Getter for attribute -- _REPLY-SEQ
   * @return the value of the _REPLY-SEQ attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence get_replySeq() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_REPLY_SEQ_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _REPLY-EXCEPTION-NAME
   * @param _replyExceptionName new value to conclude for _REPLY-EXCEPTION-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_replyExceptionName(java.lang.String _replyExceptionName) throws G2AccessException {
    setAttributeValue (_REPLY_EXCEPTION_NAME_, _replyExceptionName);
  }

  /**
   * Generated Property Getter for attribute -- _REPLY-EXCEPTION-NAME
   * @return the value of the _REPLY-EXCEPTION-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String get_replyExceptionName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_REPLY_EXCEPTION_NAME_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _REPLY-EXCEPTION-TEXT
   * @param _replyExceptionText new value to conclude for _REPLY-EXCEPTION-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_replyExceptionText(java.lang.String _replyExceptionText) throws G2AccessException {
    setAttributeValue (_REPLY_EXCEPTION_TEXT_, _replyExceptionText);
  }

  /**
   * Generated Property Getter for attribute -- _REPLY-EXCEPTION-TEXT
   * @return the value of the _REPLY-EXCEPTION-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String get_replyExceptionText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_REPLY_EXCEPTION_TEXT_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CONTENT-TYPE
   * @param contentType new value to conclude for CONTENT-TYPE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setContentType(java.lang.String contentType) throws G2AccessException {
    setAttributeValue (CONTENT_TYPE_, contentType);
  }

  /**
   * Generated Property Getter for attribute -- CONTENT-TYPE
   * @return the value of the CONTENT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getContentType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CONTENT_TYPE_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CONTENT
   * @param content new value to conclude for CONTENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setContent(java.lang.Object content) throws G2AccessException {
    setAttributeValue (CONTENT_, content);
  }

  /**
   * Generated Property Getter for attribute -- CONTENT
   * @return the value of the CONTENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getContent() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CONTENT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAuthorsForClass(com.gensym.util.Structure authors) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAuthorsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getChangeLogForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-NAME
   * @param className new value to conclude for CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassNameForClass(com.gensym.util.Symbol className) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_, className);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-NAME
   * @return the value of the CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getClassNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @param directSuperiorClasses new value to conclude for DIRECT-SUPERIOR-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDirectSuperiorClassesForClass(com.gensym.util.Sequence directSuperiorClasses) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_, directSuperiorClasses);
  }

  /**
   * Generated Property Getter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @return the value of the DIRECT-SUPERIOR-CLASSES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getDirectSuperiorClassesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @param classSpecificAttributes new value to conclude for CLASS-SPECIFIC-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassSpecificAttributesForClass(com.gensym.util.Sequence classSpecificAttributes) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_, classSpecificAttributes);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @return the value of the CLASS-SPECIFIC-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getClassSpecificAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-RESTRICTIONS
   * @return the value of the CLASS-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getClassRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INSTANCE-CONFIGURATION
   * @param instanceConfiguration new value to conclude for INSTANCE-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInstanceConfigurationForClass(com.gensym.util.Sequence instanceConfiguration) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_, instanceConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- INSTANCE-CONFIGURATION
   * @return the value of the INSTANCE-CONFIGURATION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInstanceConfigurationForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getChangeForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-INHERITANCE-PATH
   * @return the value of the CLASS-INHERITANCE-PATH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getClassInheritancePathForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_INHERITANCE_PATH_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INHERITED-ATTRIBUTES
   * @return the value of the INHERITED-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInheritedAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INHERITED_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INITIALIZABLE-SYSTEM-ATTRIBUTES
   * @return the value of the INITIALIZABLE-SYSTEM-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInitializableSystemAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INITIALIZABLE_SYSTEM_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @param attributeInitializations new value to conclude for ATTRIBUTE-INITIALIZATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAttributeInitializationsForClass(com.gensym.util.Sequence attributeInitializations) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_, attributeInitializations);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @return the value of the ATTRIBUTE-INITIALIZATIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getAttributeInitializationsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CLASS
   * @return the value of the SUPERIOR-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSuperiorClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SUPERIOR_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CAPABILITIES-AND-RESTRICTIONS
   * @return the value of the CAPABILITIES-AND-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getCapabilitiesAndRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CAPABILITIES_AND_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTES-SPECIFIC-TO-CLASS
   * @return the value of the ATTRIBUTES-SPECIFIC-TO-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAttributesSpecificToClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTES_SPECIFIC_TO_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- MENU-OPTION
   * @return the value of the MENU-OPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMenuOptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.MENU_OPTION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SUBSTITUTE-JAVA-INTERFACE-CLASS-NAME
   * @param substituteJavaInterfaceClassName new value to conclude for SUBSTITUTE-JAVA-INTERFACE-CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSubstituteJavaInterfaceClassNameForClass(java.lang.String substituteJavaInterfaceClassName) throws G2AccessException {
    setStaticAttributeValue (SUBSTITUTE_JAVA_INTERFACE_CLASS_NAME_FOR_CLASS_, substituteJavaInterfaceClassName);
  }

  /**
   * Generated Property Getter for attribute -- SUBSTITUTE-JAVA-INTERFACE-CLASS-NAME
   * @return the value of the SUBSTITUTE-JAVA-INTERFACE-CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getSubstituteJavaInterfaceClassNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SUBSTITUTE_JAVA_INTERFACE_CLASS_NAME_FOR_CLASS_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SUBSTITUTE-JAVA-IMPLEMENTATION-CLASS-NAME
   * @param substituteJavaImplementationClassName new value to conclude for SUBSTITUTE-JAVA-IMPLEMENTATION-CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSubstituteJavaImplementationClassNameForClass(java.lang.String substituteJavaImplementationClassName) throws G2AccessException {
    setStaticAttributeValue (SUBSTITUTE_JAVA_IMPLEMENTATION_CLASS_NAME_FOR_CLASS_, substituteJavaImplementationClassName);
  }

  /**
   * Generated Property Getter for attribute -- SUBSTITUTE-JAVA-IMPLEMENTATION-CLASS-NAME
   * @return the value of the SUBSTITUTE-JAVA-IMPLEMENTATION-CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getSubstituteJavaImplementationClassNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SUBSTITUTE_JAVA_IMPLEMENTATION_CLASS_NAME_FOR_CLASS_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EXPORT-CLASS-METHODS-TO-JAVA
   * @param exportClassMethodsToJava new value to conclude for EXPORT-CLASS-METHODS-TO-JAVA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setExportClassMethodsToJavaForClass(boolean exportClassMethodsToJava) throws G2AccessException {
    setStaticAttributeValue (EXPORT_CLASS_METHODS_TO_JAVA_FOR_CLASS_, new Boolean (exportClassMethodsToJava));
  }

  /**
   * Generated Property Getter for attribute -- EXPORT-CLASS-METHODS-TO-JAVA
   * @return the value of the EXPORT-CLASS-METHODS-TO-JAVA attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getExportClassMethodsToJavaForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (EXPORT_CLASS_METHODS_TO_JAVA_FOR_CLASS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  // Method Name Constants
  private static final Symbol MethodName_SET_CONTENT_ = Symbol.intern ("SET-CONTENT");
  private static final Symbol MethodName_SET_CONTENT_TYPE_ = Symbol.intern ("SET-CONTENT-TYPE");
  private static final Symbol MethodName_GET_CONTENT_ = Symbol.intern ("GET-CONTENT");
  private static final Symbol MethodName_GET_CONTENT_TYPE_ = Symbol.intern ("GET-CONTENT-TYPE");
  private static final Symbol MethodName_GET_CATEGORY_ = Symbol.intern ("GET-CATEGORY");
  private static final Symbol MethodName_GET_TIME_STAMP_ = Symbol.intern ("GET-TIME-STAMP");
  private static final Symbol MethodName_SET_REPLY_ = Symbol.intern ("SET-REPLY");
  private static final Symbol MethodName_SET_EXCEPTION_ = Symbol.intern ("SET-EXCEPTION");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * G2RT-MESSAGE::GET-TIME-STAMP
   * @return the return from calling GET-TIME-STAMP
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-MESSAGE) = (FLOAT)
   */
  @Override
  public  double getTimeStamp() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GET_TIME_STAMP_, args);
      return ((Double)result).doubleValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-MESSAGE::SET-REPLY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-MESSAGE,arg1:ITEM-OR-VALUE) = ()
   */
  @Override
  public  void setReply(java.lang.Object arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_SET_REPLY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-MESSAGE::SET-EXCEPTION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-MESSAGE,arg1:TEXT,arg2:TEXT) = ()
   */
  @Override
  public  void setException(java.lang.String arg1,java.lang.String arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_SET_EXCEPTION_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
