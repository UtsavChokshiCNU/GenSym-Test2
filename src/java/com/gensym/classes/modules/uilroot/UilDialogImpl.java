/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilDialogImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:18 EDT 2007
 *
 */


package com.gensym.classes.modules.uilroot;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class UilDialogImpl extends com.gensym.classes.modules.uilroot.UilGrobjImpl implements UilDialog {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_INITIATING_CLASS_FOR_DIALOG_ = Symbol.intern ("UIL-INITIATING-CLASS-FOR-DIALOG");
  private static final Symbol RELATED_ITEM_ = Symbol.intern ("RELATED-ITEM");
  private static final Symbol UIL_TEMPORARY_STORAGE_OBJECT_ = Symbol.intern ("UIL-TEMPORARY-STORAGE-OBJECT");
  private static final Symbol UIL_DIALOG_MODE_ = Symbol.intern ("UIL-DIALOG-MODE");
  private static final Symbol UIL_DIALOG_STATUS_ = Symbol.intern ("UIL-DIALOG-STATUS");
  private static final Symbol UIL_WHICH_BUTTON_PRESSED_ = Symbol.intern ("UIL-WHICH-BUTTON-PRESSED");
  private static final Symbol UIL_RETURN_KEY_BEHAVIOR_ = Symbol.intern ("UIL-RETURN-KEY-BEHAVIOR");
  private static final Symbol UIL_TAB_KEY_BEHAVIOR_ = Symbol.intern ("UIL-TAB-KEY-BEHAVIOR");
  private static final Symbol UIL_ABORT_KEY_BEHAVIOR_ = Symbol.intern ("UIL-ABORT-KEY-BEHAVIOR");
  private static final Symbol UIL_DIALOG_HAS_MOVABLE_WORKSPACE_ = Symbol.intern ("UIL-DIALOG-HAS-MOVABLE-WORKSPACE");
  private static final Symbol UIL_DIALOG_EDIT_BOXES_HAVE_MENUS_ = Symbol.intern ("UIL-DIALOG-EDIT-BOXES-HAVE-MENUS");
  private static final Symbol UIL_EDIT_EVENT_TRIGGER_ = Symbol.intern ("UIL-EDIT-EVENT-TRIGGER");
  private static final Symbol UIL_ACTION_TRIGGER_ = Symbol.intern ("UIL-ACTION-TRIGGER");
  private static final Symbol UIL_ORIGIN_ = Symbol.intern ("UIL-ORIGIN");
  private static final Symbol UIL_ALLOW_MULTIPLE_COPIES_PER_WINDOW_ = Symbol.intern ("UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW");
  private static final Symbol UIL_DIALOG_ALLOW_FIELD_EDIT_ = Symbol.intern ("UIL-DIALOG-ALLOW-FIELD-EDIT");
  private static final Symbol UIL_DIALOG_ALLOW_OUTSIDE_TEXT_SELECTION_ = Symbol.intern ("UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION");
  private static final Symbol UIL_DIALOG_HOME_MODULE_NAME_ = Symbol.intern ("UIL-DIALOG-HOME-MODULE-NAME");
  private static final Symbol UIL_DIALOG_INSTANCE_POOL_LIMIT_ = Symbol.intern ("UIL-DIALOG-INSTANCE-POOL-LIMIT");
  private static final Symbol UIL_DIALOG_IN_USE_ = Symbol.intern ("UIL-DIALOG-IN-USE");
  private static final Symbol UIL_BUSY_ = Symbol.intern ("UIL-BUSY");
  private static final Symbol UIL_MARKED_FOR_DELETE_ = Symbol.intern ("UIL-MARKED-FOR-DELETE");
  private static final Symbol UIL_DIALOG_ACTION_TOKEN_LIST_ = Symbol.intern ("UIL-DIALOG-ACTION-TOKEN-LIST");
  private static final Symbol UIL_DIALOG_ACTION_ITEM_LIST_ = Symbol.intern ("UIL-DIALOG-ACTION-ITEM-LIST");
  private static final Symbol UIL_DIALOG_WINDOW_LIST_ = Symbol.intern ("UIL-DIALOG-WINDOW-LIST");
  private static final Symbol UIL_DIALOG_GROBJ_LIST_ = Symbol.intern ("UIL-DIALOG-GROBJ-LIST");
  private static final Symbol UIL_DIALOG_USING_NEW_MECHANISM_ = Symbol.intern ("UIL-DIALOG-USING-NEW-MECHANISM");
  private static final Symbol UIL_ALWAYS_UPDATE_WHEN_MANAGED_ = Symbol.intern ("UIL-ALWAYS-UPDATE-WHEN-MANAGED");
  private static final Symbol UIL_X_POSITION_ = Symbol.intern ("UIL-X-POSITION");
  private static final Symbol UIL_Y_POSITION_ = Symbol.intern ("UIL-Y-POSITION");
  private static final Symbol UIL_USE_DEFAULT_POSITIONING_ = Symbol.intern ("UIL-USE-DEFAULT-POSITIONING");
  private static final Symbol UIL_ALLOW_LIFT_TO_TOP_ = Symbol.intern ("UIL-ALLOW-LIFT-TO-TOP");
  private static final Symbol UIL_TRANSLATE_DIALOG_ = Symbol.intern ("UIL-TRANSLATE-DIALOG");
  private static final Symbol UIL_GFR_TEXT_RESOURCE_GROUP_ = Symbol.intern ("UIL-GFR-TEXT-RESOURCE-GROUP");
  private static final Symbol UIL_LANGUAGE_ = Symbol.intern ("UIL-LANGUAGE");

  /* Generated constructors */

  public UilDialogImpl() {
    super();
  }

  public UilDialogImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilDialogImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-INITIATING-CLASS-FOR-DIALOG
   * @param uilInitiatingClassForDialog new value to conclude for UIL-INITIATING-CLASS-FOR-DIALOG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilInitiatingClassForDialog(java.lang.Object uilInitiatingClassForDialog) throws G2AccessException {
    setAttributeValue (UIL_INITIATING_CLASS_FOR_DIALOG_, uilInitiatingClassForDialog);
  }

  /**
   * Generated Property Getter for attribute -- UIL-INITIATING-CLASS-FOR-DIALOG
   * @return the value of the UIL-INITIATING-CLASS-FOR-DIALOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilInitiatingClassForDialog() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_INITIATING_CLASS_FOR_DIALOG_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RELATED-ITEM
   * @param relatedItem new value to conclude for RELATED-ITEM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRelatedItem(java.lang.Object relatedItem) throws G2AccessException {
    setAttributeValue (RELATED_ITEM_, relatedItem);
  }

  /**
   * Generated Property Getter for attribute -- RELATED-ITEM
   * @return the value of the RELATED-ITEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getRelatedItem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (RELATED_ITEM_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-TEMPORARY-STORAGE-OBJECT
   * @param uilTemporaryStorageObject new value to conclude for UIL-TEMPORARY-STORAGE-OBJECT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTemporaryStorageObject(java.lang.Object uilTemporaryStorageObject) throws G2AccessException {
    setAttributeValue (UIL_TEMPORARY_STORAGE_OBJECT_, uilTemporaryStorageObject);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TEMPORARY-STORAGE-OBJECT
   * @return the value of the UIL-TEMPORARY-STORAGE-OBJECT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilTemporaryStorageObject() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TEMPORARY_STORAGE_OBJECT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-MODE
   * @param uilDialogMode new value to conclude for UIL-DIALOG-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogMode(java.lang.Object uilDialogMode) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_MODE_, uilDialogMode);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-MODE
   * @return the value of the UIL-DIALOG-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_MODE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-STATUS
   * @param uilDialogStatus new value to conclude for UIL-DIALOG-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogStatus(java.lang.Object uilDialogStatus) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_STATUS_, uilDialogStatus);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-STATUS
   * @return the value of the UIL-DIALOG-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_STATUS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-WHICH-BUTTON-PRESSED
   * @param uilWhichButtonPressed new value to conclude for UIL-WHICH-BUTTON-PRESSED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilWhichButtonPressed(java.lang.Object uilWhichButtonPressed) throws G2AccessException {
    setAttributeValue (UIL_WHICH_BUTTON_PRESSED_, uilWhichButtonPressed);
  }

  /**
   * Generated Property Getter for attribute -- UIL-WHICH-BUTTON-PRESSED
   * @return the value of the UIL-WHICH-BUTTON-PRESSED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilWhichButtonPressed() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_WHICH_BUTTON_PRESSED_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-RETURN-KEY-BEHAVIOR
   * @param uilReturnKeyBehavior new value to conclude for UIL-RETURN-KEY-BEHAVIOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilReturnKeyBehavior(java.lang.Object uilReturnKeyBehavior) throws G2AccessException {
    setAttributeValue (UIL_RETURN_KEY_BEHAVIOR_, uilReturnKeyBehavior);
  }

  /**
   * Generated Property Getter for attribute -- UIL-RETURN-KEY-BEHAVIOR
   * @return the value of the UIL-RETURN-KEY-BEHAVIOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilReturnKeyBehavior() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_RETURN_KEY_BEHAVIOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-TAB-KEY-BEHAVIOR
   * @param uilTabKeyBehavior new value to conclude for UIL-TAB-KEY-BEHAVIOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTabKeyBehavior(java.lang.Object uilTabKeyBehavior) throws G2AccessException {
    setAttributeValue (UIL_TAB_KEY_BEHAVIOR_, uilTabKeyBehavior);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TAB-KEY-BEHAVIOR
   * @return the value of the UIL-TAB-KEY-BEHAVIOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilTabKeyBehavior() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TAB_KEY_BEHAVIOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ABORT-KEY-BEHAVIOR
   * @param uilAbortKeyBehavior new value to conclude for UIL-ABORT-KEY-BEHAVIOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilAbortKeyBehavior(java.lang.Object uilAbortKeyBehavior) throws G2AccessException {
    setAttributeValue (UIL_ABORT_KEY_BEHAVIOR_, uilAbortKeyBehavior);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ABORT-KEY-BEHAVIOR
   * @return the value of the UIL-ABORT-KEY-BEHAVIOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilAbortKeyBehavior() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ABORT_KEY_BEHAVIOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-HAS-MOVABLE-WORKSPACE
   * @param uilDialogHasMovableWorkspace new value to conclude for UIL-DIALOG-HAS-MOVABLE-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogHasMovableWorkspace(java.lang.Object uilDialogHasMovableWorkspace) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_HAS_MOVABLE_WORKSPACE_, uilDialogHasMovableWorkspace);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-HAS-MOVABLE-WORKSPACE
   * @return the value of the UIL-DIALOG-HAS-MOVABLE-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogHasMovableWorkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_HAS_MOVABLE_WORKSPACE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-EDIT-BOXES-HAVE-MENUS
   * @param uilDialogEditBoxesHaveMenus new value to conclude for UIL-DIALOG-EDIT-BOXES-HAVE-MENUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogEditBoxesHaveMenus(java.lang.Object uilDialogEditBoxesHaveMenus) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_EDIT_BOXES_HAVE_MENUS_, uilDialogEditBoxesHaveMenus);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-EDIT-BOXES-HAVE-MENUS
   * @return the value of the UIL-DIALOG-EDIT-BOXES-HAVE-MENUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogEditBoxesHaveMenus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_EDIT_BOXES_HAVE_MENUS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-EDIT-EVENT-TRIGGER
   * @param uilEditEventTrigger new value to conclude for UIL-EDIT-EVENT-TRIGGER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEditEventTrigger(java.lang.Object uilEditEventTrigger) throws G2AccessException {
    setAttributeValue (UIL_EDIT_EVENT_TRIGGER_, uilEditEventTrigger);
  }

  /**
   * Generated Property Getter for attribute -- UIL-EDIT-EVENT-TRIGGER
   * @return the value of the UIL-EDIT-EVENT-TRIGGER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEditEventTrigger() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_EDIT_EVENT_TRIGGER_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ACTION-TRIGGER
   * @param uilActionTrigger new value to conclude for UIL-ACTION-TRIGGER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilActionTrigger(java.lang.Object uilActionTrigger) throws G2AccessException {
    setAttributeValue (UIL_ACTION_TRIGGER_, uilActionTrigger);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ACTION-TRIGGER
   * @return the value of the UIL-ACTION-TRIGGER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilActionTrigger() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ACTION_TRIGGER_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ORIGIN
   * @param uilOrigin new value to conclude for UIL-ORIGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilOrigin(java.lang.Object uilOrigin) throws G2AccessException {
    setAttributeValue (UIL_ORIGIN_, uilOrigin);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ORIGIN
   * @return the value of the UIL-ORIGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilOrigin() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ORIGIN_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW
   * @param uilAllowMultipleCopiesPerWindow new value to conclude for UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilAllowMultipleCopiesPerWindow(java.lang.Object uilAllowMultipleCopiesPerWindow) throws G2AccessException {
    setAttributeValue (UIL_ALLOW_MULTIPLE_COPIES_PER_WINDOW_, uilAllowMultipleCopiesPerWindow);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW
   * @return the value of the UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilAllowMultipleCopiesPerWindow() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ALLOW_MULTIPLE_COPIES_PER_WINDOW_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-ALLOW-FIELD-EDIT
   * @param uilDialogAllowFieldEdit new value to conclude for UIL-DIALOG-ALLOW-FIELD-EDIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogAllowFieldEdit(java.lang.Object uilDialogAllowFieldEdit) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_ALLOW_FIELD_EDIT_, uilDialogAllowFieldEdit);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-ALLOW-FIELD-EDIT
   * @return the value of the UIL-DIALOG-ALLOW-FIELD-EDIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogAllowFieldEdit() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_ALLOW_FIELD_EDIT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION
   * @param uilDialogAllowOutsideTextSelection new value to conclude for UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogAllowOutsideTextSelection(java.lang.Object uilDialogAllowOutsideTextSelection) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_ALLOW_OUTSIDE_TEXT_SELECTION_, uilDialogAllowOutsideTextSelection);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION
   * @return the value of the UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogAllowOutsideTextSelection() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_ALLOW_OUTSIDE_TEXT_SELECTION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-HOME-MODULE-NAME
   * @param uilDialogHomeModuleName new value to conclude for UIL-DIALOG-HOME-MODULE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogHomeModuleName(java.lang.Object uilDialogHomeModuleName) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_HOME_MODULE_NAME_, uilDialogHomeModuleName);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-HOME-MODULE-NAME
   * @return the value of the UIL-DIALOG-HOME-MODULE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogHomeModuleName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_HOME_MODULE_NAME_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-INSTANCE-POOL-LIMIT
   * @param uilDialogInstancePoolLimit new value to conclude for UIL-DIALOG-INSTANCE-POOL-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogInstancePoolLimit(java.lang.Object uilDialogInstancePoolLimit) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_INSTANCE_POOL_LIMIT_, uilDialogInstancePoolLimit);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-INSTANCE-POOL-LIMIT
   * @return the value of the UIL-DIALOG-INSTANCE-POOL-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogInstancePoolLimit() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_INSTANCE_POOL_LIMIT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-IN-USE
   * @param uilDialogInUse new value to conclude for UIL-DIALOG-IN-USE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogInUse(java.lang.Object uilDialogInUse) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_IN_USE_, uilDialogInUse);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-IN-USE
   * @return the value of the UIL-DIALOG-IN-USE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogInUse() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_IN_USE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUSY
   * @param uilBusy new value to conclude for UIL-BUSY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBusy(java.lang.Object uilBusy) throws G2AccessException {
    setAttributeValue (UIL_BUSY_, uilBusy);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUSY
   * @return the value of the UIL-BUSY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBusy() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUSY_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-MARKED-FOR-DELETE
   * @param uilMarkedForDelete new value to conclude for UIL-MARKED-FOR-DELETE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMarkedForDelete(java.lang.Object uilMarkedForDelete) throws G2AccessException {
    setAttributeValue (UIL_MARKED_FOR_DELETE_, uilMarkedForDelete);
  }

  /**
   * Generated Property Getter for attribute -- UIL-MARKED-FOR-DELETE
   * @return the value of the UIL-MARKED-FOR-DELETE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilMarkedForDelete() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MARKED_FOR_DELETE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-ACTION-TOKEN-LIST
   * @param uilDialogActionTokenList new value to conclude for UIL-DIALOG-ACTION-TOKEN-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogActionTokenList(java.lang.Object uilDialogActionTokenList) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_ACTION_TOKEN_LIST_, uilDialogActionTokenList);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-ACTION-TOKEN-LIST
   * @return the value of the UIL-DIALOG-ACTION-TOKEN-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogActionTokenList() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_ACTION_TOKEN_LIST_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-ACTION-ITEM-LIST
   * @param uilDialogActionItemList new value to conclude for UIL-DIALOG-ACTION-ITEM-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogActionItemList(java.lang.Object uilDialogActionItemList) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_ACTION_ITEM_LIST_, uilDialogActionItemList);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-ACTION-ITEM-LIST
   * @return the value of the UIL-DIALOG-ACTION-ITEM-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogActionItemList() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_ACTION_ITEM_LIST_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-WINDOW-LIST
   * @param uilDialogWindowList new value to conclude for UIL-DIALOG-WINDOW-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogWindowList(java.lang.Object uilDialogWindowList) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_WINDOW_LIST_, uilDialogWindowList);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-WINDOW-LIST
   * @return the value of the UIL-DIALOG-WINDOW-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogWindowList() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_WINDOW_LIST_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-GROBJ-LIST
   * @param uilDialogGrobjList new value to conclude for UIL-DIALOG-GROBJ-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogGrobjList(java.lang.Object uilDialogGrobjList) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_GROBJ_LIST_, uilDialogGrobjList);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-GROBJ-LIST
   * @return the value of the UIL-DIALOG-GROBJ-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogGrobjList() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_GROBJ_LIST_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-USING-NEW-MECHANISM
   * @param uilDialogUsingNewMechanism new value to conclude for UIL-DIALOG-USING-NEW-MECHANISM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDialogUsingNewMechanism(java.lang.Object uilDialogUsingNewMechanism) throws G2AccessException {
    setAttributeValue (UIL_DIALOG_USING_NEW_MECHANISM_, uilDialogUsingNewMechanism);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-USING-NEW-MECHANISM
   * @return the value of the UIL-DIALOG-USING-NEW-MECHANISM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDialogUsingNewMechanism() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DIALOG_USING_NEW_MECHANISM_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ALWAYS-UPDATE-WHEN-MANAGED
   * @param uilAlwaysUpdateWhenManaged new value to conclude for UIL-ALWAYS-UPDATE-WHEN-MANAGED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilAlwaysUpdateWhenManaged(java.lang.Object uilAlwaysUpdateWhenManaged) throws G2AccessException {
    setAttributeValue (UIL_ALWAYS_UPDATE_WHEN_MANAGED_, uilAlwaysUpdateWhenManaged);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ALWAYS-UPDATE-WHEN-MANAGED
   * @return the value of the UIL-ALWAYS-UPDATE-WHEN-MANAGED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilAlwaysUpdateWhenManaged() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ALWAYS_UPDATE_WHEN_MANAGED_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-X-POSITION
   * @param uilXPosition new value to conclude for UIL-X-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilXPosition(java.lang.Object uilXPosition) throws G2AccessException {
    setAttributeValue (UIL_X_POSITION_, uilXPosition);
  }

  /**
   * Generated Property Getter for attribute -- UIL-X-POSITION
   * @return the value of the UIL-X-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilXPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_X_POSITION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-Y-POSITION
   * @param uilYPosition new value to conclude for UIL-Y-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilYPosition(java.lang.Object uilYPosition) throws G2AccessException {
    setAttributeValue (UIL_Y_POSITION_, uilYPosition);
  }

  /**
   * Generated Property Getter for attribute -- UIL-Y-POSITION
   * @return the value of the UIL-Y-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilYPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_Y_POSITION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-USE-DEFAULT-POSITIONING
   * @param uilUseDefaultPositioning new value to conclude for UIL-USE-DEFAULT-POSITIONING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilUseDefaultPositioning(java.lang.Object uilUseDefaultPositioning) throws G2AccessException {
    setAttributeValue (UIL_USE_DEFAULT_POSITIONING_, uilUseDefaultPositioning);
  }

  /**
   * Generated Property Getter for attribute -- UIL-USE-DEFAULT-POSITIONING
   * @return the value of the UIL-USE-DEFAULT-POSITIONING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilUseDefaultPositioning() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_USE_DEFAULT_POSITIONING_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-LIFT-TO-TOP
   * @param uilAllowLiftToTop new value to conclude for UIL-ALLOW-LIFT-TO-TOP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilAllowLiftToTop(java.lang.Object uilAllowLiftToTop) throws G2AccessException {
    setAttributeValue (UIL_ALLOW_LIFT_TO_TOP_, uilAllowLiftToTop);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-LIFT-TO-TOP
   * @return the value of the UIL-ALLOW-LIFT-TO-TOP attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilAllowLiftToTop() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ALLOW_LIFT_TO_TOP_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-TRANSLATE-DIALOG
   * @param uilTranslateDialog new value to conclude for UIL-TRANSLATE-DIALOG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTranslateDialog(java.lang.Object uilTranslateDialog) throws G2AccessException {
    setAttributeValue (UIL_TRANSLATE_DIALOG_, uilTranslateDialog);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TRANSLATE-DIALOG
   * @return the value of the UIL-TRANSLATE-DIALOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilTranslateDialog() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TRANSLATE_DIALOG_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-GFR-TEXT-RESOURCE-GROUP
   * @param uilGfrTextResourceGroup new value to conclude for UIL-GFR-TEXT-RESOURCE-GROUP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilGfrTextResourceGroup(com.gensym.util.Symbol uilGfrTextResourceGroup) throws G2AccessException {
    setAttributeValue (UIL_GFR_TEXT_RESOURCE_GROUP_, uilGfrTextResourceGroup);
  }

  /**
   * Generated Property Getter for attribute -- UIL-GFR-TEXT-RESOURCE-GROUP
   * @return the value of the UIL-GFR-TEXT-RESOURCE-GROUP attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUilGfrTextResourceGroup() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_GFR_TEXT_RESOURCE_GROUP_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-LANGUAGE
   * @param uilLanguage new value to conclude for UIL-LANGUAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilLanguage(com.gensym.util.Symbol uilLanguage) throws G2AccessException {
    setAttributeValue (UIL_LANGUAGE_, uilLanguage);
  }

  /**
   * Generated Property Getter for attribute -- UIL-LANGUAGE
   * @return the value of the UIL-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUilLanguage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_LANGUAGE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_UPP_GET_DIALOG_LAYOUT_ = Symbol.intern ("UPP-GET-DIALOG-LAYOUT");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-DIALOG::UPP-GET-DIALOG-LAYOUT
   * @return the return from calling UPP-GET-DIALOG-LAYOUT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-DIALOG) = (STRUCTURE)
   */
  @Override
  public  com.gensym.util.Structure uppGetDialogLayout() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_UPP_GET_DIALOG_LAYOUT_, args);
      return (com.gensym.util.Structure)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
