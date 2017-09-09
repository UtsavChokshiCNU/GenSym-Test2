/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Workspace.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:33 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;

public interface Workspace extends com.gensym.classes.Block {

  public static final Symbol WORKSPACE_ = com.gensym.util.symbol.G2ClassSymbols.WORKSPACE_;
  static final Symbol g2ClassName = WORKSPACE_;
  static final Symbol[] classInheritancePath = new Symbol[] {WORKSPACE_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- WORKSPACE-MARGIN
   * @return the value of the WORKSPACE-MARGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WORKSPACE-MARGIN is : 
   * Integer
   *
   */
  public int getWorkspaceMargin() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WORKSPACE-MARGIN
   * @param workspaceMargin new value to conclude for WORKSPACE-MARGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWorkspaceMargin(int workspaceMargin) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BACKGROUND-IMAGES
   * @return the value of the BACKGROUND-IMAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BACKGROUND-IMAGES is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          IMAGE-NAME Symbol
          POINT
            (Structure 
              X Integer
              Y Integer)
          TILED BooleanTruthValue)
        1)))
   *
   */
  public com.gensym.util.Sequence getBackgroundImages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BACKGROUND-IMAGES
   * @param backgroundImages new value to conclude for BACKGROUND-IMAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBackgroundImages(com.gensym.util.Sequence backgroundImages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FRAME-STYLE
   * @return the value of the FRAME-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FRAME-STYLE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getFrameStyle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FRAME-STYLE
   * @param frameStyle new value to conclude for FRAME-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFrameStyle(com.gensym.util.Symbol frameStyle) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TITLE-BAR-TEXT
   * @return the value of the TITLE-BAR-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TITLE-BAR-TEXT is : 
   * (OR Symbol
      Text
      (Sequence 
        (OR Symbol
            Text)
        0))
      NoItem)
   *
   */
  public java.lang.Object getTitleBarText() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TITLE-BAR-TEXT
   * @param titleBarText new value to conclude for TITLE-BAR-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTitleBarText(java.lang.Object titleBarText) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VIEW-PREFERENCES
   * @return the value of the VIEW-PREFERENCES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VIEW-PREFERENCES is : 
   * (OR NoItem
      (Structure 
        VISIBLE-GRID BooleanTruthValue
        UNSELECTABLE BooleanTruthValue
        FIXED-SIZE BooleanTruthValue))
   *
   */
  public com.gensym.util.Structure getViewPreferences() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VIEW-PREFERENCES
   * @param viewPreferences new value to conclude for VIEW-PREFERENCES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setViewPreferences(com.gensym.util.Structure viewPreferences) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PREFER-BUFFERED-DRAWING
   * @return the value of the PREFER-BUFFERED-DRAWING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PREFER-BUFFERED-DRAWING is : 
   * BooleanTruthValue
   *
   */
  public boolean getPreferBufferedDrawing() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PREFER-BUFFERED-DRAWING
   * @param preferBufferedDrawing new value to conclude for PREFER-BUFFERED-DRAWING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPreferBufferedDrawing(boolean preferBufferedDrawing) throws G2AccessException;

}
