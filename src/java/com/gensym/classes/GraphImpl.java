/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GraphImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:00 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class GraphImpl extends com.gensym.classes.ItemImpl implements Graph {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public GraphImpl() {
    super();
  }

  public GraphImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GraphImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- SCROLL-CONTINUOUSLY?
   * @param scrollContinuously new value to conclude for SCROLL-CONTINUOUSLY?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setScrollContinuously(boolean scrollContinuously) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SCROLL_CONTINUOUSLYQ_, new Boolean (scrollContinuously));
  }

  /**
   * Generated Property Getter for attribute -- SCROLL-CONTINUOUSLY?
   * @return the value of the SCROLL-CONTINUOUSLY? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getScrollContinuously() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SCROLL_CONTINUOUSLYQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- PERCENTAGE-EXTRA-SPACE-TO-LEAVE
   * @param percentageExtraSpaceToLeave new value to conclude for PERCENTAGE-EXTRA-SPACE-TO-LEAVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPercentageExtraSpaceToLeave(int percentageExtraSpaceToLeave) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PERCENTAGE_EXTRA_SPACE_TO_LEAVE_, percentageExtraSpaceToLeave);
  }

  /**
   * Generated Property Getter for attribute -- PERCENTAGE-EXTRA-SPACE-TO-LEAVE
   * @return the value of the PERCENTAGE-EXTRA-SPACE-TO-LEAVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getPercentageExtraSpaceToLeave() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PERCENTAGE_EXTRA_SPACE_TO_LEAVE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- SHOW-GRID-LINES?
   * @param showGridLines new value to conclude for SHOW-GRID-LINES?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setShowGridLines(boolean showGridLines) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SHOW_GRID_LINESQ_, new Boolean (showGridLines));
  }

  /**
   * Generated Property Getter for attribute -- SHOW-GRID-LINES?
   * @return the value of the SHOW-GRID-LINES? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getShowGridLines() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SHOW_GRID_LINESQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- EXPRESSIONS-TO-DISPLAY
   * @param expressionsToDisplay new value to conclude for EXPRESSIONS-TO-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setExpressionsToDisplay(java.lang.String expressionsToDisplay) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.EXPRESSIONS_TO_DISPLAY_, expressionsToDisplay);
  }

  /**
   * Generated Property Getter for attribute -- EXPRESSIONS-TO-DISPLAY
   * @return the value of the EXPRESSIONS-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getExpressionsToDisplay() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EXPRESSIONS_TO_DISPLAY_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- LABEL-TO-DISPLAY
   * @param labelToDisplay new value to conclude for LABEL-TO-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLabelToDisplay(java.lang.String labelToDisplay) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.LABEL_TO_DISPLAY_, labelToDisplay);
  }

  /**
   * Generated Property Getter for attribute -- LABEL-TO-DISPLAY
   * @return the value of the LABEL-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getLabelToDisplay() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LABEL_TO_DISPLAY_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DISPLAY-UPDATE-INTERVAL
   * @param displayUpdateInterval new value to conclude for DISPLAY-UPDATE-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDisplayUpdateInterval(java.lang.Number displayUpdateInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DISPLAY_UPDATE_INTERVAL_, displayUpdateInterval);
  }

  /**
   * Generated Property Getter for attribute -- DISPLAY-UPDATE-INTERVAL
   * @return the value of the DISPLAY-UPDATE-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getDisplayUpdateInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DISPLAY_UPDATE_INTERVAL_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DISPLAY-WAIT-INTERVAL
   * @param displayWaitInterval new value to conclude for DISPLAY-WAIT-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDisplayWaitInterval(java.lang.Number displayWaitInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DISPLAY_WAIT_INTERVAL_, displayWaitInterval);
  }

  /**
   * Generated Property Getter for attribute -- DISPLAY-WAIT-INTERVAL
   * @return the value of the DISPLAY-WAIT-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getDisplayWaitInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DISPLAY_WAIT_INTERVAL_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DISPLAY-UPDATE-PRIORITY
   * @param displayUpdatePriority new value to conclude for DISPLAY-UPDATE-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDisplayUpdatePriority(com.gensym.util.Symbol displayUpdatePriority) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DISPLAY_UPDATE_PRIORITY_, displayUpdatePriority);
  }

  /**
   * Generated Property Getter for attribute -- DISPLAY-UPDATE-PRIORITY
   * @return the value of the DISPLAY-UPDATE-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getDisplayUpdatePriority() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DISPLAY_UPDATE_PRIORITY_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SHOW-SIMULATED-VALUES
   * @param showSimulatedValues new value to conclude for SHOW-SIMULATED-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setShowSimulatedValues(boolean showSimulatedValues) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SHOW_SIMULATED_VALUES_, new Boolean (showSimulatedValues));
  }

  /**
   * Generated Property Getter for attribute -- SHOW-SIMULATED-VALUES
   * @return the value of the SHOW-SIMULATED-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getShowSimulatedValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SHOW_SIMULATED_VALUES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- SIZE-IN-WORKSPACE
   * @param sizeInWorkspace new value to conclude for SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSizeInWorkspace(com.gensym.util.Structure sizeInWorkspace) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SIZE_IN_WORKSPACE_, sizeInWorkspace);
  }

  /**
   * Generated Property Getter for attribute -- SIZE-IN-WORKSPACE
   * @return the value of the SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getSizeInWorkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SIZE_IN_WORKSPACE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- TABLE-ROWS
   * @return the value of the TABLE-ROWS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getTableRows() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TABLE_ROWS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- FORMAT-TYPE
   * @return the value of the FORMAT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFormatType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FORMAT_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ITEM-CONFIGURATION
   * @param itemConfiguration new value to conclude for ITEM-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setItemConfiguration(com.gensym.util.Sequence itemConfiguration) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ITEM_CONFIGURATION_, itemConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- ITEM-CONFIGURATION
   * @return the value of the ITEM-CONFIGURATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getItemConfiguration() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NAMES
   * @param names new value to conclude for NAMES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNames(java.lang.Object names) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NAMES_, names);
  }

  /**
   * Generated Property Getter for attribute -- NAMES
   * @return the value of the NAMES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getNames() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NAMES_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- LAYER-POSITION
   * @return the value of the LAYER-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getLayerPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LAYER_POSITION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @param followingItemInWorkspaceLayering new value to conclude for FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFollowingItemInWorkspaceLayering(com.gensym.classes.Block followingItemInWorkspaceLayering) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FOLLOWING_ITEM_IN_WORKSPACE_LAYERING_, followingItemInWorkspaceLayering);
  }

  /**
   * Generated Property Getter for attribute -- FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @return the value of the FOLLOWING-ITEM-IN-WORKSPACE-LAYERING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.Block getFollowingItemInWorkspaceLayering() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FOLLOWING_ITEM_IN_WORKSPACE_LAYERING_);
    return (com.gensym.classes.Block)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- POSITION-IN-WORKSPACE
   * @param positionInWorkspace new value to conclude for POSITION-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPositionInWorkspace(com.gensym.util.Structure positionInWorkspace) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.POSITION_IN_WORKSPACE_, positionInWorkspace);
  }

  /**
   * Generated Property Getter for attribute -- POSITION-IN-WORKSPACE
   * @return the value of the POSITION-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getPositionInWorkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.POSITION_IN_WORKSPACE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RELATIONSHIPS
   * @param relationships new value to conclude for RELATIONSHIPS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRelationships(com.gensym.util.Sequence relationships) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RELATIONSHIPS_, relationships);
  }

  /**
   * Generated Property Getter for attribute -- RELATIONSHIPS
   * @return the value of the RELATIONSHIPS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getRelationships() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RELATIONSHIPS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ITEM-NOTES
   * @return the value of the ITEM-NOTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getItemNotes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_NOTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CONTAINING-MODULE
   * @return the value of the CONTAINING-MODULE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getContainingModule() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONTAINING_MODULE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ITEM-ACTIVE
   * @return the value of the ITEM-ACTIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getItemActive() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_ACTIVE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEM-STATUS
   * @return the value of the ITEM-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getItemStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_STATUS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INSTANTIATE
   * @return the value of the INSTANTIATE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getInstantiateForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANTIATE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- INCLUDE-IN-MENUS
   * @return the value of the INCLUDE-IN-MENUS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getIncludeInMenusForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INCLUDE_IN_MENUS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- SYSTEM-MENU-CHOICES
   * @return the value of the SYSTEM-MENU-CHOICES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSystemMenuChoicesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SYSTEM_MENU_CHOICES_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
