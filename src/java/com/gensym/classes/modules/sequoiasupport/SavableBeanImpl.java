/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SavableBeanImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 0 (H01)
 *
 *          Date: Sat Aug 15 01:03:58 EDT 1998
 *
 */


package com.gensym.classes.modules.sequoiasupport;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;
import java.io.*;
import java.util.Vector;
import com.gensym.message.Trace;
import com.gensym.util.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public class SavableBeanImpl extends ItemImpl implements SavableBean {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  private static final Symbol sizeKey = Symbol.intern("SIZE-IN-BYTES");
  /* Overriden Field */
  private static final Symbol
  G2_MAKE_SUBWORKSPACE_ = Symbol.intern ("G2-MAKE-SUBWORKSPACE"),
    G2_GET_SUBWORKSPACE_
  = Symbol.intern ("G2-GET-SUBWORKSPACE");
  /* Generated constructors */

  public SavableBeanImpl() {
    super();
    // Add the classname, so its all setup to send back to G2
    try { 
      setAttributeValue(CLASS_,SavableBean.g2ClassName);
    }
    catch (G2AccessException e) {}
  }

  public SavableBeanImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes, SavableBean.g2ClassName);
  }


  /* Overriden Property - SUBWORKSPACE */
  /** Property Getter for SUBWORKSPACE */
  @Override
  public KbWorkspace getSubworkspace()
       throws G2AccessException {
    
        java.lang.Object[] args = {this};
        return (KbWorkspace)context.callRPC(G2_GET_SUBWORKSPACE_, args);
      
  }

  /** Property Setter for SUBWORKSPACE */
  @Override
  public void setSubworkspace(KbWorkspace workspace)
       throws G2AccessException   {
    
        java.lang.Object[] args = {workspace, this};
        context.callRPC(G2_MAKE_SUBWORKSPACE_, args);
      
  }

  /**
   * Generated Property Getter for attribute -- INTERNAL-MEDIA-BIN
   * @return the value of the INTERNAL-MEDIA-BIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.MediaBin getInternalMediaBin() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERNAL_MEDIA_BIN_);
    return (com.gensym.classes.MediaBin)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- TRANSIENT
   * @return the value of the TRANSIENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getTransient() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TRANSIENT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- PERMANENT
   * @return the value of the PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPermanent() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PERMANENT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- REPRESENTATION-TYPE
   * @return the value of the REPRESENTATION-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getRepresentationType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.REPRESENTATION_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- TABLE-HEADER
   * @return the value of the TABLE-HEADER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getTableHeader() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TABLE_HEADER_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ITEM-WIDTH
   * @return the value of the ITEM-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getItemWidth() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_WIDTH_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEM-HEIGHT
   * @return the value of the ITEM-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getItemHeight() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_HEIGHT_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEM-Y-POSITION
   * @return the value of the ITEM-Y-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getItemYPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_Y_POSITION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEM-X-POSITION
   * @return the value of the ITEM-X-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getItemXPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_X_POSITION_);
    return ((Integer)retnValue).intValue ();
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
   * Generated Property Getter for attribute -- FOUNDATION-CLASS
   * @return the value of the FOUNDATION-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFoundationClass() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FOUNDATION_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS
   * @return the value of the CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getG2ClassName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAuthorsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getChangeLogForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-NAME
   * @param className new value to conclude for CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassNameForClass(com.gensym.util.Symbol className) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_, className);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-NAME
   * @return the value of the CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getClassNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @param directSuperiorClasses new value to conclude for DIRECT-SUPERIOR-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDirectSuperiorClassesForClass(com.gensym.util.Sequence directSuperiorClasses) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_, directSuperiorClasses);
  }

  /**
   * Generated Property Getter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @return the value of the DIRECT-SUPERIOR-CLASSES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getDirectSuperiorClassesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @param classSpecificAttributes new value to conclude for CLASS-SPECIFIC-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassSpecificAttributesForClass(com.gensym.util.Sequence classSpecificAttributes) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_, classSpecificAttributes);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @return the value of the CLASS-SPECIFIC-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getClassSpecificAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-RESTRICTIONS
   * @return the value of the CLASS-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getClassRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INSTANCE-CONFIGURATION
   * @param instanceConfiguration new value to conclude for INSTANCE-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInstanceConfigurationForClass(com.gensym.util.Sequence instanceConfiguration) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_, instanceConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- INSTANCE-CONFIGURATION
   * @return the value of the INSTANCE-CONFIGURATION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInstanceConfigurationForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getChangeForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-INHERITANCE-PATH
   * @return the value of the CLASS-INHERITANCE-PATH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getClassInheritancePathForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_INHERITANCE_PATH_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INHERITED-ATTRIBUTES
   * @return the value of the INHERITED-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInheritedAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INHERITED_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INITIALIZABLE-SYSTEM-ATTRIBUTES
   * @return the value of the INITIALIZABLE-SYSTEM-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInitializableSystemAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INITIALIZABLE_SYSTEM_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @param attributeInitializations new value to conclude for ATTRIBUTE-INITIALIZATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAttributeInitializationsForClass(com.gensym.util.Sequence attributeInitializations) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_, attributeInitializations);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @return the value of the ATTRIBUTE-INITIALIZATIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getAttributeInitializationsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CLASS
   * @return the value of the SUPERIOR-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSuperiorClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SUPERIOR_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CAPABILITIES-AND-RESTRICTIONS
   * @return the value of the CAPABILITIES-AND-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getCapabilitiesAndRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CAPABILITIES_AND_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTES-SPECIFIC-TO-CLASS
   * @return the value of the ATTRIBUTES-SPECIFIC-TO-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAttributesSpecificToClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTES_SPECIFIC_TO_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- MENU-OPTION
   * @return the value of the MENU-OPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMenuOptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.MENU_OPTION_);
    return (java.lang.Object)retnValue;
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
  
  /* Overriden method - SAVE-OBJECT */
  @Override
  public void saveObject (java.lang.Object obj) throws G2AccessException
 {
    
        if (this instanceof G2ForeignSerializable) {
          try {
    	MediaBin dataBin = ((G2JavaBean)this).getInternalMediaBin ();
    	Vector location = new Vector ();
    	G2BinaryOutputStream mbos = dataBin.makeBinaryOutputStream (location, "object");
    	ObjectOutputStream oos = new ObjectOutputStream (mbos);
    	oos.writeObject (obj);
    	oos.close ();
          } catch (IOException ioe) {
    	Trace.exception (ioe);
    	throw new RuntimeException ("IOException during object write : " + ioe);
          }
        } else
          throw new RuntimeException ("Unsupported Persistence type");
      
  }

  /* Overriden method - RETRIEVE-OBJECT */
  @Override
  public java.lang.Object retrieveObject () throws G2AccessException
 {
    
        if (this instanceof G2ForeignSerializable) {
          try {
    	MediaBin dataBin = ((G2JavaBean)this).getInternalMediaBin ();
    	Vector location = new Vector ();
    	G2BinaryInputStream mbis = dataBin.makeBinaryInputStream (location, "object");
    	Structure metaData = dataBin.describe(location, "object");
    	Integer size
    	  = (Integer) metaData.getAttributeValue(sizeKey,sizeKey);
    	int fileSize = size.intValue();
    	byte[] objectData = new byte[fileSize];
    	for (int i = 0; i<fileSize;i++) {
    	  objectData[i] = (byte)mbis.read();
    	}
    	mbis.close();
    	ByteArrayInputStream bis = new ByteArrayInputStream (objectData);
    	ObjectInputStream ois = new ObjectInputStream (bis);
    	java.lang.Object savedObject = ois.readObject ();
    	return savedObject;
          } catch (ClassNotFoundException cnfe) {
    	Trace.exception (cnfe);
    	throw new RuntimeException ("Class not found during object read : " + cnfe);
          } catch (IOException ioe) {
    	Trace.exception (ioe);
    	throw new RuntimeException ("IOException during object read : " + ioe);
          }
        } else
          throw new RuntimeException ("Unsupported Persistence type");
      
  }

  
}
