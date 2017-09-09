/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MessageDefinition.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:33 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface MessageDefinition extends com.gensym.classes.ClassDefinition {

  public static final Symbol MESSAGE_DEFINITION_ = com.gensym.util.symbol.G2ClassSymbols.MESSAGE_DEFINITION_;
  static final Symbol g2ClassName = MESSAGE_DEFINITION_;
  static final Symbol[] classInheritancePath = new Symbol[] {MESSAGE_DEFINITION_, CLASS_DEFINITION_, DEFINITION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- DEFAULT-MESSAGE-PROPERTIES
   * @return the value of the DEFAULT-MESSAGE-PROPERTIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-MESSAGE-PROPERTIES is : 
   * (OR NoItem
      (Structure 
        MESSAGE-TEXT-COLOR
          (OR NoItem
              Symbol)
        MESSAGE-BACKGROUND-COLOR
          (OR NoItem
              Symbol)
        MESSAGE-BORDER-COLOR
          (OR NoItem
              Symbol)
        MESSAGE-MINIMUM-WIDTH
          (OR NoItem
              Integer)
        MESSAGE-MINIMUM-HEIGHT
          (OR NoItem
              Integer)
        MESSAGE-FONT
          (OR NoItem
              (MEMBER SMALL LARGE EXTRA-LARGE))
        MESSAGE-TEXT-ALIGNMENT
          (OR NoItem
              (MEMBER LEFT CENTER RIGHT))))
   *
   */
  public com.gensym.util.Structure getDefaultMessageProperties() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-MESSAGE-PROPERTIES
   * @param defaultMessageProperties new value to conclude for DEFAULT-MESSAGE-PROPERTIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultMessageProperties(com.gensym.util.Structure defaultMessageProperties) throws G2AccessException;

}
