/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqmEntryImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:46:07 EDT 2000
 *
 */


package com.gensym.classes.modules.gqm;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GqmEntryImpl extends com.gensym.classes.ObjectImpl implements GqmEntry {


  static final long serialVersionUID = 2L;
  private static final Symbol GQM_COMMENTS_ = Symbol.intern ("GQM-COMMENTS");
  private static final Symbol GQM_MESSAGE_TEXT_ = Symbol.intern ("GQM-MESSAGE-TEXT");
  private static final Symbol GQM_CREATION_TIME_ = Symbol.intern ("GQM-CREATION-TIME");
  private static final Symbol GQM_PRIORITY_ = Symbol.intern ("GQM-PRIORITY");

  /* Generated constructors */

  public GqmEntryImpl() {
    super();
  }

  public GqmEntryImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GQM-COMMENTS
   * @param gqmComments new value to conclude for GQM-COMMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmComments(com.gensym.classes.TextArray gqmComments) throws G2AccessException {
    setAttributeValue (GQM_COMMENTS_, gqmComments);
  }

  /**
   * Generated Property Getter for attribute -- GQM-COMMENTS
   * @return the value of the GQM-COMMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.TextArray getGqmComments() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_COMMENTS_);
    return (com.gensym.classes.TextArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GQM-MESSAGE-TEXT
   * @param gqmMessageText new value to conclude for GQM-MESSAGE-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmMessageText(java.lang.String gqmMessageText) throws G2AccessException {
    setAttributeValue (GQM_MESSAGE_TEXT_, gqmMessageText);
  }

  /**
   * Generated Property Getter for attribute -- GQM-MESSAGE-TEXT
   * @return the value of the GQM-MESSAGE-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getGqmMessageText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_MESSAGE_TEXT_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GQM-CREATION-TIME
   * @param gqmCreationTime new value to conclude for GQM-CREATION-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmCreationTime(double gqmCreationTime) throws G2AccessException {
    setAttributeValue (GQM_CREATION_TIME_, new Double (gqmCreationTime));
  }

  /**
   * Generated Property Getter for attribute -- GQM-CREATION-TIME
   * @return the value of the GQM-CREATION-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public double getGqmCreationTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_CREATION_TIME_);
    return ((Double)retnValue).doubleValue ();
  }

  /**
   * Generated Property Setter for attribute -- GQM-PRIORITY
   * @param gqmPriority new value to conclude for GQM-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmPriority(int gqmPriority) throws G2AccessException {
    setAttributeValue (GQM_PRIORITY_, new Integer (gqmPriority));
  }

  /**
   * Generated Property Getter for attribute -- GQM-PRIORITY
   * @return the value of the GQM-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getGqmPriority() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_PRIORITY_);
    return ((Integer)retnValue).intValue ();
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
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
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
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_, attributeDisplays);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
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
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.STUBS_, stubs);
  }

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getStubsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.STUBS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DEFAULT_SETTINGS_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GQM_ENTRY_CONSTRUCTOR_ = Symbol.intern ("GQM-ENTRY-CONSTRUCTOR");
  private static final Symbol MethodName_GQM_EXPIRE_ENTRY_ = Symbol.intern ("GQM-EXPIRE-ENTRY");
  private static final Symbol MethodName_GQM_LOG_ENTRY_ = Symbol.intern ("GQM-LOG-ENTRY");
  private static final Symbol MethodName_GQM_DELETE_ = Symbol.intern ("GQM-DELETE");
  private static final Symbol MethodName_GQM_SAVE_ENTRY_ = Symbol.intern ("GQM-SAVE-ENTRY");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GQM-ENTRY::GQM-ENTRY-CONSTRUCTOR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-ENTRY,arg1:CLASS GQM-QUEUE,arg2:STRUCTURE,arg3:CLASS OBJECT) = ()
   */
  public  void gqmEntryConstructor(com.gensym.classes.modules.gqm.GqmQueue arg1,com.gensym.util.Structure arg2,com.gensym.classes.Object arg3) throws G2AccessException
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
   * GQM-ENTRY::GQM-EXPIRE-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-ENTRY,arg1:CLASS GQM-QUEUE,arg2:CLASS ITEM,arg3:CLASS OBJECT) = ()
   */
  public  void gqmExpireEntry(com.gensym.classes.modules.gqm.GqmQueue arg1,com.gensym.classes.Item arg2,com.gensym.classes.Object arg3) throws G2AccessException
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
   * GQM-ENTRY::GQM-LOG-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-ENTRY,arg1:CLASS GQM-QUEUE,arg2:CLASS GQM-LOGGING-MANAGER,arg3:CLASS OBJECT) = ()
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
   * GQM-ENTRY::GQM-DELETE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-ENTRY,arg1:CLASS OBJECT) = ()
   */
  public  void gqmDelete(com.gensym.classes.Object arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GQM_DELETE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GQM-ENTRY::GQM-SAVE-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-ENTRY,arg1:CLASS GQM-QUEUE,arg2:TEXT,arg3:CLASS OBJECT) = ()
   */
  public  void gqmSaveEntry(com.gensym.classes.modules.gqm.GqmQueue arg1,java.lang.String arg2,com.gensym.classes.Object arg3) throws G2AccessException
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
  
}
