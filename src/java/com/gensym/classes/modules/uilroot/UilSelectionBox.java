/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSelectionBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:27 EDT 2007
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

public interface UilSelectionBox extends com.gensym.classes.modules.uilroot.UilGrobj {

  public static final Symbol UIL_SELECTION_BOX_ = Symbol.intern ("UIL-SELECTION-BOX");
  static final Symbol g2ClassName = UIL_SELECTION_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_SELECTION_BOX_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-ORIENTATION
   * @return the value of the UIL-BUTTON-ORIENTATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-ORIENTATION is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUilButtonOrientation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-ORIENTATION
   * @param uilButtonOrientation new value to conclude for UIL-BUTTON-ORIENTATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonOrientation(com.gensym.util.Symbol uilButtonOrientation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MEMBERS
   * @return the value of the MEMBERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MEMBERS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMembers() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MEMBERS
   * @param members new value to conclude for MEMBERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMembers(java.lang.Object members) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MEMBERS-INDEX
   * @return the value of the MEMBERS-INDEX attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MEMBERS-INDEX is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMembersIndex() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MEMBERS-INDEX
   * @param membersIndex new value to conclude for MEMBERS-INDEX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMembersIndex(java.lang.Object membersIndex) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-VALUE
   * @return the value of the UIL-UPDATE-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-UPDATE-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUpdateValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-VALUE
   * @param uilUpdateValue new value to conclude for UIL-UPDATE-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUpdateValue(java.lang.Object uilUpdateValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STATE
   * @return the value of the STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getState() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STATE
   * @param state new value to conclude for STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setState(java.lang.Object state) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LABEL
   * @return the value of the LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LABEL is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getLabel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LABEL
   * @param label new value to conclude for LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLabel(java.lang.Object label) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TEXT-RELATION
   * @return the value of the UIL-TEXT-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TEXT-RELATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTextRelation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TEXT-RELATION
   * @param uilTextRelation new value to conclude for UIL-TEXT-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTextRelation(java.lang.Object uilTextRelation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-ID
   * @return the value of the UIL-LABEL-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LABEL-ID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilLabelId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-ID
   * @param uilLabelId new value to conclude for UIL-LABEL-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLabelId(java.lang.Object uilLabelId) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-X-OFFSET
   * @return the value of the UIL-BORDER-X-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BORDER-X-OFFSET is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBorderXOffset() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-X-OFFSET
   * @param uilBorderXOffset new value to conclude for UIL-BORDER-X-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBorderXOffset(java.lang.Object uilBorderXOffset) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-Y-OFFSET
   * @return the value of the UIL-BORDER-Y-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BORDER-Y-OFFSET is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBorderYOffset() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-Y-OFFSET
   * @param uilBorderYOffset new value to conclude for UIL-BORDER-Y-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBorderYOffset(java.lang.Object uilBorderYOffset) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-WIDTH
   * @return the value of the UIL-BORDER-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BORDER-WIDTH is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBorderWidth() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-WIDTH
   * @param uilBorderWidth new value to conclude for UIL-BORDER-WIDTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBorderWidth(java.lang.Object uilBorderWidth) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-HEIGHT
   * @return the value of the UIL-BORDER-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BORDER-HEIGHT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBorderHeight() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-HEIGHT
   * @param uilBorderHeight new value to conclude for UIL-BORDER-HEIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBorderHeight(java.lang.Object uilBorderHeight) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-X-OFFSET
   * @return the value of the UIL-LABEL-X-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LABEL-X-OFFSET is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilLabelXOffset() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-X-OFFSET
   * @param uilLabelXOffset new value to conclude for UIL-LABEL-X-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLabelXOffset(java.lang.Object uilLabelXOffset) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-Y-OFFSET
   * @return the value of the UIL-LABEL-Y-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LABEL-Y-OFFSET is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilLabelYOffset() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-Y-OFFSET
   * @param uilLabelYOffset new value to conclude for UIL-LABEL-Y-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLabelYOffset(java.lang.Object uilLabelYOffset) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-SIZE
   * @return the value of the UIL-LABEL-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LABEL-SIZE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilLabelSize() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-SIZE
   * @param uilLabelSize new value to conclude for UIL-LABEL-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLabelSize(java.lang.Object uilLabelSize) throws G2AccessException;

}
