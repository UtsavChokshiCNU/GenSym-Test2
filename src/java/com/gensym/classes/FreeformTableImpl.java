/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      FreeformTableImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:44:05 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class FreeformTableImpl extends com.gensym.classes.ItemImpl implements FreeformTable {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public FreeformTableImpl() {
    super();
  }

  public FreeformTableImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public FreeformTableImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- TABLE-SIZE
   * @param tableSize new value to conclude for TABLE-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTableSize(com.gensym.util.Structure tableSize) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TABLE_SIZE_, tableSize);
  }

  /**
   * Generated Property Getter for attribute -- TABLE-SIZE
   * @return the value of the TABLE-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getTableSize() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TABLE_SIZE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TABLE-CELLS
   * @param tableCells new value to conclude for TABLE-CELLS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTableCells(com.gensym.util.Sequence tableCells) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TABLE_CELLS_, tableCells);
  }

  /**
   * Generated Property Getter for attribute -- TABLE-CELLS
   * @return the value of the TABLE-CELLS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getTableCells() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TABLE_CELLS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_, evaluationAttributes);
  }

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_);
    return (com.gensym.util.Structure)retnValue;
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
   * Generated Property Setter for attribute -- DEFAULT-CELL-FORMAT
   * @param defaultCellFormat new value to conclude for DEFAULT-CELL-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultCellFormat(com.gensym.util.Structure defaultCellFormat) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_CELL_FORMAT_, defaultCellFormat);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-CELL-FORMAT
   * @return the value of the DEFAULT-CELL-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getDefaultCellFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_CELL_FORMAT_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DEFAULT-EVALUATION-SETTING
   * @param defaultEvaluationSetting new value to conclude for DEFAULT-EVALUATION-SETTING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultEvaluationSetting(com.gensym.util.Structure defaultEvaluationSetting) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_EVALUATION_SETTING_, defaultEvaluationSetting);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-EVALUATION-SETTING
   * @return the value of the DEFAULT-EVALUATION-SETTING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getDefaultEvaluationSetting() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_EVALUATION_SETTING_);
    return (com.gensym.util.Structure)retnValue;
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
