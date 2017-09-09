/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ItemSpecialImpl.java
 *
 *	 Author:
 *		Robert Penny		Aug/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.classes;

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

public class ItemSpecialImpl extends G2__BaseImpl {

  static final G2Version G2_VERSION_FOR_USER_MENU_CHOICES_FOR_SESSION = new G2Version(5, 1, "Rev", 1, "BC10");

  private static final Symbol MODIFY_ = Symbol.intern ("MODIFY"),
    DELETE_ = Symbol.intern ("DELETE"),
    SUBSCRIPTION_HANDLE_ = Symbol.intern ("SUBSCRIPTION-HANDLE"),
    INITIAL_VALUE_ = Symbol.intern ("INITIAL-VALUE");

  // This should be constrained to Entity and TextBox

  /**
   * @undocumented
   */
  @Override
  public Rectangle getBounds () throws G2AccessException {
    int xCenter = ((Integer)getAttributeValue (ITEM_X_POSITION_)).intValue ();
    int yCenter = ((Integer)getAttributeValue (ITEM_Y_POSITION_)).intValue ();
    int width   = ((Integer)getAttributeValue (ITEM_WIDTH_)).intValue ();
    int height  = ((Integer)getAttributeValue (ITEM_HEIGHT_)).intValue ();
    int x       = xCenter - (width >> 1);
    int y       = yCenter + (height >> 1);
    return new Rectangle (x, y, width, height);
  }

