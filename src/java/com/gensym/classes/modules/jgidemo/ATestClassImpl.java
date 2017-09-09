/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ATestClassImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:49:19 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ATestClassImpl extends com.gensym.classes.ObjectImpl implements ATestClass {


  static final long serialVersionUID = 2L;
  private static final Symbol A_INT_ = Symbol.intern ("A-INT");
  private static final Symbol A_FLOAT_ = Symbol.intern ("A-FLOAT");
  private static final Symbol A_TEXT_ = Symbol.intern ("A-TEXT");
  private static final Symbol A_SYMBOL_ = Symbol.intern ("A-SYMBOL");
  private static final Symbol A_THRUTH_VALUE_ = Symbol.intern ("A-THRUTH-VALUE");
  private static final Symbol A_SEQUENCE_ = Symbol.intern ("A-SEQUENCE");
  private static final Symbol A_STRUCTURE_ = Symbol.intern ("A-STRUCTURE");

  /* Generated constructors */

  public ATestClassImpl() {
    super();
  }

  public ATestClassImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ATestClassImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- A-INT
   * @param aInt new value to conclude for A-INT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAInt(int aInt) throws G2AccessException {
    setAttributeValue (A_INT_, aInt);
  }

  /**
   * Generated Property Getter for attribute -- A-INT
   * @return the value of the A-INT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getAInt() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (A_INT_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- A-FLOAT
   * @param aFloat new value to conclude for A-FLOAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAFloat(double aFloat) throws G2AccessException {
    setAttributeValue (A_FLOAT_, aFloat);
  }

  /**
   * Generated Property Getter for attribute -- A-FLOAT
   * @return the value of the A-FLOAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public double getAFloat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (A_FLOAT_);
    return ((Double)retnValue).doubleValue ();
  }

  /**
   * Generated Property Setter for attribute -- A-TEXT
   * @param aText new value to conclude for A-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAText(java.lang.String aText) throws G2AccessException {
    setAttributeValue (A_TEXT_, aText);
  }

  /**
   * Generated Property Getter for attribute -- A-TEXT
   * @return the value of the A-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getAText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (A_TEXT_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- A-SYMBOL
   * @param aSymbol new value to conclude for A-SYMBOL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setASymbol(com.gensym.util.Symbol aSymbol) throws G2AccessException {
    setAttributeValue (A_SYMBOL_, aSymbol);
  }

  /**
   * Generated Property Getter for attribute -- A-SYMBOL
   * @return the value of the A-SYMBOL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getASymbol() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (A_SYMBOL_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- A-THRUTH-VALUE
   * @param aThruthValue new value to conclude for A-THRUTH-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAThruthValue(boolean aThruthValue) throws G2AccessException {
    setAttributeValue (A_THRUTH_VALUE_, new Boolean (aThruthValue));
  }

  /**
   * Generated Property Getter for attribute -- A-THRUTH-VALUE
   * @return the value of the A-THRUTH-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getAThruthValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (A_THRUTH_VALUE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- A-SEQUENCE
   * @param aSequence new value to conclude for A-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setASequence(com.gensym.util.Sequence aSequence) throws G2AccessException {
    setAttributeValue (A_SEQUENCE_, aSequence);
  }

  /**
   * Generated Property Getter for attribute -- A-SEQUENCE
   * @return the value of the A-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getASequence() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (A_SEQUENCE_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- A-STRUCTURE
   * @param aStructure new value to conclude for A-STRUCTURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAStructure(com.gensym.util.Structure aStructure) throws G2AccessException {
    setAttributeValue (A_STRUCTURE_, aStructure);
  }

  /**
   * Generated Property Getter for attribute -- A-STRUCTURE
   * @return the value of the A-STRUCTURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAStructure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (A_STRUCTURE_);
    return (com.gensym.util.Structure)retnValue;
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
  public com.gensym.util.Sequence getChangeLogForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (com.gensym.util.Sequence)retnValue;
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
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_, attributeDisplays);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAttributeDisplaysForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.STUBS_, stubs);
  }

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getStubsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.STUBS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DEFAULT_SETTINGS_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_TEST_METHOD_ = Symbol.intern ("TEST-METHOD");
  private static final Symbol MethodName_A_TEST_METHOD_VARARG_ = Symbol.intern ("A-TEST-METHOD-VARARG");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * A-TEST-CLASS::TEST-METHOD
   * @return the return from calling TEST-METHOD
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS A-TEST-CLASS,arg1:VALUE) = (VALUE)
   */
  @Override
  public  java.lang.Object testMethod(java.lang.Object arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_TEST_METHOD_, args);
      return (java.lang.Object)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * A-TEST-CLASS::A-TEST-METHOD-VARARG
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS A-TEST-CLASS,arg1:ITEM-OR-VALUE) = ()
   */
  @Override
  public  void aTestMethodVararg(java.lang.Object arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_A_TEST_METHOD_VARARG_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * A-TEST-CLASS::A-TEST-METHOD-VARARG
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS A-TEST-CLASS,arg1:ITEM-OR-VALUE,arg2:ITEM-OR-VALUE) = ()
   */
  @Override
  public  void aTestMethodVararg(java.lang.Object arg1,java.lang.Object arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_A_TEST_METHOD_VARARG_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
