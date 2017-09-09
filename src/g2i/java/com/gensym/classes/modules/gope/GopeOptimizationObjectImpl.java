/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GopeOptimizationObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Dec 20 00:10:37 EST 2002
 *
 */


package com.gensym.classes.modules.gope;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GopeOptimizationObjectImpl extends com.gensym.classes.ObjectImpl implements GopeOptimizationObject {


  static final long serialVersionUID = 2L;
  private static final Symbol IS_MINIMIZATION_PROBLEM_ = Symbol.intern ("IS-MINIMIZATION-PROBLEM");
  private static final Symbol XINITS_ = Symbol.intern ("XINITS");
  private static final Symbol X_ = Symbol.intern ("X");
  private static final Symbol EXTRPARAM_ = Symbol.intern ("EXTRPARAM");
  private static final Symbol XUBS_ = Symbol.intern ("XUBS");
  private static final Symbol XLBS_ = Symbol.intern ("XLBS");
  private static final Symbol NUMBER_OF_CONSTRAINTS_ = Symbol.intern ("NUMBER-OF-CONSTRAINTS");
  private static final Symbol SENSE_OF_CONSTRAINTS_ = Symbol.intern ("SENSE-OF-CONSTRAINTS");
  private static final Symbol RHV_ = Symbol.intern ("RHV");
  private static final Symbol LHV_ = Symbol.intern ("LHV");
  private static final Symbol Y_ = Symbol.intern ("Y");
  private static final Symbol NAME_OF_GSI_INTERFACE_ = Symbol.intern ("NAME-OF-GSI-INTERFACE");
  private static final Symbol NAME_OF_PROBLEM_DLL_ = Symbol.intern ("NAME-OF-PROBLEM-DLL");
  private static final Symbol FINAL_STATUS_ = Symbol.intern ("FINAL-STATUS");
  private static final Symbol _EVENT_NOTIFICATION_ENABLED_ = Symbol.intern ("_EVENT-NOTIFICATION-ENABLED");
  private static final Symbol _LISTENERS_ = Symbol.intern ("_LISTENERS");
  private static final Symbol _LISTENERS_FOR_CLASS_ = Symbol.intern ("_LISTENERS");
  private static final Symbol CLASS_DESCRIPTION_FOR_CLASS_ = Symbol.intern ("CLASS-DESCRIPTION");
  private static final Symbol INSTANCE_KEY_ATTRIBUTE_NAME_FOR_CLASS_ = Symbol.intern ("INSTANCE-KEY-ATTRIBUTE-NAME");
  private static final Symbol CLASS_ATTRIBUTE_PROPERTIES_FOR_CLASS_ = Symbol.intern ("CLASS-ATTRIBUTE-PROPERTIES");
  private static final Symbol CLASS_EVENTS_DESCRIPTION_FOR_CLASS_ = Symbol.intern ("CLASS-EVENTS-DESCRIPTION");

  /* Generated constructors */

  public GopeOptimizationObjectImpl() {
    super();
  }

  public GopeOptimizationObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- IS-MINIMIZATION-PROBLEM
   * @param isMinimizationProblem new value to conclude for IS-MINIMIZATION-PROBLEM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIsMinimizationProblem(boolean isMinimizationProblem) throws G2AccessException {
    setAttributeValue (IS_MINIMIZATION_PROBLEM_, new Boolean (isMinimizationProblem));
  }

  /**
   * Generated Property Getter for attribute -- IS-MINIMIZATION-PROBLEM
   * @return the value of the IS-MINIMIZATION-PROBLEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getIsMinimizationProblem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (IS_MINIMIZATION_PROBLEM_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- XINITS
   * @param xinits new value to conclude for XINITS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXinits(com.gensym.classes.FloatArray xinits) throws G2AccessException {
    setAttributeValue (XINITS_, xinits);
  }

  /**
   * Generated Property Getter for attribute -- XINITS
   * @return the value of the XINITS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.FloatArray getXinits() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (XINITS_);
    return (com.gensym.classes.FloatArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- X
   * @param x new value to conclude for X
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setX(com.gensym.classes.FloatArray x) throws G2AccessException {
    setAttributeValue (X_, x);
  }

  /**
   * Generated Property Getter for attribute -- X
   * @return the value of the X attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.FloatArray getX() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (X_);
    return (com.gensym.classes.FloatArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EXTRPARAM
   * @param extrparam new value to conclude for EXTRPARAM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setExtrparam(com.gensym.classes.FloatArray extrparam) throws G2AccessException {
    setAttributeValue (EXTRPARAM_, extrparam);
  }

  /**
   * Generated Property Getter for attribute -- EXTRPARAM
   * @return the value of the EXTRPARAM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.FloatArray getExtrparam() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (EXTRPARAM_);
    return (com.gensym.classes.FloatArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- XUBS
   * @param xubs new value to conclude for XUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXubs(com.gensym.classes.FloatArray xubs) throws G2AccessException {
    setAttributeValue (XUBS_, xubs);
  }

  /**
   * Generated Property Getter for attribute -- XUBS
   * @return the value of the XUBS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.FloatArray getXubs() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (XUBS_);
    return (com.gensym.classes.FloatArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- XLBS
   * @param xlbs new value to conclude for XLBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXlbs(com.gensym.classes.FloatArray xlbs) throws G2AccessException {
    setAttributeValue (XLBS_, xlbs);
  }

  /**
   * Generated Property Getter for attribute -- XLBS
   * @return the value of the XLBS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.FloatArray getXlbs() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (XLBS_);
    return (com.gensym.classes.FloatArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-CONSTRAINTS
   * @param numberOfConstraints new value to conclude for NUMBER-OF-CONSTRAINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfConstraints(int numberOfConstraints) throws G2AccessException {
    setAttributeValue (NUMBER_OF_CONSTRAINTS_, new Integer (numberOfConstraints));
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-CONSTRAINTS
   * @return the value of the NUMBER-OF-CONSTRAINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getNumberOfConstraints() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NUMBER_OF_CONSTRAINTS_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- SENSE-OF-CONSTRAINTS
   * @param senseOfConstraints new value to conclude for SENSE-OF-CONSTRAINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSenseOfConstraints(java.lang.String senseOfConstraints) throws G2AccessException {
    setAttributeValue (SENSE_OF_CONSTRAINTS_, senseOfConstraints);
  }

  /**
   * Generated Property Getter for attribute -- SENSE-OF-CONSTRAINTS
   * @return the value of the SENSE-OF-CONSTRAINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getSenseOfConstraints() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SENSE_OF_CONSTRAINTS_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RHV
   * @param rhv new value to conclude for RHV
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRhv(com.gensym.classes.FloatArray rhv) throws G2AccessException {
    setAttributeValue (RHV_, rhv);
  }

  /**
   * Generated Property Getter for attribute -- RHV
   * @return the value of the RHV attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.FloatArray getRhv() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (RHV_);
    return (com.gensym.classes.FloatArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- LHV
   * @param lhv new value to conclude for LHV
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLhv(com.gensym.classes.FloatArray lhv) throws G2AccessException {
    setAttributeValue (LHV_, lhv);
  }

  /**
   * Generated Property Getter for attribute -- LHV
   * @return the value of the LHV attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.FloatArray getLhv() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (LHV_);
    return (com.gensym.classes.FloatArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- Y
   * @param y new value to conclude for Y
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setY(double y) throws G2AccessException {
    setAttributeValue (Y_, new Double (y));
  }

  /**
   * Generated Property Getter for attribute -- Y
   * @return the value of the Y attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public double getY() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (Y_);
    return ((Double)retnValue).doubleValue ();
  }

  /**
   * Generated Property Setter for attribute -- NAME-OF-GSI-INTERFACE
   * @param nameOfGsiInterface new value to conclude for NAME-OF-GSI-INTERFACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameOfGsiInterface(com.gensym.util.Symbol nameOfGsiInterface) throws G2AccessException {
    setAttributeValue (NAME_OF_GSI_INTERFACE_, nameOfGsiInterface);
  }

  /**
   * Generated Property Getter for attribute -- NAME-OF-GSI-INTERFACE
   * @return the value of the NAME-OF-GSI-INTERFACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getNameOfGsiInterface() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NAME_OF_GSI_INTERFACE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NAME-OF-PROBLEM-DLL
   * @param nameOfProblemDll new value to conclude for NAME-OF-PROBLEM-DLL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameOfProblemDll(java.lang.String nameOfProblemDll) throws G2AccessException {
    setAttributeValue (NAME_OF_PROBLEM_DLL_, nameOfProblemDll);
  }

  /**
   * Generated Property Getter for attribute -- NAME-OF-PROBLEM-DLL
   * @return the value of the NAME-OF-PROBLEM-DLL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getNameOfProblemDll() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NAME_OF_PROBLEM_DLL_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FINAL-STATUS
   * @param finalStatus new value to conclude for FINAL-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFinalStatus(int finalStatus) throws G2AccessException {
    setAttributeValue (FINAL_STATUS_, new Integer (finalStatus));
  }

  /**
   * Generated Property Getter for attribute -- FINAL-STATUS
   * @return the value of the FINAL-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getFinalStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (FINAL_STATUS_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- _EVENT-NOTIFICATION-ENABLED
   * @param _eventNotificationEnabled new value to conclude for _EVENT-NOTIFICATION-ENABLED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_eventNotificationEnabled(boolean _eventNotificationEnabled) throws G2AccessException {
    setAttributeValue (_EVENT_NOTIFICATION_ENABLED_, new Boolean (_eventNotificationEnabled));
  }

  /**
   * Generated Property Getter for attribute -- _EVENT-NOTIFICATION-ENABLED
   * @return the value of the _EVENT-NOTIFICATION-ENABLED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean get_eventNotificationEnabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_EVENT_NOTIFICATION_ENABLED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- _LISTENERS
   * @param _listeners new value to conclude for _LISTENERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_listeners(com.gensym.util.Structure _listeners) throws G2AccessException {
    setAttributeValue (_LISTENERS_, _listeners);
  }

  /**
   * Generated Property Getter for attribute -- _LISTENERS
   * @return the value of the _LISTENERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Structure get_listeners() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_LISTENERS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _LISTENERS
   * @param _listeners new value to conclude for _LISTENERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_listenersForClass(com.gensym.util.Structure _listeners) throws G2AccessException {
    setStaticAttributeValue (_LISTENERS_FOR_CLASS_, _listeners);
  }

  /**
   * Generated Property Getter for attribute -- _LISTENERS
   * @return the value of the _LISTENERS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Structure get_listenersForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (_LISTENERS_FOR_CLASS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthorsForClass(com.gensym.util.Structure authors) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Structure getAuthorsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
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
  public void setClassNameForClass(com.gensym.util.Symbol className) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_, className);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-NAME
   * @return the value of the CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
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
  public void setDirectSuperiorClassesForClass(com.gensym.util.Sequence directSuperiorClasses) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_, directSuperiorClasses);
  }

  /**
   * Generated Property Getter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @return the value of the DIRECT-SUPERIOR-CLASSES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
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
  public void setClassSpecificAttributesForClass(com.gensym.util.Sequence classSpecificAttributes) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_, classSpecificAttributes);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @return the value of the CLASS-SPECIFIC-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getClassSpecificAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-RESTRICTIONS
   * @return the value of the CLASS-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
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
  public void setInstanceConfigurationForClass(com.gensym.util.Sequence instanceConfiguration) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_, instanceConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- INSTANCE-CONFIGURATION
   * @return the value of the INSTANCE-CONFIGURATION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getInstanceConfigurationForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getChangeForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INSTANTIATE
   * @param instantiate new value to conclude for INSTANTIATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInstantiateForClass(boolean instantiate) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INSTANTIATE_, new Boolean (instantiate));
  }

  /**
   * Generated Property Getter for attribute -- INSTANTIATE
   * @return the value of the INSTANTIATE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getInstantiateForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANTIATE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- INCLUDE-IN-MENUS
   * @param includeInMenus new value to conclude for INCLUDE-IN-MENUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIncludeInMenusForClass(boolean includeInMenus) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INCLUDE_IN_MENUS_, new Boolean (includeInMenus));
  }

  /**
   * Generated Property Getter for attribute -- INCLUDE-IN-MENUS
   * @return the value of the INCLUDE-IN-MENUS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getIncludeInMenusForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INCLUDE_IN_MENUS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- CLASS-INHERITANCE-PATH
   * @return the value of the CLASS-INHERITANCE-PATH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getClassInheritancePathForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_INHERITANCE_PATH_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INHERITED-ATTRIBUTES
   * @return the value of the INHERITED-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getInheritedAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INHERITED_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INITIALIZABLE-SYSTEM-ATTRIBUTES
   * @return the value of the INITIALIZABLE-SYSTEM-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
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
  public void setAttributeInitializationsForClass(com.gensym.util.Sequence attributeInitializations) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_, attributeInitializations);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @return the value of the ATTRIBUTE-INITIALIZATIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getAttributeInitializationsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ICON-DESCRIPTION
   * @param iconDescription new value to conclude for ICON-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIconDescriptionForClass(com.gensym.util.Structure iconDescription) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ICON_DESCRIPTION_, iconDescription);
  }

  /**
   * Generated Property Getter for attribute -- ICON-DESCRIPTION
   * @return the value of the ICON-DESCRIPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Structure getIconDescriptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ICON_DESCRIPTION_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CLASS
   * @return the value of the SUPERIOR-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getSuperiorClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SUPERIOR_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CAPABILITIES-AND-RESTRICTIONS
   * @return the value of the CAPABILITIES-AND-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getCapabilitiesAndRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CAPABILITIES_AND_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTES-SPECIFIC-TO-CLASS
   * @return the value of the ATTRIBUTES-SPECIFIC-TO-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getAttributesSpecificToClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTES_SPECIFIC_TO_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- MENU-OPTION
   * @return the value of the MENU-OPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getMenuOptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.MENU_OPTION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-DESCRIPTION
   * @param classDescription new value to conclude for CLASS-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassDescriptionForClass(java.lang.String classDescription) throws G2AccessException {
    setStaticAttributeValue (CLASS_DESCRIPTION_FOR_CLASS_, classDescription);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-DESCRIPTION
   * @return the value of the CLASS-DESCRIPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getClassDescriptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (CLASS_DESCRIPTION_FOR_CLASS_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INSTANCE-KEY-ATTRIBUTE-NAME
   * @param instanceKeyAttributeName new value to conclude for INSTANCE-KEY-ATTRIBUTE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInstanceKeyAttributeNameForClass(com.gensym.util.Symbol instanceKeyAttributeName) throws G2AccessException {
    setStaticAttributeValue (INSTANCE_KEY_ATTRIBUTE_NAME_FOR_CLASS_, instanceKeyAttributeName);
  }

  /**
   * Generated Property Getter for attribute -- INSTANCE-KEY-ATTRIBUTE-NAME
   * @return the value of the INSTANCE-KEY-ATTRIBUTE-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getInstanceKeyAttributeNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (INSTANCE_KEY_ATTRIBUTE_NAME_FOR_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-ATTRIBUTE-PROPERTIES
   * @param classAttributeProperties new value to conclude for CLASS-ATTRIBUTE-PROPERTIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassAttributePropertiesForClass(com.gensym.util.Sequence classAttributeProperties) throws G2AccessException {
    setStaticAttributeValue (CLASS_ATTRIBUTE_PROPERTIES_FOR_CLASS_, classAttributeProperties);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-ATTRIBUTE-PROPERTIES
   * @return the value of the CLASS-ATTRIBUTE-PROPERTIES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getClassAttributePropertiesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (CLASS_ATTRIBUTE_PROPERTIES_FOR_CLASS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-EVENTS-DESCRIPTION
   * @param classEventsDescription new value to conclude for CLASS-EVENTS-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassEventsDescriptionForClass(com.gensym.util.Sequence classEventsDescription) throws G2AccessException {
    setStaticAttributeValue (CLASS_EVENTS_DESCRIPTION_FOR_CLASS_, classEventsDescription);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-EVENTS-DESCRIPTION
   * @return the value of the CLASS-EVENTS-DESCRIPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getClassEventsDescriptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (CLASS_EVENTS_DESCRIPTION_FOR_CLASS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GRTL_DISPATCH_EVENT$GRTL_EVENT_SOURCE_ = Symbol.intern ("GRTL-EVENT-SOURCE::GRTL-DISPATCH-EVENT");
  private static final Symbol MethodName_GRTL_ADD_EVENT_LISTENER$GRTL_EVENT_SOURCE_ = Symbol.intern ("GRTL-EVENT-SOURCE::GRTL-ADD-EVENT-LISTENER");
  private static final Symbol MethodName_GRTL_REMOVE_EVENT_LISTENER$GRTL_EVENT_SOURCE_ = Symbol.intern ("GRTL-EVENT-SOURCE::GRTL-REMOVE-EVENT-LISTENER");
  private static final Symbol MethodName_GRTL_REMOVE_ALL_EVENT_LISTENERS$GRTL_EVENT_SOURCE_ = Symbol.intern ("GRTL-EVENT-SOURCE::GRTL-REMOVE-ALL-EVENT-LISTENERS");
  private static final Symbol MethodName_GRTL_ENABLE_EVENT_NOTIFICATION$GRTL_EVENT_SOURCE_ = Symbol.intern ("GRTL-EVENT-SOURCE::GRTL-ENABLE-EVENT-NOTIFICATION");
  private static final Symbol MethodName_GRTL_DISABLE_EVENT_NOTIFICATION$GRTL_EVENT_SOURCE_ = Symbol.intern ("GRTL-EVENT-SOURCE::GRTL-DISABLE-EVENT-NOTIFICATION");
  private static final Symbol MethodName_GRTL_IS_EVENT_NOTIFICATION_ENABLED$GRTL_EVENT_SOURCE_ = Symbol.intern ("GRTL-EVENT-SOURCE::GRTL-IS-EVENT-NOTIFICATION-ENABLED");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-DISPATCH-EVENT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE,arg1:SYMBOL,arg2:SEQUENCE) = ()
   */
  public  void grtlDispatchEvent(com.gensym.util.Symbol arg1,com.gensym.util.Sequence arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_GRTL_DISPATCH_EVENT$GRTL_EVENT_SOURCE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-ADD-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE,arg1:ITEM-OR-VALUE,arg2:TRUTH-VALUE,arg3:TEXT,arg4:SEQUENCE) = ()
   */
  public  void grtlAddEventListener(java.lang.Object arg1,boolean arg2,java.lang.String arg3,com.gensym.util.Sequence arg4) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,new Boolean (arg2),arg3,arg4};
      result = (java.lang.Object)callRPC(MethodName_GRTL_ADD_EVENT_LISTENER$GRTL_EVENT_SOURCE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-REMOVE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE,arg1:ITEM-OR-VALUE,arg2:TRUTH-VALUE,arg3:TEXT) = ()
   */
  public  void grtlRemoveEventListener(java.lang.Object arg1,boolean arg2,java.lang.String arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,new Boolean (arg2),arg3};
      result = (java.lang.Object)callRPC(MethodName_GRTL_REMOVE_EVENT_LISTENER$GRTL_EVENT_SOURCE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-REMOVE-ALL-EVENT-LISTENERS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE) = ()
   */
  public  void grtlRemoveAllEventListeners() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GRTL_REMOVE_ALL_EVENT_LISTENERS$GRTL_EVENT_SOURCE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-ENABLE-EVENT-NOTIFICATION
   * @return the return from calling GRTL-ENABLE-EVENT-NOTIFICATION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE) = (TRUTH-VALUE)
   */
  public  boolean grtlEnableEventNotification() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GRTL_ENABLE_EVENT_NOTIFICATION$GRTL_EVENT_SOURCE_, args);
      return ((Boolean)result).booleanValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-DISABLE-EVENT-NOTIFICATION
   * @return the return from calling GRTL-DISABLE-EVENT-NOTIFICATION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE) = (TRUTH-VALUE)
   */
  public  boolean grtlDisableEventNotification() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GRTL_DISABLE_EVENT_NOTIFICATION$GRTL_EVENT_SOURCE_, args);
      return ((Boolean)result).booleanValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-IS-EVENT-NOTIFICATION-ENABLED
   * @return the return from calling GRTL-IS-EVENT-NOTIFICATION-ENABLED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE) = (TRUTH-VALUE)
   */
  public  boolean grtlIsEventNotificationEnabled() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GRTL_IS_EVENT_NOTIFICATION_ENABLED$GRTL_EVENT_SOURCE_, args);
      return ((Boolean)result).booleanValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
