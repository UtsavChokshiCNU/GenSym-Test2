/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EditorParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:40:43 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface EditorParameters extends com.gensym.classes.SystemTable {

  public static final Symbol EDITOR_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.EDITOR_PARAMETERS_;
  static final Symbol g2ClassName = EDITOR_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {EDITOR_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-NAMES-IN-MENUS
   * @return the value of the MAXIMUM-NUMBER-OF-NAMES-IN-MENUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-NUMBER-OF-NAMES-IN-MENUS is : 
   * Integer
   *
   */
  public int getMaximumNumberOfNamesInMenus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-NAMES-IN-MENUS
   * @param maximumNumberOfNamesInMenus new value to conclude for MAXIMUM-NUMBER-OF-NAMES-IN-MENUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumNumberOfNamesInMenus(int maximumNumberOfNamesInMenus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- OBJECT-NAME-MENUS-IN-UPPER-CASE?
   * @return the value of the OBJECT-NAME-MENUS-IN-UPPER-CASE? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for OBJECT-NAME-MENUS-IN-UPPER-CASE? is : 
   * BooleanTruthValue
   *
   */
  public boolean getObjectNameMenusInUpperCase() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- OBJECT-NAME-MENUS-IN-UPPER-CASE?
   * @param objectNameMenusInUpperCase new value to conclude for OBJECT-NAME-MENUS-IN-UPPER-CASE?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setObjectNameMenusInUpperCase(boolean objectNameMenusInUpperCase) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB
   * @return the value of the NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB is : 
   * Integer
   *
   */
  public int getNumberOfSpacesToInsertOnATab() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB
   * @param numberOfSpacesToInsertOnATab new value to conclude for NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfSpacesToInsertOnATab(int numberOfSpacesToInsertOnATab) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER
   * @return the value of the MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER is : 
   * Integer
   *
   */
  public int getMaximumNumberOfUndosToRemember() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER
   * @param maximumNumberOfUndosToRemember new value to conclude for MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumNumberOfUndosToRemember(int maximumNumberOfUndosToRemember) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP
   * @return the value of the MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP is : 
   * Integer
   *
   */
  public int getMaximumNumberOfScrapsToKeep() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP
   * @param maximumNumberOfScrapsToKeep new value to conclude for MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumNumberOfScrapsToKeep(int maximumNumberOfScrapsToKeep) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MINIMUM-WIDTH-FOR-EDIT-BOX
   * @return the value of the MINIMUM-WIDTH-FOR-EDIT-BOX attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MINIMUM-WIDTH-FOR-EDIT-BOX is : 
   * Integer
   *
   */
  public int getMinimumWidthForEditBox() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MINIMUM-WIDTH-FOR-EDIT-BOX
   * @param minimumWidthForEditBox new value to conclude for MINIMUM-WIDTH-FOR-EDIT-BOX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMinimumWidthForEditBox(int minimumWidthForEditBox) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- AUTHOR-RECORDING-ENABLED?
   * @return the value of the AUTHOR-RECORDING-ENABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTHOR-RECORDING-ENABLED? is : 
   * BooleanTruthValue
   *
   */
  public boolean getAuthorRecordingEnabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTHOR-RECORDING-ENABLED?
   * @param authorRecordingEnabled new value to conclude for AUTHOR-RECORDING-ENABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthorRecordingEnabled(boolean authorRecordingEnabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- POP-UP-EDIT-OPERATIONS-MENU
   * @return the value of the POP-UP-EDIT-OPERATIONS-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for POP-UP-EDIT-OPERATIONS-MENU is : 
   * BooleanTruthValue
   *
   */
  public boolean getPopUpEditOperationsMenu() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- POP-UP-EDIT-OPERATIONS-MENU
   * @param popUpEditOperationsMenu new value to conclude for POP-UP-EDIT-OPERATIONS-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPopUpEditOperationsMenu(boolean popUpEditOperationsMenu) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BUTTONS-FOR-EDIT-OPERATIONS
   * @return the value of the BUTTONS-FOR-EDIT-OPERATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BUTTONS-FOR-EDIT-OPERATIONS is : 
   * BooleanTruthValue
   *
   */
  public boolean getButtonsForEditOperations() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BUTTONS-FOR-EDIT-OPERATIONS
   * @param buttonsForEditOperations new value to conclude for BUTTONS-FOR-EDIT-OPERATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setButtonsForEditOperations(boolean buttonsForEditOperations) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-PROCEDURE-SIGNATURES?
   * @return the value of the SHOW-PROCEDURE-SIGNATURES? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-PROCEDURE-SIGNATURES? is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowProcedureSignatures() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-PROCEDURE-SIGNATURES?
   * @param showProcedureSignatures new value to conclude for SHOW-PROCEDURE-SIGNATURES?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowProcedureSignatures(boolean showProcedureSignatures) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SMART-SPACE-INSERTION
   * @return the value of the SMART-SPACE-INSERTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SMART-SPACE-INSERTION is : 
   * BooleanTruthValue
   *
   */
  public boolean getSmartSpaceInsertion() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SMART-SPACE-INSERTION
   * @param smartSpaceInsertion new value to conclude for SMART-SPACE-INSERTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSmartSpaceInsertion(boolean smartSpaceInsertion) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PREFER-NATIVE-EDITOR
   * @return the value of the PREFER-NATIVE-EDITOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PREFER-NATIVE-EDITOR is : 
   * BooleanTruthValue
   *
   */
  public boolean getPreferNativeEditor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PREFER-NATIVE-EDITOR
   * @param preferNativeEditor new value to conclude for PREFER-NATIVE-EDITOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPreferNativeEditor(boolean preferNativeEditor) throws G2AccessException;

}
