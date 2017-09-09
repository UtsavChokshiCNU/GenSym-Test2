/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceListener.java
 *
 *   Description: 
 *     
 *
 *	 Author(s):
 *		Robert Penny,Paul B. Konigsberg		May/97
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.util;

/**
 * The listener interface for handling workspace events.
 *
 */

public interface WorkspaceListener extends java.util.EventListener {

  /**
   * Invoked when the listener is added
   * (within the context of the addWorkspaceListener method).
   */
  public void receivedInitialDownload (WorkspaceEvent event);

  /**
   * Invoked when an item is transferred onto the Workspace
   */
  public void workspaceItemAdded (WorkspaceEvent event);

  /**
   * Invoked when an item is transferred off the Workspace
   */
  public void workspaceItemRemoved (WorkspaceEvent event);

  /**
   * Invoked when the Workspace bounds changes
   */
  public void workspaceResized (WorkspaceEvent event);

  /**
   * Invoked when an item on the workspace is moved
   */
  public void workspaceItemMoved (WorkspaceEvent event);

  /**
   * Invoked when an item on the workspace is resized
   */
  public void workspaceItemResized (WorkspaceEvent event);

  /**
   * Invoked when an item on the workspace is rotated
   */
  public void workspaceItemRotated (WorkspaceEvent event);

  /**
   * Invoked when an item on the workspace changes colors
   */
  public void workspaceItemColorsChanged (WorkspaceEvent event);

  /**
   * Invoked when the icon-variables of an item on the workspace changes
   */
  public void workspaceItemIconVariablesChanged (WorkspaceEvent event);

  /**
   * Invoked when one of the interesting virtual attributes of an
   * item changes.
   */
  public void workspaceItemAttributesChanged (WorkspaceEvent event);
}
