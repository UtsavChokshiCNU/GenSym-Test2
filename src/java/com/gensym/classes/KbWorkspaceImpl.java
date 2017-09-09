/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      KbWorkspaceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:00:22 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import java.util.Vector;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.Enumeration;
import com.gensym.util.symbol.G2ClassSymbols;

public class KbWorkspaceImpl extends com.gensym.classes.ItemImpl implements KbWorkspace {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  public static final boolean traceOn = false;
  /* Overriden Field */
  private static MessageKey traceKey = Trace.registerMessageKey ("com.gensym.util.classes",
			    KbWorkspaceImpl.class);
  /* Overriden Field */
  private static Resource i18nTrace = Trace.getBundle("com.gensym.classes.TraceMessages");
  /* Overriden Field */
  private static Resource i18n = Resource.getBundle("com.gensym.classes.Messages");
  /* Overriden Field */
  private static final Symbol WORKSPACE_INITIAL_DATA_ = Symbol.intern ("WORKSPACE-INITIAL-DATA");
  private static final Symbol SUBSCRIPTION_HANDLE_     = Symbol.intern ("SUBSCRIPTION-HANDLE");
  private static final Symbol TW_WORKSPACE_ITEM_PROXY_ = Symbol.intern ("TW-WORKSPACE-ITEM-PROXY");
  private static final Symbol ITEM_INFO_LIST_          = Symbol.intern ("ITEM-INFO-LIST");
  private static final Symbol ITEM_DATA_LIST_ = Symbol.intern("ITEM-DATA-LIST");
  private static final Symbol G2_SHOW_WORKSPACE_ = Symbol.intern ("G2-SHOW-WORKSPACE");	
  private static final Symbol G2_HIDE_WORKSPACE_ = Symbol.intern ("G2-HIDE-WORKSPACE");
  /* Overriden Field */
  private static final Symbol INITIAL_DOWNLOAD_ = Symbol.intern ("INITIAL-DOWNLOAD");
  /* Overriden Field */
  private static final Symbol POSITION_OR_NEXT_LOWER_ITEM_ = Symbol.intern ("POSITION-OR-NEXT-LOWER-ITEM");
  /* Overriden Field */
  private static final Symbol WORKSPACE_BACKGROUND_COLOR_ = Symbol.intern ("WORKSPACE-BACKGROUND-COLOR");
  /* Overriden Field */
  private static final Symbol WORKSPACE_DIMENSIONS_ = Symbol.intern ("WORKSPACE-DIMENSIONS");
  /* Overriden Field */
  private static final Symbol WORKSPACE_FOREGROUND_COLOR_ = Symbol.intern ("WORKSPACE-FOREGROUND-COLOR");
  /* Overriden Field */
  private static final Symbol G2_GET_UPDATED_WORKSPACE_INFORMATION_ = Symbol.intern ("G2-GET-UPDATED-WORKSPACE-INFORMATION");
  /* Overriden Field */
  public static final Symbol ITEM_REMOVE_ = Symbol.intern ("ITEM-REMOVE");
  /* Overriden Field */
  public static final Symbol ITEM_INSERT_ = Symbol.intern ("ITEM-INSERT");
  /* Overriden Field */
  private static final Symbol PROPRIETARY_PACKAGE_ = Symbol.intern ("PROPRIETARY-PACKAGE");
  /* Overriden Field */
  private static final Symbol G2_GET_TEXT_OF_ATTRIBUTE_ = Symbol.intern ("G2-GET-TEXT-OF-ATTRIBUTE");
  /* Overriden Field */
  private static final Symbol LEFT_ = Symbol.intern ("LEFT");
  private static final Symbol TOP_ = Symbol.intern ("TOP");
  private static final Symbol RIGHT_ = Symbol.intern ("RIGHT");
  private static final Symbol BOTTOM_ = Symbol.intern ("BOTTOM");
  /* Overriden Field */
  private static final Symbol garbageMode = Symbol.intern("FOO-MODE");
  /* Overriden Field */
  /* communicate between workspace document and workspace about sizing.  
     Otherwise you have a race.  But not export to users. */

  private boolean shrinkwrapping = false;
  /* Generated constructors */

  public KbWorkspaceImpl() {
    super();
  }

