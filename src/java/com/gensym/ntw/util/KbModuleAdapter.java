
package com.gensym.ntw.util;

/**
 * Empty implementation of the KbModuleListener
 * interface. This class is provided as a convienence
 * adapter for easily creating listeners by extending this class
 * and overriding only the methods of interest.
 */
public class KbModuleAdapter implements KbModuleListener {

  @Override
  public void receivedInitialModules (KbEvent evt) {}

  @Override
  public void moduleCreated (KbEvent evt) {}

  @Override
  public void moduleDeleted (KbEvent evt) {}

  @Override
  public void moduleNameChanged (KbEvent evt) {}

  @Override
  public void moduleDependencyChanged (KbEvent evt) {}

  @Override
  public void kbCleared (KbEvent evt) {}

  @Override
  public void topLevelWorkspaceAdded(KbEvent evt) {}

  @Override
  public void topLevelWorkspaceDeleted(KbEvent evt) {}

}
