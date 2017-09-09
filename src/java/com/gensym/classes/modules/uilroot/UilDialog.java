/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilDialog.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:16 EDT 2007
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

public interface UilDialog extends com.gensym.classes.modules.uilroot.UilGrobj {

  public static final Symbol UIL_DIALOG_ = Symbol.intern ("UIL-DIALOG");
  static final Symbol g2ClassName = UIL_DIALOG_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_DIALOG_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-INITIATING-CLASS-FOR-DIALOG
   * @return the value of the UIL-INITIATING-CLASS-FOR-DIALOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-INITIATING-CLASS-FOR-DIALOG is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilInitiatingClassForDialog() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-INITIATING-CLASS-FOR-DIALOG
   * @param uilInitiatingClassForDialog new value to conclude for UIL-INITIATING-CLASS-FOR-DIALOG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilInitiatingClassForDialog(java.lang.Object uilInitiatingClassForDialog) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RELATED-ITEM
   * @return the value of the RELATED-ITEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RELATED-ITEM is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getRelatedItem() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RELATED-ITEM
   * @param relatedItem new value to conclude for RELATED-ITEM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRelatedItem(java.lang.Object relatedItem) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TEMPORARY-STORAGE-OBJECT
   * @return the value of the UIL-TEMPORARY-STORAGE-OBJECT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TEMPORARY-STORAGE-OBJECT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTemporaryStorageObject() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TEMPORARY-STORAGE-OBJECT
   * @param uilTemporaryStorageObject new value to conclude for UIL-TEMPORARY-STORAGE-OBJECT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTemporaryStorageObject(java.lang.Object uilTemporaryStorageObject) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-MODE
   * @return the value of the UIL-DIALOG-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-MODE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogMode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-MODE
   * @param uilDialogMode new value to conclude for UIL-DIALOG-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogMode(java.lang.Object uilDialogMode) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-STATUS
   * @return the value of the UIL-DIALOG-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-STATUS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogStatus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-STATUS
   * @param uilDialogStatus new value to conclude for UIL-DIALOG-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogStatus(java.lang.Object uilDialogStatus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-WHICH-BUTTON-PRESSED
   * @return the value of the UIL-WHICH-BUTTON-PRESSED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-WHICH-BUTTON-PRESSED is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilWhichButtonPressed() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-WHICH-BUTTON-PRESSED
   * @param uilWhichButtonPressed new value to conclude for UIL-WHICH-BUTTON-PRESSED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilWhichButtonPressed(java.lang.Object uilWhichButtonPressed) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-RETURN-KEY-BEHAVIOR
   * @return the value of the UIL-RETURN-KEY-BEHAVIOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-RETURN-KEY-BEHAVIOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilReturnKeyBehavior() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-RETURN-KEY-BEHAVIOR
   * @param uilReturnKeyBehavior new value to conclude for UIL-RETURN-KEY-BEHAVIOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilReturnKeyBehavior(java.lang.Object uilReturnKeyBehavior) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TAB-KEY-BEHAVIOR
   * @return the value of the UIL-TAB-KEY-BEHAVIOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TAB-KEY-BEHAVIOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTabKeyBehavior() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TAB-KEY-BEHAVIOR
   * @param uilTabKeyBehavior new value to conclude for UIL-TAB-KEY-BEHAVIOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTabKeyBehavior(java.lang.Object uilTabKeyBehavior) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ABORT-KEY-BEHAVIOR
   * @return the value of the UIL-ABORT-KEY-BEHAVIOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ABORT-KEY-BEHAVIOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAbortKeyBehavior() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ABORT-KEY-BEHAVIOR
   * @param uilAbortKeyBehavior new value to conclude for UIL-ABORT-KEY-BEHAVIOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAbortKeyBehavior(java.lang.Object uilAbortKeyBehavior) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-HAS-MOVABLE-WORKSPACE
   * @return the value of the UIL-DIALOG-HAS-MOVABLE-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-HAS-MOVABLE-WORKSPACE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogHasMovableWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-HAS-MOVABLE-WORKSPACE
   * @param uilDialogHasMovableWorkspace new value to conclude for UIL-DIALOG-HAS-MOVABLE-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogHasMovableWorkspace(java.lang.Object uilDialogHasMovableWorkspace) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-EDIT-BOXES-HAVE-MENUS
   * @return the value of the UIL-DIALOG-EDIT-BOXES-HAVE-MENUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-EDIT-BOXES-HAVE-MENUS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogEditBoxesHaveMenus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-EDIT-BOXES-HAVE-MENUS
   * @param uilDialogEditBoxesHaveMenus new value to conclude for UIL-DIALOG-EDIT-BOXES-HAVE-MENUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogEditBoxesHaveMenus(java.lang.Object uilDialogEditBoxesHaveMenus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-EDIT-EVENT-TRIGGER
   * @return the value of the UIL-EDIT-EVENT-TRIGGER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-EDIT-EVENT-TRIGGER is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEditEventTrigger() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-EDIT-EVENT-TRIGGER
   * @param uilEditEventTrigger new value to conclude for UIL-EDIT-EVENT-TRIGGER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEditEventTrigger(java.lang.Object uilEditEventTrigger) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ACTION-TRIGGER
   * @return the value of the UIL-ACTION-TRIGGER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ACTION-TRIGGER is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilActionTrigger() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ACTION-TRIGGER
   * @param uilActionTrigger new value to conclude for UIL-ACTION-TRIGGER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilActionTrigger(java.lang.Object uilActionTrigger) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ORIGIN
   * @return the value of the UIL-ORIGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ORIGIN is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilOrigin() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ORIGIN
   * @param uilOrigin new value to conclude for UIL-ORIGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilOrigin(java.lang.Object uilOrigin) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW
   * @return the value of the UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAllowMultipleCopiesPerWindow() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW
   * @param uilAllowMultipleCopiesPerWindow new value to conclude for UIL-ALLOW-MULTIPLE-COPIES-PER-WINDOW
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAllowMultipleCopiesPerWindow(java.lang.Object uilAllowMultipleCopiesPerWindow) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-ALLOW-FIELD-EDIT
   * @return the value of the UIL-DIALOG-ALLOW-FIELD-EDIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-ALLOW-FIELD-EDIT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogAllowFieldEdit() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-ALLOW-FIELD-EDIT
   * @param uilDialogAllowFieldEdit new value to conclude for UIL-DIALOG-ALLOW-FIELD-EDIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogAllowFieldEdit(java.lang.Object uilDialogAllowFieldEdit) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION
   * @return the value of the UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogAllowOutsideTextSelection() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION
   * @param uilDialogAllowOutsideTextSelection new value to conclude for UIL-DIALOG-ALLOW-OUTSIDE-TEXT-SELECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogAllowOutsideTextSelection(java.lang.Object uilDialogAllowOutsideTextSelection) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-HOME-MODULE-NAME
   * @return the value of the UIL-DIALOG-HOME-MODULE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-HOME-MODULE-NAME is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogHomeModuleName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-HOME-MODULE-NAME
   * @param uilDialogHomeModuleName new value to conclude for UIL-DIALOG-HOME-MODULE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogHomeModuleName(java.lang.Object uilDialogHomeModuleName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-INSTANCE-POOL-LIMIT
   * @return the value of the UIL-DIALOG-INSTANCE-POOL-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-INSTANCE-POOL-LIMIT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogInstancePoolLimit() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-INSTANCE-POOL-LIMIT
   * @param uilDialogInstancePoolLimit new value to conclude for UIL-DIALOG-INSTANCE-POOL-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogInstancePoolLimit(java.lang.Object uilDialogInstancePoolLimit) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-IN-USE
   * @return the value of the UIL-DIALOG-IN-USE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-IN-USE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogInUse() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-IN-USE
   * @param uilDialogInUse new value to conclude for UIL-DIALOG-IN-USE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogInUse(java.lang.Object uilDialogInUse) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUSY
   * @return the value of the UIL-BUSY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUSY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBusy() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUSY
   * @param uilBusy new value to conclude for UIL-BUSY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBusy(java.lang.Object uilBusy) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MARKED-FOR-DELETE
   * @return the value of the UIL-MARKED-FOR-DELETE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MARKED-FOR-DELETE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMarkedForDelete() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MARKED-FOR-DELETE
   * @param uilMarkedForDelete new value to conclude for UIL-MARKED-FOR-DELETE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMarkedForDelete(java.lang.Object uilMarkedForDelete) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-ACTION-TOKEN-LIST
   * @return the value of the UIL-DIALOG-ACTION-TOKEN-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-ACTION-TOKEN-LIST is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogActionTokenList() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-ACTION-TOKEN-LIST
   * @param uilDialogActionTokenList new value to conclude for UIL-DIALOG-ACTION-TOKEN-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogActionTokenList(java.lang.Object uilDialogActionTokenList) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-ACTION-ITEM-LIST
   * @return the value of the UIL-DIALOG-ACTION-ITEM-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-ACTION-ITEM-LIST is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogActionItemList() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-ACTION-ITEM-LIST
   * @param uilDialogActionItemList new value to conclude for UIL-DIALOG-ACTION-ITEM-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogActionItemList(java.lang.Object uilDialogActionItemList) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-WINDOW-LIST
   * @return the value of the UIL-DIALOG-WINDOW-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-WINDOW-LIST is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogWindowList() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-WINDOW-LIST
   * @param uilDialogWindowList new value to conclude for UIL-DIALOG-WINDOW-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogWindowList(java.lang.Object uilDialogWindowList) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-GROBJ-LIST
   * @return the value of the UIL-DIALOG-GROBJ-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-GROBJ-LIST is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogGrobjList() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-GROBJ-LIST
   * @param uilDialogGrobjList new value to conclude for UIL-DIALOG-GROBJ-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogGrobjList(java.lang.Object uilDialogGrobjList) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DIALOG-USING-NEW-MECHANISM
   * @return the value of the UIL-DIALOG-USING-NEW-MECHANISM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DIALOG-USING-NEW-MECHANISM is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDialogUsingNewMechanism() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DIALOG-USING-NEW-MECHANISM
   * @param uilDialogUsingNewMechanism new value to conclude for UIL-DIALOG-USING-NEW-MECHANISM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDialogUsingNewMechanism(java.lang.Object uilDialogUsingNewMechanism) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ALWAYS-UPDATE-WHEN-MANAGED
   * @return the value of the UIL-ALWAYS-UPDATE-WHEN-MANAGED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ALWAYS-UPDATE-WHEN-MANAGED is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAlwaysUpdateWhenManaged() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ALWAYS-UPDATE-WHEN-MANAGED
   * @param uilAlwaysUpdateWhenManaged new value to conclude for UIL-ALWAYS-UPDATE-WHEN-MANAGED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAlwaysUpdateWhenManaged(java.lang.Object uilAlwaysUpdateWhenManaged) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-X-POSITION
   * @return the value of the UIL-X-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-X-POSITION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilXPosition() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-X-POSITION
   * @param uilXPosition new value to conclude for UIL-X-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilXPosition(java.lang.Object uilXPosition) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-Y-POSITION
   * @return the value of the UIL-Y-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-Y-POSITION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilYPosition() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-Y-POSITION
   * @param uilYPosition new value to conclude for UIL-Y-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilYPosition(java.lang.Object uilYPosition) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-USE-DEFAULT-POSITIONING
   * @return the value of the UIL-USE-DEFAULT-POSITIONING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-USE-DEFAULT-POSITIONING is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUseDefaultPositioning() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-USE-DEFAULT-POSITIONING
   * @param uilUseDefaultPositioning new value to conclude for UIL-USE-DEFAULT-POSITIONING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUseDefaultPositioning(java.lang.Object uilUseDefaultPositioning) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-LIFT-TO-TOP
   * @return the value of the UIL-ALLOW-LIFT-TO-TOP attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ALLOW-LIFT-TO-TOP is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAllowLiftToTop() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-LIFT-TO-TOP
   * @param uilAllowLiftToTop new value to conclude for UIL-ALLOW-LIFT-TO-TOP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAllowLiftToTop(java.lang.Object uilAllowLiftToTop) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TRANSLATE-DIALOG
   * @return the value of the UIL-TRANSLATE-DIALOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TRANSLATE-DIALOG is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTranslateDialog() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TRANSLATE-DIALOG
   * @param uilTranslateDialog new value to conclude for UIL-TRANSLATE-DIALOG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTranslateDialog(java.lang.Object uilTranslateDialog) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-GFR-TEXT-RESOURCE-GROUP
   * @return the value of the UIL-GFR-TEXT-RESOURCE-GROUP attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-GFR-TEXT-RESOURCE-GROUP is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUilGfrTextResourceGroup() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-GFR-TEXT-RESOURCE-GROUP
   * @param uilGfrTextResourceGroup new value to conclude for UIL-GFR-TEXT-RESOURCE-GROUP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilGfrTextResourceGroup(com.gensym.util.Symbol uilGfrTextResourceGroup) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-LANGUAGE
   * @return the value of the UIL-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LANGUAGE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUilLanguage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LANGUAGE
   * @param uilLanguage new value to conclude for UIL-LANGUAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLanguage(com.gensym.util.Symbol uilLanguage) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-DIALOG::UPP-GET-DIALOG-LAYOUT
   * @return the return from calling UPP-GET-DIALOG-LAYOUT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-DIALOG) = (STRUCTURE)
   */
  public  com.gensym.util.Structure uppGetDialogLayout() throws G2AccessException;
  
}
