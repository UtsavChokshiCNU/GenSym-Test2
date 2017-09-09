/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2rtReplySetImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Jul 23 05:27:20 EDT 1999
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

public class G2rtReplySetImpl extends com.gensym.classes.ObjectImpl implements G2rtReplySet {


  static final long serialVersionUID = 2L;
  private static final Symbol _REPLIES_ = Symbol.intern ("_REPLIES");
  private static final Symbol _UNAVAILABLE_REPLIES_ = Symbol.intern ("_UNAVAILABLE-REPLIES");
  private static final Symbol _CURRENT_REPLY_INDEX_ = Symbol.intern ("_CURRENT-REPLY-INDEX");
  private static final Symbol _NUMBER_OF_REPLIES_RECEIVED_ = Symbol.intern ("_NUMBER-OF-REPLIES-RECEIVED");
  private static final Symbol _NUMBER_OF_AVAIL_REPLIES_RECEIVED_ = Symbol.intern ("_NUMBER-OF-AVAIL-REPLIES-RECEIVED");
  private static final Symbol SUBSTITUTE_JAVA_INTERFACE_CLASS_NAME_FOR_CLASS_ = Symbol.intern ("SUBSTITUTE-JAVA-INTERFACE-CLASS-NAME");
  private static final Symbol SUBSTITUTE_JAVA_IMPLEMENTATION_CLASS_NAME_FOR_CLASS_ = Symbol.intern ("SUBSTITUTE-JAVA-IMPLEMENTATION-CLASS-NAME");
  private static final Symbol EXPORT_CLASS_METHODS_TO_JAVA_FOR_CLASS_ = Symbol.intern ("EXPORT-CLASS-METHODS-TO-JAVA");

  /* Generated constructors */

  public G2rtReplySetImpl() {
    super();
  }

  public G2rtReplySetImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- _REPLIES
   * @param _replies new value to conclude for _REPLIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_replies(com.gensym.classes.G2List _replies) throws G2AccessException {
    setAttributeValue (_REPLIES_, _replies);
  }

