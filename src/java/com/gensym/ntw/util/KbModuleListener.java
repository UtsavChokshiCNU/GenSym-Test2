
package com.gensym.ntw.util;

/**
 * Interface for listening to changes in the module
 * hierarchy of a KB. The KbEvent argument to each method
 * contains all the data necessary for the client to
 * determine the extent of the change.
 */
public interface KbModuleListener extends java.util.EventListener {

  /**
   * Listener is called when the subscription is added
   */
  public void receivedInitialModules (KbEvent evt);

  /**
   * Invoked when a new module is added
   */
  public void moduleCreated (KbEvent evt);

  /**
   * Invoked when a module is deleted
   */
  public void moduleDeleted (KbEvent evt);

  /**
   * Invoked when the top-level-module of a Module
   * changes.
   */
  public void moduleNameChanged (KbEvent evt);

  /**
   * Invoked when the directly-required-modules of a
   * Module changes
   */
  public void moduleDependencyChanged (KbEvent evt);

  /**
   * Invoked when the KB is cleared.
   */
  public void kbCleared (KbEvent evt);

  /**
   * Invoked when a top-level workspace of a Module
   * is added.
   */
  public void topLevelWorkspaceAdded(KbEvent evt);

  /**
   * Invoked when a top-level workspace of a Module
   * is deleted.
   */
  public void topLevelWorkspaceDeleted(KbEvent evt);

}
