/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ObjectDefinition.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:31 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ObjectDefinition extends com.gensym.classes.ClassDefinition {

  public static final Symbol OBJECT_DEFINITION_ = com.gensym.util.symbol.G2ClassSymbols.OBJECT_DEFINITION_;
  static final Symbol g2ClassName = OBJECT_DEFINITION_;
  static final Symbol[] classInheritancePath = new Symbol[] {OBJECT_DEFINITION_, CLASS_DEFINITION_, DEFINITION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this item
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
  public java.lang.Object getAttributeDisplays() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplays(java.lang.Object attributeDisplays) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this item
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
  public java.lang.Object getStubs() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStubs(java.lang.Object stubs) throws G2AccessException;

}
