/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceShowingListener.java
 *
 *   Description: 
 *     
 *
 *	 Author:
 *		Joe Devlin		Sept/97
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.ntw;

/**
 * Interface for WorkspaceShowingEvents
 *  WorkspaceShowingEvents are generated when G2 invokes a show/hide
 *  action on a workspace programmatically.
 */

public interface WorkspaceShowingListener extends java.util.EventListener {

  /**
   * Called when the KB wants to display a kb-workspace on this
   * TwConnection.
   */
  public void showWorkspace(WorkspaceShowingEvent event);

  /**
   * Called when the KB wants to hide a currently showing kb-workspace
   * on this TwConnection.
   */
  public void hideWorkspace(WorkspaceShowingEvent event);
}
