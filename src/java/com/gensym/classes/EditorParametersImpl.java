/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EditorParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:40:44 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class EditorParametersImpl extends com.gensym.classes.SystemTableImpl implements EditorParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public EditorParametersImpl() {
    super();
  }

  public EditorParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public EditorParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-NAMES-IN-MENUS
   * @param maximumNumberOfNamesInMenus new value to conclude for MAXIMUM-NUMBER-OF-NAMES-IN-MENUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMaximumNumberOfNamesInMenus(int maximumNumberOfNamesInMenus) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_NAMES_IN_MENUS_, maximumNumberOfNamesInMenus);
  }

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-NAMES-IN-MENUS
   * @return the value of the MAXIMUM-NUMBER-OF-NAMES-IN-MENUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getMaximumNumberOfNamesInMenus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_NAMES_IN_MENUS_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- OBJECT-NAME-MENUS-IN-UPPER-CASE?
   * @param objectNameMenusInUpperCase new value to conclude for OBJECT-NAME-MENUS-IN-UPPER-CASE?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setObjectNameMenusInUpperCase(boolean objectNameMenusInUpperCase) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.OBJECT_NAME_MENUS_IN_UPPER_CASEQ_, new Boolean (objectNameMenusInUpperCase));
  }

  /**
   * Generated Property Getter for attribute -- OBJECT-NAME-MENUS-IN-UPPER-CASE?
   * @return the value of the OBJECT-NAME-MENUS-IN-UPPER-CASE? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getObjectNameMenusInUpperCase() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.OBJECT_NAME_MENUS_IN_UPPER_CASEQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB
   * @param numberOfSpacesToInsertOnATab new value to conclude for NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNumberOfSpacesToInsertOnATab(int numberOfSpacesToInsertOnATab) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NUMBER_OF_SPACES_TO_INSERT_ON_A_TAB_, numberOfSpacesToInsertOnATab);
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB
   * @return the value of the NUMBER-OF-SPACES-TO-INSERT-ON-A-TAB attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getNumberOfSpacesToInsertOnATab() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NUMBER_OF_SPACES_TO_INSERT_ON_A_TAB_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER
   * @param maximumNumberOfUndosToRemember new value to conclude for MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMaximumNumberOfUndosToRemember(int maximumNumberOfUndosToRemember) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_UNDOS_TO_REMEMBER_, maximumNumberOfUndosToRemember);
  }

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER
   * @return the value of the MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getMaximumNumberOfUndosToRemember() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_UNDOS_TO_REMEMBER_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP
   * @param maximumNumberOfScrapsToKeep new value to conclude for MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMaximumNumberOfScrapsToKeep(int maximumNumberOfScrapsToKeep) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_SCRAPS_TO_KEEP_, maximumNumberOfScrapsToKeep);
  }

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP
   * @return the value of the MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getMaximumNumberOfScrapsToKeep() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_SCRAPS_TO_KEEP_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- MINIMUM-WIDTH-FOR-EDIT-BOX
   * @param minimumWidthForEditBox new value to conclude for MINIMUM-WIDTH-FOR-EDIT-BOX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMinimumWidthForEditBox(int minimumWidthForEditBox) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MINIMUM_WIDTH_FOR_EDIT_BOX_, minimumWidthForEditBox);
  }

  /**
   * Generated Property Getter for attribute -- MINIMUM-WIDTH-FOR-EDIT-BOX
   * @return the value of the MINIMUM-WIDTH-FOR-EDIT-BOX attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getMinimumWidthForEditBox() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MINIMUM_WIDTH_FOR_EDIT_BOX_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- AUTHOR-RECORDING-ENABLED?
   * @param authorRecordingEnabled new value to conclude for AUTHOR-RECORDING-ENABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAuthorRecordingEnabled(boolean authorRecordingEnabled) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.AUTHOR_RECORDING_ENABLEDQ_, authorRecordingEnabled);
  }

  /**
   * Generated Property Getter for attribute -- AUTHOR-RECORDING-ENABLED?
   * @return the value of the AUTHOR-RECORDING-ENABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getAuthorRecordingEnabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.AUTHOR_RECORDING_ENABLEDQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- POP-UP-EDIT-OPERATIONS-MENU
   * @param popUpEditOperationsMenu new value to conclude for POP-UP-EDIT-OPERATIONS-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPopUpEditOperationsMenu(boolean popUpEditOperationsMenu) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.POP_UP_EDIT_OPERATIONS_MENU_, popUpEditOperationsMenu);
  }

  /**
   * Generated Property Getter for attribute -- POP-UP-EDIT-OPERATIONS-MENU
   * @return the value of the POP-UP-EDIT-OPERATIONS-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPopUpEditOperationsMenu() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.POP_UP_EDIT_OPERATIONS_MENU_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- BUTTONS-FOR-EDIT-OPERATIONS
   * @param buttonsForEditOperations new value to conclude for BUTTONS-FOR-EDIT-OPERATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setButtonsForEditOperations(boolean buttonsForEditOperations) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BUTTONS_FOR_EDIT_OPERATIONS_, buttonsForEditOperations);
  }

  /**
   * Generated Property Getter for attribute -- BUTTONS-FOR-EDIT-OPERATIONS
   * @return the value of the BUTTONS-FOR-EDIT-OPERATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getButtonsForEditOperations() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BUTTONS_FOR_EDIT_OPERATIONS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- SHOW-PROCEDURE-SIGNATURES?
   * @param showProcedureSignatures new value to conclude for SHOW-PROCEDURE-SIGNATURES?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setShowProcedureSignatures(boolean showProcedureSignatures) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SHOW_PROCEDURE_SIGNATURESQ_, showProcedureSignatures);
  }

  /**
   * Generated Property Getter for attribute -- SHOW-PROCEDURE-SIGNATURES?
   * @return the value of the SHOW-PROCEDURE-SIGNATURES? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getShowProcedureSignatures() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SHOW_PROCEDURE_SIGNATURESQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- SMART-SPACE-INSERTION
   * @param smartSpaceInsertion new value to conclude for SMART-SPACE-INSERTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSmartSpaceInsertion(boolean smartSpaceInsertion) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SMART_SPACE_INSERTION_, smartSpaceInsertion);
  }

  /**
   * Generated Property Getter for attribute -- SMART-SPACE-INSERTION
   * @return the value of the SMART-SPACE-INSERTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getSmartSpaceInsertion() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SMART_SPACE_INSERTION_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- PREFER-NATIVE-EDITOR
   * @param preferNativeEditor new value to conclude for PREFER-NATIVE-EDITOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPreferNativeEditor(boolean preferNativeEditor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PREFER_NATIVE_EDITOR_, preferNativeEditor);
  }

  /**
   * Generated Property Getter for attribute -- PREFER-NATIVE-EDITOR
   * @return the value of the PREFER-NATIVE-EDITOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPreferNativeEditor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PREFER_NATIVE_EDITOR_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
