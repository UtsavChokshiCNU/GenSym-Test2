/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GsiLogicalClass.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:52:39 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GsiLogicalClass extends com.gensym.classes.GsiMessageService, com.gensym.classes.GsiDataService, com.gensym.classes.LogicalVariable, com.gensym.classes.modules.jgidemo.IdentAttsClass {

  public static final Symbol GSI_LOGICAL_CLASS_ = Symbol.intern ("GSI-LOGICAL-CLASS");
  static final Symbol g2ClassName = GSI_LOGICAL_CLASS_;
  static final Symbol[] classInheritancePath = new Symbol[] {GSI_LOGICAL_CLASS_, GSI_MESSAGE_SERVICE_, GSI_DATA_SERVICE_, LOGICAL_VARIABLE_, G2_VARIABLE_, VARIABLE_, VARIABLE_OR_PARAMETER_, IDENT_ATTS_CLASS_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol ATTRIBUTE_DISPLAYS_ = Symbol.intern ("ATTRIBUTE-DISPLAYS");
  static final Symbol STUBS_ = Symbol.intern ("STUBS");
  static final Symbol DEFAULT_SETTINGS_ = Symbol.intern ("DEFAULT-SETTINGS");

  static final Symbol[] staticAttributes = new Symbol[] {ATTRIBUTE_DISPLAYS_, STUBS_, DEFAULT_SETTINGS_};


  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ATTRIBUTE-DISPLAYS is : 
   * (OR NoItem
      (MEMBER INHERITED)
      (Sequence 
        (Structure 
          ATTRIBUTE-LIST
            (Sequence 
              (Structure 
                ATTRIBUTE Symbol
                QUALIFIED-CLASS Symbol
                DISPLAY-WITH-NAME BooleanTruthValue)
              1))
          POSITION
            (OR (MEMBER AT-STANDARD-POSITION)
                (Structure 
                  X-OFFSET Integer
                  Y-OFFSET Integer)))
        1)))
   *
   */
  public java.lang.Object getAttributeDisplaysForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STUBS is : 
   * (OR NoItem
      (MEMBER INHERITED)
      (Sequence 
        (Structure 
          PORTNAME Symbol
          CONNECTION-CLASS Symbol
          STUB-DIRECTION
            (MEMBER INPUT OUTPUT)
          EDGE-LOCATION
            (MEMBER TOP BOTTOM RIGHT LEFT)
          COORDINATE-LOCATION Integer
          STYLE
            (MEMBER DIAGONAL ORTHOGONAL)
          CONNECTION-ARROWS
            (OR NoItem
                (MEMBER DEFAULT NONE ARROW TRIANGLE DIAMOND CIRCLE)
                (Sequence 
                  (Structure 
                    SHAPE
                      (MEMBER ARROW TRIANGLE DIAMOND CIRCLE)
                    FILLED BooleanTruthValue
                    SCALE Float
                    ASPECT-RATIO Float
                    LINE-WEIGHT Float
                    PLACEMENT
                      (MEMBER DEFAULT OUTPUT INPUT BOTH)))))
          LINE-PATTERN
            (OR NoItem
                (MEMBER SOLID DASH DOT LONG-DASH SHORT-DASH COARSE-DOT FINE-DOT)
                (Sequence Symbol 1)
                (Sequence Integer 1)
                (Structure 
                  PATTERN
                    (Sequence Integer 1)
                  NOT-SCALED-BY-LINE-WIDTH BooleanTruthValue)))
        1)))
   *
   */
  public java.lang.Object getStubsForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute DEFAULT-SETTINGS has no type
   *
   */
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException;

}