  public KbWorkspaceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public KbWorkspaceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - G2WKSP-SUBSCRIPTION-HANDLE */
  /**
   * @undocumented
   * @deprecated
   */
  @Override
  public int getG2WkspSubscriptionHandle() {
    
        return ((WorkspaceData)data).activeSubscriptionIndex;
      
  }


  /* Overriden Property - ITEMS */
  /**
   * @undocumented Returns the items on the workspace
   * if it is subscribed to. Returns null otherwise.
   */
  @Override
  public Item[] getItems () {
    
        synchronized (data) {
          Sequence items = ((WorkspaceData)data).items;
          if (items == null)
    	return null;
          Item[] array = new Item[items.size()];
          items.copyInto(array);
          return array;
        }
      
  }


  /* Overriden Property - SHRINKWRAPPING */
  /**
   * @undocumented
   */
  @Override
  public boolean getShrinkwrapping () {
    
        return shrinkwrapping;
      
  }

  /**
   * @undocumented
   */
  @Override
  public void setShrinkwrapping (boolean value)   {
    
        shrinkwrapping = value;
      
  }

  /* Overriden Property - CONTAINMENT-HIERARCHY-ITEM-CONFIGURATION-SNAPSHOT */
  /**
   * @undocumented
   */
  @Override
  public Vector getContainmentHierarchyItemConfigurationSnapshot()
  throws G2AccessException {
    
        Vector returnValue;
        synchronized (data) {
          returnValue = ((WorkspaceData)data).containmentHierarchyItemConfigurationSnapshot;
        }
        
        if (returnValue == null) {
          Sequence containmentHierarchy = getContainmentHierarchy();
          if (containmentHierarchy == null)             
    	containmentHierarchy = new Sequence();
          containmentHierarchy.insertElementAt(this, 0);
          returnValue = new Vector();
          int size = containmentHierarchy.size();
          for (int i = 0; i < size; i++) {
    	Item item = (Item)containmentHierarchy.elementAt(i);
    	Sequence configurations = item.getItemConfigurationSnapshot();
    	if (configurations != null)
    	  returnValue.addElement(configurations);
          }
          KbConfiguration kbConfiguration =
    	(KbConfiguration)context.getUniqueNamedItem(G2ClassSymbols.KB_CONFIGURATION_,
    						    G2ClassSymbols.KB_CONFIGURATION_);
          Sequence configurations = kbConfiguration.getItemConfigurationSnapshot();
          if (configurations != null)
    	returnValue.addElement(configurations);
        }
        synchronized (data) {
          WorkspaceData wsData = (WorkspaceData)data;
          if (wsData.containmentHierarchyItemConfigurationSnapshot == null)
    	 wsData.containmentHierarchyItemConfigurationSnapshot = returnValue;
        }
        return (Vector)returnValue.clone();
      
  }


  /* Overriden Property - COMPLETE-CONFIGURATION-SNAPSHOT */
  /**
   * @undocumented
   */
  @Override
  public Vector getCompleteConfigurationSnapshot() throws G2AccessException {
    
        return getContainmentHierarchyItemConfigurationSnapshot();
      
  }