  /**
   * Generated Property Getter for attribute -- _REPLIES
   * @return the value of the _REPLIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.G2List get_replies() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_REPLIES_);
    return (com.gensym.classes.G2List)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _UNAVAILABLE-REPLIES
   * @param _unavailableReplies new value to conclude for _UNAVAILABLE-REPLIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_unavailableReplies(com.gensym.classes.G2List _unavailableReplies) throws G2AccessException {
    setAttributeValue (_UNAVAILABLE_REPLIES_, _unavailableReplies);
  }

  /**
   * Generated Property Getter for attribute -- _UNAVAILABLE-REPLIES
   * @return the value of the _UNAVAILABLE-REPLIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.G2List get_unavailableReplies() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_UNAVAILABLE_REPLIES_);
    return (com.gensym.classes.G2List)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _CURRENT-REPLY-INDEX
   * @param _currentReplyIndex new value to conclude for _CURRENT-REPLY-INDEX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_currentReplyIndex(int _currentReplyIndex) throws G2AccessException {
    setAttributeValue (_CURRENT_REPLY_INDEX_, new Integer (_currentReplyIndex));
  }

  /**
   * Generated Property Getter for attribute -- _CURRENT-REPLY-INDEX
   * @return the value of the _CURRENT-REPLY-INDEX attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int get_currentReplyIndex() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_CURRENT_REPLY_INDEX_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- _NUMBER-OF-REPLIES-RECEIVED
   * @param _numberOfRepliesReceived new value to conclude for _NUMBER-OF-REPLIES-RECEIVED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_numberOfRepliesReceived(int _numberOfRepliesReceived) throws G2AccessException {
    setAttributeValue (_NUMBER_OF_REPLIES_RECEIVED_, new Integer (_numberOfRepliesReceived));
  }

  /**
   * Generated Property Getter for attribute -- _NUMBER-OF-REPLIES-RECEIVED
   * @return the value of the _NUMBER-OF-REPLIES-RECEIVED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int get_numberOfRepliesReceived() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_NUMBER_OF_REPLIES_RECEIVED_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- _NUMBER-OF-AVAIL-REPLIES-RECEIVED
   * @param _numberOfAvailRepliesReceived new value to conclude for _NUMBER-OF-AVAIL-REPLIES-RECEIVED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_numberOfAvailRepliesReceived(int _numberOfAvailRepliesReceived) throws G2AccessException {
    setAttributeValue (_NUMBER_OF_AVAIL_REPLIES_RECEIVED_, new Integer (_numberOfAvailRepliesReceived));
  }

  /**
   * Generated Property Getter for attribute -- _NUMBER-OF-AVAIL-REPLIES-RECEIVED
   * @return the value of the _NUMBER-OF-AVAIL-REPLIES-RECEIVED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int get_numberOfAvailRepliesReceived() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_NUMBER_OF_AVAIL_REPLIES_RECEIVED_);
    return ((Integer)retnValue).intValue ();
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
  private static final Symbol MethodName_HAS_MORE_FUTURE_REPLIES_ = Symbol.intern ("HAS-MORE-FUTURE-REPLIES");
  private static final Symbol MethodName_IS_ANY_AVAILABLE_ = Symbol.intern ("IS-ANY-AVAILABLE");
  private static final Symbol MethodName_ARE_ALL_AVAILABLE_ = Symbol.intern ("ARE-ALL-AVAILABLE");
  private static final Symbol MethodName_COUNT_AVAILABLE_ = Symbol.intern ("COUNT-AVAILABLE");
  private static final Symbol MethodName_COUNT_UNAVAILABLE_ = Symbol.intern ("COUNT-UNAVAILABLE");
  private static final Symbol MethodName_WAIT_FOR_NEXT_FUTURE_REPLY_ = Symbol.intern ("WAIT-FOR-NEXT-FUTURE-REPLY");
  private static final Symbol MethodName_WAIT_FOR_ALL_REPLIES_ = Symbol.intern ("WAIT-FOR-ALL-REPLIES");
  private static final Symbol MethodName_WAIT_FOR_FUTURE_REPLIES_ = Symbol.intern ("WAIT-FOR-FUTURE-REPLIES");
  private static final Symbol MethodName_GET_NEXT_FUTURE_REPLY_ = Symbol.intern ("GET-NEXT-FUTURE-REPLY");
  private static final Symbol MethodName__RECEIVED_AVAILABLE_FUTURE_REPLY_ = Symbol.intern ("_RECEIVED-AVAILABLE-FUTURE-REPLY");
  private static final Symbol MethodName__RECEIVED_UNAVAILABLE_FUTURE_REPLY_ = Symbol.intern ("_RECEIVED-UNAVAILABLE-FUTURE-REPLY");
  private static final Symbol MethodName_DISPOSE_ = Symbol.intern ("DISPOSE");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::HAS-MORE-FUTURE-REPLIES
   * @return the return from calling HAS-MORE-FUTURE-REPLIES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET) = (TRUTH-VALUE)
   */
  @Override
  public  boolean hasMoreFutureReplies() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_HAS_MORE_FUTURE_REPLIES_, args);
      return ((Boolean)result).booleanValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::IS-ANY-AVAILABLE
   * @return the return from calling IS-ANY-AVAILABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET) = (TRUTH-VALUE)
   */
  @Override
  public  boolean isAnyAvailable() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_IS_ANY_AVAILABLE_, args);
      return ((Boolean)result).booleanValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::ARE-ALL-AVAILABLE
   * @return the return from calling ARE-ALL-AVAILABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET) = (TRUTH-VALUE)
   */
  @Override
  public  boolean areAllAvailable() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_ARE_ALL_AVAILABLE_, args);
      return ((Boolean)result).booleanValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::COUNT-AVAILABLE
   * @return the return from calling COUNT-AVAILABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET) = (INTEGER)
   */
  @Override
  public  int countAvailable() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_COUNT_AVAILABLE_, args);
      return ((Integer)result).intValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::COUNT-UNAVAILABLE
   * @return the return from calling COUNT-UNAVAILABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET) = (INTEGER)
   */
  @Override
  public  int countUnavailable() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_COUNT_UNAVAILABLE_, args);
      return ((Integer)result).intValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::WAIT-FOR-NEXT-FUTURE-REPLY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET,arg1:FLOAT) = ()
   */
  @Override
  public  void waitForNextFutureReply(double arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,new Double (arg1)};
      result = (java.lang.Object)callRPC(MethodName_WAIT_FOR_NEXT_FUTURE_REPLY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::WAIT-FOR-ALL-REPLIES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET,arg1:FLOAT) = ()
   */
  @Override
  public  void waitForAllReplies(double arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,new Double (arg1)};
      result = (java.lang.Object)callRPC(MethodName_WAIT_FOR_ALL_REPLIES_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::WAIT-FOR-FUTURE-REPLIES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET,arg1:FLOAT,arg2:INTEGER) = ()
   */
  @Override
  public  void waitForFutureReplies(double arg1,int arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,new Double (arg1),new Integer (arg2)};
      result = (java.lang.Object)callRPC(MethodName_WAIT_FOR_FUTURE_REPLIES_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::GET-NEXT-FUTURE-REPLY
   * @return the return from calling GET-NEXT-FUTURE-REPLY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET) = (CLASS G2RT-FUTURE-REPLY)
   */
  @Override
  public  com.gensym.classes.modules.g2runtime.G2rtFutureReply getNextFutureReply() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GET_NEXT_FUTURE_REPLY_, args);
      return (com.gensym.classes.modules.g2runtime.G2rtFutureReply)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::_RECEIVED-AVAILABLE-FUTURE-REPLY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET,arg1:CLASS G2RT-FUTURE-REPLY) = ()
   */
  @Override
  public  void _receivedAvailableFutureReply(com.gensym.classes.modules.g2runtime.G2rtFutureReply arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName__RECEIVED_AVAILABLE_FUTURE_REPLY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2RT-REPLY-SET::_RECEIVED-UNAVAILABLE-FUTURE-REPLY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2RT-REPLY-SET,arg1:CLASS G2RT-FUTURE-REPLY) = ()
   */
  @Override
  public  void _receivedUnavailableFutureReply(com.gensym.classes.modules.g2runtime.G2rtFutureReply arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName__RECEIVED_UNAVAILABLE_FUTURE_REPLY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
