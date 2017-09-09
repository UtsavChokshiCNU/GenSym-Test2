/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GfrTextResourceGroupImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:08:52 EDT 2007
 *
 */


package com.gensym.classes.modules.gfr;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GfrTextResourceGroupImpl extends com.gensym.classes.ObjectImpl implements GfrTextResourceGroup {


  static final long serialVersionUID = 2L;
  private static final Symbol GFR_VERSION_ = Symbol.intern ("GFR-VERSION");
  private static final Symbol GFR_DEFAULT_LANGUAGE_ = Symbol.intern ("GFR-DEFAULT-LANGUAGE");
  private static final Symbol GFR_USE_DEFAULT_LANGUAGE_ = Symbol.intern ("GFR-USE-DEFAULT-LANGUAGE");

  /* Generated constructors */

  public GfrTextResourceGroupImpl() {
    super();
  }

  public GfrTextResourceGroupImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GfrTextResourceGroupImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GFR-VERSION
   * @param gfrVersion new value to conclude for GFR-VERSION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfrVersion(java.lang.String gfrVersion) throws G2AccessException {
    setAttributeValue (GFR_VERSION_, gfrVersion);
  }

  /**
   * Generated Property Getter for attribute -- GFR-VERSION
   * @return the value of the GFR-VERSION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getGfrVersion() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GFR_VERSION_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFR-DEFAULT-LANGUAGE
   * @param gfrDefaultLanguage new value to conclude for GFR-DEFAULT-LANGUAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfrDefaultLanguage(com.gensym.util.Symbol gfrDefaultLanguage) throws G2AccessException {
    setAttributeValue (GFR_DEFAULT_LANGUAGE_, gfrDefaultLanguage);
  }

  /**
   * Generated Property Getter for attribute -- GFR-DEFAULT-LANGUAGE
   * @return the value of the GFR-DEFAULT-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGfrDefaultLanguage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GFR_DEFAULT_LANGUAGE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFR-USE-DEFAULT-LANGUAGE
   * @param gfrUseDefaultLanguage new value to conclude for GFR-USE-DEFAULT-LANGUAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfrUseDefaultLanguage(boolean gfrUseDefaultLanguage) throws G2AccessException {
    setAttributeValue (GFR_USE_DEFAULT_LANGUAGE_, new Boolean (gfrUseDefaultLanguage));
  }

  /**
   * Generated Property Getter for attribute -- GFR-USE-DEFAULT-LANGUAGE
   * @return the value of the GFR-USE-DEFAULT-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getGfrUseDefaultLanguage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GFR_USE_DEFAULT_LANGUAGE_);
    return ((Boolean)retnValue).booleanValue ();
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
  private static final Symbol MethodName_GFR_LOCALIZE_MESSAGE_ = Symbol.intern ("GFR-LOCALIZE-MESSAGE");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,com.gensym.classes.Object arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,com.gensym.classes.Object arg4) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,com.gensym.classes.Object arg5) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:VALUE,arg6:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,java.lang.Object arg5,com.gensym.classes.Object arg6) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5,arg6};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:VALUE,arg6:VALUE,arg7:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,java.lang.Object arg5,java.lang.Object arg6,com.gensym.classes.Object arg7) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5,arg6,arg7};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:VALUE,arg6:VALUE,arg7:VALUE,arg8:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,java.lang.Object arg5,java.lang.Object arg6,java.lang.Object arg7,com.gensym.classes.Object arg8) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:VALUE,arg6:VALUE,arg7:VALUE,arg8:VALUE,arg9:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,java.lang.Object arg5,java.lang.Object arg6,java.lang.Object arg7,java.lang.Object arg8,com.gensym.classes.Object arg9) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:VALUE,arg6:VALUE,arg7:VALUE,arg8:VALUE,arg9:VALUE,arg10:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,java.lang.Object arg5,java.lang.Object arg6,java.lang.Object arg7,java.lang.Object arg8,java.lang.Object arg9,com.gensym.classes.Object arg10) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:VALUE,arg6:VALUE,arg7:VALUE,arg8:VALUE,arg9:VALUE,arg10:VALUE,arg11:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,java.lang.Object arg5,java.lang.Object arg6,java.lang.Object arg7,java.lang.Object arg8,java.lang.Object arg9,java.lang.Object arg10,com.gensym.classes.Object arg11) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:VALUE,arg6:VALUE,arg7:VALUE,arg8:VALUE,arg9:VALUE,arg10:VALUE,arg11:VALUE,arg12:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,java.lang.Object arg5,java.lang.Object arg6,java.lang.Object arg7,java.lang.Object arg8,java.lang.Object arg9,java.lang.Object arg10,java.lang.Object arg11,com.gensym.classes.Object arg12) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GFR-TEXT-RESOURCE-GROUP::GFR-LOCALIZE-MESSAGE
   * @return the return from calling GFR-LOCALIZE-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GFR-TEXT-RESOURCE-GROUP,arg1:SYMBOL,arg2:SYMBOL,arg3:VALUE,arg4:VALUE,arg5:VALUE,arg6:VALUE,arg7:VALUE,arg8:VALUE,arg9:VALUE,arg10:VALUE,arg11:VALUE,arg12:VALUE,arg13:CLASS OBJECT) = (TEXT)
   */
  @Override
  public  java.lang.String gfrLocalizeMessage(com.gensym.util.Symbol arg1,com.gensym.util.Symbol arg2,java.lang.Object arg3,java.lang.Object arg4,java.lang.Object arg5,java.lang.Object arg6,java.lang.Object arg7,java.lang.Object arg8,java.lang.Object arg9,java.lang.Object arg10,java.lang.Object arg11,java.lang.Object arg12,com.gensym.classes.Object arg13) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13};
      result = (java.lang.Object)callRPC(MethodName_GFR_LOCALIZE_MESSAGE_, args);
      return (java.lang.String)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
