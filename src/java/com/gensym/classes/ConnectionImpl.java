/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ConnectionImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:12 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ConnectionImpl extends com.gensym.classes.ItemImpl implements Connection {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  private static final Symbol
    G2_MAKE_CONNECTION_FOR_USER_ = Symbol.intern ("G2-MAKE-CONNECTION-FOR-USER"),
    G2_GET_CONNECTION_INPUT_AND_OUTPUT_  = Symbol.intern ("G2-GET-CONNECTION-INPUT-AND-OUTPUT");
  /* Overriden Field */
  private static final Symbol
  G2_MAKE_SUBWORKSPACE_ = Symbol.intern ("G2-MAKE-SUBWORKSPACE"),
  G2_GET_SUBWORKSPACE_  = Symbol.intern ("G2-GET-SUBWORKSPACE"),
  G2_REFLECT_ITEM_VERTICALLY_  = Symbol.intern ("G2-REFLECT-ITEM-VERTICALLY"),
  G2_REFLECT_ITEM_HORIZONTALLY_  = Symbol.intern ("G2-REFLECT-ITEM-HORIZONTALLY");
  /* Generated constructors */

  public ConnectionImpl() {
    super();
  }

  public ConnectionImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ConnectionImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - CONNECTION-INPUT-AND-OUTPUT */
  /**
   * @return a Sequence of the {InputObject or False, OutputObject or False}
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  @Override
  public Sequence getConnectionInputAndOutput () throws G2AccessException {
    
        java.lang.Object[] args
          = new java.lang.Object[] {this};
        return (Sequence) callRPC (G2_GET_CONNECTION_INPUT_AND_OUTPUT_, args);
      
  }


  /* Overriden Property - VERTICES-AND-JOIN */

  /**
   * @param otherItemOrStub either the loose end Connection or Entity to
   * which this Connection should be connected.
   * @param makeConnectionMode either MOVING_LOOSE_END_, JOINING_LOOSE_ENDS_,
   * or MAKING_NEW_JUNCTION_BLOCK_;
   * @param connectionPositionSequence a flattend Sequence of the vertices
   * to be set for this connection.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  @Override
  public void setVerticesAndJoin(Item otherItemOrStub,
				 Symbol makeConnectionMode,
				 Sequence connectionPositionSequence) throws G2AccessException   {
    
        java.lang.Object otherItemOrFalse = otherItemOrStub;
        if (otherItemOrStub == null)
          otherItemOrFalse = Boolean.FALSE;
        java.lang.Object[] args = new java.lang.Object[5];
        args[0] = this;
        args[1] = otherItemOrFalse;
        args[2] = makeConnectionMode;
        args[3] = connectionPositionSequence;
        args[4] = Boolean.FALSE;
        callRPC (G2_MAKE_CONNECTION_FOR_USER_, args);
      
  }

  /* Overriden Property - BOUNDS-FROM-WORKSPACE-EVENT */

  /**
   * @undocumented Used to update the CONNECTION-POSITION-SEQUENCE
   * attribute from a WorkspaceEvent
   */
  @Override
  public void setBoundsFromWorkspaceEvent (Structure eventInfo)   {
    
        Structure attributes = getActualAttributes();
        Sequence cxnPosnSeq = (Sequence)
    	  eventInfo.getAttributeValue (TW_WORKSPACE_ITEM_POSITION_, null);
        attributes.setAttributeValue (CONNECTION_POSITION_SEQUENCE_, cxnPosnSeq);
      
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
   * Generated Property Setter for attribute -- CONNECTION-ARROWS
   * @param connectionArrows new value to conclude for CONNECTION-ARROWS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setConnectionArrows(java.lang.Object connectionArrows) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CONNECTION_ARROWS_, connectionArrows);
  }

  /**
   * Generated Property Getter for attribute -- CONNECTION-ARROWS
   * @return the value of the CONNECTION-ARROWS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getConnectionArrows() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTION_ARROWS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- LINE-PATTERN
   * @param linePattern new value to conclude for LINE-PATTERN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLinePattern(java.lang.Object linePattern) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.LINE_PATTERN_, linePattern);
  }

  /**
   * Generated Property Getter for attribute -- LINE-PATTERN
   * @return the value of the LINE-PATTERN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getLinePattern() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LINE_PATTERN_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CONNECTION-POSITION-SEQUENCE
   * @return the value of the CONNECTION-POSITION-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getConnectionPositionSequence() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTION_POSITION_SEQUENCE_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CONNECTION-IS-DIRECTED
   * @return the value of the CONNECTION-IS-DIRECTED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getConnectionIsDirected() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTION_IS_DIRECTED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- CONNECTION-VERTICES
   * @return the value of the CONNECTION-VERTICES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getConnectionVertices() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTION_VERTICES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CONNECTION-STYLE
   * @return the value of the CONNECTION-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getConnectionStyle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTION_STYLE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CONNECTION-OUTPUT
   * @return the value of the CONNECTION-OUTPUT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getConnectionOutput() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTION_OUTPUT_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CONNECTION-INPUT
   * @return the value of the CONNECTION-INPUT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getConnectionInput() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTION_INPUT_);
    return (com.gensym.util.Structure)retnValue;
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
   * Generated Property Getter for attribute -- CROSS-SECTION-PATTERN
   * @return the value of the CROSS-SECTION-PATTERN attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getCrossSectionPatternForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CROSS_SECTION_PATTERN_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- STUB-LENGTH
   * @return the value of the STUB-LENGTH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getStubLengthForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.STUB_LENGTH_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- JUNCTION-BLOCK-CLASS
   * @return the value of the JUNCTION-BLOCK-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getJunctionBlockClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.JUNCTION_BLOCK_CLASS_);
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
