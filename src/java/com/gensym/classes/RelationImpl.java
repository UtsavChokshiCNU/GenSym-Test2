/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RelationImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:07:26 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class RelationImpl extends com.gensym.classes.ItemImpl implements Relation {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  private static final Symbol
  G2_MAKE_SUBWORKSPACE_ = Symbol.intern ("G2-MAKE-SUBWORKSPACE"),
  G2_GET_SUBWORKSPACE_  = Symbol.intern ("G2-GET-SUBWORKSPACE"),
  G2_REFLECT_ITEM_VERTICALLY_  = Symbol.intern ("G2-REFLECT-ITEM-VERTICALLY"),
  G2_REFLECT_ITEM_HORIZONTALLY_  = Symbol.intern ("G2-REFLECT-ITEM-HORIZONTALLY");
  /* Generated constructors */

  public RelationImpl() {
    super();
  }

  public RelationImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public RelationImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - SUBWORKSPACE */
  /**
   * @return this Item's subworkspace, if one exists.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  @Override
  public KbWorkspace getSubworkspace()
       throws G2AccessException {
    
        java.lang.Object[] args = {this};
        return (KbWorkspace)context.callRPC(G2_GET_SUBWORKSPACE_, args);
      
  }

  /**
   * @param workspace the KbWorkspace to attempt to set as
   * this Item's subworkspace.  
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call, such as when
   * this Item already has a subworkspace.
   */
  @Override
  public void setSubworkspace(KbWorkspace workspace)
       throws G2AccessException   {
    
        java.lang.Object[] args = {workspace, this};
        context.callRPC(G2_MAKE_SUBWORKSPACE_, args);
      
  }

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAuthors(com.gensym.util.Structure authors) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAuthors() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getChangeLog() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FIRST-CLASS
   * @param firstClass new value to conclude for FIRST-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFirstClass(com.gensym.util.Symbol firstClass) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FIRST_CLASS_, firstClass);
  }

  /**
   * Generated Property Getter for attribute -- FIRST-CLASS
   * @return the value of the FIRST-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFirstClass() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FIRST_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SECOND-CLASS
   * @param secondClass new value to conclude for SECOND-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSecondClass(com.gensym.util.Symbol secondClass) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SECOND_CLASS_, secondClass);
  }

  /**
   * Generated Property Getter for attribute -- SECOND-CLASS
   * @return the value of the SECOND-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getSecondClass() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SECOND_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RELATION-NAME
   * @param relationName new value to conclude for RELATION-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRelationName(com.gensym.util.Symbol relationName) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RELATION_NAME_, relationName);
  }

  /**
   * Generated Property Getter for attribute -- RELATION-NAME
   * @return the value of the RELATION-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getRelationName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RELATION_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INVERSE-OF-RELATION
   * @param inverseOfRelation new value to conclude for INVERSE-OF-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInverseOfRelation(com.gensym.util.Symbol inverseOfRelation) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INVERSE_OF_RELATION_, inverseOfRelation);
  }

  /**
   * Generated Property Getter for attribute -- INVERSE-OF-RELATION
   * @return the value of the INVERSE-OF-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getInverseOfRelation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INVERSE_OF_RELATION_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TYPE-OF-RELATION
   * @param typeOfRelation new value to conclude for TYPE-OF-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTypeOfRelation(com.gensym.util.Symbol typeOfRelation) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TYPE_OF_RELATION_, typeOfRelation);
  }

  /**
   * Generated Property Getter for attribute -- TYPE-OF-RELATION
   * @return the value of the TYPE-OF-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getTypeOfRelation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TYPE_OF_RELATION_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RELATION-IS-SYMMETRIC
   * @param relationIsSymmetric new value to conclude for RELATION-IS-SYMMETRIC
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRelationIsSymmetric(boolean relationIsSymmetric) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RELATION_IS_SYMMETRIC_, new Boolean (relationIsSymmetric));
  }

  /**
   * Generated Property Getter for attribute -- RELATION-IS-SYMMETRIC
   * @return the value of the RELATION-IS-SYMMETRIC attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getRelationIsSymmetric() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RELATION_IS_SYMMETRIC_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- RELATION-IS-PERMANENT
   * @param relationIsPermanent new value to conclude for RELATION-IS-PERMANENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRelationIsPermanent(boolean relationIsPermanent) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RELATION_IS_PERMANENT_, new Boolean (relationIsPermanent));
  }

  /**
   * Generated Property Getter for attribute -- RELATION-IS-PERMANENT
   * @return the value of the RELATION-IS-PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getRelationIsPermanent() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RELATION_IS_PERMANENT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEMS-IN-THIS-RELATION
   * @return the value of the ITEMS-IN-THIS-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getItemsInThisRelation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEMS_IN_THIS_RELATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAY-ITEMS
   * @return the value of the ATTRIBUTE-DISPLAY-ITEMS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getAttributeDisplayItems() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAY_ITEMS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- NAME-BOX-ITEM
   * @return the value of the NAME-BOX-ITEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getNameBoxItem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NAME_BOX_ITEM_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ICON-VARIABLES
   * @param iconVariables new value to conclude for ICON-VARIABLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIconVariables(com.gensym.util.Structure iconVariables) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ICON_VARIABLES_, iconVariables);
  }

  /**
   * Generated Property Getter for attribute -- ICON-VARIABLES
   * @return the value of the ICON-VARIABLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getIconVariables() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ICON_VARIABLES_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ICON-COLOR
   * @param iconColor new value to conclude for ICON-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIconColor(com.gensym.util.Symbol iconColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ICON_COLOR_, iconColor);
  }

  /**
   * Generated Property Getter for attribute -- ICON-COLOR
   * @return the value of the ICON-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getIconColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ICON_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ICON-REFLECTION
   * @param iconReflection new value to conclude for ICON-REFLECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIconReflection(com.gensym.util.Symbol iconReflection) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ICON_REFLECTION_, iconReflection);
  }

  /**
   * Generated Property Getter for attribute -- ICON-REFLECTION
   * @return the value of the ICON-REFLECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getIconReflection() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ICON_REFLECTION_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ICON-HEADING
   * @param iconHeading new value to conclude for ICON-HEADING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIconHeading(int iconHeading) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ICON_HEADING_, iconHeading);
  }

  /**
   * Generated Property Getter for attribute -- ICON-HEADING
   * @return the value of the ICON-HEADING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getIconHeading() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ICON_HEADING_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- ITEM-COLOR-PATTERN
   * @param itemColorPattern new value to conclude for ITEM-COLOR-PATTERN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setItemColorPattern(com.gensym.util.Structure itemColorPattern) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ITEM_COLOR_PATTERN_, itemColorPattern);
  }

  /**
   * Generated Property Getter for attribute -- ITEM-COLOR-PATTERN
   * @return the value of the ITEM-COLOR-PATTERN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getItemColorPattern() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_COLOR_PATTERN_);
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
   * Generated Property Setter for attribute -- CURRENT-ATTRIBUTE-DISPLAYS
   * @param currentAttributeDisplays new value to conclude for CURRENT-ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCurrentAttributeDisplays(com.gensym.util.Sequence currentAttributeDisplays) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CURRENT_ATTRIBUTE_DISPLAYS_, currentAttributeDisplays);
  }

  /**
   * Generated Property Getter for attribute -- CURRENT-ATTRIBUTE-DISPLAYS
   * @return the value of the CURRENT-ATTRIBUTE-DISPLAYS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getCurrentAttributeDisplays() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CURRENT_ATTRIBUTE_DISPLAYS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NAME-BOX
   * @param nameBox new value to conclude for NAME-BOX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNameBox(com.gensym.util.Structure nameBox) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NAME_BOX_, nameBox);
  }

  /**
   * Generated Property Getter for attribute -- NAME-BOX
   * @return the value of the NAME-BOX attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getNameBox() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NAME_BOX_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STRIPE-COLOR
   * @param stripeColor new value to conclude for STRIPE-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setStripeColor(com.gensym.util.Symbol stripeColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.STRIPE_COLOR_, stripeColor);
  }

  /**
   * Generated Property Getter for attribute -- STRIPE-COLOR
   * @return the value of the STRIPE-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getStripeColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.STRIPE_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- BORDER-COLOR
   * @param borderColor new value to conclude for BORDER-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBorderColor(com.gensym.util.Symbol borderColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BORDER_COLOR_, borderColor);
  }

  /**
   * Generated Property Getter for attribute -- BORDER-COLOR
   * @return the value of the BORDER-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getBorderColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BORDER_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TEXT-COLOR
   * @param textColor new value to conclude for TEXT-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTextColor(com.gensym.util.Symbol textColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TEXT_COLOR_, textColor);
  }

  /**
   * Generated Property Getter for attribute -- TEXT-COLOR
   * @return the value of the TEXT-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getTextColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TEXT_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FOREGROUND-COLOR
   * @param foregroundColor new value to conclude for FOREGROUND-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setForegroundColor(com.gensym.util.Symbol foregroundColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FOREGROUND_COLOR_, foregroundColor);
  }

  /**
   * Generated Property Getter for attribute -- FOREGROUND-COLOR
   * @return the value of the FOREGROUND-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getForegroundColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FOREGROUND_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- BACKGROUND-COLOR
   * @param backgroundColor new value to conclude for BACKGROUND-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBackgroundColor(com.gensym.util.Symbol backgroundColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BACKGROUND_COLOR_, backgroundColor);
  }

  /**
   * Generated Property Getter for attribute -- BACKGROUND-COLOR
   * @return the value of the BACKGROUND-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getBackgroundColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BACKGROUND_COLOR_);
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
   * Generated Property Getter for attribute -- ICON-DESCRIPTION
   * @return the value of the ICON-DESCRIPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getIconDescriptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ICON_DESCRIPTION_);
    return (com.gensym.util.Structure)retnValue;
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
  
  /* Overriden method - REFLECT-VERTICALLY */
  @Override
  public Symbol reflectVertically() throws G2AccessException
 {
    
        java.lang.Object[] args = {this};
        Symbol retnvalue = (Symbol)
          callRPC(G2_REFLECT_ITEM_VERTICALLY_, args);
        return retnvalue;
      
  }

  /* Overriden method - REFLECT-HORIZONTALLY */
  @Override
  public Symbol reflectHorizontally() throws G2AccessException
 {
    
        java.lang.Object[] args = {this};
        Symbol retnvalue = (Symbol)
          callRPC(G2_REFLECT_ITEM_HORIZONTALLY_, args);
        return retnvalue;
      
  }

  
}
