/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilGrmes.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:56 EDT 2007
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

public interface UilGrmes extends com.gensym.classes.modules.uilroot.UilMessage {

  public static final Symbol UIL_GRMES_ = Symbol.intern ("UIL-GRMES");
  static final Symbol g2ClassName = UIL_GRMES_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_GRMES_, UIL_MESSAGE_, MESSAGE_, ITEM_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-IS-MANAGED
   * @return the value of the UIL-IS-MANAGED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-IS-MANAGED is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilIsManaged() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-IS-MANAGED
   * @param uilIsManaged new value to conclude for UIL-IS-MANAGED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilIsManaged(java.lang.Object uilIsManaged) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-IS-PERMANENT
   * @return the value of the UIL-IS-PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-IS-PERMANENT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilIsPermanent() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-IS-PERMANENT
   * @param uilIsPermanent new value to conclude for UIL-IS-PERMANENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilIsPermanent(java.lang.Object uilIsPermanent) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ID
   * @return the value of the ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ID
   * @param id new value to conclude for ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setId(java.lang.Object id) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONFIGURATION
   * @return the value of the CONFIGURATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONFIGURATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getConfiguration() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CONFIGURATION
   * @param configuration new value to conclude for CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setConfiguration(java.lang.Object configuration) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CONFIGURATION-METHOD
   * @return the value of the UIL-CONFIGURATION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CONFIGURATION-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilConfigurationMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CONFIGURATION-METHOD
   * @param uilConfigurationMethod new value to conclude for UIL-CONFIGURATION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilConfigurationMethod(java.lang.Object uilConfigurationMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MAXIMUM-CHARACTERS-TO-DISPLAY
   * @return the value of the UIL-MAXIMUM-CHARACTERS-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MAXIMUM-CHARACTERS-TO-DISPLAY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMaximumCharactersToDisplay() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MAXIMUM-CHARACTERS-TO-DISPLAY
   * @param uilMaximumCharactersToDisplay new value to conclude for UIL-MAXIMUM-CHARACTERS-TO-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMaximumCharactersToDisplay(java.lang.Object uilMaximumCharactersToDisplay) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-INITIALIZATION-METHOD
   * @return the value of the UIL-INITIALIZATION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-INITIALIZATION-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilInitializationMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-INITIALIZATION-METHOD
   * @param uilInitializationMethod new value to conclude for UIL-INITIALIZATION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilInitializationMethod(java.lang.Object uilInitializationMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ENABLE-METHOD
   * @return the value of the UIL-ENABLE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ENABLE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEnableMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ENABLE-METHOD
   * @param uilEnableMethod new value to conclude for UIL-ENABLE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEnableMethod(java.lang.Object uilEnableMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DISABLE-METHOD
   * @return the value of the UIL-DISABLE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DISABLE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDisableMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DISABLE-METHOD
   * @param uilDisableMethod new value to conclude for UIL-DISABLE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDisableMethod(java.lang.Object uilDisableMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SIZE-OF-METHOD
   * @return the value of the UIL-SIZE-OF-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SIZE-OF-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSizeOfMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SIZE-OF-METHOD
   * @param uilSizeOfMethod new value to conclude for UIL-SIZE-OF-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSizeOfMethod(java.lang.Object uilSizeOfMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SIZE
   * @return the value of the UIL-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SIZE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSize() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SIZE
   * @param uilSize new value to conclude for UIL-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSize(java.lang.Object uilSize) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- USER-DATA
   * @return the value of the USER-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for USER-DATA is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUserData() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- USER-DATA
   * @param userData new value to conclude for USER-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUserData(java.lang.Object userData) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CLONE-METHOD
   * @return the value of the UIL-CLONE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CLONE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilCloneMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CLONE-METHOD
   * @param uilCloneMethod new value to conclude for UIL-CLONE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilCloneMethod(java.lang.Object uilCloneMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MANAGE-METHOD
   * @return the value of the UIL-MANAGE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MANAGE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilManageMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MANAGE-METHOD
   * @param uilManageMethod new value to conclude for UIL-MANAGE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilManageMethod(java.lang.Object uilManageMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CONCLUDE-VALUE-IMMEDIATELY
   * @return the value of the UIL-CONCLUDE-VALUE-IMMEDIATELY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CONCLUDE-VALUE-IMMEDIATELY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilConcludeValueImmediately() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CONCLUDE-VALUE-IMMEDIATELY
   * @param uilConcludeValueImmediately new value to conclude for UIL-CONCLUDE-VALUE-IMMEDIATELY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilConcludeValueImmediately(java.lang.Object uilConcludeValueImmediately) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-EVENT-TARGET-OBJECT
   * @return the value of the UIL-EVENT-TARGET-OBJECT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-EVENT-TARGET-OBJECT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEventTargetObject() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-EVENT-TARGET-OBJECT
   * @param uilEventTargetObject new value to conclude for UIL-EVENT-TARGET-OBJECT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEventTargetObject(java.lang.Object uilEventTargetObject) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-EVENT-TARGET-ATTRIBUTE
   * @return the value of the UIL-EVENT-TARGET-ATTRIBUTE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-EVENT-TARGET-ATTRIBUTE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEventTargetAttribute() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-EVENT-TARGET-ATTRIBUTE
   * @param uilEventTargetAttribute new value to conclude for UIL-EVENT-TARGET-ATTRIBUTE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEventTargetAttribute(java.lang.Object uilEventTargetAttribute) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-EVENT-SOURCE-OBJECT
   * @return the value of the UIL-EVENT-SOURCE-OBJECT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-EVENT-SOURCE-OBJECT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEventSourceObject() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-EVENT-SOURCE-OBJECT
   * @param uilEventSourceObject new value to conclude for UIL-EVENT-SOURCE-OBJECT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEventSourceObject(java.lang.Object uilEventSourceObject) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-EVENT-SOURCE-ATTRIBUTE
   * @return the value of the UIL-EVENT-SOURCE-ATTRIBUTE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-EVENT-SOURCE-ATTRIBUTE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEventSourceAttribute() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-EVENT-SOURCE-ATTRIBUTE
   * @param uilEventSourceAttribute new value to conclude for UIL-EVENT-SOURCE-ATTRIBUTE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEventSourceAttribute(java.lang.Object uilEventSourceAttribute) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BOX-WIDTH
   * @return the value of the UIL-BOX-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BOX-WIDTH is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBoxWidth() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BOX-WIDTH
   * @param uilBoxWidth new value to conclude for UIL-BOX-WIDTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBoxWidth(java.lang.Object uilBoxWidth) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-METHOD
   * @return the value of the UIL-UPDATE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-UPDATE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUpdateMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-METHOD
   * @param uilUpdateMethod new value to conclude for UIL-UPDATE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUpdateMethod(java.lang.Object uilUpdateMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DELETE-METHOD
   * @return the value of the UIL-DELETE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DELETE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDeleteMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DELETE-METHOD
   * @param uilDeleteMethod new value to conclude for UIL-DELETE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDeleteMethod(java.lang.Object uilDeleteMethod) throws G2AccessException;

}
