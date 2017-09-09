/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Graph.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:56:58 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Graph extends com.gensym.classes.Item, com.gensym.classes.Table {

  public static final Symbol GRAPH_ = com.gensym.util.symbol.G2ClassSymbols.GRAPH_;
  static final Symbol g2ClassName = GRAPH_;
  static final Symbol[] classInheritancePath = new Symbol[] {GRAPH_, ITEM_, TABLE_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- SCROLL-CONTINUOUSLY?
   * @return the value of the SCROLL-CONTINUOUSLY? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SCROLL-CONTINUOUSLY? is : 
   * BooleanTruthValue
   *
   */
  public boolean getScrollContinuously() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SCROLL-CONTINUOUSLY?
   * @param scrollContinuously new value to conclude for SCROLL-CONTINUOUSLY?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setScrollContinuously(boolean scrollContinuously) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PERCENTAGE-EXTRA-SPACE-TO-LEAVE
   * @return the value of the PERCENTAGE-EXTRA-SPACE-TO-LEAVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PERCENTAGE-EXTRA-SPACE-TO-LEAVE is : 
   * Integer
   *
   */
  public int getPercentageExtraSpaceToLeave() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PERCENTAGE-EXTRA-SPACE-TO-LEAVE
   * @param percentageExtraSpaceToLeave new value to conclude for PERCENTAGE-EXTRA-SPACE-TO-LEAVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPercentageExtraSpaceToLeave(int percentageExtraSpaceToLeave) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-GRID-LINES?
   * @return the value of the SHOW-GRID-LINES? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-GRID-LINES? is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowGridLines() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-GRID-LINES?
   * @param showGridLines new value to conclude for SHOW-GRID-LINES?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowGridLines(boolean showGridLines) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EXPRESSIONS-TO-DISPLAY
   * @return the value of the EXPRESSIONS-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EXPRESSIONS-TO-DISPLAY is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getExpressionsToDisplay() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EXPRESSIONS-TO-DISPLAY
   * @param expressionsToDisplay new value to conclude for EXPRESSIONS-TO-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setExpressionsToDisplay(java.lang.String expressionsToDisplay) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LABEL-TO-DISPLAY
   * @return the value of the LABEL-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LABEL-TO-DISPLAY is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getLabelToDisplay() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LABEL-TO-DISPLAY
   * @param labelToDisplay new value to conclude for LABEL-TO-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLabelToDisplay(java.lang.String labelToDisplay) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISPLAY-UPDATE-INTERVAL
   * @return the value of the DISPLAY-UPDATE-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISPLAY-UPDATE-INTERVAL is : 
   * Quantity
   *
   */
  public java.lang.Number getDisplayUpdateInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISPLAY-UPDATE-INTERVAL
   * @param displayUpdateInterval new value to conclude for DISPLAY-UPDATE-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisplayUpdateInterval(java.lang.Number displayUpdateInterval) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISPLAY-WAIT-INTERVAL
   * @return the value of the DISPLAY-WAIT-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISPLAY-WAIT-INTERVAL is : 
   * Quantity
   *
   */
  public java.lang.Number getDisplayWaitInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISPLAY-WAIT-INTERVAL
   * @param displayWaitInterval new value to conclude for DISPLAY-WAIT-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisplayWaitInterval(java.lang.Number displayWaitInterval) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISPLAY-UPDATE-PRIORITY
   * @return the value of the DISPLAY-UPDATE-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISPLAY-UPDATE-PRIORITY is : 
   * (MEMBER 1 2 3 4 5 6 7 8 9 10)
   *
   */
  public com.gensym.util.Symbol getDisplayUpdatePriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISPLAY-UPDATE-PRIORITY
   * @param displayUpdatePriority new value to conclude for DISPLAY-UPDATE-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisplayUpdatePriority(com.gensym.util.Symbol displayUpdatePriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-SIMULATED-VALUES
   * @return the value of the SHOW-SIMULATED-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-SIMULATED-VALUES is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowSimulatedValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-SIMULATED-VALUES
   * @param showSimulatedValues new value to conclude for SHOW-SIMULATED-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowSimulatedValues(boolean showSimulatedValues) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIZE-IN-WORKSPACE
   * @return the value of the SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIZE-IN-WORKSPACE is : 
   * (OR NoItem
      (Structure 
        WIDTH Quantity
        HEIGHT Quantity))
   *
   */
  public com.gensym.util.Structure getSizeInWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIZE-IN-WORKSPACE
   * @param sizeInWorkspace new value to conclude for SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSizeInWorkspace(com.gensym.util.Structure sizeInWorkspace) throws G2AccessException;

}
