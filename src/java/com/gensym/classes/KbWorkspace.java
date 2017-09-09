/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      KbWorkspace.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:00:20 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import java.util.Vector;
import com.gensym.core.GensymApplication;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.Enumeration;
import com.gensym.util.symbol.G2ClassSymbols;

public interface KbWorkspace extends com.gensym.classes.Item, com.gensym.classes.Workspace {

  public static final Symbol KB_WORKSPACE_ = com.gensym.util.symbol.G2ClassSymbols.KB_WORKSPACE_;
  static final Symbol g2ClassName = KB_WORKSPACE_;
  static final Symbol[] classInheritancePath = new Symbol[] {KB_WORKSPACE_, ITEM_, WORKSPACE_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol KB_WORKSPACE_INITIAL_WIDTH_ = Symbol.intern ("KB-WORKSPACE-INITIAL-WIDTH");
  static final Symbol KB_WORKSPACE_INITIAL_HEIGHT_ = Symbol.intern ("KB-WORKSPACE-INITIAL-HEIGHT");

  static final Symbol[] staticAttributes = new Symbol[] {KB_WORKSPACE_INITIAL_WIDTH_, KB_WORKSPACE_INITIAL_HEIGHT_};


  /* Overriden Property - G2WKSP-SUBSCRIPTION-HANDLE */
  /**
   * @undocumented
   * @deprecated
   */
  public int getG2WkspSubscriptionHandle();

  /* Overriden Property - ITEMS */
  /**
   * @undocumented Returns the items on the workspace
   * if it is subscribed to. Returns null otherwise.
   */
  public Item[] getItems ();

  /* Overriden Property - SHRINKWRAPPING */
  /**
   * @undocumented
   */
  public boolean getShrinkwrapping ();
  /**
   * @undocumented
   */
  public void setShrinkwrapping (boolean value);

  /* Overriden Property - CONTAINMENT-HIERARCHY-ITEM-CONFIGURATION-SNAPSHOT */
  /**
   * @undocumented
   */
  public Vector getContainmentHierarchyItemConfigurationSnapshot()
  throws G2AccessException;

  /* Overriden Property - COMPLETE-CONFIGURATION-SNAPSHOT */
  /**
   * @undocumented
   */
  @Override
  public Vector getCompleteConfigurationSnapshot() throws G2AccessException;

  /* Overriden Property - ITEM-CONFIGURATION-SNAPSHOT */
  /**
   * This goes to G2 only the first time.
   * @undocumented
   */
  @Override
  public Sequence getItemConfigurationSnapshot() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BACKGROUND-COLOR
   * @return the value of the BACKGROUND-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BACKGROUND-COLOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getBackgroundColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BACKGROUND-COLOR
   * @param backgroundColor new value to conclude for BACKGROUND-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBackgroundColor(com.gensym.util.Symbol backgroundColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FOREGROUND-COLOR
   * @return the value of the FOREGROUND-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FOREGROUND-COLOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getForegroundColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FOREGROUND-COLOR
   * @param foregroundColor new value to conclude for FOREGROUND-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setForegroundColor(com.gensym.util.Symbol foregroundColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MODULE-ASSIGNMENT
   * @return the value of the MODULE-ASSIGNMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MODULE-ASSIGNMENT is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getModuleAssignment() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MODULE-ASSIGNMENT
   * @param moduleAssignment new value to conclude for MODULE-ASSIGNMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setModuleAssignment(com.gensym.util.Symbol moduleAssignment) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-WINDOW-POSITION-AND-SCALE
   * @return the value of the DEFAULT-WINDOW-POSITION-AND-SCALE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-WINDOW-POSITION-AND-SCALE is : 
   * (OR NoItem
      (Structure 
        X Integer
        Y Integer
        X-SCALE Float
        Y-SCALE Float))
   *
   */
  public com.gensym.util.Structure getDefaultWindowPositionAndScale() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-WINDOW-POSITION-AND-SCALE
   * @param defaultWindowPositionAndScale new value to conclude for DEFAULT-WINDOW-POSITION-AND-SCALE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultWindowPositionAndScale(com.gensym.util.Structure defaultWindowPositionAndScale) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EDGES-OF-WORKSPACE
   * @return the value of the EDGES-OF-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EDGES-OF-WORKSPACE is : 
   * (Structure 
    LEFT Integer
    TOP Integer
    RIGHT Integer
    BOTTOM Integer)
   *
   */
  public com.gensym.util.Structure getEdgesOfWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EDGES-OF-WORKSPACE
   * @param edgesOfWorkspace new value to conclude for EDGES-OF-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEdgesOfWorkspace(com.gensym.util.Structure edgesOfWorkspace) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PARENT-OF-SUBWORKSPACE
   * @return the value of the PARENT-OF-SUBWORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PARENT-OF-SUBWORKSPACE is : 
   * (OR NoItem
      (Class BLOCK))
   *
   */
  public com.gensym.classes.Block getParentOfSubworkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PARENT-OF-SUBWORKSPACE
   * @param parentOfSubworkspace new value to conclude for PARENT-OF-SUBWORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setParentOfSubworkspace(com.gensym.classes.Block parentOfSubworkspace) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NAME-BOX
   * @return the value of the NAME-BOX attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-BOX is : 
   * (OR NoItem
      (Structure 
        COLOR
          (Structure 
            BACKGROUND-COLOR Symbol
            TEXT-COLOR Symbol)
        POSITION
          (OR (MEMBER AT-STANDARD-POSITION)
              (Structure 
                X-OFFSET Integer
                Y-OFFSET Integer))))
   *
   */
  public com.gensym.util.Structure getNameBox() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NAME-BOX
   * @param nameBox new value to conclude for NAME-BOX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameBox(com.gensym.util.Structure nameBox) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- KB-WORKSPACE-INITIAL-WIDTH
   * @return the value of the KB-WORKSPACE-INITIAL-WIDTH attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for KB-WORKSPACE-INITIAL-WIDTH is : 
   * Integer
   *
   */
  public int getKbWorkspaceInitialWidthForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- KB-WORKSPACE-INITIAL-HEIGHT
   * @return the value of the KB-WORKSPACE-INITIAL-HEIGHT attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for KB-WORKSPACE-INITIAL-HEIGHT is : 
   * Integer
   *
   */
  public int getKbWorkspaceInitialHeightForClass() throws G2AccessException;

  /* Overriden  - WORKSPACE Event Listeners Management */
  /* Adder */
  /**
   * Register for notification of changes to Items on the kb-workspace.
   * This information is typically necessary to render a view of the
   * kb-workspace.
   * @exception G2AccessException If an error occurs during
   * communication with G2.
   */
  public void addWorkspaceListener (WorkspaceListener wl) 
  throws G2AccessException;
  /* Remover */
  /**
   * Deregister for notification regarding changes on the kb-workspace
   * @exception G2AccessException If an error occurs during
   * communication with G2.
   */
  public void removeWorkspaceListener (WorkspaceListener wl) throws G2AccessException;

  /* Overriden method - REFRESH-ITEM-DATA-FOR-WORKSPACE */
  /**
   * Temporary measure to compensate for the lack of updates
   * (via the workapce protocol) for such things
   * as the ITEM-CONFIGURATIONS and CONNECTION-STYLES.
   * Only does something if there is an existing subscription.
   * The WorkspaceListener argument is for the support of three
   * tier connections: the TwRMIServerImpl has no UiClientSession
   * object of its own, and must use the one from the
   * TwServerQueueManager (which will be the WorkspaceListener
   * in that case). In the two-tier case, retrieveSession ignores
   * its argument.
   * @undocumented
   */
  public void refreshItemDataForWorkspace(Sequence attrsToRefresh, WorkspaceListener wl) throws G2AccessException;

  /* Overriden method - WORKSPACE-IS-PROPRIETARY */
  /**
   * @undocumented
   */
  public boolean workspaceIsProprietary (Sequence containers, int index) throws G2AccessException;

  /* Overriden method - ADD-WORKSPACE-LISTENER-RETRIEVING-STATE */
  /**
   * @undocumented
   */
  public Structure addWorkspaceListenerRetrievingState(WorkspaceListener wl)
  throws G2AccessException;

  /* Overriden method - PROCESS-WORKSPACE-EVENT */
  /**
   * @undocumented Called from ntw.TwGateway, ntw.rmi.TwRMIClientImpl, wksp.WorkspaceViewAdapter
   */
  public void processWorkspaceEvent (WorkspaceEvent evt);

  /* Overriden method - HIDE */
  /**
   * Requests G2 to hide this workspace on this item's UiClientSession.
   * this workspaces items.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call.
   */
  public void hide()
       throws G2AccessException;

  /* Overriden method - SHOW */
  /**
   * Requests G2 to show this workspace on this item's UiClientSession.
   * this workspaces items.
   * @param particulars a structure containing more specific instructions
   * as to how to show the workspace, which may contain any of the
   * following attributes:
   *  <code>
   *  symbolic-x-scale 
   *  symbolic-y-scale 
   *  symbolic-x-in-workspace 
   *  symbolic-y-in-workspace 
   *  symbolic-x-in-window 
   *  symbolic-y-in-window 
   *  x-offset-units 
   *  y-offset-units 
   *  symbolic-x-offset-direction 
   *  symbolic-y-offset-direction 
   *  x-magnification 
   *  y-magnification 
   *  x-in-workspace 
   *  y-in-workspace 
   *  x-in-window 
   *  y-in-window
   *  </code>. 
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call.
   */
  public void show(Structure particulars)
       throws G2AccessException;

  /* Overriden method - SHRINK-WRAP */
  /**
   * Sets the bounds of this workspace to a minimum size surrounding 
   * this workspaces items.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public void shrinkWrap()
       throws G2AccessException;

}