  /* Overriden Property - ITEM-CONFIGURATION-SNAPSHOT */
  /**
   * This goes to G2 only the first time.
   * @undocumented
   */
  @Override
  public Sequence getItemConfigurationSnapshot() throws G2AccessException {
    
        WorkspaceData wsData = (WorkspaceData)data;
        ItemData principalData = getPrincipalData();    
        if (wsData.configurationSnapshotCached) {
          return principalData.wsSnapshotOfConfiguration;
        } else {
          principalData.wsSnapshotOfConfiguration = getItemConfiguration();
          wsData.configurationSnapshotCached = true;
          return principalData.wsSnapshotOfConfiguration;
        }
      
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
   * Generated Property Setter for attribute -- MODULE-ASSIGNMENT
   * @param moduleAssignment new value to conclude for MODULE-ASSIGNMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setModuleAssignment(com.gensym.util.Symbol moduleAssignment) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MODULE_ASSIGNMENT_, moduleAssignment);
  }

  /**
   * Generated Property Getter for attribute -- MODULE-ASSIGNMENT
   * @return the value of the MODULE-ASSIGNMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getModuleAssignment() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MODULE_ASSIGNMENT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DEFAULT-WINDOW-POSITION-AND-SCALE
   * @param defaultWindowPositionAndScale new value to conclude for DEFAULT-WINDOW-POSITION-AND-SCALE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultWindowPositionAndScale(com.gensym.util.Structure defaultWindowPositionAndScale) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_WINDOW_POSITION_AND_SCALE_, defaultWindowPositionAndScale);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-WINDOW-POSITION-AND-SCALE
   * @return the value of the DEFAULT-WINDOW-POSITION-AND-SCALE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getDefaultWindowPositionAndScale() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_WINDOW_POSITION_AND_SCALE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EDGES-OF-WORKSPACE
   * @param edgesOfWorkspace new value to conclude for EDGES-OF-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEdgesOfWorkspace(com.gensym.util.Structure edgesOfWorkspace) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.EDGES_OF_WORKSPACE_, edgesOfWorkspace);
  }

  /**
   * Generated Property Getter for attribute -- EDGES-OF-WORKSPACE
   * @return the value of the EDGES-OF-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getEdgesOfWorkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EDGES_OF_WORKSPACE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PARENT-OF-SUBWORKSPACE
   * @param parentOfSubworkspace new value to conclude for PARENT-OF-SUBWORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setParentOfSubworkspace(com.gensym.classes.Block parentOfSubworkspace) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PARENT_OF_SUBWORKSPACE_, parentOfSubworkspace);
  }

  /**
   * Generated Property Getter for attribute -- PARENT-OF-SUBWORKSPACE
   * @return the value of the PARENT-OF-SUBWORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.Block getParentOfSubworkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PARENT_OF_SUBWORKSPACE_);
    return (com.gensym.classes.Block)retnValue;
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
   * Generated Property Setter for attribute -- WORKSPACE-MARGIN
   * @param workspaceMargin new value to conclude for WORKSPACE-MARGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWorkspaceMargin(int workspaceMargin) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WORKSPACE_MARGIN_, workspaceMargin);
  }

  /**
   * Generated Property Getter for attribute -- WORKSPACE-MARGIN
   * @return the value of the WORKSPACE-MARGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getWorkspaceMargin() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WORKSPACE_MARGIN_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- BACKGROUND-IMAGES
   * @param backgroundImages new value to conclude for BACKGROUND-IMAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBackgroundImages(com.gensym.util.Sequence backgroundImages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BACKGROUND_IMAGES_, backgroundImages);
  }

  /**
   * Generated Property Getter for attribute -- BACKGROUND-IMAGES
   * @return the value of the BACKGROUND-IMAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getBackgroundImages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BACKGROUND_IMAGES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FRAME-STYLE
   * @param frameStyle new value to conclude for FRAME-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFrameStyle(com.gensym.util.Symbol frameStyle) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FRAME_STYLE_, frameStyle);
  }

  /**
   * Generated Property Getter for attribute -- FRAME-STYLE
   * @return the value of the FRAME-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFrameStyle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FRAME_STYLE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TITLE-BAR-TEXT
   * @param titleBarText new value to conclude for TITLE-BAR-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTitleBarText(java.lang.Object titleBarText) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TITLE_BAR_TEXT_, titleBarText);
  }

  /**
   * Generated Property Getter for attribute -- TITLE-BAR-TEXT
   * @return the value of the TITLE-BAR-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getTitleBarText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TITLE_BAR_TEXT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- VIEW-PREFERENCES
   * @param viewPreferences new value to conclude for VIEW-PREFERENCES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setViewPreferences(com.gensym.util.Structure viewPreferences) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VIEW_PREFERENCES_, viewPreferences);
  }

  /**
   * Generated Property Getter for attribute -- VIEW-PREFERENCES
   * @return the value of the VIEW-PREFERENCES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getViewPreferences() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VIEW_PREFERENCES_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PREFER-BUFFERED-DRAWING
   * @param preferBufferedDrawing new value to conclude for PREFER-BUFFERED-DRAWING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPreferBufferedDrawing(boolean preferBufferedDrawing) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PREFER_BUFFERED_DRAWING_, new Boolean (preferBufferedDrawing));
  }

  /**
   * Generated Property Getter for attribute -- PREFER-BUFFERED-DRAWING
   * @return the value of the PREFER-BUFFERED-DRAWING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPreferBufferedDrawing() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PREFER_BUFFERED_DRAWING_);
    return ((Boolean)retnValue).booleanValue ();
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
   * Generated Property Getter for attribute -- KB-WORKSPACE-INITIAL-WIDTH
   * @return the value of the KB-WORKSPACE-INITIAL-WIDTH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getKbWorkspaceInitialWidthForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.KB_WORKSPACE_INITIAL_WIDTH_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- KB-WORKSPACE-INITIAL-HEIGHT
   * @return the value of the KB-WORKSPACE-INITIAL-HEIGHT attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getKbWorkspaceInitialHeightForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.KB_WORKSPACE_INITIAL_HEIGHT_);
    return ((Integer)retnValue).intValue ();
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

  /* Overriden  - WORKSPACE Event Listener - Adder1 */
  @Override
  public void addWorkspaceListener (WorkspaceListener wl) 
  throws G2AccessException {
    
        WorkspaceData wsData = (WorkspaceData)data;
        synchronized(wsData) {
          Structure initialInfo;
          if (wsData.subscribedToWksp) {
    	initialInfo = makeWorkspaceSnapshot();
          } else {
    	try {
    	  initialInfo = representWorkspace();
    	} catch (NoSuchAttributeException nsae) {
    	  throw new CorruptionException(nsae);
    	}
          }
          
          wsData.workspaceListener =
    	EventMulticaster.add (wsData.workspaceListener, wl);
          wl.receivedInitialDownload(new WorkspaceEvent(this,
    						    INITIAL_DOWNLOAD_,
    						    this,
    						    initialInfo));
        }
        decacheEvents(context, wsData.activeSubscriptionIndex);
      
  }

  /* Overriden  - WORKSPACE Event Listener - Remover1 */
  @Override
  public void removeWorkspaceListener (WorkspaceListener wl) throws G2AccessException   {
    
        WorkspaceData wsData = (WorkspaceData)data;
        synchronized(data) {
          wsData.workspaceListener =
    	EventMulticaster.remove (wsData.workspaceListener, wl);
          
          if (wsData.workspaceListener == null && wsData.subscribedToWksp) {
    	unrepresentWorkspace(context,wsData.activeSubscriptionIndex);
    	wsData.subscribedToWksp = false;
    	setWorkspaceUpdates (false);
          }
        }
      
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  /* Overriden method - MAKE-ITEM-DATA-LIST */
  private Sequence makeItemDataList() throws G2AccessException
 {
    
        Sequence items = ((WorkspaceData)data).items;
        int count = items.size();
        if (count == 0)
          return null;
        
        Sequence itemDataList = new Sequence();
        for (int i = 0; i < count; i++) {
          Structure info = ((G2__BaseImpl)items.elementAt(i)).getInitialInfo();
          itemDataList.addElement(info);
        }
        return itemDataList;
      
  }

  /* Overriden method - MAKE-WORKSPACE-SNAPSHOT */
  private Structure makeWorkspaceSnapshot() throws G2AccessException
 {
    
        Structure wkspInitialData = new Structure();
        Structure returnValue = new Structure();
        WorkspaceData wsData = (WorkspaceData)data;
        synchronized (wsData) {
          wkspInitialData.setAttributeValue(ITEM_INFO_LIST_,
    					((wsData).items).clone());
          wkspInitialData.setAttributeValue(ITEM_DATA_LIST_,
    					makeItemDataList());
          wkspInitialData.setAttributeValue(WORKSPACE_DIMENSIONS_,
    					getBounds());
          wkspInitialData.setAttributeValue(WORKSPACE_BACKGROUND_COLOR_,
     					getBackgroundColor());
          wkspInitialData.setAttributeValue(WORKSPACE_FOREGROUND_COLOR_,
     					getForegroundColor());
          returnValue.setAttributeValue(SUBSCRIPTION_HANDLE_,
    				    wsData.activeSubscriptionIndex);
          returnValue.setAttributeValue(WORKSPACE_INITIAL_DATA_,
    				    wkspInitialData);
          return returnValue;
        }
      
  }

  /* Overriden method - REPRESENT-WORKSPACE-0 */
  private Structure representWorkspace() throws G2AccessException,
  NoSuchAttributeException
 {
    
        
        WorkspaceData wsData = (WorkspaceData)data;
        synchronized (wsData) {
          wsData.containmentHierarchyItemConfigurationSnapshot = null;
          Structure initialInfo = representWorkspace(context,(KbWorkspace)this);
          Structure initialData =
        	(Structure)initialInfo.getAttributeValue(WORKSPACE_INITIAL_DATA_);
          setWorkspaceUpdates (true);
          wsData.subscribedToWksp = true;
          Integer subscriptionHandle =
        	((Integer)initialInfo.getAttributeValue (SUBSCRIPTION_HANDLE_, null));
          wsData.activeSubscriptionIndex = subscriptionHandle.intValue ();
          Sequence items =
    	(Sequence)initialData.getAttributeValue(ITEM_INFO_LIST_, null);
          Sequence itemDatas =
    	(Sequence)initialData.getAttributeValue(ITEM_DATA_LIST_, null);
          updateBounds(initialData);      
          //System.out.println("representWorkspace " + items + ";" + itemDatas);
          int count = items.size();
          for (int i=0;i<count;i++) {
    	Item itm = (Item)items.elementAt(i);
    	((G2__BaseImpl)itm).data.parentWorkspace = this;
    	if (itemDatas != null) {
    	  Structure info = (Structure)itemDatas.elementAt(i);
    	  ((G2__BaseImpl)itm).setInitialInfo(info);
    	}
    	if (itm != null) {
    	  setWorkspaceUpdatesForItem (true, (G2__BaseImpl)itm);
    	} else {
    	  throw new UnexpectedException(null, "null item");
    	}
          }
          wsData.items = items;
          return initialInfo;
        }
      
  }

  /* Overriden method - UPDATE-BOUNDS */
  private void updateBounds(Structure initialData)
 {
    
        java.lang.Object temporary = initialData.getAttributeValue(WORKSPACE_DIMENSIONS_, null);
    
        Integer width = null;
        Integer height = null;
        Integer centerX = null;
        Integer centerY = null;
        if (temporary != null) {
          try {
    	if (temporary instanceof Structure) {
    	  Structure dimensions = (Structure)temporary;
    	  Integer left = (Integer)dimensions.getAttributeValue(LEFT_);
    	  Integer top = (Integer)dimensions.getAttributeValue(TOP_);
    	  Integer right = (Integer)dimensions.getAttributeValue(RIGHT_);
    	  Integer bottom = (Integer)dimensions.getAttributeValue(BOTTOM_);
    	  width = right - left;
    	  height = bottom - top;
    	  centerX = left + width/2;
    	  centerY = -(top + height/2);       
    	} else if (temporary instanceof java.awt.Rectangle) {
    	  /* if we are in the third tier, then the bounds have already been
    	     set and will be returned as a java.awt.Rectangle, and so we need
    	     to handle that case.  We invert the algorithm used by
    	     ItemImpl.getBounds in order to choose our center points. */
    	  java.awt.Rectangle dimensions = (java.awt.Rectangle)temporary;
    	  width = dimensions.width;
    	  height = dimensions.height;
    	  centerX = dimensions.x+width/2;
    	  centerY = dimensions.y-height/2;
    	}
    	synchronized (data) {
    	  data.attributes.setAttributeValue(ITEM_X_POSITION_, centerX);
    	  data.attributes.setAttributeValue(ITEM_Y_POSITION_, centerY);
    	  data.attributes.setAttributeValue(ITEM_WIDTH_, width);
    	  data.attributes.setAttributeValue(ITEM_HEIGHT_, height);                  
    	}
          } catch (NoSuchAttributeException nsae) {
    	Trace.exception(nsae);
          }
        }
    
      
  }

  /* Overriden method - REFRESH-ITEM-DATA-FOR-WORKSPACE */
  @Override
  public void refreshItemDataForWorkspace(Sequence attrsToRefresh, WorkspaceListener wl) throws G2AccessException
 {
    
        if (!((WorkspaceData)data).subscribedToWksp) {
          return;
        }
        
        UiClientSession session =
          (UiClientSession)invokeTwAccessMethod(context, "retrieveSession",
         					    new Class[]{java.lang.Object.class},
         					    new java.lang.Object[]{wl});
        if (session == null)
          throw new G2AccessException(i18n.getString("notLoggedIn"));
        
        Structure initialData =
          (Structure)context.callRPC(G2_GET_UPDATED_WORKSPACE_INFORMATION_,
     				 new java.lang.Object[] {session, this, attrsToRefresh});
        
        Sequence items =
          (Sequence)initialData.getAttributeValue(ITEM_INFO_LIST_, null);
        Sequence itemDatas =
          (Sequence)initialData.getAttributeValue(ITEM_DATA_LIST_, null);
                                                                               
        updateBounds(initialData);
        int count = items.size();
        for (int i=0;i<count;i++) {
          G2__BaseImpl itm = (G2__BaseImpl)items.elementAt(i);
          itm.refreshWsInfo(this, (Structure)itemDatas.elementAt(i));
        }
      
  }

  /* Overriden method - UNREPRESENT-WORKSPACE */
  private void unrepresentWorkspace (G2Access context,
				     int activeSubscriptionIndex)
       throws G2AccessException
 {
    
        invokeTwAccessMethod(context, "unrepresentWorkspace",
    			 new Class[]{Integer.TYPE},
    			 new java.lang.Object[]{activeSubscriptionIndex});
        WorkspaceData wsData = (WorkspaceData)data;
        wsData.containmentHierarchyItemConfigurationSnapshot = null;
        for(Enumeration en = wsData.items.elements(); en.hasMoreElements();) {
          Item itm = (Item) en.nextElement();
          setWorkspaceUpdatesForItem (false, (G2__BaseImpl)itm);
        }
                                                                               
                                                
        wsData.items = new Sequence(0);
      
  }

  /* Overriden method - REPRESENT-WORKSPACE */
  private static Structure representWorkspace(G2Access context,
					      KbWorkspace workspace)
       throws G2AccessException
 {
    
        return (Structure)invokeTwAccessMethod(context, "representWorkspace",
    					   new Class[]{KbWorkspace.class},
    					   new java.lang.Object[]{workspace});
      
  }

  /* Overriden method - DECACHE-EVENTS */
  private static void decacheEvents(G2Access context,
				    Integer activeSubscriptionIndex)
       throws G2AccessException
 {
    
        invokeTwAccessMethod(context, "decacheEvents",
    			 new Class[]{Integer.class},
    			 new java.lang.Object[]{activeSubscriptionIndex});
      
  }

  /* Overriden method - WORKSPACE-IS-PROPRIETARY */
  @Override
  public boolean workspaceIsProprietary (final Sequence containers, final int index) throws G2AccessException
 {
	  	Sequence squence = containers;
        boolean wkspIsProprietary = false;
        ItemData principalData = getPrincipalData();
        if (principalData.itemIsProprietaryThroughContainment != null)
          return principalData.itemIsProprietaryThroughContainment.booleanValue ();
        
        if (squence == null)
        	squence = getContainmentHierarchy();
        java.lang.Object[] rpcArgs = new java.lang.Object[] {this, PROPRIETARY_PACKAGE_, Boolean.FALSE};
        java.lang.Object y = context.callRPC (G2_GET_TEXT_OF_ATTRIBUTE_, rpcArgs);
        String propPackage = (String)y;
        if (propPackage.equals ("none")) {
          if (squence.size () > index + 2) {
    	KbWorkspace nextWksp = (KbWorkspace) squence.elementAt (index + 2);
    	wkspIsProprietary = nextWksp.workspaceIsProprietary (squence, index + 2);
          }
        } else if (propPackage.equals ("not proprietary"))
          wkspIsProprietary = false;                               
        else {
          wkspIsProprietary = true;
        }
        
        if (wkspIsProprietary)
          getPrincipalData().itemIsProprietaryThroughContainment = Boolean.TRUE;
        else
          getPrincipalData().itemIsProprietaryThroughContainment = Boolean.FALSE;
        
        return wkspIsProprietary;
      
  }

  /* Overriden method - WORKSPACE-ITEM-ADDED */
  private void workspaceItemAdded(Item item, WorkspaceData wsData,
				  WorkspaceEvent event)
 {
    
        if (item instanceof G2__BaseImpl)
          ((G2__BaseImpl)item).data.parentWorkspace = this;
        Sequence items = wsData.items;
        synchronized (wsData) {
          if (items.contains (item))
            return;
        }
        Structure extraInfo = event.getInfo();
        java.lang.Object positionInfo
          = extraInfo.getAttributeValue(POSITION_OR_NEXT_LOWER_ITEM_, null);
    
        if (item.equals(positionInfo)) {
          positionInfo = null;
          extraInfo.deleteAttribute(POSITION_OR_NEXT_LOWER_ITEM_);
        }
        
        synchronized (wsData) {
          if (positionInfo == null) {
    	if (item instanceof Connection && item.isValid ()) {
    	  try {
    	    Sequence connectionIO = ((Connection)item).getConnectionInputAndOutput();
    	    java.lang.Object inputObject = connectionIO.elementAt(0);
    	    if (inputObject instanceof Item)
    	      positionInfo = inputObject;
    	  } catch(G2AccessException g2ae) {
    	    Trace.exception(g2ae);
    	  }
    	}
          }
          if (positionInfo == null) {
    	items.addElement(item);
          } else if (positionInfo instanceof Symbol) {
    	items.insertElementAt(item, 0);
          } else {
    	int nextLowerItemPosition =
    	  items.lastIndexOf(positionInfo);
    	if (nextLowerItemPosition > -1) {
    	  items.insertElementAt(item, nextLowerItemPosition + 1);
    	} else {
    	  items.addElement(item);
    	  Trace.exception(new IllegalArgumentException
    			  (i18n.format("kbwiPositionElementNotFound",
    				       new java.lang.Object [] {item, this, positionInfo})));
    	}
          }
        }
      
  }

  /* Overriden method - ATTRIBUTE-SENDS-UPDATES */
  @Override
  protected boolean attributeSendsUpdates (Symbol attrName)
 {
    
        return super.attributeSendsUpdates(attrName) ||
          BACKGROUND_COLOR_.equals(attrName) ||
          FOREGROUND_COLOR_.equals(attrName);
      
  }

  /* Overriden method - ADD-WORKSPACE-LISTENER-RETRIEVING-STATE */
  @Override
  public Structure addWorkspaceListenerRetrievingState(WorkspaceListener wl)
  throws G2AccessException
 {
    
        refreshItemDataForWorkspace(null, wl);
        synchronized(data) {
          addWorkspaceListener(wl);
          return makeWorkspaceSnapshot();
        }
      
  }

  /* Overriden method - HANDLE-ITEM-LAYER-CHANGE */
  private void handleItemLayerChange(WorkspaceEvent event)
 {
    
        try {
          java.lang.Object source = event.getSource();
          Item item = event.getItem();
          Structure info = event.getInfo();
          java.lang.Object positionOrNextLowerItem =
    	info.getAttributeValue(POSITION_OR_NEXT_LOWER_ITEM_, null);
          Structure initialInfo = ((G2__BaseImpl)item).getInitialInfo();
          initialInfo.setAttributeValue(POSITION_OR_NEXT_LOWER_ITEM_, positionOrNextLowerItem);
          processWorkspaceEvent(new WorkspaceEvent(source, ITEM_REMOVE_, item, null));
          processWorkspaceEvent(new WorkspaceEvent(source, ITEM_INSERT_, item,
    					       initialInfo));
        } catch (G2AccessException g2ae) {
          throw new UnexpectedException(g2ae);
        }
      
  }

  /* Overriden method - PROCESS-WORKSPACE-EVENT */
  @Override
  public void processWorkspaceEvent (WorkspaceEvent evt)
 {
    
       WorkspaceListener workspaceListener = null;
       WorkspaceData wsData = (WorkspaceData)data;
        
       if (wsData == null)
         return;
    
       synchronized(wsData) {
         workspaceListener = wsData.workspaceListener;
                                                                   
                                                                            
                                                              
         if (!isValid() || workspaceListener == null)
           return;
       }
        
            Symbol notfnCode = evt.getNotificationCode ();
            Item changedItem = evt.getItem ();
    	
            if (changedItem == null)
              System.out.println ("Got WorkspaceEvent with null item -> " + evt);
            else if (!changedItem.isValid()) {
    	  boolean actuallyRemoved = false;
    	  synchronized (wsData) {
    	    actuallyRemoved = wsData.items.removeElement(changedItem);
    	  }
    	  if (actuallyRemoved) {
                                                                         
    	    wsData.workspaceListener.workspaceItemRemoved (evt);
    	  }
    	  return;
    	}
    	else
              ((G2__BaseImpl)changedItem).updateItemForWorkspaceEvent (evt);
            int id = evt.getID ();
        
            Trace.send(30, traceKey, i18nTrace,
        	       "kbwiprocessWorkspaceEvent", notfnCode, changedItem,
        	       wsData.workspaceListener);
        
            switch (id)
              {
              case WorkspaceEvent.ITEM_INSERT:
            	  workspaceItemAdded(changedItem, wsData, evt);
            	  wsData.workspaceListener.workspaceItemAdded (evt);
            	  break;
              case WorkspaceEvent.ITEM_REMOVE:
            	  synchronized (wsData) {
            		  wsData.items.removeElement(changedItem);
            	  }
            	  wsData.workspaceListener.workspaceItemRemoved (evt);
            	  break;
              case WorkspaceEvent.ITEM_MOVE: 
            	  wsData.workspaceListener.workspaceItemMoved (evt); 
            	  break;
              case WorkspaceEvent.ITEM_RESIZE: 
            	  wsData.workspaceListener.workspaceItemResized (evt); 
            	  break;
              case WorkspaceEvent.ITEM_ROTATE: 
            	  wsData.workspaceListener.workspaceItemRotated (evt); 
            	  break;
              case WorkspaceEvent.ITEM_COLOR_PATTERN_CHANGE: 
            	  wsData.workspaceListener.workspaceItemColorsChanged (evt); 
            	  break;
              case WorkspaceEvent.ITEM_ICON_VARIABLES_CHANGE: 
            	  wsData.workspaceListener.workspaceItemIconVariablesChanged (evt); 
            	  break;
              case WorkspaceEvent.ITEM_CHANGE: 
            	  wsData.workspaceListener.workspaceItemAttributesChanged (evt); 
            	  break;
              case WorkspaceEvent.WORKSPACE_RESIZED: 
            	  wsData.workspaceListener.workspaceResized (evt); 
            	  break;
              case WorkspaceEvent.ITEM_LAYER_CHANGE:
            	  handleItemLayerChange(evt); 
            	  break;
              default:
              }      
      
  }

  /* Overriden method - HIDE */
  @Override
  public void hide()
       throws G2AccessException
 {
    
        UiClientSession uiClientSession = retrieveSession(context);
        java.lang.Object[] args
          = new java.lang.Object[] {this, uiClientSession};
        context.callRPC(G2_HIDE_WORKSPACE_, args);
      
  }

  /* Overriden method - MAKE-DATA-FOR-ITEM */
  @Override
  protected ItemData makeDataForItem()
 {
    
        return new WorkspaceData();
      
  }

  /* Overriden method - SHOW */
  @Override
  public void show(Structure particulars)
       throws G2AccessException
 {
    
        UiClientSession uiClientSession = retrieveSession(context);
        java.lang.Object[] args
          = new java.lang.Object[] {this, particulars, uiClientSession};
        context.callRPC(G2_SHOW_WORKSPACE_, args);
      
  }

  /* Overriden method - SHRINK-WRAP */
  @Override
  public void shrinkWrap()
       throws G2AccessException
 {
    
        /*yduj: as far as I can tell, what this code does is to request
          the G2 set the workspace bounds to the bounds of the first
          element on the workspace.  G2 itself has code that says "but
          everything else won't fit!  I'll just make it big enough to fit,
          OK?"  Then, we later get a resize event for the change in size
          of the workspace (interestingly, it is a resize item, rather
          than a resize workspace event), and so eventually we have a clue
          how big the workspace is.  However, the person responsible for
          this horrible kluge should at least be embarrassed about it!
          And should have commented what they were doing originally.  I
          think it's kind of odd that we go to all this careful calculation
          of the size, rather than just saying one pixel will do, given
          what we're really doing.*/
        Item[] items = getItems();
        if (items == null ||
    	items.length == 0) return;
        Item item = items[0];
        int x = item.getItemXPosition();
        int y = item.getItemYPosition();
        int width = item.getItemWidth();
        int height = item.getItemHeight();
        int lft = x - (width/2);
        int rgt = lft + Math.max(width, 1);
        int top = y + (height/2);
        int bot = top - Math.max(height, 1);
        shrinkwrapping = true;
        setBounds (lft, top, rgt, bot);
      
  }

  
}
