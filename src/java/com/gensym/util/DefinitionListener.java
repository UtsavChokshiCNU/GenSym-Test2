/*
 * @(#)DefinitionListener.java 1.0 97/10/22
 *
 * Copyright (C) 1986-2017 Gensym Corporation. All Rights reserved.
 *
 */
package com.gensym.util;

/**
 * The listener interface for receiving class change events
 * from G2 Definitions.
 *
 * @version 1.0 10/22/97
 * @author vkp
 */
public interface DefinitionListener extends java.util.EventListener {

  /**
   * Invoked when an attribute of the definition changes.
   */
  public void staticAttributeChanged (DefinitionEvent e);

  /**
   * Invoked when the class-name in the definition changes.
   */
  public void classNameChanged (DefinitionEvent e);
  
  /**
   * Invoked when the direct-superior-classes in the definition changes.
   */
  public void directSuperiorClassesChanged (DefinitionEvent e);

  /**
   * Invoked when the definition is deleted.
   */
  public void deleted (DefinitionEvent e);

  /**
   * Invoked when the inheritance-path of the class
   * being defined by the class-definition changes
   */
  public void classInheritancePathChanged (DefinitionEvent e);

  /**
   *
   */
  public void classSpecificAttributesChanged (DefinitionEvent e);
}