  private static final Symbol
    G2_DELETE_ITEM_                  = Symbol.intern ("G2-DELETE-ITEM"),
    G2_ENABLE_ITEM_                  = Symbol.intern ("G2-ENABLE-ITEM"),
    G2_DISABLE_ITEM_                 = Symbol.intern ("G2-DISABLE-ITEM"),
    G2_MAKE_PERMANENT_               = Symbol.intern ("G2-MAKE-PERMANENT"),
    G2_MAKE_TRANSIENT_               = Symbol.intern ("G2-MAKE-TRANSIENT"),
    G2_LIFT_ITEM_TO_TOP_             = Symbol.intern ("G2-LIFT-ITEM-TO-TOP"),
    G2_DROP_ITEM_TO_BOTTOM_          = Symbol.intern ("G2-DROP-ITEM-TO-BOTTOM"),
    G2_CLONE_ITEM_                   = Symbol.intern ("G2-CLONE-ITEM"),
    G2_MOVE_WS_ITEM_                 = Symbol.intern ("G2-MOVE-WS-ITEM"),
    G2_MOVE_WS_ITEM_BY_              = Symbol.intern ("G2-MOVE-WS-ITEM-BY"),
    G2_GET_CONTAINMENT_HIERARCHY_    = Symbol.intern ("G2-GET-CONTAINMENT-HIERARCHY"),
    G2_GET_CURRENT_USER_MENU_CHOICES_= Symbol.intern ("G2-GET-CURRENT-USER-MENU-CHOICES"),
    G2_TRANSFER_ITEM_                = Symbol.intern ("G2-TRANSFER-ITEM"),
    G2_CHANGE_SIZE_OF_ITEM_PER_AREA_ = Symbol.intern ("G2-CHANGE-SIZE-OF-ITEM-PER-AREA"),
    G2_RESTORE_ITEM_TO_NORMAL_SIZE_  = Symbol.intern ("G2-RESTORE-ITEM-TO-NORMAL-SIZE"),  
    G2_GET_DIALOG_                   = Symbol.intern ("G2-GET-DIALOG");

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
		      boolean withoutLeavingStubs) throws G2AccessException
  {
   //Note: calling the GensymApplication method enables e-SCOR and ReThink to 
   //override the behavior of delete.  The default behavior will take place if 
   //the application returns FALSE (or there is no application in place).
   if ((com.gensym.core.GensymApplication.getApplication() == null) ||
       (com.gensym.core.GensymApplication.getApplication().deleteItem
	(this,withPermanencyChecksDisabled, withoutLeavingStubs) == false)) {
     java.lang.Object[] args = new java.lang.Object[]
       {this, withPermanencyChecksDisabled ? Boolean.TRUE : Boolean.FALSE,
	  withoutLeavingStubs ? Boolean.TRUE : Boolean.FALSE};
       context.callRPC (G2_DELETE_ITEM_, args);
   }
  }

  /**
   * @undocumented FOr VB use only
   */
  public void deleteForVB (int pseudoBooleanWithPermanencyChecksDisabled,
			   int pseudoBooleanWithoutLeavingStubs) throws G2AccessException {
    delete ((pseudoBooleanWithPermanencyChecksDisabled != 0), (pseudoBooleanWithoutLeavingStubs != 0));
  }

  /**
   * Enables this Item in G2. If the Item is already
   * enabled, this method does nothing.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void enable () throws G2AccessException {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this};
    Boolean retnvalue = (Boolean)
      context.callRPC(G2_ENABLE_ITEM_, args);
    //return retnvalue.booleanValue ();
  }

  /**
   * Disables this Item in G2. If the Item is already
   * disabled, this method does nothing.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void disable () throws G2AccessException {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this};
    Boolean retnvalue = (Boolean)
      context.callRPC(G2_DISABLE_ITEM_, args);
    //return retnvalue.booleanValue ();
  }

  private static final Symbol G2_ITEM_IS_DISABLED_ = Symbol.intern ("G2-ITEM-IS-DISABLED");

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
  public boolean isEnabled () throws G2AccessException {
    return !getManuallyDisabled();
  }

  /**
   * Makes this Item permanent
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @see #makeTransient
   * @see #getPermanent
   */
  public void makePermanent () throws G2AccessException {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this};
    context.callRPC(G2_MAKE_PERMANENT_, args);
  }

  /**
   * Makes this Item transient
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @see #makePermanent
   * @see #getTransient
   */
  public void makeTransient () throws G2AccessException {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this};
    context.callRPC(G2_MAKE_TRANSIENT_, args);
  }

  /**
   * Lifts the item to the top of the workspace stacking order
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void liftToTop () throws G2AccessException {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this};
    context.callRPC (G2_LIFT_ITEM_TO_TOP_, args);
  }

  /**
   * Drops the item to the bottom of  the workspace stacking order
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void dropToBottom () throws G2AccessException {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this};
    context.callRPC (G2_DROP_ITEM_TO_BOTTOM_, args);
  }

  /**
   * @return a clone of this item in G2.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public Item g2Clone() throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this};
    return (Item) context.callRPC(G2_CLONE_ITEM_, args);
  }

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
       throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[5];
    args[0] = this;
    args[1] = new Integer (x);
    args[2] = new Integer (y);
    args[3] = new Boolean(enlargeWorkspaceIfNecessary);
    args[4] = Boolean.FALSE;   // transient-change-p
    Boolean retnvalue = (Boolean)
      context.callRPC(G2_MOVE_WS_ITEM_, args);
    return retnvalue.booleanValue ();
  }

  /**
   * @undocumented For VB use only
   */
  public boolean moveForVB (int x,
			    int y,
			    int pseudoBooleanEnlargeWorkspaceIfNecessary)
       throws G2AccessException {
    return move (x, y, (pseudoBooleanEnlargeWorkspaceIfNecessary != 0));
  }

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
       throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[5];
    args[0] = this;
    args[1] = new Integer (xDelta);
    args[2] = new Integer (yDelta);
    args[3] = new Boolean(enlargeWorkspaceIfNecessary);
    args[4] = Boolean.FALSE;  // transient-change-p  
    Boolean retnvalue = (Boolean)
      context.callRPC(G2_MOVE_WS_ITEM_BY_, args);
    return retnvalue.booleanValue ();
  }

  /**
   * @undocumented For VB use only
   */
  public boolean moveByForVB (int xDelta,
			      int yDelta,
			      int pseudoBooleanEnlargeWorkspaceIfNecessary)
       throws G2AccessException {
    return moveBy (xDelta, yDelta, (pseudoBooleanEnlargeWorkspaceIfNecessary != 0));
  }


  /**
   * @return a Sequence of the Items and/or KbWorkspaces in which this
   * item is contained.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */              
  public Sequence getContainmentHierarchy()
       throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this};
    return (Sequence)callRPC(G2_GET_CONTAINMENT_HIERARCHY_, args);
  }

  /**
   * @undocumented
   */
  public boolean isProprietaryThroughContainment () throws G2AccessException {

    Boolean isProprietaryObject = data.itemIsProprietaryThroughContainment;
    if (isProprietaryObject != null)
      return isProprietaryObject.booleanValue ();

    boolean isProprietary = false;

    ItemData principalData = getPrincipalData();
    if (this instanceof KbWorkspace) {
      isProprietary = ((KbWorkspace)this).workspaceIsProprietary(null, -1);
    } else {
      isProprietary =
	(principalData.parentWorkspace == null ? false :
	 principalData.parentWorkspace.workspaceIsProprietary(null, -1));
    }

    if(isProprietary)
      principalData.itemIsProprietaryThroughContainment = Boolean.TRUE;
    else
      principalData.itemIsProprietaryThroughContainment = Boolean.FALSE;

    return isProprietary;
  }

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
       throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this, userMode};
    return (Sequence)callRPC(G2_GET_CURRENT_USER_MENU_CHOICES_, args);
  }

  private static final Symbol G2_GET_CURRENT_USER_MENU_CHOICES_FOR_SESSION_ = Symbol.intern ("G2-GET-CURRENT-USER-MENU-CHOICES-FOR-SESSION");

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
  throws G2AccessException {
    checkItemValidity ();

    G2Gateway context = (G2Gateway)getContext();
    UiClientSession session =
      (UiClientSession) invokeTwAccessMethod(context, "getSession", null, null);
			 
    G2Version currentVersion = context.getG2Version();

    if (currentVersion.compareTo(G2_VERSION_FOR_USER_MENU_CHOICES_FOR_SESSION) == G2Version.OLDER) {
      return getCurrentUserMenuChoices(session.getUiClientSessionUserMode());
    } else {    
      java.lang.Object[] args = new java.lang.Object[] {this, session};
      return (Sequence)callRPC(G2_GET_CURRENT_USER_MENU_CHOICES_FOR_SESSION_, args);
    }
  }

  /**
   * @return true if successful
   * @param targetItem the Item or workspace to which this item should be
   * transfered
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  private boolean transfer (Item targetItem,
			    int x,
			    int y,
			    java.lang.Object attributeNameOrFalse,
			    java.lang.Object classQualifierOrFalse)
       throws G2AccessException
  {
    checkItemValidity ();
    if (targetItem != null)
      ((G2__BaseImpl)targetItem).checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[6];
    args[0] = this;
    args[1] = (targetItem != null ? 
	       (java.lang.Object)targetItem : (java.lang.Object)Boolean.FALSE);
    args[2] = new Integer (x);
    args[3] = new Integer (y);
    args[4] = attributeNameOrFalse;
    args[5] = (classQualifierOrFalse == null ?
               Boolean.FALSE : classQualifierOrFalse);
    Boolean retnvalue = (Boolean)
      context.callRPC(G2_TRANSFER_ITEM_, args);
    return retnvalue.booleanValue ();
  }

  /**
   * Transfers the Item to a kb-workspace
   * @param wksp the target kb-workspace to transfer to
   * @param x the x co-ordinate to which to transfer
   * @param y the y co-ordinate to which to tranfer
   * @return true if the transfer was successful, false otherwise
   */
  public boolean transferTo (KbWorkspace wksp, int x, int y) throws G2AccessException {
    return transfer (wksp, x, y, Boolean.FALSE, Boolean.FALSE);
  }

  /**
   * @undocumented For VB use only
   */
  public boolean transferToWorkspace (KbWorkspace wksp, int x, int y) throws G2AccessException {
    return transferTo (wksp, x, y);
  }

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
  public boolean transferTo (Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException {
    return transfer (targetItem, 0, 0, attributeName, classQualifier);
  }

  /**
   * @undocumented For VB use only
   */
  public boolean transferToItem (Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException {
    return transferTo (targetItem, attributeName, classQualifier);
  }

  /**
   * Tranfers this Item off a workspace or an attribute
   */
  public boolean transferOff () throws G2AccessException {
    return transfer (null, 0, 0, Boolean.FALSE, Boolean.FALSE);
  }
  

  private static final Symbol DEFAULT_ = Symbol.intern("DEFAULT");

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
       throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args =
      {this,
       new Integer (left), new Integer (top),
       new Integer (right), new Integer (bottom),
       DEFAULT_};
    callRPC (G2_CHANGE_SIZE_OF_ITEM_PER_AREA_, args);
  }

  /**
   * Restores this Item to its original size
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */                                   
  public void restoreNormalSize() throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args = {this};
    callRPC(G2_RESTORE_ITEM_TO_NORMAL_SIZE_, args);
  }

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
  public void addItemListener (ItemListener il) throws G2AccessException {

    addItemListener (il, WILDCARD_ARRAY);
      
  }

  private boolean checkWILDCARD(Symbol[] attributeNames) throws  G2AccessException {
    boolean hasWILDCARD = false;

        for (int i=0; i < attributeNames.length; i++) {
          if (attributeNames[i].equals(WILDCARD_)) {
            hasWILDCARD = true;
            break;
          }
        }
        if (hasWILDCARD && (attributeNames.length > 1))
          throw new G2AccessException("Wrong arguments. attributeNames should be either contain WILDCARD only or any attribute names without WILDCARD.");

        return hasWILDCARD;
  }

  /**
   * add itemlistener for specifical attributes
   * @exception G2AccessException If there was a problem communicating with G2.
   * @exception  AttributeUncachableException if one of the
   * <code>attributeNames</code> is not actually cacheable.
   * @author fy  03/05/00
   */
  public void addItemListener (ItemListener il, Symbol[] attributeNames) throws G2AccessException {

        boolean hasWILDCARD = checkWILDCARD (attributeNames);
        checkItemValidity ();

        //check if attributeName is cachable
        Vector attrUncachable = new Vector();
        for (int i =0; i <attributeNames.length; i++) {
          if (!attributeSendsUpdates (attributeNames[i]))
            attrUncachable.addElement(attributeNames[i]);
        }
        if (!attrUncachable.isEmpty())
          throw new AttributeUncachableException(attrUncachable);


        ItemData principalData = getPrincipalData();
        synchronized (principalData) {
          if (principalData.subscriptionManager == null)
            principalData.subscriptionManager = new SubscriptionManager();

          principalData.subscriptionManager.addEntry(il, attributeNames);
          Vector addedSubscriptions = principalData.subscriptionManager.getAddedSubscriptions();
          Vector removedSubscriptions = principalData.subscriptionManager.getRemovedSubscriptions();
          if (addedSubscriptions != null && removedSubscriptions != null) {
              subscribe(addedSubscriptions);
              unsubscribe (removedSubscriptions);
          } else if (addedSubscriptions != null)
              subscribe(addedSubscriptions);

        }

        // process initial values
        Structure attributes = null;
        Sequence attributeDenotations = null;
        int sHandle = 0;
        if (hasWILDCARD) {
          attributes = getAttributes ();
          attributeDenotations = AttributeDenotation.WILDCARD_DENOTATION;
          sHandle = principalData.subscriptionManager.getHandleByAttributeName(attributeNames[0]);

        } else {
          // make structure for multiple attributes
          java.lang.Object[] objs = new java.lang.Object[attributeNames.length];
          try {
            for (int i=0; i < attributeNames.length; i++) {
              objs[i] = principalData.attributes.getAttributeValue(attributeNames[i]);
            }
            attributes = new Structure(attributeNames, objs);
          }
          catch (NoSuchAttributeException ex) {
            throw new CorruptionException(ex, "No such attribute.");
          }
	  catch (NtwIllegalArgumentException ex) {
	    throw new CorruptionException(ex, "Error making Structure");
          }

          // for multiple attributes, a single "denotation" doesn't make
	  // sense. event.getDenotation() doesn't really make sense in
	  // receivedInitialValues, but if someone calls it there anyway,
	  // at least they won't be confused by a misleading data structure...
          attributeDenotations = null;
        }
        ItemEvent itemEvent = new ItemEvent (this, INITIAL_VALUE_, this,
					     attributeDenotations,
					     attributes, USER_DATA,
					     sHandle);
        il.receivedInitialValues (itemEvent);
  }

  /**
   * Stop listening to all attributes. Must only be called if the
   * listener was added using addItemListener(ItemListener).
   * @see #addItemListener(ItemListener)
   */
  public void removeItemListener (ItemListener il) throws G2AccessException   {
    removeItemListener (il, WILDCARD_ARRAY);
  }

  // For interested attributes to be removed   - fy
  /**
   * Removes the listener as a listener to the attributes specified.
   * @param il the listener to be removed
   * @param attributeNames the attributes from which the listener is being removed
   * @see #addItemListener(ItemListener, Symbol[])
   */
  public void removeItemListener (ItemListener il, Symbol[] attributeNames) throws G2AccessException   {
        checkWILDCARD (attributeNames);

        ItemData principalData = getPrincipalData();
        if (principalData.subscriptionManager == null) return;
        principalData.subscriptionManager.removeEntry(il, attributeNames);
        Vector addedSubscriptions = principalData.subscriptionManager.getAddedSubscriptions();
        Vector removedSubscriptions = principalData.subscriptionManager.getRemovedSubscriptions();
        if ((addedSubscriptions != null) && (removedSubscriptions != null)) {
          subscribe(addedSubscriptions);
          unsubscribe (removedSubscriptions);
        } else if (removedSubscriptions != null)
          unsubscribe(removedSubscriptions);
        

  }

  /**
   * @undocumented
   */
  @Override
  public Sequence addItemListenerRetrievingStateMultiple (ItemListener l, Sequence denotation_sequences) throws G2AccessException {
    Symbol[] attributeNames = new Symbol[denotation_sequences.size()];
    for (int i=0; i < attributeNames.length; i++) {
      attributeNames[i] = ((AttributeDenotation) denotation_sequences.elementAt(i)).getAttributeName();
    }
    synchronized (data) {
      addItemListener(l, attributeNames);
      return makeSnapshot(attributeNames);
    }
  }

  // overriden method for three-tier only - fy 03/01/00
  /**
   * @undocumented
   */
   @Override
   public void  removeItemListenerForThreeTiers(com.gensym.util.ItemListener l, Sequence subscriptionHandles)
    throws com.gensym.jgi.G2AccessException
 {
    
          Symbol[] attrNames = new Symbol[subscriptionHandles.size()];
          for (int i=0; i < subscriptionHandles.size(); i++) {
            attrNames[i] = data.subscriptionManager.getAttributeNameByHandle(((Integer) subscriptionHandles.elementAt(i)).intValue());
          }
          removeItemListener(l, attrNames);

  }



}
