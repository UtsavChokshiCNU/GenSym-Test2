/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TypeInBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:36 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface TypeInBox extends com.gensym.classes.Item, com.gensym.classes.NonActionButton {

  public static final Symbol TYPE_IN_BOX_ = com.gensym.util.symbol.G2ClassSymbols.TYPE_IN_BOX_;
  static final Symbol g2ClassName = TYPE_IN_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {TYPE_IN_BOX_, ITEM_, NON_ACTION_BUTTON_, BUTTON_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- FORMAT-FOR-TYPE-IN-BOX
   * @return the value of the FORMAT-FOR-TYPE-IN-BOX attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FORMAT-FOR-TYPE-IN-BOX is : 
   * (OR (MEMBER DEFAULT INTERVAL TIME-STAMP FREE-TEXT)
      (Structure 
        WHOLE-NUMBER-PRECISION Integer
        FRACTION-PRECISION Integer))
   *
   */
  public java.lang.Object getFormatForTypeInBox() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FORMAT-FOR-TYPE-IN-BOX
   * @param formatForTypeInBox new value to conclude for FORMAT-FOR-TYPE-IN-BOX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFormatForTypeInBox(java.lang.Object formatForTypeInBox) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BLANK-FOR-TYPE-IN?
   * @return the value of the BLANK-FOR-TYPE-IN? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BLANK-FOR-TYPE-IN? is : 
   * BooleanTruthValue
   *
   */
  public boolean getBlankForTypeIn() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BLANK-FOR-TYPE-IN?
   * @param blankForTypeIn new value to conclude for BLANK-FOR-TYPE-IN?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBlankForTypeIn(boolean blankForTypeIn) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HAVE-EDIT-OPTION-BUTTONS-FOR-TYPE-IN?
   * @return the value of the HAVE-EDIT-OPTION-BUTTONS-FOR-TYPE-IN? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HAVE-EDIT-OPTION-BUTTONS-FOR-TYPE-IN? is : 
   * BooleanTruthValue
   *
   */
  public boolean getHaveEditOptionButtonsForTypeIn() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- HAVE-EDIT-OPTION-BUTTONS-FOR-TYPE-IN?
   * @param haveEditOptionButtonsForTypeIn new value to conclude for HAVE-EDIT-OPTION-BUTTONS-FOR-TYPE-IN?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setHaveEditOptionButtonsForTypeIn(boolean haveEditOptionButtonsForTypeIn) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-PROMPTS-FOR-TYPE-IN
   * @return the value of the SHOW-PROMPTS-FOR-TYPE-IN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-PROMPTS-FOR-TYPE-IN is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowPromptsForTypeIn() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-PROMPTS-FOR-TYPE-IN
   * @param showPromptsForTypeIn new value to conclude for SHOW-PROMPTS-FOR-TYPE-IN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowPromptsForTypeIn(boolean showPromptsForTypeIn) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TYPE-IN-BOX-VARIABLE-OR-PARAMETER
   * @return the value of the TYPE-IN-BOX-VARIABLE-OR-PARAMETER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TYPE-IN-BOX-VARIABLE-OR-PARAMETER is : 
   * (OR Value
      NoItem)
   *
   */
  public java.lang.Object getTypeInBoxVariableOrParameter() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TYPE-IN-BOX-VALUE
   * @return the value of the TYPE-IN-BOX-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TYPE-IN-BOX-VALUE is : 
   * (OR Symbol
      Text
      Quantity
      BooleanTruthValue)
   *
   */
  public java.lang.Object getTypeInBoxValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TYPE-IN-BOX-VALUE
   * @param typeInBoxValue new value to conclude for TYPE-IN-BOX-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTypeInBoxValue(java.lang.Object typeInBoxValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MINIMUM-SIZE-IN-WORKSPACE
   * @return the value of the MINIMUM-SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MINIMUM-SIZE-IN-WORKSPACE is : 
   * (OR NoItem
      (Structure 
        WIDTH
          (OR Integer
              (MEMBER NONE))
        HEIGHT
          (OR Integer
              (MEMBER NONE))))
   *
   */
  public com.gensym.util.Structure getMinimumSizeInWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MINIMUM-SIZE-IN-WORKSPACE
   * @param minimumSizeInWorkspace new value to conclude for MINIMUM-SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMinimumSizeInWorkspace(com.gensym.util.Structure minimumSizeInWorkspace) throws G2AccessException;

}
