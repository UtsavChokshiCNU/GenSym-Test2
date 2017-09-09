/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Item.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:25:45 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import java.awt.Rectangle;
import java.util.Vector;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Version;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.AttributeDenotation;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.EventMulticaster;
import com.gensym.jgi.AttributeUncachableException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.NtwIllegalArgumentException;
import com.gensym.util.CorruptionException;

public interface Item extends com.gensym.classes.SystemItem {

  public static final Symbol ITEM_ = com.gensym.util.symbol.G2ClassSymbols.ITEM_;
  static final Symbol g2ClassName = ITEM_;
  static final Symbol[] classInheritancePath = new Symbol[] {ITEM_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - BOUNDS */
  /**
   * @undocumented
   */
  public Rectangle getBounds () throws G2AccessException;
  /**
   * Sets the bounds of this Item
   * @param the new left bound of this Item.
   * @param the new top bound of this Item.
   * @param the new right bound of this Item.
   * @param the new bottom bound of this Item.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void setBounds (int left, int top, int right, int bottom)
       throws G2AccessException;

  /* Overriden Property - CONTAINMENT-HIERARCHY */
  /**
   * @return a Sequence of the Items and/or KbWorkspaces in which this
   * item is contained.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public Sequence getContainmentHierarchy()
       throws G2AccessException;

  /* Overriden Property - CURRENT-USER-MENU-CHOICES */
  /**
   * Retrieves the current set of user-menu-choices applicable for this instance
   * in a particular mode.
   * @param a Symbol indicating the G2 user mode with which to make this
   *   query.
   * @return a Sequence of the UserMenuChoices that are currently availible 
   *   for this item in the given mode.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @deprecated use retrieveCurrentUserMenuChoices()
   */
  public Sequence getCurrentUserMenuChoices(Symbol userMode)
       throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TRANSIENT
   * @return the value of the TRANSIENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TRANSIENT is : 
   * BooleanTruthValue
   *
   */
  public boolean getTransient() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MANUALLY-DISABLED?
   * @return the value of the MANUALLY-DISABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MANUALLY-DISABLED? is : 
   * BooleanTruthValue
   *
   */
  public boolean getManuallyDisabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MANUALLY-DISABLED?
   * @param manuallyDisabled new value to conclude for MANUALLY-DISABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setManuallyDisabled(boolean manuallyDisabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PERMANENT
   * @return the value of the PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PERMANENT is : 
   * BooleanTruthValue
   *
   */
  public boolean getPermanent() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DO-NOT-STRIP-TEXT-MARK
   * @return the value of the DO-NOT-STRIP-TEXT-MARK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DO-NOT-STRIP-TEXT-MARK is : 
   * BooleanTruthValue
   *
   */
  public boolean getDoNotStripTextMark() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DO-NOT-STRIP-TEXT-MARK
   * @param doNotStripTextMark new value to conclude for DO-NOT-STRIP-TEXT-MARK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDoNotStripTextMark(boolean doNotStripTextMark) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STRIP-TEXT-MARK
   * @return the value of the STRIP-TEXT-MARK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STRIP-TEXT-MARK is : 
   * BooleanTruthValue
   *
   */
  public boolean getStripTextMark() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STRIP-TEXT-MARK
   * @param stripTextMark new value to conclude for STRIP-TEXT-MARK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStripTextMark(boolean stripTextMark) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- REPRESENTATION-TYPE
   * @return the value of the REPRESENTATION-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for REPRESENTATION-TYPE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getRepresentationType() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TABLE-HEADER
   * @return the value of the TABLE-HEADER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TABLE-HEADER is : 
   * Text
   *
   */
  public java.lang.String getTableHeader() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEM-WIDTH
   * @return the value of the ITEM-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-WIDTH is : 
   * Integer
   *
   */
  public int getItemWidth() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEM-HEIGHT
   * @return the value of the ITEM-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-HEIGHT is : 
   * Integer
   *
   */
  public int getItemHeight() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEM-Y-POSITION
   * @return the value of the ITEM-Y-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-Y-POSITION is : 
   * Integer
   *
   */
  public int getItemYPosition() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEM-X-POSITION
   * @return the value of the ITEM-X-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-X-POSITION is : 
   * Integer
   *
   */
  public int getItemXPosition() throws G2AccessException;

  /* Overriden  - ITEM Event Listeners Management */
  /* Adder */
  /**
   * Add an ItemListener that will be notified of nofications
   * to this Item. The listener will be called with the initial
   * state of the Item, whenever any of the attributes change, or
   * when the Item is deleted.
   * @param il An ItemListener that is kept in sync with changes to
   *   this Item.
   * @see #com.gensym.util.ItemListener
   * @see #removeItemListener
   */
  public void addItemListener (ItemListener il) throws G2AccessException;
  /* Remover */
  /**
   * Stop listening to all attributes. Must only be called if the
   * listener was added using addItemListener(ItemListener).
   * @see #addItemListener(ItemListener)
   */
  public void removeItemListener (ItemListener il) throws G2AccessException;

  /* Overriden method - REMOVE-ITEM-LISTENER-FOR-THREE-TIERS */
  /**
   * @undocumented
   */
  public void  removeItemListenerForThreeTiers(com.gensym.util.ItemListener l, Sequence subscriptionHandles)
    throws com.gensym.jgi.G2AccessException;

  /* Overriden method - ADD-ITEM-LISTENER-RETRIEVING-STATE-MULTIPLE */
  /**
   * @undocumented
   */
  public Sequence addItemListenerRetrievingStateMultiple (ItemListener l, Sequence denotation_sequences) throws G2AccessException;

  /* Overriden method - REMOVE-ITEM-LISTENER */
  /**
   * Removes the listener as a listener to the attributes specified.
   * @param il the listener to be removed
   * @param attributeNames the attributes from which the listener is being removed
   * @see #addItemListener(ItemListener, Symbol[])
   */
  public void removeItemListener (ItemListener il, Symbol[] attributeNames) throws G2AccessException;

  /* Overriden method - ADD-ITEM-LISTENER */
  /**
   * add itemlistener for specifical attributes
   * @exception G2AccessException If there was a problem communicating with G2.
   * @exception  AttributeUncachableException if one of the
   * <code>attributeNames</code> is not actually cacheable.
   * @author fy  03/05/00
   */
  public void addItemListener (ItemListener il, Symbol[] attributeNames) throws G2AccessException;

  /* Overriden method - RESTORE-NORMAL-SIZE */
  /**
   * Restores this Item to its original size
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void restoreNormalSize() throws G2AccessException;

  /* Overriden method - TRANSFER-OFF */
  /**
   * Tranfers this Item off a workspace or an attribute
   */
  public boolean transferOff () throws G2AccessException;

  /* Overriden method - TRANSFER-TO-ITEM */
  /**
   * @undocumented For VB use only
   */
  public boolean transferToItem (Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException;

  /* Overriden method - TRANSFER-TO-0 */
  /**
   * Transfers this this Item to be the value of an attribute on the
   * target Item.
   * @return true if successful
   * @param targetItem the Item to which this item should be
   * transfered
   * @param attributeName the name of the target attribute for which this Item
   * will be the new value
   * @param classQualifier the name of the class at which the target attribute
   * is defined (to be used when the attribute is overriden). It can be null
   * if the reference is to the default attribute of that name (not
   * overriden or defined at the lowest overriding class).
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public boolean transferTo (Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException;

  /* Overriden method - TRANSFER-TO-WORKSPACE */
  /**
   * @undocumented For VB use only
   */
  public boolean transferToWorkspace (KbWorkspace wksp, int x, int y) throws G2AccessException;

  /* Overriden method - TRANSFER-TO */
  /**
   * Transfers the Item to a kb-workspace
   * @param wksp the target kb-workspace to transfer to
   * @param x the x co-ordinate to which to transfer
   * @param y the y co-ordinate to which to tranfer
   * @return true if the transfer was successful, false otherwise
   */
  public boolean transferTo (KbWorkspace wksp, int x, int y) throws G2AccessException;

  /* Overriden method - RETRIEVE-CURRENT-USER-MENU-CHOICES */
  /**
   * Retrieves the current set of user-menu-choices applicable for this instance
   * in a particular mode.
   * @return a Sequence of the UserMenuChoices that are currently availible 
   *   for this item in the current user mode.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @deprecated use getCurrentUserMenuChoices()
   */
  public Sequence retrieveCurrentUserMenuChoices()
  throws G2AccessException;

  /* Overriden method - IS-PROPRIETARY-THROUGH-CONTAINMENT */
  /**
   * @undocumented
   */
  public boolean isProprietaryThroughContainment () throws G2AccessException;

  /* Overriden method - MOVE-BY-FOR-VB */
  /**
   * @undocumented For VB use only
   */
  public boolean moveByForVB (int xDelta,
			      int yDelta,
			      int pseudoBooleanEnlargeWorkspaceIfNecessary)
       throws G2AccessException;

  /* Overriden method - MOVE-BY */
  /**
   * Moves the item by xDelta/yDelta in the item's workspace.
   * @param enlargeWorkspaceIfNeccessary true if the item should be allowed
   * to move beyond the workspace's margins.
   * @return true if the move was accepted
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public boolean moveBy(int xDelta,
			int yDelta,
			boolean enlargeWorkspaceIfNecessary)
       throws G2AccessException;

  /* Overriden method - MOVE-FOR-VB */
  /**
   * @undocumented For VB use only
   */
  public boolean moveForVB (int x,
			    int y,
			    int pseudoBooleanEnlargeWorkspaceIfNecessary)
       throws G2AccessException;

  /* Overriden method - MOVE */
  /**
   * Moves the item to the point (x, y) in the item's workspace.
   * @param enlargeWorkspaceIfNeccessary true if the item should be allowed
   * to move beyond the workspace's margins.
   * @return true if the move was accepted
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public boolean move(int x,
		      int y,
		      boolean enlargeWorkspaceIfNecessary)
       throws G2AccessException;

  /* Overriden method - G2CLONE */
  /**
   * @return a clone of this item in G2.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public Item g2Clone() throws G2AccessException;

  /* Overriden method - DROP-TO-BOTTOM */
  /**
   * Drops the item to the bottom of  the workspace stacking order
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void dropToBottom () throws G2AccessException;

  /* Overriden method - LIFT-TO-TOP */
  /**
   * Lifts the item to the top of the workspace stacking order
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void liftToTop () throws G2AccessException;

  /* Overriden method - MAKE-TRANSIENT */
  /**
   * Makes this Item transient
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @see #makePermanent
   * @see #getTransient
   */
  public void makeTransient () throws G2AccessException;

  /* Overriden method - MAKE-PERMANENT */
  /**
   * Makes this Item permanent
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @see #makeTransient
   * @see #getPermanent
   */
  public void makePermanent () throws G2AccessException;

  /* Overriden method - IS-ENABLED */
  /**
   * Indicates whether the Item is enabled or disabled.
   * @deprecated use #getManuallyDisabled instead
   * @undocumented
   * @return true if the item is enabled, false otherwise
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @see #enable
   * @see #disable
   */
  public boolean isEnabled () throws G2AccessException;

  /* Overriden method - DISABLE */
  /**
   * Disables this Item in G2. If the Item is already
   * disabled, this method does nothing.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void disable () throws G2AccessException;

  /* Overriden method - ENABLE */
  /**
   * Enables this Item in G2. If the Item is already
   * enabled, this method does nothing.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void enable () throws G2AccessException;

  /* Overriden method - DELETE-FOR-VB */
  /**
   * @undocumented FOr VB use only
   */
  public void deleteForVB (int pseudoBooleanWithPermanencyChecksDisabled,
			   int pseudoBooleanWithoutLeavingStubs) throws G2AccessException;

  /* Overriden method - DELETE */
  /**
   * Deletes this Item in G2.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @param withPermanencyChecksDisabled if true then the Item need not
   *   be transient. Otherwise the item must already have been made
   *   transient.
   * @param withoutLeavingStubs determines whether or not delete any
   *   hanging stubs created as a result of the deletion of this Item.
   */
  public void delete (boolean withPermanencyChecksDisabled,
		      boolean withoutLeavingStubs) throws G2AccessException;

}
