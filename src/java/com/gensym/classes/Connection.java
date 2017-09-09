/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Connection.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:09 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public interface Connection extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol CONNECTION_ = com.gensym.util.symbol.G2ClassSymbols.CONNECTION_;
  static final Symbol g2ClassName = CONNECTION_;
  static final Symbol[] classInheritancePath = new Symbol[] {CONNECTION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol CROSS_SECTION_PATTERN_ = Symbol.intern ("CROSS-SECTION-PATTERN");
  static final Symbol STUB_LENGTH_ = Symbol.intern ("STUB-LENGTH");
  static final Symbol JUNCTION_BLOCK_CLASS_ = Symbol.intern ("JUNCTION-BLOCK-CLASS");

  static final Symbol[] staticAttributes = new Symbol[] {CROSS_SECTION_PATTERN_, STUB_LENGTH_, JUNCTION_BLOCK_CLASS_};


  /* Overriden Property - CONNECTION-INPUT-AND-OUTPUT */
  /**
   * @return a Sequence of the {InputObject or False, OutputObject or False}
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public Sequence getConnectionInputAndOutput () throws G2AccessException;

  /* Overriden Property - VERTICES-AND-JOIN */
  /**
   * @param otherItemOrStub either the loose end Connection or Entity to
   * which this Connection should be connected.
   * @param makeConnectionMode either MOVING_LOOSE_END_, JOINING_LOOSE_ENDS_,
   * or MAKING_NEW_JUNCTION_BLOCK_;
   * @param connectionPositionSequence a flattend Sequence of the vertices
   * to be set for this connection.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void setVerticesAndJoin(Item otherItemOrStub,
				 Symbol makeConnectionMode,
				 Sequence connectionPositionSequence) throws G2AccessException;

  /* Overriden Property - BOUNDS-FROM-WORKSPACE-EVENT */
  /**
   * @undocumented Used to update the CONNECTION-POSITION-SEQUENCE
   * attribute from a WorkspaceEvent
   */
  public void setBoundsFromWorkspaceEvent (Structure eventInfo);

  /**
   * Generated Property Getter for attribute -- CONNECTION-ARROWS
   * @return the value of the CONNECTION-ARROWS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTION-ARROWS is : 
   * (OR NoItem
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
   *
   */
  public java.lang.Object getConnectionArrows() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CONNECTION-ARROWS
   * @param connectionArrows new value to conclude for CONNECTION-ARROWS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setConnectionArrows(java.lang.Object connectionArrows) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LINE-PATTERN
   * @return the value of the LINE-PATTERN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LINE-PATTERN is : 
   * (OR NoItem
      (MEMBER SOLID DASH DOT LONG-DASH SHORT-DASH COARSE-DOT FINE-DOT)
      (Sequence Symbol 1)
      (Sequence Integer 1)
      (Structure 
        PATTERN
          (Sequence Integer 1)
        NOT-SCALED-BY-LINE-WIDTH BooleanTruthValue))
   *
   */
  public java.lang.Object getLinePattern() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LINE-PATTERN
   * @param linePattern new value to conclude for LINE-PATTERN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLinePattern(java.lang.Object linePattern) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONNECTION-POSITION-SEQUENCE
   * @return the value of the CONNECTION-POSITION-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTION-POSITION-SEQUENCE is : 
   * (Sequence)
   *
   */
  public com.gensym.util.Sequence getConnectionPositionSequence() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONNECTION-IS-DIRECTED
   * @return the value of the CONNECTION-IS-DIRECTED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTION-IS-DIRECTED is : 
   * BooleanTruthValue
   *
   */
  public boolean getConnectionIsDirected() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONNECTION-VERTICES
   * @return the value of the CONNECTION-VERTICES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTION-VERTICES is : 
   * (Sequence Integer 1)
   *
   */
  public com.gensym.util.Sequence getConnectionVertices() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONNECTION-STYLE
   * @return the value of the CONNECTION-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTION-STYLE is : 
   * (MEMBER DIAGONAL ORTHOGONAL)
   *
   */
  public com.gensym.util.Symbol getConnectionStyle() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONNECTION-OUTPUT
   * @return the value of the CONNECTION-OUTPUT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTION-OUTPUT is : 
   * (OR NoItem
      (Structure 
        ITEM (Class ITEM)
        PORT-NAME
          (OR NoItem
              Symbol)
        SIDE
          (MEMBER TOP BOTTOM LEFT RIGHT)
        POSITION Integer))
   *
   */
  public com.gensym.util.Structure getConnectionOutput() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONNECTION-INPUT
   * @return the value of the CONNECTION-INPUT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTION-INPUT is : 
   * (OR NoItem
      (Structure 
        ITEM (Class ITEM)
        PORT-NAME
          (OR NoItem
              Symbol)
        SIDE
          (MEMBER TOP BOTTOM LEFT RIGHT)
        POSITION Integer))
   *
   */
  public com.gensym.util.Structure getConnectionInput() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CROSS-SECTION-PATTERN
   * @return the value of the CROSS-SECTION-PATTERN attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CROSS-SECTION-PATTERN is : 
   * (OR NoItem
      (Structure 
        CROSS-SECTION-REGIONS
          (Sequence 
            (Structure 
              REGION-NAME Symbol
              REGION-COLOR
                (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE 
                        CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD 
                        GRAY GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN 
                        MAGENTA MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                        ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN 
                        THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE 
                        LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE 
                        PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW 
                        LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY))
            1))
        CROSS-SECTION-STRIPES
          (Sequence 
            (Structure 
              REGION-NAME Symbol
              REGION-SIZE Integer)
            1))))
   *
   */
  public com.gensym.util.Structure getCrossSectionPatternForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STUB-LENGTH
   * @return the value of the STUB-LENGTH attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STUB-LENGTH is : 
   * (OR Symbol
      Quantity)
   *
   */
  public java.lang.Object getStubLengthForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JUNCTION-BLOCK-CLASS
   * @return the value of the JUNCTION-BLOCK-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JUNCTION-BLOCK-CLASS is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getJunctionBlockClassForClass() throws G2AccessException;

}
