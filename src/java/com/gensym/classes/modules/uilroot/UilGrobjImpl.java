/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilGrobjImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:14:37 EDT 2007
 *
 */


package com.gensym.classes.modules.uilroot;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class UilGrobjImpl extends com.gensym.classes.modules.uilroot.UilObjectImpl implements UilGrobj {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_IS_MANAGED_ = Symbol.intern ("UIL-IS-MANAGED");
  private static final Symbol UIL_IS_PERMANENT_ = Symbol.intern ("UIL-IS-PERMANENT");
  private static final Symbol ID_ = Symbol.intern ("ID");
  private static final Symbol CONFIGURATION_ = Symbol.intern ("CONFIGURATION");
  private static final Symbol UIL_DELETE_METHOD_ = Symbol.intern ("UIL-DELETE-METHOD");
  private static final Symbol UIL_CONCLUDE_METHOD_ = Symbol.intern ("UIL-CONCLUDE-METHOD");
  private static final Symbol UIL_VALIDATION_METHOD_ = Symbol.intern ("UIL-VALIDATION-METHOD");
  private static final Symbol UIL_UPDATE_METHOD_ = Symbol.intern ("UIL-UPDATE-METHOD");
  private static final Symbol UIL_CONFIGURATION_METHOD_ = Symbol.intern ("UIL-CONFIGURATION-METHOD");
  private static final Symbol UIL_INITIALIZATION_METHOD_ = Symbol.intern ("UIL-INITIALIZATION-METHOD");
  private static final Symbol UIL_ENABLE_METHOD_ = Symbol.intern ("UIL-ENABLE-METHOD");
  private static final Symbol UIL_DISABLE_METHOD_ = Symbol.intern ("UIL-DISABLE-METHOD");
  private static final Symbol UIL_SIZE_OF_METHOD_ = Symbol.intern ("UIL-SIZE-OF-METHOD");
  private static final Symbol UIL_SIZE_ = Symbol.intern ("UIL-SIZE");
  private static final Symbol USER_DATA_ = Symbol.intern ("USER-DATA");
  private static final Symbol UIL_CLONE_METHOD_ = Symbol.intern ("UIL-CLONE-METHOD");
  private static final Symbol UIL_MANAGE_METHOD_ = Symbol.intern ("UIL-MANAGE-METHOD");
  private static final Symbol UIL_CONCLUDE_VALUE_IMMEDIATELY_ = Symbol.intern ("UIL-CONCLUDE-VALUE-IMMEDIATELY");
  private static final Symbol UIL_EVENT_TARGET_OBJECT_ = Symbol.intern ("UIL-EVENT-TARGET-OBJECT");
  private static final Symbol UIL_EVENT_TARGET_ATTRIBUTE_ = Symbol.intern ("UIL-EVENT-TARGET-ATTRIBUTE");
  private static final Symbol UIL_EVENT_SOURCE_OBJECT_ = Symbol.intern ("UIL-EVENT-SOURCE-OBJECT");
  private static final Symbol UIL_EVENT_SOURCE_ATTRIBUTE_ = Symbol.intern ("UIL-EVENT-SOURCE-ATTRIBUTE");

  /* Generated constructors */

  public UilGrobjImpl() {
    super();
  }

  public UilGrobjImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilGrobjImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-IS-MANAGED
   * @param uilIsManaged new value to conclude for UIL-IS-MANAGED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilIsManaged(java.lang.Object uilIsManaged) throws G2AccessException {
    setAttributeValue (UIL_IS_MANAGED_, uilIsManaged);
  }

  /**
   * Generated Property Getter for attribute -- UIL-IS-MANAGED
   * @return the value of the UIL-IS-MANAGED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilIsManaged() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_IS_MANAGED_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-IS-PERMANENT
   * @param uilIsPermanent new value to conclude for UIL-IS-PERMANENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilIsPermanent(java.lang.Object uilIsPermanent) throws G2AccessException {
    setAttributeValue (UIL_IS_PERMANENT_, uilIsPermanent);
  }

  /**
   * Generated Property Getter for attribute -- UIL-IS-PERMANENT
   * @return the value of the UIL-IS-PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilIsPermanent() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_IS_PERMANENT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ID
   * @param id new value to conclude for ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setId(java.lang.Object id) throws G2AccessException {
    setAttributeValue (ID_, id);
  }

  /**
   * Generated Property Getter for attribute -- ID
   * @return the value of the ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ID_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CONFIGURATION
   * @param configuration new value to conclude for CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setConfiguration(java.lang.Object configuration) throws G2AccessException {
    setAttributeValue (CONFIGURATION_, configuration);
  }

  /**
   * Generated Property Getter for attribute -- CONFIGURATION
   * @return the value of the CONFIGURATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getConfiguration() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CONFIGURATION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DELETE-METHOD
   * @param uilDeleteMethod new value to conclude for UIL-DELETE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDeleteMethod(java.lang.Object uilDeleteMethod) throws G2AccessException {
    setAttributeValue (UIL_DELETE_METHOD_, uilDeleteMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DELETE-METHOD
   * @return the value of the UIL-DELETE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDeleteMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DELETE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CONCLUDE-METHOD
   * @param uilConcludeMethod new value to conclude for UIL-CONCLUDE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilConcludeMethod(java.lang.Object uilConcludeMethod) throws G2AccessException {
    setAttributeValue (UIL_CONCLUDE_METHOD_, uilConcludeMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CONCLUDE-METHOD
   * @return the value of the UIL-CONCLUDE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilConcludeMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CONCLUDE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATION-METHOD
   * @param uilValidationMethod new value to conclude for UIL-VALIDATION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilValidationMethod(java.lang.Object uilValidationMethod) throws G2AccessException {
    setAttributeValue (UIL_VALIDATION_METHOD_, uilValidationMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATION-METHOD
   * @return the value of the UIL-VALIDATION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilValidationMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_VALIDATION_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-METHOD
   * @param uilUpdateMethod new value to conclude for UIL-UPDATE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilUpdateMethod(java.lang.Object uilUpdateMethod) throws G2AccessException {
    setAttributeValue (UIL_UPDATE_METHOD_, uilUpdateMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-METHOD
   * @return the value of the UIL-UPDATE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilUpdateMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_UPDATE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CONFIGURATION-METHOD
   * @param uilConfigurationMethod new value to conclude for UIL-CONFIGURATION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilConfigurationMethod(java.lang.Object uilConfigurationMethod) throws G2AccessException {
    setAttributeValue (UIL_CONFIGURATION_METHOD_, uilConfigurationMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CONFIGURATION-METHOD
   * @return the value of the UIL-CONFIGURATION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilConfigurationMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CONFIGURATION_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-INITIALIZATION-METHOD
   * @param uilInitializationMethod new value to conclude for UIL-INITIALIZATION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilInitializationMethod(java.lang.Object uilInitializationMethod) throws G2AccessException {
    setAttributeValue (UIL_INITIALIZATION_METHOD_, uilInitializationMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-INITIALIZATION-METHOD
   * @return the value of the UIL-INITIALIZATION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilInitializationMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_INITIALIZATION_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ENABLE-METHOD
   * @param uilEnableMethod new value to conclude for UIL-ENABLE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEnableMethod(java.lang.Object uilEnableMethod) throws G2AccessException {
    setAttributeValue (UIL_ENABLE_METHOD_, uilEnableMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ENABLE-METHOD
   * @return the value of the UIL-ENABLE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEnableMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ENABLE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DISABLE-METHOD
   * @param uilDisableMethod new value to conclude for UIL-DISABLE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDisableMethod(java.lang.Object uilDisableMethod) throws G2AccessException {
    setAttributeValue (UIL_DISABLE_METHOD_, uilDisableMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DISABLE-METHOD
   * @return the value of the UIL-DISABLE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDisableMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DISABLE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SIZE-OF-METHOD
   * @param uilSizeOfMethod new value to conclude for UIL-SIZE-OF-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSizeOfMethod(java.lang.Object uilSizeOfMethod) throws G2AccessException {
    setAttributeValue (UIL_SIZE_OF_METHOD_, uilSizeOfMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SIZE-OF-METHOD
   * @return the value of the UIL-SIZE-OF-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSizeOfMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SIZE_OF_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SIZE
   * @param uilSize new value to conclude for UIL-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSize(java.lang.Object uilSize) throws G2AccessException {
    setAttributeValue (UIL_SIZE_, uilSize);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SIZE
   * @return the value of the UIL-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSize() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SIZE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- USER-DATA
   * @param userData new value to conclude for USER-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUserData(java.lang.Object userData) throws G2AccessException {
    setAttributeValue (USER_DATA_, userData);
  }

  /**
   * Generated Property Getter for attribute -- USER-DATA
   * @return the value of the USER-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUserData() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (USER_DATA_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CLONE-METHOD
   * @param uilCloneMethod new value to conclude for UIL-CLONE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilCloneMethod(java.lang.Object uilCloneMethod) throws G2AccessException {
    setAttributeValue (UIL_CLONE_METHOD_, uilCloneMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CLONE-METHOD
   * @return the value of the UIL-CLONE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilCloneMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CLONE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-MANAGE-METHOD
   * @param uilManageMethod new value to conclude for UIL-MANAGE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilManageMethod(java.lang.Object uilManageMethod) throws G2AccessException {
    setAttributeValue (UIL_MANAGE_METHOD_, uilManageMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-MANAGE-METHOD
   * @return the value of the UIL-MANAGE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilManageMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MANAGE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CONCLUDE-VALUE-IMMEDIATELY
   * @param uilConcludeValueImmediately new value to conclude for UIL-CONCLUDE-VALUE-IMMEDIATELY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilConcludeValueImmediately(java.lang.Object uilConcludeValueImmediately) throws G2AccessException {
    setAttributeValue (UIL_CONCLUDE_VALUE_IMMEDIATELY_, uilConcludeValueImmediately);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CONCLUDE-VALUE-IMMEDIATELY
   * @return the value of the UIL-CONCLUDE-VALUE-IMMEDIATELY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilConcludeValueImmediately() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CONCLUDE_VALUE_IMMEDIATELY_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-EVENT-TARGET-OBJECT
   * @param uilEventTargetObject new value to conclude for UIL-EVENT-TARGET-OBJECT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEventTargetObject(java.lang.Object uilEventTargetObject) throws G2AccessException {
    setAttributeValue (UIL_EVENT_TARGET_OBJECT_, uilEventTargetObject);
  }

  /**
   * Generated Property Getter for attribute -- UIL-EVENT-TARGET-OBJECT
   * @return the value of the UIL-EVENT-TARGET-OBJECT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEventTargetObject() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_EVENT_TARGET_OBJECT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-EVENT-TARGET-ATTRIBUTE
   * @param uilEventTargetAttribute new value to conclude for UIL-EVENT-TARGET-ATTRIBUTE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEventTargetAttribute(java.lang.Object uilEventTargetAttribute) throws G2AccessException {
    setAttributeValue (UIL_EVENT_TARGET_ATTRIBUTE_, uilEventTargetAttribute);
  }

  /**
   * Generated Property Getter for attribute -- UIL-EVENT-TARGET-ATTRIBUTE
   * @return the value of the UIL-EVENT-TARGET-ATTRIBUTE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEventTargetAttribute() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_EVENT_TARGET_ATTRIBUTE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-EVENT-SOURCE-OBJECT
   * @param uilEventSourceObject new value to conclude for UIL-EVENT-SOURCE-OBJECT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEventSourceObject(java.lang.Object uilEventSourceObject) throws G2AccessException {
    setAttributeValue (UIL_EVENT_SOURCE_OBJECT_, uilEventSourceObject);
  }

  /**
   * Generated Property Getter for attribute -- UIL-EVENT-SOURCE-OBJECT
   * @return the value of the UIL-EVENT-SOURCE-OBJECT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEventSourceObject() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_EVENT_SOURCE_OBJECT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-EVENT-SOURCE-ATTRIBUTE
   * @param uilEventSourceAttribute new value to conclude for UIL-EVENT-SOURCE-ATTRIBUTE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEventSourceAttribute(java.lang.Object uilEventSourceAttribute) throws G2AccessException {
    setAttributeValue (UIL_EVENT_SOURCE_ATTRIBUTE_, uilEventSourceAttribute);
  }

  /**
   * Generated Property Getter for attribute -- UIL-EVENT-SOURCE-ATTRIBUTE
   * @return the value of the UIL-EVENT-SOURCE-ATTRIBUTE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEventSourceAttribute() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_EVENT_SOURCE_ATTRIBUTE_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
